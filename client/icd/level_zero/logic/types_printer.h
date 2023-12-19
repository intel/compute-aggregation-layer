/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "client/icd/level_zero/api_type_wrapper/handles_definitions.h"
#include "client/icd/level_zero/logic/struct_traits.h"

#include <type_traits>

namespace Cal::Client::Icd::LevelZero::Logic {

struct IcdL0TypePrinter {
    template <typename T>
    static const char *getObjectTypeAsStr() {
        if constexpr (std::is_same_v<T, ze_driver_handle_t>) {
            return "ze_driver_handle_t";
        } else if constexpr (std::is_same_v<T, _ze_driver_handle_t>) {
            return "_ze_driver_handle_t";
        } else if constexpr (std::is_same_v<T, ze_device_handle_t>) {
            return "ze_device_handle_t";
        } else if constexpr (std::is_same_v<T, _ze_device_handle_t>) {
            return "_ze_device_handle_t";
        } else if constexpr (std::is_same_v<T, ze_context_handle_t>) {
            return "ze_context_handle_t";
        } else if constexpr (std::is_same_v<T, _ze_context_handle_t>) {
            return "_ze_context_handle_t";
        } else if constexpr (std::is_same_v<T, ze_command_queue_handle_t>) {
            return "ze_command_queue_handle_t";
        } else if constexpr (std::is_same_v<T, _ze_command_queue_handle_t>) {
            return "_ze_command_queue_handle_t";
        } else if constexpr (std::is_same_v<T, ze_command_list_handle_t>) {
            return "ze_command_list_handle_t";
        } else if constexpr (std::is_same_v<T, _ze_command_list_handle_t>) {
            return "_ze_command_list_handle_t";
        } else if constexpr (std::is_same_v<T, ze_module_handle_t>) {
            return "ze_module_handle_t";
        } else if constexpr (std::is_same_v<T, _ze_module_handle_t>) {
            return "_ze_module_handle_t";
        } else if constexpr (std::is_same_v<T, ze_module_build_log_handle_t>) {
            return "ze_module_build_log_handle_t";
        } else if constexpr (std::is_same_v<T, _ze_module_build_log_handle_t>) {
            return "_ze_module_build_log_handle_t";
        } else if constexpr (std::is_same_v<T, ze_kernel_handle_t>) {
            return "ze_kernel_handle_t";
        } else if constexpr (std::is_same_v<T, _ze_kernel_handle_t>) {
            return "_ze_kernel_handle_t";
        } else if constexpr (std::is_same_v<T, ze_event_pool_handle_t>) {
            return "ze_event_pool_handle_t";
        } else if constexpr (std::is_same_v<T, _ze_event_pool_handle_t>) {
            return "_ze_event_pool_handle_t";
        } else if constexpr (std::is_same_v<T, ze_event_handle_t>) {
            return "ze_event_handle_t";
        } else if constexpr (std::is_same_v<T, _ze_event_handle_t>) {
            return "_ze_event_handle_t";
        } else if constexpr (std::is_same_v<T, ze_fence_handle_t>) {
            return "ze_fence_handle_t";
        } else if constexpr (std::is_same_v<T, _ze_fence_handle_t>) {
            return "_ze_fence_handle_t";
        } else if constexpr (std::is_same_v<T, ze_image_handle_t>) {
            return "ze_image_handle_t";
        } else if constexpr (std::is_same_v<T, _ze_image_handle_t>) {
            return "_ze_image_handle_t";
        } else if constexpr (std::is_same_v<T, zet_metric_group_handle_t>) {
            return "zet_metric_group_handle_t";
        } else if constexpr (std::is_same_v<T, _zet_metric_group_handle_t>) {
            return "_zet_metric_group_handle_t";
        } else if constexpr (std::is_same_v<T, zet_metric_handle_t>) {
            return "zet_metric_handle_t";
        } else if constexpr (std::is_same_v<T, _zet_metric_handle_t>) {
            return "_zet_metric_handle_t";
        } else {
            static_assert(AlwaysFalse<T>::value, "Uknown type has been passed! Please insert the code to handle the new type!");
            return "unknown";
        }
    }
};

} // namespace Cal::Client::Icd::LevelZero::Logic
