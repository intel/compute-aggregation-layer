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
namespace Ocl {

inline std::vector<std::string> getListOfUnimplementedFunctionNames(){
    std::vector<std::string> ret;
    ret.push_back("clSetCommandQueueProperty");
    ret.push_back("clCreateFromGLBuffer");
    ret.push_back("clCreateFromGLTexture2D");
    ret.push_back("clCreateFromGLTexture3D");
    ret.push_back("clCreateFromGLRenderbuffer");
    ret.push_back("clGetGLObjectInfo");
    ret.push_back("clGetGLTextureInfo");
    ret.push_back("clEnqueueAcquireGLObjects");
    ret.push_back("clEnqueueReleaseGLObjects");
    ret.push_back("clGetGLContextInfoKHR");
    ret.push_back("clCreateEventFromGLsyncKHR");
    ret.push_back("clCreateFromGLTexture");
    ret.push_back("clCreateFromEGLImageKHR");
    ret.push_back("clEnqueueAcquireEGLObjectsKHR");
    ret.push_back("clEnqueueReleaseEGLObjectsKHR");
    ret.push_back("clCreateEventFromEGLSyncKHR");
    ret.push_back("clGetDeviceIDsFromD3D10KHR");
    ret.push_back("clCreateFromD3D10BufferKHR");
    ret.push_back("clCreateFromD3D10Texture2DKHR");
    ret.push_back("clCreateFromD3D10Texture3DKHR");
    ret.push_back("clEnqueueAcquireD3D10ObjectsKHR");
    ret.push_back("clEnqueueReleaseD3D10ObjectsKHR");
    ret.push_back("clGetDeviceIDsFromD3D11KHR");
    ret.push_back("clCreateFromD3D11BufferKHR");
    ret.push_back("clCreateFromD3D11Texture2DKHR");
    ret.push_back("clCreateFromD3D11Texture3DKHR");
    ret.push_back("clCreateFromDX9MediaSurfaceKHR");
    ret.push_back("clEnqueueAcquireD3D11ObjectsKHR");
    ret.push_back("clEnqueueReleaseD3D11ObjectsKHR");
    ret.push_back("clGetDeviceIDsFromDX9MediaAdapterKHR");
    ret.push_back("clEnqueueAcquireDX9MediaSurfacesKHR");
    ret.push_back("clEnqueueReleaseDX9MediaSurfacesKHR");
    ret.push_back("clEnqueueMapImage");
    ret.push_back("clEnqueueSVMFree");
    ret.push_back("clEnqueueNativeKernel");
    ret.push_back("clSetProgramReleaseCallback");
    ret.push_back("clSetContextDestructorCallback");
    ret.push_back("clSetMemObjectDestructorCallback");
    return ret;
}

} // namespae Ocl
} // namespae Apis
} // namespae Service
} // namespae Cal
// #### Generated code -- end ####
