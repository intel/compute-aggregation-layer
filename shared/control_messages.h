/*
 * Copyright (C) 2022-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "shared/api_types.h"
#include "shared/ipc.h"
#include "shared/utils.h"

#include <limits.h>
#include <linux/taskstats.h>
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

    ReqHandshake(bool initClientInfo) {
        this->header.type = Cal::Ipc::ControlMessageHeader::messageTypeRequest;
        this->header.subtype = ReqHandshake::messageSubtype;
        if (initClientInfo) {
            this->pid = getpid();
            this->ppid = getppid();
            auto processName = Cal::Utils::getProcessName();

            auto dstSize = sizeof(this->clientProcessName);
            strncpy(this->clientProcessName, processName.data(), dstSize - 1);
            this->clientProcessName[dstSize - 1] = '\0';
        }
    }

    bool isInvalid() const {
        uint32_t invalid = 0;
        invalid |= (this->header.type != Cal::Ipc::ControlMessageHeader::messageTypeRequest) ? 1 : 0;
        invalid |= (this->header.subtype != ReqHandshake::messageSubtype) ? 1 : 0;
        invalid |= (this->pid == 0) ? 1 : 0;
        if (0 != invalid) {
            log<Verbosity::error>("Message ReqHandshake is not valid");
        }
        return 0 != invalid;
    }

    friend void sanitizeReceivedData(ReqHandshake *reqHandshake) {
        reqHandshake->clientProcessName[TS_COMM_LEN - 1] = '\0';
    }

    pid_t pid = 0;
    pid_t ppid = 0;
    char clientProcessName[TS_COMM_LEN] = {};
};
static_assert(std::is_standard_layout<ReqHandshake>::value);

struct RespHandshake {
    Cal::Ipc::ControlMessageHeader header = {};

    static constexpr uint16_t messageSubtype = 2;

    RespHandshake() {
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
    bool sharedVa = false;
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
    void *sharedVa = nullptr;
};
static_assert(std::is_standard_layout<RespAllocateShmem>::value);

inline bool operator==(const RespAllocateShmem &lhs, const RespAllocateShmem &rhs) {
    return (lhs.size == rhs.size) && (lhs.id == rhs.id);
}

using OffsetWithinChannelT = int64_t;
constexpr OffsetWithinChannelT invalidOffsetWithinChannel = -1;

//                                          rpcRingStart                   ringStart+ringCapacity / completionStampsStart  hostptrCopiesRingHead               callbacksRingHead               serviceHeapStart                       clientHeapStart                       heapEnd
// |       RPC ring HEADER                     |                 RING                  |         COMPLETION_STAMPS          |    HOSTPTR COPIES HEADER AND RING   |    CALLBACKS HEADER AND RING   |         SERVICE HEAP                  |          CLIENT HEAP           |
// | semClient , semServer, ringHead, ringTail |           MESSAGE_OFFSETs             |                                    |                                     |                                |        UNUSED FOR NOW                 | RPC MESSAGES  /  TEMP BUFFERS  |
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
    // HOSTPTR COPIES RING :
    OffsetWithinChannelT hostptrCopiesRingHead = invalidOffsetWithinChannel;
    OffsetWithinChannelT hostptrCopiesRingTail = invalidOffsetWithinChannel;
    OffsetWithinChannelT hostptrCopiesRingStart = invalidOffsetWithinChannel;
    uint64_t hostptrCopiesRingCapacity = 0U;
    // CALLBACKS RING :
    OffsetWithinChannelT callbacksRingHead = invalidOffsetWithinChannel;
    OffsetWithinChannelT callbacksRingTail = invalidOffsetWithinChannel;
    OffsetWithinChannelT semClientCallback = invalidOffsetWithinChannel;
    OffsetWithinChannelT callbacksRingStart = invalidOffsetWithinChannel;
    uint64_t callbacksRingCapacity = 0U;
    // HEAP :
    OffsetWithinChannelT serviceHeapStart = invalidOffsetWithinChannel;
    OffsetWithinChannelT serviceHeapEnd = invalidOffsetWithinChannel;
    OffsetWithinChannelT clientHeapStart = invalidOffsetWithinChannel;
    OffsetWithinChannelT clientHeapEnd = invalidOffsetWithinChannel;

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

        valid &= (hostptrCopiesRingHead >= 0) ? 1 : 0;
        valid &= (hostptrCopiesRingTail >= 0) ? 1 : 0;
        valid &= (hostptrCopiesRingStart >= 0) ? 1 : 0;
        valid &= (hostptrCopiesRingCapacity > 0U) ? 1 : 0;

        valid &= (callbacksRingHead >= 0) ? 1 : 0;
        valid &= (callbacksRingTail >= 0) ? 1 : 0;
        valid &= (semClientCallback >= 0) ? 1 : 0;
        valid &= (callbacksRingStart >= 0) ? 1 : 0;
        valid &= (callbacksRingCapacity > 0U) ? 1 : 0;

        valid &= (serviceHeapStart >= 0) ? 1 : 0;
        valid &= (serviceHeapEnd >= 0) ? 1 : 0;
        valid &= (clientHeapStart >= 0) ? 1 : 0;
        valid &= (clientHeapEnd >= 0) ? 1 : 0;

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

    same &= (lhs.hostptrCopiesRingHead == rhs.hostptrCopiesRingHead) ? 1 : 0;
    same &= (lhs.hostptrCopiesRingTail == rhs.hostptrCopiesRingTail) ? 1 : 0;
    same &= (lhs.hostptrCopiesRingStart == rhs.hostptrCopiesRingStart) ? 1 : 0;
    same &= (lhs.hostptrCopiesRingCapacity == rhs.hostptrCopiesRingCapacity) ? 1 : 0;

    same &= (lhs.callbacksRingHead == rhs.callbacksRingHead) ? 1 : 0;
    same &= (lhs.callbacksRingTail == rhs.callbacksRingTail) ? 1 : 0;
    same &= (lhs.semClientCallback == rhs.semClientCallback) ? 1 : 0;
    same &= (lhs.callbacksRingStart == rhs.callbacksRingStart) ? 1 : 0;
    same &= (lhs.callbacksRingCapacity == rhs.callbacksRingCapacity) ? 1 : 0;

    same &= (lhs.serviceHeapStart == rhs.serviceHeapStart) ? 1 : 0;
    same &= (lhs.serviceHeapEnd == rhs.serviceHeapEnd) ? 1 : 0;
    same &= (lhs.clientHeapStart == rhs.clientHeapStart) ? 1 : 0;
    same &= (lhs.clientHeapEnd == rhs.clientHeapEnd) ? 1 : 0;

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

    static constexpr uint16_t messageSubtype = 7;

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

    static constexpr uint16_t messageSubtype = 8;

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

    static constexpr uint16_t messageSubtype = 9;

    ReqImportAddressSpace() {
        header.type = Cal::Ipc::ControlMessageHeader::messageTypeRequest;
        header.subtype = ReqImportAddressSpace::messageSubtype;
    }

    bool isInvalid() const {
        return false;
    }

    friend void sanitizeReceivedData(ReqImportAddressSpace *reqImportAddressSpace) {
        reqImportAddressSpace->mallocShmemResourcePath[PATH_MAX - 1] = '\0';
    }

    char mallocShmemResourcePath[PATH_MAX] = {};
    uint64_t clientAddressSpaceBaseAddress = std::numeric_limits<uint64_t>::max();
    size_t clientAddressSpaceSize = 0U;
};
static_assert(std::is_standard_layout<ReqImportAddressSpace>::value);

struct RespImportAddressSpace {
    Cal::Ipc::ControlMessageHeader header = {};

    static constexpr uint16_t messageSubtype = 10;

    RespImportAddressSpace() {
        header.type = Cal::Ipc::ControlMessageHeader::messageTypeRequest;
        header.subtype = RespImportAddressSpace::messageSubtype;
    }

    bool isInvalid() const {
        return false;
    }

    bool successfullyImported = false;
    uintptr_t serviceBaseAddressForClientAddressSpace{};
};
static_assert(std::is_standard_layout<RespImportAddressSpace>::value);

struct ReqPageFault {
    Cal::Ipc::ControlMessageHeader header = {};

    static constexpr uint16_t messageSubtype = 11;

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

    static constexpr uint16_t messageSubtype = 12;

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

struct ReqTransferFd {
    Cal::Ipc::ControlMessageHeader header = {};

    static constexpr uint16_t messageSubtype = 13;
    static constexpr uint16_t maxFdsCount = 4;

    ReqTransferFd(uint16_t usedFdsCount) : usedFdsCount{usedFdsCount} {
        this->header.type = Cal::Ipc::ControlMessageHeader::messageTypeRequest;
        this->header.subtype = ReqTransferFd::messageSubtype;
    }

    bool isInvalid() const {
        uint32_t invalid = 0;
        invalid |= (this->header.type != Cal::Ipc::ControlMessageHeader::messageTypeRequest) ? 1 : 0;
        invalid |= (this->header.subtype != ReqTransferFd::messageSubtype) ? 1 : 0;
        if (0 != invalid) {
            log<Verbosity::error>("Message ReqTransferFd is not valid");
        }
        return 0 != invalid;
    }

    int remoteFds[maxFdsCount] = {};
    uint16_t usedFdsCount{};
};
static_assert(std::is_standard_layout<ReqTransferFd>::value);

struct ReqReverseTransferFd {
    Cal::Ipc::ControlMessageHeader header = {};

    static constexpr uint16_t messageSubtype = 14;
    static constexpr uint16_t maxFdsCount = 4;

    ReqReverseTransferFd(uint16_t numOfFds) : numOfFds(numOfFds) {
        this->header.type = Cal::Ipc::ControlMessageHeader::messageTypeRequest;
        this->header.subtype = ReqReverseTransferFd::messageSubtype;
    }

    bool isInvalid() const {
        uint32_t invalid = 0;
        invalid |= (this->header.type != Cal::Ipc::ControlMessageHeader::messageTypeRequest) ? 1 : 0;
        invalid |= (this->header.subtype != ReqReverseTransferFd::messageSubtype) ? 1 : 0;
        invalid |= (this->numOfFds > maxFdsCount) ? 1 : 0;
        if (0 != invalid) {
            log<Verbosity::error>("Message ReqReverseTransferFd is not valid");
        }
        return 0 != invalid;
    }

    uint16_t numOfFds;
};
static_assert(std::is_standard_layout<ReqReverseTransferFd>::value);

struct RespReverseTransferFd {
    Cal::Ipc::ControlMessageHeader header = {};

    static constexpr uint16_t messageSubtype = 15;
    static constexpr uint16_t maxFdsCount = 4;

    RespReverseTransferFd() {
        this->header.type = Cal::Ipc::ControlMessageHeader::messageTypeRequest;
        this->header.subtype = RespReverseTransferFd::messageSubtype;
    }

    bool isInvalid() const {
        uint32_t invalid = 0;
        invalid |= (this->header.type != Cal::Ipc::ControlMessageHeader::messageTypeRequest) ? 1 : 0;
        invalid |= (this->header.subtype != RespReverseTransferFd::messageSubtype) ? 1 : 0;
        if (0 != invalid) {
            log<Verbosity::error>("Message RespReverseTransferFd is not valid");
        }
        return 0 != invalid;
    }

    int remoteFds[maxFdsCount] = {};
};
static_assert(std::is_standard_layout<RespReverseTransferFd>::value);

struct ReqCheckApiAvailability {
    Cal::Ipc::ControlMessageHeader header = {};

    static constexpr uint16_t messageSubtype = 16;
    Cal::ApiType api = Cal::ApiType::Unknown;

    ReqCheckApiAvailability() {
        this->header.type = Cal::Ipc::ControlMessageHeader::messageTypeRequest;
        this->header.subtype = ReqCheckApiAvailability::messageSubtype;
    }

    ReqCheckApiAvailability(Cal::ApiType api) {
        this->header.type = Cal::Ipc::ControlMessageHeader::messageTypeRequest;
        this->header.subtype = ReqCheckApiAvailability::messageSubtype;
        this->api = api;
    }

    bool isInvalid() const {
        uint32_t invalid = 0;
        invalid |= (this->header.type != Cal::Ipc::ControlMessageHeader::messageTypeRequest) ? 1 : 0;
        invalid |= (this->header.subtype != ReqCheckApiAvailability::messageSubtype) ? 1 : 0;
        invalid |= (((this->api != Cal::ApiType::OpenCL) ? 1 : 0) & ((this->api != Cal::ApiType::LevelZero) ? 1 : 0));
        if (0 != invalid) {
            log<Verbosity::error>("Message ReqCheckApiAvailability is not valid");
        }
        return 0 != invalid;
    }
};
static_assert(std::is_standard_layout<ReqCheckApiAvailability>::value);

struct RespCheckApiAvailability {
    Cal::Ipc::ControlMessageHeader header = {};

    static constexpr uint16_t messageSubtype = 17;

    RespCheckApiAvailability() {
        this->header.type = Cal::Ipc::ControlMessageHeader::messageTypeRequest;
        this->header.subtype = RespCheckApiAvailability::messageSubtype;
    }

    bool isInvalid() const {
        uint32_t invalid = 0;
        invalid |= (this->header.type != Cal::Ipc::ControlMessageHeader::messageTypeRequest) ? 1 : 0;
        invalid |= (this->header.subtype != RespCheckApiAvailability::messageSubtype) ? 1 : 0;
        if (0 != invalid) {
            log<Verbosity::error>("Message RespCheckApiAvailability is not valid");
        }
        return 0 != invalid;
    }

    bool available = false;
};
static_assert(std::is_standard_layout<RespCheckApiAvailability>::value);

struct ReqRemoteMmap {
    Cal::Ipc::ControlMessageHeader header = {};

    static constexpr uint16_t messageSubtype = 18;

    ReqRemoteMmap() {
        this->header.type = Cal::Ipc::ControlMessageHeader::messageTypeRequest;
        this->header.subtype = ReqRemoteMmap::messageSubtype;
    }

    bool isInvalid() const {
        uint32_t invalid = 0;
        invalid |= (this->header.type != Cal::Ipc::ControlMessageHeader::messageTypeRequest) ? 1 : 0;
        invalid |= (this->header.subtype != ReqRemoteMmap::messageSubtype) ? 1 : 0;
        if (0 != invalid) {
            log<Verbosity::error>("Message ReqRemoteMmap is not valid");
        }
        return 0 != invalid;
    }

    void *address{};
    size_t length{};
    int prot{};
    int flags{};
    int fd{};
    off_t offset{};
};
static_assert(std::is_standard_layout<ReqRemoteMmap>::value);

struct RespRemoteMmap {
    Cal::Ipc::ControlMessageHeader header = {};

    static constexpr uint16_t messageSubtype = 19;

    RespRemoteMmap() {
        header.type = Cal::Ipc::ControlMessageHeader::messageTypeRequest;
        header.subtype = RespRemoteMmap::messageSubtype;
    }

    bool isInvalid() const {
        uint32_t invalid = 0;
        invalid |= (this->header.type != Cal::Ipc::ControlMessageHeader::messageTypeRequest) ? 1 : 0;
        invalid |= (this->header.subtype != RespRemoteMmap::messageSubtype) ? 1 : 0;
        if (0 != invalid) {
            log<Verbosity::error>("Message RespRemoteMmap is not valid");
        }
        return 0 != invalid;
    }

    void *mappedPtr = MAP_FAILED;
};
static_assert(std::is_standard_layout<RespRemoteMmap>::value);

struct ReqOpenGpuDevice {
    Cal::Ipc::ControlMessageHeader header = {};

    static constexpr uint16_t messageSubtype = 20;

    ReqOpenGpuDevice(const char *path) {
        this->header.type = Cal::Ipc::ControlMessageHeader::messageTypeRequest;
        this->header.subtype = ReqOpenGpuDevice::messageSubtype;
        if (path) {
            strncpy(this->devicePath, path, PATH_MAX - 1);
            this->devicePath[PATH_MAX - 1] = '\0';
        } else {
            this->devicePath[0] = '\0';
        }
    }

    ReqOpenGpuDevice() : ReqOpenGpuDevice(nullptr) {
    }

    bool isInvalid() const {
        uint32_t invalid = 0;
        invalid |= (this->header.type != Cal::Ipc::ControlMessageHeader::messageTypeRequest) ? 1 : 0;
        invalid |= (this->header.subtype != ReqOpenGpuDevice::messageSubtype) ? 1 : 0;
        if (0 != invalid) {
            log<Verbosity::error>("Message ReqOpenGpuDevice is not valid");
        }
        return 0 != invalid;
    }

    friend void sanitizeReceivedData(ReqOpenGpuDevice *reqOpenGpuDevice) {
        reqOpenGpuDevice->devicePath[PATH_MAX - 1] = '\0';
    }

    char devicePath[PATH_MAX] = {};
};
static_assert(std::is_standard_layout<ReqOpenGpuDevice>::value);

struct RespOpenGpuDevice {
    Cal::Ipc::ControlMessageHeader header = {};

    static constexpr uint16_t messageSubtype = 21;

    RespOpenGpuDevice() {
        header.type = Cal::Ipc::ControlMessageHeader::messageTypeRequest;
        header.subtype = RespOpenGpuDevice::messageSubtype;
    }

    bool isInvalid() const {
        uint32_t invalid = 0;
        invalid |= (this->header.type != Cal::Ipc::ControlMessageHeader::messageTypeRequest) ? 1 : 0;
        invalid |= (this->header.subtype != RespOpenGpuDevice::messageSubtype) ? 1 : 0;
        if (0 != invalid) {
            log<Verbosity::error>("Message RespOpenGpuDevice is not valid");
        }
        return 0 != invalid;
    }

    int remoteFd = -1;
};
static_assert(std::is_standard_layout<RespOpenGpuDevice>::value);

struct ReqCloseGpuDevice {
    Cal::Ipc::ControlMessageHeader header = {};

    static constexpr uint16_t messageSubtype = 22;

    ReqCloseGpuDevice(int fd) {
        this->header.type = Cal::Ipc::ControlMessageHeader::messageTypeRequest;
        this->header.subtype = ReqCloseGpuDevice::messageSubtype;
        this->remoteFd = fd;
    }

    ReqCloseGpuDevice() : ReqCloseGpuDevice(-1) {
    }

    bool isInvalid() const {
        uint32_t invalid = 0;
        invalid |= (this->header.type != Cal::Ipc::ControlMessageHeader::messageTypeRequest) ? 1 : 0;
        invalid |= (this->header.subtype != ReqCloseGpuDevice::messageSubtype) ? 1 : 0;
        if (0 != invalid) {
            log<Verbosity::error>("Message ReqCloseGpuDevice is not valid");
        }
        return 0 != invalid;
    }

    int remoteFd = -1;
};
static_assert(std::is_standard_layout<ReqCloseGpuDevice>::value);

struct RespCloseGpuDevice {
    Cal::Ipc::ControlMessageHeader header = {};

    static constexpr uint16_t messageSubtype = 23;

    RespCloseGpuDevice() {
        header.type = Cal::Ipc::ControlMessageHeader::messageTypeRequest;
        header.subtype = RespCloseGpuDevice::messageSubtype;
    }

    bool isInvalid() const {
        uint32_t invalid = 0;
        invalid |= (this->header.type != Cal::Ipc::ControlMessageHeader::messageTypeRequest) ? 1 : 0;
        invalid |= (this->header.subtype != RespCloseGpuDevice::messageSubtype) ? 1 : 0;
        if (0 != invalid) {
            log<Verbosity::error>("Message RespCloseGpuDevice is not valid");
        }
        return 0 != invalid;
    }

    int result = -1;
};
static_assert(std::is_standard_layout<RespCloseGpuDevice>::value);

} // namespace Messages
} // namespace Cal
