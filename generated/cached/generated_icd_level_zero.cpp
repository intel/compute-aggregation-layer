/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

// #### Generated code -- begin ####

#include "icd/icd_global_state.h"
#include "shared/rpc.h"
#include "shared/utils.h"

#include "generated_icd_level_zero.h"
#include "generated_rpc_messages_level_zero.h"

#include <cstdlib>
#include <type_traits>

using Cal::Utils::enforceNullWithWarning;
using Cal::Utils::ensureNull;

namespace Cal {
namespace Icd {
namespace LevelZero {
template<typename T>
auto mutable_element_cast(const T *el) {
    auto nonConst = const_cast<T*>(el);
    using NonVoidT = std::conditional_t<std::is_void_v<T>, char*, T*>;
    return reinterpret_cast<NonVoidT>(nonConst);
};

template<typename T>
auto mutable_element_cast(const T **el) {
    auto nonConst = const_cast<T**>(el);
    using NonVoidT = std::conditional_t<std::is_void_v<T>, char**, T**>;
    return reinterpret_cast<NonVoidT>(nonConst);
};

ze_result_t zeInitRpcHelper (ze_init_flags_t flags) {
    log<Verbosity::bloat>("Establishing RPC for zeInit");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeInitRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(flags);

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListCreate (ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_list_desc_t* desc, ze_command_list_handle_t* phCommandList) {
    log<Verbosity::bloat>("Establishing RPC for zeCommandListCreate");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListCreateRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hContext, hDevice, desc, phCommandList);
    command->copyFromCaller();
    command->args.hContext = static_cast<IcdL0Context*>(hContext)->asRemoteObject();
    command->args.hDevice = static_cast<IcdL0Device*>(hDevice)->asRemoteObject();
    if(desc)
    {
        ensureNull("zeCommandListCreate: desc->pNext", desc->pNext);
    }

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller();
    if(phCommandList)
    {
        phCommandList[0] = globalL0Platform->translateNewRemoteObjectToLocalObject(phCommandList[0], IcdL0CommandList::CommandListType::Regular);
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListCreateImmediate (ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_queue_desc_t* altdesc, ze_command_list_handle_t* phCommandList) {
    log<Verbosity::bloat>("Establishing RPC for zeCommandListCreateImmediate");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListCreateImmediateRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hContext, hDevice, altdesc, phCommandList);
    command->copyFromCaller();
    command->args.hContext = static_cast<IcdL0Context*>(hContext)->asRemoteObject();
    command->args.hDevice = static_cast<IcdL0Device*>(hDevice)->asRemoteObject();
    if(altdesc)
    {
        ensureNull("zeCommandListCreateImmediate: altdesc->pNext", altdesc->pNext);
    }

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller();
    if(phCommandList)
    {
        phCommandList[0] = globalL0Platform->translateNewRemoteObjectToLocalObject(phCommandList[0], IcdL0CommandList::selectImmediateType(altdesc));
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListDestroy (ze_command_list_handle_t hCommandList) {
    log<Verbosity::bloat>("Establishing RPC for zeCommandListDestroy");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListDestroyRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hCommandList);
    command->args.hCommandList = static_cast<IcdL0CommandList*>(hCommandList)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    {
        hCommandList->asLocalObject()->dec();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListClose (ze_command_list_handle_t hCommandList) {
    log<Verbosity::bloat>("Establishing RPC for zeCommandListClose");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListCloseRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hCommandList);
    command->args.hCommandList = static_cast<IcdL0CommandList*>(hCommandList)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListReset (ze_command_list_handle_t hCommandList) {
    log<Verbosity::bloat>("Establishing RPC for zeCommandListReset");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListResetRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hCommandList);
    command->args.hCommandList = static_cast<IcdL0CommandList*>(hCommandList)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    {
        hCommandList->asLocalObject()->clearRequiredMemoryTransfers();
    }
    ze_result_t ret = command->captures.ret;

    channelLock.unlock();
    static_cast<IcdL0CommandList*>(hCommandList)->sharedIndirectAccessSet = false;
    return ret;
}
ze_result_t zeCommandQueueCreate (ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_queue_desc_t* desc, ze_command_queue_handle_t* phCommandQueue) {
    log<Verbosity::bloat>("Establishing RPC for zeCommandQueueCreate");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandQueueCreateRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hContext, hDevice, desc, phCommandQueue);
    command->copyFromCaller();
    command->args.hContext = static_cast<IcdL0Context*>(hContext)->asRemoteObject();
    command->args.hDevice = static_cast<IcdL0Device*>(hDevice)->asRemoteObject();
    if(desc)
    {
        ensureNull("zeCommandQueueCreate: desc->pNext", desc->pNext);
    }

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller();
    if(phCommandQueue)
    {
        phCommandQueue[0] = globalL0Platform->translateNewRemoteObjectToLocalObject(phCommandQueue[0], command->args.desc->mode);
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandQueueDestroy (ze_command_queue_handle_t hCommandQueue) {
    log<Verbosity::bloat>("Establishing RPC for zeCommandQueueDestroy");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandQueueDestroyRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hCommandQueue);
    command->args.hCommandQueue = static_cast<IcdL0CommandQueue*>(hCommandQueue)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    {
        hCommandQueue->asLocalObject()->dec();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandQueueExecuteCommandListsRpcHelper (ze_command_queue_handle_t hCommandQueue, uint32_t numCommandLists, ze_command_list_handle_t* phCommandLists, ze_fence_handle_t hFence) {
    log<Verbosity::bloat>("Establishing RPC for zeCommandQueueExecuteCommandLists");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandQueueExecuteCommandListsRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandQueue, numCommandLists, phCommandLists, hFence);
    auto commandSpace = channel.getSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace.get()) CommandT(dynMemTraits, hCommandQueue, numCommandLists, phCommandLists, hFence);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandQueue = static_cast<IcdL0CommandQueue*>(hCommandQueue)->asRemoteObject();
    if(phCommandLists)
    {
        auto base = command->captures.phCommandLists;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phCommandLists.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = static_cast<IcdL0CommandList*>(baseMutable[i])->asRemoteObject();
        }
    }
    if(hFence)
    {
        command->args.hFence = static_cast<IcdL0Fence*>(hFence)->asRemoteObject();
    }

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandQueueExecuteCommandListsCopyMemoryRpcHelper (uint32_t chunksCount, const Cal::Rpc::MemChunk* chunks, uint32_t* transferDescsCount, Cal::Rpc::ShmemTransferDesc* transferDescs) {
    log<Verbosity::bloat>("Establishing RPC for zeCommandQueueExecuteCommandListsCopyMemoryRpcHelper");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandQueueExecuteCommandListsCopyMemoryRpcHelperRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(chunksCount, chunks, transferDescsCount, transferDescs);
    auto commandSpace = channel.getSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace.get()) CommandT(dynMemTraits, chunksCount, chunks, transferDescsCount, transferDescs);
    command->copyFromCaller(dynMemTraits);

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandQueueSynchronizeRpcHelper (ze_command_queue_handle_t hCommandQueue, uint64_t timeout) {
    log<Verbosity::bloat>("Establishing RPC for zeCommandQueueSynchronize");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandQueueSynchronizeRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hCommandQueue, timeout);
    command->args.hCommandQueue = static_cast<IcdL0CommandQueue*>(hCommandQueue)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeContextCreate (ze_driver_handle_t hDriver, const ze_context_desc_t* desc, ze_context_handle_t* phContext) {
    log<Verbosity::bloat>("Establishing RPC for zeContextCreate");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeContextCreateRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hDriver, desc, phContext);
    auto commandSpace = channel.getSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace.get()) CommandT(dynMemTraits, hDriver, desc, phContext);
    command->copyFromCaller(dynMemTraits);
    command->args.hDriver = static_cast<IcdL0Platform*>(hDriver)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    if(phContext)
    {
        phContext[0] = globalL0Platform->translateNewRemoteObjectToLocalObject(phContext[0]);
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeContextCreateEx (ze_driver_handle_t hDriver, const ze_context_desc_t* desc, uint32_t numDevices, ze_device_handle_t* phDevices, ze_context_handle_t* phContext) {
    log<Verbosity::bloat>("Establishing RPC for zeContextCreateEx");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeContextCreateExRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hDriver, desc, numDevices, phDevices, phContext);
    auto commandSpace = channel.getSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace.get()) CommandT(dynMemTraits, hDriver, desc, numDevices, phDevices, phContext);
    command->copyFromCaller(dynMemTraits);
    command->args.hDriver = static_cast<IcdL0Platform*>(hDriver)->asRemoteObject();
    if(phDevices)
    {
        auto base = command->captures.getPhDevices();
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phDevices.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = static_cast<IcdL0Device*>(baseMutable[i])->asRemoteObject();
        }
    }

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    if(phContext)
    {
        phContext[0] = globalL0Platform->translateNewRemoteObjectToLocalObject(phContext[0]);
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeContextDestroy (ze_context_handle_t hContext) {
    log<Verbosity::bloat>("Establishing RPC for zeContextDestroy");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeContextDestroyRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hContext);
    command->args.hContext = static_cast<IcdL0Context*>(hContext)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    {
        hContext->asLocalObject()->dec();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeContextGetStatus (ze_context_handle_t hContext) {
    log<Verbosity::bloat>("Establishing RPC for zeContextGetStatus");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeContextGetStatusRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hContext);
    command->args.hContext = static_cast<IcdL0Context*>(hContext)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
 // zeCommandListAppendMemoryCopy ignored in generator - based on dont_generate_handler flag
ze_result_t zeCommandListAppendMemoryCopyRpcHelperUsm2Usm (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyRpcHelperUsm2Usm");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRpcHelperUsm2UsmRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace.get()) CommandT(dynMemTraits, hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = static_cast<IcdL0CommandList*>(hCommandList)->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = static_cast<IcdL0Event*>(hSignalEvent)->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = static_cast<IcdL0Event*>(baseMutable[i])->asRemoteObject();
        }
    }

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemoryCopyRpcHelperMalloc2Usm (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyRpcHelperMalloc2Usm");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRpcHelperMalloc2UsmRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace.get()) CommandT(dynMemTraits, hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = static_cast<IcdL0CommandList*>(hCommandList)->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = static_cast<IcdL0Event*>(hSignalEvent)->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = static_cast<IcdL0Event*>(baseMutable[i])->asRemoteObject();
        }
    }

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemoryCopyRpcHelperMalloc2UsmImmediate (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyRpcHelperMalloc2UsmImmediate");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRpcHelperMalloc2UsmImmediateRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace.get()) CommandT(dynMemTraits, hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = static_cast<IcdL0CommandList*>(hCommandList)->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = static_cast<IcdL0Event*>(hSignalEvent)->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.getPhWaitEvents();
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = static_cast<IcdL0Event*>(baseMutable[i])->asRemoteObject();
        }
    }

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemoryCopyRpcHelperUsm2MallocImmediateSynchronous (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyRpcHelperUsm2MallocImmediateSynchronous");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRpcHelperUsm2MallocImmediateSynchronousRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace.get()) CommandT(dynMemTraits, hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = static_cast<IcdL0CommandList*>(hCommandList)->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = static_cast<IcdL0Event*>(hSignalEvent)->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.getPhWaitEvents();
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = static_cast<IcdL0Event*>(baseMutable[i])->asRemoteObject();
        }
    }

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemoryCopyRpcHelperMalloc2MallocImmediateSynchronous (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyRpcHelperMalloc2MallocImmediateSynchronous");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRpcHelperMalloc2MallocImmediateSynchronousRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace.get()) CommandT(dynMemTraits, hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = static_cast<IcdL0CommandList*>(hCommandList)->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = static_cast<IcdL0Event*>(hSignalEvent)->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.getPhWaitEvents();
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = static_cast<IcdL0Event*>(baseMutable[i])->asRemoteObject();
        }
    }

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemoryCopyRpcHelperUsm2Malloc (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyRpcHelperUsm2Malloc");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRpcHelperUsm2MallocRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace.get()) CommandT(dynMemTraits, hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = static_cast<IcdL0CommandList*>(hCommandList)->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = static_cast<IcdL0Event*>(hSignalEvent)->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = static_cast<IcdL0Event*>(baseMutable[i])->asRemoteObject();
        }
    }

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemoryCopyRpcHelperMalloc2Malloc (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyRpcHelperMalloc2Malloc");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRpcHelperMalloc2MallocRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace.get()) CommandT(dynMemTraits, hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = static_cast<IcdL0CommandList*>(hCommandList)->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = static_cast<IcdL0Event*>(hSignalEvent)->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = static_cast<IcdL0Event*>(baseMutable[i])->asRemoteObject();
        }
    }

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
 // zeCommandListAppendMemoryFill ignored in generator - based on dont_generate_handler flag
ze_result_t zeCommandListAppendMemoryFillRpcHelperUsm2Usm (ze_command_list_handle_t hCommandList, void* ptr, const void* pattern, size_t pattern_size, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryFillRpcHelperUsm2Usm");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryFillRpcHelperUsm2UsmRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace.get()) CommandT(dynMemTraits, hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = static_cast<IcdL0CommandList*>(hCommandList)->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = static_cast<IcdL0Event*>(hSignalEvent)->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = static_cast<IcdL0Event*>(baseMutable[i])->asRemoteObject();
        }
    }

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemoryFillRpcHelperUsm2Malloc (ze_command_list_handle_t hCommandList, void* ptr, const void* pattern, size_t pattern_size, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryFillRpcHelperUsm2Malloc");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryFillRpcHelperUsm2MallocRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace.get()) CommandT(dynMemTraits, hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = static_cast<IcdL0CommandList*>(hCommandList)->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = static_cast<IcdL0Event*>(hSignalEvent)->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = static_cast<IcdL0Event*>(baseMutable[i])->asRemoteObject();
        }
    }

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemoryFillRpcHelperMalloc2Usm (ze_command_list_handle_t hCommandList, void* ptr, const void* pattern, size_t pattern_size, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryFillRpcHelperMalloc2Usm");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryFillRpcHelperMalloc2UsmRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace.get()) CommandT(dynMemTraits, hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = static_cast<IcdL0CommandList*>(hCommandList)->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = static_cast<IcdL0Event*>(hSignalEvent)->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.getPhWaitEvents();
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = static_cast<IcdL0Event*>(baseMutable[i])->asRemoteObject();
        }
    }

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemoryFillRpcHelperMalloc2Malloc (ze_command_list_handle_t hCommandList, void* ptr, const void* pattern, size_t pattern_size, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryFillRpcHelperMalloc2Malloc");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryFillRpcHelperMalloc2MallocRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace.get()) CommandT(dynMemTraits, hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = static_cast<IcdL0CommandList*>(hCommandList)->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = static_cast<IcdL0Event*>(hSignalEvent)->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.getPhWaitEvents();
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = static_cast<IcdL0Event*>(baseMutable[i])->asRemoteObject();
        }
    }

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemoryPrefetch (ze_command_list_handle_t hCommandList, const void* ptr, size_t size) {
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryPrefetch");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryPrefetchRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hCommandList, ptr, size);
    command->args.hCommandList = static_cast<IcdL0CommandList*>(hCommandList)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemAdviseRpcHelper (ze_command_list_handle_t hCommandList, ze_device_handle_t hDevice, const void* ptr, size_t size, ze_memory_advice_t advice) {
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemAdvise");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemAdviseRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hCommandList, hDevice, ptr, size, advice);
    command->args.hCommandList = static_cast<IcdL0CommandList*>(hCommandList)->asRemoteObject();
    command->args.hDevice = static_cast<IcdL0Device*>(hDevice)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeDeviceGetRpcHelper (ze_driver_handle_t hDriver, uint32_t* pCount, ze_device_handle_t* phDevices) {
    log<Verbosity::bloat>("Establishing RPC for zeDeviceGet");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeDeviceGetRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hDriver, pCount, phDevices);
    auto commandSpace = channel.getSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace.get()) CommandT(dynMemTraits, hDriver, pCount, phDevices);
    command->copyFromCaller(dynMemTraits);
    command->args.hDriver = static_cast<IcdL0Platform*>(hDriver)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    if(phDevices)
    {
        auto baseMutable = mutable_element_cast(phDevices);

        auto numEntries = command->captures.pCount;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = globalL0Platform->translateNewRemoteObjectToLocalObject(baseMutable[i], hDriver);
        }
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeDeviceGetSubDevicesRpcHelper (ze_device_handle_t hDevice, uint32_t* pCount, ze_device_handle_t* phSubdevices) {
    log<Verbosity::bloat>("Establishing RPC for zeDeviceGetSubDevices");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeDeviceGetSubDevicesRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hDevice, pCount, phSubdevices);
    auto commandSpace = channel.getSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace.get()) CommandT(dynMemTraits, hDevice, pCount, phSubdevices);
    command->copyFromCaller(dynMemTraits);
    command->args.hDevice = static_cast<IcdL0Device*>(hDevice)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    if(phSubdevices)
    {
        auto baseMutable = mutable_element_cast(phSubdevices);

        auto numEntries = command->captures.pCount;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = globalL0Platform->translateNewRemoteObjectToLocalObject(baseMutable[i], hDevice);
        }
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeDeviceGetPropertiesRpcHelper (ze_device_handle_t hDevice, ze_device_properties_t* pDeviceProperties) {
    log<Verbosity::bloat>("Establishing RPC for zeDeviceGetProperties");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeDeviceGetPropertiesRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hDevice, pDeviceProperties);
    auto commandSpace = channel.getSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace.get()) CommandT(dynMemTraits, hDevice, pDeviceProperties);
    command->copyFromCaller(dynMemTraits);
    command->args.hDevice = static_cast<IcdL0Device*>(hDevice)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    if(pDeviceProperties)
    {
        command->captures.ret = static_cast<IcdL0Device*>(hDevice)->patchDeviceName(*pDeviceProperties) ? command->captures.ret : ZE_RESULT_ERROR_DEVICE_LOST;
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeDeviceGetComputePropertiesRpcHelper (ze_device_handle_t hDevice, ze_device_compute_properties_t* pComputeProperties) {
    log<Verbosity::bloat>("Establishing RPC for zeDeviceGetComputeProperties");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeDeviceGetComputePropertiesRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hDevice, pComputeProperties);
    command->copyFromCaller();
    command->args.hDevice = static_cast<IcdL0Device*>(hDevice)->asRemoteObject();
    if(pComputeProperties)
    {
        ensureNull("zeDeviceGetComputeProperties: pComputeProperties->pNext", pComputeProperties->pNext);
    }

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller();
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeDeviceGetModulePropertiesRpcHelper (ze_device_handle_t hDevice, ze_device_module_properties_t* pModuleProperties) {
    log<Verbosity::bloat>("Establishing RPC for zeDeviceGetModuleProperties");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeDeviceGetModulePropertiesRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hDevice, pModuleProperties);
    auto commandSpace = channel.getSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace.get()) CommandT(dynMemTraits, hDevice, pModuleProperties);
    command->copyFromCaller(dynMemTraits);
    command->args.hDevice = static_cast<IcdL0Device*>(hDevice)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeDeviceGetCommandQueueGroupPropertiesRpcHelper (ze_device_handle_t hDevice, uint32_t* pCount, ze_command_queue_group_properties_t* pCommandQueueGroupProperties) {
    log<Verbosity::bloat>("Establishing RPC for zeDeviceGetCommandQueueGroupProperties");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeDeviceGetCommandQueueGroupPropertiesRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hDevice, pCount, pCommandQueueGroupProperties);
    auto commandSpace = channel.getSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace.get()) CommandT(dynMemTraits, hDevice, pCount, pCommandQueueGroupProperties);
    command->copyFromCaller(dynMemTraits);
    command->args.hDevice = static_cast<IcdL0Device*>(hDevice)->asRemoteObject();
    if(pCommandQueueGroupProperties)
    {
        auto base = command->captures.pCommandQueueGroupProperties;
        [[maybe_unused]] auto baseMutable = mutable_element_cast(base);
        auto numEntries = (pCount ? *pCount : 0);

        for(size_t i = 0; i < numEntries; ++i){
            enforceNullWithWarning("zeDeviceGetCommandQueueGroupProperties: pCommandQueueGroupProperties[i].pNext", baseMutable[i].pNext);
        }
    }

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeDeviceGetMemoryPropertiesRpcHelper (ze_device_handle_t hDevice, uint32_t* pCount, ze_device_memory_properties_t* pMemProperties) {
    log<Verbosity::bloat>("Establishing RPC for zeDeviceGetMemoryProperties");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeDeviceGetMemoryPropertiesRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hDevice, pCount, pMemProperties);
    auto commandSpace = channel.getSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace.get()) CommandT(dynMemTraits, hDevice, pCount, pMemProperties);
    command->copyFromCaller(dynMemTraits);
    command->args.hDevice = static_cast<IcdL0Device*>(hDevice)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeDeviceGetMemoryAccessPropertiesRpcHelper (ze_device_handle_t hDevice, ze_device_memory_access_properties_t* pMemAccessProperties) {
    log<Verbosity::bloat>("Establishing RPC for zeDeviceGetMemoryAccessProperties");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeDeviceGetMemoryAccessPropertiesRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hDevice, pMemAccessProperties);
    command->copyFromCaller();
    command->args.hDevice = static_cast<IcdL0Device*>(hDevice)->asRemoteObject();
    if(pMemAccessProperties)
    {
        ensureNull("zeDeviceGetMemoryAccessProperties: pMemAccessProperties->pNext", pMemAccessProperties->pNext);
    }

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller();
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeDeviceGetCachePropertiesRpcHelper (ze_device_handle_t hDevice, uint32_t* pCount, ze_device_cache_properties_t* pCacheProperties) {
    log<Verbosity::bloat>("Establishing RPC for zeDeviceGetCacheProperties");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeDeviceGetCachePropertiesRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hDevice, pCount, pCacheProperties);
    auto commandSpace = channel.getSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace.get()) CommandT(dynMemTraits, hDevice, pCount, pCacheProperties);
    command->copyFromCaller(dynMemTraits);
    command->args.hDevice = static_cast<IcdL0Device*>(hDevice)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeDeviceGetImagePropertiesRpcHelper (ze_device_handle_t hDevice, ze_device_image_properties_t* pImageProperties) {
    log<Verbosity::bloat>("Establishing RPC for zeDeviceGetImageProperties");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeDeviceGetImagePropertiesRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hDevice, pImageProperties);
    command->copyFromCaller();
    command->args.hDevice = static_cast<IcdL0Device*>(hDevice)->asRemoteObject();
    if(pImageProperties)
    {
        ensureNull("zeDeviceGetImageProperties: pImageProperties->pNext", pImageProperties->pNext);
    }

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller();
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeDeviceGetExternalMemoryPropertiesRpcHelper (ze_device_handle_t hDevice, ze_device_external_memory_properties_t* pExternalMemoryProperties) {
    log<Verbosity::bloat>("Establishing RPC for zeDeviceGetExternalMemoryProperties");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeDeviceGetExternalMemoryPropertiesRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hDevice, pExternalMemoryProperties);
    command->copyFromCaller();
    command->args.hDevice = static_cast<IcdL0Device*>(hDevice)->asRemoteObject();
    if(pExternalMemoryProperties)
    {
        ensureNull("zeDeviceGetExternalMemoryProperties: pExternalMemoryProperties->pNext", pExternalMemoryProperties->pNext);
    }

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller();
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeDeviceGetP2PProperties (ze_device_handle_t hDevice, ze_device_handle_t hPeerDevice, ze_device_p2p_properties_t* pP2PProperties) {
    log<Verbosity::bloat>("Establishing RPC for zeDeviceGetP2PProperties");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeDeviceGetP2PPropertiesRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hDevice, hPeerDevice, pP2PProperties);
    auto commandSpace = channel.getSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace.get()) CommandT(dynMemTraits, hDevice, hPeerDevice, pP2PProperties);
    command->copyFromCaller(dynMemTraits);
    command->args.hDevice = static_cast<IcdL0Device*>(hDevice)->asRemoteObject();
    command->args.hPeerDevice = static_cast<IcdL0Device*>(hPeerDevice)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeDeviceCanAccessPeer (ze_device_handle_t hDevice, ze_device_handle_t hPeerDevice, ze_bool_t* value) {
    log<Verbosity::bloat>("Establishing RPC for zeDeviceCanAccessPeer");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeDeviceCanAccessPeerRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hDevice, hPeerDevice, value);
    command->args.hDevice = static_cast<IcdL0Device*>(hDevice)->asRemoteObject();
    command->args.hPeerDevice = static_cast<IcdL0Device*>(hPeerDevice)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller();
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeDeviceGetStatus (ze_device_handle_t hDevice) {
    log<Verbosity::bloat>("Establishing RPC for zeDeviceGetStatus");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeDeviceGetStatusRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hDevice);
    command->args.hDevice = static_cast<IcdL0Device*>(hDevice)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeDeviceGetGlobalTimestamps (ze_device_handle_t hDevice, uint64_t* hostTimestamp, uint64_t* deviceTimestamp) {
    log<Verbosity::bloat>("Establishing RPC for zeDeviceGetGlobalTimestamps");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeDeviceGetGlobalTimestampsRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hDevice, hostTimestamp, deviceTimestamp);
    command->args.hDevice = static_cast<IcdL0Device*>(hDevice)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller();
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeDriverGetRpcHelper (uint32_t* pCount, ze_driver_handle_t* phDrivers) {
    log<Verbosity::bloat>("Establishing RPC for zeDriverGet");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeDriverGetRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(pCount, phDrivers);
    auto commandSpace = channel.getSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace.get()) CommandT(dynMemTraits, pCount, phDrivers);
    command->copyFromCaller(dynMemTraits);

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeDriverGetApiVersion (ze_driver_handle_t hDriver, ze_api_version_t* version) {
    log<Verbosity::bloat>("Establishing RPC for zeDriverGetApiVersion");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeDriverGetApiVersionRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hDriver, version);
    command->args.hDriver = static_cast<IcdL0Platform*>(hDriver)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller();
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeDriverGetPropertiesRpcHelper (ze_driver_handle_t hDriver, ze_driver_properties_t* pDriverProperties) {
    log<Verbosity::bloat>("Establishing RPC for zeDriverGetProperties");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeDriverGetPropertiesRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hDriver, pDriverProperties);
    command->copyFromCaller();
    command->args.hDriver = static_cast<IcdL0Platform*>(hDriver)->asRemoteObject();
    if(pDriverProperties)
    {
        ensureNull("zeDriverGetProperties: pDriverProperties->pNext", pDriverProperties->pNext);
    }

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller();
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeDriverGetIpcPropertiesRpcHelper (ze_driver_handle_t hDriver, ze_driver_ipc_properties_t* pIpcProperties) {
    log<Verbosity::bloat>("Establishing RPC for zeDriverGetIpcProperties");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeDriverGetIpcPropertiesRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hDriver, pIpcProperties);
    command->copyFromCaller();
    command->args.hDriver = static_cast<IcdL0Platform*>(hDriver)->asRemoteObject();
    if(pIpcProperties)
    {
        ensureNull("zeDriverGetIpcProperties: pIpcProperties->pNext", pIpcProperties->pNext);
    }

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller();
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeDriverGetExtensionPropertiesRpcHelper (ze_driver_handle_t hDriver, uint32_t* pCount, ze_driver_extension_properties_t* pExtensionProperties) {
    log<Verbosity::bloat>("Establishing RPC for zeDriverGetExtensionProperties");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeDriverGetExtensionPropertiesRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hDriver, pCount, pExtensionProperties);
    auto commandSpace = channel.getSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace.get()) CommandT(dynMemTraits, hDriver, pCount, pExtensionProperties);
    command->copyFromCaller(dynMemTraits);
    command->args.hDriver = static_cast<IcdL0Platform*>(hDriver)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    ze_result_t ret = command->captures.ret;

    return ret;
}
 // zeDriverGetExtensionFunctionAddress ignored in generator - based on dont_generate_handler flag
ze_result_t zeEventPoolCreate (ze_context_handle_t hContext, const ze_event_pool_desc_t* desc, uint32_t numDevices, ze_device_handle_t* phDevices, ze_event_pool_handle_t* phEventPool) {
    log<Verbosity::bloat>("Establishing RPC for zeEventPoolCreate");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeEventPoolCreateRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hContext, desc, numDevices, phDevices, phEventPool);
    auto commandSpace = channel.getSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace.get()) CommandT(dynMemTraits, hContext, desc, numDevices, phDevices, phEventPool);
    command->copyFromCaller(dynMemTraits);
    command->args.hContext = static_cast<IcdL0Context*>(hContext)->asRemoteObject();
    if(desc)
    {
        enforceNullWithWarning("zeEventPoolCreate: desc->pNext", command->captures.desc.pNext);
    }
    if(phDevices)
    {
        auto base = command->captures.phDevices;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phDevices.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = static_cast<IcdL0Device*>(baseMutable[i])->asRemoteObject();
        }
    }

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    if(phEventPool)
    {
        phEventPool[0] = globalL0Platform->translateNewRemoteObjectToLocalObject(phEventPool[0]);
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeEventPoolDestroy (ze_event_pool_handle_t hEventPool) {
    log<Verbosity::bloat>("Establishing RPC for zeEventPoolDestroy");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeEventPoolDestroyRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hEventPool);
    command->args.hEventPool = static_cast<IcdL0EventPool*>(hEventPool)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    {
        hEventPool->asLocalObject()->dec();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeEventCreate (ze_event_pool_handle_t hEventPool, const ze_event_desc_t* desc, ze_event_handle_t* phEvent) {
    log<Verbosity::bloat>("Establishing RPC for zeEventCreate");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeEventCreateRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hEventPool, desc, phEvent);
    command->copyFromCaller();
    command->args.hEventPool = static_cast<IcdL0EventPool*>(hEventPool)->asRemoteObject();
    if(desc)
    {
        ensureNull("zeEventCreate: desc->pNext", desc->pNext);
    }

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller();
    if(phEvent)
    {
        phEvent[0] = globalL0Platform->translateNewRemoteObjectToLocalObject(phEvent[0]);
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeEventDestroy (ze_event_handle_t hEvent) {
    log<Verbosity::bloat>("Establishing RPC for zeEventDestroy");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeEventDestroyRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hEvent);
    command->args.hEvent = static_cast<IcdL0Event*>(hEvent)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    {
        hEvent->asLocalObject()->dec();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeEventPoolGetIpcHandleRpcHelper (ze_event_pool_handle_t hEventPool, ze_ipc_event_pool_handle_t* phIpc) {
    log<Verbosity::bloat>("Establishing RPC for zeEventPoolGetIpcHandle");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeEventPoolGetIpcHandleRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hEventPool, phIpc);
    command->args.hEventPool = static_cast<IcdL0EventPool*>(hEventPool)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller();
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeEventPoolOpenIpcHandleRpcHelper (ze_context_handle_t hContext, ze_ipc_event_pool_handle_t hIpc, ze_event_pool_handle_t* phEventPool) {
    log<Verbosity::bloat>("Establishing RPC for zeEventPoolOpenIpcHandle");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeEventPoolOpenIpcHandleRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hContext, hIpc, phEventPool);
    command->args.hContext = static_cast<IcdL0Context*>(hContext)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller();
    if(phEventPool)
    {
        phEventPool[0] = globalL0Platform->translateNewRemoteObjectToLocalObject(phEventPool[0]);
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeEventPoolCloseIpcHandle (ze_event_pool_handle_t hEventPool) {
    log<Verbosity::bloat>("Establishing RPC for zeEventPoolCloseIpcHandle");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeEventPoolCloseIpcHandleRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hEventPool);
    command->args.hEventPool = static_cast<IcdL0EventPool*>(hEventPool)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    {
        hEventPool->asLocalObject()->dec();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendBarrier (ze_command_list_handle_t hCommandList, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    static_cast<IcdL0Event*>(hSignalEvent)->setAllowIcdState(hCommandList);
    for (uint32_t i = 0; i < numWaitEvents; ++i) {
        static_cast<IcdL0Event*>(phWaitEvents[i])->setAllowIcdState(hCommandList);
    }
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendBarrier");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendBarrierRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace.get()) CommandT(dynMemTraits, hCommandList, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = static_cast<IcdL0CommandList*>(hCommandList)->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = static_cast<IcdL0Event*>(hSignalEvent)->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = static_cast<IcdL0Event*>(baseMutable[i])->asRemoteObject();
        }
    }

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendSignalEvent (ze_command_list_handle_t hCommandList, ze_event_handle_t hEvent) {
    static_cast<IcdL0Event*>(hEvent)->setAllowIcdState(hCommandList);
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendSignalEvent");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendSignalEventRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hCommandList, hEvent);
    command->args.hCommandList = static_cast<IcdL0CommandList*>(hCommandList)->asRemoteObject();
    if(hEvent)
    {
        command->args.hEvent = static_cast<IcdL0Event*>(hEvent)->asRemoteObject();
    }

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendWaitOnEvents (ze_command_list_handle_t hCommandList, uint32_t numEvents, ze_event_handle_t* phEvents) {
    for (uint32_t i = 0; i < numEvents; ++i) {
        static_cast<IcdL0Event*>(phEvents[i])->setAllowIcdState(hCommandList);
    }
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendWaitOnEvents");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendWaitOnEventsRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, numEvents, phEvents);
    auto commandSpace = channel.getSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace.get()) CommandT(dynMemTraits, hCommandList, numEvents, phEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = static_cast<IcdL0CommandList*>(hCommandList)->asRemoteObject();
    if(phEvents)
    {
        auto base = command->captures.phEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = static_cast<IcdL0Event*>(baseMutable[i])->asRemoteObject();
        }
    }

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeEventHostSignal (ze_event_handle_t hEvent) {
    log<Verbosity::bloat>("Establishing RPC for zeEventHostSignal");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeEventHostSignalRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hEvent);
    command->args.hEvent = static_cast<IcdL0Event*>(hEvent)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeEventHostSynchronizeRpcHelper (ze_event_handle_t hEvent, uint64_t timeout) {
    if (static_cast<IcdL0Event*>(hEvent)->isSignaled()) {
        return ZE_RESULT_SUCCESS;
    }
    log<Verbosity::bloat>("Establishing RPC for zeEventHostSynchronize");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeEventHostSynchronizeRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hEvent, timeout);
    command->args.hEvent = static_cast<IcdL0Event*>(hEvent)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    channelLock.unlock();
    if (ret == ZE_RESULT_SUCCESS) {
        static_cast<IcdL0Event*>(hEvent)->signal();
    }
    return ret;
}
ze_result_t zeEventQueryStatus (ze_event_handle_t hEvent) {
    if (static_cast<IcdL0Event*>(hEvent)->isSignaled()) {
        return ZE_RESULT_SUCCESS;
    }
    log<Verbosity::bloat>("Establishing RPC for zeEventQueryStatus");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeEventQueryStatusRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hEvent);
    command->args.hEvent = static_cast<IcdL0Event*>(hEvent)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    channelLock.unlock();
    if (ret == ZE_RESULT_SUCCESS) {
        static_cast<IcdL0Event*>(hEvent)->signal();
    }
    return ret;
}
ze_result_t zeCommandListAppendEventReset (ze_command_list_handle_t hCommandList, ze_event_handle_t hEvent) {
    static_cast<IcdL0Event*>(hEvent)->setAllowIcdState(hCommandList);
    if (static_cast<IcdL0Event*>(hEvent)->isCleared()) {
        return ZE_RESULT_SUCCESS;
    }
    static_cast<IcdL0Event*>(hEvent)->clear();

    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendEventReset");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendEventResetRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hCommandList, hEvent);
    command->args.hCommandList = static_cast<IcdL0CommandList*>(hCommandList)->asRemoteObject();
    command->args.hEvent = static_cast<IcdL0Event*>(hEvent)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeEventHostReset (ze_event_handle_t hEvent) {
    if (static_cast<IcdL0Event*>(hEvent)->isCleared()) {
        return ZE_RESULT_SUCCESS;
    }
    static_cast<IcdL0Event*>(hEvent)->clear();
    log<Verbosity::bloat>("Establishing RPC for zeEventHostReset");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeEventHostResetRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hEvent);
    command->args.hEvent = static_cast<IcdL0Event*>(hEvent)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeEventQueryKernelTimestamp (ze_event_handle_t hEvent, ze_kernel_timestamp_result_t* dstptr) {
    if (static_cast<IcdL0Event*>(hEvent)->isTimestamp()) {
        static_cast<IcdL0Event*>(hEvent)->getTimestamp(dstptr);
        return ZE_RESULT_SUCCESS;
    }
    log<Verbosity::bloat>("Establishing RPC for zeEventQueryKernelTimestamp");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeEventQueryKernelTimestampRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hEvent, dstptr);
    command->args.hEvent = static_cast<IcdL0Event*>(hEvent)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller();
    ze_result_t ret = command->captures.ret;

    channelLock.unlock();
    if (ret == ZE_RESULT_SUCCESS) {
        static_cast<IcdL0Event*>(hEvent)->storeTimestamp(dstptr);
    }
    return ret;
}
ze_result_t zeFenceCreate (ze_command_queue_handle_t hCommandQueue, const ze_fence_desc_t* desc, ze_fence_handle_t* phFence) {
    log<Verbosity::bloat>("Establishing RPC for zeFenceCreate");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeFenceCreateRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hCommandQueue, desc, phFence);
    command->copyFromCaller();
    command->args.hCommandQueue = static_cast<IcdL0CommandQueue*>(hCommandQueue)->asRemoteObject();
    if(desc)
    {
        ensureNull("zeFenceCreate: desc->pNext", desc->pNext);
    }

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller();
    if(phFence)
    {
        phFence[0] = globalL0Platform->translateNewRemoteObjectToLocalObject(phFence[0], hCommandQueue);
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeFenceDestroy (ze_fence_handle_t hFence) {
    log<Verbosity::bloat>("Establishing RPC for zeFenceDestroy");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeFenceDestroyRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hFence);
    command->args.hFence = static_cast<IcdL0Fence*>(hFence)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    {
        hFence->asLocalObject()->dec();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeFenceHostSynchronizeRpcHelper (ze_fence_handle_t hFence, uint64_t timeout) {
    log<Verbosity::bloat>("Establishing RPC for zeFenceHostSynchronize");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeFenceHostSynchronizeRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hFence, timeout);
    command->args.hFence = static_cast<IcdL0Fence*>(hFence)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeFenceQueryStatus (ze_fence_handle_t hFence) {
    log<Verbosity::bloat>("Establishing RPC for zeFenceQueryStatus");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeFenceQueryStatusRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hFence);
    command->args.hFence = static_cast<IcdL0Fence*>(hFence)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeFenceReset (ze_fence_handle_t hFence) {
    log<Verbosity::bloat>("Establishing RPC for zeFenceReset");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeFenceResetRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hFence);
    command->args.hFence = static_cast<IcdL0Fence*>(hFence)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    {
        hFence->asLocalObject()->clearExecutedCommandListsPointers();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeKernelSetGlobalOffsetExp (ze_kernel_handle_t hKernel, uint32_t offsetX, uint32_t offsetY, uint32_t offsetZ) {
    log<Verbosity::bloat>("Establishing RPC for zeKernelSetGlobalOffsetExp");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeKernelSetGlobalOffsetExpRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hKernel, offsetX, offsetY, offsetZ);
    command->args.hKernel = static_cast<IcdL0Kernel*>(hKernel)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeImageGetProperties (ze_device_handle_t hDevice, const ze_image_desc_t* desc, ze_image_properties_t* pImageProperties) {
    log<Verbosity::bloat>("Establishing RPC for zeImageGetProperties");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeImageGetPropertiesRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hDevice, desc, pImageProperties);
    auto commandSpace = channel.getSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace.get()) CommandT(dynMemTraits, hDevice, desc, pImageProperties);
    command->copyFromCaller(dynMemTraits);
    command->captures.reassembleNestedStructs();
    command->args.hDevice = static_cast<IcdL0Device*>(hDevice)->asRemoteObject();
    if(desc)
    {
        translateRequiredPNextExtensions(command->captures.desc.pNext);
    }
    if(pImageProperties)
    {
        ensureNull("zeImageGetProperties: pImageProperties->pNext", pImageProperties->pNext);
    }

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeImageCreate (ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_image_desc_t* desc, ze_image_handle_t* phImage) {
    log<Verbosity::bloat>("Establishing RPC for zeImageCreate");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeImageCreateRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hContext, hDevice, desc, phImage);
    auto commandSpace = channel.getSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace.get()) CommandT(dynMemTraits, hContext, hDevice, desc, phImage);
    command->copyFromCaller(dynMemTraits);
    command->captures.reassembleNestedStructs();
    command->args.hContext = static_cast<IcdL0Context*>(hContext)->asRemoteObject();
    command->args.hDevice = static_cast<IcdL0Device*>(hDevice)->asRemoteObject();
    if(desc)
    {
        translateRequiredPNextExtensions(command->captures.desc.pNext);
    }

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    if(phImage)
    {
        phImage[0] = globalL0Platform->translateNewRemoteObjectToLocalObject(phImage[0]);
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeImageDestroy (ze_image_handle_t hImage) {
    log<Verbosity::bloat>("Establishing RPC for zeImageDestroy");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeImageDestroyRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hImage);
    command->args.hImage = static_cast<IcdL0Image*>(hImage)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    {
        hImage->asLocalObject()->dec();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeKernelSchedulingHintExp (ze_kernel_handle_t hKernel, ze_scheduling_hint_exp_desc_t* pHint) {
    log<Verbosity::bloat>("Establishing RPC for zeKernelSchedulingHintExp");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeKernelSchedulingHintExpRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hKernel, pHint);
    command->copyFromCaller();
    command->args.hKernel = static_cast<IcdL0Kernel*>(hKernel)->asRemoteObject();
    if(pHint)
    {
        ensureNull("zeKernelSchedulingHintExp: pHint->pNext", pHint->pNext);
    }

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeMemAllocSharedRpcHelper (ze_context_handle_t hContext, const ze_device_mem_alloc_desc_t* device_desc, const ze_host_mem_alloc_desc_t* host_desc, size_t size, size_t alignment, ze_device_handle_t hDevice, void** pptr, Cal::Rpc::LevelZero::ZeMemAllocSharedRpcM::ImplicitArgs &implArgsForZeMemAllocSharedRpcM) {
    log<Verbosity::bloat>("Establishing RPC for zeMemAllocShared");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeMemAllocSharedRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hContext, device_desc, host_desc, size, alignment, hDevice, pptr);
    auto commandSpace = channel.getSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace.get()) CommandT(dynMemTraits, hContext, device_desc, host_desc, size, alignment, hDevice, pptr);
    command->copyFromCaller(dynMemTraits, implArgsForZeMemAllocSharedRpcM);
    command->captures.reassembleNestedStructs();
    command->args.hContext = static_cast<IcdL0Context*>(hContext)->asRemoteObject();
    if(device_desc)
    {
        translateRequiredPNextExtensions(command->captures.device_desc.pNext);
    }
    if(hDevice)
    {
        command->args.hDevice = static_cast<IcdL0Device*>(hDevice)->asRemoteObject();
    }

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits, implArgsForZeMemAllocSharedRpcM);
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeMemAllocDevice (ze_context_handle_t hContext, const ze_device_mem_alloc_desc_t* device_desc, size_t size, size_t alignment, ze_device_handle_t hDevice, void** pptr) {
    log<Verbosity::bloat>("Establishing RPC for zeMemAllocDevice");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeMemAllocDeviceRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hContext, device_desc, size, alignment, hDevice, pptr);
    auto commandSpace = channel.getSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace.get()) CommandT(dynMemTraits, hContext, device_desc, size, alignment, hDevice, pptr);
    command->copyFromCaller(dynMemTraits);
    command->captures.reassembleNestedStructs();
    command->args.hContext = static_cast<IcdL0Context*>(hContext)->asRemoteObject();
    if(device_desc)
    {
        translateRequiredPNextExtensions(command->captures.device_desc.pNext);
    }
    command->args.hDevice = static_cast<IcdL0Device*>(hDevice)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    if(pptr)
    {
        pptr[0] = globalL0Platform->validateNewUsmDevicePointer(pptr[0], size);
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeMemAllocHostRpcHelper (ze_context_handle_t hContext, const ze_host_mem_alloc_desc_t* host_desc, size_t size, size_t alignment, void** pptr, Cal::Rpc::LevelZero::ZeMemAllocHostRpcM::ImplicitArgs &implArgsForZeMemAllocHostRpcM) {
    log<Verbosity::bloat>("Establishing RPC for zeMemAllocHost");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeMemAllocHostRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hContext, host_desc, size, alignment, pptr);
    auto commandSpace = channel.getSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace.get()) CommandT(dynMemTraits, hContext, host_desc, size, alignment, pptr);
    command->copyFromCaller(dynMemTraits, implArgsForZeMemAllocHostRpcM);
    command->args.hContext = static_cast<IcdL0Context*>(hContext)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits, implArgsForZeMemAllocHostRpcM);
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeMemFree (ze_context_handle_t hContext, void* ptr) {
    Cal::Icd::icdGlobalState.getL0Platform()->getPageFaultManager().unregisterSharedAlloc(ptr);
    Cal::Icd::icdGlobalState.getL0Platform()->invalidateAllKernelArgCaches();
    static_cast<IcdL0Context*>(hContext)->allocPropertiesCache.invalidateAllocPropertiesCache();
    log<Verbosity::bloat>("Establishing RPC for zeMemFree");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeMemFreeRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hContext, ptr);
    command->args.hContext = static_cast<IcdL0Context*>(hContext)->asRemoteObject();
    globalL0Platform->destroyUsmDescriptor(ptr);

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeMemGetAllocPropertiesRpcHelper (ze_context_handle_t hContext, const void* ptr, ze_memory_allocation_properties_t* pMemAllocProperties, ze_device_handle_t* phDevice) {
    log<Verbosity::bloat>("Establishing RPC for zeMemGetAllocProperties");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeMemGetAllocPropertiesRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hContext, ptr, pMemAllocProperties, phDevice);
    auto commandSpace = channel.getSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace.get()) CommandT(dynMemTraits, hContext, ptr, pMemAllocProperties, phDevice);
    command->copyFromCaller(dynMemTraits);
    command->args.hContext = static_cast<IcdL0Context*>(hContext)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    if(phDevice)
    {
        phDevice[0] = globalL0Platform->translateNewRemoteObjectToLocalObject(phDevice[0], static_cast<ze_device_handle_t>(nullptr));
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeMemGetAddressRange (ze_context_handle_t hContext, const void* ptr, void** pBase, size_t* pSize) {
    log<Verbosity::bloat>("Establishing RPC for zeMemGetAddressRange");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeMemGetAddressRangeRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hContext, ptr, pBase, pSize);
    command->args.hContext = static_cast<IcdL0Context*>(hContext)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller();
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeMemGetIpcHandleRpcHelper (ze_context_handle_t hContext, const void* ptr, ze_ipc_mem_handle_t* pIpcHandle) {
    if (!Cal::Icd::icdGlobalState.getL0Platform()->isDeviceUsm(ptr)) {
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;
    }

    log<Verbosity::bloat>("Establishing RPC for zeMemGetIpcHandle");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeMemGetIpcHandleRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hContext, ptr, pIpcHandle);
    command->args.hContext = static_cast<IcdL0Context*>(hContext)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller();
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeMemOpenIpcHandleRpcHelper (ze_context_handle_t hContext, ze_device_handle_t hDevice, ze_ipc_mem_handle_t handle, ze_ipc_memory_flags_t flags, void** pptr) {
    log<Verbosity::bloat>("Establishing RPC for zeMemOpenIpcHandle");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeMemOpenIpcHandleRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hContext, hDevice, handle, flags, pptr);
    command->args.hContext = static_cast<IcdL0Context*>(hContext)->asRemoteObject();
    command->args.hDevice = static_cast<IcdL0Device*>(hDevice)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller();
    if(pptr)
    {
        pptr[0] = globalL0Platform->openUsmDevicePointerFromIpcHandle(hContext, pptr[0]);
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeMemCloseIpcHandle (ze_context_handle_t hContext, const void* ptr) {
    log<Verbosity::bloat>("Establishing RPC for zeMemCloseIpcHandle");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeMemCloseIpcHandleRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hContext, ptr);
    command->args.hContext = static_cast<IcdL0Context*>(hContext)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    {
        globalL0Platform->destroyUsmDescriptor(const_cast<void*>(ptr));
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zexMemGetIpcHandlesRpcHelper (ze_context_handle_t hContext, const void* ptr, uint32_t* numIpcHandles, ze_ipc_mem_handle_t* pIpcHandles) {
    log<Verbosity::bloat>("Establishing RPC for zexMemGetIpcHandles");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZexMemGetIpcHandlesRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hContext, ptr, numIpcHandles, pIpcHandles);
    auto commandSpace = channel.getSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace.get()) CommandT(dynMemTraits, hContext, ptr, numIpcHandles, pIpcHandles);
    command->copyFromCaller(dynMemTraits);
    command->args.hContext = static_cast<IcdL0Context*>(hContext)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zexMemOpenIpcHandlesRpcHelper (ze_context_handle_t hContext, ze_device_handle_t hDevice, uint32_t numIpcHandles, ze_ipc_mem_handle_t* pIpcHandles, ze_ipc_memory_flags_t flags, void** pptr) {
    log<Verbosity::bloat>("Establishing RPC for zexMemOpenIpcHandles");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZexMemOpenIpcHandlesRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hContext, hDevice, numIpcHandles, pIpcHandles, flags, pptr);
    auto commandSpace = channel.getSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace.get()) CommandT(dynMemTraits, hContext, hDevice, numIpcHandles, pIpcHandles, flags, pptr);
    command->copyFromCaller(dynMemTraits);
    command->args.hContext = static_cast<IcdL0Context*>(hContext)->asRemoteObject();
    command->args.hDevice = static_cast<IcdL0Device*>(hDevice)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    if(pptr)
    {
        pptr[0] = globalL0Platform->openUsmDevicePointerFromIpcHandle(hContext, pptr[0]);
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeModuleCreate (ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_module_desc_t* desc, ze_module_handle_t* phModule, ze_module_build_log_handle_t* phBuildLog) {
    log<Verbosity::bloat>("Establishing RPC for zeModuleCreate");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeModuleCreateRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hContext, hDevice, desc, phModule, phBuildLog);
    auto commandSpace = channel.getSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace.get()) CommandT(dynMemTraits, hContext, hDevice, desc, phModule, phBuildLog);
    command->copyFromCaller(dynMemTraits);
    command->args.hContext = static_cast<IcdL0Context*>(hContext)->asRemoteObject();
    command->args.hDevice = static_cast<IcdL0Device*>(hDevice)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    if(phModule)
    {
        phModule[0] = globalL0Platform->translateNewRemoteObjectToLocalObject(phModule[0]);
    }
    if(phBuildLog)
    {
        phBuildLog[0] = globalL0Platform->translateNewRemoteObjectToLocalObject(phBuildLog[0]);
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeModuleDestroy (ze_module_handle_t hModule) {
    log<Verbosity::bloat>("Establishing RPC for zeModuleDestroy");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeModuleDestroyRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hModule);
    command->args.hModule = static_cast<IcdL0Module*>(hModule)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    {
        hModule->asLocalObject()->dec();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeModuleDynamicLink (uint32_t numModules, ze_module_handle_t* phModules, ze_module_build_log_handle_t* phLinkLog) {
    log<Verbosity::bloat>("Establishing RPC for zeModuleDynamicLink");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeModuleDynamicLinkRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(numModules, phModules, phLinkLog);
    auto commandSpace = channel.getSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace.get()) CommandT(dynMemTraits, numModules, phModules, phLinkLog);
    command->copyFromCaller(dynMemTraits);
    if(phModules)
    {
        auto base = command->captures.phModules;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phModules.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = static_cast<IcdL0Module*>(baseMutable[i])->asRemoteObject();
        }
    }

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    if(phLinkLog)
    {
        phLinkLog[0] = globalL0Platform->translateNewRemoteObjectToLocalObject(phLinkLog[0]);
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeModuleBuildLogDestroy (ze_module_build_log_handle_t hModuleBuildLog) {
    log<Verbosity::bloat>("Establishing RPC for zeModuleBuildLogDestroy");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeModuleBuildLogDestroyRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hModuleBuildLog);
    command->args.hModuleBuildLog = static_cast<IcdL0ModuleBuildLog*>(hModuleBuildLog)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    {
        hModuleBuildLog->asLocalObject()->dec();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeModuleBuildLogGetString (ze_module_build_log_handle_t hModuleBuildLog, size_t* pSize, char* pBuildLog) {
    log<Verbosity::bloat>("Establishing RPC for zeModuleBuildLogGetString");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeModuleBuildLogGetStringRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hModuleBuildLog, pSize, pBuildLog);
    auto commandSpace = channel.getSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace.get()) CommandT(dynMemTraits, hModuleBuildLog, pSize, pBuildLog);
    command->copyFromCaller(dynMemTraits);
    command->args.hModuleBuildLog = static_cast<IcdL0ModuleBuildLog*>(hModuleBuildLog)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeModuleGetNativeBinary (ze_module_handle_t hModule, size_t* pSize, uint8_t* pModuleNativeBinary) {
    log<Verbosity::bloat>("Establishing RPC for zeModuleGetNativeBinary");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeModuleGetNativeBinaryRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hModule, pSize, pModuleNativeBinary);
    auto commandSpace = channel.getSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace.get()) CommandT(dynMemTraits, hModule, pSize, pModuleNativeBinary);
    command->copyFromCaller(dynMemTraits);
    command->args.hModule = static_cast<IcdL0Module*>(hModule)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeModuleGetGlobalPointer (ze_module_handle_t hModule, const char* pGlobalName, size_t* pSize, void** pptr) {
    log<Verbosity::bloat>("Establishing RPC for zeModuleGetGlobalPointer");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeModuleGetGlobalPointerRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hModule, pGlobalName, pSize, pptr);
    auto commandSpace = channel.getSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace.get()) CommandT(dynMemTraits, hModule, pGlobalName, pSize, pptr);
    command->copyFromCaller(dynMemTraits);
    command->args.hModule = static_cast<IcdL0Module*>(hModule)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    if(pptr)
    {
        command->captures.ret = static_cast<IcdL0Module*>(hModule)->recordGlobalPointer(*pptr) ? command->captures.ret : ZE_RESULT_ERROR_INVALID_ARGUMENT;
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
 // zeModuleGetKernelNames ignored in generator - based on dont_generate_handler flag
ze_result_t zeModuleGetKernelNamesRpcHelper (ze_module_handle_t hModule, uint32_t* totalLength, char* namesBuffer) {
    log<Verbosity::bloat>("Establishing RPC for zeModuleGetKernelNamesRpcHelper");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeModuleGetKernelNamesRpcHelperRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hModule, totalLength, namesBuffer);
    auto commandSpace = channel.getSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace.get()) CommandT(dynMemTraits, hModule, totalLength, namesBuffer);
    command->copyFromCaller(dynMemTraits);
    command->args.hModule = static_cast<IcdL0Module*>(hModule)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeModuleGetPropertiesRpcHelper (ze_module_handle_t hModule, ze_module_properties_t* pModuleProperties) {
    log<Verbosity::bloat>("Establishing RPC for zeModuleGetProperties");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeModuleGetPropertiesRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hModule, pModuleProperties);
    command->copyFromCaller();
    command->args.hModule = static_cast<IcdL0Module*>(hModule)->asRemoteObject();
    if(pModuleProperties)
    {
        ensureNull("zeModuleGetProperties: pModuleProperties->pNext", pModuleProperties->pNext);
    }

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller();
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeKernelCreate (ze_module_handle_t hModule, const ze_kernel_desc_t* desc, ze_kernel_handle_t* phKernel) {
    log<Verbosity::bloat>("Establishing RPC for zeKernelCreate");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeKernelCreateRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hModule, desc, phKernel);
    auto commandSpace = channel.getSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace.get()) CommandT(dynMemTraits, hModule, desc, phKernel);
    command->copyFromCaller(dynMemTraits);
    command->args.hModule = static_cast<IcdL0Module*>(hModule)->asRemoteObject();
    if(desc)
    {
        ensureNull("zeKernelCreate: desc->pNext", desc->pNext);
    }

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    if(phKernel)
    {
        phKernel[0] = globalL0Platform->translateNewRemoteObjectToLocalObject(phKernel[0]);
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeKernelDestroy (ze_kernel_handle_t hKernel) {
    log<Verbosity::bloat>("Establishing RPC for zeKernelDestroy");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeKernelDestroyRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hKernel);
    command->args.hKernel = static_cast<IcdL0Kernel*>(hKernel)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    {
        hKernel->asLocalObject()->dec();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeModuleGetFunctionPointer (ze_module_handle_t hModule, const char* pFunctionName, void** pfnFunction) {
    log<Verbosity::bloat>("Establishing RPC for zeModuleGetFunctionPointer");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeModuleGetFunctionPointerRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hModule, pFunctionName, pfnFunction);
    auto commandSpace = channel.getSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace.get()) CommandT(dynMemTraits, hModule, pFunctionName, pfnFunction);
    command->copyFromCaller(dynMemTraits);
    command->args.hModule = static_cast<IcdL0Module*>(hModule)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeKernelSetGroupSize (ze_kernel_handle_t hKernel, uint32_t groupSizeX, uint32_t groupSizeY, uint32_t groupSizeZ) {
    log<Verbosity::bloat>("Establishing RPC for zeKernelSetGroupSize");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeKernelSetGroupSizeRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hKernel, groupSizeX, groupSizeY, groupSizeZ);
    command->args.hKernel = static_cast<IcdL0Kernel*>(hKernel)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeKernelSuggestGroupSize (ze_kernel_handle_t hKernel, uint32_t globalSizeX, uint32_t globalSizeY, uint32_t globalSizeZ, uint32_t* groupSizeX, uint32_t* groupSizeY, uint32_t* groupSizeZ) {
    log<Verbosity::bloat>("Establishing RPC for zeKernelSuggestGroupSize");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeKernelSuggestGroupSizeRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hKernel, globalSizeX, globalSizeY, globalSizeZ, groupSizeX, groupSizeY, groupSizeZ);
    command->args.hKernel = static_cast<IcdL0Kernel*>(hKernel)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller();
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeKernelSuggestMaxCooperativeGroupCount (ze_kernel_handle_t hKernel, uint32_t* totalGroupCount) {
    log<Verbosity::bloat>("Establishing RPC for zeKernelSuggestMaxCooperativeGroupCount");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeKernelSuggestMaxCooperativeGroupCountRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hKernel, totalGroupCount);
    command->args.hKernel = static_cast<IcdL0Kernel*>(hKernel)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller();
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeKernelSetArgumentValueRpcHelper (ze_kernel_handle_t hKernel, uint32_t argIndex, size_t argSize, const void* pArgValue) {
    log<Verbosity::bloat>("Establishing RPC for zeKernelSetArgumentValue");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeKernelSetArgumentValueRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hKernel, argIndex, argSize, pArgValue);
    auto commandSpace = channel.getSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace.get()) CommandT(dynMemTraits, hKernel, argIndex, argSize, pArgValue);
    command->copyFromCaller(dynMemTraits);
    command->args.hKernel = static_cast<IcdL0Kernel*>(hKernel)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeKernelSetIndirectAccess (ze_kernel_handle_t hKernel, ze_kernel_indirect_access_flags_t flags) {
    log<Verbosity::bloat>("Establishing RPC for zeKernelSetIndirectAccess");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeKernelSetIndirectAccessRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hKernel, flags);
    command->args.hKernel = static_cast<IcdL0Kernel*>(hKernel)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    channelLock.unlock();
    static_cast<IcdL0Kernel*>(hKernel)->sharedIndirectAccessSet |= (ZE_KERNEL_INDIRECT_ACCESS_FLAG_SHARED & flags);
    return ret;
}
ze_result_t zeKernelGetIndirectAccess (ze_kernel_handle_t hKernel, ze_kernel_indirect_access_flags_t* pFlags) {
    log<Verbosity::bloat>("Establishing RPC for zeKernelGetIndirectAccess");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeKernelGetIndirectAccessRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hKernel, pFlags);
    command->args.hKernel = static_cast<IcdL0Kernel*>(hKernel)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller();
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeKernelSetCacheConfig (ze_kernel_handle_t hKernel, ze_cache_config_flags_t flags) {
    log<Verbosity::bloat>("Establishing RPC for zeKernelSetCacheConfig");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeKernelSetCacheConfigRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hKernel, flags);
    command->args.hKernel = static_cast<IcdL0Kernel*>(hKernel)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeKernelGetPropertiesRpcHelper (ze_kernel_handle_t hKernel, ze_kernel_properties_t* pKernelProperties) {
    log<Verbosity::bloat>("Establishing RPC for zeKernelGetProperties");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeKernelGetPropertiesRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hKernel, pKernelProperties);
    auto commandSpace = channel.getSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace.get()) CommandT(dynMemTraits, hKernel, pKernelProperties);
    command->copyFromCaller(dynMemTraits);
    command->args.hKernel = static_cast<IcdL0Kernel*>(hKernel)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeKernelGetName (ze_kernel_handle_t hKernel, size_t* pSize, char* pName) {
    log<Verbosity::bloat>("Establishing RPC for zeKernelGetName");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeKernelGetNameRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hKernel, pSize, pName);
    auto commandSpace = channel.getSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace.get()) CommandT(dynMemTraits, hKernel, pSize, pName);
    command->copyFromCaller(dynMemTraits);
    command->args.hKernel = static_cast<IcdL0Kernel*>(hKernel)->asRemoteObject();

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendLaunchKernel (ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchFuncArgs, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    static_cast<IcdL0CommandList*>(hCommandList)->sharedIndirectAccessSet |= static_cast<IcdL0Kernel*>(hKernel)->sharedIndirectAccessSet;
    static_cast<IcdL0CommandList*>(hCommandList)->moveKernelArgsToGpu(static_cast<IcdL0Kernel*>(hKernel));
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendLaunchKernel");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendLaunchKernelRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace.get()) CommandT(dynMemTraits, hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = static_cast<IcdL0CommandList*>(hCommandList)->asRemoteObject();
    command->args.hKernel = static_cast<IcdL0Kernel*>(hKernel)->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = static_cast<IcdL0Event*>(hSignalEvent)->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = static_cast<IcdL0Event*>(baseMutable[i])->asRemoteObject();
        }
    }

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    channelLock.unlock();
    if (static_cast<IcdL0CommandList*>(hCommandList)->isImmediate()) { static_cast<IcdL0CommandList*>(hCommandList)->sharedIndirectAccessSet = false; };
    return ret;
}
ze_result_t zeCommandListAppendLaunchKernelIndirect (ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchArgumentsBuffer, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    static_cast<IcdL0CommandList*>(hCommandList)->sharedIndirectAccessSet |= static_cast<IcdL0Kernel*>(hKernel)->sharedIndirectAccessSet;
    static_cast<IcdL0CommandList*>(hCommandList)->moveKernelArgsToGpu(static_cast<IcdL0Kernel*>(hKernel));
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendLaunchKernelIndirect");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendLaunchKernelIndirectRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, hKernel, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace.get()) CommandT(dynMemTraits, hCommandList, hKernel, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = static_cast<IcdL0CommandList*>(hCommandList)->asRemoteObject();
    command->args.hKernel = static_cast<IcdL0Kernel*>(hKernel)->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = static_cast<IcdL0Event*>(hSignalEvent)->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = static_cast<IcdL0Event*>(baseMutable[i])->asRemoteObject();
        }
    }

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    channelLock.unlock();
    if (static_cast<IcdL0CommandList*>(hCommandList)->isImmediate()) { static_cast<IcdL0CommandList*>(hCommandList)->sharedIndirectAccessSet = false; };
    return ret;
}
ze_result_t zeDevicePciGetPropertiesExt (ze_device_handle_t hDevice, ze_pci_ext_properties_t* pPciProperties) {
    log<Verbosity::bloat>("Establishing RPC for zeDevicePciGetPropertiesExt");
    auto *globalL0Platform = Cal::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalL0Platform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeDevicePciGetPropertiesExtRpcM;
    auto commandSpace = channel.getSpace<CommandT>(0);
    auto command = new(commandSpace.get()) CommandT(hDevice, pPciProperties);
    command->copyFromCaller();
    command->args.hDevice = static_cast<IcdL0Device*>(hDevice)->asRemoteObject();
    if(pPciProperties)
    {
        ensureNull("zeDevicePciGetPropertiesExt: pPciProperties->pNext", pPciProperties->pNext);
    }

    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }
    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller();
    ze_result_t ret = command->captures.ret;

    return ret;
}

void *getL0ExtensionFuncionAddressRpcHelper(const char *funcName) {
    if(0 == strcmp("zexMemGetIpcHandles", funcName)) {
        return reinterpret_cast<void*>(Cal::Icd::LevelZero::zexMemGetIpcHandles);
    }
    if(0 == strcmp("zexMemOpenIpcHandles", funcName)) {
        return reinterpret_cast<void*>(Cal::Icd::LevelZero::zexMemOpenIpcHandles);
    }
    return nullptr;
}

} // namespace LevelZero
} // namespace Icd
} // namespace Cal


extern "C" {
ze_result_t zeInit (ze_init_flags_t flags) {
    return Cal::Icd::LevelZero::zeInit(flags);
}
ze_result_t zeCommandListCreate (ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_list_desc_t* desc, ze_command_list_handle_t* phCommandList) {
    return Cal::Icd::LevelZero::zeCommandListCreate(hContext, hDevice, desc, phCommandList);
}
ze_result_t zeCommandListCreateImmediate (ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_queue_desc_t* altdesc, ze_command_list_handle_t* phCommandList) {
    return Cal::Icd::LevelZero::zeCommandListCreateImmediate(hContext, hDevice, altdesc, phCommandList);
}
ze_result_t zeCommandListDestroy (ze_command_list_handle_t hCommandList) {
    return Cal::Icd::LevelZero::zeCommandListDestroy(hCommandList);
}
ze_result_t zeCommandListClose (ze_command_list_handle_t hCommandList) {
    return Cal::Icd::LevelZero::zeCommandListClose(hCommandList);
}
ze_result_t zeCommandListReset (ze_command_list_handle_t hCommandList) {
    return Cal::Icd::LevelZero::zeCommandListReset(hCommandList);
}
ze_result_t zeCommandQueueCreate (ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_queue_desc_t* desc, ze_command_queue_handle_t* phCommandQueue) {
    return Cal::Icd::LevelZero::zeCommandQueueCreate(hContext, hDevice, desc, phCommandQueue);
}
ze_result_t zeCommandQueueDestroy (ze_command_queue_handle_t hCommandQueue) {
    return Cal::Icd::LevelZero::zeCommandQueueDestroy(hCommandQueue);
}
ze_result_t zeCommandQueueExecuteCommandLists (ze_command_queue_handle_t hCommandQueue, uint32_t numCommandLists, ze_command_list_handle_t* phCommandLists, ze_fence_handle_t hFence) {
    return Cal::Icd::LevelZero::zeCommandQueueExecuteCommandLists(hCommandQueue, numCommandLists, phCommandLists, hFence);
}
ze_result_t zeCommandQueueSynchronize (ze_command_queue_handle_t hCommandQueue, uint64_t timeout) {
    return Cal::Icd::LevelZero::zeCommandQueueSynchronize(hCommandQueue, timeout);
}
ze_result_t zeContextCreate (ze_driver_handle_t hDriver, const ze_context_desc_t* desc, ze_context_handle_t* phContext) {
    return Cal::Icd::LevelZero::zeContextCreate(hDriver, desc, phContext);
}
ze_result_t zeContextCreateEx (ze_driver_handle_t hDriver, const ze_context_desc_t* desc, uint32_t numDevices, ze_device_handle_t* phDevices, ze_context_handle_t* phContext) {
    return Cal::Icd::LevelZero::zeContextCreateEx(hDriver, desc, numDevices, phDevices, phContext);
}
ze_result_t zeContextDestroy (ze_context_handle_t hContext) {
    return Cal::Icd::LevelZero::zeContextDestroy(hContext);
}
ze_result_t zeContextGetStatus (ze_context_handle_t hContext) {
    return Cal::Icd::LevelZero::zeContextGetStatus(hContext);
}
ze_result_t zeCommandListAppendMemoryCopy (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    return Cal::Icd::LevelZero::zeCommandListAppendMemoryCopy(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
}
ze_result_t zeCommandListAppendMemoryFill (ze_command_list_handle_t hCommandList, void* ptr, const void* pattern, size_t pattern_size, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    return Cal::Icd::LevelZero::zeCommandListAppendMemoryFill(hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEvents);
}
ze_result_t zeCommandListAppendMemoryPrefetch (ze_command_list_handle_t hCommandList, const void* ptr, size_t size) {
    return Cal::Icd::LevelZero::zeCommandListAppendMemoryPrefetch(hCommandList, ptr, size);
}
ze_result_t zeCommandListAppendMemAdvise (ze_command_list_handle_t hCommandList, ze_device_handle_t hDevice, const void* ptr, size_t size, ze_memory_advice_t advice) {
    return Cal::Icd::LevelZero::zeCommandListAppendMemAdvise(hCommandList, hDevice, ptr, size, advice);
}
ze_result_t zeDeviceGet (ze_driver_handle_t hDriver, uint32_t* pCount, ze_device_handle_t* phDevices) {
    return Cal::Icd::LevelZero::zeDeviceGet(hDriver, pCount, phDevices);
}
ze_result_t zeDeviceGetSubDevices (ze_device_handle_t hDevice, uint32_t* pCount, ze_device_handle_t* phSubdevices) {
    return Cal::Icd::LevelZero::zeDeviceGetSubDevices(hDevice, pCount, phSubdevices);
}
ze_result_t zeDeviceGetProperties (ze_device_handle_t hDevice, ze_device_properties_t* pDeviceProperties) {
    return Cal::Icd::LevelZero::zeDeviceGetProperties(hDevice, pDeviceProperties);
}
ze_result_t zeDeviceGetComputeProperties (ze_device_handle_t hDevice, ze_device_compute_properties_t* pComputeProperties) {
    return Cal::Icd::LevelZero::zeDeviceGetComputeProperties(hDevice, pComputeProperties);
}
ze_result_t zeDeviceGetModuleProperties (ze_device_handle_t hDevice, ze_device_module_properties_t* pModuleProperties) {
    return Cal::Icd::LevelZero::zeDeviceGetModuleProperties(hDevice, pModuleProperties);
}
ze_result_t zeDeviceGetCommandQueueGroupProperties (ze_device_handle_t hDevice, uint32_t* pCount, ze_command_queue_group_properties_t* pCommandQueueGroupProperties) {
    return Cal::Icd::LevelZero::zeDeviceGetCommandQueueGroupProperties(hDevice, pCount, pCommandQueueGroupProperties);
}
ze_result_t zeDeviceGetMemoryProperties (ze_device_handle_t hDevice, uint32_t* pCount, ze_device_memory_properties_t* pMemProperties) {
    return Cal::Icd::LevelZero::zeDeviceGetMemoryProperties(hDevice, pCount, pMemProperties);
}
ze_result_t zeDeviceGetMemoryAccessProperties (ze_device_handle_t hDevice, ze_device_memory_access_properties_t* pMemAccessProperties) {
    return Cal::Icd::LevelZero::zeDeviceGetMemoryAccessProperties(hDevice, pMemAccessProperties);
}
ze_result_t zeDeviceGetCacheProperties (ze_device_handle_t hDevice, uint32_t* pCount, ze_device_cache_properties_t* pCacheProperties) {
    return Cal::Icd::LevelZero::zeDeviceGetCacheProperties(hDevice, pCount, pCacheProperties);
}
ze_result_t zeDeviceGetImageProperties (ze_device_handle_t hDevice, ze_device_image_properties_t* pImageProperties) {
    return Cal::Icd::LevelZero::zeDeviceGetImageProperties(hDevice, pImageProperties);
}
ze_result_t zeDeviceGetExternalMemoryProperties (ze_device_handle_t hDevice, ze_device_external_memory_properties_t* pExternalMemoryProperties) {
    return Cal::Icd::LevelZero::zeDeviceGetExternalMemoryProperties(hDevice, pExternalMemoryProperties);
}
ze_result_t zeDeviceGetP2PProperties (ze_device_handle_t hDevice, ze_device_handle_t hPeerDevice, ze_device_p2p_properties_t* pP2PProperties) {
    return Cal::Icd::LevelZero::zeDeviceGetP2PProperties(hDevice, hPeerDevice, pP2PProperties);
}
ze_result_t zeDeviceCanAccessPeer (ze_device_handle_t hDevice, ze_device_handle_t hPeerDevice, ze_bool_t* value) {
    return Cal::Icd::LevelZero::zeDeviceCanAccessPeer(hDevice, hPeerDevice, value);
}
ze_result_t zeDeviceGetStatus (ze_device_handle_t hDevice) {
    return Cal::Icd::LevelZero::zeDeviceGetStatus(hDevice);
}
ze_result_t zeDeviceGetGlobalTimestamps (ze_device_handle_t hDevice, uint64_t* hostTimestamp, uint64_t* deviceTimestamp) {
    return Cal::Icd::LevelZero::zeDeviceGetGlobalTimestamps(hDevice, hostTimestamp, deviceTimestamp);
}
ze_result_t zeDriverGet (uint32_t* pCount, ze_driver_handle_t* phDrivers) {
    return Cal::Icd::LevelZero::zeDriverGet(pCount, phDrivers);
}
ze_result_t zeDriverGetApiVersion (ze_driver_handle_t hDriver, ze_api_version_t* version) {
    return Cal::Icd::LevelZero::zeDriverGetApiVersion(hDriver, version);
}
ze_result_t zeDriverGetProperties (ze_driver_handle_t hDriver, ze_driver_properties_t* pDriverProperties) {
    return Cal::Icd::LevelZero::zeDriverGetProperties(hDriver, pDriverProperties);
}
ze_result_t zeDriverGetIpcProperties (ze_driver_handle_t hDriver, ze_driver_ipc_properties_t* pIpcProperties) {
    return Cal::Icd::LevelZero::zeDriverGetIpcProperties(hDriver, pIpcProperties);
}
ze_result_t zeDriverGetExtensionProperties (ze_driver_handle_t hDriver, uint32_t* pCount, ze_driver_extension_properties_t* pExtensionProperties) {
    return Cal::Icd::LevelZero::zeDriverGetExtensionProperties(hDriver, pCount, pExtensionProperties);
}
ze_result_t zeDriverGetExtensionFunctionAddress (ze_driver_handle_t hDriver, const char* name, void** ppFunctionAddress) {
    return Cal::Icd::LevelZero::zeDriverGetExtensionFunctionAddress(hDriver, name, ppFunctionAddress);
}
ze_result_t zeEventPoolCreate (ze_context_handle_t hContext, const ze_event_pool_desc_t* desc, uint32_t numDevices, ze_device_handle_t* phDevices, ze_event_pool_handle_t* phEventPool) {
    return Cal::Icd::LevelZero::zeEventPoolCreate(hContext, desc, numDevices, phDevices, phEventPool);
}
ze_result_t zeEventPoolDestroy (ze_event_pool_handle_t hEventPool) {
    return Cal::Icd::LevelZero::zeEventPoolDestroy(hEventPool);
}
ze_result_t zeEventCreate (ze_event_pool_handle_t hEventPool, const ze_event_desc_t* desc, ze_event_handle_t* phEvent) {
    return Cal::Icd::LevelZero::zeEventCreate(hEventPool, desc, phEvent);
}
ze_result_t zeEventDestroy (ze_event_handle_t hEvent) {
    return Cal::Icd::LevelZero::zeEventDestroy(hEvent);
}
ze_result_t zeEventPoolGetIpcHandle (ze_event_pool_handle_t hEventPool, ze_ipc_event_pool_handle_t* phIpc) {
    return Cal::Icd::LevelZero::zeEventPoolGetIpcHandle(hEventPool, phIpc);
}
ze_result_t zeEventPoolOpenIpcHandle (ze_context_handle_t hContext, ze_ipc_event_pool_handle_t hIpc, ze_event_pool_handle_t* phEventPool) {
    return Cal::Icd::LevelZero::zeEventPoolOpenIpcHandle(hContext, hIpc, phEventPool);
}
ze_result_t zeEventPoolCloseIpcHandle (ze_event_pool_handle_t hEventPool) {
    return Cal::Icd::LevelZero::zeEventPoolCloseIpcHandle(hEventPool);
}
ze_result_t zeCommandListAppendBarrier (ze_command_list_handle_t hCommandList, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    return Cal::Icd::LevelZero::zeCommandListAppendBarrier(hCommandList, hSignalEvent, numWaitEvents, phWaitEvents);
}
ze_result_t zeCommandListAppendSignalEvent (ze_command_list_handle_t hCommandList, ze_event_handle_t hEvent) {
    return Cal::Icd::LevelZero::zeCommandListAppendSignalEvent(hCommandList, hEvent);
}
ze_result_t zeCommandListAppendWaitOnEvents (ze_command_list_handle_t hCommandList, uint32_t numEvents, ze_event_handle_t* phEvents) {
    return Cal::Icd::LevelZero::zeCommandListAppendWaitOnEvents(hCommandList, numEvents, phEvents);
}
ze_result_t zeEventHostSignal (ze_event_handle_t hEvent) {
    return Cal::Icd::LevelZero::zeEventHostSignal(hEvent);
}
ze_result_t zeEventHostSynchronize (ze_event_handle_t hEvent, uint64_t timeout) {
    return Cal::Icd::LevelZero::zeEventHostSynchronize(hEvent, timeout);
}
ze_result_t zeEventQueryStatus (ze_event_handle_t hEvent) {
    return Cal::Icd::LevelZero::zeEventQueryStatus(hEvent);
}
ze_result_t zeCommandListAppendEventReset (ze_command_list_handle_t hCommandList, ze_event_handle_t hEvent) {
    return Cal::Icd::LevelZero::zeCommandListAppendEventReset(hCommandList, hEvent);
}
ze_result_t zeEventHostReset (ze_event_handle_t hEvent) {
    return Cal::Icd::LevelZero::zeEventHostReset(hEvent);
}
ze_result_t zeEventQueryKernelTimestamp (ze_event_handle_t hEvent, ze_kernel_timestamp_result_t* dstptr) {
    return Cal::Icd::LevelZero::zeEventQueryKernelTimestamp(hEvent, dstptr);
}
ze_result_t zeFenceCreate (ze_command_queue_handle_t hCommandQueue, const ze_fence_desc_t* desc, ze_fence_handle_t* phFence) {
    return Cal::Icd::LevelZero::zeFenceCreate(hCommandQueue, desc, phFence);
}
ze_result_t zeFenceDestroy (ze_fence_handle_t hFence) {
    return Cal::Icd::LevelZero::zeFenceDestroy(hFence);
}
ze_result_t zeFenceHostSynchronize (ze_fence_handle_t hFence, uint64_t timeout) {
    return Cal::Icd::LevelZero::zeFenceHostSynchronize(hFence, timeout);
}
ze_result_t zeFenceQueryStatus (ze_fence_handle_t hFence) {
    return Cal::Icd::LevelZero::zeFenceQueryStatus(hFence);
}
ze_result_t zeFenceReset (ze_fence_handle_t hFence) {
    return Cal::Icd::LevelZero::zeFenceReset(hFence);
}
ze_result_t zeKernelSetGlobalOffsetExp (ze_kernel_handle_t hKernel, uint32_t offsetX, uint32_t offsetY, uint32_t offsetZ) {
    return Cal::Icd::LevelZero::zeKernelSetGlobalOffsetExp(hKernel, offsetX, offsetY, offsetZ);
}
ze_result_t zeImageGetProperties (ze_device_handle_t hDevice, const ze_image_desc_t* desc, ze_image_properties_t* pImageProperties) {
    return Cal::Icd::LevelZero::zeImageGetProperties(hDevice, desc, pImageProperties);
}
ze_result_t zeImageCreate (ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_image_desc_t* desc, ze_image_handle_t* phImage) {
    return Cal::Icd::LevelZero::zeImageCreate(hContext, hDevice, desc, phImage);
}
ze_result_t zeImageDestroy (ze_image_handle_t hImage) {
    return Cal::Icd::LevelZero::zeImageDestroy(hImage);
}
ze_result_t zeKernelSchedulingHintExp (ze_kernel_handle_t hKernel, ze_scheduling_hint_exp_desc_t* pHint) {
    return Cal::Icd::LevelZero::zeKernelSchedulingHintExp(hKernel, pHint);
}
ze_result_t zeMemAllocShared (ze_context_handle_t hContext, const ze_device_mem_alloc_desc_t* device_desc, const ze_host_mem_alloc_desc_t* host_desc, size_t size, size_t alignment, ze_device_handle_t hDevice, void** pptr) {
    return Cal::Icd::LevelZero::zeMemAllocShared(hContext, device_desc, host_desc, size, alignment, hDevice, pptr);
}
ze_result_t zeMemAllocDevice (ze_context_handle_t hContext, const ze_device_mem_alloc_desc_t* device_desc, size_t size, size_t alignment, ze_device_handle_t hDevice, void** pptr) {
    return Cal::Icd::LevelZero::zeMemAllocDevice(hContext, device_desc, size, alignment, hDevice, pptr);
}
ze_result_t zeMemAllocHost (ze_context_handle_t hContext, const ze_host_mem_alloc_desc_t* host_desc, size_t size, size_t alignment, void** pptr) {
    return Cal::Icd::LevelZero::zeMemAllocHost(hContext, host_desc, size, alignment, pptr);
}
ze_result_t zeMemFree (ze_context_handle_t hContext, void* ptr) {
    return Cal::Icd::LevelZero::zeMemFree(hContext, ptr);
}
ze_result_t zeMemGetAllocProperties (ze_context_handle_t hContext, const void* ptr, ze_memory_allocation_properties_t* pMemAllocProperties, ze_device_handle_t* phDevice) {
    return Cal::Icd::LevelZero::zeMemGetAllocProperties(hContext, ptr, pMemAllocProperties, phDevice);
}
ze_result_t zeMemGetAddressRange (ze_context_handle_t hContext, const void* ptr, void** pBase, size_t* pSize) {
    return Cal::Icd::LevelZero::zeMemGetAddressRange(hContext, ptr, pBase, pSize);
}
ze_result_t zeMemGetIpcHandle (ze_context_handle_t hContext, const void* ptr, ze_ipc_mem_handle_t* pIpcHandle) {
    return Cal::Icd::LevelZero::zeMemGetIpcHandle(hContext, ptr, pIpcHandle);
}
ze_result_t zeMemOpenIpcHandle (ze_context_handle_t hContext, ze_device_handle_t hDevice, ze_ipc_mem_handle_t handle, ze_ipc_memory_flags_t flags, void** pptr) {
    return Cal::Icd::LevelZero::zeMemOpenIpcHandle(hContext, hDevice, handle, flags, pptr);
}
ze_result_t zeMemCloseIpcHandle (ze_context_handle_t hContext, const void* ptr) {
    return Cal::Icd::LevelZero::zeMemCloseIpcHandle(hContext, ptr);
}
ze_result_t zexMemGetIpcHandles (ze_context_handle_t hContext, const void* ptr, uint32_t* numIpcHandles, ze_ipc_mem_handle_t* pIpcHandles) {
    return Cal::Icd::LevelZero::zexMemGetIpcHandles(hContext, ptr, numIpcHandles, pIpcHandles);
}
ze_result_t zexMemOpenIpcHandles (ze_context_handle_t hContext, ze_device_handle_t hDevice, uint32_t numIpcHandles, ze_ipc_mem_handle_t* pIpcHandles, ze_ipc_memory_flags_t flags, void** pptr) {
    return Cal::Icd::LevelZero::zexMemOpenIpcHandles(hContext, hDevice, numIpcHandles, pIpcHandles, flags, pptr);
}
ze_result_t zeModuleCreate (ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_module_desc_t* desc, ze_module_handle_t* phModule, ze_module_build_log_handle_t* phBuildLog) {
    return Cal::Icd::LevelZero::zeModuleCreate(hContext, hDevice, desc, phModule, phBuildLog);
}
ze_result_t zeModuleDestroy (ze_module_handle_t hModule) {
    return Cal::Icd::LevelZero::zeModuleDestroy(hModule);
}
ze_result_t zeModuleDynamicLink (uint32_t numModules, ze_module_handle_t* phModules, ze_module_build_log_handle_t* phLinkLog) {
    return Cal::Icd::LevelZero::zeModuleDynamicLink(numModules, phModules, phLinkLog);
}
ze_result_t zeModuleBuildLogDestroy (ze_module_build_log_handle_t hModuleBuildLog) {
    return Cal::Icd::LevelZero::zeModuleBuildLogDestroy(hModuleBuildLog);
}
ze_result_t zeModuleBuildLogGetString (ze_module_build_log_handle_t hModuleBuildLog, size_t* pSize, char* pBuildLog) {
    return Cal::Icd::LevelZero::zeModuleBuildLogGetString(hModuleBuildLog, pSize, pBuildLog);
}
ze_result_t zeModuleGetNativeBinary (ze_module_handle_t hModule, size_t* pSize, uint8_t* pModuleNativeBinary) {
    return Cal::Icd::LevelZero::zeModuleGetNativeBinary(hModule, pSize, pModuleNativeBinary);
}
ze_result_t zeModuleGetGlobalPointer (ze_module_handle_t hModule, const char* pGlobalName, size_t* pSize, void** pptr) {
    return Cal::Icd::LevelZero::zeModuleGetGlobalPointer(hModule, pGlobalName, pSize, pptr);
}
ze_result_t zeModuleGetKernelNames (ze_module_handle_t hModule, uint32_t* pCount, const char** pNames) {
    return Cal::Icd::LevelZero::zeModuleGetKernelNames(hModule, pCount, pNames);
}
ze_result_t zeModuleGetProperties (ze_module_handle_t hModule, ze_module_properties_t* pModuleProperties) {
    return Cal::Icd::LevelZero::zeModuleGetProperties(hModule, pModuleProperties);
}
ze_result_t zeKernelCreate (ze_module_handle_t hModule, const ze_kernel_desc_t* desc, ze_kernel_handle_t* phKernel) {
    return Cal::Icd::LevelZero::zeKernelCreate(hModule, desc, phKernel);
}
ze_result_t zeKernelDestroy (ze_kernel_handle_t hKernel) {
    return Cal::Icd::LevelZero::zeKernelDestroy(hKernel);
}
ze_result_t zeModuleGetFunctionPointer (ze_module_handle_t hModule, const char* pFunctionName, void** pfnFunction) {
    return Cal::Icd::LevelZero::zeModuleGetFunctionPointer(hModule, pFunctionName, pfnFunction);
}
ze_result_t zeKernelSetGroupSize (ze_kernel_handle_t hKernel, uint32_t groupSizeX, uint32_t groupSizeY, uint32_t groupSizeZ) {
    return Cal::Icd::LevelZero::zeKernelSetGroupSize(hKernel, groupSizeX, groupSizeY, groupSizeZ);
}
ze_result_t zeKernelSuggestGroupSize (ze_kernel_handle_t hKernel, uint32_t globalSizeX, uint32_t globalSizeY, uint32_t globalSizeZ, uint32_t* groupSizeX, uint32_t* groupSizeY, uint32_t* groupSizeZ) {
    return Cal::Icd::LevelZero::zeKernelSuggestGroupSize(hKernel, globalSizeX, globalSizeY, globalSizeZ, groupSizeX, groupSizeY, groupSizeZ);
}
ze_result_t zeKernelSuggestMaxCooperativeGroupCount (ze_kernel_handle_t hKernel, uint32_t* totalGroupCount) {
    return Cal::Icd::LevelZero::zeKernelSuggestMaxCooperativeGroupCount(hKernel, totalGroupCount);
}
ze_result_t zeKernelSetArgumentValue (ze_kernel_handle_t hKernel, uint32_t argIndex, size_t argSize, const void* pArgValue) {
    return Cal::Icd::LevelZero::zeKernelSetArgumentValue(hKernel, argIndex, argSize, pArgValue);
}
ze_result_t zeKernelSetIndirectAccess (ze_kernel_handle_t hKernel, ze_kernel_indirect_access_flags_t flags) {
    return Cal::Icd::LevelZero::zeKernelSetIndirectAccess(hKernel, flags);
}
ze_result_t zeKernelGetIndirectAccess (ze_kernel_handle_t hKernel, ze_kernel_indirect_access_flags_t* pFlags) {
    return Cal::Icd::LevelZero::zeKernelGetIndirectAccess(hKernel, pFlags);
}
ze_result_t zeKernelSetCacheConfig (ze_kernel_handle_t hKernel, ze_cache_config_flags_t flags) {
    return Cal::Icd::LevelZero::zeKernelSetCacheConfig(hKernel, flags);
}
ze_result_t zeKernelGetProperties (ze_kernel_handle_t hKernel, ze_kernel_properties_t* pKernelProperties) {
    return Cal::Icd::LevelZero::zeKernelGetProperties(hKernel, pKernelProperties);
}
ze_result_t zeKernelGetName (ze_kernel_handle_t hKernel, size_t* pSize, char* pName) {
    return Cal::Icd::LevelZero::zeKernelGetName(hKernel, pSize, pName);
}
ze_result_t zeCommandListAppendLaunchKernel (ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchFuncArgs, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    return Cal::Icd::LevelZero::zeCommandListAppendLaunchKernel(hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents);
}
ze_result_t zeCommandListAppendLaunchKernelIndirect (ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchArgumentsBuffer, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    return Cal::Icd::LevelZero::zeCommandListAppendLaunchKernelIndirect(hCommandList, hKernel, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents);
}
ze_result_t zeDevicePciGetPropertiesExt (ze_device_handle_t hDevice, ze_pci_ext_properties_t* pPciProperties) {
    return Cal::Icd::LevelZero::zeDevicePciGetPropertiesExt(hDevice, pPciProperties);
}
} // extern "C"


// #### Generated code -- end ####
