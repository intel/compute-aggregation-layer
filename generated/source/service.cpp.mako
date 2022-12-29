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
% for f in standard_functions:
${f.returns.type.str} (*${f.name})(${f.get_args_list_str()}) = nullptr;
% endfor

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
    
% for f in standard_functions:
    ${f.name} = reinterpret_cast<decltype(${f.name})>(dlsym(libraryHandle, "${f.name}"));
    if(nullptr == ${f.name}){
%  if f.special_handling and f.special_handling.optional:
        log<Verbosity::debug>("Missing symbol ${f.name} in %s", loadPath.c_str());
%  else : # not (f.special_handling and f.special_handling.optional):
        log<Verbosity::error>("Missing symbol ${f.name} in %s", loadPath.c_str());
        unload${to_pascal_case(config.api_name)}Library();
        return false;
%  endif
    }
% endfor
    return true;
}

void unload${to_pascal_case(config.api_name)}Library() {
% for f in standard_functions:
    ${f.name} = nullptr;
% endfor
    if(libraryHandle){
        dlclose(libraryHandle);
    }
    libraryHandle = nullptr;
}

bool is${to_pascal_case(config.api_name)}LibraryLoaded() {
    return nullptr != libraryHandle;
}

} // namespace Standard

% if extensions:
namespace Extensions {
namespace LazyLoad {
%  for ext in extensions:
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
%  endfor
} // namespace Lazy Load
%  for ext in extensions:
${ext.returns.type.str} (*${ext.name})(${ext.get_args_list_str()}) = ${daemon_namespace_str}::Extensions::LazyLoad::${ext.name}Load;
%  endfor
} // namespace Extensions
% endif

bool isSuccessful(${config.result_type} result) {
    return result == ${config.result_success};
}

% for namespace_part in reversed(daemon_namespace):
} // namespace ${namespace_part}
%endfor
// #### Generated code -- end ####
