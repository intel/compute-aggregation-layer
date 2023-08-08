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

class TestStagingAreaManager : public StagingAreaManager<std::function<void *(size_t)>, std::function<void(void *)>> {
  public:
    TestStagingAreaManager(bool *wasDeallocated) : StagingAreaManager([this](size_t size) { return this->testAllocator(size); }, [this](void *ptr) { return this->testDeallocator(ptr); }),
                                                   testDeallocatorCalled(wasDeallocated) {}

    void *testAllocator(size_t size) {
        void *alloc = malloc(size);
        testAllocatorCalled++;
        allocations.push_back(std::pair(alloc, size));
        return alloc;
    }
    void testDeallocator(void *ptr) {
        free(ptr);
        *testDeallocatorCalled = true;
    }

    int testAllocatorCalled = 0;
    bool *testDeallocatorCalled;
};

TEST(StagingAreaManager, givenStagingAreaManagerWhenAllocatingMemoryThenMemoryIsCorrectlyAllocatedAndDeallocated) {
    bool wasDeallocated = false;
    {
        TestStagingAreaManager manager(&wasDeallocated);
        auto firstAlloc = manager.allocateStagingArea(16);
        memset(firstAlloc, 0, 16);
        EXPECT_NE(firstAlloc, nullptr);
        EXPECT_EQ(manager.testAllocatorCalled, 1);

        auto secondAlloc = manager.allocateStagingArea(32);
        EXPECT_NE(secondAlloc, nullptr);
        EXPECT_EQ(manager.testAllocatorCalled, 2);
        EXPECT_NE(firstAlloc, secondAlloc);

        auto previousAlloc = manager.allocateStagingArea(16);
        EXPECT_EQ(previousAlloc, firstAlloc);
        EXPECT_EQ(manager.testAllocatorCalled, 2);
    }
    EXPECT_TRUE(wasDeallocated);
}
} // namespace Ult
} // namespace Cal
