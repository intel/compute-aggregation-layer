##
## Copyright (C) 2022-2023 Intel Corporation
##
## SPDX-License-Identifier: MIT
##
// #### Generated code -- begin ####

% for header in file_headers:
${header}
% endfor

#include <cstdlib>

// Forward declarations of used RPC types
% for namespace_part in rpc_namespace:
namespace ${namespace_part} {
% endfor # rpc_namespace

% for group_name in functions:
%  for f in functions[group_name]:
%   if f.implicit_args:
struct ${f.message_name}ImplicitArgs;
%   endif # f.implicit_args
% endfor # functions[group_name]
% endfor # functions

% for namespace_part in reversed(rpc_namespace):
} // namespace ${namespace_part}
% endfor

% for namespace_part in icd_namespace:
namespace ${namespace_part} {
% endfor # icd_namespace
% for group_name in functions:
%  for f in functions[group_name]:
<% func_base = f if not f.aliased_function else f.aliased_function%>\
${func_base.returns.type.str} ${get_func_handler_name(f)} (${get_func_handler_args_list_str(func_base)});
%      if f.name == "zeModuleCreate":
${func_base.returns.type.str} ${get_func_handler_name(f)}Tracing (${get_func_handler_args_list_str(func_base)});
%      endif # func.name == "zeModuleCreate"
%  endfor # functions[group_name]
% endfor # functions

% if config.unimplemented:
namespace Unimplemented {
% for func_category in config.unimplemented:
%  for fname in func_category["members"]:
inline void ${fname.rpartition(".")[2]}Unimpl() {
    log<Verbosity::critical>("Function ${fname} is not yet implemented in Compute Aggregation Layer - aborting");
    std::abort();
}
%  endfor # func_category["members"]
% endfor # config.unimplemented
} // Unimplemented
% endif # config.unimplemented:

% for group_name in config.icd_dispatch_table_type:
<% init_func_name_suffix = "" if group_name == "core" else group_name.capitalize()%>\
inline void ${config.icd_init_dispatch_table_func_name_format.format(init_func_name_suffix)}(${config.icd_dispatch_table_type[group_name]} &dt){
%  for func in functions_in_dispatch_table[group_name]:
    dt.${get_func_ddi_name(func)} = ${'::'.join(config.icd_namespace + [func.name])};
%      if func.name == "zeModuleCreate":
    if (tracingEnabled) {
        dt.${get_func_ddi_name(func)} = ${'::'.join(config.icd_namespace + [func.name])}Tracing;
    }
%      endif # func.name == "zeModuleCreate"
%  endfor # functions_in_dispatch_table
%  if config.unimplemented:
    // below are unimplemented, provided bindings are for easier debugging only
%   for func_category in config.unimplemented:
%    if func_category["name"] == group_name:
%     for fname in func_category["members"]:
    dt.${get_ddi_name(fname)} = reinterpret_cast<decltype(dt.${get_ddi_name(fname)})>(${'::'.join(config.icd_namespace + ['Unimplemented', fname.rpartition(".")[2]+'Unimpl'])});
%     endfor # fname in func_category["members"]
%    endif # func_category["name"] == group_name
%   endfor # config.unimplemented
%  endif # config.unimplemented
}
% endfor # config.icd_dispatch_table_type

% if config.icd_get_extenion_func_addr_func_name:
void *${config.icd_get_extenion_func_addr_func_name}(const char *funcName);
% endif #config.icd_get_extenion_func_addr_func_name:
% for namespace_part in reversed(icd_namespace):
} // namespace ${namespace_part}
% endfor
// #### Generated code -- end ####
