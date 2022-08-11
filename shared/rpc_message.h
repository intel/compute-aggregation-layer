/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include <cinttypes>
#include <type_traits>

namespace Cal {

namespace Rpc {

struct RpcMessageHeader {
    using MessageTypeT = uint16_t;
    using MessageSubTypeT = uint16_t;
    using MessageUniqueIdT = uint32_t;
    static_assert(sizeof(MessageTypeT) + sizeof(MessageSubTypeT) == sizeof(MessageUniqueIdT));
    static constexpr MessageTypeT messageTypeUnknown = 0U;
    static constexpr MessageTypeT messageTypeRpcOcl = 1U;
    static constexpr MessageTypeT messageTypeRpcLevelZero = 2U;
    MessageTypeT type = messageTypeUnknown;
    MessageSubTypeT subtype = messageTypeUnknown;
};
static_assert(std::is_standard_layout_v<RpcMessageHeader>);

struct RpcCallId {
    constexpr RpcCallId(RpcMessageHeader::MessageTypeT type, RpcMessageHeader::MessageSubTypeT subtype)
        : type(type), subtype(subtype) {
    }
    constexpr RpcCallId() : type(RpcMessageHeader::messageTypeUnknown), subtype(RpcMessageHeader::messageTypeUnknown) {
    }
    union {
        struct {
            RpcMessageHeader::MessageTypeT type;
            RpcMessageHeader::MessageSubTypeT subtype;
        };
        RpcMessageHeader::MessageUniqueIdT id;
    };
};
static_assert(std::is_standard_layout_v<RpcCallId>);

using DirectCallCallbackT = bool (*)(Cal::Rpc::RpcMessageHeader *command);

} // namespace Rpc

} // namespace Cal
