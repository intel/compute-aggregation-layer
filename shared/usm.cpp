/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "shared/usm.h"

namespace Cal {

namespace Usm {

namespace UsmNegotiationWithRemote {

inline bool isValidMmapAddress(void *ptr) {
    return MAP_FAILED != ptr;
}

template <typename MessageT>
inline bool sendUsmRangeProposal(Cal::Ipc::Connection &remoteConnection, Cal::Utils::AddressRange addressRange) {
    MessageT message = {};
    message.proposedUsmBase = addressRange.base();
    message.proposedUsmSize = addressRange.size();
    if (false == remoteConnection.send(message)) {
        log<Verbosity::error>("Failed to send USM address space proposal (proposed base : %p, proposed size %zu)",
                              message.proposedUsmBase, message.proposedUsmSize);
        return false;
    }
    log<Verbosity::debug>("Sent USM address space proposal (proposed base : %p, proposed size %zu)",
                          message.proposedUsmBase, message.proposedUsmSize);
    return true;
}

template <typename MessageT>
inline bool receiveUsmRangeProposal(Cal::Ipc::Connection &remoteConnection, Cal::Utils::AddressRange &outAddressRange) {
    MessageT message = {};
    if ((false == remoteConnection.receive(message)) || message.isInvalid()) {
        log<Verbosity::error>("Failed to get USM address space proposal");
        return false;
    }
    log<Verbosity::debug>("Received USM address space proposal (proposed base : %p, proposed size %zu)",
                          message.proposedUsmBase, message.proposedUsmSize);
    if (nullptr == message.proposedUsmBase) {
        log<Verbosity::error>("Received NULL USM address space base proposal");
        return false;
    }
    if (0U == message.proposedUsmSize) {
        log<Verbosity::error>("Received USM address space size=0 proposal");
        return false;
    }
    outAddressRange = {message.proposedUsmBase, message.proposedUsmSize};
    return true;
}

inline bool sendUsmRangeProposalToService(Cal::Ipc::Connection &remoteConnection, Cal::Utils::AddressRange addressRange) {
    return sendUsmRangeProposal<Cal::Messages::ReqNegotiateUsmAddressRange>(remoteConnection, addressRange);
}

inline bool sendUsmRangeProposalToClient(Cal::Ipc::Connection &remoteConnection, Cal::Utils::AddressRange addressRange) {
    return sendUsmRangeProposal<Cal::Messages::RespNegotiateUsmAddressRange>(remoteConnection, addressRange);
}

inline bool receiveUsmRangeProposalFromService(Cal::Ipc::Connection &remoteConnection, Cal::Utils::AddressRange &outAddressRange) {
    return receiveUsmRangeProposal<Cal::Messages::RespNegotiateUsmAddressRange>(remoteConnection, outAddressRange);
}

inline bool receiveUsmRangeProposalFromClient(Cal::Ipc::Connection &remoteConnection, Cal::Utils::AddressRange &outAddressRange) {
    return receiveUsmRangeProposal<Cal::Messages::ReqNegotiateUsmAddressRange>(remoteConnection, outAddressRange);
}

inline bool tryMergeUsmRegions(Cal::Utils::AddressRange desiredRange, Cal::Utils::PartitionedAddressRange<> existingReservations) {
    if (false == existingReservations.intersectsSubRanges(desiredRange)) {
        return false;
    }

    log<Verbosity::debug>("Proposed USM address space collides with previous proposal - will try to merges regions to create contigous address space for USM.");
    auto missingSubRanges = existingReservations.getSubRangesDiffFrom(desiredRange);
    for (auto diff : missingSubRanges) {
        void *ptr = UsmMmappedShmemAllocator::reserveUsmCpuRange(diff.base(), diff.size());
        if (isValidMmapAddress(ptr)) {
            existingReservations.insertSubRange({diff.base(), diff.size()});
        } else {
            log<Verbosity::debug>("Could not merge regions to form a contigous USM range. Mmap failed at %p for %zu bytes.", diff.base(), diff.size());
            return false;
        }
    }

    log<Verbosity::debug>("Was able to merge regions to create contigous USM range at  %p for %zu bytes.", desiredRange.base(), desiredRange.size());

    return true;
}

inline bool sendAckToService(Cal::Ipc::Connection &remoteConnection, Cal::Utils::AddressRange addressRange) {
    log<Verbosity::debug>("Proposed USM address space is suitable, sending acknowledgement");
    Cal::Messages::ReqNegotiateUsmAddressRange request = {};
    Cal::Messages::RespNegotiateUsmAddressRange response = {};
    request.proposedUsmBase = addressRange.base();
    request.proposedUsmSize = addressRange.size();
    if (false == remoteConnection.send(request)) {
        log<Verbosity::error>("Failed to send USM address space acknowledgement)");
        return false;
    }
    if ((false == remoteConnection.receive(response)) || response.isInvalid()) {
        log<Verbosity::error>("Failed to get USM address space confirmation");
        return false;
    }
    return true;
}

inline bool sendAckToClient(Cal::Ipc::Connection &remoteConnection, Cal::Utils::AddressRange addressRange) {
    log<Verbosity::debug>("Requested USM address space is suitable, sending acknowledgement");
    Cal::Messages::RespNegotiateUsmAddressRange response = {};
    response.proposedUsmBase = addressRange.base();
    response.proposedUsmSize = addressRange.size();
    if (false == remoteConnection.send(response)) {
        log<Verbosity::error>("Failed to send USM address space acknowledgement)");
        return false;
    }
    return true;
}

inline void cleanupObsoleteAddressReservations(std::optional<Cal::Utils::AddressRange> usedRangeOpt, const Cal::Utils::PartitionedAddressRange<> &allReservations) {
    if (!usedRangeOpt) {
        for (auto &reservationRange : allReservations.getSubRanges()) {
            Cal::Sys::munmap(reservationRange.getBoundingRange().base(), reservationRange.getBoundingRange().size());
        }
        return;
    }

    bool partitionedReservation = false;
    auto usedRange = usedRangeOpt.value();
    for (auto &reservationRange : allReservations.getSubRanges()) {
        auto reservationBoundingRange = reservationRange.getBoundingRange();
        if (false == reservationBoundingRange.intersects(usedRange)) {
            Cal::Sys::munmap(reservationBoundingRange.base(), reservationBoundingRange.size());
            continue;
        }

        if (reservationBoundingRange == usedRange) {
            continue;
        }

        partitionedReservation = true;
        if (reservationBoundingRange.start < usedRange.start) {
            Cal::Sys::munmap(reservationBoundingRange.base(), usedRange.start - reservationBoundingRange.start);
        }

        if (usedRange.end < reservationBoundingRange.end) {
            Cal::Sys::munmap(usedRange.rightBound(), reservationBoundingRange.end - usedRange.end);
        }
    }

    if (partitionedReservation) {
        log<Verbosity::debug>("Merging USM range from multiple mmaps into a single one");
        auto ptr = UsmMmappedShmemAllocator::forceReserveUsmCpuRange(usedRange.base(), usedRange.size());
        if (isValidMmapAddress(ptr)) {
            log<Verbosity::debug>("Succesfully merged USM ranges from multiple reservations into a single one");
        } else {
            log<Verbosity::error>("Failed to merge USM range from multiple reservations into a single one");
        }
    }
}

} // namespace UsmNegotiationWithRemote

std::optional<Cal::Utils::AddressRange> negotiateUsmRangeWithService(Cal::Ipc::Connection &remoteConnection, void *proposedUsmBase, size_t proposedUsmSize, int maxTries) {
    using namespace UsmNegotiationWithRemote;

    std::optional<Cal::Utils::AddressRange> negotiatedRange = {};
    Cal::Utils::PartitionedAddressRange mmapReservations({});

    int tryNum = 0;

    while (tryNum < maxTries) {
        ++tryNum;
        Cal::Utils::AddressRange receivedProposal = {};

        if (false == sendUsmRangeProposalToService(remoteConnection, {proposedUsmBase, proposedUsmSize})) {
            break;
        }

        if (false == receiveUsmRangeProposalFromService(remoteConnection, receivedProposal)) {
            break;
        }

        if (proposedUsmBase == receivedProposal.base()) {
            log<Verbosity::debug>("Compute Aggregation Layer service aggreed on proposed USM address space (proposed base : %p, proposed size %zu)",
                                  receivedProposal.base(), receivedProposal.size());
            negotiatedRange = receivedProposal;
            break;
        }

        void *ptr = UsmMmappedShmemAllocator::reserveUsmCpuRange(receivedProposal.base(), receivedProposal.size());

        if (isValidMmapAddress(ptr)) {
            mmapReservations.insertSubRange(receivedProposal);
        } else {
            if (tryMergeUsmRegions(receivedProposal, mmapReservations)) {
                ptr = receivedProposal.base();
            }
        }

        if (isValidMmapAddress(ptr)) {
            if (false == sendAckToService(remoteConnection, receivedProposal)) {
                break;
            }

            negotiatedRange = receivedProposal;
            break;
        } else {
            log<Verbosity::debug>("Proposed USM address space is not suitable (mmap failed), will try to propose different range.");
            proposedUsmSize = receivedProposal.size();
            proposedUsmBase = UsmMmappedShmemAllocator::reserveUsmCpuRange(NULL, proposedUsmSize);
            if (false == isValidMmapAddress(proposedUsmBase)) {
                log<Verbosity::error>("Failed to propose any USM address space for size : %zu", proposedUsmSize);
                break;
            }
            mmapReservations.insertSubRange({proposedUsmBase, proposedUsmSize});
        }
    }

    cleanupObsoleteAddressReservations(negotiatedRange, mmapReservations);
    if (tryNum >= maxTries) {
        log<Verbosity::error>("Failed to negotiate USM range after %d tries", tryNum);
    }

    return negotiatedRange;
}

std::optional<Cal::Utils::AddressRange> negotiateUsmRangeWithClient(Cal::Ipc::Connection &remoteConnection, void *requestedUsmBase, size_t requestedUsmSize, int maxTries) {
    using namespace UsmNegotiationWithRemote;

    if (0U == requestedUsmSize) {
        return {};
    }
    std::optional<Cal::Utils::AddressRange> negotiatedRange = {};
    Cal::Utils::PartitionedAddressRange mmapReservations({});

    int tryNum = 0;

    size_t usmSize = requestedUsmSize;

    while (tryNum < maxTries) {
        ++tryNum;
        void *ptr = UsmMmappedShmemAllocator::reserveUsmCpuRange(requestedUsmBase, usmSize);
        if (isValidMmapAddress(ptr)) {
            mmapReservations.insertSubRange({ptr, usmSize});
            if (requestedUsmBase) { // address proposed by client
                if (false == sendAckToClient(remoteConnection, {requestedUsmBase, usmSize})) {
                    break;
                }

                negotiatedRange = {requestedUsmBase, usmSize};
                break;
            } else { // new address
                if (false == sendUsmRangeProposalToClient(remoteConnection, {ptr, usmSize})) {
                    break;
                }

                Cal::Utils::AddressRange receivedProposal;
                if (false == receiveUsmRangeProposalFromClient(remoteConnection, receivedProposal)) {
                    break;
                }

                if (receivedProposal.base() == ptr) {
                    if (false == sendAckToClient(remoteConnection, receivedProposal)) {
                        break;
                    }
                    negotiatedRange = {ptr, usmSize};
                    break;
                }

                log<Verbosity::debug>("Client declined USM address space proposal and sent new proposal (proposed base : %p, proposed size %zu)",
                                      receivedProposal.base(), receivedProposal.size());
                requestedUsmBase = receivedProposal.base();
                usmSize = receivedProposal.size();
            }
        } else {                               // MAP_FAILED
            if (nullptr != requestedUsmBase) { // address from client
                log<Verbosity::debug>("Requested USM address space is not suitable (mmap failed), will try to propose different range");
                ptr = UsmMmappedShmemAllocator::reserveUsmCpuRange(NULL, usmSize);
                if (false == isValidMmapAddress(ptr)) {
                    log<Verbosity::error>("Failed to propose any USM address space for size : %zu", usmSize);
                    break;
                }
                mmapReservations.insertSubRange({ptr, usmSize});
                log<Verbosity::debug>("Proposing new USM address space (proposed base : %p, proposed size %zu)", ptr, usmSize);
                if (false == sendUsmRangeProposalToClient(remoteConnection, {ptr, usmSize})) {
                    break;
                }

                Cal::Utils::AddressRange receivedProposal;
                if (false == receiveUsmRangeProposalFromClient(remoteConnection, receivedProposal)) {
                    break;
                }

                if (receivedProposal.base() == ptr) {
                    if (false == sendAckToClient(remoteConnection, receivedProposal)) {
                        break;
                    }
                    negotiatedRange = receivedProposal;
                    break;
                }

                log<Verbosity::debug>("Client declined USM address space proposal and sent new proposal (proposed base : %p, proposed size %zu)",
                                      receivedProposal.base(), receivedProposal.size());
                requestedUsmBase = receivedProposal.base();
                usmSize = receivedProposal.size();
            } else { // new address
                log<Verbosity::error>("Failed to propose any USM address space for size : %zu", usmSize);
                break;
            }
        }
    }

    cleanupObsoleteAddressReservations(negotiatedRange, mmapReservations);
    if (tryNum >= maxTries) {
        log<Verbosity::error>("Failed to negotiate USM range after %d tries", tryNum);
    }

    return negotiatedRange;
}

} // namespace Usm

} // namespace Cal
