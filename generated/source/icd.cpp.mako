##
## Copyright (C) 2022-2023 Intel Corporation
##
## SPDX-License-Identifier: MIT
##
// #### Generated code -- begin ####

#include "icd/icd_global_state.h"
#include "shared/rpc.h"
#include "shared/utils.h"

% for header in file_headers:
${header}
% endfor

#include <cstdlib>
#include <type_traits>

using Cal::Utils::enforceNullWithWarning;
using Cal::Utils::ensureNull;

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

% for group_name in functions:
%  for f in functions[group_name]:
%   if dont_generate_handler(f):
 // ${f.name} ignored in generator - based on dont_generate_handler flag
%   else : # not dont_generate_handler(f)
<%  func_base = f if not f.aliased_function else f.aliased_function%>\
${func_base.returns.type.str} ${get_func_handler_name(f)} (${get_func_handler_args_list_str(func_base)}) {
%    if itentionally_ignore(f):
    log<Verbosity::info>("Intentionally ignoring ${f.name}");
%     if not func_base.returns.type.is_void():
    return ${func_base.returns.default};
%     endif # not func_base.returns.type.is_void():
}
%    elif func_base.redirections: # not itentionally_ignore(f)
    ${config.icd_acquire_global_object};
<%    evals = set()%>\
%     for r in func_base.redirections:
%      for c in r.conditions:
%       if c.evauluate not in evals:
    ${c.evauluate};
<%       evals.add(c.evauluate)%>\
%       endif #c.evauluate not in evals:
%      endfor # r.conditions
%     endfor # func_base.redirections:
    
%     for r in func_base.redirections:
%      if not loop.last:
%       if loop.first:
    if(\
%       else: # loop.first
    else if(\
%       endif
%       for c in r.conditions:
%        if not loop.first:
 && \
%        endif # not loop.first:
(${c.check})\
%       endfor # r.conditions
)\
%      elif not loop.first:
    else\
%      else: # not loop.last
    
%      endif # not loop.last
{
%     if not func_base.returns.type.is_void():
        return \
%     else: # not func_base.returns.type.is_void():
         \
%     endif # not func_base.returns.type.is_void():
${r.destination.name}(${func_base.get_call_params_list_str()});
    }
%     endfor # func_base.redirections:
}
%    else : # not func_base.redirections
%     for prologue_line in prologue(f):
    ${prologue_line}
%     endfor # prologue(f)
    log<Verbosity::bloat>("Establishing RPC for ${f.name}");
%     if f != func_base:
    ${"return " if not func_base.returns.type.is_void() else ""}${'::'.join(config.icd_namespace + [func_base.name])}(${func_base.get_call_params_list_str()});
}
%     else : # f == func_base
    ${config.icd_acquire_global_object};
    auto &channel = ${config.icd_acquire_channel};
    auto channelLock = channel.lock();
    using CommandT = ${get_fq_message_name(func_base)};
%      if func_base.capture_layout.emit_dynamic_traits:
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(${func_base.get_call_params_list_str()});
    auto commandSpace = channel.getSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace.get()) CommandT(dynMemTraits, ${func_base.get_call_params_list_str()});
%      else : # not func_base.capture_layout.emit_dynamic_traits
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(${func_base.get_call_params_list_str()});
%      endif # not func_base.capture_layout.emit_dynamic_traits
%      for arg in func_base.traits.get_standalone_args():
    auto standaloneSpaceFor${arg.name} = channel.getSpace(${arg.get_calculated_array_size()});
%       if not arg.kind_details.server_access.write_only():
    memcpy(standaloneSpaceFor${arg.name}.get(), ${arg.name}, ${arg.get_calculated_array_size()});
%       endif # not arg.kind_details.server_access.write_only()
%      endfor # arg in func_base.traits.get_standalone_args()
%      if func_base.traits.emit_copy_from_caller:
    command->copyFromCaller(${get_copy_from_caller_call_params_list_str(func_base)});
%      endif # func_base.traits.emit_copy_from_caller:
%      for arg in func_base.traits.get_standalone_args():
    command->args.${arg.name} = channel.encodeHeapOffsetFromLocalPtr(standaloneSpaceFor${arg.name}.get());
%      endfor # arg in func_base.traits.get_standalone_args()
%      if func_base.traits.emit_reassemblation_in_icd:
    command->captures.reassembleNestedStructs();
%      endif # func_base.traits.emit_reassemblation_in_icd
%      for arg in get_args_requiring_translation_before(func_base):
%        if can_be_null(arg):
    if(${arg.name})
%        endif # arg.kind_details.can_be_null
%       if arg.kind.is_struct():
    {
%        for member in [m for m in config.structures_by_name[arg.type.str].members if m.translate_before]:
        ${member.translate_before.format(dst=f"command->args.{arg.name}.{member.name}",
                                         arg=f"{arg.name}.{member.name}",
                                         func_name=func_base.name,
                                         dst_captures=f"command->captures.{arg.name}.{member.name}")};
%        endfor # members
    }
%       endif # arg.kind.is_struct()
<%     sname = '' if not (arg.kind_details and arg.kind_details.element) else arg.kind_details.element.type.str %>\
%       if arg.kind.is_pointer_to_array() and sname in config.structures_by_name and config.structures_by_name[sname].traits.requires_translation_of_members_before():
    {
%         if arg.kind_details.num_elements.is_single_element():
%          for member in [m for m in config.structures_by_name[arg.kind_details.element.type.str].members if m.translate_before]:
        ${member.translate_before.format(dst=f"command->args.{arg.name}->{member.name}",
                                         arg=f"{arg.name}->{member.name}",
                                         func_name=func_base.name,
                                         dst_captures=f"command->captures.{arg.name}.{member.name}")};
%          endfor # members
%         else: # not arg.kind_details.num_elements.is_single_element()
        auto base = command->captures.${get_arg_from_capture(arg)};
        [[maybe_unused]] auto baseMutable = mutable_element_cast(base);
        auto numEntries = ${arg.get_calculated_elements_count()};

        for(size_t i = 0; i < numEntries; ++i){
%          for member in [m for m in config.structures_by_name[arg.kind_details.element.type.str].members if m.translate_before]:
            ${member.translate_before.format(f"command->args.{arg.name}[i].{member.name}",
                                             f"{arg.name}[i].{member.name}",
                                             func_name=func_base.name,
                                             dst_captures=f"baseMutable[i].{member.name}")};
        }
%          endfor # members
%         endif # arg.kind_details.num_elements.is_single_element():
    }
%       endif # arg.kind.is_pointer_to_array() and sname in config.structures_by_name and config.structures_by_name[sname].traits.requires_translation_of_members_before()
%       if arg.kind.is_pointer_to_array() and arg.kind_details.element.translate_before:
    {
        auto base = command->captures.${get_arg_from_capture(arg)};
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.${arg.name}.count;

        for(size_t i = 0; i < numEntries; ++i){
            ${arg.kind_details.element.translate_before.format(f"baseMutable[i]", "baseMutable[i]", "i")};
        }
    }
%       endif # arg.kind.is_pointer_to_array() and arg.kind_details.element.translate_before:
%       if arg.translate_before:
%        if can_be_null(arg):
    {
        ${arg.translate_before.format(f"command->args.{arg.name}", arg.name, index="", dst_mem=f"command->captures.{get_arg_from_capture(arg)}")};
    }
%        else : # can_be_null
    ${arg.translate_before.format(f"command->args.{arg.name}", arg.name, index="", dst_mem=f"command->captures.{get_arg_from_capture(arg)}")};
%        endif # can_be_null
%       endif # translate_before
%      endfor # get_args_requiring_translation_before(func_base)
%      if is_unsupported(f):
    return${"" if func_base.returns.type.is_void() else " command->returnValue()"};
%      else : # not is_unsupported(f)

%      if f.callAsync:
    if(
%      for arg in func_base.args:
%       if ("block" in arg.name) or (arg.kind_details and arg.kind_details.element and arg.kind_details.element.translate_after):
       !${arg.name} &&
%       endif
%      endfor
       channel.isCallAsyncEnabled()){
         channel.callAsynchronous(command, commandSpace);
%       if "queue" in func_base.name:
         command_queue->asLocalObject()->enqueue();
%       endif
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return${"" if func_base.returns.type.is_void() else " command->returnValue()"};
      }
    }
%      else:

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return${"" if func_base.returns.type.is_void() else " command->returnValue()"};
    }
%      endif
%       if func_base.traits.emit_copy_to_caller:
    command->copyToCaller(${get_copy_to_caller_call_params_list_str(func_base)});
%       endif # func_base.traits.emit_copy_to_caller
%       for arg in func_base.traits.get_standalone_args():
%        if not arg.kind_details.server_access.read_only():
    memcpy(${arg.name}, standaloneSpaceFor${arg.name}.get(), ${arg.get_calculated_array_size()});
%        endif # not arg.kind_details.server_access.write_only()
%       endfor # arg in func_base.traits.get_standalone_args():
%       for arg in get_args_requiring_translation_after(func_base):
%        if can_be_null(arg):
    if(${arg.name})
%        endif # arg.kind_details.can_be_null
    {
%        if arg.kind.is_pointer_to_array() and arg.kind_details.element.translate_after: # translate each element
%         if arg.kind_details.num_elements.is_single_element():
        ${arg.kind_details.element.translate_after.format(f"{arg.name}[0]", f"{arg.name}[0]", "")};
%         else : # not arg.kind_details.num_elements.is_single_element()
        auto baseMutable = mutable_element_cast(${arg.name});

%         if arg.kind_details.is_num_elements_ptr_to_capturable_arg:
        auto numEntries = command->captures.${arg.kind_details.num_elements.str};
%         else:
        auto numEntries = ${arg.get_calculated_elements_count()};
%         endif

        for(size_t i = 0; i < numEntries; ++i){
            ${arg.kind_details.element.translate_after.format("baseMutable[i]", f"baseMutable[i]", "i")};
        }
%         endif # not arg.kind_details.num_elements.is_single_element():
%        endif #  arg.kind.is_pointer_to_array() and arg.kind_details.element.translate_after:
%        if arg.translate_after: # translate as a whole
        ${arg.translate_after.format(arg.name, arg.name)};
%        endif # arg.translate_after
    }
%       endfor # get_args_requiring_translation_after(func_base):
%       if not func_base.returns.type.is_void():
    ${func_base.returns.type.str} ret = command->captures.ret;

%       if func_base.returns.translate_after:
    ${func_base.returns.translate_after.format("ret", "ret")};
%       endif # func_base.returns.translate_after
%       for arg in func_base.traits.get_standalone_args():
%        if not arg.capture_details.reclaim_method.is_immediate_mode():
    ${arg.capture_details.reclaim_method.format(f"standaloneSpaceFor{arg.name}")};
%        endif # not arg.capture_details.reclaim_method.is_immediate_mode()
%       endfor # arg in func_base.traits.get_standalone_args():
%       if epilogue_data(f):
%           for epilogue_data_line in epilogue_data(f):
    ${epilogue_data_line}
%           endfor # epilogue_data(f)
%       endif #epilogue_data(f)
%       if epilogue(f):
    commandSpace.reset();
    channelLock.unlock();
%       endif #epilogue(f)
%       for epilogue_line in epilogue(f):
    ${epilogue_line}
%       endfor # epilogue(f)
    return ret;
%       endif # not func_base.returns.type.is_void():
%      endif # not is_unsupported(f)
}
%     endif # func_base == func_base
%    endif # not itentionally_ignore(f)
%   endif # not dont_generate_handler(f)
%  endfor # functions[group_name]
% endfor # functions

% if config.icd_get_extenion_func_addr_func_name:
void *${config.icd_get_extenion_func_addr_func_name}(const char *funcName) {
% for group_name in icd_extensions:
% for ext_func in icd_extensions[group_name]:
    if(0 == strcmp("${ext_func.name}", funcName)) {
        return reinterpret_cast<void*>(${'::'.join(config.icd_namespace + [ext_func.name])});
    }
%  endfor # icd_extensions[group_name]
% endfor # icd_extensions
    return nullptr;
}
% endif # config.icd_get_extenion_func_addr_func_name

% for namespace_part in reversed(icd_namespace):
} // namespace ${namespace_part}
% endfor


extern "C" {
% for group_name in non_variant_functions:
%  for f in non_variant_functions[group_name]:
<% func_base = f if not f.aliased_function else f.aliased_function%>\
${func_base.returns.type.str} ${f.name} (${func_base.get_args_list_str()}) {
    return ${'::'.join(config.icd_namespace + [f.name])}(${func_base.get_call_params_list_str()});
}
%  endfor # non_variant_functions[group_name]
% endfor # non_variant_functions
} // extern "C"


// #### Generated code -- end ####
