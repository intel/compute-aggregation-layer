/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

// #### Generated code -- begin ####

#include "client/icd/icd_ocl.h"
#include "generated_rpc_messages_ocl.h"
#include "shared/utils.h"

namespace Cal {
namespace Rpc {
namespace Ocl {

using namespace Cal::Utils;

ClGetPlatformIDsRpcM::Captures::DynamicTraits ClGetPlatformIDsRpcM::Captures::DynamicTraits::calculate(cl_uint num_entries, cl_platform_id* platforms, cl_uint* num_platforms) {
    DynamicTraits ret = {};
    ret.platforms.count = num_entries;
    ret.platforms.size = ret.platforms.count * sizeof(cl_platform_id);
    ret.totalDynamicSize = alignUpPow2<8>(ret.platforms.offset + ret.platforms.size);


    return ret;
}

size_t ClGetPlatformIDsRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, platforms) + Cal::Utils::alignUpPow2<8>(this->countPlatforms * sizeof(cl_platform_id));
     return size;
}

size_t ClGetPlatformIDsRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countPlatforms * sizeof(cl_platform_id));
     return size;
}

ClGetPlatformInfoRpcM::Captures::DynamicTraits ClGetPlatformInfoRpcM::Captures::DynamicTraits::calculate(cl_platform_id platform, cl_platform_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    DynamicTraits ret = {};
    ret.param_value.count = param_value_size;
    ret.param_value.size = ret.param_value.count;
    ret.totalDynamicSize = alignUpPow2<8>(ret.param_value.offset + ret.param_value.size);


    return ret;
}

size_t ClGetPlatformInfoRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, param_value) + Cal::Utils::alignUpPow2<8>(this->countParam_value);
     return size;
}

size_t ClGetPlatformInfoRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countParam_value);
     return size;
}

ClGetDeviceIDsRpcM::Captures::DynamicTraits ClGetDeviceIDsRpcM::Captures::DynamicTraits::calculate(cl_platform_id platform, cl_device_type device_type, cl_uint num_entries, cl_device_id* devices, cl_uint* num_devices) {
    DynamicTraits ret = {};
    ret.devices.count = num_entries;
    ret.devices.size = ret.devices.count * sizeof(cl_device_id);
    ret.totalDynamicSize = alignUpPow2<8>(ret.devices.offset + ret.devices.size);


    return ret;
}

size_t ClGetDeviceIDsRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, devices) + Cal::Utils::alignUpPow2<8>(this->countDevices * sizeof(cl_device_id));
     return size;
}

size_t ClGetDeviceIDsRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countDevices * sizeof(cl_device_id));
     return size;
}

ClGetDeviceInfoRpcM::Captures::DynamicTraits ClGetDeviceInfoRpcM::Captures::DynamicTraits::calculate(cl_device_id device, cl_device_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    DynamicTraits ret = {};
    ret.param_value.count = param_value_size;
    ret.param_value.size = ret.param_value.count;
    ret.totalDynamicSize = alignUpPow2<8>(ret.param_value.offset + ret.param_value.size);


    return ret;
}

size_t ClGetDeviceInfoRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, param_value) + Cal::Utils::alignUpPow2<8>(this->countParam_value);
     return size;
}

size_t ClGetDeviceInfoRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countParam_value);
     return size;
}

ClCreateContextRpcM::Captures::DynamicTraits ClCreateContextRpcM::Captures::DynamicTraits::calculate(const cl_context_properties* properties, cl_uint num_devices, const cl_device_id* devices, void (CL_CALLBACK* pfn_notify)(const char* errinfo, const void* private_info, size_t cb, void* user_data), void* user_data, cl_int* errcode_ret) {
    DynamicTraits ret = {};
    ret.devices.count = num_devices;
    ret.devices.size = ret.devices.count * sizeof(cl_device_id);

    ret.properties.offset = alignUpPow2<8>(ret.devices.offset + ret.devices.size);
    ret.properties.count = Cal::Utils::countNullterminatedKey(properties);
    ret.properties.size = ret.properties.count * sizeof(cl_context_properties);
    ret.totalDynamicSize = alignUpPow2<8>(ret.properties.offset + ret.properties.size);


    return ret;
}

size_t ClCreateContextRpcM::Captures::getCaptureTotalSize() const {
     const auto lastMemberOffset = offsetProperties;
     const auto lastMemberArraySize = this->countProperties * sizeof(cl_context_properties);

     auto size = offsetof(Captures, dynMem) + Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

size_t ClCreateContextRpcM::Captures::getCaptureDynMemSize() const {
     const auto lastMemberOffset = offsetProperties;
     const auto lastMemberArraySize = this->countProperties * sizeof(cl_context_properties);

     auto size = Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

ClCreateContextFromTypeRpcM::Captures::DynamicTraits ClCreateContextFromTypeRpcM::Captures::DynamicTraits::calculate(const cl_context_properties* properties, cl_device_type device_type, void (CL_CALLBACK* pfn_notify)(const char* errinfo, const void* private_info, size_t cb, void* user_data), void* user_data, cl_int* errcode_ret) {
    DynamicTraits ret = {};
    ret.properties.count = Cal::Utils::countNullterminatedKey(properties);
    ret.properties.size = ret.properties.count * sizeof(cl_context_properties);
    ret.totalDynamicSize = alignUpPow2<8>(ret.properties.offset + ret.properties.size);


    return ret;
}

size_t ClCreateContextFromTypeRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, properties) + Cal::Utils::alignUpPow2<8>(this->countProperties * sizeof(cl_context_properties));
     return size;
}

size_t ClCreateContextFromTypeRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countProperties * sizeof(cl_context_properties));
     return size;
}

ClGetContextInfoRpcM::Captures::DynamicTraits ClGetContextInfoRpcM::Captures::DynamicTraits::calculate(cl_context context, cl_context_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    DynamicTraits ret = {};
    ret.param_value.count = param_value_size;
    ret.param_value.size = ret.param_value.count;
    ret.totalDynamicSize = alignUpPow2<8>(ret.param_value.offset + ret.param_value.size);


    return ret;
}

size_t ClGetContextInfoRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, param_value) + Cal::Utils::alignUpPow2<8>(this->countParam_value);
     return size;
}

size_t ClGetContextInfoRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countParam_value);
     return size;
}

ClCreateSubDevicesRpcM::Captures::DynamicTraits ClCreateSubDevicesRpcM::Captures::DynamicTraits::calculate(cl_device_id in_device, const cl_device_partition_property* properties, cl_uint num_devices, cl_device_id* out_devices, cl_uint* num_devices_ret) {
    DynamicTraits ret = {};
    ret.out_devices.count = num_devices;
    ret.out_devices.size = ret.out_devices.count * sizeof(cl_device_id);

    ret.properties.offset = alignUpPow2<8>(ret.out_devices.offset + ret.out_devices.size);
    ret.properties.count = Cal::Utils::countNullterminatedKey(properties);
    ret.properties.size = ret.properties.count * sizeof(cl_device_partition_property);
    ret.totalDynamicSize = alignUpPow2<8>(ret.properties.offset + ret.properties.size);


    return ret;
}

size_t ClCreateSubDevicesRpcM::Captures::getCaptureTotalSize() const {
     const auto lastMemberOffset = offsetProperties;
     const auto lastMemberArraySize = this->countProperties * sizeof(cl_device_partition_property);

     auto size = offsetof(Captures, dynMem) + Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

size_t ClCreateSubDevicesRpcM::Captures::getCaptureDynMemSize() const {
     const auto lastMemberOffset = offsetProperties;
     const auto lastMemberArraySize = this->countProperties * sizeof(cl_device_partition_property);

     auto size = Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

ClCreateCommandQueueWithPropertiesRpcM::Captures::DynamicTraits ClCreateCommandQueueWithPropertiesRpcM::Captures::DynamicTraits::calculate(cl_context context, cl_device_id device, const cl_queue_properties* properties, cl_int* errcode_ret) {
    DynamicTraits ret = {};
    ret.properties.count = Cal::Utils::countNullterminatedKey(properties);
    ret.properties.size = ret.properties.count * sizeof(cl_queue_properties);
    ret.totalDynamicSize = alignUpPow2<8>(ret.properties.offset + ret.properties.size);


    return ret;
}

size_t ClCreateCommandQueueWithPropertiesRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, properties) + Cal::Utils::alignUpPow2<8>(this->countProperties * sizeof(cl_queue_properties));
     return size;
}

size_t ClCreateCommandQueueWithPropertiesRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countProperties * sizeof(cl_queue_properties));
     return size;
}

ClCreateProgramWithSourceRpcM::Captures::DynamicTraits ClCreateProgramWithSourceRpcM::Captures::DynamicTraits::calculate(cl_context context, cl_uint count, const char** strings, const size_t* lengths, cl_int* errcode_ret) {
    DynamicTraits ret = {};
    ret.lengths.count = count;
    ret.lengths.size = ret.lengths.count * sizeof(size_t);

    ret.strings.offset = alignUpPow2<8>(ret.lengths.offset + ret.lengths.size);
    ret.strings.count = count;
    ret.strings.size = ret.strings.count * sizeof(uint32_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.strings.offset + ret.strings.size);

    ret.strings.nested.reserve(ret.strings.count);
    for(uint32_t i = 0; i < ret.strings.count; ++i){
        DynamicArgTraits nested;
        nested.offset = ret.totalDynamicSize;
        nested.count = Cal::Icd::Ocl::getSingleSourceLengthForClCreateProgramWithSource(strings, i, lengths);
        nested.size = nested.count * sizeof(char);
        ret.totalDynamicSize += alignUpPow2<8>(nested.size);
        ret.strings.nested.push_back(nested);
    }

    return ret;
}

size_t ClCreateProgramWithSourceRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, dynMem) + dynMemSize;
     return size;
}

size_t ClCreateProgramWithSourceRpcM::Captures::getCaptureDynMemSize() const {
     return dynMemSize;
}

ClCreateProgramWithILRpcM::Captures::DynamicTraits ClCreateProgramWithILRpcM::Captures::DynamicTraits::calculate(cl_context context, const void* il, size_t length, cl_int* errcode_ret) {
    DynamicTraits ret = {};
    ret.il.count = length;
    ret.il.size = ret.il.count;
    ret.totalDynamicSize = alignUpPow2<8>(ret.il.offset + ret.il.size);


    return ret;
}

size_t ClCreateProgramWithILRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, il) + Cal::Utils::alignUpPow2<8>(this->countIl);
     return size;
}

size_t ClCreateProgramWithILRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countIl);
     return size;
}

ClCreateProgramWithBinaryRpcM::Captures::DynamicTraits ClCreateProgramWithBinaryRpcM::Captures::DynamicTraits::calculate(cl_context context, cl_uint num_devices, const cl_device_id* device_list, const size_t* lengths, const unsigned char** binaries, cl_int* binary_status, cl_int* errcode_ret) {
    DynamicTraits ret = {};
    ret.device_list.count = num_devices;
    ret.device_list.size = ret.device_list.count * sizeof(cl_device_id);

    ret.lengths.offset = alignUpPow2<8>(ret.device_list.offset + ret.device_list.size);
    ret.lengths.count = num_devices;
    ret.lengths.size = ret.lengths.count * sizeof(size_t);

    ret.binary_status.offset = alignUpPow2<8>(ret.lengths.offset + ret.lengths.size);
    ret.binary_status.count = num_devices;
    ret.binary_status.size = ret.binary_status.count * sizeof(cl_int);

    ret.binaries.offset = alignUpPow2<8>(ret.binary_status.offset + ret.binary_status.size);
    ret.binaries.count = num_devices;
    ret.binaries.size = ret.binaries.count * sizeof(uint32_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.binaries.offset + ret.binaries.size);

    ret.binaries.nested.reserve(ret.binaries.count);
    for(uint32_t i = 0; i < ret.binaries.count; ++i){
        DynamicArgTraits nested;
        nested.offset = ret.totalDynamicSize;
        nested.count = lengths[i];
        nested.size = nested.count * sizeof(unsigned char);
        ret.totalDynamicSize += alignUpPow2<8>(nested.size);
        ret.binaries.nested.push_back(nested);
    }

    return ret;
}

size_t ClCreateProgramWithBinaryRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, dynMem) + dynMemSize;
     return size;
}

size_t ClCreateProgramWithBinaryRpcM::Captures::getCaptureDynMemSize() const {
     return dynMemSize;
}

ClCreateProgramWithBuiltInKernelsRpcM::Captures::DynamicTraits ClCreateProgramWithBuiltInKernelsRpcM::Captures::DynamicTraits::calculate(cl_context context, cl_uint num_devices, const cl_device_id* device_list, const char* kernel_names, cl_int* errcode_ret) {
    DynamicTraits ret = {};
    ret.device_list.count = num_devices;
    ret.device_list.size = ret.device_list.count * sizeof(cl_device_id);

    ret.kernel_names.offset = alignUpPow2<8>(ret.device_list.offset + ret.device_list.size);
    ret.kernel_names.count = Cal::Utils::countNullterminated(kernel_names);
    ret.kernel_names.size = ret.kernel_names.count * sizeof(char);
    ret.totalDynamicSize = alignUpPow2<8>(ret.kernel_names.offset + ret.kernel_names.size);


    return ret;
}

size_t ClCreateProgramWithBuiltInKernelsRpcM::Captures::getCaptureTotalSize() const {
     const auto lastMemberOffset = offsetKernel_names;
     const auto lastMemberArraySize = this->countKernel_names * sizeof(char);

     auto size = offsetof(Captures, dynMem) + Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

size_t ClCreateProgramWithBuiltInKernelsRpcM::Captures::getCaptureDynMemSize() const {
     const auto lastMemberOffset = offsetKernel_names;
     const auto lastMemberArraySize = this->countKernel_names * sizeof(char);

     auto size = Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

ClBuildProgramRpcM::Captures::DynamicTraits ClBuildProgramRpcM::Captures::DynamicTraits::calculate(cl_program program, cl_uint num_devices, const cl_device_id* device_list, const char* options, void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data), void* user_data) {
    DynamicTraits ret = {};
    ret.device_list.count = num_devices;
    ret.device_list.size = ret.device_list.count * sizeof(cl_device_id);

    ret.options.offset = alignUpPow2<8>(ret.device_list.offset + ret.device_list.size);
    ret.options.count = Cal::Utils::countNullterminated(options);
    ret.options.size = ret.options.count * sizeof(char);
    ret.totalDynamicSize = alignUpPow2<8>(ret.options.offset + ret.options.size);


    return ret;
}

size_t ClBuildProgramRpcM::Captures::getCaptureTotalSize() const {
     const auto lastMemberOffset = offsetOptions;
     const auto lastMemberArraySize = this->countOptions * sizeof(char);

     auto size = offsetof(Captures, dynMem) + Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

size_t ClBuildProgramRpcM::Captures::getCaptureDynMemSize() const {
     const auto lastMemberOffset = offsetOptions;
     const auto lastMemberArraySize = this->countOptions * sizeof(char);

     auto size = Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

ClCompileProgramRpcM::Captures::DynamicTraits ClCompileProgramRpcM::Captures::DynamicTraits::calculate(cl_program program, cl_uint num_devices, const cl_device_id* device_list, const char* options, cl_uint num_input_headers, const cl_program* input_headers, const char** header_include_names, void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data), void* user_data) {
    DynamicTraits ret = {};
    ret.device_list.count = num_devices;
    ret.device_list.size = ret.device_list.count * sizeof(cl_device_id);

    ret.input_headers.offset = alignUpPow2<8>(ret.device_list.offset + ret.device_list.size);
    ret.input_headers.count = num_input_headers;
    ret.input_headers.size = ret.input_headers.count * sizeof(cl_program);

    ret.options.offset = alignUpPow2<8>(ret.input_headers.offset + ret.input_headers.size);
    ret.options.count = Cal::Utils::countNullterminated(options);
    ret.options.size = ret.options.count * sizeof(char);

    ret.header_include_names.offset = alignUpPow2<8>(ret.options.offset + ret.options.size);
    ret.header_include_names.count = num_input_headers;
    ret.header_include_names.size = ret.header_include_names.count * sizeof(uint32_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.header_include_names.offset + ret.header_include_names.size);

    ret.header_include_names.nested.reserve(ret.header_include_names.count);
    for(uint32_t i = 0; i < ret.header_include_names.count; ++i){
        DynamicArgTraits nested;
        nested.offset = ret.totalDynamicSize;
        nested.count = Cal::Utils::countNullterminated(header_include_names[i]);
        nested.size = nested.count * sizeof(char);
        ret.totalDynamicSize += alignUpPow2<8>(nested.size);
        ret.header_include_names.nested.push_back(nested);
    }

    return ret;
}

size_t ClCompileProgramRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, dynMem) + dynMemSize;
     return size;
}

size_t ClCompileProgramRpcM::Captures::getCaptureDynMemSize() const {
     return dynMemSize;
}

ClLinkProgramRpcM::Captures::DynamicTraits ClLinkProgramRpcM::Captures::DynamicTraits::calculate(cl_context context, cl_uint num_devices, const cl_device_id* device_list, const char* options, cl_uint num_input_programs, const cl_program* input_programs, void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data), void* user_data, cl_int* errcode_ret) {
    DynamicTraits ret = {};
    ret.device_list.count = num_devices;
    ret.device_list.size = ret.device_list.count * sizeof(cl_device_id);

    ret.input_programs.offset = alignUpPow2<8>(ret.device_list.offset + ret.device_list.size);
    ret.input_programs.count = num_input_programs;
    ret.input_programs.size = ret.input_programs.count * sizeof(cl_program);

    ret.options.offset = alignUpPow2<8>(ret.input_programs.offset + ret.input_programs.size);
    ret.options.count = Cal::Utils::countNullterminated(options);
    ret.options.size = ret.options.count * sizeof(char);
    ret.totalDynamicSize = alignUpPow2<8>(ret.options.offset + ret.options.size);


    return ret;
}

size_t ClLinkProgramRpcM::Captures::getCaptureTotalSize() const {
     const auto lastMemberOffset = offsetOptions;
     const auto lastMemberArraySize = this->countOptions * sizeof(char);

     auto size = offsetof(Captures, dynMem) + Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

size_t ClLinkProgramRpcM::Captures::getCaptureDynMemSize() const {
     const auto lastMemberOffset = offsetOptions;
     const auto lastMemberArraySize = this->countOptions * sizeof(char);

     auto size = Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

ClGetProgramBuildInfoRpcM::Captures::DynamicTraits ClGetProgramBuildInfoRpcM::Captures::DynamicTraits::calculate(cl_program program, cl_device_id device, cl_program_build_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    DynamicTraits ret = {};
    ret.param_value.count = param_value_size;
    ret.param_value.size = ret.param_value.count;
    ret.totalDynamicSize = alignUpPow2<8>(ret.param_value.offset + ret.param_value.size);


    return ret;
}

size_t ClGetProgramBuildInfoRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, param_value) + Cal::Utils::alignUpPow2<8>(this->countParam_value);
     return size;
}

size_t ClGetProgramBuildInfoRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countParam_value);
     return size;
}

ClCreateKernelRpcM::Captures::DynamicTraits ClCreateKernelRpcM::Captures::DynamicTraits::calculate(cl_program program, const char* kernel_name, cl_int* errcode_ret) {
    DynamicTraits ret = {};
    ret.kernel_name.count = Cal::Utils::countNullterminated(kernel_name);
    ret.kernel_name.size = ret.kernel_name.count * sizeof(char);
    ret.totalDynamicSize = alignUpPow2<8>(ret.kernel_name.offset + ret.kernel_name.size);


    return ret;
}

size_t ClCreateKernelRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, kernel_name) + Cal::Utils::alignUpPow2<8>(this->countKernel_name * sizeof(char));
     return size;
}

size_t ClCreateKernelRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countKernel_name * sizeof(char));
     return size;
}

ClCreateKernelsInProgramRpcM::Captures::DynamicTraits ClCreateKernelsInProgramRpcM::Captures::DynamicTraits::calculate(cl_program program, cl_uint num_kernels, cl_kernel* kernels, cl_uint* num_kernels_ret) {
    DynamicTraits ret = {};
    ret.kernels.count = num_kernels;
    ret.kernels.size = ret.kernels.count * sizeof(cl_kernel);
    ret.totalDynamicSize = alignUpPow2<8>(ret.kernels.offset + ret.kernels.size);


    return ret;
}

size_t ClCreateKernelsInProgramRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, kernels) + Cal::Utils::alignUpPow2<8>(this->countKernels * sizeof(cl_kernel));
     return size;
}

size_t ClCreateKernelsInProgramRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countKernels * sizeof(cl_kernel));
     return size;
}

ClGetCommandQueueInfoRpcM::Captures::DynamicTraits ClGetCommandQueueInfoRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_command_queue_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    DynamicTraits ret = {};
    ret.param_value.count = param_value_size;
    ret.param_value.size = ret.param_value.count;
    ret.totalDynamicSize = alignUpPow2<8>(ret.param_value.offset + ret.param_value.size);


    return ret;
}

size_t ClGetCommandQueueInfoRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, param_value) + Cal::Utils::alignUpPow2<8>(this->countParam_value);
     return size;
}

size_t ClGetCommandQueueInfoRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countParam_value);
     return size;
}

ClGetProgramInfoRpcHelperRpcM::Captures::DynamicTraits ClGetProgramInfoRpcHelperRpcM::Captures::DynamicTraits::calculate(cl_program program, cl_program_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    DynamicTraits ret = {};
    ret.param_value.count = param_value_size;
    ret.param_value.size = ret.param_value.count;
    ret.totalDynamicSize = alignUpPow2<8>(ret.param_value.offset + ret.param_value.size);


    return ret;
}

size_t ClGetProgramInfoRpcHelperRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, param_value) + Cal::Utils::alignUpPow2<8>(this->countParam_value);
     return size;
}

size_t ClGetProgramInfoRpcHelperRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countParam_value);
     return size;
}

ClGetProgramInfoGetBinariesRpcHelperRpcM::Captures::DynamicTraits ClGetProgramInfoGetBinariesRpcHelperRpcM::Captures::DynamicTraits::calculate(cl_program program, size_t total_binaries_size, unsigned char* concatenated_binaries, size_t binaries_count, const size_t* binaries_lengths, size_t* param_value_size_ret) {
    DynamicTraits ret = {};
    ret.concatenated_binaries.count = total_binaries_size;
    ret.concatenated_binaries.size = ret.concatenated_binaries.count * sizeof(unsigned char);

    ret.binaries_lengths.offset = alignUpPow2<8>(ret.concatenated_binaries.offset + ret.concatenated_binaries.size);
    ret.binaries_lengths.count = binaries_count;
    ret.binaries_lengths.size = ret.binaries_lengths.count * sizeof(size_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.binaries_lengths.offset + ret.binaries_lengths.size);


    return ret;
}

size_t ClGetProgramInfoGetBinariesRpcHelperRpcM::Captures::getCaptureTotalSize() const {
     const auto lastMemberOffset = offsetBinaries_lengths;
     const auto lastMemberArraySize = this->countBinaries_lengths * sizeof(size_t);

     auto size = offsetof(Captures, dynMem) + Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

size_t ClGetProgramInfoGetBinariesRpcHelperRpcM::Captures::getCaptureDynMemSize() const {
     const auto lastMemberOffset = offsetBinaries_lengths;
     const auto lastMemberArraySize = this->countBinaries_lengths * sizeof(size_t);

     auto size = Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

ClGetMemObjectInfoRpcM::Captures::DynamicTraits ClGetMemObjectInfoRpcM::Captures::DynamicTraits::calculate(cl_mem memobj, cl_mem_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    DynamicTraits ret = {};
    ret.param_value.count = param_value_size;
    ret.param_value.size = ret.param_value.count;
    ret.totalDynamicSize = alignUpPow2<8>(ret.param_value.offset + ret.param_value.size);


    return ret;
}

size_t ClGetMemObjectInfoRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, param_value) + Cal::Utils::alignUpPow2<8>(this->countParam_value);
     return size;
}

size_t ClGetMemObjectInfoRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countParam_value);
     return size;
}

ClGetImageInfoRpcM::Captures::DynamicTraits ClGetImageInfoRpcM::Captures::DynamicTraits::calculate(cl_mem image, cl_image_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    DynamicTraits ret = {};
    ret.param_value.count = param_value_size;
    ret.param_value.size = ret.param_value.count;
    ret.totalDynamicSize = alignUpPow2<8>(ret.param_value.offset + ret.param_value.size);


    return ret;
}

size_t ClGetImageInfoRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, param_value) + Cal::Utils::alignUpPow2<8>(this->countParam_value);
     return size;
}

size_t ClGetImageInfoRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countParam_value);
     return size;
}

ClGetSamplerInfoRpcM::Captures::DynamicTraits ClGetSamplerInfoRpcM::Captures::DynamicTraits::calculate(cl_sampler sampler, cl_sampler_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    DynamicTraits ret = {};
    ret.param_value.count = param_value_size;
    ret.param_value.size = ret.param_value.count;
    ret.totalDynamicSize = alignUpPow2<8>(ret.param_value.offset + ret.param_value.size);


    return ret;
}

size_t ClGetSamplerInfoRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, param_value) + Cal::Utils::alignUpPow2<8>(this->countParam_value);
     return size;
}

size_t ClGetSamplerInfoRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countParam_value);
     return size;
}

ClGetKernelInfoRpcM::Captures::DynamicTraits ClGetKernelInfoRpcM::Captures::DynamicTraits::calculate(cl_kernel kernel, cl_kernel_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    DynamicTraits ret = {};
    ret.param_value.count = param_value_size;
    ret.param_value.size = ret.param_value.count;
    ret.totalDynamicSize = alignUpPow2<8>(ret.param_value.offset + ret.param_value.size);


    return ret;
}

size_t ClGetKernelInfoRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, param_value) + Cal::Utils::alignUpPow2<8>(this->countParam_value);
     return size;
}

size_t ClGetKernelInfoRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countParam_value);
     return size;
}

ClGetKernelWorkGroupInfoRpcM::Captures::DynamicTraits ClGetKernelWorkGroupInfoRpcM::Captures::DynamicTraits::calculate(cl_kernel kernel, cl_device_id device, cl_kernel_work_group_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    DynamicTraits ret = {};
    ret.param_value.count = param_value_size;
    ret.param_value.size = ret.param_value.count;
    ret.totalDynamicSize = alignUpPow2<8>(ret.param_value.offset + ret.param_value.size);


    return ret;
}

size_t ClGetKernelWorkGroupInfoRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, param_value) + Cal::Utils::alignUpPow2<8>(this->countParam_value);
     return size;
}

size_t ClGetKernelWorkGroupInfoRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countParam_value);
     return size;
}

ClGetKernelArgInfoRpcM::Captures::DynamicTraits ClGetKernelArgInfoRpcM::Captures::DynamicTraits::calculate(cl_kernel kernel, cl_uint arg_indx, cl_kernel_arg_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    DynamicTraits ret = {};
    ret.param_value.count = param_value_size;
    ret.param_value.size = ret.param_value.count;
    ret.totalDynamicSize = alignUpPow2<8>(ret.param_value.offset + ret.param_value.size);


    return ret;
}

size_t ClGetKernelArgInfoRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, param_value) + Cal::Utils::alignUpPow2<8>(this->countParam_value);
     return size;
}

size_t ClGetKernelArgInfoRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countParam_value);
     return size;
}

ClGetKernelSubGroupInfoRpcM::Captures::DynamicTraits ClGetKernelSubGroupInfoRpcM::Captures::DynamicTraits::calculate(cl_kernel kernel, cl_device_id device, cl_kernel_sub_group_info param_name, size_t input_value_size, const void* input_value, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    DynamicTraits ret = {};
    ret.input_value.count = input_value_size;
    ret.input_value.size = ret.input_value.count;

    ret.param_value.offset = alignUpPow2<8>(ret.input_value.offset + ret.input_value.size);
    ret.param_value.count = param_value_size;
    ret.param_value.size = ret.param_value.count;
    ret.totalDynamicSize = alignUpPow2<8>(ret.param_value.offset + ret.param_value.size);


    return ret;
}

size_t ClGetKernelSubGroupInfoRpcM::Captures::getCaptureTotalSize() const {
     const auto lastMemberOffset = offsetParam_value;
     const auto lastMemberArraySize = this->countParam_value;

     auto size = offsetof(Captures, dynMem) + Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

size_t ClGetKernelSubGroupInfoRpcM::Captures::getCaptureDynMemSize() const {
     const auto lastMemberOffset = offsetParam_value;
     const auto lastMemberArraySize = this->countParam_value;

     auto size = Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

ClEnqueueNDRangeKernelRpcM::Captures::DynamicTraits ClEnqueueNDRangeKernelRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_kernel kernel, cl_uint work_dim, const size_t* global_work_offset, const size_t* global_work_size, const size_t* local_work_size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.global_work_offset.count = work_dim;
    ret.global_work_offset.size = ret.global_work_offset.count * sizeof(size_t);

    ret.global_work_size.offset = alignUpPow2<8>(ret.global_work_offset.offset + ret.global_work_offset.size);
    ret.global_work_size.count = work_dim;
    ret.global_work_size.size = ret.global_work_size.count * sizeof(size_t);

    ret.local_work_size.offset = alignUpPow2<8>(ret.global_work_size.offset + ret.global_work_size.size);
    ret.local_work_size.count = work_dim;
    ret.local_work_size.size = ret.local_work_size.count * sizeof(size_t);

    ret.event_wait_list.offset = alignUpPow2<8>(ret.local_work_size.offset + ret.local_work_size.size);
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueNDRangeKernelRpcM::Captures::getCaptureTotalSize() const {
     const auto lastMemberOffset = offsetEvent_wait_list;
     const auto lastMemberArraySize = this->countEvent_wait_list * sizeof(cl_event);

     auto size = offsetof(Captures, dynMem) + Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

size_t ClEnqueueNDRangeKernelRpcM::Captures::getCaptureDynMemSize() const {
     const auto lastMemberOffset = offsetEvent_wait_list;
     const auto lastMemberArraySize = this->countEvent_wait_list * sizeof(cl_event);

     auto size = Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

ClEnqueueTaskRpcM::Captures::DynamicTraits ClEnqueueTaskRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_kernel kernel, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueTaskRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_wait_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueTaskRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

ClEnqueueMarkerWithWaitListRpcM::Captures::DynamicTraits ClEnqueueMarkerWithWaitListRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueMarkerWithWaitListRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_wait_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueMarkerWithWaitListRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

ClEnqueueBarrierWithWaitListRpcM::Captures::DynamicTraits ClEnqueueBarrierWithWaitListRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueBarrierWithWaitListRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_wait_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueBarrierWithWaitListRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

ClEnqueueWaitForEventsRpcM::Captures::DynamicTraits ClEnqueueWaitForEventsRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_uint num_events, const cl_event* event_list) {
    DynamicTraits ret = {};
    ret.event_list.count = num_events;
    ret.event_list.size = ret.event_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_list.offset + ret.event_list.size);


    return ret;
}

size_t ClEnqueueWaitForEventsRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueWaitForEventsRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_list * sizeof(cl_event));
     return size;
}

ClEnqueueMigrateMemObjectsRpcM::Captures::DynamicTraits ClEnqueueMigrateMemObjectsRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_uint num_mem_objects, const cl_mem* mem_objects, cl_mem_migration_flags flags, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.mem_objects.count = num_mem_objects;
    ret.mem_objects.size = ret.mem_objects.count * sizeof(cl_mem);

    ret.event_wait_list.offset = alignUpPow2<8>(ret.mem_objects.offset + ret.mem_objects.size);
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueMigrateMemObjectsRpcM::Captures::getCaptureTotalSize() const {
     const auto lastMemberOffset = offsetEvent_wait_list;
     const auto lastMemberArraySize = this->countEvent_wait_list * sizeof(cl_event);

     auto size = offsetof(Captures, dynMem) + Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

size_t ClEnqueueMigrateMemObjectsRpcM::Captures::getCaptureDynMemSize() const {
     const auto lastMemberOffset = offsetEvent_wait_list;
     const auto lastMemberArraySize = this->countEvent_wait_list * sizeof(cl_event);

     auto size = Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

ClCreateBufferRpcM::Captures::DynamicTraits ClCreateBufferRpcM::Captures::DynamicTraits::calculate(cl_context context, cl_mem_flags flags, size_t size, void* host_ptr, cl_int* errcode_ret) {
    DynamicTraits ret = {};
    ret.host_ptr.count = ((nullptr != host_ptr) ? size : 0U);
    ret.host_ptr.size = ret.host_ptr.count;
    ret.totalDynamicSize = alignUpPow2<8>(ret.host_ptr.offset + ret.host_ptr.size);


    return ret;
}

size_t ClCreateBufferRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, host_ptr) + Cal::Utils::alignUpPow2<8>(this->countHost_ptr);
     return size;
}

size_t ClCreateBufferRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countHost_ptr);
     return size;
}

ClCreateSubBufferRpcM::Captures::DynamicTraits ClCreateSubBufferRpcM::Captures::DynamicTraits::calculate(cl_mem buffer, cl_mem_flags flags, cl_buffer_create_type buffer_create_type, const void* buffer_create_info, cl_int* errcode_ret) {
    DynamicTraits ret = {};
    ret.buffer_create_info.count = Cal::Icd::Ocl::getSubBufferCreateInfoSize(buffer_create_type);
    ret.buffer_create_info.size = ret.buffer_create_info.count;
    ret.totalDynamicSize = alignUpPow2<8>(ret.buffer_create_info.offset + ret.buffer_create_info.size);


    return ret;
}

size_t ClCreateSubBufferRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, buffer_create_info) + Cal::Utils::alignUpPow2<8>(this->countBuffer_create_info);
     return size;
}

size_t ClCreateSubBufferRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countBuffer_create_info);
     return size;
}

ClCreatePipeRpcM::Captures::DynamicTraits ClCreatePipeRpcM::Captures::DynamicTraits::calculate(cl_context context, cl_mem_flags flags, cl_uint pipe_packet_size, cl_uint pipe_max_packets, const cl_pipe_properties* properties, cl_int* errcode_ret) {
    DynamicTraits ret = {};
    ret.properties.count = Cal::Utils::countNullterminatedKey(properties);
    ret.properties.size = ret.properties.count * sizeof(cl_pipe_properties);
    ret.totalDynamicSize = alignUpPow2<8>(ret.properties.offset + ret.properties.size);


    return ret;
}

size_t ClCreatePipeRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, properties) + Cal::Utils::alignUpPow2<8>(this->countProperties * sizeof(cl_pipe_properties));
     return size;
}

size_t ClCreatePipeRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countProperties * sizeof(cl_pipe_properties));
     return size;
}

ClGetPipeInfoRpcM::Captures::DynamicTraits ClGetPipeInfoRpcM::Captures::DynamicTraits::calculate(cl_mem pipe, cl_pipe_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    DynamicTraits ret = {};
    ret.param_value.count = param_value_size;
    ret.param_value.size = ret.param_value.count;
    ret.totalDynamicSize = alignUpPow2<8>(ret.param_value.offset + ret.param_value.size);


    return ret;
}

size_t ClGetPipeInfoRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, param_value) + Cal::Utils::alignUpPow2<8>(this->countParam_value);
     return size;
}

size_t ClGetPipeInfoRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countParam_value);
     return size;
}

ClCreateImageRpcM::Captures::DynamicTraits ClCreateImageRpcM::Captures::DynamicTraits::calculate(cl_context context, cl_mem_flags flags, const cl_image_format* image_format, const cl_image_desc* image_desc, void* host_ptr, cl_int* errcode_ret) {
    DynamicTraits ret = {};
    ret.host_ptr.count = Cal::Icd::Ocl::getImageHostMemorySize(image_format, image_desc, host_ptr);
    ret.host_ptr.size = ret.host_ptr.count;
    ret.totalDynamicSize = alignUpPow2<8>(ret.host_ptr.offset + ret.host_ptr.size);


    return ret;
}

size_t ClCreateImageRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, host_ptr) + Cal::Utils::alignUpPow2<8>(this->countHost_ptr);
     return size;
}

size_t ClCreateImageRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countHost_ptr);
     return size;
}

ClCreateImage2DRpcM::Captures::DynamicTraits ClCreateImage2DRpcM::Captures::DynamicTraits::calculate(cl_context context, cl_mem_flags flags, const cl_image_format* image_format, size_t image_width, size_t image_height, size_t image_row_pitch, void* host_ptr, cl_int* errcode_ret) {
    DynamicTraits ret = {};
    ret.host_ptr.count = Cal::Icd::Ocl::getImageHostMemorySize(CL_MEM_OBJECT_IMAGE2D, image_format, image_width, image_height, 0, image_row_pitch, 0, 0, host_ptr);
    ret.host_ptr.size = ret.host_ptr.count;
    ret.totalDynamicSize = alignUpPow2<8>(ret.host_ptr.offset + ret.host_ptr.size);


    return ret;
}

size_t ClCreateImage2DRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, host_ptr) + Cal::Utils::alignUpPow2<8>(this->countHost_ptr);
     return size;
}

size_t ClCreateImage2DRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countHost_ptr);
     return size;
}

ClCreateImage3DRpcM::Captures::DynamicTraits ClCreateImage3DRpcM::Captures::DynamicTraits::calculate(cl_context context, cl_mem_flags flags, const cl_image_format* image_format, size_t image_width, size_t image_height, size_t image_depth, size_t image_row_pitch, size_t image_slice_pitch, void* host_ptr, cl_int* errcode_ret) {
    DynamicTraits ret = {};
    ret.host_ptr.count = Cal::Icd::Ocl::getImageHostMemorySize(CL_MEM_OBJECT_IMAGE2D, image_format, image_width, image_height, image_depth, image_row_pitch, image_slice_pitch, 0, host_ptr);
    ret.host_ptr.size = ret.host_ptr.count;
    ret.totalDynamicSize = alignUpPow2<8>(ret.host_ptr.offset + ret.host_ptr.size);


    return ret;
}

size_t ClCreateImage3DRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, host_ptr) + Cal::Utils::alignUpPow2<8>(this->countHost_ptr);
     return size;
}

size_t ClCreateImage3DRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countHost_ptr);
     return size;
}

ClCreateSamplerWithPropertiesRpcM::Captures::DynamicTraits ClCreateSamplerWithPropertiesRpcM::Captures::DynamicTraits::calculate(cl_context context, const cl_sampler_properties* properties, cl_int* errcode_ret) {
    DynamicTraits ret = {};
    ret.properties.count = Cal::Utils::countNullterminatedKey(properties);
    ret.properties.size = ret.properties.count * sizeof(cl_sampler_properties);
    ret.totalDynamicSize = alignUpPow2<8>(ret.properties.offset + ret.properties.size);


    return ret;
}

size_t ClCreateSamplerWithPropertiesRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, properties) + Cal::Utils::alignUpPow2<8>(this->countProperties * sizeof(cl_sampler_properties));
     return size;
}

size_t ClCreateSamplerWithPropertiesRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countProperties * sizeof(cl_sampler_properties));
     return size;
}

ClCreateImageWithPropertiesRpcM::Captures::DynamicTraits ClCreateImageWithPropertiesRpcM::Captures::DynamicTraits::calculate(cl_context context, const cl_mem_properties* properties, cl_mem_flags flags, const cl_image_format* image_format, const cl_image_desc* image_desc, void* host_ptr, cl_int* errcode_ret) {
    DynamicTraits ret = {};
    ret.host_ptr.count = Cal::Icd::Ocl::getImageHostMemorySize(image_format, image_desc, host_ptr);
    ret.host_ptr.size = ret.host_ptr.count;

    ret.properties.offset = alignUpPow2<8>(ret.host_ptr.offset + ret.host_ptr.size);
    ret.properties.count = Cal::Utils::countNullterminatedKey(properties);
    ret.properties.size = ret.properties.count * sizeof(cl_mem_properties);
    ret.totalDynamicSize = alignUpPow2<8>(ret.properties.offset + ret.properties.size);


    return ret;
}

size_t ClCreateImageWithPropertiesRpcM::Captures::getCaptureTotalSize() const {
     const auto lastMemberOffset = offsetProperties;
     const auto lastMemberArraySize = this->countProperties * sizeof(cl_mem_properties);

     auto size = offsetof(Captures, dynMem) + Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

size_t ClCreateImageWithPropertiesRpcM::Captures::getCaptureDynMemSize() const {
     const auto lastMemberOffset = offsetProperties;
     const auto lastMemberArraySize = this->countProperties * sizeof(cl_mem_properties);

     auto size = Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

ClCreateBufferWithPropertiesRpcM::Captures::DynamicTraits ClCreateBufferWithPropertiesRpcM::Captures::DynamicTraits::calculate(cl_context context, const cl_mem_properties* properties, cl_mem_flags flags, size_t size, void* host_ptr, cl_int* errcode_ret) {
    DynamicTraits ret = {};
    ret.host_ptr.count = size;
    ret.host_ptr.size = ret.host_ptr.count;

    ret.properties.offset = alignUpPow2<8>(ret.host_ptr.offset + ret.host_ptr.size);
    ret.properties.count = Cal::Utils::countNullterminatedKey(properties);
    ret.properties.size = ret.properties.count * sizeof(cl_mem_properties);
    ret.totalDynamicSize = alignUpPow2<8>(ret.properties.offset + ret.properties.size);


    return ret;
}

size_t ClCreateBufferWithPropertiesRpcM::Captures::getCaptureTotalSize() const {
     const auto lastMemberOffset = offsetProperties;
     const auto lastMemberArraySize = this->countProperties * sizeof(cl_mem_properties);

     auto size = offsetof(Captures, dynMem) + Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

size_t ClCreateBufferWithPropertiesRpcM::Captures::getCaptureDynMemSize() const {
     const auto lastMemberOffset = offsetProperties;
     const auto lastMemberArraySize = this->countProperties * sizeof(cl_mem_properties);

     auto size = Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

ClGetSupportedImageFormatsRpcM::Captures::DynamicTraits ClGetSupportedImageFormatsRpcM::Captures::DynamicTraits::calculate(cl_context context, cl_mem_flags flags, cl_mem_object_type image_type, cl_uint num_entries, cl_image_format* image_formats, cl_uint* num_image_formats) {
    DynamicTraits ret = {};
    ret.image_formats.count = num_entries;
    ret.image_formats.size = ret.image_formats.count * sizeof(cl_image_format);
    ret.totalDynamicSize = alignUpPow2<8>(ret.image_formats.offset + ret.image_formats.size);


    return ret;
}

size_t ClGetSupportedImageFormatsRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, image_formats) + Cal::Utils::alignUpPow2<8>(this->countImage_formats * sizeof(cl_image_format));
     return size;
}

size_t ClGetSupportedImageFormatsRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countImage_formats * sizeof(cl_image_format));
     return size;
}

ClSetKernelArgRpcM::Captures::DynamicTraits ClSetKernelArgRpcM::Captures::DynamicTraits::calculate(cl_kernel kernel, cl_uint arg_index, size_t arg_size, const void* arg_value) {
    DynamicTraits ret = {};
    ret.arg_value.count = arg_size;
    ret.arg_value.size = ret.arg_value.count;
    ret.totalDynamicSize = alignUpPow2<8>(ret.arg_value.offset + ret.arg_value.size);


    return ret;
}

size_t ClSetKernelArgRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, arg_value) + Cal::Utils::alignUpPow2<8>(this->countArg_value);
     return size;
}

size_t ClSetKernelArgRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countArg_value);
     return size;
}

ClSetProgramSpecializationConstantRpcM::Captures::DynamicTraits ClSetProgramSpecializationConstantRpcM::Captures::DynamicTraits::calculate(cl_program program, cl_uint spec_id, size_t spec_size, const void* spec_value) {
    DynamicTraits ret = {};
    ret.spec_value.count = spec_size;
    ret.spec_value.size = ret.spec_value.count;
    ret.totalDynamicSize = alignUpPow2<8>(ret.spec_value.offset + ret.spec_value.size);


    return ret;
}

size_t ClSetProgramSpecializationConstantRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, spec_value) + Cal::Utils::alignUpPow2<8>(this->countSpec_value);
     return size;
}

size_t ClSetProgramSpecializationConstantRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countSpec_value);
     return size;
}

ClEnqueueWriteBufferRpcM::Captures::DynamicTraits ClEnqueueWriteBufferRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, size_t offset, size_t size, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueWriteBufferRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_wait_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueWriteBufferRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

ClEnqueueWriteBufferRectRpcM::Captures::DynamicTraits ClEnqueueWriteBufferRectRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, const size_t* buffer_offset, const size_t* host_offset, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueWriteBufferRectRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_wait_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueWriteBufferRectRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

ClEnqueueReadBufferRpcM::Captures::DynamicTraits ClEnqueueReadBufferRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, size_t offset, size_t size, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueReadBufferRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_wait_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueReadBufferRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

ClEnqueueReadBufferRectRpcM::Captures::DynamicTraits ClEnqueueReadBufferRectRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, const size_t* buffer_offset, const size_t* host_offset, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueReadBufferRectRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_wait_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueReadBufferRectRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

ClEnqueueCopyBufferRpcM::Captures::DynamicTraits ClEnqueueCopyBufferRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_mem src_buffer, cl_mem dst_buffer, size_t src_offset, size_t dst_offset, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueCopyBufferRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_wait_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueCopyBufferRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

ClEnqueueCopyBufferRectRpcM::Captures::DynamicTraits ClEnqueueCopyBufferRectRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_mem src_buffer, cl_mem dst_buffer, const size_t* src_origin, const size_t* dst_origin, const size_t* region, size_t src_row_pitch, size_t src_slice_pitch, size_t dst_row_pitch, size_t dst_slice_pitch, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueCopyBufferRectRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_wait_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueCopyBufferRectRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

ClEnqueueReadImageRpcM::Captures::DynamicTraits ClEnqueueReadImageRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_mem image, cl_bool blocking_read, const size_t* src_origin, const size_t* region, size_t row_pitch, size_t slice_pitch, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueReadImageRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_wait_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueReadImageRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

ClEnqueueWriteImageRpcM::Captures::DynamicTraits ClEnqueueWriteImageRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_mem image, cl_bool blocking_write, const size_t* origin, const size_t* region, size_t input_row_pitch, size_t input_slice_pitch, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueWriteImageRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_wait_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueWriteImageRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

ClEnqueueCopyImageRpcM::Captures::DynamicTraits ClEnqueueCopyImageRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_mem src_image, cl_mem dst_image, const size_t* src_origin, const size_t* dst_origin, const size_t* region, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueCopyImageRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_wait_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueCopyImageRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

ClEnqueueCopyImageToBufferRpcM::Captures::DynamicTraits ClEnqueueCopyImageToBufferRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_mem src_image, cl_mem dst_buffer, const size_t* src_origin, const size_t* region, size_t dst_offset, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueCopyImageToBufferRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_wait_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueCopyImageToBufferRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

ClEnqueueCopyBufferToImageRpcM::Captures::DynamicTraits ClEnqueueCopyBufferToImageRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_mem src_buffer, cl_mem dst_image, size_t src_offset, const size_t* dst_origin, const size_t* region, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueCopyBufferToImageRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_wait_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueCopyBufferToImageRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

ClEnqueueMapBufferRpcM::Captures::DynamicTraits ClEnqueueMapBufferRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_map, cl_map_flags map_flags, size_t offset, size_t cb, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event, cl_int* errcode_ret) {
    DynamicTraits ret = {};
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueMapBufferRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_wait_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueMapBufferRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

ClEnqueueUnmapMemObjectRpcM::Captures::DynamicTraits ClEnqueueUnmapMemObjectRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_mem memobj, void* mapped_ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueUnmapMemObjectRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_wait_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueUnmapMemObjectRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

ClEnqueueFillBufferRpcM::Captures::DynamicTraits ClEnqueueFillBufferRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_mem memobj, const void* pattern, size_t patternSize, size_t offset, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.pattern.count = patternSize;
    ret.pattern.size = ret.pattern.count;

    ret.event_wait_list.offset = alignUpPow2<8>(ret.pattern.offset + ret.pattern.size);
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueFillBufferRpcM::Captures::getCaptureTotalSize() const {
     const auto lastMemberOffset = offsetEvent_wait_list;
     const auto lastMemberArraySize = this->countEvent_wait_list * sizeof(cl_event);

     auto size = offsetof(Captures, dynMem) + Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

size_t ClEnqueueFillBufferRpcM::Captures::getCaptureDynMemSize() const {
     const auto lastMemberOffset = offsetEvent_wait_list;
     const auto lastMemberArraySize = this->countEvent_wait_list * sizeof(cl_event);

     auto size = Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

ClEnqueueFillImageRpcM::Captures::DynamicTraits ClEnqueueFillImageRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_mem image, const void* fill_color, const size_t* origin, const size_t* region, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueFillImageRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_wait_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueFillImageRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

ClWaitForEventsRpcM::Captures::DynamicTraits ClWaitForEventsRpcM::Captures::DynamicTraits::calculate(cl_uint num_events, const cl_event* event_list) {
    DynamicTraits ret = {};
    ret.event_list.count = num_events;
    ret.event_list.size = ret.event_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_list.offset + ret.event_list.size);


    return ret;
}

size_t ClWaitForEventsRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_list * sizeof(cl_event));
     return size;
}

size_t ClWaitForEventsRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_list * sizeof(cl_event));
     return size;
}

ClGetEventInfoRpcM::Captures::DynamicTraits ClGetEventInfoRpcM::Captures::DynamicTraits::calculate(cl_event event, cl_event_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    DynamicTraits ret = {};
    ret.param_value.count = param_value_size;
    ret.param_value.size = ret.param_value.count;
    ret.totalDynamicSize = alignUpPow2<8>(ret.param_value.offset + ret.param_value.size);


    return ret;
}

size_t ClGetEventInfoRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, param_value) + Cal::Utils::alignUpPow2<8>(this->countParam_value);
     return size;
}

size_t ClGetEventInfoRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countParam_value);
     return size;
}

ClGetEventProfilingInfoRpcM::Captures::DynamicTraits ClGetEventProfilingInfoRpcM::Captures::DynamicTraits::calculate(cl_event event, cl_profiling_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    DynamicTraits ret = {};
    ret.param_value.count = param_value_size;
    ret.param_value.size = ret.param_value.count;
    ret.totalDynamicSize = alignUpPow2<8>(ret.param_value.offset + ret.param_value.size);


    return ret;
}

size_t ClGetEventProfilingInfoRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, param_value) + Cal::Utils::alignUpPow2<8>(this->countParam_value);
     return size;
}

size_t ClGetEventProfilingInfoRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countParam_value);
     return size;
}

ClEnqueueSVMMapRpcM::Captures::DynamicTraits ClEnqueueSVMMapRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_bool blocking_map, cl_map_flags map_flags, void* svm_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueSVMMapRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_wait_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueSVMMapRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

ClEnqueueSVMUnmapRpcM::Captures::DynamicTraits ClEnqueueSVMUnmapRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, void* svm_ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueSVMUnmapRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_wait_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueSVMUnmapRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

ClSetKernelExecInfoRpcM::Captures::DynamicTraits ClSetKernelExecInfoRpcM::Captures::DynamicTraits::calculate(cl_kernel kernel, cl_kernel_exec_info param_name, size_t param_value_size, const void* param_value) {
    DynamicTraits ret = {};
    ret.param_value.count = param_value_size;
    ret.param_value.size = ret.param_value.count;
    ret.totalDynamicSize = alignUpPow2<8>(ret.param_value.offset + ret.param_value.size);


    return ret;
}

size_t ClSetKernelExecInfoRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, param_value) + Cal::Utils::alignUpPow2<8>(this->countParam_value);
     return size;
}

size_t ClSetKernelExecInfoRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countParam_value);
     return size;
}

ClEnqueueSVMMemFillRpcM::Captures::DynamicTraits ClEnqueueSVMMemFillRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, void* svm_ptr, const void* pattern, size_t patternSize, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.pattern.count = patternSize;
    ret.pattern.size = ret.pattern.count;

    ret.event_wait_list.offset = alignUpPow2<8>(ret.pattern.offset + ret.pattern.size);
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueSVMMemFillRpcM::Captures::getCaptureTotalSize() const {
     const auto lastMemberOffset = offsetEvent_wait_list;
     const auto lastMemberArraySize = this->countEvent_wait_list * sizeof(cl_event);

     auto size = offsetof(Captures, dynMem) + Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

size_t ClEnqueueSVMMemFillRpcM::Captures::getCaptureDynMemSize() const {
     const auto lastMemberOffset = offsetEvent_wait_list;
     const auto lastMemberArraySize = this->countEvent_wait_list * sizeof(cl_event);

     auto size = Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

ClEnqueueSVMMigrateMemRpcM::Captures::DynamicTraits ClEnqueueSVMMigrateMemRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_uint num_svm_pointers, const void** svm_pointers, const size_t* sizes, cl_mem_migration_flags flags, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.svm_pointers.count = num_svm_pointers;
    ret.svm_pointers.size = ret.svm_pointers.count * sizeof(const void*);

    ret.sizes.offset = alignUpPow2<8>(ret.svm_pointers.offset + ret.svm_pointers.size);
    ret.sizes.count = num_svm_pointers;
    ret.sizes.size = ret.sizes.count * sizeof(size_t);

    ret.event_wait_list.offset = alignUpPow2<8>(ret.sizes.offset + ret.sizes.size);
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueSVMMigrateMemRpcM::Captures::getCaptureTotalSize() const {
     const auto lastMemberOffset = offsetEvent_wait_list;
     const auto lastMemberArraySize = this->countEvent_wait_list * sizeof(cl_event);

     auto size = offsetof(Captures, dynMem) + Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

size_t ClEnqueueSVMMigrateMemRpcM::Captures::getCaptureDynMemSize() const {
     const auto lastMemberOffset = offsetEvent_wait_list;
     const auto lastMemberArraySize = this->countEvent_wait_list * sizeof(cl_event);

     auto size = Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

ClEnqueueSVMMemcpyRpcM::Captures::DynamicTraits ClEnqueueSVMMemcpyRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_bool blocking, void* dst_ptr, const void* src_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueSVMMemcpyRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_wait_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueSVMMemcpyRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

ClCreateSubDevicesEXTRpcM::Captures::DynamicTraits ClCreateSubDevicesEXTRpcM::Captures::DynamicTraits::calculate(cl_device_id in_device, const cl_device_partition_property_ext* properties, cl_uint num_entries, cl_device_id* out_devices, cl_uint* num_devices) {
    DynamicTraits ret = {};
    ret.out_devices.count = num_entries;
    ret.out_devices.size = ret.out_devices.count * sizeof(cl_device_id);

    ret.properties.offset = alignUpPow2<8>(ret.out_devices.offset + ret.out_devices.size);
    ret.properties.count = Cal::Utils::countNullterminatedKey(properties);
    ret.properties.size = ret.properties.count * sizeof(cl_device_partition_property_ext);
    ret.totalDynamicSize = alignUpPow2<8>(ret.properties.offset + ret.properties.size);


    return ret;
}

size_t ClCreateSubDevicesEXTRpcM::Captures::getCaptureTotalSize() const {
     const auto lastMemberOffset = offsetProperties;
     const auto lastMemberArraySize = this->countProperties * sizeof(cl_device_partition_property_ext);

     auto size = offsetof(Captures, dynMem) + Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

size_t ClCreateSubDevicesEXTRpcM::Captures::getCaptureDynMemSize() const {
     const auto lastMemberOffset = offsetProperties;
     const auto lastMemberArraySize = this->countProperties * sizeof(cl_device_partition_property_ext);

     auto size = Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

ClGetKernelSubGroupInfoKHRRpcM::Captures::DynamicTraits ClGetKernelSubGroupInfoKHRRpcM::Captures::DynamicTraits::calculate(cl_kernel kernel, cl_device_id device, cl_kernel_sub_group_info param_name, size_t input_value_size, const void* input_value, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    DynamicTraits ret = {};
    ret.input_value.count = input_value_size;
    ret.input_value.size = ret.input_value.count;

    ret.param_value.offset = alignUpPow2<8>(ret.input_value.offset + ret.input_value.size);
    ret.param_value.count = param_value_size;
    ret.param_value.size = ret.param_value.count;
    ret.totalDynamicSize = alignUpPow2<8>(ret.param_value.offset + ret.param_value.size);


    return ret;
}

size_t ClGetKernelSubGroupInfoKHRRpcM::Captures::getCaptureTotalSize() const {
     const auto lastMemberOffset = offsetParam_value;
     const auto lastMemberArraySize = this->countParam_value;

     auto size = offsetof(Captures, dynMem) + Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

size_t ClGetKernelSubGroupInfoKHRRpcM::Captures::getCaptureDynMemSize() const {
     const auto lastMemberOffset = offsetParam_value;
     const auto lastMemberArraySize = this->countParam_value;

     auto size = Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

ClGetKernelSuggestedLocalWorkSizeKHRRpcM::Captures::DynamicTraits ClGetKernelSuggestedLocalWorkSizeKHRRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_kernel kernel, cl_uint work_dim, const size_t* global_work_offset, const size_t* global_work_size, size_t * suggested_local_work_size) {
    DynamicTraits ret = {};
    ret.global_work_offset.count = work_dim;
    ret.global_work_offset.size = ret.global_work_offset.count * sizeof(size_t);

    ret.global_work_size.offset = alignUpPow2<8>(ret.global_work_offset.offset + ret.global_work_offset.size);
    ret.global_work_size.count = work_dim;
    ret.global_work_size.size = ret.global_work_size.count * sizeof(size_t);

    ret.suggested_local_work_size.offset = alignUpPow2<8>(ret.global_work_size.offset + ret.global_work_size.size);
    ret.suggested_local_work_size.count = work_dim;
    ret.suggested_local_work_size.size = ret.suggested_local_work_size.count * sizeof(size_t);
    ret.totalDynamicSize = alignUpPow2<8>(ret.suggested_local_work_size.offset + ret.suggested_local_work_size.size);


    return ret;
}

size_t ClGetKernelSuggestedLocalWorkSizeKHRRpcM::Captures::getCaptureTotalSize() const {
     const auto lastMemberOffset = offsetSuggested_local_work_size;
     const auto lastMemberArraySize = this->countSuggested_local_work_size * sizeof(size_t);

     auto size = offsetof(Captures, dynMem) + Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

size_t ClGetKernelSuggestedLocalWorkSizeKHRRpcM::Captures::getCaptureDynMemSize() const {
     const auto lastMemberOffset = offsetSuggested_local_work_size;
     const auto lastMemberArraySize = this->countSuggested_local_work_size * sizeof(size_t);

     auto size = Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

ClCreateCommandQueueWithPropertiesKHRRpcM::Captures::DynamicTraits ClCreateCommandQueueWithPropertiesKHRRpcM::Captures::DynamicTraits::calculate(cl_context context, cl_device_id device, const cl_queue_properties* properties, cl_int* errcode_ret) {
    DynamicTraits ret = {};
    ret.properties.count = Cal::Utils::countNullterminatedKey(properties);
    ret.properties.size = ret.properties.count * sizeof(cl_queue_properties);
    ret.totalDynamicSize = alignUpPow2<8>(ret.properties.offset + ret.properties.size);


    return ret;
}

size_t ClCreateCommandQueueWithPropertiesKHRRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, properties) + Cal::Utils::alignUpPow2<8>(this->countProperties * sizeof(cl_queue_properties));
     return size;
}

size_t ClCreateCommandQueueWithPropertiesKHRRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countProperties * sizeof(cl_queue_properties));
     return size;
}

ClEnqueueMemFillINTELRpcM::Captures::DynamicTraits ClEnqueueMemFillINTELRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, void* dstPtr, const void* pattern, size_t patternSize, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.pattern.count = patternSize;
    ret.pattern.size = ret.pattern.count;

    ret.event_wait_list.offset = alignUpPow2<8>(ret.pattern.offset + ret.pattern.size);
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueMemFillINTELRpcM::Captures::getCaptureTotalSize() const {
     const auto lastMemberOffset = offsetEvent_wait_list;
     const auto lastMemberArraySize = this->countEvent_wait_list * sizeof(cl_event);

     auto size = offsetof(Captures, dynMem) + Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

size_t ClEnqueueMemFillINTELRpcM::Captures::getCaptureDynMemSize() const {
     const auto lastMemberOffset = offsetEvent_wait_list;
     const auto lastMemberArraySize = this->countEvent_wait_list * sizeof(cl_event);

     auto size = Cal::Utils::alignUpPow2<8>(lastMemberOffset + lastMemberArraySize);
     return size;
}

ClEnqueueMemcpyINTELRpcM::Captures::DynamicTraits ClEnqueueMemcpyINTELRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_bool blocking, void* dstPtr, const void* srcPtr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueMemcpyINTELRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_wait_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueMemcpyINTELRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

ClGetMemAllocInfoINTELRpcM::Captures::DynamicTraits ClGetMemAllocInfoINTELRpcM::Captures::DynamicTraits::calculate(cl_context context, const void* ptr, cl_mem_info_intel param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    DynamicTraits ret = {};
    ret.param_value.count = param_value_size;
    ret.param_value.size = ret.param_value.count;
    ret.totalDynamicSize = alignUpPow2<8>(ret.param_value.offset + ret.param_value.size);


    return ret;
}

size_t ClGetMemAllocInfoINTELRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, param_value) + Cal::Utils::alignUpPow2<8>(this->countParam_value);
     return size;
}

size_t ClGetMemAllocInfoINTELRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countParam_value);
     return size;
}

ClDeviceMemAllocINTELRpcM::Captures::DynamicTraits ClDeviceMemAllocINTELRpcM::Captures::DynamicTraits::calculate(cl_context context, cl_device_id device, const cl_mem_properties_intel* properties, size_t size, cl_uint alignment, cl_int* errcode_ret) {
    DynamicTraits ret = {};
    ret.properties.count = Cal::Utils::countNullterminatedKey(properties);
    ret.properties.size = ret.properties.count * sizeof(cl_mem_properties_intel);
    ret.totalDynamicSize = alignUpPow2<8>(ret.properties.offset + ret.properties.size);


    return ret;
}

size_t ClDeviceMemAllocINTELRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, properties) + Cal::Utils::alignUpPow2<8>(this->countProperties * sizeof(cl_mem_properties_intel));
     return size;
}

size_t ClDeviceMemAllocINTELRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countProperties * sizeof(cl_mem_properties_intel));
     return size;
}

ClHostMemAllocINTELRpcM::Captures::DynamicTraits ClHostMemAllocINTELRpcM::Captures::DynamicTraits::calculate(cl_context context, const cl_mem_properties_intel* properties, size_t size, cl_uint alignment, cl_int* errcode_ret) {
    DynamicTraits ret = {};
    ret.properties.count = Cal::Utils::countNullterminatedKey(properties);
    ret.properties.size = ret.properties.count * sizeof(cl_mem_properties_intel);
    ret.totalDynamicSize = alignUpPow2<8>(ret.properties.offset + ret.properties.size);


    return ret;
}

size_t ClHostMemAllocINTELRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, properties) + Cal::Utils::alignUpPow2<8>(this->countProperties * sizeof(cl_mem_properties_intel));
     return size;
}

size_t ClHostMemAllocINTELRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countProperties * sizeof(cl_mem_properties_intel));
     return size;
}

ClSharedMemAllocINTELRpcM::Captures::DynamicTraits ClSharedMemAllocINTELRpcM::Captures::DynamicTraits::calculate(cl_context context, cl_device_id device, const cl_mem_properties_intel* properties, size_t size, cl_uint alignment, cl_int* errcode_ret) {
    DynamicTraits ret = {};
    ret.properties.count = Cal::Utils::countNullterminatedKey(properties);
    ret.properties.size = ret.properties.count * sizeof(cl_mem_properties_intel);
    ret.totalDynamicSize = alignUpPow2<8>(ret.properties.offset + ret.properties.size);


    return ret;
}

size_t ClSharedMemAllocINTELRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, properties) + Cal::Utils::alignUpPow2<8>(this->countProperties * sizeof(cl_mem_properties_intel));
     return size;
}

size_t ClSharedMemAllocINTELRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countProperties * sizeof(cl_mem_properties_intel));
     return size;
}

ClEnqueueMigrateMemINTELRpcM::Captures::DynamicTraits ClEnqueueMigrateMemINTELRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, const void* ptr, size_t size, cl_mem_migration_flags flags, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueMigrateMemINTELRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_wait_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueMigrateMemINTELRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

ClGetDeviceGlobalVariablePointerINTELRpcM::Captures::DynamicTraits ClGetDeviceGlobalVariablePointerINTELRpcM::Captures::DynamicTraits::calculate(cl_device_id device, cl_program program, const char* globalVariableName, size_t* globalVariableSizeRet, void** globalVariablePointerRet) {
    DynamicTraits ret = {};
    ret.globalVariableName.count = Cal::Utils::countNullterminated(globalVariableName);
    ret.globalVariableName.size = ret.globalVariableName.count * sizeof(char);
    ret.totalDynamicSize = alignUpPow2<8>(ret.globalVariableName.offset + ret.globalVariableName.size);


    return ret;
}

size_t ClGetDeviceGlobalVariablePointerINTELRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, globalVariableName) + Cal::Utils::alignUpPow2<8>(this->countGlobalVariableName * sizeof(char));
     return size;
}

size_t ClGetDeviceGlobalVariablePointerINTELRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countGlobalVariableName * sizeof(char));
     return size;
}

ClEnqueueWriteBuffer_LocalRpcM::Captures::DynamicTraits ClEnqueueWriteBuffer_LocalRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, size_t offset, size_t size, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueWriteBuffer_LocalRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_wait_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueWriteBuffer_LocalRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

ClEnqueueWriteBuffer_UsmRpcM::Captures::DynamicTraits ClEnqueueWriteBuffer_UsmRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, size_t offset, size_t size, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueWriteBuffer_UsmRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_wait_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueWriteBuffer_UsmRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

ClEnqueueWriteBuffer_SharedRpcM::Captures::DynamicTraits ClEnqueueWriteBuffer_SharedRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, size_t offset, size_t size, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueWriteBuffer_SharedRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_wait_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueWriteBuffer_SharedRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

ClEnqueueWriteBufferRect_LocalRpcM::Captures::DynamicTraits ClEnqueueWriteBufferRect_LocalRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, const size_t* buffer_offset, const size_t* host_offset, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueWriteBufferRect_LocalRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_wait_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueWriteBufferRect_LocalRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

ClEnqueueWriteBufferRect_UsmRpcM::Captures::DynamicTraits ClEnqueueWriteBufferRect_UsmRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, const size_t* buffer_offset, const size_t* host_offset, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueWriteBufferRect_UsmRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_wait_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueWriteBufferRect_UsmRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

ClEnqueueWriteBufferRect_SharedRpcM::Captures::DynamicTraits ClEnqueueWriteBufferRect_SharedRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, const size_t* buffer_offset, const size_t* host_offset, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueWriteBufferRect_SharedRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_wait_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueWriteBufferRect_SharedRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

ClEnqueueReadBuffer_LocalRpcM::Captures::DynamicTraits ClEnqueueReadBuffer_LocalRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, size_t offset, size_t size, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueReadBuffer_LocalRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_wait_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueReadBuffer_LocalRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

ClEnqueueReadBuffer_UsmRpcM::Captures::DynamicTraits ClEnqueueReadBuffer_UsmRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, size_t offset, size_t size, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueReadBuffer_UsmRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_wait_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueReadBuffer_UsmRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

ClEnqueueReadBuffer_SharedRpcM::Captures::DynamicTraits ClEnqueueReadBuffer_SharedRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, size_t offset, size_t size, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueReadBuffer_SharedRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_wait_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueReadBuffer_SharedRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

ClEnqueueReadBufferRect_LocalRpcM::Captures::DynamicTraits ClEnqueueReadBufferRect_LocalRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, const size_t* buffer_offset, const size_t* host_offset, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueReadBufferRect_LocalRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_wait_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueReadBufferRect_LocalRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

ClEnqueueReadBufferRect_UsmRpcM::Captures::DynamicTraits ClEnqueueReadBufferRect_UsmRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, const size_t* buffer_offset, const size_t* host_offset, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueReadBufferRect_UsmRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_wait_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueReadBufferRect_UsmRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

ClEnqueueReadBufferRect_SharedRpcM::Captures::DynamicTraits ClEnqueueReadBufferRect_SharedRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, const size_t* buffer_offset, const size_t* host_offset, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueReadBufferRect_SharedRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_wait_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueReadBufferRect_SharedRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

ClEnqueueSVMMemcpy_Local_LocalRpcM::Captures::DynamicTraits ClEnqueueSVMMemcpy_Local_LocalRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_bool blocking, void* dst_ptr, const void* src_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueSVMMemcpy_Local_LocalRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_wait_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueSVMMemcpy_Local_LocalRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

ClEnqueueSVMMemcpy_Local_UsmRpcM::Captures::DynamicTraits ClEnqueueSVMMemcpy_Local_UsmRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_bool blocking, void* dst_ptr, const void* src_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueSVMMemcpy_Local_UsmRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_wait_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueSVMMemcpy_Local_UsmRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

ClEnqueueSVMMemcpy_Local_SharedRpcM::Captures::DynamicTraits ClEnqueueSVMMemcpy_Local_SharedRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_bool blocking, void* dst_ptr, const void* src_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueSVMMemcpy_Local_SharedRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_wait_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueSVMMemcpy_Local_SharedRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

ClEnqueueSVMMemcpy_Usm_LocalRpcM::Captures::DynamicTraits ClEnqueueSVMMemcpy_Usm_LocalRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_bool blocking, void* dst_ptr, const void* src_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueSVMMemcpy_Usm_LocalRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_wait_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueSVMMemcpy_Usm_LocalRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

ClEnqueueSVMMemcpy_Usm_UsmRpcM::Captures::DynamicTraits ClEnqueueSVMMemcpy_Usm_UsmRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_bool blocking, void* dst_ptr, const void* src_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueSVMMemcpy_Usm_UsmRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_wait_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueSVMMemcpy_Usm_UsmRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

ClEnqueueSVMMemcpy_Usm_SharedRpcM::Captures::DynamicTraits ClEnqueueSVMMemcpy_Usm_SharedRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_bool blocking, void* dst_ptr, const void* src_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueSVMMemcpy_Usm_SharedRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_wait_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueSVMMemcpy_Usm_SharedRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

ClEnqueueSVMMemcpy_Shared_LocalRpcM::Captures::DynamicTraits ClEnqueueSVMMemcpy_Shared_LocalRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_bool blocking, void* dst_ptr, const void* src_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueSVMMemcpy_Shared_LocalRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_wait_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueSVMMemcpy_Shared_LocalRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

ClEnqueueSVMMemcpy_Shared_UsmRpcM::Captures::DynamicTraits ClEnqueueSVMMemcpy_Shared_UsmRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_bool blocking, void* dst_ptr, const void* src_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueSVMMemcpy_Shared_UsmRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_wait_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueSVMMemcpy_Shared_UsmRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

ClEnqueueSVMMemcpy_Shared_SharedRpcM::Captures::DynamicTraits ClEnqueueSVMMemcpy_Shared_SharedRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_bool blocking, void* dst_ptr, const void* src_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueSVMMemcpy_Shared_SharedRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_wait_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueSVMMemcpy_Shared_SharedRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

ClEnqueueMemcpyINTEL_Local_LocalRpcM::Captures::DynamicTraits ClEnqueueMemcpyINTEL_Local_LocalRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_bool blocking, void* dstPtr, const void* srcPtr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueMemcpyINTEL_Local_LocalRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_wait_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueMemcpyINTEL_Local_LocalRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

ClEnqueueMemcpyINTEL_Local_UsmRpcM::Captures::DynamicTraits ClEnqueueMemcpyINTEL_Local_UsmRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_bool blocking, void* dstPtr, const void* srcPtr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueMemcpyINTEL_Local_UsmRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_wait_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueMemcpyINTEL_Local_UsmRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

ClEnqueueMemcpyINTEL_Local_SharedRpcM::Captures::DynamicTraits ClEnqueueMemcpyINTEL_Local_SharedRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_bool blocking, void* dstPtr, const void* srcPtr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueMemcpyINTEL_Local_SharedRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_wait_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueMemcpyINTEL_Local_SharedRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

ClEnqueueMemcpyINTEL_Usm_LocalRpcM::Captures::DynamicTraits ClEnqueueMemcpyINTEL_Usm_LocalRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_bool blocking, void* dstPtr, const void* srcPtr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueMemcpyINTEL_Usm_LocalRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_wait_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueMemcpyINTEL_Usm_LocalRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

ClEnqueueMemcpyINTEL_Usm_UsmRpcM::Captures::DynamicTraits ClEnqueueMemcpyINTEL_Usm_UsmRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_bool blocking, void* dstPtr, const void* srcPtr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueMemcpyINTEL_Usm_UsmRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_wait_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueMemcpyINTEL_Usm_UsmRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

ClEnqueueMemcpyINTEL_Usm_SharedRpcM::Captures::DynamicTraits ClEnqueueMemcpyINTEL_Usm_SharedRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_bool blocking, void* dstPtr, const void* srcPtr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueMemcpyINTEL_Usm_SharedRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_wait_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueMemcpyINTEL_Usm_SharedRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

ClEnqueueMemcpyINTEL_Shared_LocalRpcM::Captures::DynamicTraits ClEnqueueMemcpyINTEL_Shared_LocalRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_bool blocking, void* dstPtr, const void* srcPtr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueMemcpyINTEL_Shared_LocalRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_wait_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueMemcpyINTEL_Shared_LocalRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

ClEnqueueMemcpyINTEL_Shared_UsmRpcM::Captures::DynamicTraits ClEnqueueMemcpyINTEL_Shared_UsmRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_bool blocking, void* dstPtr, const void* srcPtr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueMemcpyINTEL_Shared_UsmRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_wait_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueMemcpyINTEL_Shared_UsmRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

ClEnqueueMemcpyINTEL_Shared_SharedRpcM::Captures::DynamicTraits ClEnqueueMemcpyINTEL_Shared_SharedRpcM::Captures::DynamicTraits::calculate(cl_command_queue command_queue, cl_bool blocking, void* dstPtr, const void* srcPtr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    DynamicTraits ret = {};
    ret.event_wait_list.count = num_events_in_wait_list;
    ret.event_wait_list.size = ret.event_wait_list.count * sizeof(cl_event);
    ret.totalDynamicSize = alignUpPow2<8>(ret.event_wait_list.offset + ret.event_wait_list.size);


    return ret;
}

size_t ClEnqueueMemcpyINTEL_Shared_SharedRpcM::Captures::getCaptureTotalSize() const {
     auto size = offsetof(Captures, event_wait_list) + Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

size_t ClEnqueueMemcpyINTEL_Shared_SharedRpcM::Captures::getCaptureDynMemSize() const {
     auto size = Cal::Utils::alignUpPow2<8>(this->countEvent_wait_list * sizeof(cl_event));
     return size;
}

} // namespace Ocl
} // namespace Rpc
} // namespace Cal
// #### Generated code -- end ####
