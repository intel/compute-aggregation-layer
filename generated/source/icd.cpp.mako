##
## Copyright (C) 2022 Intel Corporation
##
## SPDX-License-Identifier: MIT
##
// #### Generated code -- begin ####
#include "icd/icd_global_state.h"
#include "shared/rpc.h"
% for header in file_headers:
${header}
% endfor

#include <cstdlib>
#include <type_traits>

% for namespace_part in icd_namespace:
namespace ${namespace_part} {
% endfor # icd_namespace
template<typename T>
auto mutable_element_cast(const T *el) {
    auto nonConst = const_cast<T*>(el);
    using NonVoidT = std::conditional_t<std::is_void_v<T>, char*, T*>;
    return reinterpret_cast<NonVoidT>(nonConst);
};

template<typename T>
auto mutable_element_cast(const T **el) {
    auto nonConst = const_cast<T**>(el);
    using NonVoidT = std::conditional_t<std::is_void_v<T>, char**, T**>;
    return reinterpret_cast<NonVoidT>(nonConst);
};

% for f in functions:
%  if dont_generate_handler(f):
 // ${f.name} ignored in generator - based on dont_generate_handler flag
%  else : # not dont_generate_handler(f)
<%  func_base = f if not f.aliased_function else f.aliased_function%>\
${func_base.returns.type.str} ${get_func_handler_name(f)} (${get_func_handler_args_list_str(func_base)}) {
%   if itentionally_ignore(f):
    log<Verbosity::info>("Intentionally ignoring ${f.name}");
%   if not func_base.returns.type.is_void():
    return ${func_base.returns.default};
%   endif # not func_base.returns.type.is_void():
}
%   else : # not itentionally_ignore(f)
%    for prologue_line in prologue(f):
    ${prologue_line}
%    endfor # prologue(f)
    log<Verbosity::bloat>("Establishing RPC for ${f.name}");
%    if f != func_base:
    ${"return " if not func_base.returns.type.is_void() else ""}${'::'.join(config.icd_namespace + [func_base.name])}(${func_base.get_call_params_list_str()});
}
%    else : # f == func_base
    ${config.icd_acquire_global_object}
    auto &channel = ${config.icd_acquire_channel};
    auto channelLock = channel.lock();
    using CommandT = ${get_fq_message_name(func_base)};
%     if func_base.capture_layout.emit_dynamic_traits:
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(${func_base.get_call_params_list_str()});
    auto space = channel.getSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(space.hostAccessible) CommandT(dynMemTraits, ${func_base.get_call_params_list_str()});
%     else : # not func_base.capture_layout.emit_dynamic_traits
    auto space = channel.getSpace<CommandT>(0);
    auto command = new(space.hostAccessible) CommandT(${func_base.get_call_params_list_str()});
%     endif # not func_base.capture_layout.emit_dynamic_traits
%     if func_base.traits.emit_copy_from_caller:
    command->copyFromCaller(${get_copy_from_caller_call_params_list_str(func_base)});
%     endif # func_base.traits.emit_copy_from_caller:
%     for arg in get_args_requiring_translation_before(func_base):
%       if can_be_null(arg):
    if(${arg.name})
%       endif # arg.kind_details.can_be_null
%      if arg.kind.is_pointer_to_array() and arg.kind_details.element.translate_before:
    {
        auto base = command->captures.${get_arg_from_capture(arg)};
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.${arg.name}.count;

        for(size_t i = 0; i < numEntries; ++i){
            ${arg.kind_details.element.translate_before.format(f"baseMutable[i]", "baseMutable[i]", "i")};
        }
    }
%      endif # arg.kind.is_pointer_to_array() and arg.kind_details.element.translate_before:
%      if arg.translate_before:
%       if can_be_null(arg):
    {
        ${arg.translate_before.format(f"command->args.{arg.name}", arg.name, index="", dst_mem=f"command->captures.{get_arg_from_capture(arg)}")};
    }
%       else : # can_be_null
    ${arg.translate_before.format(f"command->args.{arg.name}", arg.name, index="", dst_mem=f"command->captures.{get_arg_from_capture(arg)}")};
%       endif # can_be_null
%      endif # translate_before
%     endfor # get_args_requiring_translation_before(func_base)
%     if is_unsupported(f):
    return${"" if func_base.returns.type.is_void() else " command->returnValue()"};
%     else : # not is_unsupported(f)
    if(false == channel.callSynchronous(space)){
        return${"" if func_base.returns.type.is_void() else " command->returnValue()"};
    }
%      if func_base.traits.emit_copy_to_caller:
    command->copyToCaller(${get_copy_to_caller_call_params_list_str(func_base)});
%      endif # func_base.traits.emit_copy_to_caller
%      for arg in get_args_requiring_translation_after(func_base):
%       if can_be_null(arg):
    if(${arg.name})
%       endif # arg.kind_details.can_be_null
    {
%       if arg.kind.is_pointer_to_array() and arg.kind_details.element.translate_after: # translate each element
%        if arg.kind_details.num_elements.is_single_element():
        ${arg.kind_details.element.translate_after.format(f"{arg.name}[0]", f"{arg.name}[0]", "")};
%        else : # not arg.kind_details.num_elements.is_single_element()
        auto baseMutable = mutable_element_cast(${arg.name});

%        if arg.kind_details.is_num_elements_ptr_to_capturable_arg:
        auto numEntries = command->captures.${arg.kind_details.num_elements.str};
%        else:
        auto numEntries = ${arg.get_calculated_elements_count()};
%        endif

        for(size_t i = 0; i < numEntries; ++i){
            ${arg.kind_details.element.translate_after.format("baseMutable[i]", f"baseMutable[i]", "i")};
        }
%        endif # not arg.kind_details.num_elements.is_single_element():
%       endif #  arg.kind.is_pointer_to_array() and arg.kind_details.element.translate_after:
%       if arg.translate_after: # translate as a whole
        ${arg.translate_after.format(arg.name, arg.name)};
%       endif # arg.translate_after
    }
%      endfor # get_args_requiring_translation_after(func_base):
%      if not func_base.returns.type.is_void():
    ${func_base.returns.type.str} ret = command->captures.ret;

%      if func_base.returns.translate_after:
    ${func_base.returns.translate_after.format("ret", "ret")};
%      endif # func_base.returns.translate_after
%      if epilogue(f):
    channelLock.unlock();
%      endif #epilogue(f)
%      for epilogue_line in epilogue(f):
    ${epilogue_line}
%      endfor # epilogue(f)
    return ret;
%      endif # not func_base.returns.type.is_void():
%     endif # not is_unsupported(f)
}
%    endif # func_base == func_base
%   endif # not itentionally_ignore(f)
%  endif # not dont_generate_handler(f)
% endfor # functions

% if config.icd_get_extenion_func_addr_func_name:
void *${config.icd_get_extenion_func_addr_func_name}(const char *funcName) {
% for ext_func in icd_extensions:
    if(0 == strcmp("${ext_func.name}", funcName)) {
        return reinterpret_cast<void*>(${'::'.join(config.icd_namespace + [ext_func.name])});
    }
% endfor # icd_extensions
    return nullptr;
}
% endif # config.icd_get_extenion_func_addr_func_name

% for namespace_part in reversed(icd_namespace):
} // namespace ${namespace_part}
% endfor


extern "C" {
% for f in non_variant_functions:
<% func_base = f if not f.aliased_function else f.aliased_function%>\
${func_base.returns.type.str} ${f.name} (${func_base.get_args_list_str()}) {
    return ${'::'.join(config.icd_namespace + [f.name])}(${func_base.get_call_params_list_str()});
}
% endfor # non_variant_functions
} // extern "C"


// #### Generated code -- end ####