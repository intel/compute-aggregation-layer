/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

// #### Generated code -- begin ####
#include "icd/level_zero/icd_level_zero.h"
#include "generated_rpc_messages_level_zero.h"
#include "shared/utils.h"

namespace Cal {
namespace Rpc {
namespace LevelZero {

using namespace Cal::Utils;

ZeCommandQueueExecuteCommandListsRpcM::Captures::DynamicTraits ZeCommandQueueExecuteCommandListsRpcM::Captures::DynamicTraits::calculate(ze_command_queue_handle_t hCommandQueue, uint32_t numCommandLists, ze_command_list_handle_t* phCommandLists, ze_fence_handle_t hFence) {
    DynamicTraits ret = {};
    ret.phCommandLists.count = numCommandLists;
    ret.phCommandLists.size = ret.phCommandLists.count * sizeof(ze_command_list_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phCommandLists.offset + ret.phCommandLists.size);


    return ret;
}

size_t ZeCommandQueueExecuteCommandListsRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phCommandLists) + Cal::Utils::alignUpPow2<8>(this->countPhCommandLists * sizeof(ze_command_list_handle_t));
     return size;
}

size_t ZeCommandQueueExecuteCommandListsRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhCommandLists * sizeof(ze_command_list_handle_t));
     return size;
}

ZeCommandQueueExecuteCommandListsCopyMemoryRpcHelperRpcM::Captures::DynamicTraits ZeCommandQueueExecuteCommandListsCopyMemoryRpcHelperRpcM::Captures::DynamicTraits::calculate(uint32_t chunksCount, const Cal::Rpc::MemChunk* chunks, uint32_t* transferDescsCount, Cal::Rpc::ShmemTransferDesc* transferDescs) {
    DynamicTraits ret = {};
    ret.chunks.count = chunksCount;
    ret.chunks.size = ret.chunks.count * sizeof(Cal::Rpc::MemChunk);

    ret.transferDescs.offset = alignUpPow2<8>(ret.chunks.offset + ret.chunks.size);
    ret.transferDescs.count = (transferDescsCount ? *transferDescsCount : 0);
    ret.transferDescs.size = ret.transferDescs.count * sizeof(Cal::Rpc::ShmemTransferDesc);
    ret.totalDynamicSize = alignUpPow2<8>(ret.transferDescs.offset + ret.transferDescs.size);


    return ret;
}

size_t ZeCommandQueueExecuteCommandListsCopyMemoryRpcHelperRpcM::Captures::getCaptureTotalSize() const {
     const auto lastMemberOffset = offsetTransferDescs;
     const auto lastMemberArraySize = this->countTransferDescs * sizeof(Cal::Rpc::ShmemTransferDesc);

     auto size = offsetof(Captures, dynMem) + Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

size_t ZeCommandQueueExecuteCommandListsCopyMemoryRpcHelperRpcM::Captures::getCaptureDynMemSize() const {
     const auto lastMemberOffset = offsetTransferDescs;
     const auto lastMemberArraySize = this->countTransferDescs * sizeof(Cal::Rpc::ShmemTransferDesc);

     auto size = Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

ZeContextCreateExRpcM::Captures::DynamicTraits ZeContextCreateExRpcM::Captures::DynamicTraits::calculate(ze_driver_handle_t hDriver, const ze_context_desc_t* desc, uint32_t numDevices, ze_device_handle_t* phDevices, ze_context_handle_t* phContext) {
    DynamicTraits ret = {};
    ret.phDevices.count = numDevices;
    ret.phDevices.size = ret.phDevices.count * sizeof(ze_device_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phDevices.offset + ret.phDevices.size);


    return ret;
}

size_t ZeContextCreateExRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phDevices) + Cal::Utils::alignUpPow2<8>(this->countPhDevices * sizeof(ze_device_handle_t));
     return size;
}

size_t ZeContextCreateExRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhDevices * sizeof(ze_device_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyRpcHelperUsm2UsmRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyRpcHelperUsm2UsmRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = numWaitEvents;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyRpcHelperUsm2UsmRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyRpcHelperUsm2UsmRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyRpcHelperMalloc2UsmRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyRpcHelperMalloc2UsmRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = numWaitEvents;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyRpcHelperMalloc2UsmRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyRpcHelperMalloc2UsmRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyRpcHelperMalloc2UsmImmediateRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyRpcHelperMalloc2UsmImmediateRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.srcptr.count = size;
    ret.srcptr.size = ret.srcptr.count;

    ret.phWaitEvents.offset = alignUpPow2<8>(ret.srcptr.offset + ret.srcptr.size);
    ret.phWaitEvents.count = numWaitEvents;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyRpcHelperMalloc2UsmImmediateRpcM::Captures::getCaptureTotalSize() const {
     const auto lastMemberOffset = offsetPhWaitEvents;
     const auto lastMemberArraySize = this->countPhWaitEvents * sizeof(ze_event_handle_t);

     auto size = offsetof(Captures, dynMem) + Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

size_t ZeCommandListAppendMemoryCopyRpcHelperMalloc2UsmImmediateRpcM::Captures::getCaptureDynMemSize() const {
     const auto lastMemberOffset = offsetPhWaitEvents;
     const auto lastMemberArraySize = this->countPhWaitEvents * sizeof(ze_event_handle_t);

     auto size = Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

ZeCommandListAppendMemoryCopyRpcHelperUsm2MallocImmediateSynchronousRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyRpcHelperUsm2MallocImmediateSynchronousRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.dstptr.count = size;
    ret.dstptr.size = ret.dstptr.count;

    ret.phWaitEvents.offset = alignUpPow2<8>(ret.dstptr.offset + ret.dstptr.size);
    ret.phWaitEvents.count = numWaitEvents;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyRpcHelperUsm2MallocImmediateSynchronousRpcM::Captures::getCaptureTotalSize() const {
     const auto lastMemberOffset = offsetPhWaitEvents;
     const auto lastMemberArraySize = this->countPhWaitEvents * sizeof(ze_event_handle_t);

     auto size = offsetof(Captures, dynMem) + Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

size_t ZeCommandListAppendMemoryCopyRpcHelperUsm2MallocImmediateSynchronousRpcM::Captures::getCaptureDynMemSize() const {
     const auto lastMemberOffset = offsetPhWaitEvents;
     const auto lastMemberArraySize = this->countPhWaitEvents * sizeof(ze_event_handle_t);

     auto size = Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

ZeCommandListAppendMemoryCopyRpcHelperMalloc2MallocImmediateSynchronousRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyRpcHelperMalloc2MallocImmediateSynchronousRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.dstptr.count = size;
    ret.dstptr.size = ret.dstptr.count;

    ret.srcptr.offset = alignUpPow2<8>(ret.dstptr.offset + ret.dstptr.size);
    ret.srcptr.count = size;
    ret.srcptr.size = ret.srcptr.count;

    ret.phWaitEvents.offset = alignUpPow2<8>(ret.srcptr.offset + ret.srcptr.size);
    ret.phWaitEvents.count = numWaitEvents;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyRpcHelperMalloc2MallocImmediateSynchronousRpcM::Captures::getCaptureTotalSize() const {
     const auto lastMemberOffset = offsetPhWaitEvents;
     const auto lastMemberArraySize = this->countPhWaitEvents * sizeof(ze_event_handle_t);

     auto size = offsetof(Captures, dynMem) + Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

size_t ZeCommandListAppendMemoryCopyRpcHelperMalloc2MallocImmediateSynchronousRpcM::Captures::getCaptureDynMemSize() const {
     const auto lastMemberOffset = offsetPhWaitEvents;
     const auto lastMemberArraySize = this->countPhWaitEvents * sizeof(ze_event_handle_t);

     auto size = Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

ZeCommandListAppendMemoryCopyRpcHelperUsm2MallocRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyRpcHelperUsm2MallocRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = numWaitEvents;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyRpcHelperUsm2MallocRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyRpcHelperUsm2MallocRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyRpcHelperMalloc2MallocRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyRpcHelperMalloc2MallocRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = numWaitEvents;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyRpcHelperMalloc2MallocRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyRpcHelperMalloc2MallocRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryFillRpcHelperUsm2UsmRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryFillRpcHelperUsm2UsmRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* ptr, const void* pattern, size_t pattern_size, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = numWaitEvents;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryFillRpcHelperUsm2UsmRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryFillRpcHelperUsm2UsmRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryFillRpcHelperUsm2MallocRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryFillRpcHelperUsm2MallocRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* ptr, const void* pattern, size_t pattern_size, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = numWaitEvents;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryFillRpcHelperUsm2MallocRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryFillRpcHelperUsm2MallocRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryFillRpcHelperMalloc2UsmRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryFillRpcHelperMalloc2UsmRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* ptr, const void* pattern, size_t pattern_size, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.pattern.count = pattern_size;
    ret.pattern.size = ret.pattern.count;

    ret.phWaitEvents.offset = alignUpPow2<8>(ret.pattern.offset + ret.pattern.size);
    ret.phWaitEvents.count = numWaitEvents;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryFillRpcHelperMalloc2UsmRpcM::Captures::getCaptureTotalSize() const {
     const auto lastMemberOffset = offsetPhWaitEvents;
     const auto lastMemberArraySize = this->countPhWaitEvents * sizeof(ze_event_handle_t);

     auto size = offsetof(Captures, dynMem) + Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

size_t ZeCommandListAppendMemoryFillRpcHelperMalloc2UsmRpcM::Captures::getCaptureDynMemSize() const {
     const auto lastMemberOffset = offsetPhWaitEvents;
     const auto lastMemberArraySize = this->countPhWaitEvents * sizeof(ze_event_handle_t);

     auto size = Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

ZeCommandListAppendMemoryFillRpcHelperMalloc2MallocRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryFillRpcHelperMalloc2MallocRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* ptr, const void* pattern, size_t pattern_size, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.pattern.count = pattern_size;
    ret.pattern.size = ret.pattern.count;

    ret.phWaitEvents.offset = alignUpPow2<8>(ret.pattern.offset + ret.pattern.size);
    ret.phWaitEvents.count = numWaitEvents;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryFillRpcHelperMalloc2MallocRpcM::Captures::getCaptureTotalSize() const {
     const auto lastMemberOffset = offsetPhWaitEvents;
     const auto lastMemberArraySize = this->countPhWaitEvents * sizeof(ze_event_handle_t);

     auto size = offsetof(Captures, dynMem) + Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

size_t ZeCommandListAppendMemoryFillRpcHelperMalloc2MallocRpcM::Captures::getCaptureDynMemSize() const {
     const auto lastMemberOffset = offsetPhWaitEvents;
     const auto lastMemberArraySize = this->countPhWaitEvents * sizeof(ze_event_handle_t);

     auto size = Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

ZeDeviceGetRpcM::Captures::DynamicTraits ZeDeviceGetRpcM::Captures::DynamicTraits::calculate(ze_driver_handle_t hDriver, uint32_t* pCount, ze_device_handle_t* phDevices) {
    DynamicTraits ret = {};
    ret.phDevices.count = (pCount ? *pCount : 0);
    ret.phDevices.size = ret.phDevices.count * sizeof(ze_device_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phDevices.offset + ret.phDevices.size);


    return ret;
}

size_t ZeDeviceGetRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phDevices) + Cal::Utils::alignUpPow2<8>(this->countPhDevices * sizeof(ze_device_handle_t));
     return size;
}

size_t ZeDeviceGetRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhDevices * sizeof(ze_device_handle_t));
     return size;
}

ZeDeviceGetSubDevicesRpcM::Captures::DynamicTraits ZeDeviceGetSubDevicesRpcM::Captures::DynamicTraits::calculate(ze_device_handle_t hDevice, uint32_t* pCount, ze_device_handle_t* phSubdevices) {
    DynamicTraits ret = {};
    ret.phSubdevices.count = (pCount ? *pCount : 0);
    ret.phSubdevices.size = ret.phSubdevices.count * sizeof(ze_device_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phSubdevices.offset + ret.phSubdevices.size);


    return ret;
}

size_t ZeDeviceGetSubDevicesRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phSubdevices) + Cal::Utils::alignUpPow2<8>(this->countPhSubdevices * sizeof(ze_device_handle_t));
     return size;
}

size_t ZeDeviceGetSubDevicesRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhSubdevices * sizeof(ze_device_handle_t));
     return size;
}

ZeDeviceGetModulePropertiesRpcM::Captures::DynamicTraits ZeDeviceGetModulePropertiesRpcM::Captures::DynamicTraits::calculate(ze_device_handle_t hDevice, ze_device_module_properties_t* pModuleProperties) {
    DynamicTraits ret = {};

    ret.dynamicStructMembersOffset = ret.totalDynamicSize;
    if (pModuleProperties) {
        ret.pModulePropertiesNestedTraits.offset = ret.totalDynamicSize;
        ret.pModulePropertiesNestedTraits.count = 1;
        ret.pModulePropertiesNestedTraits.size = ret.pModulePropertiesNestedTraits.count * sizeof(DynamicStructTraits<ze_device_module_properties_t>);
        ret.totalDynamicSize += alignUpPow2<8>(ret.pModulePropertiesNestedTraits.size);

        for (uint32_t i = 0; i < ret.pModulePropertiesNestedTraits.count; ++i) {
            const auto& pModulePropertiesPNext = pModuleProperties[i].pNext;
            if(!pModulePropertiesPNext){
                continue;
            }

            const auto pModulePropertiesPNextCount = static_cast<uint32_t>(countOpaqueList(static_cast<const ze_base_desc_t*>(pModuleProperties[i].pNext)));
            if(!pModulePropertiesPNextCount){
                continue;
            }

            ret.totalDynamicSize += alignUpPow2<8>(pModulePropertiesPNextCount * sizeof(NestedPNextTraits));

            auto pModulePropertiesPNextListElement = static_cast<const ze_base_desc_t*>(pModuleProperties[i].pNext);
            for(uint32_t j = 0; j < pModulePropertiesPNextCount; ++j){
                ret.totalDynamicSize += alignUpPow2<8>(getUnderlyingSize(pModulePropertiesPNextListElement));
                pModulePropertiesPNextListElement = getNext(pModulePropertiesPNextListElement);
            }

        }
    }

    return ret;
}

size_t ZeDeviceGetModulePropertiesRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, dynMem) + dynMemSize;
     return size;
}

size_t ZeDeviceGetModulePropertiesRpcM::Captures::getCaptureDynMemSize() const {
     return dynMemSize;
}

ZeDeviceGetCommandQueueGroupPropertiesRpcM::Captures::DynamicTraits ZeDeviceGetCommandQueueGroupPropertiesRpcM::Captures::DynamicTraits::calculate(ze_device_handle_t hDevice, uint32_t* pCount, ze_command_queue_group_properties_t* pCommandQueueGroupProperties) {
    DynamicTraits ret = {};
    ret.pCommandQueueGroupProperties.count = (pCount ? *pCount : 0);
    ret.pCommandQueueGroupProperties.size = ret.pCommandQueueGroupProperties.count * sizeof(ze_command_queue_group_properties_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.pCommandQueueGroupProperties.offset + ret.pCommandQueueGroupProperties.size);


    return ret;
}

size_t ZeDeviceGetCommandQueueGroupPropertiesRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, pCommandQueueGroupProperties) + Cal::Utils::alignUpPow2<8>(this->countPCommandQueueGroupProperties * sizeof(ze_command_queue_group_properties_t));
     return size;
}

size_t ZeDeviceGetCommandQueueGroupPropertiesRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPCommandQueueGroupProperties * sizeof(ze_command_queue_group_properties_t));
     return size;
}

ZeDeviceGetMemoryPropertiesRpcM::Captures::DynamicTraits ZeDeviceGetMemoryPropertiesRpcM::Captures::DynamicTraits::calculate(ze_device_handle_t hDevice, uint32_t* pCount, ze_device_memory_properties_t* pMemProperties) {
    DynamicTraits ret = {};
    ret.pMemProperties.count = (pCount ? *pCount : 0);
    ret.pMemProperties.size = ret.pMemProperties.count * sizeof(ze_device_memory_properties_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.pMemProperties.offset + ret.pMemProperties.size);

    ret.dynamicStructMembersOffset = ret.totalDynamicSize;
    if (pMemProperties) {
        ret.pMemPropertiesNestedTraits.offset = ret.totalDynamicSize;
        ret.pMemPropertiesNestedTraits.count = (pCount ? *pCount : 0);
        ret.pMemPropertiesNestedTraits.size = ret.pMemPropertiesNestedTraits.count * sizeof(DynamicStructTraits<ze_device_memory_properties_t>);
        ret.totalDynamicSize += alignUpPow2<8>(ret.pMemPropertiesNestedTraits.size);

        for (uint32_t i = 0; i < ret.pMemPropertiesNestedTraits.count; ++i) {
            const auto& pMemPropertiesPNext = pMemProperties[i].pNext;
            if(!pMemPropertiesPNext){
                continue;
            }

            const auto pMemPropertiesPNextCount = static_cast<uint32_t>(countOpaqueList(static_cast<const ze_base_desc_t*>(pMemProperties[i].pNext)));
            if(!pMemPropertiesPNextCount){
                continue;
            }

            ret.totalDynamicSize += alignUpPow2<8>(pMemPropertiesPNextCount * sizeof(NestedPNextTraits));

            auto pMemPropertiesPNextListElement = static_cast<const ze_base_desc_t*>(pMemProperties[i].pNext);
            for(uint32_t j = 0; j < pMemPropertiesPNextCount; ++j){
                ret.totalDynamicSize += alignUpPow2<8>(getUnderlyingSize(pMemPropertiesPNextListElement));
                pMemPropertiesPNextListElement = getNext(pMemPropertiesPNextListElement);
            }

        }
    }

    return ret;
}

size_t ZeDeviceGetMemoryPropertiesRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, dynMem) + dynMemSize;
     return size;
}

size_t ZeDeviceGetMemoryPropertiesRpcM::Captures::getCaptureDynMemSize() const {
     return dynMemSize;
}

ZeDeviceGetCachePropertiesRpcM::Captures::DynamicTraits ZeDeviceGetCachePropertiesRpcM::Captures::DynamicTraits::calculate(ze_device_handle_t hDevice, uint32_t* pCount, ze_device_cache_properties_t* pCacheProperties) {
    DynamicTraits ret = {};
    ret.pCacheProperties.count = (pCount ? *pCount : 0);
    ret.pCacheProperties.size = ret.pCacheProperties.count * sizeof(ze_device_cache_properties_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.pCacheProperties.offset + ret.pCacheProperties.size);


    return ret;
}

size_t ZeDeviceGetCachePropertiesRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, pCacheProperties) + Cal::Utils::alignUpPow2<8>(this->countPCacheProperties * sizeof(ze_device_cache_properties_t));
     return size;
}

size_t ZeDeviceGetCachePropertiesRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPCacheProperties * sizeof(ze_device_cache_properties_t));
     return size;
}

ZeDeviceGetP2PPropertiesRpcM::Captures::DynamicTraits ZeDeviceGetP2PPropertiesRpcM::Captures::DynamicTraits::calculate(ze_device_handle_t hDevice, ze_device_handle_t hPeerDevice, ze_device_p2p_properties_t* pP2PProperties) {
    DynamicTraits ret = {};

    ret.dynamicStructMembersOffset = ret.totalDynamicSize;
    if (pP2PProperties) {
        ret.pP2PPropertiesNestedTraits.offset = ret.totalDynamicSize;
        ret.pP2PPropertiesNestedTraits.count = 1;
        ret.pP2PPropertiesNestedTraits.size = ret.pP2PPropertiesNestedTraits.count * sizeof(DynamicStructTraits<ze_device_p2p_properties_t>);
        ret.totalDynamicSize += alignUpPow2<8>(ret.pP2PPropertiesNestedTraits.size);

        for (uint32_t i = 0; i < ret.pP2PPropertiesNestedTraits.count; ++i) {
            const auto& pP2PPropertiesPNext = pP2PProperties[i].pNext;
            if(!pP2PPropertiesPNext){
                continue;
            }

            const auto pP2PPropertiesPNextCount = static_cast<uint32_t>(countOpaqueList(static_cast<const ze_base_desc_t*>(pP2PProperties[i].pNext)));
            if(!pP2PPropertiesPNextCount){
                continue;
            }

            ret.totalDynamicSize += alignUpPow2<8>(pP2PPropertiesPNextCount * sizeof(NestedPNextTraits));

            auto pP2PPropertiesPNextListElement = static_cast<const ze_base_desc_t*>(pP2PProperties[i].pNext);
            for(uint32_t j = 0; j < pP2PPropertiesPNextCount; ++j){
                ret.totalDynamicSize += alignUpPow2<8>(getUnderlyingSize(pP2PPropertiesPNextListElement));
                pP2PPropertiesPNextListElement = getNext(pP2PPropertiesPNextListElement);
            }

        }
    }

    return ret;
}

size_t ZeDeviceGetP2PPropertiesRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, dynMem) + dynMemSize;
     return size;
}

size_t ZeDeviceGetP2PPropertiesRpcM::Captures::getCaptureDynMemSize() const {
     return dynMemSize;
}

ZeDriverGetRpcM::Captures::DynamicTraits ZeDriverGetRpcM::Captures::DynamicTraits::calculate(uint32_t* pCount, ze_driver_handle_t* phDrivers) {
    DynamicTraits ret = {};
    ret.phDrivers.count = (pCount ? *pCount : 0);
    ret.phDrivers.size = ret.phDrivers.count * sizeof(ze_driver_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phDrivers.offset + ret.phDrivers.size);


    return ret;
}

size_t ZeDriverGetRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phDrivers) + Cal::Utils::alignUpPow2<8>(this->countPhDrivers * sizeof(ze_driver_handle_t));
     return size;
}

size_t ZeDriverGetRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhDrivers * sizeof(ze_driver_handle_t));
     return size;
}

ZeDriverGetExtensionPropertiesRpcM::Captures::DynamicTraits ZeDriverGetExtensionPropertiesRpcM::Captures::DynamicTraits::calculate(ze_driver_handle_t hDriver, uint32_t* pCount, ze_driver_extension_properties_t* pExtensionProperties) {
    DynamicTraits ret = {};
    ret.pExtensionProperties.count = (pCount ? *pCount : 0);
    ret.pExtensionProperties.size = ret.pExtensionProperties.count * sizeof(ze_driver_extension_properties_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.pExtensionProperties.offset + ret.pExtensionProperties.size);


    return ret;
}

size_t ZeDriverGetExtensionPropertiesRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, pExtensionProperties) + Cal::Utils::alignUpPow2<8>(this->countPExtensionProperties * sizeof(ze_driver_extension_properties_t));
     return size;
}

size_t ZeDriverGetExtensionPropertiesRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPExtensionProperties * sizeof(ze_driver_extension_properties_t));
     return size;
}

ZeEventPoolCreateRpcM::Captures::DynamicTraits ZeEventPoolCreateRpcM::Captures::DynamicTraits::calculate(ze_context_handle_t hContext, const ze_event_pool_desc_t* desc, uint32_t numDevices, ze_device_handle_t* phDevices, ze_event_pool_handle_t* phEventPool) {
    DynamicTraits ret = {};
    ret.phDevices.count = numDevices;
    ret.phDevices.size = ret.phDevices.count * sizeof(ze_device_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phDevices.offset + ret.phDevices.size);


    return ret;
}

size_t ZeEventPoolCreateRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phDevices) + Cal::Utils::alignUpPow2<8>(this->countPhDevices * sizeof(ze_device_handle_t));
     return size;
}

size_t ZeEventPoolCreateRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhDevices * sizeof(ze_device_handle_t));
     return size;
}

ZeCommandListAppendBarrierRpcM::Captures::DynamicTraits ZeCommandListAppendBarrierRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = numWaitEvents;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendBarrierRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendBarrierRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendWaitOnEventsRpcM::Captures::DynamicTraits ZeCommandListAppendWaitOnEventsRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, uint32_t numEvents, ze_event_handle_t* phEvents) {
    DynamicTraits ret = {};
    ret.phEvents.count = numEvents;
    ret.phEvents.size = ret.phEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phEvents.offset + ret.phEvents.size);


    return ret;
}

size_t ZeCommandListAppendWaitOnEventsRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phEvents) + Cal::Utils::alignUpPow2<8>(this->countPhEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendWaitOnEventsRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhEvents * sizeof(ze_event_handle_t));
     return size;
}

ZexMemGetIpcHandlesRpcM::Captures::DynamicTraits ZexMemGetIpcHandlesRpcM::Captures::DynamicTraits::calculate(ze_context_handle_t hContext, const void* ptr, uint32_t* numIpcHandles, ze_ipc_mem_handle_t* pIpcHandles) {
    DynamicTraits ret = {};
    ret.pIpcHandles.count = (numIpcHandles ? *numIpcHandles : 0);
    ret.pIpcHandles.size = ret.pIpcHandles.count * sizeof(ze_ipc_mem_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.pIpcHandles.offset + ret.pIpcHandles.size);


    return ret;
}

size_t ZexMemGetIpcHandlesRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, pIpcHandles) + Cal::Utils::alignUpPow2<8>(this->countPIpcHandles * sizeof(ze_ipc_mem_handle_t));
     return size;
}

size_t ZexMemGetIpcHandlesRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPIpcHandles * sizeof(ze_ipc_mem_handle_t));
     return size;
}

ZexMemOpenIpcHandlesRpcM::Captures::DynamicTraits ZexMemOpenIpcHandlesRpcM::Captures::DynamicTraits::calculate(ze_context_handle_t hContext, ze_device_handle_t hDevice, uint32_t numIpcHandles, ze_ipc_mem_handle_t* pIpcHandles, ze_ipc_memory_flags_t flags, void** pptr) {
    DynamicTraits ret = {};
    ret.pIpcHandles.count = numIpcHandles;
    ret.pIpcHandles.size = ret.pIpcHandles.count * sizeof(ze_ipc_mem_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.pIpcHandles.offset + ret.pIpcHandles.size);


    return ret;
}

size_t ZexMemOpenIpcHandlesRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, pIpcHandles) + Cal::Utils::alignUpPow2<8>(this->countPIpcHandles * sizeof(ze_ipc_mem_handle_t));
     return size;
}

size_t ZexMemOpenIpcHandlesRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPIpcHandles * sizeof(ze_ipc_mem_handle_t));
     return size;
}

ZeModuleCreateRpcM::Captures::DynamicTraits ZeModuleCreateRpcM::Captures::DynamicTraits::calculate(ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_module_desc_t* desc, ze_module_handle_t* phModule, ze_module_build_log_handle_t* phBuildLog) {
    DynamicTraits ret = {};

    ret.dynamicStructMembersOffset = ret.totalDynamicSize;
    if (desc) {
        ret.descNestedTraits.offset = ret.totalDynamicSize;
        ret.descNestedTraits.count = 1;
        ret.descNestedTraits.size = ret.descNestedTraits.count * sizeof(DynamicStructTraits<ze_module_desc_t>);
        ret.totalDynamicSize += alignUpPow2<8>(ret.descNestedTraits.size);

        for (uint32_t i = 0; i < ret.descNestedTraits.count; ++i) {
            const auto& descPInputModule = desc[i].pInputModule;
            if(!descPInputModule){
                continue;
            }

            const auto descPInputModuleCount = static_cast<uint32_t>(desc[i].inputSize);
            if(!descPInputModuleCount){
                continue;
            }

            ret.totalDynamicSize += alignUpPow2<8>(descPInputModuleCount * sizeof(uint8_t));
        }

        for (uint32_t i = 0; i < ret.descNestedTraits.count; ++i) {
            const auto& descPBuildFlags = desc[i].pBuildFlags;
            if(!descPBuildFlags){
                continue;
            }

            const auto descPBuildFlagsCount = static_cast<uint32_t>(Cal::Utils::countNullterminated(desc[i].pBuildFlags));
            if(!descPBuildFlagsCount){
                continue;
            }

            ret.totalDynamicSize += alignUpPow2<8>(descPBuildFlagsCount * sizeof(char));
        }

        for (uint32_t i = 0; i < ret.descNestedTraits.count; ++i) {
            const auto& descPConstants = desc[i].pConstants;
            if(!descPConstants){
                continue;
            }

            const auto descPConstantsCount = static_cast<uint32_t>(1);
            if(!descPConstantsCount){
                continue;
            }

            ret.totalDynamicSize += alignUpPow2<8>(descPConstantsCount * sizeof(ze_module_constants_t));
            ret.totalDynamicSize += alignUpPow2<8>(descPConstantsCount * sizeof(DynamicStructTraits<ze_module_constants_t>));
            for(uint32_t j = 0; j < descPConstantsCount; ++j){
                const auto& descPConstantsPConstantIds = desc[i].pConstants[j].pConstantIds;
                if(!descPConstantsPConstantIds){
                    continue;
                }

                const auto descPConstantsPConstantIdsCount = static_cast<uint32_t>(desc[i].pConstants[j].numConstants);
                if(!descPConstantsPConstantIdsCount){
                    continue;
                }

                ret.totalDynamicSize += alignUpPow2<8>(descPConstantsPConstantIdsCount * sizeof(uint32_t));
            }

            for(uint32_t j = 0; j < descPConstantsCount; ++j){
                const auto& descPConstantsPConstantValues = desc[i].pConstants[j].pConstantValues;
                if(!descPConstantsPConstantValues){
                    continue;
                }

                const auto descPConstantsPConstantValuesCount = static_cast<uint32_t>(desc[i].pConstants[j].numConstants);
                if(!descPConstantsPConstantValuesCount){
                    continue;
                }

                ret.totalDynamicSize += alignUpPow2<8>(descPConstantsPConstantValuesCount * sizeof(const void *));
                ret.totalDynamicSize += alignUpPow2<8>(descPConstantsPConstantValuesCount * sizeof(DynamicStructTraits<const void *>));
                for(uint32_t k = 0; k < descPConstantsPConstantValuesCount; ++k){
                    const auto& descPConstantsPConstantValues_k = descPConstantsPConstantValues[k];
                    if(!descPConstantsPConstantValues_k){
                        continue;
                    }

                    const auto descPConstantsPConstantValues_kCount = static_cast<uint32_t>(1);
                    if(!descPConstantsPConstantValues_kCount){
                        continue;
                    }
                    ret.totalDynamicSize += alignUpPow2<8>(descPConstantsPConstantValues_kCount * sizeof(uint64_t));
                }

            }

        }
    }

    return ret;
}

size_t ZeModuleCreateRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, dynMem) + dynMemSize;
     return size;
}

size_t ZeModuleCreateRpcM::Captures::getCaptureDynMemSize() const {
     return dynMemSize;
}

ZeModuleDynamicLinkRpcM::Captures::DynamicTraits ZeModuleDynamicLinkRpcM::Captures::DynamicTraits::calculate(uint32_t numModules, ze_module_handle_t* phModules, ze_module_build_log_handle_t* phLinkLog) {
    DynamicTraits ret = {};
    ret.phModules.count = numModules;
    ret.phModules.size = ret.phModules.count * sizeof(ze_module_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phModules.offset + ret.phModules.size);


    return ret;
}

size_t ZeModuleDynamicLinkRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phModules) + Cal::Utils::alignUpPow2<8>(this->countPhModules * sizeof(ze_module_handle_t));
     return size;
}

size_t ZeModuleDynamicLinkRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhModules * sizeof(ze_module_handle_t));
     return size;
}

ZeModuleBuildLogGetStringRpcM::Captures::DynamicTraits ZeModuleBuildLogGetStringRpcM::Captures::DynamicTraits::calculate(ze_module_build_log_handle_t hModuleBuildLog, size_t* pSize, char* pBuildLog) {
    DynamicTraits ret = {};
    ret.pBuildLog.count = (pSize ? *pSize : 0);
    ret.pBuildLog.size = ret.pBuildLog.count * sizeof(char);
    ret.totalDynamicSize = alignUpPow2<8>(ret.pBuildLog.offset + ret.pBuildLog.size);


    return ret;
}

size_t ZeModuleBuildLogGetStringRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, pBuildLog) + Cal::Utils::alignUpPow2<8>(this->countPBuildLog * sizeof(char));
     return size;
}

size_t ZeModuleBuildLogGetStringRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPBuildLog * sizeof(char));
     return size;
}

ZeModuleGetNativeBinaryRpcM::Captures::DynamicTraits ZeModuleGetNativeBinaryRpcM::Captures::DynamicTraits::calculate(ze_module_handle_t hModule, size_t* pSize, uint8_t* pModuleNativeBinary) {
    DynamicTraits ret = {};
    ret.pModuleNativeBinary.count = (pSize ? *pSize : 0);
    ret.pModuleNativeBinary.size = ret.pModuleNativeBinary.count * sizeof(uint8_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.pModuleNativeBinary.offset + ret.pModuleNativeBinary.size);


    return ret;
}

size_t ZeModuleGetNativeBinaryRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, pModuleNativeBinary) + Cal::Utils::alignUpPow2<8>(this->countPModuleNativeBinary * sizeof(uint8_t));
     return size;
}

size_t ZeModuleGetNativeBinaryRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPModuleNativeBinary * sizeof(uint8_t));
     return size;
}

ZeModuleGetGlobalPointerRpcM::Captures::DynamicTraits ZeModuleGetGlobalPointerRpcM::Captures::DynamicTraits::calculate(ze_module_handle_t hModule, const char* pGlobalName, size_t* pSize, void** pptr) {
    DynamicTraits ret = {};
    ret.pGlobalName.count = Cal::Utils::countNullterminated(pGlobalName);
    ret.pGlobalName.size = ret.pGlobalName.count * sizeof(char);
    ret.totalDynamicSize = alignUpPow2<8>(ret.pGlobalName.offset + ret.pGlobalName.size);


    return ret;
}

size_t ZeModuleGetGlobalPointerRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, pGlobalName) + Cal::Utils::alignUpPow2<8>(this->countPGlobalName * sizeof(char));
     return size;
}

size_t ZeModuleGetGlobalPointerRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPGlobalName * sizeof(char));
     return size;
}

ZeModuleGetKernelNamesRpcHelperRpcM::Captures::DynamicTraits ZeModuleGetKernelNamesRpcHelperRpcM::Captures::DynamicTraits::calculate(ze_module_handle_t hModule, uint32_t* totalLength, char* namesBuffer) {
    DynamicTraits ret = {};
    ret.namesBuffer.count = (totalLength ? *totalLength : 0);
    ret.namesBuffer.size = ret.namesBuffer.count * sizeof(char);
    ret.totalDynamicSize = alignUpPow2<8>(ret.namesBuffer.offset + ret.namesBuffer.size);


    return ret;
}

size_t ZeModuleGetKernelNamesRpcHelperRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, namesBuffer) + Cal::Utils::alignUpPow2<8>(this->countNamesBuffer * sizeof(char));
     return size;
}

size_t ZeModuleGetKernelNamesRpcHelperRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countNamesBuffer * sizeof(char));
     return size;
}

ZeKernelCreateRpcM::Captures::DynamicTraits ZeKernelCreateRpcM::Captures::DynamicTraits::calculate(ze_module_handle_t hModule, const ze_kernel_desc_t* desc, ze_kernel_handle_t* phKernel) {
    DynamicTraits ret = {};

    ret.dynamicStructMembersOffset = ret.totalDynamicSize;
    if (desc) {
        ret.descNestedTraits.offset = ret.totalDynamicSize;
        ret.descNestedTraits.count = 1;
        ret.descNestedTraits.size = ret.descNestedTraits.count * sizeof(DynamicStructTraits<ze_kernel_desc_t>);
        ret.totalDynamicSize += alignUpPow2<8>(ret.descNestedTraits.size);

        for (uint32_t i = 0; i < ret.descNestedTraits.count; ++i) {
            const auto& descPKernelName = desc[i].pKernelName;
            if(!descPKernelName){
                continue;
            }

            const auto descPKernelNameCount = static_cast<uint32_t>(Cal::Utils::countNullterminated(desc[i].pKernelName));
            if(!descPKernelNameCount){
                continue;
            }

            ret.totalDynamicSize += alignUpPow2<8>(descPKernelNameCount * sizeof(char));
        }
    }

    return ret;
}

size_t ZeKernelCreateRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, dynMem) + dynMemSize;
     return size;
}

size_t ZeKernelCreateRpcM::Captures::getCaptureDynMemSize() const {
     return dynMemSize;
}

ZeModuleGetFunctionPointerRpcM::Captures::DynamicTraits ZeModuleGetFunctionPointerRpcM::Captures::DynamicTraits::calculate(ze_module_handle_t hModule, const char* pFunctionName, void** pfnFunction) {
    DynamicTraits ret = {};
    ret.pFunctionName.count = Cal::Utils::countNullterminated(pFunctionName);
    ret.pFunctionName.size = ret.pFunctionName.count * sizeof(char);
    ret.totalDynamicSize = alignUpPow2<8>(ret.pFunctionName.offset + ret.pFunctionName.size);


    return ret;
}

size_t ZeModuleGetFunctionPointerRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, pFunctionName) + Cal::Utils::alignUpPow2<8>(this->countPFunctionName * sizeof(char));
     return size;
}

size_t ZeModuleGetFunctionPointerRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPFunctionName * sizeof(char));
     return size;
}

ZeKernelSetArgumentValueRpcM::Captures::DynamicTraits ZeKernelSetArgumentValueRpcM::Captures::DynamicTraits::calculate(ze_kernel_handle_t hKernel, uint32_t argIndex, size_t argSize, const void* pArgValue) {
    DynamicTraits ret = {};
    ret.pArgValue.count = argSize;
    ret.pArgValue.size = ret.pArgValue.count;
    ret.totalDynamicSize = alignUpPow2<8>(ret.pArgValue.offset + ret.pArgValue.size);


    return ret;
}

size_t ZeKernelSetArgumentValueRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, pArgValue) + Cal::Utils::alignUpPow2<8>(this->countPArgValue);
     return size;
}

size_t ZeKernelSetArgumentValueRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPArgValue);
     return size;
}

ZeKernelGetPropertiesRpcM::Captures::DynamicTraits ZeKernelGetPropertiesRpcM::Captures::DynamicTraits::calculate(ze_kernel_handle_t hKernel, ze_kernel_properties_t* pKernelProperties) {
    DynamicTraits ret = {};

    ret.dynamicStructMembersOffset = ret.totalDynamicSize;
    if (pKernelProperties) {
        ret.pKernelPropertiesNestedTraits.offset = ret.totalDynamicSize;
        ret.pKernelPropertiesNestedTraits.count = 1;
        ret.pKernelPropertiesNestedTraits.size = ret.pKernelPropertiesNestedTraits.count * sizeof(DynamicStructTraits<ze_kernel_properties_t>);
        ret.totalDynamicSize += alignUpPow2<8>(ret.pKernelPropertiesNestedTraits.size);

        for (uint32_t i = 0; i < ret.pKernelPropertiesNestedTraits.count; ++i) {
            const auto& pKernelPropertiesPNext = pKernelProperties[i].pNext;
            if(!pKernelPropertiesPNext){
                continue;
            }

            const auto pKernelPropertiesPNextCount = static_cast<uint32_t>(countOpaqueList(static_cast<const ze_base_desc_t*>(pKernelProperties[i].pNext)));
            if(!pKernelPropertiesPNextCount){
                continue;
            }

            ret.totalDynamicSize += alignUpPow2<8>(pKernelPropertiesPNextCount * sizeof(NestedPNextTraits));

            auto pKernelPropertiesPNextListElement = static_cast<const ze_base_desc_t*>(pKernelProperties[i].pNext);
            for(uint32_t j = 0; j < pKernelPropertiesPNextCount; ++j){
                ret.totalDynamicSize += alignUpPow2<8>(getUnderlyingSize(pKernelPropertiesPNextListElement));
                pKernelPropertiesPNextListElement = getNext(pKernelPropertiesPNextListElement);
            }

        }
    }

    return ret;
}

size_t ZeKernelGetPropertiesRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, dynMem) + dynMemSize;
     return size;
}

size_t ZeKernelGetPropertiesRpcM::Captures::getCaptureDynMemSize() const {
     return dynMemSize;
}

ZeKernelGetNameRpcM::Captures::DynamicTraits ZeKernelGetNameRpcM::Captures::DynamicTraits::calculate(ze_kernel_handle_t hKernel, size_t* pSize, char* pName) {
    DynamicTraits ret = {};
    ret.pName.count = (pSize ? *pSize : 0);
    ret.pName.size = ret.pName.count * sizeof(char);
    ret.totalDynamicSize = alignUpPow2<8>(ret.pName.offset + ret.pName.size);


    return ret;
}

size_t ZeKernelGetNameRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, pName) + Cal::Utils::alignUpPow2<8>(this->countPName * sizeof(char));
     return size;
}

size_t ZeKernelGetNameRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPName * sizeof(char));
     return size;
}

ZeCommandListAppendLaunchKernelRpcM::Captures::DynamicTraits ZeCommandListAppendLaunchKernelRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchFuncArgs, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = numWaitEvents;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendLaunchKernelRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendLaunchKernelRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendLaunchKernelIndirectRpcM::Captures::DynamicTraits ZeCommandListAppendLaunchKernelIndirectRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchArgumentsBuffer, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = numWaitEvents;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendLaunchKernelIndirectRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendLaunchKernelIndirectRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

} // namespace LevelZero
} // namespace Rpc
} // namespace Cal
// #### Generated code -- end ####
