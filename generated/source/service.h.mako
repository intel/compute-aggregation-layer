##
## Copyright (C) 2022 Intel Corporation
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
bool load${to_pascal_case(config.api_name)}Library(std::optional<std::string> path);
void unload${to_pascal_case(config.api_name)}Library();
bool is${to_pascal_case(config.api_name)}LibraryLoaded();
    
%  for f in standard_functions:
extern ${f.returns.type.str} (*${f.name})(${f.get_args_list_str()});
%  endfor
} // Standard

% if extensions:
namespace Extensions {
%  for ext in extensions:
extern ${ext.returns.type.str} (*${ext.name})(${ext.get_args_list_str()});
%  endfor
} // Extensions
% endif

bool isSuccessful(${config.result_type} result);

% for rpc_func in rpc_functions:
\
%  if get_rpc_handler_suffix(rpc_func) or use_rpc_custom_handler(rpc_func):
bool ${rpc_func.name}Handler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
%  endif
%  if not use_rpc_custom_handler(rpc_func):
inline bool ${rpc_func.name}Handler${get_rpc_handler_suffix(rpc_func)}(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for ${rpc_func.name}");
%    for prologue_line in prologue(rpc_func):
    ${prologue_line}
%    endfor # prologue(rpc_func)
%     if requires_malloc_shmem_zero_copy_handler(rpc_func):
    if(nullptr == ctx.getMallocShmemZeroCopyHandler()){
        log<Verbosity::error>("Client unexpectedly requested zero-copy translation for user-provided memory");
        return false;
    }
%     endif
    auto apiCommand = reinterpret_cast<${'::'.join(config.rpc_namespace + [rpc_func.message_name])}*>(command);
%     if get_struct_members_layouts(rpc_func):
    apiCommand->captures.reassembleNestedStructs();
%     endif
    apiCommand->captures.ret = ${get_rpc_func_fqfn(rpc_func)}(
%    for arg in rpc_func.args:
%     if arg.kind.is_pointer_zero_copy_malloc_shmem():
<%      arg_size = f"apiCommand->captures.{arg.name}.size" if arg.traits.uses_inline_dynamic_mem else arg.get_calculated_array_size('apiCommand->args.')%>\
                                                ctx.getMallocShmemZeroCopyHandler()->translateZeroCopyMallocShmemPtr(${get_arg_from_api_command_struct(rpc_func, arg)}, ${arg_size})\
%     else : # not arg.kind.is_pointer_zero_copy_malloc_shmem
%      if arg.traits.uses_standalone_allocation:
                                                channel.decodeLocalPtrFromHeapOffset(${get_arg_from_api_command_struct(rpc_func, arg)})\
%      else : # not arg.traits.uses_standalone_allocation       
                                                ${get_arg_from_api_command_struct(rpc_func, arg)}\
%      endif
%     endif
${", " if not loop.last else ""}
%    endfor # rpc_func.args
                                                );
%    for arg in rpc_func.args:
%     if arg.daemon_action_on_success:
    if(isSuccessful(apiCommand->captures.ret)) {
        const auto& resource = ${get_arg_from_api_command_struct(rpc_func, arg)};
        if (resource) {
            ${arg.daemon_action_on_success.format("resource" if arg.kind.is_scalar() else "*resource")};
        }
    }
%     endif # arg.daemon_action_on_success
%     if arg.daemon_action_at_end:
    {
        const auto& resource = ${get_arg_from_api_command_struct(rpc_func, arg)};
        if (resource) {
            ${arg.daemon_action_at_end.format("resource" if arg.kind.is_scalar() else "*resource")};
        }
    }
%     endif # arg.daemon_action_at_end
%    endfor # rpc_func.args
%    for epilogue_line in epilogue(rpc_func):
    ${epilogue_line}
%    endfor # epilogue(rpc_func)
    return true;
}
%  endif # not use_rpc_custom_handler
% endfor # rpc_functions

inline void registerGeneratedHandlers${to_pascal_case(config.api_name)}(Cal::Service::Provider::RpcSubtypeHandlers &outHandlers){
% if not rpc_functions:
// No RPC handlers were generated (based on dont_generate_rpc_message)
% else: # rpc_functions
    using namespace ${'::'.join(config.rpc_namespace)};
    outHandlers.resize(${rpc_functions[-1].message_name}::messageSubtype + 1);
%  for rpc_func in rpc_functions:
    outHandlers[${rpc_func.message_name}::messageSubtype] = ${rpc_func.name}Handler;
%  endfor # rpc_functions
% endif # rpc_functions
}

% for rpc_func in rpc_functions:
\
% if not (rpc_func.special_handling and rpc_func.special_handling.rpc and rpc_func.special_handling.rpc.dont_generate_call_directly):
inline void callDirectly(${'::'.join(config.rpc_namespace + [rpc_func.message_name])} &apiCommand) {
%    if rpc_func.returns.type.is_void():
    ${get_rpc_func_fqfn(rpc_func)}(
%    else : # not rpc_func.returns.type.is_void()
    apiCommand.captures.ret = ${get_rpc_func_fqfn(rpc_func)}(
%    endif
%    for arg in rpc_func.args:
                                                apiCommand.args.${arg.name}\
${", " if not loop.last else ""}
%    endfor # rpc_func.args
                                                );
}
% endif
% endfor # rpc_functions

inline bool callDirectly(Cal::Rpc::RpcMessageHeader *command) {
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
% for rpc_func in rpc_functions:
%   if not (rpc_func.special_handling and rpc_func.special_handling.rpc and rpc_func.special_handling.rpc.dont_generate_call_directly):
        case ${'::'.join(config.rpc_namespace + [rpc_func.message_name])}::messageSubtype : callDirectly(*reinterpret_cast<${'::'.join(config.rpc_namespace + [rpc_func.message_name])}*>(command)); break;
%  endif
% endfor # rpc_functions
    }
    return true;
}

% for namespace_part in reversed(daemon_namespace):
} // namespae ${namespace_part}
%endfor
// #### Generated code -- end ####
