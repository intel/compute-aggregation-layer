/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "gtest/gtest.h"
#include "shared/ref_counted.h"

#include <atomic>
#include <string>

namespace Cal {

namespace Ult {

struct TestLocalObject {
    virtual ~TestLocalObject() {
        if (nullptr != this->wasDestroyedFlag) {
            *this->wasDestroyedFlag = true;
        }
    }

    template <typename ObjT>
    static const char *getObjectTypeAsStr() {
        if constexpr (std::is_same_v<TestLocalObject, ObjT>) {
            return "TestLocalObject";
        } else {
            return "unknown";
        }
    }

    static void cleanup(void *remoteObject, void *localObject) {
        TestLocalObject *remote = static_cast<TestLocalObject *>(remoteObject);
        remote->cleanedUpObjects.remote = remoteObject;
        remote->cleanedUpObjects.local = localObject;
    }

    struct {
        void *remote = nullptr;
        void *local = nullptr;
    } cleanedUpObjects;

    bool *wasDestroyedFlag = nullptr;
};

using TestReferenceT = Cal::Shared::RefCounted<TestLocalObject, TestLocalObject>;

std::function<void(TestReferenceT *)> createDeleter(bool &wasDestroyed) {
    return [&wasDestroyed](TestReferenceT *p) {
        if (wasDestroyed == false) {
            auto counter = p->peekRefCount();
            while (counter > 0) {
                p->dec();
                counter--;
            }
        }
    };
}

using Deleter = std::function<void(TestReferenceT *)>;

TEST(RefCounted, WhenRefcountReachesZeroThenLocalObjectGetsDestroyed) {
    bool localWasDestroyed = false;
    bool remoteWasDestroyed = false;

    TestLocalObject remoteObject;
    remoteObject.wasDestroyedFlag = &remoteWasDestroyed;
    auto localRef = std::unique_ptr<TestReferenceT, Deleter>(new TestReferenceT(&remoteObject, nullptr), createDeleter(localWasDestroyed));
    localRef->wasDestroyedFlag = &localWasDestroyed;
    EXPECT_EQ(&remoteObject, localRef->asRemoteObject());

    localRef->dec();
    EXPECT_TRUE(localWasDestroyed);
    ASSERT_FALSE(remoteWasDestroyed);
}

TEST(RefCounted, GivenCustomCleanupFuncWhenDestroyingRefcountedObjectThenCallsTheCleanupFuncBeforeDelete) {
    bool localWasDestroyed = false;
    bool remoteWasDestroyed = false;

    TestLocalObject remoteObject;
    remoteObject.wasDestroyedFlag = &remoteWasDestroyed;
    auto localRef = std::unique_ptr<TestReferenceT, Deleter>(new TestReferenceT(&remoteObject, TestLocalObject::cleanup), createDeleter(localWasDestroyed));
    localRef->wasDestroyedFlag = &localWasDestroyed;

    localRef->dec();
    EXPECT_TRUE(localWasDestroyed);

    ASSERT_FALSE(remoteWasDestroyed);
    EXPECT_EQ(localRef.get(), remoteObject.cleanedUpObjects.local);
    EXPECT_EQ(&remoteObject, remoteObject.cleanedUpObjects.remote);
}

TEST(RefCounted, WhenManipulatingTheRefcountThenObjectGetsDestroyedOnlyIfRefcountReachesZero) {
    bool localWasDestroyed = false;
    bool remoteWasDestroyed = false;

    TestLocalObject remoteObject;
    remoteObject.wasDestroyedFlag = &remoteWasDestroyed;
    auto localRef = std::unique_ptr<TestReferenceT, Deleter>(new TestReferenceT(&remoteObject, nullptr), createDeleter(localWasDestroyed));
    localRef->wasDestroyedFlag = &localWasDestroyed;

    EXPECT_EQ(1U, localRef->peekRefCount());
    localRef->inc();
    EXPECT_EQ(2U, localRef->peekRefCount());
    ASSERT_FALSE(localWasDestroyed);

    localRef->dec();
    EXPECT_EQ(1U, localRef->peekRefCount());
    ASSERT_FALSE(localWasDestroyed);

    localRef->inc();
    ASSERT_FALSE(localWasDestroyed);
    localRef->inc();
    EXPECT_EQ(3U, localRef->peekRefCount());
    ASSERT_FALSE(localWasDestroyed);

    localRef->dec();
    EXPECT_EQ(2U, localRef->peekRefCount());
    ASSERT_FALSE(localWasDestroyed);

    localRef->dec();
    EXPECT_EQ(1U, localRef->peekRefCount());
    ASSERT_FALSE(localWasDestroyed);

    localRef->dec();
    EXPECT_TRUE(localWasDestroyed);

    EXPECT_FALSE(remoteWasDestroyed);
}

TEST(SingleReference, GivenAnyTypeThenCreatesTypeErasedReference) {
    bool localWasDestroyed = false;
    TestLocalObject remoteObject;
    auto localRef = std::unique_ptr<TestReferenceT, Deleter>(new TestReferenceT(&remoteObject, nullptr), createDeleter(localWasDestroyed));
    localRef->wasDestroyedFlag = &localWasDestroyed;

    {
        Cal::Shared::SingleReference singleRef = Cal::Shared::SingleReference::wrap(localRef.get());
        EXPECT_EQ(2U, localRef->peekRefCount());
        localRef->dec();
        EXPECT_EQ(1U, localRef->peekRefCount());

        ASSERT_FALSE(localWasDestroyed) << "shouldn't be destroyed due to reference in singleRef";
    }
    EXPECT_TRUE(localWasDestroyed);
}

TEST(SingleReference, WhenCreatedFromNullThenDoesNothingOnDelete) {
    Cal::Shared::SingleReference singleRef = Cal::Shared::SingleReference::wrap(nullptr);
}

TEST(SingleReference, WhenCloningThenIncreasesReference) {
    bool localWasDestroyed = false;
    TestLocalObject remoteObject;
    auto localRef = std::unique_ptr<TestReferenceT, Deleter>(new TestReferenceT(&remoteObject, nullptr), createDeleter(localWasDestroyed));
    localRef->wasDestroyedFlag = &localWasDestroyed;

    {
        Cal::Shared::SingleReference ref1 = Cal::Shared::SingleReference::wrap(nullptr);
        {
            Cal::Shared::SingleReference ref0 = Cal::Shared::SingleReference::wrap(localRef.get());
            EXPECT_EQ(2U, localRef->peekRefCount());
            localRef->dec();
            ASSERT_FALSE(localWasDestroyed) << "shouldn't be destroyed due to reference in ref0";
            EXPECT_EQ(1U, localRef->peekRefCount());
            ref1 = ref0.clone();
            EXPECT_EQ(2U, localRef->peekRefCount());
        }
        EXPECT_EQ(1U, localRef->peekRefCount());
        ASSERT_FALSE(localWasDestroyed) << "shouldn't be destroyed due to reference in ref1";
    }
    EXPECT_TRUE(localWasDestroyed);
}

TEST(SingleReference, WhenMovingThenRefcountIsNotChanged) {
    bool localWasDestroyed = false;
    TestLocalObject remoteObject;
    auto localRef = std::unique_ptr<TestReferenceT, Deleter>(new TestReferenceT(&remoteObject, nullptr), createDeleter(localWasDestroyed));
    localRef->wasDestroyedFlag = &localWasDestroyed;

    {
        Cal::Shared::SingleReference ref1 = Cal::Shared::SingleReference::wrap(nullptr);
        {
            Cal::Shared::SingleReference ref0 = Cal::Shared::SingleReference::wrap(localRef.get());
            EXPECT_EQ(2U, localRef->peekRefCount());
            localRef->dec();
            ASSERT_FALSE(localWasDestroyed) << "shouldn't be destroyed due to reference in ref0";
            EXPECT_EQ(1U, localRef->peekRefCount());
            ref1 = std::move(ref0);
            EXPECT_EQ(1U, localRef->peekRefCount());
        }
        ASSERT_FALSE(localWasDestroyed) << "shouldn't be destroyed due to reference in ref1";
    }
    EXPECT_TRUE(localWasDestroyed);
}

TEST(RefCountedWithParent, WhenCreatedWithParentObjectThenMaintainsASingleReferenceToThatParent) {
    bool localParentWasDestroyed = false;
    TestLocalObject remoteParentObject;
    auto localParentRef = std::unique_ptr<TestReferenceT, Deleter>(new TestReferenceT(&remoteParentObject, nullptr), createDeleter(localParentWasDestroyed));
    localParentRef->wasDestroyedFlag = &localParentWasDestroyed;
    {
        bool localChildWasDestroyed = false;
        TestLocalObject remoteChildObject;
        auto localParentRef = std::unique_ptr<TestReferenceT, Deleter>(new TestReferenceT(&remoteParentObject, nullptr), createDeleter(localChildWasDestroyed));
        EXPECT_EQ(1U, localParentRef->peekRefCount());
        auto localChildRef = new Cal::Shared::RefCountedWithParent<TestLocalObject, TestLocalObject>(&remoteChildObject, localParentRef.get(), nullptr);
        localChildRef->wasDestroyedFlag = &localChildWasDestroyed;
        EXPECT_EQ(2U, localParentRef->peekRefCount());
        localChildRef->dec();
        EXPECT_TRUE(localChildWasDestroyed);
        ASSERT_FALSE(localParentWasDestroyed);
        EXPECT_EQ(1U, localParentRef->peekRefCount());
    }
    localParentRef->dec();
    EXPECT_TRUE(localParentRef->wasDestroyedFlag);
}

} // namespace Ult
} // namespace Cal
