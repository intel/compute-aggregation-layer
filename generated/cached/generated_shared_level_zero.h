/*
 * Copyright (C) 2022 Intel Corporation
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
    ret.push_back("CommandList.zeCommandListAppendMemoryRangesBarrier");
    ret.push_back("Context.zeContextSystemBarrier");
    ret.push_back("Device.zeDeviceReserveCacheExt");
    ret.push_back("Device.zeDeviceSetCacheAdviceExt");
    ret.push_back("CommandList.zeCommandListAppendWriteGlobalTimestamp");
    ret.push_back("CommandList.zeCommandListAppendMemoryCopyRegion");
    ret.push_back("CommandList.zeCommandListAppendMemoryCopyFromContext");
    ret.push_back("CommandList.zeCommandListAppendImageCopy");
    ret.push_back("CommandList.zeCommandListAppendImageCopyRegion");
    ret.push_back("CommandList.zeCommandListAppendImageCopyToMemory");
    ret.push_back("CommandList.zeCommandListAppendImageCopyFromMemory");
    ret.push_back("CommandList.zeCommandListAppendMemoryPrefetch");
    ret.push_back("CommandList.zeCommandListAppendMemAdvise");
    ret.push_back("Device.zeDeviceGetP2PProperties");
    ret.push_back("EventPool.zeEventPoolGetIpcHandle");
    ret.push_back("EventPool.zeEventPoolOpenIpcHandle");
    ret.push_back("EventPool.zeEventPoolCloseIpcHandle");
    ret.push_back("Event.zeEventHostSignal");
    ret.push_back("CommandList.zeCommandListAppendEventReset");
    ret.push_back("CommandList.zeCommandListAppendQueryKernelTimestamps");
    ret.push_back("EventExp.zeEventQueryTimestampsExp");
    ret.push_back("FabricVertexExp.zeFabricVertexGetExp");
    ret.push_back("FabricVertexExp.zeFabricVertexGetSubVerticesExp");
    ret.push_back("FabricVertexExp.zeFabricVertexGetPropertiesExp");
    ret.push_back("FabricVertexExp.zeFabricVertexGetDeviceExp");
    ret.push_back("DeviceExp.zeDeviceGetFabricVertexExp");
    ret.push_back("FabricEdgeExp.zeFabricEdgeGetExp");
    ret.push_back("FabricEdgeExp.zeFabricEdgeGetVerticesExp");
    ret.push_back("FabricEdgeExp.zeFabricEdgeGetPropertiesExp");
    ret.push_back("Image.zeImageGetProperties");
    ret.push_back("Image.zeImageCreate");
    ret.push_back("Image.zeImageDestroy");
    ret.push_back("CommandList.zeCommandListAppendImageCopyToMemoryExt");
    ret.push_back("CommandList.zeCommandListAppendImageCopyFromMemoryExt");
    ret.push_back("ImageExp.zeImageGetMemoryPropertiesExp");
    ret.push_back("Image.zeImageGetAllocPropertiesExt");
    ret.push_back("ImageExp.zeImageViewCreateExp");
    ret.push_back("KernelExp.zeKernelSchedulingHintExp");
    ret.push_back("Module.zeModuleInspectLinkageExt");
    ret.push_back("Mem.zeMemGetIpcHandle");
    ret.push_back("Mem.zeMemOpenIpcHandle");
    ret.push_back("Mem.zeMemCloseIpcHandle");
    ret.push_back("Mem.zeMemFreeExt");
    ret.push_back("Module.zeModuleDynamicLink");
    ret.push_back("Kernel.zeKernelGetSourceAttributes");
    ret.push_back("CommandList.zeCommandListAppendLaunchCooperativeKernel");
    ret.push_back("CommandList.zeCommandListAppendLaunchKernelIndirect");
    ret.push_back("CommandList.zeCommandListAppendLaunchMultipleKernelsIndirect");
    ret.push_back("Context.zeContextMakeMemoryResident");
    ret.push_back("Context.zeContextEvictMemory");
    ret.push_back("Context.zeContextMakeImageResident");
    ret.push_back("Context.zeContextEvictImage");
    ret.push_back("Sampler.zeSamplerCreate");
    ret.push_back("Sampler.zeSamplerDestroy");
    ret.push_back("VirtualMem.zeVirtualMemReserve");
    ret.push_back("VirtualMem.zeVirtualMemFree");
    ret.push_back("VirtualMem.zeVirtualMemQueryPageSize");
    ret.push_back("PhysicalMem.zePhysicalMemCreate");
    ret.push_back("PhysicalMem.zePhysicalMemDestroy");
    ret.push_back("VirtualMem.zeVirtualMemMap");
    ret.push_back("VirtualMem.zeVirtualMemUnmap");
    ret.push_back("VirtualMem.zeVirtualMemSetAccessAttribute");
    ret.push_back("VirtualMem.zeVirtualMemGetAccessAttribute");
    return ret;
}

} // namespae LevelZero
} // namespae Apis
} // namespae Service
} // namespae Cal
// #### Generated code -- end ####
