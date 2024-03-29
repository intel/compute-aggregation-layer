##
## Copyright (C) 2022-2023 Intel Corporation
##
## SPDX-License-Identifier: MIT
##
// #### Generated code -- begin ####

#include "shared/rpc_message.h"
#include "shared/shmem_transfer_desc.h"

% for header in file_headers:
${header}
% endfor

#include <cassert>
#include <cstring>
#include <memory>
#include <optional>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

% for namespace_part in rpc_namespace:
namespace ${namespace_part} {
% endfor

% for struct_description in config.structures:
%  if struct_description.members_to_capture():
template <>
struct DynamicStructTraits<${struct_description.name}> {
%  for member in struct_description.members_to_capture():
    int32_t ${member.name}Offset{-1};
    int32_t ${member.name}Count{-1};
%    if member.kind.is_opaque_list():
    ${member.type.str} ${member.name}FirstOriginalElement{nullptr};
%    endif % member.kind.is_opaque_list()
%  endfor
};

%  endif
% endfor

% for group_name in config.functions:
%  for func in config.functions[group_name]:
%   if should_skip_message_generation(func):
 // ${func.name} ignored in generator - based on dont_generate_rpc_message flag
%   else: # not should_skip_message_generation(func)
\
%    if func.implicit_args:
struct ${func.message_name}ImplicitArgs {
%     for arg in func.implicit_args:
<%     assert arg.kind.is_scalar %>\
    ${arg.type.str} ${arg.name} = {};
%     endfor  # func.implicit_args
};

%    endif # implicit_args
\
struct ${func.message_name} {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = ${get_message_subtype(func)};
    static constexpr float latency = ${func.latency};
    static constexpr CallCategory category = CallCategory::${func.category};


    using ReturnValueT = ${func.returns.type.str};

    struct Args {
%    for arg in func.args:
        ${arg.to_str()} = {};
%    endfor  # func.args

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
%    for arg in func.args:
            equal &= this->${arg.name} == rhs.${arg.name};
%    endfor  # func.args            
            return equal;
        }
    }args;

%    if func.implicit_args:
    ${func.message_name}ImplicitArgs implicitArgs{};
%    endif # implicit_args
${func.capture_layout.generate_h()}
%    if not func.returns.type.is_void():
    ${func.returns.type.str} returnValue(){
        return captures.ret;
    }
%    endif func.returns.type.is_void()

    ${func.message_name}() = default;

    ${func.message_name}(${'const Captures::DynamicTraits &dynamicTraits, ' if func.capture_layout.emit_dynamic_traits else ''}${func.get_args_list_str()}) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpc${to_pascal_case(config.api_name)};
        header.subtype = messageSubtype;
%    for arg in func.args:
        args.${arg.name} = ${arg.name};
%    endfor # func.args
%    if func.capture_layout.emit_dynamic_traits:
        captures.adjustCaptureLayout(dynamicTraits);
%    endif # func.capture_layout.emit_dynamic_traits
    }
    
    static void fillWithoutCapture(${func.message_name} &message, ${func.get_args_list_str()}) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpc${to_pascal_case(config.api_name)};
        message.header.subtype = messageSubtype;
%    for arg in func.args:
        message.args.${arg.name} = ${arg.name};
%    endfor # func.args
    }
    
%    if func.traits.emit_copy_from_caller:

    void copyFromCaller(${', '.join(get_copy_from_caller_args(func))}){
%     for arg in [arg for arg in get_ptr_array_args(func) if not (arg.traits.uses_standalone_allocation or arg.traits.uses_staging_usm_allocation)] :
%      if arg.kind_details.server_access.can_read():
%       if arg.kind_details.can_be_null:
        if(args.${arg.name}){
%       endif #arg.kind_details.can_be_null
<%     i = "    " if arg.kind_details.can_be_null else ""%>\
%       if arg.kind_details.num_elements.is_single_element():
        ${i}captures.${arg.name} = *args.${arg.name};
%       elif not arg.traits.uses_nested_capture:
<%      dst = f"captures.{CapturesFormater.f_arg_getter_name(arg)}()" if arg.traits.uses_dynamic_arg_getter else f"captures.{arg.name}"%>\
<%      arg_size = f"dynMemTraits.{arg.name}.size" if arg.traits.uses_inline_dynamic_mem else arg.get_calculated_array_size('args.')%>\
        ${i}memcpy(asMemcpyDstT(${dst}), args.${arg.name}, ${arg_size});
%       else:
        ${i}{
        ${i}     auto array = captures.${CapturesFormater.f_arg_getter_name(arg)}();
        ${i}     for(uint32_t i = 0; i < dynMemTraits.${arg.name}.count; ++i) {
        ${i}         memcpy(asMemcpyDstT(array[i]), args.${arg.name}[i], dynMemTraits.${arg.name}.nested[i].size);
        ${i}     }
        ${i}}
%       endif
%       if arg.kind_details.can_be_null:
        }
%       endif #arg.kind_details.can_be_null
%      endif # arg.kind_details.server_access.can_read
%     endfor # ${get_ptr_array_args(func)}
%     for iarg in func.implicit_args:
%      if iarg.server_access.can_read():
         this->implicitArgs.${iarg.name} = implicitArgs.${iarg.name};
%      endif # iarg.server_access.can_read()
%     endfor # func.implicit_args
\
%     if get_struct_members_layouts(func):
        using Cal::Utils::alignUpPow2;

        auto& dynMem = captures.dynMem;
        uint32_t currentOffset = captures.dynamicStructMembersOffset;
%      endif
\
%     for arg, member_layouts in get_struct_members_layouts(func).items():
%      if member_layouts:
        if(args.${arg.name}){
            assert(currentOffset == captures.${arg.name}NestedTraitsOffset);
            auto* ${arg.name}Traits = reinterpret_cast<DynamicStructTraits<${arg.kind_details.element.type.str}>*>(dynMem + currentOffset);
            currentOffset += alignUpPow2<8>(captures.${arg.name}NestedTraitsCount * sizeof(DynamicStructTraits<${arg.kind_details.element.type.str}>));
%      endif
\
%      for member_layout in member_layouts:

            for (uint32_t i = 0; i < captures.${arg.name}NestedTraitsCount; ++i) {
${member_layout.create_copy_from_caller("currentOffset", member_layout_formatter, spaces_count=16, it='i')}
            }
%    endfor # for member_layout in member_layouts
        }
%   endfor # for arg, member_layouts
    }
%    endif # func.traits.emit_copy_from_caller
\
%    if func.traits.emit_copy_to_caller:

    void copyToCaller(${', '.join(get_copy_to_caller_args(func))}){
%     for arg in [arg for arg in get_ptr_array_args(func) if not arg.traits.uses_standalone_allocation] :
%      if arg.kind_details.server_access.can_write():
%       if arg.kind_details.can_be_null:
        if(args.${arg.name}){
%       endif # arg.kind_details.can_be_null
%       if arg.kind_details.num_elements.is_single_element():
            *args.${arg.name} = captures.${arg.name};
%       else: # not arg.kind_details.num_elements.is_single_element():
<%      assert arg.traits.uses_nested_capture == False %>\
<%      src = f"captures.{CapturesFormater.f_arg_getter_name(arg)}()" if arg.traits.uses_dynamic_arg_getter else f"captures.{arg.name}" %>\
<%      arg_size = f"dynMemTraits.{arg.name}.size" if arg.traits.uses_inline_dynamic_mem else arg.get_calculated_array_size('args.')%>\
            memcpy(args.${arg.name}, ${src}, ${arg_size});
%       endif # not arg.kind_details.num_elements.is_single_element():
%       if arg.kind_details.can_be_null:
        }
%       endif # arg.kind_details.can_be_null
%      endif # arg.kind_details.server_access.can_write()
%     endfor # ${get_ptr_array_args(func)}
%     for iarg in func.implicit_args:
%      if iarg.server_access.can_write():
         implicitArgs.${iarg.name} = this->implicitArgs.${iarg.name};
%      endif # iarg.server_access.can_write
%     endfor # func.implicit_args
\
%     if func.traits.is_copy_to_caller_required_for_any_of_struct_fields():
%       if get_struct_members_layouts(func):
        using Cal::Utils::alignUpPow2;

        auto& dynMem = captures.dynMem;
        uint32_t currentOffset = captures.dynamicStructMembersOffset;
%       endif
\
%       for arg, member_layouts in get_struct_members_layouts(func).items():
%         if member_layouts:
        if(args.${arg.name}) {
            assert(currentOffset == captures.${arg.name}NestedTraitsOffset);
            auto* ${arg.name}Traits = reinterpret_cast<DynamicStructTraits<${arg.kind_details.element.type.str}>*>(dynMem + currentOffset);
            currentOffset += alignUpPow2<8>(captures.${arg.name}NestedTraitsCount * sizeof(DynamicStructTraits<${arg.kind_details.element.type.str}>));

            auto* dest${member_layout_formatter.capital(arg.name)} = args.${arg.name};
%         endif
\
%         for member_layout in member_layouts:

            for (uint32_t i = 0; i < captures.${arg.name}NestedTraitsCount; ++i) {
${member_layout.create_copy_to_caller("currentOffset", member_layout_formatter, spaces_count=16, it='i')}
            }
%         endfor # for member_layout in member_layouts
        }
%       endfor # for arg, member_layouts
%     endif # func.traits.is_copy_to_caller_required_for_any_of_struct_fields()
    }
%    endif # func.traits.emit_copy_to_caller
};
static_assert(std::is_standard_layout_v<${func.message_name}>);
%   endif # should_skip_message_generation(func)
%  endfor # config.functions[group_type]
% endfor # config.functions

inline const char *getRpcCallFname${to_pascal_case(config.subconfig_name)}(const RpcCallId callId) {
    static const std::unordered_map<RpcMessageHeader::MessageUniqueIdT, std::string> options = {
% for group_name in rpc_functions:
%  for rpc_func in rpc_functions[group_name]:
%   if not should_skip_message_generation(rpc_func):
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpc${to_pascal_case(config.api_name)}, ${rpc_func.message_name}::messageSubtype).id, "${rpc_func.name}"),
%   endif # should_skip_message_generation(rpc_func)
%  endfor # rpc_functions[group_name]
% endfor # rpc_functions
    };

    auto it = options.find(callId.id);
    if(it == options.end()) {
        return "UNKNOWN";
    }
    return it->second.c_str();
}

inline auto getRpcCallId${to_pascal_case(config.subconfig_name)}(const std::string &funcName) {
    using RetT = RpcCallId;
    static const std::unordered_map<std::string, RetT> options = {
% for group_name in rpc_functions:
%  for rpc_func in rpc_functions[group_name]:
%   if not should_skip_message_generation(rpc_func):
        std::pair<std::string, RetT>("${rpc_func.name}", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpc${to_pascal_case(config.api_name)}, ${rpc_func.message_name}::messageSubtype)),
%   endif # should_skip_message_generation(rpc_func)
%  endfor # rpc_functions[group_name]
% endfor # rpc_functions
    };

    auto it = options.find(funcName);
    if(it == options.end()) {
        return std::optional<RetT>(std::nullopt);
    }
    return std::optional<RetT>(it->second);
}

namespace RpcCallIds {
% for group_name in rpc_functions:
%  for rpc_func in rpc_functions[group_name]:
%   if not should_skip_message_generation(rpc_func):
static constexpr RpcCallId ${rpc_func.name} = {Cal::Rpc::RpcMessageHeader::messageTypeRpc${to_pascal_case(config.api_name)}, ${rpc_func.message_name}::messageSubtype};
%   endif # should_skip_message_generation(rpc_func)
%  endfor # rpc_functions[group_name]
% endfor # rpc_functions
} // namespace RpcCallIds

namespace RpcCallMessageTypes {
% for group_name in rpc_functions:
%  for rpc_func in rpc_functions[group_name]:
%   if not should_skip_message_generation(rpc_func):
using ${rpc_func.name} = ${rpc_func.message_name};
%   endif # should_skip_message_generation(rpc_func)
%  endfor # rpc_functions[group_name]
% endfor # rpc_functions
}

% for namespace_part in reversed(rpc_namespace):
} // namespace ${namespace_part}
%endfor
// #### Generated code -- end ####
