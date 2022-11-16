##
## Copyright (C) 2022 Intel Corporation
##
## SPDX-License-Identifier: MIT
##
// #### Generated code -- begin ####
#include "shared/rpc_message.h"
#include "shared/shmem_transfer_desc.h"
% for header in file_headers:
${header}
% endfor

#include "shared/utils.h"

#include <cassert>
#include <cstring>
#include <optional>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

% for namespace_part in rpc_namespace:
namespace ${namespace_part} {
% endfor

% if config.api_name == 'level_zero':
    inline bool operator==(const ze_ipc_event_pool_handle_t& lhs, const ze_ipc_event_pool_handle_t& rhs) {
        return 0 == std::memcmp(lhs.data, rhs.data, ZE_MAX_IPC_HANDLE_SIZE);
    }

    inline bool operator==(const ze_ipc_mem_handle_t& lhs, const ze_ipc_mem_handle_t& rhs) {
        return 0 == std::memcmp(lhs.data, rhs.data, ZE_MAX_IPC_HANDLE_SIZE);
    }
% endif

template <typename Ptr>
inline void forcePointerWrite(Ptr& p, void* value) {
    static_assert(std::is_pointer_v<Ptr>, "forcePointerWrite() must be used with pointers!");
    using WritablePtr = std::remove_cv_t<Ptr>;

    const_cast<WritablePtr&>(p) = static_cast<WritablePtr>(value);
}

struct DynamicArgTraits {
    uint32_t offset;
    uint32_t count;
    uint32_t size;
    std::vector<DynamicArgTraits> nested;
};

template <typename DynamicStructT>
struct DynamicStructTraits {
    int32_t offset;
    int32_t count;
};

% for struct_description in config.structures:
%  if struct_description.members_to_capture():
template <>
struct DynamicStructTraits<${struct_description.name}> {
%  for member in struct_description.members_to_capture():
    int32_t ${member.name}Offset{-1};
    int32_t ${member.name}Count{-1};
%  endfor
};

%  endif
% endfor

template<typename T>
inline char *asMemcpyDstT(T * ptr) {
    static_assert(std::is_standard_layout_v<T>);
    return reinterpret_cast<char*>(const_cast<std::remove_const_t<T>*>(ptr));
};

inline char *asMemcpyDstT(const void * ptr) {
    return reinterpret_cast<char*>(const_cast<void*>(ptr));
};

inline char *asMemcpyDstT(void * ptr) {
    return reinterpret_cast<char*>(const_cast<void*>(ptr));
};

% for func in config.functions:
%  if should_skip_message_generation(func):
 // ${func.name} ignored in generator - based on dont_generate_rpc_message flag
%  else: # not should_skip_message_generation(func)
struct ${func.message_name} {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = ${get_message_subtype(func)};
    static constexpr float latency = ${func.latency};

    using ReturnValueT = ${func.returns.type.str};

    struct Args {
%   for arg in func.args:
        ${arg.to_str()} = {};
%   endfor  # func.args

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
%   for arg in func.args:
            equal &= this->${arg.name} == rhs.${arg.name};
%   endfor  # func.args            
            return equal;
        }
    }args;

%   if func.implicit_args:
    struct ImplicitArgs {
%    for arg in func.implicit_args:
<%     assert arg.kind.is_scalar %>
           ${arg.type.str} ${arg.name} = {};
%    endfor  # func.implicit_args
    } implicitArgs;
%   endif # implicit_args
${func.capture_layout.generate_h()}
%   if not func.returns.type.is_void():
    ${func.returns.type.str} returnValue(){
        return captures.ret;
    }
%   endif func.returns.type.is_void()

    ${func.message_name}() = default;

    ${func.message_name}(${'const Captures::DynamicTraits &dynamicTraits, ' if func.capture_layout.emit_dynamic_traits else ''}${func.get_args_list_str()}) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpc${to_pascal_case(config.api_name)};
        header.subtype = messageSubtype;
%   for arg in func.args:
        args.${arg.name} = ${arg.name};
%   endfor # func.args
%   if func.capture_layout.emit_dynamic_traits:
        captures.adjustCaptureLayout(dynamicTraits);
%   endif # func.capture_layout.emit_dynamic_traits
    }
    
    static void fillWithoutCapture(${func.message_name} &message, ${func.get_args_list_str()}) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpc${to_pascal_case(config.api_name)};
        message.header.subtype = messageSubtype;
%   for arg in func.args:
        message.args.${arg.name} = ${arg.name};
%   endfor # func.args
    }
    
%   if func.traits.emit_copy_from_caller:

    void copyFromCaller(${', '.join(get_copy_from_caller_args(func))}){
%    for arg in [arg for arg in get_ptr_array_args(func) if not arg.traits.uses_standalone_allocation] :
%     if not arg.kind_details.server_access.write_only():
%      if arg.kind_details.can_be_null:
        if(args.${arg.name}){
%      endif #arg.kind_details.can_be_null
<%     i = "    " if arg.kind_details.can_be_null else ""%>\
%      if arg.kind_details.num_elements.is_single_element():
        ${i}captures.${arg.name} = *args.${arg.name};
%      elif not arg.traits.uses_nested_capture:
<%      dst = f"captures.{CapturesFormater.f_arg_getter_name(arg)}()" if arg.traits.uses_dynamic_arg_getter else f"captures.{arg.name}"%>\
<%      arg_size = f"dynMemTraits.{arg.name}.size" if arg.traits.uses_inline_dynamic_mem else arg.get_calculated_array_size('args.')%>\
        ${i}memcpy(asMemcpyDstT(${dst}), args.${arg.name}, ${arg_size});
%      else:
        ${i}{
        ${i}     auto array = captures.${CapturesFormater.f_arg_getter_name(arg)}();
        ${i}     for(uint32_t i = 0; i < dynMemTraits.${arg.name}.count; ++i) {
        ${i}         memcpy(asMemcpyDstT(array[i]), args.${arg.name}[i], dynMemTraits.${arg.name}.nested[i].size);
        ${i}     }
        ${i}}
%      endif
%      if arg.kind_details.can_be_null:
        }
%      endif #arg.kind_details.can_be_null
%     endif # kind_details.server_access.write_only()
%    endfor # ${get_ptr_array_args(func)}
%    for iarg in func.implicit_args:
%     if not iarg.server_access.write_only():
         this->implicitArgs.${iarg.name} = implicitArgs.${iarg.name};
%     endif # iarg.server_access.write_only()
%    endfor # func.implicit_args
\
%    if get_struct_members_layouts(func):
        using Cal::Utils::alignUpPow2;

        auto& dynMem = captures.dynMem;
        uint32_t currentOffset = captures.dynamicStructMembersOffset;
%     endif
\
%    for arg, member_layouts in get_struct_members_layouts(func).items():
%     if member_layouts:
        if(args.${arg.name}){
            assert(currentOffset == captures.${arg.name}NestedTraitsOffset);
            auto* ${arg.name}Traits = reinterpret_cast<DynamicStructTraits<${arg.kind_details.element.type.str}>*>(dynMem + currentOffset);
            currentOffset += alignUpPow2<8>(captures.${arg.name}NestedTraitsCount * sizeof(DynamicStructTraits<${arg.kind_details.element.type.str}>));
%     endif
\
%     for member_layout in member_layouts:

            for (uint32_t i = 0; i < captures.${arg.name}NestedTraitsCount; ++i) {
${member_layout.create_copy_from_caller("currentOffset", member_layout_formatter, spaces_count=16, it='i')}
            }
%   endfor # for member_layout in member_layouts
        }
%  endfor # for arg, member_layouts
    }
%   endif # func.traits.emit_copy_from_caller
\
%   if func.traits.emit_copy_to_caller:

    void copyToCaller(${', '.join(get_copy_to_caller_args(func))}){
%    for arg in [arg for arg in get_ptr_array_args(func) if not arg.traits.uses_standalone_allocation] :
%     if not arg.kind_details.server_access.read_only():
%      if arg.kind_details.can_be_null:
        if(args.${arg.name}){
%      endif # arg.kind_details.can_be_null
%      if arg.kind_details.num_elements.is_single_element():
            *args.${arg.name} = captures.${arg.name};
%      else: # not arg.kind_details.num_elements.is_single_element():
<%      assert arg.traits.uses_nested_capture == False %>\
<%      src = f"captures.{CapturesFormater.f_arg_getter_name(arg)}()" if arg.traits.uses_dynamic_arg_getter else f"captures.{arg.name}" %>\
<%      arg_size = f"dynMemTraits.{arg.name}.size" if arg.traits.uses_inline_dynamic_mem else arg.get_calculated_array_size('args.')%>\
            memcpy(args.${arg.name}, ${src}, ${arg_size});
%      endif # not arg.kind_details.num_elements.is_single_element():
%      if arg.kind_details.can_be_null:
        }
%      endif # arg.kind_details.can_be_null
%     endif # not arg.kind_details.server_access.read_only()
%    endfor # ${get_ptr_array_args(func)}
%    for iarg in func.implicit_args:
%     if not iarg.server_access.read_only():
         implicitArgs.${iarg.name} = this->implicitArgs.${iarg.name};
%     endif # not iarg.server_access.read_only():
%    endfor # func.implicit_args
    }
%   endif # func.traits.emit_copy_to_caller
};
static_assert(std::is_standard_layout_v<${func.message_name}>);
%  endif # should_skip_message_generation(func)
% endfor # config.functions

inline const char *getRpcCallFname(const RpcCallId callId) {
    static const std::unordered_map<RpcMessageHeader::MessageUniqueIdT, std::string> options = {
% for rpc_func in rpc_functions:
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpc${to_pascal_case(config.api_name)}, ${rpc_func.message_name}::messageSubtype).id, "${rpc_func.name}"),
% endfor # rpc_functions
    };

    auto it = options.find(callId.id);
    if(it == options.end()) {
        return "UNKNOWN";
    }
    return it->second.c_str();
}

inline auto getRpcCallId(const std::string &funcName) {
    using RetT = RpcCallId;
    static const std::unordered_map<std::string, RetT> options = {
% for rpc_func in rpc_functions:
        std::pair<std::string, RetT>("${rpc_func.name}", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpc${to_pascal_case(config.api_name)}, ${rpc_func.message_name}::messageSubtype)),
% endfor # rpc_functions
    };

    auto it = options.find(funcName);
    if(it == options.end()) {
        return std::optional<RetT>(std::nullopt);
    }
    return std::optional<RetT>(it->second);
}

namespace RpcCallIds {
% for rpc_func in rpc_functions:
static constexpr RpcCallId ${rpc_func.name} = {Cal::Rpc::RpcMessageHeader::messageTypeRpc${to_pascal_case(config.api_name)}, ${rpc_func.message_name}::messageSubtype};
%endfor # rpc_functions
} // namespace RpcCallIds

namespace RpcCallMessageTypes {
% for rpc_func in rpc_functions:
using ${rpc_func.name} = ${rpc_func.message_name};
%endfor # rpc_functions
}

% for namespace_part in reversed(rpc_namespace):
} // namespace ${namespace_part}
%endfor
// #### Generated code -- end ####
