/*
 * Copyright (C) 2022-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include <cinttypes>
#include <type_traits>
#include <vector>

namespace Cal {

namespace Rpc {

struct RpcMessageHeader {
    using MessageFlagsT = uint8_t;
    enum FlagsBits : MessageFlagsT {
        signalSemaphoreOnCompletion = 1 << 0,
        batched = 1 << 1,
        async = 1 << 2
    };

    using MessageTypeT = uint8_t;
    using MessageSubTypeT = uint16_t;
    using MessageUniqueIdT = uint32_t;

    static_assert(sizeof(MessageFlagsT) + sizeof(MessageTypeT) + sizeof(MessageSubTypeT) == sizeof(MessageUniqueIdT));
    static constexpr MessageTypeT messageTypeUnknown = 0U;
    static constexpr MessageTypeT messageTypeRpcOcl = 1U;
    static constexpr MessageTypeT messageTypeRpcLevelZero = 2U;
    static constexpr MessageTypeT messageTypeRpcDrmIoctl = 3U;
    MessageFlagsT flags = 0U;
    MessageTypeT type = messageTypeUnknown;
    MessageSubTypeT subtype = messageTypeUnknown;
};
static_assert(sizeof(RpcMessageHeader) == sizeof(RpcMessageHeader::MessageUniqueIdT));
static_assert(std::is_standard_layout_v<RpcMessageHeader>);

struct RpcCallId {
    constexpr RpcCallId(RpcMessageHeader header)
        : unused(0), type(header.type), subtype(header.subtype) {
    }

    constexpr RpcCallId(RpcMessageHeader::MessageTypeT type, RpcMessageHeader::MessageSubTypeT subtype)
        : unused(0), type(type), subtype(subtype) {
    }
    constexpr RpcCallId() : unused(0), type(RpcMessageHeader::messageTypeUnknown), subtype(RpcMessageHeader::messageTypeUnknown) {
    }
    union {
        struct {
            RpcMessageHeader::MessageFlagsT unused;
            RpcMessageHeader::MessageTypeT type;
            RpcMessageHeader::MessageSubTypeT subtype;
        };
        RpcMessageHeader::MessageUniqueIdT id;
    };
};
static_assert(std::is_standard_layout_v<RpcCallId>);

using DirectCallCallbackT = bool (*)(Cal::Rpc::RpcMessageHeader *command);

enum class CallCategory {
    Other = 0,
    Compute,
    Copy
};

template <typename Ptr>
inline void forcePointerWrite(Ptr &p, void *value) {
    static_assert(std::is_pointer_v<Ptr>, "forcePointerWrite() must be used with pointers!");
    using WritablePtr = std::remove_cv_t<Ptr>;

    const_cast<WritablePtr &>(p) = static_cast<WritablePtr>(value);
}

template <typename T>
inline char *asMemcpyDstT(T *ptr) {
    static_assert(std::is_standard_layout_v<T>);
    return reinterpret_cast<char *>(const_cast<std::remove_const_t<T> *>(ptr));
};

inline char *asMemcpyDstT(const void *ptr) {
    return reinterpret_cast<char *>(const_cast<void *>(ptr));
};

inline char *asMemcpyDstT(void *ptr) {
    return reinterpret_cast<char *>(const_cast<void *>(ptr));
};

struct DynamicArgTraits {
    uint32_t offset;
    uint32_t count;
    uint32_t size;
    std::vector<DynamicArgTraits> nested;
};

namespace LevelZero {

template <typename DynamicStructT>
struct DynamicStructTraits {
    int32_t offset;
    int32_t count;
};

} // namespace LevelZero

} // namespace Rpc

} // namespace Cal

template <typename T>
inline bool isSuccessful(T result) {
    return result == 0;
}
