#
# Copyright (C) 2022 Intel Corporation
#
# SPDX-License-Identifier: MIT
#

import os
import re
import sys
import yaml

from mako.template import Template


class ServerAccess:
    def __init__(self, src: str):
        self.str = src

    def read_only(self) -> bool:
        return self.str == "read"

    def write_only(self) -> bool:
        return self.str == "write"

    def read_write(self) -> bool:
        return self.str == "read_write"


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

    def is_pointer_function(self) -> bool:
        return self.str == "ptr_func"

    def is_struct(self) -> bool:
        return self.str == "struct"

    def is_opaque(self) -> bool:
        return self.str == "opaque"

    def is_opaque_list(self) -> bool:
        return self.str == "opaque_list"


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
        self.requires_opaque_elements_translation_before = src.get("requires_opaque_elements_translation_before", False)
        self.always_queried = src.get("always_queried", False)

class CaptureMode:
    def __init__(self, src: str):
        self.str = src

    def is_inline_mode(self):
        return self.str == "inline"

    def is_standalone_mode(self):
        return self.str == "standalone"

class CaptureReclaimMethod:
    def __init__(self, src: str):
        self.str = src

    def is_immediate_mode(self):
        return self.str == "immediate"

    def format(self, ptr):
        return self.str.format(allocation=ptr)

class CaptureDetails:
    def __init__(self, src: dict):
        self.mode = CaptureMode(src.get("mode", "inline"))
        self.reclaim_method = CaptureReclaimMethod(src.get("reclaim_method", "immediate"))

class ArgTraits:
    def __init__(self, arg, parent_function):
        self.arg = arg
        self.uses_standalone_allocation = arg.capture_details.mode.is_standalone_mode()
        if self.uses_standalone_allocation:
            assert( arg.kind.is_pointer() )
        self.uses_inline_dynamic_mem = arg.kind.is_pointer_to_array() and (not arg.kind_details.num_elements.is_constant()) and (not self.uses_standalone_allocation)
        self.uses_dynamic_arg_getter = parent_function.traits.uses_dynamic_arg_getters and self.uses_inline_dynamic_mem
        self.uses_nested_capture = arg.kind.is_pointer_to_array() and arg.kind_details.element.kind.is_pointer_to_array()


class Arg:
    def __init__(self, arg_id, src: dict):
        self.arg_id = int(arg_id)
        self.name = src["name"]
        self.type = Type(src.get("type"))
        self.kind = Kind(src.get("kind"))
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

    def get_calculated_elements_count(self, arg_prefix: str = ""):
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
            if "{arg_prefix}" in self.kind_details.num_elements.str:
                return self.kind_details.num_elements.str.format(arg_prefix=arg_prefix)
            else:
                return f"{arg_prefix}{self.kind_details.num_elements.str}"

    def get_calculated_array_size(self, arg_prefix: str = "", count: str = None):
        assert self.kind.is_pointer_to_array

        mul = "" if self.kind_details.element.type.is_void() else f" * sizeof({self.kind_details.element.type.str})"

        if not count:
            count = self.get_calculated_elements_count(arg_prefix)
        return f"{count}{mul}"

    def create_traits(self, parent_function) -> None:
        self.traits = ArgTraits(self, parent_function)

    def is_always_queried(self) -> bool:
        return self.is_kind_complex() and self.kind_details.always_queried


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
            if self.handler_prologue and not isinstance(self.handler_prologue, list):
                self.handler_prologue = [self.handler_prologue]
            if self.handler_epilogue and not isinstance(self.handler_epilogue, list):
                self.handler_epilogue = [self.handler_epilogue]

    class Rpc:
        def __init__(self, src: dict):
            self.dont_generate_rpc_message = src.get("dont_generate_rpc_message", False)
            self.dont_generate_rpc_handler = src.get("dont_generate_rpc_handler", False)
            self.dont_generate_call_directly = src.get("dont_generate_call_directly", False)
            self.handler_only_suffix = src.get("handler_only_suffix", "")
            self.custom_handler = src.get("custom_handler", False)
            self.emit_copy_assignment = src.get("emit_copy_assignment", False)

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
    def __init__(self, function):
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

    def requires_copy_from_caller(self, ptr_array_args, implicit_args):
        is_copy_required_for_ptr_array_args = any(not arg.kind_details.server_access.write_only() for arg in ptr_array_args if not arg.capture_details.mode.is_standalone_mode())
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
        return [arg for arg in self.function.args if arg.capture_details.mode.is_standalone_mode()]

    def get_ptr_array_args(self):
        return [arg for arg in self.function.args if arg.kind.is_pointer_to_array()]

    def get_inline_dyn_ptr_array_args(self):
        dyn_ptr_array_args = [arg for arg in self.function.args if arg.kind.is_pointer_to_array()
                             and (not arg.kind_details.num_elements.is_constant()) and (not arg.capture_details.mode.is_standalone_mode())]

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

        def create_required_size_calculation(self, total_size_var, formatter, spaces_count, it):
            spaces = " " * spaces_count
            parent_it = str(chr(ord(it) - 1))
            current_member_name = formatter.get_full_member_name(self)
            current_member_access = formatter.generate_member_access(self, parent_it)
            current_member_count_name = current_member_name + "Count"
            current_member_count_access = formatter.generate_member_count_access(self, parent_it)
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
                member_size_calculation += f"\n{spaces}    {list_element_name} = getNext({list_element_name});"
                member_size_calculation += f"\n{spaces}}}\n"

            # Multi-dimensional array member
            if self.member.kind_details.element.kind.is_pointer_to_array() or self.member.kind_details.element.kind.is_opaque():
                member_size_calculation += f"\n{spaces}{total_size_var} += alignUpPow2<8>({current_member_count_name} * sizeof(DynamicStructTraits<{current_member_element_type}>));"
                member_size_calculation += f"\n{spaces}for(uint32_t {it} = 0; {it} < {current_member_count_name}; ++{it}){{\n"
                member_size_calculation += self.create_nested_array_member_size_calculation(
                    self.member.kind_details.element.kind_details.element, current_member_name, total_size_var, formatter, spaces_count + 4, str(chr(ord(it) + 1)))
                member_size_calculation += f"\n{spaces}}}\n"

            if self.children:
                member_size_calculation += f"\n{spaces}{total_size_var} += alignUpPow2<8>({current_member_count_name} * sizeof(DynamicStructTraits<{current_member_element_type}>));"
                for child in self.children:
                    member_size_calculation += f"\n{spaces}for(uint32_t {it} = 0; {it} < {current_member_count_name}; ++{it}){{\n"
                    member_size_calculation += child.create_required_size_calculation(
                        total_size_var, formatter, spaces_count + 4, str(chr(ord(it) + 1)))
                    member_size_calculation += f"\n{spaces}}}\n"

            return member_size_calculation

        def create_nested_array_member_size_calculation(self, element, parent_name, total_size_var, formatter, spaces_count, it):
            # In case of requirement for dynamic size, a correct way of getting size needs to be implemented here.
            assert element.kind.is_opaque() or element.kind_details.num_elements.is_constant()

            spaces = " " * spaces_count
            real_type = element.type.str if not element.kind.is_opaque() else element.kind_details.underlying_type.type.str
            real_count = element.kind_details.num_elements.get_constant() if not element.kind.is_opaque() else "1"

            prev_it = str(chr(ord(it) - 1))
            current_element_name = f"{parent_name}_{prev_it}"
            current_element_access = f"{parent_name}[{prev_it}]"
            current_element_count_name = f"{current_element_name}Count"

            member_size_calculation = f"""{spaces}const auto& {current_element_name} = {current_element_access};
{spaces}if(!{current_element_name}){{
{spaces}    continue;
{spaces}}}

{spaces}const auto {current_element_count_name} = static_cast<uint32_t>({real_count});
{spaces}if(!{current_element_count_name}){{
{spaces}    continue;
{spaces}}}
{spaces}{total_size_var} += alignUpPow2<8>({current_element_count_name} * sizeof({real_type}));"""

            if element.kind_details.element.kind.is_pointer_to_array() or element.kind_details.element.kind.is_opaque():
                member_size_calculation += f"\n{spaces}{total_size_var} += alignUpPow2<8>({current_element_count_name} * sizeof(DynamicStructTraits<{real_type}>));"
                member_size_calculation += f"\n{spaces}for(uint32_t {it} = 0; {it} < {real_count}; ++{it}){{\n"
                member_size_calculation += self.create_nested_array_member_size_calculation(
                    element.kind_details.element, current_element_name, total_size_var, formatter, spaces_count + 4, str(chr(ord(it) + 1)))
                member_size_calculation += f"\n{spaces}}}"

            return member_size_calculation

        def create_copy_to_caller(self, current_offset_var, formatter, spaces_count, it):
            spaces = " " * spaces_count
            parent_name = formatter.get_full_parent_name(self)
            current_dest_access = f"dest{formatter.capital(formatter.generate_member_access(self, it))}"

            current_member_name = formatter.get_full_member_name(self)
            current_member_offset = f"{parent_name}Traits[{it}].{self.member.name}Offset"
            current_member_count = f"{parent_name}Traits[{it}].{self.member.name}Count"
            current_member_element_type = self.member.kind_details.element.type.str

            copy_to_caller = f"""{spaces}if({parent_name}Traits[{it}].{self.member.name}Offset == -1){{
{spaces}    continue;
{spaces}}}"""

            if not self.member.kind.is_opaque_list():
                copy_to_caller += f"\n{spaces}{current_offset_var} += alignUpPow2<8>({current_member_count} * sizeof({current_member_element_type}));"
            else:
                next_it = str(chr(ord(it) + 1))
                iterator_type = self.member.kind_details.iterator_type
                list_element_name = f"{current_member_name}ListElement"
                opaque_traits = self.member.kind_details.opaque_traits_name

                copy_to_caller += f"\n\n{spaces}{current_dest_access} = {parent_name}Traits[{it}].{self.member.name}FirstOriginalElement;"

                copy_to_caller += f"\n\n{spaces}auto {list_element_name}Traits = reinterpret_cast<{opaque_traits}*>(dynMem + {current_offset_var});"
                copy_to_caller += f"\n{spaces}{current_offset_var} += alignUpPow2<8>({current_member_count} * sizeof({opaque_traits}));"

                copy_to_caller += f"\n\n{spaces}auto {list_element_name} = static_cast<const {iterator_type}*>({current_dest_access});"

                copy_to_caller += f"\n{spaces}for(int32_t {next_it} = 0; {next_it} < {current_member_count}; ++{next_it}){{"
                copy_to_caller += f"\n{spaces}    const auto sizeInBytes = getUnderlyingSize({list_element_name});"
                copy_to_caller += f"\n{spaces}    {current_offset_var} += alignUpPow2<8>(sizeInBytes);\n"

                copy_to_caller += f"\n{spaces}    const auto extensionType = getExtensionType({list_element_name});"
                copy_to_caller += f"\n{spaces}    if (!isReadOnly(extensionType)) {{"
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
            current_member_access = formatter.generate_member_access(self, it, prefix="args.")
            current_member_count_name = current_member_name + "Count"
            current_member_count_access = formatter.generate_member_count_access(self, it, prefix="args.")
            current_member_element_type = self.member.kind_details.element.type.str
            parent_name = formatter.get_full_parent_name(self)

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
            else :
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

                copy_from_caller += f"\n{spaces}    {list_element_name} = getNext({list_element_name});"
                copy_from_caller += f"\n{spaces}}}\n"


            # Multi-dimensional array member
            if self.member.kind_details.element.kind.is_pointer_to_array() or self.member.kind_details.element.kind.is_opaque():
                copy_from_caller += f"\n\n{spaces}auto* {current_member_name}Traits = reinterpret_cast<DynamicStructTraits<{current_member_element_type}>*>(dynMem + {current_offset_var});"
                copy_from_caller += f"\n{spaces}{current_offset_var} += alignUpPow2<8>({current_member_count_name} * sizeof(DynamicStructTraits<{current_member_element_type}>));\n"

                next_it = str(chr(ord(it) + 1))
                copy_from_caller += f"\n{spaces}for(int32_t {next_it} = 0; {next_it} < {current_member_count_name}; ++{next_it}){{\n"
                copy_from_caller += self.create_nested_array_member_copy_from_caller(
                    self.member.kind_details.element.kind_details.element, current_member_name, current_offset_var, formatter, spaces_count + 4, next_it)
                copy_from_caller += f"\n{spaces}}}\n"

            if self.children:
                copy_from_caller += f"\n\n{spaces}auto* {current_member_name}Traits = reinterpret_cast<DynamicStructTraits<{current_member_element_type}>*>(dynMem + {current_offset_var});"
                copy_from_caller += f"\n{spaces}{current_offset_var} += alignUpPow2<8>({current_member_count_name} * sizeof(DynamicStructTraits<{current_member_element_type}>));\n"
                next_it = str(chr(ord(it) + 1))

                for child in self.children:
                    copy_from_caller += f"\n{spaces}for(int32_t {next_it} = 0; {next_it} < {current_member_count_name}; ++{next_it}){{\n"
                    copy_from_caller += child.create_copy_from_caller(current_offset_var, formatter, spaces_count + 4, next_it)
                    copy_from_caller += f"\n{spaces}}}\n"

            return copy_from_caller

        def create_nested_array_member_copy_from_caller(self, element, parent_name, current_offset_var, formatter, spaces_count, it):
            # In case of requirement for dynamic size, a correct way of getting size needs to be implemented here.
            assert element.kind.is_opaque() or element.kind_details.num_elements.is_constant()

            spaces = " " * spaces_count
            real_type = element.type.str if not element.kind.is_opaque() else element.kind_details.underlying_type.type.str
            real_count = element.kind_details.num_elements.get_constant() if not element.kind.is_opaque() else "1"

            parent_traits = f"{parent_name}Traits"
            current_element_name = f"{parent_name}_{it}"
            current_element_access = f"{parent_name}[{it}]"
            current_element_count_name = f"{current_element_name}Count"

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

            if element.kind_details.element.kind.is_pointer_to_array() or element.kind_details.element.kind.is_opaque():
                copy_from_caller += f"\n\n{spaces}auto* {current_element_name}Traits = reinterpret_cast<DynamicStructTraits<{real_type}>*>(dynMem + {current_offset_var});"
                copy_from_caller += f"\n{spaces}{current_offset_var} += alignUpPow2<8>({current_element_count_name} * sizeof(DynamicStructTraits<{real_type}>));\n"

                next_it = str(chr(ord(it) + 1))
                copy_from_caller += f"\n{spaces}for(int32_t {next_it} = 0; {next_it} < {current_element_count_name}; ++{next_it}){{\n"
                copy_from_caller += self.create_nested_array_member_copy_from_caller(
                    element.kind_details.element.kind_details.element, current_element_name, current_offset_var, formatter, spaces_count + 4, next_it)
                copy_from_caller += f"\n{spaces}}}\n"

            return copy_from_caller

        def create_reassemble_nested_structs(self, current_offset_var, formatter, spaces_count, it):
            spaces = " " * spaces_count
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

                reassemble_nested_structs += f"\n\n{spaces}forcePointerWrite({current_dest_access}, dynMem + {list_element_name}Traits[0].extensionOffset);"
                reassemble_nested_structs += f"\n{spaces}{current_offset_var} += alignUpPow2<8>(getUnderlyingSize(static_cast<const {iterator_type}*>({current_dest_access})));"

                reassemble_nested_structs += f"\n\n{spaces}auto {list_element_name} = static_cast<const {iterator_type}*>({current_dest_access});"

                reassemble_nested_structs += f"\n{spaces}for(int32_t {next_it} = 1; {next_it} < {current_member_count}; ++{next_it}){{"
                reassemble_nested_structs += f"\n{spaces}    const auto extensionOffset = {list_element_name}Traits[{next_it}].extensionOffset;"
                reassemble_nested_structs += f"\n{spaces}    forcePointerWrite(getNextField(*{list_element_name}), dynMem + extensionOffset);\n"

                reassemble_nested_structs += f"\n{spaces}    const auto pNextElement = getNext({list_element_name});"
                reassemble_nested_structs += f"\n{spaces}    const auto sizeInBytes = getUnderlyingSize(pNextElement);"
                reassemble_nested_structs += f"\n{spaces}    {current_offset_var} += alignUpPow2<8>(sizeInBytes);\n"

                reassemble_nested_structs += f"\n{spaces}    {list_element_name} = pNextElement;"
                reassemble_nested_structs += f"\n{spaces}}}\n"

            # Multi-dimensional array member
            if self.member.kind_details.element.kind.is_pointer_to_array() or self.member.kind_details.element.kind.is_opaque():
                reassemble_nested_structs += f"\n\n{spaces}auto* {current_member_name}Traits = reinterpret_cast<DynamicStructTraits<{current_member_element_type}>*>(dynMem + {current_offset_var});"
                reassemble_nested_structs += f"\n{spaces}{current_offset_var} += alignUpPow2<8>({current_member_count} * sizeof(DynamicStructTraits<{current_member_element_type}>));\n"

                next_it = str(chr(ord(it) + 1))
                reassemble_nested_structs += f"\n{spaces}for(int32_t {next_it} = 0; {next_it} < {current_member_count}; ++{next_it}){{\n"
                reassemble_nested_structs += self.create_nested_array_member_reassemble_structs(
                    self.member.kind_details.element.kind_details.element,
                    current_member_name,
                    current_dest_access,
                    current_offset_var,
                    formatter,
                    spaces_count + 4,
                    next_it)
                reassemble_nested_structs += f"\n{spaces}}}\n"

            if self.children:
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
            # In case of requirement for dynamic size, a correct way of getting size needs to be implemented here.
            assert element.kind.is_opaque() or element.kind_details.num_elements.is_constant()

            spaces = " " * spaces_count
            real_type = element.type.str if not element.kind.is_opaque() else element.kind_details.underlying_type.type.str

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

            if element.kind_details.element.kind.is_pointer_to_array() or element.kind_details.element.kind.is_opaque():
                reassemble_nested_structs += f"\n\n{spaces}auto* {current_element_name}Traits = reinterpret_cast<DynamicStructTraits<{real_type}>*>(dynMem + {current_offset_var});"
                reassemble_nested_structs += f"\n{spaces}{current_offset_var} += alignUpPow2<8>({current_element_count} * sizeof(DynamicStructTraits<{real_type}>));\n"

                next_it = str(chr(ord(it) + 1))
                reassemble_nested_structs += f"\n{spaces}for(int32_t {next_it} = 0; {next_it} < {current_element_count}; ++{next_it}){{\n"
                reassemble_nested_structs += self.create_nested_array_member_reassemble_structs(
                    element.kind_details.element.kind_details.element,
                    current_element_name,
                    current_dest_access,
                    current_offset_var,
                    formatter,
                    spaces_count + 4,
                    next_it)
                reassemble_nested_structs += f"\n{spaces}}}\n"

            return reassemble_nested_structs

    def __init__(self, structures, function):
        self.structures = structures
        self.function = function
        self.fixed_ptr_array_args_layouts = []
        self.dynamic_ptr_array_args_layouts = []
        self.struct_members_layouts = {}

        for arg in function.traits.get_ptr_array_args():
            if arg.traits.uses_standalone_allocation:
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
            if arg.traits.uses_standalone_allocation:
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
        

    def prepare_nested_member_layouts(self, parent, parent_layout, member):
        member_layout = FunctionCaptureLayout.MemberCaptureLayout()
        member_layout.member = member
        member_layout.parent = parent
        member_layout.parent_layout = parent_layout

        if not (member.kind_details.element.kind.is_struct() and member.kind_details.element.type.str in self.structures):
            return member_layout

        struct_type = self.structures[member.kind_details.element.type.str]
        members_to_capture = struct_type.members_to_capture()
        member_layout.children = [
            self.prepare_nested_member_layouts(
                member,
                member_layout,
                member_to_capture) for member_to_capture in members_to_capture]

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

        return Template(template).render(cl=self,
                                         inline_dyn_array_args=self.function.traits.get_inline_dyn_ptr_array_args(),
                                         fixed_array_args=self.function.traits.get_fixed_ptr_array_args(),
                                         dyn_offset_args=[arg_layout.arg for arg_layout in self.dynamic_offsets_args_layouts],
                                         dyn_count_args=[arg_layout.arg for arg_layout in self.dynamic_counts_args_layouts],
                                         nested_args=[arg_layout.arg for arg_layout in self.nested_capture_args_layouts],
                                         member_layout_formatter=MemberLayoutFormatter(),
                                         emit_copy_assignment=emit_copy_assignment,
                                         **vars(self), **Formater.get_all_formaters())

    def generate_cpp(self):
        with open("captures.cpp.mako", "r", encoding="utf-8") as f:
            template = f.read()

        return Template(template).render(cl=self,
                                         inline_dyn_array_args=self.function.traits.get_inline_dyn_ptr_array_args(),
                                         fixed_array_args=self.function.traits.get_fixed_ptr_array_args(),
                                         dyn_offset_args=[arg_layout.arg for arg_layout in self.dynamic_offsets_args_layouts],
                                         dyn_count_args=[arg_layout.arg for arg_layout in self.dynamic_counts_args_layouts],
                                         nested_args=[arg_layout.arg for arg_layout in self.nested_capture_args_layouts],
                                         member_layout_formatter=MemberLayoutFormatter(),
                                         **vars(self), **Formater.get_all_formaters())


class Function:
    def __init__(self, structures, src: dict):
        self.structures = structures
        self.name = src["name"]
        self.latency = float(src.get("latency", 0.0))
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
        self.message_name = f"{self.name[0].upper()}{self.name[1:]}RpcM"
        self.aliased_function = None
        self.traits = FunctionTraits(self)
        for arg in self.args:
            arg.create_traits(self)
        for iarg in self.implicit_args:
            iarg.create_traits(self)
        self.capture_layout = FunctionCaptureLayout(structures, self)

    def get_args_list_str(self) -> str:
        return ", ".join(arg.to_str() for arg in self.args)

    def get_call_params_list_str(self) -> str:
        return ", ".join([f"{arg.name}" for arg in self.args])


class MemberLayoutFormatter:
    def __init__(self):
        pass

    def generate_member_access(self, member_layout, it, prefix=""):
        # Only nested members have parent_layout. Args do not have it.
        if not member_layout.parent_layout:
            return f"{prefix}{member_layout.parent.name}[{it}].{member_layout.member.name}"
        else:
            parent_it = str(chr(ord(it) - 1))
            return f"{self.generate_member_access(member_layout.parent_layout, parent_it, prefix)}[{it}].{member_layout.member.name}"

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
            to_strip = member_access.rfind(f".{member_layout.member.name}")
            return member_access[:to_strip] + f".{member_layout.member.kind_details.num_elements.str}"

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
        # Only nested members have parent_layout.
        if not member_layout.parent_layout:
            return f"{member_layout.parent.name}{self.capital(member_layout.member.name)}"
        else:
            return f"{self.get_full_member_name(member_layout.parent_layout)}{self.capital(member_layout.member.name)}"

    def capital(self, name):
        return f"{name[0].upper() + name[1:]}"

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
    return anycase.replace("_", " ").title().replace(" ", "")


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


class Config:
    def __init__(self, src: dict):
        self.api_name = src["api_name"]
        self.loader_lib_names = src["loader_lib_names"]

        self.structures = [Structure(s) for s in src.get("structures", [])]
        self.structures_by_name = {struct.name: struct for struct in self.structures}
        for s in self.structures:
            s.set_all_structures_description(self.structures_by_name)

        self.functions = [Function(self.structures_by_name, f) for f in src.get("functions", [])]
        self.unimplemented = src.get("unimplemented", [])
        self.functions_by_name = {func.name: func for func in self.functions}
        self.icd_namespace = src.get("icd_namespace", "").split("::")
        self.icd_dispatch_table_type = src.get("icd_dispatch_table_type", "DispatchTableT")
        self.icd_init_dispatch_table_func_name_format = src.get("icd_init_dispatch_table_func_name_format", "initIcdDispatchTable")
        self.icd_get_extenion_func_addr_func_name = src.get("icd_get_extenion_func_addr_func_name", None)
        self.icd_acquire_global_object = src.get("icd_acquire_global_object", "")
        self.icd_acquire_channel = src.get("icd_acquire_channel", "")
        self.rpc_namespace = src.get("rpc_namespace", "").split("::")
        self.daemon_namespace = src.get("daemon_namespace", "").split("::")
        self.file_headers = FileHeaders(src.get("file_headers", {}))
        self.ddi_format_regexp0 = FormatRegexp(src.get("ddi_format_regexp0", None))
        self.ddi_format_regexp1_category = FormatRegexp(src.get("ddi_format_regexp1_category", None))
        self.result_type = src.get("result_type", "int")
        self.result_success = src.get("result_success", 0)
        for f in self.functions:
            if not (f.special_handling and f.special_handling.icd and f.special_handling.icd.alias_to):
                continue
            f.aliased_function = self.functions_by_name[f.special_handling.icd.alias_to]

        for func_category in self.unimplemented:
            assert not any(f for f in self.functions if f.name in func_category["members"])

    def get_extensions(self, include_variants=False):
        return [f for f in self.functions if f.traits.is_extension and not f.special_handling.is_variant()]


def load(fname: str) -> Config:
    with open(fname, "r", encoding="utf-8") as f:
        doc = yaml.load(f, Loader=yaml.Loader)
    return Config(doc["config"])


def generate_rpc_messages_h(config: Config, additional_file_headers: list) -> str:
    def should_skip_message_generation(func):
        return func.special_handling and func.special_handling.rpc and func.special_handling.rpc.dont_generate_rpc_message
    functions_with_messages = [f for f in config.functions if not should_skip_message_generation(f)]

    def get_message_subtype(func):
        return functions_with_messages.index(func)

    def get_copy_from_or_to_caller_args(func, const_iargs):
        return (["const Captures::DynamicTraits &dynMemTraits"] if func.traits.uses_inline_dynamic_mem else []) + \
            ([f"{'const ' if const_iargs else ''}ImplicitArgs &implicitArgs"] if func.implicit_args else [])

    def get_ptr_array_args(func):
        return func.traits.get_ptr_array_args()

    def get_struct_members_layouts(func):
        return func.capture_layout.struct_members_layouts

    with open("rpc_messages.h.mako", "r", encoding="utf-8") as f:
        template = f.read()
    return Template(template).render(
        config=config,
        unimplemented=config.unimplemented,
        daemon_namespace=config.daemon_namespace,
        rpc_namespace=config.rpc_namespace,
        rpc_functions=[
            f for f in config.functions if not (
                f.special_handling and f.special_handling.rpc and f.special_handling.rpc.dont_generate_rpc_message)],
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


def generate_rpc_messages_cpp(config: Config, additional_file_headers: list) -> str:
    def should_skip_message_generation(func):
        return func.special_handling and func.special_handling.rpc and func.special_handling.rpc.dont_generate_rpc_message

    with open("rpc_messages.cpp.mako", "r", encoding="utf-8") as f:
        template = f.read()
    return Template(template).render(
        config=config,
        rpc_namespace=config.rpc_namespace,
        file_headers=config.file_headers.common +
        config.file_headers.rpc_messages_cpp +
        additional_file_headers,
        should_skip_message_generation=should_skip_message_generation)


def generate_stub_lib_cpp(config: Config) -> str:
    with open("stub_lib.cpp.mako", "r", encoding="utf-8") as f:
        template = f.read()

    def get_func_handler_args_list_str(f):
        return ", ".join([f"{sarg}" for sarg in [arg.to_str() for arg in f.args]])

    return Template(template).render(config=config, functions=config.functions,
                                     file_headers=config.file_headers.api,
                                     get_func_handler_args_list_str=get_func_handler_args_list_str)


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
        return [f"{get_fq_message_name(f)}::ImplicitArgs &implArgsFor{f.message_name}"] if f.implicit_args else []

    def get_func_handler_args_list_str(f):
        return ", ".join([f"{sarg}" for sarg in [arg.to_str() for arg in f.args] + get_implicit_arg(f)])
    functions_in_dispatch_table = [f for f in config.functions if not (
        f.special_handling and f.special_handling.icd and f.special_handling.icd.not_in_dispatch_table)]

    def get_func_ddi_name_bind(f):
        return get_func_ddi_name(config, f)

    def get_ddi_name_bind(f):
        return get_ddi_name(config, f)

    with open("icd.h.mako", "r", encoding="utf-8") as f:
        template = f.read()

    return Template(template).render(
        config=config,
        file_headers=config.file_headers.common +
        config.file_headers.icd_h +
        additional_file_headers,
        icd_namespace=config.icd_namespace,
        icd_namespace_str='::'.join(
            config.icd_namespace),
        functions=config.functions,
        functions_in_dispatch_table=functions_in_dispatch_table,
        get_func_handler_name=get_func_handler_name,
        get_func_handler_args_list_str=get_func_handler_args_list_str,
        get_func_ddi_name=get_func_ddi_name_bind,
        get_ddi_name=get_ddi_name_bind)


def generate_icd_cpp(config: Config, additional_file_headers: list) -> str:
    def get_func_handler_suffix(f):
        return f.special_handling.icd.handler_only_suffix if (
            f.special_handling and f.special_handling.icd) else ""

    def get_func_handler_name(f):
        return f.name + get_func_handler_suffix(f)

    def get_fq_message_name(f):
        return '::'.join(config.rpc_namespace + [f.message_name])

    def get_implicit_arg(f):
        return [f"{get_fq_message_name(f)}::ImplicitArgs &implArgsFor{f.message_name}"] if f.implicit_args else []

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
    functions_in_dispatch_table = [f for f in config.functions if not (
        f.special_handling and f.special_handling.icd and f.special_handling.icd.not_in_dispatch_table)]
    non_variant_functions = [f for f in config.functions if not (f.special_handling and f.special_handling.is_variant())]

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
    icd_extensions = [f for f in config.functions if f.special_handling and f.special_handling.icd and f.special_handling and f.special_handling.icd.in_get_extension_function_address and not f.special_handling.is_variant()]

    def can_be_null(arg):
        return arg.kind_details and arg.kind_details.can_be_null
    with open("icd.cpp.mako", "r", encoding="utf-8") as f:
        template = f.read()

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
        prologue=lambda f: f.special_handling.icd.handler_prologue if (
            f.special_handling and f.special_handling.icd and f.special_handling.icd.handler_prologue) else "",
        epilogue=lambda f: f.special_handling.icd.handler_epilogue if (
            f.special_handling and f.special_handling.icd and f.special_handling.icd.handler_epilogue) else "")


def generate_service_h(config: Config, additional_file_headers: list) -> str:
    with open("service.h.mako", "r", encoding="utf-8") as f:
        template = f.read()
    rpc_extensions = [
        ext for ext in config.get_extensions() if not (
            ext.aliased_function or (
                ext.special_handling and ext.special_handling.rpc and (
                    ext.special_handling.rpc.dont_generate_rpc_message or ext.special_handling.rpc.dont_generate_rpc_handler)))]
    rpc_functions = [
        f for f in config.functions if not (
            f.aliased_function or (
                f.special_handling and f.special_handling.rpc and (
                    f.special_handling.rpc.dont_generate_rpc_message or f.special_handling.rpc.dont_generate_rpc_handler)))]
    standard_functions = [f for f in config.functions if not (f.aliased_function or f.traits.is_extension or f.traits.is_variant)]

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
        if arg.kind.is_pointer_to_array() and not arg.traits.uses_standalone_allocation:
            if arg.kind_details.num_elements.is_constant() or not rpc_func.traits.uses_dynamic_arg_getters:
                captured_arg = f"{'&' if (arg.kind_details.num_elements.get_constant() == 1) else ''}apiCommand->captures.{arg.name}"
            else:
                captured_arg = f"apiCommand->captures.get{arg.name[0].upper() + arg.name[1:]}()"
            if arg.traits.uses_nested_capture:
                captured_arg += ".data()"
            return f"apiCommand->args.{arg.name} ? {captured_arg} : nullptr"
        else:
            return f"apiCommand->args.{arg.name}"

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
        get_struct_members_layouts=get_struct_members_layouts)


def generate_service_cpp(config: Config, additional_file_headers: list) -> str:
    with open("service.cpp.mako", "r", encoding="utf-8") as f:
        template = f.read()
    rpc_extensions = [
        ext for ext in config.get_extensions() if not (
            ext.aliased_function or (
                ext.special_handling and ext.special_handling.rpc and (
                    ext.special_handling.rpc.dont_generate_rpc_message or ext.special_handling.rpc.dont_generate_rpc_handler)))]
    standard_functions = [f for f in config.functions if not (f.aliased_function or f.traits.is_extension or f.traits.is_variant)]
    return Template(template).render(config=config, extensions=rpc_extensions, standard_functions=standard_functions,
                                     file_headers=config.file_headers.common + config.file_headers.daemon_cpp + additional_file_headers,
                                     daemon_namespace=config.daemon_namespace, daemon_namespace_str='::'.join(config.daemon_namespace),
                                     ext_loader='::'.join(config.daemon_namespace + ['getExtensionFuncAddress']),
                                     to_pascal_case=to_pascal_case)


def generate_shared_h(config: Config, additional_file_headers: list) -> str:
    with open("shared.h.mako", "r", encoding="utf-8") as f:
        template = f.read()
    return Template(template).render(config=config, unimplemented=config.unimplemented,
                                     file_headers=config.file_headers.common + config.file_headers.shared_h + additional_file_headers,
                                     daemon_namespace=config.daemon_namespace)


def process_license(raw_text: str) -> str:
    output = "/*\n"
    output += "".join([" *" + (" " + line if line != "" else "") + "\n" for line in raw_text.splitlines()])
    output += " *\n"
    output += " */\n\n"

    return output


def dump(data: str, fname: str) -> None:
    print(f"Writing {fname}")
    with open("../../LICENSE.md", "r", encoding="utf-8") as f:
        cal_license = process_license(f.read())
    with open(fname, "wb") as f:
        contents = cal_license
        contents += "#pragma once\n" if fname.endswith((".h", ".hpp")) else ""
        contents += data
        f.write(contents.encode("utf-8"))


def generate(config: Config, out_dir: str) -> str:
    fname_base = "generated"
    fpath_base = os.path.join(out_dir, fname_base)

    icd_h = generate_icd_h(config, [f"#include \"{fname_base}_rpc_messages_{config.api_name}.h\""])
    dump(icd_h, fpath_base + f"_icd_{config.api_name}.h")

    icd_cpp = generate_icd_cpp(config, [f"#include \"{fname_base}_icd_{config.api_name}.h\"",
                                        f"#include \"{fname_base}_rpc_messages_{config.api_name}.h\""])
    dump(icd_cpp, fpath_base + f"_icd_{config.api_name}.cpp")

    rpc_messages_h = generate_rpc_messages_h(config, [])
    dump(rpc_messages_h, fpath_base + f"_rpc_messages_{config.api_name}.h")

    rpc_messages_cpp = generate_rpc_messages_cpp(config, [f"#include \"{fname_base}_rpc_messages_{config.api_name}.h\""])
    dump(rpc_messages_cpp, fpath_base + f"_rpc_messages_{config.api_name}.cpp")

    service_h = generate_service_h(config, [f"#include \"{fname_base}_rpc_messages_{config.api_name}.h\""])
    dump(service_h, fpath_base + f"_service_{config.api_name}.h")

    service_cpp = generate_service_cpp(config, [f"#include \"{fname_base}_service_{config.api_name}.h\""])
    dump(service_cpp, fpath_base + f"_service_{config.api_name}.cpp")

    shared_h = generate_shared_h(config, [])
    dump(shared_h, fpath_base + f"_shared_{config.api_name}.h")

    stub_lib_cpp = generate_stub_lib_cpp(config)
    dump(stub_lib_cpp, fpath_base + f"_stub_lib_{config.api_name}.cpp")


def main():
    path = "../cached/"

    if len(sys.argv) > 1:
        path = sys.argv[1]
    
    print(f"output directory : {path}")
    config = load("ocl.yml")
    generate(config, path)
    config = load("level_zero.yml")
    generate(config, path)


if __name__ == "__main__":
    main()
