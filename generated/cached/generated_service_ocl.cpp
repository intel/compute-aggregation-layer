/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

// #### Generated code -- begin ####

#include "generated_service_ocl.h"

#include <shared/log.h>

#include <cassert>
#include <mutex>

namespace Cal {
namespace Service {
namespace Apis {
namespace Ocl {

namespace Standard {
cl_int (*clGetPlatformIDs)(cl_uint num_entries, cl_platform_id* platforms, cl_uint* num_platforms) = nullptr;
cl_int (*clGetPlatformInfo)(cl_platform_id platform, cl_platform_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) = nullptr;
void* (*clGetExtensionFunctionAddress)(const char* funcname) = nullptr;
cl_int (*clGetDeviceIDs)(cl_platform_id platform, cl_device_type device_type, cl_uint num_entries, cl_device_id* devices, cl_uint* num_devices) = nullptr;
cl_int (*clGetDeviceInfo)(cl_device_id device, cl_device_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) = nullptr;
cl_context (*clCreateContext)(const cl_context_properties* properties, cl_uint num_devices, const cl_device_id* devices, void (CL_CALLBACK* pfn_notify)(const char* errinfo, const void* private_info, size_t cb, void* user_data), void* user_data, cl_int* errcode_ret) = nullptr;
cl_context (*clCreateContextFromType)(const cl_context_properties* properties, cl_device_type device_type, void (CL_CALLBACK* pfn_notify)(const char* errinfo, const void* private_info, size_t cb, void* user_data), void* user_data, cl_int* errcode_ret) = nullptr;
cl_int (*clGetContextInfo)(cl_context context, cl_context_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) = nullptr;
cl_int (*clCreateSubDevices)(cl_device_id in_device, const cl_device_partition_property* properties, cl_uint num_devices, cl_device_id* out_devices, cl_uint* num_devices_ret) = nullptr;
cl_command_queue (*clCreateCommandQueue)(cl_context context, cl_device_id device, cl_command_queue_properties  properties, cl_int* errcode_ret) = nullptr;
cl_int (*clSetDefaultDeviceCommandQueue)(cl_context context, cl_device_id device, cl_command_queue command_queue) = nullptr;
cl_command_queue (*clCreateCommandQueueWithProperties)(cl_context context, cl_device_id device, const cl_queue_properties* properties, cl_int* errcode_ret) = nullptr;
cl_program (*clCreateProgramWithSource)(cl_context context, cl_uint count, const char** strings, const size_t* lengths, cl_int* errcode_ret) = nullptr;
cl_program (*clCreateProgramWithIL)(cl_context context, const void* il, size_t length, cl_int* errcode_ret) = nullptr;
cl_program (*clCreateProgramWithBinary)(cl_context context, cl_uint num_devices, const cl_device_id* device_list, const size_t* lengths, const unsigned char** binaries, cl_int* binary_status, cl_int* errcode_ret) = nullptr;
cl_program (*clCreateProgramWithBuiltInKernels)(cl_context context, cl_uint num_devices, const cl_device_id* device_list, const char* kernel_names, cl_int* errcode_ret) = nullptr;
cl_int (*clUnloadCompiler)() = nullptr;
cl_int (*clUnloadPlatformCompiler)(cl_platform_id platform) = nullptr;
cl_int (*clBuildProgram)(cl_program program, cl_uint num_devices, const cl_device_id* device_list, const char* options, void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data), void* user_data) = nullptr;
cl_int (*clCompileProgram)(cl_program program, cl_uint num_devices, const cl_device_id* device_list, const char* options, cl_uint num_input_headers, const cl_program* input_headers, const char** header_include_names, void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data), void* user_data) = nullptr;
cl_program (*clLinkProgram)(cl_context context, cl_uint num_devices, const cl_device_id* device_list, const char* options, cl_uint num_input_programs, const cl_program* input_programs, void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data), void* user_data, cl_int* errcode_ret) = nullptr;
cl_int (*clGetProgramBuildInfo)(cl_program program, cl_device_id device, cl_program_build_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) = nullptr;
cl_kernel (*clCreateKernel)(cl_program program, const char* kernel_name, cl_int* errcode_ret) = nullptr;
cl_kernel (*clCloneKernel)(cl_kernel source_kernel, cl_int* errcode_ret) = nullptr;
cl_int (*clCreateKernelsInProgram)(cl_program program, cl_uint num_kernels, cl_kernel* kernels, cl_uint* num_kernels_ret) = nullptr;
cl_int (*clGetCommandQueueInfo)(cl_command_queue command_queue, cl_command_queue_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) = nullptr;
cl_int (*clGetProgramInfo)(cl_program program, cl_program_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) = nullptr;
cl_int (*clGetMemObjectInfo)(cl_mem memobj, cl_mem_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) = nullptr;
cl_int (*clGetImageInfo)(cl_mem image, cl_image_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) = nullptr;
cl_int (*clGetSamplerInfo)(cl_sampler sampler, cl_sampler_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) = nullptr;
cl_int (*clGetKernelInfo)(cl_kernel kernel, cl_kernel_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) = nullptr;
cl_int (*clGetKernelWorkGroupInfo)(cl_kernel kernel, cl_device_id device, cl_kernel_work_group_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) = nullptr;
cl_int (*clGetKernelArgInfo)(cl_kernel kernel, cl_uint arg_indx, cl_kernel_arg_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) = nullptr;
cl_int (*clGetKernelSubGroupInfo)(cl_kernel kernel, cl_device_id device, cl_kernel_sub_group_info param_name, size_t input_value_size, const void* input_value, size_t param_value_size, void* param_value, size_t* param_value_size_ret) = nullptr;
cl_int (*clReleaseCommandQueue)(cl_command_queue command_queue) = nullptr;
cl_int (*clReleaseContext)(cl_context context) = nullptr;
cl_int (*clReleaseDevice)(cl_device_id device) = nullptr;
cl_int (*clReleaseKernel)(cl_kernel kernel) = nullptr;
cl_int (*clReleaseSampler)(cl_sampler sampler) = nullptr;
cl_int (*clReleaseProgram)(cl_program program) = nullptr;
cl_int (*clReleaseMemObject)(cl_mem memobj) = nullptr;
cl_int (*clReleaseEvent)(cl_event event) = nullptr;
cl_int (*clRetainCommandQueue)(cl_command_queue command_queue) = nullptr;
cl_int (*clRetainContext)(cl_context context) = nullptr;
cl_int (*clRetainDevice)(cl_device_id device) = nullptr;
cl_int (*clRetainProgram)(cl_program program) = nullptr;
cl_int (*clRetainMemObject)(cl_mem memobj) = nullptr;
cl_int (*clRetainSampler)(cl_sampler sampler) = nullptr;
cl_int (*clRetainKernel)(cl_kernel kernel) = nullptr;
cl_int (*clRetainEvent)(cl_event event) = nullptr;
cl_int (*clFlush)(cl_command_queue command_queue) = nullptr;
cl_int (*clFinish)(cl_command_queue command_queue) = nullptr;
cl_int (*clEnqueueNDRangeKernel)(cl_command_queue command_queue, cl_kernel kernel, cl_uint work_dim, const size_t* global_work_offset, const size_t* global_work_size, const size_t* local_work_size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) = nullptr;
cl_int (*clEnqueueTask)(cl_command_queue command_queue, cl_kernel kernel, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) = nullptr;
cl_int (*clEnqueueMarkerWithWaitList)(cl_command_queue command_queue, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) = nullptr;
cl_int (*clEnqueueMarker)(cl_command_queue command_queue, cl_event* event) = nullptr;
cl_int (*clEnqueueBarrierWithWaitList)(cl_command_queue command_queue, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) = nullptr;
cl_int (*clEnqueueBarrier)(cl_command_queue command_queue) = nullptr;
cl_int (*clEnqueueWaitForEvents)(cl_command_queue command_queue, cl_uint num_events, const cl_event* event_list) = nullptr;
cl_int (*clEnqueueMigrateMemObjects)(cl_command_queue command_queue, cl_uint num_mem_objects, const cl_mem* mem_objects, cl_mem_migration_flags flags, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) = nullptr;
void* (*clGetExtensionFunctionAddressForPlatform)(cl_platform_id platform, const char* funcname) = nullptr;
cl_mem (*clCreateBuffer)(cl_context context, cl_mem_flags flags, size_t size, void* host_ptr, cl_int* errcode_ret) = nullptr;
cl_mem (*clCreateSubBuffer)(cl_mem buffer, cl_mem_flags flags, cl_buffer_create_type buffer_create_type, const void* buffer_create_info, cl_int* errcode_ret) = nullptr;
cl_mem (*clCreatePipe)(cl_context context, cl_mem_flags flags, cl_uint pipe_packet_size, cl_uint pipe_max_packets, const cl_pipe_properties* properties, cl_int* errcode_ret) = nullptr;
cl_int (*clGetPipeInfo)(cl_mem pipe, cl_pipe_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) = nullptr;
cl_mem (*clCreateImage)(cl_context context, cl_mem_flags flags, const cl_image_format* image_format, const cl_image_desc* image_desc, void* host_ptr, cl_int* errcode_ret) = nullptr;
cl_mem (*clCreateImage2D)(cl_context context, cl_mem_flags flags, const cl_image_format* image_format, size_t image_width, size_t image_height, size_t image_row_pitch, void* host_ptr, cl_int* errcode_ret) = nullptr;
cl_mem (*clCreateImage3D)(cl_context context, cl_mem_flags flags, const cl_image_format* image_format, size_t image_width, size_t image_height, size_t image_depth, size_t image_row_pitch, size_t image_slice_pitch, void* host_ptr, cl_int* errcode_ret) = nullptr;
cl_sampler (*clCreateSampler)(cl_context context, cl_bool normalized_coords, cl_addressing_mode addressing_mode, cl_filter_mode filter_mode, cl_int* errcode_ret) = nullptr;
cl_sampler (*clCreateSamplerWithProperties)(cl_context context, const cl_sampler_properties* properties, cl_int* errcode_ret) = nullptr;
cl_mem (*clCreateImageWithProperties)(cl_context context, const cl_mem_properties* properties, cl_mem_flags flags, const cl_image_format* image_format, const cl_image_desc* image_desc, void* host_ptr, cl_int* errcode_ret) = nullptr;
cl_mem (*clCreateBufferWithProperties)(cl_context context, const cl_mem_properties* properties, cl_mem_flags flags, size_t size, void* host_ptr, cl_int* errcode_ret) = nullptr;
cl_int (*clGetSupportedImageFormats)(cl_context context, cl_mem_flags flags, cl_mem_object_type image_type, cl_uint num_entries, cl_image_format* image_formats, cl_uint* num_image_formats) = nullptr;
cl_int (*clSetKernelArg)(cl_kernel kernel, cl_uint arg_index, size_t arg_size, const void* arg_value) = nullptr;
cl_int (*clSetProgramSpecializationConstant)(cl_program program, cl_uint spec_id, size_t spec_size, const void* spec_value) = nullptr;
cl_int (*clEnqueueWriteBuffer)(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, size_t offset, size_t size, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) = nullptr;
cl_int (*clEnqueueWriteBufferRect)(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, const size_t* buffer_offset, const size_t* host_offset, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) = nullptr;
cl_int (*clEnqueueReadBuffer)(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, size_t offset, size_t size, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) = nullptr;
cl_int (*clEnqueueReadBufferRect)(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, const size_t* buffer_offset, const size_t* host_offset, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) = nullptr;
cl_int (*clEnqueueCopyBuffer)(cl_command_queue command_queue, cl_mem src_buffer, cl_mem dst_buffer, size_t src_offset, size_t dst_offset, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) = nullptr;
cl_int (*clEnqueueCopyBufferRect)(cl_command_queue command_queue, cl_mem src_buffer, cl_mem dst_buffer, const size_t* src_origin, const size_t* dst_origin, const size_t* region, size_t src_row_pitch, size_t src_slice_pitch, size_t dst_row_pitch, size_t dst_slice_pitch, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) = nullptr;
cl_int (*clEnqueueReadImage)(cl_command_queue command_queue, cl_mem image, cl_bool blocking_read, const size_t* src_origin, const size_t* region, size_t row_pitch, size_t slice_pitch, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) = nullptr;
cl_int (*clEnqueueWriteImage)(cl_command_queue command_queue, cl_mem image, cl_bool blocking_write, const size_t* origin, const size_t* region, size_t input_row_pitch, size_t input_slice_pitch, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) = nullptr;
cl_int (*clEnqueueCopyImage)(cl_command_queue command_queue, cl_mem src_image, cl_mem dst_image, const size_t* src_origin, const size_t* dst_origin, const size_t* region, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) = nullptr;
cl_int (*clEnqueueCopyImageToBuffer)(cl_command_queue command_queue, cl_mem src_image, cl_mem dst_buffer, const size_t* src_origin, const size_t* region, size_t dst_offset, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) = nullptr;
cl_int (*clEnqueueCopyBufferToImage)(cl_command_queue command_queue, cl_mem src_buffer, cl_mem dst_image, size_t src_offset, const size_t* dst_origin, const size_t* region, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) = nullptr;
void* (*clEnqueueMapBuffer)(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_map, cl_map_flags map_flags, size_t offset, size_t cb, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event, cl_int* errcode_ret) = nullptr;
cl_int (*clEnqueueUnmapMemObject)(cl_command_queue command_queue, cl_mem memobj, void* mapped_ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) = nullptr;
cl_int (*clEnqueueFillBuffer)(cl_command_queue command_queue, cl_mem memobj, const void* pattern, size_t patternSize, size_t offset, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) = nullptr;
cl_int (*clEnqueueFillImage)(cl_command_queue command_queue, cl_mem image, const void* fill_color, const size_t* origin, const size_t* region, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) = nullptr;
cl_int (*clWaitForEvents)(cl_uint num_events, const cl_event* event_list) = nullptr;
cl_int (*clGetEventInfo)(cl_event event, cl_event_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) = nullptr;
cl_int (*clGetEventProfilingInfo)(cl_event event, cl_profiling_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) = nullptr;
cl_event (*clCreateUserEvent)(cl_context context, cl_int* errcode_ret) = nullptr;
cl_int (*clSetUserEventStatus)(cl_event event, cl_int execution_status) = nullptr;
cl_int (*clSetEventCallback)(cl_event event, cl_int command_exec_callback_type, void (CL_CALLBACK* pfn_notify)(cl_event event, cl_int event_command_status, void *user_data), void* user_data) = nullptr;
cl_int (*clGetDeviceAndHostTimer)(cl_device_id device, cl_ulong* device_timestamp, cl_ulong* host_timestamp) = nullptr;
cl_int (*clGetHostTimer)(cl_device_id device, cl_ulong* host_timestamp) = nullptr;
void* (*clSVMAlloc)(cl_context context, cl_svm_mem_flags flags, size_t size, cl_uint alignment) = nullptr;
void (*clSVMFree)(cl_context context, void* ptr) = nullptr;
cl_int (*clEnqueueSVMMap)(cl_command_queue command_queue, cl_bool blocking_map, cl_map_flags map_flags, void* svm_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) = nullptr;
cl_int (*clEnqueueSVMUnmap)(cl_command_queue command_queue, void* svm_ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) = nullptr;
cl_int (*clSetKernelArgSVMPointer)(cl_kernel kernel, cl_uint argIndex, const void* argValue) = nullptr;
cl_int (*clSetKernelExecInfo)(cl_kernel kernel, cl_kernel_exec_info param_name, size_t param_value_size, const void* param_value) = nullptr;
cl_int (*clEnqueueSVMMemFill)(cl_command_queue command_queue, void* svm_ptr, const void* pattern, size_t patternSize, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) = nullptr;
cl_int (*clEnqueueSVMMigrateMem)(cl_command_queue command_queue, cl_uint num_svm_pointers, const void** svm_pointers, const size_t* sizes, cl_mem_migration_flags flags, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) = nullptr;
cl_int (*clEnqueueSVMMemcpy)(cl_command_queue command_queue, cl_bool blocking, void* dst_ptr, const void* src_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) = nullptr;

void *libraryHandle = nullptr;

bool loadOclLibrary(std::optional<std::string> path) {
    if(libraryHandle){
        return false == path.has_value();
    }
    
    std::string loadPath = path.value_or("libOpenCL.so");
    libraryHandle = dlopen(loadPath.c_str(), RTLD_NOW);
    
    if(nullptr == libraryHandle){
        loadPath = path.value_or("libOpenCL.so.1");
        libraryHandle = dlopen(loadPath.c_str(), RTLD_NOW);
    }

    if(nullptr == libraryHandle){
        return false;
    }
    
    clGetPlatformIDs = reinterpret_cast<decltype(clGetPlatformIDs)>(dlsym(libraryHandle, "clGetPlatformIDs"));
    if(nullptr == clGetPlatformIDs){
        log<Verbosity::error>("Missing symbol clGetPlatformIDs in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clGetPlatformInfo = reinterpret_cast<decltype(clGetPlatformInfo)>(dlsym(libraryHandle, "clGetPlatformInfo"));
    if(nullptr == clGetPlatformInfo){
        log<Verbosity::error>("Missing symbol clGetPlatformInfo in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clGetExtensionFunctionAddress = reinterpret_cast<decltype(clGetExtensionFunctionAddress)>(dlsym(libraryHandle, "clGetExtensionFunctionAddress"));
    if(nullptr == clGetExtensionFunctionAddress){
        log<Verbosity::error>("Missing symbol clGetExtensionFunctionAddress in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clGetDeviceIDs = reinterpret_cast<decltype(clGetDeviceIDs)>(dlsym(libraryHandle, "clGetDeviceIDs"));
    if(nullptr == clGetDeviceIDs){
        log<Verbosity::error>("Missing symbol clGetDeviceIDs in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clGetDeviceInfo = reinterpret_cast<decltype(clGetDeviceInfo)>(dlsym(libraryHandle, "clGetDeviceInfo"));
    if(nullptr == clGetDeviceInfo){
        log<Verbosity::error>("Missing symbol clGetDeviceInfo in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clCreateContext = reinterpret_cast<decltype(clCreateContext)>(dlsym(libraryHandle, "clCreateContext"));
    if(nullptr == clCreateContext){
        log<Verbosity::error>("Missing symbol clCreateContext in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clCreateContextFromType = reinterpret_cast<decltype(clCreateContextFromType)>(dlsym(libraryHandle, "clCreateContextFromType"));
    if(nullptr == clCreateContextFromType){
        log<Verbosity::error>("Missing symbol clCreateContextFromType in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clGetContextInfo = reinterpret_cast<decltype(clGetContextInfo)>(dlsym(libraryHandle, "clGetContextInfo"));
    if(nullptr == clGetContextInfo){
        log<Verbosity::error>("Missing symbol clGetContextInfo in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clCreateSubDevices = reinterpret_cast<decltype(clCreateSubDevices)>(dlsym(libraryHandle, "clCreateSubDevices"));
    if(nullptr == clCreateSubDevices){
        log<Verbosity::error>("Missing symbol clCreateSubDevices in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clCreateCommandQueue = reinterpret_cast<decltype(clCreateCommandQueue)>(dlsym(libraryHandle, "clCreateCommandQueue"));
    if(nullptr == clCreateCommandQueue){
        log<Verbosity::error>("Missing symbol clCreateCommandQueue in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clSetDefaultDeviceCommandQueue = reinterpret_cast<decltype(clSetDefaultDeviceCommandQueue)>(dlsym(libraryHandle, "clSetDefaultDeviceCommandQueue"));
    if(nullptr == clSetDefaultDeviceCommandQueue){
        log<Verbosity::error>("Missing symbol clSetDefaultDeviceCommandQueue in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clCreateCommandQueueWithProperties = reinterpret_cast<decltype(clCreateCommandQueueWithProperties)>(dlsym(libraryHandle, "clCreateCommandQueueWithProperties"));
    if(nullptr == clCreateCommandQueueWithProperties){
        log<Verbosity::error>("Missing symbol clCreateCommandQueueWithProperties in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clCreateProgramWithSource = reinterpret_cast<decltype(clCreateProgramWithSource)>(dlsym(libraryHandle, "clCreateProgramWithSource"));
    if(nullptr == clCreateProgramWithSource){
        log<Verbosity::error>("Missing symbol clCreateProgramWithSource in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clCreateProgramWithIL = reinterpret_cast<decltype(clCreateProgramWithIL)>(dlsym(libraryHandle, "clCreateProgramWithIL"));
    if(nullptr == clCreateProgramWithIL){
        log<Verbosity::error>("Missing symbol clCreateProgramWithIL in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clCreateProgramWithBinary = reinterpret_cast<decltype(clCreateProgramWithBinary)>(dlsym(libraryHandle, "clCreateProgramWithBinary"));
    if(nullptr == clCreateProgramWithBinary){
        log<Verbosity::error>("Missing symbol clCreateProgramWithBinary in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clCreateProgramWithBuiltInKernels = reinterpret_cast<decltype(clCreateProgramWithBuiltInKernels)>(dlsym(libraryHandle, "clCreateProgramWithBuiltInKernels"));
    if(nullptr == clCreateProgramWithBuiltInKernels){
        log<Verbosity::error>("Missing symbol clCreateProgramWithBuiltInKernels in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clUnloadCompiler = reinterpret_cast<decltype(clUnloadCompiler)>(dlsym(libraryHandle, "clUnloadCompiler"));
    if(nullptr == clUnloadCompiler){
        log<Verbosity::error>("Missing symbol clUnloadCompiler in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clUnloadPlatformCompiler = reinterpret_cast<decltype(clUnloadPlatformCompiler)>(dlsym(libraryHandle, "clUnloadPlatformCompiler"));
    if(nullptr == clUnloadPlatformCompiler){
        log<Verbosity::error>("Missing symbol clUnloadPlatformCompiler in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clBuildProgram = reinterpret_cast<decltype(clBuildProgram)>(dlsym(libraryHandle, "clBuildProgram"));
    if(nullptr == clBuildProgram){
        log<Verbosity::error>("Missing symbol clBuildProgram in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clCompileProgram = reinterpret_cast<decltype(clCompileProgram)>(dlsym(libraryHandle, "clCompileProgram"));
    if(nullptr == clCompileProgram){
        log<Verbosity::error>("Missing symbol clCompileProgram in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clLinkProgram = reinterpret_cast<decltype(clLinkProgram)>(dlsym(libraryHandle, "clLinkProgram"));
    if(nullptr == clLinkProgram){
        log<Verbosity::error>("Missing symbol clLinkProgram in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clGetProgramBuildInfo = reinterpret_cast<decltype(clGetProgramBuildInfo)>(dlsym(libraryHandle, "clGetProgramBuildInfo"));
    if(nullptr == clGetProgramBuildInfo){
        log<Verbosity::error>("Missing symbol clGetProgramBuildInfo in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clCreateKernel = reinterpret_cast<decltype(clCreateKernel)>(dlsym(libraryHandle, "clCreateKernel"));
    if(nullptr == clCreateKernel){
        log<Verbosity::error>("Missing symbol clCreateKernel in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clCloneKernel = reinterpret_cast<decltype(clCloneKernel)>(dlsym(libraryHandle, "clCloneKernel"));
    if(nullptr == clCloneKernel){
        log<Verbosity::error>("Missing symbol clCloneKernel in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clCreateKernelsInProgram = reinterpret_cast<decltype(clCreateKernelsInProgram)>(dlsym(libraryHandle, "clCreateKernelsInProgram"));
    if(nullptr == clCreateKernelsInProgram){
        log<Verbosity::error>("Missing symbol clCreateKernelsInProgram in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clGetCommandQueueInfo = reinterpret_cast<decltype(clGetCommandQueueInfo)>(dlsym(libraryHandle, "clGetCommandQueueInfo"));
    if(nullptr == clGetCommandQueueInfo){
        log<Verbosity::error>("Missing symbol clGetCommandQueueInfo in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clGetProgramInfo = reinterpret_cast<decltype(clGetProgramInfo)>(dlsym(libraryHandle, "clGetProgramInfo"));
    if(nullptr == clGetProgramInfo){
        log<Verbosity::error>("Missing symbol clGetProgramInfo in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clGetMemObjectInfo = reinterpret_cast<decltype(clGetMemObjectInfo)>(dlsym(libraryHandle, "clGetMemObjectInfo"));
    if(nullptr == clGetMemObjectInfo){
        log<Verbosity::error>("Missing symbol clGetMemObjectInfo in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clGetImageInfo = reinterpret_cast<decltype(clGetImageInfo)>(dlsym(libraryHandle, "clGetImageInfo"));
    if(nullptr == clGetImageInfo){
        log<Verbosity::error>("Missing symbol clGetImageInfo in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clGetSamplerInfo = reinterpret_cast<decltype(clGetSamplerInfo)>(dlsym(libraryHandle, "clGetSamplerInfo"));
    if(nullptr == clGetSamplerInfo){
        log<Verbosity::error>("Missing symbol clGetSamplerInfo in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clGetKernelInfo = reinterpret_cast<decltype(clGetKernelInfo)>(dlsym(libraryHandle, "clGetKernelInfo"));
    if(nullptr == clGetKernelInfo){
        log<Verbosity::error>("Missing symbol clGetKernelInfo in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clGetKernelWorkGroupInfo = reinterpret_cast<decltype(clGetKernelWorkGroupInfo)>(dlsym(libraryHandle, "clGetKernelWorkGroupInfo"));
    if(nullptr == clGetKernelWorkGroupInfo){
        log<Verbosity::error>("Missing symbol clGetKernelWorkGroupInfo in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clGetKernelArgInfo = reinterpret_cast<decltype(clGetKernelArgInfo)>(dlsym(libraryHandle, "clGetKernelArgInfo"));
    if(nullptr == clGetKernelArgInfo){
        log<Verbosity::error>("Missing symbol clGetKernelArgInfo in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clGetKernelSubGroupInfo = reinterpret_cast<decltype(clGetKernelSubGroupInfo)>(dlsym(libraryHandle, "clGetKernelSubGroupInfo"));
    if(nullptr == clGetKernelSubGroupInfo){
        log<Verbosity::error>("Missing symbol clGetKernelSubGroupInfo in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clReleaseCommandQueue = reinterpret_cast<decltype(clReleaseCommandQueue)>(dlsym(libraryHandle, "clReleaseCommandQueue"));
    if(nullptr == clReleaseCommandQueue){
        log<Verbosity::error>("Missing symbol clReleaseCommandQueue in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clReleaseContext = reinterpret_cast<decltype(clReleaseContext)>(dlsym(libraryHandle, "clReleaseContext"));
    if(nullptr == clReleaseContext){
        log<Verbosity::error>("Missing symbol clReleaseContext in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clReleaseDevice = reinterpret_cast<decltype(clReleaseDevice)>(dlsym(libraryHandle, "clReleaseDevice"));
    if(nullptr == clReleaseDevice){
        log<Verbosity::error>("Missing symbol clReleaseDevice in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clReleaseKernel = reinterpret_cast<decltype(clReleaseKernel)>(dlsym(libraryHandle, "clReleaseKernel"));
    if(nullptr == clReleaseKernel){
        log<Verbosity::error>("Missing symbol clReleaseKernel in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clReleaseSampler = reinterpret_cast<decltype(clReleaseSampler)>(dlsym(libraryHandle, "clReleaseSampler"));
    if(nullptr == clReleaseSampler){
        log<Verbosity::error>("Missing symbol clReleaseSampler in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clReleaseProgram = reinterpret_cast<decltype(clReleaseProgram)>(dlsym(libraryHandle, "clReleaseProgram"));
    if(nullptr == clReleaseProgram){
        log<Verbosity::error>("Missing symbol clReleaseProgram in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clReleaseMemObject = reinterpret_cast<decltype(clReleaseMemObject)>(dlsym(libraryHandle, "clReleaseMemObject"));
    if(nullptr == clReleaseMemObject){
        log<Verbosity::error>("Missing symbol clReleaseMemObject in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clReleaseEvent = reinterpret_cast<decltype(clReleaseEvent)>(dlsym(libraryHandle, "clReleaseEvent"));
    if(nullptr == clReleaseEvent){
        log<Verbosity::error>("Missing symbol clReleaseEvent in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clRetainCommandQueue = reinterpret_cast<decltype(clRetainCommandQueue)>(dlsym(libraryHandle, "clRetainCommandQueue"));
    if(nullptr == clRetainCommandQueue){
        log<Verbosity::error>("Missing symbol clRetainCommandQueue in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clRetainContext = reinterpret_cast<decltype(clRetainContext)>(dlsym(libraryHandle, "clRetainContext"));
    if(nullptr == clRetainContext){
        log<Verbosity::error>("Missing symbol clRetainContext in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clRetainDevice = reinterpret_cast<decltype(clRetainDevice)>(dlsym(libraryHandle, "clRetainDevice"));
    if(nullptr == clRetainDevice){
        log<Verbosity::error>("Missing symbol clRetainDevice in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clRetainProgram = reinterpret_cast<decltype(clRetainProgram)>(dlsym(libraryHandle, "clRetainProgram"));
    if(nullptr == clRetainProgram){
        log<Verbosity::error>("Missing symbol clRetainProgram in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clRetainMemObject = reinterpret_cast<decltype(clRetainMemObject)>(dlsym(libraryHandle, "clRetainMemObject"));
    if(nullptr == clRetainMemObject){
        log<Verbosity::error>("Missing symbol clRetainMemObject in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clRetainSampler = reinterpret_cast<decltype(clRetainSampler)>(dlsym(libraryHandle, "clRetainSampler"));
    if(nullptr == clRetainSampler){
        log<Verbosity::error>("Missing symbol clRetainSampler in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clRetainKernel = reinterpret_cast<decltype(clRetainKernel)>(dlsym(libraryHandle, "clRetainKernel"));
    if(nullptr == clRetainKernel){
        log<Verbosity::error>("Missing symbol clRetainKernel in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clRetainEvent = reinterpret_cast<decltype(clRetainEvent)>(dlsym(libraryHandle, "clRetainEvent"));
    if(nullptr == clRetainEvent){
        log<Verbosity::error>("Missing symbol clRetainEvent in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clFlush = reinterpret_cast<decltype(clFlush)>(dlsym(libraryHandle, "clFlush"));
    if(nullptr == clFlush){
        log<Verbosity::error>("Missing symbol clFlush in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clFinish = reinterpret_cast<decltype(clFinish)>(dlsym(libraryHandle, "clFinish"));
    if(nullptr == clFinish){
        log<Verbosity::error>("Missing symbol clFinish in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clEnqueueNDRangeKernel = reinterpret_cast<decltype(clEnqueueNDRangeKernel)>(dlsym(libraryHandle, "clEnqueueNDRangeKernel"));
    if(nullptr == clEnqueueNDRangeKernel){
        log<Verbosity::error>("Missing symbol clEnqueueNDRangeKernel in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clEnqueueTask = reinterpret_cast<decltype(clEnqueueTask)>(dlsym(libraryHandle, "clEnqueueTask"));
    if(nullptr == clEnqueueTask){
        log<Verbosity::error>("Missing symbol clEnqueueTask in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clEnqueueMarkerWithWaitList = reinterpret_cast<decltype(clEnqueueMarkerWithWaitList)>(dlsym(libraryHandle, "clEnqueueMarkerWithWaitList"));
    if(nullptr == clEnqueueMarkerWithWaitList){
        log<Verbosity::error>("Missing symbol clEnqueueMarkerWithWaitList in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clEnqueueMarker = reinterpret_cast<decltype(clEnqueueMarker)>(dlsym(libraryHandle, "clEnqueueMarker"));
    if(nullptr == clEnqueueMarker){
        log<Verbosity::error>("Missing symbol clEnqueueMarker in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clEnqueueBarrierWithWaitList = reinterpret_cast<decltype(clEnqueueBarrierWithWaitList)>(dlsym(libraryHandle, "clEnqueueBarrierWithWaitList"));
    if(nullptr == clEnqueueBarrierWithWaitList){
        log<Verbosity::error>("Missing symbol clEnqueueBarrierWithWaitList in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clEnqueueBarrier = reinterpret_cast<decltype(clEnqueueBarrier)>(dlsym(libraryHandle, "clEnqueueBarrier"));
    if(nullptr == clEnqueueBarrier){
        log<Verbosity::error>("Missing symbol clEnqueueBarrier in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clEnqueueWaitForEvents = reinterpret_cast<decltype(clEnqueueWaitForEvents)>(dlsym(libraryHandle, "clEnqueueWaitForEvents"));
    if(nullptr == clEnqueueWaitForEvents){
        log<Verbosity::error>("Missing symbol clEnqueueWaitForEvents in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clEnqueueMigrateMemObjects = reinterpret_cast<decltype(clEnqueueMigrateMemObjects)>(dlsym(libraryHandle, "clEnqueueMigrateMemObjects"));
    if(nullptr == clEnqueueMigrateMemObjects){
        log<Verbosity::error>("Missing symbol clEnqueueMigrateMemObjects in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clGetExtensionFunctionAddressForPlatform = reinterpret_cast<decltype(clGetExtensionFunctionAddressForPlatform)>(dlsym(libraryHandle, "clGetExtensionFunctionAddressForPlatform"));
    if(nullptr == clGetExtensionFunctionAddressForPlatform){
        log<Verbosity::error>("Missing symbol clGetExtensionFunctionAddressForPlatform in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clCreateBuffer = reinterpret_cast<decltype(clCreateBuffer)>(dlsym(libraryHandle, "clCreateBuffer"));
    if(nullptr == clCreateBuffer){
        log<Verbosity::error>("Missing symbol clCreateBuffer in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clCreateSubBuffer = reinterpret_cast<decltype(clCreateSubBuffer)>(dlsym(libraryHandle, "clCreateSubBuffer"));
    if(nullptr == clCreateSubBuffer){
        log<Verbosity::error>("Missing symbol clCreateSubBuffer in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clCreatePipe = reinterpret_cast<decltype(clCreatePipe)>(dlsym(libraryHandle, "clCreatePipe"));
    if(nullptr == clCreatePipe){
        log<Verbosity::error>("Missing symbol clCreatePipe in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clGetPipeInfo = reinterpret_cast<decltype(clGetPipeInfo)>(dlsym(libraryHandle, "clGetPipeInfo"));
    if(nullptr == clGetPipeInfo){
        log<Verbosity::error>("Missing symbol clGetPipeInfo in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clCreateImage = reinterpret_cast<decltype(clCreateImage)>(dlsym(libraryHandle, "clCreateImage"));
    if(nullptr == clCreateImage){
        log<Verbosity::error>("Missing symbol clCreateImage in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clCreateImage2D = reinterpret_cast<decltype(clCreateImage2D)>(dlsym(libraryHandle, "clCreateImage2D"));
    if(nullptr == clCreateImage2D){
        log<Verbosity::error>("Missing symbol clCreateImage2D in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clCreateImage3D = reinterpret_cast<decltype(clCreateImage3D)>(dlsym(libraryHandle, "clCreateImage3D"));
    if(nullptr == clCreateImage3D){
        log<Verbosity::error>("Missing symbol clCreateImage3D in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clCreateSampler = reinterpret_cast<decltype(clCreateSampler)>(dlsym(libraryHandle, "clCreateSampler"));
    if(nullptr == clCreateSampler){
        log<Verbosity::error>("Missing symbol clCreateSampler in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clCreateSamplerWithProperties = reinterpret_cast<decltype(clCreateSamplerWithProperties)>(dlsym(libraryHandle, "clCreateSamplerWithProperties"));
    if(nullptr == clCreateSamplerWithProperties){
        log<Verbosity::debug>("Missing symbol clCreateSamplerWithProperties in %s", loadPath.c_str());
    }
    clCreateImageWithProperties = reinterpret_cast<decltype(clCreateImageWithProperties)>(dlsym(libraryHandle, "clCreateImageWithProperties"));
    if(nullptr == clCreateImageWithProperties){
        log<Verbosity::debug>("Missing symbol clCreateImageWithProperties in %s", loadPath.c_str());
    }
    clCreateBufferWithProperties = reinterpret_cast<decltype(clCreateBufferWithProperties)>(dlsym(libraryHandle, "clCreateBufferWithProperties"));
    if(nullptr == clCreateBufferWithProperties){
        log<Verbosity::debug>("Missing symbol clCreateBufferWithProperties in %s", loadPath.c_str());
    }
    clGetSupportedImageFormats = reinterpret_cast<decltype(clGetSupportedImageFormats)>(dlsym(libraryHandle, "clGetSupportedImageFormats"));
    if(nullptr == clGetSupportedImageFormats){
        log<Verbosity::error>("Missing symbol clGetSupportedImageFormats in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clSetKernelArg = reinterpret_cast<decltype(clSetKernelArg)>(dlsym(libraryHandle, "clSetKernelArg"));
    if(nullptr == clSetKernelArg){
        log<Verbosity::error>("Missing symbol clSetKernelArg in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clSetProgramSpecializationConstant = reinterpret_cast<decltype(clSetProgramSpecializationConstant)>(dlsym(libraryHandle, "clSetProgramSpecializationConstant"));
    if(nullptr == clSetProgramSpecializationConstant){
        log<Verbosity::debug>("Missing symbol clSetProgramSpecializationConstant in %s", loadPath.c_str());
    }
    clEnqueueWriteBuffer = reinterpret_cast<decltype(clEnqueueWriteBuffer)>(dlsym(libraryHandle, "clEnqueueWriteBuffer"));
    if(nullptr == clEnqueueWriteBuffer){
        log<Verbosity::error>("Missing symbol clEnqueueWriteBuffer in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clEnqueueWriteBufferRect = reinterpret_cast<decltype(clEnqueueWriteBufferRect)>(dlsym(libraryHandle, "clEnqueueWriteBufferRect"));
    if(nullptr == clEnqueueWriteBufferRect){
        log<Verbosity::error>("Missing symbol clEnqueueWriteBufferRect in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clEnqueueReadBuffer = reinterpret_cast<decltype(clEnqueueReadBuffer)>(dlsym(libraryHandle, "clEnqueueReadBuffer"));
    if(nullptr == clEnqueueReadBuffer){
        log<Verbosity::error>("Missing symbol clEnqueueReadBuffer in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clEnqueueReadBufferRect = reinterpret_cast<decltype(clEnqueueReadBufferRect)>(dlsym(libraryHandle, "clEnqueueReadBufferRect"));
    if(nullptr == clEnqueueReadBufferRect){
        log<Verbosity::error>("Missing symbol clEnqueueReadBufferRect in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clEnqueueCopyBuffer = reinterpret_cast<decltype(clEnqueueCopyBuffer)>(dlsym(libraryHandle, "clEnqueueCopyBuffer"));
    if(nullptr == clEnqueueCopyBuffer){
        log<Verbosity::error>("Missing symbol clEnqueueCopyBuffer in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clEnqueueCopyBufferRect = reinterpret_cast<decltype(clEnqueueCopyBufferRect)>(dlsym(libraryHandle, "clEnqueueCopyBufferRect"));
    if(nullptr == clEnqueueCopyBufferRect){
        log<Verbosity::error>("Missing symbol clEnqueueCopyBufferRect in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clEnqueueReadImage = reinterpret_cast<decltype(clEnqueueReadImage)>(dlsym(libraryHandle, "clEnqueueReadImage"));
    if(nullptr == clEnqueueReadImage){
        log<Verbosity::error>("Missing symbol clEnqueueReadImage in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clEnqueueWriteImage = reinterpret_cast<decltype(clEnqueueWriteImage)>(dlsym(libraryHandle, "clEnqueueWriteImage"));
    if(nullptr == clEnqueueWriteImage){
        log<Verbosity::error>("Missing symbol clEnqueueWriteImage in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clEnqueueCopyImage = reinterpret_cast<decltype(clEnqueueCopyImage)>(dlsym(libraryHandle, "clEnqueueCopyImage"));
    if(nullptr == clEnqueueCopyImage){
        log<Verbosity::error>("Missing symbol clEnqueueCopyImage in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clEnqueueCopyImageToBuffer = reinterpret_cast<decltype(clEnqueueCopyImageToBuffer)>(dlsym(libraryHandle, "clEnqueueCopyImageToBuffer"));
    if(nullptr == clEnqueueCopyImageToBuffer){
        log<Verbosity::error>("Missing symbol clEnqueueCopyImageToBuffer in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clEnqueueCopyBufferToImage = reinterpret_cast<decltype(clEnqueueCopyBufferToImage)>(dlsym(libraryHandle, "clEnqueueCopyBufferToImage"));
    if(nullptr == clEnqueueCopyBufferToImage){
        log<Verbosity::error>("Missing symbol clEnqueueCopyBufferToImage in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clEnqueueMapBuffer = reinterpret_cast<decltype(clEnqueueMapBuffer)>(dlsym(libraryHandle, "clEnqueueMapBuffer"));
    if(nullptr == clEnqueueMapBuffer){
        log<Verbosity::error>("Missing symbol clEnqueueMapBuffer in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clEnqueueUnmapMemObject = reinterpret_cast<decltype(clEnqueueUnmapMemObject)>(dlsym(libraryHandle, "clEnqueueUnmapMemObject"));
    if(nullptr == clEnqueueUnmapMemObject){
        log<Verbosity::error>("Missing symbol clEnqueueUnmapMemObject in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clEnqueueFillBuffer = reinterpret_cast<decltype(clEnqueueFillBuffer)>(dlsym(libraryHandle, "clEnqueueFillBuffer"));
    if(nullptr == clEnqueueFillBuffer){
        log<Verbosity::error>("Missing symbol clEnqueueFillBuffer in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clEnqueueFillImage = reinterpret_cast<decltype(clEnqueueFillImage)>(dlsym(libraryHandle, "clEnqueueFillImage"));
    if(nullptr == clEnqueueFillImage){
        log<Verbosity::error>("Missing symbol clEnqueueFillImage in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clWaitForEvents = reinterpret_cast<decltype(clWaitForEvents)>(dlsym(libraryHandle, "clWaitForEvents"));
    if(nullptr == clWaitForEvents){
        log<Verbosity::error>("Missing symbol clWaitForEvents in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clGetEventInfo = reinterpret_cast<decltype(clGetEventInfo)>(dlsym(libraryHandle, "clGetEventInfo"));
    if(nullptr == clGetEventInfo){
        log<Verbosity::error>("Missing symbol clGetEventInfo in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clGetEventProfilingInfo = reinterpret_cast<decltype(clGetEventProfilingInfo)>(dlsym(libraryHandle, "clGetEventProfilingInfo"));
    if(nullptr == clGetEventProfilingInfo){
        log<Verbosity::error>("Missing symbol clGetEventProfilingInfo in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clCreateUserEvent = reinterpret_cast<decltype(clCreateUserEvent)>(dlsym(libraryHandle, "clCreateUserEvent"));
    if(nullptr == clCreateUserEvent){
        log<Verbosity::error>("Missing symbol clCreateUserEvent in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clSetUserEventStatus = reinterpret_cast<decltype(clSetUserEventStatus)>(dlsym(libraryHandle, "clSetUserEventStatus"));
    if(nullptr == clSetUserEventStatus){
        log<Verbosity::error>("Missing symbol clSetUserEventStatus in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clSetEventCallback = reinterpret_cast<decltype(clSetEventCallback)>(dlsym(libraryHandle, "clSetEventCallback"));
    if(nullptr == clSetEventCallback){
        log<Verbosity::error>("Missing symbol clSetEventCallback in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clGetDeviceAndHostTimer = reinterpret_cast<decltype(clGetDeviceAndHostTimer)>(dlsym(libraryHandle, "clGetDeviceAndHostTimer"));
    if(nullptr == clGetDeviceAndHostTimer){
        log<Verbosity::error>("Missing symbol clGetDeviceAndHostTimer in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clGetHostTimer = reinterpret_cast<decltype(clGetHostTimer)>(dlsym(libraryHandle, "clGetHostTimer"));
    if(nullptr == clGetHostTimer){
        log<Verbosity::error>("Missing symbol clGetHostTimer in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clSVMAlloc = reinterpret_cast<decltype(clSVMAlloc)>(dlsym(libraryHandle, "clSVMAlloc"));
    if(nullptr == clSVMAlloc){
        log<Verbosity::error>("Missing symbol clSVMAlloc in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clSVMFree = reinterpret_cast<decltype(clSVMFree)>(dlsym(libraryHandle, "clSVMFree"));
    if(nullptr == clSVMFree){
        log<Verbosity::error>("Missing symbol clSVMFree in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clEnqueueSVMMap = reinterpret_cast<decltype(clEnqueueSVMMap)>(dlsym(libraryHandle, "clEnqueueSVMMap"));
    if(nullptr == clEnqueueSVMMap){
        log<Verbosity::error>("Missing symbol clEnqueueSVMMap in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clEnqueueSVMUnmap = reinterpret_cast<decltype(clEnqueueSVMUnmap)>(dlsym(libraryHandle, "clEnqueueSVMUnmap"));
    if(nullptr == clEnqueueSVMUnmap){
        log<Verbosity::error>("Missing symbol clEnqueueSVMUnmap in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clSetKernelArgSVMPointer = reinterpret_cast<decltype(clSetKernelArgSVMPointer)>(dlsym(libraryHandle, "clSetKernelArgSVMPointer"));
    if(nullptr == clSetKernelArgSVMPointer){
        log<Verbosity::error>("Missing symbol clSetKernelArgSVMPointer in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clSetKernelExecInfo = reinterpret_cast<decltype(clSetKernelExecInfo)>(dlsym(libraryHandle, "clSetKernelExecInfo"));
    if(nullptr == clSetKernelExecInfo){
        log<Verbosity::error>("Missing symbol clSetKernelExecInfo in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clEnqueueSVMMemFill = reinterpret_cast<decltype(clEnqueueSVMMemFill)>(dlsym(libraryHandle, "clEnqueueSVMMemFill"));
    if(nullptr == clEnqueueSVMMemFill){
        log<Verbosity::error>("Missing symbol clEnqueueSVMMemFill in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clEnqueueSVMMigrateMem = reinterpret_cast<decltype(clEnqueueSVMMigrateMem)>(dlsym(libraryHandle, "clEnqueueSVMMigrateMem"));
    if(nullptr == clEnqueueSVMMigrateMem){
        log<Verbosity::error>("Missing symbol clEnqueueSVMMigrateMem in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    clEnqueueSVMMemcpy = reinterpret_cast<decltype(clEnqueueSVMMemcpy)>(dlsym(libraryHandle, "clEnqueueSVMMemcpy"));
    if(nullptr == clEnqueueSVMMemcpy){
        log<Verbosity::error>("Missing symbol clEnqueueSVMMemcpy in %s", loadPath.c_str());
        unloadOclLibrary();
        return false;
    }
    return true;
}

void unloadOclLibrary() {
    clGetPlatformIDs = nullptr;
    clGetPlatformInfo = nullptr;
    clGetExtensionFunctionAddress = nullptr;
    clGetDeviceIDs = nullptr;
    clGetDeviceInfo = nullptr;
    clCreateContext = nullptr;
    clCreateContextFromType = nullptr;
    clGetContextInfo = nullptr;
    clCreateSubDevices = nullptr;
    clCreateCommandQueue = nullptr;
    clSetDefaultDeviceCommandQueue = nullptr;
    clCreateCommandQueueWithProperties = nullptr;
    clCreateProgramWithSource = nullptr;
    clCreateProgramWithIL = nullptr;
    clCreateProgramWithBinary = nullptr;
    clCreateProgramWithBuiltInKernels = nullptr;
    clUnloadCompiler = nullptr;
    clUnloadPlatformCompiler = nullptr;
    clBuildProgram = nullptr;
    clCompileProgram = nullptr;
    clLinkProgram = nullptr;
    clGetProgramBuildInfo = nullptr;
    clCreateKernel = nullptr;
    clCloneKernel = nullptr;
    clCreateKernelsInProgram = nullptr;
    clGetCommandQueueInfo = nullptr;
    clGetProgramInfo = nullptr;
    clGetMemObjectInfo = nullptr;
    clGetImageInfo = nullptr;
    clGetSamplerInfo = nullptr;
    clGetKernelInfo = nullptr;
    clGetKernelWorkGroupInfo = nullptr;
    clGetKernelArgInfo = nullptr;
    clGetKernelSubGroupInfo = nullptr;
    clReleaseCommandQueue = nullptr;
    clReleaseContext = nullptr;
    clReleaseDevice = nullptr;
    clReleaseKernel = nullptr;
    clReleaseSampler = nullptr;
    clReleaseProgram = nullptr;
    clReleaseMemObject = nullptr;
    clReleaseEvent = nullptr;
    clRetainCommandQueue = nullptr;
    clRetainContext = nullptr;
    clRetainDevice = nullptr;
    clRetainProgram = nullptr;
    clRetainMemObject = nullptr;
    clRetainSampler = nullptr;
    clRetainKernel = nullptr;
    clRetainEvent = nullptr;
    clFlush = nullptr;
    clFinish = nullptr;
    clEnqueueNDRangeKernel = nullptr;
    clEnqueueTask = nullptr;
    clEnqueueMarkerWithWaitList = nullptr;
    clEnqueueMarker = nullptr;
    clEnqueueBarrierWithWaitList = nullptr;
    clEnqueueBarrier = nullptr;
    clEnqueueWaitForEvents = nullptr;
    clEnqueueMigrateMemObjects = nullptr;
    clGetExtensionFunctionAddressForPlatform = nullptr;
    clCreateBuffer = nullptr;
    clCreateSubBuffer = nullptr;
    clCreatePipe = nullptr;
    clGetPipeInfo = nullptr;
    clCreateImage = nullptr;
    clCreateImage2D = nullptr;
    clCreateImage3D = nullptr;
    clCreateSampler = nullptr;
    clCreateSamplerWithProperties = nullptr;
    clCreateImageWithProperties = nullptr;
    clCreateBufferWithProperties = nullptr;
    clGetSupportedImageFormats = nullptr;
    clSetKernelArg = nullptr;
    clSetProgramSpecializationConstant = nullptr;
    clEnqueueWriteBuffer = nullptr;
    clEnqueueWriteBufferRect = nullptr;
    clEnqueueReadBuffer = nullptr;
    clEnqueueReadBufferRect = nullptr;
    clEnqueueCopyBuffer = nullptr;
    clEnqueueCopyBufferRect = nullptr;
    clEnqueueReadImage = nullptr;
    clEnqueueWriteImage = nullptr;
    clEnqueueCopyImage = nullptr;
    clEnqueueCopyImageToBuffer = nullptr;
    clEnqueueCopyBufferToImage = nullptr;
    clEnqueueMapBuffer = nullptr;
    clEnqueueUnmapMemObject = nullptr;
    clEnqueueFillBuffer = nullptr;
    clEnqueueFillImage = nullptr;
    clWaitForEvents = nullptr;
    clGetEventInfo = nullptr;
    clGetEventProfilingInfo = nullptr;
    clCreateUserEvent = nullptr;
    clSetUserEventStatus = nullptr;
    clSetEventCallback = nullptr;
    clGetDeviceAndHostTimer = nullptr;
    clGetHostTimer = nullptr;
    clSVMAlloc = nullptr;
    clSVMFree = nullptr;
    clEnqueueSVMMap = nullptr;
    clEnqueueSVMUnmap = nullptr;
    clSetKernelArgSVMPointer = nullptr;
    clSetKernelExecInfo = nullptr;
    clEnqueueSVMMemFill = nullptr;
    clEnqueueSVMMigrateMem = nullptr;
    clEnqueueSVMMemcpy = nullptr;
    if(libraryHandle){
        dlclose(libraryHandle);
    }
    libraryHandle = nullptr;
}

bool isOclLibraryLoaded() {
    return nullptr != libraryHandle;
}

} // namespace Standard

namespace Extensions {
namespace LazyLoad {
cl_int clCreateSubDevicesEXTLoad(cl_device_id in_device, const cl_device_partition_property_ext* properties, cl_uint num_entries, cl_device_id* out_devices, cl_uint* num_devices){
    using ExtFuncT = decltype(clCreateSubDevicesEXTLoad);
    static ExtFuncT *extAddr = reinterpret_cast<ExtFuncT*>(Cal::Service::Apis::Ocl::getExtensionFuncAddress("clCreateSubDevicesEXT"));
    if(nullptr == extAddr){
        log<Verbosity::error>("Client requested for unavailable extension function rpc : clCreateSubDevicesEXT");
        assert(false);
        return {};
    }
    Cal::Service::Apis::Ocl::Extensions::clCreateSubDevicesEXT = extAddr;
    return extAddr(in_device, properties, num_entries, out_devices, num_devices);
}
cl_int clReleaseDeviceEXTLoad(cl_device_id device){
    using ExtFuncT = decltype(clReleaseDeviceEXTLoad);
    static ExtFuncT *extAddr = reinterpret_cast<ExtFuncT*>(Cal::Service::Apis::Ocl::getExtensionFuncAddress("clReleaseDeviceEXT"));
    if(nullptr == extAddr){
        log<Verbosity::error>("Client requested for unavailable extension function rpc : clReleaseDeviceEXT");
        assert(false);
        return {};
    }
    Cal::Service::Apis::Ocl::Extensions::clReleaseDeviceEXT = extAddr;
    return extAddr(device);
}
cl_int clRetainDeviceEXTLoad(cl_device_id device){
    using ExtFuncT = decltype(clRetainDeviceEXTLoad);
    static ExtFuncT *extAddr = reinterpret_cast<ExtFuncT*>(Cal::Service::Apis::Ocl::getExtensionFuncAddress("clRetainDeviceEXT"));
    if(nullptr == extAddr){
        log<Verbosity::error>("Client requested for unavailable extension function rpc : clRetainDeviceEXT");
        assert(false);
        return {};
    }
    Cal::Service::Apis::Ocl::Extensions::clRetainDeviceEXT = extAddr;
    return extAddr(device);
}
cl_int clGetKernelSubGroupInfoKHRLoad(cl_kernel kernel, cl_device_id device, cl_kernel_sub_group_info param_name, size_t input_value_size, const void* input_value, size_t param_value_size, void* param_value, size_t* param_value_size_ret){
    using ExtFuncT = decltype(clGetKernelSubGroupInfoKHRLoad);
    static ExtFuncT *extAddr = reinterpret_cast<ExtFuncT*>(Cal::Service::Apis::Ocl::getExtensionFuncAddress("clGetKernelSubGroupInfoKHR"));
    if(nullptr == extAddr){
        log<Verbosity::error>("Client requested for unavailable extension function rpc : clGetKernelSubGroupInfoKHR");
        assert(false);
        return {};
    }
    Cal::Service::Apis::Ocl::Extensions::clGetKernelSubGroupInfoKHR = extAddr;
    return extAddr(kernel, device, param_name, input_value_size, input_value, param_value_size, param_value, param_value_size_ret);
}
cl_int clEnqueueMemFillINTELLoad(cl_command_queue command_queue, void* dstPtr, const void* pattern, size_t patternSize, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event){
    using ExtFuncT = decltype(clEnqueueMemFillINTELLoad);
    static ExtFuncT *extAddr = reinterpret_cast<ExtFuncT*>(Cal::Service::Apis::Ocl::getExtensionFuncAddress("clEnqueueMemFillINTEL"));
    if(nullptr == extAddr){
        log<Verbosity::error>("Client requested for unavailable extension function rpc : clEnqueueMemFillINTEL");
        assert(false);
        return {};
    }
    Cal::Service::Apis::Ocl::Extensions::clEnqueueMemFillINTEL = extAddr;
    return extAddr(command_queue, dstPtr, pattern, patternSize, size, num_events_in_wait_list, event_wait_list, event);
}
cl_int clEnqueueMemcpyINTELLoad(cl_command_queue command_queue, cl_bool blocking, void* dstPtr, const void* srcPtr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event){
    using ExtFuncT = decltype(clEnqueueMemcpyINTELLoad);
    static ExtFuncT *extAddr = reinterpret_cast<ExtFuncT*>(Cal::Service::Apis::Ocl::getExtensionFuncAddress("clEnqueueMemcpyINTEL"));
    if(nullptr == extAddr){
        log<Verbosity::error>("Client requested for unavailable extension function rpc : clEnqueueMemcpyINTEL");
        assert(false);
        return {};
    }
    Cal::Service::Apis::Ocl::Extensions::clEnqueueMemcpyINTEL = extAddr;
    return extAddr(command_queue, blocking, dstPtr, srcPtr, size, num_events_in_wait_list, event_wait_list, event);
}
cl_int clSetKernelArgMemPointerINTELLoad(cl_kernel kernel, cl_uint argIndex, const void* argValue){
    using ExtFuncT = decltype(clSetKernelArgMemPointerINTELLoad);
    static ExtFuncT *extAddr = reinterpret_cast<ExtFuncT*>(Cal::Service::Apis::Ocl::getExtensionFuncAddress("clSetKernelArgMemPointerINTEL"));
    if(nullptr == extAddr){
        log<Verbosity::error>("Client requested for unavailable extension function rpc : clSetKernelArgMemPointerINTEL");
        assert(false);
        return {};
    }
    Cal::Service::Apis::Ocl::Extensions::clSetKernelArgMemPointerINTEL = extAddr;
    return extAddr(kernel, argIndex, argValue);
}
cl_int clGetMemAllocInfoINTELLoad(cl_context context, const void* ptr, cl_mem_info_intel param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret){
    using ExtFuncT = decltype(clGetMemAllocInfoINTELLoad);
    static ExtFuncT *extAddr = reinterpret_cast<ExtFuncT*>(Cal::Service::Apis::Ocl::getExtensionFuncAddress("clGetMemAllocInfoINTEL"));
    if(nullptr == extAddr){
        log<Verbosity::error>("Client requested for unavailable extension function rpc : clGetMemAllocInfoINTEL");
        assert(false);
        return {};
    }
    Cal::Service::Apis::Ocl::Extensions::clGetMemAllocInfoINTEL = extAddr;
    return extAddr(context, ptr, param_name, param_value_size, param_value, param_value_size_ret);
}
void* clDeviceMemAllocINTELLoad(cl_context context, cl_device_id device, const cl_mem_properties_intel* properties, size_t size, cl_uint alignment, cl_int* errcode_ret){
    using ExtFuncT = decltype(clDeviceMemAllocINTELLoad);
    static ExtFuncT *extAddr = reinterpret_cast<ExtFuncT*>(Cal::Service::Apis::Ocl::getExtensionFuncAddress("clDeviceMemAllocINTEL"));
    if(nullptr == extAddr){
        log<Verbosity::error>("Client requested for unavailable extension function rpc : clDeviceMemAllocINTEL");
        assert(false);
        return {};
    }
    Cal::Service::Apis::Ocl::Extensions::clDeviceMemAllocINTEL = extAddr;
    return extAddr(context, device, properties, size, alignment, errcode_ret);
}
void* clHostMemAllocINTELLoad(cl_context context, const cl_mem_properties_intel* properties, size_t size, cl_uint alignment, cl_int* errcode_ret){
    using ExtFuncT = decltype(clHostMemAllocINTELLoad);
    static ExtFuncT *extAddr = reinterpret_cast<ExtFuncT*>(Cal::Service::Apis::Ocl::getExtensionFuncAddress("clHostMemAllocINTEL"));
    if(nullptr == extAddr){
        log<Verbosity::error>("Client requested for unavailable extension function rpc : clHostMemAllocINTEL");
        assert(false);
        return {};
    }
    Cal::Service::Apis::Ocl::Extensions::clHostMemAllocINTEL = extAddr;
    return extAddr(context, properties, size, alignment, errcode_ret);
}
void* clSharedMemAllocINTELLoad(cl_context context, cl_device_id device, const cl_mem_properties_intel* properties, size_t size, cl_uint alignment, cl_int* errcode_ret){
    using ExtFuncT = decltype(clSharedMemAllocINTELLoad);
    static ExtFuncT *extAddr = reinterpret_cast<ExtFuncT*>(Cal::Service::Apis::Ocl::getExtensionFuncAddress("clSharedMemAllocINTEL"));
    if(nullptr == extAddr){
        log<Verbosity::error>("Client requested for unavailable extension function rpc : clSharedMemAllocINTEL");
        assert(false);
        return {};
    }
    Cal::Service::Apis::Ocl::Extensions::clSharedMemAllocINTEL = extAddr;
    return extAddr(context, device, properties, size, alignment, errcode_ret);
}
cl_int clMemFreeINTELLoad(cl_context context, void* ptr){
    using ExtFuncT = decltype(clMemFreeINTELLoad);
    static ExtFuncT *extAddr = reinterpret_cast<ExtFuncT*>(Cal::Service::Apis::Ocl::getExtensionFuncAddress("clMemFreeINTEL"));
    if(nullptr == extAddr){
        log<Verbosity::error>("Client requested for unavailable extension function rpc : clMemFreeINTEL");
        assert(false);
        return {};
    }
    Cal::Service::Apis::Ocl::Extensions::clMemFreeINTEL = extAddr;
    return extAddr(context, ptr);
}
cl_int clMemBlockingFreeINTELLoad(cl_context context, void* ptr){
    using ExtFuncT = decltype(clMemBlockingFreeINTELLoad);
    static ExtFuncT *extAddr = reinterpret_cast<ExtFuncT*>(Cal::Service::Apis::Ocl::getExtensionFuncAddress("clMemBlockingFreeINTEL"));
    if(nullptr == extAddr){
        log<Verbosity::error>("Client requested for unavailable extension function rpc : clMemBlockingFreeINTEL");
        assert(false);
        return {};
    }
    Cal::Service::Apis::Ocl::Extensions::clMemBlockingFreeINTEL = extAddr;
    return extAddr(context, ptr);
}
cl_int clEnqueueMigrateMemINTELLoad(cl_command_queue command_queue, const void* ptr, size_t size, cl_mem_migration_flags flags, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event){
    using ExtFuncT = decltype(clEnqueueMigrateMemINTELLoad);
    static ExtFuncT *extAddr = reinterpret_cast<ExtFuncT*>(Cal::Service::Apis::Ocl::getExtensionFuncAddress("clEnqueueMigrateMemINTEL"));
    if(nullptr == extAddr){
        log<Verbosity::error>("Client requested for unavailable extension function rpc : clEnqueueMigrateMemINTEL");
        assert(false);
        return {};
    }
    Cal::Service::Apis::Ocl::Extensions::clEnqueueMigrateMemINTEL = extAddr;
    return extAddr(command_queue, ptr, size, flags, num_events_in_wait_list, event_wait_list, event);
}
cl_int clGetDeviceGlobalVariablePointerINTELLoad(cl_device_id device, cl_program program, const char* globalVariableName, size_t* globalVariableSizeRet, void** globalVariablePointerRet){
    using ExtFuncT = decltype(clGetDeviceGlobalVariablePointerINTELLoad);
    static ExtFuncT *extAddr = reinterpret_cast<ExtFuncT*>(Cal::Service::Apis::Ocl::getExtensionFuncAddress("clGetDeviceGlobalVariablePointerINTEL"));
    if(nullptr == extAddr){
        log<Verbosity::error>("Client requested for unavailable extension function rpc : clGetDeviceGlobalVariablePointerINTEL");
        assert(false);
        return {};
    }
    Cal::Service::Apis::Ocl::Extensions::clGetDeviceGlobalVariablePointerINTEL = extAddr;
    return extAddr(device, program, globalVariableName, globalVariableSizeRet, globalVariablePointerRet);
}
} // namespace Lazy Load
cl_int (*clCreateSubDevicesEXT)(cl_device_id in_device, const cl_device_partition_property_ext* properties, cl_uint num_entries, cl_device_id* out_devices, cl_uint* num_devices) = Cal::Service::Apis::Ocl::Extensions::LazyLoad::clCreateSubDevicesEXTLoad;
cl_int (*clReleaseDeviceEXT)(cl_device_id device) = Cal::Service::Apis::Ocl::Extensions::LazyLoad::clReleaseDeviceEXTLoad;
cl_int (*clRetainDeviceEXT)(cl_device_id device) = Cal::Service::Apis::Ocl::Extensions::LazyLoad::clRetainDeviceEXTLoad;
cl_int (*clGetKernelSubGroupInfoKHR)(cl_kernel kernel, cl_device_id device, cl_kernel_sub_group_info param_name, size_t input_value_size, const void* input_value, size_t param_value_size, void* param_value, size_t* param_value_size_ret) = Cal::Service::Apis::Ocl::Extensions::LazyLoad::clGetKernelSubGroupInfoKHRLoad;
cl_int (*clEnqueueMemFillINTEL)(cl_command_queue command_queue, void* dstPtr, const void* pattern, size_t patternSize, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) = Cal::Service::Apis::Ocl::Extensions::LazyLoad::clEnqueueMemFillINTELLoad;
cl_int (*clEnqueueMemcpyINTEL)(cl_command_queue command_queue, cl_bool blocking, void* dstPtr, const void* srcPtr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) = Cal::Service::Apis::Ocl::Extensions::LazyLoad::clEnqueueMemcpyINTELLoad;
cl_int (*clSetKernelArgMemPointerINTEL)(cl_kernel kernel, cl_uint argIndex, const void* argValue) = Cal::Service::Apis::Ocl::Extensions::LazyLoad::clSetKernelArgMemPointerINTELLoad;
cl_int (*clGetMemAllocInfoINTEL)(cl_context context, const void* ptr, cl_mem_info_intel param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) = Cal::Service::Apis::Ocl::Extensions::LazyLoad::clGetMemAllocInfoINTELLoad;
void* (*clDeviceMemAllocINTEL)(cl_context context, cl_device_id device, const cl_mem_properties_intel* properties, size_t size, cl_uint alignment, cl_int* errcode_ret) = Cal::Service::Apis::Ocl::Extensions::LazyLoad::clDeviceMemAllocINTELLoad;
void* (*clHostMemAllocINTEL)(cl_context context, const cl_mem_properties_intel* properties, size_t size, cl_uint alignment, cl_int* errcode_ret) = Cal::Service::Apis::Ocl::Extensions::LazyLoad::clHostMemAllocINTELLoad;
void* (*clSharedMemAllocINTEL)(cl_context context, cl_device_id device, const cl_mem_properties_intel* properties, size_t size, cl_uint alignment, cl_int* errcode_ret) = Cal::Service::Apis::Ocl::Extensions::LazyLoad::clSharedMemAllocINTELLoad;
cl_int (*clMemFreeINTEL)(cl_context context, void* ptr) = Cal::Service::Apis::Ocl::Extensions::LazyLoad::clMemFreeINTELLoad;
cl_int (*clMemBlockingFreeINTEL)(cl_context context, void* ptr) = Cal::Service::Apis::Ocl::Extensions::LazyLoad::clMemBlockingFreeINTELLoad;
cl_int (*clEnqueueMigrateMemINTEL)(cl_command_queue command_queue, const void* ptr, size_t size, cl_mem_migration_flags flags, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) = Cal::Service::Apis::Ocl::Extensions::LazyLoad::clEnqueueMigrateMemINTELLoad;
cl_int (*clGetDeviceGlobalVariablePointerINTEL)(cl_device_id device, cl_program program, const char* globalVariableName, size_t* globalVariableSizeRet, void** globalVariablePointerRet) = Cal::Service::Apis::Ocl::Extensions::LazyLoad::clGetDeviceGlobalVariablePointerINTELLoad;
} // namespace Extensions

bool isSuccessful(cl_int result) {
    return result == CL_SUCCESS;
}

} // namespace Ocl
} // namespace Apis
} // namespace Service
} // namespace Cal
// #### Generated code -- end ####
