/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "client/icd/level_zero/logic/struct_traits.h"
#include "level_zero/ze_api.h"

#include <cstring>
#include <tuple>
#include <vector>

namespace Cal::Client::Icd::LevelZero::Logic::PropertiesCache {

template <typename... Ts>
using VectorTuple = std::tuple<std::vector<Ts>...>;

template <typename T, typename L0Obj>
constexpr auto &getProperties(L0Obj *obj) {
    return std::get<std::vector<T>>(obj->properties);
}

inline uint32_t defaultPropertiesCount = 1u;

template <typename L0Obj, typename T, typename F>
ze_result_t obtainProperties(L0Obj *obj, T *properties, F &&rpcHelper) {
    if (properties == nullptr) {
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;
    }

    if constexpr (HasPNext<T>::value) {
        if (properties->pNext) {
            return rpcHelper(obj, properties);
        }
    }
    ze_result_t ret = ZE_RESULT_SUCCESS;
    auto &internalProperties = getProperties<T>(obj);
    if (internalProperties.empty()) {
        ret = rpcHelper(obj, properties);
        internalProperties.resize(obj->template getPropertiesCount<T>());
        memcpy(internalProperties.data(), properties, sizeof(T) * obj->template getPropertiesCount<T>());
    } else {
        memcpy(properties, internalProperties.data(), sizeof(T) * obj->template getPropertiesCount<T>());
    }
    return ret;
}

template <typename L0Obj, typename T, typename F>
ze_result_t obtainProperties(L0Obj *obj, uint32_t *pCount, T *properties, F &&rpcHelper) {
    if constexpr (HasPNext<T>::value) {
        if (properties && properties->pNext) {
            return rpcHelper(obj, pCount, properties);
        }
    }
    ze_result_t ret = ZE_RESULT_SUCCESS;
    if (*pCount == 0u) {
        auto &internalPropertiesCount = obj->template getPropertiesCount<T>();
        if (internalPropertiesCount == 0u) {
            ret = rpcHelper(obj, pCount, properties);
            internalPropertiesCount = *pCount;
        } else {
            *pCount = internalPropertiesCount;
        }
    } else {
        ret = obtainProperties(obj, properties, [&rpcHelper, &pCount](L0Obj *hObj, T *properties) {
            return rpcHelper(hObj, pCount, properties);
        });
    }
    return ret;
}

} // namespace Cal::Client::Icd::LevelZero::Logic::PropertiesCache
