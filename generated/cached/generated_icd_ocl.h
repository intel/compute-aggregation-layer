/*
 * Copyright (C) 2022-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once
// #### Generated code -- begin ####

#include "client/icd/icd_ocl.h"

#include <cstdlib>

// Forward declarations of used RPC types
namespace Cal {
namespace Rpc {
namespace Ocl {

struct ClCreateContextRpcMImplicitArgs;
struct ClCreateContextFromTypeRpcMImplicitArgs;
struct ClSVMAllocRpcMImplicitArgs;
struct ClHostMemAllocINTELRpcMImplicitArgs;
struct ClSharedMemAllocINTELRpcMImplicitArgs;

} // namespace Ocl
} // namespace Rpc
} // namespace Cal

namespace Cal {
namespace Client {
namespace Icd {
namespace Ocl {
cl_int clGetPlatformIDsRpcHelper (cl_uint num_entries, cl_platform_id* platforms, cl_uint* num_platforms);
cl_int clIcdGetPlatformIDsKHR (cl_uint num_entries, cl_platform_id* platforms, cl_uint* num_platforms);
cl_int clGetPlatformInfoRpcHelper (cl_platform_id platform, cl_platform_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
void* clGetExtensionFunctionAddress (const char* funcname);
cl_int clGetDeviceIDs (cl_platform_id platform, cl_device_type device_type, cl_uint num_entries, cl_device_id* devices, cl_uint* num_devices);
cl_int clGetDeviceInfoRpcHelper (cl_device_id device, cl_device_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
cl_context clCreateContextRpcHelper (const cl_context_properties* properties, cl_uint num_devices, const cl_device_id* devices, void (CL_CALLBACK* pfn_notify)(const char* errinfo, const void* private_info, size_t cb, void* user_data), void* user_data, cl_int* errcode_ret, Cal::Rpc::Ocl::ClCreateContextRpcMImplicitArgs &implArgsForClCreateContextRpcM);
cl_context clCreateContextFromTypeRpcHelper (const cl_context_properties* properties, cl_device_type device_type, void (CL_CALLBACK* pfn_notify)(const char* errinfo, const void* private_info, size_t cb, void* user_data), void* user_data, cl_int* errcode_ret, Cal::Rpc::Ocl::ClCreateContextFromTypeRpcMImplicitArgs &implArgsForClCreateContextFromTypeRpcM);
cl_int clGetContextInfo (cl_context context, cl_context_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
cl_int clSetContextDestructorCallback (cl_context context, void (CL_CALLBACK* pfn_notify)(cl_context context, void* user_data), void* user_data);
cl_int clSetMemObjectDestructorCallback (cl_mem memobj, void (CL_CALLBACK* pfn_notify)(cl_mem memobj, void* user_data), void* user_data);
cl_int clCreateSubDevices (cl_device_id in_device, const cl_device_partition_property* properties, cl_uint num_devices, cl_device_id* out_devices, cl_uint* num_devices_ret);
cl_command_queue clCreateCommandQueue (cl_context context, cl_device_id device, cl_command_queue_properties  properties, cl_int* errcode_ret);
cl_int clSetDefaultDeviceCommandQueue (cl_context context, cl_device_id device, cl_command_queue command_queue);
cl_command_queue clCreateCommandQueueWithProperties (cl_context context, cl_device_id device, const cl_queue_properties* properties, cl_int* errcode_ret);
cl_program clCreateProgramWithSource (cl_context context, cl_uint count, const char** strings, const size_t* lengths, cl_int* errcode_ret);
cl_program clCreateProgramWithIL (cl_context context, const void* il, size_t length, cl_int* errcode_ret);
cl_program clCreateProgramWithBinary (cl_context context, cl_uint num_devices, const cl_device_id* device_list, const size_t* lengths, const unsigned char** binaries, cl_int* binary_status, cl_int* errcode_ret);
cl_program clCreateProgramWithBuiltInKernels (cl_context context, cl_uint num_devices, const cl_device_id* device_list, const char* kernel_names, cl_int* errcode_ret);
cl_int clUnloadCompiler ();
cl_int clUnloadPlatformCompiler (cl_platform_id platform);
cl_int clBuildProgram (cl_program program, cl_uint num_devices, const cl_device_id* device_list, const char* options, void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data), void* user_data);
cl_int clCompileProgram (cl_program program, cl_uint num_devices, const cl_device_id* device_list, const char* options, cl_uint num_input_headers, const cl_program* input_headers, const char** header_include_names, void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data), void* user_data);
cl_program clLinkProgram (cl_context context, cl_uint num_devices, const cl_device_id* device_list, const char* options, cl_uint num_input_programs, const cl_program* input_programs, void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data), void* user_data, cl_int* errcode_ret);
cl_int clGetProgramBuildInfo (cl_program program, cl_device_id device, cl_program_build_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
cl_int clSetProgramReleaseCallback (cl_program program, void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data), void* user_data);
cl_kernel clCreateKernelRpcHelper (cl_program program, const char* kernel_name, cl_int* errcode_ret);
cl_kernel clCloneKernel (cl_kernel source_kernel, cl_int* errcode_ret);
cl_int clCreateKernelsInProgramRpcHelper (cl_program program, cl_uint num_kernels, cl_kernel* kernels, cl_uint* num_kernels_ret);
cl_int clGetCommandQueueInfo (cl_command_queue command_queue, cl_command_queue_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
cl_int clGetProgramInfo (cl_program program, cl_program_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
cl_int clGetProgramInfoRpcHelper (cl_program program, cl_program_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
cl_int clGetProgramInfoGetBinariesRpcHelper (cl_program program, size_t total_binaries_size, unsigned char* concatenated_binaries, size_t binaries_count, const size_t* binaries_lengths, size_t* param_value_size_ret);
cl_int clGetMemObjectInfoRpcHelper (cl_mem memobj, cl_mem_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
cl_int clGetImageInfo (cl_mem image, cl_image_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
cl_int clGetSamplerInfo (cl_sampler sampler, cl_sampler_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
cl_int clGetKernelInfo (cl_kernel kernel, cl_kernel_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
cl_int clGetKernelWorkGroupInfo (cl_kernel kernel, cl_device_id device, cl_kernel_work_group_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
cl_int clGetKernelArgInfo (cl_kernel kernel, cl_uint arg_indx, cl_kernel_arg_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
cl_int clGetKernelSubGroupInfo (cl_kernel kernel, cl_device_id device, cl_kernel_sub_group_info param_name, size_t input_value_size, const void* input_value, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
cl_int clReleaseCommandQueue (cl_command_queue command_queue);
cl_int clReleaseContext (cl_context context);
cl_int clReleaseDevice (cl_device_id device);
cl_int clReleaseKernel (cl_kernel kernel);
cl_int clReleaseSampler (cl_sampler sampler);
cl_int clReleaseProgram (cl_program program);
cl_int clReleaseMemObject (cl_mem memobj);
cl_int clReleaseEvent (cl_event event);
cl_int clRetainCommandQueue (cl_command_queue command_queue);
cl_int clRetainContext (cl_context context);
cl_int clRetainDevice (cl_device_id device);
cl_int clRetainProgram (cl_program program);
cl_int clRetainMemObject (cl_mem memobj);
cl_int clRetainSampler (cl_sampler sampler);
cl_int clRetainKernel (cl_kernel kernel);
cl_int clRetainEvent (cl_event event);
cl_int clFlush (cl_command_queue command_queue);
cl_int clFinish (cl_command_queue command_queue);
cl_int clEnqueueNDRangeKernel (cl_command_queue command_queue, cl_kernel kernel, cl_uint work_dim, const size_t* global_work_offset, const size_t* global_work_size, const size_t* local_work_size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clEnqueueTask (cl_command_queue command_queue, cl_kernel kernel, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clEnqueueMarkerWithWaitList (cl_command_queue command_queue, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clEnqueueMarker (cl_command_queue command_queue, cl_event* event);
cl_int clEnqueueBarrierWithWaitList (cl_command_queue command_queue, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clEnqueueBarrier (cl_command_queue command_queue);
cl_int clEnqueueWaitForEvents (cl_command_queue command_queue, cl_uint num_events, const cl_event* event_list);
cl_int clEnqueueMigrateMemObjects (cl_command_queue command_queue, cl_uint num_mem_objects, const cl_mem* mem_objects, cl_mem_migration_flags flags, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
void* clGetExtensionFunctionAddressForPlatform (cl_platform_id platform, const char* funcname);
cl_mem clCreateBuffer (cl_context context, cl_mem_flags flags, size_t size, void* host_ptr, cl_int* errcode_ret);
cl_mem clCreateBufferRpcHelperUseHostPtrZeroCopyMallocShmem (cl_context context, cl_mem_flags flags, size_t size, void* host_ptr, cl_int* errcode_ret);
cl_mem clCreateBufferRpcHelperNotUseHostPtrZeroCopyMallocShmem (cl_context context, cl_mem_flags flags, size_t size, void* host_ptr, cl_int* errcode_ret);
cl_mem clCreateSubBufferRpcHelper (cl_mem buffer, cl_mem_flags flags, cl_buffer_create_type buffer_create_type, const void* buffer_create_info, cl_int* errcode_ret);
cl_mem clCreatePipe (cl_context context, cl_mem_flags flags, cl_uint pipe_packet_size, cl_uint pipe_max_packets, const cl_pipe_properties* properties, cl_int* errcode_ret);
cl_int clGetPipeInfo (cl_mem pipe, cl_pipe_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
cl_mem clCreateImage (cl_context context, cl_mem_flags flags, const cl_image_format* image_format, const cl_image_desc* image_desc, void* host_ptr, cl_int* errcode_ret);
cl_mem clCreateImage2D (cl_context context, cl_mem_flags flags, const cl_image_format* image_format, size_t image_width, size_t image_height, size_t image_row_pitch, void* host_ptr, cl_int* errcode_ret);
cl_mem clCreateImage3D (cl_context context, cl_mem_flags flags, const cl_image_format* image_format, size_t image_width, size_t image_height, size_t image_depth, size_t image_row_pitch, size_t image_slice_pitch, void* host_ptr, cl_int* errcode_ret);
cl_sampler clCreateSampler (cl_context context, cl_bool normalized_coords, cl_addressing_mode addressing_mode, cl_filter_mode filter_mode, cl_int* errcode_ret);
cl_sampler clCreateSamplerWithProperties (cl_context context, const cl_sampler_properties* properties, cl_int* errcode_ret);
cl_mem clCreateImageWithProperties (cl_context context, const cl_mem_properties* properties, cl_mem_flags flags, const cl_image_format* image_format, const cl_image_desc* image_desc, void* host_ptr, cl_int* errcode_ret);
cl_mem clCreateBufferWithProperties (cl_context context, const cl_mem_properties* properties, cl_mem_flags flags, size_t size, void* host_ptr, cl_int* errcode_ret);
cl_int clGetSupportedImageFormats (cl_context context, cl_mem_flags flags, cl_mem_object_type image_type, cl_uint num_entries, cl_image_format* image_formats, cl_uint* num_image_formats);
cl_int clSetKernelArgRpcHelper (cl_kernel kernel, cl_uint arg_index, size_t arg_size, const void* arg_value);
cl_int clSetProgramSpecializationConstant (cl_program program, cl_uint spec_id, size_t spec_size, const void* spec_value);
cl_int clEnqueueWriteBuffer (cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, size_t offset, size_t size, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clEnqueueWriteBufferRect (cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, const size_t* buffer_origin, const size_t* host_origin, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clEnqueueReadBuffer (cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, size_t offset, size_t size, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clEnqueueReadBufferRect (cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, const size_t* buffer_origin, const size_t* host_origin, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clEnqueueCopyBuffer (cl_command_queue command_queue, cl_mem src_buffer, cl_mem dst_buffer, size_t src_offset, size_t dst_offset, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clEnqueueCopyBufferRect (cl_command_queue command_queue, cl_mem src_buffer, cl_mem dst_buffer, const size_t* src_origin, const size_t* dst_origin, const size_t* region, size_t src_row_pitch, size_t src_slice_pitch, size_t dst_row_pitch, size_t dst_slice_pitch, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clEnqueueReadImage (cl_command_queue command_queue, cl_mem image, cl_bool blocking_read, const size_t* src_origin, const size_t* region, size_t row_pitch, size_t slice_pitch, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clEnqueueWriteImage (cl_command_queue command_queue, cl_mem image, cl_bool blocking_write, const size_t* origin, const size_t* region, size_t input_row_pitch, size_t input_slice_pitch, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clEnqueueCopyImage (cl_command_queue command_queue, cl_mem src_image, cl_mem dst_image, const size_t* src_origin, const size_t* dst_origin, const size_t* region, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clEnqueueCopyImageToBuffer (cl_command_queue command_queue, cl_mem src_image, cl_mem dst_buffer, const size_t* src_origin, const size_t* region, size_t dst_offset, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clEnqueueCopyBufferToImage (cl_command_queue command_queue, cl_mem src_buffer, cl_mem dst_image, size_t src_offset, const size_t* dst_origin, const size_t* region, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
void* clEnqueueMapBufferRpcHelper (cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_map, cl_map_flags map_flags, size_t offset, size_t cb, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event, cl_int* errcode_ret);
cl_int clEnqueueUnmapMemObjectRpcHelper (cl_command_queue command_queue, cl_mem memobj, void* mapped_ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clEnqueueFillBuffer (cl_command_queue command_queue, cl_mem memobj, const void* pattern, size_t patternSize, size_t offset, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clEnqueueFillImage (cl_command_queue command_queue, cl_mem image, const void* fill_color, const size_t* origin, const size_t* region, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clWaitForEventsRpcHelper (cl_uint num_events, const cl_event* event_list);
cl_int clGetEventInfoRpcHelper (cl_event event, cl_event_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
cl_int clGetEventProfilingInfo (cl_event event, cl_profiling_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
cl_event clCreateUserEvent (cl_context context, cl_int* errcode_ret);
cl_int clSetUserEventStatus (cl_event event, cl_int execution_status);
cl_int clSetEventCallback (cl_event event, cl_int command_exec_callback_type, void (CL_CALLBACK* pfn_notify)(cl_event event, cl_int event_command_status, void *user_data), void* user_data);
cl_int clGetDeviceAndHostTimer (cl_device_id device, cl_ulong* device_timestamp, cl_ulong* host_timestamp);
cl_int clGetHostTimerRpcHelper (cl_device_id device, cl_ulong* host_timestamp);
void* clSVMAllocRpcHelper (cl_context context, cl_svm_mem_flags flags, size_t size, cl_uint alignment, Cal::Rpc::Ocl::ClSVMAllocRpcMImplicitArgs &implArgsForClSVMAllocRpcM);
void clSVMFree (cl_context context, void* ptr);
cl_int clEnqueueSVMMap (cl_command_queue command_queue, cl_bool blocking_map, cl_map_flags map_flags, void* svm_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clEnqueueSVMUnmap (cl_command_queue command_queue, void* svm_ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clSetKernelArgSVMPointer (cl_kernel kernel, cl_uint argIndex, const void* argValue);
cl_int clSetKernelExecInfoRpcHelper (cl_kernel kernel, cl_kernel_exec_info param_name, size_t param_value_size, const void* param_value);
cl_int clEnqueueSVMMemFill (cl_command_queue command_queue, void* svm_ptr, const void* pattern, size_t patternSize, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clEnqueueSVMMigrateMem (cl_command_queue command_queue, cl_uint num_svm_pointers, const void** svm_pointers, const size_t* sizes, cl_mem_migration_flags flags, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clEnqueueSVMMemcpy (cl_command_queue command_queue, cl_bool blocking, void* dst_ptr, const void* src_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clEnqueueSVMFree (cl_command_queue command_queue, cl_uint num_svm_pointers, void** svm_pointers, void (CL_CALLBACK* pfn_notify)(cl_command_queue queue, cl_uint num_svm_pointers, void ** svm_pointers, void* user_data), void* user_data, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clCreateSubDevicesEXT (cl_device_id in_device, const cl_device_partition_property_ext* properties, cl_uint num_entries, cl_device_id* out_devices, cl_uint* num_devices);
cl_int clReleaseDeviceEXT (cl_device_id device);
cl_int clRetainDeviceEXT (cl_device_id device);
cl_int clGetKernelSubGroupInfoKHR (cl_kernel kernel, cl_device_id device, cl_kernel_sub_group_info param_name, size_t input_value_size, const void* input_value, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
cl_int clGetKernelSuggestedLocalWorkSizeKHR (cl_command_queue command_queue, cl_kernel kernel, cl_uint work_dim, const size_t* global_work_offset, const size_t* global_work_size, size_t * suggested_local_work_size);
cl_command_queue clCreateCommandQueueWithPropertiesKHR (cl_context context, cl_device_id device, const cl_queue_properties* properties, cl_int* errcode_ret);
cl_int clEnqueueMemFillINTEL (cl_command_queue command_queue, void* dstPtr, const void* pattern, size_t patternSize, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clEnqueueMemcpyINTEL (cl_command_queue command_queue, cl_bool blocking, void* dstPtr, const void* srcPtr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clSetKernelArgMemPointerINTELRpcHelper (cl_kernel kernel, cl_uint argIndex, const void* argValue);
cl_int clGetMemAllocInfoINTEL (cl_context context, const void* ptr, cl_mem_info_intel param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
void* clDeviceMemAllocINTEL (cl_context context, cl_device_id device, const cl_mem_properties_intel* properties, size_t size, cl_uint alignment, cl_int* errcode_ret);
void* clHostMemAllocINTELRpcHelper (cl_context context, const cl_mem_properties_intel* properties, size_t size, cl_uint alignment, cl_int* errcode_ret, Cal::Rpc::Ocl::ClHostMemAllocINTELRpcMImplicitArgs &implArgsForClHostMemAllocINTELRpcM);
void* clSharedMemAllocINTELRpcHelper (cl_context context, cl_device_id device, const cl_mem_properties_intel* properties, size_t size, cl_uint alignment, cl_int* errcode_ret, Cal::Rpc::Ocl::ClSharedMemAllocINTELRpcMImplicitArgs &implArgsForClSharedMemAllocINTELRpcM);
cl_int clMemFreeINTEL (cl_context context, void* ptr);
cl_int clMemBlockingFreeINTEL (cl_context context, void* ptr);
cl_int clEnqueueMigrateMemINTEL (cl_command_queue command_queue, const void* ptr, size_t size, cl_mem_migration_flags flags, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clEnqueueMemAdviseINTEL (cl_command_queue command_queue, const void* ptr, size_t size, cl_mem_advice_intel advice, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clGetDeviceGlobalVariablePointerINTEL (cl_device_id device, cl_program program, const char* globalVariableName, size_t* globalVariableSizeRet, void** globalVariablePointerRet);
cl_mem clCreateBufferRpcHelperNotUseHostPtrZeroCopyMallocShmem_Usm (cl_context context, cl_mem_flags flags, size_t size, void* host_ptr, cl_int* errcode_ret);
cl_int clEnqueueWriteBuffer_Local (cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, size_t offset, size_t size, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clEnqueueWriteBuffer_Usm (cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, size_t offset, size_t size, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clEnqueueWriteBuffer_Shared (cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, size_t offset, size_t size, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clEnqueueWriteBufferRect_Local (cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, const size_t* buffer_origin, const size_t* host_origin, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clEnqueueWriteBufferRect_Usm (cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, const size_t* buffer_origin, const size_t* host_origin, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clEnqueueWriteBufferRect_Shared (cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, const size_t* buffer_origin, const size_t* host_origin, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clEnqueueReadBuffer_Local (cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, size_t offset, size_t size, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clEnqueueReadBuffer_Usm (cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, size_t offset, size_t size, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clEnqueueReadBuffer_Shared (cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, size_t offset, size_t size, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clEnqueueReadBufferRect_Local (cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, const size_t* buffer_origin, const size_t* host_origin, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clEnqueueReadBufferRect_Usm (cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, const size_t* buffer_origin, const size_t* host_origin, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clEnqueueReadBufferRect_Shared (cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, const size_t* buffer_origin, const size_t* host_origin, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clEnqueueSVMMemcpy_Local_Local (cl_command_queue command_queue, cl_bool blocking, void* dst_ptr, const void* src_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clEnqueueSVMMemcpy_Local_Usm (cl_command_queue command_queue, cl_bool blocking, void* dst_ptr, const void* src_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clEnqueueSVMMemcpy_Local_Shared (cl_command_queue command_queue, cl_bool blocking, void* dst_ptr, const void* src_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clEnqueueSVMMemcpy_Usm_Local (cl_command_queue command_queue, cl_bool blocking, void* dst_ptr, const void* src_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clEnqueueSVMMemcpy_Usm_Usm (cl_command_queue command_queue, cl_bool blocking, void* dst_ptr, const void* src_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clEnqueueSVMMemcpy_Usm_Shared (cl_command_queue command_queue, cl_bool blocking, void* dst_ptr, const void* src_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clEnqueueSVMMemcpy_Shared_Local (cl_command_queue command_queue, cl_bool blocking, void* dst_ptr, const void* src_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clEnqueueSVMMemcpy_Shared_Usm (cl_command_queue command_queue, cl_bool blocking, void* dst_ptr, const void* src_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clEnqueueSVMMemcpy_Shared_Shared (cl_command_queue command_queue, cl_bool blocking, void* dst_ptr, const void* src_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clEnqueueMemcpyINTEL_Local_Local (cl_command_queue command_queue, cl_bool blocking, void* dstPtr, const void* srcPtr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clEnqueueMemcpyINTEL_Local_Usm (cl_command_queue command_queue, cl_bool blocking, void* dstPtr, const void* srcPtr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clEnqueueMemcpyINTEL_Local_Shared (cl_command_queue command_queue, cl_bool blocking, void* dstPtr, const void* srcPtr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clEnqueueMemcpyINTEL_Usm_Local (cl_command_queue command_queue, cl_bool blocking, void* dstPtr, const void* srcPtr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clEnqueueMemcpyINTEL_Usm_Usm (cl_command_queue command_queue, cl_bool blocking, void* dstPtr, const void* srcPtr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clEnqueueMemcpyINTEL_Usm_Shared (cl_command_queue command_queue, cl_bool blocking, void* dstPtr, const void* srcPtr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clEnqueueMemcpyINTEL_Shared_Local (cl_command_queue command_queue, cl_bool blocking, void* dstPtr, const void* srcPtr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clEnqueueMemcpyINTEL_Shared_Usm (cl_command_queue command_queue, cl_bool blocking, void* dstPtr, const void* srcPtr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
cl_int clEnqueueMemcpyINTEL_Shared_Shared (cl_command_queue command_queue, cl_bool blocking, void* dstPtr, const void* srcPtr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);

namespace Unimplemented {
inline void clSetCommandQueuePropertyUnimpl() {
    Cal::Utils::signalAbort("Function clSetCommandQueueProperty is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void clCreateFromGLBufferUnimpl() {
    Cal::Utils::signalAbort("Function clCreateFromGLBuffer is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void clCreateFromGLTexture2DUnimpl() {
    Cal::Utils::signalAbort("Function clCreateFromGLTexture2D is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void clCreateFromGLTexture3DUnimpl() {
    Cal::Utils::signalAbort("Function clCreateFromGLTexture3D is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void clCreateFromGLRenderbufferUnimpl() {
    Cal::Utils::signalAbort("Function clCreateFromGLRenderbuffer is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void clGetGLObjectInfoUnimpl() {
    Cal::Utils::signalAbort("Function clGetGLObjectInfo is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void clGetGLTextureInfoUnimpl() {
    Cal::Utils::signalAbort("Function clGetGLTextureInfo is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void clEnqueueAcquireGLObjectsUnimpl() {
    Cal::Utils::signalAbort("Function clEnqueueAcquireGLObjects is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void clEnqueueReleaseGLObjectsUnimpl() {
    Cal::Utils::signalAbort("Function clEnqueueReleaseGLObjects is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void clGetGLContextInfoKHRUnimpl() {
    Cal::Utils::signalAbort("Function clGetGLContextInfoKHR is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void clCreateEventFromGLsyncKHRUnimpl() {
    Cal::Utils::signalAbort("Function clCreateEventFromGLsyncKHR is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void clCreateFromGLTextureUnimpl() {
    Cal::Utils::signalAbort("Function clCreateFromGLTexture is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void clCreateFromEGLImageKHRUnimpl() {
    Cal::Utils::signalAbort("Function clCreateFromEGLImageKHR is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void clEnqueueAcquireEGLObjectsKHRUnimpl() {
    Cal::Utils::signalAbort("Function clEnqueueAcquireEGLObjectsKHR is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void clEnqueueReleaseEGLObjectsKHRUnimpl() {
    Cal::Utils::signalAbort("Function clEnqueueReleaseEGLObjectsKHR is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void clCreateEventFromEGLSyncKHRUnimpl() {
    Cal::Utils::signalAbort("Function clCreateEventFromEGLSyncKHR is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void clGetDeviceIDsFromD3D10KHRUnimpl() {
    Cal::Utils::signalAbort("Function clGetDeviceIDsFromD3D10KHR is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void clCreateFromD3D10BufferKHRUnimpl() {
    Cal::Utils::signalAbort("Function clCreateFromD3D10BufferKHR is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void clCreateFromD3D10Texture2DKHRUnimpl() {
    Cal::Utils::signalAbort("Function clCreateFromD3D10Texture2DKHR is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void clCreateFromD3D10Texture3DKHRUnimpl() {
    Cal::Utils::signalAbort("Function clCreateFromD3D10Texture3DKHR is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void clEnqueueAcquireD3D10ObjectsKHRUnimpl() {
    Cal::Utils::signalAbort("Function clEnqueueAcquireD3D10ObjectsKHR is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void clEnqueueReleaseD3D10ObjectsKHRUnimpl() {
    Cal::Utils::signalAbort("Function clEnqueueReleaseD3D10ObjectsKHR is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void clGetDeviceIDsFromD3D11KHRUnimpl() {
    Cal::Utils::signalAbort("Function clGetDeviceIDsFromD3D11KHR is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void clCreateFromD3D11BufferKHRUnimpl() {
    Cal::Utils::signalAbort("Function clCreateFromD3D11BufferKHR is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void clCreateFromD3D11Texture2DKHRUnimpl() {
    Cal::Utils::signalAbort("Function clCreateFromD3D11Texture2DKHR is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void clCreateFromD3D11Texture3DKHRUnimpl() {
    Cal::Utils::signalAbort("Function clCreateFromD3D11Texture3DKHR is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void clCreateFromDX9MediaSurfaceKHRUnimpl() {
    Cal::Utils::signalAbort("Function clCreateFromDX9MediaSurfaceKHR is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void clEnqueueAcquireD3D11ObjectsKHRUnimpl() {
    Cal::Utils::signalAbort("Function clEnqueueAcquireD3D11ObjectsKHR is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void clEnqueueReleaseD3D11ObjectsKHRUnimpl() {
    Cal::Utils::signalAbort("Function clEnqueueReleaseD3D11ObjectsKHR is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void clGetDeviceIDsFromDX9MediaAdapterKHRUnimpl() {
    Cal::Utils::signalAbort("Function clGetDeviceIDsFromDX9MediaAdapterKHR is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void clEnqueueAcquireDX9MediaSurfacesKHRUnimpl() {
    Cal::Utils::signalAbort("Function clEnqueueAcquireDX9MediaSurfacesKHR is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void clEnqueueReleaseDX9MediaSurfacesKHRUnimpl() {
    Cal::Utils::signalAbort("Function clEnqueueReleaseDX9MediaSurfacesKHR is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void clEnqueueMapImageUnimpl() {
    Cal::Utils::signalAbort("Function clEnqueueMapImage is not yet implemented in Compute Aggregation Layer - aborting");
}
inline void clEnqueueNativeKernelUnimpl() {
    Cal::Utils::signalAbort("Function clEnqueueNativeKernel is not yet implemented in Compute Aggregation Layer - aborting");
}
} // Unimplemented

inline void initOclIcdDispatchTable(cl_icd_dispatch &dt){
    dt.clGetPlatformIDs = Cal::Client::Icd::Ocl::clGetPlatformIDs;
    dt.clGetPlatformInfo = Cal::Client::Icd::Ocl::clGetPlatformInfo;
    dt.clGetExtensionFunctionAddress = Cal::Client::Icd::Ocl::clGetExtensionFunctionAddress;
    dt.clGetDeviceIDs = Cal::Client::Icd::Ocl::clGetDeviceIDs;
    dt.clGetDeviceInfo = Cal::Client::Icd::Ocl::clGetDeviceInfo;
    dt.clCreateContext = Cal::Client::Icd::Ocl::clCreateContext;
    dt.clCreateContextFromType = Cal::Client::Icd::Ocl::clCreateContextFromType;
    dt.clGetContextInfo = Cal::Client::Icd::Ocl::clGetContextInfo;
    dt.clSetContextDestructorCallback = Cal::Client::Icd::Ocl::clSetContextDestructorCallback;
    dt.clSetMemObjectDestructorCallback = Cal::Client::Icd::Ocl::clSetMemObjectDestructorCallback;
    dt.clCreateSubDevices = Cal::Client::Icd::Ocl::clCreateSubDevices;
    dt.clCreateCommandQueue = Cal::Client::Icd::Ocl::clCreateCommandQueue;
    dt.clSetDefaultDeviceCommandQueue = Cal::Client::Icd::Ocl::clSetDefaultDeviceCommandQueue;
    dt.clCreateCommandQueueWithProperties = Cal::Client::Icd::Ocl::clCreateCommandQueueWithProperties;
    dt.clCreateProgramWithSource = Cal::Client::Icd::Ocl::clCreateProgramWithSource;
    dt.clCreateProgramWithIL = Cal::Client::Icd::Ocl::clCreateProgramWithIL;
    dt.clCreateProgramWithBinary = Cal::Client::Icd::Ocl::clCreateProgramWithBinary;
    dt.clCreateProgramWithBuiltInKernels = Cal::Client::Icd::Ocl::clCreateProgramWithBuiltInKernels;
    dt.clUnloadCompiler = Cal::Client::Icd::Ocl::clUnloadCompiler;
    dt.clUnloadPlatformCompiler = Cal::Client::Icd::Ocl::clUnloadPlatformCompiler;
    dt.clBuildProgram = Cal::Client::Icd::Ocl::clBuildProgram;
    dt.clCompileProgram = Cal::Client::Icd::Ocl::clCompileProgram;
    dt.clLinkProgram = Cal::Client::Icd::Ocl::clLinkProgram;
    dt.clGetProgramBuildInfo = Cal::Client::Icd::Ocl::clGetProgramBuildInfo;
    dt.clSetProgramReleaseCallback = Cal::Client::Icd::Ocl::clSetProgramReleaseCallback;
    dt.clCreateKernel = Cal::Client::Icd::Ocl::clCreateKernel;
    dt.clCloneKernel = Cal::Client::Icd::Ocl::clCloneKernel;
    dt.clCreateKernelsInProgram = Cal::Client::Icd::Ocl::clCreateKernelsInProgram;
    dt.clGetCommandQueueInfo = Cal::Client::Icd::Ocl::clGetCommandQueueInfo;
    dt.clGetProgramInfo = Cal::Client::Icd::Ocl::clGetProgramInfo;
    dt.clGetMemObjectInfo = Cal::Client::Icd::Ocl::clGetMemObjectInfo;
    dt.clGetImageInfo = Cal::Client::Icd::Ocl::clGetImageInfo;
    dt.clGetSamplerInfo = Cal::Client::Icd::Ocl::clGetSamplerInfo;
    dt.clGetKernelInfo = Cal::Client::Icd::Ocl::clGetKernelInfo;
    dt.clGetKernelWorkGroupInfo = Cal::Client::Icd::Ocl::clGetKernelWorkGroupInfo;
    dt.clGetKernelArgInfo = Cal::Client::Icd::Ocl::clGetKernelArgInfo;
    dt.clGetKernelSubGroupInfo = Cal::Client::Icd::Ocl::clGetKernelSubGroupInfo;
    dt.clReleaseCommandQueue = Cal::Client::Icd::Ocl::clReleaseCommandQueue;
    dt.clReleaseContext = Cal::Client::Icd::Ocl::clReleaseContext;
    dt.clReleaseDevice = Cal::Client::Icd::Ocl::clReleaseDevice;
    dt.clReleaseKernel = Cal::Client::Icd::Ocl::clReleaseKernel;
    dt.clReleaseSampler = Cal::Client::Icd::Ocl::clReleaseSampler;
    dt.clReleaseProgram = Cal::Client::Icd::Ocl::clReleaseProgram;
    dt.clReleaseMemObject = Cal::Client::Icd::Ocl::clReleaseMemObject;
    dt.clReleaseEvent = Cal::Client::Icd::Ocl::clReleaseEvent;
    dt.clRetainCommandQueue = Cal::Client::Icd::Ocl::clRetainCommandQueue;
    dt.clRetainContext = Cal::Client::Icd::Ocl::clRetainContext;
    dt.clRetainDevice = Cal::Client::Icd::Ocl::clRetainDevice;
    dt.clRetainProgram = Cal::Client::Icd::Ocl::clRetainProgram;
    dt.clRetainMemObject = Cal::Client::Icd::Ocl::clRetainMemObject;
    dt.clRetainSampler = Cal::Client::Icd::Ocl::clRetainSampler;
    dt.clRetainKernel = Cal::Client::Icd::Ocl::clRetainKernel;
    dt.clRetainEvent = Cal::Client::Icd::Ocl::clRetainEvent;
    dt.clFlush = Cal::Client::Icd::Ocl::clFlush;
    dt.clFinish = Cal::Client::Icd::Ocl::clFinish;
    dt.clEnqueueNDRangeKernel = Cal::Client::Icd::Ocl::clEnqueueNDRangeKernel;
    dt.clEnqueueTask = Cal::Client::Icd::Ocl::clEnqueueTask;
    dt.clEnqueueMarkerWithWaitList = Cal::Client::Icd::Ocl::clEnqueueMarkerWithWaitList;
    dt.clEnqueueMarker = Cal::Client::Icd::Ocl::clEnqueueMarker;
    dt.clEnqueueBarrierWithWaitList = Cal::Client::Icd::Ocl::clEnqueueBarrierWithWaitList;
    dt.clEnqueueBarrier = Cal::Client::Icd::Ocl::clEnqueueBarrier;
    dt.clEnqueueWaitForEvents = Cal::Client::Icd::Ocl::clEnqueueWaitForEvents;
    dt.clEnqueueMigrateMemObjects = Cal::Client::Icd::Ocl::clEnqueueMigrateMemObjects;
    dt.clGetExtensionFunctionAddressForPlatform = Cal::Client::Icd::Ocl::clGetExtensionFunctionAddressForPlatform;
    dt.clCreateBuffer = Cal::Client::Icd::Ocl::clCreateBuffer;
    dt.clCreateSubBuffer = Cal::Client::Icd::Ocl::clCreateSubBuffer;
    dt.clCreatePipe = Cal::Client::Icd::Ocl::clCreatePipe;
    dt.clGetPipeInfo = Cal::Client::Icd::Ocl::clGetPipeInfo;
    dt.clCreateImage = Cal::Client::Icd::Ocl::clCreateImage;
    dt.clCreateImage2D = Cal::Client::Icd::Ocl::clCreateImage2D;
    dt.clCreateImage3D = Cal::Client::Icd::Ocl::clCreateImage3D;
    dt.clCreateSampler = Cal::Client::Icd::Ocl::clCreateSampler;
    dt.clCreateSamplerWithProperties = Cal::Client::Icd::Ocl::clCreateSamplerWithProperties;
    dt.clCreateImageWithProperties = Cal::Client::Icd::Ocl::clCreateImageWithProperties;
    dt.clCreateBufferWithProperties = Cal::Client::Icd::Ocl::clCreateBufferWithProperties;
    dt.clGetSupportedImageFormats = Cal::Client::Icd::Ocl::clGetSupportedImageFormats;
    dt.clSetKernelArg = Cal::Client::Icd::Ocl::clSetKernelArg;
    dt.clSetProgramSpecializationConstant = Cal::Client::Icd::Ocl::clSetProgramSpecializationConstant;
    dt.clEnqueueWriteBuffer = Cal::Client::Icd::Ocl::clEnqueueWriteBuffer;
    dt.clEnqueueWriteBufferRect = Cal::Client::Icd::Ocl::clEnqueueWriteBufferRect;
    dt.clEnqueueReadBuffer = Cal::Client::Icd::Ocl::clEnqueueReadBuffer;
    dt.clEnqueueReadBufferRect = Cal::Client::Icd::Ocl::clEnqueueReadBufferRect;
    dt.clEnqueueCopyBuffer = Cal::Client::Icd::Ocl::clEnqueueCopyBuffer;
    dt.clEnqueueCopyBufferRect = Cal::Client::Icd::Ocl::clEnqueueCopyBufferRect;
    dt.clEnqueueReadImage = Cal::Client::Icd::Ocl::clEnqueueReadImage;
    dt.clEnqueueWriteImage = Cal::Client::Icd::Ocl::clEnqueueWriteImage;
    dt.clEnqueueCopyImage = Cal::Client::Icd::Ocl::clEnqueueCopyImage;
    dt.clEnqueueCopyImageToBuffer = Cal::Client::Icd::Ocl::clEnqueueCopyImageToBuffer;
    dt.clEnqueueCopyBufferToImage = Cal::Client::Icd::Ocl::clEnqueueCopyBufferToImage;
    dt.clEnqueueMapBuffer = Cal::Client::Icd::Ocl::clEnqueueMapBuffer;
    dt.clEnqueueUnmapMemObject = Cal::Client::Icd::Ocl::clEnqueueUnmapMemObject;
    dt.clEnqueueFillBuffer = Cal::Client::Icd::Ocl::clEnqueueFillBuffer;
    dt.clEnqueueFillImage = Cal::Client::Icd::Ocl::clEnqueueFillImage;
    dt.clWaitForEvents = Cal::Client::Icd::Ocl::clWaitForEvents;
    dt.clGetEventInfo = Cal::Client::Icd::Ocl::clGetEventInfo;
    dt.clGetEventProfilingInfo = Cal::Client::Icd::Ocl::clGetEventProfilingInfo;
    dt.clCreateUserEvent = Cal::Client::Icd::Ocl::clCreateUserEvent;
    dt.clSetUserEventStatus = Cal::Client::Icd::Ocl::clSetUserEventStatus;
    dt.clSetEventCallback = Cal::Client::Icd::Ocl::clSetEventCallback;
    dt.clGetDeviceAndHostTimer = Cal::Client::Icd::Ocl::clGetDeviceAndHostTimer;
    dt.clGetHostTimer = Cal::Client::Icd::Ocl::clGetHostTimer;
    dt.clSVMAlloc = Cal::Client::Icd::Ocl::clSVMAlloc;
    dt.clSVMFree = Cal::Client::Icd::Ocl::clSVMFree;
    dt.clEnqueueSVMMap = Cal::Client::Icd::Ocl::clEnqueueSVMMap;
    dt.clEnqueueSVMUnmap = Cal::Client::Icd::Ocl::clEnqueueSVMUnmap;
    dt.clSetKernelArgSVMPointer = Cal::Client::Icd::Ocl::clSetKernelArgSVMPointer;
    dt.clSetKernelExecInfo = Cal::Client::Icd::Ocl::clSetKernelExecInfo;
    dt.clEnqueueSVMMemFill = Cal::Client::Icd::Ocl::clEnqueueSVMMemFill;
    dt.clEnqueueSVMMigrateMem = Cal::Client::Icd::Ocl::clEnqueueSVMMigrateMem;
    dt.clEnqueueSVMMemcpy = Cal::Client::Icd::Ocl::clEnqueueSVMMemcpy;
    dt.clEnqueueSVMFree = Cal::Client::Icd::Ocl::clEnqueueSVMFree;
    dt.clCreateSubDevicesEXT = Cal::Client::Icd::Ocl::clCreateSubDevicesEXT;
    dt.clReleaseDeviceEXT = Cal::Client::Icd::Ocl::clReleaseDeviceEXT;
    dt.clRetainDeviceEXT = Cal::Client::Icd::Ocl::clRetainDeviceEXT;
    dt.clGetKernelSubGroupInfoKHR = Cal::Client::Icd::Ocl::clGetKernelSubGroupInfoKHR;
    // below are unimplemented, provided bindings are for easier debugging only
    dt.clSetCommandQueueProperty = reinterpret_cast<decltype(dt.clSetCommandQueueProperty)>(Cal::Client::Icd::Ocl::Unimplemented::clSetCommandQueuePropertyUnimpl);
    dt.clCreateFromGLBuffer = reinterpret_cast<decltype(dt.clCreateFromGLBuffer)>(Cal::Client::Icd::Ocl::Unimplemented::clCreateFromGLBufferUnimpl);
    dt.clCreateFromGLTexture2D = reinterpret_cast<decltype(dt.clCreateFromGLTexture2D)>(Cal::Client::Icd::Ocl::Unimplemented::clCreateFromGLTexture2DUnimpl);
    dt.clCreateFromGLTexture3D = reinterpret_cast<decltype(dt.clCreateFromGLTexture3D)>(Cal::Client::Icd::Ocl::Unimplemented::clCreateFromGLTexture3DUnimpl);
    dt.clCreateFromGLRenderbuffer = reinterpret_cast<decltype(dt.clCreateFromGLRenderbuffer)>(Cal::Client::Icd::Ocl::Unimplemented::clCreateFromGLRenderbufferUnimpl);
    dt.clGetGLObjectInfo = reinterpret_cast<decltype(dt.clGetGLObjectInfo)>(Cal::Client::Icd::Ocl::Unimplemented::clGetGLObjectInfoUnimpl);
    dt.clGetGLTextureInfo = reinterpret_cast<decltype(dt.clGetGLTextureInfo)>(Cal::Client::Icd::Ocl::Unimplemented::clGetGLTextureInfoUnimpl);
    dt.clEnqueueAcquireGLObjects = reinterpret_cast<decltype(dt.clEnqueueAcquireGLObjects)>(Cal::Client::Icd::Ocl::Unimplemented::clEnqueueAcquireGLObjectsUnimpl);
    dt.clEnqueueReleaseGLObjects = reinterpret_cast<decltype(dt.clEnqueueReleaseGLObjects)>(Cal::Client::Icd::Ocl::Unimplemented::clEnqueueReleaseGLObjectsUnimpl);
    dt.clGetGLContextInfoKHR = reinterpret_cast<decltype(dt.clGetGLContextInfoKHR)>(Cal::Client::Icd::Ocl::Unimplemented::clGetGLContextInfoKHRUnimpl);
    dt.clCreateEventFromGLsyncKHR = reinterpret_cast<decltype(dt.clCreateEventFromGLsyncKHR)>(Cal::Client::Icd::Ocl::Unimplemented::clCreateEventFromGLsyncKHRUnimpl);
    dt.clCreateFromGLTexture = reinterpret_cast<decltype(dt.clCreateFromGLTexture)>(Cal::Client::Icd::Ocl::Unimplemented::clCreateFromGLTextureUnimpl);
    dt.clCreateFromEGLImageKHR = reinterpret_cast<decltype(dt.clCreateFromEGLImageKHR)>(Cal::Client::Icd::Ocl::Unimplemented::clCreateFromEGLImageKHRUnimpl);
    dt.clEnqueueAcquireEGLObjectsKHR = reinterpret_cast<decltype(dt.clEnqueueAcquireEGLObjectsKHR)>(Cal::Client::Icd::Ocl::Unimplemented::clEnqueueAcquireEGLObjectsKHRUnimpl);
    dt.clEnqueueReleaseEGLObjectsKHR = reinterpret_cast<decltype(dt.clEnqueueReleaseEGLObjectsKHR)>(Cal::Client::Icd::Ocl::Unimplemented::clEnqueueReleaseEGLObjectsKHRUnimpl);
    dt.clCreateEventFromEGLSyncKHR = reinterpret_cast<decltype(dt.clCreateEventFromEGLSyncKHR)>(Cal::Client::Icd::Ocl::Unimplemented::clCreateEventFromEGLSyncKHRUnimpl);
    dt.clGetDeviceIDsFromD3D10KHR = reinterpret_cast<decltype(dt.clGetDeviceIDsFromD3D10KHR)>(Cal::Client::Icd::Ocl::Unimplemented::clGetDeviceIDsFromD3D10KHRUnimpl);
    dt.clCreateFromD3D10BufferKHR = reinterpret_cast<decltype(dt.clCreateFromD3D10BufferKHR)>(Cal::Client::Icd::Ocl::Unimplemented::clCreateFromD3D10BufferKHRUnimpl);
    dt.clCreateFromD3D10Texture2DKHR = reinterpret_cast<decltype(dt.clCreateFromD3D10Texture2DKHR)>(Cal::Client::Icd::Ocl::Unimplemented::clCreateFromD3D10Texture2DKHRUnimpl);
    dt.clCreateFromD3D10Texture3DKHR = reinterpret_cast<decltype(dt.clCreateFromD3D10Texture3DKHR)>(Cal::Client::Icd::Ocl::Unimplemented::clCreateFromD3D10Texture3DKHRUnimpl);
    dt.clEnqueueAcquireD3D10ObjectsKHR = reinterpret_cast<decltype(dt.clEnqueueAcquireD3D10ObjectsKHR)>(Cal::Client::Icd::Ocl::Unimplemented::clEnqueueAcquireD3D10ObjectsKHRUnimpl);
    dt.clEnqueueReleaseD3D10ObjectsKHR = reinterpret_cast<decltype(dt.clEnqueueReleaseD3D10ObjectsKHR)>(Cal::Client::Icd::Ocl::Unimplemented::clEnqueueReleaseD3D10ObjectsKHRUnimpl);
    dt.clGetDeviceIDsFromD3D11KHR = reinterpret_cast<decltype(dt.clGetDeviceIDsFromD3D11KHR)>(Cal::Client::Icd::Ocl::Unimplemented::clGetDeviceIDsFromD3D11KHRUnimpl);
    dt.clCreateFromD3D11BufferKHR = reinterpret_cast<decltype(dt.clCreateFromD3D11BufferKHR)>(Cal::Client::Icd::Ocl::Unimplemented::clCreateFromD3D11BufferKHRUnimpl);
    dt.clCreateFromD3D11Texture2DKHR = reinterpret_cast<decltype(dt.clCreateFromD3D11Texture2DKHR)>(Cal::Client::Icd::Ocl::Unimplemented::clCreateFromD3D11Texture2DKHRUnimpl);
    dt.clCreateFromD3D11Texture3DKHR = reinterpret_cast<decltype(dt.clCreateFromD3D11Texture3DKHR)>(Cal::Client::Icd::Ocl::Unimplemented::clCreateFromD3D11Texture3DKHRUnimpl);
    dt.clCreateFromDX9MediaSurfaceKHR = reinterpret_cast<decltype(dt.clCreateFromDX9MediaSurfaceKHR)>(Cal::Client::Icd::Ocl::Unimplemented::clCreateFromDX9MediaSurfaceKHRUnimpl);
    dt.clEnqueueAcquireD3D11ObjectsKHR = reinterpret_cast<decltype(dt.clEnqueueAcquireD3D11ObjectsKHR)>(Cal::Client::Icd::Ocl::Unimplemented::clEnqueueAcquireD3D11ObjectsKHRUnimpl);
    dt.clEnqueueReleaseD3D11ObjectsKHR = reinterpret_cast<decltype(dt.clEnqueueReleaseD3D11ObjectsKHR)>(Cal::Client::Icd::Ocl::Unimplemented::clEnqueueReleaseD3D11ObjectsKHRUnimpl);
    dt.clGetDeviceIDsFromDX9MediaAdapterKHR = reinterpret_cast<decltype(dt.clGetDeviceIDsFromDX9MediaAdapterKHR)>(Cal::Client::Icd::Ocl::Unimplemented::clGetDeviceIDsFromDX9MediaAdapterKHRUnimpl);
    dt.clEnqueueAcquireDX9MediaSurfacesKHR = reinterpret_cast<decltype(dt.clEnqueueAcquireDX9MediaSurfacesKHR)>(Cal::Client::Icd::Ocl::Unimplemented::clEnqueueAcquireDX9MediaSurfacesKHRUnimpl);
    dt.clEnqueueReleaseDX9MediaSurfacesKHR = reinterpret_cast<decltype(dt.clEnqueueReleaseDX9MediaSurfacesKHR)>(Cal::Client::Icd::Ocl::Unimplemented::clEnqueueReleaseDX9MediaSurfacesKHRUnimpl);
    dt.clEnqueueMapImage = reinterpret_cast<decltype(dt.clEnqueueMapImage)>(Cal::Client::Icd::Ocl::Unimplemented::clEnqueueMapImageUnimpl);
    dt.clEnqueueNativeKernel = reinterpret_cast<decltype(dt.clEnqueueNativeKernel)>(Cal::Client::Icd::Ocl::Unimplemented::clEnqueueNativeKernelUnimpl);
}

void *getOclExtensionFuncionAddressRpcHelper(const char *funcName);
} // namespace Ocl
} // namespace Icd
} // namespace Client
} // namespace Cal
// #### Generated code -- end ####
