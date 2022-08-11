##
## Copyright (C) 2022 Intel Corporation
##
## SPDX-License-Identifier: MIT
##
// #### Generated code -- begin ####
% for header in file_headers:
${header}
% endfor

% for f in [f for f in functions if not f.traits.is_extension and not (f.special_handling and f.special_handling.icd and f.special_handling.icd.dont_generate_stub)] :
<% func_base = f if not f.aliased_function else f.aliased_function%>\
${func_base.returns.type.str} ${f.name}(${get_func_handler_args_list_str(func_base)}){
%  if not func_base.returns.type.is_void():
   return {};
%  endif
}

% endfor # functions
// #### Generated code -- end ####
