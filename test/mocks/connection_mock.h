/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "shared/ipc.h"

#include <functional>
#include <type_traits>

namespace Cal {

namespace Mocks {

class ConnectionMock : public Cal::Ipc::Connection {
  public:
    ~ConnectionMock() override = default;

    ConnectionMock() = default;
    ConnectionMock(const ConnectionMock &rhs) {
    }

    int send(const void *data, size_t dataSize) override {
        if (apiConfig.send.impl) {
            return apiConfig.send.impl.value()(data, dataSize);
        }
        return apiConfig.send.defaultReturnValue;
    }

    int receive(void *data, size_t dataSize) override {
        if (apiConfig.receive.impl) {
            return apiConfig.receive.impl.value()(data, dataSize);
        }
        return apiConfig.receive.defaultReturnValue;
    }

    int peek(void *data, size_t dataSize) override {
        if (apiConfig.peek.impl) {
            return apiConfig.peek.impl.value()(data, dataSize);
        }
        return apiConfig.peek.defaultReturnValue;
    }

    int close() override {
        if (apiConfig.close.impl) {
            return apiConfig.close.impl.value()();
        }
        return apiConfig.close.defaultReturnValue;
    }

    bool isAlive() override {
        if (apiConfig.isAlive.impl) {
            return apiConfig.isAlive.impl.value()();
        }
        return apiConfig.isAlive.defaultReturnValue;
    }

    int getId() override {
        if (apiConfig.getId.impl) {
            return apiConfig.getId.impl.value()();
        }
        return apiConfig.getId.defaultReturnValue;
    }

    std::unique_lock<std::mutex> lock() override {
        if (apiConfig.lock.impl) {
            return apiConfig.lock.impl.value()();
        }
        return std::unique_lock<std::mutex>(mutex);
    }

    struct {
        struct {
            std::optional<std::function<int(const void *data, size_t dataSize)>> impl;
            int defaultReturnValue = 0;
        } send;

        struct {
            std::optional<std::function<int(const void *data, size_t dataSize)>> impl;
            int defaultReturnValue = 0;
        } receive;

        struct {
            std::optional<std::function<int(const void *data, size_t dataSize)>> impl;
            int defaultReturnValue = 0;
        } peek;

        struct {
            std::optional<std::function<int()>> impl;
            int defaultReturnValue = 0;
        } close;

        struct {
            std::optional<std::function<bool()>> impl;
            int defaultReturnValue = 0;
        } isAlive;

        struct {
            std::optional<std::function<int()>> impl;
            int defaultReturnValue = 0;
        } getId;

        struct {
            std::optional<std::function<std::unique_lock<std::mutex>()>> impl;
            int defaultReturnValue = 0;
        } lock;
    } apiConfig;

    std::mutex mutex;
};

template <typename MessagesT, int CurrIt = 0>
auto equals(const MessagesT &messages, int expIt, const void *data, size_t dataSize, std::string &outMismatchLog)
    -> std::enable_if_t<CurrIt >= std::tuple_size<MessagesT>(), bool> {
    outMismatchLog = "Not enough messages in the stream";
    return false;
}

template <typename MessagesT, int CurrIt = 0>
    auto equals(const MessagesT &messages, int expIt, const void *data, size_t dataSize, std::string &outMismatchLog)
        -> std::enable_if_t < CurrIt<std::tuple_size<MessagesT>(), bool> {
    if (CurrIt < expIt) {
        return equals<MessagesT, CurrIt + 1>(messages, expIt, data, dataSize, outMismatchLog);
    }

    {
        auto &expMessage = std::get<CurrIt>(messages);
        if (sizeof(expMessage) > dataSize) {
            outMismatchLog.append("Not enough size (" + std::to_string(dataSize) + " < " + std::to_string(sizeof(expMessage)) + ") for message #" + std::to_string(expIt) + ".");
            return false;
        }

        auto gotMessage = reinterpret_cast<const std::decay_t<decltype(expMessage)> *>(data);
        bool same = true;
        if (gotMessage->header.type != expMessage.header.type) {
            outMismatchLog.append("Data mismatch for message #" + std::to_string(expIt) + " - invalid type.");
            same = false;
        }
        if (gotMessage->header.subtype != expMessage.header.subtype) {
            outMismatchLog.append("Data mismatch for message #" + std::to_string(expIt) + " - invalid subtype.");
            same = false;
        }

        if (false == (*gotMessage == expMessage)) { // comparison operators are defined along control messages
            outMismatchLog.append("Data mismatch for message #" + std::to_string(expIt) + " - payload mismatch.");
            same = false;
        }

        return same;
    }

    return false; // unreachable
}

template <typename MessagesT, int CurrIt = 0>
auto encode(const MessagesT &messages, int expIt, void *data, size_t dataSize, std::string &encodeIssuesLog)
    -> std::enable_if_t<CurrIt >= std::tuple_size<MessagesT>(), bool> {
    encodeIssuesLog = "Not enough messages in the stream";
    return false;
}

template <typename MessagesT, int CurrIt = 0>
    auto encode(const MessagesT &messages, int expIt, void *data, size_t dataSize, std::string &encodeIssuesLog)
        -> std::enable_if_t < CurrIt<std::tuple_size<MessagesT>(), int> {
    if (CurrIt < expIt) {
        return encode<MessagesT, CurrIt + 1>(messages, expIt, data, dataSize, encodeIssuesLog);
    }

    {
        auto &currMessage = std::get<CurrIt>(messages);
        if (sizeof(currMessage) > dataSize) {
            encodeIssuesLog.append("Not enough size (" + std::to_string(dataSize) + " < " + std::to_string(sizeof(currMessage)) + ") for message #" + std::to_string(expIt) + ".");
            return 0;
        }

        memcpy(data, &currMessage, sizeof(currMessage));
        return sizeof(currMessage);
    }

    return 0; // unreachable
}

template <typename InMessagesT, typename OutMessagesT>
class ConnectionExpectedProtocol : public ConnectionMock {
  public:
    InMessagesT inMessages;
    OutMessagesT outMessages;

    int inIt = 0;
    int outIt = 0;

    int send(const void *data, size_t dataSize) override {
        if (outIt >= std::tuple_size<OutMessagesT>()) {
            return 0;
        }

        std::string mismatchLog;
        auto success = equals(outMessages, inIt, data, dataSize, mismatchLog);
        if (false == mismatchLog.empty()) {
            mismatchLogs.push_back(mismatchLog);
        }
        ++outIt;
        return success ? dataSize : 0U;
    }

    int receive(void *data, size_t dataSize) override {
        if (inIt >= std::tuple_size<InMessagesT>()) {
            return 0;
        }
        auto ret = peek(data, dataSize);
        ++inIt;
        return ret;
    }

    int peek(void *data, size_t dataSize) override {
        if (inIt >= std::tuple_size<InMessagesT>()) {
            return 0;
        }
        std::string encodeIssue;
        auto ret = encode<InMessagesT>(inMessages, inIt, data, dataSize, encodeIssue);
        if (false == encodeIssues.empty()) {
            encodeIssues.push_back(encodeIssue);
        }
        return ret;
    }

    std::string getMismatchLogFlat() const {
        std::stringstream ss;
        for (const auto &log : mismatchLogs) {
            ss << log;
        }
        return ss.str();
    }

    std::string getEncodeLogFlat() const {
        std::stringstream ss;
        for (const auto &log : encodeIssues) {
            ss << log;
        }
        return ss.str();
    }

    std::vector<std::string> mismatchLogs;
    std::vector<std::string> encodeIssues;
};

} // namespace Mocks

} // namespace Cal
