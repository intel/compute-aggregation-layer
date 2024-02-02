##
## Copyright (C) 2022-2023 Intel Corporation
##
## SPDX-License-Identifier: MIT
##
// #### Generated code -- begin ####

#include "service/service.h"
#include "shared/rpc.h"
#include "shared/utils.h"

% for header in file_headers:
${header}
% endfor

#include <optional>
#include <string>
#include <type_traits>
#include <vector>

% for namespace_part in daemon_namespace:
namespace ${namespace_part} {
% endfor

namespace Standard {
% if not config.parent_config:
bool load${to_pascal_case(config.api_name)}Library(std::optional<std::string> path);
void unload${to_pascal_case(config.api_name)}Library();
bool is${to_pascal_case(config.api_name)}LibraryLoaded();
% endif # not config.parent_config

% for group_name in standard_functions:
%  for f in standard_functions[group_name]:
extern ${f.returns.type.str} (*${f.name})(${f.get_args_list_str()});
%  endfor # standard_functions[group_name]
% endfor # standard_functions
} // Standard

% if extensions:
namespace Extensions {
%  for group_name in extensions:
%   for ext in extensions[group_name]:
extern ${ext.returns.type.str} (*${ext.name})(${ext.get_args_list_str()});
%   endfor # extensions[group_name]
%  endfor # extensions
} // Extensions
% endif # extensions

% for group_name in rpc_functions:
%  for rpc_func in rpc_functions[group_name]:
\
%   if get_rpc_handler_suffix(rpc_func) or use_rpc_custom_handler(rpc_func):
bool ${rpc_func.name}Handler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
%   endif
%   if not (use_rpc_custom_handler(rpc_func) or should_skip_message_generation(rpc_func)):
inline bool ${rpc_func.name}Handler${get_rpc_handler_suffix(rpc_func)}(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for ${rpc_func.name}");
%     for prologue_line in prologue(rpc_func):
    ${prologue_line}
%     endfor # prologue(rpc_func)
    auto apiCommand = reinterpret_cast<${'::'.join(config.rpc_namespace + [rpc_func.message_name])}*>(command);
<%     op_end_marker_event_arg = None%>\
%      for arg in rpc_func.args:
%       if arg.kind.is_pointer_zero_copy_malloc_shmem():
<%       arg_size = f"apiCommand->captures.{arg.name}.size" if arg.traits.uses_inline_dynamic_mem else arg.get_calculated_array_size('apiCommand->args.', 'apiCommand->captures.')%>\
    void *importedMallocPtr${to_pascal_case(arg.name)} = ctx.importClientMallocPtr(reinterpret_cast<uintptr_t>(${get_arg_from_api_command_struct(rpc_func, arg)}), ${arg_size}, 0U);
    if((nullptr == importedMallocPtr${to_pascal_case(arg.name)})  && (nullptr != apiCommand->args.${arg.name})){
        log<Verbosity::error>("Could not import client's malloced pointer : %p (size : %zuB)", ${get_arg_from_api_command_struct(rpc_func, arg)}, ${arg_size});
        return false;
    }
%       elif arg.kind.is_pointer_remapped():
    void *remappedPtr${to_pascal_case(arg.name)} = ctx.remapPointer(service.getGlobalShmemAllocators().getNonUsmMmappedAllocator(), apiCommand->args.${arg.name}, ${arg.get_calculated_array_size('apiCommand->args.', 'apiCommand->captures.')});
    if((nullptr == remappedPtr${to_pascal_case(arg.name)}) && (nullptr != apiCommand->args.${arg.name})){
        log<Verbosity::error>("Could not import client's malloced pointer : %p (size : %zuB)", ${get_arg_from_api_command_struct(rpc_func, arg)}, ${arg.get_calculated_array_size('apiCommand->args.', 'apiCommand->captures.')});
        return false;
    }
%        if not arg.kind_details.server_access.read_only():
<%        op_end_marker_event_arg = rpc_func.traits.getOpEndEventArg()%>\
%        endif
%       elif arg.kind.is_pointer_va() and arg.traits.uses_staging_usm_allocation:
%        if not arg.kind_details.server_access.read_only() and config.api_name == "level_zero":
<%        op_end_marker_event_arg = rpc_func.traits.getOpEndEventArg()%>\
    ctx.getMemoryBlocksManager().registerUSMStaging(apiCommand->args.${arg.name}, ${arg.get_calculated_array_size('apiCommand->args.', 'apiCommand->captures.')});
%        endif
%       endif # arg.kind.is_pointer_va():
%      endfor # rpc_func.args
%      if op_end_marker_event_arg:
    auto opEndMarkerEvent = Cal::Service::Apis::${to_pascal_case(config.api_name)}::getInternalEvent(ctx, apiCommand->args.hCommandList);
    if (!opEndMarkerEvent) {
        apiCommand->captures.ret = ${rpc_func.returns.default};
        return false;
    }
%      endif #op_end_marker_event_arg
%      if get_struct_members_layouts(rpc_func):
    apiCommand->captures.reassembleNestedStructs();
%      endif
    apiCommand->captures.ret = ${get_rpc_func_fqfn(rpc_func)}(
%     for arg in rpc_func.args:
%      if arg.kind.is_pointer_zero_copy_malloc_shmem():
                                                reinterpret_cast<${arg.type.str}>(importedMallocPtr${to_pascal_case(arg.name)})\
%      elif arg.kind.is_pointer_remapped():
                                                remappedPtr${to_pascal_case(arg.name)}\
%      elif arg == op_end_marker_event_arg:
                                                opEndMarkerEvent\
%      else : # not arg.kind.is_pointer_zero_copy_malloc_shmem
%       if arg.traits.uses_standalone_allocation:
                                                channel.decodeLocalPtrFromHeapOffset(${get_arg_from_api_command_struct(rpc_func, arg)})\
%       else : # not arg.traits.uses_standalone_allocation       
                                                ${get_arg_from_api_command_struct(rpc_func, arg)}\
%       endif
%      endif
${", " if not loop.last else ""}
%     endfor # rpc_func.args
                                                );
%     if rpc_func.callAsync:
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to ${rpc_func.name} (as ${rpc_func.name}Handler${get_rpc_handler_suffix(rpc_func)}) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
%     endif # rpc_func.callAsync
%     if op_end_marker_event_arg:
    Cal::Service::Apis::${to_pascal_case(config.api_name)}::addRelay(apiCommand->captures.ret, ${get_arg_from_api_command_struct(rpc_func, op_end_marker_event_arg)}, opEndMarkerEvent, apiCommand->args.hCommandList);
    if (apiCommand->captures.ret == 0) {
        auto &copiesManager = ctx.getOngoingHostptrCopiesManager();
%      for arg in rpc_func.args:
%       if arg.kind.is_pointer_remapped() and (not arg.kind_details.server_access.read_only()):
        copiesManager.registerCopyOperation(apiCommand->args.hCommandList, opEndMarkerEvent, ${get_arg_from_api_command_struct(rpc_func, arg)}, ${arg.get_calculated_array_size('apiCommand->args.', 'apiCommand->captures.')}, ${str(arg.capture_details.replayable_command).lower()});
%       elif arg.kind.is_pointer_va() and arg.traits.uses_staging_usm_allocation:
%        if not arg.kind_details.server_access.read_only():
<%        op_end_marker_event_arg = rpc_func.traits.getOpEndEventArg()%>\
        copiesManager.registerCopyOperation(apiCommand->args.hCommandList, opEndMarkerEvent, ${get_arg_from_api_command_struct(rpc_func, arg)}, ${arg.get_calculated_array_size('apiCommand->args.', 'apiCommand->captures.')}, ${str(arg.capture_details.replayable_command).lower()});
%        endif
%       endif # arg.kind.is_pointer_va():
%      endfor
    }
%     endif # op_end_marker_event_arg
%     for arg in rpc_func.args:
%      if arg.daemon_action_on_success:
    if(isSuccessful(apiCommand->captures.ret)) {
        const auto& resource = ${get_arg_from_api_command_struct(rpc_func, arg)};
        if (resource) {
            ${arg.daemon_action_on_success.format("resource" if arg.kind.is_scalar() else "*resource")};
        }
    }
%      endif # arg.daemon_action_on_success
%      if arg.daemon_action_at_end:
    {
        const auto& resource = ${get_arg_from_api_command_struct(rpc_func, arg)};
        if (resource) {
            ${arg.daemon_action_at_end.format("resource" if arg.kind.is_scalar() else "*resource")};
        }
    }
%      endif # arg.daemon_action_at_end
%     endfor # rpc_func.args
%     for epilogue_line in epilogue(rpc_func):
    ${epilogue_line}
%     endfor # epilogue(rpc_func)
    return true;
}
%   endif # not (use_rpc_custom_handler or should_skip_message_generation)
%  endfor # rpc_functions[group_name]
% endfor # rpc_functions

inline void registerGeneratedHandlers${to_pascal_case(config.api_name)}${to_pascal_case(config.subconfig_name)}(Cal::Service::Provider::RpcSubtypeHandlers &outHandlers){
% if not rpc_functions:
// No RPC handlers were generated (based on dont_generate_rpc_message)
% else: # rpc_functions
    using namespace ${'::'.join(config.rpc_namespace)};
    if(outHandlers.size() < ${last_function_with_message.message_name}::messageSubtype + 1){
        outHandlers.resize(${last_function_with_message.message_name}::messageSubtype + 1);
    }
%  for group_name in rpc_functions:
%   for rpc_func in rpc_functions[group_name]:
%    if not should_skip_message_generation(rpc_func):
    outHandlers[${rpc_func.message_name}::messageSubtype] = ${rpc_func.name}Handler;
%    endif # not should_skip_message_generation(rpc_func)
%   endfor # rpc_functions[group_name]
%  endfor # rpc_functions
% endif # rpc_functions
}

% for group_name in rpc_functions:
%  for rpc_func in rpc_functions[group_name]:
\
%  if not (rpc_func.special_handling and rpc_func.special_handling.rpc and rpc_func.special_handling.rpc.dont_generate_call_directly):
%   if not should_skip_message_generation(rpc_func):
inline void callDirectly(${'::'.join(config.rpc_namespace + [rpc_func.message_name])} &apiCommand) {
%     if rpc_func.returns.type.is_void():
    ${get_rpc_func_fqfn(rpc_func)}(
%     else : # not rpc_func.returns.type.is_void()
    apiCommand.captures.ret = ${get_rpc_func_fqfn(rpc_func)}(
%     endif
%     for arg in rpc_func.args:
                                                apiCommand.args.${arg.name}\
${", " if not loop.last else ""}
%     endfor # rpc_func.args
                                                );
}
%   endif # not should_skip_message_generation(rpc_func)
%  endif
%  endfor # rpc_functions[group_name]
% endfor # rpc_functions

inline bool callDirectly${to_pascal_case(config.subconfig_name)}(Cal::Rpc::RpcMessageHeader *command) {
    if(nullptr == command){
        log<Verbosity::debug>("Tried to call directly with empty command message header");
        return false;
    }
    if(command->type != Cal::Rpc::RpcMessageHeader::messageTypeRpc${to_pascal_case(config.api_name)}){
        log<Verbosity::debug>("Tried to call directly %d message type as ${to_pascal_case(config.api_name)}", command->type);
        return false;
    }
    switch(command->subtype){
        default:
            log<Verbosity::debug>("Tried to call directly unknown message subtype %d", command->subtype);
            return false;
% for group_name in rpc_functions:
%  for rpc_func in rpc_functions[group_name]:
%    if not (rpc_func.special_handling and rpc_func.special_handling.rpc and rpc_func.special_handling.rpc.dont_generate_call_directly):
%     if not should_skip_message_generation(rpc_func):
        case ${'::'.join(config.rpc_namespace + [rpc_func.message_name])}::messageSubtype : callDirectly(*reinterpret_cast<${'::'.join(config.rpc_namespace + [rpc_func.message_name])}*>(command)); break;
%     endif # not should_skip_message_generation(rpc_func)
%   endif
%  endfor # rpc_functions[group_name]
% endfor # rpc_functions
    }
    return true;
}

% for namespace_part in reversed(daemon_namespace):
} // namespae ${namespace_part}
%endfor
// #### Generated code -- end ####
