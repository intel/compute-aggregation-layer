/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include <iostream>

#define RUN_REQUIRED_STEP(step)                                                                       \
    std::cout << "================= Running required step: " #step " =================" << std::endl; \
    if (!step) {                                                                                      \
        std::cout << "================= Required step: " #step " failed! =================\n"         \
                  << std::endl;                                                                       \
        return -1;                                                                                    \
    }                                                                                                 \
    std::cout << "================= Required step: " #step " run successfuly! =================\n"    \
              << std::endl;

#define RUN_OPTIONAL_STEP(step)                                                                        \
    std::cout << "================= Running optional step: " #step " =================" << std::endl;  \
    if (!step) {                                                                                       \
        std::cout << "================= Optional step: " #step " failed! =================\n"          \
                  << std::endl;                                                                        \
    } else {                                                                                           \
        std::cout << "================= Optional step: " #step " run successfuly! =================\n" \
                  << std::endl;                                                                        \
    }

#define RUN_STEPS_FOREACH(indexVariable, maxCount, steps)                                                                                   \
    for (auto indexVariable = 0u; indexVariable < maxCount; ++indexVariable) {                                                              \
        std::cout << "================= Running sub-steps for " #indexVariable " = " << indexVariable << " =================\n"             \
                  << std::endl;                                                                                                             \
        if (steps() != 0) {                                                                                                                 \
            std::cout << "================= Execution of steps failed for " #indexVariable " = " << indexVariable << " =================\n" \
                      << std::endl;                                                                                                         \
            return -1;                                                                                                                      \
        }                                                                                                                                   \
        std::cout << "================= Finished sub-steps for " #indexVariable " = " << indexVariable << " =================\n"            \
                  << std::endl;                                                                                                             \
    }

#define FINISH_ITERATION return 0
