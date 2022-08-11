/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "shared/shmem.h"
#include "test/mocks/connection_mock.h"
#include "test/mocks/log_mock.h"
#include "test/mocks/sys_mock.h"

#include <string>

namespace Cal {

namespace Ult {

TEST(RemoteShmem, whenIsValidIsCalledThenReturnsTrueOnlyIfCalIdIsValid) {
    Cal::Ipc::RemoteShmem rshmem = {};
    EXPECT_EQ(Cal::Ipc::invalidShmemId, rshmem.id);
    EXPECT_FALSE(rshmem.isValid());

    rshmem.id = 0;
    EXPECT_TRUE(rshmem.isValid());
}

TEST(Shmem, whenIsValidIsCalledThenReturnsTrueOnlyIfCalIdIsValidAndPtrOrFdAreValid) {
    Cal::Ipc::Shmem shmem = {};
    EXPECT_EQ(Cal::Ipc::invalidShmemId, shmem.id);
    EXPECT_EQ(nullptr, shmem.ptr);
    EXPECT_EQ(-1, shmem.fd);

    EXPECT_FALSE(shmem.isValid());

    shmem.id = 0;
    EXPECT_FALSE(shmem.isValid());

    shmem.fd = 0;
    EXPECT_TRUE(shmem.isValid());
    shmem.fd = -1;
    EXPECT_FALSE(shmem.isValid());

    shmem.ptr = &shmem;
    EXPECT_TRUE(shmem.isValid());
    shmem.fd = 0;
    EXPECT_TRUE(shmem.isValid());

    shmem.id = Cal::Ipc::invalidShmemId;
    EXPECT_FALSE(shmem.isValid());
}

TEST(ShmemManagerGetFromRemoteShmem, givenInvalidRemoteShmemThenReturnsInvalidShmem) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;

    Cal::Ipc::ShmemManager shmemManager;
    Cal::Ipc::RemoteShmem rshmem = {};
    EXPECT_FALSE(rshmem.isValid());

    auto shmem = shmemManager.get(rshmem, nullptr);

    EXPECT_EQ(0U, tempSysCallsCtx.apiConfig.shm_open.callCount);
    EXPECT_FALSE(shmem.isValid());
    EXPECT_FALSE(logs.empty());
}

TEST(ShmemManagerGetFromRemoteShmem, givenSpecificPointerToMapWhenPointerIsMisalignedThenReturnsInvalidShmem) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;

    Cal::Ipc::ShmemManager shmemManager;
    Cal::Ipc::RemoteShmem rshmem = {};
    rshmem.id = 1;
    rshmem.size = Cal::Utils::pageSize4KB;
    EXPECT_TRUE(rshmem.isValid());

    auto shmem = shmemManager.get(rshmem, reinterpret_cast<void *>(static_cast<uintptr_t>(5)));

    EXPECT_EQ(0U, tempSysCallsCtx.apiConfig.shm_open.callCount);
    EXPECT_FALSE(shmem.isValid());
    EXPECT_FALSE(logs.empty());
}

TEST(ShmemManagerGetFromRemoteShmem, givenSpecificPointerToMapWhenSizeIsMisalignedThenReturnsInvalidShmem) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;

    Cal::Ipc::ShmemManager shmemManager;
    Cal::Ipc::RemoteShmem rshmem = {};
    rshmem.id = 1;
    rshmem.size = 7;
    EXPECT_TRUE(rshmem.isValid());

    auto shmem = shmemManager.get(rshmem, reinterpret_cast<void *>(static_cast<uintptr_t>(4096U)));

    EXPECT_EQ(0U, tempSysCallsCtx.apiConfig.shm_open.callCount);
    EXPECT_FALSE(shmem.isValid());
    EXPECT_FALSE(logs.empty());
}

TEST(ShmemManagerGetFromRemoteShmem, whenFailedToShmOpenThenReturnsInvalidShmem) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;

    Cal::Ipc::ShmemManager shmemManager;
    Cal::Ipc::RemoteShmem rshmem = {};
    rshmem.id = 1;
    rshmem.size = Cal::Utils::pageSize4KB;
    EXPECT_TRUE(rshmem.isValid());

    tempSysCallsCtx.apiConfig.shm_open.returnValue = -1;
    auto shmem = shmemManager.get(rshmem, nullptr);

    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.shm_open.callCount);
    EXPECT_EQ(0U, tempSysCallsCtx.apiConfig.mmap.callCount);
    EXPECT_FALSE(shmem.isValid());
    EXPECT_FALSE(logs.empty());
}

TEST(ShmemManagerGetFromRemoteShmem, whenFailedToMmapOpenedFileToAddreessThenReturnsInvalidShmem) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;

    Cal::Ipc::ShmemManager shmemManager;
    Cal::Ipc::RemoteShmem rshmem = {};
    rshmem.id = 1;
    rshmem.size = Cal::Utils::pageSize4KB;
    EXPECT_TRUE(rshmem.isValid());

    tempSysCallsCtx.apiConfig.shm_open.returnValue = 3;
    tempSysCallsCtx.apiConfig.mmap.returnValue = MAP_FAILED;
    auto shmem = shmemManager.get(rshmem, nullptr);

    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.shm_open.callCount);
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.mmap.callCount);
    EXPECT_FALSE(shmem.isValid());
    EXPECT_FALSE(logs.empty());
}

TEST(ShmemManagerGetFromRemoteShmem, whenOpenedTheShmemFileAndMappedItToVaThenReturnsDescriptorOfOpenedShmem) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;

    Cal::Ipc::ShmemManager shmemManager;
    Cal::Ipc::RemoteShmem rshmem = {};
    rshmem.id = 1;
    rshmem.size = 16;
    EXPECT_TRUE(rshmem.isValid());

    int fd = 3;
    void *va = reinterpret_cast<void *>(static_cast<uintptr_t>(4096U));
    tempSysCallsCtx.apiConfig.shm_open.returnValue = fd;
    tempSysCallsCtx.apiConfig.mmap.returnValue = va;
    auto shmem = shmemManager.get(rshmem, nullptr);

    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.shm_open.callCount);
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.mmap.callCount);
    EXPECT_TRUE(shmem.isValid());
    EXPECT_TRUE(logs.empty()) << logs.str();

    EXPECT_EQ(fd, shmem.fd);
    EXPECT_EQ(va, shmem.ptr);
    EXPECT_EQ(rshmem.id, shmem.id);
    EXPECT_EQ(rshmem.size, shmem.size);
    EXPECT_FALSE(shmem.owned);
    EXPECT_EQ(Cal::Utils::pageSize4KB, shmem.underlyingSize);
}

TEST(ShmemManagerGetFromRemoteShmem, whenOpeningTheShmemFileThenUsesProperPathAndFlags) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;

    Cal::Ipc::ShmemManager shmemManager;
    Cal::Ipc::RemoteShmem rshmem = {};
    rshmem.id = 7;
    rshmem.size = 16;
    EXPECT_TRUE(rshmem.isValid());

    std::string_view testBasePath = "/test_base_path";
    shmemManager.setShmemPathBase(testBasePath.data());
    std::string capturedName;
    int capturedOflag = {};
    mode_t capturedMode = {};
    tempSysCallsCtx.apiConfig.shm_open.impl = [&](const char *name, int oflag, mode_t mode) -> int {
        capturedName = name;
        capturedOflag = oflag;
        capturedMode = mode;
        return -1;
    };
    auto shmem = shmemManager.get(rshmem, nullptr);
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.shm_open.callCount);
    EXPECT_STREQ((std::string(testBasePath.data()) + std::to_string(rshmem.id)).c_str(), capturedName.c_str());
    EXPECT_EQ(O_RDWR, capturedOflag);
    EXPECT_EQ(0, capturedMode);
}

TEST(ShmemManagerGetFromRemoteShmem, whenMmapingTheShmemFileThenUsesProperFlagsAndFd) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;

    Cal::Ipc::ShmemManager shmemManager;
    Cal::Ipc::RemoteShmem rshmem = {};
    rshmem.id = 1;
    rshmem.size = Cal::Utils::pageSize4KB;
    EXPECT_TRUE(rshmem.isValid());

    int fd0 = 3;
    void *va0 = reinterpret_cast<void *>(static_cast<uintptr_t>(4096U));
    tempSysCallsCtx.apiConfig.shm_open.returnValue = fd0;
    auto shmem0 = shmemManager.get(rshmem, va0);
    EXPECT_TRUE(shmem0.isValid());
    EXPECT_EQ(fd0, shmem0.fd);
    EXPECT_EQ(va0, shmem0.ptr);

    int fd1 = 7;
    tempSysCallsCtx.apiConfig.shm_open.returnValue = fd1;
    rshmem.id = 13;
    auto shmem1 = shmemManager.get(rshmem, nullptr);
    EXPECT_TRUE(shmem1.isValid());
    EXPECT_EQ(fd1, shmem1.fd);
    EXPECT_NE(nullptr, shmem1.ptr);
    void *va1 = shmem1.ptr;

    EXPECT_NE(va0, va1);

    ASSERT_EQ(2U, tempSysCallsCtx.vma.getSubRanges().size());
    EXPECT_FALSE(tempSysCallsCtx.vma.getSubRanges()[0].getBoundingRange().intersects(tempSysCallsCtx.vma.getSubRanges()[1].getBoundingRange()));

    EXPECT_EQ(va0, tempSysCallsCtx.vma.getSubRanges()[0].getBoundingRange().base());
    EXPECT_EQ(Cal::Utils::pageSize4KB, tempSysCallsCtx.vma.getSubRanges()[0].getBoundingRange().size());

    auto mmapFlags0 = tempSysCallsCtx.vma.getSubRanges()[0].getTag();
    EXPECT_EQ(va0, mmapFlags0.addr);
    EXPECT_EQ(Cal::Utils::pageSize4KB, mmapFlags0.length);
    EXPECT_EQ(PROT_READ | PROT_WRITE, mmapFlags0.prot);
    EXPECT_EQ(MAP_SHARED | MAP_FIXED, mmapFlags0.flags);
    EXPECT_EQ(fd0, mmapFlags0.fd);
    EXPECT_EQ(0, mmapFlags0.offset);

    auto mmapFlags1 = tempSysCallsCtx.vma.getSubRanges()[1].getTag();
    EXPECT_EQ(nullptr, mmapFlags1.addr);
    EXPECT_EQ(Cal::Utils::pageSize4KB, mmapFlags1.length);
    EXPECT_EQ(PROT_READ | PROT_WRITE, mmapFlags1.prot);
    EXPECT_EQ(MAP_SHARED, mmapFlags1.flags);
    EXPECT_EQ(fd1, mmapFlags1.fd);
    EXPECT_EQ(0, mmapFlags1.offset);

    EXPECT_TRUE(logs.empty()) << logs.str();
}

TEST(ShmemManagerGet, whenCreatingShmemThenFirstUnlinkStalePath) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;

    Cal::Ipc::ShmemManager shmemManager;

    std::string_view testBasePath = "/test_base_path";
    shmemManager.setShmemPathBase(testBasePath.data());

    std::string capturedUnlinkPath;
    tempSysCallsCtx.apiConfig.shm_unlink.impl = [&](const char *path) -> int {
        capturedUnlinkPath = path;
        return 0;
    };

    auto shmem = shmemManager.get(64, false);

    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.shm_unlink.callCount);
    EXPECT_STREQ((testBasePath.data() + std::to_string(0)).c_str(), capturedUnlinkPath.c_str());
}

TEST(ShmemManagerGet, whenFailedCreatingShmemThenReturnInvalidObject) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;

    Cal::Ipc::ShmemManager shmemManager;

    auto shmem = shmemManager.get(64, false);

    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.shm_open.callCount);
    EXPECT_FALSE(shmem.isValid());
    EXPECT_FALSE(logs.empty());
}

TEST(ShmemManagerGet, whenOpeningShmemThenProperFlagsAreUsed) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;

    Cal::Ipc::ShmemManager shmemManager;

    std::string_view testBasePath = "/test_base_path";
    shmemManager.setShmemPathBase(testBasePath.data());
    std::string capturedName;
    int capturedOflag = {};
    mode_t capturedMode = {};
    tempSysCallsCtx.apiConfig.shm_open.impl = [&](const char *name, int oflag, mode_t mode) -> int {
        capturedName = name;
        capturedOflag = oflag;
        capturedMode = mode;
        return -1;
    };
    auto shmem = shmemManager.get(64, false);

    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.shm_open.callCount);
    EXPECT_STREQ((std::string(testBasePath.data()) + std::to_string(0)).c_str(), capturedName.c_str());
    EXPECT_EQ(O_CREAT | O_EXCL | O_RDWR, capturedOflag);
    EXPECT_EQ(S_IRUSR | S_IWUSR, capturedMode);
    EXPECT_FALSE(shmem.isValid());
    EXPECT_FALSE(logs.empty());
}

} // namespace Ult
} // namespace Cal
