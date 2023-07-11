/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "shared/log.h"
#include "shared/utils.h"

#include <cstdio>
#include <cstdlib>
#include <dlfcn.h>
#include <mutex>

namespace Cal::Icd::MallocOverride {

enum class MallocOverrideMode {
    Disabled,
    CalMallocAsShmem,
};

const char *getCalMallocOverrideInitError();
MallocOverrideMode getMode();

struct MallocShmemState {
    const char *resourcePath;
    void *baseAddress = nullptr;
    size_t capacity = 0;
    size_t size = 0;
    int fd = -1;
};

MallocShmemState readMallocShmemState();

class MallocShmemExporter {
  public:
    MallocShmemExporter() {
        auto initState = readMallocShmemState();
        this->localRange = Cal::Utils::AddressRange(initState.baseAddress, initState.capacity);
    }

    MallocShmemExporter(const MallocShmemExporter &) = delete;
    MallocShmemExporter &operator=(const MallocShmemExporter &) = delete;

    bool isAllowed() const {
        bool available = (Cal::Icd::MallocOverride::MallocOverrideMode::CalMallocAsShmem == Cal::Icd::MallocOverride::getMode());
        if ((false == available) && enabled) {
            log<Verbosity::debug>("CAL malloc override not available because : %s", Cal::Icd::MallocOverride::getCalMallocOverrideInitError());
        }
        return available && enabled;
    }

    void enable() {
        enabled = true;
    }

    void disable() {
        enabled = false;
    }

    bool isRegionSharable(const void *ptr, size_t size) {
        bool sharable = localRange.contains({ptr, size});
        if (sharable) {
            printf("SHARABEL!!!\n\n");
        }
        return sharable;
    }

    uintptr_t getRemoteAddress(void *currentProcessPtr) {
        if (nullptr == currentProcessPtr) {
            return 0U;
        }
        if (false == localRange.contains(currentProcessPtr)) {
            return std::numeric_limits<std::uintptr_t>::max();
        }
        auto diff = Cal::Utils::byteDistanceAbs(localRange.base(), currentProcessPtr);
        return remoteHeapBase + diff;
    }

    const char *getResourcePath() const {
        return Cal::Icd::MallocOverride::readMallocShmemState().resourcePath;
    }

    size_t getHeapSize() const {
        return Cal::Icd::MallocOverride::readMallocShmemState().size;
    }

    size_t getHeapCapacity() const {
        return Cal::Icd::MallocOverride::readMallocShmemState().capacity;
    }

    void *getHeapBaseAddress() const {
        return Cal::Icd::MallocOverride::readMallocShmemState().baseAddress;
    }

    uintptr_t getRemoteHeapBaseAddress() {
        return remoteHeapBase;
    }

    void setRemoteHeapBaseAddress(uintptr_t baseAddress) {
        remoteHeapBase = baseAddress;
    }

  protected:
    bool enabled = true;

    Cal::Utils::AddressRange localRange;
    uintptr_t remoteHeapBase = std::numeric_limits<uintptr_t>::max();
};

} // namespace Cal::Icd::MallocOverride
