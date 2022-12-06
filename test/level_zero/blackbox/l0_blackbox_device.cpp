/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#define FULL_VERBOSITY_IN_RELEASE_BUILD 1
#define ENABLE_BLOATED_VERBOSITY 1

#include "cal.h"
#include "level_zero/ze_api.h"
#include "shared/log.h"
#include "test/utils/assertions.h"
#include "test/utils/l0_common_steps.h"

#include <cstdint>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>

bool getDeviceStatus(ze_device_handle_t device) {
    const auto deviceStatus = zeDeviceGetStatus(device);
    if (deviceStatus == ZE_RESULT_SUCCESS) {
        log<Verbosity::info>("Device status is OK!");
    } else if (deviceStatus == ZE_RESULT_ERROR_UNSUPPORTED_FEATURE) {
        log<Verbosity::info>("Checking device status is not supported!");
    } else {
        log<Verbosity::error>("zeDeviceStatusGet() call indicates, that device cannot be used! Error code = %d", static_cast<int>(deviceStatus));
        return false;
    }

    return true;
}

bool getDeviceProperties(ze_device_handle_t device) {
    ze_device_properties_t deviceProperties = {ZE_STRUCTURE_TYPE_DEVICE_PROPERTIES};

    const auto zeDeviceGetPropertiesResult = zeDeviceGetProperties(device, &deviceProperties);
    if (zeDeviceGetPropertiesResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeDeviceGetProperties() call has failed! Error code = %d", static_cast<int>(zeDeviceGetPropertiesResult));
        return false;
    }

    std::stringstream ss;
    ss << "Device properties: \n"
       << " * name : " << deviceProperties.name << "\n"
       << " * deviceId : " << deviceProperties.deviceId << "\n"
       << " * numSlices : " << deviceProperties.numSlices << "\n"
       << " * numSubslicesPerSlice : " << deviceProperties.numSubslicesPerSlice << "\n"
       << " * numEUsPerSubslice : " << deviceProperties.numEUsPerSubslice << "\n"
       << " * numThreadsPerEU : " << deviceProperties.numThreadsPerEU;

    const auto deviceInfoStr = ss.str();
    log<Verbosity::info>("%s", deviceInfoStr.c_str());

    return true;
}

bool getDeviceComputeProperties(ze_device_handle_t device) {
    ze_device_compute_properties_t computeProperties = {ZE_STRUCTURE_TYPE_DEVICE_COMPUTE_PROPERTIES};

    const auto zeDeviceGetComputePropertiesResult = zeDeviceGetComputeProperties(device, &computeProperties);
    if (zeDeviceGetComputePropertiesResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeDeviceGetComputeProperties() call has failed! Error code = %d", static_cast<int>(zeDeviceGetComputePropertiesResult));
        return false;
    }

    std::stringstream ss;
    ss << "Device compute properties : \n"
       << " * maxTotalGroupSize : " << computeProperties.maxTotalGroupSize << "\n"
       << " * maxGroupSizeX :  " << computeProperties.maxGroupSizeX << "\n"
       << " * maxGroupSizeY :  " << computeProperties.maxGroupSizeY << "\n"
       << " * maxGroupSizeZ :  " << computeProperties.maxGroupSizeZ << "\n"
       << " * maxGroupCountX :  " << computeProperties.maxGroupCountX << "\n"
       << " * maxGroupCountY :  " << computeProperties.maxGroupCountY << "\n"
       << " * maxGroupCountZ :  " << computeProperties.maxGroupCountZ << "\n"
       << " * maxSharedLocalMemory : " << computeProperties.maxSharedLocalMemory << "\n"
       << " * numSubGroupSizes : " << computeProperties.numSubGroupSizes << "\n";

    for (auto i = 0u; i < computeProperties.numSubGroupSizes; ++i) {
        ss << " * subGroupSizes[" << i << "] : " << computeProperties.subGroupSizes[i] << "\n";
    }

    const auto computeInfoStr = ss.str();
    log<Verbosity::info>("%s", computeInfoStr.c_str());

    return true;
}

bool getDevicePciPropertiesExt(ze_device_handle_t device) {
    ze_pci_ext_properties_t properties = {ZE_STRUCTURE_TYPE_PCI_EXT_PROPERTIES};

    const auto zeDevicePciGetPropertiesExtResult = zeDevicePciGetPropertiesExt(device, &properties);
    if (ZE_RESULT_SUCCESS != zeDevicePciGetPropertiesExtResult) {
        log<Verbosity::error>("zeDevicePciGetPropertiesExt failed! Error code = %d", static_cast<int>(zeDevicePciGetPropertiesExtResult));
        return false;
    }

    std::stringstream ss;
    ss << "Pci properties : \n"
       << " * address : \n"
       << "     - domain : " << properties.address.domain << "\n"
       << "     - bus : " << properties.address.bus << "\n"
       << "     - device : " << properties.address.device << "\n"
       << "     - function : " << properties.address.function << "\n"
       << " * maxSpeed : \n"
       << "     - genVersion : " << properties.maxSpeed.genVersion << "\n"
       << "     - width : " << properties.maxSpeed.width << "\n"
       << "     - maxBandwidth : " << properties.maxSpeed.maxBandwidth;

    const auto pciInfoStr = ss.str();
    log<Verbosity::info>("%s", pciInfoStr.c_str());

    return true;
}

bool getDeviceModuleProperties(ze_device_handle_t device) {
    ze_float_atomic_ext_properties_t floatProperties = {ZE_STRUCTURE_TYPE_FLOAT_ATOMIC_EXT_PROPERTIES};
    floatProperties.pNext = nullptr;

    ze_device_module_properties_t moduleProperties = {ZE_STRUCTURE_TYPE_DEVICE_MODULE_PROPERTIES};
    moduleProperties.pNext = &floatProperties;

    const auto zeDeviceGetModulePropertiesResult = zeDeviceGetModuleProperties(device, &moduleProperties);
    if (zeDeviceGetModulePropertiesResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeDeviceGetModuleProperties() call has failed! Error code = %d", static_cast<int>(zeDeviceGetModulePropertiesResult));
        return true;
    }

    std::stringstream ss;
    ss << "Module properties : \n"
       << " * spirvVersionSupported : " << moduleProperties.spirvVersionSupported << "\n"
       << " * flags : " << static_cast<int>(moduleProperties.flags) << "\n"
       << " * fp16flags : " << static_cast<int>(moduleProperties.fp16flags) << "\n"
       << " * fp32flags : " << static_cast<int>(moduleProperties.fp32flags) << "\n"
       << " * fp64flags : " << static_cast<int>(moduleProperties.fp64flags) << "\n"
       << " * maxArgumentsSize : " << moduleProperties.maxArgumentsSize << "\n"
       << " * printfBufferSize : " << moduleProperties.printfBufferSize << "\n\n"
       << "Float atomic exp properties : \n"
       << " * fp16Flags : " << floatProperties.fp16Flags << "\n"
       << " * fp32Flags : " << floatProperties.fp32Flags << "\n"
       << " * fp64Flags : " << floatProperties.fp64Flags;

    const auto moduleInfoStr = ss.str();
    log<Verbosity::info>("%s", moduleInfoStr.c_str());

    return true;
}

bool getDeviceImageProperties(ze_device_handle_t device) {
    ze_device_image_properties_t imageProperties = {ZE_STRUCTURE_TYPE_DEVICE_IMAGE_PROPERTIES};

    const auto zeDeviceGetImagePropertiesResult = zeDeviceGetImageProperties(device, &imageProperties);
    if (zeDeviceGetImagePropertiesResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeDeviceGetImageProperties() call has failed! Error code = %d", static_cast<int>(zeDeviceGetImagePropertiesResult));
        return false;
    }

    std::stringstream ss;
    ss << "Image properties : \n"
       << " * maxImageDims1D : " << imageProperties.maxImageDims1D << "\n"
       << " * maxImageDims2D : " << imageProperties.maxImageDims2D << "\n"
       << " * maxImageDims3D : " << imageProperties.maxImageDims3D << "\n"
       << " * maxImageBufferSize : " << imageProperties.maxImageBufferSize << "\n"
       << " * maxImageArraySlices : " << imageProperties.maxImageArraySlices << "\n"
       << " * maxSamplers : " << imageProperties.maxSamplers << "\n"
       << " * maxReadImageArgs : " << imageProperties.maxReadImageArgs << "\n"
       << " * maxWriteImageArgs : " << imageProperties.maxWriteImageArgs;

    const auto imageInfoStr = ss.str();
    log<Verbosity::info>("%s", imageInfoStr.c_str());

    return true;
}

bool getDeviceExternalMemoryProperties(ze_device_handle_t device) {
    ze_device_external_memory_properties_t externalMemoryProperties = {ZE_STRUCTURE_TYPE_DEVICE_EXTERNAL_MEMORY_PROPERTIES};

    const auto zeDeviceGetExternalMemoryPropertiesResult = zeDeviceGetExternalMemoryProperties(device, &externalMemoryProperties);
    if (zeDeviceGetExternalMemoryPropertiesResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeDeviceGetExternalMemoryProperties() call has failed! Error code = %d", static_cast<int>(zeDeviceGetExternalMemoryPropertiesResult));
        return false;
    }

    std::stringstream ss;
    ss << "External memory properties : \n"
       << " * memoryAllocationImportTypes : " << static_cast<int>(externalMemoryProperties.memoryAllocationImportTypes) << "\n"
       << " * memoryAllocationExportTypes : " << static_cast<int>(externalMemoryProperties.memoryAllocationExportTypes) << "\n"
       << " * imageImportTypes : " << static_cast<int>(externalMemoryProperties.imageImportTypes) << "\n"
       << " * imageExportTypes : " << static_cast<int>(externalMemoryProperties.imageExportTypes);

    const auto externalMemoryInfoStr = ss.str();
    log<Verbosity::info>("%s", externalMemoryInfoStr.c_str());

    return true;
}

bool getDeviceMemoryAccessProperties(ze_device_handle_t device) {
    ze_device_memory_access_properties_t memoryAccessProperties = {ZE_STRUCTURE_TYPE_DEVICE_MEMORY_ACCESS_PROPERTIES};

    const auto zeDeviceGetMemoryAccessPropertiesResult = zeDeviceGetMemoryAccessProperties(device, &memoryAccessProperties);
    if (zeDeviceGetMemoryAccessPropertiesResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeDeviceGetMemoryAccessProperties() call has failed! Error code = %d", static_cast<int>(zeDeviceGetMemoryAccessPropertiesResult));
        return false;
    }

    std::stringstream ss;
    ss << "Memory access properties : \n"
       << " * hostAllocCapabilities : " << static_cast<int>(memoryAccessProperties.hostAllocCapabilities) << "\n"
       << " * deviceAllocCapabilities : " << static_cast<int>(memoryAccessProperties.deviceAllocCapabilities) << "\n"
       << " * sharedSingleDeviceAllocCapabilities : " << static_cast<int>(memoryAccessProperties.sharedSingleDeviceAllocCapabilities) << "\n"
       << " * sharedCrossDeviceAllocCapabilities : " << static_cast<int>(memoryAccessProperties.sharedCrossDeviceAllocCapabilities) << "\n"
       << " * sharedSystemAllocCapabilities : " << static_cast<int>(memoryAccessProperties.sharedSystemAllocCapabilities);

    const auto memoryAccessInfoStr = ss.str();
    log<Verbosity::info>("%s", memoryAccessInfoStr.c_str());

    return true;
}

bool getDeviceMemoryProperties(ze_device_handle_t device) {
    uint32_t memoryPropertiesCount{0};

    auto zeDeviceGetMemoryPropertiesResult = zeDeviceGetMemoryProperties(device, &memoryPropertiesCount, nullptr);
    if (zeDeviceGetMemoryPropertiesResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeDeviceGetMemoryProperties() call has failed! Error code = %d", static_cast<int>(zeDeviceGetMemoryPropertiesResult));
        return false;
    }

    log<Verbosity::info>("Number of memory properties: %d!", static_cast<int>(memoryPropertiesCount));
    if (memoryPropertiesCount == 0) {
        return true;
    }

    log<Verbosity::info>("Reading memory properties via zeDeviceGetMemoryProperties()!");

    std::vector<ze_device_memory_properties_t> memoryProperties(memoryPropertiesCount);
    std::vector<ze_device_memory_ext_properties_t> memoryExtProperties(memoryPropertiesCount);

    for (auto i = 0u; i < memoryPropertiesCount; ++i) {
        memoryProperties[i].stype = ZE_STRUCTURE_TYPE_DEVICE_MEMORY_PROPERTIES;
        memoryProperties[i].pNext = &memoryExtProperties[i];

        memoryExtProperties[i].stype = ZE_STRUCTURE_TYPE_DEVICE_MEMORY_EXT_PROPERTIES;
        memoryExtProperties[i].pNext = nullptr;
    }

    zeDeviceGetMemoryPropertiesResult = zeDeviceGetMemoryProperties(device, &memoryPropertiesCount, memoryProperties.data());
    if (zeDeviceGetMemoryPropertiesResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeDeviceGetMemoryProperties() call has failed! Error code = %d", static_cast<int>(zeDeviceGetMemoryPropertiesResult));
        return false;
    }

    std::stringstream ss;
    for (auto i = 0u; i < memoryPropertiesCount; ++i) {
        const auto &memoryProperty = memoryProperties[i];

        ss.str("");
        ss << "Memory properties[" << i << "] : \n"
           << " * flags : " << memoryProperty.flags << "\n"
           << " * maxClockRate : " << memoryProperty.maxClockRate << "\n"
           << " * maxBusWidth : " << memoryProperty.maxBusWidth << "\n"
           << " * totalSize : " << memoryProperty.totalSize << "\n"
           << " * name : ";

        for (const auto c : memoryProperty.name) {
            if (c == '\0') {
                break;
            }

            ss << c;
        }

        ss << "\n"
           << "ze_device_memory_ext_properties_t[" << i << "] : \n"
           << " * type : " << static_cast<int>(memoryExtProperties[i].type) << "\n"
           << " * physicalSize : " << memoryExtProperties[i].physicalSize << "\n"
           << " * readBandwidth : " << memoryExtProperties[i].readBandwidth << "\n"
           << " * writeBandwidth : " << memoryExtProperties[i].writeBandwidth << "\n"
           << " * bandwidthUnit : " << static_cast<int>(memoryExtProperties[i].bandwidthUnit);

        const auto memoryPropertyInfoStr = ss.str();
        log<Verbosity::info>("%s", memoryPropertyInfoStr.c_str());
    }

    return true;
}

bool getDeviceCacheProperties(ze_device_handle_t device) {
    uint32_t cachePropertiesCount{0};

    auto zeDeviceGetCachePropertiesResult = zeDeviceGetCacheProperties(device, &cachePropertiesCount, nullptr);
    if (zeDeviceGetCachePropertiesResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeDeviceGetCachePropertiesResult() call has failed! Error code = %d", static_cast<int>(zeDeviceGetCachePropertiesResult));
        return false;
    }

    log<Verbosity::info>("Number of cache properties: %d!", static_cast<int>(cachePropertiesCount));
    if (cachePropertiesCount == 0) {
        return true;
    }

    log<Verbosity::info>("Reading cache properties via zeDeviceGetCacheProperties()!");

    std::vector<ze_device_cache_properties_t> cacheProperties;
    cacheProperties.resize(cachePropertiesCount);

    for (auto &cacheProperty : cacheProperties) {
        cacheProperty.stype = ZE_STRUCTURE_TYPE_DEVICE_CACHE_PROPERTIES;
    }

    zeDeviceGetCachePropertiesResult = zeDeviceGetCacheProperties(device, &cachePropertiesCount, cacheProperties.data());
    if (zeDeviceGetCachePropertiesResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeDeviceGetCachePropertiesResult() call has failed! Error code = %d", static_cast<int>(zeDeviceGetCachePropertiesResult));
        return false;
    }

    std::stringstream ss;
    for (auto i = 0u; i < cacheProperties.size(); ++i) {
        const auto &cacheProperty = cacheProperties[i];

        ss.str("");
        ss << "Cache properties[" << i << "] : \n"
           << " * flags : " << static_cast<int>(cacheProperty.flags) << "\n"
           << " * cacheSize : " << cacheProperty.cacheSize;

        const auto cacheInfoStr = ss.str();
        log<Verbosity::info>("%s", cacheInfoStr.c_str());
    }

    return true;
}

bool checkAccessToOwnAllocations(ze_device_handle_t device) {
    log<Verbosity::info>("Checking if device can access it's own allocations via zeDeviceCanAccessPeer");

    ze_bool_t peerAccess = false;

    const auto zeDeviceCanAccessPeerResult = zeDeviceCanAccessPeer(device, device, &peerAccess);
    if (zeDeviceCanAccessPeerResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeDeviceCanAccessPeer() call has failed! Error code = %d", static_cast<int>(zeDeviceCanAccessPeerResult));
        return false;
    }

    log<Verbosity::info>("Result of zeDeviceCanAccessPeer is: %s", peerAccess ? "true" : "false");
    return true;
}

bool gatherSynchronizedHostAndGpuTimestamps(ze_device_handle_t device) {
    uint64_t hostTs, deviceTs;
    auto zeDeviceGetGlobalTimestampsResult = zeDeviceGetGlobalTimestamps(device, &hostTs, &deviceTs);
    if (zeDeviceGetGlobalTimestampsResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeDeviceGetGlobalTimestamp() call has failed! Error code = %d", static_cast<int>(zeDeviceGetGlobalTimestampsResult));
        return false;
    }

    log<Verbosity::info>("Global Timestamps returned: hostTs: %lx, DeviceTs: %lx", hostTs, deviceTs);
    return true;
}

bool getDeviceCommandQueueGroupProperties(ze_device_handle_t device) {
    uint32_t queueGroupPropertiesCount{0};

    auto zeDeviceGetCommandQueueGroupPropertiesResult = zeDeviceGetCommandQueueGroupProperties(device, &queueGroupPropertiesCount, nullptr);
    if (zeDeviceGetCommandQueueGroupPropertiesResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeDeviceGetCommandQueueGroupProperties() call has failed! Error code = %d", static_cast<int>(zeDeviceGetCommandQueueGroupPropertiesResult));
        return false;
    }

    log<Verbosity::info>("Number of command queue group properties: %d!", static_cast<int>(queueGroupPropertiesCount));
    if (queueGroupPropertiesCount == 0) {
        return true;
    }

    log<Verbosity::info>("Reading command queue group properties via zeDeviceGetCommandQueueGroupProperties()!");
    std::vector<ze_command_queue_group_properties_t> queueGroupProperties{};
    queueGroupProperties.resize(queueGroupPropertiesCount);

    for (auto &queueGroupProperty : queueGroupProperties) {
        queueGroupProperty.stype = ZE_STRUCTURE_TYPE_COMMAND_QUEUE_GROUP_PROPERTIES;
    }

    zeDeviceGetCommandQueueGroupPropertiesResult = zeDeviceGetCommandQueueGroupProperties(device, &queueGroupPropertiesCount, queueGroupProperties.data());
    if (zeDeviceGetCommandQueueGroupPropertiesResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeDeviceGetCommandQueueGroupProperties() call has failed! Error code = %d", static_cast<int>(zeDeviceGetCommandQueueGroupPropertiesResult));
        return false;
    }

    std::stringstream ss;
    for (const auto &queueGroupProperty : queueGroupProperties) {
        ss.str("");
        ss << "Queue group properties : \n"
           << " * flags : " << static_cast<int>(queueGroupProperty.flags) << "\n"
           << " * maxMemoryFillPatternSize : " << queueGroupProperty.maxMemoryFillPatternSize << "\n"
           << " * numQueues : " << queueGroupProperty.numQueues;

        const auto queueGroupInfoStr = ss.str();
        log<Verbosity::info>("%s", queueGroupInfoStr.c_str());
    }

    return true;
}

bool getSubDevices(ze_device_handle_t device, std::vector<ze_device_handle_t> &subdevices) {
    uint32_t numSubDevices{0};

    auto zeDeviceGetSubDevicesResult = zeDeviceGetSubDevices(device, &numSubDevices, nullptr);
    if (zeDeviceGetSubDevicesResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeDeviceGetSubDevices() call has failed! Error code = %d", static_cast<int>(zeDeviceGetSubDevicesResult));
        return false;
    }

    log<Verbosity::info>("Number of subdevices: %d!", static_cast<int>(numSubDevices));
    if (numSubDevices == 0) {
        return true;
    }

    log<Verbosity::info>("Reading subdevices via zeDeviceGetSubDevices()!");
    subdevices.resize(numSubDevices);

    zeDeviceGetSubDevicesResult = zeDeviceGetSubDevices(device, &numSubDevices, subdevices.data());
    if (zeDeviceGetSubDevicesResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeDeviceGetSubDevices() call has failed! Error code = %d", static_cast<int>(zeDeviceGetSubDevicesResult));
        return false;
    }

    return true;
}

bool getOwnP2PProperties(ze_device_handle_t device) {
    log<Verbosity::info>("Getting own P2P properties of device = %p", static_cast<void *>(device));

    ze_device_p2p_bandwidth_exp_properties_t bandwidthProperties{ZE_STRUCTURE_TYPE_DEVICE_P2P_BANDWIDTH_EXP_PROPERTIES};
    ze_device_p2p_properties_t p2pProperties{ZE_STRUCTURE_TYPE_DEVICE_P2P_PROPERTIES, &bandwidthProperties};

    const auto zeDeviceGetP2PPropertiesResult = zeDeviceGetP2PProperties(device, device, &p2pProperties);
    if (zeDeviceGetP2PPropertiesResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeDeviceGetP2PProperties() call has failed! Error code = %d", static_cast<int>(zeDeviceGetP2PPropertiesResult));
        return false;
    }

    log<Verbosity::info>("ze_device_p2p_property_flags_t = %d", static_cast<int>(p2pProperties.flags));

    std::stringstream ss;
    ss << "ze_device_p2p_bandwidth_exp_properties_t : \n"
       << " * logicalBandwidth : " << bandwidthProperties.logicalBandwidth << "\n"
       << " * physicalBandwidth : " << bandwidthProperties.physicalBandwidth << "\n"
       << " * bandwidthUnit : " << static_cast<int>(bandwidthProperties.bandwidthUnit) << "\n"
       << " * logicalLatency : " << bandwidthProperties.logicalLatency << "\n"
       << " * physicalLatency : " << bandwidthProperties.physicalLatency << "\n"
       << " * latencyUnit : " << static_cast<int>(bandwidthProperties.latencyUnit);

    const auto bandwidthPropertiesStr = ss.str();
    log<Verbosity::info>("%s", bandwidthPropertiesStr.c_str());

    return true;
}

bool parseAllowOptionalSteps(int argc, const char **argv) {
    for (int i = 0; i < argc; ++i) {
        if (0 == strcmp(argv[i], "--allow-optional-steps")) {
            return true;
        }
    }

    return false;
}

int main(int argc, const char *argv[]) {
    using Cal::Testing::Utils::LevelZero::getDevices;
    using Cal::Testing::Utils::LevelZero::getDrivers;
    using Cal::Testing::Utils::LevelZero::initL0;

    Cal::Utils::initMaxDynamicVerbosity(Verbosity::debug);

    const auto allowOptionalSteps = parseAllowOptionalSteps(argc, argv);
    std::vector<ze_driver_handle_t> drivers{};
    std::vector<ze_device_handle_t> devices{};

    RUN_REQUIRED_STEP(initL0());
    RUN_REQUIRED_STEP(getDrivers(drivers));
    RUN_REQUIRED_STEP(getDevices(drivers[0], devices));

    RUN_STEPS_FOREACH(deviceIndex, devices.size(), [&] {
        RUN_REQUIRED_STEP(getDeviceStatus(devices[deviceIndex]));
        RUN_REQUIRED_STEP(getDeviceProperties(devices[deviceIndex]));
        RUN_REQUIRED_STEP(getDeviceComputeProperties(devices[deviceIndex]));
        RUN_REQUIRED_STEP(getDeviceModuleProperties(devices[deviceIndex]));
        RUN_REQUIRED_STEP(getDeviceImageProperties(devices[deviceIndex]));
        RUN_REQUIRED_STEP(getDeviceExternalMemoryProperties(devices[deviceIndex]));
        RUN_REQUIRED_STEP(getDeviceMemoryAccessProperties(devices[deviceIndex]));
        RUN_REQUIRED_STEP(getDeviceMemoryProperties(devices[deviceIndex]));
        RUN_REQUIRED_STEP(getDeviceCacheProperties(devices[deviceIndex]));
        RUN_REQUIRED_STEP(getDeviceCommandQueueGroupProperties(devices[deviceIndex]));
        RUN_REQUIRED_STEP(checkAccessToOwnAllocations(devices[deviceIndex]));
        RUN_REQUIRED_STEP(getOwnP2PProperties(devices[deviceIndex]));

        if (allowOptionalSteps) {
            RUN_OPTIONAL_STEP(getDevicePciPropertiesExt(devices[deviceIndex]));
            RUN_OPTIONAL_STEP(gatherSynchronizedHostAndGpuTimestamps(devices[deviceIndex]));
        } else {
            RUN_REQUIRED_STEP(getDevicePciPropertiesExt(devices[deviceIndex]));
            RUN_REQUIRED_STEP(gatherSynchronizedHostAndGpuTimestamps(devices[deviceIndex]));
        }

        std::vector<ze_device_handle_t> subdevices{};
        RUN_REQUIRED_STEP(getSubDevices(devices[deviceIndex], subdevices));

        RUN_STEPS_FOREACH(subdeviceIndex, subdevices.size(), [&] {
            RUN_REQUIRED_STEP(getDeviceProperties(subdevices[subdeviceIndex]));
            FINISH_ITERATION;
        });

        FINISH_ITERATION;
    });

    return 0;
}
