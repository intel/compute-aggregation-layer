##
## Copyright (C) 2022 Intel Corporation
##
## SPDX-License-Identifier: MIT
##
// #### Generated code -- begin ####
#include "icd/icd_global_state.h"
#include "shared/rpc.h"
% for header in file_headers:
${header}
% endfor

#include <cstdlib>

% for namespace_part in icd_namespace:
namespace ${namespace_part} {
% endfor # icd_namespace
% for f in functions:
<% func_base = f if not f.aliased_function else f.aliased_function%>\
${func_base.returns.type.str} ${get_func_handler_name(f)} (${get_func_handler_args_list_str(func_base)});
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

inline void ${config.icd_init_dispatch_table_func_name_format.format("")}(${config.icd_dispatch_table_type["core"]} &dt){
% for func in functions_in_dispatch_table:
    dt.${get_func_ddi_name(func)} = ${'::'.join(config.icd_namespace + [func.name])};
% endfor # functions_in_dispatch_table
% if config.unimplemented:
    // below are unimplemented, provided bindings are for easier debugging only
%  for func_category in config.unimplemented:
%   if func_category["name"] == "core":
%    for fname in func_category["members"]:
    dt.${get_ddi_name(fname)} = reinterpret_cast<decltype(dt.${get_ddi_name(fname)})>(${'::'.join(config.icd_namespace + ['Unimplemented', fname.rpartition(".")[2]+'Unimpl'])});
%    endfor # fname in func_category["members"]
%   endif # func_category["name"] == "core"
%  endfor # config.unimplemented
% endif # config.unimplemented
}

% for func_category in config.unimplemented:
%  if func_category["name"] != "core":
inline void ${config.icd_init_dispatch_table_func_name_format.format(func_category["name"].capitalize())}(${config.icd_dispatch_table_type[func_category["name"]]} &dt){
%   for fname in func_category["members"]:
    dt.${get_ddi_name(fname)} = reinterpret_cast<decltype(dt.${get_ddi_name(fname)})>(${'::'.join(config.icd_namespace + ['Unimplemented', fname.rpartition(".")[2]+'Unimpl'])});
%   endfor # fname in func_category["members"]
}
%  endif # func_category["name"] != "core"
% endfor # config.unimplemented

% if config.icd_get_extenion_func_addr_func_name:
void *${config.icd_get_extenion_func_addr_func_name}(const char *funcName);
% endif #config.icd_get_extenion_func_addr_func_name:
% for namespace_part in reversed(icd_namespace):
} // namespace ${namespace_part}
% endfor
// #### Generated code -- end ####
