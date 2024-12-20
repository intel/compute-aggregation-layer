#
# Copyright (C) 2022-2024 Intel Corporation
#
# SPDX-License-Identifier: MIT
#

import concurrent
import copy
import datetime
import itertools
import multiprocessing
import os
import re
import string
import sys
import time
import threading
import yaml

from concurrent.futures import ThreadPoolExecutor
from collections import defaultdict
from mako.template import Template
import mako

license_fname = "LICENSE.md"
base_license = "../../LICENSE.md"

class ServerAccess:
    def __init__(self, src: str):
        self.str = src

    def read_only(self) -> bool:
        return self.str == "read"

    def write_only(self) -> bool:
        return self.str == "write"

    def none(self) -> bool:
        return self.str == "none"

    def read_write(self) -> bool:
        return self.str == "read_write"

    def can_read(self) -> bool:
        return not (self.write_only() or self.none())

    def can_write(self) -> bool:
        return not (self.read_only() or self.none())

class Translate:
    def __init__(self, src: str):
        self.str = src

    def format(self, dst, arg, index="", dst_mem="", func_name="", dst_captures="") -> str:
        return self.str.format(dst=dst, arg=arg, index=index, dst_mem=dst_mem, func_name=func_name, dst_captures=dst_captures)


class DaemonAction:
    def __init__(self, src: str):
        self.str = src

    def format(self, arg) -> str:
        return self.str.format(arg=arg)


class NumElements:
    def __init__(self, src: str):
        self.str = src
        self.int = None
        try:
            self.int = int(src)
        except BaseException:
            pass

    def is_constant(self) -> bool:
        return None is not self.int

    def get_constant(self) -> int:
        return self.int

    def is_nullterminated(self) -> bool:
        return self.str == "nullterminated"

    def is_nullterminated_key(self) -> bool:
        return self.str == "nullterminated_key"

    def is_single_element(self) -> bool:
        return self.is_constant and (self.get_constant() == 1)

    def is_complex(self):
        return self.is_nullterminated() or self.is_nullterminated_key() or ("(" in self.str)


class Type:
    def __init__(self, src: str):
        self.str = src

    def get_size_in_bytes(self) -> int:
        if self.str in ("cl_int", "cl_uint", "cl_device_info", "cl_platform_info"):
            return 4
        if self.str in ("size_t"):
            return 8
        assert False

    def is_void(self) -> bool:
        return self.str == "void"

    def get_deref_type(self) -> str:
        return self.str if not self.is_void() else "char"

    def dereferenceable_str(self) -> str:
        return "char" if self.is_void() else self.str


class Kind:
    def __init__(self, src: str):
        self.str = src

    def is_scalar(self) -> bool:
        return self.str == "scalar"

    def is_pointer(self) -> bool:
        return self.str in ("ptr_array", "ptr_va", "func_ptr")

    def is_pointer_to_array(self) -> bool:
        return self.str == "ptr_array"

    def is_pointer_va(self) -> bool:
        return self.str == "ptr_va"

    def is_pointer_usm(self) -> bool:
        return self.str == "ptr_usm_va"

    def is_pointer_zero_copy_malloc_shmem(self) -> bool:
        return self.str == "ptr_zero_copy_malloc_shmem_va"

    def is_pointer_remapped(self) -> bool:
        return self.str == "ptr_remapped_va"

    def is_pointer_function(self) -> bool:
        return self.str == "ptr_func"

    def is_struct(self) -> bool:
        return self.str == "struct"

    def is_opaque(self) -> bool:
        return self.str == "opaque"

    def is_opaque_list(self) -> bool:
        return self.str == "opaque_list"

def get_ptr_sharing_kind_abbreviation(kind : Kind):
    if kind.is_pointer_zero_copy_malloc_shmem():
        return "shared"
    elif kind.is_pointer_usm():
        return "usm"
    if kind.is_pointer_remapped():
        return "remapped"
    else :
        return "local"

class KindVariant:
    def __init__(self, src: dict):
        self.kind = Kind(src.get("kind")) if "kind" in src.keys() else None
        self.capture_details = CaptureDetails(src.get("capture_details", {})) if "capture_details" in src.keys() else None

class Element:
    def __init__(self, src: dict):
        self.type = Type(src.get("type"))
        self.kind = Kind(src.get("kind"))
        self.translate_before = Translate(src["translate_before"]) if "translate_before" in src.keys() else None
        self.translate_after = Translate(src["translate_after"]) if "translate_after" in src.keys() else None
        self.kind_details = KindDetails(src["kind_details"]) if "kind_details" in src.keys() else None

    def is_kind_complex(self) -> bool:
        return self.kind_details is not None

    def get_calculated_elements_count(self, name, index):
        assert self.kind.is_pointer_to_array

        if self.kind_details.num_elements.is_nullterminated():
            return f"Cal::Utils::countNullterminated({name}[{index}])"
        elif self.kind_details.num_elements.is_nullterminated_key():
            return f"Cal::Utils::countNullterminatedKey({name}[{index}])"
        elif self.kind_details.num_elements.is_constant():
            return self.kind_details.num_elements.str
        else:
            return self.kind_details.num_elements.str.format(name=name, index=index)

    def get_calculated_array_size(self, name="", index="", count: str = None):
        assert self.kind.is_pointer_to_array

        mul = "" if self.kind_details.element.type.is_void() else f" * sizeof({self.kind_details.element.type.str})"

        if not count:
            count = self.get_calculated_elements_count(name, index)
        return f"{count}{mul}"


class UnderlyingType:
    def __init__(self, src: dict):
        self.type = Type(src["type"]) if "type" in src else None
        self.kind = Kind(src["kind"]) if "kind" in src else None

class OpaqueType:
    def __init__(self, src: dict):
        self.type_name = src.get("extension_type", "")
        self.extension_enum_value = src.get("extension_enum_value", None)

class KindDetails:
    def __init__(self, src: dict):
        self.num_elements = NumElements(src.get("num_elements", {}))
        self.is_num_elements_ptr_to_capturable_arg = src.get("is_num_elements_ptr_to_capturable_arg", False)
        self.can_be_null = src.get("can_be_null", False)
        self.element = Element(src.get("element", {}))
        self.server_access = ServerAccess(src.get("server_access", {}))
        self.variable_generator = src.get("variable_generator", None)
        self.underlying_type = UnderlyingType(src.get("underlying_type", {}))
        self.iterator_type = src.get("iterator_type", "")
        self.opaque_traits_name = src.get("opaque_traits_name", "")
        self.possible_nontrivial_nested_types = [OpaqueType(t) for t in src.get("possible_nontrivial_nested_types", {})]
        self.possible_nontrivial_nested_types_by_name = {opaque_type.type_name : opaque_type for opaque_type in self.possible_nontrivial_nested_types}
        self.requires_opaque_elements_translation_before = src.get("requires_opaque_elements_translation_before", False)
        self.always_queried = src.get("always_queried", False)
        self.is_op_end_event = src.get("op_end_event", False)

class CaptureMode:
    def __init__(self, src: str):
        self.str = src

    def is_inline_mode(self):
        return self.str == "inline"

    def is_standalone_mode(self):
        return self.str == "standalone"

    def is_staging_usm_mode(self):
        return self.str == "staging_usm"

class CaptureReclaimMethod:
    def __init__(self, src: str):
        self.str = src

    def is_immediate_mode(self):
        return self.str == "immediate"

    def format(self, ptr):
        try:
            return self.str.format(allocation=ptr)
        except Exception as e:
            raise Exception(f"CaptureReclaimMethod format was ${self.str} allocation was {ptr}") from e

class CaptureDetails:
    def __init__(self, src: dict):
        self.mode = CaptureMode(src.get("mode", "inline"))
        self.reclaim_method = CaptureReclaimMethod(src.get("reclaim_method", "immediate"))
        self.replayable_command = src.get("replayable_command", False)

class ArgTraits:
    def __init__(self, arg, parent_function, is_implicit_arg):
        self.arg = arg
        self.uses_standalone_allocation = arg.capture_details.mode.is_standalone_mode()
        self.uses_staging_usm_allocation = arg.capture_details.mode.is_staging_usm_mode()
        if self.uses_standalone_allocation or self.uses_staging_usm_allocation:
            assert( arg.kind.is_pointer() )
        self.uses_inline_dynamic_mem = arg.kind.is_pointer_to_array() and (not arg.kind_details.num_elements.is_constant()) and (not self.uses_standalone_allocation) and (not self.uses_staging_usm_allocation)
        self.uses_dynamic_arg_getter = parent_function.traits.uses_dynamic_arg_getters and self.uses_inline_dynamic_mem
        self.uses_nested_capture = arg.kind.is_pointer_to_array() and arg.kind_details.element.kind.is_pointer_to_array()
        self.is_implicit_arg = is_implicit_arg

class Arg:
    def __init__(self, arg_id, src: dict):
        self.arg_id = int(arg_id)
        self.name = src["name"]
        self.type = Type(src.get("type"))
        self.kind = Kind(src.get("kind"))
        self.kind_variants = [KindVariant(k) for k in src.get("kind_variants")] if "kind_variants" in src.keys() else None
        self.ignore = src.get("ignore", False)
        self.kind_details = KindDetails(src["kind_details"]) if "kind_details" in src.keys() else None
        self.translate_before = Translate(src["translate_before"]) if "translate_before" in src.keys() else None
        self.translate_after = Translate(src["translate_after"]) if "translate_after" in src.keys() else None
        self.daemon_action_on_success = DaemonAction(src["daemon_action_on_success"]) if "daemon_action_on_success" in src.keys() else None
        self.daemon_action_at_end = DaemonAction(src["daemon_action_at_end"]) if "daemon_action_at_end" in src.keys() else None
        self.server_access = ServerAccess(src.get("server_access", {}))
        self.capture_details = CaptureDetails(src.get("capture_details", {}))

    def to_str(self, inject_pointer=0, inject_ref=False) -> str:
        if self.kind.is_pointer_function():
            return self.kind_details.variable_generator.format(arg=self.name)
        inner_modifier = " "
        if inject_pointer:
            inner_modifier = "*" * inject_pointer
        if inject_ref:
            inner_modifier += "&"
        return f"{self.type.str}{inner_modifier}{self.name}"

    def is_kind_complex(self) -> bool:
        return self.kind_details is not None

    def get_calculated_elements_count(self, arg_prefix: str = "", captures_prefix: str = ""):
        assert self.kind.is_pointer_to_array
        if self.kind_details.num_elements.is_nullterminated():
            return f"Cal::Utils::countNullterminated({arg_prefix}{self.name})"
        elif self.kind_details.num_elements.is_nullterminated_key():
            return f"Cal::Utils::countNullterminatedKey({arg_prefix}{self.name})"
        elif self.kind_details.num_elements.is_constant():
            return self.kind_details.num_elements.str
        elif self.kind_details.is_num_elements_ptr_to_capturable_arg:
            return f"({arg_prefix}{self.kind_details.num_elements.str} ? *{arg_prefix}{self.kind_details.num_elements.str} : 0)"
        else:
            if ("{arg_prefix}" in self.kind_details.num_elements.str) or ("{captures_prefix}" in self.kind_details.num_elements.str):
                return self.kind_details.num_elements.str.format(arg_prefix=arg_prefix, captures_prefix=captures_prefix)
            else:
                return f"{arg_prefix}{self.kind_details.num_elements.str}"

    def get_calculated_array_size(self, arg_prefix: str = "", captures_prefix: str = "", count: str = None):
        assert self.kind.is_pointer_to_array

        mul = "" if self.kind_details.element.type.is_void() else f" * sizeof({self.kind_details.element.type.str})"

        if not count:
            count = self.get_calculated_elements_count(arg_prefix, captures_prefix)
        return f"{count}{mul}"

    def create_traits(self, parent_function, is_implicit_arg) -> None:
        self.traits = ArgTraits(self, parent_function, is_implicit_arg)

    def is_always_queried(self) -> bool:
        return self.is_kind_complex() and self.kind_details.always_queried

    def apply_kind_variant(self, variant_id) :
        variant = self.kind_variants[variant_id]
        if variant.kind:
            self.kind = variant.kind
        if variant.capture_details:
            self.capture_details = variant.capture_details

class Member:
    def __init__(self, member_id, src: dict):
        self.member_id = int(member_id)
        self.name = src["name"]
        self.type = Type(src.get("type"))
        self.kind = Kind(src.get("kind"))
        self.kind_details = KindDetails(src["kind_details"]) if "kind_details" in src.keys() else None
        self.server_access = ServerAccess(src.get("server_access", {}))
        self.translate_before = Translate(src["translate_before"]) if "translate_before" in src.keys() else None

class StructureTraits:
    def __init__(self, struct):
        self.struct = struct

    def requires_copy_from_caller(self):
        ptr_array_members = self.struct.members_to_capture()
        is_copy_required_for_ptr_array_members = any(not m.kind_details.server_access.write_only() for m in ptr_array_members)
        if is_copy_required_for_ptr_array_members:
            return True

        capturable_struct_members = [m for m in ptr_array_members if self.is_non_trivial_struct_dependency(m.kind_details.element)]
        capturable_structs = [self.struct.all_structures_description[m.kind_details.element.type.str] for m in capturable_struct_members]

        return any(s.traits.requires_copy_from_caller() for s in capturable_structs if s.name != self.struct.name)

    def requires_copy_to_caller(self):
        ptr_array_members = self.struct.members_to_capture()
        is_copy_required_for_ptr_array_members = any(not m.kind_details.server_access.read_only() for m in ptr_array_members)
        if is_copy_required_for_ptr_array_members:
            return True

        capturable_struct_members = [m for m in ptr_array_members if self.is_non_trivial_struct_dependency(m.kind_details.element)]
        capturable_structs = [self.struct.all_structures_description[m.kind_details.element.type.str] for m in capturable_struct_members]

        return any(s.traits.requires_copy_to_caller() for s in capturable_structs if s.name != self.struct.name)

    # Warning: recursive data structures (e.g. linked-lists) are not supported yet.
    def capturable_members_count_including_nested(self):
        ptr_array_members = self.struct.members_to_capture()
        total_count = len(ptr_array_members)

        capturable_struct_members = [m for m in ptr_array_members if self.is_non_trivial_struct_dependency(m.kind_details.element)]
        capturable_structs = [self.struct.all_structures_description[m.kind_details.element.type.str] for m in capturable_struct_members]

        for struct in capturable_structs:
            total_count += struct.traits.capturable_members_count_including_nested()

        return total_count

    # Warning: recursive struct members are currently not included.
    def requires_translation_of_members_before(self):
        return any(member.translate_before for member in self.struct.members)

    def is_trivial(self): # struct containing only scalar or trivial struct member variables 
        trivial = all(member.kind.is_scalar() or (member.kind.is_struct() and not self.is_non_trivial_struct_dependency(member))
                      for member in self.struct.members)
        return trivial

    def is_non_trivial_struct_dependency(self, variable):
        if (not (variable.kind.is_struct() and variable.type.str in self.struct.all_structures_description)) and not variable.kind.is_opaque_list():
            return False

        if variable.kind.is_struct():
            struct_type = self.struct.all_structures_description[variable.type.str]
            return not struct_type.traits.is_trivial()

    def requires_opaque_elements_translation_before(self):
        members_to_captures = self.struct.members_to_capture()
        return any(member.kind_details.requires_opaque_elements_translation_before for member in members_to_captures)


class Structure:
    def __init__(self, src: dict):
        self.name = src["name"]
        members_src = src.get("members", {})
        self.members = sorted([Member(member_id, members_src[member_id])
                              for member_id in members_src.keys()], key=lambda member: member.member_id)
        self.traits = StructureTraits(self)

    def members_to_capture(self):
        return [member for member in self.members if (member.kind.is_pointer_to_array() or member.kind.is_opaque_list())]

    def set_all_structures_description(self, all_structures_description):
        self.all_structures_description = all_structures_description


class Returns:
    def __init__(self, src: dict):
        self.type = Type(src.get("type"))
        self.kind = Kind(src.get("kind"))
        self.translate_after = Translate(src["translate_after"]) if "translate_after" in src.keys() else None
        self.default = src.get("default", "{}")


class Cacheable:
    def __init__(self, src: dict):
        pass


class SpecialHandling:
    class Icd:
        def __init__(self, src: dict):
            self.dont_generate_handler = src.get("dont_generate_handler", False)
            self.alias_to = src.get("alias_to", None)
            self.handler_only_suffix = src.get("handler_only_suffix", "")
            self.not_in_dispatch_table = src.get("not_in_dispatch_table", False)
            self.in_get_extension_function_address = src.get("in_get_extension_function_address", False)
            self.dont_generate_stub = src.get("dont_generate_stub", False)
            self.unsupported = src.get("unsupported", False)
            self.intentionally_ignore = src.get("intentionally_ignore", False)
            self.handler_prologue = src.get("handler_prologue", None)
            self.handler_epilogue = src.get("handler_epilogue", None)
            self.handler_epilogue_data = src.get("handler_epilogue_data", None)
            self.tracable = src.get("tracable", None)
            if self.handler_prologue and not isinstance(self.handler_prologue, list):
                self.handler_prologue = [self.handler_prologue]
            if self.handler_epilogue and not isinstance(self.handler_epilogue, list):
                self.handler_epilogue = [self.handler_epilogue]
            if self.handler_epilogue_data and not isinstance(self.handler_epilogue_data, list):
                self.handler_epilogue_data = [self.handler_epilogue_data]

    class Rpc:
        def __init__(self, src: dict):
            self.dont_generate_rpc_message = src.get("dont_generate_rpc_message", False)
            self.dont_generate_rpc_handler = src.get("dont_generate_rpc_handler", False)
            self.dont_generate_call_directly = src.get("dont_generate_call_directly", False)
            self.handler_only_suffix = src.get("handler_only_suffix", "")
            self.custom_handler = src.get("custom_handler", False)
            self.emit_copy_assignment = src.get("emit_copy_assignment", False)
            self.handler_prologue = src.get("handler_prologue", None)
            self.handler_epilogue = src.get("handler_epilogue", None)
            if self.handler_prologue and not isinstance(self.handler_prologue, list):
                self.handler_prologue = [self.handler_prologue]
            if self.handler_epilogue and not isinstance(self.handler_epilogue, list):
                self.handler_epilogue = [self.handler_epilogue]

    def __init__(self, src: dict):
        self.icd = SpecialHandling.Icd(src["icd"]) if "icd" in src.keys() else None
        self.rpc = SpecialHandling.Rpc(src["rpc"]) if "rpc" in src.keys() else None
        self.extension_name = src.get("extension_name", "")
        self.variant_of = src.get("variant_of", "")
        self.optional = src.get("optional", False)

    def is_extension(self):
        return self.extension_name or (self.icd and self.icd.in_get_extension_function_address and self.icd.not_in_dispatch_table)

    def is_variant(self):
        return self.variant_of != ""


class FunctionTraits:
    def __init__(self, function, tracable_group_defaults):
        self.function = function
        self.num_of_all_args_with_inline_dynamic_mem = len(self.get_inline_dyn_ptr_array_args()) + \
            self.count_of_capturable_struct_members_includig_nested(self.get_ptr_array_args())
        self.uses_dynamic_arg_getters = self.num_of_all_args_with_inline_dynamic_mem > 1
        ptr_array_args = self.get_ptr_array_args()

        self.emit_copy_from_caller = self.requires_copy_from_caller(ptr_array_args, function.implicit_args)
        self.emit_copy_to_caller = self.requires_copy_to_caller(ptr_array_args, function.implicit_args)
        self.emit_reassemblation_in_icd = self.requires_opaque_elements_translation_before(ptr_array_args)

        self.uses_inline_dynamic_mem = self.num_of_all_args_with_inline_dynamic_mem > 0
        self.is_extension = function.special_handling and function.special_handling.is_extension()
        self.is_variant = function.special_handling and function.special_handling.is_variant()
        self.requires_malloc_shmem_zero_copy_handler = any(arg.kind.is_pointer_zero_copy_malloc_shmem() for arg in function.args)
        self.requires_pointer_remapping = any(arg.kind.is_pointer_remapped() for arg in function.args)
        self.has_arg_kind_variants = any(arg.kind_variants for arg in function.args)
        self.is_tracable = function.special_handling.icd.tracable if (function.special_handling and function.special_handling.icd and (function.special_handling.icd.tracable != None)) else tracable_group_defaults

    def requires_copy_from_caller(self, ptr_array_args, implicit_args):
        is_copy_required_for_ptr_array_args = any(not arg.kind_details.server_access.write_only() for arg in ptr_array_args if not (arg.capture_details.mode.is_standalone_mode() or arg.capture_details.mode.is_staging_usm_mode()))
        is_copy_required_for_implicit_args = any(not arg.server_access.write_only() for arg in implicit_args)

        capturable_struct_args = [arg for arg in ptr_array_args if self.is_non_trivial_struct_dependency(arg.kind_details.element)]
        capturable_structs = [self.function.structures[arg.kind_details.element.type.str] for arg in capturable_struct_args]
        is_copy_required_for_struct_fields = any(struct.traits.requires_copy_from_caller() for struct in capturable_structs)

        return is_copy_required_for_ptr_array_args or is_copy_required_for_implicit_args or is_copy_required_for_struct_fields

    def requires_copy_to_caller(self, ptr_array_args, implicit_args):
        is_copy_required_for_ptr_array_args = any(not arg.kind_details.server_access.read_only() for arg in ptr_array_args)
        is_copy_required_for_implicit_args = any(not arg.server_access.read_only() for arg in implicit_args)

        capturable_struct_args = [arg for arg in ptr_array_args if self.is_non_trivial_struct_dependency(arg.kind_details.element)]
        capturable_structs = [self.function.structures[arg.kind_details.element.type.str] for arg in capturable_struct_args]
        is_copy_required_for_struct_fields = any(struct.traits.requires_copy_to_caller() for struct in capturable_structs)

        return is_copy_required_for_ptr_array_args or is_copy_required_for_implicit_args or is_copy_required_for_struct_fields

    def is_copy_to_caller_required_for_any_of_struct_fields(self):
        ptr_array_args = self.get_ptr_array_args()
        capturable_struct_args = [arg for arg in ptr_array_args if self.is_non_trivial_struct_dependency(arg.kind_details.element)]
        writable_struct_args = [arg for arg in capturable_struct_args if not arg.kind_details.server_access.read_only()]
        capturable_structs = [self.function.structures[arg.kind_details.element.type.str] for arg in writable_struct_args]

        return any(struct.traits.requires_copy_to_caller() for struct in capturable_structs)

    def requires_opaque_elements_translation_before(self, ptr_array_args):
        capturable_struct_args = [arg for arg in ptr_array_args if self.is_non_trivial_struct_dependency(arg.kind_details.element)]
        capturable_structs = [self.function.structures[arg.kind_details.element.type.str] for arg in capturable_struct_args]
        return any(struct.traits.requires_opaque_elements_translation_before() for struct in capturable_structs)

    def count_of_capturable_struct_members_includig_nested(self, args):
        total_count = 0

        capturable_struct_args = [arg for arg in self.get_ptr_array_args() if self.is_non_trivial_struct_dependency(arg.kind_details.element)]
        for arg in capturable_struct_args:
            struct_type = self.function.structures[arg.kind_details.element.type.str]
            total_count += struct_type.traits.capturable_members_count_including_nested()
        return total_count

    def get_standalone_args(self):
        return [arg for arg in self.function.args+self.function.implicit_args if arg.capture_details.mode.is_standalone_mode() or arg.capture_details.mode.is_staging_usm_mode()]

    def get_remapped_pointer_args(self):
        return [arg for arg in self.function.args+self.function.implicit_args if arg.kind.is_pointer_remapped()]

    def get_shared_pointer_args(self):
        return [arg for arg in self.function.args+self.function.implicit_args if arg.kind.is_pointer_zero_copy_malloc_shmem()]

    def get_ptr_array_args(self):
        return [arg for arg in self.function.args+self.function.implicit_args if arg.kind.is_pointer_to_array()]

    def get_inline_dyn_ptr_array_args(self):
        dyn_ptr_array_args = [arg for arg in self.function.args+self.function.implicit_args if arg.kind.is_pointer_to_array()
                             and (not arg.kind_details.num_elements.is_constant()) and not (arg.capture_details.mode.is_standalone_mode() or arg.capture_details.mode.is_staging_usm_mode())]

        def is_costly(arg):
            return arg.kind_details.num_elements.is_nullterminated() or arg.kind_details.num_elements.is_nullterminated_key() or arg.kind_details.element.kind.is_pointer_to_array()

        # push out nullterminated and nested dynamic args to the end for better packing
        return sorted(dyn_ptr_array_args, key=lambda arg: arg.arg_id + 8192 * is_costly(arg))

    def get_fixed_ptr_array_args(self):
        return [arg for arg in self.function.args if arg.kind.is_pointer_to_array() and arg.kind_details.num_elements.is_constant()]

    def is_non_trivial_struct_dependency(self, variable):
        if (not (variable.kind.is_struct() and variable.type.str in self.function.structures)) and not variable.kind.is_opaque_list():
            return False
        struct_type = self.function.structures[variable.type.str]
        return not struct_type.traits.is_trivial()

    def getOpEndEventArg(self):
        ev = [arg for arg in self.function.args if arg.kind_details and arg.kind_details.is_op_end_event]
        assert(len(ev) <= 1)
        return ev[0] if ev else None

def handle_mako_error(template_name : str):
    mako_error = mako.exceptions.text_error_template().render()
    if "raise exceptions.SyntaxException(" in mako_error:
        stack, mako_error = mako_error.split("raise exceptions.SyntaxException(")
        mako_error = mako_error.strip("\n\r")
    message = f"Failed to generate file using {template_name} because:\n{mako_error}"
    print(message)
    os._exit(1)

class FunctionCaptureLayout:
    #  | <--- return value ---> | <--- fixed length arrays ---> | <--- dynamic arg offsets ---> | <--- dynamic args ---> | <--- nested captures ---> |
    #
    # e.g. int f(int*one, char **two, size_t numTwo, char * three)
    #  | int | int one[1] | uin32_t offset_three | offset_t two[X]    char three[Y] | char two{0}[A]   char two{0}[B] ... char two{0}[N]|
    class ArgCaptureLayout:
        def __init__(self):
            self.arg = None
            self.fixed_size = None
            self.complex_count = False
            self.complex_offset = False
            self.uses_nested_capture = False

    class MemberCaptureLayout:
        def __init__(self):
            self.member = None
            self.parent = None
            self.parent_layout = None
            self.children = []
            self.extension_data = None
            self.is_extension_child = False
            self.function_capture_layout = None

        def uses_extension_prefix(self):
            return self.is_extension_child or self.extension_data

        def get_children_per_extension(self):
            children_per_ext_dict = defaultdict(list)
            for child in self.children:
                children_per_ext_dict[child.extension_data.extension_enum_value].append(child)

            return children_per_ext_dict

        def get_real_type(self, element):
            if element.kind.is_opaque():
                return element.kind_details.underlying_type.type.str
            else:
                return element.type.str

        def get_real_count(self, element, parent_access, it, formatter, current_element_access):
            nested_element = element.kind_details.element
            if nested_element.kind.is_opaque():
                return "1"
            elif element.kind_details.num_elements.is_constant():
                return element.kind_details.num_elements.get_constant()
            elif element.kind_details.num_elements.is_nullterminated():
                return f"Cal::Utils::countNullterminated({current_element_access})"
            else:
                access = formatter.trim_right_from(source=parent_access, needle=".")
                count_format = access + f".{element.kind_details.num_elements.str}"
                return count_format.format(it=it)

        def create_required_size_calculation(self, total_size_var, formatter, spaces_count, it):
            spaces = " " * spaces_count
            parent_it = str(chr(ord(it) - 1))
            current_member_name = formatter.get_full_member_name(self)
            prefix = "extension." if self.uses_extension_prefix() else ""
            current_member_access = formatter.generate_member_access(self, parent_it, prefix)
            current_member_count_name = current_member_name + "Count"
            current_member_count_access = formatter.generate_member_count_access(self, parent_it, prefix)
            current_member_element_type = self.member.kind_details.element.type.str if not self.member.kind.is_opaque_list() else self.member.kind_details.opaque_traits_name

            member_size_calculation = f"""{spaces}const auto& {current_member_name} = {current_member_access};
{spaces}if(!{current_member_name}){{
{spaces}    continue;
{spaces}}}

{spaces}const auto {current_member_count_name} = static_cast<uint32_t>({current_member_count_access});
{spaces}if(!{current_member_count_name}){{
{spaces}    continue;
{spaces}}}

{spaces}{total_size_var} += alignUpPow2<8>({current_member_count_name} * sizeof({current_member_element_type}));"""

            # Heterogeneous list hold as void*
            if self.member.kind.is_opaque_list():
                iterator_type = self.member.kind_details.iterator_type
                list_element_name = f"{current_member_name}ListElement"

                member_size_calculation += f"\n\n{spaces}auto {list_element_name} = static_cast<const {iterator_type}*>({current_member_access});"
                member_size_calculation += f"\n{spaces}for(uint32_t {it} = 0; {it} < {current_member_count_name}; ++{it}){{"
                member_size_calculation += f"\n{spaces}    {total_size_var} += alignUpPow2<8>(getUnderlyingSize({list_element_name}));"
                if self.children:
                    member_size_calculation += f"\n\n{spaces}    const auto extensionType = static_cast<int>(getExtensionType({list_element_name}));"

                    children_per_ext_dict = self.get_children_per_extension()
                    for enum_value, ext_children in children_per_ext_dict.items():
                        extension_type = ext_children[0].extension_data.type_name
                        member_size_calculation += f"\n{spaces}    if (extensionType == {enum_value}) {{"
                        member_size_calculation += f"\n{spaces}        auto& extension = *reinterpret_cast<const {extension_type}*>({list_element_name});"
                        member_size_calculation += f"\n{spaces}        {total_size_var} += alignUpPow2<8>(sizeof(DynamicStructTraits<{extension_type}>));"

                        for child in ext_children:
                            member_size_calculation += f"\n\n{spaces}        do {{"
                            member_size_calculation += "\n" + child.create_required_size_calculation(total_size_var, formatter, spaces_count + 12, str(chr(ord(it) + 1)))
                            member_size_calculation += f"\n{spaces}        }} while (0);"
                        member_size_calculation += f"\n{spaces}    }}"

                member_size_calculation += f"\n{spaces}    {list_element_name} = getNext({list_element_name});"
                member_size_calculation += f"\n{spaces}}}\n"

            # Multi-dimensional array member
            if self.member.kind_details.element.kind.is_pointer_to_array() or self.member.kind_details.element.kind.is_opaque():
                member_size_calculation += f"\n{spaces}{total_size_var} += alignUpPow2<8>({current_member_count_name} * sizeof(DynamicStructTraits<{current_member_element_type}>));"
                member_size_calculation += f"\n{spaces}for(uint32_t {it} = 0; {it} < {current_member_count_name}; ++{it}){{\n"
                member_size_calculation += self.create_nested_array_member_size_calculation(
                    self.member.kind_details.element, current_member_name, current_member_access, total_size_var, formatter, spaces_count + 4, str(chr(ord(it) + 1)))
                member_size_calculation += f"\n{spaces}}}\n"

            if self.children and not self.member.kind.is_opaque_list():
                member_size_calculation += f"\n{spaces}{total_size_var} += alignUpPow2<8>({current_member_count_name} * sizeof(DynamicStructTraits<{current_member_element_type}>));"
                for child in self.children:
                    member_size_calculation += f"\n{spaces}for(uint32_t {it} = 0; {it} < {current_member_count_name}; ++{it}){{\n"
                    member_size_calculation += child.create_required_size_calculation(
                        total_size_var, formatter, spaces_count + 4, str(chr(ord(it) + 1)))
                    member_size_calculation += f"\n{spaces}}}\n"

            return member_size_calculation

        def create_nested_array_member_size_calculation(self, element, parent_name, parent_access, total_size_var, formatter, spaces_count, it):
            prev_it = str(chr(ord(it) - 1))
            current_element_name = f"{parent_name}_{prev_it}"
            current_element_access = f"{parent_name}[{prev_it}]"
            current_element_count_name = f"{current_element_name}Count"

            spaces = " " * spaces_count
            nested_element = element.kind_details.element
            real_type = self.get_real_type(nested_element)
            real_count = self.get_real_count(element, parent_access, prev_it, formatter, current_element_access)


            member_size_calculation = f"""{spaces}const auto& {current_element_name} = {current_element_access};
{spaces}if(!{current_element_name}){{
{spaces}    continue;
{spaces}}}

{spaces}const auto {current_element_count_name} = static_cast<uint32_t>({real_count});
{spaces}if(!{current_element_count_name}){{
{spaces}    continue;
{spaces}}}
{spaces}{total_size_var} += alignUpPow2<8>({current_element_count_name} * sizeof({real_type}));"""

            if nested_element.kind.is_pointer_to_array():
                member_size_calculation += f"\n{spaces}{total_size_var} += alignUpPow2<8>({current_element_count_name} * sizeof(DynamicStructTraits<{real_type}>));"
                member_size_calculation += f"\n{spaces}for(uint32_t {it} = 0; {it} < {real_count}; ++{it}){{\n"
                member_size_calculation += self.create_nested_array_member_size_calculation(
                    nested_element, current_element_name, current_element_access, total_size_var, formatter, spaces_count + 4, str(chr(ord(it) + 1)))
                member_size_calculation += f"\n{spaces}}}"
            elif nested_element.kind.is_struct():
                element.name = f"[{it}]"
                struct_layout = self.function_capture_layout.prepare_nested_member_layouts(self.member, self, element, is_extension_child=True)

                member_size_calculation += f"\n{spaces}{total_size_var} += alignUpPow2<8>({current_element_count_name} * sizeof(DynamicStructTraits<{real_type}>));"
                member_size_calculation += f"\n\n{spaces}for(uint32_t {it} = 0; {it} < {real_count}; ++{it}){{"
                for child in struct_layout.children:
                    member_size_calculation += f"\n{spaces}    do {{"
                    member_size_calculation += "\n" + child.create_required_size_calculation(total_size_var, formatter, spaces_count + 8, str(chr(ord(it) + 1)))
                    member_size_calculation += f"\n{spaces}    }} while (0);"
                member_size_calculation += f"\n{spaces}}}"

            return member_size_calculation

        def create_copy_to_caller(self, current_offset_var, formatter, spaces_count, it):
            spaces = " " * spaces_count
            parent_name = formatter.get_full_parent_name(self)
            current_dest_access = f"dest{formatter.capital(formatter.generate_member_access(self, it))}"

            current_member_name = formatter.get_full_member_name(self)
            current_member_offset = f"{parent_name}Traits[{it}].{self.member.name}Offset"
            current_member_count_name = current_member_name + "Count"
            prefix = "args." if not self.uses_extension_prefix() else "extension."
            current_member_access = formatter.generate_member_access(self, it, prefix=prefix)
            current_member_count_access = formatter.generate_member_count_access(self, it, prefix=prefix)
            current_member_element_type = self.member.kind_details.element.type.str

            copy_to_caller = f"""{spaces}const auto& {current_member_name} = {current_member_access};
{spaces}if(!{current_member_name}){{
{spaces}    continue;
{spaces}}}
{spaces}const auto {current_member_count_name} = static_cast<int32_t>({current_member_count_access});"""

            if not self.member.kind.is_opaque_list():
                copy_to_caller += f"\n\n{spaces}std::memcpy({current_member_name}, dynMem + {current_offset_var}, {current_member_count_name} * sizeof({current_member_element_type}));"
                copy_to_caller += f"\n{spaces}{current_offset_var} += alignUpPow2<8>({current_member_count_name} * sizeof({current_member_element_type}));"
            else:
                next_it = str(chr(ord(it) + 1))
                iterator_type = self.member.kind_details.iterator_type
                list_element_name = f"{current_member_name}ListElement"
                opaque_traits = self.member.kind_details.opaque_traits_name

                copy_to_caller += f"\n\n{spaces}{current_dest_access} = {parent_name}Traits[{it}].{self.member.name}FirstOriginalElement;"

                copy_to_caller += f"\n\n{spaces}auto {list_element_name}Traits = reinterpret_cast<{opaque_traits}*>(dynMem + {current_offset_var});"
                copy_to_caller += f"\n{spaces}{current_offset_var} += alignUpPow2<8>({current_member_count_name} * sizeof({opaque_traits}));"

                copy_to_caller += f"\n\n{spaces}auto {list_element_name} = static_cast<const {iterator_type}*>({current_dest_access});"

                copy_to_caller += f"\n{spaces}for(int32_t {next_it} = 0; {next_it} < {current_member_count_name}; ++{next_it}){{"
                copy_to_caller += f"\n{spaces}    const auto sizeInBytes = getUnderlyingSize({list_element_name});"
                copy_to_caller += f"\n{spaces}    {current_offset_var} += alignUpPow2<8>(sizeInBytes);\n"

                copy_to_caller += f"\n{spaces}    const auto extensionType = getExtensionType({list_element_name});"
                copy_to_caller += f"\n{spaces}    if (!isReadOnly(extensionType)) {{"

                if self.children:
                    children_per_ext_dict = self.get_children_per_extension()
                    for enum_value, ext_children in children_per_ext_dict.items():
                        extension_type = ext_children[0].extension_data.type_name
                        copy_to_caller += f"\n{spaces}        if (extensionType == static_cast<int>({enum_value})) {{"
                        copy_to_caller += f"\n{spaces}            auto& extension = *reinterpret_cast<const {extension_type}*>({list_element_name});"
                        copy_to_caller += f"\n{spaces}            {current_offset_var} += alignUpPow2<8>(sizeof(DynamicStructTraits<{extension_type}>));"
                        for child in ext_children:
                            next_it_2 = str(chr(ord(next_it) + 1))
                            copy_to_caller += f"\n\n{spaces}            for(int32_t {next_it_2} = 0; {next_it_2} < 1; ++{next_it_2}) {{"
                            copy_to_caller += "\n" + child.create_copy_to_caller(current_offset_var, formatter, spaces_count + 16, next_it_2)
                            copy_to_caller += f"\n    {spaces}        }}"
                        copy_to_caller += f"\n{spaces}        }}"

                copy_to_caller += f"\n{spaces}        auto originalNextOpaqueElement = getNext({list_element_name});"
                copy_to_caller += f"\n{spaces}        const auto extensionOffset = {list_element_name}Traits[{next_it}].extensionOffset;"
                copy_to_caller += f"\n{spaces}        auto destination = const_cast<{iterator_type}*>({list_element_name});"
                copy_to_caller += f"\n{spaces}        std::memcpy(destination, dynMem + extensionOffset, sizeInBytes);\n"
                copy_to_caller += f"\n{spaces}        getNextField(*destination) = originalNextOpaqueElement;"

                copy_to_caller += f"\n{spaces}    }}\n"
                copy_to_caller += f"\n{spaces}    {list_element_name} = getNext({list_element_name});"
                copy_to_caller += f"\n{spaces}}}\n"

            return copy_to_caller

        def create_copy_from_caller(self, current_offset_var, formatter, spaces_count, it):
            spaces = " " * spaces_count
            current_member_name = formatter.get_full_member_name(self)

            prefix = "args." if not self.uses_extension_prefix() else "extension."
            current_member_access = formatter.generate_member_access(self, it, prefix=prefix)

            current_member_count_name = current_member_name + "Count"
            current_member_count_access = formatter.generate_member_count_access(self, it, prefix=prefix)
            current_member_element_type = self.member.kind_details.element.type.str

            if not self.uses_extension_prefix():
                parent_name = formatter.get_full_parent_name(self)
            elif self.extension_data:
                parent_name = "extension"
            else:
                parent_name = "nestedChild"

            copy_from_caller = f"""{spaces}const auto& {current_member_name} = {current_member_access};
{spaces}if(!{current_member_name}){{
{spaces}    {parent_name}Traits[{it}].{self.member.name}Offset = -1;
{spaces}    {parent_name}Traits[{it}].{self.member.name}Count = -1;
{spaces}    continue;
{spaces}}}

{spaces}const auto {current_member_count_name} = static_cast<int32_t>({current_member_count_access});
{spaces}if(!{current_member_count_name}){{
{spaces}    {parent_name}Traits[{it}].{self.member.name}Offset = -1;
{spaces}    {parent_name}Traits[{it}].{self.member.name}Count = -1;
{spaces}    continue;
{spaces}}}

{spaces}{parent_name}Traits[{it}].{self.member.name}Offset = {current_offset_var};
{spaces}{parent_name}Traits[{it}].{self.member.name}Count = {current_member_count_name};"""

            if not self.member.kind.is_opaque_list():
                copy_from_caller += f"\n\n{spaces}std::memcpy(dynMem + {current_offset_var}, {current_member_name}, {current_member_count_name} * sizeof({current_member_element_type}));"
                copy_from_caller += f"\n{spaces}{current_offset_var} += alignUpPow2<8>({current_member_count_name} * sizeof({current_member_element_type}));"
            else:
                next_it = str(chr(ord(it) + 1))
                iterator_type = self.member.kind_details.iterator_type
                list_element_name = f"{current_member_name}ListElement"
                opaque_traits = self.member.kind_details.opaque_traits_name

                copy_from_caller += f"\n{spaces}{parent_name}Traits[{it}].{self.member.name}FirstOriginalElement = {current_member_access};";

                copy_from_caller += f"\n\n{spaces}auto {list_element_name}Traits = reinterpret_cast<{opaque_traits}*>(dynMem + {current_offset_var});"
                copy_from_caller += f"\n{spaces}{current_offset_var} += alignUpPow2<8>({current_member_count_name} * sizeof({opaque_traits}));"

                copy_from_caller += f"\n\n{spaces}auto {list_element_name} = static_cast<const {iterator_type}*>({current_member_access});"
                copy_from_caller += f"\n{spaces}for(int32_t {next_it} = 0; {next_it} < {current_member_count_name}; ++{next_it}){{"
                copy_from_caller += f"\n{spaces}    {list_element_name}Traits[{next_it}].extensionType = getExtensionType({list_element_name});"
                copy_from_caller += f"\n{spaces}    {list_element_name}Traits[{next_it}].extensionOffset = {current_offset_var};\n"

                copy_from_caller += f"\n{spaces}    const auto sizeInBytes = getUnderlyingSize({list_element_name});"
                copy_from_caller += f"\n{spaces}    std::memcpy(dynMem + {current_offset_var}, {list_element_name}, sizeInBytes);"
                copy_from_caller += f"\n{spaces}    {current_offset_var} += alignUpPow2<8>(sizeInBytes);\n"

                if self.children:
                    copy_from_caller += f"\n\n{spaces}    const auto extensionType = static_cast<int>(getExtensionType({list_element_name}));"

                    children_per_ext_dict = self.get_children_per_extension()
                    for enum_value, ext_children in children_per_ext_dict.items():
                        extension_type = ext_children[0].extension_data.type_name
                        copy_from_caller += f"\n{spaces}    if (extensionType == {enum_value}) {{"
                        copy_from_caller += f"\n{spaces}        auto& extension = *reinterpret_cast<const {extension_type}*>({list_element_name});"
                        copy_from_caller += f"\n{spaces}        auto* extensionTraits = reinterpret_cast<DynamicStructTraits<{extension_type}>*>(dynMem + {current_offset_var});"
                        copy_from_caller += f"\n{spaces}        {current_offset_var} += alignUpPow2<8>(sizeof(DynamicStructTraits<{extension_type}>));"
                        for child in ext_children:
                            next_it_2 = str(chr(ord(next_it) + 1))
                            copy_from_caller += f"\n\n{spaces}        for(int32_t {next_it_2} = 0; {next_it_2} < 1; ++{next_it_2}) {{"
                            copy_from_caller += "\n" + child.create_copy_from_caller(current_offset_var, formatter, spaces_count + 12, next_it_2)
                            copy_from_caller += f"\n{spaces}        }}"
                        copy_from_caller += f"\n{spaces}    }}"

                copy_from_caller += f"\n{spaces}    {list_element_name} = getNext({list_element_name});"
                copy_from_caller += f"\n{spaces}}}\n"


            # Multi-dimensional array member
            if self.member.kind_details.element.kind.is_pointer_to_array() or self.member.kind_details.element.kind.is_opaque():
                copy_from_caller += f"\n\n{spaces}auto* {current_member_name}Traits = reinterpret_cast<DynamicStructTraits<{current_member_element_type}>*>(dynMem + {current_offset_var});"
                copy_from_caller += f"\n{spaces}{current_offset_var} += alignUpPow2<8>({current_member_count_name} * sizeof(DynamicStructTraits<{current_member_element_type}>));\n"

                next_it = str(chr(ord(it) + 1))
                copy_from_caller += f"\n{spaces}for(int32_t {next_it} = 0; {next_it} < {current_member_count_name}; ++{next_it}){{\n"
                copy_from_caller += self.create_nested_array_member_copy_from_caller(
                    self.member.kind_details.element, current_member_name, current_member_access, current_offset_var, formatter, spaces_count + 4, next_it)
                copy_from_caller += f"\n{spaces}}}\n"

            if self.children and not self.member.kind.is_opaque_list():
                copy_from_caller += f"\n\n{spaces}auto* {current_member_name}Traits = reinterpret_cast<DynamicStructTraits<{current_member_element_type}>*>(dynMem + {current_offset_var});"
                copy_from_caller += f"\n{spaces}{current_offset_var} += alignUpPow2<8>({current_member_count_name} * sizeof(DynamicStructTraits<{current_member_element_type}>));\n"
                next_it = str(chr(ord(it) + 1))

                for child in self.children:
                    copy_from_caller += f"\n{spaces}for(int32_t {next_it} = 0; {next_it} < {current_member_count_name}; ++{next_it}){{\n"
                    copy_from_caller += child.create_copy_from_caller(current_offset_var, formatter, spaces_count + 4, next_it)
                    copy_from_caller += f"\n{spaces}}}\n"

            return copy_from_caller

        def create_nested_array_member_copy_from_caller(self, element, parent_name, parent_access, current_offset_var, formatter, spaces_count, it):
            parent_traits = f"{parent_name}Traits"
            current_element_name = f"{parent_name}_{it}"
            current_element_access = f"{parent_name}[{it}]"
            current_element_count_name = f"{current_element_name}Count"

            spaces = " " * spaces_count
            nested_element = element.kind_details.element
            real_type = self.get_real_type(nested_element)
            real_count = self.get_real_count(element, parent_access, it, formatter, current_element_access)

            copy_from_caller = f"""{spaces}const auto& {current_element_name} = {current_element_access};
{spaces}if(!{current_element_name}){{
{spaces}    {parent_traits}[{it}].offset = -1;
{spaces}    {parent_traits}[{it}].count = -1;
{spaces}    continue;
{spaces}}}

{spaces}const auto& {current_element_count_name} = {real_count};
{spaces}if(!{current_element_count_name}){{
{spaces}    {parent_traits}[{it}].offset = -1;
{spaces}    {parent_traits}[{it}].count = -1;
{spaces}    continue;
{spaces}}}

{spaces}{parent_traits}[{it}].offset = {current_offset_var};
{spaces}{parent_traits}[{it}].count = {current_element_count_name};

{spaces}std::memcpy(dynMem + {current_offset_var}, {current_element_name}, {current_element_count_name} * sizeof({real_type}));
{spaces}{current_offset_var} += alignUpPow2<8>({current_element_count_name} * sizeof({real_type}));"""

            if nested_element.kind.is_pointer_to_array():
                copy_from_caller += f"\n\n{spaces}auto* {current_element_name}Traits = reinterpret_cast<DynamicStructTraits<{real_type}>*>(dynMem + {current_offset_var});"
                copy_from_caller += f"\n{spaces}{current_offset_var} += alignUpPow2<8>({current_element_count_name} * sizeof(DynamicStructTraits<{real_type}>));\n"

                next_it = str(chr(ord(it) + 1))
                copy_from_caller += f"\n{spaces}for(int32_t {next_it} = 0; {next_it} < {current_element_count_name}; ++{next_it}){{\n"
                copy_from_caller += self.create_nested_array_member_copy_from_caller(
                    nested_element, current_element_name, current_element_access, current_offset_var, formatter, spaces_count + 4, next_it)
                copy_from_caller += f"\n{spaces}}}\n"
            elif nested_element.kind.is_struct():
                next_it = str(chr(ord(it) + 1))
                element.name = f"[{next_it}]"
                struct_layout = self.function_capture_layout.prepare_nested_member_layouts(self.member, self, element, is_extension_child=True)

                copy_from_caller += f"\n\n{spaces}auto* nestedChildTraits = reinterpret_cast<DynamicStructTraits<{real_type}>*>(dynMem + {current_offset_var});"
                copy_from_caller += f"\n{spaces}{current_offset_var} += alignUpPow2<8>({current_element_count_name} * sizeof(DynamicStructTraits<{real_type}>));\n"
                copy_from_caller += f"\n\n{spaces}for(int32_t {next_it} = 0; {next_it} < {real_count}; ++{next_it}){{"
                for child in struct_layout.children:
                    copy_from_caller += f"\n{spaces}    do {{"
                    copy_from_caller += "\n" + child.create_copy_from_caller(current_offset_var, formatter, spaces_count + 8, next_it)
                    copy_from_caller += f"\n{spaces}    }} while (0);"
                copy_from_caller += f"\n{spaces}}}"

            return copy_from_caller

        def create_reassemble_nested_structs(self, current_offset_var, formatter, spaces_count, it):
            spaces = " " * spaces_count
            if self.uses_extension_prefix():
                parent_name = "extension" if self.extension_data else "nestedChild"
                current_dest_access = f"extension.{formatter.generate_member_access(self, it)}"
            else:
                parent_name = formatter.get_full_parent_name(self)
                current_dest_access = f"dest{formatter.capital(formatter.generate_member_access(self, it))}"

            current_member_name = formatter.get_full_member_name(self)
            current_member_offset = f"{parent_name}Traits[{it}].{self.member.name}Offset"
            current_member_count = f"{parent_name}Traits[{it}].{self.member.name}Count"
            current_member_element_type = self.member.kind_details.element.type.str

            reassemble_nested_structs = f"""{spaces}if({parent_name}Traits[{it}].{self.member.name}Offset == -1){{
{spaces}    forcePointerWrite({current_dest_access}, nullptr);
{spaces}    continue;
{spaces}}}"""

            if not self.member.kind.is_opaque_list():
                reassemble_nested_structs += f"\n\n{spaces}forcePointerWrite({current_dest_access}, dynMem + {current_member_offset});"
                reassemble_nested_structs += f"\n{spaces}{current_offset_var} += alignUpPow2<8>({current_member_count} * sizeof({current_member_element_type}));"
            else:
                next_it = str(chr(ord(it) + 1))
                iterator_type = self.member.kind_details.iterator_type
                list_element_name = f"{current_member_name}ListElement"
                opaque_traits = self.member.kind_details.opaque_traits_name

                reassemble_nested_structs += f"\n\n{spaces}auto {list_element_name}Traits = reinterpret_cast<{opaque_traits}*>(dynMem + {current_offset_var});"
                reassemble_nested_structs += f"\n{spaces}{current_offset_var} += alignUpPow2<8>({current_member_count} * sizeof({opaque_traits}));"

                reassemble_nested_structs += f"\n\n{spaces}assert(currentOffset == static_cast<uint32_t>({list_element_name}Traits[0].extensionOffset));"
                reassemble_nested_structs += f"\n{spaces}forcePointerWrite({current_dest_access}, dynMem + {list_element_name}Traits[0].extensionOffset);"
                reassemble_nested_structs += f"\n{spaces}{current_offset_var} += alignUpPow2<8>(getUnderlyingSize(static_cast<const {iterator_type}*>({current_dest_access})));"

                reassemble_nested_structs += f"\n\n{spaces}auto {list_element_name} = static_cast<const {iterator_type}*>({current_dest_access});"

                reassemble_nested_structs += f"\n{spaces}for(int32_t {next_it} = 1; {next_it} <= {current_member_count}; ++{next_it}){{"
                reassemble_nested_structs += f"\n{spaces}    if ({next_it} < {current_member_count}) {{"
                reassemble_nested_structs += f"\n{spaces}        const auto extensionOffset = {list_element_name}Traits[{next_it}].extensionOffset;"
                reassemble_nested_structs += f"\n{spaces}        forcePointerWrite(getNextField(*{list_element_name}), dynMem + extensionOffset);"
                reassemble_nested_structs += f"\n{spaces}    }}\n"

                if self.children:
                    reassemble_nested_structs += f"\n{spaces}    const auto extensionType = static_cast<int>({list_element_name}Traits[{next_it} - 1].extensionType);"

                    children_per_ext_dict = self.get_children_per_extension()
                    for enum_value, ext_children in children_per_ext_dict.items():
                        extension_type = ext_children[0].extension_data.type_name
                        reassemble_nested_structs += f"\n{spaces}    if (extensionType == {enum_value}) {{"
                        reassemble_nested_structs += f"\n{spaces}        auto& extension = *reinterpret_cast<const {extension_type}*>({list_element_name});"
                        reassemble_nested_structs += f"\n{spaces}        auto* extensionTraits = reinterpret_cast<DynamicStructTraits<{extension_type}>*>(dynMem + {current_offset_var});"
                        reassemble_nested_structs += f"\n{spaces}        {current_offset_var} += alignUpPow2<8>(sizeof(DynamicStructTraits<{extension_type}>));"
                        for child in ext_children:
                            next_it_2 = str(chr(ord(next_it) + 1))
                            reassemble_nested_structs += f"\n\n{spaces}        for(int32_t {next_it_2} = 0; {next_it_2} < 1; ++{next_it_2}) {{"
                            reassemble_nested_structs += "\n" + child.create_reassemble_nested_structs(current_offset_var, formatter, spaces_count + 12, next_it_2)
                            reassemble_nested_structs += f"\n{spaces}        }}"
                        reassemble_nested_structs += f"\n{spaces}    }}"

                reassemble_nested_structs += f"\n{spaces}    if ({next_it} < {current_member_count}) {{"
                reassemble_nested_structs += f"\n{spaces}        const auto pNextElement = getNext({list_element_name});"
                reassemble_nested_structs += f"\n{spaces}        const auto sizeInBytes = getUnderlyingSize(pNextElement);"
                reassemble_nested_structs += f"\n{spaces}        {current_offset_var} += alignUpPow2<8>(sizeInBytes);\n"

                reassemble_nested_structs += f"\n{spaces}        {list_element_name} = pNextElement;"
                reassemble_nested_structs += f"\n{spaces}    }}\n"
                reassemble_nested_structs += f"\n{spaces}}}\n"

            # Multi-dimensional array member
            if self.member.kind_details.element.kind.is_pointer_to_array() or self.member.kind_details.element.kind.is_opaque():
                reassemble_nested_structs += f"\n\n{spaces}auto* {current_member_name}Traits = reinterpret_cast<DynamicStructTraits<{current_member_element_type}>*>(dynMem + {current_offset_var});"
                reassemble_nested_structs += f"\n{spaces}{current_offset_var} += alignUpPow2<8>({current_member_count} * sizeof(DynamicStructTraits<{current_member_element_type}>));\n"

                next_it = str(chr(ord(it) + 1))
                reassemble_nested_structs += f"\n{spaces}for(int32_t {next_it} = 0; {next_it} < {current_member_count}; ++{next_it}){{\n"
                reassemble_nested_structs += self.create_nested_array_member_reassemble_structs(
                    self.member.kind_details.element,
                    current_member_name,
                    current_dest_access,
                    current_offset_var,
                    formatter,
                    spaces_count + 4,
                    next_it)
                reassemble_nested_structs += f"\n{spaces}}}\n"

            if self.children and not self.member.kind.is_opaque_list():
                reassemble_nested_structs += f"\n\n{spaces}auto* {current_member_name}Traits = reinterpret_cast<DynamicStructTraits<{current_member_element_type}>*>(dynMem + {current_offset_var});"
                reassemble_nested_structs += f"\n{spaces}{current_offset_var} += alignUpPow2<8>({current_member_count} * sizeof(DynamicStructTraits<{current_member_element_type}>));\n"
                next_it = str(chr(ord(it) + 1))

                for child in self.children:
                    reassemble_nested_structs += f"\n{spaces}for(int32_t {next_it} = 0; {next_it} < {current_member_count}; ++{next_it}){{\n"
                    reassemble_nested_structs += child.create_reassemble_nested_structs(
                        current_offset_var, formatter, spaces_count + 4, next_it)
                    reassemble_nested_structs += f"\n{spaces}}}\n"

            return reassemble_nested_structs

        def create_nested_array_member_reassemble_structs(
                self,
                element,
                parent_name,
                parent_dest_access,
                current_offset_var,
                formatter,
                spaces_count,
                it):
            spaces = " " * spaces_count
            nested_element = element.kind_details.element
            real_type = self.get_real_type(nested_element)

            parent_traits = f"{parent_name}Traits"
            current_dest_access = f"{parent_dest_access}[{it}]"
            current_element_offset = f"{parent_traits}[{it}].offset"
            current_element_count = f"{parent_traits}[{it}].count"
            current_element_name = f"{parent_name}_{it}"

            reassemble_nested_structs = f"""{spaces}if({current_element_offset} == -1){{
{spaces}    forcePointerWrite({current_dest_access}, nullptr);
{spaces}    continue;
{spaces}}}

{spaces}forcePointerWrite({current_dest_access}, dynMem + {current_element_offset});
{spaces}{current_offset_var} += alignUpPow2<8>({current_element_count} * sizeof({real_type}));"""

            if nested_element.kind.is_pointer_to_array():
                reassemble_nested_structs += f"\n\n{spaces}auto* {current_element_name}Traits = reinterpret_cast<DynamicStructTraits<{real_type}>*>(dynMem + {current_offset_var});"
                reassemble_nested_structs += f"\n{spaces}{current_offset_var} += alignUpPow2<8>({current_element_count} * sizeof(DynamicStructTraits<{real_type}>));\n"

                next_it = str(chr(ord(it) + 1))
                reassemble_nested_structs += f"\n{spaces}for(int32_t {next_it} = 0; {next_it} < {current_element_count}; ++{next_it}){{\n"
                reassemble_nested_structs += self.create_nested_array_member_reassemble_structs(
                    nested_element,
                    current_element_name,
                    current_dest_access,
                    current_offset_var,
                    formatter,
                    spaces_count + 4,
                    next_it)
                reassemble_nested_structs += f"\n{spaces}}}\n"
            elif nested_element.kind.is_struct():
                next_it = str(chr(ord(it) + 1))
                element.name = f"[{next_it}]"
                struct_layout = self.function_capture_layout.prepare_nested_member_layouts(self.member, self, element, is_extension_child=True)

                reassemble_nested_structs += f"\n\n{spaces}auto* nestedChildTraits = reinterpret_cast<DynamicStructTraits<{real_type}>*>(dynMem + {current_offset_var});"
                reassemble_nested_structs += f"\n{spaces}{current_offset_var} += alignUpPow2<8>({current_element_count} * sizeof(DynamicStructTraits<{real_type}>));\n"
                reassemble_nested_structs += f"\n{spaces}for(int32_t {next_it} = 0; {next_it} < {current_element_count}; ++{next_it}){{"
                for child in struct_layout.children:
                    reassemble_nested_structs += f"\n{spaces}    do {{"
                    reassemble_nested_structs += "\n" + child.create_reassemble_nested_structs(current_offset_var, formatter, spaces_count + 8, next_it)
                    reassemble_nested_structs += f"\n{spaces}    }} while (0);"
                reassemble_nested_structs += f"\n{spaces}}}"

            return reassemble_nested_structs

    def __init__(self, structures, function):
        self.structures = structures
        self.function = function
        self.fixed_ptr_array_args_layouts = []
        self.dynamic_ptr_array_args_layouts = []
        self.struct_members_layouts = {}

        for arg in function.traits.get_ptr_array_args():
            if arg.traits.uses_standalone_allocation or arg.traits.uses_staging_usm_allocation:
                continue
            # Ensure that capture layout includes nested structure fields.
            if arg.kind_details.element.kind.is_struct() and arg.kind_details.element.type.str in structures:
                if structures[arg.kind_details.element.type.str].traits.is_trivial():
                    continue
                members_to_capture = structures[arg.kind_details.element.type.str].members_to_capture()
                parent_layout = None
                self.struct_members_layouts[arg] = [
                    self.prepare_nested_member_layouts(
                        arg, parent_layout, member) for member in members_to_capture]

        for arg in function.traits.get_fixed_ptr_array_args():
            if arg.traits.uses_standalone_allocation or arg.traits.uses_staging_usm_allocation:
                continue
            arg_layout = FunctionCaptureLayout.ArgCaptureLayout()
            arg_layout.arg = arg
            arg_layout.fixed_size = True
            arg_layout.nested_capture = arg.kind_details.element.kind.is_pointer_to_array()
            assert False is arg_layout.nested_capture  # Supported only for dynamic length args for now
            self.fixed_ptr_array_args_layouts.append(arg_layout)

        prev = None
        for arg in function.traits.get_inline_dyn_ptr_array_args():
            arg_layout = FunctionCaptureLayout.ArgCaptureLayout()
            arg_layout.arg = arg
            arg_layout.fixed_size = False
            arg_layout.complex_count = arg.kind_details.num_elements.is_complex()
            arg_layout.complex_offset = prev and (prev.complex_count or prev.complex_offset)
            arg_layout.complex_offset = prev is not None  # temporary
            arg_layout.complex_count = True  # temporary
            arg_layout.uses_nested_capture = arg.kind_details.element.kind.is_pointer_to_array()
            self.dynamic_ptr_array_args_layouts.append(arg_layout)
            prev = arg_layout

        self.nested_capture_args_layouts = [
            arg_layout for arg_layout in self.dynamic_ptr_array_args_layouts if arg_layout.uses_nested_capture]
        self.emit_dynamic_traits = self.function.traits.uses_inline_dynamic_mem

        self.emit_per_arg_dynamic_traits = any(
            a for a in self.dynamic_ptr_array_args_layouts if (
                arg_layout.complex_count or arg_layout.complex_offset))

        self.dynamic_offsets_args_layouts = [arg_layout for arg_layout in self.dynamic_ptr_array_args_layouts if arg_layout.complex_offset]
        self.dynamic_counts_args_layouts = [arg_layout for arg_layout in self.dynamic_ptr_array_args_layouts if arg_layout.complex_count]

        self.returns = function.returns if not function.returns.type.is_void() else ""

        self.emit_per_arg_dynamic_traits = self.emit_per_arg_dynamic_traits or (len(self.dynamic_ptr_array_args_layouts) > 1)
        self.requires_raw_dynamic_mem = (len(self.dynamic_ptr_array_args_layouts) >
                                         1) or self.nested_capture_args_layouts or self.struct_members_layouts 
        

    def prepare_nested_member_layouts(self, parent, parent_layout, member, extension=None, is_extension_child=False):
        member_layout = FunctionCaptureLayout.MemberCaptureLayout()
        member_layout.member = member
        member_layout.parent = parent
        member_layout.parent_layout = parent_layout
        member_layout.children = []
        member_layout.extension_data = extension
        member_layout.is_extension_child = is_extension_child
        member_layout.function_capture_layout = self

        is_opaque_list_with_nontrivial_extension = member.kind.is_opaque_list() and member.kind_details.possible_nontrivial_nested_types
        is_nontrivial_struct_member = member.kind_details.element.kind.is_struct() and member.kind_details.element.type.str in self.structures

        if not is_opaque_list_with_nontrivial_extension and not is_nontrivial_struct_member:
            return member_layout

        if is_nontrivial_struct_member:
            type_names = [member.kind_details.element.type.str]
            extension_data = [None]
        else:
            type_names = [t.type_name for t in member.kind_details.possible_nontrivial_nested_types]
            extension_data = [t for t in member.kind_details.possible_nontrivial_nested_types]
            is_extension_child = True

        for i in range(0, len(type_names)):
            struct_type = self.structures[type_names[i]]
            members_to_capture = struct_type.members_to_capture()

            new_children = [
                self.prepare_nested_member_layouts(
                    member,
                    member_layout,
                    member_to_capture,
                    extension_data[i],
                    is_extension_child) for member_to_capture in members_to_capture]

            for child in new_children:
                member_layout.children.append(child)

        return member_layout

    def get_dynamic_array_size_str(self, element, count_str) -> str:
        if element.kind_details.element.kind.is_pointer_to_array():
            return f"{count_str} * sizeof(uint32_t)"
        else:
            return element.get_calculated_array_size(count=count_str)

    def get_calculated_dynamic_offset(self, arg) -> str:
        ret = ""
        for pred in self.dynamic_ptr_array_args_layouts:
            if pred.arg == arg:
                break
            predSize = f"alignUpPow2<8>({pred.arg.get_calculated_array_size()})"
            ret = f"{ret} + {predSize}" if ret else predSize

        return ret if ret else "0"

    def get_arg_dynamic_offset(self, arg) -> str:
        if arg in [arg_layout.arg for arg_layout in self.dynamic_offsets_args_layouts]:
            return f"{Formater.RpcMessage.Captures.Traits.f_offset_name(arg)}"
        else:
            return self.get_calculated_dynamic_offset(arg)

    def get_arg_dynamic_count(self, arg) -> str:
        if arg in [arg_layout.arg for arg_layout in self.dynamic_counts_args_layouts]:
            return f"{Formater.RpcMessage.Captures.Traits.f_count_name(arg)}"
        else:
            return arg.get_calculated_array_count()

    def generate_h(self):
        with open("captures.h.mako", "r", encoding="utf-8") as f:
            template = f.read()

        emit_copy_assignment = self.function.special_handling and self.function.special_handling.rpc and self.function.special_handling.rpc.emit_copy_assignment

        try:
            return Template(template).render(cl=self,
                                            inline_dyn_array_args=self.function.traits.get_inline_dyn_ptr_array_args(),
                                            fixed_array_args=self.function.traits.get_fixed_ptr_array_args(),
                                            dyn_offset_args=[arg_layout.arg for arg_layout in self.dynamic_offsets_args_layouts],
                                            dyn_count_args=[arg_layout.arg for arg_layout in self.dynamic_counts_args_layouts],
                                            nested_args=[arg_layout.arg for arg_layout in self.nested_capture_args_layouts],
                                            member_layout_formatter=MemberLayoutFormatter(),
                                            emit_copy_assignment=emit_copy_assignment,
                                            **vars(self), **Formater.get_all_formaters())
        except :
            handle_mako_error("captures.h.mako")

    def generate_cpp(self):
        with open("captures.cpp.mako", "r", encoding="utf-8") as f:
            template = f.read()

        try:
            return Template(template).render(cl=self,
                                            inline_dyn_array_args=self.function.traits.get_inline_dyn_ptr_array_args(),
                                            fixed_array_args=self.function.traits.get_fixed_ptr_array_args(),
                                            dyn_offset_args=[arg_layout.arg for arg_layout in self.dynamic_offsets_args_layouts],
                                            dyn_count_args=[arg_layout.arg for arg_layout in self.dynamic_counts_args_layouts],
                                            nested_args=[arg_layout.arg for arg_layout in self.nested_capture_args_layouts],
                                            member_layout_formatter=MemberLayoutFormatter(),
                                            **vars(self), **Formater.get_all_formaters())
        except :
            handle_mako_error("captures.cpp.mako")

def remove_prefix(text : str, prefix : str) -> str :
    return text[len(prefix) : ] if text.startswith(prefix) else text

class Redirection:
    def __init__(self, destination):
        self.destination = destination # Function
        self.conditions = []

class Function:
    def __init__(self, structures, src: dict, tracable_group_defaults : bool):
        self.structures = structures
        self.name = src["name"]
        self.latency = float(src.get("latency", 0.0))
        self.category = src.get("category", "Other")
        self.callAsync = bool(src.get("call_async", 0))
        self.returns = Returns(src.get("returns", {}))
        args_src = src.get("args", {})
        implicit_args_src = src.get("implicit_args", {})
        self.args = sorted([Arg(arg_id, args_src[arg_id]) for arg_id in args_src.keys()], key=lambda arg: arg.arg_id)
        self.implicit_args = sorted([Arg(arg_id, implicit_args_src[arg_id])
                                    for arg_id in implicit_args_src.keys()], key=lambda arg: arg.arg_id)
        self.args_by_name = {arg.name: arg for arg in self.args}
        self.cacheable = Cacheable(src.get("cacheable", {}))
        self.special_handling = SpecialHandling(src["special_handling"]) if "special_handling" in src.keys() else None
        self.ddi_category = src.get("ddi_category", "")
        self.aliased_function = None
        self.redirections = []
        self.const_expressions = []
        self.tracable_group_defaults = tracable_group_defaults
        self.recreateTraitsAndCaptureLayout(structures)

    def recreateTraitsAndCaptureLayout(self, structures):
        self.message_name = f"{self.name[0].upper()}{self.name[1:]}RpcM"
        self.traits = FunctionTraits(self, self.tracable_group_defaults)
        for arg in self.args:
            arg.create_traits(self, False)
        for iarg in self.implicit_args:
            iarg.create_traits(self, True)
        self.capture_layout = FunctionCaptureLayout(structures, self)


    def get_args_list_str(self) -> str:
        return ", ".join(arg.to_str() for arg in self.args)

    def get_call_params_list_str(self, prefix="") -> str:
        return ", ".join([f"{prefix}{arg.name}" for arg in self.args])


class MemberLayoutFormatter:
    def __init__(self):
        pass

    def generate_member_access(self, member_layout, it, prefix=""):
        # Only nested members have parent_layout. Args do not have it.
        if not member_layout.parent_layout:
            return f"{prefix}{member_layout.parent.name}[{it}].{member_layout.member.name}"
        elif member_layout.extension_data:
            return f"{prefix}{member_layout.member.name}"
        else:
            parent_it = str(chr(ord(it) - 1))
            member_access = f"{self.generate_member_access(member_layout.parent_layout, parent_it, prefix)}[{it}].{member_layout.member.name}"
            # Nested array elements' names are [it]. This is added in generic case - we don't need to double it.
            return self.trim_right_from(source=member_access, needle=".[")

    def generate_member_count_access(self, member_layout, it, prefix=""):
        if member_layout.member.kind_details.num_elements.is_constant():
            return member_layout.member.kind_details.num_elements.str

        member_access = self.generate_member_access(member_layout, it, prefix)
        if member_layout.member.kind.is_opaque_list():
            iterator_type = member_layout.member.kind_details.iterator_type
            return f"countOpaqueList(static_cast<const {iterator_type}*>({member_access}))"
        if member_layout.member.kind_details.num_elements.is_nullterminated():
            return f"Cal::Utils::countNullterminated({member_access})"
        elif member_layout.member.kind_details.num_elements.is_nullterminated_key():
            return f"Cal::Utils::countNullterminatedKey({member_access})"
        else:
            # Access to count for members is generated via replacement of structure member name with its count member.
            access = self.trim_right_from(source=member_access, needle=f".{member_layout.member.name}");
            return f"{access}.{member_layout.member.kind_details.num_elements.str}"

    def get_full_parent_name(self, member_layout, recursive_call=False):
        if not recursive_call:
            if not member_layout.parent_layout:
                return f"{member_layout.parent.name}"
            else:
                return self.get_full_parent_name(member_layout.parent_layout, True)
        else:
            if not member_layout.parent_layout:
                return f"{member_layout.parent.name}{self.capital(member_layout.member.name)}"
            else:
                return f"{self.get_full_parent_name(member_layout.parent_layout, True)}{self.capital(member_layout.member.name)}"

    def get_full_member_name(self, member_layout):
        # Nested array elements should not include [] in variable names.
        name = self.trim_right_from(source=member_layout.member.name, needle="[")

        # Only nested members have parent_layout.
        if not member_layout.parent_layout:
            return f"{member_layout.parent.name}{self.capital(name)}"
        else:
            return f"{self.get_full_member_name(member_layout.parent_layout)}{self.capital(name)}"

    def capital(self, name):
        if not name:
            return ""
        elif len(name) == 1:
            return f"{name[0].upper()}"
        else:
            return f"{name[0].upper() + name[1:]}"

    def trim_right_from(self, source, needle):
        to_trim = source.rfind(needle)
        if to_trim == -1:
            return source
        else:
            return source[:to_trim]

class Formater:
    class RpcMessage:
        class Captures:
            class Traits:
                def f_offset_name(arg):
                    return f"offset{arg.name[0].upper() + arg.name[1:]}"

                def f_count_name(arg):
                    return f"count{arg.name[0].upper() + arg.name[1:]}"

                def f_size_name(arg):
                    return f"size{arg.name[0].upper() + arg.name[1:]}"

            def f_arg_getter_name(arg):
                return f"get{arg.name[0].upper() + arg.name[1:]}"

    @staticmethod
    def get_all_formaters() -> dict:
        ret = vars(Formater.RpcMessage.Captures.Traits).copy()
        ret.update(vars(Formater.RpcMessage.Captures))
        ret.update(vars(Formater.RpcMessage))
        ret.update(vars(Formater))
        return ret


RpcMessageFormater = Formater.RpcMessage
CapturesFormater = Formater.RpcMessage.Captures
TraitsFormater = Formater.RpcMessage.Captures.Traits


def to_pascal_case(anycase: str) -> str:
    if not anycase:
        return anycase
    if("_") in anycase:
        return anycase.replace("_", " ").title().replace(" ", "")
    elif(" ") in anycase:
        return anycase.title().replace(" ", "")
    return anycase[0].upper() + anycase[1:]

def to_camel_case(anycase: str) -> str:
    pascal = to_pascal_case(anycase)
    if not pascal:
        return pascal
    return pascal[0].lower() + pascal[1:]

def to_snake_case(anycase: str) -> str:
    if not anycase:
        return anycase
    ret = anycase[0].lower() + anycase[1:]
    for ul in string.ascii_uppercase:
        if ul in ret:
            ret = ret.replace(ul, f"_{ul.lower()}")
    return ret

class FileHeaders:
    def __init__(self, src: dict):
        self.common = src.get("common", [])
        self.rpc_messages_h = src.get("rpc_messages_h", [])
        self.rpc_messages_cpp = src.get("rpc_messages_cpp", [])
        self.daemon_h = src.get("daemon_h", [])
        self.daemon_cpp = src.get("daemon_cpp", [])
        self.icd_h = src.get("icd_h", [])
        self.icd_cpp = src.get("icd_cpp", [])
        self.shared_h = src.get("shared_h", [])
        self.shared_cpp = src.get("shared_cpp", [])
        self.api = src.get("api", [])


class FormatRegexp:
    def __init__(self, src: dict):
        self.r_from = None
        self.r_to = None
        if src:
            self.r_from = src.get("from", "")
            self.r_to = src.get("to", "")

    def format(self, src: str, d: dict = {}) -> str:
        if not self.r_from:
            return src
        return re.sub(self.r_from.format(**d), self.r_to.format(**d), src)

class Condition:
    def __init__(self):
        self.evaluate = ""
        self.check = ""

def create_condition_based_on_ptr_kind(var_name, required_kind):
    cond = Condition()
    cond.evaluate = f"[[maybe_unused]] auto {var_name}_pointer_type = globalPlatform->getPointerType({var_name})"
    cond.check = f"{var_name}_pointer_type == {get_ptr_sharing_kind_abbreviation(required_kind)}"
    return cond

class Config:
    def __init__(self, root_config: dict, child_configs : list, filter):
        self.parent_config = None
        self.license = root_config["license"]
        self.subconfig_name = ""
        self.message_subtype_base = 0
        self.api_name = root_config["api_name"]
        self.loader_lib_names = root_config["loader_lib_names"]
        self.supports_tracing = root_config["supports_tracing"]
        self.filter = filter

        self.structures = [Structure(s) for s in root_config.get("structures", [])]
        self.structures_by_name = {struct.name: struct for struct in self.structures}
        for s in self.structures:
            s.set_all_structures_description(self.structures_by_name)

        self.tracable_group_defaults = {function_group["name"] : (function_group["tracable_default"] if "tracable_default" in function_group.keys() else False) for function_group in root_config.get("functions", [])}
        self.functions = {function_group["name"] : [Function(self.structures_by_name, f, self.tracable_group_defaults[function_group["name"]]) for f in function_group["members"]] for function_group in root_config.get("functions", [])}
        if self.filter:
            for group_name in self.functions.keys():
                new_group_members = []
                for func in self.functions[group_name]:
                    if re.match(self.filter, func.name):
                        new_group_members.append(func)
                self.functions[group_name] = new_group_members

        self.group_prefixes = {function_group["name"] : (function_group["prefix"] if "prefix" in function_group.keys() else "") for function_group in root_config.get("functions", [])}
        
        self.generate_variants()
            
        self.unimplemented = root_config.get("unimplemented", [])
        self.functions_by_name = {group_name : {func.name: func for func in self.functions[group_name]} for group_name in self.functions.keys()}
        self.icd_namespace = root_config.get("icd_namespace", "").split("::")
        self.icd_dispatch_table_type = root_config.get("icd_dispatch_table_type", "DispatchTableT")
        self.icd_init_dispatch_table_func_name_format = root_config.get("icd_init_dispatch_table_func_name_format", "initIcdDispatchTable")
        self.icd_get_extenion_func_addr_func_name = root_config.get("icd_get_extenion_func_addr_func_name", None)
        self.icd_acquire_global_object = root_config.get("icd_acquire_global_object", "")
        self.icd_acquire_channel = root_config.get("icd_acquire_channel", "")
        self.rpc_namespace = root_config.get("rpc_namespace", "").split("::")
        self.daemon_namespace = root_config.get("daemon_namespace", "").split("::")
        self.file_headers = FileHeaders(root_config.get("file_headers", {}))
        self.ddi_format_regexp0 = FormatRegexp(root_config.get("ddi_format_regexp0", None))
        self.ddi_format_regexp1_category = FormatRegexp(root_config.get("ddi_format_regexp1_category", None))
        self.result_type = root_config.get("result_type", "int")
        self.result_success = root_config.get("result_success", 0)

        for group_name in self.functions:
            for f in self.functions[group_name]:
                if not (f.special_handling and f.special_handling.icd and f.special_handling.icd.alias_to):
                    continue
                f.aliased_function = self.functions_by_name[group_name][f.special_handling.icd.alias_to]

        for func_category in self.unimplemented:
            category_name = func_category["name"]
            category_members = func_category["members"]
            assert not any(f for f in self.functions[category_name] if f.name in category_members)

        self.child_configs = dict()
        if child_configs:
            message_subtype_base = get_num_distinct_messages(self.functions, self.api_name)
            for cc_name in child_configs.keys():
                child_config_in = child_configs[cc_name]
                config_base = Config(root_config, None, filter)
                child_config = config_base
                child_config.subconfig_name = cc_name
                child_config.functions = []
                child_config.functions_by_name = dict()
                child_config.structures = []
                child_config.structures_by_name = dict()
                child_config.unimplemented = []
                child_config.icd_get_extenion_func_addr_func_name = child_config_in.get("icd_get_extenion_func_addr_func_name", None)
                child_config.file_headers = FileHeaders(child_config_in.get("file_headers", {}))

                child_config.structures = [Structure(s) for s in child_config_in.get("structures", [])]
                child_config.structures_by_name = {struct.name: struct for struct in child_config.structures}
                for s in child_config.structures:
                    s.set_all_structures_description(child_config.structures_by_name)

                child_config.tracable_group_defaults = {function_group["name"] : (function_group["tracable_default"] if "tracable_default" in function_group.keys() else False) for function_group in child_config_in.get("functions", [])}
                child_config.functions = {function_group["name"] : [Function(child_config.structures_by_name, f, child_config.tracable_group_defaults[function_group["name"]]) for f in function_group["members"]] for function_group in child_config_in.get("functions", [])}
                child_config.group_prefixes = {function_group["name"] : (function_group["prefix"] if "prefix" in function_group.keys() else "") for function_group in child_config_in.get("functions", [])}
                
                child_config.generate_variants()
                child_config.unimplemented = child_config_in.get("unimplemented", [])
                child_config.functions_by_name = {group_name : {func.name: func for func in child_config.functions[group_name]} for group_name in child_config.functions.keys()}
                child_config.icd_dispatch_table_type = []
                child_config.parent_config = self
                child_config.license = child_config_in["license"]
                child_config.message_subtype_base = message_subtype_base
                self.child_configs[cc_name] = child_config
                message_subtype_base += get_num_distinct_messages(child_config.functions, child_config.api_name)

    def get_extensions(self, include_variants=False):
        return {group_name : [f for f in self.functions[group_name] if f.traits.is_extension and not f.special_handling.is_variant()] for group_name in self.functions}
    
    def generate_variants(self):
        generated_variants = []
        for group in self.functions.keys():
            for func in self.functions[group]:
                if not func.traits.has_arg_kind_variants:
                    continue
                ids_of_args_with_variants = [arg_id for arg_id in range(0, len(func.args)) if func.args[arg_id].kind_variants]

                variants_per_arg_id = []
                for arg_id in ids_of_args_with_variants:
                    variants_per_arg_id.append([(arg_id, variant_id) for variant_id in range(0, len(func.args[arg_id].kind_variants))])
                
                all_variants = list(itertools.product(*variants_per_arg_id))
                all_redirections = []
                for variant_desc in all_variants:
                    function_variant = copy.deepcopy(func)
                    if not function_variant.special_handling:
                        function_variant.special_handling = SpecialHandling({})
                    function_variant.special_handling.variant_of = func.name if not (func.special_handling and func.special_handling.is_variant()) else func.special_handling.variant_of
                    if not function_variant.special_handling.icd:
                        function_variant.special_handling.icd = SpecialHandling.Icd({})
                    function_variant.special_handling.icd.not_in_dispatch_table = True
                    for variant_arg_desc in variant_desc:
                        function_variant.args[variant_arg_desc[0]].apply_kind_variant(variant_arg_desc[1])
                        function_variant.name += "_" + to_pascal_case(get_ptr_sharing_kind_abbreviation(function_variant.args[variant_arg_desc[0]].kind))
                    function_variant.recreateTraitsAndCaptureLayout(self.structures_by_name)
                    function_variant.const_expressions = []
                    for variant_arg_desc in variant_desc:
                        function_variant.const_expressions.append(f"[[maybe_unused]] constexpr auto {function_variant.args[variant_arg_desc[0]].name}_kind = {get_ptr_sharing_kind_abbreviation(function_variant.args[variant_arg_desc[0]].kind)}")
                    generated_variants.append(function_variant)
                    redir = Redirection(function_variant)
                    for arg_id in ids_of_args_with_variants:
                        redir.conditions.append(create_condition_based_on_ptr_kind(function_variant.args[arg_id].name, function_variant.args[arg_id].kind))
                    all_redirections.append(redir)
                func.redirections += all_redirections
                if not func.special_handling:
                        func.special_handling = SpecialHandling({})
                if not func.special_handling.rpc:
                        func.special_handling.rpc = SpecialHandling.Rpc({})
                func.dont_generate_rpc_message = True
                func.dont_generate_rpc_handler = True
            self.functions[group] = self.functions[group] + generated_variants

def get_configs(root_config : str) -> str:
    configs = dict()
    root_path = os.path.dirname(os.path.abspath(root_config))
    fname = os.path.basename(root_config)

    for root, dirs, files in os.walk(root_path, topdown=True):
        for f in files:
            if f == fname:
                with open(os.path.join(root, f), "r", encoding="utf-8") as f:
                    new_config = yaml.load(f, Loader=yaml.Loader)
                    license_path = os.path.join(root, license_fname)
                    if not os.path.exists(license_path):
                        license_path = base_license
                    with open(license_path, "r") as license:
                        new_config["config"]["license"] = license.read()
                    configs[remove_prefix(remove_prefix(remove_prefix(root, root_path), "/"), "\\")] = new_config

    return configs

def load(fname: str, filter : str) -> Config:
    print(f"Loading {fname} configs")
    configs = get_configs(fname)
    root_config = configs[""]
    return Config(root_config["config"], {name : configs[name]["config"] for name in configs.keys() if (name != "")}, filter)

def get_num_distinct_messages(grouped_functions, api_name):
    def should_skip_message_generation(func):
        if func.special_handling and func.special_handling.rpc and func.special_handling.rpc.dont_generate_rpc_message:
            return True
        if api_name == 'level_zero' and len(func.redirections):
            return True
        return False
    grouped_messages = [[f for f in grouped_functions[group_name] if not should_skip_message_generation(f)] for group_name in grouped_functions]
    ret = 0
    for group in grouped_messages:
        ret += len(group)
    return ret


def generate_rpc_messages_h(config: Config, additional_file_headers: list) -> str:
    def should_skip_message_generation(func):
        if func.special_handling and func.special_handling.rpc and func.special_handling.rpc.dont_generate_rpc_message:
            return True
        if config.api_name == 'level_zero' and len(func.redirections):
            return True
        return False

    functions_with_messages = {group_name : [f for f in config.functions[group_name] if not should_skip_message_generation(f)] for group_name in config.functions}
    flat_functions_with_messages = []
    for group_name in functions_with_messages:
        flat_functions_with_messages = flat_functions_with_messages + functions_with_messages[group_name]

    def get_message_subtype(func):
        return flat_functions_with_messages.index(func) + config.message_subtype_base

    def get_fq_message_name(func):
        return '::'.join(config.rpc_namespace + [func.message_name])

    def get_copy_from_or_to_caller_args(func, const_iargs):
        return (["const Captures::DynamicTraits &dynMemTraits"] if func.traits.uses_inline_dynamic_mem else []) + \
            ([f"{'const ' if const_iargs else ''}{get_fq_message_name(func)}ImplicitArgs &implicitArgs"] if func.implicit_args else [])

    def get_ptr_array_args(func):
        return func.traits.get_ptr_array_args()

    def get_struct_members_layouts(func):
        return func.capture_layout.struct_members_layouts

    with open("rpc_messages.h.mako", "r", encoding="utf-8") as f:
        template = f.read()
    try:
        return Template(template).render(
            config=config,
            unimplemented=config.unimplemented,
            daemon_namespace=config.daemon_namespace,
            rpc_namespace=config.rpc_namespace,
            rpc_functions={
                group_name : [f for f in config.functions[group_name] if not (
                    f.special_handling and f.special_handling.rpc and f.special_handling.rpc.dont_generate_rpc_message)] for group_name in config.functions},
            file_headers=config.file_headers.common +
            config.file_headers.rpc_messages_h +
            additional_file_headers,
            CapturesFormater=CapturesFormater,
            should_skip_message_generation=should_skip_message_generation,
            get_message_subtype=get_message_subtype,
            get_copy_from_caller_args=lambda f: get_copy_from_or_to_caller_args(
                f,
                True),
            get_copy_to_caller_args=lambda f: get_copy_from_or_to_caller_args(
                f,
                False),
            get_ptr_array_args=get_ptr_array_args,
            to_pascal_case=to_pascal_case,
            get_struct_members_layouts=get_struct_members_layouts,
            member_layout_formatter=MemberLayoutFormatter())
    except :
        handle_mako_error("rpc_messages.h.mako")


def generate_rpc_messages_cpp(config: Config, additional_file_headers: list) -> str:
    def should_skip_message_generation(func):
        if func.special_handling and func.special_handling.rpc and func.special_handling.rpc.dont_generate_rpc_message:
            return True
        if config.api_name == 'level_zero' and len(func.redirections):
            return True
        return False

    with open("rpc_messages.cpp.mako", "r", encoding="utf-8") as f:
        template = f.read()
    try:    
        return Template(template).render(
            config=config,
            rpc_namespace=config.rpc_namespace,
            file_headers=config.file_headers.common +
            config.file_headers.rpc_messages_cpp +
            additional_file_headers,
            should_skip_message_generation=should_skip_message_generation)
    except :
        handle_mako_error("rpc_messages.cpp.mako")


def generate_stub_lib_cpp(config: Config) -> str:
    with open("stub_lib.cpp.mako", "r", encoding="utf-8") as f:
        template = f.read()

    functions_to_stub = {group_name : [f for f in config.functions[group_name] if not f.traits.is_extension and not (f.special_handling and f.special_handling.icd and f.special_handling.icd.dont_generate_stub)] for group_name in config.functions}

    def get_func_handler_args_list_str(f):
        return ", ".join([f"{sarg}" for sarg in [arg.to_str() for arg in f.args]])

    try:
        return Template(template).render(config=config, functions_to_stub=functions_to_stub,
                                        file_headers=config.file_headers.api,
                                        get_func_handler_args_list_str=get_func_handler_args_list_str)
    except :
        handle_mako_error("stub_lib.cpp.mako")


def get_func_ddi_name(config: Config, func):
    if not func.ddi_category:
        return config.ddi_format_regexp0.format(func.name)

    # L0 specific: ddi_category cannot be extracted from function name if we have Exp suffix.
    regex_category = func.ddi_category[:-3] if func.ddi_category.endswith("Exp") else func.ddi_category

    name = f"{config.ddi_format_regexp1_category.format(config.ddi_format_regexp0.format(func.name), {'category' : regex_category})}"
    if "pfnExp" in name:
        name = name.replace("pfnExp", "pfn")
    name = f"{func.ddi_category}.{name}"

    return name


def get_ddi_name(config: Config, qual_name: str):
    if "." not in qual_name:
        return config.ddi_format_regexp0.format(qual_name)
    category, fname = qual_name.split(".")

    # L0 specific: ddi_category cannot be extracted from function name if we have Exp suffix.
    regex_category = category[:-3] if category.endswith("Exp") else category

    name = f"{config.ddi_format_regexp1_category.format(config.ddi_format_regexp0.format(fname), {'category' : regex_category})}"
    if "pfnExp" in name:
        name = name.replace("pfnExp", "pfn")

    if category not in name:
        name = f"{category}.{name}"
    return name


def generate_icd_h(config: Config, additional_file_headers: list) -> str:
    def get_func_handler_suffix(f):
        return f.special_handling.icd.handler_only_suffix if (
            f.special_handling and f.special_handling.icd) else ""

    def get_func_handler_name(f):
        return f.name + get_func_handler_suffix(f)

    def get_fq_message_name(f):
        return '::'.join(config.rpc_namespace + [f.message_name])

    def get_implicit_arg(f):
        return [f"{get_fq_message_name(f)}ImplicitArgs &implArgsFor{f.message_name}"] if f.implicit_args else []

    def get_func_handler_args_list_str(f):
        return ", ".join([f"{sarg}" for sarg in [arg.to_str() for arg in f.args] + get_implicit_arg(f)])
    functions_in_dispatch_table = {group_name : [f for f in config.functions[group_name] if not (
        f.special_handling and f.special_handling.icd and f.special_handling.icd.not_in_dispatch_table)] for group_name in config.functions}

    def get_func_ddi_name_bind(f):
        return get_func_ddi_name(config, f)

    def get_ddi_name_bind(f):
        return get_ddi_name(config, f)

    with open("icd.h.mako", "r", encoding="utf-8") as f:
        template = f.read()

    try:
        return Template(template).render(
            config=config,
            file_headers=config.file_headers.common +
            config.file_headers.icd_h +
            additional_file_headers,
            rpc_namespace=config.rpc_namespace,
            icd_namespace=config.icd_namespace,
            icd_namespace_str='::'.join(
                config.icd_namespace),
            functions=config.functions,
            functions_in_dispatch_table=functions_in_dispatch_table,
            get_func_handler_name=get_func_handler_name,
            get_func_handler_args_list_str=get_func_handler_args_list_str,
            get_func_ddi_name=get_func_ddi_name_bind,
            get_ddi_name=get_ddi_name_bind)
    except :
        handle_mako_error("icd.h.mako")


def generate_icd_cpp(config: Config, additional_file_headers: list) -> str:
    def get_func_handler_suffix(f):
        return f.special_handling.icd.handler_only_suffix if (
            f.special_handling and f.special_handling.icd) else ""

    def get_func_handler_name(f):
        return f.name + get_func_handler_suffix(f)

    def get_fq_message_name(f):
        return '::'.join(config.rpc_namespace + [f.message_name])

    def get_implicit_arg(f):
        return [f"{get_fq_message_name(f)}ImplicitArgs &implArgsFor{f.message_name}"] if f.implicit_args else []

    def get_implicit_call_param(f):
        return [f"implArgsFor{f.message_name}"] if f.implicit_args else []

    def get_func_handler_args_list_str(f):
        return ", ".join([f"{sarg}" for sarg in [arg.to_str() for arg in f.args] + get_implicit_arg(f)])

    def get_func_handler_call_params_list_str(f):
        return ", ".join(
            [f"{sarg}" for sarg in [arg.name for arg in f.args] + get_implicit_call_param(f)])

    def get_copy_from_or_to_caller_call_params_list(f):
        return (["dynMemTraits"] if f.traits.uses_inline_dynamic_mem else [
        ]) + ([f"implArgsFor{f.message_name}"] if f.implicit_args else [])

    def get_copy_from_or_to_caller_call_params_list_str(f):
        return ", ".join(get_copy_from_or_to_caller_call_params_list(f))

    def dont_generate_handler(f):
        return f.special_handling and f.special_handling.icd and f.special_handling.icd.dont_generate_handler

    def get_func_ddi_name_bind(f):
        return get_func_ddi_name(config, f)

    def get_ddi_name_bind(f):
        return get_ddi_name(config, f)

    functions_in_dispatch_table = {group_name : [f for f in config.functions[group_name] if not (
        f.special_handling and f.special_handling.icd and f.special_handling.icd.not_in_dispatch_table)] for group_name in config.functions}

    non_variant_functions = {group_name : [f for f in config.functions[group_name] if not (f.special_handling and f.special_handling.is_variant())] for group_name in config.functions}

    def itentionally_ignore(f):
        return f.special_handling and f.special_handling.icd and f.special_handling.icd.intentionally_ignore

    def get_args_requiring_translation_before(f):
        return [
            arg for arg in f.args if arg.translate_before or
                (arg.kind.is_pointer_to_array() and arg.kind_details.element.translate_before) or
                (arg.kind.is_struct() and config.structures_by_name[arg.type.str].traits.requires_translation_of_members_before()) or
                (arg.kind.is_pointer_to_array() and arg.kind_details.element.kind.is_struct() and
                 config.structures_by_name[arg.kind_details.element.type.str].traits.requires_translation_of_members_before())]

    def get_args_requiring_translation_after(f):
        return [
            arg for arg in f.args if arg.translate_after or (
                arg.kind.is_pointer_to_array() and arg.kind_details.element.translate_after)]

    def get_arg_from_capture(arg):
        return f"get{arg.name[0].upper() + arg.name[1:]}()" if arg.traits.uses_dynamic_arg_getter else arg.name

    def is_unsupported(f):
        return f.special_handling and f.special_handling.icd and f.special_handling.icd.unsupported

    icd_extensions = {group_name : [f for f in config.functions[group_name] if f.special_handling and f.special_handling.icd and f.special_handling.icd.in_get_extension_function_address and not f.special_handling.is_variant()] for group_name in config.functions}

    def can_be_null(arg):
        return arg.kind_details and arg.kind_details.can_be_null
    

    with open("icd.cpp.mako", "r", encoding="utf-8") as f:
        template = f.read()

    try:
        return Template(template).render(
            config=config,
            file_headers=config.file_headers.common + config.file_headers.icd_cpp + additional_file_headers,
            icd_namespace=config.icd_namespace,
            icd_namespace_str='::'.join(
                config.icd_namespace),
            functions=config.functions,
            functions_in_dispatch_table=functions_in_dispatch_table,
            icd_extensions=icd_extensions,
            non_variant_functions=non_variant_functions,
            get_func_handler_name=get_func_handler_name,
            get_func_handler_args_list_str=get_func_handler_args_list_str,
            get_fq_message_name=get_fq_message_name,
            get_func_handler_call_params_list_str=get_func_handler_call_params_list_str,
            dont_generate_handler=dont_generate_handler,
            itentionally_ignore=itentionally_ignore,
            get_copy_from_caller_call_params_list_str=get_copy_from_or_to_caller_call_params_list_str,
            get_copy_to_caller_call_params_list_str=get_copy_from_or_to_caller_call_params_list_str,
            get_args_requiring_translation_before=get_args_requiring_translation_before,
            get_args_requiring_translation_after=get_args_requiring_translation_after,
            get_arg_from_capture=get_arg_from_capture,
            is_unsupported=is_unsupported,
            can_be_null=can_be_null,
            to_pascal_case = to_pascal_case,
            to_camel_case = to_camel_case,
            to_snake_case = to_snake_case,
            get_ddi_name = get_ddi_name_bind,
            get_func_ddi_name = get_func_ddi_name_bind,
            remove_prefix = remove_prefix,

            prologue=lambda f: f.special_handling.icd.handler_prologue if (
                f.special_handling and f.special_handling.icd and f.special_handling.icd.handler_prologue) else "",
            epilogue=lambda f: f.special_handling.icd.handler_epilogue if (
                f.special_handling and f.special_handling.icd and f.special_handling.icd.handler_epilogue) else "",
            epilogue_data=lambda f: f.special_handling.icd.handler_epilogue_data if (
                f.special_handling and f.special_handling.icd and f.special_handling.icd.handler_epilogue_data) else "")
    except :
        handle_mako_error("icd.cpp.mako")


def generate_service_h(config: Config, additional_file_headers: list) -> str:
    with open("service.h.mako", "r", encoding="utf-8") as f:
        template = f.read()

    def should_skip_message_generation(func):
        if func.special_handling and func.special_handling.rpc and func.special_handling.rpc.dont_generate_rpc_message:
            return True
        if config.api_name == 'level_zero' and len(func.redirections):
            return True
        return False

    functions_with_messages = {group_name : [f for f in config.functions[group_name] if not should_skip_message_generation(f)] for group_name in config.functions}
    last_function_with_message_group = list(functions_with_messages.keys())[-1]
    last_function_with_message = None
    if functions_with_messages[last_function_with_message_group]:
        last_function_with_message = functions_with_messages[last_function_with_message_group][-1]

    all_extensions = config.get_extensions()
    rpc_extensions = {group_name : [
        ext for ext in all_extensions[group_name] if not (
            ext.aliased_function or (
                ext.special_handling and ext.special_handling.rpc and (
                    ext.special_handling.rpc.dont_generate_rpc_message or ext.special_handling.rpc.dont_generate_rpc_handler)))] for group_name in all_extensions}

    rpc_functions = dict()
    if last_function_with_message:
        rpc_functions = {group_name : [
            f for f in config.functions[group_name] if not (
                f.aliased_function or (
                    f.special_handling and f.special_handling.rpc and (
                        f.special_handling.rpc.dont_generate_rpc_message or f.special_handling.rpc.dont_generate_rpc_handler)))] for group_name in config.functions}
    standard_functions = {group_name : [f for f in config.functions[group_name] if not (f.aliased_function or f.traits.is_extension or f.traits.is_variant)] for group_name in config.functions}

    def get_rpc_handler_suffix(rpc_func):
        return "" if not (
            rpc_func.special_handling and rpc_func.special_handling.rpc and rpc_func.special_handling.rpc.handler_only_suffix) else rpc_func.special_handling.rpc.handler_only_suffix

    def use_rpc_custom_handler(rpc_func):
        return rpc_func.special_handling and rpc_func.special_handling.rpc and rpc_func.special_handling.rpc.custom_handler

    def get_api_func_name(rpc_func):
        return rpc_func.name if not (rpc_func.special_handling and rpc_func.special_handling.is_variant()
                                     ) else rpc_func.special_handling.variant_of

    def get_rpc_func_fqfn(rpc_func):
        return f"{'::'.join(config.daemon_namespace + ['Standard', get_api_func_name(rpc_func)])}" if not rpc_func.traits.is_extension else f"{'::'.join(config.daemon_namespace + ['Extensions', get_api_func_name(rpc_func)])}"

    def requires_malloc_shmem_zero_copy_handler(rpc_func):
        return rpc_func.traits.requires_malloc_shmem_zero_copy_handler

    def get_struct_members_layouts(rpc_func):
        return rpc_func.capture_layout.struct_members_layouts

    def get_arg_from_api_command_struct(rpc_func, arg):
        if arg.is_always_queried():
            return f"&apiCommand->captures.{arg.name}"
        if arg.kind.is_pointer_to_array() and not (arg.traits.uses_standalone_allocation or arg.traits.uses_staging_usm_allocation):
            if arg.kind_details.num_elements.is_constant() or not rpc_func.traits.uses_dynamic_arg_getters:
                captured_arg = f"{'&' if (arg.kind_details.num_elements.get_constant() == 1) else ''}apiCommand->captures.{arg.name}"
            else:
                captured_arg = f"apiCommand->captures.get{arg.name[0].upper() + arg.name[1:]}()"
            if arg.traits.uses_nested_capture:
                captured_arg += ".data()"
            return f"apiCommand->args.{arg.name} ? {captured_arg} : nullptr"
        else:
            return f"apiCommand->args.{arg.name}"

    try:
        return Template(template).render(
            config=config,
            extensions=rpc_extensions,
            standard_functions=standard_functions,
            rpc_functions=rpc_functions,
            file_headers=config.file_headers.common +
            config.file_headers.daemon_h +
            additional_file_headers,
            daemon_namespace=config.daemon_namespace,
            daemon_namespace_str='::'.join(
                config.daemon_namespace),
            ext_loader='::'.join(
                config.daemon_namespace +
                ['getExtensionFuncAddress']),
            get_rpc_handler_suffix=get_rpc_handler_suffix,
            use_rpc_custom_handler=use_rpc_custom_handler,
            get_api_func_name=get_api_func_name,
            get_rpc_func_fqfn=get_rpc_func_fqfn,
            get_arg_from_api_command_struct=get_arg_from_api_command_struct,
            requires_malloc_shmem_zero_copy_handler=requires_malloc_shmem_zero_copy_handler,
            to_pascal_case=to_pascal_case,
            get_struct_members_layouts=get_struct_members_layouts,
            prologue=lambda f: f.special_handling.rpc.handler_prologue if (
                f.special_handling and f.special_handling.rpc and f.special_handling.rpc.handler_prologue) else "",
            epilogue=lambda f: f.special_handling.rpc.handler_epilogue if (
                f.special_handling and f.special_handling.rpc and f.special_handling.rpc.handler_epilogue) else "",
            last_function_with_message=last_function_with_message,
            should_skip_message_generation=should_skip_message_generation)
    except :
        handle_mako_error("service.h.mako")


def generate_service_cpp(config: Config, additional_file_headers: list) -> str:
    with open("service.cpp.mako", "r", encoding="utf-8") as f:
        template = f.read()

    all_extensions = config.get_extensions()
    rpc_extensions = {group_name : [
        ext for ext in all_extensions[group_name] if not (
            ext.aliased_function or (
                ext.special_handling and ext.special_handling.rpc and (
                    ext.special_handling.rpc.dont_generate_rpc_message or ext.special_handling.rpc.dont_generate_rpc_handler)))] for group_name in all_extensions}

    standard_functions = {group_name : [f for f in config.functions[group_name] if not (f.aliased_function or f.traits.is_extension or f.traits.is_variant)] for group_name in config.functions}
    try:
        return Template(template).render(config=config, extensions=rpc_extensions, standard_functions=standard_functions,
                                        file_headers=config.file_headers.common + config.file_headers.daemon_cpp + additional_file_headers,
                                        daemon_namespace=config.daemon_namespace, daemon_namespace_str='::'.join(config.daemon_namespace),
                                        ext_loader='::'.join(config.daemon_namespace + ['getExtensionFuncAddress']),
                                        to_pascal_case=to_pascal_case)
    except :
        handle_mako_error("service.cpp.mako")


def generate_shared_h(config: Config, additional_file_headers: list) -> str:
    with open("shared.h.mako", "r", encoding="utf-8") as f:
        template = f.read()
    try:
        return Template(template).render(config=config, unimplemented=config.unimplemented,
                                        file_headers=config.file_headers.common + config.file_headers.shared_h + additional_file_headers,
                                        daemon_namespace=config.daemon_namespace)
    except :
        handle_mako_error("shared.h.mako")


def license_line_to_cpp_comment(line :str) -> str:
    return f" * {line}" if line else " *"
    

def license_to_cpp_comment(raw_text: str) -> str:
    output = "/*\n"
    output += "\n".join([license_line_to_cpp_comment(line) for line in raw_text.splitlines()])
    output += "\n */\n\n"

    return output


def dump(data: str, fname: str, license: str) -> None:
    print(f"Writing {fname}")
    cal_license = license_to_cpp_comment(license)
    with open(fname, "wb") as f:
        contents = cal_license
        contents += "#pragma once\n" if fname.endswith((".h", ".hpp")) else ""
        contents += data
        f.write(contents.encode("utf-8"))

def wrapped_parallel_job(target, args):
    try:
        target(*args)
    except Exception as e :
        print(e)

def generate(config: Config, out_dir: str, prefix:str, file_filter:str, max_num_workers:int, parallel_jobs) -> str:
    os.makedirs(out_dir, exist_ok=True)
    fname_base = "generated" + prefix
    fpath_base = os.path.join(out_dir)

    files_to_generate = [  
                           (f"{fname_base}_rpc_messages_{config.api_name}.h", lambda config : generate_rpc_messages_h(config, [])),
                           (f"{fname_base}_rpc_messages_{config.api_name}.cpp", lambda config : generate_rpc_messages_cpp(config, [f"#include \"{fname_base}_rpc_messages_{config.api_name}.h\""])),
                           (f"{fname_base}_icd_{config.api_name}.h", lambda config : generate_icd_h(config, [])),
                           (f"{fname_base}_icd_{config.api_name}.cpp", lambda config : generate_icd_cpp(config, [f"#include \"{fname_base}_icd_{config.api_name}.h\"", f"#include \"{fname_base}_rpc_messages_{config.api_name}.h\""])),
                           (f"{fname_base}_service_{config.api_name}.h", lambda config : generate_service_h(config, [f"#include \"{fname_base}_rpc_messages_{config.api_name}.h\""])),
                           (f"{fname_base}_service_{config.api_name}.cpp", lambda config : generate_service_cpp(config, [f"#include \"{fname_base}_service_{config.api_name}.h\""])),
                           (f"{fname_base}_shared_{config.api_name}.h", lambda config : generate_shared_h(config, [])),
                           (f"{fname_base}_stub_lib_{config.api_name}.cpp", lambda config : generate_stub_lib_cpp(config)),
                         ]

    jobs = []
    for f in files_to_generate:
        path, generator = (f[0], f[1])
        if file_filter and not re.match(file_filter, path):
            print(f"Skipping generation of {path}")
            continue
        wrapped_generator = lambda generator, config, path,: dump(generator(config), os.path.join(fpath_base, path), config.license)
        job = (wrapped_generator, (generator, config, path))
        jobs.append(job)

    if max_num_workers > 1:
        for job in jobs:
            wrapped_job = (wrapped_parallel_job, (job[0], job[1]))
            parallel_jobs.append(wrapped_job)
        
    else:
        for job in jobs:
            job[0](*job[1])
        

def print_help():
    print("""This is generator for Compute Aggregation Layer RPC protocol. Run without any parameters to regenerate the files.
          
--help                             prints this help
--func_filter REGEXP               only API functions that match this pattern (regular expression) will be taken into account
--file_filter REGEXP               only output files that matchi this pattern (regular expression) will be taken into account
--configs NAME1.yml,NAME2.yml,...  chooses configuration files to be used (instead of default ones)
-j NUM                             maximum number of worker threads
          """)

def main(args):
    path = "../cached/"
    func_filter = ""
    file_filter = ""

    i = 1
    configs = ["level_zero.yml", "ocl.yml"]
    max_num_workers = 1
    max_num_workers_arg_value_it = -1
    configs_arg_value_it = -1
    is_child = False
    while i < len(args):
        if args[i] == "--help":
            print_help()
            return 0
        elif args[i] == "--is_child":
            is_child = True
            i += 1
        elif args[i] == "--func_filter":
            func_filter = args[i+1]
            i+=2
            if not is_child:
                print(f"filter (treated as regexp) : {func_filter}")
        elif args[i] == "--file_filter":
            file_filter = args[i+1]
            i+=2
            if not is_child:
                print(f"generated file filter (treated as regexp) : {file_filter}")
        elif args[i] == "--configs":
            configs = args[i+1].split(",")
            configs_arg_value_it = i+1
            i+=2
        elif args[i] == "-j":
            max_num_workers = int(args[i+1])
            max_num_workers_arg_value_it = i+1
            i+=2
        else:
            path = args[i]
            i+=1

    if max_num_workers > 1 and (len(configs) > 1):
        num_workers_per_config = int(max_num_workers/(len(configs)))
        if max_num_workers_arg_value_it == -1:
            args.append("-j")
            args.append(num_workers_per_config)
        else:
            args[max_num_workers_arg_value_it] = num_workers_per_config
        if configs_arg_value_it == -1:
            configs_arg_value_it = len(args)+1
            args.append("--configs")
            args.append(configs)
        args.append("--is_child")
        workers = []
        
        for config in configs:
            args[configs_arg_value_it] = config
            w = multiprocessing.Process(target=main, args=[args])
            w.start()
            workers.append(w)

        for w in workers:
            w.join()
        return
    
    if not is_child:
        print(f"Output directory : {path}")
        print(f"Base configurations : [{', '.join(configs)}]")
    parallel_jobs = []
    for config_name in configs:
        config = load(config_name, func_filter)
        config.func_filter = func_filter
        generate(config, path, "", file_filter, max_num_workers, parallel_jobs)
        for cc_name in config.child_configs.keys():
            generate(config.child_configs[cc_name], os.path.join(path, cc_name), "_"+cc_name, file_filter, max_num_workers, parallel_jobs)

    if parallel_jobs:
        print(f"Running {len(parallel_jobs)} jobs in parallel (-j {max_num_workers})")
        active_workers = []
        while parallel_jobs:
            if active_workers or (len(active_workers) < max_num_workers):
                w = multiprocessing.Process(target=parallel_jobs[-1][0], args=(parallel_jobs[-1][1]))
                active_workers.append(w)
                parallel_jobs = parallel_jobs[0:-1]
                w.start()
            else:
                for worker in active_workers:
                    if not worker.is_alive():
                        worker.join()
                        active_workers = active_workers.remove(worker)
                        break
                if active_workers and (len(active_workers) == max_num_workers):
                    time.sleep(1)
        while active_workers:
            for worker in active_workers:
                if not worker.is_alive():
                    worker.join()
                    active_workers = active_workers.remove(worker)
                    break
            time.sleep(0.1)


if __name__ == "__main__":
    main(sys.argv)
