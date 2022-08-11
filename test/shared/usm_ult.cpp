/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "shared/usm.h"
#include "test/mocks/connection_mock.h"
#include "test/mocks/log_mock.h"
#include "test/mocks/sys_mock.h"

#include <string>

namespace Cal {

namespace Ult {

TEST(UsmCpuRange, whenReservingUsmCpuRangeThenProperMmapFlagsAreSet) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;

    constexpr auto size = 8192U;
    void *addr = Cal::Usm::reserveUsmCpuRange(nullptr, size);
    EXPECT_NE(nullptr, addr);
    EXPECT_NE(MAP_FAILED, addr);
    ASSERT_EQ(1U, tempSysCallsCtx.vma.getSubRanges().size());
    EXPECT_EQ(Cal::Utils::AddressRange(addr, size), tempSysCallsCtx.vma.getSubRanges()[0].getBoundingRange());
    auto mmapTraits = tempSysCallsCtx.vma.getSubRanges()[0].getTag();
    EXPECT_EQ(nullptr, mmapTraits.addr);
    EXPECT_EQ(size, mmapTraits.length);
    EXPECT_EQ(PROT_NONE, mmapTraits.prot);
    EXPECT_EQ(MAP_PRIVATE | MAP_ANONYMOUS | MAP_NORESERVE, mmapTraits.flags);
    EXPECT_EQ(-1, mmapTraits.fd);
    EXPECT_EQ(0, mmapTraits.offset);

    constexpr auto size2 = 4096U;
    auto addr2 = Cal::Utils::moveByBytes(addr, size);
    addr = Cal::Usm::reserveUsmCpuRange(addr2, size2);
    EXPECT_EQ(addr2, addr);
    ASSERT_EQ(2U, tempSysCallsCtx.vma.getSubRanges().size());
    EXPECT_EQ(Cal::Utils::AddressRange(addr, size2), tempSysCallsCtx.vma.getSubRanges()[1].getBoundingRange());
    mmapTraits = tempSysCallsCtx.vma.getSubRanges()[1].getTag();
    EXPECT_EQ(addr2, mmapTraits.addr);
    EXPECT_EQ(size2, mmapTraits.length);
    EXPECT_EQ(PROT_NONE, mmapTraits.prot);
    EXPECT_EQ(MAP_PRIVATE | MAP_ANONYMOUS | MAP_NORESERVE | MAP_FIXED_NOREPLACE, mmapTraits.flags);
    EXPECT_EQ(-1, mmapTraits.fd);
    EXPECT_EQ(0, mmapTraits.offset);
}

TEST(UsmCpuRange, whenForceReservingUsmCpuRangeThenProperMmapFlagsAreSet) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;

    constexpr auto size = 8192U;
    void *addr = Cal::Usm::forceReserveUsmCpuRange(nullptr, size);
    EXPECT_NE(nullptr, addr);
    EXPECT_NE(MAP_FAILED, addr);
    ASSERT_EQ(1U, tempSysCallsCtx.vma.getSubRanges().size());
    EXPECT_EQ(Cal::Utils::AddressRange(addr, size), tempSysCallsCtx.vma.getSubRanges()[0].getBoundingRange());
    auto mmapTraits = tempSysCallsCtx.vma.getSubRanges()[0].getTag();
    EXPECT_EQ(nullptr, mmapTraits.addr);
    EXPECT_EQ(size, mmapTraits.length);
    EXPECT_EQ(PROT_NONE, mmapTraits.prot);
    EXPECT_EQ(MAP_PRIVATE | MAP_ANONYMOUS | MAP_NORESERVE, mmapTraits.flags);
    EXPECT_EQ(-1, mmapTraits.fd);
    EXPECT_EQ(0, mmapTraits.offset);

    constexpr auto size2 = 4096U;
    auto addr2 = Cal::Utils::moveByBytes(addr, size);
    addr = Cal::Usm::forceReserveUsmCpuRange(addr2, size2);
    EXPECT_EQ(addr2, addr);
    ASSERT_EQ(2U, tempSysCallsCtx.vma.getSubRanges().size());
    EXPECT_EQ(Cal::Utils::AddressRange(addr, size2), tempSysCallsCtx.vma.getSubRanges()[1].getBoundingRange());
    mmapTraits = tempSysCallsCtx.vma.getSubRanges()[1].getTag();
    EXPECT_EQ(addr2, mmapTraits.addr);
    EXPECT_EQ(size2, mmapTraits.length);
    EXPECT_EQ(PROT_NONE, mmapTraits.prot);
    EXPECT_EQ(MAP_PRIVATE | MAP_ANONYMOUS | MAP_NORESERVE | MAP_FIXED, mmapTraits.flags);
    EXPECT_EQ(-1, mmapTraits.fd);
    EXPECT_EQ(0, mmapTraits.offset);
}

TEST(UsmCpuRange, whenCommitingUsmCpuRangeThenProperMmapFlagsAreSet) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;

    constexpr auto size = 8192U;
    void *addr = Cal::Usm::commitUsmCpuRange(nullptr, size);
    EXPECT_NE(nullptr, addr);
    EXPECT_NE(MAP_FAILED, addr);
    ASSERT_EQ(1U, tempSysCallsCtx.vma.getSubRanges().size());
    EXPECT_EQ(Cal::Utils::AddressRange(addr, size), tempSysCallsCtx.vma.getSubRanges()[0].getBoundingRange());
    auto mmapTraits = tempSysCallsCtx.vma.getSubRanges()[0].getTag();
    EXPECT_EQ(nullptr, mmapTraits.addr);
    EXPECT_EQ(size, mmapTraits.length);
    EXPECT_EQ(PROT_READ | PROT_WRITE, mmapTraits.prot);
    EXPECT_EQ(MAP_PRIVATE | MAP_ANONYMOUS, mmapTraits.flags);
    EXPECT_EQ(-1, mmapTraits.fd);
    EXPECT_EQ(0, mmapTraits.offset);

    constexpr auto size2 = 4096U;
    auto addr2 = Cal::Utils::moveByBytes(addr, size);
    addr = Cal::Usm::commitUsmCpuRange(addr2, size2);
    EXPECT_EQ(addr2, addr);
    ASSERT_EQ(2U, tempSysCallsCtx.vma.getSubRanges().size());
    EXPECT_EQ(Cal::Utils::AddressRange(addr, size2), tempSysCallsCtx.vma.getSubRanges()[1].getBoundingRange());
    mmapTraits = tempSysCallsCtx.vma.getSubRanges()[1].getTag();
    EXPECT_EQ(addr2, mmapTraits.addr);
    EXPECT_EQ(size2, mmapTraits.length);
    EXPECT_EQ(PROT_READ | PROT_WRITE, mmapTraits.prot);
    EXPECT_EQ(MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, mmapTraits.flags);
    EXPECT_EQ(-1, mmapTraits.fd);
    EXPECT_EQ(0, mmapTraits.offset);
}

TEST(UsmCpuRange, whenMappingUsmCpuRangeToFdThenProperMmapFlagsAndFdAreSet) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    int fd = 7;

    constexpr auto size = 8192U;
    void *addr = Cal::Usm::mapUsmCpuRangeToFd(nullptr, size, fd);
    EXPECT_NE(nullptr, addr);
    EXPECT_NE(MAP_FAILED, addr);
    ASSERT_EQ(1U, tempSysCallsCtx.vma.getSubRanges().size());
    EXPECT_EQ(Cal::Utils::AddressRange(addr, size), tempSysCallsCtx.vma.getSubRanges()[0].getBoundingRange());
    auto mmapTraits = tempSysCallsCtx.vma.getSubRanges()[0].getTag();
    EXPECT_EQ(nullptr, mmapTraits.addr);
    EXPECT_EQ(size, mmapTraits.length);
    EXPECT_EQ(PROT_READ | PROT_WRITE, mmapTraits.prot);
    EXPECT_EQ(MAP_SHARED, mmapTraits.flags);
    EXPECT_EQ(fd, mmapTraits.fd);
    EXPECT_EQ(0, mmapTraits.offset);

    constexpr auto size2 = 4096U;
    auto addr2 = Cal::Utils::moveByBytes(addr, size);
    addr = Cal::Usm::mapUsmCpuRangeToFd(addr2, size2, fd);
    EXPECT_EQ(addr2, addr);
    ASSERT_EQ(2U, tempSysCallsCtx.vma.getSubRanges().size());
    EXPECT_EQ(Cal::Utils::AddressRange(addr, size2), tempSysCallsCtx.vma.getSubRanges()[1].getBoundingRange());
    mmapTraits = tempSysCallsCtx.vma.getSubRanges()[1].getTag();
    EXPECT_EQ(addr2, mmapTraits.addr);
    EXPECT_EQ(size2, mmapTraits.length);
    EXPECT_EQ(PROT_READ | PROT_WRITE, mmapTraits.prot);
    EXPECT_EQ(MAP_SHARED | MAP_FIXED, mmapTraits.flags);
    EXPECT_EQ(fd, mmapTraits.fd);
    EXPECT_EQ(0, mmapTraits.offset);
}

TEST(UsmCpuRange, whenResettingUsmCpuRangeThenRangeIsResetToOnouccupiedUsmRange) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;

    constexpr auto size = 8192U;
    void *addr = Cal::Usm::reserveUsmCpuRange(nullptr, size);
    EXPECT_NE(nullptr, addr);
    EXPECT_NE(MAP_FAILED, addr);
    ASSERT_EQ(1U, tempSysCallsCtx.vma.getSubRanges().size());
    EXPECT_EQ(Cal::Utils::AddressRange(addr, size), tempSysCallsCtx.vma.getSubRanges()[0].getBoundingRange());
    auto mmapTraitsExpected = tempSysCallsCtx.vma.getSubRanges()[0].getTag();

    constexpr auto size2 = 4096U;
    auto addr2 = Cal::Utils::moveByBytes(addr, size);
    Cal::Usm::resetUsmCpuRange(addr2, size2);
    ASSERT_EQ(2U, tempSysCallsCtx.vma.getSubRanges().size());
    EXPECT_EQ(Cal::Utils::AddressRange(addr2, size2), tempSysCallsCtx.vma.getSubRanges()[1].getBoundingRange());
    auto mmapTraitsGot = tempSysCallsCtx.vma.getSubRanges()[1].getTag();
    EXPECT_EQ(addr2, mmapTraitsGot.addr);
    EXPECT_EQ(size2, mmapTraitsGot.length);
    EXPECT_EQ(mmapTraitsExpected.prot, mmapTraitsGot.prot);
    EXPECT_EQ(mmapTraitsExpected.flags | MAP_FIXED, mmapTraitsGot.flags);
    EXPECT_EQ(mmapTraitsExpected.fd, mmapTraitsGot.fd);
    EXPECT_EQ(mmapTraitsExpected.offset, mmapTraitsGot.offset);

    EXPECT_TRUE(logs.empty());
}

TEST(UsmCpuRange, whenFailedResettingUsmCpuRangeThenOutputsAWarning) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;

    constexpr auto size = 8192U;
    void *addr = Cal::Usm::reserveUsmCpuRange(nullptr, size);
    EXPECT_NE(nullptr, addr);
    EXPECT_NE(MAP_FAILED, addr);
    ASSERT_EQ(1U, tempSysCallsCtx.vma.getSubRanges().size());
    EXPECT_EQ(Cal::Utils::AddressRange(addr, size), tempSysCallsCtx.vma.getSubRanges()[0].getBoundingRange());
    auto mmapTraitsExpected = tempSysCallsCtx.vma.getSubRanges()[0].getTag();

    tempSysCallsCtx.apiConfig.mmap.returnValue = MAP_FAILED;
    constexpr auto size2 = 4096U;
    auto addr2 = Cal::Utils::moveByBytes(addr, size);
    Cal::Usm::resetUsmCpuRange(addr2, size);
    EXPECT_EQ(1U, tempSysCallsCtx.vma.getSubRanges().size());

    EXPECT_FALSE(logs.empty());
    EXPECT_THAT(logs.str(), testing::HasSubstr(Cal::Utils::Log::to_cstring_tag(Verbosity::error)));
}

TEST(NegotiateUsmRangeWithService, whenStartingNegotiationThenSuggestsProvidedAddressAsInitialProposal) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;
    Cal::Mocks::ConnectionMock mockConnection;

    void *expectedAddr = reinterpret_cast<void *>(static_cast<uintptr_t>(4096U));
    size_t expectedSize = 8192U;

    bool correctMessage = false;
    void *gotAddr = nullptr;
    size_t gotSize = 0U;
    mockConnection.apiConfig.send.impl = [&](const void *data, size_t dataSize) -> int {
        if (dataSize != sizeof(Cal::Messages::ReqNegotiateUsmAddressRange)) {
            return -1;
        }

        auto message = reinterpret_cast<const Cal::Messages::ReqNegotiateUsmAddressRange *>(data);
        if ((message->header.type != Cal::Ipc::ControlMessageHeader::messageTypeRequest) && (message->header.subtype != Cal::Messages::ReqNegotiateUsmAddressRange::messageSubtype) || message->isInvalid()) {
            return -1;
        }
        correctMessage = true;
        gotAddr = message->proposedUsmBase;
        gotSize = message->proposedUsmSize;

        return 0;
    };

    auto ret = Cal::Usm::negotiateUsmRangeWithService(mockConnection, expectedAddr, expectedSize);

    ASSERT_TRUE(correctMessage);
    EXPECT_EQ(expectedAddr, gotAddr);
    EXPECT_EQ(expectedSize, gotSize);
    EXPECT_FALSE(ret.has_value());
}

TEST(NegotiateUsmRangeWithService, whenServiceAgreesOnFirstProposedRangeThenUseThatRange) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;

    using namespace Cal::Messages;
    using OutMessages = std::tuple<ReqNegotiateUsmAddressRange>;
    using InMessages = std::tuple<RespNegotiateUsmAddressRange>;
    Cal::Mocks::ConnectionExpectedProtocol<InMessages, OutMessages> mockConnection;

    void *expectedAddr = reinterpret_cast<void *>(static_cast<uintptr_t>(4096U));
    size_t expectedSize = 8192U;

    std::get<0>(mockConnection.outMessages).proposedUsmBase = expectedAddr;
    std::get<0>(mockConnection.outMessages).proposedUsmSize = expectedSize;

    std::get<0>(mockConnection.inMessages).proposedUsmBase = expectedAddr;
    std::get<0>(mockConnection.inMessages).proposedUsmSize = expectedSize;

    auto ret = Cal::Usm::negotiateUsmRangeWithService(mockConnection, expectedAddr, expectedSize);
    EXPECT_TRUE(mockConnection.mismatchLogs.empty()) << " out messages issues : [" << mockConnection.getMismatchLogFlat() << "]";
    EXPECT_TRUE(mockConnection.encodeIssues.empty()) << " in messages issues : [" << mockConnection.getEncodeLogFlat() << "]";

    EXPECT_TRUE(logs.empty()) << logs.str();
    ASSERT_TRUE(ret.has_value());
    EXPECT_EQ(Cal::Utils::AddressRange(expectedAddr, expectedSize), ret.value());

    EXPECT_EQ(0U, tempSysCallsCtx.vma.getSubRanges().size()) << "Caller should ensure that provided address is already reserved with mmap";
}

TEST(NegotiateUsmRangeWithService, whenServiceDisagreesOnFirstProposedRangeThenTryOneSuggestedByService) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;

    using namespace Cal::Messages;
    using OutMessages = std::tuple<ReqNegotiateUsmAddressRange, ReqNegotiateUsmAddressRange>;
    using InMessages = std::tuple<RespNegotiateUsmAddressRange, RespNegotiateUsmAddressRange>;
    Cal::Mocks::ConnectionExpectedProtocol<InMessages, OutMessages> mockConnection;

    auto &client = mockConnection.outMessages;
    auto &service = mockConnection.inMessages;

    std::get<0>(client).proposedUsmBase = reinterpret_cast<void *>(static_cast<uintptr_t>(4096U));
    std::get<0>(client).proposedUsmSize = 8192U;

    std::get<0>(service).proposedUsmBase = reinterpret_cast<void *>(static_cast<uintptr_t>(8192U));
    std::get<0>(service).proposedUsmSize = 8192U;

    std::get<1>(client).proposedUsmBase = std::get<0>(service).proposedUsmBase;
    std::get<1>(client).proposedUsmSize = 8192U;

    std::get<1>(service).proposedUsmBase = std::get<1>(client).proposedUsmBase;
    std::get<1>(service).proposedUsmSize = 8192U;

    auto ret = Cal::Usm::negotiateUsmRangeWithService(mockConnection, std::get<0>(client).proposedUsmBase, std::get<0>(client).proposedUsmSize);
    EXPECT_TRUE(mockConnection.mismatchLogs.empty()) << " out messages issues : [" << mockConnection.getMismatchLogFlat() << "]";
    EXPECT_TRUE(mockConnection.encodeIssues.empty()) << " in messages issues : [" << mockConnection.getEncodeLogFlat() << "]";

    EXPECT_TRUE(logs.empty()) << logs.str();
    ASSERT_TRUE(ret.has_value());
    EXPECT_EQ(Cal::Utils::AddressRange(std::get<0>(service).proposedUsmBase, std::get<0>(service).proposedUsmSize), ret.value());

    ASSERT_EQ(1U, tempSysCallsCtx.vma.getSubRanges().size());
    EXPECT_EQ(ret.value(), tempSysCallsCtx.vma.getSubRanges()[0].getBoundingRange());
}

TEST(NegotiateUsmRangeWithService, whenServiceDisagreesOnceAndClientDisagreesOnceThenTryToProposeNewAddressRangeOnClientSide) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;

    using namespace Cal::Messages;
    using OutMessages = std::tuple<ReqNegotiateUsmAddressRange, ReqNegotiateUsmAddressRange>;
    using InMessages = std::tuple<RespNegotiateUsmAddressRange, RespNegotiateUsmAddressRange>;
    Cal::Mocks::ConnectionExpectedProtocol<InMessages, OutMessages> mockConnection;

    auto &client = mockConnection.outMessages;
    auto &service = mockConnection.inMessages;

    std::get<0>(client).proposedUsmBase = reinterpret_cast<void *>(static_cast<uintptr_t>(4096U));
    std::get<0>(client).proposedUsmSize = 8192U;

    std::get<0>(service).proposedUsmBase = reinterpret_cast<void *>(static_cast<uintptr_t>(8192U));
    std::get<0>(service).proposedUsmSize = 8192U;

    std::get<1>(client).proposedUsmBase = reinterpret_cast<void *>(static_cast<uintptr_t>(8192U * 4));
    std::get<1>(client).proposedUsmSize = 8192U;

    std::get<1>(service).proposedUsmBase = std::get<1>(client).proposedUsmBase;
    std::get<1>(service).proposedUsmSize = 8192U;

    int numMmapCalls = 0;
    tempSysCallsCtx.apiConfig.mmap.impl = [&](void *addr, size_t length, int prot, int flags, int fd, off_t offset) -> void * {
        ++numMmapCalls;
        return addr ? MAP_FAILED : std::get<1>(client).proposedUsmBase;
    };

    auto ret = Cal::Usm::negotiateUsmRangeWithService(mockConnection, std::get<0>(client).proposedUsmBase, std::get<0>(client).proposedUsmSize);
    EXPECT_TRUE(mockConnection.mismatchLogs.empty()) << " out messages issues : [" << mockConnection.getMismatchLogFlat() << "]";
    EXPECT_TRUE(mockConnection.encodeIssues.empty()) << " in messages issues : [" << mockConnection.getEncodeLogFlat() << "]";

    EXPECT_TRUE(logs.empty()) << logs.str();
    ASSERT_TRUE(ret.has_value());
    EXPECT_EQ(Cal::Utils::AddressRange(std::get<1>(service).proposedUsmBase, std::get<1>(service).proposedUsmSize), ret.value());
    EXPECT_EQ(2U, numMmapCalls);
}

TEST(NegotiateUsmRangeWithService, whenServiceDisagreesMaxTimesThenFail) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;

    using namespace Cal::Messages;
    using OutMessages = std::tuple<ReqNegotiateUsmAddressRange, ReqNegotiateUsmAddressRange>;
    using InMessages = std::tuple<RespNegotiateUsmAddressRange, RespNegotiateUsmAddressRange>;
    Cal::Mocks::ConnectionExpectedProtocol<InMessages, OutMessages> mockConnection;

    auto &client = mockConnection.outMessages;
    auto &service = mockConnection.inMessages;

    std::get<0>(client).proposedUsmBase = reinterpret_cast<void *>(static_cast<uintptr_t>(4096U));
    std::get<0>(client).proposedUsmSize = 8192U;

    std::get<0>(service).proposedUsmBase = reinterpret_cast<void *>(static_cast<uintptr_t>(8192U));
    std::get<0>(service).proposedUsmSize = 8192U;

    std::get<1>(client).proposedUsmBase = reinterpret_cast<void *>(static_cast<uintptr_t>(8192U * 4));
    std::get<1>(client).proposedUsmSize = 8192U;

    std::get<1>(service).proposedUsmBase = std::get<1>(client).proposedUsmBase;
    std::get<1>(service).proposedUsmSize = 8192U;

    int numMmapCalls = 0;
    tempSysCallsCtx.apiConfig.mmap.impl = [&](void *addr, size_t length, int prot, int flags, int fd, off_t offset) -> void * {
        ++numMmapCalls;
        return addr ? MAP_FAILED : std::get<1>(client).proposedUsmBase;
    };

    auto ret = Cal::Usm::negotiateUsmRangeWithService(mockConnection, std::get<0>(client).proposedUsmBase, std::get<0>(client).proposedUsmSize, 1U);
    EXPECT_TRUE(mockConnection.mismatchLogs.empty()) << " out messages issues : [" << mockConnection.getMismatchLogFlat() << "]";
    EXPECT_TRUE(mockConnection.encodeIssues.empty()) << " in messages issues : [" << mockConnection.getEncodeLogFlat() << "]";

    EXPECT_FALSE(logs.empty()) << logs.str();
    EXPECT_FALSE(ret.has_value());
    EXPECT_EQ(2U, numMmapCalls);
}

TEST(NegotiateUsmRangeWithService, whenAMergedVmaLooksUsableThenTryIt) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;

    using namespace Cal::Messages;
    using OutMessages = std::tuple<ReqNegotiateUsmAddressRange, ReqNegotiateUsmAddressRange, ReqNegotiateUsmAddressRange, ReqNegotiateUsmAddressRange>;
    using InMessages = std::tuple<RespNegotiateUsmAddressRange, RespNegotiateUsmAddressRange, RespNegotiateUsmAddressRange, RespNegotiateUsmAddressRange>;
    Cal::Mocks::ConnectionExpectedProtocol<InMessages, OutMessages> mockConnection;

    auto &client = mockConnection.outMessages;
    auto &service = mockConnection.inMessages;

    size_t pageSize = 4096U;
    size_t serviceProposalsOffset = 64 * pageSize;
    size_t rangeSize = 2 * pageSize;
    Cal::Utils::AddressRange rangesProposedByClient[] = {{1 * pageSize, 1 * pageSize + rangeSize}, {1 * pageSize + rangeSize, 1 * pageSize + 2 * rangeSize}};
    Cal::Utils::AddressRange overlapRange = {rangesProposedByClient[1].start - pageSize, rangesProposedByClient[1].start + pageSize};
    Cal::Utils::AddressRange rangesProposedByService[] = {{serviceProposalsOffset + 1 * pageSize, serviceProposalsOffset + 1 * pageSize + rangeSize}, {serviceProposalsOffset + 1 * pageSize + rangeSize, serviceProposalsOffset + 1 * pageSize + 2 * rangeSize}, overlapRange};
    Cal::Utils::AddressRange colidedRangesOnClient[] = {rangesProposedByService[0], rangesProposedByService[1]};
    for (auto range : colidedRangesOnClient) {
        void *collidedRange = Cal::Sys::mmap(range.base(), range.size(), 0, 0, -1, 0);
        ASSERT_EQ(range.base(), collidedRange);
    }

    std::get<0>(client).proposedUsmBase = nullptr;
    std::get<0>(client).proposedUsmSize = 0U;

    std::get<0>(service).proposedUsmBase = rangesProposedByService[0].base();
    std::get<0>(service).proposedUsmSize = rangesProposedByService[0].size();

    std::get<1>(client).proposedUsmBase = rangesProposedByClient[0].base();
    std::get<1>(client).proposedUsmSize = rangesProposedByClient[0].size();

    std::get<1>(service).proposedUsmBase = rangesProposedByService[1].base();
    std::get<1>(service).proposedUsmSize = rangesProposedByService[1].size();

    std::get<2>(client).proposedUsmBase = rangesProposedByClient[1].base();
    std::get<2>(client).proposedUsmSize = rangesProposedByClient[1].size();

    std::get<2>(service).proposedUsmBase = overlapRange.base();
    std::get<2>(service).proposedUsmSize = overlapRange.size();

    std::get<3>(client).proposedUsmBase = overlapRange.base();
    std::get<3>(client).proposedUsmSize = overlapRange.size();

    std::get<3>(service).proposedUsmBase = overlapRange.base();
    std::get<3>(service).proposedUsmSize = overlapRange.size();

    int numNullAddrMmapCalls = 0;
    tempSysCallsCtx.apiConfig.mmap.impl = [&](void *addr, size_t length, int prot, int flags, int fd, off_t offset) -> void * {
        if (nullptr == addr) {
            ++numNullAddrMmapCalls;
            if (numNullAddrMmapCalls > 2) {
                return MAP_FAILED;
            }
            return tempSysCallsCtx.mmapBaseImpl(rangesProposedByClient[numNullAddrMmapCalls - 1].base(), length, prot, flags, fd, offset);
        } else {
            return tempSysCallsCtx.mmapBaseImpl(addr, length, prot, flags, fd, offset);
        }
    };

    auto ret = Cal::Usm::negotiateUsmRangeWithService(mockConnection, std::get<0>(client).proposedUsmBase, std::get<0>(client).proposedUsmSize);
    EXPECT_TRUE(mockConnection.mismatchLogs.empty()) << " out messages issues : [" << mockConnection.getMismatchLogFlat() << "]";
    EXPECT_TRUE(mockConnection.encodeIssues.empty()) << " in messages issues : [" << mockConnection.getEncodeLogFlat() << "]";

    EXPECT_TRUE(logs.empty()) << logs.str();
    EXPECT_TRUE(ret.has_value());
    EXPECT_EQ(overlapRange, ret.value());
    EXPECT_EQ(2U, numNullAddrMmapCalls);

    ASSERT_EQ(3U, tempSysCallsCtx.vma.getSubRanges().size());
}

TEST(NegotiateUsmRangeWithClient, whenInitialSizeIsZeroThenFail) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;
    Cal::Mocks::ConnectionMock mockConnection;
    auto range = Cal::Usm::negotiateUsmRangeWithClient(mockConnection, nullptr, 0U);
    EXPECT_FALSE(range.has_value());
}

TEST(NegotiateUsmRangeWithClient, whenFirstProvidedAddressFromClientIsUsableThenUseThatRange) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;

    using namespace Cal::Messages;
    using OutMessages = std::tuple<RespNegotiateUsmAddressRange>;
    using InMessages = std::tuple<>;
    Cal::Mocks::ConnectionExpectedProtocol<InMessages, OutMessages> mockConnection;

    void *expectedAddr = reinterpret_cast<void *>(static_cast<uintptr_t>(4096U));
    size_t expectedSize = 8192U;

    auto &client = mockConnection.inMessages;
    auto &service = mockConnection.outMessages;

    std::get<0>(service).proposedUsmBase = expectedAddr;
    std::get<0>(service).proposedUsmSize = expectedSize;

    auto ret = Cal::Usm::negotiateUsmRangeWithClient(mockConnection, expectedAddr, expectedSize);
    EXPECT_TRUE(mockConnection.mismatchLogs.empty()) << " out messages issues : [" << mockConnection.getMismatchLogFlat() << "]";
    EXPECT_TRUE(mockConnection.encodeIssues.empty()) << " in messages issues : [" << mockConnection.getEncodeLogFlat() << "]";

    EXPECT_TRUE(logs.empty()) << logs.str();
    ASSERT_TRUE(ret.has_value());
    EXPECT_EQ(Cal::Utils::AddressRange(expectedAddr, expectedSize), ret.value());

    ASSERT_EQ(1U, tempSysCallsCtx.vma.getSubRanges().size());
}

TEST(NegotiateUsmRangeWithClient, whenFirstProvidedAddressFromClientIsNullThenProposeOne) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;

    using namespace Cal::Messages;
    using OutMessages = std::tuple<RespNegotiateUsmAddressRange, RespNegotiateUsmAddressRange>;
    using InMessages = std::tuple<ReqNegotiateUsmAddressRange>;
    Cal::Mocks::ConnectionExpectedProtocol<InMessages, OutMessages> mockConnection;

    void *expectedAddr = reinterpret_cast<void *>(static_cast<uintptr_t>(4096U));
    size_t expectedSize = 8192U;

    auto &client = mockConnection.inMessages;
    auto &service = mockConnection.outMessages;

    tempSysCallsCtx.apiConfig.mmap.returnValue = expectedAddr;
    std::get<0>(service).proposedUsmBase = expectedAddr;
    std::get<0>(service).proposedUsmSize = expectedSize;

    std::get<0>(client).proposedUsmBase = expectedAddr;
    std::get<0>(client).proposedUsmSize = expectedSize;

    std::get<1>(service).proposedUsmBase = expectedAddr;
    std::get<1>(service).proposedUsmSize = expectedSize;

    auto ret = Cal::Usm::negotiateUsmRangeWithClient(mockConnection, nullptr, expectedSize);
    EXPECT_TRUE(mockConnection.mismatchLogs.empty()) << " out messages issues : [" << mockConnection.getMismatchLogFlat() << "]";
    EXPECT_TRUE(mockConnection.encodeIssues.empty()) << " in messages issues : [" << mockConnection.getEncodeLogFlat() << "]";

    EXPECT_TRUE(logs.empty()) << logs.str();
    ASSERT_TRUE(ret.has_value());
    EXPECT_EQ(Cal::Utils::AddressRange(expectedAddr, expectedSize), ret.value());
}

TEST(NegotiateUsmRangeWithClient, whenClientRejectedProposedRangeAndProvidedItsOwnProposalThenTryUsingIt) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;

    using namespace Cal::Messages;
    using OutMessages = std::tuple<RespNegotiateUsmAddressRange, RespNegotiateUsmAddressRange>;
    using InMessages = std::tuple<ReqNegotiateUsmAddressRange>;
    Cal::Mocks::ConnectionExpectedProtocol<InMessages, OutMessages> mockConnection;

    void *serviceProposedAddr = reinterpret_cast<void *>(static_cast<uintptr_t>(4096U));
    size_t expectedSize = 8192U;

    auto &client = mockConnection.inMessages;
    auto &service = mockConnection.outMessages;

    std::get<0>(service).proposedUsmBase = serviceProposedAddr;
    std::get<0>(service).proposedUsmSize = expectedSize;

    std::get<0>(client).proposedUsmBase = Cal::Utils::moveByBytes(serviceProposedAddr, expectedSize);
    std::get<0>(client).proposedUsmSize = expectedSize;

    std::get<1>(service).proposedUsmBase = std::get<0>(client).proposedUsmBase;
    std::get<1>(service).proposedUsmSize = std::get<0>(client).proposedUsmSize;

    tempSysCallsCtx.apiConfig.mmap.impl = [&](void *addr, size_t length, int prot, int flags, int fd, off_t offset) -> void * {
        return addr ? tempSysCallsCtx.mmapBaseImpl(addr, length, prot, flags, fd, offset) : tempSysCallsCtx.mmapBaseImpl(serviceProposedAddr, length, prot, flags, fd, offset);
    };

    auto ret = Cal::Usm::negotiateUsmRangeWithClient(mockConnection, nullptr, expectedSize);
    EXPECT_TRUE(mockConnection.mismatchLogs.empty()) << " out messages issues : [" << mockConnection.getMismatchLogFlat() << "]";
    EXPECT_TRUE(mockConnection.encodeIssues.empty()) << " in messages issues : [" << mockConnection.getEncodeLogFlat() << "]";

    EXPECT_TRUE(logs.empty()) << logs.str();
    ASSERT_TRUE(ret.has_value());
    EXPECT_EQ(Cal::Utils::AddressRange(std::get<0>(client).proposedUsmBase, expectedSize), ret.value());

    ASSERT_EQ(1U, tempSysCallsCtx.vma.getSubRanges().size());
    EXPECT_EQ(Cal::Utils::AddressRange(std::get<1>(service).proposedUsmBase, std::get<1>(service).proposedUsmSize), tempSysCallsCtx.vma.getSubRanges()[0].getBoundingRange());
}

TEST(NegotiateUsmRangeWithClient, whenClientRejectedProposedRangeAndProvidedItsOwnSecondProposalThenTryUsingIt) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;

    using namespace Cal::Messages;
    using OutMessages = std::tuple<RespNegotiateUsmAddressRange, RespNegotiateUsmAddressRange>;
    using InMessages = std::tuple<ReqNegotiateUsmAddressRange>;
    Cal::Mocks::ConnectionExpectedProtocol<InMessages, OutMessages> mockConnection;

    void *clientProposedAddr = reinterpret_cast<void *>(static_cast<uintptr_t>(4096U));
    size_t expectedSize = 8192U;
    void *collidedRange = Cal::Sys::mmap(clientProposedAddr, expectedSize, 0, 0, -1, 0);
    ASSERT_EQ(clientProposedAddr, collidedRange);

    void *serviceProposedAddr = Cal::Utils::moveByBytes(clientProposedAddr, expectedSize);
    void *clientProposedAddr2 = Cal::Utils::moveByBytes(serviceProposedAddr, expectedSize);

    auto &client = mockConnection.inMessages;
    auto &service = mockConnection.outMessages;

    std::get<0>(service).proposedUsmBase = serviceProposedAddr;
    std::get<0>(service).proposedUsmSize = expectedSize;

    std::get<0>(client).proposedUsmBase = clientProposedAddr2;
    std::get<0>(client).proposedUsmSize = expectedSize;

    std::get<1>(service).proposedUsmBase = clientProposedAddr2;
    std::get<1>(service).proposedUsmSize = expectedSize;

    tempSysCallsCtx.apiConfig.mmap.impl = [&](void *addr, size_t length, int prot, int flags, int fd, off_t offset) -> void * {
        return addr ? tempSysCallsCtx.mmapBaseImpl(addr, length, prot, flags, fd, offset) : tempSysCallsCtx.mmapBaseImpl(serviceProposedAddr, length, prot, flags, fd, offset);
    };

    auto ret = Cal::Usm::negotiateUsmRangeWithClient(mockConnection, clientProposedAddr, expectedSize);
    EXPECT_TRUE(mockConnection.mismatchLogs.empty()) << " out messages issues : [" << mockConnection.getMismatchLogFlat() << "]";
    EXPECT_TRUE(mockConnection.encodeIssues.empty()) << " in messages issues : [" << mockConnection.getEncodeLogFlat() << "]";

    EXPECT_TRUE(logs.empty()) << logs.str();
    ASSERT_TRUE(ret.has_value());
    EXPECT_EQ(Cal::Utils::AddressRange(clientProposedAddr2, expectedSize), ret.value());

    ASSERT_EQ(2U, tempSysCallsCtx.vma.getSubRanges().size());
    EXPECT_EQ(Cal::Utils::AddressRange(collidedRange, expectedSize), tempSysCallsCtx.vma.getSubRanges()[0].getBoundingRange());
    EXPECT_EQ(Cal::Utils::AddressRange(clientProposedAddr2, expectedSize), tempSysCallsCtx.vma.getSubRanges()[1].getBoundingRange());
}

TEST(NegotiateUsmRangeWithClient, whenClientRejectedProposedRangeAndProvidedItsOwnProposalAndItsNotUsableThenTryProposeADifferentOne) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;

    using namespace Cal::Messages;
    using OutMessages = std::tuple<RespNegotiateUsmAddressRange, RespNegotiateUsmAddressRange>;
    using InMessages = std::tuple<ReqNegotiateUsmAddressRange>;
    Cal::Mocks::ConnectionExpectedProtocol<InMessages, OutMessages> mockConnection;

    void *clientProposedAddr = reinterpret_cast<void *>(static_cast<uintptr_t>(4096U));
    size_t expectedSize = 8192U;
    void *collidedRange = Cal::Sys::mmap(clientProposedAddr, expectedSize, 0, 0, -1, 0);
    ASSERT_EQ(clientProposedAddr, collidedRange);

    void *serviceProposedAddr = Cal::Utils::moveByBytes(clientProposedAddr, expectedSize);

    auto &client = mockConnection.inMessages;
    auto &service = mockConnection.outMessages;

    std::get<0>(service).proposedUsmBase = serviceProposedAddr;
    std::get<0>(service).proposedUsmSize = expectedSize;

    std::get<0>(client).proposedUsmBase = serviceProposedAddr;
    std::get<0>(client).proposedUsmSize = expectedSize;

    std::get<1>(service).proposedUsmBase = serviceProposedAddr;
    std::get<1>(service).proposedUsmSize = expectedSize;

    tempSysCallsCtx.apiConfig.mmap.impl = [&](void *addr, size_t length, int prot, int flags, int fd, off_t offset) -> void * {
        return addr ? tempSysCallsCtx.mmapBaseImpl(addr, length, prot, flags, fd, offset) : tempSysCallsCtx.mmapBaseImpl(serviceProposedAddr, length, prot, flags, fd, offset);
    };

    auto ret = Cal::Usm::negotiateUsmRangeWithClient(mockConnection, clientProposedAddr, expectedSize);
    EXPECT_TRUE(mockConnection.mismatchLogs.empty()) << " out messages issues : [" << mockConnection.getMismatchLogFlat() << "]";
    EXPECT_TRUE(mockConnection.encodeIssues.empty()) << " in messages issues : [" << mockConnection.getEncodeLogFlat() << "]";

    EXPECT_TRUE(logs.empty()) << logs.str();
    ASSERT_TRUE(ret.has_value());
    EXPECT_EQ(Cal::Utils::AddressRange(serviceProposedAddr, expectedSize), ret.value());

    ASSERT_EQ(2U, tempSysCallsCtx.vma.getSubRanges().size());
    EXPECT_EQ(Cal::Utils::AddressRange(collidedRange, expectedSize), tempSysCallsCtx.vma.getSubRanges()[0].getBoundingRange());
    EXPECT_EQ(Cal::Utils::AddressRange(serviceProposedAddr, expectedSize), tempSysCallsCtx.vma.getSubRanges()[1].getBoundingRange());
}

TEST(NegotiateUsmRangeWithClient, whenClientDisagreesMaxTimesThenFail) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;

    using namespace Cal::Messages;
    using OutMessages = std::tuple<RespNegotiateUsmAddressRange, RespNegotiateUsmAddressRange>;
    using InMessages = std::tuple<ReqNegotiateUsmAddressRange>;
    Cal::Mocks::ConnectionExpectedProtocol<InMessages, OutMessages> mockConnection;

    void *clientProposedAddr = reinterpret_cast<void *>(static_cast<uintptr_t>(4096U));
    size_t expectedSize = 8192U;
    void *collidedRange = Cal::Sys::mmap(clientProposedAddr, expectedSize, 0, 0, -1, 0);
    ASSERT_EQ(clientProposedAddr, collidedRange);

    void *serviceProposedAddr = Cal::Utils::moveByBytes(clientProposedAddr, expectedSize);
    void *clientProposedAddr2 = Cal::Utils::moveByBytes(serviceProposedAddr, expectedSize);

    auto &client = mockConnection.inMessages;
    auto &service = mockConnection.outMessages;

    std::get<0>(service).proposedUsmBase = serviceProposedAddr;
    std::get<0>(service).proposedUsmSize = expectedSize;

    std::get<0>(client).proposedUsmBase = clientProposedAddr2;
    std::get<0>(client).proposedUsmSize = expectedSize;

    std::get<1>(service).proposedUsmBase = clientProposedAddr2;
    std::get<1>(service).proposedUsmSize = expectedSize;

    tempSysCallsCtx.apiConfig.mmap.impl = [&](void *addr, size_t length, int prot, int flags, int fd, off_t offset) -> void * {
        return addr ? tempSysCallsCtx.mmapBaseImpl(addr, length, prot, flags, fd, offset) : tempSysCallsCtx.mmapBaseImpl(serviceProposedAddr, length, prot, flags, fd, offset);
    };

    auto ret = Cal::Usm::negotiateUsmRangeWithClient(mockConnection, clientProposedAddr, expectedSize, 1);
    EXPECT_TRUE(mockConnection.mismatchLogs.empty()) << " out messages issues : [" << mockConnection.getMismatchLogFlat() << "]";
    EXPECT_TRUE(mockConnection.encodeIssues.empty()) << " in messages issues : [" << mockConnection.getEncodeLogFlat() << "]";

    EXPECT_FALSE(logs.empty()) << logs.str();
    EXPECT_FALSE(ret.has_value());
}

} // namespace Ult
} // namespace Cal
