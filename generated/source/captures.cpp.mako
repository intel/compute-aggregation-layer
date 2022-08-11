##
## Copyright (C) 2022 Intel Corporation
##
## SPDX-License-Identifier: MIT
##
% if emit_dynamic_traits:
${function.message_name}::Captures::DynamicTraits ${function.message_name}::Captures::DynamicTraits::calculate(${function.get_args_list_str()}) {
    DynamicTraits ret = {};
%  if dyn_array_args:
%   if emit_per_arg_dynamic_traits:
    ret.${dyn_array_args[0].name}.count = ${dyn_array_args[0].get_calculated_elements_count()};
    ret.${dyn_array_args[0].name}.size = ${cl.get_dynamic_array_size_str(dyn_array_args[0], f"ret.{dyn_array_args[0].name}.count")};
<% prev = dyn_array_args[0] %>\
%    for arg in dyn_array_args[1:]:

    ret.${arg.name}.offset = alignUpPow2<8>(ret.${prev.name}.offset + ret.${prev.name}.size);
    ret.${arg.name}.count = ${arg.get_calculated_elements_count()};
    ret.${arg.name}.size = ${cl.get_dynamic_array_size_str(arg, f"ret.{arg.name}.count")};
<% prev = arg %>\
%    endfor # dyn_array_args[1:]
## Total size
    ret.totalDynamicSize = alignUpPow2<8>(ret.${prev.name}.offset + ret.${prev.name}.size);
%   else : # not emit_per_arg_dynamic_traits
    ret.totalDynamicSize = alignUpPow2<8>(${dyn_array_args[0].get_calculated_array_size()});
%   endif # not emit_per_arg_dynamic_traits
%  endif # dyn_array_args

%  for arg in nested_args:
    ret.${arg.name}.nested.reserve(ret.${arg.name}.count);
    for(uint32_t i = 0; i < ret.${arg.name}.count; ++i){
        DynamicArgTraits nested;
        nested.offset = ret.totalDynamicSize;
        nested.count = ${arg.kind_details.element.get_calculated_elements_count(arg.name, 'i')};
        nested.size = ${arg.kind_details.element.get_calculated_array_size(count = "nested.count")};
        ret.totalDynamicSize += alignUpPow2<8>(nested.size);
        ret.${arg.name}.nested.push_back(nested);
    }
%  endfor # nested_args
%  if cl.struct_members_layouts:
    ret.dynamicStructMembersOffset = ret.totalDynamicSize;
%  endif
%  for arg, member_layouts in cl.struct_members_layouts.items():
%   if member_layouts:
    if (${arg.name}) {
        ret.${arg.name}NestedTraits.offset = ret.totalDynamicSize;
        ret.${arg.name}NestedTraits.count = ${arg.get_calculated_elements_count()};
        ret.${arg.name}NestedTraits.size = ret.${arg.name}NestedTraits.count * sizeof(DynamicStructTraits<${arg.kind_details.element.type.str}>);
        ret.totalDynamicSize += alignUpPow2<8>(ret.${arg.name}NestedTraits.size);
%   endif
%   for member_layout in member_layouts:

        for (uint32_t i = 0; i < ret.${arg.name}NestedTraits.count; ++i) {
${member_layout.create_required_size_calculation("ret.totalDynamicSize", member_layout_formatter, spaces_count=12, it='j')}
        }
%   endfor
    }
%  endfor

    return ret;
}
% endif # emit_dynamic_traits

size_t ${function.message_name}::Captures::getCaptureTotalSize() const {
% if dyn_array_args or cl.struct_members_layouts:
%  if requires_raw_dynamic_mem:
%   if cl.struct_members_layouts or dyn_array_args[-1].traits.uses_nested_capture:
     auto size = offsetof(Captures, dynMem) + dynMemSize;
     return size;
%   else : # not cl.struct_members_layouts and not dyn_array_args[-1].traits.uses_nested_capture
%    if dyn_offset_args: # More than one dynamic member. We need to include the offset.
     const auto lastMemberOffset = ${f_offset_name(dyn_offset_args[-1])};
     const auto lastMemberArraySize = ${dyn_array_args[-1].get_calculated_array_size(count = f"this->{f_count_name(dyn_array_args[-1])}")};

     auto size = offsetof(Captures, dynMem) + Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
%    else:
     auto size = offsetof(Captures, dynMem) + Cal::Utils::alignUpPow2<8>(${dyn_array_args[-1].get_calculated_array_size(count = f"this->{f_count_name(dyn_array_args[-1])}")});
%    endif
     return size;
%   endif # dyn_array_args[-1].traits.uses_nested_capture
%  else : # not requires_raw_dynamic_mem
     auto size = offsetof(Captures, ${dyn_array_args[-1].name}) + Cal::Utils::alignUpPow2<8>(${dyn_array_args[-1].get_calculated_array_size(count = f"this->{f_count_name(dyn_array_args[-1])}")});
     return size;
%  endif : # not requires_raw_dynamic_mem
% else : # not dyn_array_args
    return sizeof(*this);
% endif # not dyn_array_args
}

size_t ${function.message_name}::Captures::getCaptureDynMemSize() const {
% if dyn_array_args or cl.struct_members_layouts:
%  if requires_raw_dynamic_mem:
%   if cl.struct_members_layouts or dyn_array_args[-1].traits.uses_nested_capture:
     return dynMemSize;
%   else : # not cl.struct_members_layouts and not dyn_array_args[-1].traits.uses_nested_capture
%    if dyn_offset_args: # More than one dynamic member. We need to include the offset.
     const auto lastMemberOffset = ${f_offset_name(dyn_offset_args[-1])};
     const auto lastMemberArraySize = ${dyn_array_args[-1].get_calculated_array_size(count = f"this->{f_count_name(dyn_array_args[-1])}")};

     auto size = Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
%    else:
     auto size = Cal::Utils::alignUpPow2<8>(${dyn_array_args[-1].get_calculated_array_size(count = f"this->{f_count_name(dyn_array_args[-1])}")});
%    endif
     return size;
%   endif # cl.struct_members_layouts or dyn_array_args[-1].traits.uses_nested_capture
%  else : # not requires_raw_dynamic_mem
     auto size = Cal::Utils::alignUpPow2<8>(${dyn_array_args[-1].get_calculated_array_size(count = f"this->{f_count_name(dyn_array_args[-1])}")});
     return size;
%  endif : # not requires_raw_dynamic_mem
% else : # not dyn_array_args
    return 0;
% endif # not dyn_array_args
}
