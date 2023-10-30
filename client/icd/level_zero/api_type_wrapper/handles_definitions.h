/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "client/icd/level_zero/api_type_wrapper/wrapper_base.h"
#include "level_zero/ze_api.h"

namespace Cal::Icd::LevelZero {

class IcdL0Platform;
class IcdL0Module;
class IcdL0CommandList;
class IcdL0Device;
class IcdL0CommandQueue;
class IcdL0Fence;
struct IcdL0Context;
struct IcdL0ModuleBuildLog;
struct IcdL0Kernel;
struct IcdL0EventPool;
struct IcdL0Event;
struct IcdL0Image;

} // namespace Cal::Icd::LevelZero

struct _ze_driver_handle_t : Cal::Icd::LevelZero::IcdMappedTypeWrapper<Cal::Icd::LevelZero::IcdL0Platform> {};
struct _ze_device_handle_t : Cal::Icd::LevelZero::IcdMappedTypeWrapper<Cal::Icd::LevelZero::IcdL0Device> {};
struct _ze_context_handle_t : Cal::Icd::LevelZero::IcdMappedTypeWrapper<Cal::Icd::LevelZero::IcdL0Context> {};
struct _ze_command_queue_handle_t : Cal::Icd::LevelZero::IcdMappedTypeWrapper<Cal::Icd::LevelZero::IcdL0CommandQueue> {};
struct _ze_command_list_handle_t : Cal::Icd::LevelZero::IcdMappedTypeWrapper<Cal::Icd::LevelZero::IcdL0CommandList> {};
struct _ze_module_handle_t : Cal::Icd::LevelZero::IcdMappedTypeWrapper<Cal::Icd::LevelZero::IcdL0Module> {};
struct _ze_module_build_log_handle_t : Cal::Icd::LevelZero::IcdMappedTypeWrapper<Cal::Icd::LevelZero::IcdL0ModuleBuildLog> {};
struct _ze_kernel_handle_t : Cal::Icd::LevelZero::IcdMappedTypeWrapper<Cal::Icd::LevelZero::IcdL0Kernel> {};
struct _ze_event_pool_handle_t : Cal::Icd::LevelZero::IcdMappedTypeWrapper<Cal::Icd::LevelZero::IcdL0EventPool> {};
struct _ze_event_handle_t : Cal::Icd::LevelZero::IcdMappedTypeWrapper<Cal::Icd::LevelZero::IcdL0Event> {};
struct _ze_fence_handle_t : Cal::Icd::LevelZero::IcdMappedTypeWrapper<Cal::Icd::LevelZero::IcdL0Fence> {};
struct _ze_image_handle_t : Cal::Icd::LevelZero::IcdMappedTypeWrapper<Cal::Icd::LevelZero::IcdL0Image> {};
