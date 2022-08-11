##
## Copyright (C) 2022 Intel Corporation
##
## SPDX-License-Identifier: MIT
##
// #### Generated code -- begin ####
% for header in file_headers:
${header}
% endfor
#include "shared/utils.h"

% for namespace_part in rpc_namespace:
namespace ${namespace_part} {
% endfor

using namespace Cal::Utils;

% for func in config.functions:
%  if not should_skip_message_generation(func):
%   if func.capture_layout.emit_dynamic_traits:
${func.capture_layout.generate_cpp()}
%   endif # func.capture_layout.emit_dynamic_traits
%  endif # not should_skip_message_generation(func):
% endfor # config.functions:
% for namespace_part in reversed(rpc_namespace):
} // namespace ${namespace_part}
%endfor
// #### Generated code -- end ####
