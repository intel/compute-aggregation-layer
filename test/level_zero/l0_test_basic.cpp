/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#define FULL_VERBOSITY_IN_RELEASE_BUILD 1
#define ENABLE_BLOATED_VERBOSITY 1
#include "cal.h"
#include "icd/icd_global_state.h"
#include "level_zero/ze_api.h"
#include "shared/log.h"

#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <dlfcn.h>
#include <fstream>
#include <sstream>
#include <string_view>
#include <sys/wait.h>
#include <type_traits>
#include <unistd.h>
#include <vector>

class DynamicLibrary {
  public:
    DynamicLibrary(const DynamicLibrary &lib) = delete;
    DynamicLibrary &operator=(const DynamicLibrary &lib) = delete;

    DynamicLibrary(std::string name)
        : name{std::move(name)} {
        libHandle = dlopen(this->name.c_str(), RTLD_LAZY);
    }

    ~DynamicLibrary() {
        close();
    }

    DynamicLibrary(DynamicLibrary &&other) noexcept
        : libHandle{std::exchange(other.libHandle, nullptr)},
          name{std::move(other.name)} {}

    DynamicLibrary &operator=(DynamicLibrary &&other) noexcept {
        if (this == &other) {
            return *this;
        }

        close();

        libHandle = std::exchange(other.libHandle, nullptr);
        name = std::move(other.name);

        return *this;
    }

    void close() {
        if (libHandle) {
            dlclose(libHandle);
            libHandle = nullptr;
        }
    }

    bool isLoaded() const {
        return libHandle != nullptr;
    }

    template <typename FunctionT>
    auto getFunction(const std::string &symbol) {
        static_assert(std::is_function_v<FunctionT>, "Passed type is not a function!");

        if (!libHandle) {
            return static_cast<std::add_pointer_t<FunctionT>>(nullptr);
        }

        return reinterpret_cast<std::add_pointer_t<FunctionT>>(dlsym(libHandle, symbol.c_str()));
    }

  private:
    void *libHandle{nullptr};
    std::string name{};
};

bool testZeDevicePciGetProperiesExt(ze_device_handle_t device) {
    ze_pci_ext_properties_t properties = {ZE_STRUCTURE_TYPE_PCI_EXT_PROPERTIES};

    log<Verbosity::info>("Querying PCI properties using zeDevicePciGetPropertiesExt");
    auto ret = zeDevicePciGetPropertiesExt(device, &properties);
    if (ZE_RESULT_SUCCESS != ret) {
        log<Verbosity::error>("zeDevicePciGetPropertiesExt failed");
        return false;
    }
    log<Verbosity::info>("zeDevicePciGetPropertiesExt succeeded");
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
       << "     - maxBandwidth : " << properties.maxSpeed.maxBandwidth << "\n";

    log<Verbosity::info>("%s", ss.str().c_str());
    return true;
}

int main(int argc, const char *argv[]) {
    Cal::Utils::initMaxDynamicVerbosity(Verbosity::bloat);

    [[maybe_unused]] int platformOrd = -1;
    int forkNum = 0;
    [[maybe_unused]] bool skipStressTests = false;
    std::vector<pid_t> childProcesses;
    for (int i = 0; i < argc; ++i) {
        if (0 == strcmp(argv[i], "--platform_ordinal")) {
            if (i + 1 == argc) {
                log<Verbosity::info>("Expected integer parameter after --platform_ordinal");
                return -1;
            }
            platformOrd = atoi(argv[i + 1]);
            i++;
        } else if (0 == strcmp(argv[i], "--fork")) {
            if (i + 1 == argc) {
                log<Verbosity::info>("Expected integer parameter after --fork");
                return -1;
            }
            forkNum = atoi(argv[i + 1]);
            i++;
        } else if (0 == strcmp(argv[i], "--skip_stress")) {
            skipStressTests = true;
        }
    }

    if (forkNum) {
        log<Verbosity::info>("Forking (requested fork num : %d) ...\n", forkNum);
        for (int i = 0; i < forkNum; ++i) {
            pid_t childPid = fork();
            if (0 == childPid) {
                childProcesses.clear();
                break;
            }
            if (-1 == childPid) {
                log<Verbosity::error>("Fork #%d/%d failed", i + 1, forkNum);
            } else {
                log<Verbosity::info>("Fork #%d/%d successful, child : %d", i + 1, forkNum, childPid);
                childProcesses.push_back(childPid);
            }
        }
    }

    log<Verbosity::info>("Calling zeInit()");
    const auto zeInitResult = zeInit(0);
    if (zeInitResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeInit() call has failed! Error code = %d", static_cast<int>(zeInitResult));
        return -1;
    }

    log<Verbosity::info>("Initialization has been successful");

    log<Verbosity::info>("Calling zeDriverGet() to get number of drivers!");
    uint32_t numDrivers{0};
    auto zeDriverGetResult = zeDriverGet(&numDrivers, nullptr);
    if (zeDriverGetResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeDriverGet() call has failed! Error code = %d", static_cast<int>(zeDriverGetResult));
        return -1;
    }

    log<Verbosity::info>("Number of supported drivers: %d", numDrivers);

    log<Verbosity::info>("Calling zeDriverGet() to get drivers!");
    std::vector<ze_driver_handle_t> drivers{};
    drivers.resize(numDrivers);

    zeDriverGetResult = zeDriverGet(&numDrivers, drivers.data());
    if (zeDriverGetResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeDriverGet() call has failed! Error code = %d", static_cast<int>(zeDriverGetResult));
        return -1;
    }

    const auto driver = drivers[0];
    assert(driver != nullptr);

    log<Verbosity::info>("Getting driver API version for first driver!");

    ze_api_version_t version{};
    const auto zeGetDriverApiVersionResult = zeDriverGetApiVersion(driver, &version);
    if (zeGetDriverApiVersionResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeGetDriverApiVersion() call has failed! Error code = %d", static_cast<int>(zeGetDriverApiVersionResult));
        return -1;
    }

    log<Verbosity::info>("Supported API version -> (MAJOR: %d, MINOR: %d)", static_cast<int>(ZE_MAJOR_VERSION(version)), static_cast<int>(ZE_MINOR_VERSION(version)));

    log<Verbosity::info>("Getting driver properties for first driver!");

    ze_driver_properties_t driverProperties{ZE_STRUCTURE_TYPE_DRIVER_PROPERTIES};
    const auto zeDriverGetPropertiesResult = zeDriverGetProperties(driver, &driverProperties);
    if (zeDriverGetPropertiesResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeDriverGetProperties() call has failed! Error code = %d", static_cast<int>(zeDriverGetPropertiesResult));
        return -1;
    }

    std::stringstream driverPropsSs;
    driverPropsSs << "Driver version: " << driverProperties.driverVersion << "\n"
                  << "UUID:";
    for (const auto uuidByte : driverProperties.uuid.id) {
        driverPropsSs << " " << static_cast<int>(uuidByte);
    }

    const auto driverPropsStr = driverPropsSs.str();
    log<Verbosity::info>("Driver properties: %s!", driverPropsStr.c_str());

    log<Verbosity::info>("Getting driver extension properties for first driver");
    uint32_t extensionsCount = 0;
    auto zeDriverGetExtensionPropertiesResult = zeDriverGetExtensionProperties(driver, &extensionsCount, nullptr);
    if (zeDriverGetExtensionPropertiesResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeDriverGetExtensionProperties() call has failed! Error code = %d", static_cast<int>(zeDriverGetExtensionPropertiesResult));
        return -1;
    }
    if (extensionsCount == 0) {
        log<Verbosity::info>("No extensions supported on this driver");
    } else {
        std::vector<ze_driver_extension_properties_t> extensionsSupported(extensionsCount);
        zeDriverGetExtensionPropertiesResult = zeDriverGetExtensionProperties(driver, &extensionsCount, extensionsSupported.data());
        if (zeDriverGetExtensionPropertiesResult != ZE_RESULT_SUCCESS) {
            log<Verbosity::error>("zeDriverGetExtensionProperties() call has failed! Error code = %d", static_cast<int>(zeDriverGetExtensionPropertiesResult));
            return -1;
        }

        log<Verbosity::info>("List of Driver extensions properties:");
        for (uint32_t i = 0; i < extensionsSupported.size(); i++) {
            log<Verbosity::info>("Extension %d: %s", i + 1, extensionsSupported[i].name);
        }
    }

    void *zexDriverImportExternalPointerFptr = nullptr;
    auto zeDriverGetExtensionFunctionAddressResult = zeDriverGetExtensionFunctionAddress(driver, "zexDriverImportExternalPointer", &zexDriverImportExternalPointerFptr);
    if (zeDriverGetExtensionFunctionAddressResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeDriverGetExtensionFunctionAddress() call has failed! Error code = %d", static_cast<int>(zeDriverGetExtensionFunctionAddressResult));
    }

    log<Verbosity::info>("Getting IPC properties for the first driver!");

    ze_driver_ipc_properties_t ipcProperties{ZE_STRUCTURE_TYPE_DRIVER_IPC_PROPERTIES};
    const auto zeDriverGetIpcPropertiesResult = zeDriverGetIpcProperties(driver, &ipcProperties);
    if (zeDriverGetIpcPropertiesResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeDriverGetIpcProperties() call has failed! Error code = %d", static_cast<int>(zeDriverGetIpcPropertiesResult));
        return -1;
    }
    log<Verbosity::info>("Driver IPC flags: %d", static_cast<int>(ipcProperties.flags));

    log<Verbosity::info>("Getting number of devices from the first driver!");

    uint32_t numDevices{0};
    auto zeDeviceGetResult = zeDeviceGet(driver, &numDevices, nullptr);
    if (zeDeviceGetResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeDeviceGet() call has failed! Error code = %d", static_cast<int>(zeDeviceGetResult));
        return -1;
    }

    log<Verbosity::info>("Number of available devices: %d", numDevices);

    log<Verbosity::info>("Calling zeDeviceGet() to get devices!");
    std::vector<ze_device_handle_t> devices{};
    devices.resize(numDevices);

    zeDeviceGetResult = zeDeviceGet(driver, &numDevices, devices.data());
    if (zeDeviceGetResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeDeviceGet() call has failed! Error code = %d", static_cast<int>(zeDeviceGetResult));
        return -1;
    }

    for (const auto device : devices) {
        log<Verbosity::info>("Reading device status!");

        const auto deviceStatus = zeDeviceGetStatus(device);
        if (deviceStatus == ZE_RESULT_SUCCESS) {
            log<Verbosity::info>("Device status is OK!");
        } else if (deviceStatus == ZE_RESULT_ERROR_UNSUPPORTED_FEATURE) {
            log<Verbosity::info>("Checking device status is not supported!");
        } else {
            log<Verbosity::error>("zeDeviceStatusGet() call indicates, that device cannot be used! Error code = %d", static_cast<int>(deviceStatus));
            continue;
        }

        log<Verbosity::info>("Reading device properties!");

        ze_device_properties_t deviceProperties = {ZE_STRUCTURE_TYPE_DEVICE_PROPERTIES};
        const auto zeDeviceGetPropertiesResult = zeDeviceGetProperties(device, &deviceProperties);

        if (zeDeviceGetPropertiesResult != ZE_RESULT_SUCCESS) {
            log<Verbosity::error>("zeDeviceGetProperties() call has failed! Error code = %d", static_cast<int>(zeDeviceGetPropertiesResult));
            return -1;
        }

        std::stringstream ss;
        ss << "Device : \n"
           << " * name : " << deviceProperties.name << "\n"
           << " * deviceId : " << deviceProperties.deviceId << "\n"
           << " * numSlices : " << deviceProperties.numSlices << "\n"
           << " * numSubslicesPerSlice : " << deviceProperties.numSubslicesPerSlice << "\n"
           << " * numEUsPerSubslice : " << deviceProperties.numEUsPerSubslice << "\n"
           << " * numThreadsPerEU : " << deviceProperties.numThreadsPerEU << "\n";
        const auto deviceInfoStr = ss.str();

        log<Verbosity::info>("%s", deviceInfoStr.c_str());

        log<Verbosity::info>("Reading compute properties!");

        ze_device_compute_properties_t computeProperties = {ZE_STRUCTURE_TYPE_DEVICE_COMPUTE_PROPERTIES};
        const auto zeDeviceGetComputePropertiesResult = zeDeviceGetComputeProperties(device, &computeProperties);
        if (zeDeviceGetComputePropertiesResult != ZE_RESULT_SUCCESS) {
            log<Verbosity::error>("zeDeviceGetComputeProperties() call has failed! Error code = %d", static_cast<int>(zeDeviceGetComputePropertiesResult));
            return -1;
        }

        ss.str("");
        ss << "Compute properties : \n"
           << " * maxTotalGroupSize : " << computeProperties.maxTotalGroupSize << "\n"
           << " * maxGroupSizeX :  " << computeProperties.maxGroupSizeX << "\n"
           << " * maxGroupSizeY :  " << computeProperties.maxGroupSizeY << "\n"
           << " * maxGroupSizeZ :  " << computeProperties.maxGroupSizeZ << "\n"
           << " * maxGroupCountX :  " << computeProperties.maxGroupCountX << "\n"
           << " * maxGroupCountY :  " << computeProperties.maxGroupCountY << "\n"
           << " * maxGroupCountZ :  " << computeProperties.maxGroupCountZ << "\n"
           << " * maxSharedLocalMemory : " << computeProperties.maxSharedLocalMemory << "\n"
           << " * numSubGroupSizes : " << computeProperties.numSubGroupSizes << "\n";
        for (int i = 0; i < computeProperties.numSubGroupSizes; ++i) {
            ss << " * subGroupSizes[" << i << "] : " << computeProperties.subGroupSizes[i] << "\n";
        }
        const auto computeInfoStr = ss.str();

        if (false == testZeDevicePciGetProperiesExt(device)) {
            return -1;
        }

        log<Verbosity::info>("%s", computeInfoStr.c_str());

        log<Verbosity::info>("Reading module properties!");
        ze_device_module_properties_t moduleProperties = {ZE_STRUCTURE_TYPE_DEVICE_MODULE_PROPERTIES};
        const auto zeDeviceGetModulePropertiesResult = zeDeviceGetModuleProperties(device, &moduleProperties);
        if (zeDeviceGetModulePropertiesResult != ZE_RESULT_SUCCESS) {
            log<Verbosity::error>("zeDeviceGetModuleProperties() call has failed! Error code = %d", static_cast<int>(zeDeviceGetModulePropertiesResult));
            return -1;
        }

        ss.str("");
        ss << "Module properties : \n"
           << " * spirvVersionSupported : " << moduleProperties.spirvVersionSupported << "\n"
           << " * flags : " << static_cast<int>(moduleProperties.flags) << "\n"
           << " * fp16flags : " << static_cast<int>(moduleProperties.fp16flags) << "\n"
           << " * fp32flags : " << static_cast<int>(moduleProperties.fp32flags) << "\n"
           << " * fp64flags : " << static_cast<int>(moduleProperties.fp64flags) << "\n"
           << " * maxArgumentsSize : " << moduleProperties.maxArgumentsSize << "\n"
           << " * printfBufferSize : " << moduleProperties.printfBufferSize << "\n";
        const auto moduleInfoStr = ss.str();

        log<Verbosity::info>("%s", moduleInfoStr.c_str());

        log<Verbosity::info>("Reading image properties!");
        ze_device_image_properties_t imageProperties = {ZE_STRUCTURE_TYPE_DEVICE_IMAGE_PROPERTIES};
        const auto zeDeviceGetImagePropertiesResult = zeDeviceGetImageProperties(device, &imageProperties);
        if (zeDeviceGetImagePropertiesResult != ZE_RESULT_SUCCESS) {
            log<Verbosity::error>("zeDeviceGetImageProperties() call has failed! Error code = %d", static_cast<int>(zeDeviceGetImagePropertiesResult));
            return -1;
        }

        ss.str("");
        ss << "Image properties : \n"
           << " * maxImageDims1D : " << imageProperties.maxImageDims1D << "\n"
           << " * maxImageDims2D : " << imageProperties.maxImageDims2D << "\n"
           << " * maxImageDims3D : " << imageProperties.maxImageDims3D << "\n"
           << " * maxImageBufferSize : " << imageProperties.maxImageBufferSize << "\n"
           << " * maxImageArraySlices : " << imageProperties.maxImageArraySlices << "\n"
           << " * maxSamplers : " << imageProperties.maxSamplers << "\n"
           << " * maxReadImageArgs : " << imageProperties.maxReadImageArgs << "\n"
           << " * maxWriteImageArgs : " << imageProperties.maxWriteImageArgs << "\n";

        const auto imageInfoStr = ss.str();
        log<Verbosity::info>("%s", imageInfoStr.c_str());

        log<Verbosity::info>("Reading external memory properties!");
        ze_device_external_memory_properties_t externalMemoryProperties = {ZE_STRUCTURE_TYPE_DEVICE_EXTERNAL_MEMORY_PROPERTIES};
        const auto zeDeviceGetExternalMemoryPropertiesResult = zeDeviceGetExternalMemoryProperties(device, &externalMemoryProperties);
        if (zeDeviceGetExternalMemoryPropertiesResult != ZE_RESULT_SUCCESS) {
            log<Verbosity::error>("zeDeviceGetExternalMemoryProperties() call has failed! Error code = %d", static_cast<int>(zeDeviceGetExternalMemoryPropertiesResult));
            return -1;
        }

        ss.str("");
        ss << "External memory properties : \n"
           << " * memoryAllocationImportTypes : " << static_cast<int>(externalMemoryProperties.memoryAllocationImportTypes) << "\n"
           << " * memoryAllocationExportTypes : " << static_cast<int>(externalMemoryProperties.memoryAllocationExportTypes) << "\n"
           << " * imageImportTypes : " << static_cast<int>(externalMemoryProperties.imageImportTypes) << "\n"
           << " * imageExportTypes : " << static_cast<int>(externalMemoryProperties.imageExportTypes) << "\n";

        const auto externalMemoryInfoStr = ss.str();
        log<Verbosity::info>("%s", externalMemoryInfoStr.c_str());

        log<Verbosity::info>("Reading memory access properties!");
        ze_device_memory_access_properties_t memoryAccessProperties = {ZE_STRUCTURE_TYPE_DEVICE_MEMORY_ACCESS_PROPERTIES};
        const auto zeDeviceGetMemoryAccessPropertiesResult = zeDeviceGetMemoryAccessProperties(device, &memoryAccessProperties);
        if (zeDeviceGetMemoryAccessPropertiesResult != ZE_RESULT_SUCCESS) {
            log<Verbosity::error>("zeDeviceGetMemoryAccessProperties() call has failed! Error code = %d", static_cast<int>(zeDeviceGetMemoryAccessPropertiesResult));
            return -1;
        }

        ss.str("");
        ss << "Memory access properties : \n"
           << " * hostAllocCapabilities : " << static_cast<int>(memoryAccessProperties.hostAllocCapabilities) << "\n"
           << " * deviceAllocCapabilities : " << static_cast<int>(memoryAccessProperties.deviceAllocCapabilities) << "\n"
           << " * sharedSingleDeviceAllocCapabilities : " << static_cast<int>(memoryAccessProperties.sharedSingleDeviceAllocCapabilities) << "\n"
           << " * sharedCrossDeviceAllocCapabilities : " << static_cast<int>(memoryAccessProperties.sharedCrossDeviceAllocCapabilities) << "\n"
           << " * sharedSystemAllocCapabilities : " << static_cast<int>(memoryAccessProperties.sharedSystemAllocCapabilities) << "\n";
        const auto memoryAccessInfoStr = ss.str();

        log<Verbosity::info>("%s", memoryAccessInfoStr.c_str());

        log<Verbosity::info>("Reading number of memory properties via zeDeviceGetMemoryProperties()!");

        uint32_t memoryPropertiesCount{0};
        auto zeDeviceGetMemoryPropertiesResult = zeDeviceGetMemoryProperties(device, &memoryPropertiesCount, nullptr);
        if (zeDeviceGetMemoryPropertiesResult != ZE_RESULT_SUCCESS) {
            log<Verbosity::error>("zeDeviceGetMemoryProperties() call has failed! Error code = %d", static_cast<int>(zeDeviceGetMemoryPropertiesResult));
            return -1;
        }

        log<Verbosity::info>("Number of memory properties: %d!", memoryPropertiesCount);

        log<Verbosity::info>("Reading memory properties via zeDeviceGetMemoryProperties()!");

        std::vector<ze_device_memory_properties_t> memoryProperties{};
        memoryProperties.resize(memoryPropertiesCount);

        for (auto &memoryProperty : memoryProperties) {
            memoryProperty.stype = ZE_STRUCTURE_TYPE_DEVICE_MEMORY_PROPERTIES;
        }

        zeDeviceGetMemoryPropertiesResult = zeDeviceGetMemoryProperties(device, &memoryPropertiesCount, memoryProperties.data());
        if (zeDeviceGetMemoryPropertiesResult != ZE_RESULT_SUCCESS) {
            log<Verbosity::error>("zeDeviceGetMemoryProperties() call has failed! Error code = %d", static_cast<int>(zeDeviceGetMemoryPropertiesResult));
            return -1;
        }

        for (const auto &memoryProperty : memoryProperties) {
            ss.str("");
            ss << "Memory properties : \n"
               << " * flags : " << memoryProperty.flags << "\n"
               << " * maxClockRate : " << memoryProperty.maxClockRate << "\n"
               << " * maxBusWidth : " << memoryProperty.maxBusWidth << "\n"
               << " * totalSize : " << memoryProperty.totalSize << "\n"
               << " * name : ";

            for (const auto c : memoryProperty.name) {
                ss << c;
            }
            ss << "\n";

            const auto memoryPropertyInfo = ss.str();
            log<Verbosity::info>("%s", memoryPropertyInfo.c_str());
        }

        log<Verbosity::info>("Reading number of cache properties via zeDeviceGetCacheProperties()!");

        uint32_t cachePropertiesCount{0};
        auto zeDeviceGetCachePropertiesResult = zeDeviceGetCacheProperties(device, &cachePropertiesCount, nullptr);
        if (zeDeviceGetCachePropertiesResult != ZE_RESULT_SUCCESS) {
            log<Verbosity::error>("zeDeviceGetCachePropertiesResult() call has failed! Error code = %d", static_cast<int>(zeDeviceGetCachePropertiesResult));
            return -1;
        }

        log<Verbosity::info>("Number of cache properties: %d!", cachePropertiesCount);

        log<Verbosity::info>("Reading cache properties via zeDeviceGetCacheProperties()!");

        std::vector<ze_device_cache_properties_t> cacheProperties;
        cacheProperties.resize(cachePropertiesCount);

        for (auto &cacheProperty : cacheProperties) {
            cacheProperty.stype = ZE_STRUCTURE_TYPE_DEVICE_CACHE_PROPERTIES;
        }

        zeDeviceGetCachePropertiesResult = zeDeviceGetCacheProperties(device, &cachePropertiesCount, cacheProperties.data());
        if (zeDeviceGetCachePropertiesResult != ZE_RESULT_SUCCESS) {
            log<Verbosity::error>("zeDeviceGetCachePropertiesResult() call has failed! Error code = %d", static_cast<int>(zeDeviceGetCachePropertiesResult));
            return -1;
        }

        for (const auto &cacheProperty : cacheProperties) {
            ss.str("");
            ss << "Cache properties : \n"
               << " * flags : " << static_cast<int>(cacheProperty.flags) << "\n"
               << " * cacheSize : " << cacheProperty.cacheSize << "\n";

            const auto cacheInfo = ss.str();
            log<Verbosity::info>("%s", cacheInfo.c_str());
        }

        log<Verbosity::info>("Checking if device can access it's own allocations via zeDeviceCanAccessPeer");
        ze_bool_t peerAccess = false;
        const auto zeDeviceCanAccessPeerResult = zeDeviceCanAccessPeer(device, device, &peerAccess);
        if (zeDeviceCanAccessPeerResult != ZE_RESULT_SUCCESS) {
            log<Verbosity::error>("zeDeviceCanAccessPeer() call has failed! Error code = %d", static_cast<int>(zeDeviceCanAccessPeerResult));
            return -1;
        }

        log<Verbosity::info>("Result of zeDeviceCanAccessPeer is: %s", peerAccess ? "true" : "false");

        log<Verbosity::info>("Gather synchronized host and GPU timestamps");
        uint64_t hostTs, deviceTs;
        auto zeDeviceGetGlobalTimestampsResult = zeDeviceGetGlobalTimestamps(device, &hostTs, &deviceTs);
        if (zeDeviceGetGlobalTimestampsResult != ZE_RESULT_SUCCESS) {
            log<Verbosity::error>("zeDeviceGetGlobalTimestamp() call has failed! Error code = %d", static_cast<int>(zeDeviceGetGlobalTimestampsResult));
            return -1;
        }

        log<Verbosity::info>("Global Timestamps returned: hostTs: %lx, DeviceTs: %lx", hostTs, deviceTs);

        log<Verbosity::info>("Reading number of command queue group properties via zeDeviceGetCommandQueueGroupProperties()!");

        uint32_t queueGroupPropertiesCount{0};
        auto zeDeviceGetCommandQueueGroupPropertiesResult = zeDeviceGetCommandQueueGroupProperties(device, &queueGroupPropertiesCount, nullptr);
        if (zeDeviceGetCommandQueueGroupPropertiesResult != ZE_RESULT_SUCCESS) {
            log<Verbosity::error>("zeDeviceGetCommandQueueGroupProperties() call has failed! Error code = %d", static_cast<int>(zeDeviceGetCommandQueueGroupPropertiesResult));
            return -1;
        }

        log<Verbosity::info>("Number of command queue group properties: %d!", queueGroupPropertiesCount);

        log<Verbosity::info>("Reading command queue group properties via zeDeviceGetCommandQueueGroupProperties()!");
        std::vector<ze_command_queue_group_properties_t> queueGroupProperties{};
        queueGroupProperties.resize(queueGroupPropertiesCount);

        for (auto &queueGroupProperty : queueGroupProperties) {
            queueGroupProperty.stype = ZE_STRUCTURE_TYPE_COMMAND_QUEUE_GROUP_PROPERTIES;
        }

        zeDeviceGetCommandQueueGroupPropertiesResult = zeDeviceGetCommandQueueGroupProperties(device, &queueGroupPropertiesCount, queueGroupProperties.data());
        if (zeDeviceGetCommandQueueGroupPropertiesResult != ZE_RESULT_SUCCESS) {
            log<Verbosity::error>("zeDeviceGetCommandQueueGroupProperties() call has failed! Error code = %d", static_cast<int>(zeDeviceGetCommandQueueGroupPropertiesResult));
            return -1;
        }

        for (const auto &queueGroupProperty : queueGroupProperties) {
            ss.str("");
            ss << "Queue group properties : \n"
               << " * flags : " << static_cast<int>(queueGroupProperty.flags) << "\n"
               << " * maxMemoryFillPatternSize : " << queueGroupProperty.maxMemoryFillPatternSize << "\n"
               << " * numQueues : " << queueGroupProperty.numQueues << "\n";

            const auto queueGroupInfoStr = ss.str();
            log<Verbosity::info>("%s", queueGroupInfoStr.c_str());
        }

        log<Verbosity::info>("Reading subdevices count via zeDeviceGetSubDevices()!");

        uint32_t numSubDevices{0};
        auto zeDeviceGetSubDevicesResult = zeDeviceGetSubDevices(device, &numSubDevices, nullptr);
        if (zeDeviceGetSubDevicesResult != ZE_RESULT_SUCCESS) {
            log<Verbosity::error>("zeDeviceGetSubDevices() call has failed! Error code = %d", static_cast<int>(zeDeviceGetSubDevicesResult));
            return -1;
        }
        log<Verbosity::info>("Number of subdevices: %d!", numSubDevices);

        log<Verbosity::info>("Reading subdevices via zeDeviceGetSubDevices()!");
        std::vector<ze_device_handle_t> subdevices{};
        subdevices.resize(numSubDevices);

        zeDeviceGetSubDevicesResult = zeDeviceGetSubDevices(device, &numSubDevices, subdevices.data());
        if (zeDeviceGetSubDevicesResult != ZE_RESULT_SUCCESS) {
            log<Verbosity::error>("zeDeviceGetSubDevices() call has failed! Error code = %d", static_cast<int>(zeDeviceGetSubDevicesResult));
            return -1;
        }

        for (const auto subdevice : subdevices) {
            log<Verbosity::info>("Reading subdevice properties!");

            ze_device_properties_t subDeviceProperties = {ZE_STRUCTURE_TYPE_DEVICE_PROPERTIES};
            const auto zeDeviceGetPropertiesOfSubdeviceResult = zeDeviceGetProperties(subdevice, &subDeviceProperties);

            if (zeDeviceGetPropertiesOfSubdeviceResult != ZE_RESULT_SUCCESS) {
                log<Verbosity::error>("zeDeviceGetProperties() call has failed! Error code = %d", static_cast<int>(zeDeviceGetPropertiesOfSubdeviceResult));
                return -1;
            }

            ss.str("");
            ss << "Subdevice : \n"
               << " * name : " << subDeviceProperties.name << "\n"
               << " * deviceId : " << subDeviceProperties.deviceId << "\n"
               << " * numSlices : " << subDeviceProperties.numSlices << "\n"
               << " * numSubslicesPerSlice : " << subDeviceProperties.numSubslicesPerSlice << "\n"
               << " * numEUsPerSubslice : " << subDeviceProperties.numEUsPerSubslice << "\n"
               << " * numThreadsPerEU : " << subDeviceProperties.numThreadsPerEU << "\n";
            const auto subDeviceInfoStr = ss.str();

            log<Verbosity::info>("%s", subDeviceInfoStr.c_str());
        }
    }

    log<Verbosity::info>("Creating L0 context via zeContextCreate()!");

    ze_context_desc_t contextDescription{};
    contextDescription.stype = ZE_STRUCTURE_TYPE_CONTEXT_DESC;

    ze_context_handle_t contextHandle{};

    const auto zeContextCreateResult = zeContextCreate(driver, &contextDescription, &contextHandle);
    if (zeContextCreateResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeContextCreate() call has failed! Error code = %d", static_cast<int>(zeContextCreateResult));
        return -1;
    }

    log<Verbosity::info>("L0 context has been created! contextHandle = %p", static_cast<void *>(contextHandle));

    log<Verbosity::info>("Getting L0 context status via zeContextGetStatus()");
    const auto zeContextGetStatusResult = zeContextGetStatus(contextHandle);
    log<Verbosity::info>("L0 context status is: %d", static_cast<int>(zeContextGetStatusResult));

    log<Verbosity::info>("Getting command queue properties for device[0] to prepare command queue description!");
    assert(!devices.empty());

    const auto device = devices[0];
    uint32_t queueGroupPropertiesCount{0};
    auto zeDeviceGetCommandQueueGroupPropertiesResult = zeDeviceGetCommandQueueGroupProperties(device, &queueGroupPropertiesCount, nullptr);
    if (zeDeviceGetCommandQueueGroupPropertiesResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeDeviceGetCommandQueueGroupProperties() call has failed! Error code = %d", static_cast<int>(zeDeviceGetCommandQueueGroupPropertiesResult));
        return -1;
    }

    std::vector<ze_command_queue_group_properties_t> queueGroupProperties{};
    queueGroupProperties.resize(queueGroupPropertiesCount);

    for (auto &queueGroupProperty : queueGroupProperties) {
        queueGroupProperty.stype = ZE_STRUCTURE_TYPE_COMMAND_QUEUE_GROUP_PROPERTIES;
    }

    zeDeviceGetCommandQueueGroupPropertiesResult = zeDeviceGetCommandQueueGroupProperties(device, &queueGroupPropertiesCount, queueGroupProperties.data());
    if (zeDeviceGetCommandQueueGroupPropertiesResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeDeviceGetCommandQueueGroupProperties() call has failed! Error code = %d", static_cast<int>(zeDeviceGetCommandQueueGroupPropertiesResult));
        return -1;
    }

    ze_command_queue_desc_t queueDescription{};

    queueDescription.stype = ZE_STRUCTURE_TYPE_COMMAND_QUEUE_DESC;
    queueDescription.mode = ZE_COMMAND_QUEUE_MODE_DEFAULT;
    queueDescription.priority = ZE_COMMAND_QUEUE_PRIORITY_NORMAL;

    bool isComputeQueueFound{false};
    for (uint32_t i{0}; i < queueGroupPropertiesCount; ++i) {
        if (queueGroupProperties[i].flags & ZE_COMMAND_QUEUE_GROUP_PROPERTY_FLAG_COMPUTE) {
            queueDescription.ordinal = i;
            log<Verbosity::info>("Using ordinal = %d --> compute flag enabled", static_cast<int>(i));

            isComputeQueueFound = true;
            break;
        }
    }

    if (!isComputeQueueFound) {
        log<Verbosity::error>("Could not find compute queue! Aborting...");
        return -1;
    }

    log<Verbosity::info>("Creating command queue via zeCommandQueueCreate()!");

    ze_command_queue_handle_t commandQueue;
    const auto zeCommandQueueCreateResult = zeCommandQueueCreate(contextHandle, device, &queueDescription, &commandQueue);
    if (zeCommandQueueCreateResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandQueueCreate() call has failed! Error code = %d", static_cast<int>(zeCommandQueueCreateResult));
        return -1;
    }

    log<Verbosity::info>("Command queue created successfully! Handle = %p", static_cast<void *>(commandQueue));

    log<Verbosity::info>("Creating command list via zeCommandListCreate()!");

    ze_command_list_handle_t commandListHandle{};
    ze_command_list_desc_t commandListDescription = {
        ZE_STRUCTURE_TYPE_COMMAND_LIST_DESC,
        nullptr,
        queueDescription.ordinal,
        0};

    const auto zeCommandListCreateResult = zeCommandListCreate(contextHandle, device, &commandListDescription, &commandListHandle);
    if (zeCommandListCreateResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandListCreate() call has failed! Error code = %d", static_cast<int>(zeCommandListCreateResult));
        return -1;
    }

    log<Verbosity::info>("Command list created successfully! Handle = %p", static_cast<void *>(commandListHandle));

    log<Verbosity::info>("Creating module from SPIR-V source via zeModuleCreate()!");
    log<Verbosity::info>("Compiling simple kernel to SPIR-V via libocloc.so!");

    DynamicLibrary oclocLib{"libocloc.so"};
    if (!oclocLib.isLoaded()) {
        log<Verbosity::error>("Could not find libocloc.so!");
        return -1;
    }

    using OclocInvokeFunT = int(unsigned int, const char *[], const uint32_t, const uint8_t **, const uint64_t *, const char **, const uint32_t,
                                const uint8_t **, const uint64_t *, const char **, uint32_t *, uint8_t ***, uint64_t **, char ***);

    auto *oclocInvoke = oclocLib.getFunction<OclocInvokeFunT>("oclocInvoke");
    if (!oclocInvoke) {
        log<Verbosity::error>("Cannot find oclocInvoke() function inside libocloc.so!");
        return -1;
    }

    std::array oclocArgs = {
        "ocloc",
        "-file",
        "simple_app.cl",
        "-spv_only",
    };

    const char *simpleAppSource =
        R"(__kernel void CopyBuffer(__global unsigned int *src, __global unsigned int *dst) {
    int id = (int)get_global_id(0);
    dst[id] = src[id];
}

__kernel void DoubleVals(__global unsigned int *src, __global unsigned int *dst) {
    int id = (int)get_global_id(0);
    dst[id] = 2 * src[id];
})";

    std::array<const unsigned char *, 1> sources = {reinterpret_cast<const unsigned char *>(simpleAppSource)};
    std::array<size_t, 1> sourcesLengths = {strlen(simpleAppSource) + 1};
    std::array<const char *, 1> sourcesNames = {"simple_app.cl"};
    unsigned int numOutputs = 0U;
    unsigned char **outputs = nullptr;
    size_t *ouputLengths = nullptr;
    char **outputNames = nullptr;

    const auto compilationResult = oclocInvoke(oclocArgs.size(), oclocArgs.data(),
                                               sources.size(), sources.data(),
                                               sourcesLengths.data(), sourcesNames.data(),
                                               0, nullptr, nullptr, nullptr,
                                               &numOutputs, &outputs, &ouputLengths, &outputNames);
    if (compilationResult != 0) {
        log<Verbosity::error>("Compilation via ocloc lib has failed!!");
        return -1;
    }

    unsigned char *spirV = nullptr;
    size_t spirVlen = 0;

    for (unsigned int i = 0; i < numOutputs; ++i) {
        auto nameLen = strlen(outputNames[i]);
        if ((nameLen > 4) && (strstr(&outputNames[i][nameLen - 4], ".spv") != nullptr)) {
            spirV = outputs[i];
            spirVlen = ouputLengths[i];
            break;
        }
    }

    if (!spirV) {
        log<Verbosity::error>("Could not get generated SPIR-V file!");
        return -1;
    }

    ze_module_desc_t moduleHandleDescription = {
        ZE_STRUCTURE_TYPE_MODULE_DESC,
        nullptr,
        ZE_MODULE_FORMAT_IL_SPIRV,
        spirVlen,
        reinterpret_cast<const uint8_t *>(spirV),
        "-Wno-recompiled-from-ir",
        nullptr};

    bool shouldFinishAfterBuildLog{false};
    ze_module_handle_t moduleHandle{};
    ze_module_build_log_handle_t buildLog{};

    auto zeModuleCreateResult = zeModuleCreate(contextHandle, device, &moduleHandleDescription, &moduleHandle, &buildLog);
    if (zeModuleCreateResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeModuleCreate() has failed! Error code: %d", static_cast<int>(zeModuleCreateResult));
        shouldFinishAfterBuildLog = true;
    } else {
        log<Verbosity::info>("Creation of module has succeeded!");
    }

    log<Verbosity::info>("Getting build log size!");

    size_t buildLogSize{0};
    auto zeModuleBuildLogGetStringResult = zeModuleBuildLogGetString(buildLog, &buildLogSize, nullptr);
    if (zeModuleBuildLogGetStringResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeModuleBuildLogGetString() call has failed! Error code = %d", static_cast<int>(zeModuleBuildLogGetStringResult));
        return -1;
    }

    log<Verbosity::info>("Build log size is %zd!", buildLogSize);
    log<Verbosity::info>("Getting build log!");

    std::string buildLogStr{};
    buildLogStr.resize(buildLogSize + 1);

    zeModuleBuildLogGetStringResult = zeModuleBuildLogGetString(buildLog, &buildLogSize, buildLogStr.data());
    if (zeModuleBuildLogGetStringResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeModuleBuildLogGetString() call has failed! Error code = %d", static_cast<int>(zeModuleBuildLogGetStringResult));
        return -1;
    }

    log<Verbosity::info>("Build log : %s", buildLogStr.c_str());

    log<Verbosity::info>("Destroying module build log via zeModuleBuildLogDestroy()!");

    auto zeModuleBuildLogDestroyResult = zeModuleBuildLogDestroy(buildLog);
    if (zeModuleBuildLogDestroyResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeModuleBuildLogDestroy() call has failed! Error code = %d", static_cast<int>(zeModuleBuildLogDestroyResult));
        return -1;
    } else {
        buildLog = nullptr;
        buildLogSize = 0;
        buildLogStr = "";
    }

    log<Verbosity::info>("Destruction of L0 module build log has been successful!");

    if (shouldFinishAfterBuildLog) {
        return -1;
    }

    log<Verbosity::info>("Getting count of available kernels in module!");

    uint32_t kernelNamesCount{0};
    auto zeModuleGetKernelNamesResult = zeModuleGetKernelNames(moduleHandle, &kernelNamesCount, nullptr);
    if (zeModuleGetKernelNamesResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeModuleGetKernelNames() call has failed! Error code = %d", static_cast<int>(zeModuleGetKernelNamesResult));
        return -1;
    }

    log<Verbosity::info>("Count of kernels in module is: %d!", static_cast<int>(kernelNamesCount));

    log<Verbosity::info>("Getting available kernel names from module!");

    std::vector<const char *> kernelNames{};
    kernelNames.resize(kernelNamesCount);

    zeModuleGetKernelNamesResult = zeModuleGetKernelNames(moduleHandle, &kernelNamesCount, kernelNames.data());
    if (zeModuleGetKernelNamesResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeModuleGetKernelNames() call has failed! Error code = %d", static_cast<int>(zeModuleGetKernelNamesResult));
        return -1;
    }

    log<Verbosity::info>("Kernel names from module are:");
    for (const auto &name : kernelNames) {
        log<Verbosity::info>("%s", name);
    }

    log<Verbosity::info>("Getting module properties via zeModuleGetProperties()");

    ze_module_properties_t moduleProps = {ZE_STRUCTURE_TYPE_MODULE_PROPERTIES};
    const auto zeModuleGetPropertiesResult = zeModuleGetProperties(moduleHandle, &moduleProps);
    if (zeModuleGetPropertiesResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeModuleGetProperties() call has failed! Error code = %d", static_cast<int>(zeModuleGetPropertiesResult));
        return -1;
    }

    log<Verbosity::info>("Module properties flags are: %d", static_cast<int>(moduleProps.flags));

    log<Verbosity::info>("Getting function pointer to non-existing function from module via zeModuleGetFunctionPointer!");

    void *nonexistingFunctionPtr{nullptr};
    const auto zeModuleGetFunctionPointerResult = zeModuleGetFunctionPointer(moduleHandle, "SomeNonexistingFunction", &nonexistingFunctionPtr);
    if (zeModuleGetFunctionPointerResult == ZE_RESULT_ERROR_INVALID_FUNCTION_NAME && nonexistingFunctionPtr == nullptr) {
        log<Verbosity::info>("zeModuleGetFunctionPointer() correctly returned ZE_RESULT_ERROR_INVALID_FUNCTION_NAME!");
    } else {
        log<Verbosity::error>("zeModuleGetFunctionPointer() call has failed! Error code = %d, nonexistingFunctionPtr = %p",
                              static_cast<int>(zeModuleGetFunctionPointerResult),
                              nonexistingFunctionPtr);
        return -1;
    }

    log<Verbosity::info>("Getting global pointer from module");
    const std::string global_name = "global_variable";
    size_t globalSize = sizeof(float);
    void *globalPtr;
    const auto zeModuleGetGlobalPointerResult = zeModuleGetGlobalPointer(moduleHandle, global_name.c_str(), &globalSize, &globalPtr);
    if (zeModuleGetGlobalPointerResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeModuleGetGlobalPointer() call has failed! Error code = %d", static_cast<int>(zeModuleGetGlobalPointerResult));
    } else {
        log<Verbosity::info>("Get Global Pointer API success!");
    }

    log<Verbosity::info>("Creating CopyBuffer kernel via zeKernelCreate()!");

    ze_kernel_desc_t kernelDesc = {
        ZE_STRUCTURE_TYPE_KERNEL_DESC,
        nullptr,
        0, // flags
        "CopyBuffer"};

    ze_kernel_handle_t copyBufferKernelHandle;
    auto zeKernelCreateResult = zeKernelCreate(moduleHandle, &kernelDesc, &copyBufferKernelHandle);
    if (zeKernelCreateResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeKernelCreate() call has failed! Error code = %d", static_cast<int>(zeKernelCreateResult));
        return -1;
    }

    log<Verbosity::info>("Kernel has been created successfully!");

    log<Verbosity::info>("Creating DoubleVals kernel via zeKernelCreate()!");

    kernelDesc.pKernelName = "DoubleVals";

    ze_kernel_handle_t doubleValsKernelHandle;
    zeKernelCreateResult = zeKernelCreate(moduleHandle, &kernelDesc, &doubleValsKernelHandle);
    if (zeKernelCreateResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeKernelCreate() call has failed! Error code = %d", static_cast<int>(zeKernelCreateResult));
        return -1;
    }

    log<Verbosity::info>("Kernel has been created successfully!");

    log<Verbosity::info>("Getting kernel name size via zeKernelGetName()");

    size_t kernelNameSize{};
    const auto zeKernelGetNameSizeResult = zeKernelGetName(copyBufferKernelHandle, &kernelNameSize, nullptr);
    if (zeKernelGetNameSizeResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeKernelGetName() call has failed! Error code = %d", static_cast<int>(zeKernelGetNameSizeResult));
        return -1;
    }

    log<Verbosity::info>("The size of kernel name is %zd", kernelNameSize);

    log<Verbosity::info>("Getting kernel name via zeKernelGetName()");

    std::string kernelName{};
    kernelName.resize(kernelNameSize + 1);

    const auto zeKernelGetNameResult = zeKernelGetName(copyBufferKernelHandle, &kernelNameSize, kernelName.data());
    if (zeKernelGetNameResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeKernelGetName() call has failed! Error code = %d", static_cast<int>(zeKernelGetNameResult));
        return -1;
    }

    log<Verbosity::info>("Kernel name is: %s", kernelName.c_str());

    log<Verbosity::info>("Getting indirect access flags via zeKernelGetIndirectAccess()!");

    ze_kernel_indirect_access_flags_t indirectAccessFlags{};
    const auto zeKernelGetIndirectAccessResult = zeKernelGetIndirectAccess(copyBufferKernelHandle, &indirectAccessFlags);
    if (zeKernelGetIndirectAccessResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeKernelGetIndirectAccess() call has failed! Error code = %d", static_cast<int>(zeKernelGetIndirectAccessResult));
        return -1;
    }

    log<Verbosity::info>("Indirect access flags: %d", static_cast<int>(indirectAccessFlags));

    log<Verbosity::info>("Setting indirect access flags via zeKernelSetIndirectAccess()!");

    const auto zeKernelSetIndirectAccessResult = zeKernelSetIndirectAccess(copyBufferKernelHandle, indirectAccessFlags);
    if (zeKernelSetIndirectAccessResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeKernelSetIndirectAccess() call has failed! Error code = %d", static_cast<int>(zeKernelSetIndirectAccessResult));
        return -1;
    }

    log<Verbosity::info>("Indirect access flags have been set successfully!");

    log<Verbosity::info>("Getting total group count via zeKernelSuggestMaxCooperativeGroupCount()");

    uint32_t totalGroupCount{};
    const auto zeKernelSuggestMaxCooperativeGroupCountResult = zeKernelSuggestMaxCooperativeGroupCount(copyBufferKernelHandle, &totalGroupCount);
    if (zeKernelSuggestMaxCooperativeGroupCountResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeKernelSuggestMaxCooperativeGroupCount() call has failed! Error code = %d", static_cast<int>(zeKernelSuggestMaxCooperativeGroupCountResult));
        return -1;
    }

    log<Verbosity::info>("Total group count is: %d", static_cast<int>(totalGroupCount));

    log<Verbosity::info>("Getting kernel properties via zeKernelGetProperties()!");

    ze_kernel_properties_t kernelProperties{};
    const auto zeKernelGetPropertiesResult = zeKernelGetProperties(copyBufferKernelHandle, &kernelProperties);
    if (zeKernelGetPropertiesResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeKernelGetProperties() call has failed! Error code = %d", static_cast<int>(zeKernelGetPropertiesResult));
        return -1;
    }

    log<Verbosity::info>("Number of kernel arguments read from properties is: %d", static_cast<int>(kernelProperties.numKernelArgs));

    log<Verbosity::info>("Calling zeKernelSetCacheConfig() to set ZE_CACHE_CONFIG_FLAG_LARGE_SLM flag!");

    const auto zeKernelSetCacheConfigResult = zeKernelSetCacheConfig(copyBufferKernelHandle, ZE_CACHE_CONFIG_FLAG_LARGE_SLM);
    if (zeKernelSetCacheConfigResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeKernelSetCacheConfig() call has failed! Error code = %d", static_cast<int>(zeKernelSetCacheConfigResult));
        return -1;
    }

    log<Verbosity::info>("zeKernelSetCacheConfig() call has succeeded!");

    const int arraySize = 1024;
    log<Verbosity::info>("Trying to get suggested group size for processing 1D array of %d elements", arraySize);

    uint32_t suggestedGroupSizeX{};
    uint32_t suggestedGroupSizeY{};
    uint32_t suggestedGroupSizeZ{};

    const auto zeKernelSuggestGroupSizeResult = zeKernelSuggestGroupSize(copyBufferKernelHandle, arraySize, 1, 1, &suggestedGroupSizeX, &suggestedGroupSizeY, &suggestedGroupSizeZ);
    if (zeKernelSuggestGroupSizeResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeKernelSuggestGroupSize() call has failed! Error code = %d", static_cast<int>(zeKernelSuggestGroupSizeResult));
        return -1;
    }

    log<Verbosity::info>("The suggested sizes are: (%d, %d, %d)", static_cast<int>(suggestedGroupSizeX), static_cast<int>(suggestedGroupSizeY), static_cast<int>(suggestedGroupSizeZ));

    log<Verbosity::info>("Setting kernel group size via zeKernelSetGroupSize() for CopyBuffer kernel!");

    auto zeKernelSetGroupSizeResult = zeKernelSetGroupSize(copyBufferKernelHandle, suggestedGroupSizeX, suggestedGroupSizeY, suggestedGroupSizeZ);
    if (zeKernelSetGroupSizeResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeKernelSetGroupSize() call has failed! Error code: %d", static_cast<int>(zeKernelSetGroupSizeResult));
        return -1;
    }

    log<Verbosity::info>("Call to zeKernelSetGroupSize() has been successful!");

    log<Verbosity::info>("Setting kernel group size via zeKernelSetGroupSize() for DoubleVals kernel!");

    zeKernelSetGroupSizeResult = zeKernelSetGroupSize(doubleValsKernelHandle, suggestedGroupSizeX, suggestedGroupSizeY, suggestedGroupSizeZ);
    if (zeKernelSetGroupSizeResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeKernelSetGroupSize() call has failed! Error code: %d", static_cast<int>(zeKernelSetGroupSizeResult));
        return -1;
    }

    log<Verbosity::info>("Call to zeKernelSetGroupSize() has been successful!");

    log<Verbosity::info>("Allocating destination and source buffers via zeMemAllocDevice()");

    constexpr size_t bufferSize{arraySize * sizeof(unsigned int)};
    constexpr size_t alignment{4};

    void *sourceBuffer{nullptr};
    void *destinationBuffer{nullptr};

    ze_device_mem_alloc_desc_t deviceMemAllocDesc = {ZE_STRUCTURE_TYPE_DEVICE_MEM_ALLOC_DESC};
    deviceMemAllocDesc.flags = ZE_DEVICE_MEM_ALLOC_FLAG_BIAS_UNCACHED;
    deviceMemAllocDesc.ordinal = 0;

    auto zeMemAllocDeviceResult = zeMemAllocDevice(contextHandle, &deviceMemAllocDesc, bufferSize, alignment, device, &sourceBuffer);
    if (zeMemAllocDeviceResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeMemAllocDevice() call has failed! Error code: %d", static_cast<int>(zeMemAllocDeviceResult));
        return -1;
    }

    zeMemAllocDeviceResult = zeMemAllocDevice(contextHandle, &deviceMemAllocDesc, bufferSize, alignment, device, &destinationBuffer);
    if (zeMemAllocDeviceResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeMemAllocDevice() call has failed! Error code: %d", static_cast<int>(zeMemAllocDeviceResult));
        return -1;
    }

    log<Verbosity::info>("Allocations have been successful!");

    log<Verbosity::info>("Getting alloc properties for destination buffer via zeMemGetAllocProperties()!");

    ze_memory_allocation_properties_t dstBufMemAllocProps{};
    ze_device_handle_t dstBufDeviceHandle{};

    const auto zeMemGetAllocPropertiesResult = zeMemGetAllocProperties(contextHandle, destinationBuffer, &dstBufMemAllocProps, &dstBufDeviceHandle);
    if (zeMemGetAllocPropertiesResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeMemGetAllocProperties() call has failed! Error code: %d", static_cast<int>(zeMemGetAllocPropertiesResult));
        return -1;
    }

    log<Verbosity::info>("Got allocation properties! pageSize=%d, type=%d, id=%d",
                         static_cast<int>(dstBufMemAllocProps.pageSize),
                         static_cast<int>(dstBufMemAllocProps.type),
                         static_cast<int>(dstBufMemAllocProps.id));

    log<Verbosity::info>("Comparing allocation type to ZE_MEMORY_TYPE_DEVICE - it is expected!");
    if (dstBufMemAllocProps.type != ZE_MEMORY_TYPE_DEVICE) {
        log<Verbosity::error>("Invalid allocation type!");
        return -1;
    } else {
        log<Verbosity::info>("Comparison has been successful!");
    }

    log<Verbosity::info>("Comparing device handle received for allocation with the previously used device handle!");
    if (device != dstBufDeviceHandle) {
        log<Verbosity::error>("Invalid device has been received! Expected %p, Received %p", static_cast<void *>(device), static_cast<void *>(dstBufDeviceHandle));
        return -1;
    } else {
        log<Verbosity::info>("Comparison has been successful!");
    }

    log<Verbosity::info>("Allocating USM host buffer!");

    void *usmHostBuffer{nullptr};
    ze_host_mem_alloc_desc_t hostMemAllocDesc = {ZE_STRUCTURE_TYPE_HOST_MEM_ALLOC_DESC};

    const auto zeMemAllocHostResult = zeMemAllocHost(contextHandle, &hostMemAllocDesc, bufferSize, alignment, &usmHostBuffer);
    if (zeMemAllocHostResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeMemAllocHost() call has failed! Error code: %d", static_cast<int>(zeMemAllocHostResult));
        return -1;
    }

    log<Verbosity::info>("Allocation has been successful!");

    auto UsmHostBufferWithOffset = static_cast<char *>(usmHostBuffer) + 10;
    void *basePtrToQuery = nullptr;
    size_t sizeOfUSMBuffer = 0;
    auto zeMemGetAddressRangeResult = zeMemGetAddressRange(contextHandle, UsmHostBufferWithOffset, &basePtrToQuery, &sizeOfUSMBuffer);
    if (zeMemGetAddressRangeResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeMemGetAddressRange() call has failed! Error code: %d", static_cast<int>(zeMemGetAddressRangeResult));
        return -1;
    }

    log<Verbosity::info>("zeMemGetAddressRange has been successful! For USM pointer %p base address is %p. Allocation size is %zd", UsmHostBufferWithOffset, basePtrToQuery, sizeOfUSMBuffer);

    log<Verbosity::info>("Allocating USM shared buffer!");
    void *usmBufferShared{nullptr};
    const auto zeMemAllocSharedResult = zeMemAllocShared(contextHandle, &deviceMemAllocDesc, &hostMemAllocDesc, bufferSize, alignment, nullptr, &usmBufferShared);
    if (zeMemAllocSharedResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeMemAllocShared() call has failed! Error code: %d", static_cast<int>(zeMemAllocSharedResult));
        return -1;
    }

    log<Verbosity::info>("Shared Allocation has been successful!");

    log<Verbosity::info>("Performing direct access to USM host buffer! Filling it with constant value: 7.");

    for (int i = 0; i < arraySize; ++i) {
        auto *usmHostBufUint = static_cast<unsigned int *>(usmHostBuffer);
        usmHostBufUint[i] = 7;
    }

    log<Verbosity::info>("Host buffer Fill has been completed successfully!");

    log<Verbosity::info>("Performing direct access to USM shared buffer! Filling it with constant value: 3.");

    for (int i = 0; i < arraySize; ++i) {
        auto *usmSharedBufUint = static_cast<unsigned int *>(usmBufferShared);
        usmSharedBufUint[i] = 3;
    }

    log<Verbosity::info>("Shared Buffer fill has been completed successfully!");

    log<Verbosity::info>("Creating event pool via zeEventPoolCreate()!");

    ze_event_pool_handle_t eventPoolHandle{};
    ze_event_pool_desc_t eventPoolDescription{};
    eventPoolDescription.count = 10;
    eventPoolDescription.flags = ZE_EVENT_POOL_FLAG_HOST_VISIBLE | ZE_EVENT_POOL_FLAG_KERNEL_TIMESTAMP;

    ze_device_handle_t poolDevices[] = {device};

    const auto zeEventPoolCreateResult = zeEventPoolCreate(contextHandle, &eventPoolDescription, 1, poolDevices, &eventPoolHandle);
    if (zeEventPoolCreateResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeEventPoolCreate() call has failed! Error code: %d", static_cast<int>(zeEventPoolCreateResult));
        return -1;
    }

    log<Verbosity::info>("Event pool has been created successfully!");

    ze_event_pool_handle_t eventPoolHostVisibleHandle{};
    ze_event_pool_desc_t eventPoolHostVisibleDescription{};
    eventPoolHostVisibleDescription.count = 10;
    eventPoolHostVisibleDescription.flags = ZE_EVENT_POOL_FLAG_HOST_VISIBLE;

    const auto zeEventPoolHostVisibleCreateResult = zeEventPoolCreate(contextHandle, &eventPoolHostVisibleDescription, 1, poolDevices, &eventPoolHostVisibleHandle);
    if (zeEventPoolHostVisibleCreateResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeEventPoolCreate() call has failed for host visible event pool! Error code: %d", static_cast<int>(zeEventPoolHostVisibleCreateResult));
        return -1;
    }

    log<Verbosity::info>("Host Visible Event pool has been created successfully!");

    log<Verbosity::info>("Setting kernel arguments for CopyBuffer()!");

    auto zeKernelSetArgumentValueResult = zeKernelSetArgumentValue(copyBufferKernelHandle, 0, sizeof(usmHostBuffer), &usmHostBuffer);
    if (zeKernelSetArgumentValueResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeKernelSetArgumentValue() call has failed for usmHostBuffer! Error code: %d", static_cast<int>(zeKernelSetArgumentValueResult));
        return -1;
    }

    zeKernelSetArgumentValueResult = zeKernelSetArgumentValue(copyBufferKernelHandle, 1, sizeof(sourceBuffer), &sourceBuffer);
    if (zeKernelSetArgumentValueResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeKernelSetArgumentValue() call has failed for sourceBuffer! Error code: %d", static_cast<int>(zeKernelSetArgumentValueResult));
        return -1;
    }

    log<Verbosity::info>("Arguments have been correctly set!");

    log<Verbosity::info>("Creating an event for copying from usmHostBuffer to device source buffer via zeEventCreate()!");

    ze_event_handle_t usmHostBufCopiedToDeviceSourceBufEventHandle{};
    ze_event_desc_t eventDesc{};
    eventDesc.index = 0;

    auto zeEventCreateResult = zeEventCreate(eventPoolHandle, &eventDesc, &usmHostBufCopiedToDeviceSourceBufEventHandle);
    if (zeEventCreateResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeEventCreate() call has failed! Error code = %d", static_cast<int>(zeEventCreateResult));
        return -1;
    }

    log<Verbosity::info>("Creation of event has been successful!");

    log<Verbosity::info>("Appending launch kernel operation for copying usmHostBuffer to device source buffer to command list!");

    ze_group_count_t launchArgs{};
    launchArgs.groupCountX = arraySize / suggestedGroupSizeX;
    launchArgs.groupCountY = 1;
    launchArgs.groupCountZ = 1;

    auto zeCommandListAppendLaunchKernelResult = zeCommandListAppendLaunchKernel(commandListHandle,
                                                                                 copyBufferKernelHandle,
                                                                                 &launchArgs,
                                                                                 usmHostBufCopiedToDeviceSourceBufEventHandle,
                                                                                 0,
                                                                                 nullptr);
    if (zeCommandListAppendLaunchKernelResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandListAppendLaunchKernel() call has failed! Error code = %d", static_cast<int>(zeCommandListAppendLaunchKernelResult));
        return -1;
    }

    log<Verbosity::info>("Launch kernel operation appended successfully!");

    log<Verbosity::info>("Setting kernel arguments for DoubleVals kernel()!");

    zeKernelSetArgumentValueResult = zeKernelSetArgumentValue(doubleValsKernelHandle, 0, sizeof(sourceBuffer), &sourceBuffer);
    if (zeKernelSetArgumentValueResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeKernelSetArgumentValue() call has failed for sourceBuffer! Error code: %d", static_cast<int>(zeKernelSetArgumentValueResult));
        return -1;
    }

    zeKernelSetArgumentValueResult = zeKernelSetArgumentValue(doubleValsKernelHandle, 1, sizeof(destinationBuffer), &destinationBuffer);
    if (zeKernelSetArgumentValueResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeKernelSetArgumentValue() call has failed for destinationBuffer! Error code: %d", static_cast<int>(zeKernelSetArgumentValueResult));
        return -1;
    }

    log<Verbosity::info>("Arguments have been correctly set!");

    log<Verbosity::info>("Creating an event for doubling values of device source buffer and storing them in device destination buffer via zeEventCreate()!");

    ze_event_handle_t deviceSourceDoubledAndStoredInDeviceDestBufEventHandle{};
    eventDesc.index = 1;
    eventDesc.wait = ZE_EVENT_SCOPE_FLAG_HOST;

    zeEventCreateResult = zeEventCreate(eventPoolHandle, &eventDesc, &deviceSourceDoubledAndStoredInDeviceDestBufEventHandle);
    if (zeEventCreateResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeEventCreate() call has failed! Error code = %d", static_cast<int>(zeEventCreateResult));
        return -1;
    }

    log<Verbosity::info>("Creating an event for signaling independently in command list zeEventCreate()!");
    ze_event_handle_t appendSignalEventHandle{};
    eventDesc.index = 2;
    eventDesc.wait = ZE_EVENT_SCOPE_FLAG_HOST;

    zeEventCreateResult = zeEventCreate(eventPoolHostVisibleHandle, &eventDesc, &appendSignalEventHandle);
    if (zeEventCreateResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeEventCreate() call has failed! Error code = %d", static_cast<int>(zeEventCreateResult));
        return -1;
    }
    log<Verbosity::info>("Creation of event has been successful!");

    log<Verbosity::info>("Setting global offset in X dim to 1 for doubleValsKernel");
    uint32_t offsetX = 0;
    auto zeKernelSetGlobalOffsetExpResult = zeKernelSetGlobalOffsetExp(doubleValsKernelHandle, offsetX, 0, 0);
    if (zeKernelSetGlobalOffsetExpResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeKernelSetGlobalOffsetExp() call has failed! Error code = %d", static_cast<int>(zeKernelSetGlobalOffsetExpResult));
        return -1;
    }

    log<Verbosity::info>("Setting global offset in X dim to 1 succeeded!");

    log<Verbosity::info>("Appending launch kernel operation for doubling device sourceBuffer and storing it in destinationBuffer to command list!");

    zeCommandListAppendLaunchKernelResult = zeCommandListAppendLaunchKernel(commandListHandle,
                                                                            doubleValsKernelHandle,
                                                                            &launchArgs,
                                                                            deviceSourceDoubledAndStoredInDeviceDestBufEventHandle,
                                                                            1,
                                                                            &usmHostBufCopiedToDeviceSourceBufEventHandle);
    if (zeCommandListAppendLaunchKernelResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandListAppendLaunchKernel() call has failed! Error code = %d", static_cast<int>(zeCommandListAppendLaunchKernelResult));
        return -1;
    }

    log<Verbosity::info>("Launch kernel operation appended successfully!");

    auto zeCommandListAppendWaitOnEventsResult = zeCommandListAppendWaitOnEvents(commandListHandle,
                                                                                 1, &usmHostBufCopiedToDeviceSourceBufEventHandle);
    if (zeCommandListAppendWaitOnEventsResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandListAppendWaitOnEvents() call has failed! Error code = %d", static_cast<int>(zeCommandListAppendWaitOnEventsResult));
        return -1;
    }
    log<Verbosity::info>("Wait on Event operation appended successfully!");

    auto zeCommandListAppendSignalEventResult = zeCommandListAppendSignalEvent(commandListHandle, appendSignalEventHandle);
    if (zeCommandListAppendSignalEventResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandListAppendSignalEvent() call has failed! Error code = %d", static_cast<int>(zeCommandListAppendSignalEventResult));
        return -1;
    }
    log<Verbosity::info>("Append Signal Event operation appended successfully!");

    log<Verbosity::info>("Closing command list via zeCommandListClose()!");

    auto zeCommandListCloseResult = zeCommandListClose(commandListHandle);
    if (zeCommandListCloseResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandListClose() call has failed! Error code = %d", static_cast<int>(zeCommandListCloseResult));
        return -1;
    }

    log<Verbosity::info>("Command list has been successfully closed!");

    log<Verbosity::info>("Executing command list via zeCommandQueueExecuteCommandLists()!");

    auto zeCommandQueueExecuteCommandListsResult = zeCommandQueueExecuteCommandLists(commandQueue, 1, &commandListHandle, nullptr);
    if (zeCommandQueueExecuteCommandListsResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandQueueExecuteCommandLists() call has failed! Error code = %d", static_cast<int>(zeCommandQueueExecuteCommandListsResult));
        return -1;
    }

    log<Verbosity::info>("Execution started!");

    log<Verbosity::info>("Waiting for finish of execution via zeEventHostSynchronize()!");

    auto zeEventHostSynchronizeResult = zeEventHostSynchronize(deviceSourceDoubledAndStoredInDeviceDestBufEventHandle, UINT64_MAX);
    if (zeEventHostSynchronizeResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeEventHostSynchronize() call has failed! Error code = %d", static_cast<int>(zeEventHostSynchronizeResult));
        return -1;
    }
    log<Verbosity::info>("zeEventHostSynchronize() completed for deviceSourceDoubledAndStoredInDeviceDestBufEventHandle!");

    ze_kernel_timestamp_result_t kernelTsResults;
    auto zeEventQueryKernelTimestampsResult = zeEventQueryKernelTimestamp(deviceSourceDoubledAndStoredInDeviceDestBufEventHandle, &kernelTsResults);
    if (zeEventQueryKernelTimestampsResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeEventQueryKernelTimestamp() call has failed! Error code = %d", static_cast<int>(zeEventQueryKernelTimestampsResult));
        return -1;
    }
    log<Verbosity::info>("zeEventQueryKernelTimestamp() completed for deviceSourceDoubledAndStoredInDeviceDestBufEventHandle!");
    ze_device_properties_t deviceProperties = {ZE_STRUCTURE_TYPE_DEVICE_PROPERTIES};
    const auto zeDeviceGetPropertiesResult = zeDeviceGetProperties(device, &deviceProperties);

    if (zeDeviceGetPropertiesResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeDeviceGetProperties() call has failed! Error code = %d", static_cast<int>(zeDeviceGetPropertiesResult));
        return -1;
    }
    uint64_t timerResolution = deviceProperties.timerResolution;
    uint64_t kernelDuration = kernelTsResults.context.kernelEnd - kernelTsResults.context.kernelStart;
    log<Verbosity::info>("Kernel timestamp statistics: \n"
                         " Global start : %lx cycles\n"
                         " Kernel start:  %lx cycles\n"
                         " Kernel end: %lx cycles\n"
                         " Global end: %lx cycles\n"
                         " timerResolution clock: %d ns\n"
                         " Kernel duration : %d cycles",
                         kernelTsResults.global.kernelStart, kernelTsResults.context.kernelStart, kernelTsResults.context.kernelEnd, kernelTsResults.global.kernelEnd, timerResolution,
                         kernelDuration);

    zeEventHostSynchronizeResult = zeEventHostSynchronize(appendSignalEventHandle, UINT64_MAX);
    if (zeEventHostSynchronizeResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeEventHostSynchronize() call has failed! Error code = %d", static_cast<int>(zeEventHostSynchronizeResult));
        return -1;
    }
    log<Verbosity::info>("zeEventHostSynchronize() completed for appendSignalEventHandle!");

    auto zeEventQueryStatusResult = zeEventQueryStatus(appendSignalEventHandle);
    if (zeEventQueryStatusResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeEventQueryStatus() call has failed! Error code = %d", static_cast<int>(zeEventQueryStatusResult));
        return -1;
    }
    log<Verbosity::info>("zeEventQueryStatus() completed for appendSignalEventHandle!");

    log<Verbosity::info>("Execution finished!");

    log<Verbosity::info>("Resetting appendSignalEventHandle on the host");
    auto zeEventHostResetResult = zeEventHostReset(appendSignalEventHandle);
    if (zeEventHostResetResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::info>("zeEventHostResetResult call failed. Error code = %d", static_cast<int>(zeEventHostResetResult));
        return -1;
    }

    zeEventQueryStatusResult = zeEventQueryStatus(appendSignalEventHandle);
    if (zeEventQueryStatusResult == ZE_RESULT_NOT_READY) {
        log<Verbosity::info>("zeEventQueryStatus() returns NOT_READY for appendSignalEventHandle correctly!");
    }

    log<Verbosity::info>("Resetting command list via zeCommandListReset()!");
    auto zeCommandListResetResult = zeCommandListReset(commandListHandle);
    if (zeCommandListResetResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandListReset() call has failed! Error code = %d", static_cast<int>(zeCommandListResetResult));
        return -1;
    }

    log<Verbosity::info>("Command list reset has been successful!");

    log<Verbosity::info>("Setting kernel arguments for CopyBuffer() to copy from device destination to usmHostBuffer!!");

    zeKernelSetArgumentValueResult = zeKernelSetArgumentValue(copyBufferKernelHandle, 0, sizeof(destinationBuffer), &destinationBuffer);
    if (zeKernelSetArgumentValueResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeKernelSetArgumentValue() call has failed for destinationBuffer! Error code: %d", static_cast<int>(zeKernelSetArgumentValueResult));
        return -1;
    }

    zeKernelSetArgumentValueResult = zeKernelSetArgumentValue(copyBufferKernelHandle, 1, sizeof(usmHostBuffer), &usmHostBuffer);
    if (zeKernelSetArgumentValueResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeKernelSetArgumentValue() call has failed for usmHostBuffer! Error code: %d", static_cast<int>(zeKernelSetArgumentValueResult));
        return -1;
    }

    log<Verbosity::info>("Arguments have been correctly set!");

    log<Verbosity::info>("Appending launch kernel operation for copying device destination buffer to usmHostBuffer to command list!");

    zeCommandListAppendLaunchKernelResult = zeCommandListAppendLaunchKernel(commandListHandle,
                                                                            copyBufferKernelHandle,
                                                                            &launchArgs,
                                                                            nullptr,
                                                                            0,
                                                                            nullptr);
    if (zeCommandListAppendLaunchKernelResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandListAppendLaunchKernel() call has failed! Error code = %d", static_cast<int>(zeCommandListAppendLaunchKernelResult));
        return -1;
    }

    log<Verbosity::info>("Launch kernel operation appended successfully!");

    log<Verbosity::info>("Creating fence via zeFenceCreate()!");

    ze_fence_handle_t fenceHandle{};
    ze_fence_desc_t fenceDesc{};

    const auto zeFenceCreateResult = zeFenceCreate(commandQueue, &fenceDesc, &fenceHandle);
    if (zeFenceCreateResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeFenceCreate() call has failed! Error code = %d", static_cast<int>(zeFenceCreateResult));
        return -1;
    }

    log<Verbosity::info>("Successfully created a fence!");

    log<Verbosity::info>("Closing command list via zeCommandListClose()!");

    zeCommandListCloseResult = zeCommandListClose(commandListHandle);
    if (zeCommandListCloseResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandListClose() call has failed! Error code = %d", static_cast<int>(zeCommandListCloseResult));
        return -1;
    }

    log<Verbosity::info>("Command list has been successfully closed!");

    log<Verbosity::info>("Executing command list via zeCommandQueueExecuteCommandLists()!");

    zeCommandQueueExecuteCommandListsResult = zeCommandQueueExecuteCommandLists(commandQueue, 1, &commandListHandle, fenceHandle);
    if (zeCommandQueueExecuteCommandListsResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandQueueExecuteCommandLists() call has failed! Error code = %d", static_cast<int>(zeCommandQueueExecuteCommandListsResult));
        return -1;
    }

    log<Verbosity::info>("Execution started!");

    log<Verbosity::info>("Waiting for finish of command queue via zeFenceHostSynchronize()!");

    auto zeFenceHostSynchronizeResult = zeFenceHostSynchronize(fenceHandle, UINT64_MAX);
    if (zeFenceHostSynchronizeResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeFenceHostSynchronize() call has failed! Error code = %d", static_cast<int>(zeFenceHostSynchronizeResult));
        return -1;
    }

    log<Verbosity::info>("Execution finished!");

    log<Verbosity::info>("Making sure that fence was signaled via zeFenceQueryStatus()!");

    auto zeFenceQueryStatusResult = zeFenceQueryStatus(fenceHandle);
    if (zeFenceQueryStatusResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeFenceQueryStatus() call returned value different than signaled! Error code = %d", static_cast<int>(zeFenceQueryStatusResult));
        return -1;
    }

    log<Verbosity::info>("Fence was signaled!");

    log<Verbosity::info>("Checking if usmHostBuffer contains doubled value after all operations!");

    for (int i = 0; i < arraySize; ++i) {
        auto *usmHostBufUint = static_cast<unsigned int *>(usmHostBuffer);
        if (usmHostBufUint[i] != 14) {
            log<Verbosity::error>("usmHostBuffer contains invalid values! They should be doubled. Expected: 14, actual: %d. Index: %d", usmHostBufUint[i], i);
            return -1;
        }
    }

    log<Verbosity::info>("usmHostBuffer passed check!");

    log<Verbosity::info>("Resetting fence via zeFenceReset()!");

    auto zeFenceResetResult = zeFenceReset(fenceHandle);
    if (zeFenceResetResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeFenceReset() call has failed! Error code = %d", static_cast<int>(zeFenceResetResult));
        return -1;
    }

    log<Verbosity::info>("zeFenceReset() has been successful!");

    log<Verbosity::info>("Making sure that fence is not signaled via zeFenceQueryStatus()!");

    zeFenceQueryStatusResult = zeFenceQueryStatus(fenceHandle);
    if (zeFenceQueryStatusResult != ZE_RESULT_NOT_READY) {
        log<Verbosity::error>("zeFenceQueryStatus() call returned value different than not-signaled! Error code = %d", static_cast<int>(zeFenceQueryStatusResult));
        return -1;
    }

    log<Verbosity::info>("Fence is in not-signaled state!");

    log<Verbosity::info>("Resetting command list via zeCommandListReset()!");
    zeCommandListResetResult = zeCommandListReset(commandListHandle);
    if (zeCommandListResetResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandListReset() call has failed! Error code = %d", static_cast<int>(zeCommandListResetResult));
        return -1;
    }

    log<Verbosity::info>("Command list reset has been successful!");

    log<Verbosity::info>("Appending launch kernel operation for copying device destination buffer to usmHostBuffer to command list!");

    zeCommandListAppendLaunchKernelResult = zeCommandListAppendLaunchKernel(commandListHandle,
                                                                            copyBufferKernelHandle,
                                                                            &launchArgs,
                                                                            nullptr,
                                                                            0,
                                                                            nullptr);
    if (zeCommandListAppendLaunchKernelResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandListAppendLaunchKernel() call has failed! Error code = %d", static_cast<int>(zeCommandListAppendLaunchKernelResult));
        return -1;
    }

    log<Verbosity::info>("Launch kernel operation appended successfully!");

    log<Verbosity::info>("Closing command list via zeCommandListClose()!");

    zeCommandListCloseResult = zeCommandListClose(commandListHandle);
    if (zeCommandListCloseResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandListClose() call has failed! Error code = %d", static_cast<int>(zeCommandListCloseResult));
        return -1;
    }

    log<Verbosity::info>("Command list has been successfully closed!");

    log<Verbosity::info>("Executing command list via zeCommandQueueExecuteCommandLists()!");

    zeCommandQueueExecuteCommandListsResult = zeCommandQueueExecuteCommandLists(commandQueue, 1, &commandListHandle, nullptr);
    if (zeCommandQueueExecuteCommandListsResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandQueueExecuteCommandLists() call has failed! Error code = %d", static_cast<int>(zeCommandQueueExecuteCommandListsResult));
        return -1;
    }

    log<Verbosity::info>("Execution started!");

    log<Verbosity::info>("Waiting for finishing execution via zeCommandQueueSynchronize()!");

    auto zeCommandQueueSynchronizeResult = zeCommandQueueSynchronize(commandQueue, UINT64_MAX);
    if (zeCommandQueueSynchronizeResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandQueueSynchronize() call has failed! Error code = %d", static_cast<int>(zeCommandQueueSynchronizeResult));
        return -1;
    }

    log<Verbosity::info>("Execution finished!");

    log<Verbosity::info>("Resetting command list via zeCommandListReset()!");
    zeCommandListResetResult = zeCommandListReset(commandListHandle);
    if (zeCommandListResetResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandListReset() call has failed! Error code = %d", static_cast<int>(zeCommandListResetResult));
        return -1;
    }

    log<Verbosity::info>("Command list reset has been successful!");

    log<Verbosity::info>("Appending memory copy operation for copying device source buffer to usmHostBuffer to command list!");

    auto zeCommandListAppendMemoryCopyResult = zeCommandListAppendMemoryCopy(commandListHandle,
                                                                             usmHostBuffer,
                                                                             sourceBuffer,
                                                                             bufferSize,
                                                                             nullptr,
                                                                             0,
                                                                             nullptr);
    if (zeCommandListAppendMemoryCopyResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandListAppendMemoryCopy() call has failed! Error code = %d", static_cast<int>(zeCommandListAppendMemoryCopyResult));
        return -1;
    }

    log<Verbosity::info>("Memory copy operation appended successfully!");

    log<Verbosity::info>("Closing command list via zeCommandListClose()!");

    zeCommandListCloseResult = zeCommandListClose(commandListHandle);
    if (zeCommandListCloseResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandListClose() call has failed! Error code = %d", static_cast<int>(zeCommandListCloseResult));
        return -1;
    }

    log<Verbosity::info>("Command list has been successfully closed!");

    log<Verbosity::info>("Executing command list via zeCommandQueueExecuteCommandLists()!");

    zeCommandQueueExecuteCommandListsResult = zeCommandQueueExecuteCommandLists(commandQueue, 1, &commandListHandle, nullptr);
    if (zeCommandQueueExecuteCommandListsResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandQueueExecuteCommandLists() call has failed! Error code = %d", static_cast<int>(zeCommandQueueExecuteCommandListsResult));
        return -1;
    }

    log<Verbosity::info>("Execution started!");

    log<Verbosity::info>("Waiting for finishing execution via zeCommandQueueSynchronize()!");

    zeCommandQueueSynchronizeResult = zeCommandQueueSynchronize(commandQueue, UINT64_MAX);
    if (zeCommandQueueSynchronizeResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandQueueSynchronize() call has failed! Error code = %d", static_cast<int>(zeCommandQueueSynchronizeResult));
        return -1;
    }

    log<Verbosity::info>("Execution finished!");

    log<Verbosity::info>("Checking if usmHostBuffer contains values from sourceBuffer!");

    for (int i = 0; i < arraySize; ++i) {
        auto *usmHostBufUint = static_cast<unsigned int *>(usmHostBuffer);
        if (usmHostBufUint[i] != 7) {
            log<Verbosity::error>("usmHostBuffer contains invalid values! Expected: 7, actual: %d. Index: %d", usmHostBufUint[i], i);
            return -1;
        }
    }

    log<Verbosity::info>("usmHostBuffer passed check!");

    log<Verbosity::info>("Resetting command list via zeCommandListReset()!");
    zeCommandListResetResult = zeCommandListReset(commandListHandle);
    if (zeCommandListResetResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandListReset() call has failed! Error code = %d", static_cast<int>(zeCommandListResetResult));
        return -1;
    }

    log<Verbosity::info>("Command list reset has been successful!");

    log<Verbosity::info>("Preparing a buffer on stack. Filling each byte with value 1!");
    unsigned char stackBuffer[bufferSize] = {};
    for (int i = 0; i < bufferSize; ++i) {
        stackBuffer[i] = 1;
    }

    log<Verbosity::info>("Appending overlapping memory copy operations for copying client's stack buffer to usmHostBuffer and usmBufferShared to command list!");

    log<Verbosity::info>("Appending copy operation for copying first 512 bytes of client's stack buffer to usmHostBuffer to command list!");

    static_assert(bufferSize >= 512);
    zeCommandListAppendMemoryCopyResult = zeCommandListAppendMemoryCopy(commandListHandle,
                                                                        usmHostBuffer,
                                                                        stackBuffer,
                                                                        512,
                                                                        nullptr,
                                                                        0,
                                                                        nullptr);
    if (zeCommandListAppendMemoryCopyResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandListAppendMemoryCopy() call has failed! Error code = %d", static_cast<int>(zeCommandListAppendMemoryCopyResult));
        return -1;
    }

    log<Verbosity::info>("Memory copy operation appended successfully!");

    log<Verbosity::info>("Appending copy operation for copying of client's stack buffer to usmBufferShared to command list!");

    zeCommandListAppendMemoryCopyResult = zeCommandListAppendMemoryCopy(commandListHandle,
                                                                        usmBufferShared,
                                                                        stackBuffer,
                                                                        bufferSize,
                                                                        nullptr,
                                                                        0,
                                                                        nullptr);
    if (zeCommandListAppendMemoryCopyResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandListAppendMemoryCopy() call has failed! Error code = %d", static_cast<int>(zeCommandListAppendMemoryCopyResult));
        return -1;
    }

    log<Verbosity::info>("Memory copy operation appended successfully!");

    log<Verbosity::info>("Closing command list via zeCommandListClose()!");

    zeCommandListCloseResult = zeCommandListClose(commandListHandle);
    if (zeCommandListCloseResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandListClose() call has failed! Error code = %d", static_cast<int>(zeCommandListCloseResult));
        return -1;
    }

    log<Verbosity::info>("Command list has been successfully closed!");

    log<Verbosity::info>("Executing command list via zeCommandQueueExecuteCommandLists()!");

    zeCommandQueueExecuteCommandListsResult = zeCommandQueueExecuteCommandLists(commandQueue, 1, &commandListHandle, nullptr);
    if (zeCommandQueueExecuteCommandListsResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandQueueExecuteCommandLists() call has failed! Error code = %d", static_cast<int>(zeCommandQueueExecuteCommandListsResult));
        return -1;
    }

    log<Verbosity::info>("Execution started!");

    log<Verbosity::info>("Waiting for finishing execution via zeCommandQueueSynchronize()!");

    zeCommandQueueSynchronizeResult = zeCommandQueueSynchronize(commandQueue, UINT64_MAX);
    if (zeCommandQueueSynchronizeResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandQueueSynchronize() call has failed! Error code = %d", static_cast<int>(zeCommandQueueSynchronizeResult));
        return -1;
    }

    log<Verbosity::info>("Execution finished!");

    log<Verbosity::info>("Checking if first 512 bytes of usmHostBuffer contains values from client's stack buffer - each byte should be equal to 1!");

    for (int i = 0; i < 512; ++i) {
        auto *usmHostBufBytes = static_cast<unsigned char *>(usmHostBuffer);
        if (usmHostBufBytes[i] != 1) {
            log<Verbosity::error>("usmHostBuffer contains invalid values! Expected: 1, actual: %d. Byte: %d", static_cast<int>(usmHostBufBytes[i]), i);
            return -1;
        }
    }

    log<Verbosity::info>("usmHostBuffer passed check!");

    log<Verbosity::info>("Checking if usmBufferShared contains values from client's stack buffer - each byte should be equal to 1!");

    for (int i = 0; i < bufferSize; ++i) {
        auto *usmSharedBufBytes = static_cast<unsigned char *>(usmBufferShared);
        if (usmSharedBufBytes[i] != 1) {
            log<Verbosity::error>("usmBufferShared contains invalid values! Expected: 1, actual: %d. Byte: %d", static_cast<int>(usmSharedBufBytes[i]), i);
            return -1;
        }
    }

    log<Verbosity::info>("usmBufferShared passed check!");

    log<Verbosity::info>("Resetting command list!");

    zeCommandListResetResult = zeCommandListReset(commandListHandle);
    if (zeCommandListResetResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandListReset() call has failed! Error code = %d", static_cast<int>(zeCommandListResetResult));
        return -1;
    }

    log<Verbosity::info>("Command list reset has been successful!");

    log<Verbosity::info>("Preparing a buffer containing pattern on stack. Filling each byte with its index!");

    constexpr size_t patternSize{128};
    unsigned char stackPattern[patternSize] = {};
    for (int i = 0; i < patternSize; ++i) {
        stackPattern[i] = i;
    }

    log<Verbosity::info>("Appending fill operation for pattern from client's stack buffer to usmHostBuffer to command list!");

    auto zeCommandListAppendMemoryFillResult = zeCommandListAppendMemoryFill(commandListHandle,
                                                                             usmHostBuffer,
                                                                             stackPattern,
                                                                             patternSize,
                                                                             bufferSize,
                                                                             nullptr,
                                                                             0,
                                                                             nullptr);
    if (zeCommandListAppendMemoryFillResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandListAppendMemoryFill() call has failed! Error code = %d", static_cast<int>(zeCommandListAppendMemoryFillResult));
        return -1;
    }

    log<Verbosity::info>("Memory fill operation appended successfully!");

    log<Verbosity::info>("Appending fill operation for pattern from usmHostBufer to usmBufferShared to command list!");

    // zeCommandListAppendMemoryFill() stores the content of pattern.
    unsigned char snapshotOfHostBufferForValidation[bufferSize] = {};
    std::memcpy(snapshotOfHostBufferForValidation, usmHostBuffer, bufferSize);

    zeCommandListAppendMemoryFillResult = zeCommandListAppendMemoryFill(commandListHandle,
                                                                        usmBufferShared,
                                                                        usmHostBuffer,
                                                                        bufferSize,
                                                                        bufferSize,
                                                                        nullptr,
                                                                        0,
                                                                        nullptr);
    if (zeCommandListAppendMemoryFillResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandListAppendMemoryFill() call has failed! Error code = %d", static_cast<int>(zeCommandListAppendMemoryFillResult));
        return -1;
    }

    log<Verbosity::info>("Memory fill operation appended successfully!");

    auto zeCommandListAppendBarrierResult = zeCommandListAppendBarrier(commandListHandle, nullptr, 0, nullptr);
    if (zeCommandListAppendBarrierResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandListAppendBarrier() call has failed! Error code = %d", static_cast<int>(zeCommandListAppendBarrierResult));
        return -1;
    }
    log<Verbosity::info>("Barrier appended successfully");

    log<Verbosity::info>("Closing command list via zeCommandListClose()!");

    zeCommandListCloseResult = zeCommandListClose(commandListHandle);
    if (zeCommandListCloseResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandListClose() call has failed! Error code = %d", static_cast<int>(zeCommandListCloseResult));
        return -1;
    }

    log<Verbosity::info>("Command list has been successfully closed!");

    log<Verbosity::info>("Executing command list via zeCommandQueueExecuteCommandLists()!");

    zeCommandQueueExecuteCommandListsResult = zeCommandQueueExecuteCommandLists(commandQueue, 1, &commandListHandle, nullptr);
    if (zeCommandQueueExecuteCommandListsResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandQueueExecuteCommandLists() call has failed! Error code = %d", static_cast<int>(zeCommandQueueExecuteCommandListsResult));
        return -1;
    }

    log<Verbosity::info>("Execution started!");

    log<Verbosity::info>("Waiting for finishing execution via zeCommandQueueSynchronize()!");

    zeCommandQueueSynchronizeResult = zeCommandQueueSynchronize(commandQueue, UINT64_MAX);
    if (zeCommandQueueSynchronizeResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandQueueSynchronize() call has failed! Error code = %d", static_cast<int>(zeCommandQueueSynchronizeResult));
        return -1;
    }

    log<Verbosity::info>("Execution finished!");

    log<Verbosity::info>("Checking if usmHostBuffer contains values from client's stack buffer pattern!");

    for (int i = 0; i < bufferSize; ++i) {
        auto *usmHostBufBytes = static_cast<unsigned char *>(usmHostBuffer);
        auto expectedValue = static_cast<unsigned char>(i % patternSize);

        if (usmHostBufBytes[i] != expectedValue) {
            log<Verbosity::error>("usmHostBuffer contains invalid values! Expected: %d, actual: %d. Byte: %d",
                                  static_cast<int>(expectedValue),
                                  static_cast<int>(usmHostBufBytes[i]),
                                  i);
            return -1;
        }
    }

    log<Verbosity::info>("usmHostBuffer passed check!");

    log<Verbosity::info>("Checking if usmBufferShared contains values from snapshot of usmHostBuffer!");

    for (int i = 0; i < bufferSize; ++i) {
        auto *usmSharedBufBytes = static_cast<unsigned char *>(usmBufferShared);
        if (usmSharedBufBytes[i] != snapshotOfHostBufferForValidation[i]) {
            log<Verbosity::error>("usmBufferShared contains invalid values! Expected: %d, actual: %d. Byte: %d",
                                  static_cast<int>(snapshotOfHostBufferForValidation[i]),
                                  static_cast<int>(usmSharedBufBytes[i]),
                                  i);
            return -1;
        }
    }

    log<Verbosity::info>("usmBufferShared passed check!");

    log<Verbosity::info>("Resetting command list!");

    zeCommandListResetResult = zeCommandListReset(commandListHandle);
    if (zeCommandListResetResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandListReset() call has failed! Error code = %d", static_cast<int>(zeCommandListResetResult));
        return -1;
    }

    log<Verbosity::info>("Command list reset has been successful!");

    std::vector<unsigned char> bufferOnClientsHeap{};
    bufferOnClientsHeap.resize(bufferSize, 0xFF);

    log<Verbosity::info>("Appending memory copy operation for copying usmHostBuffer to a buffer on client's heap to command list!");

    zeCommandListAppendMemoryCopyResult = zeCommandListAppendMemoryCopy(commandListHandle,
                                                                        bufferOnClientsHeap.data(),
                                                                        usmHostBuffer,
                                                                        bufferSize,
                                                                        nullptr,
                                                                        0,
                                                                        nullptr);
    if (zeCommandListAppendMemoryCopyResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandListAppendMemoryCopy() call has failed! Error code = %d", static_cast<int>(zeCommandListAppendMemoryCopyResult));
        return -1;
    }

    log<Verbosity::info>("Memory copy operation appended successfully!");

    log<Verbosity::info>("Closing command list via zeCommandListClose()!");

    zeCommandListCloseResult = zeCommandListClose(commandListHandle);
    if (zeCommandListCloseResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandListClose() call has failed! Error code = %d", static_cast<int>(zeCommandListCloseResult));
        return -1;
    }

    log<Verbosity::info>("Command list has been successfully closed!");

    log<Verbosity::info>("Executing command list via zeCommandQueueExecuteCommandLists()!");

    zeCommandQueueExecuteCommandListsResult = zeCommandQueueExecuteCommandLists(commandQueue, 1, &commandListHandle, nullptr);
    if (zeCommandQueueExecuteCommandListsResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandQueueExecuteCommandLists() call has failed! Error code = %d", static_cast<int>(zeCommandQueueExecuteCommandListsResult));
        return -1;
    }

    log<Verbosity::info>("Execution started!");

    log<Verbosity::info>("Waiting for finishing execution via zeCommandQueueSynchronize()!");

    zeCommandQueueSynchronizeResult = zeCommandQueueSynchronize(commandQueue, UINT64_MAX);
    if (zeCommandQueueSynchronizeResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandQueueSynchronize() call has failed! Error code = %d", static_cast<int>(zeCommandQueueSynchronizeResult));
        return -1;
    }

    log<Verbosity::info>("Execution finished!");

    log<Verbosity::info>("Checking if buffer on client's heap contains values from usmHostBuffer!");

    for (int i = 0; i < bufferSize; ++i) {
        auto *usmHostBufBytes = static_cast<unsigned char *>(usmHostBuffer);

        if (usmHostBufBytes[i] != bufferOnClientsHeap[i]) {
            log<Verbosity::error>("bufferOnClientsHeap differs from usmHostBuffer! Expected: %d, actual: %d. Byte: %d",
                                  static_cast<int>(usmHostBufBytes[i]),
                                  static_cast<int>(bufferOnClientsHeap[i]),
                                  i);
            return -1;
        }
    }

    log<Verbosity::info>("bufferOnClientsHeap passed check!");

    log<Verbosity::info>("Resetting command list!");

    zeCommandListResetResult = zeCommandListReset(commandListHandle);
    if (zeCommandListResetResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandListReset() call has failed! Error code = %d", static_cast<int>(zeCommandListResetResult));
        return -1;
    }

    log<Verbosity::info>("Command list reset has been successful!");

    std::vector<unsigned char> anotherBufferOnClientsHeap{};
    anotherBufferOnClientsHeap.resize(bufferSize, 0xAA);

    log<Verbosity::info>("Appending memory copy operation for copying bufferOnClientsHeap to anotherBufferOnClientsHeap to command list!");

    zeCommandListAppendMemoryCopyResult = zeCommandListAppendMemoryCopy(commandListHandle,
                                                                        anotherBufferOnClientsHeap.data(),
                                                                        bufferOnClientsHeap.data(),
                                                                        bufferSize,
                                                                        nullptr,
                                                                        0,
                                                                        nullptr);
    if (zeCommandListAppendMemoryCopyResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandListAppendMemoryCopy() call has failed! Error code = %d", static_cast<int>(zeCommandListAppendMemoryCopyResult));
        return -1;
    }

    log<Verbosity::info>("Memory copy operation appended successfully!");

    log<Verbosity::info>("Closing command list via zeCommandListClose()!");

    zeCommandListCloseResult = zeCommandListClose(commandListHandle);
    if (zeCommandListCloseResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandListClose() call has failed! Error code = %d", static_cast<int>(zeCommandListCloseResult));
        return -1;
    }

    log<Verbosity::info>("Command list has been successfully closed!");

    log<Verbosity::info>("Resetting fence via zeFenceReset()!");

    zeFenceResetResult = zeFenceReset(fenceHandle);
    if (zeFenceResetResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeFenceReset() call has failed! Error code = %d", static_cast<int>(zeFenceResetResult));
        return -1;
    }

    log<Verbosity::info>("zeFenceReset() has been successful!");

    log<Verbosity::info>("Executing command list via zeCommandQueueExecuteCommandLists()!");

    zeCommandQueueExecuteCommandListsResult = zeCommandQueueExecuteCommandLists(commandQueue, 1, &commandListHandle, fenceHandle);
    if (zeCommandQueueExecuteCommandListsResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandQueueExecuteCommandLists() call has failed! Error code = %d", static_cast<int>(zeCommandQueueExecuteCommandListsResult));
        return -1;
    }

    log<Verbosity::info>("Execution started!");

    log<Verbosity::info>("Waiting for finish of command queue via zeFenceHostSynchronize()!");

    zeFenceHostSynchronizeResult = zeFenceHostSynchronize(fenceHandle, UINT64_MAX);
    if (zeFenceHostSynchronizeResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeFenceHostSynchronize() call has failed! Error code = %d", static_cast<int>(zeFenceHostSynchronizeResult));
        return -1;
    }

    log<Verbosity::info>("Execution finished!");

    log<Verbosity::info>("Checking if another buffer on client's heap contains values from buffer on client's heap!");

    for (int i = 0; i < bufferSize; ++i) {
        if (anotherBufferOnClientsHeap[i] != bufferOnClientsHeap[i]) {
            log<Verbosity::error>("anotherBufferOnClientsHeap differs from bufferOnClientsHeap! Expected: %d, actual: %d. Byte: %d",
                                  static_cast<int>(bufferOnClientsHeap[i]),
                                  static_cast<int>(anotherBufferOnClientsHeap[i]),
                                  i);
            return -1;
        }
    }

    log<Verbosity::info>("anotherBufferOnClientsHeap passed check!");

    log<Verbosity::info>("Destroying DoubleVals kernel via zeKernelDestroy()!");

    auto zeKernelDestroyResult = zeKernelDestroy(doubleValsKernelHandle);
    if (zeKernelDestroyResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeKernelDestroy() call has failed! Error code = %d", static_cast<int>(zeKernelDestroyResult));
        return -1;
    }

    log<Verbosity::info>("Kernel has been successfully destroyed!");

    log<Verbosity::info>("Destroying CopyBuffer kernel via zeKernelDestroy()!");

    zeKernelDestroyResult = zeKernelDestroy(copyBufferKernelHandle);
    if (zeKernelDestroyResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeKernelDestroy() call has failed! Error code = %d", static_cast<int>(zeKernelDestroyResult));
        return -1;
    }

    log<Verbosity::info>("Kernel has been successfully destroyed!");

    log<Verbosity::info>("Releasing device memory for buffers via zeMemFree()");

    auto zeMemFreeResult = zeMemFree(contextHandle, sourceBuffer);
    if (zeMemFreeResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeMemFree() call has failed for sourceBuffer! Error code: %d", static_cast<int>(zeMemFreeResult));
        return -1;
    }

    zeMemFreeResult = zeMemFree(contextHandle, destinationBuffer);
    if (zeMemFreeResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeMemFree() call has failed for destinationBuffer! Error code: %d", static_cast<int>(zeMemFreeResult));
        return -1;
    }

    zeMemFreeResult = zeMemFree(contextHandle, usmHostBuffer);
    if (zeMemFreeResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeMemFree() call has failed for usmHostBuffer! Error code: %d", static_cast<int>(zeMemFreeResult));
        return -1;
    }

    zeMemFreeResult = zeMemFree(contextHandle, usmBufferShared);
    if (zeMemFreeResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeMemFree() call has failed for usmSharedBuffer! Error code: %d", static_cast<int>(zeMemFreeResult));
        return -1;
    }

    log<Verbosity::info>("Memory for buffers has been released via zeMemFree()");

    log<Verbosity::info>("Destroying usmHostBufCopiedToDeviceSourceBufEvent via zeEventDestroy()!");

    auto zeEventDestroyResult = zeEventDestroy(usmHostBufCopiedToDeviceSourceBufEventHandle);
    if (zeEventDestroyResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeEventDestroy() call has failed! Error code: %d", static_cast<int>(zeEventDestroyResult));
        return -1;
    }

    log<Verbosity::info>("Event usmHostBufCopiedToDeviceSourceBufEvent destruction has been successful!");

    log<Verbosity::info>("Destroying deviceSourceDoubledAndStoredInDeviceDestBufEventHandle via zeEventDestroy()!");

    zeEventDestroyResult = zeEventDestroy(deviceSourceDoubledAndStoredInDeviceDestBufEventHandle);
    if (zeEventDestroyResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeEventDestroy() call has failed! Error code: %d", static_cast<int>(zeEventDestroyResult));
        return -1;
    }

    log<Verbosity::info>("Event deviceSourceDoubledAndStoredInDeviceDestBufEventHandle destruction has been successful!");

    log<Verbosity::info>("Destroying appendSignalEventHandle via zeEventDestroy()!");

    zeEventDestroyResult = zeEventDestroy(appendSignalEventHandle);
    if (zeEventDestroyResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeEventDestroy() call has failed! Error code: %d", static_cast<int>(zeEventDestroyResult));
        return -1;
    }

    log<Verbosity::info>("Event appendSignalEventHandle destruction has been successful!");

    log<Verbosity::info>("Destroying event pool via zeEventPoolDestroy()!");

    const auto zeEventPoolDestroyResult = zeEventPoolDestroy(eventPoolHandle);
    if (zeEventPoolDestroyResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeEventPoolDestroy() call has failed! Error code = %d", static_cast<int>(zeEventPoolDestroyResult));
        return -1;
    }

    log<Verbosity::info>("Destruction of event pool has been successful!");

    log<Verbosity::info>("Destroying module via zeModuleDestroy()!");

    auto zeModuleDestroyResult = zeModuleDestroy(moduleHandle);
    if (zeModuleDestroyResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeModuleDestroy() call has failed! Error code = %d", static_cast<int>(zeModuleDestroyResult));
        return -1;
    }

    log<Verbosity::info>("Destruction of L0 module has been successful!");

    log<Verbosity::info>("Destroying fence via zeFenceDestroy()!");

    const auto zeFenceDestroyResult = zeFenceDestroy(fenceHandle);
    if (zeFenceDestroyResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeFenceDestroy() call has failed! Error code = %d", static_cast<int>(zeFenceDestroyResult));
        return -1;
    }

    log<Verbosity::info>("Fence destruction has been successful!");

    log<Verbosity::info>("Destroying L0 command list via zeCommandListDestroy()!");
    auto zeCommandListDestroyResult = zeCommandListDestroy(commandListHandle);
    if (zeCommandListDestroyResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandListDestroy() call has failed! Error code = %d", static_cast<int>(zeCommandListDestroyResult));
        return -1;
    }

    log<Verbosity::info>("L0 command list has been destroyed!");

    log<Verbosity::info>("Creating L0 immediate command list via zeCommandListCreateImmediate()!");

    ze_command_list_handle_t commandListImmediateHandle{};
    const auto zeCommandListCreateImmediateResult = zeCommandListCreateImmediate(contextHandle, device, &queueDescription, &commandListImmediateHandle);
    if (zeCommandListCreateImmediateResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandListCreateImmediate() call has failed! Error code = %d", static_cast<int>(zeCommandListCreateImmediateResult));
        return -1;
    }

    log<Verbosity::info>("L0 command list immediate has been successfully created!");

    log<Verbosity::info>("Destroying L0 command list immediate via zeCommandQueueDestroy()!");
    zeCommandListDestroyResult = zeCommandListDestroy(commandListImmediateHandle);
    if (zeCommandListDestroyResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandListDestroy() call has failed! Error code = %d", static_cast<int>(zeCommandListDestroyResult));
        return -1;
    }

    log<Verbosity::info>("L0 command list immediate has been destroyed!");

    log<Verbosity::info>("Destroying L0 command queue via zeCommandQueueDestroy()!");
    const auto zeCommandQueueDestroyResult = zeCommandQueueDestroy(commandQueue);
    if (zeCommandQueueDestroyResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeCommandQueueDestroy() call has failed! Error code = %d", static_cast<int>(zeCommandQueueDestroyResult));
        return -1;
    }

    log<Verbosity::info>("L0 command queue has been destroyed!");

    log<Verbosity::info>("Destroying L0 context via zeContextDestroy()!");
    const auto zeContextDestroyResult = zeContextDestroy(contextHandle);
    if (zeContextDestroyResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeContextDestroy() call has failed! Error code = %d", static_cast<int>(zeContextDestroyResult));
        return -1;
    }

    log<Verbosity::info>("L0 context has been destroyed!");

    if (childProcesses.size()) {
        log<Verbosity::info>("Waiting for child processes");
        for (auto pid : childProcesses) {
            log<Verbosity::info>("Waiting for child process : %d", pid);
            waitpid(pid, nullptr, 0);
        }
        log<Verbosity::info>("Child processes finished");
        log<Verbosity::info>("Exiting parent process");
    }

    log<Verbosity::info>("End of test %s", argv[0]);

    return 0;
}
