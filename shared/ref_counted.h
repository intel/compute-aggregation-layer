/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "shared/log.h"

#include <atomic>
#include <cstdlib>
#include <limits>
#include <mutex>
#include <unordered_map>

namespace Cal {
namespace Shared {

template <typename BaseT, typename TypePrinterT>
class RefCounted : public BaseT {
    friend class SingleReference;

  public:
    using RemoteObjectT = BaseT *;
    using CleanupFuncT = void (*)(void *remoteObject, void *localObject);

    RefCounted(RemoteObjectT remoteObject, CleanupFuncT cleanupFunc) : remoteObject(remoteObject), cleanupFunc(cleanupFunc) {}

    uint32_t dec() {
        if (externalRefCount >= refCount) {
            log<Verbosity::error>("Attempt to decrease refCount while %d other objects are referencing this element.",
                                  static_cast<uint32_t>(externalRefCount));
            return refCount;
        }

        auto prev = refCount--;
        const char *objectTypeName = TypePrinterT::template getObjectTypeAsStr<RemoteObjectT>();
        log<Verbosity::bloat>("Decreasing %s refcount for %p - previous refcount was %d", objectTypeName, this, prev);
        if (prev == 1) {
            log<Verbosity::bloat>("Destroying client-side %s : %p", objectTypeName, this);
            if (cleanupFunc) {
                cleanupFunc(remoteObject, this);
            }
            delete this;
        }
        return prev;
    }

    uint32_t inc() {
        auto prev = refCount++;
        const char *objectTypeName = TypePrinterT::template getObjectTypeAsStr<RemoteObjectT>();
        log<Verbosity::bloat>("Increasing refcount for %s : %p - previous refcount was %d", objectTypeName, this, prev);
        return prev;
    }

    RemoteObjectT asRemoteObject() const {
        return remoteObject;
    }

    uint32_t peekRefCount() {
        return refCount;
    }

  protected:
    uint32_t externalInc() {
        externalRefCount++;
        return inc();
    }
    uint32_t externalDec() {
        externalRefCount--;
        return dec();
    }

    virtual ~RefCounted() = default;

    std::atomic_uint refCount = 1;
    std::atomic_uint externalRefCount = 0;
    RemoteObjectT remoteObject = {};
    CleanupFuncT cleanupFunc = nullptr;
};

class SingleReference {
    class RefCountedOpaque {
      public:
        virtual uint32_t dec() = 0;
        virtual uint32_t inc() = 0;
        virtual uint32_t externalInc() = 0;
        virtual uint32_t externalDec() = 0;

        virtual std::unique_ptr<RefCountedOpaque> clone() const = 0;
        virtual ~RefCountedOpaque() = default;
    };

    template <typename RefCountedT>
    class ReferenceToRefCounted : public RefCountedOpaque {
      public:
        ReferenceToRefCounted(RefCountedT *refCounted)
            : refCounted(refCounted) {
        }

        uint32_t dec() override {
            if (refCounted) {
                return refCounted->dec();
            }
            return std::numeric_limits<uint32_t>::max();
        }
        uint32_t inc() override {
            if (refCounted) {
                refCounted->inc();
            }
            return std::numeric_limits<uint32_t>::max();
        }
        uint32_t externalInc() override {
            if (refCounted) {
                refCounted->externalInc();
            }
            return std::numeric_limits<uint32_t>::max();
        }
        uint32_t externalDec() override {
            if (refCounted) {
                return refCounted->externalDec(); // NOLINT(clang-analyzer-cplusplus.NewDelete)
            }
            return std::numeric_limits<uint32_t>::max();
        }

        std::unique_ptr<RefCountedOpaque> clone() const override {
            return std::make_unique<ReferenceToRefCounted<RefCountedT>>(refCounted);
        }

      protected:
        RefCountedT *refCounted = nullptr;
    };

  public:
    template <typename ObjT>
    SingleReference(ObjT *obj) {
        wrappedObj = std::make_unique<ReferenceToRefCounted<ObjT>>(obj);
        wrappedObj->externalInc();
    }

    ~SingleReference() {
        if (wrappedObj) {
            wrappedObj->externalDec(); // NOLINT(clang-analyzer-cplusplus.NewDelete)
        }
    }

    SingleReference(const SingleReference &) = delete;
    SingleReference &operator=(const SingleReference &) = delete;

    SingleReference(SingleReference &&rhs) {
        this->wrappedObj = std::move(rhs.wrappedObj);
    }

    SingleReference &operator=(SingleReference &&rhs) {
        this->wrappedObj = std::move(rhs.wrappedObj);
        return *this;
    }

    template <typename ObjT>
    static SingleReference wrap(ObjT *obj) {
        return SingleReference(obj);
    }

    static SingleReference wrap(std::nullptr_t) {
        return SingleReference{};
    }

    SingleReference clone() {
        SingleReference ret;
        if (this->wrappedObj) {
            ret.wrappedObj = this->wrappedObj->clone();
            ret.wrappedObj->externalInc();
        }
        return ret;
    }

  protected:
    SingleReference() = default;
    std::unique_ptr<RefCountedOpaque> wrappedObj = nullptr;
};

template <typename BaseT, typename TypePrinterT>
class RefCountedWithParent : public RefCounted<BaseT, TypePrinterT> {
  public:
    RefCountedWithParent(typename RefCounted<BaseT, TypePrinterT>::RemoteObjectT remoteObject, SingleReference &&parent,
                         typename RefCounted<BaseT, TypePrinterT>::CleanupFuncT cleanupFunc) : RefCounted<BaseT, TypePrinterT>(remoteObject, cleanupFunc), parent(std::move(parent)) {
    }

    ~RefCountedWithParent() override = default;

    SingleReference cloneReferenes() {
        return parent.clone();
    }

  protected:
    SingleReference parent;
};

} // namespace Shared
} // namespace Cal
