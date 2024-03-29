/*
 * Copyright (C) 2022-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once
// #### Generated code -- begin ####

#include <string>
#include <vector>

namespace Cal {
namespace Service {
namespace Apis {
namespace LevelZero {

inline std::vector<std::string> getListOfUnimplementedFunctionNames(){
    std::vector<std::string> ret;
    ret.push_back("CommandList.zeCommandListAppendImageCopy");
    ret.push_back("CommandList.zeCommandListAppendImageCopyRegion");
    ret.push_back("CommandList.zeCommandListAppendImageCopyToMemory");
    ret.push_back("CommandList.zeCommandListAppendImageCopyFromMemory");
    ret.push_back("CommandList.zeCommandListAppendImageCopyToMemoryExt");
    ret.push_back("CommandList.zeCommandListAppendImageCopyFromMemoryExt");
    ret.push_back("ImageExp.zeImageGetMemoryPropertiesExp");
    ret.push_back("Image.zeImageGetAllocPropertiesExt");
    ret.push_back("ImageExp.zeImageViewCreateExp");
    ret.push_back("Context.zeContextMakeImageResident");
    ret.push_back("Context.zeContextEvictImage");
    ret.push_back("Sampler.zeSamplerCreate");
    ret.push_back("Sampler.zeSamplerDestroy");
    ret.push_back("Device.zesDeviceEnumFans");
    ret.push_back("Fan.zesFanGetProperties");
    ret.push_back("Fan.zesFanGetConfig");
    ret.push_back("Fan.zesFanSetDefaultMode");
    ret.push_back("Fan.zesFanSetFixedSpeedMode");
    ret.push_back("Fan.zesFanSetSpeedTableMode");
    ret.push_back("Fan.zesFanGetState");
    ret.push_back("Device.zesDeviceEnumFirmwares");
    ret.push_back("Firmware.zesFirmwareGetProperties");
    ret.push_back("Firmware.zesFirmwareFlash");
    ret.push_back("Device.zesDeviceEccAvailable");
    ret.push_back("Device.zesDeviceEccConfigurable");
    ret.push_back("Device.zesDeviceGetEccState");
    ret.push_back("Device.zesDeviceSetEccState");
    ret.push_back("Device.zesDeviceEnumLeds");
    ret.push_back("Led.zesLedGetProperties");
    ret.push_back("Led.zesLedGetState");
    ret.push_back("Led.zesLedSetState");
    ret.push_back("Led.zesLedSetColor");
    ret.push_back("Device.zesDeviceEnumFabricPorts");
    ret.push_back("FabricPort.zesFabricPortGetProperties");
    ret.push_back("FabricPort.zesFabricPortGetLinkType");
    ret.push_back("FabricPort.zesFabricPortGetConfig");
    ret.push_back("FabricPort.zesFabricPortSetConfig");
    ret.push_back("FabricPort.zesFabricPortGetState");
    ret.push_back("FabricPort.zesFabricPortGetThroughput");
    ret.push_back("Device.zesDeviceEnumDiagnosticTestSuites");
    ret.push_back("Diagnostics.zesDiagnosticsGetProperties");
    ret.push_back("Diagnostics.zesDiagnosticsGetTests");
    ret.push_back("Diagnostics.zesDiagnosticsRunTests");
    ret.push_back("Device.zesDeviceEnumPsus");
    ret.push_back("Psu.zesPsuGetProperties");
    ret.push_back("Psu.zesPsuGetState");
    ret.push_back("Debug.zetDebugAttach");
    ret.push_back("Debug.zetDebugDetach");
    ret.push_back("Debug.zetDebugReadEvent");
    ret.push_back("Debug.zetDebugAcknowledgeEvent");
    ret.push_back("Debug.zetDebugInterrupt");
    ret.push_back("Debug.zetDebugResume");
    ret.push_back("Debug.zetDebugReadMemory");
    ret.push_back("Debug.zetDebugWriteMemory");
    ret.push_back("Debug.zetDebugGetRegisterSetProperties");
    ret.push_back("Debug.zetDebugReadRegisters");
    ret.push_back("Debug.zetDebugWriteRegisters");
    ret.push_back("Module.zetModuleGetDebugInfo");
    return ret;
}

} // namespae LevelZero
} // namespae Apis
} // namespae Service
} // namespae Cal
// #### Generated code -- end ####
