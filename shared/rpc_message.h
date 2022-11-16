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
    using MessageFlagsT = uint8_t;
    enum FlagsBits : MessageFlagsT {
        signalSemaphoreOnCompletion = 1 << 0
    };

    using MessageTypeT = uint8_t;
    using MessageSubTypeT = uint16_t;
    using MessageUniqueIdT = uint32_t;

    static_assert(sizeof(MessageFlagsT) + sizeof(MessageTypeT) + sizeof(MessageSubTypeT) == sizeof(MessageUniqueIdT));
    static constexpr MessageTypeT messageTypeUnknown = 0U;
    static constexpr MessageTypeT messageTypeRpcOcl = 1U;
    static constexpr MessageTypeT messageTypeRpcLevelZero = 2U;
    MessageFlagsT flags = 0U;
    MessageTypeT type = messageTypeUnknown;
    MessageSubTypeT subtype = messageTypeUnknown;
};
static_assert(sizeof(RpcMessageHeader) == sizeof(RpcMessageHeader::MessageUniqueIdT));
static_assert(std::is_standard_layout_v<RpcMessageHeader>);

struct RpcCallId {
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

} // namespace Rpc

} // namespace Cal
