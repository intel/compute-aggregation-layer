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

#include "client/icd/icd_page_fault_manager.h"
#include "generated_icd_ocl.h"
#include "generated_rpc_messages_ocl.h"

#include <cstdlib>
#include <type_traits>

using Cal::Utils::enforceNullWithWarning;
using Cal::Utils::ensureNull;
using Cal::Utils::warnIfNotNull;

namespace Cal {
namespace Client {
namespace Icd {
namespace Ocl {
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

cl_int clGetPlatformIDsRpcHelper (cl_uint num_entries, cl_platform_id* platforms, cl_uint* num_platforms) {
    log<Verbosity::bloat>("Establishing RPC for clGetPlatformIDs");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClGetPlatformIDsRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(num_entries, platforms, num_platforms);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, num_entries, platforms, num_platforms);


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    cl_int ret = command->captures.ret;

    return ret;
}
cl_int clIcdGetPlatformIDsKHR (cl_uint num_entries, cl_platform_id* platforms, cl_uint* num_platforms) {
    log<Verbosity::bloat>("Establishing RPC for clIcdGetPlatformIDsKHR");
    return Cal::Client::Icd::Ocl::clGetPlatformIDs(num_entries, platforms, num_platforms);
}
cl_int clGetPlatformInfoRpcHelper (cl_platform_id platform, cl_platform_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    log<Verbosity::bloat>("Establishing RPC for clGetPlatformInfo");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClGetPlatformInfoRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(platform, param_name, param_value_size, param_value, param_value_size_ret);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, platform, param_name, param_value_size, param_value, param_value_size_ret);
    command->args.platform = platform->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    if(param_value)
    {
        globalPlatform->translateRemoteObjectToLocalObjectInParams(param_value, param_name);
    }
    cl_int ret = command->captures.ret;

    return ret;
}
 // clGetExtensionFunctionAddress ignored in generator - based on dont_generate_handler flag
cl_int clGetDeviceIDs (cl_platform_id platform, cl_device_type device_type, cl_uint num_entries, cl_device_id* devices, cl_uint* num_devices) {
    if (nullptr == platform) {
        return CL_INVALID_PLATFORM;
    }

    log<Verbosity::bloat>("Establishing RPC for clGetDeviceIDs");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClGetDeviceIDsRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(platform, device_type, num_entries, devices, num_devices);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, platform, device_type, num_entries, devices, num_devices);
    command->args.platform = platform->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    if(devices)
    {
        auto baseMutable = mutable_element_cast(devices);

        auto numEntries = num_entries;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = globalPlatform->translateNewRemoteObjectToLocalObject(baseMutable[i], platform, false);
        }
    }
    cl_int ret = command->captures.ret;

    return ret;
}
cl_int clGetDeviceInfoRpcHelper (cl_device_id device, cl_device_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    if (isCacheable(param_name) && device->asLocalObject()->cache.find(param_name,param_value,param_value_size_ret)) {
        return CL_SUCCESS;
    }
    log<Verbosity::bloat>("Establishing RPC for clGetDeviceInfo");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClGetDeviceInfoRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(device, param_name, param_value_size, param_value, param_value_size_ret);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, device, param_name, param_value_size, param_value, param_value_size_ret);
    command->args.device = device->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    if(param_value)
    {
        globalPlatform->translateRemoteObjectToLocalObjectInParams(param_value, param_name);
    }
    cl_int ret = command->captures.ret;

    auto captured_size = command->captures.param_value_size_ret;
    channelLock.unlock();
    if (isCacheable(param_name)) {
        device->asLocalObject()->cache.store(param_name, param_value, captured_size);
    }
    return ret;
}
cl_context clCreateContextRpcHelper (const cl_context_properties* properties, cl_uint num_devices, const cl_device_id* devices, void (CL_CALLBACK* pfn_notify)(const char* errinfo, const void* private_info, size_t cb, void* user_data), void* user_data, cl_int* errcode_ret, Cal::Rpc::Ocl::ClCreateContextRpcMImplicitArgs &implArgsForClCreateContextRpcM) {
    if(pfn_notify){Cal::Client::Icd::icdGlobalState.getOclPlatform()->enableCallbacksHandler();}

    log<Verbosity::bloat>("Establishing RPC for clCreateContext");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClCreateContextRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(properties, num_devices, devices, pfn_notify, user_data, errcode_ret);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, properties, num_devices, devices, pfn_notify, user_data, errcode_ret);
    auto standalone_error_info = channel.getStandaloneSpace(256 * sizeof(char));
    command->copyFromCaller(dynMemTraits, implArgsForClCreateContextRpcM);
    command->implicitArgs.error_info = reinterpret_cast<char*>(channel.encodeHeapOffsetFromLocalPtr(Cal::Utils::toAddress(standalone_error_info)));
    if(properties)
    {
        auto base = command->captures.getProperties();
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.properties.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = ((i >= 1) && (CL_CONTEXT_PLATFORM == *(&baseMutable[i]-1))) ? reinterpret_cast<cl_context_properties>(reinterpret_cast<cl_platform_id>(baseMutable[i])->asLocalObject()->asRemoteObject()) : baseMutable[i];
        }
    }
    {
        auto base = command->captures.getDevices();
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.devices.count;

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
    command->copyToCaller(dynMemTraits, implArgsForClCreateContextRpcM);
    cl_context ret = command->captures.ret;

    ret = globalPlatform->translateNewRemoteObjectToLocalObject(ret);
    channelLock.unlock();
    if (ret != nullptr) {
        ret->asLocalObject()->setDevicesList(num_devices, devices);
        if (pfn_notify) {
            ret->asLocalObject()->notifyErrInfoMem = std::move(standalone_error_info);
        }
    } else {
        *errcode_ret = CL_OUT_OF_HOST_MEMORY;
    }
    return ret;
}
cl_context clCreateContextFromTypeRpcHelper (const cl_context_properties* properties, cl_device_type device_type, void (CL_CALLBACK* pfn_notify)(const char* errinfo, const void* private_info, size_t cb, void* user_data), void* user_data, cl_int* errcode_ret, Cal::Rpc::Ocl::ClCreateContextFromTypeRpcMImplicitArgs &implArgsForClCreateContextFromTypeRpcM) {
    if(pfn_notify){Cal::Client::Icd::icdGlobalState.getOclPlatform()->enableCallbacksHandler();}

    log<Verbosity::bloat>("Establishing RPC for clCreateContextFromType");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClCreateContextFromTypeRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(properties, device_type, pfn_notify, user_data, errcode_ret);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, properties, device_type, pfn_notify, user_data, errcode_ret);
    auto standalone_error_info = channel.getStandaloneSpace(256 * sizeof(char));
    command->copyFromCaller(dynMemTraits, implArgsForClCreateContextFromTypeRpcM);
    command->implicitArgs.error_info = reinterpret_cast<char*>(channel.encodeHeapOffsetFromLocalPtr(Cal::Utils::toAddress(standalone_error_info)));
    if(properties)
    {
        auto base = command->captures.properties;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.properties.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = ((i >= 1) && (CL_CONTEXT_PLATFORM == *(&baseMutable[i]-1))) ? reinterpret_cast<cl_context_properties>(reinterpret_cast<cl_platform_id>(baseMutable[i])->asLocalObject()->asRemoteObject()) : baseMutable[i];
        }
    }


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits, implArgsForClCreateContextFromTypeRpcM);
    cl_context ret = command->captures.ret;

    ret = globalPlatform->translateNewRemoteObjectToLocalObject(ret);
    channelLock.unlock();
    if(pfn_notify){ret->asLocalObject()->notifyErrInfoMem = std::move(standalone_error_info);}

    return ret;
}
cl_int clGetContextInfo (cl_context context, cl_context_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    if (isCacheable(param_name) && context->asLocalObject()->cache.find(param_name,param_value,param_value_size_ret)) {
        return CL_SUCCESS;
    }
    log<Verbosity::bloat>("Establishing RPC for clGetContextInfo");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClGetContextInfoRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(context, param_name, param_value_size, param_value, param_value_size_ret);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, context, param_name, param_value_size, param_value, param_value_size_ret);
    command->args.context = context->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    if(param_value)
    {
        auto baseMutable = mutable_element_cast(param_value);

        auto numEntries = param_value_size;

        for(size_t i = 0; i < numEntries; ++i){
            if((param_name == CL_CONTEXT_DEVICES) && ((i%sizeof(cl_device_id)) == 0)) {  globalPlatform->translateRemoteObjectToLocalObject(*reinterpret_cast<cl_device_id*>(&baseMutable[i])); };
        }
        globalPlatform->translateRemoteObjectToLocalObjectInParams(param_value, param_name);
    }
    cl_int ret = command->captures.ret;

    auto captured_size = command->captures.param_value_size_ret;
    channelLock.unlock();
    if (isCacheable(param_name)) {
        context->asLocalObject()->cache.store(param_name, param_value, captured_size);
    }
    return ret;
}
cl_int clSetContextDestructorCallback (cl_context context, void (CL_CALLBACK* pfn_notify)(cl_context context, void* user_data), void* user_data) {
    Cal::Client::Icd::icdGlobalState.getOclPlatform()->enableCallbacksHandler();

    log<Verbosity::bloat>("Establishing RPC for clSetContextDestructorCallback");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClSetContextDestructorCallbackRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(context, pfn_notify, user_data);
    command->args.context = context->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    {
        context->asLocalObject()->inc();
    }
    cl_int ret = command->captures.ret;

    return ret;
}
cl_int clSetMemObjectDestructorCallback (cl_mem memobj, void (CL_CALLBACK* pfn_notify)(cl_mem memobj, void* user_data), void* user_data) {
    Cal::Client::Icd::icdGlobalState.getOclPlatform()->enableCallbacksHandler();

    log<Verbosity::bloat>("Establishing RPC for clSetMemObjectDestructorCallback");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClSetMemObjectDestructorCallbackRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(memobj, pfn_notify, user_data);
    command->args.memobj = memobj->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    {
        memobj->asLocalObject()->inc();
    }
    cl_int ret = command->captures.ret;

    return ret;
}
cl_int clCreateSubDevices (cl_device_id in_device, const cl_device_partition_property* properties, cl_uint num_devices, cl_device_id* out_devices, cl_uint* num_devices_ret) {
    log<Verbosity::bloat>("Establishing RPC for clCreateSubDevices");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClCreateSubDevicesRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(in_device, properties, num_devices, out_devices, num_devices_ret);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, in_device, properties, num_devices, out_devices, num_devices_ret);
    command->copyFromCaller(dynMemTraits);
    command->args.in_device = in_device->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    if(out_devices)
    {
        auto baseMutable = mutable_element_cast(out_devices);

        auto numEntries = num_devices;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = globalPlatform->translateNewRemoteObjectToLocalObject(baseMutable[i], in_device, true);
        }
    }
    cl_int ret = command->captures.ret;

    return ret;
}
cl_command_queue clCreateCommandQueue (cl_context context, cl_device_id device, cl_command_queue_properties  properties, cl_int* errcode_ret) {
    log<Verbosity::bloat>("Establishing RPC for clCreateCommandQueue");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClCreateCommandQueueRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(context, device, properties, errcode_ret);
    command->args.context = context->asLocalObject()->asRemoteObject();
    command->args.device = device->asLocalObject()->asRemoteObject();
    command->args.properties = globalPlatform->translateQueueFlags(properties);


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller();
    cl_command_queue ret = command->captures.ret;

    ret = globalPlatform->translateNewRemoteObjectToLocalObject(ret, context);
    channelLock.unlock();
    ret->asLocalObject()->context = context->asLocalObject();
    return ret;
}
cl_int clSetDefaultDeviceCommandQueue (cl_context context, cl_device_id device, cl_command_queue command_queue) {
    log<Verbosity::bloat>("Establishing RPC for clSetDefaultDeviceCommandQueue");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClSetDefaultDeviceCommandQueueRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(context, device, command_queue);
    command->args.context = context->asLocalObject()->asRemoteObject();
    command->args.device = device->asLocalObject()->asRemoteObject();
    if (command_queue) command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    cl_int ret = command->captures.ret;

    return ret;
}
cl_command_queue clCreateCommandQueueWithProperties (cl_context context, cl_device_id device, const cl_queue_properties* properties, cl_int* errcode_ret) {
    log<Verbosity::bloat>("Establishing RPC for clCreateCommandQueueWithProperties");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClCreateCommandQueueWithPropertiesRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(context, device, properties, errcode_ret);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, context, device, properties, errcode_ret);
    command->copyFromCaller(dynMemTraits);
    command->args.context = context->asLocalObject()->asRemoteObject();
    command->args.device = device->asLocalObject()->asRemoteObject();
    if(properties)
    {
        globalPlatform->translateQueueFlags(mutable_element_cast(command->captures.properties));
    }


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    cl_command_queue ret = command->captures.ret;

    ret = globalPlatform->translateNewRemoteObjectToLocalObject(ret, context);
    channelLock.unlock();
    ret->asLocalObject()->context = context->asLocalObject();
    return ret;
}
cl_program clCreateProgramWithSource (cl_context context, cl_uint count, const char** strings, const size_t* lengths, cl_int* errcode_ret) {
    log<Verbosity::bloat>("Establishing RPC for clCreateProgramWithSource");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClCreateProgramWithSourceRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(context, count, strings, lengths, errcode_ret);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, context, count, strings, lengths, errcode_ret);
    command->copyFromCaller(dynMemTraits);
    command->args.context = context->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    cl_program ret = command->captures.ret;

    ret = globalPlatform->translateNewRemoteObjectToLocalObject(ret, context);
    channelLock.unlock();
    ret->asLocalObject()->context = context->asLocalObject();
    return ret;
}
cl_program clCreateProgramWithIL (cl_context context, const void* il, size_t length, cl_int* errcode_ret) {
    log<Verbosity::bloat>("Establishing RPC for clCreateProgramWithIL");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClCreateProgramWithILRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(context, il, length, errcode_ret);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, context, il, length, errcode_ret);
    command->copyFromCaller(dynMemTraits);
    command->args.context = context->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    cl_program ret = command->captures.ret;

    ret = globalPlatform->translateNewRemoteObjectToLocalObject(ret, context);
    channelLock.unlock();
    ret->asLocalObject()->context = context->asLocalObject();
    return ret;
}
cl_program clCreateProgramWithBinary (cl_context context, cl_uint num_devices, const cl_device_id* device_list, const size_t* lengths, const unsigned char** binaries, cl_int* binary_status, cl_int* errcode_ret) {
    log<Verbosity::bloat>("Establishing RPC for clCreateProgramWithBinary");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClCreateProgramWithBinaryRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(context, num_devices, device_list, lengths, binaries, binary_status, errcode_ret);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, context, num_devices, device_list, lengths, binaries, binary_status, errcode_ret);
    command->copyFromCaller(dynMemTraits);
    command->args.context = context->asLocalObject()->asRemoteObject();
    if(device_list)
    {
        auto base = command->captures.getDevice_list();
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.device_list.count;

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
    cl_program ret = command->captures.ret;

    ret = globalPlatform->translateNewRemoteObjectToLocalObject(ret, context);
    channelLock.unlock();
    ret->asLocalObject()->context = context->asLocalObject();
    return ret;
}
cl_program clCreateProgramWithBuiltInKernels (cl_context context, cl_uint num_devices, const cl_device_id* device_list, const char* kernel_names, cl_int* errcode_ret) {
    log<Verbosity::bloat>("Establishing RPC for clCreateProgramWithBuiltInKernels");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClCreateProgramWithBuiltInKernelsRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(context, num_devices, device_list, kernel_names, errcode_ret);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, context, num_devices, device_list, kernel_names, errcode_ret);
    command->copyFromCaller(dynMemTraits);
    command->args.context = context->asLocalObject()->asRemoteObject();
    if(device_list)
    {
        auto base = command->captures.getDevice_list();
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.device_list.count;

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
    cl_program ret = command->captures.ret;

    ret = globalPlatform->translateNewRemoteObjectToLocalObject(ret, context);
    channelLock.unlock();
    ret->asLocalObject()->context = context->asLocalObject();
    return ret;
}
cl_int clUnloadCompiler () {
    log<Verbosity::info>("Intentionally ignoring clUnloadCompiler");
    return {};
}
cl_int clUnloadPlatformCompiler (cl_platform_id platform) {
    log<Verbosity::info>("Intentionally ignoring clUnloadPlatformCompiler");
    return {};
}
cl_int clBuildProgram (cl_program program, cl_uint num_devices, const cl_device_id* device_list, const char* options, void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data), void* user_data) {
    if(pfn_notify){Cal::Client::Icd::icdGlobalState.getOclPlatform()->enableCallbacksHandler();}

    log<Verbosity::bloat>("Establishing RPC for clBuildProgram");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClBuildProgramRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(program, num_devices, device_list, options, pfn_notify, user_data);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, program, num_devices, device_list, options, pfn_notify, user_data);
    command->copyFromCaller(dynMemTraits);
    command->args.program = program->asLocalObject()->asRemoteObject();
    if(device_list)
    {
        auto base = command->captures.getDevice_list();
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.device_list.count;

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
    cl_int ret = command->captures.ret;

    return ret;
}
cl_int clCompileProgram (cl_program program, cl_uint num_devices, const cl_device_id* device_list, const char* options, cl_uint num_input_headers, const cl_program* input_headers, const char** header_include_names, void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data), void* user_data) {
    if(pfn_notify){Cal::Client::Icd::icdGlobalState.getOclPlatform()->enableCallbacksHandler();}

    log<Verbosity::bloat>("Establishing RPC for clCompileProgram");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClCompileProgramRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(program, num_devices, device_list, options, num_input_headers, input_headers, header_include_names, pfn_notify, user_data);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, program, num_devices, device_list, options, num_input_headers, input_headers, header_include_names, pfn_notify, user_data);
    command->copyFromCaller(dynMemTraits);
    command->args.program = program->asLocalObject()->asRemoteObject();
    if(device_list)
    {
        auto base = command->captures.getDevice_list();
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.device_list.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }
    if(input_headers)
    {
        auto base = command->captures.getInput_headers();
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.input_headers.count;

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
    cl_int ret = command->captures.ret;

    return ret;
}
cl_program clLinkProgram (cl_context context, cl_uint num_devices, const cl_device_id* device_list, const char* options, cl_uint num_input_programs, const cl_program* input_programs, void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data), void* user_data, cl_int* errcode_ret) {
    if(pfn_notify){Cal::Client::Icd::icdGlobalState.getOclPlatform()->enableCallbacksHandler();}

    log<Verbosity::bloat>("Establishing RPC for clLinkProgram");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClLinkProgramRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(context, num_devices, device_list, options, num_input_programs, input_programs, pfn_notify, user_data, errcode_ret);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, context, num_devices, device_list, options, num_input_programs, input_programs, pfn_notify, user_data, errcode_ret);
    command->copyFromCaller(dynMemTraits);
    command->args.context = context->asLocalObject()->asRemoteObject();
    if(device_list)
    {
        auto base = command->captures.getDevice_list();
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.device_list.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }
    if(input_programs)
    {
        auto base = command->captures.getInput_programs();
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.input_programs.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }
    command->args.user_data = user_data ? new UserDataLinkProgram(context, user_data) : nullptr;


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    cl_program ret = command->captures.ret;

    ret = globalPlatform->translateNewRemoteObjectToLocalObject(ret,context);
    return ret;
}
cl_int clGetProgramBuildInfo (cl_program program, cl_device_id device, cl_program_build_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    log<Verbosity::bloat>("Establishing RPC for clGetProgramBuildInfo");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClGetProgramBuildInfoRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(program, device, param_name, param_value_size, param_value, param_value_size_ret);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, program, device, param_name, param_value_size, param_value, param_value_size_ret);
    command->args.program = program->asLocalObject()->asRemoteObject();
    command->args.device = device->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    cl_int ret = command->captures.ret;

    return ret;
}
cl_int clSetProgramReleaseCallback (cl_program program, void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data), void* user_data) {
    Cal::Client::Icd::icdGlobalState.getOclPlatform()->enableCallbacksHandler();

    log<Verbosity::bloat>("Establishing RPC for clSetProgramReleaseCallback");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClSetProgramReleaseCallbackRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(program, pfn_notify, user_data);
    command->args.program = program->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    cl_int ret = command->captures.ret;

    return ret;
}
cl_kernel clCreateKernelRpcHelper (cl_program program, const char* kernel_name, cl_int* errcode_ret) {
    log<Verbosity::bloat>("Establishing RPC for clCreateKernel");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClCreateKernelRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(program, kernel_name, errcode_ret);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, program, kernel_name, errcode_ret);
    command->copyFromCaller(dynMemTraits);
    command->args.program = program->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    cl_kernel ret = command->captures.ret;

    ret = globalPlatform->translateNewRemoteObjectToLocalObject(ret, program);
    return ret;
}
cl_kernel clCloneKernel (cl_kernel source_kernel, cl_int* errcode_ret) {
    log<Verbosity::bloat>("Establishing RPC for clCloneKernel");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClCloneKernelRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(source_kernel, errcode_ret);
    command->args.source_kernel = source_kernel->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller();
    cl_kernel ret = command->captures.ret;

    ret = globalPlatform->translateNewRemoteObjectToLocalObject(ret, source_kernel->asLocalObject());
    return ret;
}
cl_int clCreateKernelsInProgramRpcHelper (cl_program program, cl_uint num_kernels, cl_kernel* kernels, cl_uint* num_kernels_ret) {
    log<Verbosity::bloat>("Establishing RPC for clCreateKernelsInProgram");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClCreateKernelsInProgramRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(program, num_kernels, kernels, num_kernels_ret);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, program, num_kernels, kernels, num_kernels_ret);
    command->args.program = program->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    if(kernels)
    {
        auto baseMutable = mutable_element_cast(kernels);

        auto numEntries = num_kernels;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = globalPlatform->translateNewRemoteObjectToLocalObject(baseMutable[i], program);
        }
    }
    cl_int ret = command->captures.ret;

    return ret;
}
cl_int clGetCommandQueueInfo (cl_command_queue command_queue, cl_command_queue_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    if (isCacheable(param_name) && command_queue->asLocalObject()->cache.find(param_name,param_value,param_value_size_ret)) {
        return CL_SUCCESS;
    }
    log<Verbosity::bloat>("Establishing RPC for clGetCommandQueueInfo");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClGetCommandQueueInfoRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, param_name, param_value_size, param_value, param_value_size_ret);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, param_name, param_value_size, param_value, param_value_size_ret);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    if(param_value)
    {
        globalPlatform->translateRemoteObjectToLocalObjectInParams(param_value, param_name);
    }
    cl_int ret = command->captures.ret;

    auto captured_size = command->captures.param_value_size_ret;
    channelLock.unlock();
    if (isCacheable(param_name)) {
        command_queue->asLocalObject()->cache.store(param_name, param_value, captured_size);
    }
    return ret;
}
 // clGetProgramInfo ignored in generator - based on dont_generate_handler flag
cl_int clGetProgramInfoRpcHelper (cl_program program, cl_program_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    log<Verbosity::bloat>("Establishing RPC for clGetProgramInfoRpcHelper");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClGetProgramInfoRpcHelperRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(program, param_name, param_value_size, param_value, param_value_size_ret);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, program, param_name, param_value_size, param_value, param_value_size_ret);
    command->args.program = program->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    if(param_value)
    {
        auto baseMutable = mutable_element_cast(param_value);

        auto numEntries = param_value_size;

        for(size_t i = 0; i < numEntries; ++i){
            if((param_name == CL_PROGRAM_DEVICES) && ((i % sizeof(cl_device_id)) == 0)) {
                *reinterpret_cast<cl_device_id*>(&baseMutable[i]) = globalPlatform->translateNewRemoteObjectToLocalObject(*reinterpret_cast<cl_device_id*>(&baseMutable[i]), program);
            };
        }
        globalPlatform->translateRemoteObjectToLocalObjectInParams(param_value, param_name);
    }
    cl_int ret = command->captures.ret;

    return ret;
}
cl_int clGetProgramInfoGetBinariesRpcHelper (cl_program program, size_t total_binaries_size, unsigned char* concatenated_binaries, size_t binaries_count, const size_t* binaries_lengths, size_t* param_value_size_ret) {
    log<Verbosity::bloat>("Establishing RPC for clGetProgramInfoGetBinariesRpcHelper");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClGetProgramInfoGetBinariesRpcHelperRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(program, total_binaries_size, concatenated_binaries, binaries_count, binaries_lengths, param_value_size_ret);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, program, total_binaries_size, concatenated_binaries, binaries_count, binaries_lengths, param_value_size_ret);
    command->copyFromCaller(dynMemTraits);
    command->args.program = program->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    cl_int ret = command->captures.ret;

    return ret;
}
cl_int clGetMemObjectInfoRpcHelper (cl_mem memobj, cl_mem_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    log<Verbosity::bloat>("Establishing RPC for clGetMemObjectInfo");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClGetMemObjectInfoRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(memobj, param_name, param_value_size, param_value, param_value_size_ret);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, memobj, param_name, param_value_size, param_value, param_value_size_ret);
    command->args.memobj = memobj->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    if(param_value)
    {
        globalPlatform->translateRemoteObjectToLocalObjectInParams(param_value, param_name);
    }
    cl_int ret = command->captures.ret;

    return ret;
}
cl_int clGetImageInfo (cl_mem image, cl_image_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    log<Verbosity::bloat>("Establishing RPC for clGetImageInfo");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClGetImageInfoRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(image, param_name, param_value_size, param_value, param_value_size_ret);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, image, param_name, param_value_size, param_value, param_value_size_ret);
    command->args.image = image->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    if(param_value)
    {
        globalPlatform->translateRemoteObjectToLocalObjectInParams(param_value, param_name);
    }
    cl_int ret = command->captures.ret;

    return ret;
}
cl_int clGetSamplerInfo (cl_sampler sampler, cl_sampler_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    log<Verbosity::bloat>("Establishing RPC for clGetSamplerInfo");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClGetSamplerInfoRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(sampler, param_name, param_value_size, param_value, param_value_size_ret);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, sampler, param_name, param_value_size, param_value, param_value_size_ret);
    command->args.sampler = sampler->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    if(param_value)
    {
        globalPlatform->translateRemoteObjectToLocalObjectInParams(param_value, param_name);
    }
    cl_int ret = command->captures.ret;

    return ret;
}
cl_int clGetKernelInfo (cl_kernel kernel, cl_kernel_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    if (isCacheable(param_name) && kernel->asLocalObject()->cache.find(param_name,param_value,param_value_size_ret)) {
        return CL_SUCCESS;
    }
    log<Verbosity::bloat>("Establishing RPC for clGetKernelInfo");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClGetKernelInfoRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(kernel, param_name, param_value_size, param_value, param_value_size_ret);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, kernel, param_name, param_value_size, param_value, param_value_size_ret);
    command->args.kernel = kernel->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    if(param_value)
    {
        globalPlatform->translateRemoteObjectToLocalObjectInParams(param_value, param_name);
    }
    cl_int ret = command->captures.ret;

    auto captured_size = command->captures.param_value_size_ret;
    channelLock.unlock();
    if (isCacheable(param_name)) {
        kernel->asLocalObject()->cache.store(param_name, param_value, captured_size);
    }
    return ret;
}
cl_int clGetKernelWorkGroupInfo (cl_kernel kernel, cl_device_id device, cl_kernel_work_group_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    log<Verbosity::bloat>("Establishing RPC for clGetKernelWorkGroupInfo");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClGetKernelWorkGroupInfoRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(kernel, device, param_name, param_value_size, param_value, param_value_size_ret);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, kernel, device, param_name, param_value_size, param_value, param_value_size_ret);
    command->args.kernel = kernel->asLocalObject()->asRemoteObject();
    command->args.device = device->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    cl_int ret = command->captures.ret;

    return ret;
}
cl_int clGetKernelArgInfo (cl_kernel kernel, cl_uint arg_indx, cl_kernel_arg_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    log<Verbosity::bloat>("Establishing RPC for clGetKernelArgInfo");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClGetKernelArgInfoRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(kernel, arg_indx, param_name, param_value_size, param_value, param_value_size_ret);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, kernel, arg_indx, param_name, param_value_size, param_value, param_value_size_ret);
    command->args.kernel = kernel->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    cl_int ret = command->captures.ret;

    return ret;
}
cl_int clGetKernelSubGroupInfo (cl_kernel kernel, cl_device_id device, cl_kernel_sub_group_info param_name, size_t input_value_size, const void* input_value, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    log<Verbosity::bloat>("Establishing RPC for clGetKernelSubGroupInfo");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClGetKernelSubGroupInfoRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(kernel, device, param_name, input_value_size, input_value, param_value_size, param_value, param_value_size_ret);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, kernel, device, param_name, input_value_size, input_value, param_value_size, param_value, param_value_size_ret);
    command->copyFromCaller(dynMemTraits);
    command->args.kernel = kernel->asLocalObject()->asRemoteObject();
    command->args.device = device->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    cl_int ret = command->captures.ret;

    return ret;
}
cl_int clReleaseCommandQueue (cl_command_queue command_queue) {
    command_queue->asLocalObject()->beforeReleaseCallback();
    log<Verbosity::bloat>("Establishing RPC for clReleaseCommandQueue");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClReleaseCommandQueueRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(command_queue);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();

    if(
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         {
           command_queue->asLocalObject()->dec();
         }
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    {
        command_queue->asLocalObject()->dec();
    }
    cl_int ret = command->captures.ret;

    return ret;
}
cl_int clReleaseContext (cl_context context) {
    context->asLocalObject()->beforeReleaseCallback();
    log<Verbosity::bloat>("Establishing RPC for clReleaseContext");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClReleaseContextRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(context);
    command->args.context = context->asLocalObject()->asRemoteObject();

    if(
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         {
           context->asLocalObject()->dec();
         }
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    {
        context->asLocalObject()->dec();
    }
    cl_int ret = command->captures.ret;

    return ret;
}
cl_int clReleaseDevice (cl_device_id device) {
    log<Verbosity::bloat>("Establishing RPC for clReleaseDevice");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClReleaseDeviceRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(device);
    command->args.device = device->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    {
        if(device->asLocalObject()->isSubDevice){device->asLocalObject()->dec();};
    }
    cl_int ret = command->captures.ret;

    return ret;
}
cl_int clReleaseKernel (cl_kernel kernel) {
    log<Verbosity::bloat>("Establishing RPC for clReleaseKernel");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClReleaseKernelRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(kernel);
    command->args.kernel = kernel->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    {
        kernel->asLocalObject()->dec();
    }
    cl_int ret = command->captures.ret;

    return ret;
}
cl_int clReleaseSampler (cl_sampler sampler) {
    log<Verbosity::bloat>("Establishing RPC for clReleaseSampler");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClReleaseSamplerRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(sampler);
    command->args.sampler = sampler->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    {
        sampler->asLocalObject()->dec();
    }
    cl_int ret = command->captures.ret;

    return ret;
}
cl_int clReleaseProgram (cl_program program) {
    if (program->asLocalObject()->context) {
        program->asLocalObject()->context->asLocalObject()->beforeReleaseCallback();
    }
    log<Verbosity::bloat>("Establishing RPC for clReleaseProgram");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClReleaseProgramRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(program);
    command->args.program = program->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    {
        const auto prevRefCount = program->asLocalObject()->dec();
        if (prevRefCount == 1u) {
            globalPlatform->removeGlobalPointers(program);
        };
    }
    cl_int ret = command->captures.ret;

    return ret;
}
cl_int clReleaseMemObject (cl_mem memobj) {
    invalidateKernelArgCache();
    if(memobj->asLocalObject()->getContext() && memobj->asLocalObject()->getContext()->tryRecycleClBuffer(memobj)){ return CL_SUCCESS; }
    log<Verbosity::bloat>("Establishing RPC for clReleaseMemObject");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClReleaseMemObjectRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(memobj);
    command->args.memobj = memobj->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    memobj->asLocalObject()->dec();
    return ret;
}
cl_int clReleaseEvent (cl_event event) {
    log<Verbosity::bloat>("Establishing RPC for clReleaseEvent");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClReleaseEventRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(event);
    command->args.event = event->asLocalObject()->asRemoteObject();

    if(
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         {
           event->asLocalObject()->dec();
         }
         return static_cast<CommandT::ReturnValueT>(0);
    }else{
      if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
      }

      if(false == channel.callSynchronous(command)){
        return command->returnValue();
      }
    }
    {
        event->asLocalObject()->dec();
    }
    cl_int ret = command->captures.ret;

    return ret;
}
cl_int clRetainCommandQueue (cl_command_queue command_queue) {
    log<Verbosity::bloat>("Establishing RPC for clRetainCommandQueue");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClRetainCommandQueueRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(command_queue);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    {
        command_queue->asLocalObject()->inc();
    }
    cl_int ret = command->captures.ret;

    return ret;
}
cl_int clRetainContext (cl_context context) {
    log<Verbosity::bloat>("Establishing RPC for clRetainContext");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClRetainContextRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(context);
    command->args.context = context->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    {
        context->asLocalObject()->inc();
    }
    cl_int ret = command->captures.ret;

    return ret;
}
cl_int clRetainDevice (cl_device_id device) {
    log<Verbosity::bloat>("Establishing RPC for clRetainDevice");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClRetainDeviceRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(device);
    command->args.device = device->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    {
        device->asLocalObject()->inc();
    }
    cl_int ret = command->captures.ret;

    return ret;
}
cl_int clRetainProgram (cl_program program) {
    log<Verbosity::bloat>("Establishing RPC for clRetainProgram");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClRetainProgramRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(program);
    command->args.program = program->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    {
        program->asLocalObject()->inc();
    }
    cl_int ret = command->captures.ret;

    return ret;
}
cl_int clRetainMemObject (cl_mem memobj) {
    log<Verbosity::bloat>("Establishing RPC for clRetainMemObject");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClRetainMemObjectRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(memobj);
    command->args.memobj = memobj->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    {
        memobj->asLocalObject()->inc();
    }
    cl_int ret = command->captures.ret;

    return ret;
}
cl_int clRetainSampler (cl_sampler sampler) {
    log<Verbosity::bloat>("Establishing RPC for clRetainSampler");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClRetainSamplerRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(sampler);
    command->args.sampler = sampler->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    {
        sampler->asLocalObject()->inc();
    }
    cl_int ret = command->captures.ret;

    return ret;
}
cl_int clRetainKernel (cl_kernel kernel) {
    log<Verbosity::bloat>("Establishing RPC for clRetainKernel");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClRetainKernelRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(kernel);
    command->args.kernel = kernel->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    {
        kernel->asLocalObject()->inc();
    }
    cl_int ret = command->captures.ret;

    return ret;
}
cl_int clRetainEvent (cl_event event) {
    log<Verbosity::bloat>("Establishing RPC for clRetainEvent");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClRetainEventRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(event);
    command->args.event = event->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    {
        event->asLocalObject()->inc();
    }
    cl_int ret = command->captures.ret;

    return ret;
}
cl_int clFlush (cl_command_queue command_queue) {
    log<Verbosity::bloat>("Establishing RPC for clFlush");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClFlushRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(command_queue);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();

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
    cl_int ret = command->captures.ret;

    return ret;
}
cl_int clFinish (cl_command_queue command_queue) {
    if(command_queue->asLocalObject()->isSynchronized()){ return CL_SUCCESS; }

    log<Verbosity::bloat>("Establishing RPC for clFinish");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClFinishRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(command_queue);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->synchronizeNow(true);
    return ret;
}
cl_int clEnqueueNDRangeKernel (cl_command_queue command_queue, cl_kernel kernel, cl_uint work_dim, const size_t* global_work_offset, const size_t* global_work_size, const size_t* local_work_size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    kernel->asLocalObject()->moveArgsToGpu();

    log<Verbosity::bloat>("Establishing RPC for clEnqueueNDRangeKernel");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueNDRangeKernelRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, kernel, work_dim, global_work_offset, global_work_size, local_work_size, num_events_in_wait_list, event_wait_list, event);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, kernel, work_dim, global_work_offset, global_work_size, local_work_size, num_events_in_wait_list, event_wait_list, event);
    command->copyFromCaller(dynMemTraits);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    command->args.kernel = kernel->asLocalObject()->asRemoteObject();
    if(event_wait_list)
    {
        auto base = command->captures.getEvent_wait_list();
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !command->args.event &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         command_queue->asLocalObject()->enqueue();
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
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue);
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->enqueue();
    return ret;
}
cl_int clEnqueueTask (cl_command_queue command_queue, cl_kernel kernel, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    log<Verbosity::bloat>("Establishing RPC for clEnqueueTask");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueTaskRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, kernel, num_events_in_wait_list, event_wait_list, event);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, kernel, num_events_in_wait_list, event_wait_list, event);
    command->copyFromCaller(dynMemTraits);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    command->args.kernel = kernel->asLocalObject()->asRemoteObject();
    if(event_wait_list)
    {
        auto base = command->captures.event_wait_list;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

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
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue);
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->enqueue();
    return ret;
}
cl_int clEnqueueMarkerWithWaitList (cl_command_queue command_queue, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    log<Verbosity::bloat>("Establishing RPC for clEnqueueMarkerWithWaitList");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueMarkerWithWaitListRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, num_events_in_wait_list, event_wait_list, event);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, num_events_in_wait_list, event_wait_list, event);
    command->copyFromCaller(dynMemTraits);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    if(event_wait_list)
    {
        auto base = command->captures.event_wait_list;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

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
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue);
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->enqueue();
    return ret;
}
cl_int clEnqueueMarker (cl_command_queue command_queue, cl_event* event) {
    log<Verbosity::bloat>("Establishing RPC for clEnqueueMarker");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueMarkerRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(command_queue, event);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller();
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue);
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->enqueue();
    return ret;
}
cl_int clEnqueueBarrierWithWaitList (cl_command_queue command_queue, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    log<Verbosity::bloat>("Establishing RPC for clEnqueueBarrierWithWaitList");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueBarrierWithWaitListRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, num_events_in_wait_list, event_wait_list, event);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, num_events_in_wait_list, event_wait_list, event);
    command->copyFromCaller(dynMemTraits);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    if(event_wait_list)
    {
        auto base = command->captures.event_wait_list;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

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
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue);
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->enqueue();
    return ret;
}
cl_int clEnqueueBarrier (cl_command_queue command_queue) {
    log<Verbosity::bloat>("Establishing RPC for clEnqueueBarrier");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueBarrierRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(command_queue);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->enqueue();
    return ret;
}
cl_int clEnqueueWaitForEvents (cl_command_queue command_queue, cl_uint num_events, const cl_event* event_list) {
    log<Verbosity::bloat>("Establishing RPC for clEnqueueWaitForEvents");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueWaitForEventsRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, num_events, event_list);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, num_events, event_list);
    command->copyFromCaller(dynMemTraits);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    if(event_list)
    {
        auto base = command->captures.event_list;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_list.count;

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
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->enqueue();
    return ret;
}
cl_int clEnqueueMigrateMemObjects (cl_command_queue command_queue, cl_uint num_mem_objects, const cl_mem* mem_objects, cl_mem_migration_flags flags, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    log<Verbosity::bloat>("Establishing RPC for clEnqueueMigrateMemObjects");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueMigrateMemObjectsRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, num_mem_objects, mem_objects, flags, num_events_in_wait_list, event_wait_list, event);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, num_mem_objects, mem_objects, flags, num_events_in_wait_list, event_wait_list, event);
    command->copyFromCaller(dynMemTraits);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    if(mem_objects)
    {
        auto base = command->captures.getMem_objects();
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.mem_objects.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }
    if(event_wait_list)
    {
        auto base = command->captures.getEvent_wait_list();
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

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
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue);
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->enqueue();
    return ret;
}
 // clGetExtensionFunctionAddressForPlatform ignored in generator - based on dont_generate_handler flag
 // clCreateBuffer ignored in generator - based on dont_generate_handler flag
cl_mem clCreateBufferRpcHelperUseHostPtrZeroCopyMallocShmem (cl_context context, cl_mem_flags flags, size_t size, void* host_ptr, cl_int* errcode_ret) {
    log<Verbosity::bloat>("Establishing RPC for clCreateBufferRpcHelperUseHostPtrZeroCopyMallocShmem");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClCreateBufferRpcHelperUseHostPtrZeroCopyMallocShmemRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(context, flags, size, host_ptr, errcode_ret);
    command->args.context = context->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller();
    cl_mem ret = command->captures.ret;

    ret = globalPlatform->translateNewRemoteObjectToLocalObject(ret, context);
    return ret;
}
cl_mem clCreateBufferRpcHelperNotUseHostPtrZeroCopyMallocShmem (cl_context context, cl_mem_flags flags, size_t size, void* host_ptr, cl_int* errcode_ret) {
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    [[maybe_unused]] auto host_ptr_pointer_type = globalPlatform->getPointerType(host_ptr);
    
    
{
        return clCreateBufferRpcHelperNotUseHostPtrZeroCopyMallocShmem_Usm(context, flags, size, host_ptr, errcode_ret);
    }
}
cl_mem clCreateSubBufferRpcHelper (cl_mem buffer, cl_mem_flags flags, cl_buffer_create_type buffer_create_type, const void* buffer_create_info, cl_int* errcode_ret) {
    log<Verbosity::bloat>("Establishing RPC for clCreateSubBuffer");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClCreateSubBufferRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(buffer, flags, buffer_create_type, buffer_create_info, errcode_ret);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, buffer, flags, buffer_create_type, buffer_create_info, errcode_ret);
    command->copyFromCaller(dynMemTraits);
    command->args.buffer = buffer->asLocalObject()->asRemoteObject();
    command->args.flags = Cal::Client::Icd::Ocl::translateUseHostPtr(flags);


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    cl_mem ret = command->captures.ret;

    ret = globalPlatform->translateNewRemoteObjectToLocalObject(ret, buffer);
    return ret;
}
cl_mem clCreatePipe (cl_context context, cl_mem_flags flags, cl_uint pipe_packet_size, cl_uint pipe_max_packets, const cl_pipe_properties* properties, cl_int* errcode_ret) {
    log<Verbosity::bloat>("Establishing RPC for clCreatePipe");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClCreatePipeRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(context, flags, pipe_packet_size, pipe_max_packets, properties, errcode_ret);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, context, flags, pipe_packet_size, pipe_max_packets, properties, errcode_ret);
    command->copyFromCaller(dynMemTraits);
    command->args.context = context->asLocalObject()->asRemoteObject();
    command->args.flags = Cal::Client::Icd::Ocl::translateUseHostPtr(flags);


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    cl_mem ret = command->captures.ret;

    ret = globalPlatform->translateNewRemoteObjectToLocalObject(ret, context);
    return ret;
}
cl_int clGetPipeInfo (cl_mem pipe, cl_pipe_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    log<Verbosity::bloat>("Establishing RPC for clGetPipeInfo");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClGetPipeInfoRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(pipe, param_name, param_value_size, param_value, param_value_size_ret);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, pipe, param_name, param_value_size, param_value, param_value_size_ret);
    command->args.pipe = pipe->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    if(param_value)
    {
        globalPlatform->translateRemoteObjectToLocalObjectInParams(param_value, param_name);
    }
    cl_int ret = command->captures.ret;

    return ret;
}
cl_mem clCreateImage (cl_context context, cl_mem_flags flags, const cl_image_format* image_format, const cl_image_desc* image_desc, void* host_ptr, cl_int* errcode_ret) {
    log<Verbosity::bloat>("Establishing RPC for clCreateImage");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClCreateImageRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(context, flags, image_format, image_desc, host_ptr, errcode_ret);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, context, flags, image_format, image_desc, host_ptr, errcode_ret);
    command->copyFromCaller(dynMemTraits);
    command->args.context = context->asLocalObject()->asRemoteObject();
    command->args.flags = Cal::Client::Icd::Ocl::translateUseHostPtr(flags);


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    cl_mem ret = command->captures.ret;

    ret = globalPlatform->translateNewRemoteImageObjectToLocalObject(ret, context, OclImageTraits(image_format, image_desc));
    return ret;
}
cl_mem clCreateImage2D (cl_context context, cl_mem_flags flags, const cl_image_format* image_format, size_t image_width, size_t image_height, size_t image_row_pitch, void* host_ptr, cl_int* errcode_ret) {
    log<Verbosity::bloat>("Establishing RPC for clCreateImage2D");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClCreateImage2DRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(context, flags, image_format, image_width, image_height, image_row_pitch, host_ptr, errcode_ret);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, context, flags, image_format, image_width, image_height, image_row_pitch, host_ptr, errcode_ret);
    command->copyFromCaller(dynMemTraits);
    command->args.context = context->asLocalObject()->asRemoteObject();
    command->args.flags = Cal::Client::Icd::Ocl::translateUseHostPtr(flags);


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    cl_mem ret = command->captures.ret;

    ret = globalPlatform->translateNewRemoteImageObjectToLocalObject(ret, context, OclImageTraits(image_format, image_width, image_height, image_row_pitch));
    return ret;
}
cl_mem clCreateImage3D (cl_context context, cl_mem_flags flags, const cl_image_format* image_format, size_t image_width, size_t image_height, size_t image_depth, size_t image_row_pitch, size_t image_slice_pitch, void* host_ptr, cl_int* errcode_ret) {
    log<Verbosity::bloat>("Establishing RPC for clCreateImage3D");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClCreateImage3DRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(context, flags, image_format, image_width, image_height, image_depth, image_row_pitch, image_slice_pitch, host_ptr, errcode_ret);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, context, flags, image_format, image_width, image_height, image_depth, image_row_pitch, image_slice_pitch, host_ptr, errcode_ret);
    command->copyFromCaller(dynMemTraits);
    command->args.context = context->asLocalObject()->asRemoteObject();
    command->args.flags = Cal::Client::Icd::Ocl::translateUseHostPtr(flags);


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    cl_mem ret = command->captures.ret;

    ret = globalPlatform->translateNewRemoteImageObjectToLocalObject(ret, context, OclImageTraits(image_format, image_width, image_height, image_depth, image_row_pitch, image_slice_pitch));
    return ret;
}
cl_sampler clCreateSampler (cl_context context, cl_bool normalized_coords, cl_addressing_mode addressing_mode, cl_filter_mode filter_mode, cl_int* errcode_ret) {
    log<Verbosity::bloat>("Establishing RPC for clCreateSampler");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClCreateSamplerRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(context, normalized_coords, addressing_mode, filter_mode, errcode_ret);
    command->args.context = context->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller();
    cl_sampler ret = command->captures.ret;

    ret = globalPlatform->translateNewRemoteObjectToLocalObject(ret, context);
    return ret;
}
cl_sampler clCreateSamplerWithProperties (cl_context context, const cl_sampler_properties* properties, cl_int* errcode_ret) {
    log<Verbosity::bloat>("Establishing RPC for clCreateSamplerWithProperties");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClCreateSamplerWithPropertiesRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(context, properties, errcode_ret);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, context, properties, errcode_ret);
    command->copyFromCaller(dynMemTraits);
    command->args.context = context->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    cl_sampler ret = command->captures.ret;

    ret = globalPlatform->translateNewRemoteObjectToLocalObject(ret, context);
    return ret;
}
cl_mem clCreateImageWithProperties (cl_context context, const cl_mem_properties* properties, cl_mem_flags flags, const cl_image_format* image_format, const cl_image_desc* image_desc, void* host_ptr, cl_int* errcode_ret) {
    log<Verbosity::bloat>("Establishing RPC for clCreateImageWithProperties");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClCreateImageWithPropertiesRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(context, properties, flags, image_format, image_desc, host_ptr, errcode_ret);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, context, properties, flags, image_format, image_desc, host_ptr, errcode_ret);
    command->copyFromCaller(dynMemTraits);
    command->args.context = context->asLocalObject()->asRemoteObject();
    command->args.flags = Cal::Client::Icd::Ocl::translateUseHostPtr(flags);


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    cl_mem ret = command->captures.ret;

    ret = globalPlatform->translateNewRemoteObjectToLocalObject(ret, context);
    return ret;
}
cl_mem clCreateBufferWithProperties (cl_context context, const cl_mem_properties* properties, cl_mem_flags flags, size_t size, void* host_ptr, cl_int* errcode_ret) {
    log<Verbosity::bloat>("Establishing RPC for clCreateBufferWithProperties");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClCreateBufferWithPropertiesRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(context, properties, flags, size, host_ptr, errcode_ret);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, context, properties, flags, size, host_ptr, errcode_ret);
    command->copyFromCaller(dynMemTraits);
    command->args.context = context->asLocalObject()->asRemoteObject();
    command->args.flags = Cal::Client::Icd::Ocl::translateUseHostPtr(flags);


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    cl_mem ret = command->captures.ret;

    ret = globalPlatform->translateNewRemoteObjectToLocalObject(ret, context);
    return ret;
}
cl_int clGetSupportedImageFormats (cl_context context, cl_mem_flags flags, cl_mem_object_type image_type, cl_uint num_entries, cl_image_format* image_formats, cl_uint* num_image_formats) {
    log<Verbosity::bloat>("Establishing RPC for clGetSupportedImageFormats");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClGetSupportedImageFormatsRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(context, flags, image_type, num_entries, image_formats, num_image_formats);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, context, flags, image_type, num_entries, image_formats, num_image_formats);
    command->args.context = context->asLocalObject()->asRemoteObject();
    command->args.flags = Cal::Client::Icd::Ocl::translateUseHostPtr(flags);


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    cl_int ret = command->captures.ret;

    return ret;
}
cl_int clSetKernelArgRpcHelper (cl_kernel kernel, cl_uint arg_index, size_t arg_size, const void* arg_value) {
    log<Verbosity::bloat>("Establishing RPC for clSetKernelArg");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClSetKernelArgRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(kernel, arg_index, arg_size, arg_value);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, kernel, arg_index, arg_size, arg_value);
    command->copyFromCaller(dynMemTraits);
    command->args.kernel = kernel->asLocalObject()->asRemoteObject();
    if(arg_value)
    {
        kernel->asLocalObject()->convertClMemArgIfNeeded(arg_index, arg_size, command->captures.arg_value);
    }

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
    cl_int ret = command->captures.ret;

    return ret;
}
cl_int clSetProgramSpecializationConstant (cl_program program, cl_uint spec_id, size_t spec_size, const void* spec_value) {
    log<Verbosity::bloat>("Establishing RPC for clSetProgramSpecializationConstant");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClSetProgramSpecializationConstantRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(program, spec_id, spec_size, spec_value);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, program, spec_id, spec_size, spec_value);
    command->copyFromCaller(dynMemTraits);
    command->args.program = program->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    cl_int ret = command->captures.ret;

    return ret;
}
cl_int clEnqueueWriteBuffer (cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, size_t offset, size_t size, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    [[maybe_unused]] auto ptr_pointer_type = globalPlatform->getPointerType(ptr);
    
    if(ptr_pointer_type == local){
        return clEnqueueWriteBuffer_Local(command_queue, buffer, blocking_write, offset, size, ptr, num_events_in_wait_list, event_wait_list, event);
    }
    else if(ptr_pointer_type == usm){
        return clEnqueueWriteBuffer_Usm(command_queue, buffer, blocking_write, offset, size, ptr, num_events_in_wait_list, event_wait_list, event);
    }
    else{
        return clEnqueueWriteBuffer_Shared(command_queue, buffer, blocking_write, offset, size, ptr, num_events_in_wait_list, event_wait_list, event);
    }
}
cl_int clEnqueueWriteBufferRect (cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, const size_t* buffer_origin, const size_t* host_origin, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    [[maybe_unused]] auto ptr_pointer_type = globalPlatform->getPointerType(ptr);
    
    if(ptr_pointer_type == local){
        return clEnqueueWriteBufferRect_Local(command_queue, buffer, blocking_write, buffer_origin, host_origin, region, buffer_row_pitch, buffer_slice_pitch, host_row_pitch, host_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event);
    }
    else if(ptr_pointer_type == usm){
        return clEnqueueWriteBufferRect_Usm(command_queue, buffer, blocking_write, buffer_origin, host_origin, region, buffer_row_pitch, buffer_slice_pitch, host_row_pitch, host_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event);
    }
    else{
        return clEnqueueWriteBufferRect_Shared(command_queue, buffer, blocking_write, buffer_origin, host_origin, region, buffer_row_pitch, buffer_slice_pitch, host_row_pitch, host_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event);
    }
}
cl_int clEnqueueReadBuffer (cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, size_t offset, size_t size, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    [[maybe_unused]] auto ptr_pointer_type = globalPlatform->getPointerType(ptr);
    
    if(ptr_pointer_type == local){
        return clEnqueueReadBuffer_Local(command_queue, buffer, blocking_read, offset, size, ptr, num_events_in_wait_list, event_wait_list, event);
    }
    else if(ptr_pointer_type == usm){
        return clEnqueueReadBuffer_Usm(command_queue, buffer, blocking_read, offset, size, ptr, num_events_in_wait_list, event_wait_list, event);
    }
    else{
        return clEnqueueReadBuffer_Shared(command_queue, buffer, blocking_read, offset, size, ptr, num_events_in_wait_list, event_wait_list, event);
    }
}
cl_int clEnqueueReadBufferRect (cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, const size_t* buffer_origin, const size_t* host_origin, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    [[maybe_unused]] auto ptr_pointer_type = globalPlatform->getPointerType(ptr);
    
    if(ptr_pointer_type == local){
        return clEnqueueReadBufferRect_Local(command_queue, buffer, blocking_read, buffer_origin, host_origin, region, buffer_row_pitch, buffer_slice_pitch, host_row_pitch, host_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event);
    }
    else if(ptr_pointer_type == usm){
        return clEnqueueReadBufferRect_Usm(command_queue, buffer, blocking_read, buffer_origin, host_origin, region, buffer_row_pitch, buffer_slice_pitch, host_row_pitch, host_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event);
    }
    else{
        return clEnqueueReadBufferRect_Shared(command_queue, buffer, blocking_read, buffer_origin, host_origin, region, buffer_row_pitch, buffer_slice_pitch, host_row_pitch, host_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event);
    }
}
cl_int clEnqueueCopyBuffer (cl_command_queue command_queue, cl_mem src_buffer, cl_mem dst_buffer, size_t src_offset, size_t dst_offset, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    log<Verbosity::bloat>("Establishing RPC for clEnqueueCopyBuffer");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueCopyBufferRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, src_buffer, dst_buffer, src_offset, dst_offset, size, num_events_in_wait_list, event_wait_list, event);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, src_buffer, dst_buffer, src_offset, dst_offset, size, num_events_in_wait_list, event_wait_list, event);
    command->copyFromCaller(dynMemTraits);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    command->args.src_buffer = src_buffer->asLocalObject()->asRemoteObject();
    command->args.dst_buffer = dst_buffer->asLocalObject()->asRemoteObject();
    if(event_wait_list)
    {
        auto base = command->captures.event_wait_list;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

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
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue);
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->enqueue();
    return ret;
}
cl_int clEnqueueCopyBufferRect (cl_command_queue command_queue, cl_mem src_buffer, cl_mem dst_buffer, const size_t* src_origin, const size_t* dst_origin, const size_t* region, size_t src_row_pitch, size_t src_slice_pitch, size_t dst_row_pitch, size_t dst_slice_pitch, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    log<Verbosity::bloat>("Establishing RPC for clEnqueueCopyBufferRect");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueCopyBufferRectRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, src_buffer, dst_buffer, src_origin, dst_origin, region, src_row_pitch, src_slice_pitch, dst_row_pitch, dst_slice_pitch, num_events_in_wait_list, event_wait_list, event);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, src_buffer, dst_buffer, src_origin, dst_origin, region, src_row_pitch, src_slice_pitch, dst_row_pitch, dst_slice_pitch, num_events_in_wait_list, event_wait_list, event);
    command->copyFromCaller(dynMemTraits);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    command->args.src_buffer = src_buffer->asLocalObject()->asRemoteObject();
    command->args.dst_buffer = dst_buffer->asLocalObject()->asRemoteObject();
    if(event_wait_list)
    {
        auto base = command->captures.event_wait_list;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

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
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue);
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->enqueue();
    return ret;
}
cl_int clEnqueueReadImage (cl_command_queue command_queue, cl_mem image, cl_bool blocking_read, const size_t* src_origin, const size_t* region, size_t row_pitch, size_t slice_pitch, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    log<Verbosity::bloat>("Establishing RPC for clEnqueueReadImage");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    void *standalone_ptr{};
    {
        std::unique_ptr<void, std::function<void(void*)>> standalone_ptr_alloc(static_cast<IcdOclCommandQueue *>(command_queue)->context->getStagingAreaManager().allocateStagingArea(Cal::Client::Icd::Ocl::getImageReadWriteHostMemorySize(image, src_origin, region, row_pitch, slice_pitch)), [command_queue](void *ptrToMarkAsUnused){static_cast<IcdOclCommandQueue *>(command_queue)->context->getStagingAreaManager().releaseStagingArea(ptrToMarkAsUnused);});
        standalone_ptr = standalone_ptr_alloc.get();
        command_queue->asLocalObject()->registerTemporaryAllocation(std::move(standalone_ptr_alloc));
    }
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueReadImageRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, image, blocking_read, src_origin, region, row_pitch, slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, image, blocking_read, src_origin, region, row_pitch, slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event);
    command->copyFromCaller(dynMemTraits);
    command->args.ptr = reinterpret_cast<void*>(standalone_ptr);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    command->args.image = image->asLocalObject()->asRemoteObject();
    Cal::Client::Icd::Ocl::warnIfNonBlockingRead(command->args.blocking_read);
    if(event_wait_list)
    {
        auto base = command->captures.event_wait_list;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

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
    memcpy(ptr, standalone_ptr, Cal::Client::Icd::Ocl::getImageReadWriteHostMemorySize(image, src_origin, region, row_pitch, slice_pitch));
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue);
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->enqueue();
    return ret;
}
cl_int clEnqueueWriteImage (cl_command_queue command_queue, cl_mem image, cl_bool blocking_write, const size_t* origin, const size_t* region, size_t input_row_pitch, size_t input_slice_pitch, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    log<Verbosity::bloat>("Establishing RPC for clEnqueueWriteImage");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    void *standalone_ptr{};
    {
        std::unique_ptr<void, std::function<void(void*)>> standalone_ptr_alloc(static_cast<IcdOclCommandQueue *>(command_queue)->context->getStagingAreaManager().allocateStagingArea(Cal::Client::Icd::Ocl::getImageReadWriteHostMemorySize(image, origin, region, input_row_pitch, input_slice_pitch)), [command_queue](void *ptrToMarkAsUnused){static_cast<IcdOclCommandQueue *>(command_queue)->context->getStagingAreaManager().releaseStagingArea(ptrToMarkAsUnused);});
        standalone_ptr = standalone_ptr_alloc.get();
        command_queue->asLocalObject()->registerTemporaryAllocation(std::move(standalone_ptr_alloc));
    }
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueWriteImageRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, image, blocking_write, origin, region, input_row_pitch, input_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, image, blocking_write, origin, region, input_row_pitch, input_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event);
    memcpy(Cal::Utils::toAddress(standalone_ptr), ptr, Cal::Client::Icd::Ocl::getImageReadWriteHostMemorySize(image, origin, region, input_row_pitch, input_slice_pitch));
    command->copyFromCaller(dynMemTraits);
    command->args.ptr = reinterpret_cast<const void*>(standalone_ptr);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    command->args.image = image->asLocalObject()->asRemoteObject();
    if(event_wait_list)
    {
        auto base = command->captures.event_wait_list;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

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
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue);
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->enqueue();
    return ret;
}
cl_int clEnqueueCopyImage (cl_command_queue command_queue, cl_mem src_image, cl_mem dst_image, const size_t* src_origin, const size_t* dst_origin, const size_t* region, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    log<Verbosity::bloat>("Establishing RPC for clEnqueueCopyImage");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueCopyImageRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, src_image, dst_image, src_origin, dst_origin, region, num_events_in_wait_list, event_wait_list, event);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, src_image, dst_image, src_origin, dst_origin, region, num_events_in_wait_list, event_wait_list, event);
    command->copyFromCaller(dynMemTraits);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    command->args.src_image = src_image->asLocalObject()->asRemoteObject();
    command->args.dst_image = dst_image->asLocalObject()->asRemoteObject();
    if(event_wait_list)
    {
        auto base = command->captures.event_wait_list;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

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
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue);
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->enqueue();
    return ret;
}
cl_int clEnqueueCopyImageToBuffer (cl_command_queue command_queue, cl_mem src_image, cl_mem dst_buffer, const size_t* src_origin, const size_t* region, size_t dst_offset, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    log<Verbosity::bloat>("Establishing RPC for clEnqueueCopyImageToBuffer");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueCopyImageToBufferRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, src_image, dst_buffer, src_origin, region, dst_offset, num_events_in_wait_list, event_wait_list, event);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, src_image, dst_buffer, src_origin, region, dst_offset, num_events_in_wait_list, event_wait_list, event);
    command->copyFromCaller(dynMemTraits);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    command->args.src_image = src_image->asLocalObject()->asRemoteObject();
    command->args.dst_buffer = dst_buffer->asLocalObject()->asRemoteObject();
    if(event_wait_list)
    {
        auto base = command->captures.event_wait_list;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

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
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue);
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->enqueue();
    return ret;
}
cl_int clEnqueueCopyBufferToImage (cl_command_queue command_queue, cl_mem src_buffer, cl_mem dst_image, size_t src_offset, const size_t* dst_origin, const size_t* region, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    log<Verbosity::bloat>("Establishing RPC for clEnqueueCopyBufferToImage");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueCopyBufferToImageRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, src_buffer, dst_image, src_offset, dst_origin, region, num_events_in_wait_list, event_wait_list, event);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, src_buffer, dst_image, src_offset, dst_origin, region, num_events_in_wait_list, event_wait_list, event);
    command->copyFromCaller(dynMemTraits);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    command->args.src_buffer = src_buffer->asLocalObject()->asRemoteObject();
    command->args.dst_image = dst_image->asLocalObject()->asRemoteObject();
    if(event_wait_list)
    {
        auto base = command->captures.event_wait_list;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

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
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue);
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->enqueue();
    return ret;
}
void* clEnqueueMapBuffer (cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_map, cl_map_flags map_flags, size_t offset, size_t cb, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event, cl_int* errcode_ret) {
    log<Verbosity::bloat>("Establishing RPC for clEnqueueMapBuffer");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueMapBufferRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, buffer, blocking_map, map_flags, offset, cb, num_events_in_wait_list, event_wait_list, event, errcode_ret);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, buffer, blocking_map, map_flags, offset, cb, num_events_in_wait_list, event_wait_list, event, errcode_ret);
    command->copyFromCaller(dynMemTraits);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    command->args.buffer = buffer->asLocalObject()->asRemoteObject();
    Cal::Client::Icd::Ocl::warnIfNonBlockingRead(command->args.blocking_map, globalPlatform->getPointerType(buffer->asLocalObject()->apiHostPtr));
    if(event_wait_list)
    {
        auto base = command->captures.event_wait_list;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

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
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue);
    }
    void* ret = command->captures.ret;

    ret = globalPlatform->translateMappedPointer(buffer, ret, offset);
    channelLock.unlock();
    command_queue->asLocalObject()->synchronizeNow(command->args.blocking_map);
    command_queue->asLocalObject()->enqueue();

    return ret;
}
cl_int clEnqueueUnmapMemObject (cl_command_queue command_queue, cl_mem memobj, void* mapped_ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    Cal::Client::Icd::icdGlobalState.getPageFaultManager().moveAllocationToGpu(mapped_ptr);
    log<Verbosity::bloat>("Establishing RPC for clEnqueueUnmapMemObject");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueUnmapMemObjectRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, memobj, mapped_ptr, num_events_in_wait_list, event_wait_list, event);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, memobj, mapped_ptr, num_events_in_wait_list, event_wait_list, event);
    command->copyFromCaller(dynMemTraits);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    command->args.memobj = memobj->asLocalObject()->asRemoteObject();
    command->args.mapped_ptr = globalPlatform->translateUnMappedPointer(memobj, mapped_ptr);
    if(event_wait_list)
    {
        auto base = command->captures.event_wait_list;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

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
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue);
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->enqueue();
    return ret;
}
cl_int clEnqueueFillBuffer (cl_command_queue command_queue, cl_mem memobj, const void* pattern, size_t patternSize, size_t offset, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    log<Verbosity::bloat>("Establishing RPC for clEnqueueFillBuffer");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueFillBufferRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, memobj, pattern, patternSize, offset, size, num_events_in_wait_list, event_wait_list, event);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, memobj, pattern, patternSize, offset, size, num_events_in_wait_list, event_wait_list, event);
    command->copyFromCaller(dynMemTraits);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    command->args.memobj = memobj->asLocalObject()->asRemoteObject();
    if(event_wait_list)
    {
        auto base = command->captures.getEvent_wait_list();
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

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
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue);
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->enqueue();
    return ret;
}
cl_int clEnqueueFillImage (cl_command_queue command_queue, cl_mem image, const void* fill_color, const size_t* origin, const size_t* region, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    log<Verbosity::bloat>("Establishing RPC for clEnqueueFillImage");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueFillImageRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, image, fill_color, origin, region, num_events_in_wait_list, event_wait_list, event);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, image, fill_color, origin, region, num_events_in_wait_list, event_wait_list, event);
    command->copyFromCaller(dynMemTraits);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    command->args.image = image->asLocalObject()->asRemoteObject();
    if(event_wait_list)
    {
        auto base = command->captures.event_wait_list;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

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
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue);
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->enqueue();
    return ret;
}
cl_int clWaitForEventsRpcHelper (cl_uint num_events, const cl_event* event_list) {
    log<Verbosity::bloat>("Establishing RPC for clWaitForEvents");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClWaitForEventsRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(num_events, event_list);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, num_events, event_list);
    command->copyFromCaller(dynMemTraits);
    if(event_list)
    {
        auto base = command->captures.event_list;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_list.count;

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
    cl_int ret = command->captures.ret;

    return ret;
}
cl_int clGetEventInfoRpcHelper (cl_event event, cl_event_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    log<Verbosity::bloat>("Establishing RPC for clGetEventInfo");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClGetEventInfoRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(event, param_name, param_value_size, param_value, param_value_size_ret);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, event, param_name, param_value_size, param_value, param_value_size_ret);
    command->args.event = event->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    if(param_value)
    {
        globalPlatform->translateRemoteObjectToLocalObjectInParams(param_value, param_name);
    }
    cl_int ret = command->captures.ret;

    return ret;
}
cl_int clGetEventProfilingInfo (cl_event event, cl_profiling_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    if(Cal::Client::Icd::icdGlobalState.getOclPlatform()->overrideEventProfilingInfo(event, param_name, param_value_size, param_value, param_value_size_ret)) { return CL_SUCCESS; }
    log<Verbosity::bloat>("Establishing RPC for clGetEventProfilingInfo");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClGetEventProfilingInfoRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(event, param_name, param_value_size, param_value, param_value_size_ret);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, event, param_name, param_value_size, param_value, param_value_size_ret);
    command->args.event = event->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    if(param_value)
    {
        globalPlatform->translateRemoteObjectToLocalObjectInParams(param_value, param_name);
    }
    cl_int ret = command->captures.ret;

    return ret;
}
cl_event clCreateUserEvent (cl_context context, cl_int* errcode_ret) {
    log<Verbosity::bloat>("Establishing RPC for clCreateUserEvent");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClCreateUserEventRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(context, errcode_ret);
    command->args.context = context->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller();
    cl_event ret = command->captures.ret;

    ret = globalPlatform->translateNewRemoteObjectToLocalObject(ret, context);
    return ret;
}
cl_int clSetUserEventStatus (cl_event event, cl_int execution_status) {
    log<Verbosity::bloat>("Establishing RPC for clSetUserEventStatus");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClSetUserEventStatusRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(event, execution_status);
    command->args.event = event->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    cl_int ret = command->captures.ret;

    return ret;
}
cl_int clSetEventCallback (cl_event event, cl_int command_exec_callback_type, void (CL_CALLBACK* pfn_notify)(cl_event event, cl_int event_command_status, void *user_data), void* user_data) {
    Cal::Client::Icd::icdGlobalState.getOclPlatform()->enableCallbacksHandler();

    log<Verbosity::bloat>("Establishing RPC for clSetEventCallback");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClSetEventCallbackRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(event, command_exec_callback_type, pfn_notify, user_data);
    command->args.event = event->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    cl_int ret = command->captures.ret;

    return ret;
}
cl_int clGetDeviceAndHostTimer (cl_device_id device, cl_ulong* device_timestamp, cl_ulong* host_timestamp) {
    log<Verbosity::bloat>("Establishing RPC for clGetDeviceAndHostTimer");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClGetDeviceAndHostTimerRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(device, device_timestamp, host_timestamp);
    command->args.device = device->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller();
    cl_int ret = command->captures.ret;

    return ret;
}
cl_int clGetHostTimerRpcHelper (cl_device_id device, cl_ulong* host_timestamp) {
    log<Verbosity::bloat>("Establishing RPC for clGetHostTimer");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClGetHostTimerRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(device, host_timestamp);
    command->args.device = device->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller();
    cl_int ret = command->captures.ret;

    return ret;
}
void* clSVMAllocRpcHelper (cl_context context, cl_svm_mem_flags flags, size_t size, cl_uint alignment, Cal::Rpc::Ocl::ClSVMAllocRpcMImplicitArgs &implArgsForClSVMAllocRpcM) {
    log<Verbosity::bloat>("Establishing RPC for clSVMAlloc");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClSVMAllocRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(context, flags, size, alignment);
    command->args.context = context->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(implArgsForClSVMAllocRpcM);
    void* ret = command->captures.ret;

    return ret;
}
void clSVMFree (cl_context context, void* ptr) {
    invalidateKernelArgCache();
    Cal::Client::Icd::icdGlobalState.getPageFaultManager().unregisterSharedAlloc(ptr);

    log<Verbosity::bloat>("Establishing RPC for clSVMFree");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClSVMFreeRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(context, ptr);
    command->args.context = context->asLocalObject()->asRemoteObject();
    globalPlatform->destroyUsmDescriptor(ptr);


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return;
    }
}
cl_int clEnqueueSVMMap (cl_command_queue command_queue, cl_bool blocking_map, cl_map_flags map_flags, void* svm_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    log<Verbosity::bloat>("Establishing RPC for clEnqueueSVMMap");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueSVMMapRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, blocking_map, map_flags, svm_ptr, size, num_events_in_wait_list, event_wait_list, event);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, blocking_map, map_flags, svm_ptr, size, num_events_in_wait_list, event_wait_list, event);
    command->copyFromCaller(dynMemTraits);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    if(event_wait_list)
    {
        auto base = command->captures.event_wait_list;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

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
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue, CL_COMMAND_SVM_MAP);
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->enqueue();
    return ret;
}
cl_int clEnqueueSVMUnmap (cl_command_queue command_queue, void* svm_ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    log<Verbosity::bloat>("Establishing RPC for clEnqueueSVMUnmap");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueSVMUnmapRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, svm_ptr, num_events_in_wait_list, event_wait_list, event);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, svm_ptr, num_events_in_wait_list, event_wait_list, event);
    command->copyFromCaller(dynMemTraits);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    if(event_wait_list)
    {
        auto base = command->captures.event_wait_list;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

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
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue, CL_COMMAND_SVM_UNMAP);
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->enqueue();
    return ret;
}
 // clSetKernelArgSVMPointer ignored in generator - based on dont_generate_handler flag
cl_int clSetKernelExecInfo (cl_kernel kernel, cl_kernel_exec_info param_name, size_t param_value_size, const void* param_value) {
    kernel->asLocalObject()->sharedIndirectAccessSet |= ((param_name == CL_KERNEL_EXEC_INFO_INDIRECT_SHARED_ACCESS_INTEL && param_value) ? *reinterpret_cast<const bool*>(param_value) : false);
    log<Verbosity::bloat>("Establishing RPC for clSetKernelExecInfo");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClSetKernelExecInfoRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(kernel, param_name, param_value_size, param_value);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, kernel, param_name, param_value_size, param_value);
    command->copyFromCaller(dynMemTraits);
    command->args.kernel = kernel->asLocalObject()->asRemoteObject();

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
    cl_int ret = command->captures.ret;

    return ret;
}
cl_int clEnqueueSVMMemFill (cl_command_queue command_queue, void* svm_ptr, const void* pattern, size_t patternSize, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    Cal::Client::Icd::icdGlobalState.getPageFaultManager().moveAllocationToGpu(svm_ptr);
    log<Verbosity::bloat>("Establishing RPC for clEnqueueSVMMemFill");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueSVMMemFillRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, svm_ptr, pattern, patternSize, size, num_events_in_wait_list, event_wait_list, event);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, svm_ptr, pattern, patternSize, size, num_events_in_wait_list, event_wait_list, event);
    command->copyFromCaller(dynMemTraits);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    if(event_wait_list)
    {
        auto base = command->captures.getEvent_wait_list();
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

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
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue);
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->enqueue();
    return ret;
}
cl_int clEnqueueSVMMigrateMem (cl_command_queue command_queue, cl_uint num_svm_pointers, const void** svm_pointers, const size_t* sizes, cl_mem_migration_flags flags, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    log<Verbosity::bloat>("Establishing RPC for clEnqueueSVMMigrateMem");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueSVMMigrateMemRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, num_svm_pointers, svm_pointers, sizes, flags, num_events_in_wait_list, event_wait_list, event);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, num_svm_pointers, svm_pointers, sizes, flags, num_events_in_wait_list, event_wait_list, event);
    command->copyFromCaller(dynMemTraits);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    if(event_wait_list)
    {
        auto base = command->captures.getEvent_wait_list();
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

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
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue);
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->enqueue();
    return ret;
}
cl_int clEnqueueSVMMemcpy (cl_command_queue command_queue, cl_bool blocking, void* dst_ptr, const void* src_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    [[maybe_unused]] auto dst_ptr_pointer_type = globalPlatform->getPointerType(dst_ptr);
    [[maybe_unused]] auto src_ptr_pointer_type = globalPlatform->getPointerType(src_ptr);
    
    if((dst_ptr_pointer_type == local) && (src_ptr_pointer_type == local)){
        return clEnqueueSVMMemcpy_Local_Local(command_queue, blocking, dst_ptr, src_ptr, size, num_events_in_wait_list, event_wait_list, event);
    }
    else if((dst_ptr_pointer_type == local) && (src_ptr_pointer_type == usm)){
        return clEnqueueSVMMemcpy_Local_Usm(command_queue, blocking, dst_ptr, src_ptr, size, num_events_in_wait_list, event_wait_list, event);
    }
    else if((dst_ptr_pointer_type == local) && (src_ptr_pointer_type == shared)){
        return clEnqueueSVMMemcpy_Local_Shared(command_queue, blocking, dst_ptr, src_ptr, size, num_events_in_wait_list, event_wait_list, event);
    }
    else if((dst_ptr_pointer_type == usm) && (src_ptr_pointer_type == local)){
        return clEnqueueSVMMemcpy_Usm_Local(command_queue, blocking, dst_ptr, src_ptr, size, num_events_in_wait_list, event_wait_list, event);
    }
    else if((dst_ptr_pointer_type == usm) && (src_ptr_pointer_type == usm)){
        return clEnqueueSVMMemcpy_Usm_Usm(command_queue, blocking, dst_ptr, src_ptr, size, num_events_in_wait_list, event_wait_list, event);
    }
    else if((dst_ptr_pointer_type == usm) && (src_ptr_pointer_type == shared)){
        return clEnqueueSVMMemcpy_Usm_Shared(command_queue, blocking, dst_ptr, src_ptr, size, num_events_in_wait_list, event_wait_list, event);
    }
    else if((dst_ptr_pointer_type == shared) && (src_ptr_pointer_type == local)){
        return clEnqueueSVMMemcpy_Shared_Local(command_queue, blocking, dst_ptr, src_ptr, size, num_events_in_wait_list, event_wait_list, event);
    }
    else if((dst_ptr_pointer_type == shared) && (src_ptr_pointer_type == usm)){
        return clEnqueueSVMMemcpy_Shared_Usm(command_queue, blocking, dst_ptr, src_ptr, size, num_events_in_wait_list, event_wait_list, event);
    }
    else{
        return clEnqueueSVMMemcpy_Shared_Shared(command_queue, blocking, dst_ptr, src_ptr, size, num_events_in_wait_list, event_wait_list, event);
    }
}
cl_int clEnqueueSVMFree (cl_command_queue command_queue, cl_uint num_svm_pointers, void** svm_pointers, void (CL_CALLBACK* pfn_notify)(cl_command_queue queue, cl_uint num_svm_pointers, void ** svm_pointers, void* user_data), void* user_data, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    invalidateKernelArgCache();
    if(pfn_notify){Cal::Client::Icd::icdGlobalState.getOclPlatform()->enableCallbacksHandler();}
    if(!pfn_notify){for (cl_uint i = 0; i < num_svm_pointers; i++) Cal::Client::Icd::icdGlobalState.getPageFaultManager().unregisterSharedAlloc(svm_pointers[i]);}

    log<Verbosity::bloat>("Establishing RPC for clEnqueueSVMFree");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueSVMFreeRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, num_svm_pointers, svm_pointers, pfn_notify, user_data, num_events_in_wait_list, event_wait_list, event);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, num_svm_pointers, svm_pointers, pfn_notify, user_data, num_events_in_wait_list, event_wait_list, event);
    command->copyFromCaller(dynMemTraits);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    command->args.user_data = user_data ? new UserDataClEnqueueSVMFree(num_svm_pointers, svm_pointers, user_data) : nullptr;
    if(event_wait_list)
    {
        auto base = command->captures.getEvent_wait_list();
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

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
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue);
    }
    cl_int ret = command->captures.ret;

    return ret;
}
cl_int clCreateSubDevicesEXT (cl_device_id in_device, const cl_device_partition_property_ext* properties, cl_uint num_entries, cl_device_id* out_devices, cl_uint* num_devices) {
    log<Verbosity::bloat>("Establishing RPC for clCreateSubDevicesEXT");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClCreateSubDevicesEXTRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(in_device, properties, num_entries, out_devices, num_devices);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, in_device, properties, num_entries, out_devices, num_devices);
    command->copyFromCaller(dynMemTraits);
    command->args.in_device = in_device->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    if(out_devices)
    {
        auto baseMutable = mutable_element_cast(out_devices);

        auto numEntries = num_entries;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = globalPlatform->translateNewRemoteObjectToLocalObject(baseMutable[i], in_device);
        }
    }
    cl_int ret = command->captures.ret;

    return ret;
}
cl_int clReleaseDeviceEXT (cl_device_id device) {
    log<Verbosity::bloat>("Establishing RPC for clReleaseDeviceEXT");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClReleaseDeviceEXTRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(device);
    command->args.device = device->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    {
        device->asLocalObject()->dec();
    }
    cl_int ret = command->captures.ret;

    return ret;
}
cl_int clRetainDeviceEXT (cl_device_id device) {
    log<Verbosity::bloat>("Establishing RPC for clRetainDeviceEXT");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClRetainDeviceEXTRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(device);
    command->args.device = device->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    {
        device->asLocalObject()->inc();
    }
    cl_int ret = command->captures.ret;

    return ret;
}
cl_int clGetKernelSubGroupInfoKHR (cl_kernel kernel, cl_device_id device, cl_kernel_sub_group_info param_name, size_t input_value_size, const void* input_value, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    log<Verbosity::bloat>("Establishing RPC for clGetKernelSubGroupInfoKHR");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClGetKernelSubGroupInfoKHRRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(kernel, device, param_name, input_value_size, input_value, param_value_size, param_value, param_value_size_ret);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, kernel, device, param_name, input_value_size, input_value, param_value_size, param_value, param_value_size_ret);
    command->copyFromCaller(dynMemTraits);
    command->args.kernel = kernel->asLocalObject()->asRemoteObject();
    command->args.device = device->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    cl_int ret = command->captures.ret;

    return ret;
}
cl_int clGetKernelSuggestedLocalWorkSizeKHR (cl_command_queue command_queue, cl_kernel kernel, cl_uint work_dim, const size_t* global_work_offset, const size_t* global_work_size, size_t * suggested_local_work_size) {
    log<Verbosity::bloat>("Establishing RPC for clGetKernelSuggestedLocalWorkSizeKHR");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClGetKernelSuggestedLocalWorkSizeKHRRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, kernel, work_dim, global_work_offset, global_work_size, suggested_local_work_size);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, kernel, work_dim, global_work_offset, global_work_size, suggested_local_work_size);
    command->copyFromCaller(dynMemTraits);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    command->args.kernel = kernel->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    cl_int ret = command->captures.ret;

    return ret;
}
cl_command_queue clCreateCommandQueueWithPropertiesKHR (cl_context context, cl_device_id device, const cl_queue_properties* properties, cl_int* errcode_ret) {
    log<Verbosity::bloat>("Establishing RPC for clCreateCommandQueueWithPropertiesKHR");
    return Cal::Client::Icd::Ocl::clCreateCommandQueueWithProperties(context, device, properties, errcode_ret);
}
cl_int clEnqueueMemFillINTEL (cl_command_queue command_queue, void* dstPtr, const void* pattern, size_t patternSize, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    Cal::Client::Icd::icdGlobalState.getPageFaultManager().moveAllocationToGpu(dstPtr);
    log<Verbosity::bloat>("Establishing RPC for clEnqueueMemFillINTEL");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueMemFillINTELRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, dstPtr, pattern, patternSize, size, num_events_in_wait_list, event_wait_list, event);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, dstPtr, pattern, patternSize, size, num_events_in_wait_list, event_wait_list, event);
    command->copyFromCaller(dynMemTraits);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    if(event_wait_list)
    {
        auto base = command->captures.getEvent_wait_list();
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

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
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue);
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->enqueue();
    return ret;
}
cl_int clEnqueueMemcpyINTEL (cl_command_queue command_queue, cl_bool blocking, void* dstPtr, const void* srcPtr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    [[maybe_unused]] auto dstPtr_pointer_type = globalPlatform->getPointerType(dstPtr);
    [[maybe_unused]] auto srcPtr_pointer_type = globalPlatform->getPointerType(srcPtr);
    
    if((dstPtr_pointer_type == local) && (srcPtr_pointer_type == local)){
        return clEnqueueMemcpyINTEL_Local_Local(command_queue, blocking, dstPtr, srcPtr, size, num_events_in_wait_list, event_wait_list, event);
    }
    else if((dstPtr_pointer_type == local) && (srcPtr_pointer_type == usm)){
        return clEnqueueMemcpyINTEL_Local_Usm(command_queue, blocking, dstPtr, srcPtr, size, num_events_in_wait_list, event_wait_list, event);
    }
    else if((dstPtr_pointer_type == local) && (srcPtr_pointer_type == shared)){
        return clEnqueueMemcpyINTEL_Local_Shared(command_queue, blocking, dstPtr, srcPtr, size, num_events_in_wait_list, event_wait_list, event);
    }
    else if((dstPtr_pointer_type == usm) && (srcPtr_pointer_type == local)){
        return clEnqueueMemcpyINTEL_Usm_Local(command_queue, blocking, dstPtr, srcPtr, size, num_events_in_wait_list, event_wait_list, event);
    }
    else if((dstPtr_pointer_type == usm) && (srcPtr_pointer_type == usm)){
        return clEnqueueMemcpyINTEL_Usm_Usm(command_queue, blocking, dstPtr, srcPtr, size, num_events_in_wait_list, event_wait_list, event);
    }
    else if((dstPtr_pointer_type == usm) && (srcPtr_pointer_type == shared)){
        return clEnqueueMemcpyINTEL_Usm_Shared(command_queue, blocking, dstPtr, srcPtr, size, num_events_in_wait_list, event_wait_list, event);
    }
    else if((dstPtr_pointer_type == shared) && (srcPtr_pointer_type == local)){
        return clEnqueueMemcpyINTEL_Shared_Local(command_queue, blocking, dstPtr, srcPtr, size, num_events_in_wait_list, event_wait_list, event);
    }
    else if((dstPtr_pointer_type == shared) && (srcPtr_pointer_type == usm)){
        return clEnqueueMemcpyINTEL_Shared_Usm(command_queue, blocking, dstPtr, srcPtr, size, num_events_in_wait_list, event_wait_list, event);
    }
    else{
        return clEnqueueMemcpyINTEL_Shared_Shared(command_queue, blocking, dstPtr, srcPtr, size, num_events_in_wait_list, event_wait_list, event);
    }
}
cl_int clSetKernelArgMemPointerINTELRpcHelper (cl_kernel kernel, cl_uint argIndex, const void* argValue) {
    log<Verbosity::bloat>("Establishing RPC for clSetKernelArgMemPointerINTEL");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClSetKernelArgMemPointerINTELRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(kernel, argIndex, argValue);
    command->args.kernel = kernel->asLocalObject()->asRemoteObject();

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
    cl_int ret = command->captures.ret;

    return ret;
}
cl_int clGetMemAllocInfoINTEL (cl_context context, const void* ptr, cl_mem_info_intel param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    log<Verbosity::bloat>("Establishing RPC for clGetMemAllocInfoINTEL");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClGetMemAllocInfoINTELRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(context, ptr, param_name, param_value_size, param_value, param_value_size_ret);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, context, ptr, param_name, param_value_size, param_value, param_value_size_ret);
    command->args.context = context->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    if(param_value)
    {
        globalPlatform->translateRemoteObjectToLocalObjectInParams(param_value, param_name);
    }
    cl_int ret = command->captures.ret;

    return ret;
}
void* clDeviceMemAllocINTEL (cl_context context, cl_device_id device, const cl_mem_properties_intel* properties, size_t size, cl_uint alignment, cl_int* errcode_ret) {
    log<Verbosity::bloat>("Establishing RPC for clDeviceMemAllocINTEL");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClDeviceMemAllocINTELRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(context, device, properties, size, alignment, errcode_ret);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, context, device, properties, size, alignment, errcode_ret);
    command->copyFromCaller(dynMemTraits);
    command->args.context = context->asLocalObject()->asRemoteObject();
    command->args.device = device->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    void* ret = command->captures.ret;

    ret = Cal::Client::Icd::icdGlobalState.getOclPlatform()->validateNewUsmDevicePointer(ret, size);
    return ret;
}
void* clHostMemAllocINTELRpcHelper (cl_context context, const cl_mem_properties_intel* properties, size_t size, cl_uint alignment, cl_int* errcode_ret, Cal::Rpc::Ocl::ClHostMemAllocINTELRpcMImplicitArgs &implArgsForClHostMemAllocINTELRpcM) {
    log<Verbosity::bloat>("Establishing RPC for clHostMemAllocINTEL");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClHostMemAllocINTELRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(context, properties, size, alignment, errcode_ret);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, context, properties, size, alignment, errcode_ret);
    command->copyFromCaller(dynMemTraits, implArgsForClHostMemAllocINTELRpcM);
    command->args.context = context->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits, implArgsForClHostMemAllocINTELRpcM);
    void* ret = command->captures.ret;

    return ret;
}
void* clSharedMemAllocINTELRpcHelper (cl_context context, cl_device_id device, const cl_mem_properties_intel* properties, size_t size, cl_uint alignment, cl_int* errcode_ret, Cal::Rpc::Ocl::ClSharedMemAllocINTELRpcMImplicitArgs &implArgsForClSharedMemAllocINTELRpcM) {
    log<Verbosity::bloat>("Establishing RPC for clSharedMemAllocINTEL");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClSharedMemAllocINTELRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(context, device, properties, size, alignment, errcode_ret);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, context, device, properties, size, alignment, errcode_ret);
    command->copyFromCaller(dynMemTraits, implArgsForClSharedMemAllocINTELRpcM);
    command->args.context = context->asLocalObject()->asRemoteObject();
    command->args.device = device->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits, implArgsForClSharedMemAllocINTELRpcM);
    void* ret = command->captures.ret;

    return ret;
}
cl_int clMemFreeINTEL (cl_context context, void* ptr) {
    invalidateKernelArgCache();
    Cal::Client::Icd::icdGlobalState.getPageFaultManager().unregisterSharedAlloc(ptr);

    log<Verbosity::bloat>("Establishing RPC for clMemFreeINTEL");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClMemFreeINTELRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(context, ptr);
    command->args.context = context->asLocalObject()->asRemoteObject();
    globalPlatform->destroyUsmDescriptor(ptr);


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    cl_int ret = command->captures.ret;

    return ret;
}
cl_int clMemBlockingFreeINTEL (cl_context context, void* ptr) {
    invalidateKernelArgCache();
    log<Verbosity::bloat>("Establishing RPC for clMemBlockingFreeINTEL");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClMemBlockingFreeINTELRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(context, ptr);
    command->args.context = context->asLocalObject()->asRemoteObject();
    globalPlatform->destroyUsmDescriptor(ptr);


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    cl_int ret = command->captures.ret;

    return ret;
}
cl_int clEnqueueMigrateMemINTEL (cl_command_queue command_queue, const void* ptr, size_t size, cl_mem_migration_flags flags, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    log<Verbosity::bloat>("Establishing RPC for clEnqueueMigrateMemINTEL");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueMigrateMemINTELRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, ptr, size, flags, num_events_in_wait_list, event_wait_list, event);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, ptr, size, flags, num_events_in_wait_list, event_wait_list, event);
    command->copyFromCaller(dynMemTraits);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    if(event_wait_list)
    {
        auto base = command->captures.event_wait_list;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

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
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue);
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->enqueue();
    return ret;
}
cl_int clGetDeviceGlobalVariablePointerINTEL (cl_device_id device, cl_program program, const char* globalVariableName, size_t* globalVariableSizeRet, void** globalVariablePointerRet) {
    log<Verbosity::bloat>("Establishing RPC for clGetDeviceGlobalVariablePointerINTEL");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClGetDeviceGlobalVariablePointerINTELRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(device, program, globalVariableName, globalVariableSizeRet, globalVariablePointerRet);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, device, program, globalVariableName, globalVariableSizeRet, globalVariablePointerRet);
    command->copyFromCaller(dynMemTraits);
    command->args.device = device->asLocalObject()->asRemoteObject();
    command->args.program = program->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller(dynMemTraits);
    if(globalVariablePointerRet)
    {
        if (command->captures.ret == CL_SUCCESS)
            globalPlatform->recordGlobalPointer(program, *globalVariablePointerRet);
    }
    cl_int ret = command->captures.ret;

    return ret;
}
cl_mem clCreateBufferRpcHelperNotUseHostPtrZeroCopyMallocShmem_Usm (cl_context context, cl_mem_flags flags, size_t size, void* host_ptr, cl_int* errcode_ret) {
    [[maybe_unused]] constexpr auto host_ptr_kind = usm;
    Cal::Client::Icd::icdGlobalState.getOclPlatform()->getPageFaultManager().moveAllocationToGpu(host_ptr);
    log<Verbosity::bloat>("Establishing RPC for clCreateBufferRpcHelperNotUseHostPtrZeroCopyMallocShmem_Usm");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClCreateBufferRpcHelperNotUseHostPtrZeroCopyMallocShmem_UsmRpcM;
    auto commandSpace = channel.getCmdSpace<CommandT>(0);
    auto command = new(commandSpace) CommandT(context, flags, size, host_ptr, errcode_ret);
    command->args.context = context->asLocalObject()->asRemoteObject();


    if(channel.shouldSynchronizeNextCommandWithSemaphores(CommandT::latency)) {
        command->header.flags |= Cal::Rpc::RpcMessageHeader::signalSemaphoreOnCompletion;
    }

    if(false == channel.callSynchronous(command)){
        return command->returnValue();
    }
    command->copyToCaller();
    cl_mem ret = command->captures.ret;

    ret = globalPlatform->translateNewRemoteObjectToLocalObject(ret, context);
    return ret;
}
cl_int clEnqueueWriteBuffer_Local (cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, size_t offset, size_t size, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    [[maybe_unused]] constexpr auto ptr_kind = local;
    Cal::Client::Icd::icdGlobalState.getPageFaultManager().moveAllocationToGpu(ptr);
    log<Verbosity::bloat>("Establishing RPC for clEnqueueWriteBuffer_Local");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    void *standalone_ptr{};
    {
        std::unique_ptr<void, std::function<void(void*)>> standalone_ptr_alloc(static_cast<IcdOclCommandQueue *>(command_queue)->context->getStagingAreaManager().allocateStagingArea(size), [command_queue](void *ptrToMarkAsUnused){static_cast<IcdOclCommandQueue *>(command_queue)->context->getStagingAreaManager().releaseStagingArea(ptrToMarkAsUnused);});
        standalone_ptr = standalone_ptr_alloc.get();
        command_queue->asLocalObject()->registerTemporaryAllocation(std::move(standalone_ptr_alloc));
    }
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueWriteBuffer_LocalRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, buffer, blocking_write, offset, size, ptr, num_events_in_wait_list, event_wait_list, event);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, buffer, blocking_write, offset, size, ptr, num_events_in_wait_list, event_wait_list, event);
    memcpy(Cal::Utils::toAddress(standalone_ptr), ptr, size);
    command->copyFromCaller(dynMemTraits);
    command->args.ptr = reinterpret_cast<const void*>(standalone_ptr);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    command->args.buffer = buffer->asLocalObject()->asRemoteObject();
    if(event_wait_list)
    {
        auto base = command->captures.event_wait_list;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !command->args.blocking_write &&
       !command->args.event &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         command_queue->asLocalObject()->enqueue();
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
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue);
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->enqueue();
    return ret;
}
cl_int clEnqueueWriteBuffer_Usm (cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, size_t offset, size_t size, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    [[maybe_unused]] constexpr auto ptr_kind = usm;
    Cal::Client::Icd::icdGlobalState.getPageFaultManager().moveAllocationToGpu(ptr);
    log<Verbosity::bloat>("Establishing RPC for clEnqueueWriteBuffer_Usm");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueWriteBuffer_UsmRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, buffer, blocking_write, offset, size, ptr, num_events_in_wait_list, event_wait_list, event);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, buffer, blocking_write, offset, size, ptr, num_events_in_wait_list, event_wait_list, event);
    command->copyFromCaller(dynMemTraits);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    command->args.buffer = buffer->asLocalObject()->asRemoteObject();
    if(event_wait_list)
    {
        auto base = command->captures.event_wait_list;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !command->args.blocking_write &&
       !command->args.event &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         command_queue->asLocalObject()->enqueue();
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
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue);
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->enqueue();
    return ret;
}
cl_int clEnqueueWriteBuffer_Shared (cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, size_t offset, size_t size, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    [[maybe_unused]] constexpr auto ptr_kind = shared;
    Cal::Client::Icd::icdGlobalState.getPageFaultManager().moveAllocationToGpu(ptr);
    log<Verbosity::bloat>("Establishing RPC for clEnqueueWriteBuffer_Shared");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueWriteBuffer_SharedRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, buffer, blocking_write, offset, size, ptr, num_events_in_wait_list, event_wait_list, event);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, buffer, blocking_write, offset, size, ptr, num_events_in_wait_list, event_wait_list, event);
    command->copyFromCaller(dynMemTraits);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    command->args.buffer = buffer->asLocalObject()->asRemoteObject();
    if(event_wait_list)
    {
        auto base = command->captures.event_wait_list;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !command->args.blocking_write &&
       !command->args.event &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         command_queue->asLocalObject()->enqueue();
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
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue);
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->enqueue();
    return ret;
}
cl_int clEnqueueWriteBufferRect_Local (cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, const size_t* buffer_origin, const size_t* host_origin, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    [[maybe_unused]] constexpr auto ptr_kind = local;
    Cal::Client::Icd::icdGlobalState.getPageFaultManager().moveAllocationToGpu(ptr);
    log<Verbosity::bloat>("Establishing RPC for clEnqueueWriteBufferRect_Local");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    void *standalone_ptr{};
    {
        std::unique_ptr<void, std::function<void(void*)>> standalone_ptr_alloc(static_cast<IcdOclCommandQueue *>(command_queue)->context->getStagingAreaManager().allocateStagingArea(Cal::Utils::getBufferRectSizeInBytes(host_origin, region, host_row_pitch, host_slice_pitch)), [command_queue](void *ptrToMarkAsUnused){static_cast<IcdOclCommandQueue *>(command_queue)->context->getStagingAreaManager().releaseStagingArea(ptrToMarkAsUnused);});
        standalone_ptr = standalone_ptr_alloc.get();
        command_queue->asLocalObject()->registerTemporaryAllocation(std::move(standalone_ptr_alloc));
    }
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueWriteBufferRect_LocalRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, buffer, blocking_write, buffer_origin, host_origin, region, buffer_row_pitch, buffer_slice_pitch, host_row_pitch, host_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, buffer, blocking_write, buffer_origin, host_origin, region, buffer_row_pitch, buffer_slice_pitch, host_row_pitch, host_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event);
    memcpy(Cal::Utils::toAddress(standalone_ptr), ptr, Cal::Utils::getBufferRectSizeInBytes(host_origin, region, host_row_pitch, host_slice_pitch));
    command->copyFromCaller(dynMemTraits);
    command->args.ptr = reinterpret_cast<const void*>(standalone_ptr);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    command->args.buffer = buffer->asLocalObject()->asRemoteObject();
    if(event_wait_list)
    {
        auto base = command->captures.event_wait_list;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !command->args.blocking_write &&
       !command->args.event &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         command_queue->asLocalObject()->enqueue();
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
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue);
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->enqueue();
    return ret;
}
cl_int clEnqueueWriteBufferRect_Usm (cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, const size_t* buffer_origin, const size_t* host_origin, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    [[maybe_unused]] constexpr auto ptr_kind = usm;
    Cal::Client::Icd::icdGlobalState.getPageFaultManager().moveAllocationToGpu(ptr);
    log<Verbosity::bloat>("Establishing RPC for clEnqueueWriteBufferRect_Usm");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueWriteBufferRect_UsmRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, buffer, blocking_write, buffer_origin, host_origin, region, buffer_row_pitch, buffer_slice_pitch, host_row_pitch, host_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, buffer, blocking_write, buffer_origin, host_origin, region, buffer_row_pitch, buffer_slice_pitch, host_row_pitch, host_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event);
    command->copyFromCaller(dynMemTraits);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    command->args.buffer = buffer->asLocalObject()->asRemoteObject();
    if(event_wait_list)
    {
        auto base = command->captures.event_wait_list;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !command->args.blocking_write &&
       !command->args.event &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         command_queue->asLocalObject()->enqueue();
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
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue);
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->enqueue();
    return ret;
}
cl_int clEnqueueWriteBufferRect_Shared (cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, const size_t* buffer_origin, const size_t* host_origin, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    [[maybe_unused]] constexpr auto ptr_kind = shared;
    Cal::Client::Icd::icdGlobalState.getPageFaultManager().moveAllocationToGpu(ptr);
    log<Verbosity::bloat>("Establishing RPC for clEnqueueWriteBufferRect_Shared");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueWriteBufferRect_SharedRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, buffer, blocking_write, buffer_origin, host_origin, region, buffer_row_pitch, buffer_slice_pitch, host_row_pitch, host_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, buffer, blocking_write, buffer_origin, host_origin, region, buffer_row_pitch, buffer_slice_pitch, host_row_pitch, host_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event);
    command->copyFromCaller(dynMemTraits);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    command->args.buffer = buffer->asLocalObject()->asRemoteObject();
    if(event_wait_list)
    {
        auto base = command->captures.event_wait_list;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !command->args.blocking_write &&
       !command->args.event &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         command_queue->asLocalObject()->enqueue();
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
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue);
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->enqueue();
    return ret;
}
cl_int clEnqueueReadBuffer_Local (cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, size_t offset, size_t size, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    [[maybe_unused]] constexpr auto ptr_kind = local;
    Cal::Client::Icd::icdGlobalState.getPageFaultManager().moveAllocationToGpu(ptr);
    log<Verbosity::bloat>("Establishing RPC for clEnqueueReadBuffer_Local");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    void *standalone_ptr{};
    {
        std::unique_ptr<void, std::function<void(void*)>> standalone_ptr_alloc(static_cast<IcdOclCommandQueue *>(command_queue)->context->getStagingAreaManager().allocateStagingArea(size), [command_queue](void *ptrToMarkAsUnused){static_cast<IcdOclCommandQueue *>(command_queue)->context->getStagingAreaManager().releaseStagingArea(ptrToMarkAsUnused);});
        standalone_ptr = standalone_ptr_alloc.get();
        command_queue->asLocalObject()->registerTemporaryAllocation(std::move(standalone_ptr_alloc));
    }
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueReadBuffer_LocalRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, buffer, blocking_read, offset, size, ptr, num_events_in_wait_list, event_wait_list, event);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, buffer, blocking_read, offset, size, ptr, num_events_in_wait_list, event_wait_list, event);
    command->copyFromCaller(dynMemTraits);
    command->args.ptr = reinterpret_cast<void*>(standalone_ptr);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    command->args.buffer = buffer->asLocalObject()->asRemoteObject();
    Cal::Client::Icd::Ocl::warnIfNonBlockingRead(command->args.blocking_read, ptr_kind);
    if(event_wait_list)
    {
        auto base = command->captures.event_wait_list;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !command->args.blocking_read &&
       !command->args.event &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         command_queue->asLocalObject()->enqueue();
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
    memcpy(ptr, standalone_ptr, size);
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue);
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->synchronizeNow(command->args.blocking_read);
    command_queue->asLocalObject()->enqueue();

    return ret;
}
cl_int clEnqueueReadBuffer_Usm (cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, size_t offset, size_t size, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    [[maybe_unused]] constexpr auto ptr_kind = usm;
    Cal::Client::Icd::icdGlobalState.getPageFaultManager().moveAllocationToGpu(ptr);
    log<Verbosity::bloat>("Establishing RPC for clEnqueueReadBuffer_Usm");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueReadBuffer_UsmRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, buffer, blocking_read, offset, size, ptr, num_events_in_wait_list, event_wait_list, event);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, buffer, blocking_read, offset, size, ptr, num_events_in_wait_list, event_wait_list, event);
    command->copyFromCaller(dynMemTraits);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    command->args.buffer = buffer->asLocalObject()->asRemoteObject();
    Cal::Client::Icd::Ocl::warnIfNonBlockingRead(command->args.blocking_read, ptr_kind);
    if(event_wait_list)
    {
        auto base = command->captures.event_wait_list;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !command->args.blocking_read &&
       !command->args.event &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         command_queue->asLocalObject()->enqueue();
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
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue);
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->synchronizeNow(command->args.blocking_read);
    command_queue->asLocalObject()->enqueue();

    return ret;
}
cl_int clEnqueueReadBuffer_Shared (cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, size_t offset, size_t size, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    [[maybe_unused]] constexpr auto ptr_kind = shared;
    Cal::Client::Icd::icdGlobalState.getPageFaultManager().moveAllocationToGpu(ptr);
    log<Verbosity::bloat>("Establishing RPC for clEnqueueReadBuffer_Shared");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueReadBuffer_SharedRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, buffer, blocking_read, offset, size, ptr, num_events_in_wait_list, event_wait_list, event);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, buffer, blocking_read, offset, size, ptr, num_events_in_wait_list, event_wait_list, event);
    command->copyFromCaller(dynMemTraits);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    command->args.buffer = buffer->asLocalObject()->asRemoteObject();
    Cal::Client::Icd::Ocl::warnIfNonBlockingRead(command->args.blocking_read, ptr_kind);
    if(event_wait_list)
    {
        auto base = command->captures.event_wait_list;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !command->args.blocking_read &&
       !command->args.event &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         command_queue->asLocalObject()->enqueue();
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
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue);
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->synchronizeNow(command->args.blocking_read);
    command_queue->asLocalObject()->enqueue();

    return ret;
}
cl_int clEnqueueReadBufferRect_Local (cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, const size_t* buffer_origin, const size_t* host_origin, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    [[maybe_unused]] constexpr auto ptr_kind = local;
    Cal::Client::Icd::icdGlobalState.getPageFaultManager().moveAllocationToGpu(ptr);
    log<Verbosity::bloat>("Establishing RPC for clEnqueueReadBufferRect_Local");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    void *standalone_ptr{};
    {
        std::unique_ptr<void, std::function<void(void*)>> standalone_ptr_alloc(static_cast<IcdOclCommandQueue *>(command_queue)->context->getStagingAreaManager().allocateStagingArea(Cal::Utils::getBufferRectSizeInBytes(host_origin, region, host_row_pitch, host_slice_pitch)), [command_queue](void *ptrToMarkAsUnused){static_cast<IcdOclCommandQueue *>(command_queue)->context->getStagingAreaManager().releaseStagingArea(ptrToMarkAsUnused);});
        standalone_ptr = standalone_ptr_alloc.get();
        command_queue->asLocalObject()->registerTemporaryAllocation(std::move(standalone_ptr_alloc));
    }
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueReadBufferRect_LocalRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, buffer, blocking_read, buffer_origin, host_origin, region, buffer_row_pitch, buffer_slice_pitch, host_row_pitch, host_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, buffer, blocking_read, buffer_origin, host_origin, region, buffer_row_pitch, buffer_slice_pitch, host_row_pitch, host_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event);
    command->copyFromCaller(dynMemTraits);
    command->args.ptr = reinterpret_cast<void*>(standalone_ptr);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    command->args.buffer = buffer->asLocalObject()->asRemoteObject();
    Cal::Client::Icd::Ocl::warnIfNonBlockingRead(command->args.blocking_read, ptr_kind);
    if(event_wait_list)
    {
        auto base = command->captures.event_wait_list;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !command->args.blocking_read &&
       !command->args.event &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         command_queue->asLocalObject()->enqueue();
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
    memcpy(ptr, standalone_ptr, Cal::Utils::getBufferRectSizeInBytes(host_origin, region, host_row_pitch, host_slice_pitch));
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue);
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->synchronizeNow(command->args.blocking_read);
    command_queue->asLocalObject()->enqueue();

    return ret;
}
cl_int clEnqueueReadBufferRect_Usm (cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, const size_t* buffer_origin, const size_t* host_origin, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    [[maybe_unused]] constexpr auto ptr_kind = usm;
    Cal::Client::Icd::icdGlobalState.getPageFaultManager().moveAllocationToGpu(ptr);
    log<Verbosity::bloat>("Establishing RPC for clEnqueueReadBufferRect_Usm");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueReadBufferRect_UsmRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, buffer, blocking_read, buffer_origin, host_origin, region, buffer_row_pitch, buffer_slice_pitch, host_row_pitch, host_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, buffer, blocking_read, buffer_origin, host_origin, region, buffer_row_pitch, buffer_slice_pitch, host_row_pitch, host_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event);
    command->copyFromCaller(dynMemTraits);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    command->args.buffer = buffer->asLocalObject()->asRemoteObject();
    Cal::Client::Icd::Ocl::warnIfNonBlockingRead(command->args.blocking_read, ptr_kind);
    if(event_wait_list)
    {
        auto base = command->captures.event_wait_list;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !command->args.blocking_read &&
       !command->args.event &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         command_queue->asLocalObject()->enqueue();
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
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue);
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->synchronizeNow(command->args.blocking_read);
    command_queue->asLocalObject()->enqueue();

    return ret;
}
cl_int clEnqueueReadBufferRect_Shared (cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, const size_t* buffer_origin, const size_t* host_origin, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    [[maybe_unused]] constexpr auto ptr_kind = shared;
    Cal::Client::Icd::icdGlobalState.getPageFaultManager().moveAllocationToGpu(ptr);
    log<Verbosity::bloat>("Establishing RPC for clEnqueueReadBufferRect_Shared");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueReadBufferRect_SharedRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, buffer, blocking_read, buffer_origin, host_origin, region, buffer_row_pitch, buffer_slice_pitch, host_row_pitch, host_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, buffer, blocking_read, buffer_origin, host_origin, region, buffer_row_pitch, buffer_slice_pitch, host_row_pitch, host_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event);
    command->copyFromCaller(dynMemTraits);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    command->args.buffer = buffer->asLocalObject()->asRemoteObject();
    Cal::Client::Icd::Ocl::warnIfNonBlockingRead(command->args.blocking_read, ptr_kind);
    if(event_wait_list)
    {
        auto base = command->captures.event_wait_list;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !command->args.blocking_read &&
       !command->args.event &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         command_queue->asLocalObject()->enqueue();
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
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue);
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->synchronizeNow(command->args.blocking_read);
    command_queue->asLocalObject()->enqueue();

    return ret;
}
cl_int clEnqueueSVMMemcpy_Local_Local (cl_command_queue command_queue, cl_bool blocking, void* dst_ptr, const void* src_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    [[maybe_unused]] constexpr auto dst_ptr_kind = local;
    [[maybe_unused]] constexpr auto src_ptr_kind = local;
    Cal::Client::Icd::icdGlobalState.getPageFaultManager().moveAllocationToGpu(dst_ptr, src_ptr);
    log<Verbosity::bloat>("Establishing RPC for clEnqueueSVMMemcpy_Local_Local");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    void *standalone_dst_ptr{};
    {
        std::unique_ptr<void, std::function<void(void*)>> standalone_dst_ptr_alloc(static_cast<IcdOclCommandQueue *>(command_queue)->context->getStagingAreaManager().allocateStagingArea(size), [command_queue](void *ptrToMarkAsUnused){static_cast<IcdOclCommandQueue *>(command_queue)->context->getStagingAreaManager().releaseStagingArea(ptrToMarkAsUnused);});
        standalone_dst_ptr = standalone_dst_ptr_alloc.get();
        command_queue->asLocalObject()->registerTemporaryAllocation(std::move(standalone_dst_ptr_alloc));
    }
    void *standalone_src_ptr{};
    {
        std::unique_ptr<void, std::function<void(void*)>> standalone_src_ptr_alloc(static_cast<IcdOclCommandQueue *>(command_queue)->context->getStagingAreaManager().allocateStagingArea(size), [command_queue](void *ptrToMarkAsUnused){static_cast<IcdOclCommandQueue *>(command_queue)->context->getStagingAreaManager().releaseStagingArea(ptrToMarkAsUnused);});
        standalone_src_ptr = standalone_src_ptr_alloc.get();
        command_queue->asLocalObject()->registerTemporaryAllocation(std::move(standalone_src_ptr_alloc));
    }
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueSVMMemcpy_Local_LocalRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, blocking, dst_ptr, src_ptr, size, num_events_in_wait_list, event_wait_list, event);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, blocking, dst_ptr, src_ptr, size, num_events_in_wait_list, event_wait_list, event);
    memcpy(Cal::Utils::toAddress(standalone_src_ptr), src_ptr, size);
    command->copyFromCaller(dynMemTraits);
    command->args.dst_ptr = reinterpret_cast<void*>(standalone_dst_ptr);
    command->args.src_ptr = reinterpret_cast<const void*>(standalone_src_ptr);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    Cal::Client::Icd::Ocl::warnIfNonBlockingRead(command->args.blocking, dst_ptr_kind);
    if(event_wait_list)
    {
        auto base = command->captures.event_wait_list;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !command->args.blocking &&
       !command->args.event &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         command_queue->asLocalObject()->enqueue();
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
    memcpy(dst_ptr, standalone_dst_ptr, size);
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue);
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->synchronizeNow(command->args.blocking);
    command_queue->asLocalObject()->enqueue();

    return ret;
}
cl_int clEnqueueSVMMemcpy_Local_Usm (cl_command_queue command_queue, cl_bool blocking, void* dst_ptr, const void* src_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    [[maybe_unused]] constexpr auto dst_ptr_kind = local;
    [[maybe_unused]] constexpr auto src_ptr_kind = usm;
    Cal::Client::Icd::icdGlobalState.getPageFaultManager().moveAllocationToGpu(dst_ptr, src_ptr);
    log<Verbosity::bloat>("Establishing RPC for clEnqueueSVMMemcpy_Local_Usm");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    void *standalone_dst_ptr{};
    {
        std::unique_ptr<void, std::function<void(void*)>> standalone_dst_ptr_alloc(static_cast<IcdOclCommandQueue *>(command_queue)->context->getStagingAreaManager().allocateStagingArea(size), [command_queue](void *ptrToMarkAsUnused){static_cast<IcdOclCommandQueue *>(command_queue)->context->getStagingAreaManager().releaseStagingArea(ptrToMarkAsUnused);});
        standalone_dst_ptr = standalone_dst_ptr_alloc.get();
        command_queue->asLocalObject()->registerTemporaryAllocation(std::move(standalone_dst_ptr_alloc));
    }
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueSVMMemcpy_Local_UsmRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, blocking, dst_ptr, src_ptr, size, num_events_in_wait_list, event_wait_list, event);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, blocking, dst_ptr, src_ptr, size, num_events_in_wait_list, event_wait_list, event);
    command->copyFromCaller(dynMemTraits);
    command->args.dst_ptr = reinterpret_cast<void*>(standalone_dst_ptr);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    Cal::Client::Icd::Ocl::warnIfNonBlockingRead(command->args.blocking, dst_ptr_kind);
    if(event_wait_list)
    {
        auto base = command->captures.event_wait_list;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !command->args.blocking &&
       !command->args.event &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         command_queue->asLocalObject()->enqueue();
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
    memcpy(dst_ptr, standalone_dst_ptr, size);
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue);
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->synchronizeNow(command->args.blocking);
    command_queue->asLocalObject()->enqueue();

    return ret;
}
cl_int clEnqueueSVMMemcpy_Local_Shared (cl_command_queue command_queue, cl_bool blocking, void* dst_ptr, const void* src_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    [[maybe_unused]] constexpr auto dst_ptr_kind = local;
    [[maybe_unused]] constexpr auto src_ptr_kind = shared;
    Cal::Client::Icd::icdGlobalState.getPageFaultManager().moveAllocationToGpu(dst_ptr, src_ptr);
    log<Verbosity::bloat>("Establishing RPC for clEnqueueSVMMemcpy_Local_Shared");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    void *standalone_dst_ptr{};
    {
        std::unique_ptr<void, std::function<void(void*)>> standalone_dst_ptr_alloc(static_cast<IcdOclCommandQueue *>(command_queue)->context->getStagingAreaManager().allocateStagingArea(size), [command_queue](void *ptrToMarkAsUnused){static_cast<IcdOclCommandQueue *>(command_queue)->context->getStagingAreaManager().releaseStagingArea(ptrToMarkAsUnused);});
        standalone_dst_ptr = standalone_dst_ptr_alloc.get();
        command_queue->asLocalObject()->registerTemporaryAllocation(std::move(standalone_dst_ptr_alloc));
    }
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueSVMMemcpy_Local_SharedRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, blocking, dst_ptr, src_ptr, size, num_events_in_wait_list, event_wait_list, event);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, blocking, dst_ptr, src_ptr, size, num_events_in_wait_list, event_wait_list, event);
    command->copyFromCaller(dynMemTraits);
    command->args.dst_ptr = reinterpret_cast<void*>(standalone_dst_ptr);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    Cal::Client::Icd::Ocl::warnIfNonBlockingRead(command->args.blocking, dst_ptr_kind);
    if(event_wait_list)
    {
        auto base = command->captures.event_wait_list;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !command->args.blocking &&
       !command->args.event &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         command_queue->asLocalObject()->enqueue();
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
    memcpy(dst_ptr, standalone_dst_ptr, size);
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue);
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->synchronizeNow(command->args.blocking);
    command_queue->asLocalObject()->enqueue();

    return ret;
}
cl_int clEnqueueSVMMemcpy_Usm_Local (cl_command_queue command_queue, cl_bool blocking, void* dst_ptr, const void* src_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    [[maybe_unused]] constexpr auto dst_ptr_kind = usm;
    [[maybe_unused]] constexpr auto src_ptr_kind = local;
    Cal::Client::Icd::icdGlobalState.getPageFaultManager().moveAllocationToGpu(dst_ptr, src_ptr);
    log<Verbosity::bloat>("Establishing RPC for clEnqueueSVMMemcpy_Usm_Local");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    void *standalone_src_ptr{};
    {
        std::unique_ptr<void, std::function<void(void*)>> standalone_src_ptr_alloc(static_cast<IcdOclCommandQueue *>(command_queue)->context->getStagingAreaManager().allocateStagingArea(size), [command_queue](void *ptrToMarkAsUnused){static_cast<IcdOclCommandQueue *>(command_queue)->context->getStagingAreaManager().releaseStagingArea(ptrToMarkAsUnused);});
        standalone_src_ptr = standalone_src_ptr_alloc.get();
        command_queue->asLocalObject()->registerTemporaryAllocation(std::move(standalone_src_ptr_alloc));
    }
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueSVMMemcpy_Usm_LocalRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, blocking, dst_ptr, src_ptr, size, num_events_in_wait_list, event_wait_list, event);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, blocking, dst_ptr, src_ptr, size, num_events_in_wait_list, event_wait_list, event);
    memcpy(Cal::Utils::toAddress(standalone_src_ptr), src_ptr, size);
    command->copyFromCaller(dynMemTraits);
    command->args.src_ptr = reinterpret_cast<const void*>(standalone_src_ptr);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    Cal::Client::Icd::Ocl::warnIfNonBlockingRead(command->args.blocking, dst_ptr_kind);
    if(event_wait_list)
    {
        auto base = command->captures.event_wait_list;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !command->args.blocking &&
       !command->args.event &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         command_queue->asLocalObject()->enqueue();
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
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue);
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->synchronizeNow(command->args.blocking);
    command_queue->asLocalObject()->enqueue();

    return ret;
}
cl_int clEnqueueSVMMemcpy_Usm_Usm (cl_command_queue command_queue, cl_bool blocking, void* dst_ptr, const void* src_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    [[maybe_unused]] constexpr auto dst_ptr_kind = usm;
    [[maybe_unused]] constexpr auto src_ptr_kind = usm;
    Cal::Client::Icd::icdGlobalState.getPageFaultManager().moveAllocationToGpu(dst_ptr, src_ptr);
    log<Verbosity::bloat>("Establishing RPC for clEnqueueSVMMemcpy_Usm_Usm");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueSVMMemcpy_Usm_UsmRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, blocking, dst_ptr, src_ptr, size, num_events_in_wait_list, event_wait_list, event);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, blocking, dst_ptr, src_ptr, size, num_events_in_wait_list, event_wait_list, event);
    command->copyFromCaller(dynMemTraits);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    Cal::Client::Icd::Ocl::warnIfNonBlockingRead(command->args.blocking, dst_ptr_kind);
    if(event_wait_list)
    {
        auto base = command->captures.event_wait_list;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !command->args.blocking &&
       !command->args.event &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         command_queue->asLocalObject()->enqueue();
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
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue);
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->synchronizeNow(command->args.blocking);
    command_queue->asLocalObject()->enqueue();

    return ret;
}
cl_int clEnqueueSVMMemcpy_Usm_Shared (cl_command_queue command_queue, cl_bool blocking, void* dst_ptr, const void* src_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    [[maybe_unused]] constexpr auto dst_ptr_kind = usm;
    [[maybe_unused]] constexpr auto src_ptr_kind = shared;
    Cal::Client::Icd::icdGlobalState.getPageFaultManager().moveAllocationToGpu(dst_ptr, src_ptr);
    log<Verbosity::bloat>("Establishing RPC for clEnqueueSVMMemcpy_Usm_Shared");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueSVMMemcpy_Usm_SharedRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, blocking, dst_ptr, src_ptr, size, num_events_in_wait_list, event_wait_list, event);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, blocking, dst_ptr, src_ptr, size, num_events_in_wait_list, event_wait_list, event);
    command->copyFromCaller(dynMemTraits);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    Cal::Client::Icd::Ocl::warnIfNonBlockingRead(command->args.blocking, dst_ptr_kind);
    if(event_wait_list)
    {
        auto base = command->captures.event_wait_list;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !command->args.blocking &&
       !command->args.event &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         command_queue->asLocalObject()->enqueue();
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
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue);
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->synchronizeNow(command->args.blocking);
    command_queue->asLocalObject()->enqueue();

    return ret;
}
cl_int clEnqueueSVMMemcpy_Shared_Local (cl_command_queue command_queue, cl_bool blocking, void* dst_ptr, const void* src_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    [[maybe_unused]] constexpr auto dst_ptr_kind = shared;
    [[maybe_unused]] constexpr auto src_ptr_kind = local;
    Cal::Client::Icd::icdGlobalState.getPageFaultManager().moveAllocationToGpu(dst_ptr, src_ptr);
    log<Verbosity::bloat>("Establishing RPC for clEnqueueSVMMemcpy_Shared_Local");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    void *standalone_src_ptr{};
    {
        std::unique_ptr<void, std::function<void(void*)>> standalone_src_ptr_alloc(static_cast<IcdOclCommandQueue *>(command_queue)->context->getStagingAreaManager().allocateStagingArea(size), [command_queue](void *ptrToMarkAsUnused){static_cast<IcdOclCommandQueue *>(command_queue)->context->getStagingAreaManager().releaseStagingArea(ptrToMarkAsUnused);});
        standalone_src_ptr = standalone_src_ptr_alloc.get();
        command_queue->asLocalObject()->registerTemporaryAllocation(std::move(standalone_src_ptr_alloc));
    }
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueSVMMemcpy_Shared_LocalRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, blocking, dst_ptr, src_ptr, size, num_events_in_wait_list, event_wait_list, event);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, blocking, dst_ptr, src_ptr, size, num_events_in_wait_list, event_wait_list, event);
    memcpy(Cal::Utils::toAddress(standalone_src_ptr), src_ptr, size);
    command->copyFromCaller(dynMemTraits);
    command->args.src_ptr = reinterpret_cast<const void*>(standalone_src_ptr);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    Cal::Client::Icd::Ocl::warnIfNonBlockingRead(command->args.blocking, dst_ptr_kind);
    if(event_wait_list)
    {
        auto base = command->captures.event_wait_list;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !command->args.blocking &&
       !command->args.event &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         command_queue->asLocalObject()->enqueue();
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
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue);
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->synchronizeNow(command->args.blocking);
    command_queue->asLocalObject()->enqueue();

    return ret;
}
cl_int clEnqueueSVMMemcpy_Shared_Usm (cl_command_queue command_queue, cl_bool blocking, void* dst_ptr, const void* src_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    [[maybe_unused]] constexpr auto dst_ptr_kind = shared;
    [[maybe_unused]] constexpr auto src_ptr_kind = usm;
    Cal::Client::Icd::icdGlobalState.getPageFaultManager().moveAllocationToGpu(dst_ptr, src_ptr);
    log<Verbosity::bloat>("Establishing RPC for clEnqueueSVMMemcpy_Shared_Usm");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueSVMMemcpy_Shared_UsmRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, blocking, dst_ptr, src_ptr, size, num_events_in_wait_list, event_wait_list, event);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, blocking, dst_ptr, src_ptr, size, num_events_in_wait_list, event_wait_list, event);
    command->copyFromCaller(dynMemTraits);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    Cal::Client::Icd::Ocl::warnIfNonBlockingRead(command->args.blocking, dst_ptr_kind);
    if(event_wait_list)
    {
        auto base = command->captures.event_wait_list;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !command->args.blocking &&
       !command->args.event &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         command_queue->asLocalObject()->enqueue();
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
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue);
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->synchronizeNow(command->args.blocking);
    command_queue->asLocalObject()->enqueue();

    return ret;
}
cl_int clEnqueueSVMMemcpy_Shared_Shared (cl_command_queue command_queue, cl_bool blocking, void* dst_ptr, const void* src_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    [[maybe_unused]] constexpr auto dst_ptr_kind = shared;
    [[maybe_unused]] constexpr auto src_ptr_kind = shared;
    Cal::Client::Icd::icdGlobalState.getPageFaultManager().moveAllocationToGpu(dst_ptr, src_ptr);
    log<Verbosity::bloat>("Establishing RPC for clEnqueueSVMMemcpy_Shared_Shared");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueSVMMemcpy_Shared_SharedRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, blocking, dst_ptr, src_ptr, size, num_events_in_wait_list, event_wait_list, event);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, blocking, dst_ptr, src_ptr, size, num_events_in_wait_list, event_wait_list, event);
    command->copyFromCaller(dynMemTraits);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    Cal::Client::Icd::Ocl::warnIfNonBlockingRead(command->args.blocking, dst_ptr_kind);
    if(event_wait_list)
    {
        auto base = command->captures.event_wait_list;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !command->args.blocking &&
       !command->args.event &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         command_queue->asLocalObject()->enqueue();
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
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue);
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->synchronizeNow(command->args.blocking);
    command_queue->asLocalObject()->enqueue();

    return ret;
}
cl_int clEnqueueMemcpyINTEL_Local_Local (cl_command_queue command_queue, cl_bool blocking, void* dstPtr, const void* srcPtr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    [[maybe_unused]] constexpr auto dstPtr_kind = local;
    [[maybe_unused]] constexpr auto srcPtr_kind = local;
    Cal::Client::Icd::icdGlobalState.getPageFaultManager().moveAllocationToGpu(dstPtr, srcPtr);
    log<Verbosity::bloat>("Establishing RPC for clEnqueueMemcpyINTEL_Local_Local");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    void *standalone_dstPtr{};
    {
        std::unique_ptr<void, std::function<void(void*)>> standalone_dstPtr_alloc(static_cast<IcdOclCommandQueue *>(command_queue)->context->getStagingAreaManager().allocateStagingArea(size), [command_queue](void *ptrToMarkAsUnused){static_cast<IcdOclCommandQueue *>(command_queue)->context->getStagingAreaManager().releaseStagingArea(ptrToMarkAsUnused);});
        standalone_dstPtr = standalone_dstPtr_alloc.get();
        command_queue->asLocalObject()->registerTemporaryAllocation(std::move(standalone_dstPtr_alloc));
    }
    void *standalone_srcPtr{};
    {
        std::unique_ptr<void, std::function<void(void*)>> standalone_srcPtr_alloc(static_cast<IcdOclCommandQueue *>(command_queue)->context->getStagingAreaManager().allocateStagingArea(size), [command_queue](void *ptrToMarkAsUnused){static_cast<IcdOclCommandQueue *>(command_queue)->context->getStagingAreaManager().releaseStagingArea(ptrToMarkAsUnused);});
        standalone_srcPtr = standalone_srcPtr_alloc.get();
        command_queue->asLocalObject()->registerTemporaryAllocation(std::move(standalone_srcPtr_alloc));
    }
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueMemcpyINTEL_Local_LocalRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, blocking, dstPtr, srcPtr, size, num_events_in_wait_list, event_wait_list, event);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, blocking, dstPtr, srcPtr, size, num_events_in_wait_list, event_wait_list, event);
    memcpy(Cal::Utils::toAddress(standalone_srcPtr), srcPtr, size);
    command->copyFromCaller(dynMemTraits);
    command->args.dstPtr = reinterpret_cast<void*>(standalone_dstPtr);
    command->args.srcPtr = reinterpret_cast<const void*>(standalone_srcPtr);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    Cal::Client::Icd::Ocl::warnIfNonBlockingRead(command->args.blocking, dstPtr_kind);
    if(event_wait_list)
    {
        auto base = command->captures.event_wait_list;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !command->args.blocking &&
       !command->args.event &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         command_queue->asLocalObject()->enqueue();
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
    memcpy(dstPtr, standalone_dstPtr, size);
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue);
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->synchronizeNow(command->args.blocking);
    command_queue->asLocalObject()->enqueue();

    return ret;
}
cl_int clEnqueueMemcpyINTEL_Local_Usm (cl_command_queue command_queue, cl_bool blocking, void* dstPtr, const void* srcPtr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    [[maybe_unused]] constexpr auto dstPtr_kind = local;
    [[maybe_unused]] constexpr auto srcPtr_kind = usm;
    Cal::Client::Icd::icdGlobalState.getPageFaultManager().moveAllocationToGpu(dstPtr, srcPtr);
    log<Verbosity::bloat>("Establishing RPC for clEnqueueMemcpyINTEL_Local_Usm");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    void *standalone_dstPtr{};
    {
        std::unique_ptr<void, std::function<void(void*)>> standalone_dstPtr_alloc(static_cast<IcdOclCommandQueue *>(command_queue)->context->getStagingAreaManager().allocateStagingArea(size), [command_queue](void *ptrToMarkAsUnused){static_cast<IcdOclCommandQueue *>(command_queue)->context->getStagingAreaManager().releaseStagingArea(ptrToMarkAsUnused);});
        standalone_dstPtr = standalone_dstPtr_alloc.get();
        command_queue->asLocalObject()->registerTemporaryAllocation(std::move(standalone_dstPtr_alloc));
    }
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueMemcpyINTEL_Local_UsmRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, blocking, dstPtr, srcPtr, size, num_events_in_wait_list, event_wait_list, event);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, blocking, dstPtr, srcPtr, size, num_events_in_wait_list, event_wait_list, event);
    command->copyFromCaller(dynMemTraits);
    command->args.dstPtr = reinterpret_cast<void*>(standalone_dstPtr);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    Cal::Client::Icd::Ocl::warnIfNonBlockingRead(command->args.blocking, dstPtr_kind);
    if(event_wait_list)
    {
        auto base = command->captures.event_wait_list;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !command->args.blocking &&
       !command->args.event &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         command_queue->asLocalObject()->enqueue();
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
    memcpy(dstPtr, standalone_dstPtr, size);
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue);
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->synchronizeNow(command->args.blocking);
    command_queue->asLocalObject()->enqueue();

    return ret;
}
cl_int clEnqueueMemcpyINTEL_Local_Shared (cl_command_queue command_queue, cl_bool blocking, void* dstPtr, const void* srcPtr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    [[maybe_unused]] constexpr auto dstPtr_kind = local;
    [[maybe_unused]] constexpr auto srcPtr_kind = shared;
    Cal::Client::Icd::icdGlobalState.getPageFaultManager().moveAllocationToGpu(dstPtr, srcPtr);
    log<Verbosity::bloat>("Establishing RPC for clEnqueueMemcpyINTEL_Local_Shared");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    void *standalone_dstPtr{};
    {
        std::unique_ptr<void, std::function<void(void*)>> standalone_dstPtr_alloc(static_cast<IcdOclCommandQueue *>(command_queue)->context->getStagingAreaManager().allocateStagingArea(size), [command_queue](void *ptrToMarkAsUnused){static_cast<IcdOclCommandQueue *>(command_queue)->context->getStagingAreaManager().releaseStagingArea(ptrToMarkAsUnused);});
        standalone_dstPtr = standalone_dstPtr_alloc.get();
        command_queue->asLocalObject()->registerTemporaryAllocation(std::move(standalone_dstPtr_alloc));
    }
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueMemcpyINTEL_Local_SharedRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, blocking, dstPtr, srcPtr, size, num_events_in_wait_list, event_wait_list, event);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, blocking, dstPtr, srcPtr, size, num_events_in_wait_list, event_wait_list, event);
    command->copyFromCaller(dynMemTraits);
    command->args.dstPtr = reinterpret_cast<void*>(standalone_dstPtr);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    Cal::Client::Icd::Ocl::warnIfNonBlockingRead(command->args.blocking, dstPtr_kind);
    if(event_wait_list)
    {
        auto base = command->captures.event_wait_list;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !command->args.blocking &&
       !command->args.event &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         command_queue->asLocalObject()->enqueue();
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
    memcpy(dstPtr, standalone_dstPtr, size);
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue);
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->synchronizeNow(command->args.blocking);
    command_queue->asLocalObject()->enqueue();

    return ret;
}
cl_int clEnqueueMemcpyINTEL_Usm_Local (cl_command_queue command_queue, cl_bool blocking, void* dstPtr, const void* srcPtr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    [[maybe_unused]] constexpr auto dstPtr_kind = usm;
    [[maybe_unused]] constexpr auto srcPtr_kind = local;
    Cal::Client::Icd::icdGlobalState.getPageFaultManager().moveAllocationToGpu(dstPtr, srcPtr);
    log<Verbosity::bloat>("Establishing RPC for clEnqueueMemcpyINTEL_Usm_Local");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    void *standalone_srcPtr{};
    {
        std::unique_ptr<void, std::function<void(void*)>> standalone_srcPtr_alloc(static_cast<IcdOclCommandQueue *>(command_queue)->context->getStagingAreaManager().allocateStagingArea(size), [command_queue](void *ptrToMarkAsUnused){static_cast<IcdOclCommandQueue *>(command_queue)->context->getStagingAreaManager().releaseStagingArea(ptrToMarkAsUnused);});
        standalone_srcPtr = standalone_srcPtr_alloc.get();
        command_queue->asLocalObject()->registerTemporaryAllocation(std::move(standalone_srcPtr_alloc));
    }
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueMemcpyINTEL_Usm_LocalRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, blocking, dstPtr, srcPtr, size, num_events_in_wait_list, event_wait_list, event);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, blocking, dstPtr, srcPtr, size, num_events_in_wait_list, event_wait_list, event);
    memcpy(Cal::Utils::toAddress(standalone_srcPtr), srcPtr, size);
    command->copyFromCaller(dynMemTraits);
    command->args.srcPtr = reinterpret_cast<const void*>(standalone_srcPtr);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    Cal::Client::Icd::Ocl::warnIfNonBlockingRead(command->args.blocking, dstPtr_kind);
    if(event_wait_list)
    {
        auto base = command->captures.event_wait_list;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !command->args.blocking &&
       !command->args.event &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         command_queue->asLocalObject()->enqueue();
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
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue);
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->synchronizeNow(command->args.blocking);
    command_queue->asLocalObject()->enqueue();

    return ret;
}
cl_int clEnqueueMemcpyINTEL_Usm_Usm (cl_command_queue command_queue, cl_bool blocking, void* dstPtr, const void* srcPtr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    [[maybe_unused]] constexpr auto dstPtr_kind = usm;
    [[maybe_unused]] constexpr auto srcPtr_kind = usm;
    Cal::Client::Icd::icdGlobalState.getPageFaultManager().moveAllocationToGpu(dstPtr, srcPtr);
    log<Verbosity::bloat>("Establishing RPC for clEnqueueMemcpyINTEL_Usm_Usm");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueMemcpyINTEL_Usm_UsmRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, blocking, dstPtr, srcPtr, size, num_events_in_wait_list, event_wait_list, event);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, blocking, dstPtr, srcPtr, size, num_events_in_wait_list, event_wait_list, event);
    command->copyFromCaller(dynMemTraits);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    Cal::Client::Icd::Ocl::warnIfNonBlockingRead(command->args.blocking, dstPtr_kind);
    if(event_wait_list)
    {
        auto base = command->captures.event_wait_list;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !command->args.blocking &&
       !command->args.event &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         command_queue->asLocalObject()->enqueue();
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
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue);
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->synchronizeNow(command->args.blocking);
    command_queue->asLocalObject()->enqueue();

    return ret;
}
cl_int clEnqueueMemcpyINTEL_Usm_Shared (cl_command_queue command_queue, cl_bool blocking, void* dstPtr, const void* srcPtr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    [[maybe_unused]] constexpr auto dstPtr_kind = usm;
    [[maybe_unused]] constexpr auto srcPtr_kind = shared;
    Cal::Client::Icd::icdGlobalState.getPageFaultManager().moveAllocationToGpu(dstPtr, srcPtr);
    log<Verbosity::bloat>("Establishing RPC for clEnqueueMemcpyINTEL_Usm_Shared");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueMemcpyINTEL_Usm_SharedRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, blocking, dstPtr, srcPtr, size, num_events_in_wait_list, event_wait_list, event);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, blocking, dstPtr, srcPtr, size, num_events_in_wait_list, event_wait_list, event);
    command->copyFromCaller(dynMemTraits);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    Cal::Client::Icd::Ocl::warnIfNonBlockingRead(command->args.blocking, dstPtr_kind);
    if(event_wait_list)
    {
        auto base = command->captures.event_wait_list;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !command->args.blocking &&
       !command->args.event &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         command_queue->asLocalObject()->enqueue();
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
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue);
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->synchronizeNow(command->args.blocking);
    command_queue->asLocalObject()->enqueue();

    return ret;
}
cl_int clEnqueueMemcpyINTEL_Shared_Local (cl_command_queue command_queue, cl_bool blocking, void* dstPtr, const void* srcPtr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    [[maybe_unused]] constexpr auto dstPtr_kind = shared;
    [[maybe_unused]] constexpr auto srcPtr_kind = local;
    Cal::Client::Icd::icdGlobalState.getPageFaultManager().moveAllocationToGpu(dstPtr, srcPtr);
    log<Verbosity::bloat>("Establishing RPC for clEnqueueMemcpyINTEL_Shared_Local");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    void *standalone_srcPtr{};
    {
        std::unique_ptr<void, std::function<void(void*)>> standalone_srcPtr_alloc(static_cast<IcdOclCommandQueue *>(command_queue)->context->getStagingAreaManager().allocateStagingArea(size), [command_queue](void *ptrToMarkAsUnused){static_cast<IcdOclCommandQueue *>(command_queue)->context->getStagingAreaManager().releaseStagingArea(ptrToMarkAsUnused);});
        standalone_srcPtr = standalone_srcPtr_alloc.get();
        command_queue->asLocalObject()->registerTemporaryAllocation(std::move(standalone_srcPtr_alloc));
    }
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueMemcpyINTEL_Shared_LocalRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, blocking, dstPtr, srcPtr, size, num_events_in_wait_list, event_wait_list, event);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, blocking, dstPtr, srcPtr, size, num_events_in_wait_list, event_wait_list, event);
    memcpy(Cal::Utils::toAddress(standalone_srcPtr), srcPtr, size);
    command->copyFromCaller(dynMemTraits);
    command->args.srcPtr = reinterpret_cast<const void*>(standalone_srcPtr);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    Cal::Client::Icd::Ocl::warnIfNonBlockingRead(command->args.blocking, dstPtr_kind);
    if(event_wait_list)
    {
        auto base = command->captures.event_wait_list;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !command->args.blocking &&
       !command->args.event &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         command_queue->asLocalObject()->enqueue();
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
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue);
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->synchronizeNow(command->args.blocking);
    command_queue->asLocalObject()->enqueue();

    return ret;
}
cl_int clEnqueueMemcpyINTEL_Shared_Usm (cl_command_queue command_queue, cl_bool blocking, void* dstPtr, const void* srcPtr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    [[maybe_unused]] constexpr auto dstPtr_kind = shared;
    [[maybe_unused]] constexpr auto srcPtr_kind = usm;
    Cal::Client::Icd::icdGlobalState.getPageFaultManager().moveAllocationToGpu(dstPtr, srcPtr);
    log<Verbosity::bloat>("Establishing RPC for clEnqueueMemcpyINTEL_Shared_Usm");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueMemcpyINTEL_Shared_UsmRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, blocking, dstPtr, srcPtr, size, num_events_in_wait_list, event_wait_list, event);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, blocking, dstPtr, srcPtr, size, num_events_in_wait_list, event_wait_list, event);
    command->copyFromCaller(dynMemTraits);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    Cal::Client::Icd::Ocl::warnIfNonBlockingRead(command->args.blocking, dstPtr_kind);
    if(event_wait_list)
    {
        auto base = command->captures.event_wait_list;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !command->args.blocking &&
       !command->args.event &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         command_queue->asLocalObject()->enqueue();
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
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue);
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->synchronizeNow(command->args.blocking);
    command_queue->asLocalObject()->enqueue();

    return ret;
}
cl_int clEnqueueMemcpyINTEL_Shared_Shared (cl_command_queue command_queue, cl_bool blocking, void* dstPtr, const void* srcPtr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    [[maybe_unused]] constexpr auto dstPtr_kind = shared;
    [[maybe_unused]] constexpr auto srcPtr_kind = shared;
    Cal::Client::Icd::icdGlobalState.getPageFaultManager().moveAllocationToGpu(dstPtr, srcPtr);
    log<Verbosity::bloat>("Establishing RPC for clEnqueueMemcpyINTEL_Shared_Shared");
    auto *globalPlatform = Cal::Client::Icd::icdGlobalState.getOclPlatform();
    auto &channel = globalPlatform->getRpcChannel();
    auto channelLock = channel.lock();
    using CommandT = Cal::Rpc::Ocl::ClEnqueueMemcpyINTEL_Shared_SharedRpcM;
    const auto dynMemTraits = CommandT::Captures::DynamicTraits::calculate(command_queue, blocking, dstPtr, srcPtr, size, num_events_in_wait_list, event_wait_list, event);
    auto commandSpace = channel.getCmdSpace<CommandT>(dynMemTraits.totalDynamicSize);
    auto command = new(commandSpace) CommandT(dynMemTraits, command_queue, blocking, dstPtr, srcPtr, size, num_events_in_wait_list, event_wait_list, event);
    command->copyFromCaller(dynMemTraits);
    command->args.command_queue = command_queue->asLocalObject()->asRemoteObject();
    Cal::Client::Icd::Ocl::warnIfNonBlockingRead(command->args.blocking, dstPtr_kind);
    if(event_wait_list)
    {
        auto base = command->captures.event_wait_list;
        auto baseMutable = mutable_element_cast(base);
        auto numEntries = dynMemTraits.event_wait_list.count;

        for(size_t i = 0; i < numEntries; ++i){
            baseMutable[i] = baseMutable[i]->asLocalObject()->asRemoteObject();
        }
    }

    if(
       !command->args.blocking &&
       !command->args.event &&
       channel.isCallAsyncEnabled()){
         command->header.flags |= Cal::Rpc::RpcMessageHeader::async;
         channel.callAsynchronous(command);
         command_queue->asLocalObject()->enqueue();
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
    if(event)
    {
        event[0] = globalPlatform->translateNewRemoteObjectToLocalObject(event[0], command_queue);
    }
    cl_int ret = command->captures.ret;

    channelLock.unlock();
    command_queue->asLocalObject()->synchronizeNow(command->args.blocking);
    command_queue->asLocalObject()->enqueue();

    return ret;
}

void *getOclExtensionFuncionAddressRpcHelper(const char *funcName) {
    if(0 == strcmp("clCreateSubDevicesEXT", funcName)) {
        return reinterpret_cast<void*>(Cal::Client::Icd::Ocl::clCreateSubDevicesEXT);
    }
    if(0 == strcmp("clReleaseDeviceEXT", funcName)) {
        return reinterpret_cast<void*>(Cal::Client::Icd::Ocl::clReleaseDeviceEXT);
    }
    if(0 == strcmp("clRetainDeviceEXT", funcName)) {
        return reinterpret_cast<void*>(Cal::Client::Icd::Ocl::clRetainDeviceEXT);
    }
    if(0 == strcmp("clGetKernelSubGroupInfoKHR", funcName)) {
        return reinterpret_cast<void*>(Cal::Client::Icd::Ocl::clGetKernelSubGroupInfoKHR);
    }
    if(0 == strcmp("clGetKernelSuggestedLocalWorkSizeKHR", funcName)) {
        return reinterpret_cast<void*>(Cal::Client::Icd::Ocl::clGetKernelSuggestedLocalWorkSizeKHR);
    }
    if(0 == strcmp("clCreateCommandQueueWithPropertiesKHR", funcName)) {
        return reinterpret_cast<void*>(Cal::Client::Icd::Ocl::clCreateCommandQueueWithPropertiesKHR);
    }
    if(0 == strcmp("clEnqueueMemFillINTEL", funcName)) {
        return reinterpret_cast<void*>(Cal::Client::Icd::Ocl::clEnqueueMemFillINTEL);
    }
    if(0 == strcmp("clEnqueueMemcpyINTEL", funcName)) {
        return reinterpret_cast<void*>(Cal::Client::Icd::Ocl::clEnqueueMemcpyINTEL);
    }
    if(0 == strcmp("clSetKernelArgMemPointerINTEL", funcName)) {
        return reinterpret_cast<void*>(Cal::Client::Icd::Ocl::clSetKernelArgMemPointerINTEL);
    }
    if(0 == strcmp("clGetMemAllocInfoINTEL", funcName)) {
        return reinterpret_cast<void*>(Cal::Client::Icd::Ocl::clGetMemAllocInfoINTEL);
    }
    if(0 == strcmp("clDeviceMemAllocINTEL", funcName)) {
        return reinterpret_cast<void*>(Cal::Client::Icd::Ocl::clDeviceMemAllocINTEL);
    }
    if(0 == strcmp("clHostMemAllocINTEL", funcName)) {
        return reinterpret_cast<void*>(Cal::Client::Icd::Ocl::clHostMemAllocINTEL);
    }
    if(0 == strcmp("clSharedMemAllocINTEL", funcName)) {
        return reinterpret_cast<void*>(Cal::Client::Icd::Ocl::clSharedMemAllocINTEL);
    }
    if(0 == strcmp("clMemFreeINTEL", funcName)) {
        return reinterpret_cast<void*>(Cal::Client::Icd::Ocl::clMemFreeINTEL);
    }
    if(0 == strcmp("clMemBlockingFreeINTEL", funcName)) {
        return reinterpret_cast<void*>(Cal::Client::Icd::Ocl::clMemBlockingFreeINTEL);
    }
    if(0 == strcmp("clEnqueueMigrateMemINTEL", funcName)) {
        return reinterpret_cast<void*>(Cal::Client::Icd::Ocl::clEnqueueMigrateMemINTEL);
    }
    if(0 == strcmp("clGetDeviceGlobalVariablePointerINTEL", funcName)) {
        return reinterpret_cast<void*>(Cal::Client::Icd::Ocl::clGetDeviceGlobalVariablePointerINTEL);
    }
    return nullptr;
}


} // namespace Ocl
} // namespace Icd
} // namespace Client
} // namespace Cal


extern "C" {
cl_int clGetPlatformIDs (cl_uint num_entries, cl_platform_id* platforms, cl_uint* num_platforms) {
    return Cal::Client::Icd::Ocl::clGetPlatformIDs(num_entries, platforms, num_platforms);
}
cl_int clIcdGetPlatformIDsKHR (cl_uint num_entries, cl_platform_id* platforms, cl_uint* num_platforms) {
    return Cal::Client::Icd::Ocl::clIcdGetPlatformIDsKHR(num_entries, platforms, num_platforms);
}
cl_int clGetPlatformInfo (cl_platform_id platform, cl_platform_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    return Cal::Client::Icd::Ocl::clGetPlatformInfo(platform, param_name, param_value_size, param_value, param_value_size_ret);
}
void* clGetExtensionFunctionAddress (const char* funcname) {
    return Cal::Client::Icd::Ocl::clGetExtensionFunctionAddress(funcname);
}
cl_int clGetDeviceIDs (cl_platform_id platform, cl_device_type device_type, cl_uint num_entries, cl_device_id* devices, cl_uint* num_devices) {
    return Cal::Client::Icd::Ocl::clGetDeviceIDs(platform, device_type, num_entries, devices, num_devices);
}
cl_int clGetDeviceInfo (cl_device_id device, cl_device_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    return Cal::Client::Icd::Ocl::clGetDeviceInfo(device, param_name, param_value_size, param_value, param_value_size_ret);
}
cl_context clCreateContext (const cl_context_properties* properties, cl_uint num_devices, const cl_device_id* devices, void (CL_CALLBACK* pfn_notify)(const char* errinfo, const void* private_info, size_t cb, void* user_data), void* user_data, cl_int* errcode_ret) {
    return Cal::Client::Icd::Ocl::clCreateContext(properties, num_devices, devices, pfn_notify, user_data, errcode_ret);
}
cl_context clCreateContextFromType (const cl_context_properties* properties, cl_device_type device_type, void (CL_CALLBACK* pfn_notify)(const char* errinfo, const void* private_info, size_t cb, void* user_data), void* user_data, cl_int* errcode_ret) {
    return Cal::Client::Icd::Ocl::clCreateContextFromType(properties, device_type, pfn_notify, user_data, errcode_ret);
}
cl_int clGetContextInfo (cl_context context, cl_context_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    return Cal::Client::Icd::Ocl::clGetContextInfo(context, param_name, param_value_size, param_value, param_value_size_ret);
}
cl_int clSetContextDestructorCallback (cl_context context, void (CL_CALLBACK* pfn_notify)(cl_context context, void* user_data), void* user_data) {
    return Cal::Client::Icd::Ocl::clSetContextDestructorCallback(context, pfn_notify, user_data);
}
cl_int clSetMemObjectDestructorCallback (cl_mem memobj, void (CL_CALLBACK* pfn_notify)(cl_mem memobj, void* user_data), void* user_data) {
    return Cal::Client::Icd::Ocl::clSetMemObjectDestructorCallback(memobj, pfn_notify, user_data);
}
cl_int clCreateSubDevices (cl_device_id in_device, const cl_device_partition_property* properties, cl_uint num_devices, cl_device_id* out_devices, cl_uint* num_devices_ret) {
    return Cal::Client::Icd::Ocl::clCreateSubDevices(in_device, properties, num_devices, out_devices, num_devices_ret);
}
cl_command_queue clCreateCommandQueue (cl_context context, cl_device_id device, cl_command_queue_properties  properties, cl_int* errcode_ret) {
    return Cal::Client::Icd::Ocl::clCreateCommandQueue(context, device, properties, errcode_ret);
}
cl_int clSetDefaultDeviceCommandQueue (cl_context context, cl_device_id device, cl_command_queue command_queue) {
    return Cal::Client::Icd::Ocl::clSetDefaultDeviceCommandQueue(context, device, command_queue);
}
cl_command_queue clCreateCommandQueueWithProperties (cl_context context, cl_device_id device, const cl_queue_properties* properties, cl_int* errcode_ret) {
    return Cal::Client::Icd::Ocl::clCreateCommandQueueWithProperties(context, device, properties, errcode_ret);
}
cl_program clCreateProgramWithSource (cl_context context, cl_uint count, const char** strings, const size_t* lengths, cl_int* errcode_ret) {
    return Cal::Client::Icd::Ocl::clCreateProgramWithSource(context, count, strings, lengths, errcode_ret);
}
cl_program clCreateProgramWithIL (cl_context context, const void* il, size_t length, cl_int* errcode_ret) {
    return Cal::Client::Icd::Ocl::clCreateProgramWithIL(context, il, length, errcode_ret);
}
cl_program clCreateProgramWithBinary (cl_context context, cl_uint num_devices, const cl_device_id* device_list, const size_t* lengths, const unsigned char** binaries, cl_int* binary_status, cl_int* errcode_ret) {
    return Cal::Client::Icd::Ocl::clCreateProgramWithBinary(context, num_devices, device_list, lengths, binaries, binary_status, errcode_ret);
}
cl_program clCreateProgramWithBuiltInKernels (cl_context context, cl_uint num_devices, const cl_device_id* device_list, const char* kernel_names, cl_int* errcode_ret) {
    return Cal::Client::Icd::Ocl::clCreateProgramWithBuiltInKernels(context, num_devices, device_list, kernel_names, errcode_ret);
}
cl_int clUnloadCompiler () {
    return Cal::Client::Icd::Ocl::clUnloadCompiler();
}
cl_int clUnloadPlatformCompiler (cl_platform_id platform) {
    return Cal::Client::Icd::Ocl::clUnloadPlatformCompiler(platform);
}
cl_int clBuildProgram (cl_program program, cl_uint num_devices, const cl_device_id* device_list, const char* options, void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data), void* user_data) {
    return Cal::Client::Icd::Ocl::clBuildProgram(program, num_devices, device_list, options, pfn_notify, user_data);
}
cl_int clCompileProgram (cl_program program, cl_uint num_devices, const cl_device_id* device_list, const char* options, cl_uint num_input_headers, const cl_program* input_headers, const char** header_include_names, void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data), void* user_data) {
    return Cal::Client::Icd::Ocl::clCompileProgram(program, num_devices, device_list, options, num_input_headers, input_headers, header_include_names, pfn_notify, user_data);
}
cl_program clLinkProgram (cl_context context, cl_uint num_devices, const cl_device_id* device_list, const char* options, cl_uint num_input_programs, const cl_program* input_programs, void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data), void* user_data, cl_int* errcode_ret) {
    return Cal::Client::Icd::Ocl::clLinkProgram(context, num_devices, device_list, options, num_input_programs, input_programs, pfn_notify, user_data, errcode_ret);
}
cl_int clGetProgramBuildInfo (cl_program program, cl_device_id device, cl_program_build_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    return Cal::Client::Icd::Ocl::clGetProgramBuildInfo(program, device, param_name, param_value_size, param_value, param_value_size_ret);
}
cl_int clSetProgramReleaseCallback (cl_program program, void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data), void* user_data) {
    return Cal::Client::Icd::Ocl::clSetProgramReleaseCallback(program, pfn_notify, user_data);
}
cl_kernel clCreateKernel (cl_program program, const char* kernel_name, cl_int* errcode_ret) {
    return Cal::Client::Icd::Ocl::clCreateKernel(program, kernel_name, errcode_ret);
}
cl_kernel clCloneKernel (cl_kernel source_kernel, cl_int* errcode_ret) {
    return Cal::Client::Icd::Ocl::clCloneKernel(source_kernel, errcode_ret);
}
cl_int clCreateKernelsInProgram (cl_program program, cl_uint num_kernels, cl_kernel* kernels, cl_uint* num_kernels_ret) {
    return Cal::Client::Icd::Ocl::clCreateKernelsInProgram(program, num_kernels, kernels, num_kernels_ret);
}
cl_int clGetCommandQueueInfo (cl_command_queue command_queue, cl_command_queue_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    return Cal::Client::Icd::Ocl::clGetCommandQueueInfo(command_queue, param_name, param_value_size, param_value, param_value_size_ret);
}
cl_int clGetProgramInfo (cl_program program, cl_program_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    return Cal::Client::Icd::Ocl::clGetProgramInfo(program, param_name, param_value_size, param_value, param_value_size_ret);
}
cl_int clGetMemObjectInfo (cl_mem memobj, cl_mem_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    return Cal::Client::Icd::Ocl::clGetMemObjectInfo(memobj, param_name, param_value_size, param_value, param_value_size_ret);
}
cl_int clGetImageInfo (cl_mem image, cl_image_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    return Cal::Client::Icd::Ocl::clGetImageInfo(image, param_name, param_value_size, param_value, param_value_size_ret);
}
cl_int clGetSamplerInfo (cl_sampler sampler, cl_sampler_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    return Cal::Client::Icd::Ocl::clGetSamplerInfo(sampler, param_name, param_value_size, param_value, param_value_size_ret);
}
cl_int clGetKernelInfo (cl_kernel kernel, cl_kernel_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    return Cal::Client::Icd::Ocl::clGetKernelInfo(kernel, param_name, param_value_size, param_value, param_value_size_ret);
}
cl_int clGetKernelWorkGroupInfo (cl_kernel kernel, cl_device_id device, cl_kernel_work_group_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    return Cal::Client::Icd::Ocl::clGetKernelWorkGroupInfo(kernel, device, param_name, param_value_size, param_value, param_value_size_ret);
}
cl_int clGetKernelArgInfo (cl_kernel kernel, cl_uint arg_indx, cl_kernel_arg_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    return Cal::Client::Icd::Ocl::clGetKernelArgInfo(kernel, arg_indx, param_name, param_value_size, param_value, param_value_size_ret);
}
cl_int clGetKernelSubGroupInfo (cl_kernel kernel, cl_device_id device, cl_kernel_sub_group_info param_name, size_t input_value_size, const void* input_value, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    return Cal::Client::Icd::Ocl::clGetKernelSubGroupInfo(kernel, device, param_name, input_value_size, input_value, param_value_size, param_value, param_value_size_ret);
}
cl_int clReleaseCommandQueue (cl_command_queue command_queue) {
    return Cal::Client::Icd::Ocl::clReleaseCommandQueue(command_queue);
}
cl_int clReleaseContext (cl_context context) {
    return Cal::Client::Icd::Ocl::clReleaseContext(context);
}
cl_int clReleaseDevice (cl_device_id device) {
    return Cal::Client::Icd::Ocl::clReleaseDevice(device);
}
cl_int clReleaseKernel (cl_kernel kernel) {
    return Cal::Client::Icd::Ocl::clReleaseKernel(kernel);
}
cl_int clReleaseSampler (cl_sampler sampler) {
    return Cal::Client::Icd::Ocl::clReleaseSampler(sampler);
}
cl_int clReleaseProgram (cl_program program) {
    return Cal::Client::Icd::Ocl::clReleaseProgram(program);
}
cl_int clReleaseMemObject (cl_mem memobj) {
    return Cal::Client::Icd::Ocl::clReleaseMemObject(memobj);
}
cl_int clReleaseEvent (cl_event event) {
    return Cal::Client::Icd::Ocl::clReleaseEvent(event);
}
cl_int clRetainCommandQueue (cl_command_queue command_queue) {
    return Cal::Client::Icd::Ocl::clRetainCommandQueue(command_queue);
}
cl_int clRetainContext (cl_context context) {
    return Cal::Client::Icd::Ocl::clRetainContext(context);
}
cl_int clRetainDevice (cl_device_id device) {
    return Cal::Client::Icd::Ocl::clRetainDevice(device);
}
cl_int clRetainProgram (cl_program program) {
    return Cal::Client::Icd::Ocl::clRetainProgram(program);
}
cl_int clRetainMemObject (cl_mem memobj) {
    return Cal::Client::Icd::Ocl::clRetainMemObject(memobj);
}
cl_int clRetainSampler (cl_sampler sampler) {
    return Cal::Client::Icd::Ocl::clRetainSampler(sampler);
}
cl_int clRetainKernel (cl_kernel kernel) {
    return Cal::Client::Icd::Ocl::clRetainKernel(kernel);
}
cl_int clRetainEvent (cl_event event) {
    return Cal::Client::Icd::Ocl::clRetainEvent(event);
}
cl_int clFlush (cl_command_queue command_queue) {
    return Cal::Client::Icd::Ocl::clFlush(command_queue);
}
cl_int clFinish (cl_command_queue command_queue) {
    return Cal::Client::Icd::Ocl::clFinish(command_queue);
}
cl_int clEnqueueNDRangeKernel (cl_command_queue command_queue, cl_kernel kernel, cl_uint work_dim, const size_t* global_work_offset, const size_t* global_work_size, const size_t* local_work_size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    return Cal::Client::Icd::Ocl::clEnqueueNDRangeKernel(command_queue, kernel, work_dim, global_work_offset, global_work_size, local_work_size, num_events_in_wait_list, event_wait_list, event);
}
cl_int clEnqueueTask (cl_command_queue command_queue, cl_kernel kernel, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    return Cal::Client::Icd::Ocl::clEnqueueTask(command_queue, kernel, num_events_in_wait_list, event_wait_list, event);
}
cl_int clEnqueueMarkerWithWaitList (cl_command_queue command_queue, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    return Cal::Client::Icd::Ocl::clEnqueueMarkerWithWaitList(command_queue, num_events_in_wait_list, event_wait_list, event);
}
cl_int clEnqueueMarker (cl_command_queue command_queue, cl_event* event) {
    return Cal::Client::Icd::Ocl::clEnqueueMarker(command_queue, event);
}
cl_int clEnqueueBarrierWithWaitList (cl_command_queue command_queue, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    return Cal::Client::Icd::Ocl::clEnqueueBarrierWithWaitList(command_queue, num_events_in_wait_list, event_wait_list, event);
}
cl_int clEnqueueBarrier (cl_command_queue command_queue) {
    return Cal::Client::Icd::Ocl::clEnqueueBarrier(command_queue);
}
cl_int clEnqueueWaitForEvents (cl_command_queue command_queue, cl_uint num_events, const cl_event* event_list) {
    return Cal::Client::Icd::Ocl::clEnqueueWaitForEvents(command_queue, num_events, event_list);
}
cl_int clEnqueueMigrateMemObjects (cl_command_queue command_queue, cl_uint num_mem_objects, const cl_mem* mem_objects, cl_mem_migration_flags flags, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    return Cal::Client::Icd::Ocl::clEnqueueMigrateMemObjects(command_queue, num_mem_objects, mem_objects, flags, num_events_in_wait_list, event_wait_list, event);
}
void* clGetExtensionFunctionAddressForPlatform (cl_platform_id platform, const char* funcname) {
    return Cal::Client::Icd::Ocl::clGetExtensionFunctionAddressForPlatform(platform, funcname);
}
cl_mem clCreateBuffer (cl_context context, cl_mem_flags flags, size_t size, void* host_ptr, cl_int* errcode_ret) {
    return Cal::Client::Icd::Ocl::clCreateBuffer(context, flags, size, host_ptr, errcode_ret);
}
cl_mem clCreateSubBuffer (cl_mem buffer, cl_mem_flags flags, cl_buffer_create_type buffer_create_type, const void* buffer_create_info, cl_int* errcode_ret) {
    return Cal::Client::Icd::Ocl::clCreateSubBuffer(buffer, flags, buffer_create_type, buffer_create_info, errcode_ret);
}
cl_mem clCreatePipe (cl_context context, cl_mem_flags flags, cl_uint pipe_packet_size, cl_uint pipe_max_packets, const cl_pipe_properties* properties, cl_int* errcode_ret) {
    return Cal::Client::Icd::Ocl::clCreatePipe(context, flags, pipe_packet_size, pipe_max_packets, properties, errcode_ret);
}
cl_int clGetPipeInfo (cl_mem pipe, cl_pipe_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    return Cal::Client::Icd::Ocl::clGetPipeInfo(pipe, param_name, param_value_size, param_value, param_value_size_ret);
}
cl_mem clCreateImage (cl_context context, cl_mem_flags flags, const cl_image_format* image_format, const cl_image_desc* image_desc, void* host_ptr, cl_int* errcode_ret) {
    return Cal::Client::Icd::Ocl::clCreateImage(context, flags, image_format, image_desc, host_ptr, errcode_ret);
}
cl_mem clCreateImage2D (cl_context context, cl_mem_flags flags, const cl_image_format* image_format, size_t image_width, size_t image_height, size_t image_row_pitch, void* host_ptr, cl_int* errcode_ret) {
    return Cal::Client::Icd::Ocl::clCreateImage2D(context, flags, image_format, image_width, image_height, image_row_pitch, host_ptr, errcode_ret);
}
cl_mem clCreateImage3D (cl_context context, cl_mem_flags flags, const cl_image_format* image_format, size_t image_width, size_t image_height, size_t image_depth, size_t image_row_pitch, size_t image_slice_pitch, void* host_ptr, cl_int* errcode_ret) {
    return Cal::Client::Icd::Ocl::clCreateImage3D(context, flags, image_format, image_width, image_height, image_depth, image_row_pitch, image_slice_pitch, host_ptr, errcode_ret);
}
cl_sampler clCreateSampler (cl_context context, cl_bool normalized_coords, cl_addressing_mode addressing_mode, cl_filter_mode filter_mode, cl_int* errcode_ret) {
    return Cal::Client::Icd::Ocl::clCreateSampler(context, normalized_coords, addressing_mode, filter_mode, errcode_ret);
}
cl_sampler clCreateSamplerWithProperties (cl_context context, const cl_sampler_properties* properties, cl_int* errcode_ret) {
    return Cal::Client::Icd::Ocl::clCreateSamplerWithProperties(context, properties, errcode_ret);
}
cl_mem clCreateImageWithProperties (cl_context context, const cl_mem_properties* properties, cl_mem_flags flags, const cl_image_format* image_format, const cl_image_desc* image_desc, void* host_ptr, cl_int* errcode_ret) {
    return Cal::Client::Icd::Ocl::clCreateImageWithProperties(context, properties, flags, image_format, image_desc, host_ptr, errcode_ret);
}
cl_mem clCreateBufferWithProperties (cl_context context, const cl_mem_properties* properties, cl_mem_flags flags, size_t size, void* host_ptr, cl_int* errcode_ret) {
    return Cal::Client::Icd::Ocl::clCreateBufferWithProperties(context, properties, flags, size, host_ptr, errcode_ret);
}
cl_int clGetSupportedImageFormats (cl_context context, cl_mem_flags flags, cl_mem_object_type image_type, cl_uint num_entries, cl_image_format* image_formats, cl_uint* num_image_formats) {
    return Cal::Client::Icd::Ocl::clGetSupportedImageFormats(context, flags, image_type, num_entries, image_formats, num_image_formats);
}
cl_int clSetKernelArg (cl_kernel kernel, cl_uint arg_index, size_t arg_size, const void* arg_value) {
    return Cal::Client::Icd::Ocl::clSetKernelArg(kernel, arg_index, arg_size, arg_value);
}
cl_int clSetProgramSpecializationConstant (cl_program program, cl_uint spec_id, size_t spec_size, const void* spec_value) {
    return Cal::Client::Icd::Ocl::clSetProgramSpecializationConstant(program, spec_id, spec_size, spec_value);
}
cl_int clEnqueueWriteBuffer (cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, size_t offset, size_t size, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    return Cal::Client::Icd::Ocl::clEnqueueWriteBuffer(command_queue, buffer, blocking_write, offset, size, ptr, num_events_in_wait_list, event_wait_list, event);
}
cl_int clEnqueueWriteBufferRect (cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, const size_t* buffer_origin, const size_t* host_origin, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    return Cal::Client::Icd::Ocl::clEnqueueWriteBufferRect(command_queue, buffer, blocking_write, buffer_origin, host_origin, region, buffer_row_pitch, buffer_slice_pitch, host_row_pitch, host_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event);
}
cl_int clEnqueueReadBuffer (cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, size_t offset, size_t size, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    return Cal::Client::Icd::Ocl::clEnqueueReadBuffer(command_queue, buffer, blocking_read, offset, size, ptr, num_events_in_wait_list, event_wait_list, event);
}
cl_int clEnqueueReadBufferRect (cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, const size_t* buffer_origin, const size_t* host_origin, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    return Cal::Client::Icd::Ocl::clEnqueueReadBufferRect(command_queue, buffer, blocking_read, buffer_origin, host_origin, region, buffer_row_pitch, buffer_slice_pitch, host_row_pitch, host_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event);
}
cl_int clEnqueueCopyBuffer (cl_command_queue command_queue, cl_mem src_buffer, cl_mem dst_buffer, size_t src_offset, size_t dst_offset, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    return Cal::Client::Icd::Ocl::clEnqueueCopyBuffer(command_queue, src_buffer, dst_buffer, src_offset, dst_offset, size, num_events_in_wait_list, event_wait_list, event);
}
cl_int clEnqueueCopyBufferRect (cl_command_queue command_queue, cl_mem src_buffer, cl_mem dst_buffer, const size_t* src_origin, const size_t* dst_origin, const size_t* region, size_t src_row_pitch, size_t src_slice_pitch, size_t dst_row_pitch, size_t dst_slice_pitch, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    return Cal::Client::Icd::Ocl::clEnqueueCopyBufferRect(command_queue, src_buffer, dst_buffer, src_origin, dst_origin, region, src_row_pitch, src_slice_pitch, dst_row_pitch, dst_slice_pitch, num_events_in_wait_list, event_wait_list, event);
}
cl_int clEnqueueReadImage (cl_command_queue command_queue, cl_mem image, cl_bool blocking_read, const size_t* src_origin, const size_t* region, size_t row_pitch, size_t slice_pitch, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    return Cal::Client::Icd::Ocl::clEnqueueReadImage(command_queue, image, blocking_read, src_origin, region, row_pitch, slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event);
}
cl_int clEnqueueWriteImage (cl_command_queue command_queue, cl_mem image, cl_bool blocking_write, const size_t* origin, const size_t* region, size_t input_row_pitch, size_t input_slice_pitch, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    return Cal::Client::Icd::Ocl::clEnqueueWriteImage(command_queue, image, blocking_write, origin, region, input_row_pitch, input_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event);
}
cl_int clEnqueueCopyImage (cl_command_queue command_queue, cl_mem src_image, cl_mem dst_image, const size_t* src_origin, const size_t* dst_origin, const size_t* region, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    return Cal::Client::Icd::Ocl::clEnqueueCopyImage(command_queue, src_image, dst_image, src_origin, dst_origin, region, num_events_in_wait_list, event_wait_list, event);
}
cl_int clEnqueueCopyImageToBuffer (cl_command_queue command_queue, cl_mem src_image, cl_mem dst_buffer, const size_t* src_origin, const size_t* region, size_t dst_offset, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    return Cal::Client::Icd::Ocl::clEnqueueCopyImageToBuffer(command_queue, src_image, dst_buffer, src_origin, region, dst_offset, num_events_in_wait_list, event_wait_list, event);
}
cl_int clEnqueueCopyBufferToImage (cl_command_queue command_queue, cl_mem src_buffer, cl_mem dst_image, size_t src_offset, const size_t* dst_origin, const size_t* region, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    return Cal::Client::Icd::Ocl::clEnqueueCopyBufferToImage(command_queue, src_buffer, dst_image, src_offset, dst_origin, region, num_events_in_wait_list, event_wait_list, event);
}
void* clEnqueueMapBuffer (cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_map, cl_map_flags map_flags, size_t offset, size_t cb, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event, cl_int* errcode_ret) {
    return Cal::Client::Icd::Ocl::clEnqueueMapBuffer(command_queue, buffer, blocking_map, map_flags, offset, cb, num_events_in_wait_list, event_wait_list, event, errcode_ret);
}
cl_int clEnqueueUnmapMemObject (cl_command_queue command_queue, cl_mem memobj, void* mapped_ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    return Cal::Client::Icd::Ocl::clEnqueueUnmapMemObject(command_queue, memobj, mapped_ptr, num_events_in_wait_list, event_wait_list, event);
}
cl_int clEnqueueFillBuffer (cl_command_queue command_queue, cl_mem memobj, const void* pattern, size_t patternSize, size_t offset, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    return Cal::Client::Icd::Ocl::clEnqueueFillBuffer(command_queue, memobj, pattern, patternSize, offset, size, num_events_in_wait_list, event_wait_list, event);
}
cl_int clEnqueueFillImage (cl_command_queue command_queue, cl_mem image, const void* fill_color, const size_t* origin, const size_t* region, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    return Cal::Client::Icd::Ocl::clEnqueueFillImage(command_queue, image, fill_color, origin, region, num_events_in_wait_list, event_wait_list, event);
}
cl_int clWaitForEvents (cl_uint num_events, const cl_event* event_list) {
    return Cal::Client::Icd::Ocl::clWaitForEvents(num_events, event_list);
}
cl_int clGetEventInfo (cl_event event, cl_event_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    return Cal::Client::Icd::Ocl::clGetEventInfo(event, param_name, param_value_size, param_value, param_value_size_ret);
}
cl_int clGetEventProfilingInfo (cl_event event, cl_profiling_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    return Cal::Client::Icd::Ocl::clGetEventProfilingInfo(event, param_name, param_value_size, param_value, param_value_size_ret);
}
cl_event clCreateUserEvent (cl_context context, cl_int* errcode_ret) {
    return Cal::Client::Icd::Ocl::clCreateUserEvent(context, errcode_ret);
}
cl_int clSetUserEventStatus (cl_event event, cl_int execution_status) {
    return Cal::Client::Icd::Ocl::clSetUserEventStatus(event, execution_status);
}
cl_int clSetEventCallback (cl_event event, cl_int command_exec_callback_type, void (CL_CALLBACK* pfn_notify)(cl_event event, cl_int event_command_status, void *user_data), void* user_data) {
    return Cal::Client::Icd::Ocl::clSetEventCallback(event, command_exec_callback_type, pfn_notify, user_data);
}
cl_int clGetDeviceAndHostTimer (cl_device_id device, cl_ulong* device_timestamp, cl_ulong* host_timestamp) {
    return Cal::Client::Icd::Ocl::clGetDeviceAndHostTimer(device, device_timestamp, host_timestamp);
}
cl_int clGetHostTimer (cl_device_id device, cl_ulong* host_timestamp) {
    return Cal::Client::Icd::Ocl::clGetHostTimer(device, host_timestamp);
}
void* clSVMAlloc (cl_context context, cl_svm_mem_flags flags, size_t size, cl_uint alignment) {
    return Cal::Client::Icd::Ocl::clSVMAlloc(context, flags, size, alignment);
}
void clSVMFree (cl_context context, void* ptr) {
    return Cal::Client::Icd::Ocl::clSVMFree(context, ptr);
}
cl_int clEnqueueSVMMap (cl_command_queue command_queue, cl_bool blocking_map, cl_map_flags map_flags, void* svm_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    return Cal::Client::Icd::Ocl::clEnqueueSVMMap(command_queue, blocking_map, map_flags, svm_ptr, size, num_events_in_wait_list, event_wait_list, event);
}
cl_int clEnqueueSVMUnmap (cl_command_queue command_queue, void* svm_ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    return Cal::Client::Icd::Ocl::clEnqueueSVMUnmap(command_queue, svm_ptr, num_events_in_wait_list, event_wait_list, event);
}
cl_int clSetKernelArgSVMPointer (cl_kernel kernel, cl_uint argIndex, const void* argValue) {
    return Cal::Client::Icd::Ocl::clSetKernelArgSVMPointer(kernel, argIndex, argValue);
}
cl_int clSetKernelExecInfo (cl_kernel kernel, cl_kernel_exec_info param_name, size_t param_value_size, const void* param_value) {
    return Cal::Client::Icd::Ocl::clSetKernelExecInfo(kernel, param_name, param_value_size, param_value);
}
cl_int clEnqueueSVMMemFill (cl_command_queue command_queue, void* svm_ptr, const void* pattern, size_t patternSize, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    return Cal::Client::Icd::Ocl::clEnqueueSVMMemFill(command_queue, svm_ptr, pattern, patternSize, size, num_events_in_wait_list, event_wait_list, event);
}
cl_int clEnqueueSVMMigrateMem (cl_command_queue command_queue, cl_uint num_svm_pointers, const void** svm_pointers, const size_t* sizes, cl_mem_migration_flags flags, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    return Cal::Client::Icd::Ocl::clEnqueueSVMMigrateMem(command_queue, num_svm_pointers, svm_pointers, sizes, flags, num_events_in_wait_list, event_wait_list, event);
}
cl_int clEnqueueSVMMemcpy (cl_command_queue command_queue, cl_bool blocking, void* dst_ptr, const void* src_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    return Cal::Client::Icd::Ocl::clEnqueueSVMMemcpy(command_queue, blocking, dst_ptr, src_ptr, size, num_events_in_wait_list, event_wait_list, event);
}
cl_int clEnqueueSVMFree (cl_command_queue command_queue, cl_uint num_svm_pointers, void** svm_pointers, void (CL_CALLBACK* pfn_notify)(cl_command_queue queue, cl_uint num_svm_pointers, void ** svm_pointers, void* user_data), void* user_data, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    return Cal::Client::Icd::Ocl::clEnqueueSVMFree(command_queue, num_svm_pointers, svm_pointers, pfn_notify, user_data, num_events_in_wait_list, event_wait_list, event);
}
cl_int clCreateSubDevicesEXT (cl_device_id in_device, const cl_device_partition_property_ext* properties, cl_uint num_entries, cl_device_id* out_devices, cl_uint* num_devices) {
    return Cal::Client::Icd::Ocl::clCreateSubDevicesEXT(in_device, properties, num_entries, out_devices, num_devices);
}
cl_int clReleaseDeviceEXT (cl_device_id device) {
    return Cal::Client::Icd::Ocl::clReleaseDeviceEXT(device);
}
cl_int clRetainDeviceEXT (cl_device_id device) {
    return Cal::Client::Icd::Ocl::clRetainDeviceEXT(device);
}
cl_int clGetKernelSubGroupInfoKHR (cl_kernel kernel, cl_device_id device, cl_kernel_sub_group_info param_name, size_t input_value_size, const void* input_value, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    return Cal::Client::Icd::Ocl::clGetKernelSubGroupInfoKHR(kernel, device, param_name, input_value_size, input_value, param_value_size, param_value, param_value_size_ret);
}
cl_int clGetKernelSuggestedLocalWorkSizeKHR (cl_command_queue command_queue, cl_kernel kernel, cl_uint work_dim, const size_t* global_work_offset, const size_t* global_work_size, size_t * suggested_local_work_size) {
    return Cal::Client::Icd::Ocl::clGetKernelSuggestedLocalWorkSizeKHR(command_queue, kernel, work_dim, global_work_offset, global_work_size, suggested_local_work_size);
}
cl_command_queue clCreateCommandQueueWithPropertiesKHR (cl_context context, cl_device_id device, const cl_queue_properties* properties, cl_int* errcode_ret) {
    return Cal::Client::Icd::Ocl::clCreateCommandQueueWithPropertiesKHR(context, device, properties, errcode_ret);
}
cl_int clEnqueueMemFillINTEL (cl_command_queue command_queue, void* dstPtr, const void* pattern, size_t patternSize, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    return Cal::Client::Icd::Ocl::clEnqueueMemFillINTEL(command_queue, dstPtr, pattern, patternSize, size, num_events_in_wait_list, event_wait_list, event);
}
cl_int clEnqueueMemcpyINTEL (cl_command_queue command_queue, cl_bool blocking, void* dstPtr, const void* srcPtr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    return Cal::Client::Icd::Ocl::clEnqueueMemcpyINTEL(command_queue, blocking, dstPtr, srcPtr, size, num_events_in_wait_list, event_wait_list, event);
}
cl_int clSetKernelArgMemPointerINTEL (cl_kernel kernel, cl_uint argIndex, const void* argValue) {
    return Cal::Client::Icd::Ocl::clSetKernelArgMemPointerINTEL(kernel, argIndex, argValue);
}
cl_int clGetMemAllocInfoINTEL (cl_context context, const void* ptr, cl_mem_info_intel param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
    return Cal::Client::Icd::Ocl::clGetMemAllocInfoINTEL(context, ptr, param_name, param_value_size, param_value, param_value_size_ret);
}
void* clDeviceMemAllocINTEL (cl_context context, cl_device_id device, const cl_mem_properties_intel* properties, size_t size, cl_uint alignment, cl_int* errcode_ret) {
    return Cal::Client::Icd::Ocl::clDeviceMemAllocINTEL(context, device, properties, size, alignment, errcode_ret);
}
void* clHostMemAllocINTEL (cl_context context, const cl_mem_properties_intel* properties, size_t size, cl_uint alignment, cl_int* errcode_ret) {
    return Cal::Client::Icd::Ocl::clHostMemAllocINTEL(context, properties, size, alignment, errcode_ret);
}
void* clSharedMemAllocINTEL (cl_context context, cl_device_id device, const cl_mem_properties_intel* properties, size_t size, cl_uint alignment, cl_int* errcode_ret) {
    return Cal::Client::Icd::Ocl::clSharedMemAllocINTEL(context, device, properties, size, alignment, errcode_ret);
}
cl_int clMemFreeINTEL (cl_context context, void* ptr) {
    return Cal::Client::Icd::Ocl::clMemFreeINTEL(context, ptr);
}
cl_int clMemBlockingFreeINTEL (cl_context context, void* ptr) {
    return Cal::Client::Icd::Ocl::clMemBlockingFreeINTEL(context, ptr);
}
cl_int clEnqueueMigrateMemINTEL (cl_command_queue command_queue, const void* ptr, size_t size, cl_mem_migration_flags flags, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
    return Cal::Client::Icd::Ocl::clEnqueueMigrateMemINTEL(command_queue, ptr, size, flags, num_events_in_wait_list, event_wait_list, event);
}
cl_int clGetDeviceGlobalVariablePointerINTEL (cl_device_id device, cl_program program, const char* globalVariableName, size_t* globalVariableSizeRet, void** globalVariablePointerRet) {
    return Cal::Client::Icd::Ocl::clGetDeviceGlobalVariablePointerINTEL(device, program, globalVariableName, globalVariableSizeRet, globalVariablePointerRet);
}
} // extern "C"


// #### Generated code -- end ####
