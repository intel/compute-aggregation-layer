/*
 * Copyright (C) 2022-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once
// #### Generated code -- begin ####

#include "service/service.h"
#include "shared/rpc.h"
#include "shared/utils.h"

#include "generated_rpc_messages_ocl.h"

#include <optional>
#include <string>
#include <type_traits>
#include <vector>

namespace Cal {
namespace Service {
namespace Apis {
namespace Ocl {

namespace Standard {
bool loadOclLibrary(std::optional<std::string> path);
void unloadOclLibrary();
bool isOclLibraryLoaded();

extern cl_int (*clGetPlatformIDs)(cl_uint num_entries, cl_platform_id* platforms, cl_uint* num_platforms);
extern cl_int (*clGetPlatformInfo)(cl_platform_id platform, cl_platform_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
extern void* (*clGetExtensionFunctionAddress)(const char* funcname);
extern cl_int (*clGetDeviceIDs)(cl_platform_id platform, cl_device_type device_type, cl_uint num_entries, cl_device_id* devices, cl_uint* num_devices);
extern cl_int (*clGetDeviceInfo)(cl_device_id device, cl_device_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
extern cl_context (*clCreateContext)(const cl_context_properties* properties, cl_uint num_devices, const cl_device_id* devices, void (CL_CALLBACK* pfn_notify)(const char* errinfo, const void* private_info, size_t cb, void* user_data), void* user_data, cl_int* errcode_ret);
extern cl_context (*clCreateContextFromType)(const cl_context_properties* properties, cl_device_type device_type, void (CL_CALLBACK* pfn_notify)(const char* errinfo, const void* private_info, size_t cb, void* user_data), void* user_data, cl_int* errcode_ret);
extern cl_int (*clGetContextInfo)(cl_context context, cl_context_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
extern cl_int (*clSetContextDestructorCallback)(cl_context context, void (CL_CALLBACK* pfn_notify)(cl_context context, void* user_data), void* user_data);
extern cl_int (*clSetMemObjectDestructorCallback)(cl_mem memobj, void (CL_CALLBACK* pfn_notify)(cl_mem memobj, void* user_data), void* user_data);
extern cl_int (*clCreateSubDevices)(cl_device_id in_device, const cl_device_partition_property* properties, cl_uint num_devices, cl_device_id* out_devices, cl_uint* num_devices_ret);
extern cl_command_queue (*clCreateCommandQueue)(cl_context context, cl_device_id device, cl_command_queue_properties  properties, cl_int* errcode_ret);
extern cl_int (*clSetDefaultDeviceCommandQueue)(cl_context context, cl_device_id device, cl_command_queue command_queue);
extern cl_command_queue (*clCreateCommandQueueWithProperties)(cl_context context, cl_device_id device, const cl_queue_properties* properties, cl_int* errcode_ret);
extern cl_program (*clCreateProgramWithSource)(cl_context context, cl_uint count, const char** strings, const size_t* lengths, cl_int* errcode_ret);
extern cl_program (*clCreateProgramWithIL)(cl_context context, const void* il, size_t length, cl_int* errcode_ret);
extern cl_program (*clCreateProgramWithBinary)(cl_context context, cl_uint num_devices, const cl_device_id* device_list, const size_t* lengths, const unsigned char** binaries, cl_int* binary_status, cl_int* errcode_ret);
extern cl_program (*clCreateProgramWithBuiltInKernels)(cl_context context, cl_uint num_devices, const cl_device_id* device_list, const char* kernel_names, cl_int* errcode_ret);
extern cl_int (*clUnloadCompiler)();
extern cl_int (*clUnloadPlatformCompiler)(cl_platform_id platform);
extern cl_int (*clBuildProgram)(cl_program program, cl_uint num_devices, const cl_device_id* device_list, const char* options, void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data), void* user_data);
extern cl_int (*clCompileProgram)(cl_program program, cl_uint num_devices, const cl_device_id* device_list, const char* options, cl_uint num_input_headers, const cl_program* input_headers, const char** header_include_names, void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data), void* user_data);
extern cl_program (*clLinkProgram)(cl_context context, cl_uint num_devices, const cl_device_id* device_list, const char* options, cl_uint num_input_programs, const cl_program* input_programs, void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data), void* user_data, cl_int* errcode_ret);
extern cl_int (*clGetProgramBuildInfo)(cl_program program, cl_device_id device, cl_program_build_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
extern cl_int (*clSetProgramReleaseCallback)(cl_program program, void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data), void* user_data);
extern cl_kernel (*clCreateKernel)(cl_program program, const char* kernel_name, cl_int* errcode_ret);
extern cl_kernel (*clCloneKernel)(cl_kernel source_kernel, cl_int* errcode_ret);
extern cl_int (*clCreateKernelsInProgram)(cl_program program, cl_uint num_kernels, cl_kernel* kernels, cl_uint* num_kernels_ret);
extern cl_int (*clGetCommandQueueInfo)(cl_command_queue command_queue, cl_command_queue_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
extern cl_int (*clGetProgramInfo)(cl_program program, cl_program_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
extern cl_int (*clGetMemObjectInfo)(cl_mem memobj, cl_mem_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
extern cl_int (*clGetImageInfo)(cl_mem image, cl_image_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
extern cl_int (*clGetSamplerInfo)(cl_sampler sampler, cl_sampler_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
extern cl_int (*clGetKernelInfo)(cl_kernel kernel, cl_kernel_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
extern cl_int (*clGetKernelWorkGroupInfo)(cl_kernel kernel, cl_device_id device, cl_kernel_work_group_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
extern cl_int (*clGetKernelArgInfo)(cl_kernel kernel, cl_uint arg_indx, cl_kernel_arg_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
extern cl_int (*clGetKernelSubGroupInfo)(cl_kernel kernel, cl_device_id device, cl_kernel_sub_group_info param_name, size_t input_value_size, const void* input_value, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
extern cl_int (*clReleaseCommandQueue)(cl_command_queue command_queue);
extern cl_int (*clReleaseContext)(cl_context context);
extern cl_int (*clReleaseDevice)(cl_device_id device);
extern cl_int (*clReleaseKernel)(cl_kernel kernel);
extern cl_int (*clReleaseSampler)(cl_sampler sampler);
extern cl_int (*clReleaseProgram)(cl_program program);
extern cl_int (*clReleaseMemObject)(cl_mem memobj);
extern cl_int (*clReleaseEvent)(cl_event event);
extern cl_int (*clRetainCommandQueue)(cl_command_queue command_queue);
extern cl_int (*clRetainContext)(cl_context context);
extern cl_int (*clRetainDevice)(cl_device_id device);
extern cl_int (*clRetainProgram)(cl_program program);
extern cl_int (*clRetainMemObject)(cl_mem memobj);
extern cl_int (*clRetainSampler)(cl_sampler sampler);
extern cl_int (*clRetainKernel)(cl_kernel kernel);
extern cl_int (*clRetainEvent)(cl_event event);
extern cl_int (*clFlush)(cl_command_queue command_queue);
extern cl_int (*clFinish)(cl_command_queue command_queue);
extern cl_int (*clEnqueueNDRangeKernel)(cl_command_queue command_queue, cl_kernel kernel, cl_uint work_dim, const size_t* global_work_offset, const size_t* global_work_size, const size_t* local_work_size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
extern cl_int (*clEnqueueTask)(cl_command_queue command_queue, cl_kernel kernel, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
extern cl_int (*clEnqueueMarkerWithWaitList)(cl_command_queue command_queue, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
extern cl_int (*clEnqueueMarker)(cl_command_queue command_queue, cl_event* event);
extern cl_int (*clEnqueueBarrierWithWaitList)(cl_command_queue command_queue, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
extern cl_int (*clEnqueueBarrier)(cl_command_queue command_queue);
extern cl_int (*clEnqueueWaitForEvents)(cl_command_queue command_queue, cl_uint num_events, const cl_event* event_list);
extern cl_int (*clEnqueueMigrateMemObjects)(cl_command_queue command_queue, cl_uint num_mem_objects, const cl_mem* mem_objects, cl_mem_migration_flags flags, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
extern void* (*clGetExtensionFunctionAddressForPlatform)(cl_platform_id platform, const char* funcname);
extern cl_mem (*clCreateBuffer)(cl_context context, cl_mem_flags flags, size_t size, void* host_ptr, cl_int* errcode_ret);
extern cl_mem (*clCreateSubBuffer)(cl_mem buffer, cl_mem_flags flags, cl_buffer_create_type buffer_create_type, const void* buffer_create_info, cl_int* errcode_ret);
extern cl_mem (*clCreatePipe)(cl_context context, cl_mem_flags flags, cl_uint pipe_packet_size, cl_uint pipe_max_packets, const cl_pipe_properties* properties, cl_int* errcode_ret);
extern cl_int (*clGetPipeInfo)(cl_mem pipe, cl_pipe_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
extern cl_mem (*clCreateImage)(cl_context context, cl_mem_flags flags, const cl_image_format* image_format, const cl_image_desc* image_desc, void* host_ptr, cl_int* errcode_ret);
extern cl_mem (*clCreateImage2D)(cl_context context, cl_mem_flags flags, const cl_image_format* image_format, size_t image_width, size_t image_height, size_t image_row_pitch, void* host_ptr, cl_int* errcode_ret);
extern cl_mem (*clCreateImage3D)(cl_context context, cl_mem_flags flags, const cl_image_format* image_format, size_t image_width, size_t image_height, size_t image_depth, size_t image_row_pitch, size_t image_slice_pitch, void* host_ptr, cl_int* errcode_ret);
extern cl_sampler (*clCreateSampler)(cl_context context, cl_bool normalized_coords, cl_addressing_mode addressing_mode, cl_filter_mode filter_mode, cl_int* errcode_ret);
extern cl_sampler (*clCreateSamplerWithProperties)(cl_context context, const cl_sampler_properties* properties, cl_int* errcode_ret);
extern cl_mem (*clCreateImageWithProperties)(cl_context context, const cl_mem_properties* properties, cl_mem_flags flags, const cl_image_format* image_format, const cl_image_desc* image_desc, void* host_ptr, cl_int* errcode_ret);
extern cl_mem (*clCreateBufferWithProperties)(cl_context context, const cl_mem_properties* properties, cl_mem_flags flags, size_t size, void* host_ptr, cl_int* errcode_ret);
extern cl_int (*clGetSupportedImageFormats)(cl_context context, cl_mem_flags flags, cl_mem_object_type image_type, cl_uint num_entries, cl_image_format* image_formats, cl_uint* num_image_formats);
extern cl_int (*clSetKernelArg)(cl_kernel kernel, cl_uint arg_index, size_t arg_size, const void* arg_value);
extern cl_int (*clSetProgramSpecializationConstant)(cl_program program, cl_uint spec_id, size_t spec_size, const void* spec_value);
extern cl_int (*clEnqueueWriteBuffer)(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, size_t offset, size_t size, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
extern cl_int (*clEnqueueWriteBufferRect)(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, const size_t* buffer_origin, const size_t* host_origin, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
extern cl_int (*clEnqueueReadBuffer)(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, size_t offset, size_t size, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
extern cl_int (*clEnqueueReadBufferRect)(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, const size_t* buffer_origin, const size_t* host_origin, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
extern cl_int (*clEnqueueCopyBuffer)(cl_command_queue command_queue, cl_mem src_buffer, cl_mem dst_buffer, size_t src_offset, size_t dst_offset, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
extern cl_int (*clEnqueueCopyBufferRect)(cl_command_queue command_queue, cl_mem src_buffer, cl_mem dst_buffer, const size_t* src_origin, const size_t* dst_origin, const size_t* region, size_t src_row_pitch, size_t src_slice_pitch, size_t dst_row_pitch, size_t dst_slice_pitch, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
extern cl_int (*clEnqueueReadImage)(cl_command_queue command_queue, cl_mem image, cl_bool blocking_read, const size_t* src_origin, const size_t* region, size_t row_pitch, size_t slice_pitch, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
extern cl_int (*clEnqueueWriteImage)(cl_command_queue command_queue, cl_mem image, cl_bool blocking_write, const size_t* origin, const size_t* region, size_t input_row_pitch, size_t input_slice_pitch, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
extern cl_int (*clEnqueueCopyImage)(cl_command_queue command_queue, cl_mem src_image, cl_mem dst_image, const size_t* src_origin, const size_t* dst_origin, const size_t* region, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
extern cl_int (*clEnqueueCopyImageToBuffer)(cl_command_queue command_queue, cl_mem src_image, cl_mem dst_buffer, const size_t* src_origin, const size_t* region, size_t dst_offset, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
extern cl_int (*clEnqueueCopyBufferToImage)(cl_command_queue command_queue, cl_mem src_buffer, cl_mem dst_image, size_t src_offset, const size_t* dst_origin, const size_t* region, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
extern void* (*clEnqueueMapBuffer)(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_map, cl_map_flags map_flags, size_t offset, size_t cb, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event, cl_int* errcode_ret);
extern cl_int (*clEnqueueUnmapMemObject)(cl_command_queue command_queue, cl_mem memobj, void* mapped_ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
extern cl_int (*clEnqueueFillBuffer)(cl_command_queue command_queue, cl_mem memobj, const void* pattern, size_t patternSize, size_t offset, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
extern cl_int (*clEnqueueFillImage)(cl_command_queue command_queue, cl_mem image, const void* fill_color, const size_t* origin, const size_t* region, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
extern cl_int (*clWaitForEvents)(cl_uint num_events, const cl_event* event_list);
extern cl_int (*clGetEventInfo)(cl_event event, cl_event_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
extern cl_int (*clGetEventProfilingInfo)(cl_event event, cl_profiling_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
extern cl_event (*clCreateUserEvent)(cl_context context, cl_int* errcode_ret);
extern cl_int (*clSetUserEventStatus)(cl_event event, cl_int execution_status);
extern cl_int (*clSetEventCallback)(cl_event event, cl_int command_exec_callback_type, void (CL_CALLBACK* pfn_notify)(cl_event event, cl_int event_command_status, void *user_data), void* user_data);
extern cl_int (*clGetDeviceAndHostTimer)(cl_device_id device, cl_ulong* device_timestamp, cl_ulong* host_timestamp);
extern cl_int (*clGetHostTimer)(cl_device_id device, cl_ulong* host_timestamp);
extern void* (*clSVMAlloc)(cl_context context, cl_svm_mem_flags flags, size_t size, cl_uint alignment);
extern void (*clSVMFree)(cl_context context, void* ptr);
extern cl_int (*clEnqueueSVMMap)(cl_command_queue command_queue, cl_bool blocking_map, cl_map_flags map_flags, void* svm_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
extern cl_int (*clEnqueueSVMUnmap)(cl_command_queue command_queue, void* svm_ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
extern cl_int (*clSetKernelArgSVMPointer)(cl_kernel kernel, cl_uint argIndex, const void* argValue);
extern cl_int (*clSetKernelExecInfo)(cl_kernel kernel, cl_kernel_exec_info param_name, size_t param_value_size, const void* param_value);
extern cl_int (*clEnqueueSVMMemFill)(cl_command_queue command_queue, void* svm_ptr, const void* pattern, size_t patternSize, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
extern cl_int (*clEnqueueSVMMigrateMem)(cl_command_queue command_queue, cl_uint num_svm_pointers, const void** svm_pointers, const size_t* sizes, cl_mem_migration_flags flags, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
extern cl_int (*clEnqueueSVMMemcpy)(cl_command_queue command_queue, cl_bool blocking, void* dst_ptr, const void* src_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
extern cl_int (*clEnqueueSVMFree)(cl_command_queue command_queue, cl_uint num_svm_pointers, void** svm_pointers, void (CL_CALLBACK* pfn_notify)(cl_command_queue queue, cl_uint num_svm_pointers, void ** svm_pointers, void* user_data), void* user_data, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
} // Standard

namespace Extensions {
extern cl_int (*clCreateSubDevicesEXT)(cl_device_id in_device, const cl_device_partition_property_ext* properties, cl_uint num_entries, cl_device_id* out_devices, cl_uint* num_devices);
extern cl_int (*clReleaseDeviceEXT)(cl_device_id device);
extern cl_int (*clRetainDeviceEXT)(cl_device_id device);
extern cl_int (*clGetKernelSubGroupInfoKHR)(cl_kernel kernel, cl_device_id device, cl_kernel_sub_group_info param_name, size_t input_value_size, const void* input_value, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
extern cl_int (*clGetKernelSuggestedLocalWorkSizeKHR)(cl_command_queue command_queue, cl_kernel kernel, cl_uint work_dim, const size_t* global_work_offset, const size_t* global_work_size, size_t * suggested_local_work_size);
extern cl_int (*clEnqueueMemFillINTEL)(cl_command_queue command_queue, void* dstPtr, const void* pattern, size_t patternSize, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
extern cl_int (*clEnqueueMemcpyINTEL)(cl_command_queue command_queue, cl_bool blocking, void* dstPtr, const void* srcPtr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
extern cl_int (*clSetKernelArgMemPointerINTEL)(cl_kernel kernel, cl_uint argIndex, const void* argValue);
extern cl_int (*clGetMemAllocInfoINTEL)(cl_context context, const void* ptr, cl_mem_info_intel param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
extern void* (*clDeviceMemAllocINTEL)(cl_context context, cl_device_id device, const cl_mem_properties_intel* properties, size_t size, cl_uint alignment, cl_int* errcode_ret);
extern void* (*clHostMemAllocINTEL)(cl_context context, const cl_mem_properties_intel* properties, size_t size, cl_uint alignment, cl_int* errcode_ret);
extern void* (*clSharedMemAllocINTEL)(cl_context context, cl_device_id device, const cl_mem_properties_intel* properties, size_t size, cl_uint alignment, cl_int* errcode_ret);
extern cl_int (*clMemFreeINTEL)(cl_context context, void* ptr);
extern cl_int (*clMemBlockingFreeINTEL)(cl_context context, void* ptr);
extern cl_int (*clEnqueueMigrateMemINTEL)(cl_command_queue command_queue, const void* ptr, size_t size, cl_mem_migration_flags flags, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
extern cl_int (*clGetDeviceGlobalVariablePointerINTEL)(cl_device_id device, cl_program program, const char* globalVariableName, size_t* globalVariableSizeRet, void** globalVariablePointerRet);
} // Extensions

inline bool clGetPlatformInfoHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clGetPlatformInfo");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClGetPlatformInfoRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clGetPlatformInfo(
                                                apiCommand->args.platform, 
                                                apiCommand->args.param_name, 
                                                apiCommand->args.param_value_size, 
                                                apiCommand->args.param_value ? apiCommand->captures.param_value : nullptr, 
                                                apiCommand->args.param_value_size_ret ? &apiCommand->captures.param_value_size_ret : nullptr
                                                );
    return true;
}
inline bool clGetDeviceIDsHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clGetDeviceIDs");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClGetDeviceIDsRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clGetDeviceIDs(
                                                apiCommand->args.platform, 
                                                apiCommand->args.device_type, 
                                                apiCommand->args.num_entries, 
                                                apiCommand->args.devices ? apiCommand->captures.devices : nullptr, 
                                                apiCommand->args.num_devices ? &apiCommand->captures.num_devices : nullptr
                                                );
    return true;
}
inline bool clGetDeviceInfoHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clGetDeviceInfo");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClGetDeviceInfoRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clGetDeviceInfo(
                                                apiCommand->args.device, 
                                                apiCommand->args.param_name, 
                                                apiCommand->args.param_value_size, 
                                                apiCommand->args.param_value ? apiCommand->captures.param_value : nullptr, 
                                                &apiCommand->captures.param_value_size_ret
                                                );
    return true;
}
bool clCreateContextHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
bool clCreateContextFromTypeHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
inline bool clGetContextInfoHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clGetContextInfo");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClGetContextInfoRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clGetContextInfo(
                                                apiCommand->args.context, 
                                                apiCommand->args.param_name, 
                                                apiCommand->args.param_value_size, 
                                                apiCommand->args.param_value ? apiCommand->captures.param_value : nullptr, 
                                                &apiCommand->captures.param_value_size_ret
                                                );
    return true;
}
bool clSetContextDestructorCallbackHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
bool clSetMemObjectDestructorCallbackHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
inline bool clCreateSubDevicesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clCreateSubDevices");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClCreateSubDevicesRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clCreateSubDevices(
                                                apiCommand->args.in_device, 
                                                apiCommand->args.properties ? apiCommand->captures.getProperties() : nullptr, 
                                                apiCommand->args.num_devices, 
                                                apiCommand->args.out_devices ? apiCommand->captures.getOut_devices() : nullptr, 
                                                apiCommand->args.num_devices_ret ? &apiCommand->captures.num_devices_ret : nullptr
                                                );
    return true;
}
inline bool clCreateCommandQueueHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clCreateCommandQueue");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClCreateCommandQueueRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clCreateCommandQueue(
                                                apiCommand->args.context, 
                                                apiCommand->args.device, 
                                                apiCommand->args.properties, 
                                                apiCommand->args.errcode_ret ? &apiCommand->captures.errcode_ret : nullptr
                                                );
    return true;
}
inline bool clSetDefaultDeviceCommandQueueHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clSetDefaultDeviceCommandQueue");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClSetDefaultDeviceCommandQueueRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clSetDefaultDeviceCommandQueue(
                                                apiCommand->args.context, 
                                                apiCommand->args.device, 
                                                apiCommand->args.command_queue
                                                );
    return true;
}
inline bool clCreateCommandQueueWithPropertiesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clCreateCommandQueueWithProperties");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClCreateCommandQueueWithPropertiesRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clCreateCommandQueueWithProperties(
                                                apiCommand->args.context, 
                                                apiCommand->args.device, 
                                                apiCommand->args.properties ? apiCommand->captures.properties : nullptr, 
                                                apiCommand->args.errcode_ret ? &apiCommand->captures.errcode_ret : nullptr
                                                );
    return true;
}
inline bool clCreateProgramWithSourceHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clCreateProgramWithSource");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClCreateProgramWithSourceRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clCreateProgramWithSource(
                                                apiCommand->args.context, 
                                                apiCommand->args.count, 
                                                apiCommand->args.strings ? apiCommand->captures.getStrings().data() : nullptr, 
                                                apiCommand->args.lengths ? apiCommand->captures.getLengths() : nullptr, 
                                                apiCommand->args.errcode_ret ? &apiCommand->captures.errcode_ret : nullptr
                                                );
    return true;
}
inline bool clCreateProgramWithILHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clCreateProgramWithIL");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClCreateProgramWithILRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clCreateProgramWithIL(
                                                apiCommand->args.context, 
                                                apiCommand->args.il ? apiCommand->captures.il : nullptr, 
                                                apiCommand->args.length, 
                                                apiCommand->args.errcode_ret ? &apiCommand->captures.errcode_ret : nullptr
                                                );
    return true;
}
inline bool clCreateProgramWithBinaryHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clCreateProgramWithBinary");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClCreateProgramWithBinaryRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clCreateProgramWithBinary(
                                                apiCommand->args.context, 
                                                apiCommand->args.num_devices, 
                                                apiCommand->args.device_list ? apiCommand->captures.getDevice_list() : nullptr, 
                                                apiCommand->args.lengths ? apiCommand->captures.getLengths() : nullptr, 
                                                apiCommand->args.binaries ? apiCommand->captures.getBinaries().data() : nullptr, 
                                                apiCommand->args.binary_status ? apiCommand->captures.getBinary_status() : nullptr, 
                                                apiCommand->args.errcode_ret ? &apiCommand->captures.errcode_ret : nullptr
                                                );
    return true;
}
inline bool clCreateProgramWithBuiltInKernelsHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clCreateProgramWithBuiltInKernels");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClCreateProgramWithBuiltInKernelsRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clCreateProgramWithBuiltInKernels(
                                                apiCommand->args.context, 
                                                apiCommand->args.num_devices, 
                                                apiCommand->args.device_list ? apiCommand->captures.getDevice_list() : nullptr, 
                                                apiCommand->args.kernel_names ? apiCommand->captures.getKernel_names() : nullptr, 
                                                apiCommand->args.errcode_ret ? &apiCommand->captures.errcode_ret : nullptr
                                                );
    return true;
}
bool clBuildProgramHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
bool clCompileProgramHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
bool clLinkProgramHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
inline bool clGetProgramBuildInfoHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clGetProgramBuildInfo");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClGetProgramBuildInfoRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clGetProgramBuildInfo(
                                                apiCommand->args.program, 
                                                apiCommand->args.device, 
                                                apiCommand->args.param_name, 
                                                apiCommand->args.param_value_size, 
                                                apiCommand->args.param_value ? apiCommand->captures.param_value : nullptr, 
                                                apiCommand->args.param_value_size_ret ? &apiCommand->captures.param_value_size_ret : nullptr
                                                );
    return true;
}
bool clSetProgramReleaseCallbackHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
inline bool clCreateKernelHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clCreateKernel");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClCreateKernelRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clCreateKernel(
                                                apiCommand->args.program, 
                                                apiCommand->args.kernel_name ? apiCommand->captures.kernel_name : nullptr, 
                                                apiCommand->args.errcode_ret ? &apiCommand->captures.errcode_ret : nullptr
                                                );
    return true;
}
inline bool clCloneKernelHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clCloneKernel");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClCloneKernelRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clCloneKernel(
                                                apiCommand->args.source_kernel, 
                                                apiCommand->args.errcode_ret ? &apiCommand->captures.errcode_ret : nullptr
                                                );
    return true;
}
inline bool clCreateKernelsInProgramHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clCreateKernelsInProgram");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClCreateKernelsInProgramRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clCreateKernelsInProgram(
                                                apiCommand->args.program, 
                                                apiCommand->args.num_kernels, 
                                                apiCommand->args.kernels ? apiCommand->captures.kernels : nullptr, 
                                                apiCommand->args.num_kernels_ret ? &apiCommand->captures.num_kernels_ret : nullptr
                                                );
    return true;
}
inline bool clGetCommandQueueInfoHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clGetCommandQueueInfo");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClGetCommandQueueInfoRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clGetCommandQueueInfo(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.param_name, 
                                                apiCommand->args.param_value_size, 
                                                apiCommand->args.param_value ? apiCommand->captures.param_value : nullptr, 
                                                &apiCommand->captures.param_value_size_ret
                                                );
    return true;
}
inline bool clGetProgramInfoRpcHelperHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clGetProgramInfoRpcHelper");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClGetProgramInfoRpcHelperRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clGetProgramInfo(
                                                apiCommand->args.program, 
                                                apiCommand->args.param_name, 
                                                apiCommand->args.param_value_size, 
                                                apiCommand->args.param_value ? apiCommand->captures.param_value : nullptr, 
                                                apiCommand->args.param_value_size_ret ? &apiCommand->captures.param_value_size_ret : nullptr
                                                );
    return true;
}
bool clGetProgramInfoGetBinariesRpcHelperHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
inline bool clGetMemObjectInfoHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clGetMemObjectInfo");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClGetMemObjectInfoRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clGetMemObjectInfo(
                                                apiCommand->args.memobj, 
                                                apiCommand->args.param_name, 
                                                apiCommand->args.param_value_size, 
                                                apiCommand->args.param_value ? apiCommand->captures.param_value : nullptr, 
                                                apiCommand->args.param_value_size_ret ? &apiCommand->captures.param_value_size_ret : nullptr
                                                );
    return true;
}
inline bool clGetImageInfoHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clGetImageInfo");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClGetImageInfoRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clGetImageInfo(
                                                apiCommand->args.image, 
                                                apiCommand->args.param_name, 
                                                apiCommand->args.param_value_size, 
                                                apiCommand->args.param_value ? apiCommand->captures.param_value : nullptr, 
                                                apiCommand->args.param_value_size_ret ? &apiCommand->captures.param_value_size_ret : nullptr
                                                );
    return true;
}
inline bool clGetSamplerInfoHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clGetSamplerInfo");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClGetSamplerInfoRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clGetSamplerInfo(
                                                apiCommand->args.sampler, 
                                                apiCommand->args.param_name, 
                                                apiCommand->args.param_value_size, 
                                                apiCommand->args.param_value ? apiCommand->captures.param_value : nullptr, 
                                                apiCommand->args.param_value_size_ret ? &apiCommand->captures.param_value_size_ret : nullptr
                                                );
    return true;
}
inline bool clGetKernelInfoHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clGetKernelInfo");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClGetKernelInfoRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clGetKernelInfo(
                                                apiCommand->args.kernel, 
                                                apiCommand->args.param_name, 
                                                apiCommand->args.param_value_size, 
                                                apiCommand->args.param_value ? apiCommand->captures.param_value : nullptr, 
                                                &apiCommand->captures.param_value_size_ret
                                                );
    return true;
}
inline bool clGetKernelWorkGroupInfoHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clGetKernelWorkGroupInfo");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClGetKernelWorkGroupInfoRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clGetKernelWorkGroupInfo(
                                                apiCommand->args.kernel, 
                                                apiCommand->args.device, 
                                                apiCommand->args.param_name, 
                                                apiCommand->args.param_value_size, 
                                                apiCommand->args.param_value ? apiCommand->captures.param_value : nullptr, 
                                                apiCommand->args.param_value_size_ret ? &apiCommand->captures.param_value_size_ret : nullptr
                                                );
    return true;
}
inline bool clGetKernelArgInfoHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clGetKernelArgInfo");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClGetKernelArgInfoRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clGetKernelArgInfo(
                                                apiCommand->args.kernel, 
                                                apiCommand->args.arg_indx, 
                                                apiCommand->args.param_name, 
                                                apiCommand->args.param_value_size, 
                                                apiCommand->args.param_value ? apiCommand->captures.param_value : nullptr, 
                                                apiCommand->args.param_value_size_ret ? &apiCommand->captures.param_value_size_ret : nullptr
                                                );
    return true;
}
inline bool clGetKernelSubGroupInfoHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clGetKernelSubGroupInfo");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClGetKernelSubGroupInfoRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clGetKernelSubGroupInfo(
                                                apiCommand->args.kernel, 
                                                apiCommand->args.device, 
                                                apiCommand->args.param_name, 
                                                apiCommand->args.input_value_size, 
                                                apiCommand->args.input_value ? apiCommand->captures.getInput_value() : nullptr, 
                                                apiCommand->args.param_value_size, 
                                                apiCommand->args.param_value ? apiCommand->captures.getParam_value() : nullptr, 
                                                apiCommand->args.param_value_size_ret ? &apiCommand->captures.param_value_size_ret : nullptr
                                                );
    return true;
}
inline bool clReleaseCommandQueueHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clReleaseCommandQueue");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClReleaseCommandQueueRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clReleaseCommandQueue(
                                                apiCommand->args.command_queue
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to clReleaseCommandQueue (as clReleaseCommandQueueHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool clReleaseContextHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clReleaseContext");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClReleaseContextRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clReleaseContext(
                                                apiCommand->args.context
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to clReleaseContext (as clReleaseContextHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool clReleaseDeviceHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clReleaseDevice");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClReleaseDeviceRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clReleaseDevice(
                                                apiCommand->args.device
                                                );
    return true;
}
inline bool clReleaseKernelHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clReleaseKernel");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClReleaseKernelRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clReleaseKernel(
                                                apiCommand->args.kernel
                                                );
    return true;
}
inline bool clReleaseSamplerHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clReleaseSampler");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClReleaseSamplerRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clReleaseSampler(
                                                apiCommand->args.sampler
                                                );
    return true;
}
inline bool clReleaseProgramHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clReleaseProgram");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClReleaseProgramRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clReleaseProgram(
                                                apiCommand->args.program
                                                );
    return true;
}
bool clReleaseMemObjectHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
inline bool clReleaseEventHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clReleaseEvent");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClReleaseEventRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clReleaseEvent(
                                                apiCommand->args.event
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to clReleaseEvent (as clReleaseEventHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool clRetainCommandQueueHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clRetainCommandQueue");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClRetainCommandQueueRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clRetainCommandQueue(
                                                apiCommand->args.command_queue
                                                );
    return true;
}
inline bool clRetainContextHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clRetainContext");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClRetainContextRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clRetainContext(
                                                apiCommand->args.context
                                                );
    return true;
}
inline bool clRetainDeviceHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clRetainDevice");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClRetainDeviceRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clRetainDevice(
                                                apiCommand->args.device
                                                );
    return true;
}
inline bool clRetainProgramHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clRetainProgram");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClRetainProgramRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clRetainProgram(
                                                apiCommand->args.program
                                                );
    return true;
}
inline bool clRetainMemObjectHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clRetainMemObject");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClRetainMemObjectRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clRetainMemObject(
                                                apiCommand->args.memobj
                                                );
    return true;
}
inline bool clRetainSamplerHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clRetainSampler");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClRetainSamplerRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clRetainSampler(
                                                apiCommand->args.sampler
                                                );
    return true;
}
inline bool clRetainKernelHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clRetainKernel");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClRetainKernelRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clRetainKernel(
                                                apiCommand->args.kernel
                                                );
    return true;
}
inline bool clRetainEventHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clRetainEvent");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClRetainEventRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clRetainEvent(
                                                apiCommand->args.event
                                                );
    return true;
}
inline bool clFlushHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clFlush");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClFlushRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clFlush(
                                                apiCommand->args.command_queue
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to clFlush (as clFlushHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool clFinishHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clFinish");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClFinishRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clFinish(
                                                apiCommand->args.command_queue
                                                );
    return true;
}
inline bool clEnqueueNDRangeKernelHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueNDRangeKernel");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueNDRangeKernelRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueNDRangeKernel(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.kernel, 
                                                apiCommand->args.work_dim, 
                                                apiCommand->args.global_work_offset ? apiCommand->captures.getGlobal_work_offset() : nullptr, 
                                                apiCommand->args.global_work_size ? apiCommand->captures.getGlobal_work_size() : nullptr, 
                                                apiCommand->args.local_work_size ? apiCommand->captures.getLocal_work_size() : nullptr, 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.getEvent_wait_list() : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to clEnqueueNDRangeKernel (as clEnqueueNDRangeKernelHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool clEnqueueTaskHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueTask");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueTaskRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueTask(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.kernel, 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    return true;
}
inline bool clEnqueueMarkerWithWaitListHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueMarkerWithWaitList");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueMarkerWithWaitListRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueMarkerWithWaitList(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    return true;
}
inline bool clEnqueueMarkerHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueMarker");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueMarkerRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueMarker(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    return true;
}
inline bool clEnqueueBarrierWithWaitListHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueBarrierWithWaitList");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueBarrierWithWaitListRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueBarrierWithWaitList(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    return true;
}
inline bool clEnqueueBarrierHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueBarrier");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueBarrierRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueBarrier(
                                                apiCommand->args.command_queue
                                                );
    return true;
}
inline bool clEnqueueWaitForEventsHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueWaitForEvents");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueWaitForEventsRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueWaitForEvents(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.num_events, 
                                                apiCommand->args.event_list ? apiCommand->captures.event_list : nullptr
                                                );
    return true;
}
inline bool clEnqueueMigrateMemObjectsHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueMigrateMemObjects");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueMigrateMemObjectsRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueMigrateMemObjects(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.num_mem_objects, 
                                                apiCommand->args.mem_objects ? apiCommand->captures.getMem_objects() : nullptr, 
                                                apiCommand->args.flags, 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.getEvent_wait_list() : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    return true;
}
inline bool clCreateBufferRpcHelperUseHostPtrZeroCopyMallocShmemHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clCreateBufferRpcHelperUseHostPtrZeroCopyMallocShmem");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClCreateBufferRpcHelperUseHostPtrZeroCopyMallocShmemRpcM*>(command);
    void *importedMallocPtrHostPtr = ctx.importClientMallocPtr(reinterpret_cast<uintptr_t>(apiCommand->args.host_ptr), ((nullptr != apiCommand->args.host_ptr) ? apiCommand->args.size : 0U), 0U);
    if((nullptr == importedMallocPtrHostPtr)  && (nullptr != apiCommand->args.host_ptr)){
        log<Verbosity::error>("Could not import client's malloced pointer : %p (size : %zuB)", apiCommand->args.host_ptr, ((nullptr != apiCommand->args.host_ptr) ? apiCommand->args.size : 0U));
        return false;
    }
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clCreateBuffer(
                                                apiCommand->args.context, 
                                                apiCommand->args.flags, 
                                                apiCommand->args.size, 
                                                reinterpret_cast<void*>(importedMallocPtrHostPtr), 
                                                apiCommand->args.errcode_ret ? &apiCommand->captures.errcode_ret : nullptr
                                                );
    return true;
}
inline bool clCreateBufferRpcHelperNotUseHostPtrZeroCopyMallocShmemHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clCreateBufferRpcHelperNotUseHostPtrZeroCopyMallocShmem");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClCreateBufferRpcHelperNotUseHostPtrZeroCopyMallocShmemRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clCreateBuffer(
                                                apiCommand->args.context, 
                                                apiCommand->args.flags, 
                                                apiCommand->args.size, 
                                                apiCommand->args.host_ptr ? apiCommand->captures.host_ptr : nullptr, 
                                                apiCommand->args.errcode_ret ? &apiCommand->captures.errcode_ret : nullptr
                                                );
    return true;
}
inline bool clCreateSubBufferHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clCreateSubBuffer");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClCreateSubBufferRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clCreateSubBuffer(
                                                apiCommand->args.buffer, 
                                                apiCommand->args.flags, 
                                                apiCommand->args.buffer_create_type, 
                                                apiCommand->args.buffer_create_info ? apiCommand->captures.buffer_create_info : nullptr, 
                                                apiCommand->args.errcode_ret ? &apiCommand->captures.errcode_ret : nullptr
                                                );
    return true;
}
inline bool clCreatePipeHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clCreatePipe");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClCreatePipeRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clCreatePipe(
                                                apiCommand->args.context, 
                                                apiCommand->args.flags, 
                                                apiCommand->args.pipe_packet_size, 
                                                apiCommand->args.pipe_max_packets, 
                                                apiCommand->args.properties ? apiCommand->captures.properties : nullptr, 
                                                apiCommand->args.errcode_ret ? &apiCommand->captures.errcode_ret : nullptr
                                                );
    return true;
}
inline bool clGetPipeInfoHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clGetPipeInfo");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClGetPipeInfoRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clGetPipeInfo(
                                                apiCommand->args.pipe, 
                                                apiCommand->args.param_name, 
                                                apiCommand->args.param_value_size, 
                                                apiCommand->args.param_value ? apiCommand->captures.param_value : nullptr, 
                                                apiCommand->args.param_value_size_ret ? &apiCommand->captures.param_value_size_ret : nullptr
                                                );
    return true;
}
inline bool clCreateImageHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clCreateImage");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClCreateImageRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clCreateImage(
                                                apiCommand->args.context, 
                                                apiCommand->args.flags, 
                                                apiCommand->args.image_format ? &apiCommand->captures.image_format : nullptr, 
                                                apiCommand->args.image_desc ? &apiCommand->captures.image_desc : nullptr, 
                                                apiCommand->args.host_ptr ? apiCommand->captures.host_ptr : nullptr, 
                                                apiCommand->args.errcode_ret ? &apiCommand->captures.errcode_ret : nullptr
                                                );
    return true;
}
inline bool clCreateImage2DHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clCreateImage2D");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClCreateImage2DRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clCreateImage2D(
                                                apiCommand->args.context, 
                                                apiCommand->args.flags, 
                                                apiCommand->args.image_format ? &apiCommand->captures.image_format : nullptr, 
                                                apiCommand->args.image_width, 
                                                apiCommand->args.image_height, 
                                                apiCommand->args.image_row_pitch, 
                                                apiCommand->args.host_ptr ? apiCommand->captures.host_ptr : nullptr, 
                                                apiCommand->args.errcode_ret ? &apiCommand->captures.errcode_ret : nullptr
                                                );
    return true;
}
inline bool clCreateImage3DHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clCreateImage3D");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClCreateImage3DRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clCreateImage3D(
                                                apiCommand->args.context, 
                                                apiCommand->args.flags, 
                                                apiCommand->args.image_format ? &apiCommand->captures.image_format : nullptr, 
                                                apiCommand->args.image_width, 
                                                apiCommand->args.image_height, 
                                                apiCommand->args.image_depth, 
                                                apiCommand->args.image_row_pitch, 
                                                apiCommand->args.image_slice_pitch, 
                                                apiCommand->args.host_ptr ? apiCommand->captures.host_ptr : nullptr, 
                                                apiCommand->args.errcode_ret ? &apiCommand->captures.errcode_ret : nullptr
                                                );
    return true;
}
inline bool clCreateSamplerHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clCreateSampler");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClCreateSamplerRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clCreateSampler(
                                                apiCommand->args.context, 
                                                apiCommand->args.normalized_coords, 
                                                apiCommand->args.addressing_mode, 
                                                apiCommand->args.filter_mode, 
                                                apiCommand->args.errcode_ret ? &apiCommand->captures.errcode_ret : nullptr
                                                );
    return true;
}
inline bool clCreateSamplerWithPropertiesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clCreateSamplerWithProperties");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClCreateSamplerWithPropertiesRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clCreateSamplerWithProperties(
                                                apiCommand->args.context, 
                                                apiCommand->args.properties ? apiCommand->captures.properties : nullptr, 
                                                apiCommand->args.errcode_ret ? &apiCommand->captures.errcode_ret : nullptr
                                                );
    return true;
}
inline bool clCreateImageWithPropertiesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clCreateImageWithProperties");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClCreateImageWithPropertiesRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clCreateImageWithProperties(
                                                apiCommand->args.context, 
                                                apiCommand->args.properties ? apiCommand->captures.getProperties() : nullptr, 
                                                apiCommand->args.flags, 
                                                apiCommand->args.image_format ? &apiCommand->captures.image_format : nullptr, 
                                                apiCommand->args.image_desc ? &apiCommand->captures.image_desc : nullptr, 
                                                apiCommand->args.host_ptr ? apiCommand->captures.getHost_ptr() : nullptr, 
                                                apiCommand->args.errcode_ret ? &apiCommand->captures.errcode_ret : nullptr
                                                );
    return true;
}
inline bool clCreateBufferWithPropertiesHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clCreateBufferWithProperties");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClCreateBufferWithPropertiesRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clCreateBufferWithProperties(
                                                apiCommand->args.context, 
                                                apiCommand->args.properties ? apiCommand->captures.getProperties() : nullptr, 
                                                apiCommand->args.flags, 
                                                apiCommand->args.size, 
                                                apiCommand->args.host_ptr ? apiCommand->captures.getHost_ptr() : nullptr, 
                                                apiCommand->args.errcode_ret ? &apiCommand->captures.errcode_ret : nullptr
                                                );
    return true;
}
inline bool clGetSupportedImageFormatsHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clGetSupportedImageFormats");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClGetSupportedImageFormatsRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clGetSupportedImageFormats(
                                                apiCommand->args.context, 
                                                apiCommand->args.flags, 
                                                apiCommand->args.image_type, 
                                                apiCommand->args.num_entries, 
                                                apiCommand->args.image_formats ? apiCommand->captures.image_formats : nullptr, 
                                                apiCommand->args.num_image_formats ? &apiCommand->captures.num_image_formats : nullptr
                                                );
    return true;
}
inline bool clSetKernelArgHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clSetKernelArg");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClSetKernelArgRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clSetKernelArg(
                                                apiCommand->args.kernel, 
                                                apiCommand->args.arg_index, 
                                                apiCommand->args.arg_size, 
                                                apiCommand->args.arg_value ? apiCommand->captures.arg_value : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to clSetKernelArg (as clSetKernelArgHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool clSetProgramSpecializationConstantHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clSetProgramSpecializationConstant");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClSetProgramSpecializationConstantRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clSetProgramSpecializationConstant(
                                                apiCommand->args.program, 
                                                apiCommand->args.spec_id, 
                                                apiCommand->args.spec_size, 
                                                apiCommand->args.spec_value ? apiCommand->captures.spec_value : nullptr
                                                );
    return true;
}
inline bool clEnqueueWriteBufferHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueWriteBuffer");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueWriteBufferRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueWriteBuffer(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.buffer, 
                                                apiCommand->args.blocking_write, 
                                                apiCommand->args.offset, 
                                                apiCommand->args.size, 
                                                apiCommand->args.ptr, 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to clEnqueueWriteBuffer (as clEnqueueWriteBufferHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool clEnqueueWriteBufferRectHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueWriteBufferRect");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueWriteBufferRectRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueWriteBufferRect(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.buffer, 
                                                apiCommand->args.blocking_write, 
                                                apiCommand->args.buffer_origin ? apiCommand->captures.buffer_origin : nullptr, 
                                                apiCommand->args.host_origin ? apiCommand->captures.host_origin : nullptr, 
                                                apiCommand->args.region ? apiCommand->captures.region : nullptr, 
                                                apiCommand->args.buffer_row_pitch, 
                                                apiCommand->args.buffer_slice_pitch, 
                                                apiCommand->args.host_row_pitch, 
                                                apiCommand->args.host_slice_pitch, 
                                                apiCommand->args.ptr, 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to clEnqueueWriteBufferRect (as clEnqueueWriteBufferRectHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool clEnqueueReadBufferHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueReadBuffer");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueReadBufferRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueReadBuffer(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.buffer, 
                                                apiCommand->args.blocking_read, 
                                                apiCommand->args.offset, 
                                                apiCommand->args.size, 
                                                apiCommand->args.ptr, 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to clEnqueueReadBuffer (as clEnqueueReadBufferHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool clEnqueueReadBufferRectHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueReadBufferRect");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueReadBufferRectRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueReadBufferRect(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.buffer, 
                                                apiCommand->args.blocking_read, 
                                                apiCommand->args.buffer_origin ? apiCommand->captures.buffer_origin : nullptr, 
                                                apiCommand->args.host_origin ? apiCommand->captures.host_origin : nullptr, 
                                                apiCommand->args.region ? apiCommand->captures.region : nullptr, 
                                                apiCommand->args.buffer_row_pitch, 
                                                apiCommand->args.buffer_slice_pitch, 
                                                apiCommand->args.host_row_pitch, 
                                                apiCommand->args.host_slice_pitch, 
                                                apiCommand->args.ptr, 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to clEnqueueReadBufferRect (as clEnqueueReadBufferRectHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool clEnqueueCopyBufferHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueCopyBuffer");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueCopyBufferRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueCopyBuffer(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.src_buffer, 
                                                apiCommand->args.dst_buffer, 
                                                apiCommand->args.src_offset, 
                                                apiCommand->args.dst_offset, 
                                                apiCommand->args.size, 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    return true;
}
inline bool clEnqueueCopyBufferRectHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueCopyBufferRect");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueCopyBufferRectRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueCopyBufferRect(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.src_buffer, 
                                                apiCommand->args.dst_buffer, 
                                                apiCommand->args.src_origin ? apiCommand->captures.src_origin : nullptr, 
                                                apiCommand->args.dst_origin ? apiCommand->captures.dst_origin : nullptr, 
                                                apiCommand->args.region ? apiCommand->captures.region : nullptr, 
                                                apiCommand->args.src_row_pitch, 
                                                apiCommand->args.src_slice_pitch, 
                                                apiCommand->args.dst_row_pitch, 
                                                apiCommand->args.dst_slice_pitch, 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    return true;
}
inline bool clEnqueueReadImageHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueReadImage");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueReadImageRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueReadImage(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.image, 
                                                apiCommand->args.blocking_read, 
                                                apiCommand->args.src_origin ? apiCommand->captures.src_origin : nullptr, 
                                                apiCommand->args.region ? apiCommand->captures.region : nullptr, 
                                                apiCommand->args.row_pitch, 
                                                apiCommand->args.slice_pitch, 
                                                apiCommand->args.ptr, 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    return true;
}
inline bool clEnqueueWriteImageHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueWriteImage");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueWriteImageRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueWriteImage(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.image, 
                                                apiCommand->args.blocking_write, 
                                                apiCommand->args.origin ? apiCommand->captures.origin : nullptr, 
                                                apiCommand->args.region ? apiCommand->captures.region : nullptr, 
                                                apiCommand->args.input_row_pitch, 
                                                apiCommand->args.input_slice_pitch, 
                                                apiCommand->args.ptr, 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    return true;
}
inline bool clEnqueueCopyImageHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueCopyImage");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueCopyImageRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueCopyImage(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.src_image, 
                                                apiCommand->args.dst_image, 
                                                apiCommand->args.src_origin ? apiCommand->captures.src_origin : nullptr, 
                                                apiCommand->args.dst_origin ? apiCommand->captures.dst_origin : nullptr, 
                                                apiCommand->args.region ? apiCommand->captures.region : nullptr, 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    return true;
}
inline bool clEnqueueCopyImageToBufferHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueCopyImageToBuffer");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueCopyImageToBufferRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueCopyImageToBuffer(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.src_image, 
                                                apiCommand->args.dst_buffer, 
                                                apiCommand->args.src_origin ? apiCommand->captures.src_origin : nullptr, 
                                                apiCommand->args.region ? apiCommand->captures.region : nullptr, 
                                                apiCommand->args.dst_offset, 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    return true;
}
inline bool clEnqueueCopyBufferToImageHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueCopyBufferToImage");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueCopyBufferToImageRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueCopyBufferToImage(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.src_buffer, 
                                                apiCommand->args.dst_image, 
                                                apiCommand->args.src_offset, 
                                                apiCommand->args.dst_origin ? apiCommand->captures.dst_origin : nullptr, 
                                                apiCommand->args.region ? apiCommand->captures.region : nullptr, 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    return true;
}
inline bool clEnqueueMapBufferHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueMapBuffer");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueMapBufferRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueMapBuffer(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.buffer, 
                                                apiCommand->args.blocking_map, 
                                                apiCommand->args.map_flags, 
                                                apiCommand->args.offset, 
                                                apiCommand->args.cb, 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr, 
                                                apiCommand->args.errcode_ret ? &apiCommand->captures.errcode_ret : nullptr
                                                );
    return true;
}
inline bool clEnqueueUnmapMemObjectHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueUnmapMemObject");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueUnmapMemObjectRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueUnmapMemObject(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.memobj, 
                                                apiCommand->args.mapped_ptr, 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    return true;
}
inline bool clEnqueueFillBufferHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueFillBuffer");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueFillBufferRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueFillBuffer(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.memobj, 
                                                apiCommand->args.pattern ? apiCommand->captures.getPattern() : nullptr, 
                                                apiCommand->args.patternSize, 
                                                apiCommand->args.offset, 
                                                apiCommand->args.size, 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.getEvent_wait_list() : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    return true;
}
inline bool clEnqueueFillImageHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueFillImage");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueFillImageRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueFillImage(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.image, 
                                                apiCommand->args.fill_color ? apiCommand->captures.fill_color : nullptr, 
                                                apiCommand->args.origin ? apiCommand->captures.origin : nullptr, 
                                                apiCommand->args.region ? apiCommand->captures.region : nullptr, 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    return true;
}
inline bool clWaitForEventsHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clWaitForEvents");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClWaitForEventsRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clWaitForEvents(
                                                apiCommand->args.num_events, 
                                                apiCommand->args.event_list ? apiCommand->captures.event_list : nullptr
                                                );
    return true;
}
inline bool clGetEventInfoHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clGetEventInfo");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClGetEventInfoRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clGetEventInfo(
                                                apiCommand->args.event, 
                                                apiCommand->args.param_name, 
                                                apiCommand->args.param_value_size, 
                                                apiCommand->args.param_value ? apiCommand->captures.param_value : nullptr, 
                                                apiCommand->args.param_value_size_ret ? &apiCommand->captures.param_value_size_ret : nullptr
                                                );
    return true;
}
inline bool clGetEventProfilingInfoHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clGetEventProfilingInfo");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClGetEventProfilingInfoRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clGetEventProfilingInfo(
                                                apiCommand->args.event, 
                                                apiCommand->args.param_name, 
                                                apiCommand->args.param_value_size, 
                                                apiCommand->args.param_value ? apiCommand->captures.param_value : nullptr, 
                                                apiCommand->args.param_value_size_ret ? &apiCommand->captures.param_value_size_ret : nullptr
                                                );
    return true;
}
inline bool clCreateUserEventHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clCreateUserEvent");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClCreateUserEventRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clCreateUserEvent(
                                                apiCommand->args.context, 
                                                apiCommand->args.errcode_ret ? &apiCommand->captures.errcode_ret : nullptr
                                                );
    return true;
}
inline bool clSetUserEventStatusHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clSetUserEventStatus");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClSetUserEventStatusRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clSetUserEventStatus(
                                                apiCommand->args.event, 
                                                apiCommand->args.execution_status
                                                );
    return true;
}
bool clSetEventCallbackHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
inline bool clGetDeviceAndHostTimerHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clGetDeviceAndHostTimer");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClGetDeviceAndHostTimerRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clGetDeviceAndHostTimer(
                                                apiCommand->args.device, 
                                                apiCommand->args.device_timestamp ? &apiCommand->captures.device_timestamp : nullptr, 
                                                apiCommand->args.host_timestamp ? &apiCommand->captures.host_timestamp : nullptr
                                                );
    return true;
}
inline bool clGetHostTimerHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clGetHostTimer");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClGetHostTimerRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clGetHostTimer(
                                                apiCommand->args.device, 
                                                apiCommand->args.host_timestamp ? &apiCommand->captures.host_timestamp : nullptr
                                                );
    return true;
}
bool clSVMAllocHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
bool clSVMFreeHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
bool clEnqueueSVMMapHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
bool clEnqueueSVMUnmapHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
inline bool clSetKernelArgSVMPointerHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clSetKernelArgSVMPointer");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClSetKernelArgSVMPointerRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clSetKernelArgSVMPointer(
                                                apiCommand->args.kernel, 
                                                apiCommand->args.argIndex, 
                                                apiCommand->args.argValue
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to clSetKernelArgSVMPointer (as clSetKernelArgSVMPointerHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool clSetKernelExecInfoHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clSetKernelExecInfo");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClSetKernelExecInfoRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clSetKernelExecInfo(
                                                apiCommand->args.kernel, 
                                                apiCommand->args.param_name, 
                                                apiCommand->args.param_value_size, 
                                                apiCommand->args.param_value ? apiCommand->captures.param_value : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to clSetKernelExecInfo (as clSetKernelExecInfoHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool clEnqueueSVMMemFillHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueSVMMemFill");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueSVMMemFillRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueSVMMemFill(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.svm_ptr, 
                                                apiCommand->args.pattern ? apiCommand->captures.getPattern() : nullptr, 
                                                apiCommand->args.patternSize, 
                                                apiCommand->args.size, 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.getEvent_wait_list() : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    return true;
}
inline bool clEnqueueSVMMigrateMemHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueSVMMigrateMem");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueSVMMigrateMemRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueSVMMigrateMem(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.num_svm_pointers, 
                                                apiCommand->args.svm_pointers ? apiCommand->captures.getSvm_pointers() : nullptr, 
                                                apiCommand->args.sizes ? apiCommand->captures.getSizes() : nullptr, 
                                                apiCommand->args.flags, 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.getEvent_wait_list() : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    return true;
}
inline bool clEnqueueSVMMemcpyHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueSVMMemcpy");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueSVMMemcpyRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueSVMMemcpy(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.blocking, 
                                                apiCommand->args.dst_ptr, 
                                                apiCommand->args.src_ptr, 
                                                apiCommand->args.size, 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to clEnqueueSVMMemcpy (as clEnqueueSVMMemcpyHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
bool clEnqueueSVMFreeHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
inline bool clCreateSubDevicesEXTHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clCreateSubDevicesEXT");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClCreateSubDevicesEXTRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Extensions::clCreateSubDevicesEXT(
                                                apiCommand->args.in_device, 
                                                apiCommand->args.properties ? apiCommand->captures.getProperties() : nullptr, 
                                                apiCommand->args.num_entries, 
                                                apiCommand->args.out_devices ? apiCommand->captures.getOut_devices() : nullptr, 
                                                apiCommand->args.num_devices ? &apiCommand->captures.num_devices : nullptr
                                                );
    return true;
}
inline bool clReleaseDeviceEXTHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clReleaseDeviceEXT");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClReleaseDeviceEXTRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Extensions::clReleaseDeviceEXT(
                                                apiCommand->args.device
                                                );
    return true;
}
inline bool clRetainDeviceEXTHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clRetainDeviceEXT");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClRetainDeviceEXTRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Extensions::clRetainDeviceEXT(
                                                apiCommand->args.device
                                                );
    return true;
}
inline bool clGetKernelSubGroupInfoKHRHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clGetKernelSubGroupInfoKHR");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClGetKernelSubGroupInfoKHRRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Extensions::clGetKernelSubGroupInfoKHR(
                                                apiCommand->args.kernel, 
                                                apiCommand->args.device, 
                                                apiCommand->args.param_name, 
                                                apiCommand->args.input_value_size, 
                                                apiCommand->args.input_value ? apiCommand->captures.getInput_value() : nullptr, 
                                                apiCommand->args.param_value_size, 
                                                apiCommand->args.param_value ? apiCommand->captures.getParam_value() : nullptr, 
                                                apiCommand->args.param_value_size_ret ? &apiCommand->captures.param_value_size_ret : nullptr
                                                );
    return true;
}
inline bool clGetKernelSuggestedLocalWorkSizeKHRHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clGetKernelSuggestedLocalWorkSizeKHR");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClGetKernelSuggestedLocalWorkSizeKHRRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Extensions::clGetKernelSuggestedLocalWorkSizeKHR(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.kernel, 
                                                apiCommand->args.work_dim, 
                                                apiCommand->args.global_work_offset ? apiCommand->captures.getGlobal_work_offset() : nullptr, 
                                                apiCommand->args.global_work_size ? apiCommand->captures.getGlobal_work_size() : nullptr, 
                                                apiCommand->args.suggested_local_work_size ? apiCommand->captures.getSuggested_local_work_size() : nullptr
                                                );
    return true;
}
inline bool clEnqueueMemFillINTELHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueMemFillINTEL");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueMemFillINTELRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Extensions::clEnqueueMemFillINTEL(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.dstPtr, 
                                                apiCommand->args.pattern ? apiCommand->captures.getPattern() : nullptr, 
                                                apiCommand->args.patternSize, 
                                                apiCommand->args.size, 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.getEvent_wait_list() : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    return true;
}
inline bool clEnqueueMemcpyINTELHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueMemcpyINTEL");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueMemcpyINTELRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Extensions::clEnqueueMemcpyINTEL(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.blocking, 
                                                apiCommand->args.dstPtr, 
                                                apiCommand->args.srcPtr, 
                                                apiCommand->args.size, 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to clEnqueueMemcpyINTEL (as clEnqueueMemcpyINTELHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool clSetKernelArgMemPointerINTELHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clSetKernelArgMemPointerINTEL");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClSetKernelArgMemPointerINTELRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Extensions::clSetKernelArgMemPointerINTEL(
                                                apiCommand->args.kernel, 
                                                apiCommand->args.argIndex, 
                                                apiCommand->args.argValue
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to clSetKernelArgMemPointerINTEL (as clSetKernelArgMemPointerINTELHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool clGetMemAllocInfoINTELHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clGetMemAllocInfoINTEL");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClGetMemAllocInfoINTELRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Extensions::clGetMemAllocInfoINTEL(
                                                apiCommand->args.context, 
                                                apiCommand->args.ptr, 
                                                apiCommand->args.param_name, 
                                                apiCommand->args.param_value_size, 
                                                apiCommand->args.param_value ? apiCommand->captures.param_value : nullptr, 
                                                apiCommand->args.param_value_size_ret ? &apiCommand->captures.param_value_size_ret : nullptr
                                                );
    return true;
}
inline bool clDeviceMemAllocINTELHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clDeviceMemAllocINTEL");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClDeviceMemAllocINTELRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Extensions::clDeviceMemAllocINTEL(
                                                apiCommand->args.context, 
                                                apiCommand->args.device, 
                                                apiCommand->args.properties ? apiCommand->captures.properties : nullptr, 
                                                apiCommand->args.size, 
                                                apiCommand->args.alignment, 
                                                apiCommand->args.errcode_ret ? &apiCommand->captures.errcode_ret : nullptr
                                                );
    return true;
}
bool clHostMemAllocINTELHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
bool clSharedMemAllocINTELHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
bool clMemFreeINTELHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
bool clMemBlockingFreeINTELHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize);
inline bool clEnqueueMigrateMemINTELHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueMigrateMemINTEL");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueMigrateMemINTELRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Extensions::clEnqueueMigrateMemINTEL(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.ptr, 
                                                apiCommand->args.size, 
                                                apiCommand->args.flags, 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    return true;
}
inline bool clGetDeviceGlobalVariablePointerINTELHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clGetDeviceGlobalVariablePointerINTEL");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClGetDeviceGlobalVariablePointerINTELRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Extensions::clGetDeviceGlobalVariablePointerINTEL(
                                                apiCommand->args.device, 
                                                apiCommand->args.program, 
                                                apiCommand->args.globalVariableName ? apiCommand->captures.globalVariableName : nullptr, 
                                                apiCommand->args.globalVariableSizeRet ? &apiCommand->captures.globalVariableSizeRet : nullptr, 
                                                apiCommand->args.globalVariablePointerRet ? &apiCommand->captures.globalVariablePointerRet : nullptr
                                                );
    return true;
}
inline bool clCreateBufferRpcHelperNotUseHostPtrZeroCopyMallocShmem_UsmHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clCreateBufferRpcHelperNotUseHostPtrZeroCopyMallocShmem_Usm");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClCreateBufferRpcHelperNotUseHostPtrZeroCopyMallocShmem_UsmRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clCreateBuffer(
                                                apiCommand->args.context, 
                                                apiCommand->args.flags, 
                                                apiCommand->args.size, 
                                                apiCommand->args.host_ptr, 
                                                apiCommand->args.errcode_ret ? &apiCommand->captures.errcode_ret : nullptr
                                                );
    return true;
}
inline bool clEnqueueWriteBuffer_LocalHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueWriteBuffer_Local");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueWriteBuffer_LocalRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueWriteBuffer(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.buffer, 
                                                apiCommand->args.blocking_write, 
                                                apiCommand->args.offset, 
                                                apiCommand->args.size, 
                                                apiCommand->args.ptr, 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to clEnqueueWriteBuffer_Local (as clEnqueueWriteBuffer_LocalHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool clEnqueueWriteBuffer_UsmHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueWriteBuffer_Usm");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueWriteBuffer_UsmRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueWriteBuffer(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.buffer, 
                                                apiCommand->args.blocking_write, 
                                                apiCommand->args.offset, 
                                                apiCommand->args.size, 
                                                apiCommand->args.ptr, 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to clEnqueueWriteBuffer_Usm (as clEnqueueWriteBuffer_UsmHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool clEnqueueWriteBuffer_SharedHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueWriteBuffer_Shared");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueWriteBuffer_SharedRpcM*>(command);
    void *importedMallocPtrPtr = ctx.importClientMallocPtr(reinterpret_cast<uintptr_t>(apiCommand->args.ptr), apiCommand->args.size, 0U);
    if((nullptr == importedMallocPtrPtr)  && (nullptr != apiCommand->args.ptr)){
        log<Verbosity::error>("Could not import client's malloced pointer : %p (size : %zuB)", apiCommand->args.ptr, apiCommand->args.size);
        return false;
    }
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueWriteBuffer(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.buffer, 
                                                apiCommand->args.blocking_write, 
                                                apiCommand->args.offset, 
                                                apiCommand->args.size, 
                                                reinterpret_cast<const void*>(importedMallocPtrPtr), 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to clEnqueueWriteBuffer_Shared (as clEnqueueWriteBuffer_SharedHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool clEnqueueWriteBufferRect_LocalHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueWriteBufferRect_Local");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueWriteBufferRect_LocalRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueWriteBufferRect(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.buffer, 
                                                apiCommand->args.blocking_write, 
                                                apiCommand->args.buffer_origin ? apiCommand->captures.buffer_origin : nullptr, 
                                                apiCommand->args.host_origin ? apiCommand->captures.host_origin : nullptr, 
                                                apiCommand->args.region ? apiCommand->captures.region : nullptr, 
                                                apiCommand->args.buffer_row_pitch, 
                                                apiCommand->args.buffer_slice_pitch, 
                                                apiCommand->args.host_row_pitch, 
                                                apiCommand->args.host_slice_pitch, 
                                                apiCommand->args.ptr, 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to clEnqueueWriteBufferRect_Local (as clEnqueueWriteBufferRect_LocalHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool clEnqueueWriteBufferRect_UsmHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueWriteBufferRect_Usm");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueWriteBufferRect_UsmRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueWriteBufferRect(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.buffer, 
                                                apiCommand->args.blocking_write, 
                                                apiCommand->args.buffer_origin ? apiCommand->captures.buffer_origin : nullptr, 
                                                apiCommand->args.host_origin ? apiCommand->captures.host_origin : nullptr, 
                                                apiCommand->args.region ? apiCommand->captures.region : nullptr, 
                                                apiCommand->args.buffer_row_pitch, 
                                                apiCommand->args.buffer_slice_pitch, 
                                                apiCommand->args.host_row_pitch, 
                                                apiCommand->args.host_slice_pitch, 
                                                apiCommand->args.ptr, 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to clEnqueueWriteBufferRect_Usm (as clEnqueueWriteBufferRect_UsmHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool clEnqueueWriteBufferRect_SharedHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueWriteBufferRect_Shared");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueWriteBufferRect_SharedRpcM*>(command);
    void *importedMallocPtrPtr = ctx.importClientMallocPtr(reinterpret_cast<uintptr_t>(apiCommand->args.ptr), Cal::Utils::getBufferRectSizeInBytes(apiCommand->captures.host_origin, apiCommand->captures.region, apiCommand->args.host_row_pitch, apiCommand->args.host_slice_pitch), 0U);
    if((nullptr == importedMallocPtrPtr)  && (nullptr != apiCommand->args.ptr)){
        log<Verbosity::error>("Could not import client's malloced pointer : %p (size : %zuB)", apiCommand->args.ptr, Cal::Utils::getBufferRectSizeInBytes(apiCommand->captures.host_origin, apiCommand->captures.region, apiCommand->args.host_row_pitch, apiCommand->args.host_slice_pitch));
        return false;
    }
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueWriteBufferRect(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.buffer, 
                                                apiCommand->args.blocking_write, 
                                                apiCommand->args.buffer_origin ? apiCommand->captures.buffer_origin : nullptr, 
                                                apiCommand->args.host_origin ? apiCommand->captures.host_origin : nullptr, 
                                                apiCommand->args.region ? apiCommand->captures.region : nullptr, 
                                                apiCommand->args.buffer_row_pitch, 
                                                apiCommand->args.buffer_slice_pitch, 
                                                apiCommand->args.host_row_pitch, 
                                                apiCommand->args.host_slice_pitch, 
                                                reinterpret_cast<const void*>(importedMallocPtrPtr), 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to clEnqueueWriteBufferRect_Shared (as clEnqueueWriteBufferRect_SharedHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool clEnqueueReadBuffer_LocalHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueReadBuffer_Local");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueReadBuffer_LocalRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueReadBuffer(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.buffer, 
                                                apiCommand->args.blocking_read, 
                                                apiCommand->args.offset, 
                                                apiCommand->args.size, 
                                                apiCommand->args.ptr, 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to clEnqueueReadBuffer_Local (as clEnqueueReadBuffer_LocalHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool clEnqueueReadBuffer_UsmHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueReadBuffer_Usm");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueReadBuffer_UsmRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueReadBuffer(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.buffer, 
                                                apiCommand->args.blocking_read, 
                                                apiCommand->args.offset, 
                                                apiCommand->args.size, 
                                                apiCommand->args.ptr, 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to clEnqueueReadBuffer_Usm (as clEnqueueReadBuffer_UsmHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool clEnqueueReadBuffer_SharedHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueReadBuffer_Shared");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueReadBuffer_SharedRpcM*>(command);
    void *importedMallocPtrPtr = ctx.importClientMallocPtr(reinterpret_cast<uintptr_t>(apiCommand->args.ptr), apiCommand->args.size, 0U);
    if((nullptr == importedMallocPtrPtr)  && (nullptr != apiCommand->args.ptr)){
        log<Verbosity::error>("Could not import client's malloced pointer : %p (size : %zuB)", apiCommand->args.ptr, apiCommand->args.size);
        return false;
    }
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueReadBuffer(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.buffer, 
                                                apiCommand->args.blocking_read, 
                                                apiCommand->args.offset, 
                                                apiCommand->args.size, 
                                                reinterpret_cast<void*>(importedMallocPtrPtr), 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to clEnqueueReadBuffer_Shared (as clEnqueueReadBuffer_SharedHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool clEnqueueReadBufferRect_LocalHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueReadBufferRect_Local");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueReadBufferRect_LocalRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueReadBufferRect(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.buffer, 
                                                apiCommand->args.blocking_read, 
                                                apiCommand->args.buffer_origin ? apiCommand->captures.buffer_origin : nullptr, 
                                                apiCommand->args.host_origin ? apiCommand->captures.host_origin : nullptr, 
                                                apiCommand->args.region ? apiCommand->captures.region : nullptr, 
                                                apiCommand->args.buffer_row_pitch, 
                                                apiCommand->args.buffer_slice_pitch, 
                                                apiCommand->args.host_row_pitch, 
                                                apiCommand->args.host_slice_pitch, 
                                                apiCommand->args.ptr, 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to clEnqueueReadBufferRect_Local (as clEnqueueReadBufferRect_LocalHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool clEnqueueReadBufferRect_UsmHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueReadBufferRect_Usm");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueReadBufferRect_UsmRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueReadBufferRect(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.buffer, 
                                                apiCommand->args.blocking_read, 
                                                apiCommand->args.buffer_origin ? apiCommand->captures.buffer_origin : nullptr, 
                                                apiCommand->args.host_origin ? apiCommand->captures.host_origin : nullptr, 
                                                apiCommand->args.region ? apiCommand->captures.region : nullptr, 
                                                apiCommand->args.buffer_row_pitch, 
                                                apiCommand->args.buffer_slice_pitch, 
                                                apiCommand->args.host_row_pitch, 
                                                apiCommand->args.host_slice_pitch, 
                                                apiCommand->args.ptr, 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to clEnqueueReadBufferRect_Usm (as clEnqueueReadBufferRect_UsmHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool clEnqueueReadBufferRect_SharedHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueReadBufferRect_Shared");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueReadBufferRect_SharedRpcM*>(command);
    void *importedMallocPtrPtr = ctx.importClientMallocPtr(reinterpret_cast<uintptr_t>(apiCommand->args.ptr), Cal::Utils::getBufferRectSizeInBytes(apiCommand->captures.host_origin, apiCommand->captures.region, apiCommand->args.host_row_pitch, apiCommand->args.host_slice_pitch), 0U);
    if((nullptr == importedMallocPtrPtr)  && (nullptr != apiCommand->args.ptr)){
        log<Verbosity::error>("Could not import client's malloced pointer : %p (size : %zuB)", apiCommand->args.ptr, Cal::Utils::getBufferRectSizeInBytes(apiCommand->captures.host_origin, apiCommand->captures.region, apiCommand->args.host_row_pitch, apiCommand->args.host_slice_pitch));
        return false;
    }
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueReadBufferRect(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.buffer, 
                                                apiCommand->args.blocking_read, 
                                                apiCommand->args.buffer_origin ? apiCommand->captures.buffer_origin : nullptr, 
                                                apiCommand->args.host_origin ? apiCommand->captures.host_origin : nullptr, 
                                                apiCommand->args.region ? apiCommand->captures.region : nullptr, 
                                                apiCommand->args.buffer_row_pitch, 
                                                apiCommand->args.buffer_slice_pitch, 
                                                apiCommand->args.host_row_pitch, 
                                                apiCommand->args.host_slice_pitch, 
                                                reinterpret_cast<void*>(importedMallocPtrPtr), 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to clEnqueueReadBufferRect_Shared (as clEnqueueReadBufferRect_SharedHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool clEnqueueSVMMemcpy_Local_LocalHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueSVMMemcpy_Local_Local");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueSVMMemcpy_Local_LocalRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueSVMMemcpy(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.blocking, 
                                                channel.decodeLocalPtrFromHeapOffset(apiCommand->args.dst_ptr), 
                                                apiCommand->args.src_ptr, 
                                                apiCommand->args.size, 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to clEnqueueSVMMemcpy_Local_Local (as clEnqueueSVMMemcpy_Local_LocalHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool clEnqueueSVMMemcpy_Local_UsmHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueSVMMemcpy_Local_Usm");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueSVMMemcpy_Local_UsmRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueSVMMemcpy(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.blocking, 
                                                channel.decodeLocalPtrFromHeapOffset(apiCommand->args.dst_ptr), 
                                                apiCommand->args.src_ptr, 
                                                apiCommand->args.size, 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to clEnqueueSVMMemcpy_Local_Usm (as clEnqueueSVMMemcpy_Local_UsmHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool clEnqueueSVMMemcpy_Local_SharedHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueSVMMemcpy_Local_Shared");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueSVMMemcpy_Local_SharedRpcM*>(command);
    void *importedMallocPtrSrcPtr = ctx.importClientMallocPtr(reinterpret_cast<uintptr_t>(apiCommand->args.src_ptr), apiCommand->args.size, 0U);
    if((nullptr == importedMallocPtrSrcPtr)  && (nullptr != apiCommand->args.src_ptr)){
        log<Verbosity::error>("Could not import client's malloced pointer : %p (size : %zuB)", apiCommand->args.src_ptr, apiCommand->args.size);
        return false;
    }
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueSVMMemcpy(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.blocking, 
                                                channel.decodeLocalPtrFromHeapOffset(apiCommand->args.dst_ptr), 
                                                reinterpret_cast<const void*>(importedMallocPtrSrcPtr), 
                                                apiCommand->args.size, 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to clEnqueueSVMMemcpy_Local_Shared (as clEnqueueSVMMemcpy_Local_SharedHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool clEnqueueSVMMemcpy_Usm_LocalHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueSVMMemcpy_Usm_Local");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueSVMMemcpy_Usm_LocalRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueSVMMemcpy(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.blocking, 
                                                apiCommand->args.dst_ptr, 
                                                apiCommand->args.src_ptr, 
                                                apiCommand->args.size, 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to clEnqueueSVMMemcpy_Usm_Local (as clEnqueueSVMMemcpy_Usm_LocalHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool clEnqueueSVMMemcpy_Usm_UsmHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueSVMMemcpy_Usm_Usm");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueSVMMemcpy_Usm_UsmRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueSVMMemcpy(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.blocking, 
                                                apiCommand->args.dst_ptr, 
                                                apiCommand->args.src_ptr, 
                                                apiCommand->args.size, 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to clEnqueueSVMMemcpy_Usm_Usm (as clEnqueueSVMMemcpy_Usm_UsmHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool clEnqueueSVMMemcpy_Usm_SharedHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueSVMMemcpy_Usm_Shared");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueSVMMemcpy_Usm_SharedRpcM*>(command);
    void *importedMallocPtrSrcPtr = ctx.importClientMallocPtr(reinterpret_cast<uintptr_t>(apiCommand->args.src_ptr), apiCommand->args.size, 0U);
    if((nullptr == importedMallocPtrSrcPtr)  && (nullptr != apiCommand->args.src_ptr)){
        log<Verbosity::error>("Could not import client's malloced pointer : %p (size : %zuB)", apiCommand->args.src_ptr, apiCommand->args.size);
        return false;
    }
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueSVMMemcpy(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.blocking, 
                                                apiCommand->args.dst_ptr, 
                                                reinterpret_cast<const void*>(importedMallocPtrSrcPtr), 
                                                apiCommand->args.size, 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to clEnqueueSVMMemcpy_Usm_Shared (as clEnqueueSVMMemcpy_Usm_SharedHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool clEnqueueSVMMemcpy_Shared_LocalHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueSVMMemcpy_Shared_Local");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueSVMMemcpy_Shared_LocalRpcM*>(command);
    void *importedMallocPtrDstPtr = ctx.importClientMallocPtr(reinterpret_cast<uintptr_t>(apiCommand->args.dst_ptr), apiCommand->args.size, 0U);
    if((nullptr == importedMallocPtrDstPtr)  && (nullptr != apiCommand->args.dst_ptr)){
        log<Verbosity::error>("Could not import client's malloced pointer : %p (size : %zuB)", apiCommand->args.dst_ptr, apiCommand->args.size);
        return false;
    }
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueSVMMemcpy(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.blocking, 
                                                reinterpret_cast<void*>(importedMallocPtrDstPtr), 
                                                apiCommand->args.src_ptr, 
                                                apiCommand->args.size, 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to clEnqueueSVMMemcpy_Shared_Local (as clEnqueueSVMMemcpy_Shared_LocalHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool clEnqueueSVMMemcpy_Shared_UsmHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueSVMMemcpy_Shared_Usm");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueSVMMemcpy_Shared_UsmRpcM*>(command);
    void *importedMallocPtrDstPtr = ctx.importClientMallocPtr(reinterpret_cast<uintptr_t>(apiCommand->args.dst_ptr), apiCommand->args.size, 0U);
    if((nullptr == importedMallocPtrDstPtr)  && (nullptr != apiCommand->args.dst_ptr)){
        log<Verbosity::error>("Could not import client's malloced pointer : %p (size : %zuB)", apiCommand->args.dst_ptr, apiCommand->args.size);
        return false;
    }
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueSVMMemcpy(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.blocking, 
                                                reinterpret_cast<void*>(importedMallocPtrDstPtr), 
                                                apiCommand->args.src_ptr, 
                                                apiCommand->args.size, 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to clEnqueueSVMMemcpy_Shared_Usm (as clEnqueueSVMMemcpy_Shared_UsmHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool clEnqueueSVMMemcpy_Shared_SharedHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueSVMMemcpy_Shared_Shared");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueSVMMemcpy_Shared_SharedRpcM*>(command);
    void *importedMallocPtrDstPtr = ctx.importClientMallocPtr(reinterpret_cast<uintptr_t>(apiCommand->args.dst_ptr), apiCommand->args.size, 0U);
    if((nullptr == importedMallocPtrDstPtr)  && (nullptr != apiCommand->args.dst_ptr)){
        log<Verbosity::error>("Could not import client's malloced pointer : %p (size : %zuB)", apiCommand->args.dst_ptr, apiCommand->args.size);
        return false;
    }
    void *importedMallocPtrSrcPtr = ctx.importClientMallocPtr(reinterpret_cast<uintptr_t>(apiCommand->args.src_ptr), apiCommand->args.size, 0U);
    if((nullptr == importedMallocPtrSrcPtr)  && (nullptr != apiCommand->args.src_ptr)){
        log<Verbosity::error>("Could not import client's malloced pointer : %p (size : %zuB)", apiCommand->args.src_ptr, apiCommand->args.size);
        return false;
    }
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueSVMMemcpy(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.blocking, 
                                                reinterpret_cast<void*>(importedMallocPtrDstPtr), 
                                                reinterpret_cast<const void*>(importedMallocPtrSrcPtr), 
                                                apiCommand->args.size, 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to clEnqueueSVMMemcpy_Shared_Shared (as clEnqueueSVMMemcpy_Shared_SharedHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool clEnqueueMemcpyINTEL_Local_LocalHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueMemcpyINTEL_Local_Local");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueMemcpyINTEL_Local_LocalRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Extensions::clEnqueueMemcpyINTEL(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.blocking, 
                                                apiCommand->args.dstPtr, 
                                                apiCommand->args.srcPtr, 
                                                apiCommand->args.size, 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to clEnqueueMemcpyINTEL_Local_Local (as clEnqueueMemcpyINTEL_Local_LocalHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool clEnqueueMemcpyINTEL_Local_UsmHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueMemcpyINTEL_Local_Usm");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueMemcpyINTEL_Local_UsmRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Extensions::clEnqueueMemcpyINTEL(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.blocking, 
                                                apiCommand->args.dstPtr, 
                                                apiCommand->args.srcPtr, 
                                                apiCommand->args.size, 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to clEnqueueMemcpyINTEL_Local_Usm (as clEnqueueMemcpyINTEL_Local_UsmHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool clEnqueueMemcpyINTEL_Local_SharedHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueMemcpyINTEL_Local_Shared");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueMemcpyINTEL_Local_SharedRpcM*>(command);
    void *importedMallocPtrSrcPtr = ctx.importClientMallocPtr(reinterpret_cast<uintptr_t>(apiCommand->args.srcPtr), apiCommand->args.size, 0U);
    if((nullptr == importedMallocPtrSrcPtr)  && (nullptr != apiCommand->args.srcPtr)){
        log<Verbosity::error>("Could not import client's malloced pointer : %p (size : %zuB)", apiCommand->args.srcPtr, apiCommand->args.size);
        return false;
    }
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Extensions::clEnqueueMemcpyINTEL(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.blocking, 
                                                apiCommand->args.dstPtr, 
                                                reinterpret_cast<const void*>(importedMallocPtrSrcPtr), 
                                                apiCommand->args.size, 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to clEnqueueMemcpyINTEL_Local_Shared (as clEnqueueMemcpyINTEL_Local_SharedHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool clEnqueueMemcpyINTEL_Usm_LocalHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueMemcpyINTEL_Usm_Local");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueMemcpyINTEL_Usm_LocalRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Extensions::clEnqueueMemcpyINTEL(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.blocking, 
                                                apiCommand->args.dstPtr, 
                                                apiCommand->args.srcPtr, 
                                                apiCommand->args.size, 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to clEnqueueMemcpyINTEL_Usm_Local (as clEnqueueMemcpyINTEL_Usm_LocalHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool clEnqueueMemcpyINTEL_Usm_UsmHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueMemcpyINTEL_Usm_Usm");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueMemcpyINTEL_Usm_UsmRpcM*>(command);
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Extensions::clEnqueueMemcpyINTEL(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.blocking, 
                                                apiCommand->args.dstPtr, 
                                                apiCommand->args.srcPtr, 
                                                apiCommand->args.size, 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to clEnqueueMemcpyINTEL_Usm_Usm (as clEnqueueMemcpyINTEL_Usm_UsmHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool clEnqueueMemcpyINTEL_Usm_SharedHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueMemcpyINTEL_Usm_Shared");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueMemcpyINTEL_Usm_SharedRpcM*>(command);
    void *importedMallocPtrSrcPtr = ctx.importClientMallocPtr(reinterpret_cast<uintptr_t>(apiCommand->args.srcPtr), apiCommand->args.size, 0U);
    if((nullptr == importedMallocPtrSrcPtr)  && (nullptr != apiCommand->args.srcPtr)){
        log<Verbosity::error>("Could not import client's malloced pointer : %p (size : %zuB)", apiCommand->args.srcPtr, apiCommand->args.size);
        return false;
    }
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Extensions::clEnqueueMemcpyINTEL(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.blocking, 
                                                apiCommand->args.dstPtr, 
                                                reinterpret_cast<const void*>(importedMallocPtrSrcPtr), 
                                                apiCommand->args.size, 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to clEnqueueMemcpyINTEL_Usm_Shared (as clEnqueueMemcpyINTEL_Usm_SharedHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool clEnqueueMemcpyINTEL_Shared_LocalHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueMemcpyINTEL_Shared_Local");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueMemcpyINTEL_Shared_LocalRpcM*>(command);
    void *importedMallocPtrDstPtr = ctx.importClientMallocPtr(reinterpret_cast<uintptr_t>(apiCommand->args.dstPtr), apiCommand->args.size, 0U);
    if((nullptr == importedMallocPtrDstPtr)  && (nullptr != apiCommand->args.dstPtr)){
        log<Verbosity::error>("Could not import client's malloced pointer : %p (size : %zuB)", apiCommand->args.dstPtr, apiCommand->args.size);
        return false;
    }
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Extensions::clEnqueueMemcpyINTEL(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.blocking, 
                                                reinterpret_cast<void*>(importedMallocPtrDstPtr), 
                                                apiCommand->args.srcPtr, 
                                                apiCommand->args.size, 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to clEnqueueMemcpyINTEL_Shared_Local (as clEnqueueMemcpyINTEL_Shared_LocalHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool clEnqueueMemcpyINTEL_Shared_UsmHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueMemcpyINTEL_Shared_Usm");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueMemcpyINTEL_Shared_UsmRpcM*>(command);
    void *importedMallocPtrDstPtr = ctx.importClientMallocPtr(reinterpret_cast<uintptr_t>(apiCommand->args.dstPtr), apiCommand->args.size, 0U);
    if((nullptr == importedMallocPtrDstPtr)  && (nullptr != apiCommand->args.dstPtr)){
        log<Verbosity::error>("Could not import client's malloced pointer : %p (size : %zuB)", apiCommand->args.dstPtr, apiCommand->args.size);
        return false;
    }
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Extensions::clEnqueueMemcpyINTEL(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.blocking, 
                                                reinterpret_cast<void*>(importedMallocPtrDstPtr), 
                                                apiCommand->args.srcPtr, 
                                                apiCommand->args.size, 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to clEnqueueMemcpyINTEL_Shared_Usm (as clEnqueueMemcpyINTEL_Shared_UsmHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}
inline bool clEnqueueMemcpyINTEL_Shared_SharedHandler(Provider &service, Cal::Rpc::ChannelServer &channel, ClientContext &ctx, Cal::Rpc::RpcMessageHeader*command, size_t commandMaxSize) {
    log<Verbosity::bloat>("Servicing RPC request for clEnqueueMemcpyINTEL_Shared_Shared");
    auto apiCommand = reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueMemcpyINTEL_Shared_SharedRpcM*>(command);
    void *importedMallocPtrDstPtr = ctx.importClientMallocPtr(reinterpret_cast<uintptr_t>(apiCommand->args.dstPtr), apiCommand->args.size, 0U);
    if((nullptr == importedMallocPtrDstPtr)  && (nullptr != apiCommand->args.dstPtr)){
        log<Verbosity::error>("Could not import client's malloced pointer : %p (size : %zuB)", apiCommand->args.dstPtr, apiCommand->args.size);
        return false;
    }
    void *importedMallocPtrSrcPtr = ctx.importClientMallocPtr(reinterpret_cast<uintptr_t>(apiCommand->args.srcPtr), apiCommand->args.size, 0U);
    if((nullptr == importedMallocPtrSrcPtr)  && (nullptr != apiCommand->args.srcPtr)){
        log<Verbosity::error>("Could not import client's malloced pointer : %p (size : %zuB)", apiCommand->args.srcPtr, apiCommand->args.size);
        return false;
    }
    apiCommand->captures.ret = Cal::Service::Apis::Ocl::Extensions::clEnqueueMemcpyINTEL(
                                                apiCommand->args.command_queue, 
                                                apiCommand->args.blocking, 
                                                reinterpret_cast<void*>(importedMallocPtrDstPtr), 
                                                reinterpret_cast<const void*>(importedMallocPtrSrcPtr), 
                                                apiCommand->args.size, 
                                                apiCommand->args.num_events_in_wait_list, 
                                                apiCommand->args.event_wait_list ? apiCommand->captures.event_wait_list : nullptr, 
                                                apiCommand->args.event ? &apiCommand->captures.event : nullptr
                                                );
    if((false == isSuccessful(apiCommand->captures.ret)) && (0 != (apiCommand->header.flags & Cal::Rpc::RpcMessageHeader::async))) {
        log<Verbosity::error>("Asynchronous call to clEnqueueMemcpyINTEL_Shared_Shared (as clEnqueueMemcpyINTEL_Shared_SharedHandler) has failed! Please rerun workload with CAL_ASYNC_CALLS=0 to debug the issue.");
        return false;
    }
    return true;
}

inline void registerGeneratedHandlersOcl(Cal::Service::Provider::RpcSubtypeHandlers &outHandlers){
    using namespace Cal::Rpc::Ocl;
    if(outHandlers.size() < ClEnqueueMemcpyINTEL_Shared_SharedRpcM::messageSubtype + 1){
        outHandlers.resize(ClEnqueueMemcpyINTEL_Shared_SharedRpcM::messageSubtype + 1);
    }
    outHandlers[ClGetPlatformInfoRpcM::messageSubtype] = clGetPlatformInfoHandler;
    outHandlers[ClGetDeviceIDsRpcM::messageSubtype] = clGetDeviceIDsHandler;
    outHandlers[ClGetDeviceInfoRpcM::messageSubtype] = clGetDeviceInfoHandler;
    outHandlers[ClCreateContextRpcM::messageSubtype] = clCreateContextHandler;
    outHandlers[ClCreateContextFromTypeRpcM::messageSubtype] = clCreateContextFromTypeHandler;
    outHandlers[ClGetContextInfoRpcM::messageSubtype] = clGetContextInfoHandler;
    outHandlers[ClSetContextDestructorCallbackRpcM::messageSubtype] = clSetContextDestructorCallbackHandler;
    outHandlers[ClSetMemObjectDestructorCallbackRpcM::messageSubtype] = clSetMemObjectDestructorCallbackHandler;
    outHandlers[ClCreateSubDevicesRpcM::messageSubtype] = clCreateSubDevicesHandler;
    outHandlers[ClCreateCommandQueueRpcM::messageSubtype] = clCreateCommandQueueHandler;
    outHandlers[ClSetDefaultDeviceCommandQueueRpcM::messageSubtype] = clSetDefaultDeviceCommandQueueHandler;
    outHandlers[ClCreateCommandQueueWithPropertiesRpcM::messageSubtype] = clCreateCommandQueueWithPropertiesHandler;
    outHandlers[ClCreateProgramWithSourceRpcM::messageSubtype] = clCreateProgramWithSourceHandler;
    outHandlers[ClCreateProgramWithILRpcM::messageSubtype] = clCreateProgramWithILHandler;
    outHandlers[ClCreateProgramWithBinaryRpcM::messageSubtype] = clCreateProgramWithBinaryHandler;
    outHandlers[ClCreateProgramWithBuiltInKernelsRpcM::messageSubtype] = clCreateProgramWithBuiltInKernelsHandler;
    outHandlers[ClBuildProgramRpcM::messageSubtype] = clBuildProgramHandler;
    outHandlers[ClCompileProgramRpcM::messageSubtype] = clCompileProgramHandler;
    outHandlers[ClLinkProgramRpcM::messageSubtype] = clLinkProgramHandler;
    outHandlers[ClGetProgramBuildInfoRpcM::messageSubtype] = clGetProgramBuildInfoHandler;
    outHandlers[ClSetProgramReleaseCallbackRpcM::messageSubtype] = clSetProgramReleaseCallbackHandler;
    outHandlers[ClCreateKernelRpcM::messageSubtype] = clCreateKernelHandler;
    outHandlers[ClCloneKernelRpcM::messageSubtype] = clCloneKernelHandler;
    outHandlers[ClCreateKernelsInProgramRpcM::messageSubtype] = clCreateKernelsInProgramHandler;
    outHandlers[ClGetCommandQueueInfoRpcM::messageSubtype] = clGetCommandQueueInfoHandler;
    outHandlers[ClGetProgramInfoRpcHelperRpcM::messageSubtype] = clGetProgramInfoRpcHelperHandler;
    outHandlers[ClGetProgramInfoGetBinariesRpcHelperRpcM::messageSubtype] = clGetProgramInfoGetBinariesRpcHelperHandler;
    outHandlers[ClGetMemObjectInfoRpcM::messageSubtype] = clGetMemObjectInfoHandler;
    outHandlers[ClGetImageInfoRpcM::messageSubtype] = clGetImageInfoHandler;
    outHandlers[ClGetSamplerInfoRpcM::messageSubtype] = clGetSamplerInfoHandler;
    outHandlers[ClGetKernelInfoRpcM::messageSubtype] = clGetKernelInfoHandler;
    outHandlers[ClGetKernelWorkGroupInfoRpcM::messageSubtype] = clGetKernelWorkGroupInfoHandler;
    outHandlers[ClGetKernelArgInfoRpcM::messageSubtype] = clGetKernelArgInfoHandler;
    outHandlers[ClGetKernelSubGroupInfoRpcM::messageSubtype] = clGetKernelSubGroupInfoHandler;
    outHandlers[ClReleaseCommandQueueRpcM::messageSubtype] = clReleaseCommandQueueHandler;
    outHandlers[ClReleaseContextRpcM::messageSubtype] = clReleaseContextHandler;
    outHandlers[ClReleaseDeviceRpcM::messageSubtype] = clReleaseDeviceHandler;
    outHandlers[ClReleaseKernelRpcM::messageSubtype] = clReleaseKernelHandler;
    outHandlers[ClReleaseSamplerRpcM::messageSubtype] = clReleaseSamplerHandler;
    outHandlers[ClReleaseProgramRpcM::messageSubtype] = clReleaseProgramHandler;
    outHandlers[ClReleaseMemObjectRpcM::messageSubtype] = clReleaseMemObjectHandler;
    outHandlers[ClReleaseEventRpcM::messageSubtype] = clReleaseEventHandler;
    outHandlers[ClRetainCommandQueueRpcM::messageSubtype] = clRetainCommandQueueHandler;
    outHandlers[ClRetainContextRpcM::messageSubtype] = clRetainContextHandler;
    outHandlers[ClRetainDeviceRpcM::messageSubtype] = clRetainDeviceHandler;
    outHandlers[ClRetainProgramRpcM::messageSubtype] = clRetainProgramHandler;
    outHandlers[ClRetainMemObjectRpcM::messageSubtype] = clRetainMemObjectHandler;
    outHandlers[ClRetainSamplerRpcM::messageSubtype] = clRetainSamplerHandler;
    outHandlers[ClRetainKernelRpcM::messageSubtype] = clRetainKernelHandler;
    outHandlers[ClRetainEventRpcM::messageSubtype] = clRetainEventHandler;
    outHandlers[ClFlushRpcM::messageSubtype] = clFlushHandler;
    outHandlers[ClFinishRpcM::messageSubtype] = clFinishHandler;
    outHandlers[ClEnqueueNDRangeKernelRpcM::messageSubtype] = clEnqueueNDRangeKernelHandler;
    outHandlers[ClEnqueueTaskRpcM::messageSubtype] = clEnqueueTaskHandler;
    outHandlers[ClEnqueueMarkerWithWaitListRpcM::messageSubtype] = clEnqueueMarkerWithWaitListHandler;
    outHandlers[ClEnqueueMarkerRpcM::messageSubtype] = clEnqueueMarkerHandler;
    outHandlers[ClEnqueueBarrierWithWaitListRpcM::messageSubtype] = clEnqueueBarrierWithWaitListHandler;
    outHandlers[ClEnqueueBarrierRpcM::messageSubtype] = clEnqueueBarrierHandler;
    outHandlers[ClEnqueueWaitForEventsRpcM::messageSubtype] = clEnqueueWaitForEventsHandler;
    outHandlers[ClEnqueueMigrateMemObjectsRpcM::messageSubtype] = clEnqueueMigrateMemObjectsHandler;
    outHandlers[ClCreateBufferRpcHelperUseHostPtrZeroCopyMallocShmemRpcM::messageSubtype] = clCreateBufferRpcHelperUseHostPtrZeroCopyMallocShmemHandler;
    outHandlers[ClCreateBufferRpcHelperNotUseHostPtrZeroCopyMallocShmemRpcM::messageSubtype] = clCreateBufferRpcHelperNotUseHostPtrZeroCopyMallocShmemHandler;
    outHandlers[ClCreateSubBufferRpcM::messageSubtype] = clCreateSubBufferHandler;
    outHandlers[ClCreatePipeRpcM::messageSubtype] = clCreatePipeHandler;
    outHandlers[ClGetPipeInfoRpcM::messageSubtype] = clGetPipeInfoHandler;
    outHandlers[ClCreateImageRpcM::messageSubtype] = clCreateImageHandler;
    outHandlers[ClCreateImage2DRpcM::messageSubtype] = clCreateImage2DHandler;
    outHandlers[ClCreateImage3DRpcM::messageSubtype] = clCreateImage3DHandler;
    outHandlers[ClCreateSamplerRpcM::messageSubtype] = clCreateSamplerHandler;
    outHandlers[ClCreateSamplerWithPropertiesRpcM::messageSubtype] = clCreateSamplerWithPropertiesHandler;
    outHandlers[ClCreateImageWithPropertiesRpcM::messageSubtype] = clCreateImageWithPropertiesHandler;
    outHandlers[ClCreateBufferWithPropertiesRpcM::messageSubtype] = clCreateBufferWithPropertiesHandler;
    outHandlers[ClGetSupportedImageFormatsRpcM::messageSubtype] = clGetSupportedImageFormatsHandler;
    outHandlers[ClSetKernelArgRpcM::messageSubtype] = clSetKernelArgHandler;
    outHandlers[ClSetProgramSpecializationConstantRpcM::messageSubtype] = clSetProgramSpecializationConstantHandler;
    outHandlers[ClEnqueueWriteBufferRpcM::messageSubtype] = clEnqueueWriteBufferHandler;
    outHandlers[ClEnqueueWriteBufferRectRpcM::messageSubtype] = clEnqueueWriteBufferRectHandler;
    outHandlers[ClEnqueueReadBufferRpcM::messageSubtype] = clEnqueueReadBufferHandler;
    outHandlers[ClEnqueueReadBufferRectRpcM::messageSubtype] = clEnqueueReadBufferRectHandler;
    outHandlers[ClEnqueueCopyBufferRpcM::messageSubtype] = clEnqueueCopyBufferHandler;
    outHandlers[ClEnqueueCopyBufferRectRpcM::messageSubtype] = clEnqueueCopyBufferRectHandler;
    outHandlers[ClEnqueueReadImageRpcM::messageSubtype] = clEnqueueReadImageHandler;
    outHandlers[ClEnqueueWriteImageRpcM::messageSubtype] = clEnqueueWriteImageHandler;
    outHandlers[ClEnqueueCopyImageRpcM::messageSubtype] = clEnqueueCopyImageHandler;
    outHandlers[ClEnqueueCopyImageToBufferRpcM::messageSubtype] = clEnqueueCopyImageToBufferHandler;
    outHandlers[ClEnqueueCopyBufferToImageRpcM::messageSubtype] = clEnqueueCopyBufferToImageHandler;
    outHandlers[ClEnqueueMapBufferRpcM::messageSubtype] = clEnqueueMapBufferHandler;
    outHandlers[ClEnqueueUnmapMemObjectRpcM::messageSubtype] = clEnqueueUnmapMemObjectHandler;
    outHandlers[ClEnqueueFillBufferRpcM::messageSubtype] = clEnqueueFillBufferHandler;
    outHandlers[ClEnqueueFillImageRpcM::messageSubtype] = clEnqueueFillImageHandler;
    outHandlers[ClWaitForEventsRpcM::messageSubtype] = clWaitForEventsHandler;
    outHandlers[ClGetEventInfoRpcM::messageSubtype] = clGetEventInfoHandler;
    outHandlers[ClGetEventProfilingInfoRpcM::messageSubtype] = clGetEventProfilingInfoHandler;
    outHandlers[ClCreateUserEventRpcM::messageSubtype] = clCreateUserEventHandler;
    outHandlers[ClSetUserEventStatusRpcM::messageSubtype] = clSetUserEventStatusHandler;
    outHandlers[ClSetEventCallbackRpcM::messageSubtype] = clSetEventCallbackHandler;
    outHandlers[ClGetDeviceAndHostTimerRpcM::messageSubtype] = clGetDeviceAndHostTimerHandler;
    outHandlers[ClGetHostTimerRpcM::messageSubtype] = clGetHostTimerHandler;
    outHandlers[ClSVMAllocRpcM::messageSubtype] = clSVMAllocHandler;
    outHandlers[ClSVMFreeRpcM::messageSubtype] = clSVMFreeHandler;
    outHandlers[ClEnqueueSVMMapRpcM::messageSubtype] = clEnqueueSVMMapHandler;
    outHandlers[ClEnqueueSVMUnmapRpcM::messageSubtype] = clEnqueueSVMUnmapHandler;
    outHandlers[ClSetKernelArgSVMPointerRpcM::messageSubtype] = clSetKernelArgSVMPointerHandler;
    outHandlers[ClSetKernelExecInfoRpcM::messageSubtype] = clSetKernelExecInfoHandler;
    outHandlers[ClEnqueueSVMMemFillRpcM::messageSubtype] = clEnqueueSVMMemFillHandler;
    outHandlers[ClEnqueueSVMMigrateMemRpcM::messageSubtype] = clEnqueueSVMMigrateMemHandler;
    outHandlers[ClEnqueueSVMMemcpyRpcM::messageSubtype] = clEnqueueSVMMemcpyHandler;
    outHandlers[ClEnqueueSVMFreeRpcM::messageSubtype] = clEnqueueSVMFreeHandler;
    outHandlers[ClCreateSubDevicesEXTRpcM::messageSubtype] = clCreateSubDevicesEXTHandler;
    outHandlers[ClReleaseDeviceEXTRpcM::messageSubtype] = clReleaseDeviceEXTHandler;
    outHandlers[ClRetainDeviceEXTRpcM::messageSubtype] = clRetainDeviceEXTHandler;
    outHandlers[ClGetKernelSubGroupInfoKHRRpcM::messageSubtype] = clGetKernelSubGroupInfoKHRHandler;
    outHandlers[ClGetKernelSuggestedLocalWorkSizeKHRRpcM::messageSubtype] = clGetKernelSuggestedLocalWorkSizeKHRHandler;
    outHandlers[ClEnqueueMemFillINTELRpcM::messageSubtype] = clEnqueueMemFillINTELHandler;
    outHandlers[ClEnqueueMemcpyINTELRpcM::messageSubtype] = clEnqueueMemcpyINTELHandler;
    outHandlers[ClSetKernelArgMemPointerINTELRpcM::messageSubtype] = clSetKernelArgMemPointerINTELHandler;
    outHandlers[ClGetMemAllocInfoINTELRpcM::messageSubtype] = clGetMemAllocInfoINTELHandler;
    outHandlers[ClDeviceMemAllocINTELRpcM::messageSubtype] = clDeviceMemAllocINTELHandler;
    outHandlers[ClHostMemAllocINTELRpcM::messageSubtype] = clHostMemAllocINTELHandler;
    outHandlers[ClSharedMemAllocINTELRpcM::messageSubtype] = clSharedMemAllocINTELHandler;
    outHandlers[ClMemFreeINTELRpcM::messageSubtype] = clMemFreeINTELHandler;
    outHandlers[ClMemBlockingFreeINTELRpcM::messageSubtype] = clMemBlockingFreeINTELHandler;
    outHandlers[ClEnqueueMigrateMemINTELRpcM::messageSubtype] = clEnqueueMigrateMemINTELHandler;
    outHandlers[ClGetDeviceGlobalVariablePointerINTELRpcM::messageSubtype] = clGetDeviceGlobalVariablePointerINTELHandler;
    outHandlers[ClCreateBufferRpcHelperNotUseHostPtrZeroCopyMallocShmem_UsmRpcM::messageSubtype] = clCreateBufferRpcHelperNotUseHostPtrZeroCopyMallocShmem_UsmHandler;
    outHandlers[ClEnqueueWriteBuffer_LocalRpcM::messageSubtype] = clEnqueueWriteBuffer_LocalHandler;
    outHandlers[ClEnqueueWriteBuffer_UsmRpcM::messageSubtype] = clEnqueueWriteBuffer_UsmHandler;
    outHandlers[ClEnqueueWriteBuffer_SharedRpcM::messageSubtype] = clEnqueueWriteBuffer_SharedHandler;
    outHandlers[ClEnqueueWriteBufferRect_LocalRpcM::messageSubtype] = clEnqueueWriteBufferRect_LocalHandler;
    outHandlers[ClEnqueueWriteBufferRect_UsmRpcM::messageSubtype] = clEnqueueWriteBufferRect_UsmHandler;
    outHandlers[ClEnqueueWriteBufferRect_SharedRpcM::messageSubtype] = clEnqueueWriteBufferRect_SharedHandler;
    outHandlers[ClEnqueueReadBuffer_LocalRpcM::messageSubtype] = clEnqueueReadBuffer_LocalHandler;
    outHandlers[ClEnqueueReadBuffer_UsmRpcM::messageSubtype] = clEnqueueReadBuffer_UsmHandler;
    outHandlers[ClEnqueueReadBuffer_SharedRpcM::messageSubtype] = clEnqueueReadBuffer_SharedHandler;
    outHandlers[ClEnqueueReadBufferRect_LocalRpcM::messageSubtype] = clEnqueueReadBufferRect_LocalHandler;
    outHandlers[ClEnqueueReadBufferRect_UsmRpcM::messageSubtype] = clEnqueueReadBufferRect_UsmHandler;
    outHandlers[ClEnqueueReadBufferRect_SharedRpcM::messageSubtype] = clEnqueueReadBufferRect_SharedHandler;
    outHandlers[ClEnqueueSVMMemcpy_Local_LocalRpcM::messageSubtype] = clEnqueueSVMMemcpy_Local_LocalHandler;
    outHandlers[ClEnqueueSVMMemcpy_Local_UsmRpcM::messageSubtype] = clEnqueueSVMMemcpy_Local_UsmHandler;
    outHandlers[ClEnqueueSVMMemcpy_Local_SharedRpcM::messageSubtype] = clEnqueueSVMMemcpy_Local_SharedHandler;
    outHandlers[ClEnqueueSVMMemcpy_Usm_LocalRpcM::messageSubtype] = clEnqueueSVMMemcpy_Usm_LocalHandler;
    outHandlers[ClEnqueueSVMMemcpy_Usm_UsmRpcM::messageSubtype] = clEnqueueSVMMemcpy_Usm_UsmHandler;
    outHandlers[ClEnqueueSVMMemcpy_Usm_SharedRpcM::messageSubtype] = clEnqueueSVMMemcpy_Usm_SharedHandler;
    outHandlers[ClEnqueueSVMMemcpy_Shared_LocalRpcM::messageSubtype] = clEnqueueSVMMemcpy_Shared_LocalHandler;
    outHandlers[ClEnqueueSVMMemcpy_Shared_UsmRpcM::messageSubtype] = clEnqueueSVMMemcpy_Shared_UsmHandler;
    outHandlers[ClEnqueueSVMMemcpy_Shared_SharedRpcM::messageSubtype] = clEnqueueSVMMemcpy_Shared_SharedHandler;
    outHandlers[ClEnqueueMemcpyINTEL_Local_LocalRpcM::messageSubtype] = clEnqueueMemcpyINTEL_Local_LocalHandler;
    outHandlers[ClEnqueueMemcpyINTEL_Local_UsmRpcM::messageSubtype] = clEnqueueMemcpyINTEL_Local_UsmHandler;
    outHandlers[ClEnqueueMemcpyINTEL_Local_SharedRpcM::messageSubtype] = clEnqueueMemcpyINTEL_Local_SharedHandler;
    outHandlers[ClEnqueueMemcpyINTEL_Usm_LocalRpcM::messageSubtype] = clEnqueueMemcpyINTEL_Usm_LocalHandler;
    outHandlers[ClEnqueueMemcpyINTEL_Usm_UsmRpcM::messageSubtype] = clEnqueueMemcpyINTEL_Usm_UsmHandler;
    outHandlers[ClEnqueueMemcpyINTEL_Usm_SharedRpcM::messageSubtype] = clEnqueueMemcpyINTEL_Usm_SharedHandler;
    outHandlers[ClEnqueueMemcpyINTEL_Shared_LocalRpcM::messageSubtype] = clEnqueueMemcpyINTEL_Shared_LocalHandler;
    outHandlers[ClEnqueueMemcpyINTEL_Shared_UsmRpcM::messageSubtype] = clEnqueueMemcpyINTEL_Shared_UsmHandler;
    outHandlers[ClEnqueueMemcpyINTEL_Shared_SharedRpcM::messageSubtype] = clEnqueueMemcpyINTEL_Shared_SharedHandler;
}

inline void callDirectly(Cal::Rpc::Ocl::ClGetPlatformInfoRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clGetPlatformInfo(
                                                apiCommand.args.platform, 
                                                apiCommand.args.param_name, 
                                                apiCommand.args.param_value_size, 
                                                apiCommand.args.param_value, 
                                                apiCommand.args.param_value_size_ret
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClGetDeviceIDsRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clGetDeviceIDs(
                                                apiCommand.args.platform, 
                                                apiCommand.args.device_type, 
                                                apiCommand.args.num_entries, 
                                                apiCommand.args.devices, 
                                                apiCommand.args.num_devices
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClGetDeviceInfoRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clGetDeviceInfo(
                                                apiCommand.args.device, 
                                                apiCommand.args.param_name, 
                                                apiCommand.args.param_value_size, 
                                                apiCommand.args.param_value, 
                                                apiCommand.args.param_value_size_ret
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClCreateContextRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clCreateContext(
                                                apiCommand.args.properties, 
                                                apiCommand.args.num_devices, 
                                                apiCommand.args.devices, 
                                                apiCommand.args.pfn_notify, 
                                                apiCommand.args.user_data, 
                                                apiCommand.args.errcode_ret
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClCreateContextFromTypeRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clCreateContextFromType(
                                                apiCommand.args.properties, 
                                                apiCommand.args.device_type, 
                                                apiCommand.args.pfn_notify, 
                                                apiCommand.args.user_data, 
                                                apiCommand.args.errcode_ret
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClGetContextInfoRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clGetContextInfo(
                                                apiCommand.args.context, 
                                                apiCommand.args.param_name, 
                                                apiCommand.args.param_value_size, 
                                                apiCommand.args.param_value, 
                                                apiCommand.args.param_value_size_ret
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClSetContextDestructorCallbackRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clSetContextDestructorCallback(
                                                apiCommand.args.context, 
                                                apiCommand.args.pfn_notify, 
                                                apiCommand.args.user_data
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClSetMemObjectDestructorCallbackRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clSetMemObjectDestructorCallback(
                                                apiCommand.args.memobj, 
                                                apiCommand.args.pfn_notify, 
                                                apiCommand.args.user_data
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClCreateSubDevicesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clCreateSubDevices(
                                                apiCommand.args.in_device, 
                                                apiCommand.args.properties, 
                                                apiCommand.args.num_devices, 
                                                apiCommand.args.out_devices, 
                                                apiCommand.args.num_devices_ret
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClCreateCommandQueueRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clCreateCommandQueue(
                                                apiCommand.args.context, 
                                                apiCommand.args.device, 
                                                apiCommand.args.properties, 
                                                apiCommand.args.errcode_ret
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClSetDefaultDeviceCommandQueueRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clSetDefaultDeviceCommandQueue(
                                                apiCommand.args.context, 
                                                apiCommand.args.device, 
                                                apiCommand.args.command_queue
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClCreateCommandQueueWithPropertiesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clCreateCommandQueueWithProperties(
                                                apiCommand.args.context, 
                                                apiCommand.args.device, 
                                                apiCommand.args.properties, 
                                                apiCommand.args.errcode_ret
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClCreateProgramWithSourceRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clCreateProgramWithSource(
                                                apiCommand.args.context, 
                                                apiCommand.args.count, 
                                                apiCommand.args.strings, 
                                                apiCommand.args.lengths, 
                                                apiCommand.args.errcode_ret
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClCreateProgramWithILRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clCreateProgramWithIL(
                                                apiCommand.args.context, 
                                                apiCommand.args.il, 
                                                apiCommand.args.length, 
                                                apiCommand.args.errcode_ret
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClCreateProgramWithBinaryRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clCreateProgramWithBinary(
                                                apiCommand.args.context, 
                                                apiCommand.args.num_devices, 
                                                apiCommand.args.device_list, 
                                                apiCommand.args.lengths, 
                                                apiCommand.args.binaries, 
                                                apiCommand.args.binary_status, 
                                                apiCommand.args.errcode_ret
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClCreateProgramWithBuiltInKernelsRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clCreateProgramWithBuiltInKernels(
                                                apiCommand.args.context, 
                                                apiCommand.args.num_devices, 
                                                apiCommand.args.device_list, 
                                                apiCommand.args.kernel_names, 
                                                apiCommand.args.errcode_ret
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClBuildProgramRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clBuildProgram(
                                                apiCommand.args.program, 
                                                apiCommand.args.num_devices, 
                                                apiCommand.args.device_list, 
                                                apiCommand.args.options, 
                                                apiCommand.args.pfn_notify, 
                                                apiCommand.args.user_data
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClCompileProgramRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clCompileProgram(
                                                apiCommand.args.program, 
                                                apiCommand.args.num_devices, 
                                                apiCommand.args.device_list, 
                                                apiCommand.args.options, 
                                                apiCommand.args.num_input_headers, 
                                                apiCommand.args.input_headers, 
                                                apiCommand.args.header_include_names, 
                                                apiCommand.args.pfn_notify, 
                                                apiCommand.args.user_data
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClLinkProgramRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clLinkProgram(
                                                apiCommand.args.context, 
                                                apiCommand.args.num_devices, 
                                                apiCommand.args.device_list, 
                                                apiCommand.args.options, 
                                                apiCommand.args.num_input_programs, 
                                                apiCommand.args.input_programs, 
                                                apiCommand.args.pfn_notify, 
                                                apiCommand.args.user_data, 
                                                apiCommand.args.errcode_ret
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClGetProgramBuildInfoRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clGetProgramBuildInfo(
                                                apiCommand.args.program, 
                                                apiCommand.args.device, 
                                                apiCommand.args.param_name, 
                                                apiCommand.args.param_value_size, 
                                                apiCommand.args.param_value, 
                                                apiCommand.args.param_value_size_ret
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClSetProgramReleaseCallbackRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clSetProgramReleaseCallback(
                                                apiCommand.args.program, 
                                                apiCommand.args.pfn_notify, 
                                                apiCommand.args.user_data
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClCreateKernelRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clCreateKernel(
                                                apiCommand.args.program, 
                                                apiCommand.args.kernel_name, 
                                                apiCommand.args.errcode_ret
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClCloneKernelRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clCloneKernel(
                                                apiCommand.args.source_kernel, 
                                                apiCommand.args.errcode_ret
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClCreateKernelsInProgramRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clCreateKernelsInProgram(
                                                apiCommand.args.program, 
                                                apiCommand.args.num_kernels, 
                                                apiCommand.args.kernels, 
                                                apiCommand.args.num_kernels_ret
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClGetCommandQueueInfoRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clGetCommandQueueInfo(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.param_name, 
                                                apiCommand.args.param_value_size, 
                                                apiCommand.args.param_value, 
                                                apiCommand.args.param_value_size_ret
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClGetMemObjectInfoRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clGetMemObjectInfo(
                                                apiCommand.args.memobj, 
                                                apiCommand.args.param_name, 
                                                apiCommand.args.param_value_size, 
                                                apiCommand.args.param_value, 
                                                apiCommand.args.param_value_size_ret
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClGetImageInfoRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clGetImageInfo(
                                                apiCommand.args.image, 
                                                apiCommand.args.param_name, 
                                                apiCommand.args.param_value_size, 
                                                apiCommand.args.param_value, 
                                                apiCommand.args.param_value_size_ret
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClGetSamplerInfoRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clGetSamplerInfo(
                                                apiCommand.args.sampler, 
                                                apiCommand.args.param_name, 
                                                apiCommand.args.param_value_size, 
                                                apiCommand.args.param_value, 
                                                apiCommand.args.param_value_size_ret
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClGetKernelInfoRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clGetKernelInfo(
                                                apiCommand.args.kernel, 
                                                apiCommand.args.param_name, 
                                                apiCommand.args.param_value_size, 
                                                apiCommand.args.param_value, 
                                                apiCommand.args.param_value_size_ret
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClGetKernelWorkGroupInfoRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clGetKernelWorkGroupInfo(
                                                apiCommand.args.kernel, 
                                                apiCommand.args.device, 
                                                apiCommand.args.param_name, 
                                                apiCommand.args.param_value_size, 
                                                apiCommand.args.param_value, 
                                                apiCommand.args.param_value_size_ret
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClGetKernelArgInfoRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clGetKernelArgInfo(
                                                apiCommand.args.kernel, 
                                                apiCommand.args.arg_indx, 
                                                apiCommand.args.param_name, 
                                                apiCommand.args.param_value_size, 
                                                apiCommand.args.param_value, 
                                                apiCommand.args.param_value_size_ret
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClGetKernelSubGroupInfoRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clGetKernelSubGroupInfo(
                                                apiCommand.args.kernel, 
                                                apiCommand.args.device, 
                                                apiCommand.args.param_name, 
                                                apiCommand.args.input_value_size, 
                                                apiCommand.args.input_value, 
                                                apiCommand.args.param_value_size, 
                                                apiCommand.args.param_value, 
                                                apiCommand.args.param_value_size_ret
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClReleaseCommandQueueRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clReleaseCommandQueue(
                                                apiCommand.args.command_queue
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClReleaseContextRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clReleaseContext(
                                                apiCommand.args.context
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClReleaseDeviceRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clReleaseDevice(
                                                apiCommand.args.device
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClReleaseKernelRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clReleaseKernel(
                                                apiCommand.args.kernel
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClReleaseSamplerRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clReleaseSampler(
                                                apiCommand.args.sampler
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClReleaseProgramRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clReleaseProgram(
                                                apiCommand.args.program
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClReleaseMemObjectRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clReleaseMemObject(
                                                apiCommand.args.memobj
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClReleaseEventRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clReleaseEvent(
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClRetainCommandQueueRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clRetainCommandQueue(
                                                apiCommand.args.command_queue
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClRetainContextRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clRetainContext(
                                                apiCommand.args.context
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClRetainDeviceRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clRetainDevice(
                                                apiCommand.args.device
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClRetainProgramRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clRetainProgram(
                                                apiCommand.args.program
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClRetainMemObjectRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clRetainMemObject(
                                                apiCommand.args.memobj
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClRetainSamplerRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clRetainSampler(
                                                apiCommand.args.sampler
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClRetainKernelRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clRetainKernel(
                                                apiCommand.args.kernel
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClRetainEventRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clRetainEvent(
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClFlushRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clFlush(
                                                apiCommand.args.command_queue
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClFinishRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clFinish(
                                                apiCommand.args.command_queue
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueNDRangeKernelRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueNDRangeKernel(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.kernel, 
                                                apiCommand.args.work_dim, 
                                                apiCommand.args.global_work_offset, 
                                                apiCommand.args.global_work_size, 
                                                apiCommand.args.local_work_size, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueTaskRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueTask(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.kernel, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueMarkerWithWaitListRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueMarkerWithWaitList(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueMarkerRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueMarker(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueBarrierWithWaitListRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueBarrierWithWaitList(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueBarrierRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueBarrier(
                                                apiCommand.args.command_queue
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueWaitForEventsRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueWaitForEvents(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.num_events, 
                                                apiCommand.args.event_list
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueMigrateMemObjectsRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueMigrateMemObjects(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.num_mem_objects, 
                                                apiCommand.args.mem_objects, 
                                                apiCommand.args.flags, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClCreateBufferRpcHelperUseHostPtrZeroCopyMallocShmemRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clCreateBuffer(
                                                apiCommand.args.context, 
                                                apiCommand.args.flags, 
                                                apiCommand.args.size, 
                                                apiCommand.args.host_ptr, 
                                                apiCommand.args.errcode_ret
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClCreateBufferRpcHelperNotUseHostPtrZeroCopyMallocShmemRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clCreateBuffer(
                                                apiCommand.args.context, 
                                                apiCommand.args.flags, 
                                                apiCommand.args.size, 
                                                apiCommand.args.host_ptr, 
                                                apiCommand.args.errcode_ret
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClCreateSubBufferRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clCreateSubBuffer(
                                                apiCommand.args.buffer, 
                                                apiCommand.args.flags, 
                                                apiCommand.args.buffer_create_type, 
                                                apiCommand.args.buffer_create_info, 
                                                apiCommand.args.errcode_ret
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClCreatePipeRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clCreatePipe(
                                                apiCommand.args.context, 
                                                apiCommand.args.flags, 
                                                apiCommand.args.pipe_packet_size, 
                                                apiCommand.args.pipe_max_packets, 
                                                apiCommand.args.properties, 
                                                apiCommand.args.errcode_ret
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClGetPipeInfoRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clGetPipeInfo(
                                                apiCommand.args.pipe, 
                                                apiCommand.args.param_name, 
                                                apiCommand.args.param_value_size, 
                                                apiCommand.args.param_value, 
                                                apiCommand.args.param_value_size_ret
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClCreateImageRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clCreateImage(
                                                apiCommand.args.context, 
                                                apiCommand.args.flags, 
                                                apiCommand.args.image_format, 
                                                apiCommand.args.image_desc, 
                                                apiCommand.args.host_ptr, 
                                                apiCommand.args.errcode_ret
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClCreateImage2DRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clCreateImage2D(
                                                apiCommand.args.context, 
                                                apiCommand.args.flags, 
                                                apiCommand.args.image_format, 
                                                apiCommand.args.image_width, 
                                                apiCommand.args.image_height, 
                                                apiCommand.args.image_row_pitch, 
                                                apiCommand.args.host_ptr, 
                                                apiCommand.args.errcode_ret
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClCreateImage3DRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clCreateImage3D(
                                                apiCommand.args.context, 
                                                apiCommand.args.flags, 
                                                apiCommand.args.image_format, 
                                                apiCommand.args.image_width, 
                                                apiCommand.args.image_height, 
                                                apiCommand.args.image_depth, 
                                                apiCommand.args.image_row_pitch, 
                                                apiCommand.args.image_slice_pitch, 
                                                apiCommand.args.host_ptr, 
                                                apiCommand.args.errcode_ret
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClCreateSamplerRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clCreateSampler(
                                                apiCommand.args.context, 
                                                apiCommand.args.normalized_coords, 
                                                apiCommand.args.addressing_mode, 
                                                apiCommand.args.filter_mode, 
                                                apiCommand.args.errcode_ret
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClCreateSamplerWithPropertiesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clCreateSamplerWithProperties(
                                                apiCommand.args.context, 
                                                apiCommand.args.properties, 
                                                apiCommand.args.errcode_ret
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClCreateImageWithPropertiesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clCreateImageWithProperties(
                                                apiCommand.args.context, 
                                                apiCommand.args.properties, 
                                                apiCommand.args.flags, 
                                                apiCommand.args.image_format, 
                                                apiCommand.args.image_desc, 
                                                apiCommand.args.host_ptr, 
                                                apiCommand.args.errcode_ret
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClCreateBufferWithPropertiesRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clCreateBufferWithProperties(
                                                apiCommand.args.context, 
                                                apiCommand.args.properties, 
                                                apiCommand.args.flags, 
                                                apiCommand.args.size, 
                                                apiCommand.args.host_ptr, 
                                                apiCommand.args.errcode_ret
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClGetSupportedImageFormatsRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clGetSupportedImageFormats(
                                                apiCommand.args.context, 
                                                apiCommand.args.flags, 
                                                apiCommand.args.image_type, 
                                                apiCommand.args.num_entries, 
                                                apiCommand.args.image_formats, 
                                                apiCommand.args.num_image_formats
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClSetKernelArgRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clSetKernelArg(
                                                apiCommand.args.kernel, 
                                                apiCommand.args.arg_index, 
                                                apiCommand.args.arg_size, 
                                                apiCommand.args.arg_value
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClSetProgramSpecializationConstantRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clSetProgramSpecializationConstant(
                                                apiCommand.args.program, 
                                                apiCommand.args.spec_id, 
                                                apiCommand.args.spec_size, 
                                                apiCommand.args.spec_value
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueWriteBufferRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueWriteBuffer(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.buffer, 
                                                apiCommand.args.blocking_write, 
                                                apiCommand.args.offset, 
                                                apiCommand.args.size, 
                                                apiCommand.args.ptr, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueWriteBufferRectRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueWriteBufferRect(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.buffer, 
                                                apiCommand.args.blocking_write, 
                                                apiCommand.args.buffer_origin, 
                                                apiCommand.args.host_origin, 
                                                apiCommand.args.region, 
                                                apiCommand.args.buffer_row_pitch, 
                                                apiCommand.args.buffer_slice_pitch, 
                                                apiCommand.args.host_row_pitch, 
                                                apiCommand.args.host_slice_pitch, 
                                                apiCommand.args.ptr, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueReadBufferRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueReadBuffer(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.buffer, 
                                                apiCommand.args.blocking_read, 
                                                apiCommand.args.offset, 
                                                apiCommand.args.size, 
                                                apiCommand.args.ptr, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueReadBufferRectRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueReadBufferRect(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.buffer, 
                                                apiCommand.args.blocking_read, 
                                                apiCommand.args.buffer_origin, 
                                                apiCommand.args.host_origin, 
                                                apiCommand.args.region, 
                                                apiCommand.args.buffer_row_pitch, 
                                                apiCommand.args.buffer_slice_pitch, 
                                                apiCommand.args.host_row_pitch, 
                                                apiCommand.args.host_slice_pitch, 
                                                apiCommand.args.ptr, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueCopyBufferRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueCopyBuffer(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.src_buffer, 
                                                apiCommand.args.dst_buffer, 
                                                apiCommand.args.src_offset, 
                                                apiCommand.args.dst_offset, 
                                                apiCommand.args.size, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueCopyBufferRectRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueCopyBufferRect(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.src_buffer, 
                                                apiCommand.args.dst_buffer, 
                                                apiCommand.args.src_origin, 
                                                apiCommand.args.dst_origin, 
                                                apiCommand.args.region, 
                                                apiCommand.args.src_row_pitch, 
                                                apiCommand.args.src_slice_pitch, 
                                                apiCommand.args.dst_row_pitch, 
                                                apiCommand.args.dst_slice_pitch, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueReadImageRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueReadImage(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.image, 
                                                apiCommand.args.blocking_read, 
                                                apiCommand.args.src_origin, 
                                                apiCommand.args.region, 
                                                apiCommand.args.row_pitch, 
                                                apiCommand.args.slice_pitch, 
                                                apiCommand.args.ptr, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueWriteImageRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueWriteImage(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.image, 
                                                apiCommand.args.blocking_write, 
                                                apiCommand.args.origin, 
                                                apiCommand.args.region, 
                                                apiCommand.args.input_row_pitch, 
                                                apiCommand.args.input_slice_pitch, 
                                                apiCommand.args.ptr, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueCopyImageRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueCopyImage(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.src_image, 
                                                apiCommand.args.dst_image, 
                                                apiCommand.args.src_origin, 
                                                apiCommand.args.dst_origin, 
                                                apiCommand.args.region, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueCopyImageToBufferRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueCopyImageToBuffer(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.src_image, 
                                                apiCommand.args.dst_buffer, 
                                                apiCommand.args.src_origin, 
                                                apiCommand.args.region, 
                                                apiCommand.args.dst_offset, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueCopyBufferToImageRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueCopyBufferToImage(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.src_buffer, 
                                                apiCommand.args.dst_image, 
                                                apiCommand.args.src_offset, 
                                                apiCommand.args.dst_origin, 
                                                apiCommand.args.region, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueMapBufferRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueMapBuffer(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.buffer, 
                                                apiCommand.args.blocking_map, 
                                                apiCommand.args.map_flags, 
                                                apiCommand.args.offset, 
                                                apiCommand.args.cb, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event, 
                                                apiCommand.args.errcode_ret
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueUnmapMemObjectRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueUnmapMemObject(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.memobj, 
                                                apiCommand.args.mapped_ptr, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueFillBufferRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueFillBuffer(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.memobj, 
                                                apiCommand.args.pattern, 
                                                apiCommand.args.patternSize, 
                                                apiCommand.args.offset, 
                                                apiCommand.args.size, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueFillImageRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueFillImage(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.image, 
                                                apiCommand.args.fill_color, 
                                                apiCommand.args.origin, 
                                                apiCommand.args.region, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClWaitForEventsRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clWaitForEvents(
                                                apiCommand.args.num_events, 
                                                apiCommand.args.event_list
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClGetEventInfoRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clGetEventInfo(
                                                apiCommand.args.event, 
                                                apiCommand.args.param_name, 
                                                apiCommand.args.param_value_size, 
                                                apiCommand.args.param_value, 
                                                apiCommand.args.param_value_size_ret
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClGetEventProfilingInfoRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clGetEventProfilingInfo(
                                                apiCommand.args.event, 
                                                apiCommand.args.param_name, 
                                                apiCommand.args.param_value_size, 
                                                apiCommand.args.param_value, 
                                                apiCommand.args.param_value_size_ret
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClCreateUserEventRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clCreateUserEvent(
                                                apiCommand.args.context, 
                                                apiCommand.args.errcode_ret
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClSetUserEventStatusRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clSetUserEventStatus(
                                                apiCommand.args.event, 
                                                apiCommand.args.execution_status
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClSetEventCallbackRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clSetEventCallback(
                                                apiCommand.args.event, 
                                                apiCommand.args.command_exec_callback_type, 
                                                apiCommand.args.pfn_notify, 
                                                apiCommand.args.user_data
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClGetDeviceAndHostTimerRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clGetDeviceAndHostTimer(
                                                apiCommand.args.device, 
                                                apiCommand.args.device_timestamp, 
                                                apiCommand.args.host_timestamp
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClGetHostTimerRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clGetHostTimer(
                                                apiCommand.args.device, 
                                                apiCommand.args.host_timestamp
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClSVMAllocRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clSVMAlloc(
                                                apiCommand.args.context, 
                                                apiCommand.args.flags, 
                                                apiCommand.args.size, 
                                                apiCommand.args.alignment
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClSVMFreeRpcM &apiCommand) {
    Cal::Service::Apis::Ocl::Standard::clSVMFree(
                                                apiCommand.args.context, 
                                                apiCommand.args.ptr
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueSVMMapRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueSVMMap(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.blocking_map, 
                                                apiCommand.args.map_flags, 
                                                apiCommand.args.svm_ptr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueSVMUnmapRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueSVMUnmap(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.svm_ptr, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClSetKernelArgSVMPointerRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clSetKernelArgSVMPointer(
                                                apiCommand.args.kernel, 
                                                apiCommand.args.argIndex, 
                                                apiCommand.args.argValue
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClSetKernelExecInfoRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clSetKernelExecInfo(
                                                apiCommand.args.kernel, 
                                                apiCommand.args.param_name, 
                                                apiCommand.args.param_value_size, 
                                                apiCommand.args.param_value
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueSVMMemFillRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueSVMMemFill(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.svm_ptr, 
                                                apiCommand.args.pattern, 
                                                apiCommand.args.patternSize, 
                                                apiCommand.args.size, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueSVMMigrateMemRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueSVMMigrateMem(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.num_svm_pointers, 
                                                apiCommand.args.svm_pointers, 
                                                apiCommand.args.sizes, 
                                                apiCommand.args.flags, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueSVMMemcpyRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueSVMMemcpy(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.blocking, 
                                                apiCommand.args.dst_ptr, 
                                                apiCommand.args.src_ptr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueSVMFreeRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueSVMFree(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.num_svm_pointers, 
                                                apiCommand.args.svm_pointers, 
                                                apiCommand.args.pfn_notify, 
                                                apiCommand.args.user_data, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClCreateSubDevicesEXTRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Extensions::clCreateSubDevicesEXT(
                                                apiCommand.args.in_device, 
                                                apiCommand.args.properties, 
                                                apiCommand.args.num_entries, 
                                                apiCommand.args.out_devices, 
                                                apiCommand.args.num_devices
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClReleaseDeviceEXTRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Extensions::clReleaseDeviceEXT(
                                                apiCommand.args.device
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClRetainDeviceEXTRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Extensions::clRetainDeviceEXT(
                                                apiCommand.args.device
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClGetKernelSubGroupInfoKHRRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Extensions::clGetKernelSubGroupInfoKHR(
                                                apiCommand.args.kernel, 
                                                apiCommand.args.device, 
                                                apiCommand.args.param_name, 
                                                apiCommand.args.input_value_size, 
                                                apiCommand.args.input_value, 
                                                apiCommand.args.param_value_size, 
                                                apiCommand.args.param_value, 
                                                apiCommand.args.param_value_size_ret
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClGetKernelSuggestedLocalWorkSizeKHRRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Extensions::clGetKernelSuggestedLocalWorkSizeKHR(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.kernel, 
                                                apiCommand.args.work_dim, 
                                                apiCommand.args.global_work_offset, 
                                                apiCommand.args.global_work_size, 
                                                apiCommand.args.suggested_local_work_size
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueMemFillINTELRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Extensions::clEnqueueMemFillINTEL(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.dstPtr, 
                                                apiCommand.args.pattern, 
                                                apiCommand.args.patternSize, 
                                                apiCommand.args.size, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueMemcpyINTELRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Extensions::clEnqueueMemcpyINTEL(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.blocking, 
                                                apiCommand.args.dstPtr, 
                                                apiCommand.args.srcPtr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClSetKernelArgMemPointerINTELRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Extensions::clSetKernelArgMemPointerINTEL(
                                                apiCommand.args.kernel, 
                                                apiCommand.args.argIndex, 
                                                apiCommand.args.argValue
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClGetMemAllocInfoINTELRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Extensions::clGetMemAllocInfoINTEL(
                                                apiCommand.args.context, 
                                                apiCommand.args.ptr, 
                                                apiCommand.args.param_name, 
                                                apiCommand.args.param_value_size, 
                                                apiCommand.args.param_value, 
                                                apiCommand.args.param_value_size_ret
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClDeviceMemAllocINTELRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Extensions::clDeviceMemAllocINTEL(
                                                apiCommand.args.context, 
                                                apiCommand.args.device, 
                                                apiCommand.args.properties, 
                                                apiCommand.args.size, 
                                                apiCommand.args.alignment, 
                                                apiCommand.args.errcode_ret
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClHostMemAllocINTELRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Extensions::clHostMemAllocINTEL(
                                                apiCommand.args.context, 
                                                apiCommand.args.properties, 
                                                apiCommand.args.size, 
                                                apiCommand.args.alignment, 
                                                apiCommand.args.errcode_ret
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClSharedMemAllocINTELRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Extensions::clSharedMemAllocINTEL(
                                                apiCommand.args.context, 
                                                apiCommand.args.device, 
                                                apiCommand.args.properties, 
                                                apiCommand.args.size, 
                                                apiCommand.args.alignment, 
                                                apiCommand.args.errcode_ret
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClMemFreeINTELRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Extensions::clMemFreeINTEL(
                                                apiCommand.args.context, 
                                                apiCommand.args.ptr
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClMemBlockingFreeINTELRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Extensions::clMemBlockingFreeINTEL(
                                                apiCommand.args.context, 
                                                apiCommand.args.ptr
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueMigrateMemINTELRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Extensions::clEnqueueMigrateMemINTEL(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.ptr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.flags, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClGetDeviceGlobalVariablePointerINTELRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Extensions::clGetDeviceGlobalVariablePointerINTEL(
                                                apiCommand.args.device, 
                                                apiCommand.args.program, 
                                                apiCommand.args.globalVariableName, 
                                                apiCommand.args.globalVariableSizeRet, 
                                                apiCommand.args.globalVariablePointerRet
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClCreateBufferRpcHelperNotUseHostPtrZeroCopyMallocShmem_UsmRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clCreateBuffer(
                                                apiCommand.args.context, 
                                                apiCommand.args.flags, 
                                                apiCommand.args.size, 
                                                apiCommand.args.host_ptr, 
                                                apiCommand.args.errcode_ret
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueWriteBuffer_LocalRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueWriteBuffer(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.buffer, 
                                                apiCommand.args.blocking_write, 
                                                apiCommand.args.offset, 
                                                apiCommand.args.size, 
                                                apiCommand.args.ptr, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueWriteBuffer_UsmRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueWriteBuffer(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.buffer, 
                                                apiCommand.args.blocking_write, 
                                                apiCommand.args.offset, 
                                                apiCommand.args.size, 
                                                apiCommand.args.ptr, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueWriteBuffer_SharedRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueWriteBuffer(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.buffer, 
                                                apiCommand.args.blocking_write, 
                                                apiCommand.args.offset, 
                                                apiCommand.args.size, 
                                                apiCommand.args.ptr, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueWriteBufferRect_LocalRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueWriteBufferRect(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.buffer, 
                                                apiCommand.args.blocking_write, 
                                                apiCommand.args.buffer_origin, 
                                                apiCommand.args.host_origin, 
                                                apiCommand.args.region, 
                                                apiCommand.args.buffer_row_pitch, 
                                                apiCommand.args.buffer_slice_pitch, 
                                                apiCommand.args.host_row_pitch, 
                                                apiCommand.args.host_slice_pitch, 
                                                apiCommand.args.ptr, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueWriteBufferRect_UsmRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueWriteBufferRect(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.buffer, 
                                                apiCommand.args.blocking_write, 
                                                apiCommand.args.buffer_origin, 
                                                apiCommand.args.host_origin, 
                                                apiCommand.args.region, 
                                                apiCommand.args.buffer_row_pitch, 
                                                apiCommand.args.buffer_slice_pitch, 
                                                apiCommand.args.host_row_pitch, 
                                                apiCommand.args.host_slice_pitch, 
                                                apiCommand.args.ptr, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueWriteBufferRect_SharedRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueWriteBufferRect(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.buffer, 
                                                apiCommand.args.blocking_write, 
                                                apiCommand.args.buffer_origin, 
                                                apiCommand.args.host_origin, 
                                                apiCommand.args.region, 
                                                apiCommand.args.buffer_row_pitch, 
                                                apiCommand.args.buffer_slice_pitch, 
                                                apiCommand.args.host_row_pitch, 
                                                apiCommand.args.host_slice_pitch, 
                                                apiCommand.args.ptr, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueReadBuffer_LocalRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueReadBuffer(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.buffer, 
                                                apiCommand.args.blocking_read, 
                                                apiCommand.args.offset, 
                                                apiCommand.args.size, 
                                                apiCommand.args.ptr, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueReadBuffer_UsmRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueReadBuffer(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.buffer, 
                                                apiCommand.args.blocking_read, 
                                                apiCommand.args.offset, 
                                                apiCommand.args.size, 
                                                apiCommand.args.ptr, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueReadBuffer_SharedRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueReadBuffer(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.buffer, 
                                                apiCommand.args.blocking_read, 
                                                apiCommand.args.offset, 
                                                apiCommand.args.size, 
                                                apiCommand.args.ptr, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueReadBufferRect_LocalRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueReadBufferRect(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.buffer, 
                                                apiCommand.args.blocking_read, 
                                                apiCommand.args.buffer_origin, 
                                                apiCommand.args.host_origin, 
                                                apiCommand.args.region, 
                                                apiCommand.args.buffer_row_pitch, 
                                                apiCommand.args.buffer_slice_pitch, 
                                                apiCommand.args.host_row_pitch, 
                                                apiCommand.args.host_slice_pitch, 
                                                apiCommand.args.ptr, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueReadBufferRect_UsmRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueReadBufferRect(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.buffer, 
                                                apiCommand.args.blocking_read, 
                                                apiCommand.args.buffer_origin, 
                                                apiCommand.args.host_origin, 
                                                apiCommand.args.region, 
                                                apiCommand.args.buffer_row_pitch, 
                                                apiCommand.args.buffer_slice_pitch, 
                                                apiCommand.args.host_row_pitch, 
                                                apiCommand.args.host_slice_pitch, 
                                                apiCommand.args.ptr, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueReadBufferRect_SharedRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueReadBufferRect(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.buffer, 
                                                apiCommand.args.blocking_read, 
                                                apiCommand.args.buffer_origin, 
                                                apiCommand.args.host_origin, 
                                                apiCommand.args.region, 
                                                apiCommand.args.buffer_row_pitch, 
                                                apiCommand.args.buffer_slice_pitch, 
                                                apiCommand.args.host_row_pitch, 
                                                apiCommand.args.host_slice_pitch, 
                                                apiCommand.args.ptr, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueSVMMemcpy_Local_LocalRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueSVMMemcpy(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.blocking, 
                                                apiCommand.args.dst_ptr, 
                                                apiCommand.args.src_ptr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueSVMMemcpy_Local_UsmRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueSVMMemcpy(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.blocking, 
                                                apiCommand.args.dst_ptr, 
                                                apiCommand.args.src_ptr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueSVMMemcpy_Local_SharedRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueSVMMemcpy(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.blocking, 
                                                apiCommand.args.dst_ptr, 
                                                apiCommand.args.src_ptr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueSVMMemcpy_Usm_LocalRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueSVMMemcpy(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.blocking, 
                                                apiCommand.args.dst_ptr, 
                                                apiCommand.args.src_ptr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueSVMMemcpy_Usm_UsmRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueSVMMemcpy(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.blocking, 
                                                apiCommand.args.dst_ptr, 
                                                apiCommand.args.src_ptr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueSVMMemcpy_Usm_SharedRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueSVMMemcpy(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.blocking, 
                                                apiCommand.args.dst_ptr, 
                                                apiCommand.args.src_ptr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueSVMMemcpy_Shared_LocalRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueSVMMemcpy(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.blocking, 
                                                apiCommand.args.dst_ptr, 
                                                apiCommand.args.src_ptr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueSVMMemcpy_Shared_UsmRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueSVMMemcpy(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.blocking, 
                                                apiCommand.args.dst_ptr, 
                                                apiCommand.args.src_ptr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueSVMMemcpy_Shared_SharedRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Standard::clEnqueueSVMMemcpy(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.blocking, 
                                                apiCommand.args.dst_ptr, 
                                                apiCommand.args.src_ptr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueMemcpyINTEL_Local_LocalRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Extensions::clEnqueueMemcpyINTEL(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.blocking, 
                                                apiCommand.args.dstPtr, 
                                                apiCommand.args.srcPtr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueMemcpyINTEL_Local_UsmRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Extensions::clEnqueueMemcpyINTEL(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.blocking, 
                                                apiCommand.args.dstPtr, 
                                                apiCommand.args.srcPtr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueMemcpyINTEL_Local_SharedRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Extensions::clEnqueueMemcpyINTEL(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.blocking, 
                                                apiCommand.args.dstPtr, 
                                                apiCommand.args.srcPtr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueMemcpyINTEL_Usm_LocalRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Extensions::clEnqueueMemcpyINTEL(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.blocking, 
                                                apiCommand.args.dstPtr, 
                                                apiCommand.args.srcPtr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueMemcpyINTEL_Usm_UsmRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Extensions::clEnqueueMemcpyINTEL(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.blocking, 
                                                apiCommand.args.dstPtr, 
                                                apiCommand.args.srcPtr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueMemcpyINTEL_Usm_SharedRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Extensions::clEnqueueMemcpyINTEL(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.blocking, 
                                                apiCommand.args.dstPtr, 
                                                apiCommand.args.srcPtr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueMemcpyINTEL_Shared_LocalRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Extensions::clEnqueueMemcpyINTEL(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.blocking, 
                                                apiCommand.args.dstPtr, 
                                                apiCommand.args.srcPtr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueMemcpyINTEL_Shared_UsmRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Extensions::clEnqueueMemcpyINTEL(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.blocking, 
                                                apiCommand.args.dstPtr, 
                                                apiCommand.args.srcPtr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}
inline void callDirectly(Cal::Rpc::Ocl::ClEnqueueMemcpyINTEL_Shared_SharedRpcM &apiCommand) {
    apiCommand.captures.ret = Cal::Service::Apis::Ocl::Extensions::clEnqueueMemcpyINTEL(
                                                apiCommand.args.command_queue, 
                                                apiCommand.args.blocking, 
                                                apiCommand.args.dstPtr, 
                                                apiCommand.args.srcPtr, 
                                                apiCommand.args.size, 
                                                apiCommand.args.num_events_in_wait_list, 
                                                apiCommand.args.event_wait_list, 
                                                apiCommand.args.event
                                                );
}

inline bool callDirectly(Cal::Rpc::RpcMessageHeader *command) {
    if(nullptr == command){
        log<Verbosity::debug>("Tried to call directly with empty command message header");
        return false;
    }
    if(command->type != Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl){
        log<Verbosity::debug>("Tried to call directly %d message type as Ocl", command->type);
        return false;
    }
    switch(command->subtype){
        default:
            log<Verbosity::debug>("Tried to call directly unknown message subtype %d", command->subtype);
            return false;
        case Cal::Rpc::Ocl::ClGetPlatformInfoRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClGetPlatformInfoRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClGetDeviceIDsRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClGetDeviceIDsRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClGetDeviceInfoRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClGetDeviceInfoRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClCreateContextRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClCreateContextRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClCreateContextFromTypeRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClCreateContextFromTypeRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClGetContextInfoRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClGetContextInfoRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClSetContextDestructorCallbackRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClSetContextDestructorCallbackRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClSetMemObjectDestructorCallbackRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClSetMemObjectDestructorCallbackRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClCreateSubDevicesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClCreateSubDevicesRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClCreateCommandQueueRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClCreateCommandQueueRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClSetDefaultDeviceCommandQueueRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClSetDefaultDeviceCommandQueueRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClCreateCommandQueueWithPropertiesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClCreateCommandQueueWithPropertiesRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClCreateProgramWithSourceRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClCreateProgramWithSourceRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClCreateProgramWithILRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClCreateProgramWithILRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClCreateProgramWithBinaryRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClCreateProgramWithBinaryRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClCreateProgramWithBuiltInKernelsRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClCreateProgramWithBuiltInKernelsRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClBuildProgramRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClBuildProgramRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClCompileProgramRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClCompileProgramRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClLinkProgramRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClLinkProgramRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClGetProgramBuildInfoRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClGetProgramBuildInfoRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClSetProgramReleaseCallbackRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClSetProgramReleaseCallbackRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClCreateKernelRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClCreateKernelRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClCloneKernelRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClCloneKernelRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClCreateKernelsInProgramRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClCreateKernelsInProgramRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClGetCommandQueueInfoRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClGetCommandQueueInfoRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClGetMemObjectInfoRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClGetMemObjectInfoRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClGetImageInfoRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClGetImageInfoRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClGetSamplerInfoRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClGetSamplerInfoRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClGetKernelInfoRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClGetKernelInfoRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClGetKernelWorkGroupInfoRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClGetKernelWorkGroupInfoRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClGetKernelArgInfoRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClGetKernelArgInfoRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClGetKernelSubGroupInfoRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClGetKernelSubGroupInfoRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClReleaseCommandQueueRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClReleaseCommandQueueRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClReleaseContextRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClReleaseContextRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClReleaseDeviceRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClReleaseDeviceRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClReleaseKernelRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClReleaseKernelRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClReleaseSamplerRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClReleaseSamplerRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClReleaseProgramRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClReleaseProgramRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClReleaseMemObjectRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClReleaseMemObjectRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClReleaseEventRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClReleaseEventRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClRetainCommandQueueRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClRetainCommandQueueRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClRetainContextRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClRetainContextRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClRetainDeviceRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClRetainDeviceRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClRetainProgramRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClRetainProgramRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClRetainMemObjectRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClRetainMemObjectRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClRetainSamplerRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClRetainSamplerRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClRetainKernelRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClRetainKernelRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClRetainEventRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClRetainEventRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClFlushRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClFlushRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClFinishRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClFinishRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueNDRangeKernelRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueNDRangeKernelRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueTaskRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueTaskRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueMarkerWithWaitListRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueMarkerWithWaitListRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueMarkerRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueMarkerRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueBarrierWithWaitListRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueBarrierWithWaitListRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueBarrierRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueBarrierRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueWaitForEventsRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueWaitForEventsRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueMigrateMemObjectsRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueMigrateMemObjectsRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClCreateBufferRpcHelperUseHostPtrZeroCopyMallocShmemRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClCreateBufferRpcHelperUseHostPtrZeroCopyMallocShmemRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClCreateBufferRpcHelperNotUseHostPtrZeroCopyMallocShmemRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClCreateBufferRpcHelperNotUseHostPtrZeroCopyMallocShmemRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClCreateSubBufferRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClCreateSubBufferRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClCreatePipeRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClCreatePipeRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClGetPipeInfoRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClGetPipeInfoRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClCreateImageRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClCreateImageRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClCreateImage2DRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClCreateImage2DRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClCreateImage3DRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClCreateImage3DRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClCreateSamplerRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClCreateSamplerRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClCreateSamplerWithPropertiesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClCreateSamplerWithPropertiesRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClCreateImageWithPropertiesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClCreateImageWithPropertiesRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClCreateBufferWithPropertiesRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClCreateBufferWithPropertiesRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClGetSupportedImageFormatsRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClGetSupportedImageFormatsRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClSetKernelArgRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClSetKernelArgRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClSetProgramSpecializationConstantRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClSetProgramSpecializationConstantRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueWriteBufferRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueWriteBufferRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueWriteBufferRectRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueWriteBufferRectRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueReadBufferRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueReadBufferRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueReadBufferRectRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueReadBufferRectRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueCopyBufferRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueCopyBufferRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueCopyBufferRectRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueCopyBufferRectRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueReadImageRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueReadImageRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueWriteImageRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueWriteImageRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueCopyImageRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueCopyImageRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueCopyImageToBufferRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueCopyImageToBufferRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueCopyBufferToImageRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueCopyBufferToImageRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueMapBufferRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueMapBufferRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueUnmapMemObjectRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueUnmapMemObjectRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueFillBufferRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueFillBufferRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueFillImageRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueFillImageRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClWaitForEventsRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClWaitForEventsRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClGetEventInfoRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClGetEventInfoRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClGetEventProfilingInfoRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClGetEventProfilingInfoRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClCreateUserEventRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClCreateUserEventRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClSetUserEventStatusRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClSetUserEventStatusRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClSetEventCallbackRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClSetEventCallbackRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClGetDeviceAndHostTimerRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClGetDeviceAndHostTimerRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClGetHostTimerRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClGetHostTimerRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClSVMAllocRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClSVMAllocRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClSVMFreeRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClSVMFreeRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueSVMMapRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueSVMMapRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueSVMUnmapRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueSVMUnmapRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClSetKernelArgSVMPointerRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClSetKernelArgSVMPointerRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClSetKernelExecInfoRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClSetKernelExecInfoRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueSVMMemFillRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueSVMMemFillRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueSVMMigrateMemRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueSVMMigrateMemRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueSVMMemcpyRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueSVMMemcpyRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueSVMFreeRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueSVMFreeRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClCreateSubDevicesEXTRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClCreateSubDevicesEXTRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClReleaseDeviceEXTRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClReleaseDeviceEXTRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClRetainDeviceEXTRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClRetainDeviceEXTRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClGetKernelSubGroupInfoKHRRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClGetKernelSubGroupInfoKHRRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClGetKernelSuggestedLocalWorkSizeKHRRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClGetKernelSuggestedLocalWorkSizeKHRRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueMemFillINTELRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueMemFillINTELRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueMemcpyINTELRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueMemcpyINTELRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClSetKernelArgMemPointerINTELRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClSetKernelArgMemPointerINTELRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClGetMemAllocInfoINTELRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClGetMemAllocInfoINTELRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClDeviceMemAllocINTELRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClDeviceMemAllocINTELRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClHostMemAllocINTELRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClHostMemAllocINTELRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClSharedMemAllocINTELRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClSharedMemAllocINTELRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClMemFreeINTELRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClMemFreeINTELRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClMemBlockingFreeINTELRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClMemBlockingFreeINTELRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueMigrateMemINTELRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueMigrateMemINTELRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClGetDeviceGlobalVariablePointerINTELRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClGetDeviceGlobalVariablePointerINTELRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClCreateBufferRpcHelperNotUseHostPtrZeroCopyMallocShmem_UsmRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClCreateBufferRpcHelperNotUseHostPtrZeroCopyMallocShmem_UsmRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueWriteBuffer_LocalRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueWriteBuffer_LocalRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueWriteBuffer_UsmRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueWriteBuffer_UsmRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueWriteBuffer_SharedRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueWriteBuffer_SharedRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueWriteBufferRect_LocalRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueWriteBufferRect_LocalRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueWriteBufferRect_UsmRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueWriteBufferRect_UsmRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueWriteBufferRect_SharedRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueWriteBufferRect_SharedRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueReadBuffer_LocalRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueReadBuffer_LocalRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueReadBuffer_UsmRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueReadBuffer_UsmRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueReadBuffer_SharedRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueReadBuffer_SharedRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueReadBufferRect_LocalRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueReadBufferRect_LocalRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueReadBufferRect_UsmRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueReadBufferRect_UsmRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueReadBufferRect_SharedRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueReadBufferRect_SharedRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueSVMMemcpy_Local_LocalRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueSVMMemcpy_Local_LocalRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueSVMMemcpy_Local_UsmRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueSVMMemcpy_Local_UsmRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueSVMMemcpy_Local_SharedRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueSVMMemcpy_Local_SharedRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueSVMMemcpy_Usm_LocalRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueSVMMemcpy_Usm_LocalRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueSVMMemcpy_Usm_UsmRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueSVMMemcpy_Usm_UsmRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueSVMMemcpy_Usm_SharedRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueSVMMemcpy_Usm_SharedRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueSVMMemcpy_Shared_LocalRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueSVMMemcpy_Shared_LocalRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueSVMMemcpy_Shared_UsmRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueSVMMemcpy_Shared_UsmRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueSVMMemcpy_Shared_SharedRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueSVMMemcpy_Shared_SharedRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueMemcpyINTEL_Local_LocalRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueMemcpyINTEL_Local_LocalRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueMemcpyINTEL_Local_UsmRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueMemcpyINTEL_Local_UsmRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueMemcpyINTEL_Local_SharedRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueMemcpyINTEL_Local_SharedRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueMemcpyINTEL_Usm_LocalRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueMemcpyINTEL_Usm_LocalRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueMemcpyINTEL_Usm_UsmRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueMemcpyINTEL_Usm_UsmRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueMemcpyINTEL_Usm_SharedRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueMemcpyINTEL_Usm_SharedRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueMemcpyINTEL_Shared_LocalRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueMemcpyINTEL_Shared_LocalRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueMemcpyINTEL_Shared_UsmRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueMemcpyINTEL_Shared_UsmRpcM*>(command)); break;
        case Cal::Rpc::Ocl::ClEnqueueMemcpyINTEL_Shared_SharedRpcM::messageSubtype : callDirectly(*reinterpret_cast<Cal::Rpc::Ocl::ClEnqueueMemcpyINTEL_Shared_SharedRpcM*>(command)); break;
    }
    return true;
}

} // namespae Ocl
} // namespae Apis
} // namespae Service
} // namespae Cal
// #### Generated code -- end ####
