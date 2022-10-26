##
## Copyright (C) 2022 Intel Corporation
##
## SPDX-License-Identifier: MIT
##
// #### Generated code -- begin ####
#include <string>
#include <vector>

% for namespace_part in daemon_namespace:
namespace ${namespace_part} {
% endfor

%if unimplemented:
inline std::vector<std::string> getListOfUnimplementedFunctionNames(){
    std::vector<std::string> ret;
% for func_category in unimplemented:
%  for func_name in func_category["members"]:
    ret.push_back("${func_name}");
%  endfor
% endfor
    return ret;
}
%endif

% for namespace_part in reversed(daemon_namespace):
} // namespae ${namespace_part}
%endfor
// #### Generated code -- end ####
