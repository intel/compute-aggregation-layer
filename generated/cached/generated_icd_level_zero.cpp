/*
 * Copyright (C) 2022-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

// #### Generated code -- begin ####

#include "client/icd/icd_global_state.h"
#include "shared/rpc.h"
#include "shared/utils.h"

#include "client/icd/level_zero/icd_level_zero.h"
#include "client/icd/icd_page_fault_manager.h"
#include "client/icd/level_zero/tracing/tracing_imp.h"
#include "generated_icd_level_zero.h"
#include "generated_rpc_messages_level_zero.h"

#include <cstdlib>
#include <type_traits>

using Cal::Utils::enforceNullWithWarning;
using Cal::Utils::ensureNull;

namespace Cal {
namespace Client {
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

ze_result_t zetMetricGroupGet (zet_device_handle_t hDevice, uint32_t* pCount, zet_metric_group_handle_t* phMetricGroups) {
    log<Verbosity::bloat>("Establishing RPC for zetMetricGroupGet");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZetMetricGroupGetRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hDevice, pCount, phMetricGroups);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hDevice, pCount, phMetricGroups);
    command->copyFromCaller(dynMemTraits);
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    if(phMetricGroups)
    {
        auto baseMutable = mutable_element_cast(phMetricGroups);

        auto numEntries = command->captures.pCount;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = globalPlatform->translateNewRemoteObjectToLocalObject(baseMutable[i]);
        }
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zetMetricGroupGetProperties (zet_metric_group_handle_t hMetricGroup, zet_metric_group_properties_t* pProperties) {
    log<Verbosity::bloat>("Establishing RPC for zetMetricGroupGetProperties");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZetMetricGroupGetPropertiesRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hMetricGroup, pProperties);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hMetricGroup, pProperties);
    command->copyFromCaller(dynMemTraits);
    command->args.hMetricGroup = hMetricGroup->asLocalObject()->asRemoteObject();


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
ze_result_t zetMetricGroupGetGlobalTimestampsExp (zet_metric_group_handle_t hMetricGroup, ze_bool_t synchronizedWithHost, uint64_t* globalTimestamp, uint64_t* metricTimestamp) {
    log<Verbosity::bloat>("Establishing RPC for zetMetricGroupGetGlobalTimestampsExp");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZetMetricGroupGetGlobalTimestampsExpRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hMetricGroup, synchronizedWithHost, globalTimestamp, metricTimestamp);
    command->args.hMetricGroup = hMetricGroup->asLocalObject()->asRemoteObject();


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
ze_result_t zetMetricGroupGetExportDataExp (zet_metric_group_handle_t hMetricGroup, const uint8_t * pRawData, size_t rawDataSize, size_t* pExportDataSize, uint8_t* pExportData) {
    log<Verbosity::bloat>("Establishing RPC for zetMetricGroupGetExportDataExp");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZetMetricGroupGetExportDataExpRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hMetricGroup, pRawData, rawDataSize, pExportDataSize, pExportData);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hMetricGroup, pRawData, rawDataSize, pExportDataSize, pExportData);
    command->copyFromCaller(dynMemTraits);
    command->args.hMetricGroup = hMetricGroup->asLocalObject()->asRemoteObject();


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
ze_result_t zetMetricGet (zet_metric_group_handle_t hMetricGroup, uint32_t* pCount, zet_metric_handle_t* phMetrics) {
    log<Verbosity::bloat>("Establishing RPC for zetMetricGet");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZetMetricGetRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hMetricGroup, pCount, phMetrics);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hMetricGroup, pCount, phMetrics);
    command->copyFromCaller(dynMemTraits);
    command->args.hMetricGroup = hMetricGroup->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    if(phMetrics)
    {
        auto baseMutable = mutable_element_cast(phMetrics);

        auto numEntries = command->captures.pCount;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = globalPlatform->translateNewRemoteObjectToLocalObject(baseMutable[i]);
        }
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zetMetricGetProperties (zet_metric_handle_t hMetric, zet_metric_properties_t* pProperties) {
    log<Verbosity::bloat>("Establishing RPC for zetMetricGetProperties");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZetMetricGetPropertiesRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hMetric, pProperties);
    command->copyFromCaller();
    command->args.hMetric = hMetric->asLocalObject()->asRemoteObject();
    if(pProperties)
    {
        ensureNull("zetMetricGetProperties: pProperties->pNext", pProperties->pNext);
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
ze_result_t zetContextActivateMetricGroups (zet_context_handle_t hContext, zet_device_handle_t hDevice, uint32_t count, zet_metric_group_handle_t* phMetricGroups) {
    log<Verbosity::bloat>("Establishing RPC for zetContextActivateMetricGroups");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZetContextActivateMetricGroupsRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hContext, hDevice, count, phMetricGroups);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hContext, hDevice, count, phMetricGroups);
    command->copyFromCaller(dynMemTraits);
    command->args.hContext = (hContext)->asLocalObject()->asRemoteObject();
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();
    if(phMetricGroups)
    {
        auto base = command->captures.phMetricGroups;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phMetricGroups.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
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
ze_result_t zetMetricStreamerOpen (zet_context_handle_t hContext, zet_device_handle_t hDevice, zet_metric_group_handle_t hMetricGroup, zet_metric_streamer_desc_t* desc, ze_event_handle_t hNotificationEvent, zet_metric_streamer_handle_t* phMetricStreamer) {
    log<Verbosity::bloat>("Establishing RPC for zetMetricStreamerOpen");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZetMetricStreamerOpenRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hContext, hDevice, hMetricGroup, desc, hNotificationEvent, phMetricStreamer);
    command->copyFromCaller();
    command->args.hContext = (hContext)->asLocalObject()->asRemoteObject();
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();
    command->args.hMetricGroup = hMetricGroup->asLocalObject()->asRemoteObject();
    if(desc)
    {
        ensureNull("zetMetricStreamerOpen: desc->pNext", desc->pNext);
    }
    if(hNotificationEvent)
    {
        command->args.hNotificationEvent = hNotificationEvent->asLocalObject()->asRemoteObject();
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
ze_result_t zetMetricStreamerReadData (zet_metric_streamer_handle_t hMetricStreamer, uint32_t maxReportCount, size_t* pRawDataSize, uint8_t* pRawData) {
    log<Verbosity::bloat>("Establishing RPC for zetMetricStreamerReadData");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZetMetricStreamerReadDataRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hMetricStreamer, maxReportCount, pRawDataSize, pRawData);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hMetricStreamer, maxReportCount, pRawDataSize, pRawData);
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
ze_result_t zetMetricStreamerClose (zet_metric_streamer_handle_t hMetricStreamer) {
    log<Verbosity::bloat>("Establishing RPC for zetMetricStreamerClose");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZetMetricStreamerCloseRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hMetricStreamer);


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
 // zetTracerExpCreate ignored in generator - based on dont_generate_handler flag
 // zetTracerExpDestroy ignored in generator - based on dont_generate_handler flag
 // zetTracerExpSetPrologues ignored in generator - based on dont_generate_handler flag
 // zetTracerExpSetEpilogues ignored in generator - based on dont_generate_handler flag
 // zetTracerExpSetEnabled ignored in generator - based on dont_generate_handler flag
ze_result_t zetDeviceGetDebugProperties (ze_device_handle_t hDevice, zet_device_debug_properties_t* pDebugProperties) {
    log<Verbosity::bloat>("Establishing RPC for zetDeviceGetDebugProperties");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZetDeviceGetDebugPropertiesRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hDevice, pDebugProperties);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hDevice, pDebugProperties);
    command->copyFromCaller(dynMemTraits);
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();


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
ze_result_t zetDebugAttach (ze_device_handle_t hDevice, const zet_debug_config_t* config, zet_debug_session_handle_t* phDebug) {
    log<Verbosity::bloat>("Establishing RPC for zetDebugAttach");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZetDebugAttachRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hDevice, config, phDebug);
    command->copyFromCaller();
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();


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
ze_result_t zetDebugDetach (zet_debug_session_handle_t hDebug) {
    log<Verbosity::bloat>("Establishing RPC for zetDebugDetach");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZetDebugDetachRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hDebug);


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zesDeviceReset (zes_device_handle_t hDevice, ze_bool_t force) {
    log<Verbosity::bloat>("Establishing RPC for zesDeviceReset");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesDeviceResetRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hDevice, force);
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zesDeviceResetExt (zes_device_handle_t hDevice, zes_reset_properties_t* pProperties) {
    log<Verbosity::bloat>("Establishing RPC for zesDeviceResetExt");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesDeviceResetExtRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hDevice, pProperties);
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zesDeviceEnumPowerDomains (zes_device_handle_t hDevice, uint32_t* pCount, zes_pwr_handle_t* phPower) {
    log<Verbosity::bloat>("Establishing RPC for zesDeviceEnumPowerDomains");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesDeviceEnumPowerDomainsRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hDevice, pCount, phPower);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hDevice, pCount, phPower);
    command->copyFromCaller(dynMemTraits);
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();


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
ze_result_t zesDeviceGetCardPowerDomain (zes_device_handle_t hDevice, zes_pwr_handle_t* phPower) {
    log<Verbosity::bloat>("Establishing RPC for zesDeviceGetCardPowerDomain");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesDeviceGetCardPowerDomainRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hDevice, phPower);
    command->copyFromCaller();
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();


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
ze_result_t zesPowerGetProperties (zes_pwr_handle_t hPower, zes_power_properties_t* pProperties) {
    log<Verbosity::bloat>("Establishing RPC for zesPowerGetProperties");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesPowerGetPropertiesRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hPower, pProperties);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hPower, pProperties);
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
ze_result_t zesPowerGetEnergyCounter (zes_pwr_handle_t hPower, zes_power_energy_counter_t* pEnergy) {
    log<Verbosity::bloat>("Establishing RPC for zesPowerGetEnergyCounter");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesPowerGetEnergyCounterRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hPower, pEnergy);
    command->copyFromCaller();


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
ze_result_t zesPowerGetLimits (zes_pwr_handle_t hPower, zes_power_sustained_limit_t* pSustained, zes_power_burst_limit_t* pBurst, zes_power_peak_limit_t* pPeak) {
    log<Verbosity::bloat>("Establishing RPC for zesPowerGetLimits");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesPowerGetLimitsRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hPower, pSustained, pBurst, pPeak);
    command->copyFromCaller();


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
ze_result_t zesPowerSetLimits (zes_pwr_handle_t hPower, const zes_power_sustained_limit_t* pSustained, const zes_power_burst_limit_t* pBurst, const zes_power_peak_limit_t* pPeak) {
    log<Verbosity::bloat>("Establishing RPC for zesPowerSetLimits");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesPowerSetLimitsRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hPower, pSustained, pBurst, pPeak);
    command->copyFromCaller();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zesPowerGetLimitsExt (zes_pwr_handle_t hPower, uint32_t* pCount, zes_power_limit_ext_desc_t* pSustained) {
    log<Verbosity::bloat>("Establishing RPC for zesPowerGetLimitsExt");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesPowerGetLimitsExtRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hPower, pCount, pSustained);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hPower, pCount, pSustained);
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
ze_result_t zesPowerSetLimitsExt (zes_pwr_handle_t hPower, uint32_t* pCount, zes_power_limit_ext_desc_t* pSustained) {
    log<Verbosity::bloat>("Establishing RPC for zesPowerSetLimitsExt");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesPowerSetLimitsExtRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hPower, pCount, pSustained);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hPower, pCount, pSustained);
    command->copyFromCaller(dynMemTraits);


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zesPowerGetEnergyThreshold (zes_pwr_handle_t hPower, zes_energy_threshold_t * pThreshold) {
    log<Verbosity::bloat>("Establishing RPC for zesPowerGetEnergyThreshold");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesPowerGetEnergyThresholdRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hPower, pThreshold);
    command->copyFromCaller();


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
ze_result_t zesPowerSetEnergyThreshold (zes_pwr_handle_t hPower, double pThreshold) {
    log<Verbosity::bloat>("Establishing RPC for zesPowerSetEnergyThreshold");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesPowerSetEnergyThresholdRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hPower, pThreshold);


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zesDeviceEventRegister (zes_device_handle_t hDevice, zes_event_type_flags_t events) {
    log<Verbosity::bloat>("Establishing RPC for zesDeviceEventRegister");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesDeviceEventRegisterRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hDevice, events);
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zesDriverEventListen (ze_driver_handle_t hDriver, uint32_t timeout, uint32_t count, ze_device_handle_t* phDevices, uint32_t* pNumDeviceEvents, zes_event_type_flags_t* pEvents) {
    log<Verbosity::bloat>("Establishing RPC for zesDriverEventListen");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesDriverEventListenRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hDriver, timeout, count, phDevices, pNumDeviceEvents, pEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hDriver, timeout, count, phDevices, pNumDeviceEvents, pEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hDriver = hDriver->asLocalObject()->asRemoteObject();
    if(phDevices)
    {
        auto base = command->captures.phDevices;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phDevices.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
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
ze_result_t zesDriverEventListenEx (ze_driver_handle_t hDriver, uint64_t timeout, uint32_t count, zes_device_handle_t* phDevices, uint32_t* pNumDeviceEvents, zes_event_type_flags_t* pEvents) {
    log<Verbosity::bloat>("Establishing RPC for zesDriverEventListenEx");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesDriverEventListenExRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hDriver, timeout, count, phDevices, pNumDeviceEvents, pEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hDriver, timeout, count, phDevices, pNumDeviceEvents, pEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hDriver = hDriver->asLocalObject()->asRemoteObject();
    if(phDevices)
    {
        auto base = command->captures.phDevices;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phDevices.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
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
ze_result_t zesDeviceEnumTemperatureSensors (zes_device_handle_t hDevice, uint32_t* pCount, zes_temp_handle_t* phTemperature) {
    log<Verbosity::bloat>("Establishing RPC for zesDeviceEnumTemperatureSensors");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesDeviceEnumTemperatureSensorsRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hDevice, pCount, phTemperature);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hDevice, pCount, phTemperature);
    command->copyFromCaller(dynMemTraits);
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();


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
ze_result_t zesTemperatureGetProperties (zes_temp_handle_t hTemperature, zes_temp_properties_t* pProperties) {
    log<Verbosity::bloat>("Establishing RPC for zesTemperatureGetProperties");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesTemperatureGetPropertiesRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hTemperature, pProperties);
    command->copyFromCaller();


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
ze_result_t zesTemperatureGetConfig (zes_temp_handle_t hTemperature, zes_temp_config_t * pConfig) {
    log<Verbosity::bloat>("Establishing RPC for zesTemperatureGetConfig");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesTemperatureGetConfigRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hTemperature, pConfig);
    command->copyFromCaller();


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
ze_result_t zesTemperatureSetConfig (zes_temp_handle_t hTemperature, const zes_temp_config_t* pConfig) {
    log<Verbosity::bloat>("Establishing RPC for zesTemperatureSetConfig");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesTemperatureSetConfigRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hTemperature, pConfig);
    command->copyFromCaller();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zesTemperatureGetState (zes_temp_handle_t hTemperature, double* pTemperature) {
    log<Verbosity::bloat>("Establishing RPC for zesTemperatureGetState");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesTemperatureGetStateRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hTemperature, pTemperature);
    command->copyFromCaller();


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
ze_result_t zesDeviceEnumRasErrorSets (zes_device_handle_t hDevice, uint32_t* pCount, zes_ras_handle_t* phRas) {
    log<Verbosity::bloat>("Establishing RPC for zesDeviceEnumRasErrorSets");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesDeviceEnumRasErrorSetsRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hDevice, pCount, phRas);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hDevice, pCount, phRas);
    command->copyFromCaller(dynMemTraits);
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();


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
ze_result_t zesRasGetProperties (zes_ras_handle_t hRas, zes_ras_properties_t* pProperties) {
    log<Verbosity::bloat>("Establishing RPC for zesRasGetProperties");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesRasGetPropertiesRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hRas, pProperties);
    command->copyFromCaller();


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
ze_result_t zesRasGetConfig (zes_ras_handle_t hRas, zes_ras_config_t * pConfig) {
    log<Verbosity::bloat>("Establishing RPC for zesRasGetConfig");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesRasGetConfigRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hRas, pConfig);
    command->copyFromCaller();


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
ze_result_t zesRasSetConfig (zes_ras_handle_t hRas, const zes_ras_config_t* pConfig) {
    log<Verbosity::bloat>("Establishing RPC for zesRasSetConfig");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesRasSetConfigRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hRas, pConfig);
    command->copyFromCaller();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zesRasGetState (zes_ras_handle_t hRas, ze_bool_t clear, zes_ras_state_t* pState) {
    log<Verbosity::bloat>("Establishing RPC for zesRasGetState");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesRasGetStateRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hRas, clear, pState);


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zesDeviceEnumFrequencyDomains (zes_device_handle_t hDevice, uint32_t* pCount, zes_freq_handle_t* phFrequency) {
    log<Verbosity::bloat>("Establishing RPC for zesDeviceEnumFrequencyDomains");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesDeviceEnumFrequencyDomainsRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hDevice, pCount, phFrequency);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hDevice, pCount, phFrequency);
    command->copyFromCaller(dynMemTraits);
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();


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
ze_result_t zesFrequencyGetProperties (zes_freq_handle_t hFrequency, zes_freq_properties_t* pProperties) {
    log<Verbosity::bloat>("Establishing RPC for zesFrequencyGetProperties");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesFrequencyGetPropertiesRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hFrequency, pProperties);
    command->copyFromCaller();


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
ze_result_t zesFrequencyGetAvailableClocks (zes_freq_handle_t hFrequency, uint32_t* pCount, double* phFrequency) {
    log<Verbosity::bloat>("Establishing RPC for zesFrequencyGetAvailableClocks");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesFrequencyGetAvailableClocksRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hFrequency, pCount, phFrequency);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hFrequency, pCount, phFrequency);
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
ze_result_t zesFrequencyGetRange (zes_freq_handle_t hFrequency, zes_freq_range_t* pConfig) {
    log<Verbosity::bloat>("Establishing RPC for zesFrequencyGetRange");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesFrequencyGetRangeRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hFrequency, pConfig);
    command->copyFromCaller();


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
ze_result_t zesFrequencySetRange (zes_freq_handle_t hFrequency, const zes_freq_range_t* pLimits) {
    log<Verbosity::bloat>("Establishing RPC for zesFrequencySetRange");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesFrequencySetRangeRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hFrequency, pLimits);
    command->copyFromCaller();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zesFrequencyGetState (zes_freq_handle_t hFrequency, zes_freq_state_t* pState) {
    log<Verbosity::bloat>("Establishing RPC for zesFrequencyGetState");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesFrequencyGetStateRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hFrequency, pState);
    command->copyFromCaller();


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
ze_result_t zesFrequencyGetThrottleTime (zes_freq_handle_t hFrequency, zes_freq_throttle_time_t* pThrottleTime) {
    log<Verbosity::bloat>("Establishing RPC for zesFrequencyGetThrottleTime");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesFrequencyGetThrottleTimeRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hFrequency, pThrottleTime);
    command->copyFromCaller();


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
ze_result_t zesFrequencyOcGetCapabilities (zes_freq_handle_t hFrequency, zes_oc_capabilities_t* pOcCapabilities) {
    log<Verbosity::bloat>("Establishing RPC for zesFrequencyOcGetCapabilities");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesFrequencyOcGetCapabilitiesRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hFrequency, pOcCapabilities);
    command->copyFromCaller();


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
ze_result_t zesFrequencyOcGetVoltageTarget (zes_freq_handle_t hFrequency, double* pCurrentVoltageTarget, double* pCurrentVoltageOffset) {
    log<Verbosity::bloat>("Establishing RPC for zesFrequencyOcGetVoltageTarget");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesFrequencyOcGetVoltageTargetRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hFrequency, pCurrentVoltageTarget, pCurrentVoltageOffset);


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zesFrequencyOcSetVoltageTarget (zes_freq_handle_t hFrequency, double CurrentVoltageTarget, double CurrentVoltageOffset) {
    log<Verbosity::bloat>("Establishing RPC for zesFrequencyOcSetVoltageTarget");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesFrequencyOcSetVoltageTargetRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hFrequency, CurrentVoltageTarget, CurrentVoltageOffset);


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zesFrequencyOcSetMode (zes_freq_handle_t hFrequency, zes_oc_mode_t CurrentOcMode) {
    log<Verbosity::bloat>("Establishing RPC for zesFrequencyOcSetMode");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesFrequencyOcSetModeRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hFrequency, CurrentOcMode);


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zesFrequencyOcGetMode (zes_freq_handle_t hFrequency, zes_oc_mode_t* pCurrentOcMode) {
    log<Verbosity::bloat>("Establishing RPC for zesFrequencyOcGetMode");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesFrequencyOcGetModeRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hFrequency, pCurrentOcMode);


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zesFrequencyOcGetIccMax (zes_freq_handle_t hFrequency, double* pOcIccMax) {
    log<Verbosity::bloat>("Establishing RPC for zesFrequencyOcGetIccMax");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesFrequencyOcGetIccMaxRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hFrequency, pOcIccMax);


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zesFrequencyOcSetIccMax (zes_freq_handle_t hFrequency, double ocIccMax) {
    log<Verbosity::bloat>("Establishing RPC for zesFrequencyOcSetIccMax");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesFrequencyOcSetIccMaxRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hFrequency, ocIccMax);


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zesFrequencyOcGetTjMax (zes_freq_handle_t hFrequency, double* pOcTjMax) {
    log<Verbosity::bloat>("Establishing RPC for zesFrequencyOcGetTjMax");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesFrequencyOcGetTjMaxRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hFrequency, pOcTjMax);


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zesFrequencyOcSetTjMax (zes_freq_handle_t hFrequency, double ocTjMax) {
    log<Verbosity::bloat>("Establishing RPC for zesFrequencyOcSetTjMax");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesFrequencyOcSetTjMaxRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hFrequency, ocTjMax);


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zesDeviceEnumEngineGroups (zes_device_handle_t hDevice, uint32_t* pCount, zes_engine_handle_t* phEngine) {
    log<Verbosity::bloat>("Establishing RPC for zesDeviceEnumEngineGroups");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesDeviceEnumEngineGroupsRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hDevice, pCount, phEngine);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hDevice, pCount, phEngine);
    command->copyFromCaller(dynMemTraits);
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();


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
ze_result_t zesDeviceEnumSchedulers (zes_device_handle_t hDevice, uint32_t* pCount, zes_sched_handle_t* phScheduler) {
    log<Verbosity::bloat>("Establishing RPC for zesDeviceEnumSchedulers");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesDeviceEnumSchedulersRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hDevice, pCount, phScheduler);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hDevice, pCount, phScheduler);
    command->copyFromCaller(dynMemTraits);
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();


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
ze_result_t zesSchedulerGetProperties (zes_sched_handle_t hScheduler, zes_sched_properties_t* pProperties) {
    log<Verbosity::bloat>("Establishing RPC for zesSchedulerGetProperties");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesSchedulerGetPropertiesRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hScheduler, pProperties);
    command->copyFromCaller();


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
ze_result_t zesSchedulerGetCurrentMode (zes_sched_handle_t hScheduler, zes_sched_mode_t* pMode) {
    log<Verbosity::bloat>("Establishing RPC for zesSchedulerGetCurrentMode");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesSchedulerGetCurrentModeRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hScheduler, pMode);
    command->copyFromCaller();


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
ze_result_t zesSchedulerGetTimeoutModeProperties (zes_sched_handle_t hScheduler, ze_bool_t getDefaults, zes_sched_timeout_properties_t* pConfig) {
    log<Verbosity::bloat>("Establishing RPC for zesSchedulerGetTimeoutModeProperties");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesSchedulerGetTimeoutModePropertiesRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hScheduler, getDefaults, pConfig);
    command->copyFromCaller();


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
ze_result_t zesSchedulerGetTimesliceModeProperties (zes_sched_handle_t hScheduler, ze_bool_t getDefaults, zes_sched_timeslice_properties_t* pConfig) {
    log<Verbosity::bloat>("Establishing RPC for zesSchedulerGetTimesliceModeProperties");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesSchedulerGetTimesliceModePropertiesRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hScheduler, getDefaults, pConfig);
    command->copyFromCaller();


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
ze_result_t zesSchedulerSetTimeoutMode (zes_sched_handle_t hScheduler, zes_sched_timeout_properties_t* pProperties, ze_bool_t* pNeedReload) {
    log<Verbosity::bloat>("Establishing RPC for zesSchedulerSetTimeoutMode");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesSchedulerSetTimeoutModeRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hScheduler, pProperties, pNeedReload);
    command->copyFromCaller();


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
ze_result_t zesSchedulerSetTimesliceMode (zes_sched_handle_t hScheduler, zes_sched_timeslice_properties_t* pProperties, ze_bool_t* pNeedReload) {
    log<Verbosity::bloat>("Establishing RPC for zesSchedulerSetTimesliceMode");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesSchedulerSetTimesliceModeRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hScheduler, pProperties, pNeedReload);
    command->copyFromCaller();


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
ze_result_t zesSchedulerSetExclusiveMode (zes_sched_handle_t hScheduler, ze_bool_t* pNeedReload) {
    log<Verbosity::bloat>("Establishing RPC for zesSchedulerSetExclusiveMode");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesSchedulerSetExclusiveModeRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hScheduler, pNeedReload);
    command->copyFromCaller();


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
ze_result_t zesSchedulerSetComputeUnitDebugMode (zes_sched_handle_t hScheduler, ze_bool_t* pNeedReload) {
    log<Verbosity::bloat>("Establishing RPC for zesSchedulerSetComputeUnitDebugMode");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesSchedulerSetComputeUnitDebugModeRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hScheduler, pNeedReload);
    command->copyFromCaller();


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
ze_result_t zesEngineGetProperties (zes_engine_handle_t hEngine, zes_engine_properties_t* pProperties) {
    log<Verbosity::bloat>("Establishing RPC for zesEngineGetProperties");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesEngineGetPropertiesRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hEngine, pProperties);
    command->copyFromCaller();


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
ze_result_t zesEngineGetActivity (zes_engine_handle_t hEngine, zes_engine_stats_t* pStats) {
    log<Verbosity::bloat>("Establishing RPC for zesEngineGetActivity");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesEngineGetActivityRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hEngine, pStats);
    command->copyFromCaller();


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
ze_result_t zesDeviceGetState (zes_device_handle_t hDevice, zes_device_state_t* pState) {
    log<Verbosity::bloat>("Establishing RPC for zesDeviceGetState");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesDeviceGetStateRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hDevice, pState);
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();


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
ze_result_t zesDeviceProcessesGetState (zes_device_handle_t hDevice, uint32_t* pCount, zes_process_state_t* pProcesses) {
    log<Verbosity::bloat>("Establishing RPC for zesDeviceProcessesGetState");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesDeviceProcessesGetStateRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hDevice, pCount, pProcesses);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hDevice, pCount, pProcesses);
    command->copyFromCaller(dynMemTraits);
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();


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
ze_result_t zesDevicePciGetProperties (zes_device_handle_t hDevice, zes_pci_properties_t* pProperties) {
    log<Verbosity::bloat>("Establishing RPC for zesDevicePciGetProperties");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesDevicePciGetPropertiesRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hDevice, pProperties);
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();


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
ze_result_t zesDevicePciGetState (zes_device_handle_t hDevice, zes_pci_state_t* pState) {
    log<Verbosity::bloat>("Establishing RPC for zesDevicePciGetState");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesDevicePciGetStateRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hDevice, pState);
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();


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
ze_result_t zesDevicePciGetBars (zes_device_handle_t hDevice, uint32_t* pCount, zes_pci_bar_properties_t* pProperties) {
    log<Verbosity::bloat>("Establishing RPC for zesDevicePciGetBars");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesDevicePciGetBarsRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hDevice, pCount, pProperties);
    command->copyFromCaller();
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();


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
ze_result_t zesDevicePciGetStats (zes_device_handle_t hDevice, zes_pci_stats_t* pStats) {
    log<Verbosity::bloat>("Establishing RPC for zesDevicePciGetStats");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesDevicePciGetStatsRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hDevice, pStats);
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();


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
ze_result_t zesDeviceGetPropertiesRpcHelper (zes_device_handle_t hDevice, zes_device_properties_t* pProperties) {
    log<Verbosity::bloat>("Establishing RPC for zesDeviceGetProperties");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesDeviceGetPropertiesRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hDevice, pProperties);
    command->copyFromCaller();
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();


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
ze_result_t zesDeviceEnumMemoryModules (zes_device_handle_t hDevice, uint32_t* pCount, zes_mem_handle_t* phMemory) {
    log<Verbosity::bloat>("Establishing RPC for zesDeviceEnumMemoryModules");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesDeviceEnumMemoryModulesRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hDevice, pCount, phMemory);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hDevice, pCount, phMemory);
    command->copyFromCaller(dynMemTraits);
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();


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
ze_result_t zesDeviceEnumPerformanceFactorDomains (zes_device_handle_t hDevice, uint32_t* pCount, zes_perf_handle_t* phPerf) {
    log<Verbosity::bloat>("Establishing RPC for zesDeviceEnumPerformanceFactorDomains");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesDeviceEnumPerformanceFactorDomainsRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hDevice, pCount, phPerf);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hDevice, pCount, phPerf);
    command->copyFromCaller(dynMemTraits);
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();


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
ze_result_t zesPerformanceFactorGetProperties (zes_perf_handle_t hPerf, zes_perf_properties_t* pProperties) {
    log<Verbosity::bloat>("Establishing RPC for zesPerformanceFactorGetProperties");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesPerformanceFactorGetPropertiesRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hPerf, pProperties);
    command->copyFromCaller();


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
ze_result_t zesPerformanceFactorGetConfig (zes_perf_handle_t hPerf, double* pFactor) {
    log<Verbosity::bloat>("Establishing RPC for zesPerformanceFactorGetConfig");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesPerformanceFactorGetConfigRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hPerf, pFactor);
    command->copyFromCaller();


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
ze_result_t zesPerformanceFactorSetConfig (zes_perf_handle_t hPerf, double pFactor) {
    log<Verbosity::bloat>("Establishing RPC for zesPerformanceFactorSetConfig");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesPerformanceFactorSetConfigRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hPerf, pFactor);


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zesDeviceEnumStandbyDomains (zes_device_handle_t hDevice, uint32_t* pCount, zes_standby_handle_t* phStandby) {
    log<Verbosity::bloat>("Establishing RPC for zesDeviceEnumStandbyDomains");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesDeviceEnumStandbyDomainsRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hDevice, pCount, phStandby);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hDevice, pCount, phStandby);
    command->copyFromCaller(dynMemTraits);
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();


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
ze_result_t zesStandbyGetProperties (zes_standby_handle_t hStandby, zes_standby_properties_t* pProperties) {
    log<Verbosity::bloat>("Establishing RPC for zesStandbyGetProperties");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesStandbyGetPropertiesRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hStandby, pProperties);
    command->copyFromCaller();


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
ze_result_t zesStandbyGetMode (zes_standby_handle_t hStandby, zes_standby_promo_mode_t* pMode) {
    log<Verbosity::bloat>("Establishing RPC for zesStandbyGetMode");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesStandbyGetModeRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hStandby, pMode);


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
ze_result_t zesStandbySetMode (zes_standby_handle_t hStandby, zes_standby_promo_mode_t mode) {
    log<Verbosity::bloat>("Establishing RPC for zesStandbySetMode");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesStandbySetModeRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hStandby, mode);


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zesMemoryGetProperties (zes_mem_handle_t hMemory, zes_mem_properties_t* pProperties) {
    log<Verbosity::bloat>("Establishing RPC for zesMemoryGetProperties");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZesMemoryGetPropertiesRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hMemory, pProperties);
    command->copyFromCaller();


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
ze_result_t zeInitRpcHelper (ze_init_flags_t flags) {
    log<Verbosity::bloat>("Establishing RPC for zeInit");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeInitRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(flags);


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemoryRangesBarrier (ze_command_list_handle_t hCommandList, uint32_t numRanges, const size_t* pRangeSizes, const void** pRanges, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryRangesBarrier");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryRangesBarrierRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, numRanges, pRangeSizes, pRanges, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, numRanges, pRangeSizes, pRanges, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.getPhWaitEvents();
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
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
ze_result_t zeContextSystemBarrier (ze_context_handle_t hContext, ze_device_handle_t hDevice) {
    log<Verbosity::bloat>("Establishing RPC for zeContextSystemBarrier");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeContextSystemBarrierRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hContext, hDevice);
    command->args.hContext = (hContext)->asLocalObject()->asRemoteObject();
    command->args.hDevice = (hDevice)->asLocalObject()->asRemoteObject();


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
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListCreateRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hContext, hDevice, desc, phCommandList);
    command->copyFromCaller();
    command->args.hContext = hContext->asLocalObject()->asRemoteObject();
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();
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
        phCommandList[0] = globalPlatform->translateNewRemoteObjectToLocalObject(phCommandList[0], IcdL0CommandList::CommandListType::Regular);
    }
    ze_result_t ret = command->captures.ret;

    channelLock.unlock();
    if (phCommandList != nullptr) {
        phCommandList[0]->asLocalObject()->context = hContext->asLocalObject();
    }
    return ret;
}
ze_result_t zeCommandListCreateImmediate (ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_queue_desc_t* altdesc, ze_command_list_handle_t* phCommandList) {
    log<Verbosity::bloat>("Establishing RPC for zeCommandListCreateImmediate");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListCreateImmediateRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hContext, hDevice, altdesc, phCommandList);
    command->copyFromCaller();
    command->args.hContext = hContext->asLocalObject()->asRemoteObject();
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();
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
        phCommandList[0] = globalPlatform->translateNewRemoteObjectToLocalObject(phCommandList[0], IcdL0CommandList::selectImmediateType(altdesc));
    }
    ze_result_t ret = command->captures.ret;

    channelLock.unlock();
    if (hContext != nullptr && phCommandList != nullptr) {
        phCommandList[0]->asLocalObject()->context = hContext->asLocalObject();
    }
    return ret;
}
ze_result_t zeCommandListDestroy (ze_command_list_handle_t hCommandList) {
    log<Verbosity::bloat>("Establishing RPC for zeCommandListDestroy");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListDestroyRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hCommandList);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();


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
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListCloseRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hCommandList);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();


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
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListResetRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hCommandList);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();


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
    hCommandList->asLocalObject()->sharedIndirectAccessSet = false;
    return ret;
}
ze_result_t zeCommandListAppendWriteGlobalTimestamp (ze_command_list_handle_t hCommandList, uint64_t* dstptr, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendWriteGlobalTimestamp");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendWriteGlobalTimestampRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();


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
ze_result_t zeCommandQueueCreate (ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_queue_desc_t* desc, ze_command_queue_handle_t* phCommandQueue) {
    log<Verbosity::bloat>("Establishing RPC for zeCommandQueueCreate");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandQueueCreateRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hContext, hDevice, desc, phCommandQueue);
    command->copyFromCaller();
    command->args.hContext = hContext->asLocalObject()->asRemoteObject();
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();
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
        phCommandQueue[0] = globalPlatform->translateNewRemoteObjectToLocalObject(phCommandQueue[0], command->args.desc->mode);
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandQueueDestroy (ze_command_queue_handle_t hCommandQueue) {
    log<Verbosity::bloat>("Establishing RPC for zeCommandQueueDestroy");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandQueueDestroyRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hCommandQueue);
    command->args.hCommandQueue = hCommandQueue->asLocalObject()->asRemoteObject();


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
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandQueueExecuteCommandListsRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandQueue, numCommandLists, phCommandLists, hFence);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandQueue, numCommandLists, phCommandLists, hFence);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandQueue = hCommandQueue->asLocalObject()->asRemoteObject();
    if(phCommandLists)
    {
        auto base = command->captures.phCommandLists;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phCommandLists.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }
    if(hFence)
    {
        command->args.hFence = hFence->asLocalObject()->asRemoteObject();
    }

    if(
       static_cast<IcdL0CommandQueue*>(hCommandQueue)->getCommandQueueMode() == ze_command_queue_mode_t::ZE_COMMAND_QUEUE_MODE_ASYNCHRONOUS &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    ze_result_t ret = command->captures.ret;

    if (ret == ZE_RESULT_SUCCESS && hCommandQueue->asLocalObject()->getCommandQueueMode() == ze_command_queue_mode_t::ZE_COMMAND_QUEUE_MODE_SYNCHRONOUS) {
        ret = globalPlatform->getHostptrCopiesReader().readMemory(channel, Cal::Client::Icd::icdGlobalState.getGlobalShmemImporter());
    };
    return ret;
}
ze_result_t zeCommandQueueExecuteCommandListsCopyMemoryRpcHelper (uint32_t chunksCount, const Cal::Rpc::MemChunk* chunks, uint32_t* transferDescsCount, Cal::Rpc::TransferDesc* transferDescs) {
    log<Verbosity::bloat>("Establishing RPC for zeCommandQueueExecuteCommandListsCopyMemoryRpcHelper");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandQueueExecuteCommandListsCopyMemoryRpcHelperRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(chunksCount, chunks, transferDescsCount, transferDescs);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, chunksCount, chunks, transferDescsCount, transferDescs);
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
ze_result_t zeCommandQueueSynchronize (ze_command_queue_handle_t hCommandQueue, uint64_t timeout) {
    log<Verbosity::bloat>("Establishing RPC for zeCommandQueueSynchronize");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandQueueSynchronizeRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hCommandQueue, timeout);
    command->args.hCommandQueue = hCommandQueue->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    if (ret == ZE_RESULT_SUCCESS) {
        ret = globalPlatform->getHostptrCopiesReader().readMemory(channel, Cal::Client::Icd::icdGlobalState.getGlobalShmemImporter());
    };
    return ret;
}
ze_result_t zeContextCreate (ze_driver_handle_t hDriver, const ze_context_desc_t* desc, ze_context_handle_t* phContext) {
    log<Verbosity::bloat>("Establishing RPC for zeContextCreate");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeContextCreateRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hDriver, desc, phContext);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hDriver, desc, phContext);
    command->copyFromCaller(dynMemTraits);
    command->args.hDriver = hDriver->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    if(phContext)
    {
        phContext[0] = globalPlatform->translateNewRemoteObjectToLocalObject(phContext[0]);
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeContextCreateEx (ze_driver_handle_t hDriver, const ze_context_desc_t* desc, uint32_t numDevices, ze_device_handle_t* phDevices, ze_context_handle_t* phContext) {
    log<Verbosity::bloat>("Establishing RPC for zeContextCreateEx");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeContextCreateExRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hDriver, desc, numDevices, phDevices, phContext);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hDriver, desc, numDevices, phDevices, phContext);
    command->copyFromCaller(dynMemTraits);
    command->args.hDriver = hDriver->asLocalObject()->asRemoteObject();
    if(phDevices)
    {
        auto base = command->captures.getPhDevices();
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phDevices.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
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
        phContext[0] = globalPlatform->translateNewRemoteObjectToLocalObject(phContext[0]);
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeContextDestroy (ze_context_handle_t hContext) {
    hContext->asLocalObject()->beforeReleaseCallback();
    log<Verbosity::bloat>("Establishing RPC for zeContextDestroy");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeContextDestroyRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hContext);
    command->args.hContext = hContext->asLocalObject()->asRemoteObject();


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
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeContextGetStatusRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hContext);
    command->args.hContext = hContext->asLocalObject()->asRemoteObject();


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
ze_result_t zeCommandListAppendMemoryCopyDeferred (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    [[maybe_unused]] auto dstptr_pointer_type = globalPlatform->getPointerType(dstptr);
    [[maybe_unused]] auto srcptr_pointer_type = globalPlatform->getPointerType(srcptr);
    
    if((dstptr_pointer_type == usm) && (srcptr_pointer_type == usm)){
        return zeCommandListAppendMemoryCopyDeferred_Usm_Usm(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else if((dstptr_pointer_type == usm) && (srcptr_pointer_type == shared)){
        return zeCommandListAppendMemoryCopyDeferred_Usm_Shared(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else if((dstptr_pointer_type == usm) && (srcptr_pointer_type == remapped)){
        return zeCommandListAppendMemoryCopyDeferred_Usm_Remapped(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else if((dstptr_pointer_type == shared) && (srcptr_pointer_type == usm)){
        return zeCommandListAppendMemoryCopyDeferred_Shared_Usm(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else if((dstptr_pointer_type == shared) && (srcptr_pointer_type == shared)){
        return zeCommandListAppendMemoryCopyDeferred_Shared_Shared(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else if((dstptr_pointer_type == shared) && (srcptr_pointer_type == remapped)){
        return zeCommandListAppendMemoryCopyDeferred_Shared_Remapped(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else if((dstptr_pointer_type == remapped) && (srcptr_pointer_type == usm)){
        return zeCommandListAppendMemoryCopyDeferred_Remapped_Usm(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else if((dstptr_pointer_type == remapped) && (srcptr_pointer_type == shared)){
        return zeCommandListAppendMemoryCopyDeferred_Remapped_Shared(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else{
        return zeCommandListAppendMemoryCopyDeferred_Remapped_Remapped(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    }
}
ze_result_t zeCommandListAppendMemoryCopyImmediate (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    [[maybe_unused]] auto dstptr_pointer_type = globalPlatform->getPointerType(dstptr);
    [[maybe_unused]] auto srcptr_pointer_type = globalPlatform->getPointerType(srcptr);
    
    if((dstptr_pointer_type == local) && (srcptr_pointer_type == local)){
        return zeCommandListAppendMemoryCopyImmediate_Local_Local(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else if((dstptr_pointer_type == local) && (srcptr_pointer_type == usm)){
        return zeCommandListAppendMemoryCopyImmediate_Local_Usm(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else if((dstptr_pointer_type == local) && (srcptr_pointer_type == shared)){
        return zeCommandListAppendMemoryCopyImmediate_Local_Shared(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else if((dstptr_pointer_type == usm) && (srcptr_pointer_type == local)){
        return zeCommandListAppendMemoryCopyImmediate_Usm_Local(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else if((dstptr_pointer_type == usm) && (srcptr_pointer_type == usm)){
        return zeCommandListAppendMemoryCopyImmediate_Usm_Usm(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else if((dstptr_pointer_type == usm) && (srcptr_pointer_type == shared)){
        return zeCommandListAppendMemoryCopyImmediate_Usm_Shared(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else if((dstptr_pointer_type == shared) && (srcptr_pointer_type == local)){
        return zeCommandListAppendMemoryCopyImmediate_Shared_Local(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else if((dstptr_pointer_type == shared) && (srcptr_pointer_type == usm)){
        return zeCommandListAppendMemoryCopyImmediate_Shared_Usm(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else{
        return zeCommandListAppendMemoryCopyImmediate_Shared_Shared(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    }
}
ze_result_t zeCommandListAppendMemoryCopyImmediateSynchronous (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    [[maybe_unused]] auto dstptr_pointer_type = globalPlatform->getPointerType(dstptr);
    [[maybe_unused]] auto srcptr_pointer_type = globalPlatform->getPointerType(srcptr);
    
    if((dstptr_pointer_type == local) && (srcptr_pointer_type == local)){
        return zeCommandListAppendMemoryCopyImmediateSynchronous_Local_Local(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else if((dstptr_pointer_type == local) && (srcptr_pointer_type == usm)){
        return zeCommandListAppendMemoryCopyImmediateSynchronous_Local_Usm(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else if((dstptr_pointer_type == local) && (srcptr_pointer_type == shared)){
        return zeCommandListAppendMemoryCopyImmediateSynchronous_Local_Shared(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else if((dstptr_pointer_type == usm) && (srcptr_pointer_type == local)){
        return zeCommandListAppendMemoryCopyImmediateSynchronous_Usm_Local(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else if((dstptr_pointer_type == usm) && (srcptr_pointer_type == usm)){
        return zeCommandListAppendMemoryCopyImmediateSynchronous_Usm_Usm(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else if((dstptr_pointer_type == usm) && (srcptr_pointer_type == shared)){
        return zeCommandListAppendMemoryCopyImmediateSynchronous_Usm_Shared(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else if((dstptr_pointer_type == shared) && (srcptr_pointer_type == local)){
        return zeCommandListAppendMemoryCopyImmediateSynchronous_Shared_Local(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else if((dstptr_pointer_type == shared) && (srcptr_pointer_type == usm)){
        return zeCommandListAppendMemoryCopyImmediateSynchronous_Shared_Usm(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else{
        return zeCommandListAppendMemoryCopyImmediateSynchronous_Shared_Shared(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    }
}
 // zeCommandListAppendMemoryFill ignored in generator - based on dont_generate_handler flag
ze_result_t zeCommandListAppendMemoryFillRpcHelperUsm2Usm (ze_command_list_handle_t hCommandList, void* ptr, const void* pattern, size_t pattern_size, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryFillRpcHelperUsm2Usm");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryFillRpcHelperUsm2UsmRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
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
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryFillRpcHelperUsm2MallocRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
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
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryFillRpcHelperMalloc2UsmRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.getPhWaitEvents();
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
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
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryFillRpcHelperMalloc2MallocRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.getPhWaitEvents();
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
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
 // zeCommandListAppendMemoryCopyRegion ignored in generator - based on dont_generate_handler flag
ze_result_t zeCommandListAppendMemoryCopyRegionDeferred (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    [[maybe_unused]] auto dstptr_pointer_type = globalPlatform->getPointerType(dstptr);
    [[maybe_unused]] auto srcptr_pointer_type = globalPlatform->getPointerType(srcptr);
    
    if((dstptr_pointer_type == usm) && (srcptr_pointer_type == usm)){
        return zeCommandListAppendMemoryCopyRegionDeferred_Usm_Usm(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else if((dstptr_pointer_type == usm) && (srcptr_pointer_type == shared)){
        return zeCommandListAppendMemoryCopyRegionDeferred_Usm_Shared(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else if((dstptr_pointer_type == usm) && (srcptr_pointer_type == remapped)){
        return zeCommandListAppendMemoryCopyRegionDeferred_Usm_Remapped(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else if((dstptr_pointer_type == shared) && (srcptr_pointer_type == usm)){
        return zeCommandListAppendMemoryCopyRegionDeferred_Shared_Usm(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else if((dstptr_pointer_type == shared) && (srcptr_pointer_type == shared)){
        return zeCommandListAppendMemoryCopyRegionDeferred_Shared_Shared(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else if((dstptr_pointer_type == shared) && (srcptr_pointer_type == remapped)){
        return zeCommandListAppendMemoryCopyRegionDeferred_Shared_Remapped(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else if((dstptr_pointer_type == remapped) && (srcptr_pointer_type == usm)){
        return zeCommandListAppendMemoryCopyRegionDeferred_Remapped_Usm(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else if((dstptr_pointer_type == remapped) && (srcptr_pointer_type == shared)){
        return zeCommandListAppendMemoryCopyRegionDeferred_Remapped_Shared(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else{
        return zeCommandListAppendMemoryCopyRegionDeferred_Remapped_Remapped(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    }
}
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateSynchronous (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    [[maybe_unused]] auto dstptr_pointer_type = globalPlatform->getPointerType(dstptr);
    [[maybe_unused]] auto srcptr_pointer_type = globalPlatform->getPointerType(srcptr);
    
    if((dstptr_pointer_type == local) && (srcptr_pointer_type == usm)){
        return zeCommandListAppendMemoryCopyRegionImmediateSynchronous_Local_Usm(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else if((dstptr_pointer_type == local) && (srcptr_pointer_type == shared)){
        return zeCommandListAppendMemoryCopyRegionImmediateSynchronous_Local_Shared(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else if((dstptr_pointer_type == local) && (srcptr_pointer_type == remapped)){
        return zeCommandListAppendMemoryCopyRegionImmediateSynchronous_Local_Remapped(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else if((dstptr_pointer_type == usm) && (srcptr_pointer_type == usm)){
        return zeCommandListAppendMemoryCopyRegionImmediateSynchronous_Usm_Usm(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else if((dstptr_pointer_type == usm) && (srcptr_pointer_type == shared)){
        return zeCommandListAppendMemoryCopyRegionImmediateSynchronous_Usm_Shared(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else if((dstptr_pointer_type == usm) && (srcptr_pointer_type == remapped)){
        return zeCommandListAppendMemoryCopyRegionImmediateSynchronous_Usm_Remapped(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else if((dstptr_pointer_type == shared) && (srcptr_pointer_type == usm)){
        return zeCommandListAppendMemoryCopyRegionImmediateSynchronous_Shared_Usm(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else if((dstptr_pointer_type == shared) && (srcptr_pointer_type == shared)){
        return zeCommandListAppendMemoryCopyRegionImmediateSynchronous_Shared_Shared(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else{
        return zeCommandListAppendMemoryCopyRegionImmediateSynchronous_Shared_Remapped(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    }
}
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateAsynchronous (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    [[maybe_unused]] auto dstptr_pointer_type = globalPlatform->getPointerType(dstptr);
    [[maybe_unused]] auto srcptr_pointer_type = globalPlatform->getPointerType(srcptr);
    
    if((dstptr_pointer_type == local) && (srcptr_pointer_type == usm)){
        return zeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Local_Usm(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else if((dstptr_pointer_type == local) && (srcptr_pointer_type == shared)){
        return zeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Local_Shared(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else if((dstptr_pointer_type == local) && (srcptr_pointer_type == remapped)){
        return zeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Local_Remapped(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else if((dstptr_pointer_type == usm) && (srcptr_pointer_type == usm)){
        return zeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Usm_Usm(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else if((dstptr_pointer_type == usm) && (srcptr_pointer_type == shared)){
        return zeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Usm_Shared(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else if((dstptr_pointer_type == usm) && (srcptr_pointer_type == remapped)){
        return zeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Usm_Remapped(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else if((dstptr_pointer_type == shared) && (srcptr_pointer_type == usm)){
        return zeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Shared_Usm(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else if((dstptr_pointer_type == shared) && (srcptr_pointer_type == shared)){
        return zeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Shared_Shared(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else{
        return zeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Shared_Remapped(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    }
}
 // zeCommandListAppendMemoryCopyFromContext ignored in generator - based on dont_generate_handler flag
ze_result_t zeCommandListAppendMemoryCopyFromContextDeferred (ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    [[maybe_unused]] auto dstptr_pointer_type = globalPlatform->getPointerType(dstptr);
    [[maybe_unused]] auto srcptr_pointer_type = globalPlatform->getPointerType(srcptr);
    
    if((dstptr_pointer_type == usm) && (srcptr_pointer_type == usm)){
        return zeCommandListAppendMemoryCopyFromContextDeferred_Usm_Usm(hCommandList, dstptr, hContextSrc, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else if((dstptr_pointer_type == shared) && (srcptr_pointer_type == usm)){
        return zeCommandListAppendMemoryCopyFromContextDeferred_Shared_Usm(hCommandList, dstptr, hContextSrc, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else{
        return zeCommandListAppendMemoryCopyFromContextDeferred_Remapped_Usm(hCommandList, dstptr, hContextSrc, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    }
}
ze_result_t zeCommandListAppendMemoryCopyFromContextImmediateSynchronous (ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    [[maybe_unused]] auto dstptr_pointer_type = globalPlatform->getPointerType(dstptr);
    [[maybe_unused]] auto srcptr_pointer_type = globalPlatform->getPointerType(srcptr);
    
    if((dstptr_pointer_type == local) && (srcptr_pointer_type == usm)){
        return zeCommandListAppendMemoryCopyFromContextImmediateSynchronous_Local_Usm(hCommandList, dstptr, hContextSrc, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else if((dstptr_pointer_type == usm) && (srcptr_pointer_type == usm)){
        return zeCommandListAppendMemoryCopyFromContextImmediateSynchronous_Usm_Usm(hCommandList, dstptr, hContextSrc, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else{
        return zeCommandListAppendMemoryCopyFromContextImmediateSynchronous_Shared_Usm(hCommandList, dstptr, hContextSrc, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    }
}
ze_result_t zeCommandListAppendMemoryCopyFromContextImmediateAsynchronous (ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    [[maybe_unused]] auto dstptr_pointer_type = globalPlatform->getPointerType(dstptr);
    [[maybe_unused]] auto srcptr_pointer_type = globalPlatform->getPointerType(srcptr);
    
    if((dstptr_pointer_type == local) && (srcptr_pointer_type == usm)){
        return zeCommandListAppendMemoryCopyFromContextImmediateAsynchronous_Local_Usm(hCommandList, dstptr, hContextSrc, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else if((dstptr_pointer_type == usm) && (srcptr_pointer_type == usm)){
        return zeCommandListAppendMemoryCopyFromContextImmediateAsynchronous_Usm_Usm(hCommandList, dstptr, hContextSrc, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    }
    else{
        return zeCommandListAppendMemoryCopyFromContextImmediateAsynchronous_Shared_Usm(hCommandList, dstptr, hContextSrc, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    }
}
ze_result_t zeCommandListAppendMemoryPrefetch (ze_command_list_handle_t hCommandList, const void* ptr, size_t size) {
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryPrefetch");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryPrefetchRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hCommandList, ptr, size);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
 // zeCommandListAppendMemAdvise ignored in generator - based on dont_generate_handler flag
ze_result_t zeDeviceGetRpcHelper (ze_driver_handle_t hDriver, uint32_t* pCount, ze_device_handle_t* phDevices) {
    log<Verbosity::bloat>("Establishing RPC for zeDeviceGet");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeDeviceGetRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hDriver, pCount, phDevices);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hDriver, pCount, phDevices);
    command->copyFromCaller(dynMemTraits);
    command->args.hDriver = hDriver->asLocalObject()->asRemoteObject();


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
            baseMutable[i] = globalPlatform->translateNewRemoteObjectToLocalObject(baseMutable[i], hDriver);
        }
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeDeviceGetSubDevicesRpcHelper (ze_device_handle_t hDevice, uint32_t* pCount, ze_device_handle_t* phSubdevices) {
    log<Verbosity::bloat>("Establishing RPC for zeDeviceGetSubDevices");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeDeviceGetSubDevicesRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hDevice, pCount, phSubdevices);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hDevice, pCount, phSubdevices);
    command->copyFromCaller(dynMemTraits);
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();


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
            baseMutable[i] = globalPlatform->translateNewRemoteObjectToLocalObject(baseMutable[i], hDevice);
        }
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeDeviceGetPropertiesRpcHelper (ze_device_handle_t hDevice, ze_device_properties_t* pDeviceProperties) {
    log<Verbosity::bloat>("Establishing RPC for zeDeviceGetProperties");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeDeviceGetPropertiesRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hDevice, pDeviceProperties);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hDevice, pDeviceProperties);
    command->copyFromCaller(dynMemTraits);
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    if(pDeviceProperties)
    {
        command->captures.ret = hDevice->asLocalObject()->patchDeviceName(*pDeviceProperties) ? command->captures.ret : ZE_RESULT_ERROR_DEVICE_LOST;
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeDeviceGetComputePropertiesRpcHelper (ze_device_handle_t hDevice, ze_device_compute_properties_t* pComputeProperties) {
    log<Verbosity::bloat>("Establishing RPC for zeDeviceGetComputeProperties");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeDeviceGetComputePropertiesRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hDevice, pComputeProperties);
    command->copyFromCaller();
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();
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
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeDeviceGetModulePropertiesRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hDevice, pModuleProperties);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hDevice, pModuleProperties);
    command->copyFromCaller(dynMemTraits);
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();


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
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeDeviceGetCommandQueueGroupPropertiesRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hDevice, pCount, pCommandQueueGroupProperties);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hDevice, pCount, pCommandQueueGroupProperties);
    command->copyFromCaller(dynMemTraits);
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();
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
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeDeviceGetMemoryPropertiesRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hDevice, pCount, pMemProperties);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hDevice, pCount, pMemProperties);
    command->copyFromCaller(dynMemTraits);
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();


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
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeDeviceGetMemoryAccessPropertiesRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hDevice, pMemAccessProperties);
    command->copyFromCaller();
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();
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
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeDeviceGetCachePropertiesRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hDevice, pCount, pCacheProperties);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hDevice, pCount, pCacheProperties);
    command->copyFromCaller(dynMemTraits);
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();


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
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeDeviceGetImagePropertiesRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hDevice, pImageProperties);
    command->copyFromCaller();
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();
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
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeDeviceGetExternalMemoryPropertiesRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hDevice, pExternalMemoryProperties);
    command->copyFromCaller();
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();
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
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeDeviceGetP2PPropertiesRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hDevice, hPeerDevice, pP2PProperties);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hDevice, hPeerDevice, pP2PProperties);
    command->copyFromCaller(dynMemTraits);
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();
    command->args.hPeerDevice = hPeerDevice->asLocalObject()->asRemoteObject();


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
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeDeviceCanAccessPeerRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hDevice, hPeerDevice, value);
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();
    command->args.hPeerDevice = hPeerDevice->asLocalObject()->asRemoteObject();


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
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeDeviceGetStatusRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hDevice);
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();


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
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeDeviceGetGlobalTimestampsRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hDevice, hostTimestamp, deviceTimestamp);
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();


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
ze_result_t zeDeviceReserveCacheExt (ze_device_handle_t hDevice, size_t cacheLevel, size_t cacheReservationSize) {
    log<Verbosity::bloat>("Establishing RPC for zeDeviceReserveCacheExt");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeDeviceReserveCacheExtRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hDevice, cacheLevel, cacheReservationSize);
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeDeviceSetCacheAdviceExt (ze_device_handle_t hDevice, void* ptr, size_t regionSize, ze_cache_ext_region_t cacheRegion) {
    log<Verbosity::bloat>("Establishing RPC for zeDeviceSetCacheAdviceExt");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeDeviceSetCacheAdviceExtRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hDevice, ptr, regionSize, cacheRegion);
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeDriverGetRpcHelper (uint32_t* pCount, ze_driver_handle_t* phDrivers) {
    log<Verbosity::bloat>("Establishing RPC for zeDriverGet");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeDriverGetRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(pCount, phDrivers);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, pCount, phDrivers);
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
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeDriverGetApiVersionRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hDriver, version);
    command->args.hDriver = hDriver->asLocalObject()->asRemoteObject();


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
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeDriverGetPropertiesRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hDriver, pDriverProperties);
    command->copyFromCaller();
    command->args.hDriver = hDriver->asLocalObject()->asRemoteObject();
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
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeDriverGetIpcPropertiesRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hDriver, pIpcProperties);
    command->copyFromCaller();
    command->args.hDriver = hDriver->asLocalObject()->asRemoteObject();
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
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeDriverGetExtensionPropertiesRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hDriver, pCount, pExtensionProperties);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hDriver, pCount, pExtensionProperties);
    command->copyFromCaller(dynMemTraits);
    command->args.hDriver = hDriver->asLocalObject()->asRemoteObject();


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
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeEventPoolCreateRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hContext, desc, numDevices, phDevices, phEventPool);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hContext, desc, numDevices, phDevices, phEventPool);
    command->copyFromCaller(dynMemTraits);
    command->args.hContext = hContext->asLocalObject()->asRemoteObject();
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
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
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
        phEventPool[0] = globalPlatform->translateNewRemoteObjectToLocalObject(phEventPool[0]);
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeEventPoolDestroy (ze_event_pool_handle_t hEventPool) {
    log<Verbosity::bloat>("Establishing RPC for zeEventPoolDestroy");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeEventPoolDestroyRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hEventPool);
    command->args.hEventPool = hEventPool->asLocalObject()->asRemoteObject();


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
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeEventCreateRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hEventPool, desc, phEvent);
    command->copyFromCaller();
    command->args.hEventPool = hEventPool->asLocalObject()->asRemoteObject();
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
        phEvent[0] = globalPlatform->translateNewRemoteObjectToLocalObject(phEvent[0]);
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeEventDestroy (ze_event_handle_t hEvent) {
    log<Verbosity::bloat>("Establishing RPC for zeEventDestroy");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeEventDestroyRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hEvent);
    command->args.hEvent = hEvent->asLocalObject()->asRemoteObject();


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
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeEventPoolGetIpcHandleRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hEventPool, phIpc);
    command->args.hEventPool = hEventPool->asLocalObject()->asRemoteObject();


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
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeEventPoolOpenIpcHandleRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hContext, hIpc, phEventPool);
    command->args.hContext = hContext->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller();
    if(phEventPool)
    {
        phEventPool[0] = globalPlatform->translateNewRemoteObjectToLocalObject(phEventPool[0]);
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeEventPoolCloseIpcHandle (ze_event_pool_handle_t hEventPool) {
    log<Verbosity::bloat>("Establishing RPC for zeEventPoolCloseIpcHandle");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeEventPoolCloseIpcHandleRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hEventPool);
    command->args.hEventPool = hEventPool->asLocalObject()->asRemoteObject();


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
    if(hSignalEvent){hSignalEvent->asLocalObject()->setAllowIcdState(hCommandList);}
    for (uint32_t i = 0; i < numWaitEvents; ++i) {
        phWaitEvents[i]->asLocalObject()->setAllowIcdState(hCommandList);
    }
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendBarrier");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendBarrierRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !static_cast<IcdL0CommandList *>(hCommandList)->isImmediateSynchronous() &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendSignalEvent (ze_command_list_handle_t hCommandList, ze_event_handle_t hEvent) {
    hEvent->asLocalObject()->setAllowIcdState(hCommandList);
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendSignalEvent");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendSignalEventRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hCommandList, hEvent);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hEvent)
    {
        command->args.hEvent = hEvent->asLocalObject()->asRemoteObject();
    }

    if(
       !static_cast<IcdL0CommandList *>(hCommandList)->isImmediateSynchronous() &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendWaitOnEvents (ze_command_list_handle_t hCommandList, uint32_t numEvents, ze_event_handle_t* phEvents) {
    for (uint32_t i = 0; i < numEvents; ++i) {
        phEvents[i]->asLocalObject()->setAllowIcdState(hCommandList);
    }
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendWaitOnEvents");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendWaitOnEventsRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, numEvents, phEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, numEvents, phEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(phEvents)
    {
        auto base = command->captures.phEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !static_cast<IcdL0CommandList *>(hCommandList)->isImmediateSynchronous() &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeEventHostSignal (ze_event_handle_t hEvent) {
    log<Verbosity::bloat>("Establishing RPC for zeEventHostSignal");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeEventHostSignalRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hEvent);
    command->args.hEvent = hEvent->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeEventHostSynchronize (ze_event_handle_t hEvent, uint64_t timeout) {
    if (hEvent->asLocalObject()->isSignaled()) {
        return ZE_RESULT_SUCCESS;
    }
    log<Verbosity::bloat>("Establishing RPC for zeEventHostSynchronize");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeEventHostSynchronizeRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hEvent, timeout);
    command->args.hEvent = hEvent->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    if (ret == ZE_RESULT_SUCCESS) {
        ret = globalPlatform->getHostptrCopiesReader().readMemory(channel, Cal::Client::Icd::icdGlobalState.getGlobalShmemImporter());
    };
    channelLock.unlock();
    if (ret == ZE_RESULT_SUCCESS) {
        hEvent->asLocalObject()->signal();
    }
    return ret;
}
ze_result_t zeEventQueryStatus (ze_event_handle_t hEvent) {
    if (hEvent->asLocalObject()->isSignaled()) {
        return ZE_RESULT_SUCCESS;
    }
    log<Verbosity::bloat>("Establishing RPC for zeEventQueryStatus");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeEventQueryStatusRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hEvent);
    command->args.hEvent = hEvent->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    if (ret == ZE_RESULT_SUCCESS) {
        ret = globalPlatform->getHostptrCopiesReader().readMemory(channel, Cal::Client::Icd::icdGlobalState.getGlobalShmemImporter());
    };
    channelLock.unlock();
    if (ret == ZE_RESULT_SUCCESS) {
        hEvent->asLocalObject()->signal();
    }
    return ret;
}
ze_result_t zeCommandListAppendEventReset (ze_command_list_handle_t hCommandList, ze_event_handle_t hEvent) {
    hEvent->asLocalObject()->setAllowIcdState(hCommandList);
    if (hEvent->asLocalObject()->isCleared()) {
        return ZE_RESULT_SUCCESS;
    }
    hEvent->asLocalObject()->clear();

    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendEventReset");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendEventResetRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hCommandList, hEvent);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    command->args.hEvent = hEvent->asLocalObject()->asRemoteObject();


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
    if (hEvent->asLocalObject()->isCleared()) {
        return ZE_RESULT_SUCCESS;
    }
    hEvent->asLocalObject()->clear();
    log<Verbosity::bloat>("Establishing RPC for zeEventHostReset");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeEventHostResetRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hEvent);
    command->args.hEvent = hEvent->asLocalObject()->asRemoteObject();

    if(
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeEventQueryKernelTimestamp (ze_event_handle_t hEvent, ze_kernel_timestamp_result_t* dstptr) {
    if (hEvent->asLocalObject()->isTimestamp()) {
        hEvent->asLocalObject()->getTimestamp(dstptr);
        return ZE_RESULT_SUCCESS;
    }
    log<Verbosity::bloat>("Establishing RPC for zeEventQueryKernelTimestamp");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeEventQueryKernelTimestampRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hEvent, dstptr);
    command->args.hEvent = hEvent->asLocalObject()->asRemoteObject();


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
        hEvent->asLocalObject()->storeTimestamp(dstptr);
    }
    return ret;
}
ze_result_t zeCommandListAppendQueryKernelTimestampsRpcHelper (ze_command_list_handle_t hCommandList, uint32_t numEvents, ze_event_handle_t* phEvents, void* dstptr, const size_t* pOffsets, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendQueryKernelTimestamps");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendQueryKernelTimestampsRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, numEvents, phEvents, dstptr, pOffsets, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, numEvents, phEvents, dstptr, pOffsets, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(phEvents)
    {
        auto base = command->captures.getPhEvents();
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.getPhWaitEvents();
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
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
ze_result_t zeEventQueryTimestampsExp (ze_event_handle_t hEvent, ze_device_handle_t hDevice, uint32_t* pCount, ze_kernel_timestamp_result_t* pTimestamps) {
    log<Verbosity::bloat>("Establishing RPC for zeEventQueryTimestampsExp");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeEventQueryTimestampsExpRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hEvent, hDevice, pCount, pTimestamps);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hEvent, hDevice, pCount, pTimestamps);
    command->copyFromCaller(dynMemTraits);
    command->args.hEvent = static_cast<IcdL0Event*>(hEvent)->asRemoteObject();
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
 // zeEventQueryKernelTimestampsExt ignored in generator - based on dont_generate_handler flag
ze_result_t zeEventQueryKernelTimestampsExtRpcHelper (ze_event_handle_t hEvent, ze_device_handle_t hDevice, uint32_t* pCount, ze_kernel_timestamp_result_t* pResultsTimestamps, ze_synchronized_timestamp_result_ext_t* pResultsSynchronizedTimestamps) {
    log<Verbosity::bloat>("Establishing RPC for zeEventQueryKernelTimestampsExtRpcHelper");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeEventQueryKernelTimestampsExtRpcHelperRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hEvent, hDevice, pCount, pResultsTimestamps, pResultsSynchronizedTimestamps);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hEvent, hDevice, pCount, pResultsTimestamps, pResultsSynchronizedTimestamps);
    command->copyFromCaller(dynMemTraits);
    command->args.hEvent = static_cast<IcdL0Event*>(hEvent)->asRemoteObject();
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
ze_result_t zeFabricVertexGetExp (ze_driver_handle_t hDriver, uint32_t* pCount, ze_fabric_vertex_handle_t* phVertices) {
    log<Verbosity::bloat>("Establishing RPC for zeFabricVertexGetExp");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeFabricVertexGetExpRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hDriver, pCount, phVertices);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hDriver, pCount, phVertices);
    command->copyFromCaller(dynMemTraits);
    command->args.hDriver = hDriver->asLocalObject()->asRemoteObject();


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
ze_result_t zeFabricVertexGetSubVerticesExp (ze_fabric_vertex_handle_t hVertex, uint32_t* pCount, ze_fabric_vertex_handle_t* phSubvertices) {
    log<Verbosity::bloat>("Establishing RPC for zeFabricVertexGetSubVerticesExp");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeFabricVertexGetSubVerticesExpRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hVertex, pCount, phSubvertices);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hVertex, pCount, phSubvertices);
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
ze_result_t zeFabricVertexGetPropertiesExp (ze_fabric_vertex_handle_t hVertex, ze_fabric_vertex_exp_properties_t* pVertexProperties) {
    log<Verbosity::bloat>("Establishing RPC for zeFabricVertexGetPropertiesExp");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeFabricVertexGetPropertiesExpRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hVertex, pVertexProperties);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hVertex, pVertexProperties);
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
ze_result_t zeFabricVertexGetDeviceExp (ze_fabric_vertex_handle_t hVertex, ze_device_handle_t* pDevice) {
    log<Verbosity::bloat>("Establishing RPC for zeFabricVertexGetDeviceExp");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeFabricVertexGetDeviceExpRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hVertex, pDevice);
    command->copyFromCaller();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller();
    if(pDevice)
    {
        pDevice[0] = globalPlatform->translateNewRemoteObjectToLocalObject(pDevice[0], static_cast<ze_device_handle_t>(nullptr));
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeDeviceGetFabricVertexExp (ze_device_handle_t hDevice, ze_fabric_vertex_handle_t* pVertex) {
    log<Verbosity::bloat>("Establishing RPC for zeDeviceGetFabricVertexExp");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeDeviceGetFabricVertexExpRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hDevice, pVertex);
    command->copyFromCaller();
    command->args.hDevice = (hDevice)->asLocalObject()->asRemoteObject();


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
ze_result_t zeFabricEdgeGetExp (ze_fabric_vertex_handle_t hVertexA, ze_fabric_vertex_handle_t hVertexB, uint32_t* pCount, ze_fabric_edge_handle_t* phEdges) {
    log<Verbosity::bloat>("Establishing RPC for zeFabricEdgeGetExp");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeFabricEdgeGetExpRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hVertexA, hVertexB, pCount, phEdges);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hVertexA, hVertexB, pCount, phEdges);
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
ze_result_t zeFabricEdgeGetVerticesExp (ze_fabric_edge_handle_t hEdge, ze_fabric_vertex_handle_t* phVertexA, ze_fabric_vertex_handle_t* phVertexB) {
    log<Verbosity::bloat>("Establishing RPC for zeFabricEdgeGetVerticesExp");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeFabricEdgeGetVerticesExpRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hEdge, phVertexA, phVertexB);
    command->copyFromCaller();


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
ze_result_t zeFabricEdgeGetPropertiesExp (ze_fabric_edge_handle_t hEdge, ze_fabric_edge_exp_properties_t* pEdgeProperties) {
    log<Verbosity::bloat>("Establishing RPC for zeFabricEdgeGetPropertiesExp");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeFabricEdgeGetPropertiesExpRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hEdge, pEdgeProperties);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hEdge, pEdgeProperties);
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
ze_result_t zeFenceCreate (ze_command_queue_handle_t hCommandQueue, const ze_fence_desc_t* desc, ze_fence_handle_t* phFence) {
    log<Verbosity::bloat>("Establishing RPC for zeFenceCreate");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeFenceCreateRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hCommandQueue, desc, phFence);
    command->copyFromCaller();
    command->args.hCommandQueue = hCommandQueue->asLocalObject()->asRemoteObject();
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
        phFence[0] = globalPlatform->translateNewRemoteObjectToLocalObject(phFence[0]);
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeFenceDestroy (ze_fence_handle_t hFence) {
    log<Verbosity::bloat>("Establishing RPC for zeFenceDestroy");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeFenceDestroyRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hFence);
    command->args.hFence = hFence->asLocalObject()->asRemoteObject();


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
ze_result_t zeFenceHostSynchronize (ze_fence_handle_t hFence, uint64_t timeout) {
    log<Verbosity::bloat>("Establishing RPC for zeFenceHostSynchronize");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeFenceHostSynchronizeRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hFence, timeout);
    command->args.hFence = hFence->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    if (ret == ZE_RESULT_SUCCESS) {
        ret = globalPlatform->getHostptrCopiesReader().readMemory(channel, Cal::Client::Icd::icdGlobalState.getGlobalShmemImporter());
    };
    return ret;
}
ze_result_t zeFenceQueryStatus (ze_fence_handle_t hFence) {
    log<Verbosity::bloat>("Establishing RPC for zeFenceQueryStatus");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeFenceQueryStatusRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hFence);
    command->args.hFence = hFence->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    if (ret == ZE_RESULT_SUCCESS) {
        ret = globalPlatform->getHostptrCopiesReader().readMemory(channel, Cal::Client::Icd::icdGlobalState.getGlobalShmemImporter());
    };
    return ret;
}
ze_result_t zeFenceReset (ze_fence_handle_t hFence) {
    log<Verbosity::bloat>("Establishing RPC for zeFenceReset");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeFenceResetRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hFence);
    command->args.hFence = hFence->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeKernelSetGlobalOffsetExp (ze_kernel_handle_t hKernel, uint32_t offsetX, uint32_t offsetY, uint32_t offsetZ) {
    log<Verbosity::bloat>("Establishing RPC for zeKernelSetGlobalOffsetExp");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeKernelSetGlobalOffsetExpRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hKernel, offsetX, offsetY, offsetZ);
    command->args.hKernel = hKernel->asLocalObject()->asRemoteObject();


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
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeImageGetPropertiesRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hDevice, desc, pImageProperties);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hDevice, desc, pImageProperties);
    command->copyFromCaller(dynMemTraits);
    command->captures.reassembleNestedStructs();
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();
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
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeImageCreateRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hContext, hDevice, desc, phImage);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hContext, hDevice, desc, phImage);
    command->copyFromCaller(dynMemTraits);
    command->captures.reassembleNestedStructs();
    command->args.hContext = hContext->asLocalObject()->asRemoteObject();
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();
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
        phImage[0] = globalPlatform->translateNewRemoteObjectToLocalObject(phImage[0]);
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeImageDestroy (ze_image_handle_t hImage) {
    log<Verbosity::bloat>("Establishing RPC for zeImageDestroy");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeImageDestroyRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hImage);
    command->args.hImage = hImage->asLocalObject()->asRemoteObject();


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
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeKernelSchedulingHintExpRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hKernel, pHint);
    command->copyFromCaller();
    command->args.hKernel = hKernel->asLocalObject()->asRemoteObject();
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
ze_result_t zeModuleInspectLinkageExt (ze_linkage_inspection_ext_desc_t* pInspectDesc, uint32_t numModules, ze_module_handle_t* phModules, ze_module_build_log_handle_t* phLog) {
    log<Verbosity::bloat>("Establishing RPC for zeModuleInspectLinkageExt");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeModuleInspectLinkageExtRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(pInspectDesc, numModules, phModules, phLog);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, pInspectDesc, numModules, phModules, phLog);
    command->copyFromCaller(dynMemTraits);
    if(phModules)
    {
        auto base = command->captures.phModules;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phModules.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    if(phLog)
    {
        phLog[0] = globalPlatform->translateNewRemoteObjectToLocalObject(phLog[0]);
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeMemAllocSharedRpcHelper (ze_context_handle_t hContext, const ze_device_mem_alloc_desc_t* device_desc, const ze_host_mem_alloc_desc_t* host_desc, size_t size, size_t alignment, ze_device_handle_t hDevice, void** pptr, Cal::Rpc::LevelZero::ZeMemAllocSharedRpcMImplicitArgs &implArgsForZeMemAllocSharedRpcM) {
    log<Verbosity::bloat>("Establishing RPC for zeMemAllocShared");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeMemAllocSharedRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hContext, device_desc, host_desc, size, alignment, hDevice, pptr);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hContext, device_desc, host_desc, size, alignment, hDevice, pptr);
    command->copyFromCaller(dynMemTraits, implArgsForZeMemAllocSharedRpcM);
    command->captures.reassembleNestedStructs();
    command->args.hContext = hContext->asLocalObject()->asRemoteObject();
    if(device_desc)
    {
        translateRequiredPNextExtensions(command->captures.device_desc.pNext);
    }
    if(hDevice)
    {
        command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();
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
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeMemAllocDeviceRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hContext, device_desc, size, alignment, hDevice, pptr);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hContext, device_desc, size, alignment, hDevice, pptr);
    command->copyFromCaller(dynMemTraits);
    command->captures.reassembleNestedStructs();
    command->args.hContext = hContext->asLocalObject()->asRemoteObject();
    if(device_desc)
    {
        translateRequiredPNextExtensions(command->captures.device_desc.pNext);
    }
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    if(pptr)
    {
        pptr[0] = globalPlatform->validateNewUsmDevicePointer(pptr[0], size);
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeMemAllocHostRpcHelper (ze_context_handle_t hContext, const ze_host_mem_alloc_desc_t* host_desc, size_t size, size_t alignment, void** pptr, Cal::Rpc::LevelZero::ZeMemAllocHostRpcMImplicitArgs &implArgsForZeMemAllocHostRpcM) {
    log<Verbosity::bloat>("Establishing RPC for zeMemAllocHost");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeMemAllocHostRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hContext, host_desc, size, alignment, pptr);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hContext, host_desc, size, alignment, pptr);
    command->copyFromCaller(dynMemTraits, implArgsForZeMemAllocHostRpcM);
    command->args.hContext = hContext->asLocalObject()->asRemoteObject();


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
    Cal::Client::Icd::icdGlobalState.getL0Platform()->getPageFaultManager().unregisterSharedAlloc(ptr);
    Cal::Client::Icd::icdGlobalState.getL0Platform()->invalidateAllKernelArgCaches();
    hContext->asLocalObject()->allocPropertiesCache.invalidateAllocPropertiesCache();
    log<Verbosity::bloat>("Establishing RPC for zeMemFree");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeMemFreeRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hContext, ptr);
    command->args.hContext = hContext->asLocalObject()->asRemoteObject();
    globalPlatform->destroyUsmDescriptor(ptr);


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
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeMemGetAllocPropertiesRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hContext, ptr, pMemAllocProperties, phDevice);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hContext, ptr, pMemAllocProperties, phDevice);
    command->copyFromCaller(dynMemTraits);
    command->args.hContext = hContext->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    if(phDevice)
    {
        phDevice[0] = globalPlatform->translateNewRemoteObjectToLocalObject(phDevice[0], static_cast<ze_device_handle_t>(nullptr));
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeMemGetAddressRange (ze_context_handle_t hContext, const void* ptr, void** pBase, size_t* pSize) {
    log<Verbosity::bloat>("Establishing RPC for zeMemGetAddressRange");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeMemGetAddressRangeRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hContext, ptr, pBase, pSize);
    command->args.hContext = hContext->asLocalObject()->asRemoteObject();


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
    if (!Cal::Client::Icd::icdGlobalState.getL0Platform()->isDeviceUsm(ptr)) {
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;
    }

    log<Verbosity::bloat>("Establishing RPC for zeMemGetIpcHandle");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeMemGetIpcHandleRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hContext, ptr, pIpcHandle);
    command->args.hContext = hContext->asLocalObject()->asRemoteObject();


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
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeMemOpenIpcHandleRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hContext, hDevice, handle, flags, pptr);
    command->args.hContext = hContext->asLocalObject()->asRemoteObject();
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller();
    if(pptr)
    {
        pptr[0] = globalPlatform->openUsmDevicePointerFromIpcHandle(hContext, pptr[0]);
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeMemCloseIpcHandle (ze_context_handle_t hContext, const void* ptr) {
    log<Verbosity::bloat>("Establishing RPC for zeMemCloseIpcHandle");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeMemCloseIpcHandleRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hContext, ptr);
    command->args.hContext = hContext->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zexMemGetIpcHandlesRpcHelper (ze_context_handle_t hContext, const void* ptr, uint32_t* numIpcHandles, ze_ipc_mem_handle_t* pIpcHandles) {
    log<Verbosity::bloat>("Establishing RPC for zexMemGetIpcHandles");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZexMemGetIpcHandlesRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hContext, ptr, numIpcHandles, pIpcHandles);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hContext, ptr, numIpcHandles, pIpcHandles);
    command->copyFromCaller(dynMemTraits);
    command->args.hContext = hContext->asLocalObject()->asRemoteObject();


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
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZexMemOpenIpcHandlesRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hContext, hDevice, numIpcHandles, pIpcHandles, flags, pptr);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hContext, hDevice, numIpcHandles, pIpcHandles, flags, pptr);
    command->copyFromCaller(dynMemTraits);
    command->args.hContext = hContext->asLocalObject()->asRemoteObject();
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    if(pptr)
    {
        pptr[0] = globalPlatform->openUsmDevicePointerFromIpcHandle(hContext, pptr[0]);
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeMemFreeExt (ze_context_handle_t hContext, const ze_memory_free_ext_desc_t* pMemFreeDesc, void* ptr) {
    Cal::Client::Icd::icdGlobalState.getL0Platform()->getPageFaultManager().unregisterSharedAlloc(ptr);
    Cal::Client::Icd::icdGlobalState.getL0Platform()->invalidateAllKernelArgCaches();
    hContext->asLocalObject()->allocPropertiesCache.invalidateAllocPropertiesCache();
    log<Verbosity::bloat>("Establishing RPC for zeMemFreeExt");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeMemFreeExtRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hContext, pMemFreeDesc, ptr);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hContext, pMemFreeDesc, ptr);
    command->copyFromCaller(dynMemTraits);
    command->captures.reassembleNestedStructs();
    command->args.hContext = hContext->asLocalObject()->asRemoteObject();
    if(pMemFreeDesc)
    {
        translateRequiredPNextExtensions(command->captures.pMemFreeDesc.pNext);
    }
    globalPlatform->destroyUsmDescriptor(ptr);


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
ze_result_t zeModuleCreate (ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_module_desc_t* desc, ze_module_handle_t* phModule, ze_module_build_log_handle_t* phBuildLog) {
    log<Verbosity::bloat>("Establishing RPC for zeModuleCreate");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeModuleCreateRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hContext, hDevice, desc, phModule, phBuildLog);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hContext, hDevice, desc, phModule, phBuildLog);
    command->copyFromCaller(dynMemTraits);
    command->args.hContext = hContext->asLocalObject()->asRemoteObject();
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    if(phModule)
    {
        phModule[0] = globalPlatform->translateNewRemoteObjectToLocalObject(phModule[0]);
    }
    if(phBuildLog)
    {
        phBuildLog[0] = globalPlatform->translateNewRemoteObjectToLocalObject(phBuildLog[0]);
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeModuleDestroy (ze_module_handle_t hModule) {
    log<Verbosity::bloat>("Establishing RPC for zeModuleDestroy");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeModuleDestroyRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hModule);
    command->args.hModule = hModule->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    {
        const auto prevRefCount = hModule->asLocalObject()->dec();
        if (prevRefCount == 1u) {
            globalPlatform->removeGlobalPointers(hModule);
        };
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeModuleDynamicLink (uint32_t numModules, ze_module_handle_t* phModules, ze_module_build_log_handle_t* phLinkLog) {
    log<Verbosity::bloat>("Establishing RPC for zeModuleDynamicLink");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeModuleDynamicLinkRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(numModules, phModules, phLinkLog);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, numModules, phModules, phLinkLog);
    command->copyFromCaller(dynMemTraits);
    if(phModules)
    {
        auto base = command->captures.phModules;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phModules.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
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
        phLinkLog[0] = globalPlatform->translateNewRemoteObjectToLocalObject(phLinkLog[0]);
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeModuleBuildLogDestroy (ze_module_build_log_handle_t hModuleBuildLog) {
    log<Verbosity::bloat>("Establishing RPC for zeModuleBuildLogDestroy");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeModuleBuildLogDestroyRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hModuleBuildLog);
    command->args.hModuleBuildLog = hModuleBuildLog->asLocalObject()->asRemoteObject();


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
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeModuleBuildLogGetStringRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hModuleBuildLog, pSize, pBuildLog);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hModuleBuildLog, pSize, pBuildLog);
    command->copyFromCaller(dynMemTraits);
    command->args.hModuleBuildLog = hModuleBuildLog->asLocalObject()->asRemoteObject();


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
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeModuleGetNativeBinaryRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hModule, pSize, pModuleNativeBinary);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hModule, pSize, pModuleNativeBinary);
    command->copyFromCaller(dynMemTraits);
    command->args.hModule = hModule->asLocalObject()->asRemoteObject();


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
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeModuleGetGlobalPointerRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hModule, pGlobalName, pSize, pptr);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hModule, pGlobalName, pSize, pptr);
    command->copyFromCaller(dynMemTraits);
    command->args.hModule = hModule->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    if(pptr)
    {
        command->captures.ret = globalPlatform->recordGlobalPointer(hModule, *pptr) ? command->captures.ret : ZE_RESULT_ERROR_INVALID_ARGUMENT;
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
 // zeModuleGetKernelNames ignored in generator - based on dont_generate_handler flag
ze_result_t zeModuleGetKernelNamesRpcHelper (ze_module_handle_t hModule, uint32_t* totalLength, char* namesBuffer) {
    log<Verbosity::bloat>("Establishing RPC for zeModuleGetKernelNamesRpcHelper");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeModuleGetKernelNamesRpcHelperRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hModule, totalLength, namesBuffer);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hModule, totalLength, namesBuffer);
    command->copyFromCaller(dynMemTraits);
    command->args.hModule = hModule->asLocalObject()->asRemoteObject();


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
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeModuleGetPropertiesRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hModule, pModuleProperties);
    command->copyFromCaller();
    command->args.hModule = hModule->asLocalObject()->asRemoteObject();
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
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeKernelCreateRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hModule, desc, phKernel);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hModule, desc, phKernel);
    command->copyFromCaller(dynMemTraits);
    command->args.hModule = hModule->asLocalObject()->asRemoteObject();
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
        phKernel[0] = globalPlatform->translateNewRemoteObjectToLocalObject(phKernel[0]);
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeKernelDestroy (ze_kernel_handle_t hKernel) {
    log<Verbosity::bloat>("Establishing RPC for zeKernelDestroy");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeKernelDestroyRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hKernel);
    command->args.hKernel = hKernel->asLocalObject()->asRemoteObject();


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
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeModuleGetFunctionPointerRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hModule, pFunctionName, pfnFunction);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hModule, pFunctionName, pfnFunction);
    command->copyFromCaller(dynMemTraits);
    command->args.hModule = hModule->asLocalObject()->asRemoteObject();


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
ze_result_t zeKernelSetGroupSizeRpcHelper (ze_kernel_handle_t hKernel, uint32_t groupSizeX, uint32_t groupSizeY, uint32_t groupSizeZ) {
    log<Verbosity::bloat>("Establishing RPC for zeKernelSetGroupSize");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeKernelSetGroupSizeRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hKernel, groupSizeX, groupSizeY, groupSizeZ);
    command->args.hKernel = hKernel->asLocalObject()->asRemoteObject();

    if(
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeKernelSuggestGroupSizeRpcHelper (ze_kernel_handle_t hKernel, uint32_t globalSizeX, uint32_t globalSizeY, uint32_t globalSizeZ, uint32_t* groupSizeX, uint32_t* groupSizeY, uint32_t* groupSizeZ) {
    log<Verbosity::bloat>("Establishing RPC for zeKernelSuggestGroupSize");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeKernelSuggestGroupSizeRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hKernel, globalSizeX, globalSizeY, globalSizeZ, groupSizeX, groupSizeY, groupSizeZ);
    command->args.hKernel = hKernel->asLocalObject()->asRemoteObject();


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
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeKernelSuggestMaxCooperativeGroupCountRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hKernel, totalGroupCount);
    command->args.hKernel = hKernel->asLocalObject()->asRemoteObject();


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
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeKernelSetArgumentValueRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hKernel, argIndex, argSize, pArgValue);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hKernel, argIndex, argSize, pArgValue);
    command->copyFromCaller(dynMemTraits);
    command->args.hKernel = hKernel->asLocalObject()->asRemoteObject();

    if(
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeKernelSetIndirectAccess (ze_kernel_handle_t hKernel, ze_kernel_indirect_access_flags_t flags) {
    log<Verbosity::bloat>("Establishing RPC for zeKernelSetIndirectAccess");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeKernelSetIndirectAccessRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hKernel, flags);
    command->args.hKernel = hKernel->asLocalObject()->asRemoteObject();

    if(
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    ze_result_t ret = command->captures.ret;

    channelLock.unlock();
    hKernel->asLocalObject()->sharedIndirectAccessSet |= (ZE_KERNEL_INDIRECT_ACCESS_FLAG_SHARED & flags);
    return ret;
}
ze_result_t zeKernelGetIndirectAccess (ze_kernel_handle_t hKernel, ze_kernel_indirect_access_flags_t* pFlags) {
    log<Verbosity::bloat>("Establishing RPC for zeKernelGetIndirectAccess");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeKernelGetIndirectAccessRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hKernel, pFlags);
    command->args.hKernel = hKernel->asLocalObject()->asRemoteObject();


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
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeKernelSetCacheConfigRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hKernel, flags);
    command->args.hKernel = hKernel->asLocalObject()->asRemoteObject();


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
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeKernelGetPropertiesRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hKernel, pKernelProperties);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hKernel, pKernelProperties);
    command->copyFromCaller(dynMemTraits);
    command->args.hKernel = hKernel->asLocalObject()->asRemoteObject();


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
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeKernelGetNameRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hKernel, pSize, pName);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hKernel, pSize, pName);
    command->copyFromCaller(dynMemTraits);
    command->args.hKernel = hKernel->asLocalObject()->asRemoteObject();


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
    hCommandList->asLocalObject()->sharedIndirectAccessSet |= hKernel->asLocalObject()->sharedIndirectAccessSet;
    hCommandList->asLocalObject()->moveKernelArgsToGpu(hKernel->asLocalObject());
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendLaunchKernel");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendLaunchKernelRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    command->args.hKernel = hKernel->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !static_cast<IcdL0CommandList *>(hCommandList)->isImmediateSynchronous() &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    ze_result_t ret = command->captures.ret;

    channelLock.unlock();
    if (hCommandList->asLocalObject()->isImmediate()) { hCommandList->asLocalObject()->sharedIndirectAccessSet = false; };
    return ret;
}
ze_result_t zeCommandListAppendLaunchCooperativeKernel (ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchFuncArgs, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendLaunchCooperativeKernel");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendLaunchCooperativeKernelRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    command->args.hKernel = hKernel->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
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
ze_result_t zeCommandListAppendLaunchKernelIndirect (ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchArgumentsBuffer, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    hCommandList->asLocalObject()->sharedIndirectAccessSet |= hKernel->asLocalObject()->sharedIndirectAccessSet;
    hCommandList->asLocalObject()->moveKernelArgsToGpu(hKernel->asLocalObject());
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendLaunchKernelIndirect");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendLaunchKernelIndirectRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, hKernel, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, hKernel, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    command->args.hKernel = hKernel->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
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
    if (hCommandList->asLocalObject()->isImmediate()) { hCommandList->asLocalObject()->sharedIndirectAccessSet = false; };
    return ret;
}
ze_result_t zeCommandListAppendLaunchMultipleKernelsIndirect (ze_command_list_handle_t hCommandList, uint32_t numKernels, ze_kernel_handle_t* phKernels, const uint32_t* pCountBuffer, const ze_group_count_t* pLaunchArgumentsBuffer, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    for (uint32_t i = 0; i < numKernels; i++) {
        hCommandList->asLocalObject()->sharedIndirectAccessSet |= phKernels[i]->asLocalObject()->sharedIndirectAccessSet;
        hCommandList->asLocalObject()->moveKernelArgsToGpu(phKernels[i]->asLocalObject());
    }
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendLaunchMultipleKernelsIndirect");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendLaunchMultipleKernelsIndirectRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, numKernels, phKernels, pCountBuffer, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, numKernels, phKernels, pCountBuffer, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(phKernels)
    {
        auto base = command->captures.getPhKernels();
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phKernels.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.getPhWaitEvents();
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
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
    if (hCommandList->asLocalObject()->isImmediate()) { hCommandList->asLocalObject()->sharedIndirectAccessSet = false; };
    return ret;
}
ze_result_t zeCommandListHostSynchronize (ze_command_list_handle_t hCommandList, uint64_t timeout) {
    log<Verbosity::bloat>("Establishing RPC for zeCommandListHostSynchronize");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListHostSynchronizeRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hCommandList, timeout);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    if (ret == ZE_RESULT_SUCCESS) {
        ret = globalPlatform->getHostptrCopiesReader().readMemory(channel, Cal::Client::Icd::icdGlobalState.getGlobalShmemImporter());
    };
    return ret;
}
ze_result_t zeDevicePciGetPropertiesExt (ze_device_handle_t hDevice, ze_pci_ext_properties_t* pPciProperties) {
    log<Verbosity::bloat>("Establishing RPC for zeDevicePciGetPropertiesExt");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeDevicePciGetPropertiesExtRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hDevice, pPciProperties);
    command->copyFromCaller();
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();
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
ze_result_t zeContextMakeMemoryResident (ze_context_handle_t hContext, ze_device_handle_t hDevice, void* ptr, size_t size) {
    log<Verbosity::bloat>("Establishing RPC for zeContextMakeMemoryResident");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeContextMakeMemoryResidentRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hContext, hDevice, ptr, size);
    command->args.hContext = hContext->asLocalObject()->asRemoteObject();
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeContextEvictMemory (ze_context_handle_t hContext, ze_device_handle_t hDevice, void* ptr, size_t size) {
    log<Verbosity::bloat>("Establishing RPC for zeContextEvictMemory");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeContextEvictMemoryRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hContext, hDevice, ptr, size);
    command->args.hContext = hContext->asLocalObject()->asRemoteObject();
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeVirtualMemReserve (ze_context_handle_t hContext, const void* pStart, size_t size, void** pptr) {
    log<Verbosity::bloat>("Establishing RPC for zeVirtualMemReserve");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeVirtualMemReserveRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hContext, pStart, size, pptr);
    command->args.hContext = hContext->asLocalObject()->asRemoteObject();


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
ze_result_t zeVirtualMemFree (ze_context_handle_t hContext, const void* ptr, size_t size) {
    log<Verbosity::bloat>("Establishing RPC for zeVirtualMemFree");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeVirtualMemFreeRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hContext, ptr, size);
    command->args.hContext = hContext->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeVirtualMemQueryPageSize (ze_context_handle_t hContext, ze_device_handle_t hDevice, size_t size, size_t* pagesize) {
    log<Verbosity::bloat>("Establishing RPC for zeVirtualMemQueryPageSize");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeVirtualMemQueryPageSizeRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hContext, hDevice, size, pagesize);
    command->copyFromCaller();
    command->args.hContext = hContext->asLocalObject()->asRemoteObject();
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();


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
ze_result_t zePhysicalMemCreate (ze_context_handle_t hContext, ze_device_handle_t hDevice, ze_physical_mem_desc_t* desc, ze_physical_mem_handle_t* phPhysicalMemory) {
    log<Verbosity::bloat>("Establishing RPC for zePhysicalMemCreate");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZePhysicalMemCreateRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hContext, hDevice, desc, phPhysicalMemory);
    command->copyFromCaller();
    command->args.hContext = hContext->asLocalObject()->asRemoteObject();
    command->args.hDevice = hDevice->asLocalObject()->asRemoteObject();


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
ze_result_t zePhysicalMemDestroy (ze_context_handle_t hContext, ze_physical_mem_handle_t hPhysicalMemory) {
    log<Verbosity::bloat>("Establishing RPC for zePhysicalMemDestroy");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZePhysicalMemDestroyRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hContext, hPhysicalMemory);
    command->args.hContext = hContext->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeVirtualMemMap (ze_context_handle_t hContext, const void* ptr, size_t size, ze_physical_mem_handle_t hPhysicalMemory, size_t offset, ze_memory_access_attribute_t access) {
    log<Verbosity::bloat>("Establishing RPC for zeVirtualMemMap");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeVirtualMemMapRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hContext, ptr, size, hPhysicalMemory, offset, access);
    command->args.hContext = hContext->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeVirtualMemUnmap (ze_context_handle_t hContext, const void* ptr, size_t size) {
    log<Verbosity::bloat>("Establishing RPC for zeVirtualMemUnmap");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeVirtualMemUnmapRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hContext, ptr, size);
    command->args.hContext = hContext->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeVirtualMemSetAccessAttribute (ze_context_handle_t hContext, const void* ptr, size_t size, ze_memory_access_attribute_t access) {
    log<Verbosity::bloat>("Establishing RPC for zeVirtualMemSetAccessAttribute");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeVirtualMemSetAccessAttributeRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hContext, ptr, size, access);
    command->args.hContext = hContext->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeVirtualMemGetAccessAttribute (ze_context_handle_t hContext, const void* ptr, size_t size, ze_memory_access_attribute_t* access, size_t* outSize) {
    log<Verbosity::bloat>("Establishing RPC for zeVirtualMemGetAccessAttribute");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeVirtualMemGetAccessAttributeRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hContext, ptr, size, access, outSize);
    command->copyFromCaller();
    command->args.hContext = hContext->asLocalObject()->asRemoteObject();


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
ze_result_t zexDriverImportExternalPointerRpcHelper (ze_driver_handle_t hDriver, void* ptr, size_t size) {
    log<Verbosity::bloat>("Establishing RPC for zexDriverImportExternalPointer");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZexDriverImportExternalPointerRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hDriver, ptr, size);
    command->args.hDriver = hDriver->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zexDriverReleaseImportedPointerRpcHelper (ze_driver_handle_t hDriver, void* ptr) {
    log<Verbosity::bloat>("Establishing RPC for zexDriverReleaseImportedPointer");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZexDriverReleaseImportedPointerRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hDriver, ptr);
    command->args.hDriver = hDriver->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zexDriverGetHostPointerBaseAddressRpcHelper (ze_driver_handle_t hDriver, void* ptr, void** baseAddress) {
    log<Verbosity::bloat>("Establishing RPC for zexDriverGetHostPointerBaseAddress");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZexDriverGetHostPointerBaseAddressRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(hDriver, ptr, baseAddress);
    command->copyFromCaller();
    command->args.hDriver = hDriver->asLocalObject()->asRemoteObject();


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
ze_result_t zeCommandListAppendMemoryCopyDeferred_Usm_Usm (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = usm;
    [[maybe_unused]] constexpr auto srcptr_kind = usm;
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyDeferred_Usm_Usm");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyDeferred_Usm_UsmRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
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
ze_result_t zeCommandListAppendMemoryCopyDeferred_Usm_Shared (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = usm;
    [[maybe_unused]] constexpr auto srcptr_kind = shared;
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyDeferred_Usm_Shared");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyDeferred_Usm_SharedRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
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
ze_result_t zeCommandListAppendMemoryCopyDeferred_Usm_Remapped (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = usm;
    [[maybe_unused]] constexpr auto srcptr_kind = remapped;
    hCommandList->asLocalObject()->registerMemoryToWrite(srcptr, size);
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyDeferred_Usm_Remapped");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyDeferred_Usm_RemappedRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
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
ze_result_t zeCommandListAppendMemoryCopyDeferred_Shared_Usm (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = shared;
    [[maybe_unused]] constexpr auto srcptr_kind = usm;
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyDeferred_Shared_Usm");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyDeferred_Shared_UsmRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
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
ze_result_t zeCommandListAppendMemoryCopyDeferred_Shared_Shared (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = shared;
    [[maybe_unused]] constexpr auto srcptr_kind = shared;
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyDeferred_Shared_Shared");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyDeferred_Shared_SharedRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
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
ze_result_t zeCommandListAppendMemoryCopyDeferred_Shared_Remapped (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = shared;
    [[maybe_unused]] constexpr auto srcptr_kind = remapped;
    hCommandList->asLocalObject()->registerMemoryToWrite(srcptr, size);
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyDeferred_Shared_Remapped");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyDeferred_Shared_RemappedRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
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
ze_result_t zeCommandListAppendMemoryCopyDeferred_Remapped_Usm (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = remapped;
    [[maybe_unused]] constexpr auto srcptr_kind = usm;
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyDeferred_Remapped_Usm");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyDeferred_Remapped_UsmRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
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
ze_result_t zeCommandListAppendMemoryCopyDeferred_Remapped_Shared (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = remapped;
    [[maybe_unused]] constexpr auto srcptr_kind = shared;
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyDeferred_Remapped_Shared");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyDeferred_Remapped_SharedRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
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
ze_result_t zeCommandListAppendMemoryCopyDeferred_Remapped_Remapped (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = remapped;
    [[maybe_unused]] constexpr auto srcptr_kind = remapped;
    hCommandList->asLocalObject()->registerMemoryToWrite(srcptr, size);
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyDeferred_Remapped_Remapped");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyDeferred_Remapped_RemappedRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
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
ze_result_t zeCommandListAppendMemoryCopyImmediate_Local_Local (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = local;
    [[maybe_unused]] constexpr auto srcptr_kind = local;
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyImmediate_Local_Local");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    void *standalone_dstptr{};
    {
        std::unique_ptr<void, std::function<void(void*)>> standalone_dstptr_alloc(static_cast<IcdL0CommandList *>(hCommandList)->context->getStagingAreaManager().allocateStagingArea(size), [hCommandList](void *ptrToMarkAsUnused){static_cast<IcdL0CommandList *>(hCommandList)->context->getStagingAreaManager().releaseStagingArea(ptrToMarkAsUnused);});
        standalone_dstptr = standalone_dstptr_alloc.get();
        globalPlatform->getHostptrCopiesReader().addToMap(standalone_dstptr, reinterpret_cast<uintptr_t>(dstptr));
    hCommandList->asLocalObject()->registerTemporaryAllocation(std::move(standalone_dstptr_alloc));
    }
    void *standalone_srcptr{};
    {
        std::unique_ptr<void, std::function<void(void*)>> standalone_srcptr_alloc(static_cast<IcdL0CommandList *>(hCommandList)->context->getStagingAreaManager().allocateStagingArea(size), [hCommandList](void *ptrToMarkAsUnused){static_cast<IcdL0CommandList *>(hCommandList)->context->getStagingAreaManager().releaseStagingArea(ptrToMarkAsUnused);});
        standalone_srcptr = standalone_srcptr_alloc.get();
        globalPlatform->getHostptrCopiesReader().addToMap(standalone_srcptr, reinterpret_cast<uintptr_t>(srcptr));
    hCommandList->asLocalObject()->registerTemporaryAllocation(std::move(standalone_srcptr_alloc));
    }
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediate_Local_LocalRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    memcpy(Cal::Utils::toAddress(standalone_srcptr), srcptr, size);
    command->copyFromCaller(dynMemTraits);
    command->args.dstptr = standalone_dstptr;
    command->args.srcptr = standalone_srcptr;
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !static_cast<IcdL0CommandList *>(hCommandList)->isImmediateSynchronous() &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemoryCopyImmediate_Local_Usm (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = local;
    [[maybe_unused]] constexpr auto srcptr_kind = usm;
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyImmediate_Local_Usm");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    void *standalone_dstptr{};
    {
        std::unique_ptr<void, std::function<void(void*)>> standalone_dstptr_alloc(static_cast<IcdL0CommandList *>(hCommandList)->context->getStagingAreaManager().allocateStagingArea(size), [hCommandList](void *ptrToMarkAsUnused){static_cast<IcdL0CommandList *>(hCommandList)->context->getStagingAreaManager().releaseStagingArea(ptrToMarkAsUnused);});
        standalone_dstptr = standalone_dstptr_alloc.get();
        globalPlatform->getHostptrCopiesReader().addToMap(standalone_dstptr, reinterpret_cast<uintptr_t>(dstptr));
    hCommandList->asLocalObject()->registerTemporaryAllocation(std::move(standalone_dstptr_alloc));
    }
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediate_Local_UsmRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.dstptr = standalone_dstptr;
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !static_cast<IcdL0CommandList *>(hCommandList)->isImmediateSynchronous() &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemoryCopyImmediate_Local_Shared (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = local;
    [[maybe_unused]] constexpr auto srcptr_kind = shared;
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyImmediate_Local_Shared");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    void *standalone_dstptr{};
    {
        std::unique_ptr<void, std::function<void(void*)>> standalone_dstptr_alloc(static_cast<IcdL0CommandList *>(hCommandList)->context->getStagingAreaManager().allocateStagingArea(size), [hCommandList](void *ptrToMarkAsUnused){static_cast<IcdL0CommandList *>(hCommandList)->context->getStagingAreaManager().releaseStagingArea(ptrToMarkAsUnused);});
        standalone_dstptr = standalone_dstptr_alloc.get();
        globalPlatform->getHostptrCopiesReader().addToMap(standalone_dstptr, reinterpret_cast<uintptr_t>(dstptr));
    hCommandList->asLocalObject()->registerTemporaryAllocation(std::move(standalone_dstptr_alloc));
    }
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediate_Local_SharedRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.dstptr = standalone_dstptr;
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !static_cast<IcdL0CommandList *>(hCommandList)->isImmediateSynchronous() &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemoryCopyImmediate_Usm_Local (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = usm;
    [[maybe_unused]] constexpr auto srcptr_kind = local;
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyImmediate_Usm_Local");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    void *standalone_srcptr{};
    {
        std::unique_ptr<void, std::function<void(void*)>> standalone_srcptr_alloc(static_cast<IcdL0CommandList *>(hCommandList)->context->getStagingAreaManager().allocateStagingArea(size), [hCommandList](void *ptrToMarkAsUnused){static_cast<IcdL0CommandList *>(hCommandList)->context->getStagingAreaManager().releaseStagingArea(ptrToMarkAsUnused);});
        standalone_srcptr = standalone_srcptr_alloc.get();
        globalPlatform->getHostptrCopiesReader().addToMap(standalone_srcptr, reinterpret_cast<uintptr_t>(srcptr));
    hCommandList->asLocalObject()->registerTemporaryAllocation(std::move(standalone_srcptr_alloc));
    }
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediate_Usm_LocalRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    memcpy(Cal::Utils::toAddress(standalone_srcptr), srcptr, size);
    command->copyFromCaller(dynMemTraits);
    command->args.srcptr = standalone_srcptr;
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !static_cast<IcdL0CommandList *>(hCommandList)->isImmediateSynchronous() &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemoryCopyImmediate_Usm_Usm (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = usm;
    [[maybe_unused]] constexpr auto srcptr_kind = usm;
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyImmediate_Usm_Usm");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediate_Usm_UsmRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !static_cast<IcdL0CommandList *>(hCommandList)->isImmediateSynchronous() &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemoryCopyImmediate_Usm_Shared (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = usm;
    [[maybe_unused]] constexpr auto srcptr_kind = shared;
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyImmediate_Usm_Shared");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediate_Usm_SharedRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !static_cast<IcdL0CommandList *>(hCommandList)->isImmediateSynchronous() &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemoryCopyImmediate_Shared_Local (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = shared;
    [[maybe_unused]] constexpr auto srcptr_kind = local;
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyImmediate_Shared_Local");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    void *standalone_srcptr{};
    {
        std::unique_ptr<void, std::function<void(void*)>> standalone_srcptr_alloc(static_cast<IcdL0CommandList *>(hCommandList)->context->getStagingAreaManager().allocateStagingArea(size), [hCommandList](void *ptrToMarkAsUnused){static_cast<IcdL0CommandList *>(hCommandList)->context->getStagingAreaManager().releaseStagingArea(ptrToMarkAsUnused);});
        standalone_srcptr = standalone_srcptr_alloc.get();
        globalPlatform->getHostptrCopiesReader().addToMap(standalone_srcptr, reinterpret_cast<uintptr_t>(srcptr));
    hCommandList->asLocalObject()->registerTemporaryAllocation(std::move(standalone_srcptr_alloc));
    }
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediate_Shared_LocalRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    memcpy(Cal::Utils::toAddress(standalone_srcptr), srcptr, size);
    command->copyFromCaller(dynMemTraits);
    command->args.srcptr = standalone_srcptr;
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !static_cast<IcdL0CommandList *>(hCommandList)->isImmediateSynchronous() &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemoryCopyImmediate_Shared_Usm (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = shared;
    [[maybe_unused]] constexpr auto srcptr_kind = usm;
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyImmediate_Shared_Usm");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediate_Shared_UsmRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !static_cast<IcdL0CommandList *>(hCommandList)->isImmediateSynchronous() &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemoryCopyImmediate_Shared_Shared (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = shared;
    [[maybe_unused]] constexpr auto srcptr_kind = shared;
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyImmediate_Shared_Shared");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediate_Shared_SharedRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !static_cast<IcdL0CommandList *>(hCommandList)->isImmediateSynchronous() &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemoryCopyImmediateSynchronous_Local_Local (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = local;
    [[maybe_unused]] constexpr auto srcptr_kind = local;
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyImmediateSynchronous_Local_Local");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateSynchronous_Local_LocalRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.getPhWaitEvents();
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !static_cast<IcdL0CommandList *>(hCommandList)->isImmediateSynchronous() &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    command->copyToCaller(dynMemTraits);
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemoryCopyImmediateSynchronous_Local_Usm (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = local;
    [[maybe_unused]] constexpr auto srcptr_kind = usm;
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyImmediateSynchronous_Local_Usm");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateSynchronous_Local_UsmRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.getPhWaitEvents();
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !static_cast<IcdL0CommandList *>(hCommandList)->isImmediateSynchronous() &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    command->copyToCaller(dynMemTraits);
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemoryCopyImmediateSynchronous_Local_Shared (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = local;
    [[maybe_unused]] constexpr auto srcptr_kind = shared;
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyImmediateSynchronous_Local_Shared");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateSynchronous_Local_SharedRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.getPhWaitEvents();
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !static_cast<IcdL0CommandList *>(hCommandList)->isImmediateSynchronous() &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    command->copyToCaller(dynMemTraits);
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemoryCopyImmediateSynchronous_Usm_Local (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = usm;
    [[maybe_unused]] constexpr auto srcptr_kind = local;
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyImmediateSynchronous_Usm_Local");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateSynchronous_Usm_LocalRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.getPhWaitEvents();
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !static_cast<IcdL0CommandList *>(hCommandList)->isImmediateSynchronous() &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemoryCopyImmediateSynchronous_Usm_Usm (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = usm;
    [[maybe_unused]] constexpr auto srcptr_kind = usm;
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyImmediateSynchronous_Usm_Usm");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateSynchronous_Usm_UsmRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !static_cast<IcdL0CommandList *>(hCommandList)->isImmediateSynchronous() &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemoryCopyImmediateSynchronous_Usm_Shared (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = usm;
    [[maybe_unused]] constexpr auto srcptr_kind = shared;
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyImmediateSynchronous_Usm_Shared");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateSynchronous_Usm_SharedRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !static_cast<IcdL0CommandList *>(hCommandList)->isImmediateSynchronous() &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemoryCopyImmediateSynchronous_Shared_Local (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = shared;
    [[maybe_unused]] constexpr auto srcptr_kind = local;
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyImmediateSynchronous_Shared_Local");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateSynchronous_Shared_LocalRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.getPhWaitEvents();
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !static_cast<IcdL0CommandList *>(hCommandList)->isImmediateSynchronous() &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemoryCopyImmediateSynchronous_Shared_Usm (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = shared;
    [[maybe_unused]] constexpr auto srcptr_kind = usm;
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyImmediateSynchronous_Shared_Usm");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateSynchronous_Shared_UsmRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !static_cast<IcdL0CommandList *>(hCommandList)->isImmediateSynchronous() &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemoryCopyImmediateSynchronous_Shared_Shared (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = shared;
    [[maybe_unused]] constexpr auto srcptr_kind = shared;
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyImmediateSynchronous_Shared_Shared");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyImmediateSynchronous_Shared_SharedRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !static_cast<IcdL0CommandList *>(hCommandList)->isImmediateSynchronous() &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemoryCopyRegionDeferred_Usm_Usm (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = usm;
    [[maybe_unused]] constexpr auto srcptr_kind = usm;
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyRegionDeferred_Usm_Usm");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRegionDeferred_Usm_UsmRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
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
ze_result_t zeCommandListAppendMemoryCopyRegionDeferred_Usm_Shared (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = usm;
    [[maybe_unused]] constexpr auto srcptr_kind = shared;
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyRegionDeferred_Usm_Shared");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRegionDeferred_Usm_SharedRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
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
ze_result_t zeCommandListAppendMemoryCopyRegionDeferred_Usm_Remapped (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = usm;
    [[maybe_unused]] constexpr auto srcptr_kind = remapped;
    hCommandList->asLocalObject()->registerMemoryToWrite(srcptr, getTotalSizeForCopyRegion(srcRegion, srcPitch, srcSlicePitch));
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyRegionDeferred_Usm_Remapped");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRegionDeferred_Usm_RemappedRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
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
ze_result_t zeCommandListAppendMemoryCopyRegionDeferred_Shared_Usm (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = shared;
    [[maybe_unused]] constexpr auto srcptr_kind = usm;
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyRegionDeferred_Shared_Usm");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRegionDeferred_Shared_UsmRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
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
ze_result_t zeCommandListAppendMemoryCopyRegionDeferred_Shared_Shared (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = shared;
    [[maybe_unused]] constexpr auto srcptr_kind = shared;
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyRegionDeferred_Shared_Shared");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRegionDeferred_Shared_SharedRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
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
ze_result_t zeCommandListAppendMemoryCopyRegionDeferred_Shared_Remapped (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = shared;
    [[maybe_unused]] constexpr auto srcptr_kind = remapped;
    hCommandList->asLocalObject()->registerMemoryToWrite(srcptr, getTotalSizeForCopyRegion(srcRegion, srcPitch, srcSlicePitch));
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyRegionDeferred_Shared_Remapped");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRegionDeferred_Shared_RemappedRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
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
ze_result_t zeCommandListAppendMemoryCopyRegionDeferred_Remapped_Usm (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = remapped;
    [[maybe_unused]] constexpr auto srcptr_kind = usm;
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyRegionDeferred_Remapped_Usm");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRegionDeferred_Remapped_UsmRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
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
ze_result_t zeCommandListAppendMemoryCopyRegionDeferred_Remapped_Shared (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = remapped;
    [[maybe_unused]] constexpr auto srcptr_kind = shared;
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyRegionDeferred_Remapped_Shared");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRegionDeferred_Remapped_SharedRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
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
ze_result_t zeCommandListAppendMemoryCopyRegionDeferred_Remapped_Remapped (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = remapped;
    [[maybe_unused]] constexpr auto srcptr_kind = remapped;
    hCommandList->asLocalObject()->registerMemoryToWrite(srcptr, getTotalSizeForCopyRegion(srcRegion, srcPitch, srcSlicePitch));
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyRegionDeferred_Remapped_Remapped");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRegionDeferred_Remapped_RemappedRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
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
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateSynchronous_Local_Usm (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = local;
    [[maybe_unused]] constexpr auto srcptr_kind = usm;
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyRegionImmediateSynchronous_Local_Usm");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRegionImmediateSynchronous_Local_UsmRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.getPhWaitEvents();
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !static_cast<IcdL0CommandList *>(hCommandList)->isImmediateSynchronous() &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    command->copyToCaller(dynMemTraits);
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateSynchronous_Local_Shared (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = local;
    [[maybe_unused]] constexpr auto srcptr_kind = shared;
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyRegionImmediateSynchronous_Local_Shared");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRegionImmediateSynchronous_Local_SharedRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.getPhWaitEvents();
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !static_cast<IcdL0CommandList *>(hCommandList)->isImmediateSynchronous() &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    command->copyToCaller(dynMemTraits);
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateSynchronous_Local_Remapped (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = local;
    [[maybe_unused]] constexpr auto srcptr_kind = remapped;
    hCommandList->asLocalObject()->registerMemoryToWrite(srcptr, getTotalSizeForCopyRegion(srcRegion, srcPitch, srcSlicePitch));
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyRegionImmediateSynchronous_Local_Remapped");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRegionImmediateSynchronous_Local_RemappedRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.getPhWaitEvents();
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !static_cast<IcdL0CommandList *>(hCommandList)->isImmediateSynchronous() &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    command->copyToCaller(dynMemTraits);
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateSynchronous_Usm_Usm (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = usm;
    [[maybe_unused]] constexpr auto srcptr_kind = usm;
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyRegionImmediateSynchronous_Usm_Usm");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRegionImmediateSynchronous_Usm_UsmRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !static_cast<IcdL0CommandList *>(hCommandList)->isImmediateSynchronous() &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateSynchronous_Usm_Shared (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = usm;
    [[maybe_unused]] constexpr auto srcptr_kind = shared;
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyRegionImmediateSynchronous_Usm_Shared");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRegionImmediateSynchronous_Usm_SharedRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !static_cast<IcdL0CommandList *>(hCommandList)->isImmediateSynchronous() &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateSynchronous_Usm_Remapped (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = usm;
    [[maybe_unused]] constexpr auto srcptr_kind = remapped;
    hCommandList->asLocalObject()->registerMemoryToWrite(srcptr, getTotalSizeForCopyRegion(srcRegion, srcPitch, srcSlicePitch));
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyRegionImmediateSynchronous_Usm_Remapped");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRegionImmediateSynchronous_Usm_RemappedRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !static_cast<IcdL0CommandList *>(hCommandList)->isImmediateSynchronous() &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateSynchronous_Shared_Usm (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = shared;
    [[maybe_unused]] constexpr auto srcptr_kind = usm;
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyRegionImmediateSynchronous_Shared_Usm");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRegionImmediateSynchronous_Shared_UsmRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !static_cast<IcdL0CommandList *>(hCommandList)->isImmediateSynchronous() &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateSynchronous_Shared_Shared (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = shared;
    [[maybe_unused]] constexpr auto srcptr_kind = shared;
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyRegionImmediateSynchronous_Shared_Shared");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRegionImmediateSynchronous_Shared_SharedRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !static_cast<IcdL0CommandList *>(hCommandList)->isImmediateSynchronous() &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateSynchronous_Shared_Remapped (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = shared;
    [[maybe_unused]] constexpr auto srcptr_kind = remapped;
    hCommandList->asLocalObject()->registerMemoryToWrite(srcptr, getTotalSizeForCopyRegion(srcRegion, srcPitch, srcSlicePitch));
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyRegionImmediateSynchronous_Shared_Remapped");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRegionImmediateSynchronous_Shared_RemappedRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !static_cast<IcdL0CommandList *>(hCommandList)->isImmediateSynchronous() &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Local_Usm (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = local;
    [[maybe_unused]] constexpr auto srcptr_kind = usm;
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Local_Usm");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    void *standalone_dstptr{};
    {
        std::unique_ptr<void, std::function<void(void*)>> standalone_dstptr_alloc(static_cast<IcdL0CommandList *>(hCommandList)->context->getStagingAreaManager().allocateStagingArea(getTotalSizeForCopyRegion(dstRegion, dstPitch, dstSlicePitch)), [hCommandList](void *ptrToMarkAsUnused){static_cast<IcdL0CommandList *>(hCommandList)->context->getStagingAreaManager().releaseStagingArea(ptrToMarkAsUnused);});
        standalone_dstptr = standalone_dstptr_alloc.get();
        globalPlatform->getHostptrCopiesReader().addToMap(standalone_dstptr, reinterpret_cast<uintptr_t>(dstptr));
    hCommandList->asLocalObject()->registerTemporaryAllocation(std::move(standalone_dstptr_alloc));
    }
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Local_UsmRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.dstptr = standalone_dstptr;
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !static_cast<IcdL0CommandList *>(hCommandList)->isImmediateSynchronous() &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Local_Shared (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = local;
    [[maybe_unused]] constexpr auto srcptr_kind = shared;
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Local_Shared");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    void *standalone_dstptr{};
    {
        std::unique_ptr<void, std::function<void(void*)>> standalone_dstptr_alloc(static_cast<IcdL0CommandList *>(hCommandList)->context->getStagingAreaManager().allocateStagingArea(getTotalSizeForCopyRegion(dstRegion, dstPitch, dstSlicePitch)), [hCommandList](void *ptrToMarkAsUnused){static_cast<IcdL0CommandList *>(hCommandList)->context->getStagingAreaManager().releaseStagingArea(ptrToMarkAsUnused);});
        standalone_dstptr = standalone_dstptr_alloc.get();
        globalPlatform->getHostptrCopiesReader().addToMap(standalone_dstptr, reinterpret_cast<uintptr_t>(dstptr));
    hCommandList->asLocalObject()->registerTemporaryAllocation(std::move(standalone_dstptr_alloc));
    }
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Local_SharedRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.dstptr = standalone_dstptr;
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !static_cast<IcdL0CommandList *>(hCommandList)->isImmediateSynchronous() &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Local_Remapped (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = local;
    [[maybe_unused]] constexpr auto srcptr_kind = remapped;
    hCommandList->asLocalObject()->registerMemoryToWrite(srcptr, getTotalSizeForCopyRegion(srcRegion, srcPitch, srcSlicePitch));
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Local_Remapped");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    void *standalone_dstptr{};
    {
        std::unique_ptr<void, std::function<void(void*)>> standalone_dstptr_alloc(static_cast<IcdL0CommandList *>(hCommandList)->context->getStagingAreaManager().allocateStagingArea(getTotalSizeForCopyRegion(dstRegion, dstPitch, dstSlicePitch)), [hCommandList](void *ptrToMarkAsUnused){static_cast<IcdL0CommandList *>(hCommandList)->context->getStagingAreaManager().releaseStagingArea(ptrToMarkAsUnused);});
        standalone_dstptr = standalone_dstptr_alloc.get();
        globalPlatform->getHostptrCopiesReader().addToMap(standalone_dstptr, reinterpret_cast<uintptr_t>(dstptr));
    hCommandList->asLocalObject()->registerTemporaryAllocation(std::move(standalone_dstptr_alloc));
    }
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Local_RemappedRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.dstptr = standalone_dstptr;
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !static_cast<IcdL0CommandList *>(hCommandList)->isImmediateSynchronous() &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Usm_Usm (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = usm;
    [[maybe_unused]] constexpr auto srcptr_kind = usm;
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Usm_Usm");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Usm_UsmRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !static_cast<IcdL0CommandList *>(hCommandList)->isImmediateSynchronous() &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Usm_Shared (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = usm;
    [[maybe_unused]] constexpr auto srcptr_kind = shared;
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Usm_Shared");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Usm_SharedRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !static_cast<IcdL0CommandList *>(hCommandList)->isImmediateSynchronous() &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Usm_Remapped (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = usm;
    [[maybe_unused]] constexpr auto srcptr_kind = remapped;
    hCommandList->asLocalObject()->registerMemoryToWrite(srcptr, getTotalSizeForCopyRegion(srcRegion, srcPitch, srcSlicePitch));
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Usm_Remapped");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Usm_RemappedRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !static_cast<IcdL0CommandList *>(hCommandList)->isImmediateSynchronous() &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Shared_Usm (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = shared;
    [[maybe_unused]] constexpr auto srcptr_kind = usm;
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Shared_Usm");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Shared_UsmRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !static_cast<IcdL0CommandList *>(hCommandList)->isImmediateSynchronous() &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Shared_Shared (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = shared;
    [[maybe_unused]] constexpr auto srcptr_kind = shared;
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Shared_Shared");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Shared_SharedRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !static_cast<IcdL0CommandList *>(hCommandList)->isImmediateSynchronous() &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Shared_Remapped (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = shared;
    [[maybe_unused]] constexpr auto srcptr_kind = remapped;
    hCommandList->asLocalObject()->registerMemoryToWrite(srcptr, getTotalSizeForCopyRegion(srcRegion, srcPitch, srcSlicePitch));
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Shared_Remapped");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Shared_RemappedRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !static_cast<IcdL0CommandList *>(hCommandList)->isImmediateSynchronous() &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemoryCopyFromContextDeferred_Usm_Usm (ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = usm;
    [[maybe_unused]] constexpr auto srcptr_kind = usm;
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyFromContextDeferred_Usm_Usm");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyFromContextDeferred_Usm_UsmRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, hContextSrc, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, hContextSrc, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    command->args.hContextSrc = hContextSrc->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
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
ze_result_t zeCommandListAppendMemoryCopyFromContextDeferred_Shared_Usm (ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = shared;
    [[maybe_unused]] constexpr auto srcptr_kind = usm;
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyFromContextDeferred_Shared_Usm");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyFromContextDeferred_Shared_UsmRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, hContextSrc, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, hContextSrc, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    command->args.hContextSrc = hContextSrc->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
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
ze_result_t zeCommandListAppendMemoryCopyFromContextDeferred_Remapped_Usm (ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = remapped;
    [[maybe_unused]] constexpr auto srcptr_kind = usm;
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyFromContextDeferred_Remapped_Usm");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyFromContextDeferred_Remapped_UsmRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, hContextSrc, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, hContextSrc, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    command->args.hContextSrc = hContextSrc->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
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
ze_result_t zeCommandListAppendMemoryCopyFromContextImmediateSynchronous_Local_Usm (ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = local;
    [[maybe_unused]] constexpr auto srcptr_kind = usm;
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyFromContextImmediateSynchronous_Local_Usm");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyFromContextImmediateSynchronous_Local_UsmRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, hContextSrc, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, hContextSrc, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    command->args.hContextSrc = hContextSrc->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.getPhWaitEvents();
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !static_cast<IcdL0CommandList *>(hCommandList)->isImmediateSynchronous() &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    command->copyToCaller(dynMemTraits);
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemoryCopyFromContextImmediateSynchronous_Usm_Usm (ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = usm;
    [[maybe_unused]] constexpr auto srcptr_kind = usm;
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyFromContextImmediateSynchronous_Usm_Usm");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyFromContextImmediateSynchronous_Usm_UsmRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, hContextSrc, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, hContextSrc, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    command->args.hContextSrc = hContextSrc->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !static_cast<IcdL0CommandList *>(hCommandList)->isImmediateSynchronous() &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemoryCopyFromContextImmediateSynchronous_Shared_Usm (ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = shared;
    [[maybe_unused]] constexpr auto srcptr_kind = usm;
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyFromContextImmediateSynchronous_Shared_Usm");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyFromContextImmediateSynchronous_Shared_UsmRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, hContextSrc, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, hContextSrc, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    command->args.hContextSrc = hContextSrc->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !static_cast<IcdL0CommandList *>(hCommandList)->isImmediateSynchronous() &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemoryCopyFromContextImmediateAsynchronous_Local_Usm (ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = local;
    [[maybe_unused]] constexpr auto srcptr_kind = usm;
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyFromContextImmediateAsynchronous_Local_Usm");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    void *standalone_dstptr{};
    {
        std::unique_ptr<void, std::function<void(void*)>> standalone_dstptr_alloc(static_cast<IcdL0CommandList *>(hCommandList)->context->getStagingAreaManager().allocateStagingArea(size), [hCommandList](void *ptrToMarkAsUnused){static_cast<IcdL0CommandList *>(hCommandList)->context->getStagingAreaManager().releaseStagingArea(ptrToMarkAsUnused);});
        standalone_dstptr = standalone_dstptr_alloc.get();
        globalPlatform->getHostptrCopiesReader().addToMap(standalone_dstptr, reinterpret_cast<uintptr_t>(dstptr));
    hCommandList->asLocalObject()->registerTemporaryAllocation(std::move(standalone_dstptr_alloc));
    }
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyFromContextImmediateAsynchronous_Local_UsmRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, hContextSrc, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, hContextSrc, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.dstptr = standalone_dstptr;
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    command->args.hContextSrc = hContextSrc->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !static_cast<IcdL0CommandList *>(hCommandList)->isImmediateSynchronous() &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemoryCopyFromContextImmediateAsynchronous_Usm_Usm (ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = usm;
    [[maybe_unused]] constexpr auto srcptr_kind = usm;
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyFromContextImmediateAsynchronous_Usm_Usm");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyFromContextImmediateAsynchronous_Usm_UsmRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, hContextSrc, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, hContextSrc, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    command->args.hContextSrc = hContextSrc->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !static_cast<IcdL0CommandList *>(hCommandList)->isImmediateSynchronous() &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}
ze_result_t zeCommandListAppendMemoryCopyFromContextImmediateAsynchronous_Shared_Usm (ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    [[maybe_unused]] constexpr auto dstptr_kind = shared;
    [[maybe_unused]] constexpr auto srcptr_kind = usm;
    log<Verbosity::bloat>("Establishing RPC for zeCommandListAppendMemoryCopyFromContextImmediateAsynchronous_Shared_Usm");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getL0Platform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::LevelZero::ZeCommandListAppendMemoryCopyFromContextImmediateAsynchronous_Shared_UsmRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(hCommandList, dstptr, hContextSrc, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, hCommandList, dstptr, hContextSrc, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
    command->copyFromCaller(dynMemTraits);
    command->args.hCommandList = hCommandList->asLocalObject()->asRemoteObject();
    command->args.hContextSrc = hContextSrc->asLocalObject()->asRemoteObject();
    if(hSignalEvent)
    {
        command->args.hSignalEvent = hSignalEvent->asLocalObject()->asRemoteObject();
    }
    if(phWaitEvents)
    {
        auto base = command->captures.phWaitEvents;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.phWaitEvents.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !static_cast<IcdL0CommandList *>(hCommandList)->isImmediateSynchronous() &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    ze_result_t ret = command->captures.ret;

    return ret;
}

void *getL0ExtensionFuncionAddressRpcHelper(const char *funcName) {
    if(0 == strcmp("zexMemGetIpcHandles", funcName)) {
        return reinterpret_cast<void*>(Cal::Client::Icd::LevelZero::zexMemGetIpcHandles);
    }
    if(0 == strcmp("zexMemOpenIpcHandles", funcName)) {
        return reinterpret_cast<void*>(Cal::Client::Icd::LevelZero::zexMemOpenIpcHandles);
    }
    if(0 == strcmp("zexDriverImportExternalPointer", funcName)) {
        return reinterpret_cast<void*>(Cal::Client::Icd::LevelZero::zexDriverImportExternalPointer);
    }
    if(0 == strcmp("zexDriverReleaseImportedPointer", funcName)) {
        return reinterpret_cast<void*>(Cal::Client::Icd::LevelZero::zexDriverReleaseImportedPointer);
    }
    if(0 == strcmp("zexDriverGetHostPointerBaseAddress", funcName)) {
        return reinterpret_cast<void*>(Cal::Client::Icd::LevelZero::zexDriverGetHostPointerBaseAddress);
    }
    return nullptr;
}

ze_result_t zeCommandListAppendMemoryRangesBarrier_WithTracing(ze_command_list_handle_t hCommandList, uint32_t numRanges, const size_t* pRangeSizes, const void** pRanges, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeCommandListAppendMemoryRangesBarrier,
                                    hCommandList, numRanges, pRangeSizes, pRanges, hSignalEvent, numWaitEvents, phWaitEvents);

    ze_command_list_append_memory_ranges_barrier_params_t tracerParams;
    tracerParams.phCommandList = &hCommandList;
    tracerParams.pnumRanges = &numRanges;
    tracerParams.ppRangeSizes = &pRangeSizes;
    tracerParams.ppRanges = &pRanges;
    tracerParams.phSignalEvent = &hSignalEvent;
    tracerParams.pnumWaitEvents = &numWaitEvents;
    tracerParams.pphWaitEvents = &phWaitEvents;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnCommandListAppendMemoryRangesBarrierCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnCommandListAppendMemoryRangesBarrierCb_t, CommandList, pfnAppendMemoryRangesBarrierCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeCommandListAppendMemoryRangesBarrier,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phCommandList, *tracerParams.pnumRanges, *tracerParams.ppRangeSizes, *tracerParams.ppRanges, *tracerParams.phSignalEvent, *tracerParams.pnumWaitEvents, *tracerParams.pphWaitEvents);
}
ze_result_t zeContextSystemBarrier_WithTracing(ze_context_handle_t hContext, ze_device_handle_t hDevice) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeContextSystemBarrier,
                                    hContext, hDevice);

    ze_context_system_barrier_params_t tracerParams;
    tracerParams.phContext = &hContext;
    tracerParams.phDevice = &hDevice;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnContextSystemBarrierCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnContextSystemBarrierCb_t, Context, pfnSystemBarrierCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeContextSystemBarrier,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phContext, *tracerParams.phDevice);
}
ze_result_t zeCommandListCreate_WithTracing(ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_list_desc_t* desc, ze_command_list_handle_t* phCommandList) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeCommandListCreate,
                                    hContext, hDevice, desc, phCommandList);

    ze_command_list_create_params_t tracerParams;
    tracerParams.phContext = &hContext;
    tracerParams.phDevice = &hDevice;
    tracerParams.pdesc = &desc;
    tracerParams.pphCommandList = &phCommandList;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnCommandListCreateCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnCommandListCreateCb_t, CommandList, pfnCreateCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeCommandListCreate,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phContext, *tracerParams.phDevice, *tracerParams.pdesc, *tracerParams.pphCommandList);
}
ze_result_t zeCommandListCreateImmediate_WithTracing(ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_queue_desc_t* altdesc, ze_command_list_handle_t* phCommandList) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeCommandListCreateImmediate,
                                    hContext, hDevice, altdesc, phCommandList);

    ze_command_list_create_immediate_params_t tracerParams;
    tracerParams.phContext = &hContext;
    tracerParams.phDevice = &hDevice;
    tracerParams.paltdesc = &altdesc;
    tracerParams.pphCommandList = &phCommandList;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnCommandListCreateImmediateCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnCommandListCreateImmediateCb_t, CommandList, pfnCreateImmediateCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeCommandListCreateImmediate,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phContext, *tracerParams.phDevice, *tracerParams.paltdesc, *tracerParams.pphCommandList);
}
ze_result_t zeCommandListDestroy_WithTracing(ze_command_list_handle_t hCommandList) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeCommandListDestroy,
                                    hCommandList);

    ze_command_list_destroy_params_t tracerParams;
    tracerParams.phCommandList = &hCommandList;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnCommandListDestroyCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnCommandListDestroyCb_t, CommandList, pfnDestroyCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeCommandListDestroy,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phCommandList);
}
ze_result_t zeCommandListClose_WithTracing(ze_command_list_handle_t hCommandList) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeCommandListClose,
                                    hCommandList);

    ze_command_list_close_params_t tracerParams;
    tracerParams.phCommandList = &hCommandList;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnCommandListCloseCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnCommandListCloseCb_t, CommandList, pfnCloseCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeCommandListClose,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phCommandList);
}
ze_result_t zeCommandListReset_WithTracing(ze_command_list_handle_t hCommandList) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeCommandListReset,
                                    hCommandList);

    ze_command_list_reset_params_t tracerParams;
    tracerParams.phCommandList = &hCommandList;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnCommandListResetCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnCommandListResetCb_t, CommandList, pfnResetCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeCommandListReset,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phCommandList);
}
ze_result_t zeCommandListAppendWriteGlobalTimestamp_WithTracing(ze_command_list_handle_t hCommandList, uint64_t* dstptr, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeCommandListAppendWriteGlobalTimestamp,
                                    hCommandList, dstptr, hSignalEvent, numWaitEvents, phWaitEvents);

    ze_command_list_append_write_global_timestamp_params_t tracerParams;
    tracerParams.phCommandList = &hCommandList;
    tracerParams.pdstptr = &dstptr;
    tracerParams.phSignalEvent = &hSignalEvent;
    tracerParams.pnumWaitEvents = &numWaitEvents;
    tracerParams.pphWaitEvents = &phWaitEvents;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnCommandListAppendWriteGlobalTimestampCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnCommandListAppendWriteGlobalTimestampCb_t, CommandList, pfnAppendWriteGlobalTimestampCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeCommandListAppendWriteGlobalTimestamp,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phCommandList, *tracerParams.pdstptr, *tracerParams.phSignalEvent, *tracerParams.pnumWaitEvents, *tracerParams.pphWaitEvents);
}
ze_result_t zeCommandQueueCreate_WithTracing(ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_queue_desc_t* desc, ze_command_queue_handle_t* phCommandQueue) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeCommandQueueCreate,
                                    hContext, hDevice, desc, phCommandQueue);

    ze_command_queue_create_params_t tracerParams;
    tracerParams.phContext = &hContext;
    tracerParams.phDevice = &hDevice;
    tracerParams.pdesc = &desc;
    tracerParams.pphCommandQueue = &phCommandQueue;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnCommandQueueCreateCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnCommandQueueCreateCb_t, CommandQueue, pfnCreateCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeCommandQueueCreate,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phContext, *tracerParams.phDevice, *tracerParams.pdesc, *tracerParams.pphCommandQueue);
}
ze_result_t zeCommandQueueDestroy_WithTracing(ze_command_queue_handle_t hCommandQueue) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeCommandQueueDestroy,
                                    hCommandQueue);

    ze_command_queue_destroy_params_t tracerParams;
    tracerParams.phCommandQueue = &hCommandQueue;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnCommandQueueDestroyCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnCommandQueueDestroyCb_t, CommandQueue, pfnDestroyCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeCommandQueueDestroy,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phCommandQueue);
}
ze_result_t zeCommandQueueExecuteCommandLists_WithTracing(ze_command_queue_handle_t hCommandQueue, uint32_t numCommandLists, ze_command_list_handle_t* phCommandLists, ze_fence_handle_t hFence) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeCommandQueueExecuteCommandLists,
                                    hCommandQueue, numCommandLists, phCommandLists, hFence);

    ze_command_queue_execute_command_lists_params_t tracerParams;
    tracerParams.phCommandQueue = &hCommandQueue;
    tracerParams.pnumCommandLists = &numCommandLists;
    tracerParams.pphCommandLists = &phCommandLists;
    tracerParams.phFence = &hFence;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnCommandQueueExecuteCommandListsCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnCommandQueueExecuteCommandListsCb_t, CommandQueue, pfnExecuteCommandListsCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeCommandQueueExecuteCommandLists,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phCommandQueue, *tracerParams.pnumCommandLists, *tracerParams.pphCommandLists, *tracerParams.phFence);
}
ze_result_t zeCommandQueueSynchronize_WithTracing(ze_command_queue_handle_t hCommandQueue, uint64_t timeout) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeCommandQueueSynchronize,
                                    hCommandQueue, timeout);

    ze_command_queue_synchronize_params_t tracerParams;
    tracerParams.phCommandQueue = &hCommandQueue;
    tracerParams.ptimeout = &timeout;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnCommandQueueSynchronizeCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnCommandQueueSynchronizeCb_t, CommandQueue, pfnSynchronizeCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeCommandQueueSynchronize,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phCommandQueue, *tracerParams.ptimeout);
}
ze_result_t zeContextCreate_WithTracing(ze_driver_handle_t hDriver, const ze_context_desc_t* desc, ze_context_handle_t* phContext) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeContextCreate,
                                    hDriver, desc, phContext);

    ze_context_create_params_t tracerParams;
    tracerParams.phDriver = &hDriver;
    tracerParams.pdesc = &desc;
    tracerParams.pphContext = &phContext;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnContextCreateCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnContextCreateCb_t, Context, pfnCreateCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeContextCreate,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phDriver, *tracerParams.pdesc, *tracerParams.pphContext);
}
ze_result_t zeContextDestroy_WithTracing(ze_context_handle_t hContext) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeContextDestroy,
                                    hContext);

    ze_context_destroy_params_t tracerParams;
    tracerParams.phContext = &hContext;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnContextDestroyCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnContextDestroyCb_t, Context, pfnDestroyCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeContextDestroy,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phContext);
}
ze_result_t zeContextGetStatus_WithTracing(ze_context_handle_t hContext) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeContextGetStatus,
                                    hContext);

    ze_context_get_status_params_t tracerParams;
    tracerParams.phContext = &hContext;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnContextGetStatusCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnContextGetStatusCb_t, Context, pfnGetStatusCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeContextGetStatus,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phContext);
}
ze_result_t zeCommandListAppendMemoryCopy_WithTracing(ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeCommandListAppendMemoryCopy,
                                    hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);

    ze_command_list_append_memory_copy_params_t tracerParams;
    tracerParams.phCommandList = &hCommandList;
    tracerParams.pdstptr = &dstptr;
    tracerParams.psrcptr = &srcptr;
    tracerParams.psize = &size;
    tracerParams.phSignalEvent = &hSignalEvent;
    tracerParams.pnumWaitEvents = &numWaitEvents;
    tracerParams.pphWaitEvents = &phWaitEvents;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnCommandListAppendMemoryCopyCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnCommandListAppendMemoryCopyCb_t, CommandList, pfnAppendMemoryCopyCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeCommandListAppendMemoryCopy,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phCommandList, *tracerParams.pdstptr, *tracerParams.psrcptr, *tracerParams.psize, *tracerParams.phSignalEvent, *tracerParams.pnumWaitEvents, *tracerParams.pphWaitEvents);
}
ze_result_t zeCommandListAppendMemoryFill_WithTracing(ze_command_list_handle_t hCommandList, void* ptr, const void* pattern, size_t pattern_size, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeCommandListAppendMemoryFill,
                                    hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEvents);

    ze_command_list_append_memory_fill_params_t tracerParams;
    tracerParams.phCommandList = &hCommandList;
    tracerParams.pptr = &ptr;
    tracerParams.ppattern = &pattern;
    tracerParams.ppattern_size = &pattern_size;
    tracerParams.psize = &size;
    tracerParams.phSignalEvent = &hSignalEvent;
    tracerParams.pnumWaitEvents = &numWaitEvents;
    tracerParams.pphWaitEvents = &phWaitEvents;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnCommandListAppendMemoryFillCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnCommandListAppendMemoryFillCb_t, CommandList, pfnAppendMemoryFillCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeCommandListAppendMemoryFill,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phCommandList, *tracerParams.pptr, *tracerParams.ppattern, *tracerParams.ppattern_size, *tracerParams.psize, *tracerParams.phSignalEvent, *tracerParams.pnumWaitEvents, *tracerParams.pphWaitEvents);
}
ze_result_t zeCommandListAppendMemoryCopyRegion_WithTracing(ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeCommandListAppendMemoryCopyRegion,
                                    hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);

    ze_command_list_append_memory_copy_region_params_t tracerParams;
    tracerParams.phCommandList = &hCommandList;
    tracerParams.pdstptr = &dstptr;
    tracerParams.pdstRegion = &dstRegion;
    tracerParams.pdstPitch = &dstPitch;
    tracerParams.pdstSlicePitch = &dstSlicePitch;
    tracerParams.psrcptr = &srcptr;
    tracerParams.psrcRegion = &srcRegion;
    tracerParams.psrcPitch = &srcPitch;
    tracerParams.psrcSlicePitch = &srcSlicePitch;
    tracerParams.phSignalEvent = &hSignalEvent;
    tracerParams.pnumWaitEvents = &numWaitEvents;
    tracerParams.pphWaitEvents = &phWaitEvents;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnCommandListAppendMemoryCopyRegionCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnCommandListAppendMemoryCopyRegionCb_t, CommandList, pfnAppendMemoryCopyRegionCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeCommandListAppendMemoryCopyRegion,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phCommandList, *tracerParams.pdstptr, *tracerParams.pdstRegion, *tracerParams.pdstPitch, *tracerParams.pdstSlicePitch, *tracerParams.psrcptr, *tracerParams.psrcRegion, *tracerParams.psrcPitch, *tracerParams.psrcSlicePitch, *tracerParams.phSignalEvent, *tracerParams.pnumWaitEvents, *tracerParams.pphWaitEvents);
}
ze_result_t zeCommandListAppendMemoryCopyFromContext_WithTracing(ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeCommandListAppendMemoryCopyFromContext,
                                    hCommandList, dstptr, hContextSrc, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);

    ze_command_list_append_memory_copy_from_context_params_t tracerParams;
    tracerParams.phCommandList = &hCommandList;
    tracerParams.pdstptr = &dstptr;
    tracerParams.phContextSrc = &hContextSrc;
    tracerParams.psrcptr = &srcptr;
    tracerParams.psize = &size;
    tracerParams.phSignalEvent = &hSignalEvent;
    tracerParams.pnumWaitEvents = &numWaitEvents;
    tracerParams.pphWaitEvents = &phWaitEvents;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnCommandListAppendMemoryCopyFromContextCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnCommandListAppendMemoryCopyFromContextCb_t, CommandList, pfnAppendMemoryCopyFromContextCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeCommandListAppendMemoryCopyFromContext,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phCommandList, *tracerParams.pdstptr, *tracerParams.phContextSrc, *tracerParams.psrcptr, *tracerParams.psize, *tracerParams.phSignalEvent, *tracerParams.pnumWaitEvents, *tracerParams.pphWaitEvents);
}
ze_result_t zeCommandListAppendMemoryPrefetch_WithTracing(ze_command_list_handle_t hCommandList, const void* ptr, size_t size) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeCommandListAppendMemoryPrefetch,
                                    hCommandList, ptr, size);

    ze_command_list_append_memory_prefetch_params_t tracerParams;
    tracerParams.phCommandList = &hCommandList;
    tracerParams.pptr = &ptr;
    tracerParams.psize = &size;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnCommandListAppendMemoryPrefetchCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnCommandListAppendMemoryPrefetchCb_t, CommandList, pfnAppendMemoryPrefetchCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeCommandListAppendMemoryPrefetch,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phCommandList, *tracerParams.pptr, *tracerParams.psize);
}
ze_result_t zeCommandListAppendMemAdvise_WithTracing(ze_command_list_handle_t hCommandList, ze_device_handle_t hDevice, const void* ptr, size_t size, ze_memory_advice_t advice) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeCommandListAppendMemAdvise,
                                    hCommandList, hDevice, ptr, size, advice);

    ze_command_list_append_mem_advise_params_t tracerParams;
    tracerParams.phCommandList = &hCommandList;
    tracerParams.phDevice = &hDevice;
    tracerParams.pptr = &ptr;
    tracerParams.psize = &size;
    tracerParams.padvice = &advice;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnCommandListAppendMemAdviseCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnCommandListAppendMemAdviseCb_t, CommandList, pfnAppendMemAdviseCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeCommandListAppendMemAdvise,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phCommandList, *tracerParams.phDevice, *tracerParams.pptr, *tracerParams.psize, *tracerParams.padvice);
}
ze_result_t zeDeviceGet_WithTracing(ze_driver_handle_t hDriver, uint32_t* pCount, ze_device_handle_t* phDevices) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeDeviceGet,
                                    hDriver, pCount, phDevices);

    ze_device_get_params_t tracerParams;
    tracerParams.phDriver = &hDriver;
    tracerParams.ppCount = &pCount;
    tracerParams.pphDevices = &phDevices;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnDeviceGetCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnDeviceGetCb_t, Device, pfnGetCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeDeviceGet,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phDriver, *tracerParams.ppCount, *tracerParams.pphDevices);
}
ze_result_t zeDeviceGetSubDevices_WithTracing(ze_device_handle_t hDevice, uint32_t* pCount, ze_device_handle_t* phSubdevices) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeDeviceGetSubDevices,
                                    hDevice, pCount, phSubdevices);

    ze_device_get_sub_devices_params_t tracerParams;
    tracerParams.phDevice = &hDevice;
    tracerParams.ppCount = &pCount;
    tracerParams.pphSubdevices = &phSubdevices;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnDeviceGetSubDevicesCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnDeviceGetSubDevicesCb_t, Device, pfnGetSubDevicesCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeDeviceGetSubDevices,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phDevice, *tracerParams.ppCount, *tracerParams.pphSubdevices);
}
ze_result_t zeDeviceGetProperties_WithTracing(ze_device_handle_t hDevice, ze_device_properties_t* pDeviceProperties) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeDeviceGetProperties,
                                    hDevice, pDeviceProperties);

    ze_device_get_properties_params_t tracerParams;
    tracerParams.phDevice = &hDevice;
    tracerParams.ppDeviceProperties = &pDeviceProperties;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnDeviceGetPropertiesCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnDeviceGetPropertiesCb_t, Device, pfnGetPropertiesCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeDeviceGetProperties,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phDevice, *tracerParams.ppDeviceProperties);
}
ze_result_t zeDeviceGetComputeProperties_WithTracing(ze_device_handle_t hDevice, ze_device_compute_properties_t* pComputeProperties) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeDeviceGetComputeProperties,
                                    hDevice, pComputeProperties);

    ze_device_get_compute_properties_params_t tracerParams;
    tracerParams.phDevice = &hDevice;
    tracerParams.ppComputeProperties = &pComputeProperties;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnDeviceGetComputePropertiesCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnDeviceGetComputePropertiesCb_t, Device, pfnGetComputePropertiesCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeDeviceGetComputeProperties,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phDevice, *tracerParams.ppComputeProperties);
}
ze_result_t zeDeviceGetModuleProperties_WithTracing(ze_device_handle_t hDevice, ze_device_module_properties_t* pModuleProperties) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeDeviceGetModuleProperties,
                                    hDevice, pModuleProperties);

    ze_device_get_module_properties_params_t tracerParams;
    tracerParams.phDevice = &hDevice;
    tracerParams.ppModuleProperties = &pModuleProperties;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnDeviceGetModulePropertiesCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnDeviceGetModulePropertiesCb_t, Device, pfnGetModulePropertiesCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeDeviceGetModuleProperties,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phDevice, *tracerParams.ppModuleProperties);
}
ze_result_t zeDeviceGetCommandQueueGroupProperties_WithTracing(ze_device_handle_t hDevice, uint32_t* pCount, ze_command_queue_group_properties_t* pCommandQueueGroupProperties) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeDeviceGetCommandQueueGroupProperties,
                                    hDevice, pCount, pCommandQueueGroupProperties);

    ze_device_get_command_queue_group_properties_params_t tracerParams;
    tracerParams.phDevice = &hDevice;
    tracerParams.ppCount = &pCount;
    tracerParams.ppCommandQueueGroupProperties = &pCommandQueueGroupProperties;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnDeviceGetCommandQueueGroupPropertiesCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnDeviceGetCommandQueueGroupPropertiesCb_t, Device, pfnGetCommandQueueGroupPropertiesCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeDeviceGetCommandQueueGroupProperties,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phDevice, *tracerParams.ppCount, *tracerParams.ppCommandQueueGroupProperties);
}
ze_result_t zeDeviceGetMemoryProperties_WithTracing(ze_device_handle_t hDevice, uint32_t* pCount, ze_device_memory_properties_t* pMemProperties) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeDeviceGetMemoryProperties,
                                    hDevice, pCount, pMemProperties);

    ze_device_get_memory_properties_params_t tracerParams;
    tracerParams.phDevice = &hDevice;
    tracerParams.ppCount = &pCount;
    tracerParams.ppMemProperties = &pMemProperties;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnDeviceGetMemoryPropertiesCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnDeviceGetMemoryPropertiesCb_t, Device, pfnGetMemoryPropertiesCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeDeviceGetMemoryProperties,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phDevice, *tracerParams.ppCount, *tracerParams.ppMemProperties);
}
ze_result_t zeDeviceGetMemoryAccessProperties_WithTracing(ze_device_handle_t hDevice, ze_device_memory_access_properties_t* pMemAccessProperties) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeDeviceGetMemoryAccessProperties,
                                    hDevice, pMemAccessProperties);

    ze_device_get_memory_access_properties_params_t tracerParams;
    tracerParams.phDevice = &hDevice;
    tracerParams.ppMemAccessProperties = &pMemAccessProperties;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnDeviceGetMemoryAccessPropertiesCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnDeviceGetMemoryAccessPropertiesCb_t, Device, pfnGetMemoryAccessPropertiesCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeDeviceGetMemoryAccessProperties,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phDevice, *tracerParams.ppMemAccessProperties);
}
ze_result_t zeDeviceGetCacheProperties_WithTracing(ze_device_handle_t hDevice, uint32_t* pCount, ze_device_cache_properties_t* pCacheProperties) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeDeviceGetCacheProperties,
                                    hDevice, pCount, pCacheProperties);

    ze_device_get_cache_properties_params_t tracerParams;
    tracerParams.phDevice = &hDevice;
    tracerParams.ppCount = &pCount;
    tracerParams.ppCacheProperties = &pCacheProperties;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnDeviceGetCachePropertiesCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnDeviceGetCachePropertiesCb_t, Device, pfnGetCachePropertiesCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeDeviceGetCacheProperties,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phDevice, *tracerParams.ppCount, *tracerParams.ppCacheProperties);
}
ze_result_t zeDeviceGetImageProperties_WithTracing(ze_device_handle_t hDevice, ze_device_image_properties_t* pImageProperties) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeDeviceGetImageProperties,
                                    hDevice, pImageProperties);

    ze_device_get_image_properties_params_t tracerParams;
    tracerParams.phDevice = &hDevice;
    tracerParams.ppImageProperties = &pImageProperties;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnDeviceGetImagePropertiesCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnDeviceGetImagePropertiesCb_t, Device, pfnGetImagePropertiesCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeDeviceGetImageProperties,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phDevice, *tracerParams.ppImageProperties);
}
ze_result_t zeDeviceGetExternalMemoryProperties_WithTracing(ze_device_handle_t hDevice, ze_device_external_memory_properties_t* pExternalMemoryProperties) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeDeviceGetExternalMemoryProperties,
                                    hDevice, pExternalMemoryProperties);

    ze_device_get_external_memory_properties_params_t tracerParams;
    tracerParams.phDevice = &hDevice;
    tracerParams.ppExternalMemoryProperties = &pExternalMemoryProperties;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnDeviceGetExternalMemoryPropertiesCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnDeviceGetExternalMemoryPropertiesCb_t, Device, pfnGetExternalMemoryPropertiesCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeDeviceGetExternalMemoryProperties,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phDevice, *tracerParams.ppExternalMemoryProperties);
}
ze_result_t zeDeviceGetP2PProperties_WithTracing(ze_device_handle_t hDevice, ze_device_handle_t hPeerDevice, ze_device_p2p_properties_t* pP2PProperties) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeDeviceGetP2PProperties,
                                    hDevice, hPeerDevice, pP2PProperties);

    ze_device_get_p2_p_properties_params_t tracerParams;
    tracerParams.phDevice = &hDevice;
    tracerParams.phPeerDevice = &hPeerDevice;
    tracerParams.ppP2PProperties = &pP2PProperties;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnDeviceGetP2PPropertiesCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnDeviceGetP2PPropertiesCb_t, Device, pfnGetP2PPropertiesCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeDeviceGetP2PProperties,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phDevice, *tracerParams.phPeerDevice, *tracerParams.ppP2PProperties);
}
ze_result_t zeDeviceCanAccessPeer_WithTracing(ze_device_handle_t hDevice, ze_device_handle_t hPeerDevice, ze_bool_t* value) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeDeviceCanAccessPeer,
                                    hDevice, hPeerDevice, value);

    ze_device_can_access_peer_params_t tracerParams;
    tracerParams.phDevice = &hDevice;
    tracerParams.phPeerDevice = &hPeerDevice;
    tracerParams.pvalue = &value;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnDeviceCanAccessPeerCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnDeviceCanAccessPeerCb_t, Device, pfnCanAccessPeerCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeDeviceCanAccessPeer,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phDevice, *tracerParams.phPeerDevice, *tracerParams.pvalue);
}
ze_result_t zeDeviceGetStatus_WithTracing(ze_device_handle_t hDevice) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeDeviceGetStatus,
                                    hDevice);

    ze_device_get_status_params_t tracerParams;
    tracerParams.phDevice = &hDevice;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnDeviceGetStatusCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnDeviceGetStatusCb_t, Device, pfnGetStatusCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeDeviceGetStatus,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phDevice);
}
ze_result_t zeDriverGet_WithTracing(uint32_t* pCount, ze_driver_handle_t* phDrivers) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeDriverGet,
                                    pCount, phDrivers);

    ze_driver_get_params_t tracerParams;
    tracerParams.ppCount = &pCount;
    tracerParams.pphDrivers = &phDrivers;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnDriverGetCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnDriverGetCb_t, Driver, pfnGetCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeDriverGet,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.ppCount, *tracerParams.pphDrivers);
}
ze_result_t zeDriverGetApiVersion_WithTracing(ze_driver_handle_t hDriver, ze_api_version_t* version) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeDriverGetApiVersion,
                                    hDriver, version);

    ze_driver_get_api_version_params_t tracerParams;
    tracerParams.phDriver = &hDriver;
    tracerParams.pversion = &version;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnDriverGetApiVersionCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnDriverGetApiVersionCb_t, Driver, pfnGetApiVersionCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeDriverGetApiVersion,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phDriver, *tracerParams.pversion);
}
ze_result_t zeDriverGetProperties_WithTracing(ze_driver_handle_t hDriver, ze_driver_properties_t* pDriverProperties) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeDriverGetProperties,
                                    hDriver, pDriverProperties);

    ze_driver_get_properties_params_t tracerParams;
    tracerParams.phDriver = &hDriver;
    tracerParams.ppDriverProperties = &pDriverProperties;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnDriverGetPropertiesCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnDriverGetPropertiesCb_t, Driver, pfnGetPropertiesCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeDriverGetProperties,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phDriver, *tracerParams.ppDriverProperties);
}
ze_result_t zeDriverGetIpcProperties_WithTracing(ze_driver_handle_t hDriver, ze_driver_ipc_properties_t* pIpcProperties) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeDriverGetIpcProperties,
                                    hDriver, pIpcProperties);

    ze_driver_get_ipc_properties_params_t tracerParams;
    tracerParams.phDriver = &hDriver;
    tracerParams.ppIpcProperties = &pIpcProperties;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnDriverGetIpcPropertiesCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnDriverGetIpcPropertiesCb_t, Driver, pfnGetIpcPropertiesCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeDriverGetIpcProperties,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phDriver, *tracerParams.ppIpcProperties);
}
ze_result_t zeDriverGetExtensionProperties_WithTracing(ze_driver_handle_t hDriver, uint32_t* pCount, ze_driver_extension_properties_t* pExtensionProperties) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeDriverGetExtensionProperties,
                                    hDriver, pCount, pExtensionProperties);

    ze_driver_get_extension_properties_params_t tracerParams;
    tracerParams.phDriver = &hDriver;
    tracerParams.ppCount = &pCount;
    tracerParams.ppExtensionProperties = &pExtensionProperties;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnDriverGetExtensionPropertiesCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnDriverGetExtensionPropertiesCb_t, Driver, pfnGetExtensionPropertiesCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeDriverGetExtensionProperties,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phDriver, *tracerParams.ppCount, *tracerParams.ppExtensionProperties);
}
ze_result_t zeEventPoolCreate_WithTracing(ze_context_handle_t hContext, const ze_event_pool_desc_t* desc, uint32_t numDevices, ze_device_handle_t* phDevices, ze_event_pool_handle_t* phEventPool) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeEventPoolCreate,
                                    hContext, desc, numDevices, phDevices, phEventPool);

    ze_event_pool_create_params_t tracerParams;
    tracerParams.phContext = &hContext;
    tracerParams.pdesc = &desc;
    tracerParams.pnumDevices = &numDevices;
    tracerParams.pphDevices = &phDevices;
    tracerParams.pphEventPool = &phEventPool;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnEventPoolCreateCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnEventPoolCreateCb_t, EventPool, pfnCreateCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeEventPoolCreate,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phContext, *tracerParams.pdesc, *tracerParams.pnumDevices, *tracerParams.pphDevices, *tracerParams.pphEventPool);
}
ze_result_t zeEventPoolDestroy_WithTracing(ze_event_pool_handle_t hEventPool) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeEventPoolDestroy,
                                    hEventPool);

    ze_event_pool_destroy_params_t tracerParams;
    tracerParams.phEventPool = &hEventPool;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnEventPoolDestroyCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnEventPoolDestroyCb_t, EventPool, pfnDestroyCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeEventPoolDestroy,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phEventPool);
}
ze_result_t zeEventCreate_WithTracing(ze_event_pool_handle_t hEventPool, const ze_event_desc_t* desc, ze_event_handle_t* phEvent) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeEventCreate,
                                    hEventPool, desc, phEvent);

    ze_event_create_params_t tracerParams;
    tracerParams.phEventPool = &hEventPool;
    tracerParams.pdesc = &desc;
    tracerParams.pphEvent = &phEvent;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnEventCreateCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnEventCreateCb_t, Event, pfnCreateCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeEventCreate,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phEventPool, *tracerParams.pdesc, *tracerParams.pphEvent);
}
ze_result_t zeEventDestroy_WithTracing(ze_event_handle_t hEvent) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeEventDestroy,
                                    hEvent);

    ze_event_destroy_params_t tracerParams;
    tracerParams.phEvent = &hEvent;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnEventDestroyCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnEventDestroyCb_t, Event, pfnDestroyCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeEventDestroy,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phEvent);
}
ze_result_t zeEventPoolGetIpcHandle_WithTracing(ze_event_pool_handle_t hEventPool, ze_ipc_event_pool_handle_t* phIpc) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeEventPoolGetIpcHandle,
                                    hEventPool, phIpc);

    ze_event_pool_get_ipc_handle_params_t tracerParams;
    tracerParams.phEventPool = &hEventPool;
    tracerParams.pphIpc = &phIpc;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnEventPoolGetIpcHandleCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnEventPoolGetIpcHandleCb_t, EventPool, pfnGetIpcHandleCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeEventPoolGetIpcHandle,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phEventPool, *tracerParams.pphIpc);
}
ze_result_t zeEventPoolOpenIpcHandle_WithTracing(ze_context_handle_t hContext, ze_ipc_event_pool_handle_t hIpc, ze_event_pool_handle_t* phEventPool) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeEventPoolOpenIpcHandle,
                                    hContext, hIpc, phEventPool);

    ze_event_pool_open_ipc_handle_params_t tracerParams;
    tracerParams.phContext = &hContext;
    tracerParams.phIpc = &hIpc;
    tracerParams.pphEventPool = &phEventPool;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnEventPoolOpenIpcHandleCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnEventPoolOpenIpcHandleCb_t, EventPool, pfnOpenIpcHandleCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeEventPoolOpenIpcHandle,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phContext, *tracerParams.phIpc, *tracerParams.pphEventPool);
}
ze_result_t zeEventPoolCloseIpcHandle_WithTracing(ze_event_pool_handle_t hEventPool) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeEventPoolCloseIpcHandle,
                                    hEventPool);

    ze_event_pool_close_ipc_handle_params_t tracerParams;
    tracerParams.phEventPool = &hEventPool;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnEventPoolCloseIpcHandleCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnEventPoolCloseIpcHandleCb_t, EventPool, pfnCloseIpcHandleCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeEventPoolCloseIpcHandle,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phEventPool);
}
ze_result_t zeCommandListAppendBarrier_WithTracing(ze_command_list_handle_t hCommandList, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeCommandListAppendBarrier,
                                    hCommandList, hSignalEvent, numWaitEvents, phWaitEvents);

    ze_command_list_append_barrier_params_t tracerParams;
    tracerParams.phCommandList = &hCommandList;
    tracerParams.phSignalEvent = &hSignalEvent;
    tracerParams.pnumWaitEvents = &numWaitEvents;
    tracerParams.pphWaitEvents = &phWaitEvents;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnCommandListAppendBarrierCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnCommandListAppendBarrierCb_t, CommandList, pfnAppendBarrierCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeCommandListAppendBarrier,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phCommandList, *tracerParams.phSignalEvent, *tracerParams.pnumWaitEvents, *tracerParams.pphWaitEvents);
}
ze_result_t zeCommandListAppendSignalEvent_WithTracing(ze_command_list_handle_t hCommandList, ze_event_handle_t hEvent) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeCommandListAppendSignalEvent,
                                    hCommandList, hEvent);

    ze_command_list_append_signal_event_params_t tracerParams;
    tracerParams.phCommandList = &hCommandList;
    tracerParams.phEvent = &hEvent;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnCommandListAppendSignalEventCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnCommandListAppendSignalEventCb_t, CommandList, pfnAppendSignalEventCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeCommandListAppendSignalEvent,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phCommandList, *tracerParams.phEvent);
}
ze_result_t zeCommandListAppendWaitOnEvents_WithTracing(ze_command_list_handle_t hCommandList, uint32_t numEvents, ze_event_handle_t* phEvents) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeCommandListAppendWaitOnEvents,
                                    hCommandList, numEvents, phEvents);

    ze_command_list_append_wait_on_events_params_t tracerParams;
    tracerParams.phCommandList = &hCommandList;
    tracerParams.pnumEvents = &numEvents;
    tracerParams.pphEvents = &phEvents;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnCommandListAppendWaitOnEventsCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnCommandListAppendWaitOnEventsCb_t, CommandList, pfnAppendWaitOnEventsCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeCommandListAppendWaitOnEvents,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phCommandList, *tracerParams.pnumEvents, *tracerParams.pphEvents);
}
ze_result_t zeEventHostSignal_WithTracing(ze_event_handle_t hEvent) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeEventHostSignal,
                                    hEvent);

    ze_event_host_signal_params_t tracerParams;
    tracerParams.phEvent = &hEvent;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnEventHostSignalCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnEventHostSignalCb_t, Event, pfnHostSignalCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeEventHostSignal,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phEvent);
}
ze_result_t zeEventHostSynchronize_WithTracing(ze_event_handle_t hEvent, uint64_t timeout) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeEventHostSynchronize,
                                    hEvent, timeout);

    ze_event_host_synchronize_params_t tracerParams;
    tracerParams.phEvent = &hEvent;
    tracerParams.ptimeout = &timeout;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnEventHostSynchronizeCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnEventHostSynchronizeCb_t, Event, pfnHostSynchronizeCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeEventHostSynchronize,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phEvent, *tracerParams.ptimeout);
}
ze_result_t zeEventQueryStatus_WithTracing(ze_event_handle_t hEvent) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeEventQueryStatus,
                                    hEvent);

    ze_event_query_status_params_t tracerParams;
    tracerParams.phEvent = &hEvent;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnEventQueryStatusCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnEventQueryStatusCb_t, Event, pfnQueryStatusCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeEventQueryStatus,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phEvent);
}
ze_result_t zeCommandListAppendEventReset_WithTracing(ze_command_list_handle_t hCommandList, ze_event_handle_t hEvent) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeCommandListAppendEventReset,
                                    hCommandList, hEvent);

    ze_command_list_append_event_reset_params_t tracerParams;
    tracerParams.phCommandList = &hCommandList;
    tracerParams.phEvent = &hEvent;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnCommandListAppendEventResetCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnCommandListAppendEventResetCb_t, CommandList, pfnAppendEventResetCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeCommandListAppendEventReset,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phCommandList, *tracerParams.phEvent);
}
ze_result_t zeEventHostReset_WithTracing(ze_event_handle_t hEvent) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeEventHostReset,
                                    hEvent);

    ze_event_host_reset_params_t tracerParams;
    tracerParams.phEvent = &hEvent;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnEventHostResetCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnEventHostResetCb_t, Event, pfnHostResetCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeEventHostReset,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phEvent);
}
ze_result_t zeEventQueryKernelTimestamp_WithTracing(ze_event_handle_t hEvent, ze_kernel_timestamp_result_t* dstptr) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeEventQueryKernelTimestamp,
                                    hEvent, dstptr);

    ze_event_query_kernel_timestamp_params_t tracerParams;
    tracerParams.phEvent = &hEvent;
    tracerParams.pdstptr = &dstptr;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnEventQueryKernelTimestampCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnEventQueryKernelTimestampCb_t, Event, pfnQueryKernelTimestampCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeEventQueryKernelTimestamp,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phEvent, *tracerParams.pdstptr);
}
ze_result_t zeCommandListAppendQueryKernelTimestamps_WithTracing(ze_command_list_handle_t hCommandList, uint32_t numEvents, ze_event_handle_t* phEvents, void* dstptr, const size_t* pOffsets, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeCommandListAppendQueryKernelTimestamps,
                                    hCommandList, numEvents, phEvents, dstptr, pOffsets, hSignalEvent, numWaitEvents, phWaitEvents);

    ze_command_list_append_query_kernel_timestamps_params_t tracerParams;
    tracerParams.phCommandList = &hCommandList;
    tracerParams.pnumEvents = &numEvents;
    tracerParams.pphEvents = &phEvents;
    tracerParams.pdstptr = &dstptr;
    tracerParams.ppOffsets = &pOffsets;
    tracerParams.phSignalEvent = &hSignalEvent;
    tracerParams.pnumWaitEvents = &numWaitEvents;
    tracerParams.pphWaitEvents = &phWaitEvents;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnCommandListAppendQueryKernelTimestampsCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnCommandListAppendQueryKernelTimestampsCb_t, CommandList, pfnAppendQueryKernelTimestampsCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeCommandListAppendQueryKernelTimestamps,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phCommandList, *tracerParams.pnumEvents, *tracerParams.pphEvents, *tracerParams.pdstptr, *tracerParams.ppOffsets, *tracerParams.phSignalEvent, *tracerParams.pnumWaitEvents, *tracerParams.pphWaitEvents);
}
ze_result_t zeFenceCreate_WithTracing(ze_command_queue_handle_t hCommandQueue, const ze_fence_desc_t* desc, ze_fence_handle_t* phFence) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeFenceCreate,
                                    hCommandQueue, desc, phFence);

    ze_fence_create_params_t tracerParams;
    tracerParams.phCommandQueue = &hCommandQueue;
    tracerParams.pdesc = &desc;
    tracerParams.pphFence = &phFence;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnFenceCreateCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnFenceCreateCb_t, Fence, pfnCreateCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeFenceCreate,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phCommandQueue, *tracerParams.pdesc, *tracerParams.pphFence);
}
ze_result_t zeFenceDestroy_WithTracing(ze_fence_handle_t hFence) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeFenceDestroy,
                                    hFence);

    ze_fence_destroy_params_t tracerParams;
    tracerParams.phFence = &hFence;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnFenceDestroyCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnFenceDestroyCb_t, Fence, pfnDestroyCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeFenceDestroy,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phFence);
}
ze_result_t zeFenceHostSynchronize_WithTracing(ze_fence_handle_t hFence, uint64_t timeout) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeFenceHostSynchronize,
                                    hFence, timeout);

    ze_fence_host_synchronize_params_t tracerParams;
    tracerParams.phFence = &hFence;
    tracerParams.ptimeout = &timeout;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnFenceHostSynchronizeCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnFenceHostSynchronizeCb_t, Fence, pfnHostSynchronizeCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeFenceHostSynchronize,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phFence, *tracerParams.ptimeout);
}
ze_result_t zeFenceQueryStatus_WithTracing(ze_fence_handle_t hFence) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeFenceQueryStatus,
                                    hFence);

    ze_fence_query_status_params_t tracerParams;
    tracerParams.phFence = &hFence;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnFenceQueryStatusCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnFenceQueryStatusCb_t, Fence, pfnQueryStatusCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeFenceQueryStatus,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phFence);
}
ze_result_t zeFenceReset_WithTracing(ze_fence_handle_t hFence) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeFenceReset,
                                    hFence);

    ze_fence_reset_params_t tracerParams;
    tracerParams.phFence = &hFence;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnFenceResetCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnFenceResetCb_t, Fence, pfnResetCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeFenceReset,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phFence);
}
ze_result_t zeImageGetProperties_WithTracing(ze_device_handle_t hDevice, const ze_image_desc_t* desc, ze_image_properties_t* pImageProperties) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeImageGetProperties,
                                    hDevice, desc, pImageProperties);

    ze_image_get_properties_params_t tracerParams;
    tracerParams.phDevice = &hDevice;
    tracerParams.pdesc = &desc;
    tracerParams.ppImageProperties = &pImageProperties;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnImageGetPropertiesCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnImageGetPropertiesCb_t, Image, pfnGetPropertiesCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeImageGetProperties,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phDevice, *tracerParams.pdesc, *tracerParams.ppImageProperties);
}
ze_result_t zeImageCreate_WithTracing(ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_image_desc_t* desc, ze_image_handle_t* phImage) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeImageCreate,
                                    hContext, hDevice, desc, phImage);

    ze_image_create_params_t tracerParams;
    tracerParams.phContext = &hContext;
    tracerParams.phDevice = &hDevice;
    tracerParams.pdesc = &desc;
    tracerParams.pphImage = &phImage;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnImageCreateCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnImageCreateCb_t, Image, pfnCreateCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeImageCreate,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phContext, *tracerParams.phDevice, *tracerParams.pdesc, *tracerParams.pphImage);
}
ze_result_t zeImageDestroy_WithTracing(ze_image_handle_t hImage) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeImageDestroy,
                                    hImage);

    ze_image_destroy_params_t tracerParams;
    tracerParams.phImage = &hImage;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnImageDestroyCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnImageDestroyCb_t, Image, pfnDestroyCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeImageDestroy,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phImage);
}
ze_result_t zeMemAllocShared_WithTracing(ze_context_handle_t hContext, const ze_device_mem_alloc_desc_t* device_desc, const ze_host_mem_alloc_desc_t* host_desc, size_t size, size_t alignment, ze_device_handle_t hDevice, void** pptr) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeMemAllocShared,
                                    hContext, device_desc, host_desc, size, alignment, hDevice, pptr);

    ze_mem_alloc_shared_params_t tracerParams;
    tracerParams.phContext = &hContext;
    tracerParams.pdevice_desc = &device_desc;
    tracerParams.phost_desc = &host_desc;
    tracerParams.psize = &size;
    tracerParams.palignment = &alignment;
    tracerParams.phDevice = &hDevice;
    tracerParams.ppptr = &pptr;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnMemAllocSharedCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnMemAllocSharedCb_t, Mem, pfnAllocSharedCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeMemAllocShared,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phContext, *tracerParams.pdevice_desc, *tracerParams.phost_desc, *tracerParams.psize, *tracerParams.palignment, *tracerParams.phDevice, *tracerParams.ppptr);
}
ze_result_t zeMemAllocDevice_WithTracing(ze_context_handle_t hContext, const ze_device_mem_alloc_desc_t* device_desc, size_t size, size_t alignment, ze_device_handle_t hDevice, void** pptr) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeMemAllocDevice,
                                    hContext, device_desc, size, alignment, hDevice, pptr);

    ze_mem_alloc_device_params_t tracerParams;
    tracerParams.phContext = &hContext;
    tracerParams.pdevice_desc = &device_desc;
    tracerParams.psize = &size;
    tracerParams.palignment = &alignment;
    tracerParams.phDevice = &hDevice;
    tracerParams.ppptr = &pptr;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnMemAllocDeviceCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnMemAllocDeviceCb_t, Mem, pfnAllocDeviceCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeMemAllocDevice,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phContext, *tracerParams.pdevice_desc, *tracerParams.psize, *tracerParams.palignment, *tracerParams.phDevice, *tracerParams.ppptr);
}
ze_result_t zeMemAllocHost_WithTracing(ze_context_handle_t hContext, const ze_host_mem_alloc_desc_t* host_desc, size_t size, size_t alignment, void** pptr) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeMemAllocHost,
                                    hContext, host_desc, size, alignment, pptr);

    ze_mem_alloc_host_params_t tracerParams;
    tracerParams.phContext = &hContext;
    tracerParams.phost_desc = &host_desc;
    tracerParams.psize = &size;
    tracerParams.palignment = &alignment;
    tracerParams.ppptr = &pptr;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnMemAllocHostCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnMemAllocHostCb_t, Mem, pfnAllocHostCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeMemAllocHost,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phContext, *tracerParams.phost_desc, *tracerParams.psize, *tracerParams.palignment, *tracerParams.ppptr);
}
ze_result_t zeMemFree_WithTracing(ze_context_handle_t hContext, void* ptr) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeMemFree,
                                    hContext, ptr);

    ze_mem_free_params_t tracerParams;
    tracerParams.phContext = &hContext;
    tracerParams.pptr = &ptr;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnMemFreeCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnMemFreeCb_t, Mem, pfnFreeCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeMemFree,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phContext, *tracerParams.pptr);
}
ze_result_t zeMemGetAllocProperties_WithTracing(ze_context_handle_t hContext, const void* ptr, ze_memory_allocation_properties_t* pMemAllocProperties, ze_device_handle_t* phDevice) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeMemGetAllocProperties,
                                    hContext, ptr, pMemAllocProperties, phDevice);

    ze_mem_get_alloc_properties_params_t tracerParams;
    tracerParams.phContext = &hContext;
    tracerParams.pptr = &ptr;
    tracerParams.ppMemAllocProperties = &pMemAllocProperties;
    tracerParams.pphDevice = &phDevice;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnMemGetAllocPropertiesCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnMemGetAllocPropertiesCb_t, Mem, pfnGetAllocPropertiesCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeMemGetAllocProperties,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phContext, *tracerParams.pptr, *tracerParams.ppMemAllocProperties, *tracerParams.pphDevice);
}
ze_result_t zeMemGetAddressRange_WithTracing(ze_context_handle_t hContext, const void* ptr, void** pBase, size_t* pSize) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeMemGetAddressRange,
                                    hContext, ptr, pBase, pSize);

    ze_mem_get_address_range_params_t tracerParams;
    tracerParams.phContext = &hContext;
    tracerParams.pptr = &ptr;
    tracerParams.ppBase = &pBase;
    tracerParams.ppSize = &pSize;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnMemGetAddressRangeCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnMemGetAddressRangeCb_t, Mem, pfnGetAddressRangeCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeMemGetAddressRange,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phContext, *tracerParams.pptr, *tracerParams.ppBase, *tracerParams.ppSize);
}
ze_result_t zeMemGetIpcHandle_WithTracing(ze_context_handle_t hContext, const void* ptr, ze_ipc_mem_handle_t* pIpcHandle) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeMemGetIpcHandle,
                                    hContext, ptr, pIpcHandle);

    ze_mem_get_ipc_handle_params_t tracerParams;
    tracerParams.phContext = &hContext;
    tracerParams.pptr = &ptr;
    tracerParams.ppIpcHandle = &pIpcHandle;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnMemGetIpcHandleCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnMemGetIpcHandleCb_t, Mem, pfnGetIpcHandleCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeMemGetIpcHandle,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phContext, *tracerParams.pptr, *tracerParams.ppIpcHandle);
}
ze_result_t zeMemOpenIpcHandle_WithTracing(ze_context_handle_t hContext, ze_device_handle_t hDevice, ze_ipc_mem_handle_t handle, ze_ipc_memory_flags_t flags, void** pptr) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeMemOpenIpcHandle,
                                    hContext, hDevice, handle, flags, pptr);

    ze_mem_open_ipc_handle_params_t tracerParams;
    tracerParams.phContext = &hContext;
    tracerParams.phDevice = &hDevice;
    tracerParams.phandle = &handle;
    tracerParams.pflags = &flags;
    tracerParams.ppptr = &pptr;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnMemOpenIpcHandleCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnMemOpenIpcHandleCb_t, Mem, pfnOpenIpcHandleCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeMemOpenIpcHandle,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phContext, *tracerParams.phDevice, *tracerParams.phandle, *tracerParams.pflags, *tracerParams.ppptr);
}
ze_result_t zeMemCloseIpcHandle_WithTracing(ze_context_handle_t hContext, const void* ptr) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeMemCloseIpcHandle,
                                    hContext, ptr);

    ze_mem_close_ipc_handle_params_t tracerParams;
    tracerParams.phContext = &hContext;
    tracerParams.pptr = &ptr;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnMemCloseIpcHandleCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnMemCloseIpcHandleCb_t, Mem, pfnCloseIpcHandleCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeMemCloseIpcHandle,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phContext, *tracerParams.pptr);
}
ze_result_t zeModuleCreate_WithTracing(ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_module_desc_t* desc, ze_module_handle_t* phModule, ze_module_build_log_handle_t* phBuildLog) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeModuleCreate,
                                    hContext, hDevice, desc, phModule, phBuildLog);

    ze_module_create_params_t tracerParams;
    tracerParams.phContext = &hContext;
    tracerParams.phDevice = &hDevice;
    tracerParams.pdesc = &desc;
    tracerParams.pphModule = &phModule;
    tracerParams.pphBuildLog = &phBuildLog;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnModuleCreateCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnModuleCreateCb_t, Module, pfnCreateCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeModuleCreate,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phContext, *tracerParams.phDevice, *tracerParams.pdesc, *tracerParams.pphModule, *tracerParams.pphBuildLog);
}
ze_result_t zeModuleDestroy_WithTracing(ze_module_handle_t hModule) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeModuleDestroy,
                                    hModule);

    ze_module_destroy_params_t tracerParams;
    tracerParams.phModule = &hModule;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnModuleDestroyCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnModuleDestroyCb_t, Module, pfnDestroyCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeModuleDestroy,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phModule);
}
ze_result_t zeModuleDynamicLink_WithTracing(uint32_t numModules, ze_module_handle_t* phModules, ze_module_build_log_handle_t* phLinkLog) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeModuleDynamicLink,
                                    numModules, phModules, phLinkLog);

    ze_module_dynamic_link_params_t tracerParams;
    tracerParams.pnumModules = &numModules;
    tracerParams.pphModules = &phModules;
    tracerParams.pphLinkLog = &phLinkLog;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnModuleDynamicLinkCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnModuleDynamicLinkCb_t, Module, pfnDynamicLinkCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeModuleDynamicLink,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.pnumModules, *tracerParams.pphModules, *tracerParams.pphLinkLog);
}
ze_result_t zeModuleBuildLogDestroy_WithTracing(ze_module_build_log_handle_t hModuleBuildLog) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeModuleBuildLogDestroy,
                                    hModuleBuildLog);

    ze_module_build_log_destroy_params_t tracerParams;
    tracerParams.phModuleBuildLog = &hModuleBuildLog;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnModuleBuildLogDestroyCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnModuleBuildLogDestroyCb_t, ModuleBuildLog, pfnDestroyCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeModuleBuildLogDestroy,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phModuleBuildLog);
}
ze_result_t zeModuleBuildLogGetString_WithTracing(ze_module_build_log_handle_t hModuleBuildLog, size_t* pSize, char* pBuildLog) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeModuleBuildLogGetString,
                                    hModuleBuildLog, pSize, pBuildLog);

    ze_module_build_log_get_string_params_t tracerParams;
    tracerParams.phModuleBuildLog = &hModuleBuildLog;
    tracerParams.ppSize = &pSize;
    tracerParams.ppBuildLog = &pBuildLog;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnModuleBuildLogGetStringCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnModuleBuildLogGetStringCb_t, ModuleBuildLog, pfnGetStringCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeModuleBuildLogGetString,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phModuleBuildLog, *tracerParams.ppSize, *tracerParams.ppBuildLog);
}
ze_result_t zeModuleGetNativeBinary_WithTracing(ze_module_handle_t hModule, size_t* pSize, uint8_t* pModuleNativeBinary) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeModuleGetNativeBinary,
                                    hModule, pSize, pModuleNativeBinary);

    ze_module_get_native_binary_params_t tracerParams;
    tracerParams.phModule = &hModule;
    tracerParams.ppSize = &pSize;
    tracerParams.ppModuleNativeBinary = &pModuleNativeBinary;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnModuleGetNativeBinaryCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnModuleGetNativeBinaryCb_t, Module, pfnGetNativeBinaryCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeModuleGetNativeBinary,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phModule, *tracerParams.ppSize, *tracerParams.ppModuleNativeBinary);
}
ze_result_t zeModuleGetGlobalPointer_WithTracing(ze_module_handle_t hModule, const char* pGlobalName, size_t* pSize, void** pptr) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeModuleGetGlobalPointer,
                                    hModule, pGlobalName, pSize, pptr);

    ze_module_get_global_pointer_params_t tracerParams;
    tracerParams.phModule = &hModule;
    tracerParams.ppGlobalName = &pGlobalName;
    tracerParams.ppSize = &pSize;
    tracerParams.ppptr = &pptr;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnModuleGetGlobalPointerCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnModuleGetGlobalPointerCb_t, Module, pfnGetGlobalPointerCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeModuleGetGlobalPointer,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phModule, *tracerParams.ppGlobalName, *tracerParams.ppSize, *tracerParams.ppptr);
}
ze_result_t zeModuleGetKernelNames_WithTracing(ze_module_handle_t hModule, uint32_t* pCount, const char** pNames) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeModuleGetKernelNames,
                                    hModule, pCount, pNames);

    ze_module_get_kernel_names_params_t tracerParams;
    tracerParams.phModule = &hModule;
    tracerParams.ppCount = &pCount;
    tracerParams.ppNames = &pNames;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnModuleGetKernelNamesCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnModuleGetKernelNamesCb_t, Module, pfnGetKernelNamesCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeModuleGetKernelNames,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phModule, *tracerParams.ppCount, *tracerParams.ppNames);
}
ze_result_t zeModuleGetProperties_WithTracing(ze_module_handle_t hModule, ze_module_properties_t* pModuleProperties) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeModuleGetProperties,
                                    hModule, pModuleProperties);

    ze_module_get_properties_params_t tracerParams;
    tracerParams.phModule = &hModule;
    tracerParams.ppModuleProperties = &pModuleProperties;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnModuleGetPropertiesCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnModuleGetPropertiesCb_t, Module, pfnGetPropertiesCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeModuleGetProperties,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phModule, *tracerParams.ppModuleProperties);
}
ze_result_t zeKernelCreate_WithTracing(ze_module_handle_t hModule, const ze_kernel_desc_t* desc, ze_kernel_handle_t* phKernel) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeKernelCreate,
                                    hModule, desc, phKernel);

    ze_kernel_create_params_t tracerParams;
    tracerParams.phModule = &hModule;
    tracerParams.pdesc = &desc;
    tracerParams.pphKernel = &phKernel;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnKernelCreateCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnKernelCreateCb_t, Kernel, pfnCreateCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeKernelCreate,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phModule, *tracerParams.pdesc, *tracerParams.pphKernel);
}
ze_result_t zeKernelDestroy_WithTracing(ze_kernel_handle_t hKernel) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeKernelDestroy,
                                    hKernel);

    ze_kernel_destroy_params_t tracerParams;
    tracerParams.phKernel = &hKernel;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnKernelDestroyCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnKernelDestroyCb_t, Kernel, pfnDestroyCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeKernelDestroy,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phKernel);
}
ze_result_t zeModuleGetFunctionPointer_WithTracing(ze_module_handle_t hModule, const char* pFunctionName, void** pfnFunction) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeModuleGetFunctionPointer,
                                    hModule, pFunctionName, pfnFunction);

    ze_module_get_function_pointer_params_t tracerParams;
    tracerParams.phModule = &hModule;
    tracerParams.ppFunctionName = &pFunctionName;
    tracerParams.ppfnFunction = &pfnFunction;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnModuleGetFunctionPointerCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnModuleGetFunctionPointerCb_t, Module, pfnGetFunctionPointerCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeModuleGetFunctionPointer,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phModule, *tracerParams.ppFunctionName, *tracerParams.ppfnFunction);
}
ze_result_t zeKernelSetGroupSize_WithTracing(ze_kernel_handle_t hKernel, uint32_t groupSizeX, uint32_t groupSizeY, uint32_t groupSizeZ) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeKernelSetGroupSize,
                                    hKernel, groupSizeX, groupSizeY, groupSizeZ);

    ze_kernel_set_group_size_params_t tracerParams;
    tracerParams.phKernel = &hKernel;
    tracerParams.pgroupSizeX = &groupSizeX;
    tracerParams.pgroupSizeY = &groupSizeY;
    tracerParams.pgroupSizeZ = &groupSizeZ;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnKernelSetGroupSizeCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnKernelSetGroupSizeCb_t, Kernel, pfnSetGroupSizeCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeKernelSetGroupSize,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phKernel, *tracerParams.pgroupSizeX, *tracerParams.pgroupSizeY, *tracerParams.pgroupSizeZ);
}
ze_result_t zeKernelSuggestGroupSize_WithTracing(ze_kernel_handle_t hKernel, uint32_t globalSizeX, uint32_t globalSizeY, uint32_t globalSizeZ, uint32_t* groupSizeX, uint32_t* groupSizeY, uint32_t* groupSizeZ) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeKernelSuggestGroupSize,
                                    hKernel, globalSizeX, globalSizeY, globalSizeZ, groupSizeX, groupSizeY, groupSizeZ);

    ze_kernel_suggest_group_size_params_t tracerParams;
    tracerParams.phKernel = &hKernel;
    tracerParams.pglobalSizeX = &globalSizeX;
    tracerParams.pglobalSizeY = &globalSizeY;
    tracerParams.pglobalSizeZ = &globalSizeZ;
    tracerParams.pgroupSizeX = &groupSizeX;
    tracerParams.pgroupSizeY = &groupSizeY;
    tracerParams.pgroupSizeZ = &groupSizeZ;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnKernelSuggestGroupSizeCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnKernelSuggestGroupSizeCb_t, Kernel, pfnSuggestGroupSizeCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeKernelSuggestGroupSize,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phKernel, *tracerParams.pglobalSizeX, *tracerParams.pglobalSizeY, *tracerParams.pglobalSizeZ, *tracerParams.pgroupSizeX, *tracerParams.pgroupSizeY, *tracerParams.pgroupSizeZ);
}
ze_result_t zeKernelSuggestMaxCooperativeGroupCount_WithTracing(ze_kernel_handle_t hKernel, uint32_t* totalGroupCount) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeKernelSuggestMaxCooperativeGroupCount,
                                    hKernel, totalGroupCount);

    ze_kernel_suggest_max_cooperative_group_count_params_t tracerParams;
    tracerParams.phKernel = &hKernel;
    tracerParams.ptotalGroupCount = &totalGroupCount;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnKernelSuggestMaxCooperativeGroupCountCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnKernelSuggestMaxCooperativeGroupCountCb_t, Kernel, pfnSuggestMaxCooperativeGroupCountCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeKernelSuggestMaxCooperativeGroupCount,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phKernel, *tracerParams.ptotalGroupCount);
}
ze_result_t zeKernelSetArgumentValue_WithTracing(ze_kernel_handle_t hKernel, uint32_t argIndex, size_t argSize, const void* pArgValue) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeKernelSetArgumentValue,
                                    hKernel, argIndex, argSize, pArgValue);

    ze_kernel_set_argument_value_params_t tracerParams;
    tracerParams.phKernel = &hKernel;
    tracerParams.pargIndex = &argIndex;
    tracerParams.pargSize = &argSize;
    tracerParams.ppArgValue = &pArgValue;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnKernelSetArgumentValueCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnKernelSetArgumentValueCb_t, Kernel, pfnSetArgumentValueCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeKernelSetArgumentValue,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phKernel, *tracerParams.pargIndex, *tracerParams.pargSize, *tracerParams.ppArgValue);
}
ze_result_t zeKernelSetIndirectAccess_WithTracing(ze_kernel_handle_t hKernel, ze_kernel_indirect_access_flags_t flags) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeKernelSetIndirectAccess,
                                    hKernel, flags);

    ze_kernel_set_indirect_access_params_t tracerParams;
    tracerParams.phKernel = &hKernel;
    tracerParams.pflags = &flags;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnKernelSetIndirectAccessCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnKernelSetIndirectAccessCb_t, Kernel, pfnSetIndirectAccessCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeKernelSetIndirectAccess,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phKernel, *tracerParams.pflags);
}
ze_result_t zeKernelGetIndirectAccess_WithTracing(ze_kernel_handle_t hKernel, ze_kernel_indirect_access_flags_t* pFlags) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeKernelGetIndirectAccess,
                                    hKernel, pFlags);

    ze_kernel_get_indirect_access_params_t tracerParams;
    tracerParams.phKernel = &hKernel;
    tracerParams.ppFlags = &pFlags;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnKernelGetIndirectAccessCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnKernelGetIndirectAccessCb_t, Kernel, pfnGetIndirectAccessCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeKernelGetIndirectAccess,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phKernel, *tracerParams.ppFlags);
}
ze_result_t zeKernelSetCacheConfig_WithTracing(ze_kernel_handle_t hKernel, ze_cache_config_flags_t flags) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeKernelSetCacheConfig,
                                    hKernel, flags);

    ze_kernel_set_cache_config_params_t tracerParams;
    tracerParams.phKernel = &hKernel;
    tracerParams.pflags = &flags;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnKernelSetCacheConfigCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnKernelSetCacheConfigCb_t, Kernel, pfnSetCacheConfigCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeKernelSetCacheConfig,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phKernel, *tracerParams.pflags);
}
ze_result_t zeKernelGetProperties_WithTracing(ze_kernel_handle_t hKernel, ze_kernel_properties_t* pKernelProperties) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeKernelGetProperties,
                                    hKernel, pKernelProperties);

    ze_kernel_get_properties_params_t tracerParams;
    tracerParams.phKernel = &hKernel;
    tracerParams.ppKernelProperties = &pKernelProperties;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnKernelGetPropertiesCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnKernelGetPropertiesCb_t, Kernel, pfnGetPropertiesCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeKernelGetProperties,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phKernel, *tracerParams.ppKernelProperties);
}
ze_result_t zeKernelGetName_WithTracing(ze_kernel_handle_t hKernel, size_t* pSize, char* pName) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeKernelGetName,
                                    hKernel, pSize, pName);

    ze_kernel_get_name_params_t tracerParams;
    tracerParams.phKernel = &hKernel;
    tracerParams.ppSize = &pSize;
    tracerParams.ppName = &pName;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnKernelGetNameCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnKernelGetNameCb_t, Kernel, pfnGetNameCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeKernelGetName,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phKernel, *tracerParams.ppSize, *tracerParams.ppName);
}
ze_result_t zeCommandListAppendLaunchKernel_WithTracing(ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchFuncArgs, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeCommandListAppendLaunchKernel,
                                    hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents);

    ze_command_list_append_launch_kernel_params_t tracerParams;
    tracerParams.phCommandList = &hCommandList;
    tracerParams.phKernel = &hKernel;
    tracerParams.ppLaunchFuncArgs = &pLaunchFuncArgs;
    tracerParams.phSignalEvent = &hSignalEvent;
    tracerParams.pnumWaitEvents = &numWaitEvents;
    tracerParams.pphWaitEvents = &phWaitEvents;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnCommandListAppendLaunchKernelCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnCommandListAppendLaunchKernelCb_t, CommandList, pfnAppendLaunchKernelCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeCommandListAppendLaunchKernel,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phCommandList, *tracerParams.phKernel, *tracerParams.ppLaunchFuncArgs, *tracerParams.phSignalEvent, *tracerParams.pnumWaitEvents, *tracerParams.pphWaitEvents);
}
ze_result_t zeCommandListAppendLaunchCooperativeKernel_WithTracing(ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchFuncArgs, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeCommandListAppendLaunchCooperativeKernel,
                                    hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents);

    ze_command_list_append_launch_cooperative_kernel_params_t tracerParams;
    tracerParams.phCommandList = &hCommandList;
    tracerParams.phKernel = &hKernel;
    tracerParams.ppLaunchFuncArgs = &pLaunchFuncArgs;
    tracerParams.phSignalEvent = &hSignalEvent;
    tracerParams.pnumWaitEvents = &numWaitEvents;
    tracerParams.pphWaitEvents = &phWaitEvents;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnCommandListAppendLaunchCooperativeKernelCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnCommandListAppendLaunchCooperativeKernelCb_t, CommandList, pfnAppendLaunchCooperativeKernelCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeCommandListAppendLaunchCooperativeKernel,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phCommandList, *tracerParams.phKernel, *tracerParams.ppLaunchFuncArgs, *tracerParams.phSignalEvent, *tracerParams.pnumWaitEvents, *tracerParams.pphWaitEvents);
}
ze_result_t zeCommandListAppendLaunchKernelIndirect_WithTracing(ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchArgumentsBuffer, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeCommandListAppendLaunchKernelIndirect,
                                    hCommandList, hKernel, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents);

    ze_command_list_append_launch_kernel_indirect_params_t tracerParams;
    tracerParams.phCommandList = &hCommandList;
    tracerParams.phKernel = &hKernel;
    tracerParams.ppLaunchArgumentsBuffer = &pLaunchArgumentsBuffer;
    tracerParams.phSignalEvent = &hSignalEvent;
    tracerParams.pnumWaitEvents = &numWaitEvents;
    tracerParams.pphWaitEvents = &phWaitEvents;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnCommandListAppendLaunchKernelIndirectCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnCommandListAppendLaunchKernelIndirectCb_t, CommandList, pfnAppendLaunchKernelIndirectCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeCommandListAppendLaunchKernelIndirect,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phCommandList, *tracerParams.phKernel, *tracerParams.ppLaunchArgumentsBuffer, *tracerParams.phSignalEvent, *tracerParams.pnumWaitEvents, *tracerParams.pphWaitEvents);
}
ze_result_t zeCommandListAppendLaunchMultipleKernelsIndirect_WithTracing(ze_command_list_handle_t hCommandList, uint32_t numKernels, ze_kernel_handle_t* phKernels, const uint32_t* pCountBuffer, const ze_group_count_t* pLaunchArgumentsBuffer, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeCommandListAppendLaunchMultipleKernelsIndirect,
                                    hCommandList, numKernels, phKernels, pCountBuffer, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents);

    ze_command_list_append_launch_multiple_kernels_indirect_params_t tracerParams;
    tracerParams.phCommandList = &hCommandList;
    tracerParams.pnumKernels = &numKernels;
    tracerParams.pphKernels = &phKernels;
    tracerParams.ppCountBuffer = &pCountBuffer;
    tracerParams.ppLaunchArgumentsBuffer = &pLaunchArgumentsBuffer;
    tracerParams.phSignalEvent = &hSignalEvent;
    tracerParams.pnumWaitEvents = &numWaitEvents;
    tracerParams.pphWaitEvents = &phWaitEvents;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnCommandListAppendLaunchMultipleKernelsIndirectCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnCommandListAppendLaunchMultipleKernelsIndirectCb_t, CommandList, pfnAppendLaunchMultipleKernelsIndirectCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeCommandListAppendLaunchMultipleKernelsIndirect,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phCommandList, *tracerParams.pnumKernels, *tracerParams.pphKernels, *tracerParams.ppCountBuffer, *tracerParams.ppLaunchArgumentsBuffer, *tracerParams.phSignalEvent, *tracerParams.pnumWaitEvents, *tracerParams.pphWaitEvents);
}
ze_result_t zeContextMakeMemoryResident_WithTracing(ze_context_handle_t hContext, ze_device_handle_t hDevice, void* ptr, size_t size) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeContextMakeMemoryResident,
                                    hContext, hDevice, ptr, size);

    ze_context_make_memory_resident_params_t tracerParams;
    tracerParams.phContext = &hContext;
    tracerParams.phDevice = &hDevice;
    tracerParams.pptr = &ptr;
    tracerParams.psize = &size;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnContextMakeMemoryResidentCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnContextMakeMemoryResidentCb_t, Context, pfnMakeMemoryResidentCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeContextMakeMemoryResident,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phContext, *tracerParams.phDevice, *tracerParams.pptr, *tracerParams.psize);
}
ze_result_t zeContextEvictMemory_WithTracing(ze_context_handle_t hContext, ze_device_handle_t hDevice, void* ptr, size_t size) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeContextEvictMemory,
                                    hContext, hDevice, ptr, size);

    ze_context_evict_memory_params_t tracerParams;
    tracerParams.phContext = &hContext;
    tracerParams.phDevice = &hDevice;
    tracerParams.pptr = &ptr;
    tracerParams.psize = &size;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnContextEvictMemoryCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnContextEvictMemoryCb_t, Context, pfnEvictMemoryCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeContextEvictMemory,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phContext, *tracerParams.phDevice, *tracerParams.pptr, *tracerParams.psize);
}
ze_result_t zeVirtualMemReserve_WithTracing(ze_context_handle_t hContext, const void* pStart, size_t size, void** pptr) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeVirtualMemReserve,
                                    hContext, pStart, size, pptr);

    ze_virtual_mem_reserve_params_t tracerParams;
    tracerParams.phContext = &hContext;
    tracerParams.ppStart = &pStart;
    tracerParams.psize = &size;
    tracerParams.ppptr = &pptr;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnVirtualMemReserveCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnVirtualMemReserveCb_t, VirtualMem, pfnReserveCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeVirtualMemReserve,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phContext, *tracerParams.ppStart, *tracerParams.psize, *tracerParams.ppptr);
}
ze_result_t zeVirtualMemFree_WithTracing(ze_context_handle_t hContext, const void* ptr, size_t size) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeVirtualMemFree,
                                    hContext, ptr, size);

    ze_virtual_mem_free_params_t tracerParams;
    tracerParams.phContext = &hContext;
    tracerParams.pptr = &ptr;
    tracerParams.psize = &size;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnVirtualMemFreeCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnVirtualMemFreeCb_t, VirtualMem, pfnFreeCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeVirtualMemFree,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phContext, *tracerParams.pptr, *tracerParams.psize);
}
ze_result_t zeVirtualMemQueryPageSize_WithTracing(ze_context_handle_t hContext, ze_device_handle_t hDevice, size_t size, size_t* pagesize) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeVirtualMemQueryPageSize,
                                    hContext, hDevice, size, pagesize);

    ze_virtual_mem_query_page_size_params_t tracerParams;
    tracerParams.phContext = &hContext;
    tracerParams.phDevice = &hDevice;
    tracerParams.psize = &size;
    tracerParams.ppagesize = &pagesize;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnVirtualMemQueryPageSizeCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnVirtualMemQueryPageSizeCb_t, VirtualMem, pfnQueryPageSizeCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeVirtualMemQueryPageSize,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phContext, *tracerParams.phDevice, *tracerParams.psize, *tracerParams.ppagesize);
}
ze_result_t zePhysicalMemCreate_WithTracing(ze_context_handle_t hContext, ze_device_handle_t hDevice, ze_physical_mem_desc_t* desc, ze_physical_mem_handle_t* phPhysicalMemory) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zePhysicalMemCreate,
                                    hContext, hDevice, desc, phPhysicalMemory);

    ze_physical_mem_create_params_t tracerParams;
    tracerParams.phContext = &hContext;
    tracerParams.phDevice = &hDevice;
    tracerParams.pdesc = &desc;
    tracerParams.pphPhysicalMemory = &phPhysicalMemory;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnPhysicalMemCreateCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnPhysicalMemCreateCb_t, PhysicalMem, pfnCreateCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zePhysicalMemCreate,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phContext, *tracerParams.phDevice, *tracerParams.pdesc, *tracerParams.pphPhysicalMemory);
}
ze_result_t zePhysicalMemDestroy_WithTracing(ze_context_handle_t hContext, ze_physical_mem_handle_t hPhysicalMemory) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zePhysicalMemDestroy,
                                    hContext, hPhysicalMemory);

    ze_physical_mem_destroy_params_t tracerParams;
    tracerParams.phContext = &hContext;
    tracerParams.phPhysicalMemory = &hPhysicalMemory;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnPhysicalMemDestroyCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnPhysicalMemDestroyCb_t, PhysicalMem, pfnDestroyCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zePhysicalMemDestroy,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phContext, *tracerParams.phPhysicalMemory);
}
ze_result_t zeVirtualMemMap_WithTracing(ze_context_handle_t hContext, const void* ptr, size_t size, ze_physical_mem_handle_t hPhysicalMemory, size_t offset, ze_memory_access_attribute_t access) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeVirtualMemMap,
                                    hContext, ptr, size, hPhysicalMemory, offset, access);

    ze_virtual_mem_map_params_t tracerParams;
    tracerParams.phContext = &hContext;
    tracerParams.pptr = &ptr;
    tracerParams.psize = &size;
    tracerParams.phPhysicalMemory = &hPhysicalMemory;
    tracerParams.poffset = &offset;
    tracerParams.paccess = &access;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnVirtualMemMapCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnVirtualMemMapCb_t, VirtualMem, pfnMapCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeVirtualMemMap,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phContext, *tracerParams.pptr, *tracerParams.psize, *tracerParams.phPhysicalMemory, *tracerParams.poffset, *tracerParams.paccess);
}
ze_result_t zeVirtualMemUnmap_WithTracing(ze_context_handle_t hContext, const void* ptr, size_t size) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeVirtualMemUnmap,
                                    hContext, ptr, size);

    ze_virtual_mem_unmap_params_t tracerParams;
    tracerParams.phContext = &hContext;
    tracerParams.pptr = &ptr;
    tracerParams.psize = &size;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnVirtualMemUnmapCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnVirtualMemUnmapCb_t, VirtualMem, pfnUnmapCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeVirtualMemUnmap,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phContext, *tracerParams.pptr, *tracerParams.psize);
}
ze_result_t zeVirtualMemSetAccessAttribute_WithTracing(ze_context_handle_t hContext, const void* ptr, size_t size, ze_memory_access_attribute_t access) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeVirtualMemSetAccessAttribute,
                                    hContext, ptr, size, access);

    ze_virtual_mem_set_access_attribute_params_t tracerParams;
    tracerParams.phContext = &hContext;
    tracerParams.pptr = &ptr;
    tracerParams.psize = &size;
    tracerParams.paccess = &access;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnVirtualMemSetAccessAttributeCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnVirtualMemSetAccessAttributeCb_t, VirtualMem, pfnSetAccessAttributeCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeVirtualMemSetAccessAttribute,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phContext, *tracerParams.pptr, *tracerParams.psize, *tracerParams.paccess);
}
ze_result_t zeVirtualMemGetAccessAttribute_WithTracing(ze_context_handle_t hContext, const void* ptr, size_t size, ze_memory_access_attribute_t* access, size_t* outSize) {
    ZE_HANDLE_TRACER_RECURSION(Cal::Client::Icd::LevelZero::zeVirtualMemGetAccessAttribute,
                                    hContext, ptr, size, access, outSize);

    ze_virtual_mem_get_access_attribute_params_t tracerParams;
    tracerParams.phContext = &hContext;
    tracerParams.pptr = &ptr;
    tracerParams.psize = &size;
    tracerParams.paccess = &access;
    tracerParams.poutSize = &outSize;

    Cal::Client::Icd::LevelZero::APITracerCallbackDataImp<ze_pfnVirtualMemGetAccessAttributeCb_t> apiCallbackData;

    ZE_GEN_PER_API_CALLBACK_STATE(apiCallbackData, ze_pfnVirtualMemGetAccessAttributeCb_t, VirtualMem, pfnGetAccessAttributeCb);

    return Cal::Client::Icd::LevelZero::apiTracerWrapperImp(Cal::Client::Icd::LevelZero::zeVirtualMemGetAccessAttribute,
                                                 &tracerParams,
                                                 apiCallbackData.apiOrdinal,
                                                 apiCallbackData.prologCallbacks,
                                                 apiCallbackData.epilogCallbacks,
                                                 *tracerParams.phContext, *tracerParams.pptr, *tracerParams.psize, *tracerParams.paccess, *tracerParams.poutSize);
}

} // namespace LevelZero
} // namespace Icd
} // namespace Client
} // namespace Cal


extern "C" {
ze_result_t zetMetricGroupGet (zet_device_handle_t hDevice, uint32_t* pCount, zet_metric_group_handle_t* phMetricGroups) {
    return Cal::Client::Icd::LevelZero::zetMetricGroupGet(hDevice, pCount, phMetricGroups);
}
ze_result_t zetMetricGroupGetProperties (zet_metric_group_handle_t hMetricGroup, zet_metric_group_properties_t* pProperties) {
    return Cal::Client::Icd::LevelZero::zetMetricGroupGetProperties(hMetricGroup, pProperties);
}
ze_result_t zetMetricGroupGetGlobalTimestampsExp (zet_metric_group_handle_t hMetricGroup, ze_bool_t synchronizedWithHost, uint64_t* globalTimestamp, uint64_t* metricTimestamp) {
    return Cal::Client::Icd::LevelZero::zetMetricGroupGetGlobalTimestampsExp(hMetricGroup, synchronizedWithHost, globalTimestamp, metricTimestamp);
}
ze_result_t zetMetricGroupGetExportDataExp (zet_metric_group_handle_t hMetricGroup, const uint8_t * pRawData, size_t rawDataSize, size_t* pExportDataSize, uint8_t* pExportData) {
    return Cal::Client::Icd::LevelZero::zetMetricGroupGetExportDataExp(hMetricGroup, pRawData, rawDataSize, pExportDataSize, pExportData);
}
ze_result_t zetMetricGet (zet_metric_group_handle_t hMetricGroup, uint32_t* pCount, zet_metric_handle_t* phMetrics) {
    return Cal::Client::Icd::LevelZero::zetMetricGet(hMetricGroup, pCount, phMetrics);
}
ze_result_t zetMetricGetProperties (zet_metric_handle_t hMetric, zet_metric_properties_t* pProperties) {
    return Cal::Client::Icd::LevelZero::zetMetricGetProperties(hMetric, pProperties);
}
ze_result_t zetContextActivateMetricGroups (zet_context_handle_t hContext, zet_device_handle_t hDevice, uint32_t count, zet_metric_group_handle_t* phMetricGroups) {
    return Cal::Client::Icd::LevelZero::zetContextActivateMetricGroups(hContext, hDevice, count, phMetricGroups);
}
ze_result_t zetMetricStreamerOpen (zet_context_handle_t hContext, zet_device_handle_t hDevice, zet_metric_group_handle_t hMetricGroup, zet_metric_streamer_desc_t* desc, ze_event_handle_t hNotificationEvent, zet_metric_streamer_handle_t* phMetricStreamer) {
    return Cal::Client::Icd::LevelZero::zetMetricStreamerOpen(hContext, hDevice, hMetricGroup, desc, hNotificationEvent, phMetricStreamer);
}
ze_result_t zetMetricStreamerReadData (zet_metric_streamer_handle_t hMetricStreamer, uint32_t maxReportCount, size_t* pRawDataSize, uint8_t* pRawData) {
    return Cal::Client::Icd::LevelZero::zetMetricStreamerReadData(hMetricStreamer, maxReportCount, pRawDataSize, pRawData);
}
ze_result_t zetMetricStreamerClose (zet_metric_streamer_handle_t hMetricStreamer) {
    return Cal::Client::Icd::LevelZero::zetMetricStreamerClose(hMetricStreamer);
}
ze_result_t zetTracerExpCreate (zet_context_handle_t hContext, const zet_tracer_exp_desc_t* desc, zet_tracer_exp_handle_t* phTracer) {
    return Cal::Client::Icd::LevelZero::zetTracerExpCreate(hContext, desc, phTracer);
}
ze_result_t zetTracerExpDestroy (zet_tracer_exp_handle_t hTracer) {
    return Cal::Client::Icd::LevelZero::zetTracerExpDestroy(hTracer);
}
ze_result_t zetTracerExpSetPrologues (zet_tracer_exp_handle_t hTracer, zet_core_callbacks_t* pCoreCbs) {
    return Cal::Client::Icd::LevelZero::zetTracerExpSetPrologues(hTracer, pCoreCbs);
}
ze_result_t zetTracerExpSetEpilogues (zet_tracer_exp_handle_t hTracer, zet_core_callbacks_t* pCoreCbs) {
    return Cal::Client::Icd::LevelZero::zetTracerExpSetEpilogues(hTracer, pCoreCbs);
}
ze_result_t zetTracerExpSetEnabled (zet_tracer_exp_handle_t hTracer, ze_bool_t enable) {
    return Cal::Client::Icd::LevelZero::zetTracerExpSetEnabled(hTracer, enable);
}
ze_result_t zetDeviceGetDebugProperties (ze_device_handle_t hDevice, zet_device_debug_properties_t* pDebugProperties) {
    return Cal::Client::Icd::LevelZero::zetDeviceGetDebugProperties(hDevice, pDebugProperties);
}
ze_result_t zetDebugAttach (ze_device_handle_t hDevice, const zet_debug_config_t* config, zet_debug_session_handle_t* phDebug) {
    return Cal::Client::Icd::LevelZero::zetDebugAttach(hDevice, config, phDebug);
}
ze_result_t zetDebugDetach (zet_debug_session_handle_t hDebug) {
    return Cal::Client::Icd::LevelZero::zetDebugDetach(hDebug);
}
ze_result_t zesDeviceReset (zes_device_handle_t hDevice, ze_bool_t force) {
    return Cal::Client::Icd::LevelZero::zesDeviceReset(hDevice, force);
}
ze_result_t zesDeviceResetExt (zes_device_handle_t hDevice, zes_reset_properties_t* pProperties) {
    return Cal::Client::Icd::LevelZero::zesDeviceResetExt(hDevice, pProperties);
}
ze_result_t zesDeviceEnumPowerDomains (zes_device_handle_t hDevice, uint32_t* pCount, zes_pwr_handle_t* phPower) {
    return Cal::Client::Icd::LevelZero::zesDeviceEnumPowerDomains(hDevice, pCount, phPower);
}
ze_result_t zesDeviceGetCardPowerDomain (zes_device_handle_t hDevice, zes_pwr_handle_t* phPower) {
    return Cal::Client::Icd::LevelZero::zesDeviceGetCardPowerDomain(hDevice, phPower);
}
ze_result_t zesPowerGetProperties (zes_pwr_handle_t hPower, zes_power_properties_t* pProperties) {
    return Cal::Client::Icd::LevelZero::zesPowerGetProperties(hPower, pProperties);
}
ze_result_t zesPowerGetEnergyCounter (zes_pwr_handle_t hPower, zes_power_energy_counter_t* pEnergy) {
    return Cal::Client::Icd::LevelZero::zesPowerGetEnergyCounter(hPower, pEnergy);
}
ze_result_t zesPowerGetLimits (zes_pwr_handle_t hPower, zes_power_sustained_limit_t* pSustained, zes_power_burst_limit_t* pBurst, zes_power_peak_limit_t* pPeak) {
    return Cal::Client::Icd::LevelZero::zesPowerGetLimits(hPower, pSustained, pBurst, pPeak);
}
ze_result_t zesPowerSetLimits (zes_pwr_handle_t hPower, const zes_power_sustained_limit_t* pSustained, const zes_power_burst_limit_t* pBurst, const zes_power_peak_limit_t* pPeak) {
    return Cal::Client::Icd::LevelZero::zesPowerSetLimits(hPower, pSustained, pBurst, pPeak);
}
ze_result_t zesPowerGetLimitsExt (zes_pwr_handle_t hPower, uint32_t* pCount, zes_power_limit_ext_desc_t* pSustained) {
    return Cal::Client::Icd::LevelZero::zesPowerGetLimitsExt(hPower, pCount, pSustained);
}
ze_result_t zesPowerSetLimitsExt (zes_pwr_handle_t hPower, uint32_t* pCount, zes_power_limit_ext_desc_t* pSustained) {
    return Cal::Client::Icd::LevelZero::zesPowerSetLimitsExt(hPower, pCount, pSustained);
}
ze_result_t zesPowerGetEnergyThreshold (zes_pwr_handle_t hPower, zes_energy_threshold_t * pThreshold) {
    return Cal::Client::Icd::LevelZero::zesPowerGetEnergyThreshold(hPower, pThreshold);
}
ze_result_t zesPowerSetEnergyThreshold (zes_pwr_handle_t hPower, double pThreshold) {
    return Cal::Client::Icd::LevelZero::zesPowerSetEnergyThreshold(hPower, pThreshold);
}
ze_result_t zesDeviceEventRegister (zes_device_handle_t hDevice, zes_event_type_flags_t events) {
    return Cal::Client::Icd::LevelZero::zesDeviceEventRegister(hDevice, events);
}
ze_result_t zesDriverEventListen (ze_driver_handle_t hDriver, uint32_t timeout, uint32_t count, ze_device_handle_t* phDevices, uint32_t* pNumDeviceEvents, zes_event_type_flags_t* pEvents) {
    return Cal::Client::Icd::LevelZero::zesDriverEventListen(hDriver, timeout, count, phDevices, pNumDeviceEvents, pEvents);
}
ze_result_t zesDriverEventListenEx (ze_driver_handle_t hDriver, uint64_t timeout, uint32_t count, zes_device_handle_t* phDevices, uint32_t* pNumDeviceEvents, zes_event_type_flags_t* pEvents) {
    return Cal::Client::Icd::LevelZero::zesDriverEventListenEx(hDriver, timeout, count, phDevices, pNumDeviceEvents, pEvents);
}
ze_result_t zesDeviceEnumTemperatureSensors (zes_device_handle_t hDevice, uint32_t* pCount, zes_temp_handle_t* phTemperature) {
    return Cal::Client::Icd::LevelZero::zesDeviceEnumTemperatureSensors(hDevice, pCount, phTemperature);
}
ze_result_t zesTemperatureGetProperties (zes_temp_handle_t hTemperature, zes_temp_properties_t* pProperties) {
    return Cal::Client::Icd::LevelZero::zesTemperatureGetProperties(hTemperature, pProperties);
}
ze_result_t zesTemperatureGetConfig (zes_temp_handle_t hTemperature, zes_temp_config_t * pConfig) {
    return Cal::Client::Icd::LevelZero::zesTemperatureGetConfig(hTemperature, pConfig);
}
ze_result_t zesTemperatureSetConfig (zes_temp_handle_t hTemperature, const zes_temp_config_t* pConfig) {
    return Cal::Client::Icd::LevelZero::zesTemperatureSetConfig(hTemperature, pConfig);
}
ze_result_t zesTemperatureGetState (zes_temp_handle_t hTemperature, double* pTemperature) {
    return Cal::Client::Icd::LevelZero::zesTemperatureGetState(hTemperature, pTemperature);
}
ze_result_t zesDeviceEnumRasErrorSets (zes_device_handle_t hDevice, uint32_t* pCount, zes_ras_handle_t* phRas) {
    return Cal::Client::Icd::LevelZero::zesDeviceEnumRasErrorSets(hDevice, pCount, phRas);
}
ze_result_t zesRasGetProperties (zes_ras_handle_t hRas, zes_ras_properties_t* pProperties) {
    return Cal::Client::Icd::LevelZero::zesRasGetProperties(hRas, pProperties);
}
ze_result_t zesRasGetConfig (zes_ras_handle_t hRas, zes_ras_config_t * pConfig) {
    return Cal::Client::Icd::LevelZero::zesRasGetConfig(hRas, pConfig);
}
ze_result_t zesRasSetConfig (zes_ras_handle_t hRas, const zes_ras_config_t* pConfig) {
    return Cal::Client::Icd::LevelZero::zesRasSetConfig(hRas, pConfig);
}
ze_result_t zesRasGetState (zes_ras_handle_t hRas, ze_bool_t clear, zes_ras_state_t* pState) {
    return Cal::Client::Icd::LevelZero::zesRasGetState(hRas, clear, pState);
}
ze_result_t zesDeviceEnumFrequencyDomains (zes_device_handle_t hDevice, uint32_t* pCount, zes_freq_handle_t* phFrequency) {
    return Cal::Client::Icd::LevelZero::zesDeviceEnumFrequencyDomains(hDevice, pCount, phFrequency);
}
ze_result_t zesFrequencyGetProperties (zes_freq_handle_t hFrequency, zes_freq_properties_t* pProperties) {
    return Cal::Client::Icd::LevelZero::zesFrequencyGetProperties(hFrequency, pProperties);
}
ze_result_t zesFrequencyGetAvailableClocks (zes_freq_handle_t hFrequency, uint32_t* pCount, double* phFrequency) {
    return Cal::Client::Icd::LevelZero::zesFrequencyGetAvailableClocks(hFrequency, pCount, phFrequency);
}
ze_result_t zesFrequencyGetRange (zes_freq_handle_t hFrequency, zes_freq_range_t* pConfig) {
    return Cal::Client::Icd::LevelZero::zesFrequencyGetRange(hFrequency, pConfig);
}
ze_result_t zesFrequencySetRange (zes_freq_handle_t hFrequency, const zes_freq_range_t* pLimits) {
    return Cal::Client::Icd::LevelZero::zesFrequencySetRange(hFrequency, pLimits);
}
ze_result_t zesFrequencyGetState (zes_freq_handle_t hFrequency, zes_freq_state_t* pState) {
    return Cal::Client::Icd::LevelZero::zesFrequencyGetState(hFrequency, pState);
}
ze_result_t zesFrequencyGetThrottleTime (zes_freq_handle_t hFrequency, zes_freq_throttle_time_t* pThrottleTime) {
    return Cal::Client::Icd::LevelZero::zesFrequencyGetThrottleTime(hFrequency, pThrottleTime);
}
ze_result_t zesFrequencyOcGetCapabilities (zes_freq_handle_t hFrequency, zes_oc_capabilities_t* pOcCapabilities) {
    return Cal::Client::Icd::LevelZero::zesFrequencyOcGetCapabilities(hFrequency, pOcCapabilities);
}
ze_result_t zesFrequencyOcGetVoltageTarget (zes_freq_handle_t hFrequency, double* pCurrentVoltageTarget, double* pCurrentVoltageOffset) {
    return Cal::Client::Icd::LevelZero::zesFrequencyOcGetVoltageTarget(hFrequency, pCurrentVoltageTarget, pCurrentVoltageOffset);
}
ze_result_t zesFrequencyOcSetVoltageTarget (zes_freq_handle_t hFrequency, double CurrentVoltageTarget, double CurrentVoltageOffset) {
    return Cal::Client::Icd::LevelZero::zesFrequencyOcSetVoltageTarget(hFrequency, CurrentVoltageTarget, CurrentVoltageOffset);
}
ze_result_t zesFrequencyOcSetMode (zes_freq_handle_t hFrequency, zes_oc_mode_t CurrentOcMode) {
    return Cal::Client::Icd::LevelZero::zesFrequencyOcSetMode(hFrequency, CurrentOcMode);
}
ze_result_t zesFrequencyOcGetMode (zes_freq_handle_t hFrequency, zes_oc_mode_t* pCurrentOcMode) {
    return Cal::Client::Icd::LevelZero::zesFrequencyOcGetMode(hFrequency, pCurrentOcMode);
}
ze_result_t zesFrequencyOcGetIccMax (zes_freq_handle_t hFrequency, double* pOcIccMax) {
    return Cal::Client::Icd::LevelZero::zesFrequencyOcGetIccMax(hFrequency, pOcIccMax);
}
ze_result_t zesFrequencyOcSetIccMax (zes_freq_handle_t hFrequency, double ocIccMax) {
    return Cal::Client::Icd::LevelZero::zesFrequencyOcSetIccMax(hFrequency, ocIccMax);
}
ze_result_t zesFrequencyOcGetTjMax (zes_freq_handle_t hFrequency, double* pOcTjMax) {
    return Cal::Client::Icd::LevelZero::zesFrequencyOcGetTjMax(hFrequency, pOcTjMax);
}
ze_result_t zesFrequencyOcSetTjMax (zes_freq_handle_t hFrequency, double ocTjMax) {
    return Cal::Client::Icd::LevelZero::zesFrequencyOcSetTjMax(hFrequency, ocTjMax);
}
ze_result_t zesDeviceEnumEngineGroups (zes_device_handle_t hDevice, uint32_t* pCount, zes_engine_handle_t* phEngine) {
    return Cal::Client::Icd::LevelZero::zesDeviceEnumEngineGroups(hDevice, pCount, phEngine);
}
ze_result_t zesDeviceEnumSchedulers (zes_device_handle_t hDevice, uint32_t* pCount, zes_sched_handle_t* phScheduler) {
    return Cal::Client::Icd::LevelZero::zesDeviceEnumSchedulers(hDevice, pCount, phScheduler);
}
ze_result_t zesSchedulerGetProperties (zes_sched_handle_t hScheduler, zes_sched_properties_t* pProperties) {
    return Cal::Client::Icd::LevelZero::zesSchedulerGetProperties(hScheduler, pProperties);
}
ze_result_t zesSchedulerGetCurrentMode (zes_sched_handle_t hScheduler, zes_sched_mode_t* pMode) {
    return Cal::Client::Icd::LevelZero::zesSchedulerGetCurrentMode(hScheduler, pMode);
}
ze_result_t zesSchedulerGetTimeoutModeProperties (zes_sched_handle_t hScheduler, ze_bool_t getDefaults, zes_sched_timeout_properties_t* pConfig) {
    return Cal::Client::Icd::LevelZero::zesSchedulerGetTimeoutModeProperties(hScheduler, getDefaults, pConfig);
}
ze_result_t zesSchedulerGetTimesliceModeProperties (zes_sched_handle_t hScheduler, ze_bool_t getDefaults, zes_sched_timeslice_properties_t* pConfig) {
    return Cal::Client::Icd::LevelZero::zesSchedulerGetTimesliceModeProperties(hScheduler, getDefaults, pConfig);
}
ze_result_t zesSchedulerSetTimeoutMode (zes_sched_handle_t hScheduler, zes_sched_timeout_properties_t* pProperties, ze_bool_t* pNeedReload) {
    return Cal::Client::Icd::LevelZero::zesSchedulerSetTimeoutMode(hScheduler, pProperties, pNeedReload);
}
ze_result_t zesSchedulerSetTimesliceMode (zes_sched_handle_t hScheduler, zes_sched_timeslice_properties_t* pProperties, ze_bool_t* pNeedReload) {
    return Cal::Client::Icd::LevelZero::zesSchedulerSetTimesliceMode(hScheduler, pProperties, pNeedReload);
}
ze_result_t zesSchedulerSetExclusiveMode (zes_sched_handle_t hScheduler, ze_bool_t* pNeedReload) {
    return Cal::Client::Icd::LevelZero::zesSchedulerSetExclusiveMode(hScheduler, pNeedReload);
}
ze_result_t zesSchedulerSetComputeUnitDebugMode (zes_sched_handle_t hScheduler, ze_bool_t* pNeedReload) {
    return Cal::Client::Icd::LevelZero::zesSchedulerSetComputeUnitDebugMode(hScheduler, pNeedReload);
}
ze_result_t zesEngineGetProperties (zes_engine_handle_t hEngine, zes_engine_properties_t* pProperties) {
    return Cal::Client::Icd::LevelZero::zesEngineGetProperties(hEngine, pProperties);
}
ze_result_t zesEngineGetActivity (zes_engine_handle_t hEngine, zes_engine_stats_t* pStats) {
    return Cal::Client::Icd::LevelZero::zesEngineGetActivity(hEngine, pStats);
}
ze_result_t zesDeviceGetState (zes_device_handle_t hDevice, zes_device_state_t* pState) {
    return Cal::Client::Icd::LevelZero::zesDeviceGetState(hDevice, pState);
}
ze_result_t zesDeviceProcessesGetState (zes_device_handle_t hDevice, uint32_t* pCount, zes_process_state_t* pProcesses) {
    return Cal::Client::Icd::LevelZero::zesDeviceProcessesGetState(hDevice, pCount, pProcesses);
}
ze_result_t zesDevicePciGetProperties (zes_device_handle_t hDevice, zes_pci_properties_t* pProperties) {
    return Cal::Client::Icd::LevelZero::zesDevicePciGetProperties(hDevice, pProperties);
}
ze_result_t zesDevicePciGetState (zes_device_handle_t hDevice, zes_pci_state_t* pState) {
    return Cal::Client::Icd::LevelZero::zesDevicePciGetState(hDevice, pState);
}
ze_result_t zesDevicePciGetBars (zes_device_handle_t hDevice, uint32_t* pCount, zes_pci_bar_properties_t* pProperties) {
    return Cal::Client::Icd::LevelZero::zesDevicePciGetBars(hDevice, pCount, pProperties);
}
ze_result_t zesDevicePciGetStats (zes_device_handle_t hDevice, zes_pci_stats_t* pStats) {
    return Cal::Client::Icd::LevelZero::zesDevicePciGetStats(hDevice, pStats);
}
ze_result_t zesDeviceGetProperties (zes_device_handle_t hDevice, zes_device_properties_t* pProperties) {
    return Cal::Client::Icd::LevelZero::zesDeviceGetProperties(hDevice, pProperties);
}
ze_result_t zesDeviceEnumMemoryModules (zes_device_handle_t hDevice, uint32_t* pCount, zes_mem_handle_t* phMemory) {
    return Cal::Client::Icd::LevelZero::zesDeviceEnumMemoryModules(hDevice, pCount, phMemory);
}
ze_result_t zesDeviceEnumPerformanceFactorDomains (zes_device_handle_t hDevice, uint32_t* pCount, zes_perf_handle_t* phPerf) {
    return Cal::Client::Icd::LevelZero::zesDeviceEnumPerformanceFactorDomains(hDevice, pCount, phPerf);
}
ze_result_t zesPerformanceFactorGetProperties (zes_perf_handle_t hPerf, zes_perf_properties_t* pProperties) {
    return Cal::Client::Icd::LevelZero::zesPerformanceFactorGetProperties(hPerf, pProperties);
}
ze_result_t zesPerformanceFactorGetConfig (zes_perf_handle_t hPerf, double* pFactor) {
    return Cal::Client::Icd::LevelZero::zesPerformanceFactorGetConfig(hPerf, pFactor);
}
ze_result_t zesPerformanceFactorSetConfig (zes_perf_handle_t hPerf, double pFactor) {
    return Cal::Client::Icd::LevelZero::zesPerformanceFactorSetConfig(hPerf, pFactor);
}
ze_result_t zesDeviceEnumStandbyDomains (zes_device_handle_t hDevice, uint32_t* pCount, zes_standby_handle_t* phStandby) {
    return Cal::Client::Icd::LevelZero::zesDeviceEnumStandbyDomains(hDevice, pCount, phStandby);
}
ze_result_t zesStandbyGetProperties (zes_standby_handle_t hStandby, zes_standby_properties_t* pProperties) {
    return Cal::Client::Icd::LevelZero::zesStandbyGetProperties(hStandby, pProperties);
}
ze_result_t zesStandbyGetMode (zes_standby_handle_t hStandby, zes_standby_promo_mode_t* pMode) {
    return Cal::Client::Icd::LevelZero::zesStandbyGetMode(hStandby, pMode);
}
ze_result_t zesStandbySetMode (zes_standby_handle_t hStandby, zes_standby_promo_mode_t mode) {
    return Cal::Client::Icd::LevelZero::zesStandbySetMode(hStandby, mode);
}
ze_result_t zesMemoryGetProperties (zes_mem_handle_t hMemory, zes_mem_properties_t* pProperties) {
    return Cal::Client::Icd::LevelZero::zesMemoryGetProperties(hMemory, pProperties);
}
ze_result_t zeInit (ze_init_flags_t flags) {
    return Cal::Client::Icd::LevelZero::zeInit(flags);
}
ze_result_t zeCommandListAppendMemoryRangesBarrier (ze_command_list_handle_t hCommandList, uint32_t numRanges, const size_t* pRangeSizes, const void** pRanges, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    return Cal::Client::Icd::LevelZero::zeCommandListAppendMemoryRangesBarrier(hCommandList, numRanges, pRangeSizes, pRanges, hSignalEvent, numWaitEvents, phWaitEvents);
}
ze_result_t zeContextSystemBarrier (ze_context_handle_t hContext, ze_device_handle_t hDevice) {
    return Cal::Client::Icd::LevelZero::zeContextSystemBarrier(hContext, hDevice);
}
ze_result_t zeCommandListCreate (ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_list_desc_t* desc, ze_command_list_handle_t* phCommandList) {
    return Cal::Client::Icd::LevelZero::zeCommandListCreate(hContext, hDevice, desc, phCommandList);
}
ze_result_t zeCommandListCreateImmediate (ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_queue_desc_t* altdesc, ze_command_list_handle_t* phCommandList) {
    return Cal::Client::Icd::LevelZero::zeCommandListCreateImmediate(hContext, hDevice, altdesc, phCommandList);
}
ze_result_t zeCommandListDestroy (ze_command_list_handle_t hCommandList) {
    return Cal::Client::Icd::LevelZero::zeCommandListDestroy(hCommandList);
}
ze_result_t zeCommandListClose (ze_command_list_handle_t hCommandList) {
    return Cal::Client::Icd::LevelZero::zeCommandListClose(hCommandList);
}
ze_result_t zeCommandListReset (ze_command_list_handle_t hCommandList) {
    return Cal::Client::Icd::LevelZero::zeCommandListReset(hCommandList);
}
ze_result_t zeCommandListAppendWriteGlobalTimestamp (ze_command_list_handle_t hCommandList, uint64_t* dstptr, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    return Cal::Client::Icd::LevelZero::zeCommandListAppendWriteGlobalTimestamp(hCommandList, dstptr, hSignalEvent, numWaitEvents, phWaitEvents);
}
ze_result_t zeCommandQueueCreate (ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_command_queue_desc_t* desc, ze_command_queue_handle_t* phCommandQueue) {
    return Cal::Client::Icd::LevelZero::zeCommandQueueCreate(hContext, hDevice, desc, phCommandQueue);
}
ze_result_t zeCommandQueueDestroy (ze_command_queue_handle_t hCommandQueue) {
    return Cal::Client::Icd::LevelZero::zeCommandQueueDestroy(hCommandQueue);
}
ze_result_t zeCommandQueueExecuteCommandLists (ze_command_queue_handle_t hCommandQueue, uint32_t numCommandLists, ze_command_list_handle_t* phCommandLists, ze_fence_handle_t hFence) {
    return Cal::Client::Icd::LevelZero::zeCommandQueueExecuteCommandLists(hCommandQueue, numCommandLists, phCommandLists, hFence);
}
ze_result_t zeCommandQueueSynchronize (ze_command_queue_handle_t hCommandQueue, uint64_t timeout) {
    return Cal::Client::Icd::LevelZero::zeCommandQueueSynchronize(hCommandQueue, timeout);
}
ze_result_t zeContextCreate (ze_driver_handle_t hDriver, const ze_context_desc_t* desc, ze_context_handle_t* phContext) {
    return Cal::Client::Icd::LevelZero::zeContextCreate(hDriver, desc, phContext);
}
ze_result_t zeContextCreateEx (ze_driver_handle_t hDriver, const ze_context_desc_t* desc, uint32_t numDevices, ze_device_handle_t* phDevices, ze_context_handle_t* phContext) {
    return Cal::Client::Icd::LevelZero::zeContextCreateEx(hDriver, desc, numDevices, phDevices, phContext);
}
ze_result_t zeContextDestroy (ze_context_handle_t hContext) {
    return Cal::Client::Icd::LevelZero::zeContextDestroy(hContext);
}
ze_result_t zeContextGetStatus (ze_context_handle_t hContext) {
    return Cal::Client::Icd::LevelZero::zeContextGetStatus(hContext);
}
ze_result_t zeCommandListAppendMemoryCopy (ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    return Cal::Client::Icd::LevelZero::zeCommandListAppendMemoryCopy(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
}
ze_result_t zeCommandListAppendMemoryFill (ze_command_list_handle_t hCommandList, void* ptr, const void* pattern, size_t pattern_size, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    return Cal::Client::Icd::LevelZero::zeCommandListAppendMemoryFill(hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEvents);
}
ze_result_t zeCommandListAppendMemoryCopyRegion (ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    return Cal::Client::Icd::LevelZero::zeCommandListAppendMemoryCopyRegion(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents);
}
ze_result_t zeCommandListAppendMemoryCopyFromContext (ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    return Cal::Client::Icd::LevelZero::zeCommandListAppendMemoryCopyFromContext(hCommandList, dstptr, hContextSrc, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
}
ze_result_t zeCommandListAppendMemoryPrefetch (ze_command_list_handle_t hCommandList, const void* ptr, size_t size) {
    return Cal::Client::Icd::LevelZero::zeCommandListAppendMemoryPrefetch(hCommandList, ptr, size);
}
ze_result_t zeCommandListAppendMemAdvise (ze_command_list_handle_t hCommandList, ze_device_handle_t hDevice, const void* ptr, size_t size, ze_memory_advice_t advice) {
    return Cal::Client::Icd::LevelZero::zeCommandListAppendMemAdvise(hCommandList, hDevice, ptr, size, advice);
}
ze_result_t zeDeviceGet (ze_driver_handle_t hDriver, uint32_t* pCount, ze_device_handle_t* phDevices) {
    return Cal::Client::Icd::LevelZero::zeDeviceGet(hDriver, pCount, phDevices);
}
ze_result_t zeDeviceGetSubDevices (ze_device_handle_t hDevice, uint32_t* pCount, ze_device_handle_t* phSubdevices) {
    return Cal::Client::Icd::LevelZero::zeDeviceGetSubDevices(hDevice, pCount, phSubdevices);
}
ze_result_t zeDeviceGetProperties (ze_device_handle_t hDevice, ze_device_properties_t* pDeviceProperties) {
    return Cal::Client::Icd::LevelZero::zeDeviceGetProperties(hDevice, pDeviceProperties);
}
ze_result_t zeDeviceGetComputeProperties (ze_device_handle_t hDevice, ze_device_compute_properties_t* pComputeProperties) {
    return Cal::Client::Icd::LevelZero::zeDeviceGetComputeProperties(hDevice, pComputeProperties);
}
ze_result_t zeDeviceGetModuleProperties (ze_device_handle_t hDevice, ze_device_module_properties_t* pModuleProperties) {
    return Cal::Client::Icd::LevelZero::zeDeviceGetModuleProperties(hDevice, pModuleProperties);
}
ze_result_t zeDeviceGetCommandQueueGroupProperties (ze_device_handle_t hDevice, uint32_t* pCount, ze_command_queue_group_properties_t* pCommandQueueGroupProperties) {
    return Cal::Client::Icd::LevelZero::zeDeviceGetCommandQueueGroupProperties(hDevice, pCount, pCommandQueueGroupProperties);
}
ze_result_t zeDeviceGetMemoryProperties (ze_device_handle_t hDevice, uint32_t* pCount, ze_device_memory_properties_t* pMemProperties) {
    return Cal::Client::Icd::LevelZero::zeDeviceGetMemoryProperties(hDevice, pCount, pMemProperties);
}
ze_result_t zeDeviceGetMemoryAccessProperties (ze_device_handle_t hDevice, ze_device_memory_access_properties_t* pMemAccessProperties) {
    return Cal::Client::Icd::LevelZero::zeDeviceGetMemoryAccessProperties(hDevice, pMemAccessProperties);
}
ze_result_t zeDeviceGetCacheProperties (ze_device_handle_t hDevice, uint32_t* pCount, ze_device_cache_properties_t* pCacheProperties) {
    return Cal::Client::Icd::LevelZero::zeDeviceGetCacheProperties(hDevice, pCount, pCacheProperties);
}
ze_result_t zeDeviceGetImageProperties (ze_device_handle_t hDevice, ze_device_image_properties_t* pImageProperties) {
    return Cal::Client::Icd::LevelZero::zeDeviceGetImageProperties(hDevice, pImageProperties);
}
ze_result_t zeDeviceGetExternalMemoryProperties (ze_device_handle_t hDevice, ze_device_external_memory_properties_t* pExternalMemoryProperties) {
    return Cal::Client::Icd::LevelZero::zeDeviceGetExternalMemoryProperties(hDevice, pExternalMemoryProperties);
}
ze_result_t zeDeviceGetP2PProperties (ze_device_handle_t hDevice, ze_device_handle_t hPeerDevice, ze_device_p2p_properties_t* pP2PProperties) {
    return Cal::Client::Icd::LevelZero::zeDeviceGetP2PProperties(hDevice, hPeerDevice, pP2PProperties);
}
ze_result_t zeDeviceCanAccessPeer (ze_device_handle_t hDevice, ze_device_handle_t hPeerDevice, ze_bool_t* value) {
    return Cal::Client::Icd::LevelZero::zeDeviceCanAccessPeer(hDevice, hPeerDevice, value);
}
ze_result_t zeDeviceGetStatus (ze_device_handle_t hDevice) {
    return Cal::Client::Icd::LevelZero::zeDeviceGetStatus(hDevice);
}
ze_result_t zeDeviceGetGlobalTimestamps (ze_device_handle_t hDevice, uint64_t* hostTimestamp, uint64_t* deviceTimestamp) {
    return Cal::Client::Icd::LevelZero::zeDeviceGetGlobalTimestamps(hDevice, hostTimestamp, deviceTimestamp);
}
ze_result_t zeDeviceReserveCacheExt (ze_device_handle_t hDevice, size_t cacheLevel, size_t cacheReservationSize) {
    return Cal::Client::Icd::LevelZero::zeDeviceReserveCacheExt(hDevice, cacheLevel, cacheReservationSize);
}
ze_result_t zeDeviceSetCacheAdviceExt (ze_device_handle_t hDevice, void* ptr, size_t regionSize, ze_cache_ext_region_t cacheRegion) {
    return Cal::Client::Icd::LevelZero::zeDeviceSetCacheAdviceExt(hDevice, ptr, regionSize, cacheRegion);
}
ze_result_t zeDriverGet (uint32_t* pCount, ze_driver_handle_t* phDrivers) {
    return Cal::Client::Icd::LevelZero::zeDriverGet(pCount, phDrivers);
}
ze_result_t zeDriverGetApiVersion (ze_driver_handle_t hDriver, ze_api_version_t* version) {
    return Cal::Client::Icd::LevelZero::zeDriverGetApiVersion(hDriver, version);
}
ze_result_t zeDriverGetProperties (ze_driver_handle_t hDriver, ze_driver_properties_t* pDriverProperties) {
    return Cal::Client::Icd::LevelZero::zeDriverGetProperties(hDriver, pDriverProperties);
}
ze_result_t zeDriverGetIpcProperties (ze_driver_handle_t hDriver, ze_driver_ipc_properties_t* pIpcProperties) {
    return Cal::Client::Icd::LevelZero::zeDriverGetIpcProperties(hDriver, pIpcProperties);
}
ze_result_t zeDriverGetExtensionProperties (ze_driver_handle_t hDriver, uint32_t* pCount, ze_driver_extension_properties_t* pExtensionProperties) {
    return Cal::Client::Icd::LevelZero::zeDriverGetExtensionProperties(hDriver, pCount, pExtensionProperties);
}
ze_result_t zeDriverGetExtensionFunctionAddress (ze_driver_handle_t hDriver, const char* name, void** ppFunctionAddress) {
    return Cal::Client::Icd::LevelZero::zeDriverGetExtensionFunctionAddress(hDriver, name, ppFunctionAddress);
}
ze_result_t zeEventPoolCreate (ze_context_handle_t hContext, const ze_event_pool_desc_t* desc, uint32_t numDevices, ze_device_handle_t* phDevices, ze_event_pool_handle_t* phEventPool) {
    return Cal::Client::Icd::LevelZero::zeEventPoolCreate(hContext, desc, numDevices, phDevices, phEventPool);
}
ze_result_t zeEventPoolDestroy (ze_event_pool_handle_t hEventPool) {
    return Cal::Client::Icd::LevelZero::zeEventPoolDestroy(hEventPool);
}
ze_result_t zeEventCreate (ze_event_pool_handle_t hEventPool, const ze_event_desc_t* desc, ze_event_handle_t* phEvent) {
    return Cal::Client::Icd::LevelZero::zeEventCreate(hEventPool, desc, phEvent);
}
ze_result_t zeEventDestroy (ze_event_handle_t hEvent) {
    return Cal::Client::Icd::LevelZero::zeEventDestroy(hEvent);
}
ze_result_t zeEventPoolGetIpcHandle (ze_event_pool_handle_t hEventPool, ze_ipc_event_pool_handle_t* phIpc) {
    return Cal::Client::Icd::LevelZero::zeEventPoolGetIpcHandle(hEventPool, phIpc);
}
ze_result_t zeEventPoolOpenIpcHandle (ze_context_handle_t hContext, ze_ipc_event_pool_handle_t hIpc, ze_event_pool_handle_t* phEventPool) {
    return Cal::Client::Icd::LevelZero::zeEventPoolOpenIpcHandle(hContext, hIpc, phEventPool);
}
ze_result_t zeEventPoolCloseIpcHandle (ze_event_pool_handle_t hEventPool) {
    return Cal::Client::Icd::LevelZero::zeEventPoolCloseIpcHandle(hEventPool);
}
ze_result_t zeCommandListAppendBarrier (ze_command_list_handle_t hCommandList, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    return Cal::Client::Icd::LevelZero::zeCommandListAppendBarrier(hCommandList, hSignalEvent, numWaitEvents, phWaitEvents);
}
ze_result_t zeCommandListAppendSignalEvent (ze_command_list_handle_t hCommandList, ze_event_handle_t hEvent) {
    return Cal::Client::Icd::LevelZero::zeCommandListAppendSignalEvent(hCommandList, hEvent);
}
ze_result_t zeCommandListAppendWaitOnEvents (ze_command_list_handle_t hCommandList, uint32_t numEvents, ze_event_handle_t* phEvents) {
    return Cal::Client::Icd::LevelZero::zeCommandListAppendWaitOnEvents(hCommandList, numEvents, phEvents);
}
ze_result_t zeEventHostSignal (ze_event_handle_t hEvent) {
    return Cal::Client::Icd::LevelZero::zeEventHostSignal(hEvent);
}
ze_result_t zeEventHostSynchronize (ze_event_handle_t hEvent, uint64_t timeout) {
    return Cal::Client::Icd::LevelZero::zeEventHostSynchronize(hEvent, timeout);
}
ze_result_t zeEventQueryStatus (ze_event_handle_t hEvent) {
    return Cal::Client::Icd::LevelZero::zeEventQueryStatus(hEvent);
}
ze_result_t zeCommandListAppendEventReset (ze_command_list_handle_t hCommandList, ze_event_handle_t hEvent) {
    return Cal::Client::Icd::LevelZero::zeCommandListAppendEventReset(hCommandList, hEvent);
}
ze_result_t zeEventHostReset (ze_event_handle_t hEvent) {
    return Cal::Client::Icd::LevelZero::zeEventHostReset(hEvent);
}
ze_result_t zeEventQueryKernelTimestamp (ze_event_handle_t hEvent, ze_kernel_timestamp_result_t* dstptr) {
    return Cal::Client::Icd::LevelZero::zeEventQueryKernelTimestamp(hEvent, dstptr);
}
ze_result_t zeCommandListAppendQueryKernelTimestamps (ze_command_list_handle_t hCommandList, uint32_t numEvents, ze_event_handle_t* phEvents, void* dstptr, const size_t* pOffsets, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    return Cal::Client::Icd::LevelZero::zeCommandListAppendQueryKernelTimestamps(hCommandList, numEvents, phEvents, dstptr, pOffsets, hSignalEvent, numWaitEvents, phWaitEvents);
}
ze_result_t zeEventQueryTimestampsExp (ze_event_handle_t hEvent, ze_device_handle_t hDevice, uint32_t* pCount, ze_kernel_timestamp_result_t* pTimestamps) {
    return Cal::Client::Icd::LevelZero::zeEventQueryTimestampsExp(hEvent, hDevice, pCount, pTimestamps);
}
ze_result_t zeEventQueryKernelTimestampsExt (ze_event_handle_t hEvent, ze_device_handle_t hDevice, uint32_t* pCount, ze_event_query_kernel_timestamps_results_ext_properties_t* pResults) {
    return Cal::Client::Icd::LevelZero::zeEventQueryKernelTimestampsExt(hEvent, hDevice, pCount, pResults);
}
ze_result_t zeFabricVertexGetExp (ze_driver_handle_t hDriver, uint32_t* pCount, ze_fabric_vertex_handle_t* phVertices) {
    return Cal::Client::Icd::LevelZero::zeFabricVertexGetExp(hDriver, pCount, phVertices);
}
ze_result_t zeFabricVertexGetSubVerticesExp (ze_fabric_vertex_handle_t hVertex, uint32_t* pCount, ze_fabric_vertex_handle_t* phSubvertices) {
    return Cal::Client::Icd::LevelZero::zeFabricVertexGetSubVerticesExp(hVertex, pCount, phSubvertices);
}
ze_result_t zeFabricVertexGetPropertiesExp (ze_fabric_vertex_handle_t hVertex, ze_fabric_vertex_exp_properties_t* pVertexProperties) {
    return Cal::Client::Icd::LevelZero::zeFabricVertexGetPropertiesExp(hVertex, pVertexProperties);
}
ze_result_t zeFabricVertexGetDeviceExp (ze_fabric_vertex_handle_t hVertex, ze_device_handle_t* pDevice) {
    return Cal::Client::Icd::LevelZero::zeFabricVertexGetDeviceExp(hVertex, pDevice);
}
ze_result_t zeDeviceGetFabricVertexExp (ze_device_handle_t hDevice, ze_fabric_vertex_handle_t* pVertex) {
    return Cal::Client::Icd::LevelZero::zeDeviceGetFabricVertexExp(hDevice, pVertex);
}
ze_result_t zeFabricEdgeGetExp (ze_fabric_vertex_handle_t hVertexA, ze_fabric_vertex_handle_t hVertexB, uint32_t* pCount, ze_fabric_edge_handle_t* phEdges) {
    return Cal::Client::Icd::LevelZero::zeFabricEdgeGetExp(hVertexA, hVertexB, pCount, phEdges);
}
ze_result_t zeFabricEdgeGetVerticesExp (ze_fabric_edge_handle_t hEdge, ze_fabric_vertex_handle_t* phVertexA, ze_fabric_vertex_handle_t* phVertexB) {
    return Cal::Client::Icd::LevelZero::zeFabricEdgeGetVerticesExp(hEdge, phVertexA, phVertexB);
}
ze_result_t zeFabricEdgeGetPropertiesExp (ze_fabric_edge_handle_t hEdge, ze_fabric_edge_exp_properties_t* pEdgeProperties) {
    return Cal::Client::Icd::LevelZero::zeFabricEdgeGetPropertiesExp(hEdge, pEdgeProperties);
}
ze_result_t zeFenceCreate (ze_command_queue_handle_t hCommandQueue, const ze_fence_desc_t* desc, ze_fence_handle_t* phFence) {
    return Cal::Client::Icd::LevelZero::zeFenceCreate(hCommandQueue, desc, phFence);
}
ze_result_t zeFenceDestroy (ze_fence_handle_t hFence) {
    return Cal::Client::Icd::LevelZero::zeFenceDestroy(hFence);
}
ze_result_t zeFenceHostSynchronize (ze_fence_handle_t hFence, uint64_t timeout) {
    return Cal::Client::Icd::LevelZero::zeFenceHostSynchronize(hFence, timeout);
}
ze_result_t zeFenceQueryStatus (ze_fence_handle_t hFence) {
    return Cal::Client::Icd::LevelZero::zeFenceQueryStatus(hFence);
}
ze_result_t zeFenceReset (ze_fence_handle_t hFence) {
    return Cal::Client::Icd::LevelZero::zeFenceReset(hFence);
}
ze_result_t zeKernelSetGlobalOffsetExp (ze_kernel_handle_t hKernel, uint32_t offsetX, uint32_t offsetY, uint32_t offsetZ) {
    return Cal::Client::Icd::LevelZero::zeKernelSetGlobalOffsetExp(hKernel, offsetX, offsetY, offsetZ);
}
ze_result_t zeImageGetProperties (ze_device_handle_t hDevice, const ze_image_desc_t* desc, ze_image_properties_t* pImageProperties) {
    return Cal::Client::Icd::LevelZero::zeImageGetProperties(hDevice, desc, pImageProperties);
}
ze_result_t zeImageCreate (ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_image_desc_t* desc, ze_image_handle_t* phImage) {
    return Cal::Client::Icd::LevelZero::zeImageCreate(hContext, hDevice, desc, phImage);
}
ze_result_t zeImageDestroy (ze_image_handle_t hImage) {
    return Cal::Client::Icd::LevelZero::zeImageDestroy(hImage);
}
ze_result_t zeKernelSchedulingHintExp (ze_kernel_handle_t hKernel, ze_scheduling_hint_exp_desc_t* pHint) {
    return Cal::Client::Icd::LevelZero::zeKernelSchedulingHintExp(hKernel, pHint);
}
ze_result_t zeModuleInspectLinkageExt (ze_linkage_inspection_ext_desc_t* pInspectDesc, uint32_t numModules, ze_module_handle_t* phModules, ze_module_build_log_handle_t* phLog) {
    return Cal::Client::Icd::LevelZero::zeModuleInspectLinkageExt(pInspectDesc, numModules, phModules, phLog);
}
ze_result_t zeMemAllocShared (ze_context_handle_t hContext, const ze_device_mem_alloc_desc_t* device_desc, const ze_host_mem_alloc_desc_t* host_desc, size_t size, size_t alignment, ze_device_handle_t hDevice, void** pptr) {
    return Cal::Client::Icd::LevelZero::zeMemAllocShared(hContext, device_desc, host_desc, size, alignment, hDevice, pptr);
}
ze_result_t zeMemAllocDevice (ze_context_handle_t hContext, const ze_device_mem_alloc_desc_t* device_desc, size_t size, size_t alignment, ze_device_handle_t hDevice, void** pptr) {
    return Cal::Client::Icd::LevelZero::zeMemAllocDevice(hContext, device_desc, size, alignment, hDevice, pptr);
}
ze_result_t zeMemAllocHost (ze_context_handle_t hContext, const ze_host_mem_alloc_desc_t* host_desc, size_t size, size_t alignment, void** pptr) {
    return Cal::Client::Icd::LevelZero::zeMemAllocHost(hContext, host_desc, size, alignment, pptr);
}
ze_result_t zeMemFree (ze_context_handle_t hContext, void* ptr) {
    return Cal::Client::Icd::LevelZero::zeMemFree(hContext, ptr);
}
ze_result_t zeMemGetAllocProperties (ze_context_handle_t hContext, const void* ptr, ze_memory_allocation_properties_t* pMemAllocProperties, ze_device_handle_t* phDevice) {
    return Cal::Client::Icd::LevelZero::zeMemGetAllocProperties(hContext, ptr, pMemAllocProperties, phDevice);
}
ze_result_t zeMemGetAddressRange (ze_context_handle_t hContext, const void* ptr, void** pBase, size_t* pSize) {
    return Cal::Client::Icd::LevelZero::zeMemGetAddressRange(hContext, ptr, pBase, pSize);
}
ze_result_t zeMemGetIpcHandle (ze_context_handle_t hContext, const void* ptr, ze_ipc_mem_handle_t* pIpcHandle) {
    return Cal::Client::Icd::LevelZero::zeMemGetIpcHandle(hContext, ptr, pIpcHandle);
}
ze_result_t zeMemOpenIpcHandle (ze_context_handle_t hContext, ze_device_handle_t hDevice, ze_ipc_mem_handle_t handle, ze_ipc_memory_flags_t flags, void** pptr) {
    return Cal::Client::Icd::LevelZero::zeMemOpenIpcHandle(hContext, hDevice, handle, flags, pptr);
}
ze_result_t zeMemCloseIpcHandle (ze_context_handle_t hContext, const void* ptr) {
    return Cal::Client::Icd::LevelZero::zeMemCloseIpcHandle(hContext, ptr);
}
ze_result_t zexMemGetIpcHandles (ze_context_handle_t hContext, const void* ptr, uint32_t* numIpcHandles, ze_ipc_mem_handle_t* pIpcHandles) {
    return Cal::Client::Icd::LevelZero::zexMemGetIpcHandles(hContext, ptr, numIpcHandles, pIpcHandles);
}
ze_result_t zexMemOpenIpcHandles (ze_context_handle_t hContext, ze_device_handle_t hDevice, uint32_t numIpcHandles, ze_ipc_mem_handle_t* pIpcHandles, ze_ipc_memory_flags_t flags, void** pptr) {
    return Cal::Client::Icd::LevelZero::zexMemOpenIpcHandles(hContext, hDevice, numIpcHandles, pIpcHandles, flags, pptr);
}
ze_result_t zeMemFreeExt (ze_context_handle_t hContext, const ze_memory_free_ext_desc_t* pMemFreeDesc, void* ptr) {
    return Cal::Client::Icd::LevelZero::zeMemFreeExt(hContext, pMemFreeDesc, ptr);
}
ze_result_t zeModuleCreate (ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_module_desc_t* desc, ze_module_handle_t* phModule, ze_module_build_log_handle_t* phBuildLog) {
    return Cal::Client::Icd::LevelZero::zeModuleCreate(hContext, hDevice, desc, phModule, phBuildLog);
}
ze_result_t zeModuleDestroy (ze_module_handle_t hModule) {
    return Cal::Client::Icd::LevelZero::zeModuleDestroy(hModule);
}
ze_result_t zeModuleDynamicLink (uint32_t numModules, ze_module_handle_t* phModules, ze_module_build_log_handle_t* phLinkLog) {
    return Cal::Client::Icd::LevelZero::zeModuleDynamicLink(numModules, phModules, phLinkLog);
}
ze_result_t zeModuleBuildLogDestroy (ze_module_build_log_handle_t hModuleBuildLog) {
    return Cal::Client::Icd::LevelZero::zeModuleBuildLogDestroy(hModuleBuildLog);
}
ze_result_t zeModuleBuildLogGetString (ze_module_build_log_handle_t hModuleBuildLog, size_t* pSize, char* pBuildLog) {
    return Cal::Client::Icd::LevelZero::zeModuleBuildLogGetString(hModuleBuildLog, pSize, pBuildLog);
}
ze_result_t zeModuleGetNativeBinary (ze_module_handle_t hModule, size_t* pSize, uint8_t* pModuleNativeBinary) {
    return Cal::Client::Icd::LevelZero::zeModuleGetNativeBinary(hModule, pSize, pModuleNativeBinary);
}
ze_result_t zeModuleGetGlobalPointer (ze_module_handle_t hModule, const char* pGlobalName, size_t* pSize, void** pptr) {
    return Cal::Client::Icd::LevelZero::zeModuleGetGlobalPointer(hModule, pGlobalName, pSize, pptr);
}
ze_result_t zeModuleGetKernelNames (ze_module_handle_t hModule, uint32_t* pCount, const char** pNames) {
    return Cal::Client::Icd::LevelZero::zeModuleGetKernelNames(hModule, pCount, pNames);
}
ze_result_t zeModuleGetProperties (ze_module_handle_t hModule, ze_module_properties_t* pModuleProperties) {
    return Cal::Client::Icd::LevelZero::zeModuleGetProperties(hModule, pModuleProperties);
}
ze_result_t zeKernelCreate (ze_module_handle_t hModule, const ze_kernel_desc_t* desc, ze_kernel_handle_t* phKernel) {
    return Cal::Client::Icd::LevelZero::zeKernelCreate(hModule, desc, phKernel);
}
ze_result_t zeKernelDestroy (ze_kernel_handle_t hKernel) {
    return Cal::Client::Icd::LevelZero::zeKernelDestroy(hKernel);
}
ze_result_t zeModuleGetFunctionPointer (ze_module_handle_t hModule, const char* pFunctionName, void** pfnFunction) {
    return Cal::Client::Icd::LevelZero::zeModuleGetFunctionPointer(hModule, pFunctionName, pfnFunction);
}
ze_result_t zeKernelSetGroupSize (ze_kernel_handle_t hKernel, uint32_t groupSizeX, uint32_t groupSizeY, uint32_t groupSizeZ) {
    return Cal::Client::Icd::LevelZero::zeKernelSetGroupSize(hKernel, groupSizeX, groupSizeY, groupSizeZ);
}
ze_result_t zeKernelSuggestGroupSize (ze_kernel_handle_t hKernel, uint32_t globalSizeX, uint32_t globalSizeY, uint32_t globalSizeZ, uint32_t* groupSizeX, uint32_t* groupSizeY, uint32_t* groupSizeZ) {
    return Cal::Client::Icd::LevelZero::zeKernelSuggestGroupSize(hKernel, globalSizeX, globalSizeY, globalSizeZ, groupSizeX, groupSizeY, groupSizeZ);
}
ze_result_t zeKernelSuggestMaxCooperativeGroupCount (ze_kernel_handle_t hKernel, uint32_t* totalGroupCount) {
    return Cal::Client::Icd::LevelZero::zeKernelSuggestMaxCooperativeGroupCount(hKernel, totalGroupCount);
}
ze_result_t zeKernelSetArgumentValue (ze_kernel_handle_t hKernel, uint32_t argIndex, size_t argSize, const void* pArgValue) {
    return Cal::Client::Icd::LevelZero::zeKernelSetArgumentValue(hKernel, argIndex, argSize, pArgValue);
}
ze_result_t zeKernelSetIndirectAccess (ze_kernel_handle_t hKernel, ze_kernel_indirect_access_flags_t flags) {
    return Cal::Client::Icd::LevelZero::zeKernelSetIndirectAccess(hKernel, flags);
}
ze_result_t zeKernelGetIndirectAccess (ze_kernel_handle_t hKernel, ze_kernel_indirect_access_flags_t* pFlags) {
    return Cal::Client::Icd::LevelZero::zeKernelGetIndirectAccess(hKernel, pFlags);
}
ze_result_t zeKernelSetCacheConfig (ze_kernel_handle_t hKernel, ze_cache_config_flags_t flags) {
    return Cal::Client::Icd::LevelZero::zeKernelSetCacheConfig(hKernel, flags);
}
ze_result_t zeKernelGetProperties (ze_kernel_handle_t hKernel, ze_kernel_properties_t* pKernelProperties) {
    return Cal::Client::Icd::LevelZero::zeKernelGetProperties(hKernel, pKernelProperties);
}
ze_result_t zeKernelGetName (ze_kernel_handle_t hKernel, size_t* pSize, char* pName) {
    return Cal::Client::Icd::LevelZero::zeKernelGetName(hKernel, pSize, pName);
}
ze_result_t zeCommandListAppendLaunchKernel (ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchFuncArgs, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    return Cal::Client::Icd::LevelZero::zeCommandListAppendLaunchKernel(hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents);
}
ze_result_t zeCommandListAppendLaunchCooperativeKernel (ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchFuncArgs, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    return Cal::Client::Icd::LevelZero::zeCommandListAppendLaunchCooperativeKernel(hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents);
}
ze_result_t zeCommandListAppendLaunchKernelIndirect (ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchArgumentsBuffer, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    return Cal::Client::Icd::LevelZero::zeCommandListAppendLaunchKernelIndirect(hCommandList, hKernel, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents);
}
ze_result_t zeCommandListAppendLaunchMultipleKernelsIndirect (ze_command_list_handle_t hCommandList, uint32_t numKernels, ze_kernel_handle_t* phKernels, const uint32_t* pCountBuffer, const ze_group_count_t* pLaunchArgumentsBuffer, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    return Cal::Client::Icd::LevelZero::zeCommandListAppendLaunchMultipleKernelsIndirect(hCommandList, numKernels, phKernels, pCountBuffer, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents);
}
ze_result_t zeCommandListHostSynchronize (ze_command_list_handle_t hCommandList, uint64_t timeout) {
    return Cal::Client::Icd::LevelZero::zeCommandListHostSynchronize(hCommandList, timeout);
}
ze_result_t zeDevicePciGetPropertiesExt (ze_device_handle_t hDevice, ze_pci_ext_properties_t* pPciProperties) {
    return Cal::Client::Icd::LevelZero::zeDevicePciGetPropertiesExt(hDevice, pPciProperties);
}
ze_result_t zeContextMakeMemoryResident (ze_context_handle_t hContext, ze_device_handle_t hDevice, void* ptr, size_t size) {
    return Cal::Client::Icd::LevelZero::zeContextMakeMemoryResident(hContext, hDevice, ptr, size);
}
ze_result_t zeContextEvictMemory (ze_context_handle_t hContext, ze_device_handle_t hDevice, void* ptr, size_t size) {
    return Cal::Client::Icd::LevelZero::zeContextEvictMemory(hContext, hDevice, ptr, size);
}
ze_result_t zeVirtualMemReserve (ze_context_handle_t hContext, const void* pStart, size_t size, void** pptr) {
    return Cal::Client::Icd::LevelZero::zeVirtualMemReserve(hContext, pStart, size, pptr);
}
ze_result_t zeVirtualMemFree (ze_context_handle_t hContext, const void* ptr, size_t size) {
    return Cal::Client::Icd::LevelZero::zeVirtualMemFree(hContext, ptr, size);
}
ze_result_t zeVirtualMemQueryPageSize (ze_context_handle_t hContext, ze_device_handle_t hDevice, size_t size, size_t* pagesize) {
    return Cal::Client::Icd::LevelZero::zeVirtualMemQueryPageSize(hContext, hDevice, size, pagesize);
}
ze_result_t zePhysicalMemCreate (ze_context_handle_t hContext, ze_device_handle_t hDevice, ze_physical_mem_desc_t* desc, ze_physical_mem_handle_t* phPhysicalMemory) {
    return Cal::Client::Icd::LevelZero::zePhysicalMemCreate(hContext, hDevice, desc, phPhysicalMemory);
}
ze_result_t zePhysicalMemDestroy (ze_context_handle_t hContext, ze_physical_mem_handle_t hPhysicalMemory) {
    return Cal::Client::Icd::LevelZero::zePhysicalMemDestroy(hContext, hPhysicalMemory);
}
ze_result_t zeVirtualMemMap (ze_context_handle_t hContext, const void* ptr, size_t size, ze_physical_mem_handle_t hPhysicalMemory, size_t offset, ze_memory_access_attribute_t access) {
    return Cal::Client::Icd::LevelZero::zeVirtualMemMap(hContext, ptr, size, hPhysicalMemory, offset, access);
}
ze_result_t zeVirtualMemUnmap (ze_context_handle_t hContext, const void* ptr, size_t size) {
    return Cal::Client::Icd::LevelZero::zeVirtualMemUnmap(hContext, ptr, size);
}
ze_result_t zeVirtualMemSetAccessAttribute (ze_context_handle_t hContext, const void* ptr, size_t size, ze_memory_access_attribute_t access) {
    return Cal::Client::Icd::LevelZero::zeVirtualMemSetAccessAttribute(hContext, ptr, size, access);
}
ze_result_t zeVirtualMemGetAccessAttribute (ze_context_handle_t hContext, const void* ptr, size_t size, ze_memory_access_attribute_t* access, size_t* outSize) {
    return Cal::Client::Icd::LevelZero::zeVirtualMemGetAccessAttribute(hContext, ptr, size, access, outSize);
}
ze_result_t zexDriverImportExternalPointer (ze_driver_handle_t hDriver, void* ptr, size_t size) {
    return Cal::Client::Icd::LevelZero::zexDriverImportExternalPointer(hDriver, ptr, size);
}
ze_result_t zexDriverReleaseImportedPointer (ze_driver_handle_t hDriver, void* ptr) {
    return Cal::Client::Icd::LevelZero::zexDriverReleaseImportedPointer(hDriver, ptr);
}
ze_result_t zexDriverGetHostPointerBaseAddress (ze_driver_handle_t hDriver, void* ptr, void** baseAddress) {
    return Cal::Client::Icd::LevelZero::zexDriverGetHostPointerBaseAddress(hDriver, ptr, baseAddress);
}
} // extern "C"


// #### Generated code -- end ####
