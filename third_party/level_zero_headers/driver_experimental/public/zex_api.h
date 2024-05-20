/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#ifndef _ZEX_API_H
#define _ZEX_API_H
#if defined(__cplusplus)
#pragma once
#endif

// 'core' API headers
#include <level_zero/ze_api.h>
// 'sysman' API headers
#include <level_zero/zes_api.h>

// driver experimental API headers
#include "driver_experimental/public/zex_cmdlist.h"

#include "zex_driver.h"
#include "zex_memory.h"
#include "zex_module.h"

#endif // _ZEX_API_H
