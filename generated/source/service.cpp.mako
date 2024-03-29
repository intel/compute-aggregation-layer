##
## Copyright (C) 2022-2023 Intel Corporation
##
## SPDX-License-Identifier: MIT
##
// #### Generated code -- begin ####

% for header in file_headers:
${header}
% endfor

#include <shared/log.h>

#include <cassert>
#include <mutex>

% for namespace_part in daemon_namespace:
namespace ${namespace_part} {
% endfor

namespace Standard {
% for group_name in standard_functions:
%  for f in standard_functions[group_name]:
${f.returns.type.str} (*${f.name})(${f.get_args_list_str()}) = nullptr;
%  endfor # standard_functions[group_name]
% endfor # standard_functions

% if not config.parent_config:
void *libraryHandle = nullptr;

bool load${to_pascal_case(config.api_name)}Library(std::optional<std::string> path) {
    if(libraryHandle){
        return false == path.has_value();
    }
    
    std::string loadPath = path.value_or("${config.loader_lib_names[0]}");
    libraryHandle = dlopen(loadPath.c_str(), RTLD_NOW);
    
% for libName in config.loader_lib_names[1:]:
    if(nullptr == libraryHandle){
        loadPath = path.value_or("${libName}");
        libraryHandle = dlopen(loadPath.c_str(), RTLD_NOW);
    }
% endfor # libName in config.loader_lib_names[1:]

    if(nullptr == libraryHandle){
        return false;
    }

% for group_name in standard_functions:    
%  for f in [icd_function for icd_function in standard_functions[group_name] if not (icd_function.special_handling and icd_function.special_handling.icd and icd_function.special_handling.icd.not_in_dispatch_table)]:
    ${f.name} = reinterpret_cast<decltype(${f.name})>(dlsym(libraryHandle, "${f.name}"));
    if(nullptr == ${f.name}){
%   if f.special_handling and f.special_handling.optional:
        log<Verbosity::debug>("Missing symbol ${f.name} in %s", loadPath.c_str());
%   else : # not (f.special_handling and f.special_handling.optional):
        log<Verbosity::error>("Missing symbol ${f.name} in %s", loadPath.c_str());
        unload${to_pascal_case(config.api_name)}Library();
        return false;
%   endif
    }
%  endfor # standard_functions[group_name]
% endfor # standard_functions
    return true;
}

void unload${to_pascal_case(config.api_name)}Library() {
% for group_name in standard_functions:
%  for f in standard_functions[group_name]:
    ${f.name} = nullptr;
%  endfor # standard_functions[group_name]
% endfor # standard_functions
    if(libraryHandle){
        dlclose(libraryHandle);
    }
    libraryHandle = nullptr;
}

bool is${to_pascal_case(config.api_name)}LibraryLoaded() {
    return nullptr != libraryHandle;
}
% else : # not config.parent_config
extern void *libraryHandle;
% endif

} // namespace Standard

% if extensions:
namespace Extensions {
namespace LazyLoad {
%  for group_name in extensions:
%   for ext in extensions[group_name]:
${ext.returns.type.str} ${ext.name}Load(${ext.get_args_list_str()}){
    using ExtFuncT = decltype(${ext.name}Load);
    static ExtFuncT *extAddr = reinterpret_cast<ExtFuncT*>(${ext_loader}("${ext.name}"));
    if(nullptr == extAddr){
        log<Verbosity::error>("Client requested for unavailable extension function rpc : ${ext.name}");
        assert(false);
        return {};
    }
    ${daemon_namespace_str}::Extensions::${ext.name} = extAddr;
    return extAddr(${ext.get_call_params_list_str()});
}
%   endfor # extensions[group_name]
%  endfor # extensions
} // namespace Lazy Load
%  for group_name in extensions:
%   for ext in extensions[group_name]:
${ext.returns.type.str} (*${ext.name})(${ext.get_args_list_str()}) = ${daemon_namespace_str}::Extensions::LazyLoad::${ext.name}Load;
%   endfor # extensions[group_name]
%  endfor # extensions
} // namespace Extensions
% endif

% for namespace_part in reversed(daemon_namespace):
} // namespace ${namespace_part}
%endfor
// #### Generated code -- end ####
