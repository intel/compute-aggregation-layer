##
## Copyright (C) 2022-2023 Intel Corporation
##
## SPDX-License-Identifier: MIT
##
// #### Generated code -- begin ####

% for header in file_headers:
${header}
% endfor

% for group_name in functions_to_stub:
%  for f in functions_to_stub[group_name]:
<% func_base = f if not f.aliased_function else f.aliased_function%>\
${func_base.returns.type.str} ${f.name}(${get_func_handler_args_list_str(func_base)}){
%  if not func_base.returns.type.is_void():
   return {};
%  endif
}

%  endfor # functions_to_stub[group_name]
% endfor # functions_to_stub
// #### Generated code -- end ####
