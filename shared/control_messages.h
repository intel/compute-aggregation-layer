/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "shared/ipc.h"
#include "shared/utils.h"

#include <limits.h>
#include <sys/types.h>
#include <type_traits>
#include <unistd.h>

namespace Cal {

namespace Messages {

struct ControlMessageNop {
    Cal::Ipc::ControlMessageHeader header = {};
    ControlMessageNop() {
        header.type = Cal::Ipc::ControlMessageHeader::messageTypeNop;
        header.subtype = 0U;
    }
};
static_assert(std::is_standard_layout<ControlMessageNop>::value);

struct ReqHandshake {
    Cal::Ipc::ControlMessageHeader header = {};

    static constexpr uint16_t messageSubtype = 1;
    enum ClientType : uint32_t { unknown,
                                 ocl,
                                 l0 };

    pid_t pid = 0;
    pid_t ppid = 0;
    char clientProcessName[512] = {};
    uint32_t clientType = unknown;

    ReqHandshake() {
        this->header.subtype = ReqHandshake::messageSubtype;
    }

    ReqHandshake(ClientType clientType) {
        this->header.type = Cal::Ipc::ControlMessageHeader::messageTypeRequest;
        this->header.subtype = ReqHandshake::messageSubtype;
        this->pid = getpid();
        this->ppid = getppid();
        this->clientType = clientType;
        auto processName = Cal::Utils::getProcessName();
        strncpy(this->clientProcessName, processName.data(), sizeof(this->clientProcessName));
    }

    bool isInvalid() const {
        bool invalid = false;
        invalid = invalid || (this->header.type != Cal::Ipc::ControlMessageHeader::messageTypeRequest);
        invalid = invalid || (this->header.subtype != ReqHandshake::messageSubtype);
        invalid = invalid || (this->pid == 0);
        invalid = invalid || ((this->clientType != ocl) && (this->clientType != l0));
        if (invalid) {
            log<Verbosity::error>("Message ReqHandshake is not valid");
        }
        return invalid;
    }

    const char *clientTypeStr() const {
        switch (this->clientType) {
        default:
            return "unknown";
        case ocl:
            return "ocl";
        case l0:
            return "l0";
        }
    }
};
static_assert(std::is_standard_layout<ReqHandshake>::value);

struct RespHandshake {
    Cal::Ipc::ControlMessageHeader header = {};

    static constexpr uint16_t messageSubtype = 2;

    void init() {
        this->header.type = Cal::Ipc::ControlMessageHeader::messageTypeRequest;
        this->header.subtype = RespHandshake::messageSubtype;
        this->pid = getpid();
    }

    bool isInvalid() const {
        bool invalid = false;
        invalid = invalid || (this->header.type != Cal::Ipc::ControlMessageHeader::messageTypeRequest);
        invalid = invalid || (this->header.subtype != RespHandshake::messageSubtype);
        invalid = invalid || (this->pid == 0);
        if (invalid) {
            log<Verbosity::error>("Message RespHandshake is not valid");
        }
        return invalid;
    }

    pid_t pid = 0;
    char mallocShmemLibraryPath[PATH_MAX] = {};
};
static_assert(std::is_standard_layout<RespHandshake>::value);

struct ReqAllocateShmem {
    Cal::Ipc::ControlMessageHeader header = {};

    static constexpr uint16_t messageSubtype = 3;
    enum AllocationPurpose : uint32_t { unknown,
                                        rpcMessageChannel };

    ReqAllocateShmem() {
        header.type = Cal::Ipc::ControlMessageHeader::messageTypeRequest;
        header.subtype = ReqAllocateShmem::messageSubtype;
    }

    bool isInvalid() const {
        bool invalid = false;
        invalid = invalid || (this->header.type != Cal::Ipc::ControlMessageHeader::messageTypeRequest);
        invalid = invalid || (this->header.subtype != ReqAllocateShmem::messageSubtype);
        if (invalid) {
            log<Verbosity::error>("Message ReqAllocateShmem is not valid");
        }
        return invalid;
    }

    const char *purposeStr() const {
        switch (this->purpose) {
        default:
            return "unknown";
        case rpcMessageChannel:
            return "rpcMessageChannel";
        }
    }

    size_t size = 0U;
    size_t minimumSize = 0U;
    uint32_t purpose = unknown;
};
static_assert(std::is_standard_layout<ReqAllocateShmem>::value);

struct RespAllocateShmem {
    Cal::Ipc::ControlMessageHeader header = {};

    static constexpr uint16_t messageSubtype = 4;

    RespAllocateShmem() {
        header.type = Cal::Ipc::ControlMessageHeader::messageTypeRequest;
        header.subtype = RespAllocateShmem::messageSubtype;
    }

    bool isInvalid() const {
        bool invalid = false;
        invalid = invalid || (this->header.type != Cal::Ipc::ControlMessageHeader::messageTypeRequest);
        invalid = invalid || (this->header.subtype != RespAllocateShmem::messageSubtype);
        if (invalid) {
            log<Verbosity::error>("Message RespAllocateShmem is not valid");
        }
        return invalid;
    }

    size_t size = 0U;
    int id = -1;
};
static_assert(std::is_standard_layout<RespAllocateShmem>::value);

struct ReqLaunchRpcShmemRingBuffer {
    Cal::Ipc::ControlMessageHeader header = {};

    static constexpr uint16_t messageSubtype = 5;
    enum SynchronizationMethod : uint32_t { unknown,
                                            activePooling,
                                            semaphores,
                                            adaptive };

    ReqLaunchRpcShmemRingBuffer() {
        header.type = Cal::Ipc::ControlMessageHeader::messageTypeRequest;
        header.subtype = ReqLaunchRpcShmemRingBuffer::messageSubtype;
    }

    bool isInvalid() const {
        bool invalid = false;
        invalid = invalid || (this->header.type != Cal::Ipc::ControlMessageHeader::messageTypeRequest);
        invalid = invalid || (this->header.subtype != ReqLaunchRpcShmemRingBuffer::messageSubtype);
        invalid = invalid || (this->ringbufferShmemId == -1);
        invalid = invalid || (this->headOffsetWithinShmem == -1);
        invalid = invalid || (this->tailOffsetWithinShmem == -1);
        invalid = invalid || (this->iterationOffsetWithinShmem == -1);
        invalid = invalid || (this->clientSemaphoreOffsetWithinShmem == -1);
        invalid = invalid || (this->serverSemaphoreOffsetWithinShmem == -1);
        invalid = invalid || (this->synchronizationMethod == unknown);
        if (invalid) {
            log<Verbosity::error>("Message ReqLaunchRpcShmemRingBuffer is not valid");
        }
        return invalid;
    }

    const char *synchronizationMethodStr() const {
        switch (this->synchronizationMethod) {
        default:
            return "unknown";
        case activePooling:
            return "activePooling";
        case semaphores:
            return "semaphores";
        case adaptive:
            return "adaptive";
        }
    }

    int ringbufferShmemId = -1;
    int64_t headOffsetWithinShmem = -1;
    int64_t tailOffsetWithinShmem = -1;
    int64_t iterationOffsetWithinShmem = -1;
    int64_t clientSemaphoreOffsetWithinShmem = -1;
    int64_t serverSemaphoreOffsetWithinShmem = -1;
    int64_t ringStartOffsetWithinShmem = -1;
    uint32_t synchronizationMethod = unknown;
};
static_assert(std::is_standard_layout<ReqLaunchRpcShmemRingBuffer>::value);

struct RespLaunchRpcShmemRingBuffer {
    Cal::Ipc::ControlMessageHeader header = {};

    static constexpr uint16_t messageSubtype = 6;
    enum SynchronizationMethod : uint32_t { activePooling,
                                            semaphores,
                                            adaptive };

    RespLaunchRpcShmemRingBuffer() {
        header.type = Cal::Ipc::ControlMessageHeader::messageTypeRequest;
        header.subtype = RespLaunchRpcShmemRingBuffer::messageSubtype;
    }

    bool isInvalid() const {
        bool invalid = false;
        invalid = invalid || (this->header.type != Cal::Ipc::ControlMessageHeader::messageTypeRequest);
        invalid = invalid || (this->header.subtype != RespLaunchRpcShmemRingBuffer::messageSubtype);
        if (invalid) {
            log<Verbosity::error>("Message RespLaunchRpcShmemRingBuffer is not valid");
        }
        return invalid;
    }
};
static_assert(std::is_standard_layout<RespLaunchRpcShmemRingBuffer>::value);

struct ReqNegotiateUsmAddressRange {
    Cal::Ipc::ControlMessageHeader header = {};

    static constexpr uint16_t messageSubtype = 6;

    ReqNegotiateUsmAddressRange() {
        header.type = Cal::Ipc::ControlMessageHeader::messageTypeRequest;
        header.subtype = ReqNegotiateUsmAddressRange::messageSubtype;
    }

    bool isInvalid() const {
        bool invalid = false;
        invalid = invalid || (false == Cal::Utils::isAlignedPow2<Cal::Utils::pageSize4KB>(this->proposedUsmBase));
        invalid = invalid || (false == Cal::Utils::isAlignedPow2<Cal::Utils::pageSize4KB>(this->proposedUsmSize));
        if (invalid) {
            log<Verbosity::error>("Message ReqNegotiateUsmAddressSpace is not valid");
        }
        return invalid;
    }

    void *proposedUsmBase = nullptr;
    size_t proposedUsmSize = 0;
};
static_assert(std::is_standard_layout<ReqNegotiateUsmAddressRange>::value);

inline bool operator==(const ReqNegotiateUsmAddressRange &lhs, const ReqNegotiateUsmAddressRange &rhs) {
    return (lhs.proposedUsmBase == rhs.proposedUsmBase) && (lhs.proposedUsmSize == rhs.proposedUsmSize);
}

struct RespNegotiateUsmAddressRange {
    Cal::Ipc::ControlMessageHeader header = {};

    static constexpr uint16_t messageSubtype = 7;

    RespNegotiateUsmAddressRange() {
        header.type = Cal::Ipc::ControlMessageHeader::messageTypeRequest;
        header.subtype = RespNegotiateUsmAddressRange::messageSubtype;
    }

    bool isInvalid() const {
        bool invalid = false;
        invalid = invalid || (false == Cal::Utils::isAlignedPow2<Cal::Utils::pageSize4KB>(this->proposedUsmBase));
        invalid = invalid || (false == Cal::Utils::isAlignedPow2<Cal::Utils::pageSize4KB>(this->proposedUsmSize));
        if (invalid) {
            log<Verbosity::error>("Message RespNegotiateUsmAddressRange is not valid");
        }
        return invalid;
    }

    void *proposedUsmBase = nullptr;
    size_t proposedUsmSize = 0;
};
static_assert(std::is_standard_layout<RespNegotiateUsmAddressRange>::value);

inline bool operator==(const RespNegotiateUsmAddressRange &lhs, const RespNegotiateUsmAddressRange &rhs) {
    return (lhs.proposedUsmBase == rhs.proposedUsmBase) && (lhs.proposedUsmSize == rhs.proposedUsmSize);
}

struct ReqImportAddressSpace {
    Cal::Ipc::ControlMessageHeader header = {};

    static constexpr uint16_t messageSubtype = 8;

    ReqImportAddressSpace() {
        header.type = Cal::Ipc::ControlMessageHeader::messageTypeRequest;
        header.subtype = ReqImportAddressSpace::messageSubtype;
    }

    bool isInvalid() const {
        bool invalid = false;
        invalid = invalid || (addressSpace <= 0);
        if (invalid) {
            log<Verbosity::error>("Message ReqImportAddressSpace is not valid");
        }
        return invalid;
    }

    malloc_shmem_exported_address_space_handle_t addressSpace = -1;
};
static_assert(std::is_standard_layout<ReqImportAddressSpace>::value);

struct RespImportAddressSpace {
    Cal::Ipc::ControlMessageHeader header = {};

    static constexpr uint16_t messageSubtype = 9;

    RespImportAddressSpace() {
        header.type = Cal::Ipc::ControlMessageHeader::messageTypeRequest;
        header.subtype = RespImportAddressSpace::messageSubtype;
    }

    bool isInvalid() const {
        bool invalid = false;
        if (invalid) {
            log<Verbosity::error>("Message RespImportAddressSpace is not valid");
        }
        return invalid;
    }

    bool allowedToUseZeroCopyForMallocShmem = false;
};
static_assert(std::is_standard_layout<RespImportAddressSpace>::value);

} // namespace Messages

} // namespace Cal
