/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

int setAlarm(bool enableAlarm);

int setSegv(bool enableSegv);

int setAbrt(bool enableAbrt);

int enableSignals(bool enableAlarm, bool enableSegv, bool enableAbrt);
