/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "icd/level_zero/api_type_wrapper/wrapper_base.h"
#include "icd/level_zero/logic/properties_cache.h"
#include "icd/level_zero/logic/types_printer.h"
#include "level_zero/zes_api.h"
#include "shared/ref_counted.h"

#include <cstdint>
#include <mutex>
#include <type_traits>
#include <vector>

namespace Cal::Icd::LevelZero {

class IcdL0Device : public Cal::Shared::RefCountedWithParent<_ze_device_handle_t, Logic::IcdL0TypePrinter> {
  public:
    using RefCountedWithParent::RefCountedWithParent;

    bool patchDeviceName(ze_device_properties_t &properties);
    void addSubDeviceToFilter(uint32_t subDeviceIndex);
    bool isZeAffinityMaskPresent();
    const std::vector<ze_device_handle_t> &getFilteredDevices() const { return filteredDevices; };

    Logic::PropertiesCache::VectorTuple<ze_device_properties_t,
                                        ze_device_compute_properties_t,
                                        ze_device_module_properties_t,
                                        ze_device_memory_access_properties_t,
                                        ze_device_image_properties_t,
                                        ze_device_external_memory_properties_t,
                                        ze_command_queue_group_properties_t,
                                        ze_device_cache_properties_t,
                                        ze_device_memory_properties_t,
                                        zes_device_properties_t>
        properties;

    struct PropertiesCount {
        uint32_t commandQueueGroupCount = 0;
        uint32_t cacheCount = 0;
        uint32_t memoryCount = 0;
    } propertiesCount;

    template <typename T>
    constexpr uint32_t &getPropertiesCount() {
        if constexpr (std::is_same_v<T, ze_command_queue_group_properties_t>) {
            return this->propertiesCount.commandQueueGroupCount;
        }
        if constexpr (std::is_same_v<T, ze_device_cache_properties_t>) {
            return this->propertiesCount.cacheCount;
        }
        if constexpr (std::is_same_v<T, ze_device_memory_properties_t>) {
            return this->propertiesCount.memoryCount;
        }
        return Logic::PropertiesCache::defaultPropertiesCount;
    }

  private:
    bool zeAffinityMaskPresent = false;
    std::vector<bool> selectedDevices;
    std::vector<ze_device_handle_t> filteredDevices;
    std::once_flag parseZeAffinityMaskOnce;
};
} // namespace Cal::Icd::LevelZero
