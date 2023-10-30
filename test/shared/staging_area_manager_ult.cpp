/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "gtest/gtest.h"
#include "shared/staging_area_manager.h"
namespace Cal {
namespace Ult {

class TestStagingAreaManager {
  public:
    TestStagingAreaManager(int *deallocationCounter) : stagingAreaManager([this](size_t size) { return this->testAllocator(size); },
                                                                          [this](void *ptr) { return this->testDeallocatorWithCounter(ptr); }),
                                                       deallocationCounter(deallocationCounter) {}

    TestStagingAreaManager() : stagingAreaManager([this](size_t size) { return this->testAllocator(size); },
                                                  [this](void *ptr) { return this->testDeallocator(ptr); }) {}
    void *testAllocator(size_t size) {
        void *alloc = malloc(size);
        testAllocatorCalled++;
        return alloc;
    }
    void testDeallocator(void *ptr) {
        free(ptr);
    }
    void testDeallocatorWithCounter(void *ptr) {
        free(ptr);
        *deallocationCounter += 1;
    }

    StagingAreaManager<std::function<void *(size_t)>, std::function<void(void *)>> stagingAreaManager;
    int testAllocatorCalled = 0;
    int *deallocationCounter = nullptr;
};

TEST(StagingAreaManager, givenStagingAreaManagerWhenAllocatingMemoryThenMemoryIsCorrectlyAllocatedAndDeallocated) {
    int deallocationCounter = 0;
    {
        TestStagingAreaManager manager(&deallocationCounter);
        auto firstAlloc = manager.stagingAreaManager.allocateStagingArea(16);
        memset(firstAlloc, 0, 16);
        EXPECT_NE(firstAlloc, nullptr);
        EXPECT_EQ(manager.testAllocatorCalled, 1);

        auto secondAlloc = manager.stagingAreaManager.allocateStagingArea(32);
        EXPECT_NE(secondAlloc, nullptr);
        EXPECT_EQ(manager.testAllocatorCalled, 2);
        EXPECT_NE(firstAlloc, secondAlloc);

        auto thirdAlloc = manager.stagingAreaManager.allocateStagingArea(16);
        EXPECT_NE(thirdAlloc, nullptr);
        EXPECT_EQ(manager.testAllocatorCalled, 3);
    }
    EXPECT_EQ(deallocationCounter, 3);
}

TEST(StagingAreaManager, givenStagingAreaManagerWhenAllocatingAreaOfSameSizeAndUnusedThenSameAllocationIsReturned) {
    TestStagingAreaManager manager{};

    auto deleter = [&manager](void *ptr) { manager.stagingAreaManager.releaseStagingArea(ptr); };
    void *ptrToFirstStagingArea{};
    {
        std::unique_ptr<void, std::function<void(void *)>> firstAlloc(manager.stagingAreaManager.allocateStagingArea(16), deleter);
        EXPECT_NE(firstAlloc.get(), nullptr);
        ptrToFirstStagingArea = firstAlloc.get();
    }

    {
        std::unique_ptr<void, std::function<void(void *)>> secondAlloc(manager.stagingAreaManager.allocateStagingArea(16), deleter);
        EXPECT_NE(secondAlloc.get(), nullptr);
        EXPECT_EQ(secondAlloc.get(), ptrToFirstStagingArea);
    }
}
} // namespace Ult
} // namespace Cal
