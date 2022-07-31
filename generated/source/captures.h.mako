##
## Copyright (C) 2022 Intel Corporation
##
## SPDX-License-Identifier: MIT
##
    struct Captures {

## Optional DynamicTraits struct
% if emit_dynamic_traits:
        struct DynamicTraits {
## Dynamic traits construction
            static DynamicTraits calculate(${function.get_args_list_str()});
            uint32_t totalDynamicSize = 0;
%  if emit_per_arg_dynamic_traits:
%   for arg in inline_dyn_array_args:
## Dynamic traits
            DynamicArgTraits ${arg.name} = {};          
%   endfor
%  endif
\
## Entry point of nested structures layouts
%  if cl.struct_members_layouts:
            uint32_t dynamicStructMembersOffset = 0;
%  endif
\
%  for arg, member_layouts in cl.struct_members_layouts.items():
%   if member_layouts:
            DynamicArgTraits ${arg.name}NestedTraits = {};
%   endif
%  endfor
        };

% endif
\
## Capture for return value
% if not function.returns.type.is_void():
        ${function.returns.type.str} ret = ${function.returns.default};
% endif
\
## Capture for all fixed-length arrays
% for arg in fixed_array_args:
%  if arg.kind_details.num_elements.is_single_element():
        ${arg.kind_details.element.type.str} ${arg.name};
%  else:
        ${arg.kind_details.element.type.dereferenceable_str()} ${arg.name}[${arg.kind_details.num_elements.get_constant()}];
%  endif
%endfor
\
## Dynmem offsets for dynamic-length arrays
% for arg in dyn_offset_args:
        uint32_t ${f_offset_name(arg)} = 0;
% endfor
\
## Dynmem counts for dynamic-length arrays
% for arg in dyn_count_args:
        uint32_t ${f_count_name(arg)} = 0;
% endfor
\
## Entry point of nested structures layouts
%  if cl.struct_members_layouts:
        uint32_t dynamicStructMembersOffset = 0;
%  endif
\
## Dynmem entry point for dynamic struct members
%  for arg, member_layouts in cl.struct_members_layouts.items():
%   if member_layouts:
        uint32_t ${arg.name}NestedTraitsOffset = 0;
        uint32_t ${arg.name}NestedTraitsCount = 0;
%   endif
%  endfor
\
## Create getters for dynamic-length arrays
% for arg in [arg for arg in inline_dyn_array_args if not arg.traits.uses_standalone_allocation]:
%  if not arg.traits.uses_dynamic_arg_getter:
## Special case without getter - only when on dynamic arg
<% assert(len([arg for arg in inline_dyn_array_args if not arg.traits.uses_standalone_allocation]) == 1) %>\
        ${arg.kind_details.element.type.get_deref_type()} ${arg.name}[];
%  else:
<% assert requires_raw_dynamic_mem %>\
## Per arg getter based on dynMemTraits
%   if arg.traits.uses_nested_capture:
        std::vector<${arg.kind_details.element.type.str}> ${f_arg_getter_name(arg)}() {
            auto arrayOffset = ${cl.get_arg_dynamic_offset(arg)};
            auto nestedArraysOffsets = reinterpret_cast<uint32_t*>(dynMem + arrayOffset);
            
            using ElementT = ${arg.kind_details.element.type.str};
            auto elCount = ${cl.get_arg_dynamic_count(arg)};
            std::vector<ElementT> ret;
            ret.reserve(elCount);
            for(uint32_t i = 0; i < elCount; ++i){
                ret.push_back(reinterpret_cast<ElementT>(dynMem + nestedArraysOffsets[i]));
            }
            return ret;
        }
%   else:
        ${arg.type.str} ${f_arg_getter_name(arg)}() {
            auto offset = ${cl.get_arg_dynamic_offset(arg)};
            return reinterpret_cast<${arg.type.str}>(dynMem + offset);
        }
%   endif

%  endif
% endfor

% if emit_dynamic_traits:
        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
%  for arg in dyn_offset_args:
        ${f_offset_name(arg)} = dynamicTraits.${arg.name}.offset;
%  endfor
%  for arg in dyn_count_args:
        ${f_count_name(arg)} = dynamicTraits.${arg.name}.count;
%  endfor
%  if cl.struct_members_layouts:
            dynamicStructMembersOffset = dynamicTraits.dynamicStructMembersOffset;
%  endif
%  for arg, member_layouts in cl.struct_members_layouts.items():
%   if member_layouts:
            ${arg.name}NestedTraitsOffset = dynamicTraits.${arg.name}NestedTraits.offset;
            ${arg.name}NestedTraitsCount = dynamicTraits.${arg.name}NestedTraits.count;
%   endif
%  endfor
%  for arg in nested_args:
            {
                auto nestedArraysOffsets = reinterpret_cast<uint32_t*>(dynMem + dynamicTraits.${arg.name}.offset);
                for(uint32_t i = 0; i < dynamicTraits.${arg.name}.count; ++i){
                    nestedArraysOffsets[i] = dynamicTraits.${arg.name}.nested[i].offset;
                }
            }
%  endfor # nested_args
%  if nested_args or cl.struct_members_layouts:
            dynMemSize = dynamicTraits.totalDynamicSize;
%  endif # nested_args
        }
        
% endif # emit_dynamic_traits
\
% if requires_raw_dynamic_mem:
## Dynamic memory blob for multiple args
%  if nested_args or cl.struct_members_layouts:
        uint32_t dynMemSize = 0;
%  endif # nested_args
        alignas(8) char dynMem[];
% endif
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
\
% if emit_copy_assignment:
        std::unique_ptr<char[]> clone() {
            auto newCapturesMem = std::make_unique<char[]>(getCaptureTotalSize());
            auto newCaptures = new (newCapturesMem.get()) Captures();

            constexpr static bool skipSizeValidation{true};
            newCaptures->assignFrom(*this, skipSizeValidation);

            return newCapturesMem;
        }

        bool assignFrom(const Captures& rhs, bool skipSizeValidation = false) {
            if (this == &rhs) {
                return true;
            }
% if emit_dynamic_traits :
            if (!skipSizeValidation && getCaptureDynMemSize() != rhs.getCaptureDynMemSize()) {
                return false;
            }
% endif
## Return value
% if not function.returns.type.is_void():
            this->ret = rhs.ret;
% endif # not function.returns.type.is_void()
\
## Fixed-length arrays
% for arg in fixed_array_args:
%  if arg.kind_details.num_elements.is_single_element():
            this->${arg.name} = rhs.${arg.name};
%  else:
            for(size_t i = 0; i < ${arg.kind_details.num_elements.get_constant()}; ++i){
                this->${arg.name}[i] = rhs.${arg.name}[i];
            }
%  endif
%endfor
\
## Dynmem offsets for dynamic-length arrays
% for arg in dyn_offset_args:
            this->${f_offset_name(arg)} = rhs.${f_offset_name(arg)};
% endfor # dyn_offset_args
\
## Dynmem counts for dynamic-length arrays
% for arg in dyn_count_args:
            this->${f_count_name(arg)} = rhs.${f_count_name(arg)};
% endfor # dyn_count_args
\
## Dynmem for entry point of nested struct members
%  for arg, member_layouts in cl.struct_members_layouts.items():
%   if member_layouts:
            this->${arg.name}NestedTraitsOffset = rhs.${arg.name}NestedTraitsOffset;
            this->${arg.name}NestedTraitsCount = rhs.${arg.name}NestedTraitsCount;
%   endif
%  endfor
\
## Dynmem
% if requires_raw_dynamic_mem:
            memcpy(this->dynMem, rhs.dynMem, rhs.getCaptureDynMemSize());
% elif inline_dyn_array_args : # not requires_raw_dynamic_mem and inline_dyn_array_args
<% assert len(inline_dyn_array_args) == 1 %>\
            for(size_t i = 0; i < ${f_count_name(inline_dyn_array_args[0])}; ++i){
                this->${inline_dyn_array_args[0].name}[i] = rhs.${inline_dyn_array_args[0].name}[i];
            }
% endif # not requires_raw_dynamic_mem and inline_dyn_array_args
\
% if requires_raw_dynamic_mem and (nested_args or cl.struct_members_layouts):
            this->dynMemSize = rhs.dynMemSize;
% endif
\
%  if cl.struct_members_layouts:
            this->dynamicStructMembersOffset = rhs.dynamicStructMembersOffset;
            reassembleNestedStructs();
%  endif
            return true;
        }
% endif # emit_copy_assignment
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;
\
%   if cl.struct_members_layouts:
\
        void reassembleNestedStructs() {
            using Cal::Utils::alignUpPow2;

            uint32_t currentOffset = dynamicStructMembersOffset;

%      for arg, member_layouts in cl.struct_members_layouts.items():
%        if member_layouts:
\
            if(${arg.name}NestedTraitsCount > 0){
                assert(currentOffset == ${arg.name}NestedTraitsOffset);
                auto* ${arg.name}Traits = reinterpret_cast<DynamicStructTraits<${arg.kind_details.element.type.str}>*>(dynMem + currentOffset);
                currentOffset += alignUpPow2<8>(${arg.name}NestedTraitsCount * sizeof(DynamicStructTraits<${arg.kind_details.element.type.str}>));

                auto* dest${member_layout_formatter.capital(arg.name)} = &${arg.name};
%        endif # member_layouts:
\
%        for member_layout in member_layouts:

                for (uint32_t i = 0; i < ${arg.name}NestedTraitsCount; ++i) {
${member_layout.create_reassemble_nested_structs("currentOffset", member_layout_formatter, spaces_count=20, it='i')}
                }
%        endfor # for member_layout in member_layouts
        }
%      endfor # for arg, member_layouts
%      if member_layouts:
    }
%      endif # member_layouts
%   endif # if cl.struct_members_layouts

    }captures;
    
