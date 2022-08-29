/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once
// #### Generated code -- begin ####
#include "shared/rpc_message.h"
#include "shared/shmem_transfer_desc.h"
#include "level_zero/ze_api.h"
#include "level_zero/ze_ddi.h"

#include "shared/utils.h"

#include <cassert>
#include <cstring>
#include <optional>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

namespace Cal {
namespace Rpc {
namespace LevelZero {

template <typename Ptr>
void forcePointerWrite(Ptr& p, void* value) {
    static_assert(std::is_pointer_v<Ptr>, "forcePointerWrite() must be used with pointers!");
    using WritablePtr = std::remove_cv_t<Ptr>;

    const_cast<WritablePtr&>(p) = static_cast<WritablePtr>(value);
}

struct DynamicArgTraits {
    uint32_t offset;
    uint32_t count;
    uint32_t size;
    std::vector<DynamicArgTraits> nested;
};

template <typename DynamicStructT>
struct DynamicStructTraits {
    uint32_t offset;
    uint32_t count;
};

template <>
struct DynamicStructTraits<ze_module_constants_t> {
    int32_t pConstantIdsOffset{-1};
    int32_t pConstantIdsCount{-1};
    int32_t pConstantValuesOffset{-1};
    int32_t pConstantValuesCount{-1};
};

template <>
struct DynamicStructTraits<ze_module_desc_t> {
    int32_t pInputModuleOffset{-1};
    int32_t pInputModuleCount{-1};
    int32_t pBuildFlagsOffset{-1};
    int32_t pBuildFlagsCount{-1};
    int32_t pConstantsOffset{-1};
    int32_t pConstantsCount{-1};
};

template <>
struct DynamicStructTraits<ze_kernel_desc_t> {
    int32_t pKernelNameOffset{-1};
    int32_t pKernelNameCount{-1};
};


template<typename T>
inline char *asMemcpyDstT(T * ptr) {
    static_assert(std::is_standard_layout_v<T>);
    return reinterpret_cast<char*>(const_cast<std::remove_const_t<T>*>(ptr));
};

inline char *asMemcpyDstT(const void * ptr) {
    return reinterpret_cast<char*>(const_cast<void*>(ptr));
};

inline char *asMemcpyDstT(void * ptr) {
    return reinterpret_cast<char*>(const_cast<void*>(ptr));
};

struct ZeInitRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 0;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_init_flags_t flags = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->flags == rhs.flags;
            return equal;
        }
    }args;

    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeInitRpcM() = default;

    ZeInitRpcM(ze_init_flags_t flags) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.flags = flags;
    }
    
    static void fillWithoutCapture(ZeInitRpcM &message, ze_init_flags_t flags) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.flags = flags;
    }
    
};
static_assert(std::is_standard_layout_v<ZeInitRpcM>);
struct ZeCommandListCreateRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 1;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_context_handle_t hContext = {};
        ze_device_handle_t hDevice = {};
        const ze_command_list_desc_t* desc = {};
        ze_command_list_handle_t* phCommandList = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hContext == rhs.hContext;
            equal &= this->hDevice == rhs.hDevice;
            equal &= this->desc == rhs.desc;
            equal &= this->phCommandList == rhs.phCommandList;
            return equal;
        }
    }args;

    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        ze_command_list_desc_t desc;
        ze_command_list_handle_t phCommandList;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeCommandListCreateRpcM() = default;

    ZeCommandListCreateRpcM(ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_list_desc_t* desc, ze_command_list_handle_t* phCommandList) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hContext = hContext;
        args.hDevice = hDevice;
        args.desc = desc;
        args.phCommandList = phCommandList;
    }
    
    static void fillWithoutCapture(ZeCommandListCreateRpcM &message, ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_list_desc_t* desc, ze_command_list_handle_t* phCommandList) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hContext = hContext;
        message.args.hDevice = hDevice;
        message.args.desc = desc;
        message.args.phCommandList = phCommandList;
    }
    

    void copyFromCaller(){
        if(args.desc){
            captures.desc = *args.desc;
        }
    }

    void copyToCaller(){
        if(args.phCommandList){
            *args.phCommandList = captures.phCommandList;
        }
    }
};
static_assert(std::is_standard_layout_v<ZeCommandListCreateRpcM>);
struct ZeCommandListCreateImmediateRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 2;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_context_handle_t hContext = {};
        ze_device_handle_t hDevice = {};
        const ze_command_queue_desc_t* altdesc = {};
        ze_command_list_handle_t* phCommandList = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hContext == rhs.hContext;
            equal &= this->hDevice == rhs.hDevice;
            equal &= this->altdesc == rhs.altdesc;
            equal &= this->phCommandList == rhs.phCommandList;
            return equal;
        }
    }args;

    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        ze_command_queue_desc_t altdesc;
        ze_command_list_handle_t phCommandList;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeCommandListCreateImmediateRpcM() = default;

    ZeCommandListCreateImmediateRpcM(ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_queue_desc_t* altdesc, ze_command_list_handle_t* phCommandList) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hContext = hContext;
        args.hDevice = hDevice;
        args.altdesc = altdesc;
        args.phCommandList = phCommandList;
    }
    
    static void fillWithoutCapture(ZeCommandListCreateImmediateRpcM &message, ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_queue_desc_t* altdesc, ze_command_list_handle_t* phCommandList) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hContext = hContext;
        message.args.hDevice = hDevice;
        message.args.altdesc = altdesc;
        message.args.phCommandList = phCommandList;
    }
    

    void copyFromCaller(){
        if(args.altdesc){
            captures.altdesc = *args.altdesc;
        }
    }

    void copyToCaller(){
        if(args.phCommandList){
            *args.phCommandList = captures.phCommandList;
        }
    }
};
static_assert(std::is_standard_layout_v<ZeCommandListCreateImmediateRpcM>);
struct ZeCommandListDestroyRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 3;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_command_list_handle_t hCommandList = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hCommandList == rhs.hCommandList;
            return equal;
        }
    }args;

    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeCommandListDestroyRpcM() = default;

    ZeCommandListDestroyRpcM(ze_command_list_handle_t hCommandList) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hCommandList = hCommandList;
    }
    
    static void fillWithoutCapture(ZeCommandListDestroyRpcM &message, ze_command_list_handle_t hCommandList) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hCommandList = hCommandList;
    }
    
};
static_assert(std::is_standard_layout_v<ZeCommandListDestroyRpcM>);
struct ZeCommandListCloseRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 4;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_command_list_handle_t hCommandList = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hCommandList == rhs.hCommandList;
            return equal;
        }
    }args;

    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeCommandListCloseRpcM() = default;

    ZeCommandListCloseRpcM(ze_command_list_handle_t hCommandList) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hCommandList = hCommandList;
    }
    
    static void fillWithoutCapture(ZeCommandListCloseRpcM &message, ze_command_list_handle_t hCommandList) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hCommandList = hCommandList;
    }
    
};
static_assert(std::is_standard_layout_v<ZeCommandListCloseRpcM>);
struct ZeCommandListResetRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 5;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_command_list_handle_t hCommandList = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hCommandList == rhs.hCommandList;
            return equal;
        }
    }args;

    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeCommandListResetRpcM() = default;

    ZeCommandListResetRpcM(ze_command_list_handle_t hCommandList) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hCommandList = hCommandList;
    }
    
    static void fillWithoutCapture(ZeCommandListResetRpcM &message, ze_command_list_handle_t hCommandList) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hCommandList = hCommandList;
    }
    
};
static_assert(std::is_standard_layout_v<ZeCommandListResetRpcM>);
struct ZeCommandQueueCreateRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 6;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_context_handle_t hContext = {};
        ze_device_handle_t hDevice = {};
        const ze_command_queue_desc_t* desc = {};
        ze_command_queue_handle_t* phCommandQueue = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hContext == rhs.hContext;
            equal &= this->hDevice == rhs.hDevice;
            equal &= this->desc == rhs.desc;
            equal &= this->phCommandQueue == rhs.phCommandQueue;
            return equal;
        }
    }args;

    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        ze_command_queue_desc_t desc;
        ze_command_queue_handle_t phCommandQueue;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeCommandQueueCreateRpcM() = default;

    ZeCommandQueueCreateRpcM(ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_queue_desc_t* desc, ze_command_queue_handle_t* phCommandQueue) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hContext = hContext;
        args.hDevice = hDevice;
        args.desc = desc;
        args.phCommandQueue = phCommandQueue;
    }
    
    static void fillWithoutCapture(ZeCommandQueueCreateRpcM &message, ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_queue_desc_t* desc, ze_command_queue_handle_t* phCommandQueue) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hContext = hContext;
        message.args.hDevice = hDevice;
        message.args.desc = desc;
        message.args.phCommandQueue = phCommandQueue;
    }
    

    void copyFromCaller(){
        if(args.desc){
            captures.desc = *args.desc;
        }
    }

    void copyToCaller(){
        if(args.phCommandQueue){
            *args.phCommandQueue = captures.phCommandQueue;
        }
    }
};
static_assert(std::is_standard_layout_v<ZeCommandQueueCreateRpcM>);
struct ZeCommandQueueDestroyRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 7;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_command_queue_handle_t hCommandQueue = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hCommandQueue == rhs.hCommandQueue;
            return equal;
        }
    }args;

    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeCommandQueueDestroyRpcM() = default;

    ZeCommandQueueDestroyRpcM(ze_command_queue_handle_t hCommandQueue) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hCommandQueue = hCommandQueue;
    }
    
    static void fillWithoutCapture(ZeCommandQueueDestroyRpcM &message, ze_command_queue_handle_t hCommandQueue) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hCommandQueue = hCommandQueue;
    }
    
};
static_assert(std::is_standard_layout_v<ZeCommandQueueDestroyRpcM>);
struct ZeCommandQueueExecuteCommandListsRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 8;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_command_queue_handle_t hCommandQueue = {};
        uint32_t numCommandLists = {};
        ze_command_list_handle_t* phCommandLists = {};
        ze_fence_handle_t hFence = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hCommandQueue == rhs.hCommandQueue;
            equal &= this->numCommandLists == rhs.numCommandLists;
            equal &= this->phCommandLists == rhs.phCommandLists;
            equal &= this->hFence == rhs.hFence;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(ze_command_queue_handle_t hCommandQueue, uint32_t numCommandLists, ze_command_list_handle_t* phCommandLists, ze_fence_handle_t hFence);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits phCommandLists = {};          
        };

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        uint32_t countPhCommandLists = 0;
        ze_command_list_handle_t phCommandLists[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countPhCommandLists = dynamicTraits.phCommandLists.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeCommandQueueExecuteCommandListsRpcM() = default;

    ZeCommandQueueExecuteCommandListsRpcM(const Captures::DynamicTraits &dynamicTraits, ze_command_queue_handle_t hCommandQueue, uint32_t numCommandLists, ze_command_list_handle_t* phCommandLists, ze_fence_handle_t hFence) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hCommandQueue = hCommandQueue;
        args.numCommandLists = numCommandLists;
        args.phCommandLists = phCommandLists;
        args.hFence = hFence;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ZeCommandQueueExecuteCommandListsRpcM &message, ze_command_queue_handle_t hCommandQueue, uint32_t numCommandLists, ze_command_list_handle_t* phCommandLists, ze_fence_handle_t hFence) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hCommandQueue = hCommandQueue;
        message.args.numCommandLists = numCommandLists;
        message.args.phCommandLists = phCommandLists;
        message.args.hFence = hFence;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.phCommandLists){
            memcpy(asMemcpyDstT(captures.phCommandLists), args.phCommandLists, dynMemTraits.phCommandLists.size);
        }
    }
};
static_assert(std::is_standard_layout_v<ZeCommandQueueExecuteCommandListsRpcM>);
struct ZeCommandQueueExecuteCommandListsCopySourceMemoryRpcHelperRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 9;

    using ReturnValueT = ze_result_t;

    struct Args {
        uint32_t chunksCount = {};
        const Cal::Rpc::MemChunk* chunks = {};
        uint32_t* transferDescsCount = {};
        Cal::Rpc::ShmemTransferDesc* transferDescs = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->chunksCount == rhs.chunksCount;
            equal &= this->chunks == rhs.chunks;
            equal &= this->transferDescsCount == rhs.transferDescsCount;
            equal &= this->transferDescs == rhs.transferDescs;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(uint32_t chunksCount, const Cal::Rpc::MemChunk* chunks, uint32_t* transferDescsCount, Cal::Rpc::ShmemTransferDesc* transferDescs);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits chunks = {};          
            DynamicArgTraits transferDescs = {};          
        };

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        uint32_t transferDescsCount;
        uint32_t offsetTransferDescs = 0;
        uint32_t countChunks = 0;
        uint32_t countTransferDescs = 0;
        const Cal::Rpc::MemChunk* getChunks() {
            auto offset = 0;
            return reinterpret_cast<const Cal::Rpc::MemChunk*>(dynMem + offset);
        }

        Cal::Rpc::ShmemTransferDesc* getTransferDescs() {
            auto offset = offsetTransferDescs;
            return reinterpret_cast<Cal::Rpc::ShmemTransferDesc*>(dynMem + offset);
        }


        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        offsetTransferDescs = dynamicTraits.transferDescs.offset;
        countChunks = dynamicTraits.chunks.count;
        countTransferDescs = dynamicTraits.transferDescs.count;
        }
        
        alignas(8) char dynMem[];
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeCommandQueueExecuteCommandListsCopySourceMemoryRpcHelperRpcM() = default;

    ZeCommandQueueExecuteCommandListsCopySourceMemoryRpcHelperRpcM(const Captures::DynamicTraits &dynamicTraits, uint32_t chunksCount, const Cal::Rpc::MemChunk* chunks, uint32_t* transferDescsCount, Cal::Rpc::ShmemTransferDesc* transferDescs) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.chunksCount = chunksCount;
        args.chunks = chunks;
        args.transferDescsCount = transferDescsCount;
        args.transferDescs = transferDescs;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ZeCommandQueueExecuteCommandListsCopySourceMemoryRpcHelperRpcM &message, uint32_t chunksCount, const Cal::Rpc::MemChunk* chunks, uint32_t* transferDescsCount, Cal::Rpc::ShmemTransferDesc* transferDescs) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.chunksCount = chunksCount;
        message.args.chunks = chunks;
        message.args.transferDescsCount = transferDescsCount;
        message.args.transferDescs = transferDescs;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.chunks){
            memcpy(asMemcpyDstT(captures.getChunks()), args.chunks, dynMemTraits.chunks.size);
        }
        if(args.transferDescsCount){
            captures.transferDescsCount = *args.transferDescsCount;
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.transferDescsCount){
            *args.transferDescsCount = captures.transferDescsCount;
        }
        if(args.transferDescs){
            memcpy(args.transferDescs, captures.getTransferDescs(), dynMemTraits.transferDescs.size);
        }
    }
};
static_assert(std::is_standard_layout_v<ZeCommandQueueExecuteCommandListsCopySourceMemoryRpcHelperRpcM>);
struct ZeCommandQueueSynchronizeRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 10;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_command_queue_handle_t hCommandQueue = {};
        uint64_t timeout = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hCommandQueue == rhs.hCommandQueue;
            equal &= this->timeout == rhs.timeout;
            return equal;
        }
    }args;

    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeCommandQueueSynchronizeRpcM() = default;

    ZeCommandQueueSynchronizeRpcM(ze_command_queue_handle_t hCommandQueue, uint64_t timeout) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hCommandQueue = hCommandQueue;
        args.timeout = timeout;
    }
    
    static void fillWithoutCapture(ZeCommandQueueSynchronizeRpcM &message, ze_command_queue_handle_t hCommandQueue, uint64_t timeout) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hCommandQueue = hCommandQueue;
        message.args.timeout = timeout;
    }
    
};
static_assert(std::is_standard_layout_v<ZeCommandQueueSynchronizeRpcM>);
struct ZeContextCreateRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 11;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_driver_handle_t hDriver = {};
        const ze_context_desc_t* desc = {};
        ze_context_handle_t* phContext = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hDriver == rhs.hDriver;
            equal &= this->desc == rhs.desc;
            equal &= this->phContext == rhs.phContext;
            return equal;
        }
    }args;

    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        ze_context_desc_t desc;
        ze_context_handle_t phContext;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeContextCreateRpcM() = default;

    ZeContextCreateRpcM(ze_driver_handle_t hDriver, const ze_context_desc_t* desc, ze_context_handle_t* phContext) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hDriver = hDriver;
        args.desc = desc;
        args.phContext = phContext;
    }
    
    static void fillWithoutCapture(ZeContextCreateRpcM &message, ze_driver_handle_t hDriver, const ze_context_desc_t* desc, ze_context_handle_t* phContext) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hDriver = hDriver;
        message.args.desc = desc;
        message.args.phContext = phContext;
    }
    

    void copyFromCaller(){
        if(args.desc){
            captures.desc = *args.desc;
        }
    }

    void copyToCaller(){
        if(args.phContext){
            *args.phContext = captures.phContext;
        }
    }
};
static_assert(std::is_standard_layout_v<ZeContextCreateRpcM>);
struct ZeContextDestroyRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 12;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_context_handle_t hContext = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hContext == rhs.hContext;
            return equal;
        }
    }args;

    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeContextDestroyRpcM() = default;

    ZeContextDestroyRpcM(ze_context_handle_t hContext) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hContext = hContext;
    }
    
    static void fillWithoutCapture(ZeContextDestroyRpcM &message, ze_context_handle_t hContext) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hContext = hContext;
    }
    
};
static_assert(std::is_standard_layout_v<ZeContextDestroyRpcM>);
struct ZeContextGetStatusRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 13;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_context_handle_t hContext = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hContext == rhs.hContext;
            return equal;
        }
    }args;

    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeContextGetStatusRpcM() = default;

    ZeContextGetStatusRpcM(ze_context_handle_t hContext) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hContext = hContext;
    }
    
    static void fillWithoutCapture(ZeContextGetStatusRpcM &message, ze_context_handle_t hContext) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hContext = hContext;
    }
    
};
static_assert(std::is_standard_layout_v<ZeContextGetStatusRpcM>);
 // zeCommandListAppendMemoryCopy ignored in generator - based on dont_generate_rpc_message flag
struct ZeCommandListAppendMemoryCopyRpcHelperUsm2UsmRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 14;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_command_list_handle_t hCommandList = {};
        void* dstptr = {};
        const void* srcptr = {};
        size_t size = {};
        ze_event_handle_t hSignalEvent = {};
        uint32_t numWaitEvents = {};
        ze_event_handle_t* phWaitEvents = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hCommandList == rhs.hCommandList;
            equal &= this->dstptr == rhs.dstptr;
            equal &= this->srcptr == rhs.srcptr;
            equal &= this->size == rhs.size;
            equal &= this->hSignalEvent == rhs.hSignalEvent;
            equal &= this->numWaitEvents == rhs.numWaitEvents;
            equal &= this->phWaitEvents == rhs.phWaitEvents;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits phWaitEvents = {};          
        };

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        uint32_t countPhWaitEvents = 0;
        ze_event_handle_t phWaitEvents[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countPhWaitEvents = dynamicTraits.phWaitEvents.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeCommandListAppendMemoryCopyRpcHelperUsm2UsmRpcM() = default;

    ZeCommandListAppendMemoryCopyRpcHelperUsm2UsmRpcM(const Captures::DynamicTraits &dynamicTraits, ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hCommandList = hCommandList;
        args.dstptr = dstptr;
        args.srcptr = srcptr;
        args.size = size;
        args.hSignalEvent = hSignalEvent;
        args.numWaitEvents = numWaitEvents;
        args.phWaitEvents = phWaitEvents;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ZeCommandListAppendMemoryCopyRpcHelperUsm2UsmRpcM &message, ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hCommandList = hCommandList;
        message.args.dstptr = dstptr;
        message.args.srcptr = srcptr;
        message.args.size = size;
        message.args.hSignalEvent = hSignalEvent;
        message.args.numWaitEvents = numWaitEvents;
        message.args.phWaitEvents = phWaitEvents;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.phWaitEvents){
            memcpy(asMemcpyDstT(captures.phWaitEvents), args.phWaitEvents, dynMemTraits.phWaitEvents.size);
        }
    }
};
static_assert(std::is_standard_layout_v<ZeCommandListAppendMemoryCopyRpcHelperUsm2UsmRpcM>);
struct ZeCommandListAppendMemoryCopyRpcHelperMalloc2UsmRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 15;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_command_list_handle_t hCommandList = {};
        void* dstptr = {};
        const void* srcptr = {};
        size_t size = {};
        ze_event_handle_t hSignalEvent = {};
        uint32_t numWaitEvents = {};
        ze_event_handle_t* phWaitEvents = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hCommandList == rhs.hCommandList;
            equal &= this->dstptr == rhs.dstptr;
            equal &= this->srcptr == rhs.srcptr;
            equal &= this->size == rhs.size;
            equal &= this->hSignalEvent == rhs.hSignalEvent;
            equal &= this->numWaitEvents == rhs.numWaitEvents;
            equal &= this->phWaitEvents == rhs.phWaitEvents;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits phWaitEvents = {};          
        };

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        uint32_t countPhWaitEvents = 0;
        ze_event_handle_t phWaitEvents[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countPhWaitEvents = dynamicTraits.phWaitEvents.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeCommandListAppendMemoryCopyRpcHelperMalloc2UsmRpcM() = default;

    ZeCommandListAppendMemoryCopyRpcHelperMalloc2UsmRpcM(const Captures::DynamicTraits &dynamicTraits, ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hCommandList = hCommandList;
        args.dstptr = dstptr;
        args.srcptr = srcptr;
        args.size = size;
        args.hSignalEvent = hSignalEvent;
        args.numWaitEvents = numWaitEvents;
        args.phWaitEvents = phWaitEvents;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ZeCommandListAppendMemoryCopyRpcHelperMalloc2UsmRpcM &message, ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hCommandList = hCommandList;
        message.args.dstptr = dstptr;
        message.args.srcptr = srcptr;
        message.args.size = size;
        message.args.hSignalEvent = hSignalEvent;
        message.args.numWaitEvents = numWaitEvents;
        message.args.phWaitEvents = phWaitEvents;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.phWaitEvents){
            memcpy(asMemcpyDstT(captures.phWaitEvents), args.phWaitEvents, dynMemTraits.phWaitEvents.size);
        }
    }
};
static_assert(std::is_standard_layout_v<ZeCommandListAppendMemoryCopyRpcHelperMalloc2UsmRpcM>);
 // zeCommandListAppendMemoryFill ignored in generator - based on dont_generate_rpc_message flag
struct ZeCommandListAppendMemoryFillRpcHelperUsm2UsmRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 16;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_command_list_handle_t hCommandList = {};
        void* ptr = {};
        const void* pattern = {};
        size_t pattern_size = {};
        size_t size = {};
        ze_event_handle_t hSignalEvent = {};
        uint32_t numWaitEvents = {};
        ze_event_handle_t* phWaitEvents = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hCommandList == rhs.hCommandList;
            equal &= this->ptr == rhs.ptr;
            equal &= this->pattern == rhs.pattern;
            equal &= this->pattern_size == rhs.pattern_size;
            equal &= this->size == rhs.size;
            equal &= this->hSignalEvent == rhs.hSignalEvent;
            equal &= this->numWaitEvents == rhs.numWaitEvents;
            equal &= this->phWaitEvents == rhs.phWaitEvents;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(ze_command_list_handle_t hCommandList, void* ptr, const void* pattern, size_t pattern_size, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits phWaitEvents = {};          
        };

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        uint32_t countPhWaitEvents = 0;
        ze_event_handle_t phWaitEvents[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countPhWaitEvents = dynamicTraits.phWaitEvents.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeCommandListAppendMemoryFillRpcHelperUsm2UsmRpcM() = default;

    ZeCommandListAppendMemoryFillRpcHelperUsm2UsmRpcM(const Captures::DynamicTraits &dynamicTraits, ze_command_list_handle_t hCommandList, void* ptr, const void* pattern, size_t pattern_size, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hCommandList = hCommandList;
        args.ptr = ptr;
        args.pattern = pattern;
        args.pattern_size = pattern_size;
        args.size = size;
        args.hSignalEvent = hSignalEvent;
        args.numWaitEvents = numWaitEvents;
        args.phWaitEvents = phWaitEvents;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ZeCommandListAppendMemoryFillRpcHelperUsm2UsmRpcM &message, ze_command_list_handle_t hCommandList, void* ptr, const void* pattern, size_t pattern_size, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hCommandList = hCommandList;
        message.args.ptr = ptr;
        message.args.pattern = pattern;
        message.args.pattern_size = pattern_size;
        message.args.size = size;
        message.args.hSignalEvent = hSignalEvent;
        message.args.numWaitEvents = numWaitEvents;
        message.args.phWaitEvents = phWaitEvents;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.phWaitEvents){
            memcpy(asMemcpyDstT(captures.phWaitEvents), args.phWaitEvents, dynMemTraits.phWaitEvents.size);
        }
    }
};
static_assert(std::is_standard_layout_v<ZeCommandListAppendMemoryFillRpcHelperUsm2UsmRpcM>);
struct ZeCommandListAppendMemoryFillRpcHelperMalloc2UsmRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 17;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_command_list_handle_t hCommandList = {};
        void* ptr = {};
        const void* pattern = {};
        size_t pattern_size = {};
        size_t size = {};
        ze_event_handle_t hSignalEvent = {};
        uint32_t numWaitEvents = {};
        ze_event_handle_t* phWaitEvents = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hCommandList == rhs.hCommandList;
            equal &= this->ptr == rhs.ptr;
            equal &= this->pattern == rhs.pattern;
            equal &= this->pattern_size == rhs.pattern_size;
            equal &= this->size == rhs.size;
            equal &= this->hSignalEvent == rhs.hSignalEvent;
            equal &= this->numWaitEvents == rhs.numWaitEvents;
            equal &= this->phWaitEvents == rhs.phWaitEvents;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(ze_command_list_handle_t hCommandList, void* ptr, const void* pattern, size_t pattern_size, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits pattern = {};          
            DynamicArgTraits phWaitEvents = {};          
        };

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        uint32_t offsetPhWaitEvents = 0;
        uint32_t countPattern = 0;
        uint32_t countPhWaitEvents = 0;
        const void* getPattern() {
            auto offset = 0;
            return reinterpret_cast<const void*>(dynMem + offset);
        }

        ze_event_handle_t* getPhWaitEvents() {
            auto offset = offsetPhWaitEvents;
            return reinterpret_cast<ze_event_handle_t*>(dynMem + offset);
        }


        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        offsetPhWaitEvents = dynamicTraits.phWaitEvents.offset;
        countPattern = dynamicTraits.pattern.count;
        countPhWaitEvents = dynamicTraits.phWaitEvents.count;
        }
        
        alignas(8) char dynMem[];
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeCommandListAppendMemoryFillRpcHelperMalloc2UsmRpcM() = default;

    ZeCommandListAppendMemoryFillRpcHelperMalloc2UsmRpcM(const Captures::DynamicTraits &dynamicTraits, ze_command_list_handle_t hCommandList, void* ptr, const void* pattern, size_t pattern_size, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hCommandList = hCommandList;
        args.ptr = ptr;
        args.pattern = pattern;
        args.pattern_size = pattern_size;
        args.size = size;
        args.hSignalEvent = hSignalEvent;
        args.numWaitEvents = numWaitEvents;
        args.phWaitEvents = phWaitEvents;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ZeCommandListAppendMemoryFillRpcHelperMalloc2UsmRpcM &message, ze_command_list_handle_t hCommandList, void* ptr, const void* pattern, size_t pattern_size, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hCommandList = hCommandList;
        message.args.ptr = ptr;
        message.args.pattern = pattern;
        message.args.pattern_size = pattern_size;
        message.args.size = size;
        message.args.hSignalEvent = hSignalEvent;
        message.args.numWaitEvents = numWaitEvents;
        message.args.phWaitEvents = phWaitEvents;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.pattern){
            memcpy(asMemcpyDstT(captures.getPattern()), args.pattern, dynMemTraits.pattern.size);
        }
        if(args.phWaitEvents){
            memcpy(asMemcpyDstT(captures.getPhWaitEvents()), args.phWaitEvents, dynMemTraits.phWaitEvents.size);
        }
    }
};
static_assert(std::is_standard_layout_v<ZeCommandListAppendMemoryFillRpcHelperMalloc2UsmRpcM>);
struct ZeDeviceGetRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 18;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_driver_handle_t hDriver = {};
        uint32_t* pCount = {};
        ze_device_handle_t* phDevices = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hDriver == rhs.hDriver;
            equal &= this->pCount == rhs.pCount;
            equal &= this->phDevices == rhs.phDevices;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(ze_driver_handle_t hDriver, uint32_t* pCount, ze_device_handle_t* phDevices);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits phDevices = {};          
        };

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        uint32_t pCount;
        uint32_t countPhDevices = 0;
        ze_device_handle_t phDevices[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countPhDevices = dynamicTraits.phDevices.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeDeviceGetRpcM() = default;

    ZeDeviceGetRpcM(const Captures::DynamicTraits &dynamicTraits, ze_driver_handle_t hDriver, uint32_t* pCount, ze_device_handle_t* phDevices) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hDriver = hDriver;
        args.pCount = pCount;
        args.phDevices = phDevices;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ZeDeviceGetRpcM &message, ze_driver_handle_t hDriver, uint32_t* pCount, ze_device_handle_t* phDevices) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hDriver = hDriver;
        message.args.pCount = pCount;
        message.args.phDevices = phDevices;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.pCount){
            captures.pCount = *args.pCount;
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.pCount){
            *args.pCount = captures.pCount;
        }
        if(args.phDevices){
            memcpy(args.phDevices, captures.phDevices, dynMemTraits.phDevices.size);
        }
    }
};
static_assert(std::is_standard_layout_v<ZeDeviceGetRpcM>);
struct ZeDeviceGetSubDevicesRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 19;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_device_handle_t hDevice = {};
        uint32_t* pCount = {};
        ze_device_handle_t* phSubdevices = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hDevice == rhs.hDevice;
            equal &= this->pCount == rhs.pCount;
            equal &= this->phSubdevices == rhs.phSubdevices;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(ze_device_handle_t hDevice, uint32_t* pCount, ze_device_handle_t* phSubdevices);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits phSubdevices = {};          
        };

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        uint32_t pCount;
        uint32_t countPhSubdevices = 0;
        ze_device_handle_t phSubdevices[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countPhSubdevices = dynamicTraits.phSubdevices.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeDeviceGetSubDevicesRpcM() = default;

    ZeDeviceGetSubDevicesRpcM(const Captures::DynamicTraits &dynamicTraits, ze_device_handle_t hDevice, uint32_t* pCount, ze_device_handle_t* phSubdevices) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hDevice = hDevice;
        args.pCount = pCount;
        args.phSubdevices = phSubdevices;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ZeDeviceGetSubDevicesRpcM &message, ze_device_handle_t hDevice, uint32_t* pCount, ze_device_handle_t* phSubdevices) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hDevice = hDevice;
        message.args.pCount = pCount;
        message.args.phSubdevices = phSubdevices;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.pCount){
            captures.pCount = *args.pCount;
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.pCount){
            *args.pCount = captures.pCount;
        }
        if(args.phSubdevices){
            memcpy(args.phSubdevices, captures.phSubdevices, dynMemTraits.phSubdevices.size);
        }
    }
};
static_assert(std::is_standard_layout_v<ZeDeviceGetSubDevicesRpcM>);
struct ZeDeviceGetPropertiesRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 20;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_device_handle_t hDevice = {};
        ze_device_properties_t* pDeviceProperties = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hDevice == rhs.hDevice;
            equal &= this->pDeviceProperties == rhs.pDeviceProperties;
            return equal;
        }
    }args;

    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        ze_device_properties_t pDeviceProperties;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeDeviceGetPropertiesRpcM() = default;

    ZeDeviceGetPropertiesRpcM(ze_device_handle_t hDevice, ze_device_properties_t* pDeviceProperties) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hDevice = hDevice;
        args.pDeviceProperties = pDeviceProperties;
    }
    
    static void fillWithoutCapture(ZeDeviceGetPropertiesRpcM &message, ze_device_handle_t hDevice, ze_device_properties_t* pDeviceProperties) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hDevice = hDevice;
        message.args.pDeviceProperties = pDeviceProperties;
    }
    

    void copyToCaller(){
        if(args.pDeviceProperties){
            *args.pDeviceProperties = captures.pDeviceProperties;
        }
    }
};
static_assert(std::is_standard_layout_v<ZeDeviceGetPropertiesRpcM>);
struct ZeDeviceGetComputePropertiesRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 21;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_device_handle_t hDevice = {};
        ze_device_compute_properties_t* pComputeProperties = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hDevice == rhs.hDevice;
            equal &= this->pComputeProperties == rhs.pComputeProperties;
            return equal;
        }
    }args;

    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        ze_device_compute_properties_t pComputeProperties;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeDeviceGetComputePropertiesRpcM() = default;

    ZeDeviceGetComputePropertiesRpcM(ze_device_handle_t hDevice, ze_device_compute_properties_t* pComputeProperties) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hDevice = hDevice;
        args.pComputeProperties = pComputeProperties;
    }
    
    static void fillWithoutCapture(ZeDeviceGetComputePropertiesRpcM &message, ze_device_handle_t hDevice, ze_device_compute_properties_t* pComputeProperties) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hDevice = hDevice;
        message.args.pComputeProperties = pComputeProperties;
    }
    

    void copyToCaller(){
        if(args.pComputeProperties){
            *args.pComputeProperties = captures.pComputeProperties;
        }
    }
};
static_assert(std::is_standard_layout_v<ZeDeviceGetComputePropertiesRpcM>);
struct ZeDeviceGetModulePropertiesRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 22;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_device_handle_t hDevice = {};
        ze_device_module_properties_t* pModuleProperties = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hDevice == rhs.hDevice;
            equal &= this->pModuleProperties == rhs.pModuleProperties;
            return equal;
        }
    }args;

    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        ze_device_module_properties_t pModuleProperties;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeDeviceGetModulePropertiesRpcM() = default;

    ZeDeviceGetModulePropertiesRpcM(ze_device_handle_t hDevice, ze_device_module_properties_t* pModuleProperties) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hDevice = hDevice;
        args.pModuleProperties = pModuleProperties;
    }
    
    static void fillWithoutCapture(ZeDeviceGetModulePropertiesRpcM &message, ze_device_handle_t hDevice, ze_device_module_properties_t* pModuleProperties) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hDevice = hDevice;
        message.args.pModuleProperties = pModuleProperties;
    }
    

    void copyToCaller(){
        if(args.pModuleProperties){
            *args.pModuleProperties = captures.pModuleProperties;
        }
    }
};
static_assert(std::is_standard_layout_v<ZeDeviceGetModulePropertiesRpcM>);
struct ZeDeviceGetCommandQueueGroupPropertiesRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 23;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_device_handle_t hDevice = {};
        uint32_t* pCount = {};
        ze_command_queue_group_properties_t* pCommandQueueGroupProperties = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hDevice == rhs.hDevice;
            equal &= this->pCount == rhs.pCount;
            equal &= this->pCommandQueueGroupProperties == rhs.pCommandQueueGroupProperties;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(ze_device_handle_t hDevice, uint32_t* pCount, ze_command_queue_group_properties_t* pCommandQueueGroupProperties);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits pCommandQueueGroupProperties = {};          
        };

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        uint32_t pCount;
        uint32_t countPCommandQueueGroupProperties = 0;
        ze_command_queue_group_properties_t pCommandQueueGroupProperties[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countPCommandQueueGroupProperties = dynamicTraits.pCommandQueueGroupProperties.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeDeviceGetCommandQueueGroupPropertiesRpcM() = default;

    ZeDeviceGetCommandQueueGroupPropertiesRpcM(const Captures::DynamicTraits &dynamicTraits, ze_device_handle_t hDevice, uint32_t* pCount, ze_command_queue_group_properties_t* pCommandQueueGroupProperties) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hDevice = hDevice;
        args.pCount = pCount;
        args.pCommandQueueGroupProperties = pCommandQueueGroupProperties;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ZeDeviceGetCommandQueueGroupPropertiesRpcM &message, ze_device_handle_t hDevice, uint32_t* pCount, ze_command_queue_group_properties_t* pCommandQueueGroupProperties) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hDevice = hDevice;
        message.args.pCount = pCount;
        message.args.pCommandQueueGroupProperties = pCommandQueueGroupProperties;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.pCount){
            captures.pCount = *args.pCount;
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.pCount){
            *args.pCount = captures.pCount;
        }
        if(args.pCommandQueueGroupProperties){
            memcpy(args.pCommandQueueGroupProperties, captures.pCommandQueueGroupProperties, dynMemTraits.pCommandQueueGroupProperties.size);
        }
    }
};
static_assert(std::is_standard_layout_v<ZeDeviceGetCommandQueueGroupPropertiesRpcM>);
struct ZeDeviceGetMemoryPropertiesRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 24;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_device_handle_t hDevice = {};
        uint32_t* pCount = {};
        ze_device_memory_properties_t* pMemProperties = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hDevice == rhs.hDevice;
            equal &= this->pCount == rhs.pCount;
            equal &= this->pMemProperties == rhs.pMemProperties;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(ze_device_handle_t hDevice, uint32_t* pCount, ze_device_memory_properties_t* pMemProperties);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits pMemProperties = {};          
        };

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        uint32_t pCount;
        uint32_t countPMemProperties = 0;
        ze_device_memory_properties_t pMemProperties[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countPMemProperties = dynamicTraits.pMemProperties.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeDeviceGetMemoryPropertiesRpcM() = default;

    ZeDeviceGetMemoryPropertiesRpcM(const Captures::DynamicTraits &dynamicTraits, ze_device_handle_t hDevice, uint32_t* pCount, ze_device_memory_properties_t* pMemProperties) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hDevice = hDevice;
        args.pCount = pCount;
        args.pMemProperties = pMemProperties;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ZeDeviceGetMemoryPropertiesRpcM &message, ze_device_handle_t hDevice, uint32_t* pCount, ze_device_memory_properties_t* pMemProperties) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hDevice = hDevice;
        message.args.pCount = pCount;
        message.args.pMemProperties = pMemProperties;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.pCount){
            captures.pCount = *args.pCount;
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.pCount){
            *args.pCount = captures.pCount;
        }
        if(args.pMemProperties){
            memcpy(args.pMemProperties, captures.pMemProperties, dynMemTraits.pMemProperties.size);
        }
    }
};
static_assert(std::is_standard_layout_v<ZeDeviceGetMemoryPropertiesRpcM>);
struct ZeDeviceGetMemoryAccessPropertiesRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 25;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_device_handle_t hDevice = {};
        ze_device_memory_access_properties_t* pMemAccessProperties = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hDevice == rhs.hDevice;
            equal &= this->pMemAccessProperties == rhs.pMemAccessProperties;
            return equal;
        }
    }args;

    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        ze_device_memory_access_properties_t pMemAccessProperties;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeDeviceGetMemoryAccessPropertiesRpcM() = default;

    ZeDeviceGetMemoryAccessPropertiesRpcM(ze_device_handle_t hDevice, ze_device_memory_access_properties_t* pMemAccessProperties) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hDevice = hDevice;
        args.pMemAccessProperties = pMemAccessProperties;
    }
    
    static void fillWithoutCapture(ZeDeviceGetMemoryAccessPropertiesRpcM &message, ze_device_handle_t hDevice, ze_device_memory_access_properties_t* pMemAccessProperties) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hDevice = hDevice;
        message.args.pMemAccessProperties = pMemAccessProperties;
    }
    

    void copyToCaller(){
        if(args.pMemAccessProperties){
            *args.pMemAccessProperties = captures.pMemAccessProperties;
        }
    }
};
static_assert(std::is_standard_layout_v<ZeDeviceGetMemoryAccessPropertiesRpcM>);
struct ZeDeviceGetCachePropertiesRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 26;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_device_handle_t hDevice = {};
        uint32_t* pCount = {};
        ze_device_cache_properties_t* pCacheProperties = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hDevice == rhs.hDevice;
            equal &= this->pCount == rhs.pCount;
            equal &= this->pCacheProperties == rhs.pCacheProperties;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(ze_device_handle_t hDevice, uint32_t* pCount, ze_device_cache_properties_t* pCacheProperties);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits pCacheProperties = {};          
        };

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        uint32_t pCount;
        uint32_t countPCacheProperties = 0;
        ze_device_cache_properties_t pCacheProperties[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countPCacheProperties = dynamicTraits.pCacheProperties.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeDeviceGetCachePropertiesRpcM() = default;

    ZeDeviceGetCachePropertiesRpcM(const Captures::DynamicTraits &dynamicTraits, ze_device_handle_t hDevice, uint32_t* pCount, ze_device_cache_properties_t* pCacheProperties) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hDevice = hDevice;
        args.pCount = pCount;
        args.pCacheProperties = pCacheProperties;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ZeDeviceGetCachePropertiesRpcM &message, ze_device_handle_t hDevice, uint32_t* pCount, ze_device_cache_properties_t* pCacheProperties) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hDevice = hDevice;
        message.args.pCount = pCount;
        message.args.pCacheProperties = pCacheProperties;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.pCount){
            captures.pCount = *args.pCount;
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.pCount){
            *args.pCount = captures.pCount;
        }
        if(args.pCacheProperties){
            memcpy(args.pCacheProperties, captures.pCacheProperties, dynMemTraits.pCacheProperties.size);
        }
    }
};
static_assert(std::is_standard_layout_v<ZeDeviceGetCachePropertiesRpcM>);
struct ZeDeviceGetImagePropertiesRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 27;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_device_handle_t hDevice = {};
        ze_device_image_properties_t* pImageProperties = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hDevice == rhs.hDevice;
            equal &= this->pImageProperties == rhs.pImageProperties;
            return equal;
        }
    }args;

    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        ze_device_image_properties_t pImageProperties;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeDeviceGetImagePropertiesRpcM() = default;

    ZeDeviceGetImagePropertiesRpcM(ze_device_handle_t hDevice, ze_device_image_properties_t* pImageProperties) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hDevice = hDevice;
        args.pImageProperties = pImageProperties;
    }
    
    static void fillWithoutCapture(ZeDeviceGetImagePropertiesRpcM &message, ze_device_handle_t hDevice, ze_device_image_properties_t* pImageProperties) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hDevice = hDevice;
        message.args.pImageProperties = pImageProperties;
    }
    

    void copyToCaller(){
        if(args.pImageProperties){
            *args.pImageProperties = captures.pImageProperties;
        }
    }
};
static_assert(std::is_standard_layout_v<ZeDeviceGetImagePropertiesRpcM>);
struct ZeDeviceGetExternalMemoryPropertiesRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 28;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_device_handle_t hDevice = {};
        ze_device_external_memory_properties_t* pExternalMemoryProperties = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hDevice == rhs.hDevice;
            equal &= this->pExternalMemoryProperties == rhs.pExternalMemoryProperties;
            return equal;
        }
    }args;

    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        ze_device_external_memory_properties_t pExternalMemoryProperties;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeDeviceGetExternalMemoryPropertiesRpcM() = default;

    ZeDeviceGetExternalMemoryPropertiesRpcM(ze_device_handle_t hDevice, ze_device_external_memory_properties_t* pExternalMemoryProperties) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hDevice = hDevice;
        args.pExternalMemoryProperties = pExternalMemoryProperties;
    }
    
    static void fillWithoutCapture(ZeDeviceGetExternalMemoryPropertiesRpcM &message, ze_device_handle_t hDevice, ze_device_external_memory_properties_t* pExternalMemoryProperties) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hDevice = hDevice;
        message.args.pExternalMemoryProperties = pExternalMemoryProperties;
    }
    

    void copyToCaller(){
        if(args.pExternalMemoryProperties){
            *args.pExternalMemoryProperties = captures.pExternalMemoryProperties;
        }
    }
};
static_assert(std::is_standard_layout_v<ZeDeviceGetExternalMemoryPropertiesRpcM>);
struct ZeDeviceCanAccessPeerRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 29;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_device_handle_t hDevice = {};
        ze_device_handle_t hPeerDevice = {};
        ze_bool_t* value = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hDevice == rhs.hDevice;
            equal &= this->hPeerDevice == rhs.hPeerDevice;
            equal &= this->value == rhs.value;
            return equal;
        }
    }args;

    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        ze_bool_t value;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeDeviceCanAccessPeerRpcM() = default;

    ZeDeviceCanAccessPeerRpcM(ze_device_handle_t hDevice, ze_device_handle_t hPeerDevice, ze_bool_t* value) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hDevice = hDevice;
        args.hPeerDevice = hPeerDevice;
        args.value = value;
    }
    
    static void fillWithoutCapture(ZeDeviceCanAccessPeerRpcM &message, ze_device_handle_t hDevice, ze_device_handle_t hPeerDevice, ze_bool_t* value) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hDevice = hDevice;
        message.args.hPeerDevice = hPeerDevice;
        message.args.value = value;
    }
    

    void copyToCaller(){
        if(args.value){
            *args.value = captures.value;
        }
    }
};
static_assert(std::is_standard_layout_v<ZeDeviceCanAccessPeerRpcM>);
struct ZeDeviceGetStatusRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 30;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_device_handle_t hDevice = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hDevice == rhs.hDevice;
            return equal;
        }
    }args;

    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeDeviceGetStatusRpcM() = default;

    ZeDeviceGetStatusRpcM(ze_device_handle_t hDevice) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hDevice = hDevice;
    }
    
    static void fillWithoutCapture(ZeDeviceGetStatusRpcM &message, ze_device_handle_t hDevice) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hDevice = hDevice;
    }
    
};
static_assert(std::is_standard_layout_v<ZeDeviceGetStatusRpcM>);
struct ZeDeviceGetGlobalTimestampsRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 31;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_device_handle_t hDevice = {};
        uint64_t* hostTimestamp = {};
        uint64_t* deviceTimestamp = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hDevice == rhs.hDevice;
            equal &= this->hostTimestamp == rhs.hostTimestamp;
            equal &= this->deviceTimestamp == rhs.deviceTimestamp;
            return equal;
        }
    }args;

    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        uint64_t hostTimestamp;
        uint64_t deviceTimestamp;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeDeviceGetGlobalTimestampsRpcM() = default;

    ZeDeviceGetGlobalTimestampsRpcM(ze_device_handle_t hDevice, uint64_t* hostTimestamp, uint64_t* deviceTimestamp) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hDevice = hDevice;
        args.hostTimestamp = hostTimestamp;
        args.deviceTimestamp = deviceTimestamp;
    }
    
    static void fillWithoutCapture(ZeDeviceGetGlobalTimestampsRpcM &message, ze_device_handle_t hDevice, uint64_t* hostTimestamp, uint64_t* deviceTimestamp) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hDevice = hDevice;
        message.args.hostTimestamp = hostTimestamp;
        message.args.deviceTimestamp = deviceTimestamp;
    }
    

    void copyToCaller(){
        if(args.hostTimestamp){
            *args.hostTimestamp = captures.hostTimestamp;
        }
        if(args.deviceTimestamp){
            *args.deviceTimestamp = captures.deviceTimestamp;
        }
    }
};
static_assert(std::is_standard_layout_v<ZeDeviceGetGlobalTimestampsRpcM>);
struct ZeDriverGetRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 32;

    using ReturnValueT = ze_result_t;

    struct Args {
        uint32_t* pCount = {};
        ze_driver_handle_t* phDrivers = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->pCount == rhs.pCount;
            equal &= this->phDrivers == rhs.phDrivers;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(uint32_t* pCount, ze_driver_handle_t* phDrivers);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits phDrivers = {};          
        };

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        uint32_t pCount;
        uint32_t countPhDrivers = 0;
        ze_driver_handle_t phDrivers[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countPhDrivers = dynamicTraits.phDrivers.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeDriverGetRpcM() = default;

    ZeDriverGetRpcM(const Captures::DynamicTraits &dynamicTraits, uint32_t* pCount, ze_driver_handle_t* phDrivers) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.pCount = pCount;
        args.phDrivers = phDrivers;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ZeDriverGetRpcM &message, uint32_t* pCount, ze_driver_handle_t* phDrivers) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.pCount = pCount;
        message.args.phDrivers = phDrivers;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.pCount){
            captures.pCount = *args.pCount;
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.pCount){
            *args.pCount = captures.pCount;
        }
        if(args.phDrivers){
            memcpy(args.phDrivers, captures.phDrivers, dynMemTraits.phDrivers.size);
        }
    }
};
static_assert(std::is_standard_layout_v<ZeDriverGetRpcM>);
struct ZeDriverGetApiVersionRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 33;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_driver_handle_t hDriver = {};
        ze_api_version_t* version = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hDriver == rhs.hDriver;
            equal &= this->version == rhs.version;
            return equal;
        }
    }args;

    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        ze_api_version_t version;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeDriverGetApiVersionRpcM() = default;

    ZeDriverGetApiVersionRpcM(ze_driver_handle_t hDriver, ze_api_version_t* version) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hDriver = hDriver;
        args.version = version;
    }
    
    static void fillWithoutCapture(ZeDriverGetApiVersionRpcM &message, ze_driver_handle_t hDriver, ze_api_version_t* version) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hDriver = hDriver;
        message.args.version = version;
    }
    

    void copyToCaller(){
        if(args.version){
            *args.version = captures.version;
        }
    }
};
static_assert(std::is_standard_layout_v<ZeDriverGetApiVersionRpcM>);
struct ZeDriverGetPropertiesRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 34;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_driver_handle_t hDriver = {};
        ze_driver_properties_t* pDriverProperties = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hDriver == rhs.hDriver;
            equal &= this->pDriverProperties == rhs.pDriverProperties;
            return equal;
        }
    }args;

    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        ze_driver_properties_t pDriverProperties;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeDriverGetPropertiesRpcM() = default;

    ZeDriverGetPropertiesRpcM(ze_driver_handle_t hDriver, ze_driver_properties_t* pDriverProperties) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hDriver = hDriver;
        args.pDriverProperties = pDriverProperties;
    }
    
    static void fillWithoutCapture(ZeDriverGetPropertiesRpcM &message, ze_driver_handle_t hDriver, ze_driver_properties_t* pDriverProperties) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hDriver = hDriver;
        message.args.pDriverProperties = pDriverProperties;
    }
    

    void copyToCaller(){
        if(args.pDriverProperties){
            *args.pDriverProperties = captures.pDriverProperties;
        }
    }
};
static_assert(std::is_standard_layout_v<ZeDriverGetPropertiesRpcM>);
struct ZeDriverGetIpcPropertiesRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 35;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_driver_handle_t hDriver = {};
        ze_driver_ipc_properties_t* pIpcProperties = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hDriver == rhs.hDriver;
            equal &= this->pIpcProperties == rhs.pIpcProperties;
            return equal;
        }
    }args;

    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        ze_driver_ipc_properties_t pIpcProperties;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeDriverGetIpcPropertiesRpcM() = default;

    ZeDriverGetIpcPropertiesRpcM(ze_driver_handle_t hDriver, ze_driver_ipc_properties_t* pIpcProperties) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hDriver = hDriver;
        args.pIpcProperties = pIpcProperties;
    }
    
    static void fillWithoutCapture(ZeDriverGetIpcPropertiesRpcM &message, ze_driver_handle_t hDriver, ze_driver_ipc_properties_t* pIpcProperties) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hDriver = hDriver;
        message.args.pIpcProperties = pIpcProperties;
    }
    

    void copyToCaller(){
        if(args.pIpcProperties){
            *args.pIpcProperties = captures.pIpcProperties;
        }
    }
};
static_assert(std::is_standard_layout_v<ZeDriverGetIpcPropertiesRpcM>);
struct ZeDriverGetExtensionPropertiesRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 36;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_driver_handle_t hDriver = {};
        uint32_t* pCount = {};
        ze_driver_extension_properties_t* pExtensionProperties = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hDriver == rhs.hDriver;
            equal &= this->pCount == rhs.pCount;
            equal &= this->pExtensionProperties == rhs.pExtensionProperties;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(ze_driver_handle_t hDriver, uint32_t* pCount, ze_driver_extension_properties_t* pExtensionProperties);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits pExtensionProperties = {};          
        };

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        uint32_t pCount;
        uint32_t countPExtensionProperties = 0;
        ze_driver_extension_properties_t pExtensionProperties[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countPExtensionProperties = dynamicTraits.pExtensionProperties.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeDriverGetExtensionPropertiesRpcM() = default;

    ZeDriverGetExtensionPropertiesRpcM(const Captures::DynamicTraits &dynamicTraits, ze_driver_handle_t hDriver, uint32_t* pCount, ze_driver_extension_properties_t* pExtensionProperties) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hDriver = hDriver;
        args.pCount = pCount;
        args.pExtensionProperties = pExtensionProperties;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ZeDriverGetExtensionPropertiesRpcM &message, ze_driver_handle_t hDriver, uint32_t* pCount, ze_driver_extension_properties_t* pExtensionProperties) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hDriver = hDriver;
        message.args.pCount = pCount;
        message.args.pExtensionProperties = pExtensionProperties;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.pCount){
            captures.pCount = *args.pCount;
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.pCount){
            *args.pCount = captures.pCount;
        }
        if(args.pExtensionProperties){
            memcpy(args.pExtensionProperties, captures.pExtensionProperties, dynMemTraits.pExtensionProperties.size);
        }
    }
};
static_assert(std::is_standard_layout_v<ZeDriverGetExtensionPropertiesRpcM>);
 // zeDriverGetExtensionFunctionAddress ignored in generator - based on dont_generate_rpc_message flag
struct ZeEventPoolCreateRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 37;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_context_handle_t hContext = {};
        const ze_event_pool_desc_t* desc = {};
        uint32_t numDevices = {};
        ze_device_handle_t* phDevices = {};
        ze_event_pool_handle_t* phEventPool = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hContext == rhs.hContext;
            equal &= this->desc == rhs.desc;
            equal &= this->numDevices == rhs.numDevices;
            equal &= this->phDevices == rhs.phDevices;
            equal &= this->phEventPool == rhs.phEventPool;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(ze_context_handle_t hContext, const ze_event_pool_desc_t* desc, uint32_t numDevices, ze_device_handle_t* phDevices, ze_event_pool_handle_t* phEventPool);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits phDevices = {};          
        };

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        ze_event_pool_desc_t desc;
        ze_event_pool_handle_t phEventPool;
        uint32_t countPhDevices = 0;
        ze_device_handle_t phDevices[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countPhDevices = dynamicTraits.phDevices.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeEventPoolCreateRpcM() = default;

    ZeEventPoolCreateRpcM(const Captures::DynamicTraits &dynamicTraits, ze_context_handle_t hContext, const ze_event_pool_desc_t* desc, uint32_t numDevices, ze_device_handle_t* phDevices, ze_event_pool_handle_t* phEventPool) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hContext = hContext;
        args.desc = desc;
        args.numDevices = numDevices;
        args.phDevices = phDevices;
        args.phEventPool = phEventPool;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ZeEventPoolCreateRpcM &message, ze_context_handle_t hContext, const ze_event_pool_desc_t* desc, uint32_t numDevices, ze_device_handle_t* phDevices, ze_event_pool_handle_t* phEventPool) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hContext = hContext;
        message.args.desc = desc;
        message.args.numDevices = numDevices;
        message.args.phDevices = phDevices;
        message.args.phEventPool = phEventPool;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.desc){
            captures.desc = *args.desc;
        }
        if(args.phDevices){
            memcpy(asMemcpyDstT(captures.phDevices), args.phDevices, dynMemTraits.phDevices.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.phEventPool){
            *args.phEventPool = captures.phEventPool;
        }
    }
};
static_assert(std::is_standard_layout_v<ZeEventPoolCreateRpcM>);
struct ZeEventPoolDestroyRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 38;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_event_pool_handle_t hEventPool = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hEventPool == rhs.hEventPool;
            return equal;
        }
    }args;

    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeEventPoolDestroyRpcM() = default;

    ZeEventPoolDestroyRpcM(ze_event_pool_handle_t hEventPool) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hEventPool = hEventPool;
    }
    
    static void fillWithoutCapture(ZeEventPoolDestroyRpcM &message, ze_event_pool_handle_t hEventPool) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hEventPool = hEventPool;
    }
    
};
static_assert(std::is_standard_layout_v<ZeEventPoolDestroyRpcM>);
struct ZeEventCreateRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 39;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_event_pool_handle_t hEventPool = {};
        const ze_event_desc_t* desc = {};
        ze_event_handle_t* phEvent = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hEventPool == rhs.hEventPool;
            equal &= this->desc == rhs.desc;
            equal &= this->phEvent == rhs.phEvent;
            return equal;
        }
    }args;

    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        ze_event_desc_t desc;
        ze_event_handle_t phEvent;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeEventCreateRpcM() = default;

    ZeEventCreateRpcM(ze_event_pool_handle_t hEventPool, const ze_event_desc_t* desc, ze_event_handle_t* phEvent) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hEventPool = hEventPool;
        args.desc = desc;
        args.phEvent = phEvent;
    }
    
    static void fillWithoutCapture(ZeEventCreateRpcM &message, ze_event_pool_handle_t hEventPool, const ze_event_desc_t* desc, ze_event_handle_t* phEvent) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hEventPool = hEventPool;
        message.args.desc = desc;
        message.args.phEvent = phEvent;
    }
    

    void copyFromCaller(){
        if(args.desc){
            captures.desc = *args.desc;
        }
    }

    void copyToCaller(){
        if(args.phEvent){
            *args.phEvent = captures.phEvent;
        }
    }
};
static_assert(std::is_standard_layout_v<ZeEventCreateRpcM>);
struct ZeEventDestroyRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 40;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_event_handle_t hEvent = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hEvent == rhs.hEvent;
            return equal;
        }
    }args;

    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeEventDestroyRpcM() = default;

    ZeEventDestroyRpcM(ze_event_handle_t hEvent) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hEvent = hEvent;
    }
    
    static void fillWithoutCapture(ZeEventDestroyRpcM &message, ze_event_handle_t hEvent) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hEvent = hEvent;
    }
    
};
static_assert(std::is_standard_layout_v<ZeEventDestroyRpcM>);
struct ZeCommandListAppendSignalEventRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 41;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_command_list_handle_t hCommandList = {};
        ze_event_handle_t hEvent = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hCommandList == rhs.hCommandList;
            equal &= this->hEvent == rhs.hEvent;
            return equal;
        }
    }args;

    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeCommandListAppendSignalEventRpcM() = default;

    ZeCommandListAppendSignalEventRpcM(ze_command_list_handle_t hCommandList, ze_event_handle_t hEvent) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hCommandList = hCommandList;
        args.hEvent = hEvent;
    }
    
    static void fillWithoutCapture(ZeCommandListAppendSignalEventRpcM &message, ze_command_list_handle_t hCommandList, ze_event_handle_t hEvent) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hCommandList = hCommandList;
        message.args.hEvent = hEvent;
    }
    
};
static_assert(std::is_standard_layout_v<ZeCommandListAppendSignalEventRpcM>);
struct ZeCommandListAppendWaitOnEventsRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 42;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_command_list_handle_t hCommandList = {};
        uint32_t numEvents = {};
        ze_event_handle_t* phEvents = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hCommandList == rhs.hCommandList;
            equal &= this->numEvents == rhs.numEvents;
            equal &= this->phEvents == rhs.phEvents;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(ze_command_list_handle_t hCommandList, uint32_t numEvents, ze_event_handle_t* phEvents);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits phEvents = {};          
        };

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        uint32_t countPhEvents = 0;
        ze_event_handle_t phEvents[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countPhEvents = dynamicTraits.phEvents.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeCommandListAppendWaitOnEventsRpcM() = default;

    ZeCommandListAppendWaitOnEventsRpcM(const Captures::DynamicTraits &dynamicTraits, ze_command_list_handle_t hCommandList, uint32_t numEvents, ze_event_handle_t* phEvents) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hCommandList = hCommandList;
        args.numEvents = numEvents;
        args.phEvents = phEvents;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ZeCommandListAppendWaitOnEventsRpcM &message, ze_command_list_handle_t hCommandList, uint32_t numEvents, ze_event_handle_t* phEvents) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hCommandList = hCommandList;
        message.args.numEvents = numEvents;
        message.args.phEvents = phEvents;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.phEvents){
            memcpy(asMemcpyDstT(captures.phEvents), args.phEvents, dynMemTraits.phEvents.size);
        }
    }
};
static_assert(std::is_standard_layout_v<ZeCommandListAppendWaitOnEventsRpcM>);
struct ZeEventHostSynchronizeRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 43;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_event_handle_t hEvent = {};
        uint64_t timeout = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hEvent == rhs.hEvent;
            equal &= this->timeout == rhs.timeout;
            return equal;
        }
    }args;

    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeEventHostSynchronizeRpcM() = default;

    ZeEventHostSynchronizeRpcM(ze_event_handle_t hEvent, uint64_t timeout) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hEvent = hEvent;
        args.timeout = timeout;
    }
    
    static void fillWithoutCapture(ZeEventHostSynchronizeRpcM &message, ze_event_handle_t hEvent, uint64_t timeout) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hEvent = hEvent;
        message.args.timeout = timeout;
    }
    
};
static_assert(std::is_standard_layout_v<ZeEventHostSynchronizeRpcM>);
struct ZeEventQueryStatusRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 44;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_event_handle_t hEvent = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hEvent == rhs.hEvent;
            return equal;
        }
    }args;

    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeEventQueryStatusRpcM() = default;

    ZeEventQueryStatusRpcM(ze_event_handle_t hEvent) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hEvent = hEvent;
    }
    
    static void fillWithoutCapture(ZeEventQueryStatusRpcM &message, ze_event_handle_t hEvent) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hEvent = hEvent;
    }
    
};
static_assert(std::is_standard_layout_v<ZeEventQueryStatusRpcM>);
struct ZeEventHostResetRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 45;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_event_handle_t hEvent = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hEvent == rhs.hEvent;
            return equal;
        }
    }args;

    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeEventHostResetRpcM() = default;

    ZeEventHostResetRpcM(ze_event_handle_t hEvent) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hEvent = hEvent;
    }
    
    static void fillWithoutCapture(ZeEventHostResetRpcM &message, ze_event_handle_t hEvent) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hEvent = hEvent;
    }
    
};
static_assert(std::is_standard_layout_v<ZeEventHostResetRpcM>);
struct ZeEventQueryKernelTimestampRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 46;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_event_handle_t hEvent = {};
        ze_kernel_timestamp_result_t* dstptr = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hEvent == rhs.hEvent;
            equal &= this->dstptr == rhs.dstptr;
            return equal;
        }
    }args;

    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        ze_kernel_timestamp_result_t dstptr;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeEventQueryKernelTimestampRpcM() = default;

    ZeEventQueryKernelTimestampRpcM(ze_event_handle_t hEvent, ze_kernel_timestamp_result_t* dstptr) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hEvent = hEvent;
        args.dstptr = dstptr;
    }
    
    static void fillWithoutCapture(ZeEventQueryKernelTimestampRpcM &message, ze_event_handle_t hEvent, ze_kernel_timestamp_result_t* dstptr) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hEvent = hEvent;
        message.args.dstptr = dstptr;
    }
    

    void copyToCaller(){
        if(args.dstptr){
            *args.dstptr = captures.dstptr;
        }
    }
};
static_assert(std::is_standard_layout_v<ZeEventQueryKernelTimestampRpcM>);
struct ZeFenceCreateRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 47;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_command_queue_handle_t hCommandQueue = {};
        const ze_fence_desc_t* desc = {};
        ze_fence_handle_t* phFence = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hCommandQueue == rhs.hCommandQueue;
            equal &= this->desc == rhs.desc;
            equal &= this->phFence == rhs.phFence;
            return equal;
        }
    }args;

    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        ze_fence_desc_t desc;
        ze_fence_handle_t phFence;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeFenceCreateRpcM() = default;

    ZeFenceCreateRpcM(ze_command_queue_handle_t hCommandQueue, const ze_fence_desc_t* desc, ze_fence_handle_t* phFence) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hCommandQueue = hCommandQueue;
        args.desc = desc;
        args.phFence = phFence;
    }
    
    static void fillWithoutCapture(ZeFenceCreateRpcM &message, ze_command_queue_handle_t hCommandQueue, const ze_fence_desc_t* desc, ze_fence_handle_t* phFence) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hCommandQueue = hCommandQueue;
        message.args.desc = desc;
        message.args.phFence = phFence;
    }
    

    void copyFromCaller(){
        if(args.desc){
            captures.desc = *args.desc;
        }
    }

    void copyToCaller(){
        if(args.phFence){
            *args.phFence = captures.phFence;
        }
    }
};
static_assert(std::is_standard_layout_v<ZeFenceCreateRpcM>);
struct ZeFenceDestroyRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 48;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_fence_handle_t hFence = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hFence == rhs.hFence;
            return equal;
        }
    }args;

    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeFenceDestroyRpcM() = default;

    ZeFenceDestroyRpcM(ze_fence_handle_t hFence) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hFence = hFence;
    }
    
    static void fillWithoutCapture(ZeFenceDestroyRpcM &message, ze_fence_handle_t hFence) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hFence = hFence;
    }
    
};
static_assert(std::is_standard_layout_v<ZeFenceDestroyRpcM>);
struct ZeFenceHostSynchronizeRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 49;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_fence_handle_t hFence = {};
        uint64_t timeout = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hFence == rhs.hFence;
            equal &= this->timeout == rhs.timeout;
            return equal;
        }
    }args;

    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeFenceHostSynchronizeRpcM() = default;

    ZeFenceHostSynchronizeRpcM(ze_fence_handle_t hFence, uint64_t timeout) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hFence = hFence;
        args.timeout = timeout;
    }
    
    static void fillWithoutCapture(ZeFenceHostSynchronizeRpcM &message, ze_fence_handle_t hFence, uint64_t timeout) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hFence = hFence;
        message.args.timeout = timeout;
    }
    
};
static_assert(std::is_standard_layout_v<ZeFenceHostSynchronizeRpcM>);
struct ZeFenceQueryStatusRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 50;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_fence_handle_t hFence = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hFence == rhs.hFence;
            return equal;
        }
    }args;

    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeFenceQueryStatusRpcM() = default;

    ZeFenceQueryStatusRpcM(ze_fence_handle_t hFence) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hFence = hFence;
    }
    
    static void fillWithoutCapture(ZeFenceQueryStatusRpcM &message, ze_fence_handle_t hFence) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hFence = hFence;
    }
    
};
static_assert(std::is_standard_layout_v<ZeFenceQueryStatusRpcM>);
struct ZeFenceResetRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 51;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_fence_handle_t hFence = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hFence == rhs.hFence;
            return equal;
        }
    }args;

    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeFenceResetRpcM() = default;

    ZeFenceResetRpcM(ze_fence_handle_t hFence) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hFence = hFence;
    }
    
    static void fillWithoutCapture(ZeFenceResetRpcM &message, ze_fence_handle_t hFence) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hFence = hFence;
    }
    
};
static_assert(std::is_standard_layout_v<ZeFenceResetRpcM>);
struct ZeKernelSetGlobalOffsetExpRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 52;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_kernel_handle_t hKernel = {};
        uint32_t offsetX = {};
        uint32_t offsetY = {};
        uint32_t offsetZ = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hKernel == rhs.hKernel;
            equal &= this->offsetX == rhs.offsetX;
            equal &= this->offsetY == rhs.offsetY;
            equal &= this->offsetZ == rhs.offsetZ;
            return equal;
        }
    }args;

    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeKernelSetGlobalOffsetExpRpcM() = default;

    ZeKernelSetGlobalOffsetExpRpcM(ze_kernel_handle_t hKernel, uint32_t offsetX, uint32_t offsetY, uint32_t offsetZ) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hKernel = hKernel;
        args.offsetX = offsetX;
        args.offsetY = offsetY;
        args.offsetZ = offsetZ;
    }
    
    static void fillWithoutCapture(ZeKernelSetGlobalOffsetExpRpcM &message, ze_kernel_handle_t hKernel, uint32_t offsetX, uint32_t offsetY, uint32_t offsetZ) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hKernel = hKernel;
        message.args.offsetX = offsetX;
        message.args.offsetY = offsetY;
        message.args.offsetZ = offsetZ;
    }
    
};
static_assert(std::is_standard_layout_v<ZeKernelSetGlobalOffsetExpRpcM>);
struct ZeMemAllocSharedRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 53;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_context_handle_t hContext = {};
        const ze_device_mem_alloc_desc_t* device_desc = {};
        const ze_host_mem_alloc_desc_t* host_desc = {};
        size_t size = {};
        size_t alignment = {};
        ze_device_handle_t hDevice = {};
        void** pptr = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hContext == rhs.hContext;
            equal &= this->device_desc == rhs.device_desc;
            equal &= this->host_desc == rhs.host_desc;
            equal &= this->size == rhs.size;
            equal &= this->alignment == rhs.alignment;
            equal &= this->hDevice == rhs.hDevice;
            equal &= this->pptr == rhs.pptr;
            return equal;
        }
    }args;

    struct ImplicitArgs {

           int shmem_resource = {};

           size_t offset_within_resource = {};

           size_t aligned_size = {};
    } implicitArgs;
    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        ze_device_mem_alloc_desc_t device_desc;
        ze_host_mem_alloc_desc_t host_desc;
        void* pptr;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeMemAllocSharedRpcM() = default;

    ZeMemAllocSharedRpcM(ze_context_handle_t hContext, const ze_device_mem_alloc_desc_t* device_desc, const ze_host_mem_alloc_desc_t* host_desc, size_t size, size_t alignment, ze_device_handle_t hDevice, void** pptr) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hContext = hContext;
        args.device_desc = device_desc;
        args.host_desc = host_desc;
        args.size = size;
        args.alignment = alignment;
        args.hDevice = hDevice;
        args.pptr = pptr;
    }
    
    static void fillWithoutCapture(ZeMemAllocSharedRpcM &message, ze_context_handle_t hContext, const ze_device_mem_alloc_desc_t* device_desc, const ze_host_mem_alloc_desc_t* host_desc, size_t size, size_t alignment, ze_device_handle_t hDevice, void** pptr) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hContext = hContext;
        message.args.device_desc = device_desc;
        message.args.host_desc = host_desc;
        message.args.size = size;
        message.args.alignment = alignment;
        message.args.hDevice = hDevice;
        message.args.pptr = pptr;
    }
    

    void copyFromCaller(const ImplicitArgs &implicitArgs){
        if(args.device_desc){
            captures.device_desc = *args.device_desc;
        }
        if(args.host_desc){
            captures.host_desc = *args.host_desc;
        }
    }

    void copyToCaller(ImplicitArgs &implicitArgs){
        if(args.pptr){
            *args.pptr = captures.pptr;
        }
         implicitArgs.shmem_resource = this->implicitArgs.shmem_resource;
         implicitArgs.offset_within_resource = this->implicitArgs.offset_within_resource;
         implicitArgs.aligned_size = this->implicitArgs.aligned_size;
    }
};
static_assert(std::is_standard_layout_v<ZeMemAllocSharedRpcM>);
struct ZeMemAllocDeviceRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 54;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_context_handle_t hContext = {};
        const ze_device_mem_alloc_desc_t* device_desc = {};
        size_t size = {};
        size_t alignment = {};
        ze_device_handle_t hDevice = {};
        void** pptr = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hContext == rhs.hContext;
            equal &= this->device_desc == rhs.device_desc;
            equal &= this->size == rhs.size;
            equal &= this->alignment == rhs.alignment;
            equal &= this->hDevice == rhs.hDevice;
            equal &= this->pptr == rhs.pptr;
            return equal;
        }
    }args;

    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        ze_device_mem_alloc_desc_t device_desc;
        void* pptr;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeMemAllocDeviceRpcM() = default;

    ZeMemAllocDeviceRpcM(ze_context_handle_t hContext, const ze_device_mem_alloc_desc_t* device_desc, size_t size, size_t alignment, ze_device_handle_t hDevice, void** pptr) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hContext = hContext;
        args.device_desc = device_desc;
        args.size = size;
        args.alignment = alignment;
        args.hDevice = hDevice;
        args.pptr = pptr;
    }
    
    static void fillWithoutCapture(ZeMemAllocDeviceRpcM &message, ze_context_handle_t hContext, const ze_device_mem_alloc_desc_t* device_desc, size_t size, size_t alignment, ze_device_handle_t hDevice, void** pptr) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hContext = hContext;
        message.args.device_desc = device_desc;
        message.args.size = size;
        message.args.alignment = alignment;
        message.args.hDevice = hDevice;
        message.args.pptr = pptr;
    }
    

    void copyFromCaller(){
        if(args.device_desc){
            captures.device_desc = *args.device_desc;
        }
    }

    void copyToCaller(){
        if(args.pptr){
            *args.pptr = captures.pptr;
        }
    }
};
static_assert(std::is_standard_layout_v<ZeMemAllocDeviceRpcM>);
struct ZeMemAllocHostRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 55;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_context_handle_t hContext = {};
        const ze_host_mem_alloc_desc_t* host_desc = {};
        size_t size = {};
        size_t alignment = {};
        void** pptr = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hContext == rhs.hContext;
            equal &= this->host_desc == rhs.host_desc;
            equal &= this->size == rhs.size;
            equal &= this->alignment == rhs.alignment;
            equal &= this->pptr == rhs.pptr;
            return equal;
        }
    }args;

    struct ImplicitArgs {

           int shmem_resource = {};

           size_t offset_within_resource = {};

           size_t aligned_size = {};
    } implicitArgs;
    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        ze_host_mem_alloc_desc_t host_desc;
        void* pptr;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeMemAllocHostRpcM() = default;

    ZeMemAllocHostRpcM(ze_context_handle_t hContext, const ze_host_mem_alloc_desc_t* host_desc, size_t size, size_t alignment, void** pptr) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hContext = hContext;
        args.host_desc = host_desc;
        args.size = size;
        args.alignment = alignment;
        args.pptr = pptr;
    }
    
    static void fillWithoutCapture(ZeMemAllocHostRpcM &message, ze_context_handle_t hContext, const ze_host_mem_alloc_desc_t* host_desc, size_t size, size_t alignment, void** pptr) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hContext = hContext;
        message.args.host_desc = host_desc;
        message.args.size = size;
        message.args.alignment = alignment;
        message.args.pptr = pptr;
    }
    

    void copyFromCaller(const ImplicitArgs &implicitArgs){
        if(args.host_desc){
            captures.host_desc = *args.host_desc;
        }
    }

    void copyToCaller(ImplicitArgs &implicitArgs){
        if(args.pptr){
            *args.pptr = captures.pptr;
        }
         implicitArgs.shmem_resource = this->implicitArgs.shmem_resource;
         implicitArgs.offset_within_resource = this->implicitArgs.offset_within_resource;
         implicitArgs.aligned_size = this->implicitArgs.aligned_size;
    }
};
static_assert(std::is_standard_layout_v<ZeMemAllocHostRpcM>);
struct ZeMemFreeRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 56;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_context_handle_t hContext = {};
        void* ptr = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hContext == rhs.hContext;
            equal &= this->ptr == rhs.ptr;
            return equal;
        }
    }args;

    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeMemFreeRpcM() = default;

    ZeMemFreeRpcM(ze_context_handle_t hContext, void* ptr) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hContext = hContext;
        args.ptr = ptr;
    }
    
    static void fillWithoutCapture(ZeMemFreeRpcM &message, ze_context_handle_t hContext, void* ptr) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hContext = hContext;
        message.args.ptr = ptr;
    }
    
};
static_assert(std::is_standard_layout_v<ZeMemFreeRpcM>);
struct ZeMemGetAllocPropertiesRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 57;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_context_handle_t hContext = {};
        const void* ptr = {};
        ze_memory_allocation_properties_t* pMemAllocProperties = {};
        ze_device_handle_t* phDevice = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hContext == rhs.hContext;
            equal &= this->ptr == rhs.ptr;
            equal &= this->pMemAllocProperties == rhs.pMemAllocProperties;
            equal &= this->phDevice == rhs.phDevice;
            return equal;
        }
    }args;

    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        ze_memory_allocation_properties_t pMemAllocProperties;
        ze_device_handle_t phDevice;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeMemGetAllocPropertiesRpcM() = default;

    ZeMemGetAllocPropertiesRpcM(ze_context_handle_t hContext, const void* ptr, ze_memory_allocation_properties_t* pMemAllocProperties, ze_device_handle_t* phDevice) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hContext = hContext;
        args.ptr = ptr;
        args.pMemAllocProperties = pMemAllocProperties;
        args.phDevice = phDevice;
    }
    
    static void fillWithoutCapture(ZeMemGetAllocPropertiesRpcM &message, ze_context_handle_t hContext, const void* ptr, ze_memory_allocation_properties_t* pMemAllocProperties, ze_device_handle_t* phDevice) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hContext = hContext;
        message.args.ptr = ptr;
        message.args.pMemAllocProperties = pMemAllocProperties;
        message.args.phDevice = phDevice;
    }
    

    void copyToCaller(){
        if(args.pMemAllocProperties){
            *args.pMemAllocProperties = captures.pMemAllocProperties;
        }
        if(args.phDevice){
            *args.phDevice = captures.phDevice;
        }
    }
};
static_assert(std::is_standard_layout_v<ZeMemGetAllocPropertiesRpcM>);
struct ZeModuleCreateRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 58;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_context_handle_t hContext = {};
        ze_device_handle_t hDevice = {};
        const ze_module_desc_t* desc = {};
        ze_module_handle_t* phModule = {};
        ze_module_build_log_handle_t* phBuildLog = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hContext == rhs.hContext;
            equal &= this->hDevice == rhs.hDevice;
            equal &= this->desc == rhs.desc;
            equal &= this->phModule == rhs.phModule;
            equal &= this->phBuildLog == rhs.phBuildLog;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_module_desc_t* desc, ze_module_handle_t* phModule, ze_module_build_log_handle_t* phBuildLog);
            uint32_t totalDynamicSize = 0;
            uint32_t dynamicStructMembersOffset = 0;
            DynamicArgTraits descNestedTraits = {};
        };

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        ze_module_desc_t desc;
        ze_module_handle_t phModule;
        ze_module_build_log_handle_t phBuildLog;
        uint32_t dynamicStructMembersOffset = 0;
        uint32_t descNestedTraitsOffset = 0;
        uint32_t descNestedTraitsCount = 0;

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
            dynamicStructMembersOffset = dynamicTraits.dynamicStructMembersOffset;
            descNestedTraitsOffset = dynamicTraits.descNestedTraits.offset;
            descNestedTraitsCount = dynamicTraits.descNestedTraits.count;
            dynMemSize = dynamicTraits.totalDynamicSize;
        }
        
        uint32_t dynMemSize = 0;
        alignas(8) char dynMem[];
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;
        void reassembleNestedStructs() {
            using Cal::Utils::alignUpPow2;

            uint32_t currentOffset = dynamicStructMembersOffset;

            if(descNestedTraitsCount > 0){
                assert(currentOffset == descNestedTraitsOffset);
                auto* descTraits = reinterpret_cast<DynamicStructTraits<ze_module_desc_t>*>(dynMem + currentOffset);
                currentOffset += alignUpPow2<8>(descNestedTraitsCount * sizeof(DynamicStructTraits<ze_module_desc_t>));

                auto* destDesc = &desc;

                for (uint32_t i = 0; i < descNestedTraitsCount; ++i) {
                    if(descTraits[i].pInputModuleOffset == -1){
                        forcePointerWrite(destDesc[i].pInputModule, nullptr);
                        continue;
                    }

                    forcePointerWrite(destDesc[i].pInputModule, dynMem + descTraits[i].pInputModuleOffset);
                    currentOffset += alignUpPow2<8>(descTraits[i].pInputModuleCount * sizeof(uint8_t));
                }

                for (uint32_t i = 0; i < descNestedTraitsCount; ++i) {
                    if(descTraits[i].pBuildFlagsOffset == -1){
                        forcePointerWrite(destDesc[i].pBuildFlags, nullptr);
                        continue;
                    }

                    forcePointerWrite(destDesc[i].pBuildFlags, dynMem + descTraits[i].pBuildFlagsOffset);
                    currentOffset += alignUpPow2<8>(descTraits[i].pBuildFlagsCount * sizeof(char));
                }

                for (uint32_t i = 0; i < descNestedTraitsCount; ++i) {
                    if(descTraits[i].pConstantsOffset == -1){
                        forcePointerWrite(destDesc[i].pConstants, nullptr);
                        continue;
                    }

                    forcePointerWrite(destDesc[i].pConstants, dynMem + descTraits[i].pConstantsOffset);
                    currentOffset += alignUpPow2<8>(descTraits[i].pConstantsCount * sizeof(ze_module_constants_t));

                    auto* descPConstantsTraits = reinterpret_cast<DynamicStructTraits<ze_module_constants_t>*>(dynMem + currentOffset);
                    currentOffset += alignUpPow2<8>(descTraits[i].pConstantsCount * sizeof(DynamicStructTraits<ze_module_constants_t>));

                    for(uint32_t j = 0; j < descTraits[i].pConstantsCount; ++j){
                        if(descPConstantsTraits[j].pConstantIdsOffset == -1){
                            forcePointerWrite(destDesc[i].pConstants[j].pConstantIds, nullptr);
                            continue;
                        }

                        forcePointerWrite(destDesc[i].pConstants[j].pConstantIds, dynMem + descPConstantsTraits[j].pConstantIdsOffset);
                        currentOffset += alignUpPow2<8>(descPConstantsTraits[j].pConstantIdsCount * sizeof(uint32_t));
                    }

                    for(uint32_t j = 0; j < descTraits[i].pConstantsCount; ++j){
                        if(descPConstantsTraits[j].pConstantValuesOffset == -1){
                            forcePointerWrite(destDesc[i].pConstants[j].pConstantValues, nullptr);
                            continue;
                        }

                        forcePointerWrite(destDesc[i].pConstants[j].pConstantValues, dynMem + descPConstantsTraits[j].pConstantValuesOffset);
                        currentOffset += alignUpPow2<8>(descPConstantsTraits[j].pConstantValuesCount * sizeof(const void *));

                        auto* descPConstantsPConstantValuesTraits = reinterpret_cast<DynamicStructTraits<const void *>*>(dynMem + currentOffset);
                        currentOffset += alignUpPow2<8>(descPConstantsTraits[j].pConstantValuesCount * sizeof(DynamicStructTraits<const void *>));

                        for(uint32_t k = 0; k < descPConstantsTraits[j].pConstantValuesCount; ++k){
                            if(descPConstantsPConstantValuesTraits[k].offset == -1){
                                forcePointerWrite(destDesc[i].pConstants[j].pConstantValues[k], nullptr);
                                continue;
                            }

                            forcePointerWrite(destDesc[i].pConstants[j].pConstantValues[k], dynMem + descPConstantsPConstantValuesTraits[k].offset);
                            currentOffset += alignUpPow2<8>(descPConstantsPConstantValuesTraits[k].count * sizeof(uint64_t));
                        }

                    }

                }
        }
    }

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeModuleCreateRpcM() = default;

    ZeModuleCreateRpcM(const Captures::DynamicTraits &dynamicTraits, ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_module_desc_t* desc, ze_module_handle_t* phModule, ze_module_build_log_handle_t* phBuildLog) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hContext = hContext;
        args.hDevice = hDevice;
        args.desc = desc;
        args.phModule = phModule;
        args.phBuildLog = phBuildLog;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ZeModuleCreateRpcM &message, ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_module_desc_t* desc, ze_module_handle_t* phModule, ze_module_build_log_handle_t* phBuildLog) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hContext = hContext;
        message.args.hDevice = hDevice;
        message.args.desc = desc;
        message.args.phModule = phModule;
        message.args.phBuildLog = phBuildLog;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.desc){
            captures.desc = *args.desc;
        }
        using Cal::Utils::alignUpPow2;

        auto& dynMem = captures.dynMem;
        uint32_t currentOffset = captures.dynamicStructMembersOffset;
        if(args.desc){
            assert(currentOffset == captures.descNestedTraitsOffset);
            auto* descTraits = reinterpret_cast<DynamicStructTraits<ze_module_desc_t>*>(dynMem + currentOffset);
            currentOffset += alignUpPow2<8>(captures.descNestedTraitsCount * sizeof(DynamicStructTraits<ze_module_desc_t>));

            for (uint32_t i = 0; i < captures.descNestedTraitsCount; ++i) {
                const auto& descPInputModule = args.desc[i].pInputModule;
                if(!descPInputModule){
                    descTraits[i].pInputModuleOffset = -1;
                    descTraits[i].pInputModuleCount = -1;
                    continue;
                }

                const auto& descPInputModuleCount = args.desc[i].inputSize;
                if(!descPInputModuleCount){
                    descTraits[i].pInputModuleOffset = -1;
                    descTraits[i].pInputModuleCount = -1;
                    continue;
                }

                descTraits[i].pInputModuleOffset = currentOffset;
                descTraits[i].pInputModuleCount = descPInputModuleCount;

                std::memcpy(dynMem + currentOffset, descPInputModule, descPInputModuleCount * sizeof(uint8_t));
                currentOffset += alignUpPow2<8>(descPInputModuleCount * sizeof(uint8_t));
            }

            for (uint32_t i = 0; i < captures.descNestedTraitsCount; ++i) {
                const auto& descPBuildFlags = args.desc[i].pBuildFlags;
                if(!descPBuildFlags){
                    descTraits[i].pBuildFlagsOffset = -1;
                    descTraits[i].pBuildFlagsCount = -1;
                    continue;
                }

                const auto& descPBuildFlagsCount = Cal::Utils::countNullterminated(args.desc[i].pBuildFlags);
                if(!descPBuildFlagsCount){
                    descTraits[i].pBuildFlagsOffset = -1;
                    descTraits[i].pBuildFlagsCount = -1;
                    continue;
                }

                descTraits[i].pBuildFlagsOffset = currentOffset;
                descTraits[i].pBuildFlagsCount = descPBuildFlagsCount;

                std::memcpy(dynMem + currentOffset, descPBuildFlags, descPBuildFlagsCount * sizeof(char));
                currentOffset += alignUpPow2<8>(descPBuildFlagsCount * sizeof(char));
            }

            for (uint32_t i = 0; i < captures.descNestedTraitsCount; ++i) {
                const auto& descPConstants = args.desc[i].pConstants;
                if(!descPConstants){
                    descTraits[i].pConstantsOffset = -1;
                    descTraits[i].pConstantsCount = -1;
                    continue;
                }

                const auto& descPConstantsCount = 1;
                if(!descPConstantsCount){
                    descTraits[i].pConstantsOffset = -1;
                    descTraits[i].pConstantsCount = -1;
                    continue;
                }

                descTraits[i].pConstantsOffset = currentOffset;
                descTraits[i].pConstantsCount = descPConstantsCount;

                std::memcpy(dynMem + currentOffset, descPConstants, descPConstantsCount * sizeof(ze_module_constants_t));
                currentOffset += alignUpPow2<8>(descPConstantsCount * sizeof(ze_module_constants_t));

                auto* descPConstantsTraits = reinterpret_cast<DynamicStructTraits<ze_module_constants_t>*>(dynMem + currentOffset);
                currentOffset += alignUpPow2<8>(descPConstantsCount * sizeof(DynamicStructTraits<ze_module_constants_t>));

                for(uint32_t j = 0; j < descPConstantsCount; ++j){
                    const auto& descPConstantsPConstantIds = args.desc[i].pConstants[j].pConstantIds;
                    if(!descPConstantsPConstantIds){
                        descPConstantsTraits[j].pConstantIdsOffset = -1;
                        descPConstantsTraits[j].pConstantIdsCount = -1;
                        continue;
                    }

                    const auto& descPConstantsPConstantIdsCount = args.desc[i].pConstants[j].numConstants;
                    if(!descPConstantsPConstantIdsCount){
                        descPConstantsTraits[j].pConstantIdsOffset = -1;
                        descPConstantsTraits[j].pConstantIdsCount = -1;
                        continue;
                    }

                    descPConstantsTraits[j].pConstantIdsOffset = currentOffset;
                    descPConstantsTraits[j].pConstantIdsCount = descPConstantsPConstantIdsCount;

                    std::memcpy(dynMem + currentOffset, descPConstantsPConstantIds, descPConstantsPConstantIdsCount * sizeof(uint32_t));
                    currentOffset += alignUpPow2<8>(descPConstantsPConstantIdsCount * sizeof(uint32_t));
                }

                for(uint32_t j = 0; j < descPConstantsCount; ++j){
                    const auto& descPConstantsPConstantValues = args.desc[i].pConstants[j].pConstantValues;
                    if(!descPConstantsPConstantValues){
                        descPConstantsTraits[j].pConstantValuesOffset = -1;
                        descPConstantsTraits[j].pConstantValuesCount = -1;
                        continue;
                    }

                    const auto& descPConstantsPConstantValuesCount = args.desc[i].pConstants[j].numConstants;
                    if(!descPConstantsPConstantValuesCount){
                        descPConstantsTraits[j].pConstantValuesOffset = -1;
                        descPConstantsTraits[j].pConstantValuesCount = -1;
                        continue;
                    }

                    descPConstantsTraits[j].pConstantValuesOffset = currentOffset;
                    descPConstantsTraits[j].pConstantValuesCount = descPConstantsPConstantValuesCount;

                    std::memcpy(dynMem + currentOffset, descPConstantsPConstantValues, descPConstantsPConstantValuesCount * sizeof(const void *));
                    currentOffset += alignUpPow2<8>(descPConstantsPConstantValuesCount * sizeof(const void *));

                    auto* descPConstantsPConstantValuesTraits = reinterpret_cast<DynamicStructTraits<const void *>*>(dynMem + currentOffset);
                    currentOffset += alignUpPow2<8>(descPConstantsPConstantValuesCount * sizeof(DynamicStructTraits<const void *>));

                    for(uint32_t k = 0; k < descPConstantsPConstantValuesCount; ++k){
                        const auto& descPConstantsPConstantValues_k = descPConstantsPConstantValues[k];
                        if(!descPConstantsPConstantValues_k){
                            descPConstantsPConstantValuesTraits[k].offset = -1;
                            descPConstantsPConstantValuesTraits[k].count = -1;
                            continue;
                        }

                        const auto& descPConstantsPConstantValues_kCount = 1;
                        if(!descPConstantsPConstantValues_kCount){
                            descPConstantsPConstantValuesTraits[k].offset = -1;
                            descPConstantsPConstantValuesTraits[k].count = -1;
                            continue;
                        }

                        descPConstantsPConstantValuesTraits[k].offset = currentOffset;
                        descPConstantsPConstantValuesTraits[k].count = descPConstantsPConstantValues_kCount;

                        std::memcpy(dynMem + currentOffset, descPConstantsPConstantValues_k, descPConstantsPConstantValues_kCount * sizeof(uint64_t));
                        currentOffset += alignUpPow2<8>(descPConstantsPConstantValues_kCount * sizeof(uint64_t));
                    }

                }

            }
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.phModule){
            *args.phModule = captures.phModule;
        }
        if(args.phBuildLog){
            *args.phBuildLog = captures.phBuildLog;
        }
    }
};
static_assert(std::is_standard_layout_v<ZeModuleCreateRpcM>);
struct ZeModuleDestroyRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 59;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_module_handle_t hModule = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hModule == rhs.hModule;
            return equal;
        }
    }args;

    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeModuleDestroyRpcM() = default;

    ZeModuleDestroyRpcM(ze_module_handle_t hModule) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hModule = hModule;
    }
    
    static void fillWithoutCapture(ZeModuleDestroyRpcM &message, ze_module_handle_t hModule) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hModule = hModule;
    }
    
};
static_assert(std::is_standard_layout_v<ZeModuleDestroyRpcM>);
struct ZeModuleBuildLogDestroyRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 60;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_module_build_log_handle_t hModuleBuildLog = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hModuleBuildLog == rhs.hModuleBuildLog;
            return equal;
        }
    }args;

    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeModuleBuildLogDestroyRpcM() = default;

    ZeModuleBuildLogDestroyRpcM(ze_module_build_log_handle_t hModuleBuildLog) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hModuleBuildLog = hModuleBuildLog;
    }
    
    static void fillWithoutCapture(ZeModuleBuildLogDestroyRpcM &message, ze_module_build_log_handle_t hModuleBuildLog) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hModuleBuildLog = hModuleBuildLog;
    }
    
};
static_assert(std::is_standard_layout_v<ZeModuleBuildLogDestroyRpcM>);
struct ZeModuleBuildLogGetStringRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 61;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_module_build_log_handle_t hModuleBuildLog = {};
        size_t* pSize = {};
        char* pBuildLog = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hModuleBuildLog == rhs.hModuleBuildLog;
            equal &= this->pSize == rhs.pSize;
            equal &= this->pBuildLog == rhs.pBuildLog;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(ze_module_build_log_handle_t hModuleBuildLog, size_t* pSize, char* pBuildLog);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits pBuildLog = {};          
        };

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        size_t pSize;
        uint32_t countPBuildLog = 0;
        char pBuildLog[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countPBuildLog = dynamicTraits.pBuildLog.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeModuleBuildLogGetStringRpcM() = default;

    ZeModuleBuildLogGetStringRpcM(const Captures::DynamicTraits &dynamicTraits, ze_module_build_log_handle_t hModuleBuildLog, size_t* pSize, char* pBuildLog) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hModuleBuildLog = hModuleBuildLog;
        args.pSize = pSize;
        args.pBuildLog = pBuildLog;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ZeModuleBuildLogGetStringRpcM &message, ze_module_build_log_handle_t hModuleBuildLog, size_t* pSize, char* pBuildLog) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hModuleBuildLog = hModuleBuildLog;
        message.args.pSize = pSize;
        message.args.pBuildLog = pBuildLog;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.pSize){
            captures.pSize = *args.pSize;
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.pSize){
            *args.pSize = captures.pSize;
        }
        if(args.pBuildLog){
            memcpy(args.pBuildLog, captures.pBuildLog, dynMemTraits.pBuildLog.size);
        }
    }
};
static_assert(std::is_standard_layout_v<ZeModuleBuildLogGetStringRpcM>);
struct ZeModuleGetGlobalPointerRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 62;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_module_handle_t hModule = {};
        const char* pGlobalName = {};
        size_t* pSize = {};
        void** pptr = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hModule == rhs.hModule;
            equal &= this->pGlobalName == rhs.pGlobalName;
            equal &= this->pSize == rhs.pSize;
            equal &= this->pptr == rhs.pptr;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(ze_module_handle_t hModule, const char* pGlobalName, size_t* pSize, void** pptr);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits pGlobalName = {};          
        };

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        size_t pSize;
        void* pptr;
        uint32_t countPGlobalName = 0;
        char pGlobalName[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countPGlobalName = dynamicTraits.pGlobalName.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeModuleGetGlobalPointerRpcM() = default;

    ZeModuleGetGlobalPointerRpcM(const Captures::DynamicTraits &dynamicTraits, ze_module_handle_t hModule, const char* pGlobalName, size_t* pSize, void** pptr) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hModule = hModule;
        args.pGlobalName = pGlobalName;
        args.pSize = pSize;
        args.pptr = pptr;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ZeModuleGetGlobalPointerRpcM &message, ze_module_handle_t hModule, const char* pGlobalName, size_t* pSize, void** pptr) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hModule = hModule;
        message.args.pGlobalName = pGlobalName;
        message.args.pSize = pSize;
        message.args.pptr = pptr;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.pGlobalName){
            memcpy(asMemcpyDstT(captures.pGlobalName), args.pGlobalName, dynMemTraits.pGlobalName.size);
        }
        if(args.pSize){
            captures.pSize = *args.pSize;
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.pSize){
            *args.pSize = captures.pSize;
        }
        if(args.pptr){
            *args.pptr = captures.pptr;
        }
    }
};
static_assert(std::is_standard_layout_v<ZeModuleGetGlobalPointerRpcM>);
 // zeModuleGetKernelNames ignored in generator - based on dont_generate_rpc_message flag
struct ZeModuleGetKernelNamesRpcHelperRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 63;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_module_handle_t hModule = {};
        uint32_t* totalLength = {};
        char* namesBuffer = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hModule == rhs.hModule;
            equal &= this->totalLength == rhs.totalLength;
            equal &= this->namesBuffer == rhs.namesBuffer;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(ze_module_handle_t hModule, uint32_t* totalLength, char* namesBuffer);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits namesBuffer = {};          
        };

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        uint32_t totalLength;
        uint32_t countNamesBuffer = 0;
        char namesBuffer[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countNamesBuffer = dynamicTraits.namesBuffer.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeModuleGetKernelNamesRpcHelperRpcM() = default;

    ZeModuleGetKernelNamesRpcHelperRpcM(const Captures::DynamicTraits &dynamicTraits, ze_module_handle_t hModule, uint32_t* totalLength, char* namesBuffer) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hModule = hModule;
        args.totalLength = totalLength;
        args.namesBuffer = namesBuffer;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ZeModuleGetKernelNamesRpcHelperRpcM &message, ze_module_handle_t hModule, uint32_t* totalLength, char* namesBuffer) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hModule = hModule;
        message.args.totalLength = totalLength;
        message.args.namesBuffer = namesBuffer;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.totalLength){
            captures.totalLength = *args.totalLength;
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.totalLength){
            *args.totalLength = captures.totalLength;
        }
        if(args.namesBuffer){
            memcpy(args.namesBuffer, captures.namesBuffer, dynMemTraits.namesBuffer.size);
        }
    }
};
static_assert(std::is_standard_layout_v<ZeModuleGetKernelNamesRpcHelperRpcM>);
struct ZeModuleGetPropertiesRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 64;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_module_handle_t hModule = {};
        ze_module_properties_t* pModuleProperties = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hModule == rhs.hModule;
            equal &= this->pModuleProperties == rhs.pModuleProperties;
            return equal;
        }
    }args;

    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        ze_module_properties_t pModuleProperties;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeModuleGetPropertiesRpcM() = default;

    ZeModuleGetPropertiesRpcM(ze_module_handle_t hModule, ze_module_properties_t* pModuleProperties) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hModule = hModule;
        args.pModuleProperties = pModuleProperties;
    }
    
    static void fillWithoutCapture(ZeModuleGetPropertiesRpcM &message, ze_module_handle_t hModule, ze_module_properties_t* pModuleProperties) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hModule = hModule;
        message.args.pModuleProperties = pModuleProperties;
    }
    

    void copyToCaller(){
        if(args.pModuleProperties){
            *args.pModuleProperties = captures.pModuleProperties;
        }
    }
};
static_assert(std::is_standard_layout_v<ZeModuleGetPropertiesRpcM>);
struct ZeKernelCreateRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 65;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_module_handle_t hModule = {};
        const ze_kernel_desc_t* desc = {};
        ze_kernel_handle_t* phKernel = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hModule == rhs.hModule;
            equal &= this->desc == rhs.desc;
            equal &= this->phKernel == rhs.phKernel;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(ze_module_handle_t hModule, const ze_kernel_desc_t* desc, ze_kernel_handle_t* phKernel);
            uint32_t totalDynamicSize = 0;
            uint32_t dynamicStructMembersOffset = 0;
            DynamicArgTraits descNestedTraits = {};
        };

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        ze_kernel_desc_t desc;
        ze_kernel_handle_t phKernel;
        uint32_t dynamicStructMembersOffset = 0;
        uint32_t descNestedTraitsOffset = 0;
        uint32_t descNestedTraitsCount = 0;

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
            dynamicStructMembersOffset = dynamicTraits.dynamicStructMembersOffset;
            descNestedTraitsOffset = dynamicTraits.descNestedTraits.offset;
            descNestedTraitsCount = dynamicTraits.descNestedTraits.count;
            dynMemSize = dynamicTraits.totalDynamicSize;
        }
        
        uint32_t dynMemSize = 0;
        alignas(8) char dynMem[];
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        std::unique_ptr<char[]> clone() {
            auto newCapturesMem = std::make_unique<char[]>(getCaptureTotalSize());
            auto newCaptures = new (newCapturesMem.get()) Captures();

            constexpr static bool skipSizeValidation{true};
            newCaptures->assignFrom(*this, skipSizeValidation);

            return newCapturesMem;
        }

        bool assignFrom(const Captures& rhs, bool skipSizeValidation = false) {
            if (this == &rhs) {
                return true;
            }
            if (!skipSizeValidation && getCaptureDynMemSize() != rhs.getCaptureDynMemSize()) {
                return false;
            }
            this->ret = rhs.ret;
            this->desc = rhs.desc;
            this->phKernel = rhs.phKernel;
            this->descNestedTraitsOffset = rhs.descNestedTraitsOffset;
            this->descNestedTraitsCount = rhs.descNestedTraitsCount;
            memcpy(this->dynMem, rhs.dynMem, rhs.getCaptureDynMemSize());
            this->dynMemSize = rhs.dynMemSize;
            this->dynamicStructMembersOffset = rhs.dynamicStructMembersOffset;
            reassembleNestedStructs();
            return true;
        }
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;
        void reassembleNestedStructs() {
            using Cal::Utils::alignUpPow2;

            uint32_t currentOffset = dynamicStructMembersOffset;

            if(descNestedTraitsCount > 0){
                assert(currentOffset == descNestedTraitsOffset);
                auto* descTraits = reinterpret_cast<DynamicStructTraits<ze_kernel_desc_t>*>(dynMem + currentOffset);
                currentOffset += alignUpPow2<8>(descNestedTraitsCount * sizeof(DynamicStructTraits<ze_kernel_desc_t>));

                auto* destDesc = &desc;

                for (uint32_t i = 0; i < descNestedTraitsCount; ++i) {
                    if(descTraits[i].pKernelNameOffset == -1){
                        forcePointerWrite(destDesc[i].pKernelName, nullptr);
                        continue;
                    }

                    forcePointerWrite(destDesc[i].pKernelName, dynMem + descTraits[i].pKernelNameOffset);
                    currentOffset += alignUpPow2<8>(descTraits[i].pKernelNameCount * sizeof(char));
                }
        }
    }

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeKernelCreateRpcM() = default;

    ZeKernelCreateRpcM(const Captures::DynamicTraits &dynamicTraits, ze_module_handle_t hModule, const ze_kernel_desc_t* desc, ze_kernel_handle_t* phKernel) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hModule = hModule;
        args.desc = desc;
        args.phKernel = phKernel;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ZeKernelCreateRpcM &message, ze_module_handle_t hModule, const ze_kernel_desc_t* desc, ze_kernel_handle_t* phKernel) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hModule = hModule;
        message.args.desc = desc;
        message.args.phKernel = phKernel;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.desc){
            captures.desc = *args.desc;
        }
        using Cal::Utils::alignUpPow2;

        auto& dynMem = captures.dynMem;
        uint32_t currentOffset = captures.dynamicStructMembersOffset;
        if(args.desc){
            assert(currentOffset == captures.descNestedTraitsOffset);
            auto* descTraits = reinterpret_cast<DynamicStructTraits<ze_kernel_desc_t>*>(dynMem + currentOffset);
            currentOffset += alignUpPow2<8>(captures.descNestedTraitsCount * sizeof(DynamicStructTraits<ze_kernel_desc_t>));

            for (uint32_t i = 0; i < captures.descNestedTraitsCount; ++i) {
                const auto& descPKernelName = args.desc[i].pKernelName;
                if(!descPKernelName){
                    descTraits[i].pKernelNameOffset = -1;
                    descTraits[i].pKernelNameCount = -1;
                    continue;
                }

                const auto& descPKernelNameCount = Cal::Utils::countNullterminated(args.desc[i].pKernelName);
                if(!descPKernelNameCount){
                    descTraits[i].pKernelNameOffset = -1;
                    descTraits[i].pKernelNameCount = -1;
                    continue;
                }

                descTraits[i].pKernelNameOffset = currentOffset;
                descTraits[i].pKernelNameCount = descPKernelNameCount;

                std::memcpy(dynMem + currentOffset, descPKernelName, descPKernelNameCount * sizeof(char));
                currentOffset += alignUpPow2<8>(descPKernelNameCount * sizeof(char));
            }
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.phKernel){
            *args.phKernel = captures.phKernel;
        }
    }
};
static_assert(std::is_standard_layout_v<ZeKernelCreateRpcM>);
struct ZeKernelDestroyRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 66;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_kernel_handle_t hKernel = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hKernel == rhs.hKernel;
            return equal;
        }
    }args;

    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeKernelDestroyRpcM() = default;

    ZeKernelDestroyRpcM(ze_kernel_handle_t hKernel) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hKernel = hKernel;
    }
    
    static void fillWithoutCapture(ZeKernelDestroyRpcM &message, ze_kernel_handle_t hKernel) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hKernel = hKernel;
    }
    
};
static_assert(std::is_standard_layout_v<ZeKernelDestroyRpcM>);
struct ZeModuleGetFunctionPointerRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 67;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_module_handle_t hModule = {};
        const char* pFunctionName = {};
        void** pfnFunction = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hModule == rhs.hModule;
            equal &= this->pFunctionName == rhs.pFunctionName;
            equal &= this->pfnFunction == rhs.pfnFunction;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(ze_module_handle_t hModule, const char* pFunctionName, void** pfnFunction);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits pFunctionName = {};          
        };

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        void* pfnFunction;
        uint32_t countPFunctionName = 0;
        char pFunctionName[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countPFunctionName = dynamicTraits.pFunctionName.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeModuleGetFunctionPointerRpcM() = default;

    ZeModuleGetFunctionPointerRpcM(const Captures::DynamicTraits &dynamicTraits, ze_module_handle_t hModule, const char* pFunctionName, void** pfnFunction) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hModule = hModule;
        args.pFunctionName = pFunctionName;
        args.pfnFunction = pfnFunction;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ZeModuleGetFunctionPointerRpcM &message, ze_module_handle_t hModule, const char* pFunctionName, void** pfnFunction) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hModule = hModule;
        message.args.pFunctionName = pFunctionName;
        message.args.pfnFunction = pfnFunction;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.pFunctionName){
            memcpy(asMemcpyDstT(captures.pFunctionName), args.pFunctionName, dynMemTraits.pFunctionName.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.pfnFunction){
            *args.pfnFunction = captures.pfnFunction;
        }
    }
};
static_assert(std::is_standard_layout_v<ZeModuleGetFunctionPointerRpcM>);
struct ZeKernelSetGroupSizeRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 68;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_kernel_handle_t hKernel = {};
        uint32_t groupSizeX = {};
        uint32_t groupSizeY = {};
        uint32_t groupSizeZ = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hKernel == rhs.hKernel;
            equal &= this->groupSizeX == rhs.groupSizeX;
            equal &= this->groupSizeY == rhs.groupSizeY;
            equal &= this->groupSizeZ == rhs.groupSizeZ;
            return equal;
        }
    }args;

    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeKernelSetGroupSizeRpcM() = default;

    ZeKernelSetGroupSizeRpcM(ze_kernel_handle_t hKernel, uint32_t groupSizeX, uint32_t groupSizeY, uint32_t groupSizeZ) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hKernel = hKernel;
        args.groupSizeX = groupSizeX;
        args.groupSizeY = groupSizeY;
        args.groupSizeZ = groupSizeZ;
    }
    
    static void fillWithoutCapture(ZeKernelSetGroupSizeRpcM &message, ze_kernel_handle_t hKernel, uint32_t groupSizeX, uint32_t groupSizeY, uint32_t groupSizeZ) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hKernel = hKernel;
        message.args.groupSizeX = groupSizeX;
        message.args.groupSizeY = groupSizeY;
        message.args.groupSizeZ = groupSizeZ;
    }
    
};
static_assert(std::is_standard_layout_v<ZeKernelSetGroupSizeRpcM>);
struct ZeKernelSuggestGroupSizeRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 69;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_kernel_handle_t hKernel = {};
        uint32_t globalSizeX = {};
        uint32_t globalSizeY = {};
        uint32_t globalSizeZ = {};
        uint32_t* groupSizeX = {};
        uint32_t* groupSizeY = {};
        uint32_t* groupSizeZ = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hKernel == rhs.hKernel;
            equal &= this->globalSizeX == rhs.globalSizeX;
            equal &= this->globalSizeY == rhs.globalSizeY;
            equal &= this->globalSizeZ == rhs.globalSizeZ;
            equal &= this->groupSizeX == rhs.groupSizeX;
            equal &= this->groupSizeY == rhs.groupSizeY;
            equal &= this->groupSizeZ == rhs.groupSizeZ;
            return equal;
        }
    }args;

    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        uint32_t groupSizeX;
        uint32_t groupSizeY;
        uint32_t groupSizeZ;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeKernelSuggestGroupSizeRpcM() = default;

    ZeKernelSuggestGroupSizeRpcM(ze_kernel_handle_t hKernel, uint32_t globalSizeX, uint32_t globalSizeY, uint32_t globalSizeZ, uint32_t* groupSizeX, uint32_t* groupSizeY, uint32_t* groupSizeZ) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hKernel = hKernel;
        args.globalSizeX = globalSizeX;
        args.globalSizeY = globalSizeY;
        args.globalSizeZ = globalSizeZ;
        args.groupSizeX = groupSizeX;
        args.groupSizeY = groupSizeY;
        args.groupSizeZ = groupSizeZ;
    }
    
    static void fillWithoutCapture(ZeKernelSuggestGroupSizeRpcM &message, ze_kernel_handle_t hKernel, uint32_t globalSizeX, uint32_t globalSizeY, uint32_t globalSizeZ, uint32_t* groupSizeX, uint32_t* groupSizeY, uint32_t* groupSizeZ) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hKernel = hKernel;
        message.args.globalSizeX = globalSizeX;
        message.args.globalSizeY = globalSizeY;
        message.args.globalSizeZ = globalSizeZ;
        message.args.groupSizeX = groupSizeX;
        message.args.groupSizeY = groupSizeY;
        message.args.groupSizeZ = groupSizeZ;
    }
    

    void copyToCaller(){
        if(args.groupSizeX){
            *args.groupSizeX = captures.groupSizeX;
        }
        if(args.groupSizeY){
            *args.groupSizeY = captures.groupSizeY;
        }
        if(args.groupSizeZ){
            *args.groupSizeZ = captures.groupSizeZ;
        }
    }
};
static_assert(std::is_standard_layout_v<ZeKernelSuggestGroupSizeRpcM>);
struct ZeKernelSuggestMaxCooperativeGroupCountRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 70;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_kernel_handle_t hKernel = {};
        uint32_t* totalGroupCount = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hKernel == rhs.hKernel;
            equal &= this->totalGroupCount == rhs.totalGroupCount;
            return equal;
        }
    }args;

    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        uint32_t totalGroupCount;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeKernelSuggestMaxCooperativeGroupCountRpcM() = default;

    ZeKernelSuggestMaxCooperativeGroupCountRpcM(ze_kernel_handle_t hKernel, uint32_t* totalGroupCount) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hKernel = hKernel;
        args.totalGroupCount = totalGroupCount;
    }
    
    static void fillWithoutCapture(ZeKernelSuggestMaxCooperativeGroupCountRpcM &message, ze_kernel_handle_t hKernel, uint32_t* totalGroupCount) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hKernel = hKernel;
        message.args.totalGroupCount = totalGroupCount;
    }
    

    void copyToCaller(){
        if(args.totalGroupCount){
            *args.totalGroupCount = captures.totalGroupCount;
        }
    }
};
static_assert(std::is_standard_layout_v<ZeKernelSuggestMaxCooperativeGroupCountRpcM>);
struct ZeKernelSetArgumentValueRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 71;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_kernel_handle_t hKernel = {};
        uint32_t argIndex = {};
        size_t argSize = {};
        const void* pArgValue = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hKernel == rhs.hKernel;
            equal &= this->argIndex == rhs.argIndex;
            equal &= this->argSize == rhs.argSize;
            equal &= this->pArgValue == rhs.pArgValue;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(ze_kernel_handle_t hKernel, uint32_t argIndex, size_t argSize, const void* pArgValue);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits pArgValue = {};          
        };

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        uint32_t countPArgValue = 0;
        char pArgValue[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countPArgValue = dynamicTraits.pArgValue.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeKernelSetArgumentValueRpcM() = default;

    ZeKernelSetArgumentValueRpcM(const Captures::DynamicTraits &dynamicTraits, ze_kernel_handle_t hKernel, uint32_t argIndex, size_t argSize, const void* pArgValue) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hKernel = hKernel;
        args.argIndex = argIndex;
        args.argSize = argSize;
        args.pArgValue = pArgValue;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ZeKernelSetArgumentValueRpcM &message, ze_kernel_handle_t hKernel, uint32_t argIndex, size_t argSize, const void* pArgValue) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hKernel = hKernel;
        message.args.argIndex = argIndex;
        message.args.argSize = argSize;
        message.args.pArgValue = pArgValue;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.pArgValue){
            memcpy(asMemcpyDstT(captures.pArgValue), args.pArgValue, dynMemTraits.pArgValue.size);
        }
    }
};
static_assert(std::is_standard_layout_v<ZeKernelSetArgumentValueRpcM>);
struct ZeKernelSetIndirectAccessRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 72;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_kernel_handle_t hKernel = {};
        ze_kernel_indirect_access_flags_t flags = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hKernel == rhs.hKernel;
            equal &= this->flags == rhs.flags;
            return equal;
        }
    }args;

    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeKernelSetIndirectAccessRpcM() = default;

    ZeKernelSetIndirectAccessRpcM(ze_kernel_handle_t hKernel, ze_kernel_indirect_access_flags_t flags) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hKernel = hKernel;
        args.flags = flags;
    }
    
    static void fillWithoutCapture(ZeKernelSetIndirectAccessRpcM &message, ze_kernel_handle_t hKernel, ze_kernel_indirect_access_flags_t flags) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hKernel = hKernel;
        message.args.flags = flags;
    }
    
};
static_assert(std::is_standard_layout_v<ZeKernelSetIndirectAccessRpcM>);
struct ZeKernelGetIndirectAccessRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 73;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_kernel_handle_t hKernel = {};
        ze_kernel_indirect_access_flags_t* pFlags = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hKernel == rhs.hKernel;
            equal &= this->pFlags == rhs.pFlags;
            return equal;
        }
    }args;

    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        ze_kernel_indirect_access_flags_t pFlags;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeKernelGetIndirectAccessRpcM() = default;

    ZeKernelGetIndirectAccessRpcM(ze_kernel_handle_t hKernel, ze_kernel_indirect_access_flags_t* pFlags) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hKernel = hKernel;
        args.pFlags = pFlags;
    }
    
    static void fillWithoutCapture(ZeKernelGetIndirectAccessRpcM &message, ze_kernel_handle_t hKernel, ze_kernel_indirect_access_flags_t* pFlags) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hKernel = hKernel;
        message.args.pFlags = pFlags;
    }
    

    void copyToCaller(){
        if(args.pFlags){
            *args.pFlags = captures.pFlags;
        }
    }
};
static_assert(std::is_standard_layout_v<ZeKernelGetIndirectAccessRpcM>);
struct ZeKernelSetCacheConfigRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 74;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_kernel_handle_t hKernel = {};
        ze_cache_config_flags_t flags = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hKernel == rhs.hKernel;
            equal &= this->flags == rhs.flags;
            return equal;
        }
    }args;

    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeKernelSetCacheConfigRpcM() = default;

    ZeKernelSetCacheConfigRpcM(ze_kernel_handle_t hKernel, ze_cache_config_flags_t flags) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hKernel = hKernel;
        args.flags = flags;
    }
    
    static void fillWithoutCapture(ZeKernelSetCacheConfigRpcM &message, ze_kernel_handle_t hKernel, ze_cache_config_flags_t flags) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hKernel = hKernel;
        message.args.flags = flags;
    }
    
};
static_assert(std::is_standard_layout_v<ZeKernelSetCacheConfigRpcM>);
struct ZeKernelGetPropertiesRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 75;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_kernel_handle_t hKernel = {};
        ze_kernel_properties_t* pKernelProperties = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hKernel == rhs.hKernel;
            equal &= this->pKernelProperties == rhs.pKernelProperties;
            return equal;
        }
    }args;

    struct Captures {

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        ze_kernel_properties_t pKernelProperties;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeKernelGetPropertiesRpcM() = default;

    ZeKernelGetPropertiesRpcM(ze_kernel_handle_t hKernel, ze_kernel_properties_t* pKernelProperties) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hKernel = hKernel;
        args.pKernelProperties = pKernelProperties;
    }
    
    static void fillWithoutCapture(ZeKernelGetPropertiesRpcM &message, ze_kernel_handle_t hKernel, ze_kernel_properties_t* pKernelProperties) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hKernel = hKernel;
        message.args.pKernelProperties = pKernelProperties;
    }
    

    void copyToCaller(){
        if(args.pKernelProperties){
            *args.pKernelProperties = captures.pKernelProperties;
        }
    }
};
static_assert(std::is_standard_layout_v<ZeKernelGetPropertiesRpcM>);
struct ZeKernelGetNameRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 76;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_kernel_handle_t hKernel = {};
        size_t* pSize = {};
        char* pName = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hKernel == rhs.hKernel;
            equal &= this->pSize == rhs.pSize;
            equal &= this->pName == rhs.pName;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(ze_kernel_handle_t hKernel, size_t* pSize, char* pName);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits pName = {};          
        };

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        size_t pSize;
        uint32_t countPName = 0;
        char pName[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countPName = dynamicTraits.pName.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeKernelGetNameRpcM() = default;

    ZeKernelGetNameRpcM(const Captures::DynamicTraits &dynamicTraits, ze_kernel_handle_t hKernel, size_t* pSize, char* pName) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hKernel = hKernel;
        args.pSize = pSize;
        args.pName = pName;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ZeKernelGetNameRpcM &message, ze_kernel_handle_t hKernel, size_t* pSize, char* pName) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hKernel = hKernel;
        message.args.pSize = pSize;
        message.args.pName = pName;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.pSize){
            captures.pSize = *args.pSize;
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.pSize){
            *args.pSize = captures.pSize;
        }
        if(args.pName){
            memcpy(args.pName, captures.pName, dynMemTraits.pName.size);
        }
    }
};
static_assert(std::is_standard_layout_v<ZeKernelGetNameRpcM>);
struct ZeCommandListAppendLaunchKernelRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 77;

    using ReturnValueT = ze_result_t;

    struct Args {
        ze_command_list_handle_t hCommandList = {};
        ze_kernel_handle_t hKernel = {};
        const ze_group_count_t* pLaunchFuncArgs = {};
        ze_event_handle_t hSignalEvent = {};
        uint32_t numWaitEvents = {};
        ze_event_handle_t* phWaitEvents = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->hCommandList == rhs.hCommandList;
            equal &= this->hKernel == rhs.hKernel;
            equal &= this->pLaunchFuncArgs == rhs.pLaunchFuncArgs;
            equal &= this->hSignalEvent == rhs.hSignalEvent;
            equal &= this->numWaitEvents == rhs.numWaitEvents;
            equal &= this->phWaitEvents == rhs.phWaitEvents;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchFuncArgs, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits phWaitEvents = {};          
        };

        ze_result_t ret = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        ze_group_count_t pLaunchFuncArgs;
        uint32_t countPhWaitEvents = 0;
        ze_event_handle_t phWaitEvents[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countPhWaitEvents = dynamicTraits.phWaitEvents.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    ze_result_t returnValue(){
        return captures.ret;
    }

    ZeCommandListAppendLaunchKernelRpcM() = default;

    ZeCommandListAppendLaunchKernelRpcM(const Captures::DynamicTraits &dynamicTraits, ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchFuncArgs, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        header.subtype = messageSubtype;
        args.hCommandList = hCommandList;
        args.hKernel = hKernel;
        args.pLaunchFuncArgs = pLaunchFuncArgs;
        args.hSignalEvent = hSignalEvent;
        args.numWaitEvents = numWaitEvents;
        args.phWaitEvents = phWaitEvents;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ZeCommandListAppendLaunchKernelRpcM &message, ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchFuncArgs, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero;
        message.header.subtype = messageSubtype;
        message.args.hCommandList = hCommandList;
        message.args.hKernel = hKernel;
        message.args.pLaunchFuncArgs = pLaunchFuncArgs;
        message.args.hSignalEvent = hSignalEvent;
        message.args.numWaitEvents = numWaitEvents;
        message.args.phWaitEvents = phWaitEvents;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.pLaunchFuncArgs){
            captures.pLaunchFuncArgs = *args.pLaunchFuncArgs;
        }
        if(args.phWaitEvents){
            memcpy(asMemcpyDstT(captures.phWaitEvents), args.phWaitEvents, dynMemTraits.phWaitEvents.size);
        }
    }
};
static_assert(std::is_standard_layout_v<ZeCommandListAppendLaunchKernelRpcM>);

inline const char *getRpcCallFname(const RpcCallId callId) {
    static const std::unordered_map<RpcMessageHeader::MessageUniqueIdT, std::string> options = {
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeInitRpcM::messageSubtype).id, "zeInit"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeCommandListCreateRpcM::messageSubtype).id, "zeCommandListCreate"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeCommandListCreateImmediateRpcM::messageSubtype).id, "zeCommandListCreateImmediate"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeCommandListDestroyRpcM::messageSubtype).id, "zeCommandListDestroy"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeCommandListCloseRpcM::messageSubtype).id, "zeCommandListClose"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeCommandListResetRpcM::messageSubtype).id, "zeCommandListReset"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeCommandQueueCreateRpcM::messageSubtype).id, "zeCommandQueueCreate"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeCommandQueueDestroyRpcM::messageSubtype).id, "zeCommandQueueDestroy"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeCommandQueueExecuteCommandListsRpcM::messageSubtype).id, "zeCommandQueueExecuteCommandLists"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeCommandQueueExecuteCommandListsCopySourceMemoryRpcHelperRpcM::messageSubtype).id, "zeCommandQueueExecuteCommandListsCopySourceMemoryRpcHelper"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeCommandQueueSynchronizeRpcM::messageSubtype).id, "zeCommandQueueSynchronize"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeContextCreateRpcM::messageSubtype).id, "zeContextCreate"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeContextDestroyRpcM::messageSubtype).id, "zeContextDestroy"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeContextGetStatusRpcM::messageSubtype).id, "zeContextGetStatus"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeCommandListAppendMemoryCopyRpcHelperUsm2UsmRpcM::messageSubtype).id, "zeCommandListAppendMemoryCopyRpcHelperUsm2Usm"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeCommandListAppendMemoryCopyRpcHelperMalloc2UsmRpcM::messageSubtype).id, "zeCommandListAppendMemoryCopyRpcHelperMalloc2Usm"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeCommandListAppendMemoryFillRpcHelperUsm2UsmRpcM::messageSubtype).id, "zeCommandListAppendMemoryFillRpcHelperUsm2Usm"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeCommandListAppendMemoryFillRpcHelperMalloc2UsmRpcM::messageSubtype).id, "zeCommandListAppendMemoryFillRpcHelperMalloc2Usm"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDeviceGetRpcM::messageSubtype).id, "zeDeviceGet"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDeviceGetSubDevicesRpcM::messageSubtype).id, "zeDeviceGetSubDevices"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDeviceGetPropertiesRpcM::messageSubtype).id, "zeDeviceGetProperties"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDeviceGetComputePropertiesRpcM::messageSubtype).id, "zeDeviceGetComputeProperties"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDeviceGetModulePropertiesRpcM::messageSubtype).id, "zeDeviceGetModuleProperties"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDeviceGetCommandQueueGroupPropertiesRpcM::messageSubtype).id, "zeDeviceGetCommandQueueGroupProperties"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDeviceGetMemoryPropertiesRpcM::messageSubtype).id, "zeDeviceGetMemoryProperties"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDeviceGetMemoryAccessPropertiesRpcM::messageSubtype).id, "zeDeviceGetMemoryAccessProperties"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDeviceGetCachePropertiesRpcM::messageSubtype).id, "zeDeviceGetCacheProperties"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDeviceGetImagePropertiesRpcM::messageSubtype).id, "zeDeviceGetImageProperties"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDeviceGetExternalMemoryPropertiesRpcM::messageSubtype).id, "zeDeviceGetExternalMemoryProperties"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDeviceCanAccessPeerRpcM::messageSubtype).id, "zeDeviceCanAccessPeer"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDeviceGetStatusRpcM::messageSubtype).id, "zeDeviceGetStatus"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDeviceGetGlobalTimestampsRpcM::messageSubtype).id, "zeDeviceGetGlobalTimestamps"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDriverGetRpcM::messageSubtype).id, "zeDriverGet"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDriverGetApiVersionRpcM::messageSubtype).id, "zeDriverGetApiVersion"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDriverGetPropertiesRpcM::messageSubtype).id, "zeDriverGetProperties"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDriverGetIpcPropertiesRpcM::messageSubtype).id, "zeDriverGetIpcProperties"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDriverGetExtensionPropertiesRpcM::messageSubtype).id, "zeDriverGetExtensionProperties"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeEventPoolCreateRpcM::messageSubtype).id, "zeEventPoolCreate"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeEventPoolDestroyRpcM::messageSubtype).id, "zeEventPoolDestroy"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeEventCreateRpcM::messageSubtype).id, "zeEventCreate"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeEventDestroyRpcM::messageSubtype).id, "zeEventDestroy"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeCommandListAppendSignalEventRpcM::messageSubtype).id, "zeCommandListAppendSignalEvent"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeCommandListAppendWaitOnEventsRpcM::messageSubtype).id, "zeCommandListAppendWaitOnEvents"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeEventHostSynchronizeRpcM::messageSubtype).id, "zeEventHostSynchronize"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeEventQueryStatusRpcM::messageSubtype).id, "zeEventQueryStatus"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeEventHostResetRpcM::messageSubtype).id, "zeEventHostReset"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeEventQueryKernelTimestampRpcM::messageSubtype).id, "zeEventQueryKernelTimestamp"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeFenceCreateRpcM::messageSubtype).id, "zeFenceCreate"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeFenceDestroyRpcM::messageSubtype).id, "zeFenceDestroy"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeFenceHostSynchronizeRpcM::messageSubtype).id, "zeFenceHostSynchronize"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeFenceQueryStatusRpcM::messageSubtype).id, "zeFenceQueryStatus"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeFenceResetRpcM::messageSubtype).id, "zeFenceReset"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeKernelSetGlobalOffsetExpRpcM::messageSubtype).id, "zeKernelSetGlobalOffsetExp"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeMemAllocSharedRpcM::messageSubtype).id, "zeMemAllocShared"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeMemAllocDeviceRpcM::messageSubtype).id, "zeMemAllocDevice"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeMemAllocHostRpcM::messageSubtype).id, "zeMemAllocHost"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeMemFreeRpcM::messageSubtype).id, "zeMemFree"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeMemGetAllocPropertiesRpcM::messageSubtype).id, "zeMemGetAllocProperties"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeModuleCreateRpcM::messageSubtype).id, "zeModuleCreate"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeModuleDestroyRpcM::messageSubtype).id, "zeModuleDestroy"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeModuleBuildLogDestroyRpcM::messageSubtype).id, "zeModuleBuildLogDestroy"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeModuleBuildLogGetStringRpcM::messageSubtype).id, "zeModuleBuildLogGetString"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeModuleGetGlobalPointerRpcM::messageSubtype).id, "zeModuleGetGlobalPointer"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeModuleGetKernelNamesRpcHelperRpcM::messageSubtype).id, "zeModuleGetKernelNamesRpcHelper"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeModuleGetPropertiesRpcM::messageSubtype).id, "zeModuleGetProperties"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeKernelCreateRpcM::messageSubtype).id, "zeKernelCreate"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeKernelDestroyRpcM::messageSubtype).id, "zeKernelDestroy"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeModuleGetFunctionPointerRpcM::messageSubtype).id, "zeModuleGetFunctionPointer"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeKernelSetGroupSizeRpcM::messageSubtype).id, "zeKernelSetGroupSize"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeKernelSuggestGroupSizeRpcM::messageSubtype).id, "zeKernelSuggestGroupSize"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeKernelSuggestMaxCooperativeGroupCountRpcM::messageSubtype).id, "zeKernelSuggestMaxCooperativeGroupCount"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeKernelSetArgumentValueRpcM::messageSubtype).id, "zeKernelSetArgumentValue"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeKernelSetIndirectAccessRpcM::messageSubtype).id, "zeKernelSetIndirectAccess"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeKernelGetIndirectAccessRpcM::messageSubtype).id, "zeKernelGetIndirectAccess"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeKernelSetCacheConfigRpcM::messageSubtype).id, "zeKernelSetCacheConfig"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeKernelGetPropertiesRpcM::messageSubtype).id, "zeKernelGetProperties"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeKernelGetNameRpcM::messageSubtype).id, "zeKernelGetName"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeCommandListAppendLaunchKernelRpcM::messageSubtype).id, "zeCommandListAppendLaunchKernel"),
    };

    auto it = options.find(callId.id);
    if(it == options.end()) {
        return "UNKNOWN";
    }
    return it->second.c_str();
}

inline auto getRpcCallId(const std::string &funcName) {
    using RetT = RpcCallId;
    static const std::unordered_map<std::string, RetT> options = {
        std::pair<std::string, RetT>("zeInit", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeInitRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeCommandListCreate", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeCommandListCreateRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeCommandListCreateImmediate", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeCommandListCreateImmediateRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeCommandListDestroy", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeCommandListDestroyRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeCommandListClose", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeCommandListCloseRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeCommandListReset", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeCommandListResetRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeCommandQueueCreate", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeCommandQueueCreateRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeCommandQueueDestroy", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeCommandQueueDestroyRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeCommandQueueExecuteCommandLists", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeCommandQueueExecuteCommandListsRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeCommandQueueExecuteCommandListsCopySourceMemoryRpcHelper", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeCommandQueueExecuteCommandListsCopySourceMemoryRpcHelperRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeCommandQueueSynchronize", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeCommandQueueSynchronizeRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeContextCreate", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeContextCreateRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeContextDestroy", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeContextDestroyRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeContextGetStatus", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeContextGetStatusRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeCommandListAppendMemoryCopyRpcHelperUsm2Usm", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeCommandListAppendMemoryCopyRpcHelperUsm2UsmRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeCommandListAppendMemoryCopyRpcHelperMalloc2Usm", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeCommandListAppendMemoryCopyRpcHelperMalloc2UsmRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeCommandListAppendMemoryFillRpcHelperUsm2Usm", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeCommandListAppendMemoryFillRpcHelperUsm2UsmRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeCommandListAppendMemoryFillRpcHelperMalloc2Usm", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeCommandListAppendMemoryFillRpcHelperMalloc2UsmRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeDeviceGet", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDeviceGetRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeDeviceGetSubDevices", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDeviceGetSubDevicesRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeDeviceGetProperties", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDeviceGetPropertiesRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeDeviceGetComputeProperties", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDeviceGetComputePropertiesRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeDeviceGetModuleProperties", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDeviceGetModulePropertiesRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeDeviceGetCommandQueueGroupProperties", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDeviceGetCommandQueueGroupPropertiesRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeDeviceGetMemoryProperties", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDeviceGetMemoryPropertiesRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeDeviceGetMemoryAccessProperties", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDeviceGetMemoryAccessPropertiesRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeDeviceGetCacheProperties", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDeviceGetCachePropertiesRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeDeviceGetImageProperties", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDeviceGetImagePropertiesRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeDeviceGetExternalMemoryProperties", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDeviceGetExternalMemoryPropertiesRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeDeviceCanAccessPeer", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDeviceCanAccessPeerRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeDeviceGetStatus", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDeviceGetStatusRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeDeviceGetGlobalTimestamps", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDeviceGetGlobalTimestampsRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeDriverGet", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDriverGetRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeDriverGetApiVersion", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDriverGetApiVersionRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeDriverGetProperties", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDriverGetPropertiesRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeDriverGetIpcProperties", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDriverGetIpcPropertiesRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeDriverGetExtensionProperties", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDriverGetExtensionPropertiesRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeEventPoolCreate", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeEventPoolCreateRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeEventPoolDestroy", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeEventPoolDestroyRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeEventCreate", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeEventCreateRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeEventDestroy", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeEventDestroyRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeCommandListAppendSignalEvent", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeCommandListAppendSignalEventRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeCommandListAppendWaitOnEvents", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeCommandListAppendWaitOnEventsRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeEventHostSynchronize", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeEventHostSynchronizeRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeEventQueryStatus", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeEventQueryStatusRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeEventHostReset", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeEventHostResetRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeEventQueryKernelTimestamp", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeEventQueryKernelTimestampRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeFenceCreate", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeFenceCreateRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeFenceDestroy", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeFenceDestroyRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeFenceHostSynchronize", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeFenceHostSynchronizeRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeFenceQueryStatus", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeFenceQueryStatusRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeFenceReset", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeFenceResetRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeKernelSetGlobalOffsetExp", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeKernelSetGlobalOffsetExpRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeMemAllocShared", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeMemAllocSharedRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeMemAllocDevice", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeMemAllocDeviceRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeMemAllocHost", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeMemAllocHostRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeMemFree", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeMemFreeRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeMemGetAllocProperties", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeMemGetAllocPropertiesRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeModuleCreate", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeModuleCreateRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeModuleDestroy", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeModuleDestroyRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeModuleBuildLogDestroy", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeModuleBuildLogDestroyRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeModuleBuildLogGetString", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeModuleBuildLogGetStringRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeModuleGetGlobalPointer", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeModuleGetGlobalPointerRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeModuleGetKernelNamesRpcHelper", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeModuleGetKernelNamesRpcHelperRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeModuleGetProperties", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeModuleGetPropertiesRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeKernelCreate", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeKernelCreateRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeKernelDestroy", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeKernelDestroyRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeModuleGetFunctionPointer", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeModuleGetFunctionPointerRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeKernelSetGroupSize", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeKernelSetGroupSizeRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeKernelSuggestGroupSize", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeKernelSuggestGroupSizeRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeKernelSuggestMaxCooperativeGroupCount", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeKernelSuggestMaxCooperativeGroupCountRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeKernelSetArgumentValue", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeKernelSetArgumentValueRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeKernelSetIndirectAccess", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeKernelSetIndirectAccessRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeKernelGetIndirectAccess", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeKernelGetIndirectAccessRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeKernelSetCacheConfig", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeKernelSetCacheConfigRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeKernelGetProperties", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeKernelGetPropertiesRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeKernelGetName", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeKernelGetNameRpcM::messageSubtype)),
        std::pair<std::string, RetT>("zeCommandListAppendLaunchKernel", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeCommandListAppendLaunchKernelRpcM::messageSubtype)),
    };

    auto it = options.find(funcName);
    if(it == options.end()) {
        return std::optional<RetT>(std::nullopt);
    }
    return std::optional<RetT>(it->second);
}

namespace RpcCallIds {
static constexpr RpcCallId zeInit = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeInitRpcM::messageSubtype};
static constexpr RpcCallId zeCommandListCreate = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeCommandListCreateRpcM::messageSubtype};
static constexpr RpcCallId zeCommandListCreateImmediate = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeCommandListCreateImmediateRpcM::messageSubtype};
static constexpr RpcCallId zeCommandListDestroy = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeCommandListDestroyRpcM::messageSubtype};
static constexpr RpcCallId zeCommandListClose = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeCommandListCloseRpcM::messageSubtype};
static constexpr RpcCallId zeCommandListReset = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeCommandListResetRpcM::messageSubtype};
static constexpr RpcCallId zeCommandQueueCreate = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeCommandQueueCreateRpcM::messageSubtype};
static constexpr RpcCallId zeCommandQueueDestroy = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeCommandQueueDestroyRpcM::messageSubtype};
static constexpr RpcCallId zeCommandQueueExecuteCommandLists = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeCommandQueueExecuteCommandListsRpcM::messageSubtype};
static constexpr RpcCallId zeCommandQueueExecuteCommandListsCopySourceMemoryRpcHelper = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeCommandQueueExecuteCommandListsCopySourceMemoryRpcHelperRpcM::messageSubtype};
static constexpr RpcCallId zeCommandQueueSynchronize = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeCommandQueueSynchronizeRpcM::messageSubtype};
static constexpr RpcCallId zeContextCreate = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeContextCreateRpcM::messageSubtype};
static constexpr RpcCallId zeContextDestroy = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeContextDestroyRpcM::messageSubtype};
static constexpr RpcCallId zeContextGetStatus = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeContextGetStatusRpcM::messageSubtype};
static constexpr RpcCallId zeCommandListAppendMemoryCopyRpcHelperUsm2Usm = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeCommandListAppendMemoryCopyRpcHelperUsm2UsmRpcM::messageSubtype};
static constexpr RpcCallId zeCommandListAppendMemoryCopyRpcHelperMalloc2Usm = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeCommandListAppendMemoryCopyRpcHelperMalloc2UsmRpcM::messageSubtype};
static constexpr RpcCallId zeCommandListAppendMemoryFillRpcHelperUsm2Usm = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeCommandListAppendMemoryFillRpcHelperUsm2UsmRpcM::messageSubtype};
static constexpr RpcCallId zeCommandListAppendMemoryFillRpcHelperMalloc2Usm = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeCommandListAppendMemoryFillRpcHelperMalloc2UsmRpcM::messageSubtype};
static constexpr RpcCallId zeDeviceGet = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDeviceGetRpcM::messageSubtype};
static constexpr RpcCallId zeDeviceGetSubDevices = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDeviceGetSubDevicesRpcM::messageSubtype};
static constexpr RpcCallId zeDeviceGetProperties = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDeviceGetPropertiesRpcM::messageSubtype};
static constexpr RpcCallId zeDeviceGetComputeProperties = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDeviceGetComputePropertiesRpcM::messageSubtype};
static constexpr RpcCallId zeDeviceGetModuleProperties = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDeviceGetModulePropertiesRpcM::messageSubtype};
static constexpr RpcCallId zeDeviceGetCommandQueueGroupProperties = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDeviceGetCommandQueueGroupPropertiesRpcM::messageSubtype};
static constexpr RpcCallId zeDeviceGetMemoryProperties = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDeviceGetMemoryPropertiesRpcM::messageSubtype};
static constexpr RpcCallId zeDeviceGetMemoryAccessProperties = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDeviceGetMemoryAccessPropertiesRpcM::messageSubtype};
static constexpr RpcCallId zeDeviceGetCacheProperties = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDeviceGetCachePropertiesRpcM::messageSubtype};
static constexpr RpcCallId zeDeviceGetImageProperties = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDeviceGetImagePropertiesRpcM::messageSubtype};
static constexpr RpcCallId zeDeviceGetExternalMemoryProperties = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDeviceGetExternalMemoryPropertiesRpcM::messageSubtype};
static constexpr RpcCallId zeDeviceCanAccessPeer = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDeviceCanAccessPeerRpcM::messageSubtype};
static constexpr RpcCallId zeDeviceGetStatus = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDeviceGetStatusRpcM::messageSubtype};
static constexpr RpcCallId zeDeviceGetGlobalTimestamps = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDeviceGetGlobalTimestampsRpcM::messageSubtype};
static constexpr RpcCallId zeDriverGet = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDriverGetRpcM::messageSubtype};
static constexpr RpcCallId zeDriverGetApiVersion = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDriverGetApiVersionRpcM::messageSubtype};
static constexpr RpcCallId zeDriverGetProperties = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDriverGetPropertiesRpcM::messageSubtype};
static constexpr RpcCallId zeDriverGetIpcProperties = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDriverGetIpcPropertiesRpcM::messageSubtype};
static constexpr RpcCallId zeDriverGetExtensionProperties = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeDriverGetExtensionPropertiesRpcM::messageSubtype};
static constexpr RpcCallId zeEventPoolCreate = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeEventPoolCreateRpcM::messageSubtype};
static constexpr RpcCallId zeEventPoolDestroy = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeEventPoolDestroyRpcM::messageSubtype};
static constexpr RpcCallId zeEventCreate = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeEventCreateRpcM::messageSubtype};
static constexpr RpcCallId zeEventDestroy = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeEventDestroyRpcM::messageSubtype};
static constexpr RpcCallId zeCommandListAppendSignalEvent = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeCommandListAppendSignalEventRpcM::messageSubtype};
static constexpr RpcCallId zeCommandListAppendWaitOnEvents = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeCommandListAppendWaitOnEventsRpcM::messageSubtype};
static constexpr RpcCallId zeEventHostSynchronize = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeEventHostSynchronizeRpcM::messageSubtype};
static constexpr RpcCallId zeEventQueryStatus = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeEventQueryStatusRpcM::messageSubtype};
static constexpr RpcCallId zeEventHostReset = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeEventHostResetRpcM::messageSubtype};
static constexpr RpcCallId zeEventQueryKernelTimestamp = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeEventQueryKernelTimestampRpcM::messageSubtype};
static constexpr RpcCallId zeFenceCreate = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeFenceCreateRpcM::messageSubtype};
static constexpr RpcCallId zeFenceDestroy = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeFenceDestroyRpcM::messageSubtype};
static constexpr RpcCallId zeFenceHostSynchronize = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeFenceHostSynchronizeRpcM::messageSubtype};
static constexpr RpcCallId zeFenceQueryStatus = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeFenceQueryStatusRpcM::messageSubtype};
static constexpr RpcCallId zeFenceReset = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeFenceResetRpcM::messageSubtype};
static constexpr RpcCallId zeKernelSetGlobalOffsetExp = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeKernelSetGlobalOffsetExpRpcM::messageSubtype};
static constexpr RpcCallId zeMemAllocShared = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeMemAllocSharedRpcM::messageSubtype};
static constexpr RpcCallId zeMemAllocDevice = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeMemAllocDeviceRpcM::messageSubtype};
static constexpr RpcCallId zeMemAllocHost = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeMemAllocHostRpcM::messageSubtype};
static constexpr RpcCallId zeMemFree = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeMemFreeRpcM::messageSubtype};
static constexpr RpcCallId zeMemGetAllocProperties = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeMemGetAllocPropertiesRpcM::messageSubtype};
static constexpr RpcCallId zeModuleCreate = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeModuleCreateRpcM::messageSubtype};
static constexpr RpcCallId zeModuleDestroy = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeModuleDestroyRpcM::messageSubtype};
static constexpr RpcCallId zeModuleBuildLogDestroy = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeModuleBuildLogDestroyRpcM::messageSubtype};
static constexpr RpcCallId zeModuleBuildLogGetString = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeModuleBuildLogGetStringRpcM::messageSubtype};
static constexpr RpcCallId zeModuleGetGlobalPointer = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeModuleGetGlobalPointerRpcM::messageSubtype};
static constexpr RpcCallId zeModuleGetKernelNamesRpcHelper = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeModuleGetKernelNamesRpcHelperRpcM::messageSubtype};
static constexpr RpcCallId zeModuleGetProperties = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeModuleGetPropertiesRpcM::messageSubtype};
static constexpr RpcCallId zeKernelCreate = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeKernelCreateRpcM::messageSubtype};
static constexpr RpcCallId zeKernelDestroy = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeKernelDestroyRpcM::messageSubtype};
static constexpr RpcCallId zeModuleGetFunctionPointer = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeModuleGetFunctionPointerRpcM::messageSubtype};
static constexpr RpcCallId zeKernelSetGroupSize = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeKernelSetGroupSizeRpcM::messageSubtype};
static constexpr RpcCallId zeKernelSuggestGroupSize = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeKernelSuggestGroupSizeRpcM::messageSubtype};
static constexpr RpcCallId zeKernelSuggestMaxCooperativeGroupCount = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeKernelSuggestMaxCooperativeGroupCountRpcM::messageSubtype};
static constexpr RpcCallId zeKernelSetArgumentValue = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeKernelSetArgumentValueRpcM::messageSubtype};
static constexpr RpcCallId zeKernelSetIndirectAccess = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeKernelSetIndirectAccessRpcM::messageSubtype};
static constexpr RpcCallId zeKernelGetIndirectAccess = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeKernelGetIndirectAccessRpcM::messageSubtype};
static constexpr RpcCallId zeKernelSetCacheConfig = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeKernelSetCacheConfigRpcM::messageSubtype};
static constexpr RpcCallId zeKernelGetProperties = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeKernelGetPropertiesRpcM::messageSubtype};
static constexpr RpcCallId zeKernelGetName = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeKernelGetNameRpcM::messageSubtype};
static constexpr RpcCallId zeCommandListAppendLaunchKernel = {Cal::Rpc::RpcMessageHeader::messageTypeRpcLevelZero, ZeCommandListAppendLaunchKernelRpcM::messageSubtype};
} // namespace RpcCallIds

namespace RpcCallMessageTypes {
using zeInit = ZeInitRpcM;
using zeCommandListCreate = ZeCommandListCreateRpcM;
using zeCommandListCreateImmediate = ZeCommandListCreateImmediateRpcM;
using zeCommandListDestroy = ZeCommandListDestroyRpcM;
using zeCommandListClose = ZeCommandListCloseRpcM;
using zeCommandListReset = ZeCommandListResetRpcM;
using zeCommandQueueCreate = ZeCommandQueueCreateRpcM;
using zeCommandQueueDestroy = ZeCommandQueueDestroyRpcM;
using zeCommandQueueExecuteCommandLists = ZeCommandQueueExecuteCommandListsRpcM;
using zeCommandQueueExecuteCommandListsCopySourceMemoryRpcHelper = ZeCommandQueueExecuteCommandListsCopySourceMemoryRpcHelperRpcM;
using zeCommandQueueSynchronize = ZeCommandQueueSynchronizeRpcM;
using zeContextCreate = ZeContextCreateRpcM;
using zeContextDestroy = ZeContextDestroyRpcM;
using zeContextGetStatus = ZeContextGetStatusRpcM;
using zeCommandListAppendMemoryCopyRpcHelperUsm2Usm = ZeCommandListAppendMemoryCopyRpcHelperUsm2UsmRpcM;
using zeCommandListAppendMemoryCopyRpcHelperMalloc2Usm = ZeCommandListAppendMemoryCopyRpcHelperMalloc2UsmRpcM;
using zeCommandListAppendMemoryFillRpcHelperUsm2Usm = ZeCommandListAppendMemoryFillRpcHelperUsm2UsmRpcM;
using zeCommandListAppendMemoryFillRpcHelperMalloc2Usm = ZeCommandListAppendMemoryFillRpcHelperMalloc2UsmRpcM;
using zeDeviceGet = ZeDeviceGetRpcM;
using zeDeviceGetSubDevices = ZeDeviceGetSubDevicesRpcM;
using zeDeviceGetProperties = ZeDeviceGetPropertiesRpcM;
using zeDeviceGetComputeProperties = ZeDeviceGetComputePropertiesRpcM;
using zeDeviceGetModuleProperties = ZeDeviceGetModulePropertiesRpcM;
using zeDeviceGetCommandQueueGroupProperties = ZeDeviceGetCommandQueueGroupPropertiesRpcM;
using zeDeviceGetMemoryProperties = ZeDeviceGetMemoryPropertiesRpcM;
using zeDeviceGetMemoryAccessProperties = ZeDeviceGetMemoryAccessPropertiesRpcM;
using zeDeviceGetCacheProperties = ZeDeviceGetCachePropertiesRpcM;
using zeDeviceGetImageProperties = ZeDeviceGetImagePropertiesRpcM;
using zeDeviceGetExternalMemoryProperties = ZeDeviceGetExternalMemoryPropertiesRpcM;
using zeDeviceCanAccessPeer = ZeDeviceCanAccessPeerRpcM;
using zeDeviceGetStatus = ZeDeviceGetStatusRpcM;
using zeDeviceGetGlobalTimestamps = ZeDeviceGetGlobalTimestampsRpcM;
using zeDriverGet = ZeDriverGetRpcM;
using zeDriverGetApiVersion = ZeDriverGetApiVersionRpcM;
using zeDriverGetProperties = ZeDriverGetPropertiesRpcM;
using zeDriverGetIpcProperties = ZeDriverGetIpcPropertiesRpcM;
using zeDriverGetExtensionProperties = ZeDriverGetExtensionPropertiesRpcM;
using zeEventPoolCreate = ZeEventPoolCreateRpcM;
using zeEventPoolDestroy = ZeEventPoolDestroyRpcM;
using zeEventCreate = ZeEventCreateRpcM;
using zeEventDestroy = ZeEventDestroyRpcM;
using zeCommandListAppendSignalEvent = ZeCommandListAppendSignalEventRpcM;
using zeCommandListAppendWaitOnEvents = ZeCommandListAppendWaitOnEventsRpcM;
using zeEventHostSynchronize = ZeEventHostSynchronizeRpcM;
using zeEventQueryStatus = ZeEventQueryStatusRpcM;
using zeEventHostReset = ZeEventHostResetRpcM;
using zeEventQueryKernelTimestamp = ZeEventQueryKernelTimestampRpcM;
using zeFenceCreate = ZeFenceCreateRpcM;
using zeFenceDestroy = ZeFenceDestroyRpcM;
using zeFenceHostSynchronize = ZeFenceHostSynchronizeRpcM;
using zeFenceQueryStatus = ZeFenceQueryStatusRpcM;
using zeFenceReset = ZeFenceResetRpcM;
using zeKernelSetGlobalOffsetExp = ZeKernelSetGlobalOffsetExpRpcM;
using zeMemAllocShared = ZeMemAllocSharedRpcM;
using zeMemAllocDevice = ZeMemAllocDeviceRpcM;
using zeMemAllocHost = ZeMemAllocHostRpcM;
using zeMemFree = ZeMemFreeRpcM;
using zeMemGetAllocProperties = ZeMemGetAllocPropertiesRpcM;
using zeModuleCreate = ZeModuleCreateRpcM;
using zeModuleDestroy = ZeModuleDestroyRpcM;
using zeModuleBuildLogDestroy = ZeModuleBuildLogDestroyRpcM;
using zeModuleBuildLogGetString = ZeModuleBuildLogGetStringRpcM;
using zeModuleGetGlobalPointer = ZeModuleGetGlobalPointerRpcM;
using zeModuleGetKernelNamesRpcHelper = ZeModuleGetKernelNamesRpcHelperRpcM;
using zeModuleGetProperties = ZeModuleGetPropertiesRpcM;
using zeKernelCreate = ZeKernelCreateRpcM;
using zeKernelDestroy = ZeKernelDestroyRpcM;
using zeModuleGetFunctionPointer = ZeModuleGetFunctionPointerRpcM;
using zeKernelSetGroupSize = ZeKernelSetGroupSizeRpcM;
using zeKernelSuggestGroupSize = ZeKernelSuggestGroupSizeRpcM;
using zeKernelSuggestMaxCooperativeGroupCount = ZeKernelSuggestMaxCooperativeGroupCountRpcM;
using zeKernelSetArgumentValue = ZeKernelSetArgumentValueRpcM;
using zeKernelSetIndirectAccess = ZeKernelSetIndirectAccessRpcM;
using zeKernelGetIndirectAccess = ZeKernelGetIndirectAccessRpcM;
using zeKernelSetCacheConfig = ZeKernelSetCacheConfigRpcM;
using zeKernelGetProperties = ZeKernelGetPropertiesRpcM;
using zeKernelGetName = ZeKernelGetNameRpcM;
using zeCommandListAppendLaunchKernel = ZeCommandListAppendLaunchKernelRpcM;
}

} // namespace LevelZero
} // namespace Rpc
} // namespace Cal
// #### Generated code -- end ####