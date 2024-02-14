/*
 * Copyright (C) 2022-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

// #### Generated code -- begin ####

#include "generated_rpc_messages_level_zero.h"
#include "shared/utils.h"

namespace Cal {
namespace Rpc {
namespace LevelZero {

using namespace Cal::Utils;

ZetMetricGroupGetRpcM::Captures::DynamicTraits ZetMetricGroupGetRpcM::Captures::DynamicTraits::calculate(zet_device_handle_t hDevice, uint32_t* pCount, zet_metric_group_handle_t* phMetricGroups) {
    DynamicTraits ret = {};
    ret.phMetricGroups.count = phMetricGroups ? ((pCount ? *pCount : 0)) : 0;
    ret.phMetricGroups.size = ret.phMetricGroups.count * sizeof(zet_metric_group_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phMetricGroups.offset + ret.phMetricGroups.size);


    return ret;
}

size_t ZetMetricGroupGetRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phMetricGroups) + Cal::Utils::alignUpPow2<8>(this->countPhMetricGroups * sizeof(zet_metric_group_handle_t));
     return size;
}

size_t ZetMetricGroupGetRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhMetricGroups * sizeof(zet_metric_group_handle_t));
     return size;
}

ZetMetricGroupGetPropertiesRpcM::Captures::DynamicTraits ZetMetricGroupGetPropertiesRpcM::Captures::DynamicTraits::calculate(zet_metric_group_handle_t hMetricGroup, zet_metric_group_properties_t* pProperties) {
    DynamicTraits ret = {};

    ret.dynamicStructMembersOffset = ret.totalDynamicSize;
    if (pProperties) {
        ret.pPropertiesNestedTraits.offset = ret.totalDynamicSize;
        ret.pPropertiesNestedTraits.count = pProperties ? (1) : 0;
        ret.pPropertiesNestedTraits.size = ret.pPropertiesNestedTraits.count * sizeof(DynamicStructTraits<zet_metric_group_properties_t>);
        ret.totalDynamicSize += alignUpPow2<8>(ret.pPropertiesNestedTraits.size);

        for (uint32_t i = 0; i < ret.pPropertiesNestedTraits.count; ++i) {
            const auto& pPropertiesPNext = pProperties[i].pNext;
            if(!pPropertiesPNext){
                continue;
            }

            const auto pPropertiesPNextCount = static_cast<uint32_t>(countOpaqueList(static_cast<const ze_base_desc_t*>(pProperties[i].pNext)));
            if(!pPropertiesPNextCount){
                continue;
            }

            ret.totalDynamicSize += alignUpPow2<8>(pPropertiesPNextCount * sizeof(NestedPNextTraits));

            auto pPropertiesPNextListElement = static_cast<const ze_base_desc_t*>(pProperties[i].pNext);
            for(uint32_t j = 0; j < pPropertiesPNextCount; ++j){
                ret.totalDynamicSize += alignUpPow2<8>(getUnderlyingSize(pPropertiesPNextListElement));
                pPropertiesPNextListElement = getNext(pPropertiesPNextListElement);
            }

        }
    }

    return ret;
}

size_t ZetMetricGroupGetPropertiesRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, dynMem) + dynMemSize;
     return size;
}

size_t ZetMetricGroupGetPropertiesRpcM::Captures::getCaptureDynMemSize() const {
     return dynMemSize;
}

ZetMetricGroupGetExportDataExpRpcM::Captures::DynamicTraits ZetMetricGroupGetExportDataExpRpcM::Captures::DynamicTraits::calculate(zet_metric_group_handle_t hMetricGroup, const uint8_t * pRawData, size_t rawDataSize, size_t* pExportDataSize, uint8_t* pExportData) {
    DynamicTraits ret = {};
    ret.pRawData.count = pRawData ? (rawDataSize) : 0;
    ret.pRawData.size = ret.pRawData.count * sizeof(uint8_t);

    ret.pExportData.offset = alignUpPow2<8>(ret.pRawData.offset + ret.pRawData.size);
    ret.pExportData.count = pExportData ? ((pExportDataSize ? *pExportDataSize : 0)) : 0;
    ret.pExportData.size = ret.pExportData.count * sizeof(uint8_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.pExportData.offset + ret.pExportData.size);


    return ret;
}

size_t ZetMetricGroupGetExportDataExpRpcM::Captures::getCaptureTotalSize() const {
     const auto lastMemberOffset = offsetPExportData;
     const auto lastMemberArraySize = this->countPExportData * sizeof(uint8_t);

     auto size = offsetof(Captures, dynMem) + Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

size_t ZetMetricGroupGetExportDataExpRpcM::Captures::getCaptureDynMemSize() const {
     const auto lastMemberOffset = offsetPExportData;
     const auto lastMemberArraySize = this->countPExportData * sizeof(uint8_t);

     auto size = Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

ZetMetricGroupCalculateMetricValuesRpcM::Captures::DynamicTraits ZetMetricGroupCalculateMetricValuesRpcM::Captures::DynamicTraits::calculate(zet_metric_group_handle_t hMetricGroup, zet_metric_group_calculation_type_t type, size_t rawDataSize, const uint8_t * pRawData, uint32_t* pMetricValueCount, zet_typed_value_t* pMetricValues) {
    DynamicTraits ret = {};
    ret.pRawData.count = pRawData ? (rawDataSize) : 0;
    ret.pRawData.size = ret.pRawData.count * sizeof(uint8_t);

    ret.pMetricValues.offset = alignUpPow2<8>(ret.pRawData.offset + ret.pRawData.size);
    ret.pMetricValues.count = pMetricValues ? ((pMetricValueCount ? *pMetricValueCount : 0)) : 0;
    ret.pMetricValues.size = ret.pMetricValues.count * sizeof(zet_typed_value_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.pMetricValues.offset + ret.pMetricValues.size);


    return ret;
}

size_t ZetMetricGroupCalculateMetricValuesRpcM::Captures::getCaptureTotalSize() const {
     const auto lastMemberOffset = offsetPMetricValues;
     const auto lastMemberArraySize = this->countPMetricValues * sizeof(zet_typed_value_t);

     auto size = offsetof(Captures, dynMem) + Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

size_t ZetMetricGroupCalculateMetricValuesRpcM::Captures::getCaptureDynMemSize() const {
     const auto lastMemberOffset = offsetPMetricValues;
     const auto lastMemberArraySize = this->countPMetricValues * sizeof(zet_typed_value_t);

     auto size = Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

ZetMetricGroupCalculateMultipleMetricValuesExpRpcM::Captures::DynamicTraits ZetMetricGroupCalculateMultipleMetricValuesExpRpcM::Captures::DynamicTraits::calculate(zet_metric_group_handle_t hMetricGroup, zet_metric_group_calculation_type_t type, size_t rawDataSize, const uint8_t * pRawData, uint32_t* pSetCount, uint32_t* pTotalMetricValueCount, uint32_t* pMetricCounts, zet_typed_value_t* pMetricValues) {
    DynamicTraits ret = {};
    ret.pRawData.count = pRawData ? (rawDataSize) : 0;
    ret.pRawData.size = ret.pRawData.count * sizeof(uint8_t);

    ret.pMetricCounts.offset = alignUpPow2<8>(ret.pRawData.offset + ret.pRawData.size);
    ret.pMetricCounts.count = pMetricCounts ? ((pSetCount ? *pSetCount : 0)) : 0;
    ret.pMetricCounts.size = ret.pMetricCounts.count * sizeof(uint32_t);

    ret.pMetricValues.offset = alignUpPow2<8>(ret.pMetricCounts.offset + ret.pMetricCounts.size);
    ret.pMetricValues.count = pMetricValues ? ((pTotalMetricValueCount ? *pTotalMetricValueCount : 0)) : 0;
    ret.pMetricValues.size = ret.pMetricValues.count * sizeof(zet_typed_value_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.pMetricValues.offset + ret.pMetricValues.size);


    return ret;
}

size_t ZetMetricGroupCalculateMultipleMetricValuesExpRpcM::Captures::getCaptureTotalSize() const {
     const auto lastMemberOffset = offsetPMetricValues;
     const auto lastMemberArraySize = this->countPMetricValues * sizeof(zet_typed_value_t);

     auto size = offsetof(Captures, dynMem) + Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

size_t ZetMetricGroupCalculateMultipleMetricValuesExpRpcM::Captures::getCaptureDynMemSize() const {
     const auto lastMemberOffset = offsetPMetricValues;
     const auto lastMemberArraySize = this->countPMetricValues * sizeof(zet_typed_value_t);

     auto size = Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

ZetMetricGetRpcM::Captures::DynamicTraits ZetMetricGetRpcM::Captures::DynamicTraits::calculate(zet_metric_group_handle_t hMetricGroup, uint32_t* pCount, zet_metric_handle_t* phMetrics) {
    DynamicTraits ret = {};
    ret.phMetrics.count = phMetrics ? ((pCount ? *pCount : 0)) : 0;
    ret.phMetrics.size = ret.phMetrics.count * sizeof(zet_metric_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phMetrics.offset + ret.phMetrics.size);


    return ret;
}

size_t ZetMetricGetRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phMetrics) + Cal::Utils::alignUpPow2<8>(this->countPhMetrics * sizeof(zet_metric_handle_t));
     return size;
}

size_t ZetMetricGetRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhMetrics * sizeof(zet_metric_handle_t));
     return size;
}

ZetContextActivateMetricGroupsRpcM::Captures::DynamicTraits ZetContextActivateMetricGroupsRpcM::Captures::DynamicTraits::calculate(zet_context_handle_t hContext, zet_device_handle_t hDevice, uint32_t count, zet_metric_group_handle_t* phMetricGroups) {
    DynamicTraits ret = {};
    ret.phMetricGroups.count = phMetricGroups ? (count) : 0;
    ret.phMetricGroups.size = ret.phMetricGroups.count * sizeof(zet_metric_group_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phMetricGroups.offset + ret.phMetricGroups.size);


    return ret;
}

size_t ZetContextActivateMetricGroupsRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phMetricGroups) + Cal::Utils::alignUpPow2<8>(this->countPhMetricGroups * sizeof(zet_metric_group_handle_t));
     return size;
}

size_t ZetContextActivateMetricGroupsRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhMetricGroups * sizeof(zet_metric_group_handle_t));
     return size;
}

ZetMetricQueryGetDataRpcM::Captures::DynamicTraits ZetMetricQueryGetDataRpcM::Captures::DynamicTraits::calculate(zet_metric_query_handle_t hMetricQuery, size_t* pRawDataSize, uint8_t* pRawData) {
    DynamicTraits ret = {};
    ret.pRawData.count = pRawData ? ((pRawDataSize ? *pRawDataSize : 0)) : 0;
    ret.pRawData.size = ret.pRawData.count * sizeof(uint8_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.pRawData.offset + ret.pRawData.size);


    return ret;
}

size_t ZetMetricQueryGetDataRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, pRawData) + Cal::Utils::alignUpPow2<8>(this->countPRawData * sizeof(uint8_t));
     return size;
}

size_t ZetMetricQueryGetDataRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPRawData * sizeof(uint8_t));
     return size;
}

ZetCommandListAppendMetricQueryEndRpcM::Captures::DynamicTraits ZetCommandListAppendMetricQueryEndRpcM::Captures::DynamicTraits::calculate(zet_command_list_handle_t hCommandList, zet_metric_query_handle_t hMetricQuery, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZetCommandListAppendMetricQueryEndRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZetCommandListAppendMetricQueryEndRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZetDeviceGetDebugPropertiesRpcM::Captures::DynamicTraits ZetDeviceGetDebugPropertiesRpcM::Captures::DynamicTraits::calculate(ze_device_handle_t hDevice, zet_device_debug_properties_t* pDebugProperties) {
    DynamicTraits ret = {};

    ret.dynamicStructMembersOffset = ret.totalDynamicSize;
    if (pDebugProperties) {
        ret.pDebugPropertiesNestedTraits.offset = ret.totalDynamicSize;
        ret.pDebugPropertiesNestedTraits.count = pDebugProperties ? (1) : 0;
        ret.pDebugPropertiesNestedTraits.size = ret.pDebugPropertiesNestedTraits.count * sizeof(DynamicStructTraits<zet_device_debug_properties_t>);
        ret.totalDynamicSize += alignUpPow2<8>(ret.pDebugPropertiesNestedTraits.size);

        for (uint32_t i = 0; i < ret.pDebugPropertiesNestedTraits.count; ++i) {
            const auto& pDebugPropertiesPNext = pDebugProperties[i].pNext;
            if(!pDebugPropertiesPNext){
                continue;
            }

            const auto pDebugPropertiesPNextCount = static_cast<uint32_t>(countOpaqueList(static_cast<const ze_base_desc_t*>(pDebugProperties[i].pNext)));
            if(!pDebugPropertiesPNextCount){
                continue;
            }

            ret.totalDynamicSize += alignUpPow2<8>(pDebugPropertiesPNextCount * sizeof(NestedPNextTraits));

            auto pDebugPropertiesPNextListElement = static_cast<const ze_base_desc_t*>(pDebugProperties[i].pNext);
            for(uint32_t j = 0; j < pDebugPropertiesPNextCount; ++j){
                ret.totalDynamicSize += alignUpPow2<8>(getUnderlyingSize(pDebugPropertiesPNextListElement));
                pDebugPropertiesPNextListElement = getNext(pDebugPropertiesPNextListElement);
            }

        }
    }

    return ret;
}

size_t ZetDeviceGetDebugPropertiesRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, dynMem) + dynMemSize;
     return size;
}

size_t ZetDeviceGetDebugPropertiesRpcM::Captures::getCaptureDynMemSize() const {
     return dynMemSize;
}

ZesDeviceEnumPowerDomainsRpcM::Captures::DynamicTraits ZesDeviceEnumPowerDomainsRpcM::Captures::DynamicTraits::calculate(zes_device_handle_t hDevice, uint32_t* pCount, zes_pwr_handle_t* phPower) {
    DynamicTraits ret = {};
    ret.phPower.count = phPower ? ((pCount ? *pCount : 0)) : 0;
    ret.phPower.size = ret.phPower.count * sizeof(zes_pwr_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phPower.offset + ret.phPower.size);


    return ret;
}

size_t ZesDeviceEnumPowerDomainsRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phPower) + Cal::Utils::alignUpPow2<8>(this->countPhPower * sizeof(zes_pwr_handle_t));
     return size;
}

size_t ZesDeviceEnumPowerDomainsRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhPower * sizeof(zes_pwr_handle_t));
     return size;
}

ZesPowerGetPropertiesRpcM::Captures::DynamicTraits ZesPowerGetPropertiesRpcM::Captures::DynamicTraits::calculate(zes_pwr_handle_t hPower, zes_power_properties_t* pProperties) {
    DynamicTraits ret = {};

    ret.dynamicStructMembersOffset = ret.totalDynamicSize;
    if (pProperties) {
        ret.pPropertiesNestedTraits.offset = ret.totalDynamicSize;
        ret.pPropertiesNestedTraits.count = pProperties ? (1) : 0;
        ret.pPropertiesNestedTraits.size = ret.pPropertiesNestedTraits.count * sizeof(DynamicStructTraits<zes_power_properties_t>);
        ret.totalDynamicSize += alignUpPow2<8>(ret.pPropertiesNestedTraits.size);

        for (uint32_t i = 0; i < ret.pPropertiesNestedTraits.count; ++i) {
            const auto& pPropertiesPNext = pProperties[i].pNext;
            if(!pPropertiesPNext){
                continue;
            }

            const auto pPropertiesPNextCount = static_cast<uint32_t>(countOpaqueList(static_cast<const ze_base_desc_t*>(pProperties[i].pNext)));
            if(!pPropertiesPNextCount){
                continue;
            }

            ret.totalDynamicSize += alignUpPow2<8>(pPropertiesPNextCount * sizeof(NestedPNextTraits));

            auto pPropertiesPNextListElement = static_cast<const ze_base_desc_t*>(pProperties[i].pNext);
            for(uint32_t j = 0; j < pPropertiesPNextCount; ++j){
                ret.totalDynamicSize += alignUpPow2<8>(getUnderlyingSize(pPropertiesPNextListElement));

                const auto extensionType = static_cast<int>(getExtensionType(pPropertiesPNextListElement));
                if (extensionType == ZES_STRUCTURE_TYPE_POWER_EXT_PROPERTIES) {
                    auto& extension = *reinterpret_cast<const zes_power_ext_properties_t*>(pPropertiesPNextListElement);
                    ret.totalDynamicSize += alignUpPow2<8>(sizeof(DynamicStructTraits<zes_power_ext_properties_t>));

                    do {
                        const auto& pPropertiesPNextDefaultLimit = extension.defaultLimit;
                        if(!pPropertiesPNextDefaultLimit){
                            continue;
                        }

                        const auto pPropertiesPNextDefaultLimitCount = static_cast<uint32_t>(1);
                        if(!pPropertiesPNextDefaultLimitCount){
                            continue;
                        }

                        ret.totalDynamicSize += alignUpPow2<8>(pPropertiesPNextDefaultLimitCount * sizeof(zes_power_limit_ext_desc_t));
                    } while (0);
                }
                pPropertiesPNextListElement = getNext(pPropertiesPNextListElement);
            }

        }
    }

    return ret;
}

size_t ZesPowerGetPropertiesRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, dynMem) + dynMemSize;
     return size;
}

size_t ZesPowerGetPropertiesRpcM::Captures::getCaptureDynMemSize() const {
     return dynMemSize;
}

ZesPowerGetLimitsExtRpcM::Captures::DynamicTraits ZesPowerGetLimitsExtRpcM::Captures::DynamicTraits::calculate(zes_pwr_handle_t hPower, uint32_t* pCount, zes_power_limit_ext_desc_t* pSustained) {
    DynamicTraits ret = {};
    ret.pSustained.count = pSustained ? ((pCount ? *pCount : 0)) : 0;
    ret.pSustained.size = ret.pSustained.count * sizeof(zes_power_limit_ext_desc_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.pSustained.offset + ret.pSustained.size);


    return ret;
}

size_t ZesPowerGetLimitsExtRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, pSustained) + Cal::Utils::alignUpPow2<8>(this->countPSustained * sizeof(zes_power_limit_ext_desc_t));
     return size;
}

size_t ZesPowerGetLimitsExtRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPSustained * sizeof(zes_power_limit_ext_desc_t));
     return size;
}

ZesPowerSetLimitsExtRpcM::Captures::DynamicTraits ZesPowerSetLimitsExtRpcM::Captures::DynamicTraits::calculate(zes_pwr_handle_t hPower, uint32_t* pCount, zes_power_limit_ext_desc_t* pSustained) {
    DynamicTraits ret = {};
    ret.pSustained.count = pSustained ? ((pCount ? *pCount : 0)) : 0;
    ret.pSustained.size = ret.pSustained.count * sizeof(zes_power_limit_ext_desc_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.pSustained.offset + ret.pSustained.size);


    return ret;
}

size_t ZesPowerSetLimitsExtRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, pSustained) + Cal::Utils::alignUpPow2<8>(this->countPSustained * sizeof(zes_power_limit_ext_desc_t));
     return size;
}

size_t ZesPowerSetLimitsExtRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPSustained * sizeof(zes_power_limit_ext_desc_t));
     return size;
}

ZesDriverEventListenRpcM::Captures::DynamicTraits ZesDriverEventListenRpcM::Captures::DynamicTraits::calculate(ze_driver_handle_t hDriver, uint32_t timeout, uint32_t count, ze_device_handle_t* phDevices, uint32_t* pNumDeviceEvents, zes_event_type_flags_t* pEvents) {
    DynamicTraits ret = {};
    ret.phDevices.count = phDevices ? (count) : 0;
    ret.phDevices.size = ret.phDevices.count * sizeof(zes_device_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phDevices.offset + ret.phDevices.size);


    return ret;
}

size_t ZesDriverEventListenRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phDevices) + Cal::Utils::alignUpPow2<8>(this->countPhDevices * sizeof(zes_device_handle_t));
     return size;
}

size_t ZesDriverEventListenRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhDevices * sizeof(zes_device_handle_t));
     return size;
}

ZesDriverEventListenExRpcM::Captures::DynamicTraits ZesDriverEventListenExRpcM::Captures::DynamicTraits::calculate(ze_driver_handle_t hDriver, uint64_t timeout, uint32_t count, zes_device_handle_t* phDevices, uint32_t* pNumDeviceEvents, zes_event_type_flags_t* pEvents) {
    DynamicTraits ret = {};
    ret.phDevices.count = phDevices ? (count) : 0;
    ret.phDevices.size = ret.phDevices.count * sizeof(ze_device_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phDevices.offset + ret.phDevices.size);


    return ret;
}

size_t ZesDriverEventListenExRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phDevices) + Cal::Utils::alignUpPow2<8>(this->countPhDevices * sizeof(ze_device_handle_t));
     return size;
}

size_t ZesDriverEventListenExRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhDevices * sizeof(ze_device_handle_t));
     return size;
}

ZesDeviceEnumTemperatureSensorsRpcM::Captures::DynamicTraits ZesDeviceEnumTemperatureSensorsRpcM::Captures::DynamicTraits::calculate(zes_device_handle_t hDevice, uint32_t* pCount, zes_temp_handle_t* phTemperature) {
    DynamicTraits ret = {};
    ret.phTemperature.count = phTemperature ? ((pCount ? *pCount : 0)) : 0;
    ret.phTemperature.size = ret.phTemperature.count * sizeof(zes_temp_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phTemperature.offset + ret.phTemperature.size);


    return ret;
}

size_t ZesDeviceEnumTemperatureSensorsRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phTemperature) + Cal::Utils::alignUpPow2<8>(this->countPhTemperature * sizeof(zes_temp_handle_t));
     return size;
}

size_t ZesDeviceEnumTemperatureSensorsRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhTemperature * sizeof(zes_temp_handle_t));
     return size;
}

ZesDeviceEnumRasErrorSetsRpcM::Captures::DynamicTraits ZesDeviceEnumRasErrorSetsRpcM::Captures::DynamicTraits::calculate(zes_device_handle_t hDevice, uint32_t* pCount, zes_ras_handle_t* phRas) {
    DynamicTraits ret = {};
    ret.phRas.count = phRas ? ((pCount ? *pCount : 0)) : 0;
    ret.phRas.size = ret.phRas.count * sizeof(zes_ras_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phRas.offset + ret.phRas.size);


    return ret;
}

size_t ZesDeviceEnumRasErrorSetsRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phRas) + Cal::Utils::alignUpPow2<8>(this->countPhRas * sizeof(zes_ras_handle_t));
     return size;
}

size_t ZesDeviceEnumRasErrorSetsRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhRas * sizeof(zes_ras_handle_t));
     return size;
}

ZesDeviceEnumFrequencyDomainsRpcM::Captures::DynamicTraits ZesDeviceEnumFrequencyDomainsRpcM::Captures::DynamicTraits::calculate(zes_device_handle_t hDevice, uint32_t* pCount, zes_freq_handle_t* phFrequency) {
    DynamicTraits ret = {};
    ret.phFrequency.count = phFrequency ? ((pCount ? *pCount : 0)) : 0;
    ret.phFrequency.size = ret.phFrequency.count * sizeof(zes_freq_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phFrequency.offset + ret.phFrequency.size);


    return ret;
}

size_t ZesDeviceEnumFrequencyDomainsRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phFrequency) + Cal::Utils::alignUpPow2<8>(this->countPhFrequency * sizeof(zes_freq_handle_t));
     return size;
}

size_t ZesDeviceEnumFrequencyDomainsRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhFrequency * sizeof(zes_freq_handle_t));
     return size;
}

ZesFrequencyGetAvailableClocksRpcM::Captures::DynamicTraits ZesFrequencyGetAvailableClocksRpcM::Captures::DynamicTraits::calculate(zes_freq_handle_t hFrequency, uint32_t* pCount, double* phFrequency) {
    DynamicTraits ret = {};
    ret.phFrequency.count = phFrequency ? ((pCount ? *pCount : 0)) : 0;
    ret.phFrequency.size = ret.phFrequency.count * sizeof(double);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phFrequency.offset + ret.phFrequency.size);


    return ret;
}

size_t ZesFrequencyGetAvailableClocksRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phFrequency) + Cal::Utils::alignUpPow2<8>(this->countPhFrequency * sizeof(double));
     return size;
}

size_t ZesFrequencyGetAvailableClocksRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhFrequency * sizeof(double));
     return size;
}

ZesDeviceEnumEngineGroupsRpcM::Captures::DynamicTraits ZesDeviceEnumEngineGroupsRpcM::Captures::DynamicTraits::calculate(zes_device_handle_t hDevice, uint32_t* pCount, zes_engine_handle_t* phEngine) {
    DynamicTraits ret = {};
    ret.phEngine.count = phEngine ? ((pCount ? *pCount : 0)) : 0;
    ret.phEngine.size = ret.phEngine.count * sizeof(zes_engine_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phEngine.offset + ret.phEngine.size);


    return ret;
}

size_t ZesDeviceEnumEngineGroupsRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phEngine) + Cal::Utils::alignUpPow2<8>(this->countPhEngine * sizeof(zes_engine_handle_t));
     return size;
}

size_t ZesDeviceEnumEngineGroupsRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhEngine * sizeof(zes_engine_handle_t));
     return size;
}

ZesDeviceEnumSchedulersRpcM::Captures::DynamicTraits ZesDeviceEnumSchedulersRpcM::Captures::DynamicTraits::calculate(zes_device_handle_t hDevice, uint32_t* pCount, zes_sched_handle_t* phScheduler) {
    DynamicTraits ret = {};
    ret.phScheduler.count = phScheduler ? ((pCount ? *pCount : 0)) : 0;
    ret.phScheduler.size = ret.phScheduler.count * sizeof(zes_sched_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phScheduler.offset + ret.phScheduler.size);


    return ret;
}

size_t ZesDeviceEnumSchedulersRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phScheduler) + Cal::Utils::alignUpPow2<8>(this->countPhScheduler * sizeof(zes_sched_handle_t));
     return size;
}

size_t ZesDeviceEnumSchedulersRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhScheduler * sizeof(zes_sched_handle_t));
     return size;
}

ZesDeviceProcessesGetStateRpcM::Captures::DynamicTraits ZesDeviceProcessesGetStateRpcM::Captures::DynamicTraits::calculate(zes_device_handle_t hDevice, uint32_t* pCount, zes_process_state_t* pProcesses) {
    DynamicTraits ret = {};
    ret.pProcesses.count = pProcesses ? ((pCount ? *pCount : 0)) : 0;
    ret.pProcesses.size = ret.pProcesses.count * sizeof(zes_process_state_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.pProcesses.offset + ret.pProcesses.size);


    return ret;
}

size_t ZesDeviceProcessesGetStateRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, pProcesses) + Cal::Utils::alignUpPow2<8>(this->countPProcesses * sizeof(zes_process_state_t));
     return size;
}

size_t ZesDeviceProcessesGetStateRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPProcesses * sizeof(zes_process_state_t));
     return size;
}

ZesDevicePciGetBarsRpcM::Captures::DynamicTraits ZesDevicePciGetBarsRpcM::Captures::DynamicTraits::calculate(zes_device_handle_t hDevice, uint32_t* pCount, zes_pci_bar_properties_t* pProperties) {
    DynamicTraits ret = {};
    ret.pProperties.count = pProperties ? ((pCount ? *pCount : 0)) : 0;
    ret.pProperties.size = ret.pProperties.count * sizeof(zes_pci_bar_properties_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.pProperties.offset + ret.pProperties.size);

    ret.dynamicStructMembersOffset = ret.totalDynamicSize;
    if (pProperties) {
        ret.pPropertiesNestedTraits.offset = ret.totalDynamicSize;
        ret.pPropertiesNestedTraits.count = pProperties ? ((pCount ? *pCount : 0)) : 0;
        ret.pPropertiesNestedTraits.size = ret.pPropertiesNestedTraits.count * sizeof(DynamicStructTraits<zes_pci_bar_properties_t>);
        ret.totalDynamicSize += alignUpPow2<8>(ret.pPropertiesNestedTraits.size);

        for (uint32_t i = 0; i < ret.pPropertiesNestedTraits.count; ++i) {
            const auto& pPropertiesPNext = pProperties[i].pNext;
            if(!pPropertiesPNext){
                continue;
            }

            const auto pPropertiesPNextCount = static_cast<uint32_t>(countOpaqueList(static_cast<const ze_base_desc_t*>(pProperties[i].pNext)));
            if(!pPropertiesPNextCount){
                continue;
            }

            ret.totalDynamicSize += alignUpPow2<8>(pPropertiesPNextCount * sizeof(NestedPNextTraits));

            auto pPropertiesPNextListElement = static_cast<const ze_base_desc_t*>(pProperties[i].pNext);
            for(uint32_t j = 0; j < pPropertiesPNextCount; ++j){
                ret.totalDynamicSize += alignUpPow2<8>(getUnderlyingSize(pPropertiesPNextListElement));
                pPropertiesPNextListElement = getNext(pPropertiesPNextListElement);
            }

        }
    }

    return ret;
}

size_t ZesDevicePciGetBarsRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, dynMem) + dynMemSize;
     return size;
}

size_t ZesDevicePciGetBarsRpcM::Captures::getCaptureDynMemSize() const {
     return dynMemSize;
}

ZesDeviceEnumMemoryModulesRpcM::Captures::DynamicTraits ZesDeviceEnumMemoryModulesRpcM::Captures::DynamicTraits::calculate(zes_device_handle_t hDevice, uint32_t* pCount, zes_mem_handle_t* phMemory) {
    DynamicTraits ret = {};
    ret.phMemory.count = phMemory ? ((pCount ? *pCount : 0)) : 0;
    ret.phMemory.size = ret.phMemory.count * sizeof(zes_mem_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phMemory.offset + ret.phMemory.size);


    return ret;
}

size_t ZesDeviceEnumMemoryModulesRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phMemory) + Cal::Utils::alignUpPow2<8>(this->countPhMemory * sizeof(zes_mem_handle_t));
     return size;
}

size_t ZesDeviceEnumMemoryModulesRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhMemory * sizeof(zes_mem_handle_t));
     return size;
}

ZesDeviceEnumPerformanceFactorDomainsRpcM::Captures::DynamicTraits ZesDeviceEnumPerformanceFactorDomainsRpcM::Captures::DynamicTraits::calculate(zes_device_handle_t hDevice, uint32_t* pCount, zes_perf_handle_t* phPerf) {
    DynamicTraits ret = {};
    ret.phPerf.count = phPerf ? ((pCount ? *pCount : 0)) : 0;
    ret.phPerf.size = ret.phPerf.count * sizeof(zes_perf_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phPerf.offset + ret.phPerf.size);


    return ret;
}

size_t ZesDeviceEnumPerformanceFactorDomainsRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phPerf) + Cal::Utils::alignUpPow2<8>(this->countPhPerf * sizeof(zes_perf_handle_t));
     return size;
}

size_t ZesDeviceEnumPerformanceFactorDomainsRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhPerf * sizeof(zes_perf_handle_t));
     return size;
}

ZesDeviceEnumStandbyDomainsRpcM::Captures::DynamicTraits ZesDeviceEnumStandbyDomainsRpcM::Captures::DynamicTraits::calculate(zes_device_handle_t hDevice, uint32_t* pCount, zes_standby_handle_t* phStandby) {
    DynamicTraits ret = {};
    ret.phStandby.count = phStandby ? ((pCount ? *pCount : 0)) : 0;
    ret.phStandby.size = ret.phStandby.count * sizeof(zes_standby_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phStandby.offset + ret.phStandby.size);


    return ret;
}

size_t ZesDeviceEnumStandbyDomainsRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phStandby) + Cal::Utils::alignUpPow2<8>(this->countPhStandby * sizeof(zes_standby_handle_t));
     return size;
}

size_t ZesDeviceEnumStandbyDomainsRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhStandby * sizeof(zes_standby_handle_t));
     return size;
}

ZeCommandListAppendMemoryRangesBarrierRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryRangesBarrierRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, uint32_t numRanges, const size_t* pRangeSizes, const void** pRanges, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.pRangeSizes.count = pRangeSizes ? (numRanges) : 0;
    ret.pRangeSizes.size = ret.pRangeSizes.count * sizeof(size_t);

    ret.pRanges.offset = alignUpPow2<8>(ret.pRangeSizes.offset + ret.pRangeSizes.size);
    ret.pRanges.count = pRanges ? (numRanges) : 0;
    ret.pRanges.size = ret.pRanges.count * sizeof(const void*);

    ret.phWaitEvents.offset = alignUpPow2<8>(ret.pRanges.offset + ret.pRanges.size);
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryRangesBarrierRpcM::Captures::getCaptureTotalSize() const {
     const auto lastMemberOffset = offsetPhWaitEvents;
     const auto lastMemberArraySize = this->countPhWaitEvents * sizeof(ze_event_handle_t);

     auto size = offsetof(Captures, dynMem) + Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

size_t ZeCommandListAppendMemoryRangesBarrierRpcM::Captures::getCaptureDynMemSize() const {
     const auto lastMemberOffset = offsetPhWaitEvents;
     const auto lastMemberArraySize = this->countPhWaitEvents * sizeof(ze_event_handle_t);

     auto size = Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

ZeCommandQueueExecuteCommandListsRpcM::Captures::DynamicTraits ZeCommandQueueExecuteCommandListsRpcM::Captures::DynamicTraits::calculate(ze_command_queue_handle_t hCommandQueue, uint32_t numCommandLists, ze_command_list_handle_t* phCommandLists, ze_fence_handle_t hFence) {
    DynamicTraits ret = {};
    ret.phCommandLists.count = phCommandLists ? (numCommandLists) : 0;
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

ZeCommandQueueExecuteCommandListsCopyMemoryRpcHelperRpcM::Captures::DynamicTraits ZeCommandQueueExecuteCommandListsCopyMemoryRpcHelperRpcM::Captures::DynamicTraits::calculate(uint32_t chunksCount, const Cal::Rpc::MemChunk* chunks, uint32_t* transferDescsCount, Cal::Rpc::TransferDesc* transferDescs) {
    DynamicTraits ret = {};
    ret.chunks.count = chunks ? (chunksCount) : 0;
    ret.chunks.size = ret.chunks.count * sizeof(Cal::Rpc::MemChunk);

    ret.transferDescs.offset = alignUpPow2<8>(ret.chunks.offset + ret.chunks.size);
    ret.transferDescs.count = transferDescs ? ((transferDescsCount ? *transferDescsCount : 0)) : 0;
    ret.transferDescs.size = ret.transferDescs.count * sizeof(Cal::Rpc::TransferDesc);
    ret.totalDynamicSize = alignUpPow2<8>(ret.transferDescs.offset + ret.transferDescs.size);


    return ret;
}

size_t ZeCommandQueueExecuteCommandListsCopyMemoryRpcHelperRpcM::Captures::getCaptureTotalSize() const {
     const auto lastMemberOffset = offsetTransferDescs;
     const auto lastMemberArraySize = this->countTransferDescs * sizeof(Cal::Rpc::TransferDesc);

     auto size = offsetof(Captures, dynMem) + Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

size_t ZeCommandQueueExecuteCommandListsCopyMemoryRpcHelperRpcM::Captures::getCaptureDynMemSize() const {
     const auto lastMemberOffset = offsetTransferDescs;
     const auto lastMemberArraySize = this->countTransferDescs * sizeof(Cal::Rpc::TransferDesc);

     auto size = Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

ZeContextCreateRpcM::Captures::DynamicTraits ZeContextCreateRpcM::Captures::DynamicTraits::calculate(ze_driver_handle_t hDriver, const ze_context_desc_t* desc, ze_context_handle_t* phContext) {
    DynamicTraits ret = {};

    ret.dynamicStructMembersOffset = ret.totalDynamicSize;
    if (desc) {
        ret.descNestedTraits.offset = ret.totalDynamicSize;
        ret.descNestedTraits.count = desc ? (1) : 0;
        ret.descNestedTraits.size = ret.descNestedTraits.count * sizeof(DynamicStructTraits<ze_context_desc_t>);
        ret.totalDynamicSize += alignUpPow2<8>(ret.descNestedTraits.size);

        for (uint32_t i = 0; i < ret.descNestedTraits.count; ++i) {
            const auto& descPNext = desc[i].pNext;
            if(!descPNext){
                continue;
            }

            const auto descPNextCount = static_cast<uint32_t>(countOpaqueList(static_cast<const ze_base_desc_t*>(desc[i].pNext)));
            if(!descPNextCount){
                continue;
            }

            ret.totalDynamicSize += alignUpPow2<8>(descPNextCount * sizeof(NestedPNextTraits));

            auto descPNextListElement = static_cast<const ze_base_desc_t*>(desc[i].pNext);
            for(uint32_t j = 0; j < descPNextCount; ++j){
                ret.totalDynamicSize += alignUpPow2<8>(getUnderlyingSize(descPNextListElement));
                descPNextListElement = getNext(descPNextListElement);
            }

        }
    }

    return ret;
}

size_t ZeContextCreateRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, dynMem) + dynMemSize;
     return size;
}

size_t ZeContextCreateRpcM::Captures::getCaptureDynMemSize() const {
     return dynMemSize;
}

ZeContextCreateExRpcM::Captures::DynamicTraits ZeContextCreateExRpcM::Captures::DynamicTraits::calculate(ze_driver_handle_t hDriver, const ze_context_desc_t* desc, uint32_t numDevices, ze_device_handle_t* phDevices, ze_context_handle_t* phContext) {
    DynamicTraits ret = {};
    ret.phDevices.count = phDevices ? (numDevices) : 0;
    ret.phDevices.size = ret.phDevices.count * sizeof(ze_device_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phDevices.offset + ret.phDevices.size);

    ret.dynamicStructMembersOffset = ret.totalDynamicSize;
    if (desc) {
        ret.descNestedTraits.offset = ret.totalDynamicSize;
        ret.descNestedTraits.count = desc ? (1) : 0;
        ret.descNestedTraits.size = ret.descNestedTraits.count * sizeof(DynamicStructTraits<ze_context_desc_t>);
        ret.totalDynamicSize += alignUpPow2<8>(ret.descNestedTraits.size);

        for (uint32_t i = 0; i < ret.descNestedTraits.count; ++i) {
            const auto& descPNext = desc[i].pNext;
            if(!descPNext){
                continue;
            }

            const auto descPNextCount = static_cast<uint32_t>(countOpaqueList(static_cast<const ze_base_desc_t*>(desc[i].pNext)));
            if(!descPNextCount){
                continue;
            }

            ret.totalDynamicSize += alignUpPow2<8>(descPNextCount * sizeof(NestedPNextTraits));

            auto descPNextListElement = static_cast<const ze_base_desc_t*>(desc[i].pNext);
            for(uint32_t j = 0; j < descPNextCount; ++j){
                ret.totalDynamicSize += alignUpPow2<8>(getUnderlyingSize(descPNextListElement));
                descPNextListElement = getNext(descPNextListElement);
            }

        }
    }

    return ret;
}

size_t ZeContextCreateExRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, dynMem) + dynMemSize;
     return size;
}

size_t ZeContextCreateExRpcM::Captures::getCaptureDynMemSize() const {
     return dynMemSize;
}

ZeCommandListAppendMemoryFillRpcHelperUsm2UsmRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryFillRpcHelperUsm2UsmRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* ptr, const void* pattern, size_t pattern_size, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
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
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
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
    ret.pattern.count = pattern ? (pattern_size) : 0;
    ret.pattern.size = ret.pattern.count;

    ret.phWaitEvents.offset = alignUpPow2<8>(ret.pattern.offset + ret.pattern.size);
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
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
    ret.pattern.count = pattern ? (pattern_size) : 0;
    ret.pattern.size = ret.pattern.count;

    ret.phWaitEvents.offset = alignUpPow2<8>(ret.pattern.offset + ret.pattern.size);
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
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
    ret.phDevices.count = phDevices ? ((pCount ? *pCount : 0)) : 0;
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
    ret.phSubdevices.count = phSubdevices ? ((pCount ? *pCount : 0)) : 0;
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

ZeDeviceGetPropertiesRpcM::Captures::DynamicTraits ZeDeviceGetPropertiesRpcM::Captures::DynamicTraits::calculate(ze_device_handle_t hDevice, ze_device_properties_t* pDeviceProperties) {
    DynamicTraits ret = {};

    ret.dynamicStructMembersOffset = ret.totalDynamicSize;
    if (pDeviceProperties) {
        ret.pDevicePropertiesNestedTraits.offset = ret.totalDynamicSize;
        ret.pDevicePropertiesNestedTraits.count = pDeviceProperties ? (1) : 0;
        ret.pDevicePropertiesNestedTraits.size = ret.pDevicePropertiesNestedTraits.count * sizeof(DynamicStructTraits<ze_device_properties_t>);
        ret.totalDynamicSize += alignUpPow2<8>(ret.pDevicePropertiesNestedTraits.size);

        for (uint32_t i = 0; i < ret.pDevicePropertiesNestedTraits.count; ++i) {
            const auto& pDevicePropertiesPNext = pDeviceProperties[i].pNext;
            if(!pDevicePropertiesPNext){
                continue;
            }

            const auto pDevicePropertiesPNextCount = static_cast<uint32_t>(countOpaqueList(static_cast<const ze_base_desc_t*>(pDeviceProperties[i].pNext)));
            if(!pDevicePropertiesPNextCount){
                continue;
            }

            ret.totalDynamicSize += alignUpPow2<8>(pDevicePropertiesPNextCount * sizeof(NestedPNextTraits));

            auto pDevicePropertiesPNextListElement = static_cast<const ze_base_desc_t*>(pDeviceProperties[i].pNext);
            for(uint32_t j = 0; j < pDevicePropertiesPNextCount; ++j){
                ret.totalDynamicSize += alignUpPow2<8>(getUnderlyingSize(pDevicePropertiesPNextListElement));
                pDevicePropertiesPNextListElement = getNext(pDevicePropertiesPNextListElement);
            }

        }
    }

    return ret;
}

size_t ZeDeviceGetPropertiesRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, dynMem) + dynMemSize;
     return size;
}

size_t ZeDeviceGetPropertiesRpcM::Captures::getCaptureDynMemSize() const {
     return dynMemSize;
}

ZeDeviceGetModulePropertiesRpcM::Captures::DynamicTraits ZeDeviceGetModulePropertiesRpcM::Captures::DynamicTraits::calculate(ze_device_handle_t hDevice, ze_device_module_properties_t* pModuleProperties) {
    DynamicTraits ret = {};

    ret.dynamicStructMembersOffset = ret.totalDynamicSize;
    if (pModuleProperties) {
        ret.pModulePropertiesNestedTraits.offset = ret.totalDynamicSize;
        ret.pModulePropertiesNestedTraits.count = pModuleProperties ? (1) : 0;
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
    ret.pCommandQueueGroupProperties.count = pCommandQueueGroupProperties ? ((pCount ? *pCount : 0)) : 0;
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
    ret.pMemProperties.count = pMemProperties ? ((pCount ? *pCount : 0)) : 0;
    ret.pMemProperties.size = ret.pMemProperties.count * sizeof(ze_device_memory_properties_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.pMemProperties.offset + ret.pMemProperties.size);

    ret.dynamicStructMembersOffset = ret.totalDynamicSize;
    if (pMemProperties) {
        ret.pMemPropertiesNestedTraits.offset = ret.totalDynamicSize;
        ret.pMemPropertiesNestedTraits.count = pMemProperties ? ((pCount ? *pCount : 0)) : 0;
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
    ret.pCacheProperties.count = pCacheProperties ? ((pCount ? *pCount : 0)) : 0;
    ret.pCacheProperties.size = ret.pCacheProperties.count * sizeof(ze_device_cache_properties_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.pCacheProperties.offset + ret.pCacheProperties.size);

    ret.dynamicStructMembersOffset = ret.totalDynamicSize;
    if (pCacheProperties) {
        ret.pCachePropertiesNestedTraits.offset = ret.totalDynamicSize;
        ret.pCachePropertiesNestedTraits.count = pCacheProperties ? ((pCount ? *pCount : 0)) : 0;
        ret.pCachePropertiesNestedTraits.size = ret.pCachePropertiesNestedTraits.count * sizeof(DynamicStructTraits<ze_device_cache_properties_t>);
        ret.totalDynamicSize += alignUpPow2<8>(ret.pCachePropertiesNestedTraits.size);

        for (uint32_t i = 0; i < ret.pCachePropertiesNestedTraits.count; ++i) {
            const auto& pCachePropertiesPNext = pCacheProperties[i].pNext;
            if(!pCachePropertiesPNext){
                continue;
            }

            const auto pCachePropertiesPNextCount = static_cast<uint32_t>(countOpaqueList(static_cast<const ze_base_desc_t*>(pCacheProperties[i].pNext)));
            if(!pCachePropertiesPNextCount){
                continue;
            }

            ret.totalDynamicSize += alignUpPow2<8>(pCachePropertiesPNextCount * sizeof(NestedPNextTraits));

            auto pCachePropertiesPNextListElement = static_cast<const ze_base_desc_t*>(pCacheProperties[i].pNext);
            for(uint32_t j = 0; j < pCachePropertiesPNextCount; ++j){
                ret.totalDynamicSize += alignUpPow2<8>(getUnderlyingSize(pCachePropertiesPNextListElement));
                pCachePropertiesPNextListElement = getNext(pCachePropertiesPNextListElement);
            }

        }
    }

    return ret;
}

size_t ZeDeviceGetCachePropertiesRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, dynMem) + dynMemSize;
     return size;
}

size_t ZeDeviceGetCachePropertiesRpcM::Captures::getCaptureDynMemSize() const {
     return dynMemSize;
}

ZeDeviceGetP2PPropertiesRpcM::Captures::DynamicTraits ZeDeviceGetP2PPropertiesRpcM::Captures::DynamicTraits::calculate(ze_device_handle_t hDevice, ze_device_handle_t hPeerDevice, ze_device_p2p_properties_t* pP2PProperties) {
    DynamicTraits ret = {};

    ret.dynamicStructMembersOffset = ret.totalDynamicSize;
    if (pP2PProperties) {
        ret.pP2PPropertiesNestedTraits.offset = ret.totalDynamicSize;
        ret.pP2PPropertiesNestedTraits.count = pP2PProperties ? (1) : 0;
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
    ret.phDrivers.count = phDrivers ? ((pCount ? *pCount : 0)) : 0;
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
    ret.pExtensionProperties.count = pExtensionProperties ? ((pCount ? *pCount : 0)) : 0;
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

ZeDriverGetLastErrorDescriptionRpcHelperRpcM::Captures::DynamicTraits ZeDriverGetLastErrorDescriptionRpcHelperRpcM::Captures::DynamicTraits::calculate(ze_driver_handle_t hDriver, size_t stringLength, char* pString) {
    DynamicTraits ret = {};
    ret.pString.count = pString ? (stringLength) : 0;
    ret.pString.size = ret.pString.count * sizeof(char);
    ret.totalDynamicSize = alignUpPow2<8>(ret.pString.offset + ret.pString.size);


    return ret;
}

size_t ZeDriverGetLastErrorDescriptionRpcHelperRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, pString) + Cal::Utils::alignUpPow2<8>(this->countPString * sizeof(char));
     return size;
}

size_t ZeDriverGetLastErrorDescriptionRpcHelperRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPString * sizeof(char));
     return size;
}

ZeEventPoolCreateRpcM::Captures::DynamicTraits ZeEventPoolCreateRpcM::Captures::DynamicTraits::calculate(ze_context_handle_t hContext, const ze_event_pool_desc_t* desc, uint32_t numDevices, ze_device_handle_t* phDevices, ze_event_pool_handle_t* phEventPool) {
    DynamicTraits ret = {};
    ret.phDevices.count = phDevices ? (numDevices) : 0;
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
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
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
    ret.phEvents.count = phEvents ? (numEvents) : 0;
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

ZeCommandListAppendQueryKernelTimestampsRpcM::Captures::DynamicTraits ZeCommandListAppendQueryKernelTimestampsRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, uint32_t numEvents, ze_event_handle_t* phEvents, void* dstptr, const size_t* pOffsets, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phEvents.count = phEvents ? (numEvents) : 0;
    ret.phEvents.size = ret.phEvents.count * sizeof(ze_event_handle_t);

    ret.dstptr.offset = alignUpPow2<8>(ret.phEvents.offset + ret.phEvents.size);
    ret.dstptr.count = dstptr ? (numEvents) : 0;
    ret.dstptr.size = ret.dstptr.count * sizeof(ze_kernel_timestamp_result_t);

    ret.phWaitEvents.offset = alignUpPow2<8>(ret.dstptr.offset + ret.dstptr.size);
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendQueryKernelTimestampsRpcM::Captures::getCaptureTotalSize() const {
     const auto lastMemberOffset = offsetPhWaitEvents;
     const auto lastMemberArraySize = this->countPhWaitEvents * sizeof(ze_event_handle_t);

     auto size = offsetof(Captures, dynMem) + Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

size_t ZeCommandListAppendQueryKernelTimestampsRpcM::Captures::getCaptureDynMemSize() const {
     const auto lastMemberOffset = offsetPhWaitEvents;
     const auto lastMemberArraySize = this->countPhWaitEvents * sizeof(ze_event_handle_t);

     auto size = Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

ZeEventQueryTimestampsExpRpcM::Captures::DynamicTraits ZeEventQueryTimestampsExpRpcM::Captures::DynamicTraits::calculate(ze_event_handle_t hEvent, ze_device_handle_t hDevice, uint32_t* pCount, ze_kernel_timestamp_result_t* pTimestamps) {
    DynamicTraits ret = {};
    ret.pTimestamps.count = pTimestamps ? ((pCount ? *pCount : 0)) : 0;
    ret.pTimestamps.size = ret.pTimestamps.count * sizeof(ze_kernel_timestamp_result_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.pTimestamps.offset + ret.pTimestamps.size);


    return ret;
}

size_t ZeEventQueryTimestampsExpRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, pTimestamps) + Cal::Utils::alignUpPow2<8>(this->countPTimestamps * sizeof(ze_kernel_timestamp_result_t));
     return size;
}

size_t ZeEventQueryTimestampsExpRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPTimestamps * sizeof(ze_kernel_timestamp_result_t));
     return size;
}

ZeEventQueryKernelTimestampsExtRpcHelperRpcM::Captures::DynamicTraits ZeEventQueryKernelTimestampsExtRpcHelperRpcM::Captures::DynamicTraits::calculate(ze_event_handle_t hEvent, ze_device_handle_t hDevice, uint32_t* pCount, ze_kernel_timestamp_result_t* pResultsTimestamps, ze_synchronized_timestamp_result_ext_t* pResultsSynchronizedTimestamps) {
    DynamicTraits ret = {};
    ret.pResultsTimestamps.count = pResultsTimestamps ? ((pCount ? *pCount : 0)) : 0;
    ret.pResultsTimestamps.size = ret.pResultsTimestamps.count * sizeof(ze_kernel_timestamp_result_t);

    ret.pResultsSynchronizedTimestamps.offset = alignUpPow2<8>(ret.pResultsTimestamps.offset + ret.pResultsTimestamps.size);
    ret.pResultsSynchronizedTimestamps.count = pResultsSynchronizedTimestamps ? ((pCount ? *pCount : 0)) : 0;
    ret.pResultsSynchronizedTimestamps.size = ret.pResultsSynchronizedTimestamps.count * sizeof(ze_synchronized_timestamp_result_ext_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.pResultsSynchronizedTimestamps.offset + ret.pResultsSynchronizedTimestamps.size);


    return ret;
}

size_t ZeEventQueryKernelTimestampsExtRpcHelperRpcM::Captures::getCaptureTotalSize() const {
     const auto lastMemberOffset = offsetPResultsSynchronizedTimestamps;
     const auto lastMemberArraySize = this->countPResultsSynchronizedTimestamps * sizeof(ze_synchronized_timestamp_result_ext_t);

     auto size = offsetof(Captures, dynMem) + Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

size_t ZeEventQueryKernelTimestampsExtRpcHelperRpcM::Captures::getCaptureDynMemSize() const {
     const auto lastMemberOffset = offsetPResultsSynchronizedTimestamps;
     const auto lastMemberArraySize = this->countPResultsSynchronizedTimestamps * sizeof(ze_synchronized_timestamp_result_ext_t);

     auto size = Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

ZeFabricVertexGetExpRpcM::Captures::DynamicTraits ZeFabricVertexGetExpRpcM::Captures::DynamicTraits::calculate(ze_driver_handle_t hDriver, uint32_t* pCount, ze_fabric_vertex_handle_t* phVertices) {
    DynamicTraits ret = {};
    ret.phVertices.count = phVertices ? ((pCount ? *pCount : 0)) : 0;
    ret.phVertices.size = ret.phVertices.count * sizeof(ze_fabric_vertex_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phVertices.offset + ret.phVertices.size);


    return ret;
}

size_t ZeFabricVertexGetExpRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phVertices) + Cal::Utils::alignUpPow2<8>(this->countPhVertices * sizeof(ze_fabric_vertex_handle_t));
     return size;
}

size_t ZeFabricVertexGetExpRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhVertices * sizeof(ze_fabric_vertex_handle_t));
     return size;
}

ZeFabricVertexGetSubVerticesExpRpcM::Captures::DynamicTraits ZeFabricVertexGetSubVerticesExpRpcM::Captures::DynamicTraits::calculate(ze_fabric_vertex_handle_t hVertex, uint32_t* pCount, ze_fabric_vertex_handle_t* phSubvertices) {
    DynamicTraits ret = {};
    ret.phSubvertices.count = phSubvertices ? ((pCount ? *pCount : 0)) : 0;
    ret.phSubvertices.size = ret.phSubvertices.count * sizeof(ze_fabric_vertex_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phSubvertices.offset + ret.phSubvertices.size);


    return ret;
}

size_t ZeFabricVertexGetSubVerticesExpRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phSubvertices) + Cal::Utils::alignUpPow2<8>(this->countPhSubvertices * sizeof(ze_fabric_vertex_handle_t));
     return size;
}

size_t ZeFabricVertexGetSubVerticesExpRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhSubvertices * sizeof(ze_fabric_vertex_handle_t));
     return size;
}

ZeFabricVertexGetPropertiesExpRpcM::Captures::DynamicTraits ZeFabricVertexGetPropertiesExpRpcM::Captures::DynamicTraits::calculate(ze_fabric_vertex_handle_t hVertex, ze_fabric_vertex_exp_properties_t* pVertexProperties) {
    DynamicTraits ret = {};

    ret.dynamicStructMembersOffset = ret.totalDynamicSize;
    if (pVertexProperties) {
        ret.pVertexPropertiesNestedTraits.offset = ret.totalDynamicSize;
        ret.pVertexPropertiesNestedTraits.count = pVertexProperties ? (1) : 0;
        ret.pVertexPropertiesNestedTraits.size = ret.pVertexPropertiesNestedTraits.count * sizeof(DynamicStructTraits<ze_fabric_vertex_exp_properties_t>);
        ret.totalDynamicSize += alignUpPow2<8>(ret.pVertexPropertiesNestedTraits.size);

        for (uint32_t i = 0; i < ret.pVertexPropertiesNestedTraits.count; ++i) {
            const auto& pVertexPropertiesPNext = pVertexProperties[i].pNext;
            if(!pVertexPropertiesPNext){
                continue;
            }

            const auto pVertexPropertiesPNextCount = static_cast<uint32_t>(countOpaqueList(static_cast<const ze_base_desc_t*>(pVertexProperties[i].pNext)));
            if(!pVertexPropertiesPNextCount){
                continue;
            }

            ret.totalDynamicSize += alignUpPow2<8>(pVertexPropertiesPNextCount * sizeof(NestedPNextTraits));

            auto pVertexPropertiesPNextListElement = static_cast<const ze_base_desc_t*>(pVertexProperties[i].pNext);
            for(uint32_t j = 0; j < pVertexPropertiesPNextCount; ++j){
                ret.totalDynamicSize += alignUpPow2<8>(getUnderlyingSize(pVertexPropertiesPNextListElement));
                pVertexPropertiesPNextListElement = getNext(pVertexPropertiesPNextListElement);
            }

        }
    }

    return ret;
}

size_t ZeFabricVertexGetPropertiesExpRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, dynMem) + dynMemSize;
     return size;
}

size_t ZeFabricVertexGetPropertiesExpRpcM::Captures::getCaptureDynMemSize() const {
     return dynMemSize;
}

ZeFabricEdgeGetExpRpcM::Captures::DynamicTraits ZeFabricEdgeGetExpRpcM::Captures::DynamicTraits::calculate(ze_fabric_vertex_handle_t hVertexA, ze_fabric_vertex_handle_t hVertexB, uint32_t* pCount, ze_fabric_edge_handle_t* phEdges) {
    DynamicTraits ret = {};
    ret.phEdges.count = phEdges ? ((pCount ? *pCount : 0)) : 0;
    ret.phEdges.size = ret.phEdges.count * sizeof(ze_fabric_edge_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phEdges.offset + ret.phEdges.size);


    return ret;
}

size_t ZeFabricEdgeGetExpRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phEdges) + Cal::Utils::alignUpPow2<8>(this->countPhEdges * sizeof(ze_fabric_edge_handle_t));
     return size;
}

size_t ZeFabricEdgeGetExpRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhEdges * sizeof(ze_fabric_edge_handle_t));
     return size;
}

ZeFabricEdgeGetPropertiesExpRpcM::Captures::DynamicTraits ZeFabricEdgeGetPropertiesExpRpcM::Captures::DynamicTraits::calculate(ze_fabric_edge_handle_t hEdge, ze_fabric_edge_exp_properties_t* pEdgeProperties) {
    DynamicTraits ret = {};

    ret.dynamicStructMembersOffset = ret.totalDynamicSize;
    if (pEdgeProperties) {
        ret.pEdgePropertiesNestedTraits.offset = ret.totalDynamicSize;
        ret.pEdgePropertiesNestedTraits.count = pEdgeProperties ? (1) : 0;
        ret.pEdgePropertiesNestedTraits.size = ret.pEdgePropertiesNestedTraits.count * sizeof(DynamicStructTraits<ze_fabric_edge_exp_properties_t>);
        ret.totalDynamicSize += alignUpPow2<8>(ret.pEdgePropertiesNestedTraits.size);

        for (uint32_t i = 0; i < ret.pEdgePropertiesNestedTraits.count; ++i) {
            const auto& pEdgePropertiesPNext = pEdgeProperties[i].pNext;
            if(!pEdgePropertiesPNext){
                continue;
            }

            const auto pEdgePropertiesPNextCount = static_cast<uint32_t>(countOpaqueList(static_cast<const ze_base_desc_t*>(pEdgeProperties[i].pNext)));
            if(!pEdgePropertiesPNextCount){
                continue;
            }

            ret.totalDynamicSize += alignUpPow2<8>(pEdgePropertiesPNextCount * sizeof(NestedPNextTraits));

            auto pEdgePropertiesPNextListElement = static_cast<const ze_base_desc_t*>(pEdgeProperties[i].pNext);
            for(uint32_t j = 0; j < pEdgePropertiesPNextCount; ++j){
                ret.totalDynamicSize += alignUpPow2<8>(getUnderlyingSize(pEdgePropertiesPNextListElement));
                pEdgePropertiesPNextListElement = getNext(pEdgePropertiesPNextListElement);
            }

        }
    }

    return ret;
}

size_t ZeFabricEdgeGetPropertiesExpRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, dynMem) + dynMemSize;
     return size;
}

size_t ZeFabricEdgeGetPropertiesExpRpcM::Captures::getCaptureDynMemSize() const {
     return dynMemSize;
}

ZeImageGetPropertiesRpcM::Captures::DynamicTraits ZeImageGetPropertiesRpcM::Captures::DynamicTraits::calculate(ze_device_handle_t hDevice, const ze_image_desc_t* desc, ze_image_properties_t* pImageProperties) {
    DynamicTraits ret = {};

    ret.dynamicStructMembersOffset = ret.totalDynamicSize;
    if (desc) {
        ret.descNestedTraits.offset = ret.totalDynamicSize;
        ret.descNestedTraits.count = desc ? (1) : 0;
        ret.descNestedTraits.size = ret.descNestedTraits.count * sizeof(DynamicStructTraits<ze_image_desc_t>);
        ret.totalDynamicSize += alignUpPow2<8>(ret.descNestedTraits.size);

        for (uint32_t i = 0; i < ret.descNestedTraits.count; ++i) {
            const auto& descPNext = desc[i].pNext;
            if(!descPNext){
                continue;
            }

            const auto descPNextCount = static_cast<uint32_t>(countOpaqueList(static_cast<const ze_base_desc_t*>(desc[i].pNext)));
            if(!descPNextCount){
                continue;
            }

            ret.totalDynamicSize += alignUpPow2<8>(descPNextCount * sizeof(NestedPNextTraits));

            auto descPNextListElement = static_cast<const ze_base_desc_t*>(desc[i].pNext);
            for(uint32_t j = 0; j < descPNextCount; ++j){
                ret.totalDynamicSize += alignUpPow2<8>(getUnderlyingSize(descPNextListElement));
                descPNextListElement = getNext(descPNextListElement);
            }

        }
    }

    return ret;
}

size_t ZeImageGetPropertiesRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, dynMem) + dynMemSize;
     return size;
}

size_t ZeImageGetPropertiesRpcM::Captures::getCaptureDynMemSize() const {
     return dynMemSize;
}

ZeImageCreateRpcM::Captures::DynamicTraits ZeImageCreateRpcM::Captures::DynamicTraits::calculate(ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_image_desc_t* desc, ze_image_handle_t* phImage) {
    DynamicTraits ret = {};

    ret.dynamicStructMembersOffset = ret.totalDynamicSize;
    if (desc) {
        ret.descNestedTraits.offset = ret.totalDynamicSize;
        ret.descNestedTraits.count = desc ? (1) : 0;
        ret.descNestedTraits.size = ret.descNestedTraits.count * sizeof(DynamicStructTraits<ze_image_desc_t>);
        ret.totalDynamicSize += alignUpPow2<8>(ret.descNestedTraits.size);

        for (uint32_t i = 0; i < ret.descNestedTraits.count; ++i) {
            const auto& descPNext = desc[i].pNext;
            if(!descPNext){
                continue;
            }

            const auto descPNextCount = static_cast<uint32_t>(countOpaqueList(static_cast<const ze_base_desc_t*>(desc[i].pNext)));
            if(!descPNextCount){
                continue;
            }

            ret.totalDynamicSize += alignUpPow2<8>(descPNextCount * sizeof(NestedPNextTraits));

            auto descPNextListElement = static_cast<const ze_base_desc_t*>(desc[i].pNext);
            for(uint32_t j = 0; j < descPNextCount; ++j){
                ret.totalDynamicSize += alignUpPow2<8>(getUnderlyingSize(descPNextListElement));
                descPNextListElement = getNext(descPNextListElement);
            }

        }
    }

    return ret;
}

size_t ZeImageCreateRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, dynMem) + dynMemSize;
     return size;
}

size_t ZeImageCreateRpcM::Captures::getCaptureDynMemSize() const {
     return dynMemSize;
}

ZeModuleInspectLinkageExtRpcM::Captures::DynamicTraits ZeModuleInspectLinkageExtRpcM::Captures::DynamicTraits::calculate(ze_linkage_inspection_ext_desc_t* pInspectDesc, uint32_t numModules, ze_module_handle_t* phModules, ze_module_build_log_handle_t* phLog) {
    DynamicTraits ret = {};
    ret.phModules.count = phModules ? (numModules) : 0;
    ret.phModules.size = ret.phModules.count * sizeof(ze_module_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phModules.offset + ret.phModules.size);


    return ret;
}

size_t ZeModuleInspectLinkageExtRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phModules) + Cal::Utils::alignUpPow2<8>(this->countPhModules * sizeof(ze_module_handle_t));
     return size;
}

size_t ZeModuleInspectLinkageExtRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhModules * sizeof(ze_module_handle_t));
     return size;
}

ZeMemAllocSharedRpcM::Captures::DynamicTraits ZeMemAllocSharedRpcM::Captures::DynamicTraits::calculate(ze_context_handle_t hContext, const ze_device_mem_alloc_desc_t* device_desc, const ze_host_mem_alloc_desc_t* host_desc, size_t size, size_t alignment, ze_device_handle_t hDevice, void** pptr) {
    DynamicTraits ret = {};

    ret.dynamicStructMembersOffset = ret.totalDynamicSize;
    if (device_desc) {
        ret.device_descNestedTraits.offset = ret.totalDynamicSize;
        ret.device_descNestedTraits.count = device_desc ? (1) : 0;
        ret.device_descNestedTraits.size = ret.device_descNestedTraits.count * sizeof(DynamicStructTraits<ze_device_mem_alloc_desc_t>);
        ret.totalDynamicSize += alignUpPow2<8>(ret.device_descNestedTraits.size);

        for (uint32_t i = 0; i < ret.device_descNestedTraits.count; ++i) {
            const auto& device_descPNext = device_desc[i].pNext;
            if(!device_descPNext){
                continue;
            }

            const auto device_descPNextCount = static_cast<uint32_t>(countOpaqueList(static_cast<const ze_base_desc_t*>(device_desc[i].pNext)));
            if(!device_descPNextCount){
                continue;
            }

            ret.totalDynamicSize += alignUpPow2<8>(device_descPNextCount * sizeof(NestedPNextTraits));

            auto device_descPNextListElement = static_cast<const ze_base_desc_t*>(device_desc[i].pNext);
            for(uint32_t j = 0; j < device_descPNextCount; ++j){
                ret.totalDynamicSize += alignUpPow2<8>(getUnderlyingSize(device_descPNextListElement));
                device_descPNextListElement = getNext(device_descPNextListElement);
            }

        }
    }
    if (host_desc) {
        ret.host_descNestedTraits.offset = ret.totalDynamicSize;
        ret.host_descNestedTraits.count = host_desc ? (1) : 0;
        ret.host_descNestedTraits.size = ret.host_descNestedTraits.count * sizeof(DynamicStructTraits<ze_host_mem_alloc_desc_t>);
        ret.totalDynamicSize += alignUpPow2<8>(ret.host_descNestedTraits.size);

        for (uint32_t i = 0; i < ret.host_descNestedTraits.count; ++i) {
            const auto& host_descPNext = host_desc[i].pNext;
            if(!host_descPNext){
                continue;
            }

            const auto host_descPNextCount = static_cast<uint32_t>(countOpaqueList(static_cast<const ze_base_desc_t*>(host_desc[i].pNext)));
            if(!host_descPNextCount){
                continue;
            }

            ret.totalDynamicSize += alignUpPow2<8>(host_descPNextCount * sizeof(NestedPNextTraits));

            auto host_descPNextListElement = static_cast<const ze_base_desc_t*>(host_desc[i].pNext);
            for(uint32_t j = 0; j < host_descPNextCount; ++j){
                ret.totalDynamicSize += alignUpPow2<8>(getUnderlyingSize(host_descPNextListElement));
                host_descPNextListElement = getNext(host_descPNextListElement);
            }

        }
    }

    return ret;
}

size_t ZeMemAllocSharedRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, dynMem) + dynMemSize;
     return size;
}

size_t ZeMemAllocSharedRpcM::Captures::getCaptureDynMemSize() const {
     return dynMemSize;
}

ZeMemAllocDeviceRpcM::Captures::DynamicTraits ZeMemAllocDeviceRpcM::Captures::DynamicTraits::calculate(ze_context_handle_t hContext, const ze_device_mem_alloc_desc_t* device_desc, size_t size, size_t alignment, ze_device_handle_t hDevice, void** pptr) {
    DynamicTraits ret = {};

    ret.dynamicStructMembersOffset = ret.totalDynamicSize;
    if (device_desc) {
        ret.device_descNestedTraits.offset = ret.totalDynamicSize;
        ret.device_descNestedTraits.count = device_desc ? (1) : 0;
        ret.device_descNestedTraits.size = ret.device_descNestedTraits.count * sizeof(DynamicStructTraits<ze_device_mem_alloc_desc_t>);
        ret.totalDynamicSize += alignUpPow2<8>(ret.device_descNestedTraits.size);

        for (uint32_t i = 0; i < ret.device_descNestedTraits.count; ++i) {
            const auto& device_descPNext = device_desc[i].pNext;
            if(!device_descPNext){
                continue;
            }

            const auto device_descPNextCount = static_cast<uint32_t>(countOpaqueList(static_cast<const ze_base_desc_t*>(device_desc[i].pNext)));
            if(!device_descPNextCount){
                continue;
            }

            ret.totalDynamicSize += alignUpPow2<8>(device_descPNextCount * sizeof(NestedPNextTraits));

            auto device_descPNextListElement = static_cast<const ze_base_desc_t*>(device_desc[i].pNext);
            for(uint32_t j = 0; j < device_descPNextCount; ++j){
                ret.totalDynamicSize += alignUpPow2<8>(getUnderlyingSize(device_descPNextListElement));
                device_descPNextListElement = getNext(device_descPNextListElement);
            }

        }
    }

    return ret;
}

size_t ZeMemAllocDeviceRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, dynMem) + dynMemSize;
     return size;
}

size_t ZeMemAllocDeviceRpcM::Captures::getCaptureDynMemSize() const {
     return dynMemSize;
}

ZeMemAllocHostRpcM::Captures::DynamicTraits ZeMemAllocHostRpcM::Captures::DynamicTraits::calculate(ze_context_handle_t hContext, const ze_host_mem_alloc_desc_t* host_desc, size_t size, size_t alignment, void** pptr) {
    DynamicTraits ret = {};

    ret.dynamicStructMembersOffset = ret.totalDynamicSize;
    if (host_desc) {
        ret.host_descNestedTraits.offset = ret.totalDynamicSize;
        ret.host_descNestedTraits.count = host_desc ? (1) : 0;
        ret.host_descNestedTraits.size = ret.host_descNestedTraits.count * sizeof(DynamicStructTraits<ze_host_mem_alloc_desc_t>);
        ret.totalDynamicSize += alignUpPow2<8>(ret.host_descNestedTraits.size);

        for (uint32_t i = 0; i < ret.host_descNestedTraits.count; ++i) {
            const auto& host_descPNext = host_desc[i].pNext;
            if(!host_descPNext){
                continue;
            }

            const auto host_descPNextCount = static_cast<uint32_t>(countOpaqueList(static_cast<const ze_base_desc_t*>(host_desc[i].pNext)));
            if(!host_descPNextCount){
                continue;
            }

            ret.totalDynamicSize += alignUpPow2<8>(host_descPNextCount * sizeof(NestedPNextTraits));

            auto host_descPNextListElement = static_cast<const ze_base_desc_t*>(host_desc[i].pNext);
            for(uint32_t j = 0; j < host_descPNextCount; ++j){
                ret.totalDynamicSize += alignUpPow2<8>(getUnderlyingSize(host_descPNextListElement));
                host_descPNextListElement = getNext(host_descPNextListElement);
            }

        }
    }

    return ret;
}

size_t ZeMemAllocHostRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, dynMem) + dynMemSize;
     return size;
}

size_t ZeMemAllocHostRpcM::Captures::getCaptureDynMemSize() const {
     return dynMemSize;
}

ZeMemGetAllocPropertiesRpcM::Captures::DynamicTraits ZeMemGetAllocPropertiesRpcM::Captures::DynamicTraits::calculate(ze_context_handle_t hContext, const void* ptr, ze_memory_allocation_properties_t* pMemAllocProperties, ze_device_handle_t* phDevice) {
    DynamicTraits ret = {};

    ret.dynamicStructMembersOffset = ret.totalDynamicSize;
    if (pMemAllocProperties) {
        ret.pMemAllocPropertiesNestedTraits.offset = ret.totalDynamicSize;
        ret.pMemAllocPropertiesNestedTraits.count = pMemAllocProperties ? (1) : 0;
        ret.pMemAllocPropertiesNestedTraits.size = ret.pMemAllocPropertiesNestedTraits.count * sizeof(DynamicStructTraits<ze_memory_allocation_properties_t>);
        ret.totalDynamicSize += alignUpPow2<8>(ret.pMemAllocPropertiesNestedTraits.size);

        for (uint32_t i = 0; i < ret.pMemAllocPropertiesNestedTraits.count; ++i) {
            const auto& pMemAllocPropertiesPNext = pMemAllocProperties[i].pNext;
            if(!pMemAllocPropertiesPNext){
                continue;
            }

            const auto pMemAllocPropertiesPNextCount = static_cast<uint32_t>(countOpaqueList(static_cast<const ze_base_desc_t*>(pMemAllocProperties[i].pNext)));
            if(!pMemAllocPropertiesPNextCount){
                continue;
            }

            ret.totalDynamicSize += alignUpPow2<8>(pMemAllocPropertiesPNextCount * sizeof(NestedPNextTraits));

            auto pMemAllocPropertiesPNextListElement = static_cast<const ze_base_desc_t*>(pMemAllocProperties[i].pNext);
            for(uint32_t j = 0; j < pMemAllocPropertiesPNextCount; ++j){
                ret.totalDynamicSize += alignUpPow2<8>(getUnderlyingSize(pMemAllocPropertiesPNextListElement));
                pMemAllocPropertiesPNextListElement = getNext(pMemAllocPropertiesPNextListElement);
            }

        }
    }

    return ret;
}

size_t ZeMemGetAllocPropertiesRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, dynMem) + dynMemSize;
     return size;
}

size_t ZeMemGetAllocPropertiesRpcM::Captures::getCaptureDynMemSize() const {
     return dynMemSize;
}

ZexMemGetIpcHandlesRpcM::Captures::DynamicTraits ZexMemGetIpcHandlesRpcM::Captures::DynamicTraits::calculate(ze_context_handle_t hContext, const void* ptr, uint32_t* numIpcHandles, ze_ipc_mem_handle_t* pIpcHandles) {
    DynamicTraits ret = {};
    ret.pIpcHandles.count = pIpcHandles ? ((numIpcHandles ? *numIpcHandles : 0)) : 0;
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
    ret.pIpcHandles.count = pIpcHandles ? (numIpcHandles) : 0;
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

ZeMemFreeExtRpcM::Captures::DynamicTraits ZeMemFreeExtRpcM::Captures::DynamicTraits::calculate(ze_context_handle_t hContext, const ze_memory_free_ext_desc_t* pMemFreeDesc, void* ptr) {
    DynamicTraits ret = {};

    ret.dynamicStructMembersOffset = ret.totalDynamicSize;
    if (pMemFreeDesc) {
        ret.pMemFreeDescNestedTraits.offset = ret.totalDynamicSize;
        ret.pMemFreeDescNestedTraits.count = pMemFreeDesc ? (1) : 0;
        ret.pMemFreeDescNestedTraits.size = ret.pMemFreeDescNestedTraits.count * sizeof(DynamicStructTraits<ze_memory_free_ext_desc_t>);
        ret.totalDynamicSize += alignUpPow2<8>(ret.pMemFreeDescNestedTraits.size);

        for (uint32_t i = 0; i < ret.pMemFreeDescNestedTraits.count; ++i) {
            const auto& pMemFreeDescPNext = pMemFreeDesc[i].pNext;
            if(!pMemFreeDescPNext){
                continue;
            }

            const auto pMemFreeDescPNextCount = static_cast<uint32_t>(countOpaqueList(static_cast<const ze_base_desc_t*>(pMemFreeDesc[i].pNext)));
            if(!pMemFreeDescPNextCount){
                continue;
            }

            ret.totalDynamicSize += alignUpPow2<8>(pMemFreeDescPNextCount * sizeof(NestedPNextTraits));

            auto pMemFreeDescPNextListElement = static_cast<const ze_base_desc_t*>(pMemFreeDesc[i].pNext);
            for(uint32_t j = 0; j < pMemFreeDescPNextCount; ++j){
                ret.totalDynamicSize += alignUpPow2<8>(getUnderlyingSize(pMemFreeDescPNextListElement));
                pMemFreeDescPNextListElement = getNext(pMemFreeDescPNextListElement);
            }

        }
    }

    return ret;
}

size_t ZeMemFreeExtRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, dynMem) + dynMemSize;
     return size;
}

size_t ZeMemFreeExtRpcM::Captures::getCaptureDynMemSize() const {
     return dynMemSize;
}

ZeModuleCreateRpcM::Captures::DynamicTraits ZeModuleCreateRpcM::Captures::DynamicTraits::calculate(ze_context_handle_t hContext, ze_device_handle_t hDevice, const ze_module_desc_t* desc, ze_module_handle_t* phModule, ze_module_build_log_handle_t* phBuildLog) {
    DynamicTraits ret = {};

    ret.dynamicStructMembersOffset = ret.totalDynamicSize;
    if (desc) {
        ret.descNestedTraits.offset = ret.totalDynamicSize;
        ret.descNestedTraits.count = desc ? (1) : 0;
        ret.descNestedTraits.size = ret.descNestedTraits.count * sizeof(DynamicStructTraits<ze_module_desc_t>);
        ret.totalDynamicSize += alignUpPow2<8>(ret.descNestedTraits.size);

        for (uint32_t i = 0; i < ret.descNestedTraits.count; ++i) {
            const auto& descPNext = desc[i].pNext;
            if(!descPNext){
                continue;
            }

            const auto descPNextCount = static_cast<uint32_t>(countOpaqueList(static_cast<const ze_base_desc_t*>(desc[i].pNext)));
            if(!descPNextCount){
                continue;
            }

            ret.totalDynamicSize += alignUpPow2<8>(descPNextCount * sizeof(NestedPNextTraits));

            auto descPNextListElement = static_cast<const ze_base_desc_t*>(desc[i].pNext);
            for(uint32_t j = 0; j < descPNextCount; ++j){
                ret.totalDynamicSize += alignUpPow2<8>(getUnderlyingSize(descPNextListElement));

                const auto extensionType = static_cast<int>(getExtensionType(descPNextListElement));
                if (extensionType == ZE_STRUCTURE_TYPE_MODULE_PROGRAM_EXP_DESC) {
                    auto& extension = *reinterpret_cast<const ze_module_program_exp_desc_t*>(descPNextListElement);
                    ret.totalDynamicSize += alignUpPow2<8>(sizeof(DynamicStructTraits<ze_module_program_exp_desc_t>));

                    do {
                        const auto& descPNextInputSizes = extension.inputSizes;
                        if(!descPNextInputSizes){
                            continue;
                        }

                        const auto descPNextInputSizesCount = static_cast<uint32_t>(extension.count);
                        if(!descPNextInputSizesCount){
                            continue;
                        }

                        ret.totalDynamicSize += alignUpPow2<8>(descPNextInputSizesCount * sizeof(size_t));
                    } while (0);

                    do {
                        const auto& descPNextPInputModules = extension.pInputModules;
                        if(!descPNextPInputModules){
                            continue;
                        }

                        const auto descPNextPInputModulesCount = static_cast<uint32_t>(extension.count);
                        if(!descPNextPInputModulesCount){
                            continue;
                        }

                        ret.totalDynamicSize += alignUpPow2<8>(descPNextPInputModulesCount * sizeof(const uint8_t*));
                        ret.totalDynamicSize += alignUpPow2<8>(descPNextPInputModulesCount * sizeof(DynamicStructTraits<const uint8_t*>));
                        for(uint32_t k = 0; k < descPNextPInputModulesCount; ++k){
                            const auto& descPNextPInputModules_k = descPNextPInputModules[k];
                            if(!descPNextPInputModules_k){
                                continue;
                            }

                            const auto descPNextPInputModules_kCount = static_cast<uint32_t>(extension.inputSizes[k]);
                            if(!descPNextPInputModules_kCount){
                                continue;
                            }
                            ret.totalDynamicSize += alignUpPow2<8>(descPNextPInputModules_kCount * sizeof(uint8_t));
                        }

                    } while (0);

                    do {
                        const auto& descPNextPBuildFlags = extension.pBuildFlags;
                        if(!descPNextPBuildFlags){
                            continue;
                        }

                        const auto descPNextPBuildFlagsCount = static_cast<uint32_t>(extension.count);
                        if(!descPNextPBuildFlagsCount){
                            continue;
                        }

                        ret.totalDynamicSize += alignUpPow2<8>(descPNextPBuildFlagsCount * sizeof(const char*));
                        ret.totalDynamicSize += alignUpPow2<8>(descPNextPBuildFlagsCount * sizeof(DynamicStructTraits<const char*>));
                        for(uint32_t k = 0; k < descPNextPBuildFlagsCount; ++k){
                            const auto& descPNextPBuildFlags_k = descPNextPBuildFlags[k];
                            if(!descPNextPBuildFlags_k){
                                continue;
                            }

                            const auto descPNextPBuildFlags_kCount = static_cast<uint32_t>(Cal::Utils::countNullterminated(descPNextPBuildFlags[k]));
                            if(!descPNextPBuildFlags_kCount){
                                continue;
                            }
                            ret.totalDynamicSize += alignUpPow2<8>(descPNextPBuildFlags_kCount * sizeof(char));
                        }

                    } while (0);

                    do {
                        const auto& descPNextPConstants = extension.pConstants;
                        if(!descPNextPConstants){
                            continue;
                        }

                        const auto descPNextPConstantsCount = static_cast<uint32_t>(extension.count);
                        if(!descPNextPConstantsCount){
                            continue;
                        }

                        ret.totalDynamicSize += alignUpPow2<8>(descPNextPConstantsCount * sizeof(const ze_module_constants_t*));
                        ret.totalDynamicSize += alignUpPow2<8>(descPNextPConstantsCount * sizeof(DynamicStructTraits<const ze_module_constants_t*>));
                        for(uint32_t k = 0; k < descPNextPConstantsCount; ++k){
                            const auto& descPNextPConstants_k = descPNextPConstants[k];
                            if(!descPNextPConstants_k){
                                continue;
                            }

                            const auto descPNextPConstants_kCount = static_cast<uint32_t>(1);
                            if(!descPNextPConstants_kCount){
                                continue;
                            }
                            ret.totalDynamicSize += alignUpPow2<8>(descPNextPConstants_kCount * sizeof(ze_module_constants_t));
                            ret.totalDynamicSize += alignUpPow2<8>(descPNextPConstants_kCount * sizeof(DynamicStructTraits<ze_module_constants_t>));

                            for(uint32_t l = 0; l < 1; ++l){
                                do {
                                    const auto& descPNextPConstantsPConstantIds = extension.pConstants[k][l].pConstantIds;
                                    if(!descPNextPConstantsPConstantIds){
                                        continue;
                                    }

                                    const auto descPNextPConstantsPConstantIdsCount = static_cast<uint32_t>(extension.pConstants[k][l].numConstants);
                                    if(!descPNextPConstantsPConstantIdsCount){
                                        continue;
                                    }

                                    ret.totalDynamicSize += alignUpPow2<8>(descPNextPConstantsPConstantIdsCount * sizeof(uint32_t));
                                } while (0);
                                do {
                                    const auto& descPNextPConstantsPConstantValues = extension.pConstants[k][l].pConstantValues;
                                    if(!descPNextPConstantsPConstantValues){
                                        continue;
                                    }

                                    const auto descPNextPConstantsPConstantValuesCount = static_cast<uint32_t>(extension.pConstants[k][l].numConstants);
                                    if(!descPNextPConstantsPConstantValuesCount){
                                        continue;
                                    }

                                    ret.totalDynamicSize += alignUpPow2<8>(descPNextPConstantsPConstantValuesCount * sizeof(const void *));
                                    ret.totalDynamicSize += alignUpPow2<8>(descPNextPConstantsPConstantValuesCount * sizeof(DynamicStructTraits<const void *>));
                                    for(uint32_t m = 0; m < descPNextPConstantsPConstantValuesCount; ++m){
                                        const auto& descPNextPConstantsPConstantValues_m = descPNextPConstantsPConstantValues[m];
                                        if(!descPNextPConstantsPConstantValues_m){
                                            continue;
                                        }

                                        const auto descPNextPConstantsPConstantValues_mCount = static_cast<uint32_t>(1);
                                        if(!descPNextPConstantsPConstantValues_mCount){
                                            continue;
                                        }
                                        ret.totalDynamicSize += alignUpPow2<8>(descPNextPConstantsPConstantValues_mCount * sizeof(uint64_t));
                                    }

                                } while (0);
                            }
                        }

                    } while (0);
                }
                descPNextListElement = getNext(descPNextListElement);
            }

        }

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
    ret.phModules.count = phModules ? (numModules) : 0;
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
    ret.pBuildLog.count = pBuildLog ? ((pSize ? *pSize : 0)) : 0;
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
    ret.pModuleNativeBinary.count = pModuleNativeBinary ? ((pSize ? *pSize : 0)) : 0;
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
    ret.pGlobalName.count = pGlobalName ? (Cal::Utils::countNullterminated(pGlobalName)) : 0;
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
    ret.namesBuffer.count = namesBuffer ? ((totalLength ? *totalLength : 0)) : 0;
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
        ret.descNestedTraits.count = desc ? (1) : 0;
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
    ret.pFunctionName.count = pFunctionName ? (Cal::Utils::countNullterminated(pFunctionName)) : 0;
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
    ret.pArgValue.count = pArgValue ? (argSize) : 0;
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

ZeKernelGetSourceAttributesRpcHelperRpcM::Captures::DynamicTraits ZeKernelGetSourceAttributesRpcHelperRpcM::Captures::DynamicTraits::calculate(ze_kernel_handle_t hKernel, uint32_t* pSize, char* pString) {
    DynamicTraits ret = {};
    ret.pString.count = pString ? (*pSize) : 0;
    ret.pString.size = ret.pString.count * sizeof(char);
    ret.totalDynamicSize = alignUpPow2<8>(ret.pString.offset + ret.pString.size);


    return ret;
}

size_t ZeKernelGetSourceAttributesRpcHelperRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, pString) + Cal::Utils::alignUpPow2<8>(this->countPString * sizeof(char));
     return size;
}

size_t ZeKernelGetSourceAttributesRpcHelperRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPString * sizeof(char));
     return size;
}

ZeKernelGetPropertiesRpcM::Captures::DynamicTraits ZeKernelGetPropertiesRpcM::Captures::DynamicTraits::calculate(ze_kernel_handle_t hKernel, ze_kernel_properties_t* pKernelProperties) {
    DynamicTraits ret = {};

    ret.dynamicStructMembersOffset = ret.totalDynamicSize;
    if (pKernelProperties) {
        ret.pKernelPropertiesNestedTraits.offset = ret.totalDynamicSize;
        ret.pKernelPropertiesNestedTraits.count = pKernelProperties ? (1) : 0;
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
    ret.pName.count = pName ? ((pSize ? *pSize : 0)) : 0;
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
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
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

ZeCommandListAppendLaunchCooperativeKernelRpcM::Captures::DynamicTraits ZeCommandListAppendLaunchCooperativeKernelRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchFuncArgs, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendLaunchCooperativeKernelRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendLaunchCooperativeKernelRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendLaunchKernelIndirectRpcM::Captures::DynamicTraits ZeCommandListAppendLaunchKernelIndirectRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, ze_kernel_handle_t hKernel, const ze_group_count_t* pLaunchArgumentsBuffer, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
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

ZeCommandListAppendLaunchMultipleKernelsIndirectRpcM::Captures::DynamicTraits ZeCommandListAppendLaunchMultipleKernelsIndirectRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, uint32_t numKernels, ze_kernel_handle_t* phKernels, const uint32_t* pCountBuffer, const ze_group_count_t* pLaunchArgumentsBuffer, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phKernels.count = phKernels ? (numKernels) : 0;
    ret.phKernels.size = ret.phKernels.count * sizeof(ze_kernel_handle_t);

    ret.phWaitEvents.offset = alignUpPow2<8>(ret.phKernels.offset + ret.phKernels.size);
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendLaunchMultipleKernelsIndirectRpcM::Captures::getCaptureTotalSize() const {
     const auto lastMemberOffset = offsetPhWaitEvents;
     const auto lastMemberArraySize = this->countPhWaitEvents * sizeof(ze_event_handle_t);

     auto size = offsetof(Captures, dynMem) + Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

size_t ZeCommandListAppendLaunchMultipleKernelsIndirectRpcM::Captures::getCaptureDynMemSize() const {
     const auto lastMemberOffset = offsetPhWaitEvents;
     const auto lastMemberArraySize = this->countPhWaitEvents * sizeof(ze_event_handle_t);

     auto size = Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

ZeCommandListAppendWriteGlobalTimestamp_LocalRpcM::Captures::DynamicTraits ZeCommandListAppendWriteGlobalTimestamp_LocalRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, uint64_t* dstptr, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendWriteGlobalTimestamp_LocalRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendWriteGlobalTimestamp_LocalRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendWriteGlobalTimestamp_UsmRpcM::Captures::DynamicTraits ZeCommandListAppendWriteGlobalTimestamp_UsmRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, uint64_t* dstptr, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendWriteGlobalTimestamp_UsmRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendWriteGlobalTimestamp_UsmRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendWriteGlobalTimestamp_SharedRpcM::Captures::DynamicTraits ZeCommandListAppendWriteGlobalTimestamp_SharedRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, uint64_t* dstptr, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendWriteGlobalTimestamp_SharedRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendWriteGlobalTimestamp_SharedRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyDeferred_Usm_UsmRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyDeferred_Usm_UsmRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyDeferred_Usm_UsmRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyDeferred_Usm_UsmRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyDeferred_Usm_SharedRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyDeferred_Usm_SharedRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyDeferred_Usm_SharedRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyDeferred_Usm_SharedRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyDeferred_Usm_RemappedRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyDeferred_Usm_RemappedRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyDeferred_Usm_RemappedRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyDeferred_Usm_RemappedRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyDeferred_Shared_UsmRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyDeferred_Shared_UsmRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyDeferred_Shared_UsmRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyDeferred_Shared_UsmRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyDeferred_Shared_SharedRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyDeferred_Shared_SharedRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyDeferred_Shared_SharedRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyDeferred_Shared_SharedRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyDeferred_Shared_RemappedRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyDeferred_Shared_RemappedRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyDeferred_Shared_RemappedRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyDeferred_Shared_RemappedRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyDeferred_Remapped_UsmRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyDeferred_Remapped_UsmRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyDeferred_Remapped_UsmRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyDeferred_Remapped_UsmRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyDeferred_Remapped_SharedRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyDeferred_Remapped_SharedRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyDeferred_Remapped_SharedRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyDeferred_Remapped_SharedRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyDeferred_Remapped_RemappedRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyDeferred_Remapped_RemappedRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyDeferred_Remapped_RemappedRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyDeferred_Remapped_RemappedRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyImmediate_Local_LocalRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyImmediate_Local_LocalRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyImmediate_Local_LocalRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyImmediate_Local_LocalRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyImmediate_Local_UsmRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyImmediate_Local_UsmRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyImmediate_Local_UsmRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyImmediate_Local_UsmRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyImmediate_Local_SharedRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyImmediate_Local_SharedRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyImmediate_Local_SharedRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyImmediate_Local_SharedRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyImmediate_Usm_LocalRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyImmediate_Usm_LocalRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyImmediate_Usm_LocalRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyImmediate_Usm_LocalRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyImmediate_Usm_UsmRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyImmediate_Usm_UsmRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyImmediate_Usm_UsmRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyImmediate_Usm_UsmRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyImmediate_Usm_SharedRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyImmediate_Usm_SharedRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyImmediate_Usm_SharedRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyImmediate_Usm_SharedRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyImmediate_Shared_LocalRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyImmediate_Shared_LocalRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyImmediate_Shared_LocalRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyImmediate_Shared_LocalRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyImmediate_Shared_UsmRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyImmediate_Shared_UsmRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyImmediate_Shared_UsmRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyImmediate_Shared_UsmRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyImmediate_Shared_SharedRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyImmediate_Shared_SharedRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyImmediate_Shared_SharedRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyImmediate_Shared_SharedRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyImmediateSynchronous_Local_LocalRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyImmediateSynchronous_Local_LocalRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.dstptr.count = dstptr ? (size) : 0;
    ret.dstptr.size = ret.dstptr.count;

    ret.srcptr.offset = alignUpPow2<8>(ret.dstptr.offset + ret.dstptr.size);
    ret.srcptr.count = srcptr ? (size) : 0;
    ret.srcptr.size = ret.srcptr.count;

    ret.phWaitEvents.offset = alignUpPow2<8>(ret.srcptr.offset + ret.srcptr.size);
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyImmediateSynchronous_Local_LocalRpcM::Captures::getCaptureTotalSize() const {
     const auto lastMemberOffset = offsetPhWaitEvents;
     const auto lastMemberArraySize = this->countPhWaitEvents * sizeof(ze_event_handle_t);

     auto size = offsetof(Captures, dynMem) + Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

size_t ZeCommandListAppendMemoryCopyImmediateSynchronous_Local_LocalRpcM::Captures::getCaptureDynMemSize() const {
     const auto lastMemberOffset = offsetPhWaitEvents;
     const auto lastMemberArraySize = this->countPhWaitEvents * sizeof(ze_event_handle_t);

     auto size = Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

ZeCommandListAppendMemoryCopyImmediateSynchronous_Local_UsmRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyImmediateSynchronous_Local_UsmRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.dstptr.count = dstptr ? (size) : 0;
    ret.dstptr.size = ret.dstptr.count;

    ret.phWaitEvents.offset = alignUpPow2<8>(ret.dstptr.offset + ret.dstptr.size);
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyImmediateSynchronous_Local_UsmRpcM::Captures::getCaptureTotalSize() const {
     const auto lastMemberOffset = offsetPhWaitEvents;
     const auto lastMemberArraySize = this->countPhWaitEvents * sizeof(ze_event_handle_t);

     auto size = offsetof(Captures, dynMem) + Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

size_t ZeCommandListAppendMemoryCopyImmediateSynchronous_Local_UsmRpcM::Captures::getCaptureDynMemSize() const {
     const auto lastMemberOffset = offsetPhWaitEvents;
     const auto lastMemberArraySize = this->countPhWaitEvents * sizeof(ze_event_handle_t);

     auto size = Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

ZeCommandListAppendMemoryCopyImmediateSynchronous_Local_SharedRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyImmediateSynchronous_Local_SharedRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.dstptr.count = dstptr ? (size) : 0;
    ret.dstptr.size = ret.dstptr.count;

    ret.phWaitEvents.offset = alignUpPow2<8>(ret.dstptr.offset + ret.dstptr.size);
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyImmediateSynchronous_Local_SharedRpcM::Captures::getCaptureTotalSize() const {
     const auto lastMemberOffset = offsetPhWaitEvents;
     const auto lastMemberArraySize = this->countPhWaitEvents * sizeof(ze_event_handle_t);

     auto size = offsetof(Captures, dynMem) + Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

size_t ZeCommandListAppendMemoryCopyImmediateSynchronous_Local_SharedRpcM::Captures::getCaptureDynMemSize() const {
     const auto lastMemberOffset = offsetPhWaitEvents;
     const auto lastMemberArraySize = this->countPhWaitEvents * sizeof(ze_event_handle_t);

     auto size = Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

ZeCommandListAppendMemoryCopyImmediateSynchronous_Usm_LocalRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyImmediateSynchronous_Usm_LocalRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.srcptr.count = srcptr ? (size) : 0;
    ret.srcptr.size = ret.srcptr.count;

    ret.phWaitEvents.offset = alignUpPow2<8>(ret.srcptr.offset + ret.srcptr.size);
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyImmediateSynchronous_Usm_LocalRpcM::Captures::getCaptureTotalSize() const {
     const auto lastMemberOffset = offsetPhWaitEvents;
     const auto lastMemberArraySize = this->countPhWaitEvents * sizeof(ze_event_handle_t);

     auto size = offsetof(Captures, dynMem) + Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

size_t ZeCommandListAppendMemoryCopyImmediateSynchronous_Usm_LocalRpcM::Captures::getCaptureDynMemSize() const {
     const auto lastMemberOffset = offsetPhWaitEvents;
     const auto lastMemberArraySize = this->countPhWaitEvents * sizeof(ze_event_handle_t);

     auto size = Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

ZeCommandListAppendMemoryCopyImmediateSynchronous_Usm_UsmRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyImmediateSynchronous_Usm_UsmRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyImmediateSynchronous_Usm_UsmRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyImmediateSynchronous_Usm_UsmRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyImmediateSynchronous_Usm_SharedRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyImmediateSynchronous_Usm_SharedRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyImmediateSynchronous_Usm_SharedRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyImmediateSynchronous_Usm_SharedRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyImmediateSynchronous_Shared_LocalRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyImmediateSynchronous_Shared_LocalRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.srcptr.count = srcptr ? (size) : 0;
    ret.srcptr.size = ret.srcptr.count;

    ret.phWaitEvents.offset = alignUpPow2<8>(ret.srcptr.offset + ret.srcptr.size);
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyImmediateSynchronous_Shared_LocalRpcM::Captures::getCaptureTotalSize() const {
     const auto lastMemberOffset = offsetPhWaitEvents;
     const auto lastMemberArraySize = this->countPhWaitEvents * sizeof(ze_event_handle_t);

     auto size = offsetof(Captures, dynMem) + Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

size_t ZeCommandListAppendMemoryCopyImmediateSynchronous_Shared_LocalRpcM::Captures::getCaptureDynMemSize() const {
     const auto lastMemberOffset = offsetPhWaitEvents;
     const auto lastMemberArraySize = this->countPhWaitEvents * sizeof(ze_event_handle_t);

     auto size = Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

ZeCommandListAppendMemoryCopyImmediateSynchronous_Shared_UsmRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyImmediateSynchronous_Shared_UsmRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyImmediateSynchronous_Shared_UsmRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyImmediateSynchronous_Shared_UsmRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyImmediateSynchronous_Shared_SharedRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyImmediateSynchronous_Shared_SharedRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyImmediateSynchronous_Shared_SharedRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyImmediateSynchronous_Shared_SharedRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyRegionDeferred_Usm_UsmRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyRegionDeferred_Usm_UsmRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyRegionDeferred_Usm_UsmRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyRegionDeferred_Usm_UsmRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyRegionDeferred_Usm_SharedRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyRegionDeferred_Usm_SharedRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyRegionDeferred_Usm_SharedRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyRegionDeferred_Usm_SharedRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyRegionDeferred_Usm_RemappedRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyRegionDeferred_Usm_RemappedRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyRegionDeferred_Usm_RemappedRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyRegionDeferred_Usm_RemappedRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyRegionDeferred_Shared_UsmRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyRegionDeferred_Shared_UsmRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyRegionDeferred_Shared_UsmRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyRegionDeferred_Shared_UsmRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyRegionDeferred_Shared_SharedRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyRegionDeferred_Shared_SharedRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyRegionDeferred_Shared_SharedRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyRegionDeferred_Shared_SharedRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyRegionDeferred_Shared_RemappedRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyRegionDeferred_Shared_RemappedRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyRegionDeferred_Shared_RemappedRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyRegionDeferred_Shared_RemappedRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyRegionDeferred_Remapped_UsmRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyRegionDeferred_Remapped_UsmRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyRegionDeferred_Remapped_UsmRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyRegionDeferred_Remapped_UsmRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyRegionDeferred_Remapped_SharedRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyRegionDeferred_Remapped_SharedRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyRegionDeferred_Remapped_SharedRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyRegionDeferred_Remapped_SharedRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyRegionDeferred_Remapped_RemappedRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyRegionDeferred_Remapped_RemappedRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyRegionDeferred_Remapped_RemappedRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyRegionDeferred_Remapped_RemappedRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyRegionImmediateSynchronous_Local_UsmRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyRegionImmediateSynchronous_Local_UsmRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.dstptr.count = dstptr ? (getTotalSizeForCopyRegion(dstRegion, dstPitch, dstSlicePitch)) : 0;
    ret.dstptr.size = ret.dstptr.count;

    ret.phWaitEvents.offset = alignUpPow2<8>(ret.dstptr.offset + ret.dstptr.size);
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyRegionImmediateSynchronous_Local_UsmRpcM::Captures::getCaptureTotalSize() const {
     const auto lastMemberOffset = offsetPhWaitEvents;
     const auto lastMemberArraySize = this->countPhWaitEvents * sizeof(ze_event_handle_t);

     auto size = offsetof(Captures, dynMem) + Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

size_t ZeCommandListAppendMemoryCopyRegionImmediateSynchronous_Local_UsmRpcM::Captures::getCaptureDynMemSize() const {
     const auto lastMemberOffset = offsetPhWaitEvents;
     const auto lastMemberArraySize = this->countPhWaitEvents * sizeof(ze_event_handle_t);

     auto size = Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

ZeCommandListAppendMemoryCopyRegionImmediateSynchronous_Local_SharedRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyRegionImmediateSynchronous_Local_SharedRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.dstptr.count = dstptr ? (getTotalSizeForCopyRegion(dstRegion, dstPitch, dstSlicePitch)) : 0;
    ret.dstptr.size = ret.dstptr.count;

    ret.phWaitEvents.offset = alignUpPow2<8>(ret.dstptr.offset + ret.dstptr.size);
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyRegionImmediateSynchronous_Local_SharedRpcM::Captures::getCaptureTotalSize() const {
     const auto lastMemberOffset = offsetPhWaitEvents;
     const auto lastMemberArraySize = this->countPhWaitEvents * sizeof(ze_event_handle_t);

     auto size = offsetof(Captures, dynMem) + Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

size_t ZeCommandListAppendMemoryCopyRegionImmediateSynchronous_Local_SharedRpcM::Captures::getCaptureDynMemSize() const {
     const auto lastMemberOffset = offsetPhWaitEvents;
     const auto lastMemberArraySize = this->countPhWaitEvents * sizeof(ze_event_handle_t);

     auto size = Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

ZeCommandListAppendMemoryCopyRegionImmediateSynchronous_Local_RemappedRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyRegionImmediateSynchronous_Local_RemappedRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.dstptr.count = dstptr ? (getTotalSizeForCopyRegion(dstRegion, dstPitch, dstSlicePitch)) : 0;
    ret.dstptr.size = ret.dstptr.count;

    ret.phWaitEvents.offset = alignUpPow2<8>(ret.dstptr.offset + ret.dstptr.size);
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyRegionImmediateSynchronous_Local_RemappedRpcM::Captures::getCaptureTotalSize() const {
     const auto lastMemberOffset = offsetPhWaitEvents;
     const auto lastMemberArraySize = this->countPhWaitEvents * sizeof(ze_event_handle_t);

     auto size = offsetof(Captures, dynMem) + Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

size_t ZeCommandListAppendMemoryCopyRegionImmediateSynchronous_Local_RemappedRpcM::Captures::getCaptureDynMemSize() const {
     const auto lastMemberOffset = offsetPhWaitEvents;
     const auto lastMemberArraySize = this->countPhWaitEvents * sizeof(ze_event_handle_t);

     auto size = Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

ZeCommandListAppendMemoryCopyRegionImmediateSynchronous_Usm_UsmRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyRegionImmediateSynchronous_Usm_UsmRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyRegionImmediateSynchronous_Usm_UsmRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyRegionImmediateSynchronous_Usm_UsmRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyRegionImmediateSynchronous_Usm_SharedRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyRegionImmediateSynchronous_Usm_SharedRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyRegionImmediateSynchronous_Usm_SharedRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyRegionImmediateSynchronous_Usm_SharedRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyRegionImmediateSynchronous_Usm_RemappedRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyRegionImmediateSynchronous_Usm_RemappedRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyRegionImmediateSynchronous_Usm_RemappedRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyRegionImmediateSynchronous_Usm_RemappedRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyRegionImmediateSynchronous_Shared_UsmRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyRegionImmediateSynchronous_Shared_UsmRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyRegionImmediateSynchronous_Shared_UsmRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyRegionImmediateSynchronous_Shared_UsmRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyRegionImmediateSynchronous_Shared_SharedRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyRegionImmediateSynchronous_Shared_SharedRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyRegionImmediateSynchronous_Shared_SharedRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyRegionImmediateSynchronous_Shared_SharedRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyRegionImmediateSynchronous_Shared_RemappedRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyRegionImmediateSynchronous_Shared_RemappedRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyRegionImmediateSynchronous_Shared_RemappedRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyRegionImmediateSynchronous_Shared_RemappedRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Local_UsmRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Local_UsmRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Local_UsmRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Local_UsmRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Local_SharedRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Local_SharedRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Local_SharedRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Local_SharedRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Local_RemappedRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Local_RemappedRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Local_RemappedRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Local_RemappedRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Usm_UsmRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Usm_UsmRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Usm_UsmRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Usm_UsmRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Usm_SharedRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Usm_SharedRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Usm_SharedRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Usm_SharedRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Usm_RemappedRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Usm_RemappedRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Usm_RemappedRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Usm_RemappedRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Shared_UsmRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Shared_UsmRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Shared_UsmRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Shared_UsmRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Shared_SharedRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Shared_SharedRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Shared_SharedRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Shared_SharedRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Shared_RemappedRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Shared_RemappedRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, const ze_copy_region_t* dstRegion, uint32_t dstPitch, uint32_t dstSlicePitch, const void* srcptr, const ze_copy_region_t* srcRegion, uint32_t srcPitch, uint32_t srcSlicePitch, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Shared_RemappedRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyRegionImmediateAsynchronous_Shared_RemappedRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyFromContextDeferred_Usm_UsmRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyFromContextDeferred_Usm_UsmRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyFromContextDeferred_Usm_UsmRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyFromContextDeferred_Usm_UsmRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyFromContextDeferred_Shared_UsmRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyFromContextDeferred_Shared_UsmRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyFromContextDeferred_Shared_UsmRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyFromContextDeferred_Shared_UsmRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyFromContextDeferred_Remapped_UsmRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyFromContextDeferred_Remapped_UsmRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyFromContextDeferred_Remapped_UsmRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyFromContextDeferred_Remapped_UsmRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyFromContextImmediateSynchronous_Local_UsmRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyFromContextImmediateSynchronous_Local_UsmRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.dstptr.count = dstptr ? (size) : 0;
    ret.dstptr.size = ret.dstptr.count;

    ret.phWaitEvents.offset = alignUpPow2<8>(ret.dstptr.offset + ret.dstptr.size);
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyFromContextImmediateSynchronous_Local_UsmRpcM::Captures::getCaptureTotalSize() const {
     const auto lastMemberOffset = offsetPhWaitEvents;
     const auto lastMemberArraySize = this->countPhWaitEvents * sizeof(ze_event_handle_t);

     auto size = offsetof(Captures, dynMem) + Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

size_t ZeCommandListAppendMemoryCopyFromContextImmediateSynchronous_Local_UsmRpcM::Captures::getCaptureDynMemSize() const {
     const auto lastMemberOffset = offsetPhWaitEvents;
     const auto lastMemberArraySize = this->countPhWaitEvents * sizeof(ze_event_handle_t);

     auto size = Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

ZeCommandListAppendMemoryCopyFromContextImmediateSynchronous_Usm_UsmRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyFromContextImmediateSynchronous_Usm_UsmRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyFromContextImmediateSynchronous_Usm_UsmRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyFromContextImmediateSynchronous_Usm_UsmRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyFromContextImmediateSynchronous_Shared_UsmRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyFromContextImmediateSynchronous_Shared_UsmRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyFromContextImmediateSynchronous_Shared_UsmRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyFromContextImmediateSynchronous_Shared_UsmRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyFromContextImmediateAsynchronous_Local_UsmRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyFromContextImmediateAsynchronous_Local_UsmRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyFromContextImmediateAsynchronous_Local_UsmRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyFromContextImmediateAsynchronous_Local_UsmRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyFromContextImmediateAsynchronous_Usm_UsmRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyFromContextImmediateAsynchronous_Usm_UsmRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyFromContextImmediateAsynchronous_Usm_UsmRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyFromContextImmediateAsynchronous_Usm_UsmRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

ZeCommandListAppendMemoryCopyFromContextImmediateAsynchronous_Shared_UsmRpcM::Captures::DynamicTraits ZeCommandListAppendMemoryCopyFromContextImmediateAsynchronous_Shared_UsmRpcM::Captures::DynamicTraits::calculate(ze_command_list_handle_t hCommandList, void* dstptr, ze_context_handle_t hContextSrc, const void* srcptr, size_t size, ze_event_handle_t hSignalEvent, uint32_t numWaitEvents, ze_event_handle_t* phWaitEvents) {
    DynamicTraits ret = {};
    ret.phWaitEvents.count = phWaitEvents ? (numWaitEvents) : 0;
    ret.phWaitEvents.size = ret.phWaitEvents.count * sizeof(ze_event_handle_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.phWaitEvents.offset + ret.phWaitEvents.size);


    return ret;
}

size_t ZeCommandListAppendMemoryCopyFromContextImmediateAsynchronous_Shared_UsmRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, phWaitEvents) + Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

size_t ZeCommandListAppendMemoryCopyFromContextImmediateAsynchronous_Shared_UsmRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPhWaitEvents * sizeof(ze_event_handle_t));
     return size;
}

} // namespace LevelZero
} // namespace Rpc
} // namespace Cal
// #### Generated code -- end ####
