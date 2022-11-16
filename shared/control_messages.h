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

        auto dstSize = sizeof(this->clientProcessName);
        strncpy(this->clientProcessName, processName.data(), dstSize - 1);
        this->clientProcessName[dstSize - 1] = '\0';
    }

    bool isInvalid() const {
        uint32_t invalid = 0;
        invalid |= (this->header.type != Cal::Ipc::ControlMessageHeader::messageTypeRequest) ? 1 : 0;
        invalid |= (this->header.subtype != ReqHandshake::messageSubtype) ? 1 : 0;
        invalid |= (this->pid == 0) ? 1 : 0;
        invalid |= (((this->clientType != ocl) ? 1 : 0) & ((this->clientType != l0) ? 1 : 0));
        if (0 != invalid) {
            log<Verbosity::error>("Message ReqHandshake is not valid");
        }
        return 0 != invalid;
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
        uint32_t invalid = 0;
        invalid |= (this->header.type != Cal::Ipc::ControlMessageHeader::messageTypeRequest) ? 1 : 0;
        invalid |= (this->header.subtype != RespHandshake::messageSubtype) ? 1 : 0;
        invalid |= (this->pid == 0) ? 1 : 0;
        if (0 != invalid) {
            log<Verbosity::error>("Message RespHandshake is not valid");
        }
        return 0 != invalid;
    }

    pid_t pid = 0;
    uint64_t assignedClientOrdinal = 0;
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
        uint32_t invalid = 0;
        invalid |= (this->header.type != Cal::Ipc::ControlMessageHeader::messageTypeRequest) ? 1 : 0;
        invalid |= (this->header.subtype != ReqAllocateShmem::messageSubtype) ? 1 : 0;
        if (0 != invalid) {
            log<Verbosity::error>("Message ReqAllocateShmem is not valid");
        }
        return 0 != invalid;
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
    AllocationPurpose purpose = unknown;
};
static_assert(std::is_standard_layout<ReqAllocateShmem>::value);

inline bool operator==(const ReqAllocateShmem &lhs, const ReqAllocateShmem &rhs) {
    return (lhs.size == rhs.size) && (lhs.purpose == rhs.purpose);
}

struct RespAllocateShmem {
    Cal::Ipc::ControlMessageHeader header = {};

    static constexpr uint16_t messageSubtype = 4;

    RespAllocateShmem() {
        header.type = Cal::Ipc::ControlMessageHeader::messageTypeRequest;
        header.subtype = RespAllocateShmem::messageSubtype;
    }

    bool isInvalid() const {
        uint32_t invalid = 0;
        invalid |= (this->header.type != Cal::Ipc::ControlMessageHeader::messageTypeRequest) ? 1 : 0;
        invalid |= (this->header.subtype != RespAllocateShmem::messageSubtype) ? 1 : 0;
        if (0 != invalid) {
            log<Verbosity::error>("Message RespAllocateShmem is not valid");
        }
        return 0 != invalid;
    }

    size_t size = 0U;
    int id = -1;
};
static_assert(std::is_standard_layout<RespAllocateShmem>::value);

inline bool operator==(const RespAllocateShmem &lhs, const RespAllocateShmem &rhs) {
    return (lhs.size == rhs.size) && (lhs.id == rhs.id);
}

using OffsetWithinChannelT = int64_t;
constexpr OffsetWithinChannelT invalidOffsetWithinChannel = -1;

//                                          ringStart                   ringStart+ringCapacity / completionStampsStart    heapStart                      heapEnd
// |       HEADER                              |                 RING                  |         COMPLETION_STAMPS          |        HEAP                    |
// | semClient , semServer, ringHead, ringTail |           MESSAGE_OFFSETs             |                                    |  MESSAGES  /  TEMP BUFFERS     |
//                                                     |                        |
//                                                 *ringHead               *ringTail
struct CommandsChannelLayout {
    // HEADER :
    OffsetWithinChannelT semClient = invalidOffsetWithinChannel;
    OffsetWithinChannelT semServer = invalidOffsetWithinChannel;
    OffsetWithinChannelT ringHead = invalidOffsetWithinChannel;
    OffsetWithinChannelT ringTail = invalidOffsetWithinChannel;
    // RING :
    OffsetWithinChannelT ringStart = invalidOffsetWithinChannel;
    uint64_t ringCapacity = 0U;
    // COMPLETION_STAMPS
    OffsetWithinChannelT completionStampsStart = invalidOffsetWithinChannel;
    uint64_t completionStampsCapacity = 0U;
    // HEAP :
    OffsetWithinChannelT heapStart = invalidOffsetWithinChannel;
    OffsetWithinChannelT heapEnd = invalidOffsetWithinChannel;

    bool isValid() const {
        uint32_t valid = 1;
        valid &= (semClient >= 0) ? 1 : 0;
        valid &= (semServer >= 0) ? 1 : 0;
        valid &= (ringHead >= 0) ? 1 : 0;
        valid &= (ringTail >= 0) ? 1 : 0;

        valid &= (ringStart >= 0) ? 1 : 0;
        valid &= (ringCapacity > 0U) ? 1 : 0;

        valid &= (completionStampsStart >= 0) ? 1 : 0;
        valid &= (completionStampsCapacity > 0U) ? 1 : 0;

        valid &= (heapStart >= 0) ? 1 : 0;
        valid &= (heapEnd >= 0) ? 1 : 0;

        if (0 == valid) {
            log<Verbosity::debug>("Commands channel layout is invalid (invalid offsets).");
        }

        return 0 != valid;
    }

    bool isInvalid() const {
        return false == isValid();
    }
};
static_assert(std::is_standard_layout<CommandsChannelLayout>::value);

inline bool operator==(const CommandsChannelLayout &lhs, const CommandsChannelLayout &rhs) {
    uint32_t same = 1;
    same &= (lhs.semClient == rhs.semClient) ? 1 : 0;
    same &= (lhs.semServer == rhs.semServer) ? 1 : 0;
    same &= (lhs.ringHead == rhs.ringHead) ? 1 : 0;
    same &= (lhs.ringTail == rhs.ringTail) ? 1 : 0;

    same &= (lhs.ringStart == rhs.ringStart) ? 1 : 0;
    same &= (lhs.ringCapacity == rhs.ringCapacity) ? 1 : 0;

    same &= (lhs.completionStampsStart == rhs.completionStampsStart) ? 1 : 0;
    same &= (lhs.completionStampsCapacity == rhs.completionStampsCapacity) ? 1 : 0;

    same &= (lhs.heapStart == rhs.heapStart) ? 1 : 0;
    same &= (lhs.heapEnd == rhs.heapEnd) ? 1 : 0;

    return same == 1;
}

struct ReqLaunchRpcShmemRingBuffer {
    Cal::Ipc::ControlMessageHeader header = {};

    static constexpr uint16_t messageSubtype = 5;

    ReqLaunchRpcShmemRingBuffer() {
        header.type = Cal::Ipc::ControlMessageHeader::messageTypeRequest;
        header.subtype = ReqLaunchRpcShmemRingBuffer::messageSubtype;
    }

    bool isInvalid() const {
        uint32_t invalid = 0;
        invalid |= (this->header.type != Cal::Ipc::ControlMessageHeader::messageTypeRequest) ? 1 : 0;
        invalid |= (this->header.subtype != ReqLaunchRpcShmemRingBuffer::messageSubtype) ? 1 : 0;
        invalid |= (this->ringbufferShmemId == -1) ? 1 : 0;
        invalid |= this->layout.isInvalid() ? 1 : 0;
        if (0 != invalid) {
            log<Verbosity::error>("Message ReqLaunchRpcShmemRingBuffer is not valid");
        }
        return 0 != invalid;
    }

    int ringbufferShmemId = -1;

    CommandsChannelLayout layout;
};
static_assert(std::is_standard_layout<ReqLaunchRpcShmemRingBuffer>::value);

inline bool operator==(const ReqLaunchRpcShmemRingBuffer &lhs, const ReqLaunchRpcShmemRingBuffer &rhs) {
    return (lhs.layout == rhs.layout) && (lhs.ringbufferShmemId == rhs.ringbufferShmemId);
}

struct RespLaunchRpcShmemRingBuffer {
    Cal::Ipc::ControlMessageHeader header = {};

    static constexpr uint16_t messageSubtype = 6;
    enum ServiceSynchronizationMethod : uint32_t { unknown,
                                                   activePolling, // service polls for new requests in busy loop
                                                   semaphores,    // service requires client to signal new request using semaphore
    };

    RespLaunchRpcShmemRingBuffer() {
        header.type = Cal::Ipc::ControlMessageHeader::messageTypeRequest;
        header.subtype = RespLaunchRpcShmemRingBuffer::messageSubtype;
    }

    bool isInvalid() const {
        uint32_t invalid = 0;
        invalid |= (this->header.type != Cal::Ipc::ControlMessageHeader::messageTypeRequest) ? 1 : 0;
        invalid |= (this->header.subtype != RespLaunchRpcShmemRingBuffer::messageSubtype) ? 1 : 0;
        invalid |= (this->serviceSynchronizationMethod == unknown) ? 1 : 0;
        if (0 != invalid) {
            log<Verbosity::error>("Message RespLaunchRpcShmemRingBuffer is not valid");
        }
        return 0 != invalid;
    }

    static const char *asCStr(ServiceSynchronizationMethod e) {
        switch (e) {
        default:
            return "unknown";
        case activePolling:
            return "activePolling";
        case semaphores:
            return "semaphores";
        }
    }

    ServiceSynchronizationMethod serviceSynchronizationMethod = unknown;
};
static_assert(std::is_standard_layout<RespLaunchRpcShmemRingBuffer>::value);

inline bool operator==(const RespLaunchRpcShmemRingBuffer &lhs, const RespLaunchRpcShmemRingBuffer &rhs) {
    return (lhs.serviceSynchronizationMethod == rhs.serviceSynchronizationMethod);
}

struct ReqNegotiateUsmAddressRange {
    Cal::Ipc::ControlMessageHeader header = {};

    static constexpr uint16_t messageSubtype = 6;

    ReqNegotiateUsmAddressRange() {
        header.type = Cal::Ipc::ControlMessageHeader::messageTypeRequest;
        header.subtype = ReqNegotiateUsmAddressRange::messageSubtype;
    }

    bool isInvalid() const {
        uint32_t invalid = 0;
        invalid |= (false == Cal::Utils::isAlignedPow2<Cal::Utils::pageSize4KB>(this->proposedUsmBase)) ? 1 : 0;
        invalid |= (false == Cal::Utils::isAlignedPow2<Cal::Utils::pageSize4KB>(this->proposedUsmSize)) ? 1 : 0;
        if (0 != invalid) {
            log<Verbosity::error>("Message ReqNegotiateUsmAddressSpace is not valid");
        }
        return 0 != invalid;
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
        uint32_t invalid = 0;
        invalid |= (false == Cal::Utils::isAlignedPow2<Cal::Utils::pageSize4KB>(this->proposedUsmBase)) ? 1 : 0;
        invalid |= (false == Cal::Utils::isAlignedPow2<Cal::Utils::pageSize4KB>(this->proposedUsmSize)) ? 1 : 0;
        if (0 != invalid) {
            log<Verbosity::error>("Message RespNegotiateUsmAddressRange is not valid");
        }
        return 0 != invalid;
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
        uint32_t invalid = 0;
        invalid |= (addressSpace <= 0) ? 1 : 0;
        if (0 != invalid) {
            log<Verbosity::error>("Message ReqImportAddressSpace is not valid");
        }
        return 0 != invalid;
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
        return false;
    }

    bool allowedToUseZeroCopyForMallocShmem = false;
};
static_assert(std::is_standard_layout<RespImportAddressSpace>::value);

struct ReqPageFault {
    Cal::Ipc::ControlMessageHeader header = {};

    static constexpr uint16_t messageSubtype = 10;

    ReqPageFault(const void *ptr) : ptr(ptr) {
        this->header.type = Cal::Ipc::ControlMessageHeader::messageTypeRequest;
        this->header.subtype = ReqPageFault::messageSubtype;
    }

    bool isInvalid() const {
        uint32_t invalid = 0;
        invalid |= (this->header.type != Cal::Ipc::ControlMessageHeader::messageTypeRequest) ? 1 : 0;
        invalid |= (this->header.subtype != ReqPageFault::messageSubtype) ? 1 : 0;
        invalid |= ptr == nullptr;
        if (0 != invalid) {
            log<Verbosity::error>("Message ReqPageFault is not valid");
        }
        return 0 != invalid;
    }

    const void *ptr;
};
static_assert(std::is_standard_layout<ReqPageFault>::value);

struct RespPageFault {
    Cal::Ipc::ControlMessageHeader header = {};

    static constexpr uint16_t messageSubtype = 11;

    RespPageFault() {
        this->header.type = Cal::Ipc::ControlMessageHeader::messageTypeRequest;
        this->header.subtype = RespPageFault::messageSubtype;
    }

    bool isInvalid() const {
        uint32_t invalid = 0;
        invalid |= (this->header.type != Cal::Ipc::ControlMessageHeader::messageTypeRequest) ? 1 : 0;
        invalid |= (this->header.subtype != RespPageFault::messageSubtype) ? 1 : 0;
        if (0 != invalid) {
            log<Verbosity::error>("Message RespPageFault is not valid");
        }
        return 0 != invalid;
    }
};
static_assert(std::is_standard_layout<RespPageFault>::value);

} // namespace Messages

} // namespace Cal
