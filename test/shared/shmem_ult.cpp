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
#include "test/mocks/shmem_manager_mock.h"
#include "test/mocks/sys_mock.h"

#include <string>

namespace Cal {

namespace Ult {

using namespace Cal::Allocators;
using namespace Cal::Ipc;

TEST(ShmemAllocation, whenCheckedIfIsValidThenVerifiesShmemId) {
    {
        Cal::Ipc::ShmemAllocation alloc{Cal::Ipc::invalidShmemId, false};
        EXPECT_FALSE(alloc.isValid());
    }
    {
        Cal::Ipc::ShmemAllocation alloc{7, false};
        EXPECT_TRUE(alloc.isValid());
    }
}

TEST(RemoteShmem, whenIsValidIsCalledThenReturnsTrueOnlyIfCalIdIsValid) {
    Cal::Ipc::RemoteShmemDesc rshmem = {};
    EXPECT_EQ(Cal::Ipc::invalidShmemId, rshmem.id);
    EXPECT_FALSE(rshmem.isValid());

    rshmem.id = 0;
    EXPECT_TRUE(rshmem.isValid());
}

TEST(ShmemImporterOpen, givenInvalidRemoteShmemThenReturnsInvalidShmem) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;

    Cal::Ipc::ShmemImporter importer;
    Cal::Ipc::RemoteShmemDesc rshmem = {};
    EXPECT_FALSE(rshmem.isValid());
    auto shmem = importer.open(rshmem, nullptr);

    EXPECT_EQ(0U, tempSysCallsCtx.apiConfig.shm_open.callCount);
    EXPECT_FALSE(shmem.isValid());
    EXPECT_FALSE(logs.empty());
}

TEST(ShmemImporterOpen, givenSpecificPointerToMapWhenPointerIsMisalignedThenReturnsInvalidShmem) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;

    Cal::Ipc::ShmemImporter importer;
    Cal::Ipc::RemoteShmemDesc rshmem = {};
    rshmem.id = 1;
    rshmem.size = Cal::Utils::pageSize4KB;
    EXPECT_TRUE(rshmem.isValid());

    auto shmem = importer.open(rshmem, reinterpret_cast<void *>(static_cast<uintptr_t>(5)));

    EXPECT_EQ(0U, tempSysCallsCtx.apiConfig.shm_open.callCount);
    EXPECT_FALSE(shmem.isValid());
    EXPECT_FALSE(logs.empty());
}

TEST(ShmemImporterOpen, givenMisalignedSizeThenReturnsInvalidShmem) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;

    Cal::Ipc::ShmemImporter importer;
    Cal::Ipc::RemoteShmemDesc rshmem = {};
    rshmem.id = 1;
    rshmem.size = 7;
    EXPECT_TRUE(rshmem.isValid());

    auto shmem = importer.open(rshmem, reinterpret_cast<void *>(static_cast<uintptr_t>(4096U)));
    EXPECT_FALSE(shmem.isValid());
    EXPECT_FALSE(logs.empty());
    logs.clear();

    shmem = importer.open(rshmem);
    EXPECT_FALSE(shmem.isValid());
    EXPECT_FALSE(logs.empty());

    EXPECT_EQ(0U, tempSysCallsCtx.apiConfig.shm_open.callCount);
}

TEST(ShmemImporterOpen, whenFailedToShmOpenThenReturnsInvalidShmem) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;

    Cal::Ipc::ShmemImporter importer;
    Cal::Ipc::RemoteShmemDesc rshmem = {};
    rshmem.id = 1;
    rshmem.size = Cal::Utils::pageSize4KB;
    EXPECT_TRUE(rshmem.isValid());

    tempSysCallsCtx.apiConfig.shm_open.returnValue = -1;
    auto shmem = importer.open(rshmem, nullptr);

    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.shm_open.callCount);
    EXPECT_EQ(0U, tempSysCallsCtx.apiConfig.mmap.callCount);
    EXPECT_FALSE(shmem.isValid());
    EXPECT_FALSE(logs.empty());
}

TEST(ShmemImporterOpen, whenFailedToMmapOpenedFileToAddreessThenReturnsInvalidShmem) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;

    Cal::Ipc::ShmemImporter importer;
    Cal::Ipc::RemoteShmemDesc rshmem = {};
    rshmem.id = 1;
    rshmem.size = Cal::Utils::pageSize4KB;
    EXPECT_TRUE(rshmem.isValid());

    tempSysCallsCtx.apiConfig.shm_open.returnValue = 3;
    tempSysCallsCtx.apiConfig.mmap.returnValue = MAP_FAILED;
    auto shmem = importer.open(rshmem, nullptr);

    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.shm_open.callCount);
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.mmap.callCount);
    EXPECT_FALSE(shmem.isValid());
    EXPECT_FALSE(logs.empty());
}

TEST(ShmemImporterOpen, whenOpenedTheShmemFileAndMappedItToVaThenReturnsDescriptorOfOpenedShmem) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;

    Cal::Ipc::ShmemImporter importer;
    Cal::Ipc::RemoteShmemDesc rshmem = {};
    rshmem.id = 1;
    rshmem.size = Cal::Utils::pageSize4KB;
    EXPECT_TRUE(rshmem.isValid());

    int fd = 3;
    void *va = reinterpret_cast<void *>(static_cast<uintptr_t>(4096U));
    tempSysCallsCtx.apiConfig.shm_open.returnValue = fd;
    tempSysCallsCtx.apiConfig.mmap.returnValue = va;
    auto shmem = importer.open(rshmem, nullptr);

    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.shm_open.callCount);
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.mmap.callCount);
    EXPECT_TRUE(shmem.isValid());
    EXPECT_TRUE(logs.empty()) << logs.str();

    EXPECT_EQ(fd, shmem.getFd());
    EXPECT_EQ(va, shmem.getMmappedPtr());
    EXPECT_EQ(rshmem.id, shmem.getShmemId());
    EXPECT_EQ(rshmem.size, shmem.getMmappedSize());
    EXPECT_FALSE(shmem.isOwnerOfShmem());
    EXPECT_TRUE(shmem.isOwnerOfFd());
    EXPECT_EQ(Cal::Utils::pageSize4KB, shmem.getFileSize());
    EXPECT_EQ(Cal::Utils::pageSize4KB, shmem.getMmappedSize());
}

TEST(ShmemImporterOpen, whenOpeningTheShmemFileThenUsesProperPathAndFlags) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;

    Cal::Ipc::RemoteShmemDesc rshmem = {};
    rshmem.id = 7;
    rshmem.size = Cal::Utils::pageSize4KB;
    EXPECT_TRUE(rshmem.isValid());

    std::string_view testBasePath = "/test_base_path";
    Cal::Ipc::ShmemImporter importer(testBasePath.data());
    std::string capturedName;
    int capturedOflag = {};
    mode_t capturedMode = {};
    tempSysCallsCtx.apiConfig.shm_open.impl = [&](const char *name, int oflag, mode_t mode) -> int {
        capturedName = name;
        capturedOflag = oflag;
        capturedMode = mode;
        return -1;
    };

    importer.open(rshmem, nullptr);
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.shm_open.callCount);
    EXPECT_STREQ((std::string(testBasePath.data()) + std::to_string(rshmem.id)).c_str(), capturedName.c_str());
    EXPECT_EQ(O_RDWR, capturedOflag);
    EXPECT_EQ(mode_t{0u}, capturedMode);
}

TEST(ShmemImporterOpen, whenMmapingTheShmemFileThenUsesProperFlagsAndFd) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;

    Cal::Ipc::ShmemImporter importer;
    Cal::Ipc::RemoteShmemDesc rshmem = {};
    rshmem.id = 1;
    rshmem.size = Cal::Utils::pageSize4KB;
    EXPECT_TRUE(rshmem.isValid());

    int fd0 = 3;
    void *va0 = reinterpret_cast<void *>(static_cast<uintptr_t>(4096U));
    tempSysCallsCtx.apiConfig.shm_open.returnValue = fd0;
    auto shmem0 = importer.open(rshmem, va0);
    EXPECT_TRUE(shmem0.isValid());
    EXPECT_EQ(fd0, shmem0.getFd());
    EXPECT_EQ(va0, shmem0.getMmappedPtr());

    int fd1 = 7;
    tempSysCallsCtx.apiConfig.shm_open.returnValue = fd1;
    rshmem.id = 13;
    auto shmem1 = importer.open(rshmem, nullptr);
    EXPECT_TRUE(shmem1.isValid());
    EXPECT_EQ(fd1, shmem1.getFd());
    EXPECT_NE(nullptr, shmem1.getMmappedPtr());
    void *va1 = shmem1.getMmappedPtr();

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

TEST(ShmemImporterRelease, givenAllocationWithMmappedPtrWhenFreeingAndMunmapFailsThenEmitsError) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;

    Cal::Ipc::ShmemImporter globalShmemImporter;

    void *ptr = Cal::Sys::mmap(nullptr, 4096U, PROT_NONE, 0, -1, 0);
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.mmap.callCount);
    auto shmemAlloc = OpenedShmemAllocationT{ShmemAllocation{1, false}, 1, 4096U, true};
    Cal::Ipc::ShmemImporter::AllocationT mmappedShmemAlloc{shmemAlloc, ptr, 4096U};

    tempSysCallsCtx.apiConfig.munmap.returnValue = -1;
    globalShmemImporter.release(mmappedShmemAlloc);
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.mmap.callCount);
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.munmap.callCount);
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.close.callCount);

    Cal::Sys::munmap(ptr, 4096U);
    EXPECT_FALSE(logs.empty());
}

TEST(ShmemImporterRelease, givenAllocationWithMmappedPtrWhenOwnsFdThenFreeingMunmapsAndClosesFd) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;

    Cal::Ipc::ShmemImporter globalShmemImporter;

    void *ptr = Cal::Sys::mmap(nullptr, 4096U, PROT_NONE, 0, -1, 0);
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.mmap.callCount);
    auto shmemAlloc = OpenedShmemAllocationT{ShmemAllocation{1, false}, 1, 4096U, true};
    Cal::Ipc::ShmemImporter::AllocationT mmappedShmemAlloc{shmemAlloc, ptr, 4096U};

    globalShmemImporter.release(mmappedShmemAlloc);
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.mmap.callCount);
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.munmap.callCount);
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.close.callCount);

    EXPECT_EQ(0U, tempSysCallsCtx.vma.getSubRanges().size());
}

TEST(ShmemImporterRelease, givenAllocationWithMmappedPtrWhenDoesNotOwnFdThenFreeingResetsMmapAndLeavesFdIntact) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;

    Cal::Ipc::ShmemImporter globalShmemImporter;

    void *ptr = Cal::Sys::mmap(nullptr, 4096U, PROT_NONE, 0, -1, 0);
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.mmap.callCount);
    auto shmemAlloc = OpenedShmemAllocationT{ShmemAllocation{1, false}, 1, 4096U, false};
    Cal::Ipc::ShmemImporter::AllocationT mmappedShmemAlloc{shmemAlloc, ptr, 4096U};

    globalShmemImporter.release(mmappedShmemAlloc);
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.mmap.callCount);
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.munmap.callCount);
    EXPECT_EQ(0U, tempSysCallsCtx.apiConfig.close.callCount);

    ASSERT_EQ(0U, tempSysCallsCtx.vma.getSubRanges().size());
}

TEST(ShmemImporterRelease, givenAllocationWithoutMmappedPtrThenOnlyClosesFd) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;

    Cal::Ipc::ShmemImporter globalShmemImporter;

    auto shmemAlloc = OpenedShmemAllocationT{ShmemAllocation{1, false}, 1, 4096U, true};
    Cal::Ipc::ShmemImporter::AllocationT mmappedShmemAlloc{shmemAlloc, nullptr, 4096U};

    globalShmemImporter.release(mmappedShmemAlloc);
    EXPECT_EQ(0U, tempSysCallsCtx.apiConfig.mmap.callCount);
    EXPECT_EQ(0U, tempSysCallsCtx.apiConfig.munmap.callCount);
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.close.callCount);
}

TEST(ShmemAllocatorAllocate, whenRequestedNonPow2AlignmentThenReturnsInvalidAllocationAndEmitsError) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;

    Cal::Ipc::ShmemAllocator allocator;
    auto alloc = allocator.allocate(4U, 3);
    EXPECT_FALSE(alloc.isValid());
    EXPECT_EQ(0U, tempSysCallsCtx.apiConfig.shm_open.callCount);
    EXPECT_FALSE(logs.empty());
}

TEST(ShmemAllocatorAllocate, whenOutOfShmemIdsThenReturnsInvalidAllocationAndEmitsError) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;

    Cal::Mocks::ShmemAllocatorWhiteBox allocator;
    auto alloc = allocator.allocate(4U, 4096U);
    EXPECT_TRUE(alloc.isValid());
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.shm_open.callCount);
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.ftruncate.callCount);
    EXPECT_EQ(0U, tempSysCallsCtx.apiConfig.close.callCount);
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.shm_unlink.callCount);

    while (Cal::Allocators::BitAllocator::invalidOffset != allocator.shmemIdAllocator.allocate()) {
    }
    auto alloc2 = allocator.allocate(4U, 4096U);
    EXPECT_FALSE(alloc2.isValid());
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.shm_open.callCount);
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.ftruncate.callCount);
    EXPECT_EQ(0U, tempSysCallsCtx.apiConfig.close.callCount);
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.shm_unlink.callCount);

    allocator.free(alloc);
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.shm_open.callCount);
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.ftruncate.callCount);
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.close.callCount);
    EXPECT_EQ(2U, tempSysCallsCtx.apiConfig.shm_unlink.callCount);

    alloc2 = allocator.allocate(4U, 4096U);
    EXPECT_TRUE(alloc2.isValid());
    EXPECT_EQ(2U, tempSysCallsCtx.apiConfig.shm_open.callCount);
    EXPECT_EQ(2U, tempSysCallsCtx.apiConfig.ftruncate.callCount);
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.close.callCount);
    EXPECT_EQ(3U, tempSysCallsCtx.apiConfig.shm_unlink.callCount);

    allocator.free(alloc2);
    EXPECT_EQ(2U, tempSysCallsCtx.apiConfig.shm_open.callCount);
    EXPECT_EQ(2U, tempSysCallsCtx.apiConfig.ftruncate.callCount);
    EXPECT_EQ(2U, tempSysCallsCtx.apiConfig.close.callCount);
    EXPECT_EQ(4U, tempSysCallsCtx.apiConfig.shm_unlink.callCount);

    EXPECT_NE(Cal::Allocators::BitAllocator::invalidOffset, allocator.shmemIdAllocator.allocate());

    alloc = allocator.allocate(4U, 4096U);
    EXPECT_FALSE(alloc.isValid());

    EXPECT_FALSE(logs.empty());
}

TEST(ShmemAllocatorAllocate, whenCreatingShmemThenFirstUnlinkStalePath) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;

    std::string_view testBasePath = "/test_base_path";
    Cal::Ipc::ShmemAllocator allocator(testBasePath.data());

    std::string capturedUnlinkPath;
    tempSysCallsCtx.apiConfig.shm_unlink.impl = [&](const char *path) -> int {
        capturedUnlinkPath = path;
        return 0;
    };

    auto shmem = allocator.allocate(64);

    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.shm_unlink.callCount);
    EXPECT_STREQ((testBasePath.data() + std::to_string(0)).c_str(), capturedUnlinkPath.c_str());

    allocator.free(shmem);
}

TEST(ShmemAllocatorAllocate, whenFailedCreatingShmemThenReturnInvalidObject) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;

    Cal::Ipc::ShmemAllocator allocator;

    tempSysCallsCtx.apiConfig.shm_open.returnValue = -1;
    auto shmem = allocator.allocate(64);

    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.shm_open.callCount);
    EXPECT_FALSE(shmem.isValid());
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.shm_open.callCount);
    EXPECT_EQ(0U, tempSysCallsCtx.apiConfig.ftruncate.callCount);
    EXPECT_EQ(0U, tempSysCallsCtx.apiConfig.close.callCount);
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.shm_unlink.callCount);
    EXPECT_FALSE(logs.empty());
}

TEST(ShmemAllocatorAllocate, whenFailedTruncatingShmemFileThenReturnInvalidObject) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;

    Cal::Ipc::ShmemAllocator allocator;

    tempSysCallsCtx.apiConfig.ftruncate.returnValue = -1;
    auto shmem = allocator.allocate(64);

    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.shm_open.callCount);
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.ftruncate.callCount);
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.close.callCount);
    EXPECT_EQ(2U, tempSysCallsCtx.apiConfig.shm_unlink.callCount);
    EXPECT_FALSE(shmem.isValid());
    EXPECT_FALSE(logs.empty());
}

TEST(ShmemAllocatorAllocate, whenOpeningShmemThenProperFlagsAreUsed) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;

    std::string_view testBasePath = "/test_base_path";
    Cal::Ipc::ShmemAllocator allocator(testBasePath.data());

    std::string capturedName;
    int capturedOflag = {};
    mode_t capturedMode = {};
    tempSysCallsCtx.apiConfig.shm_open.impl = [&](const char *name, int oflag, mode_t mode) -> int {
        capturedName = name;
        capturedOflag = oflag;
        capturedMode = mode;
        return -1;
    };
    auto shmem = allocator.allocate(64);

    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.shm_open.callCount);
    EXPECT_STREQ((std::string(testBasePath.data()) + std::to_string(0)).c_str(), capturedName.c_str());
    EXPECT_EQ(O_CREAT | O_EXCL | O_RDWR, capturedOflag);
    EXPECT_EQ(mode_t{S_IRUSR | S_IWUSR}, capturedMode);
    EXPECT_FALSE(shmem.isValid());
    EXPECT_FALSE(logs.empty());
}

TEST(ShmemAllocatorAllocate, whenOpeningShmemThenFileIsTruncatedToRequestedSize) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;

    Cal::Ipc::ShmemAllocator allocator;
    size_t allocSize = 4099;
    size_t sizeAligned = Cal::Utils::alignUpPow2<Cal::Utils::pageSize4KB>(allocSize);
    int capturedFd = {};
    off_t capturedLength = {};
    tempSysCallsCtx.apiConfig.shm_open.returnValue = 7;
    tempSysCallsCtx.apiConfig.ftruncate.impl = [&](int fd, off_t length) -> int {
        capturedFd = fd;
        capturedLength = length;
        return -1;
    };
    auto shmem = allocator.allocate(allocSize);
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.ftruncate.callCount);
    EXPECT_EQ(7, capturedFd);
    EXPECT_EQ(sizeAligned, static_cast<size_t>(capturedLength));
    EXPECT_FALSE(shmem.isValid());
    EXPECT_FALSE(logs.empty());
}

TEST(ShmemAllocatorFree, whenOwnsFdThenClosesIt) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;

    Cal::Ipc::ShmemAllocator allocator;
    auto shmem = allocator.allocate(4099);
    EXPECT_TRUE(shmem.isValid());

    EXPECT_EQ(0U, tempSysCallsCtx.apiConfig.close.callCount);
    allocator.free(shmem);
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.close.callCount);
}

TEST(ShmemAllocatorFree, whenOwnsShmemThenUnlinksShmemPath) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;

    Cal::Ipc::ShmemAllocator allocator;
    auto shmem = allocator.allocate(4099);
    EXPECT_TRUE(shmem.isValid());

    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.shm_unlink.callCount);
    allocator.free(shmem);
    EXPECT_EQ(2U, tempSysCallsCtx.apiConfig.shm_unlink.callCount);
}

TEST(ShmemAllocatorFree, whenOwnsFdAndFailedToCloseItThenEmitsError) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;

    Cal::Ipc::ShmemAllocator allocator;
    auto shmem = allocator.allocate(4099);
    EXPECT_TRUE(shmem.isValid());

    EXPECT_EQ(0U, tempSysCallsCtx.apiConfig.close.callCount);
    tempSysCallsCtx.apiConfig.close.returnValue = -1;
    allocator.free(shmem);
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.close.callCount);
    EXPECT_FALSE(logs.empty());
}

TEST(ShmemAllocatorFree, whenOwnsShmemValidAndFailedToUnlinkShmemPathThenEmitsError) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;
    Cal::Mocks::LogCaptureContext logs;

    Cal::Ipc::ShmemAllocator allocator;
    auto shmem = allocator.allocate(4099);
    EXPECT_TRUE(shmem.isValid());

    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.shm_unlink.callCount);
    tempSysCallsCtx.apiConfig.shm_unlink.returnValue = -1;
    allocator.free(shmem);
    EXPECT_EQ(2U, tempSysCallsCtx.apiConfig.shm_unlink.callCount);
    EXPECT_FALSE(logs.empty());
}

TEST(ShmemAllocatorFree, whenDoesNotOwnFdThenDoesNotCloseIt) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;

    Cal::Ipc::ShmemAllocator allocator;
    auto alloc = allocator.allocate(4099);
    EXPECT_TRUE(alloc.isValid());

    EXPECT_EQ(0U, tempSysCallsCtx.apiConfig.close.callCount);
    Cal::Mocks::MmappedShmemAllocationWhiteBox allocSharingFd{alloc, nullptr, 0};
    allocSharingFd.isFdOwner = false;
    allocator.free(allocSharingFd);
    EXPECT_EQ(0U, tempSysCallsCtx.apiConfig.close.callCount);
}

TEST(ShmemAllocatorFree, whenDoesNotOwnShmemThenDoesNotUnlinksShmemPath) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;

    Cal::Ipc::ShmemAllocator allocator;
    auto alloc = allocator.allocate(4099);
    EXPECT_TRUE(alloc.isValid());

    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.shm_unlink.callCount);
    Cal::Mocks::MmappedShmemAllocationWhiteBox allocSharingShmem{alloc, nullptr, 0};
    allocSharingShmem.isShmemOwner = false;
    allocator.free(allocSharingShmem);
    EXPECT_EQ(1U, tempSysCallsCtx.apiConfig.shm_unlink.callCount);
}

TEST(NonUsmMmappedShmemAllocator, givenAllocatorThenUsesProperMmapConfig) {
    Cal::Mocks::SysCallsContext tempSysCallsCtx;

    Cal::Ipc::ShmemAllocator shmemAllocator;
    NonUsmMmappedShmemAllocator allocator{shmemAllocator};
    auto mmapConfig = allocator.getMmapConfig();

    EXPECT_EQ(PROT_READ | PROT_WRITE, mmapConfig.prot) << "Should be mapped with RW access";
    EXPECT_EQ(MAP_SHARED, mmapConfig.flags) << "Should mapped as shared to support IPC";
}

} // namespace Ult
} // namespace Cal
