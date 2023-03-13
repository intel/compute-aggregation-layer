/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once
// #### Generated code -- begin ####

#include "shared/rpc_message.h"
#include "shared/shmem_transfer_desc.h"

#ifdef SLIM_OCL
#   include "ocl_slim_def.h"
#else 
#   include "shared/ocl_fat_def.h"
#endif

#include <cassert>
#include <cstring>
#include <memory>
#include <optional>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

namespace Cal {
namespace Rpc {
namespace Ocl {


template <typename Ptr>
inline void forcePointerWrite(Ptr& p, void* value) {
    static_assert(std::is_pointer_v<Ptr>, "forcePointerWrite() must be used with pointers!");
    using WritablePtr = std::remove_cv_t<Ptr>;

    const_cast<WritablePtr&>(p) = static_cast<WritablePtr>(value);
}

struct DynamicArgTraits {
    uint32_t offset;
    uint32_t count;
    uint32_t size;
    std::vector<DynamicArgTraits> nested;
};

template <typename DynamicStructT>
struct DynamicStructTraits {
    int32_t offset;
    int32_t count;
};


template<typename T>
inline char *asMemcpyDstT(T * ptr) {
    static_assert(std::is_standard_layout_v<T>);
    return reinterpret_cast<char*>(const_cast<std::remove_const_t<T>*>(ptr));
};

inline char *asMemcpyDstT(const void * ptr) {
    return reinterpret_cast<char*>(const_cast<void*>(ptr));
};

inline char *asMemcpyDstT(void * ptr) {
    return reinterpret_cast<char*>(const_cast<void*>(ptr));
};

struct ClGetPlatformIDsRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 0;
    static constexpr float latency = 1.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_uint num_entries = {};
        cl_platform_id* platforms = {};
        cl_uint* num_platforms = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->num_entries == rhs.num_entries;
            equal &= this->platforms == rhs.platforms;
            equal &= this->num_platforms == rhs.num_platforms;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_uint num_entries, cl_platform_id* platforms, cl_uint* num_platforms);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits platforms = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        cl_uint num_platforms;
        uint32_t countPlatforms = 0;
        cl_platform_id platforms[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countPlatforms = dynamicTraits.platforms.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClGetPlatformIDsRpcM() = default;

    ClGetPlatformIDsRpcM(const Captures::DynamicTraits &dynamicTraits, cl_uint num_entries, cl_platform_id* platforms, cl_uint* num_platforms) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.num_entries = num_entries;
        args.platforms = platforms;
        args.num_platforms = num_platforms;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClGetPlatformIDsRpcM &message, cl_uint num_entries, cl_platform_id* platforms, cl_uint* num_platforms) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.num_entries = num_entries;
        message.args.platforms = platforms;
        message.args.num_platforms = num_platforms;
    }
    

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.platforms){
            memcpy(args.platforms, captures.platforms, dynMemTraits.platforms.size);
        }
        if(args.num_platforms){
            *args.num_platforms = captures.num_platforms;
        }
    }
};
static_assert(std::is_standard_layout_v<ClGetPlatformIDsRpcM>);
 // clIcdGetPlatformIDsKHR ignored in generator - based on dont_generate_rpc_message flag
struct ClGetPlatformInfoRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 1;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_platform_id platform = {};
        cl_platform_info param_name = {};
        size_t param_value_size = {};
        void* param_value = {};
        size_t* param_value_size_ret = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->platform == rhs.platform;
            equal &= this->param_name == rhs.param_name;
            equal &= this->param_value_size == rhs.param_value_size;
            equal &= this->param_value == rhs.param_value;
            equal &= this->param_value_size_ret == rhs.param_value_size_ret;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_platform_id platform, cl_platform_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits param_value = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        size_t param_value_size_ret;
        uint32_t countParam_value = 0;
        char param_value[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countParam_value = dynamicTraits.param_value.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClGetPlatformInfoRpcM() = default;

    ClGetPlatformInfoRpcM(const Captures::DynamicTraits &dynamicTraits, cl_platform_id platform, cl_platform_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.platform = platform;
        args.param_name = param_name;
        args.param_value_size = param_value_size;
        args.param_value = param_value;
        args.param_value_size_ret = param_value_size_ret;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClGetPlatformInfoRpcM &message, cl_platform_id platform, cl_platform_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.platform = platform;
        message.args.param_name = param_name;
        message.args.param_value_size = param_value_size;
        message.args.param_value = param_value;
        message.args.param_value_size_ret = param_value_size_ret;
    }
    

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.param_value){
            memcpy(args.param_value, captures.param_value, dynMemTraits.param_value.size);
        }
        if(args.param_value_size_ret){
            *args.param_value_size_ret = captures.param_value_size_ret;
        }
    }
};
static_assert(std::is_standard_layout_v<ClGetPlatformInfoRpcM>);
 // clGetExtensionFunctionAddress ignored in generator - based on dont_generate_rpc_message flag
struct ClGetDeviceIDsRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 2;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_platform_id platform = {};
        cl_device_type device_type = {};
        cl_uint num_entries = {};
        cl_device_id* devices = {};
        cl_uint* num_devices = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->platform == rhs.platform;
            equal &= this->device_type == rhs.device_type;
            equal &= this->num_entries == rhs.num_entries;
            equal &= this->devices == rhs.devices;
            equal &= this->num_devices == rhs.num_devices;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_platform_id platform, cl_device_type device_type, cl_uint num_entries, cl_device_id* devices, cl_uint* num_devices);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits devices = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        cl_uint num_devices;
        uint32_t countDevices = 0;
        cl_device_id devices[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countDevices = dynamicTraits.devices.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClGetDeviceIDsRpcM() = default;

    ClGetDeviceIDsRpcM(const Captures::DynamicTraits &dynamicTraits, cl_platform_id platform, cl_device_type device_type, cl_uint num_entries, cl_device_id* devices, cl_uint* num_devices) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.platform = platform;
        args.device_type = device_type;
        args.num_entries = num_entries;
        args.devices = devices;
        args.num_devices = num_devices;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClGetDeviceIDsRpcM &message, cl_platform_id platform, cl_device_type device_type, cl_uint num_entries, cl_device_id* devices, cl_uint* num_devices) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.platform = platform;
        message.args.device_type = device_type;
        message.args.num_entries = num_entries;
        message.args.devices = devices;
        message.args.num_devices = num_devices;
    }
    

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.devices){
            memcpy(args.devices, captures.devices, dynMemTraits.devices.size);
        }
        if(args.num_devices){
            *args.num_devices = captures.num_devices;
        }
    }
};
static_assert(std::is_standard_layout_v<ClGetDeviceIDsRpcM>);
struct ClGetDeviceInfoRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 3;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_device_id device = {};
        cl_device_info param_name = {};
        size_t param_value_size = {};
        void* param_value = {};
        size_t* param_value_size_ret = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->device == rhs.device;
            equal &= this->param_name == rhs.param_name;
            equal &= this->param_value_size == rhs.param_value_size;
            equal &= this->param_value == rhs.param_value;
            equal &= this->param_value_size_ret == rhs.param_value_size_ret;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_device_id device, cl_device_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits param_value = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        size_t param_value_size_ret;
        uint32_t countParam_value = 0;
        char param_value[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countParam_value = dynamicTraits.param_value.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        std::unique_ptr<char[]> clone() {
            auto newCapturesMem = std::make_unique<char[]>(getCaptureTotalSize());
            auto newCaptures = new (newCapturesMem.get()) Captures();

            constexpr static bool skipSizeValidation{true};
            newCaptures->assignFrom(*this, skipSizeValidation);

            return newCapturesMem;
        }

        bool assignFrom(const Captures& rhs, bool skipSizeValidation = false) {
            if (this == &rhs) {
                return true;
            }
            if (!skipSizeValidation && getCaptureDynMemSize() != rhs.getCaptureDynMemSize()) {
                return false;
            }
            this->ret = rhs.ret;
            this->param_value_size_ret = rhs.param_value_size_ret;
            this->countParam_value = rhs.countParam_value;
            for(size_t i = 0; i < countParam_value; ++i){
                this->param_value[i] = rhs.param_value[i];
            }
            return true;
        }
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClGetDeviceInfoRpcM() = default;

    ClGetDeviceInfoRpcM(const Captures::DynamicTraits &dynamicTraits, cl_device_id device, cl_device_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.device = device;
        args.param_name = param_name;
        args.param_value_size = param_value_size;
        args.param_value = param_value;
        args.param_value_size_ret = param_value_size_ret;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClGetDeviceInfoRpcM &message, cl_device_id device, cl_device_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.device = device;
        message.args.param_name = param_name;
        message.args.param_value_size = param_value_size;
        message.args.param_value = param_value;
        message.args.param_value_size_ret = param_value_size_ret;
    }
    

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.param_value){
            memcpy(args.param_value, captures.param_value, dynMemTraits.param_value.size);
        }
        if(args.param_value_size_ret){
            *args.param_value_size_ret = captures.param_value_size_ret;
        }
    }
};
static_assert(std::is_standard_layout_v<ClGetDeviceInfoRpcM>);
struct ClCreateContextRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 4;
    static constexpr float latency = 1.0;

    using ReturnValueT = cl_context;

    struct Args {
        const cl_context_properties* properties = {};
        cl_uint num_devices = {};
        const cl_device_id* devices = {};
        void (CL_CALLBACK* pfn_notify)(const char* errinfo, const void* private_info, size_t cb, void* user_data) = {};
        void* user_data = {};
        cl_int* errcode_ret = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->properties == rhs.properties;
            equal &= this->num_devices == rhs.num_devices;
            equal &= this->devices == rhs.devices;
            equal &= this->pfn_notify == rhs.pfn_notify;
            equal &= this->user_data == rhs.user_data;
            equal &= this->errcode_ret == rhs.errcode_ret;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(const cl_context_properties* properties, cl_uint num_devices, const cl_device_id* devices, void (CL_CALLBACK* pfn_notify)(const char* errinfo, const void* private_info, size_t cb, void* user_data), void* user_data, cl_int* errcode_ret);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits devices = {};          
            DynamicArgTraits properties = {};          
        };

        cl_context ret = {};
        cl_int errcode_ret;
        uint32_t offsetProperties = 0;
        uint32_t countDevices = 0;
        uint32_t countProperties = 0;
        const cl_device_id* getDevices() {
            auto offset = 0;
            return reinterpret_cast<const cl_device_id*>(dynMem + offset);
        }

        const cl_context_properties* getProperties() {
            auto offset = offsetProperties;
            return reinterpret_cast<const cl_context_properties*>(dynMem + offset);
        }


        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        offsetProperties = dynamicTraits.properties.offset;
        countDevices = dynamicTraits.devices.count;
        countProperties = dynamicTraits.properties.count;
        }
        
        alignas(8) char dynMem[];
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_context returnValue(){
        return captures.ret;
    }

    ClCreateContextRpcM() = default;

    ClCreateContextRpcM(const Captures::DynamicTraits &dynamicTraits, const cl_context_properties* properties, cl_uint num_devices, const cl_device_id* devices, void (CL_CALLBACK* pfn_notify)(const char* errinfo, const void* private_info, size_t cb, void* user_data), void* user_data, cl_int* errcode_ret) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.properties = properties;
        args.num_devices = num_devices;
        args.devices = devices;
        args.pfn_notify = pfn_notify;
        args.user_data = user_data;
        args.errcode_ret = errcode_ret;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClCreateContextRpcM &message, const cl_context_properties* properties, cl_uint num_devices, const cl_device_id* devices, void (CL_CALLBACK* pfn_notify)(const char* errinfo, const void* private_info, size_t cb, void* user_data), void* user_data, cl_int* errcode_ret) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.properties = properties;
        message.args.num_devices = num_devices;
        message.args.devices = devices;
        message.args.pfn_notify = pfn_notify;
        message.args.user_data = user_data;
        message.args.errcode_ret = errcode_ret;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.properties){
            memcpy(asMemcpyDstT(captures.getProperties()), args.properties, dynMemTraits.properties.size);
        }
        memcpy(asMemcpyDstT(captures.getDevices()), args.devices, dynMemTraits.devices.size);
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.errcode_ret){
            *args.errcode_ret = captures.errcode_ret;
        }
    }
};
static_assert(std::is_standard_layout_v<ClCreateContextRpcM>);
struct ClCreateContextFromTypeRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 5;
    static constexpr float latency = 1.0;

    using ReturnValueT = cl_context;

    struct Args {
        const cl_context_properties* properties = {};
        cl_device_type device_type = {};
        void (CL_CALLBACK* pfn_notify)(const char* errinfo, const void* private_info, size_t cb, void* user_data) = {};
        void* user_data = {};
        cl_int* errcode_ret = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->properties == rhs.properties;
            equal &= this->device_type == rhs.device_type;
            equal &= this->pfn_notify == rhs.pfn_notify;
            equal &= this->user_data == rhs.user_data;
            equal &= this->errcode_ret == rhs.errcode_ret;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(const cl_context_properties* properties, cl_device_type device_type, void (CL_CALLBACK* pfn_notify)(const char* errinfo, const void* private_info, size_t cb, void* user_data), void* user_data, cl_int* errcode_ret);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits properties = {};          
        };

        cl_context ret = {};
        cl_int errcode_ret;
        uint32_t countProperties = 0;
        cl_context_properties properties[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countProperties = dynamicTraits.properties.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_context returnValue(){
        return captures.ret;
    }

    ClCreateContextFromTypeRpcM() = default;

    ClCreateContextFromTypeRpcM(const Captures::DynamicTraits &dynamicTraits, const cl_context_properties* properties, cl_device_type device_type, void (CL_CALLBACK* pfn_notify)(const char* errinfo, const void* private_info, size_t cb, void* user_data), void* user_data, cl_int* errcode_ret) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.properties = properties;
        args.device_type = device_type;
        args.pfn_notify = pfn_notify;
        args.user_data = user_data;
        args.errcode_ret = errcode_ret;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClCreateContextFromTypeRpcM &message, const cl_context_properties* properties, cl_device_type device_type, void (CL_CALLBACK* pfn_notify)(const char* errinfo, const void* private_info, size_t cb, void* user_data), void* user_data, cl_int* errcode_ret) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.properties = properties;
        message.args.device_type = device_type;
        message.args.pfn_notify = pfn_notify;
        message.args.user_data = user_data;
        message.args.errcode_ret = errcode_ret;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.properties){
            memcpy(asMemcpyDstT(captures.properties), args.properties, dynMemTraits.properties.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.errcode_ret){
            *args.errcode_ret = captures.errcode_ret;
        }
    }
};
static_assert(std::is_standard_layout_v<ClCreateContextFromTypeRpcM>);
struct ClGetContextInfoRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 6;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_context context = {};
        cl_context_info param_name = {};
        size_t param_value_size = {};
        void* param_value = {};
        size_t* param_value_size_ret = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->context == rhs.context;
            equal &= this->param_name == rhs.param_name;
            equal &= this->param_value_size == rhs.param_value_size;
            equal &= this->param_value == rhs.param_value;
            equal &= this->param_value_size_ret == rhs.param_value_size_ret;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_context context, cl_context_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits param_value = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        size_t param_value_size_ret;
        uint32_t countParam_value = 0;
        char param_value[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countParam_value = dynamicTraits.param_value.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        std::unique_ptr<char[]> clone() {
            auto newCapturesMem = std::make_unique<char[]>(getCaptureTotalSize());
            auto newCaptures = new (newCapturesMem.get()) Captures();

            constexpr static bool skipSizeValidation{true};
            newCaptures->assignFrom(*this, skipSizeValidation);

            return newCapturesMem;
        }

        bool assignFrom(const Captures& rhs, bool skipSizeValidation = false) {
            if (this == &rhs) {
                return true;
            }
            if (!skipSizeValidation && getCaptureDynMemSize() != rhs.getCaptureDynMemSize()) {
                return false;
            }
            this->ret = rhs.ret;
            this->param_value_size_ret = rhs.param_value_size_ret;
            this->countParam_value = rhs.countParam_value;
            for(size_t i = 0; i < countParam_value; ++i){
                this->param_value[i] = rhs.param_value[i];
            }
            return true;
        }
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClGetContextInfoRpcM() = default;

    ClGetContextInfoRpcM(const Captures::DynamicTraits &dynamicTraits, cl_context context, cl_context_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.context = context;
        args.param_name = param_name;
        args.param_value_size = param_value_size;
        args.param_value = param_value;
        args.param_value_size_ret = param_value_size_ret;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClGetContextInfoRpcM &message, cl_context context, cl_context_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.context = context;
        message.args.param_name = param_name;
        message.args.param_value_size = param_value_size;
        message.args.param_value = param_value;
        message.args.param_value_size_ret = param_value_size_ret;
    }
    

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.param_value){
            memcpy(args.param_value, captures.param_value, dynMemTraits.param_value.size);
        }
        if(args.param_value_size_ret){
            *args.param_value_size_ret = captures.param_value_size_ret;
        }
    }
};
static_assert(std::is_standard_layout_v<ClGetContextInfoRpcM>);
struct ClCreateSubDevicesRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 7;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_device_id in_device = {};
        const cl_device_partition_property* properties = {};
        cl_uint num_devices = {};
        cl_device_id* out_devices = {};
        cl_uint* num_devices_ret = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->in_device == rhs.in_device;
            equal &= this->properties == rhs.properties;
            equal &= this->num_devices == rhs.num_devices;
            equal &= this->out_devices == rhs.out_devices;
            equal &= this->num_devices_ret == rhs.num_devices_ret;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_device_id in_device, const cl_device_partition_property* properties, cl_uint num_devices, cl_device_id* out_devices, cl_uint* num_devices_ret);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits out_devices = {};          
            DynamicArgTraits properties = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        cl_uint num_devices_ret;
        uint32_t offsetProperties = 0;
        uint32_t countOut_devices = 0;
        uint32_t countProperties = 0;
        cl_device_id* getOut_devices() {
            auto offset = 0;
            return reinterpret_cast<cl_device_id*>(dynMem + offset);
        }

        const cl_device_partition_property* getProperties() {
            auto offset = offsetProperties;
            return reinterpret_cast<const cl_device_partition_property*>(dynMem + offset);
        }


        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        offsetProperties = dynamicTraits.properties.offset;
        countOut_devices = dynamicTraits.out_devices.count;
        countProperties = dynamicTraits.properties.count;
        }
        
        alignas(8) char dynMem[];
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClCreateSubDevicesRpcM() = default;

    ClCreateSubDevicesRpcM(const Captures::DynamicTraits &dynamicTraits, cl_device_id in_device, const cl_device_partition_property* properties, cl_uint num_devices, cl_device_id* out_devices, cl_uint* num_devices_ret) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.in_device = in_device;
        args.properties = properties;
        args.num_devices = num_devices;
        args.out_devices = out_devices;
        args.num_devices_ret = num_devices_ret;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClCreateSubDevicesRpcM &message, cl_device_id in_device, const cl_device_partition_property* properties, cl_uint num_devices, cl_device_id* out_devices, cl_uint* num_devices_ret) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.in_device = in_device;
        message.args.properties = properties;
        message.args.num_devices = num_devices;
        message.args.out_devices = out_devices;
        message.args.num_devices_ret = num_devices_ret;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.properties){
            memcpy(asMemcpyDstT(captures.getProperties()), args.properties, dynMemTraits.properties.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.out_devices){
            memcpy(args.out_devices, captures.getOut_devices(), dynMemTraits.out_devices.size);
        }
        if(args.num_devices_ret){
            *args.num_devices_ret = captures.num_devices_ret;
        }
    }
};
static_assert(std::is_standard_layout_v<ClCreateSubDevicesRpcM>);
struct ClCreateCommandQueueRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 8;
    static constexpr float latency = 1.0;

    using ReturnValueT = cl_command_queue;

    struct Args {
        cl_context context = {};
        cl_device_id device = {};
        cl_command_queue_properties  properties = {};
        cl_int* errcode_ret = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->context == rhs.context;
            equal &= this->device == rhs.device;
            equal &= this->properties == rhs.properties;
            equal &= this->errcode_ret == rhs.errcode_ret;
            return equal;
        }
    }args;

    struct Captures {

        cl_command_queue ret = {};
        cl_int errcode_ret;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_command_queue returnValue(){
        return captures.ret;
    }

    ClCreateCommandQueueRpcM() = default;

    ClCreateCommandQueueRpcM(cl_context context, cl_device_id device, cl_command_queue_properties  properties, cl_int* errcode_ret) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.context = context;
        args.device = device;
        args.properties = properties;
        args.errcode_ret = errcode_ret;
    }
    
    static void fillWithoutCapture(ClCreateCommandQueueRpcM &message, cl_context context, cl_device_id device, cl_command_queue_properties  properties, cl_int* errcode_ret) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.context = context;
        message.args.device = device;
        message.args.properties = properties;
        message.args.errcode_ret = errcode_ret;
    }
    

    void copyToCaller(){
        if(args.errcode_ret){
            *args.errcode_ret = captures.errcode_ret;
        }
    }
};
static_assert(std::is_standard_layout_v<ClCreateCommandQueueRpcM>);
struct ClSetDefaultDeviceCommandQueueRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 9;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_context context = {};
        cl_device_id device = {};
        cl_command_queue command_queue = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->context == rhs.context;
            equal &= this->device == rhs.device;
            equal &= this->command_queue == rhs.command_queue;
            return equal;
        }
    }args;

    struct Captures {

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClSetDefaultDeviceCommandQueueRpcM() = default;

    ClSetDefaultDeviceCommandQueueRpcM(cl_context context, cl_device_id device, cl_command_queue command_queue) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.context = context;
        args.device = device;
        args.command_queue = command_queue;
    }
    
    static void fillWithoutCapture(ClSetDefaultDeviceCommandQueueRpcM &message, cl_context context, cl_device_id device, cl_command_queue command_queue) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.context = context;
        message.args.device = device;
        message.args.command_queue = command_queue;
    }
    
};
static_assert(std::is_standard_layout_v<ClSetDefaultDeviceCommandQueueRpcM>);
struct ClCreateCommandQueueWithPropertiesRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 10;
    static constexpr float latency = 1.0;

    using ReturnValueT = cl_command_queue;

    struct Args {
        cl_context context = {};
        cl_device_id device = {};
        const cl_queue_properties* properties = {};
        cl_int* errcode_ret = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->context == rhs.context;
            equal &= this->device == rhs.device;
            equal &= this->properties == rhs.properties;
            equal &= this->errcode_ret == rhs.errcode_ret;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_context context, cl_device_id device, const cl_queue_properties* properties, cl_int* errcode_ret);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits properties = {};          
        };

        cl_command_queue ret = {};
        cl_int errcode_ret;
        uint32_t countProperties = 0;
        cl_queue_properties properties[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countProperties = dynamicTraits.properties.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_command_queue returnValue(){
        return captures.ret;
    }

    ClCreateCommandQueueWithPropertiesRpcM() = default;

    ClCreateCommandQueueWithPropertiesRpcM(const Captures::DynamicTraits &dynamicTraits, cl_context context, cl_device_id device, const cl_queue_properties* properties, cl_int* errcode_ret) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.context = context;
        args.device = device;
        args.properties = properties;
        args.errcode_ret = errcode_ret;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClCreateCommandQueueWithPropertiesRpcM &message, cl_context context, cl_device_id device, const cl_queue_properties* properties, cl_int* errcode_ret) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.context = context;
        message.args.device = device;
        message.args.properties = properties;
        message.args.errcode_ret = errcode_ret;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.properties){
            memcpy(asMemcpyDstT(captures.properties), args.properties, dynMemTraits.properties.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.errcode_ret){
            *args.errcode_ret = captures.errcode_ret;
        }
    }
};
static_assert(std::is_standard_layout_v<ClCreateCommandQueueWithPropertiesRpcM>);
struct ClCreateProgramWithSourceRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 11;
    static constexpr float latency = 0.5;

    using ReturnValueT = cl_program;

    struct Args {
        cl_context context = {};
        cl_uint count = {};
        const char** strings = {};
        const size_t* lengths = {};
        cl_int* errcode_ret = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->context == rhs.context;
            equal &= this->count == rhs.count;
            equal &= this->strings == rhs.strings;
            equal &= this->lengths == rhs.lengths;
            equal &= this->errcode_ret == rhs.errcode_ret;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_context context, cl_uint count, const char** strings, const size_t* lengths, cl_int* errcode_ret);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits lengths = {};          
            DynamicArgTraits strings = {};          
        };

        cl_program ret = {};
        cl_int errcode_ret;
        uint32_t offsetStrings = 0;
        uint32_t countLengths = 0;
        uint32_t countStrings = 0;
        const size_t* getLengths() {
            auto offset = 0;
            return reinterpret_cast<const size_t*>(dynMem + offset);
        }

        std::vector<const char*> getStrings() {
            auto arrayOffset = offsetStrings;
            auto nestedArraysOffsets = reinterpret_cast<uint32_t*>(dynMem + arrayOffset);
            
            using ElementT = const char*;
            auto elCount = countStrings;
            std::vector<ElementT> ret;
            ret.reserve(elCount);
            for(uint32_t i = 0; i < elCount; ++i){
                ret.push_back(reinterpret_cast<ElementT>(dynMem + nestedArraysOffsets[i]));
            }
            return ret;
        }


        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        offsetStrings = dynamicTraits.strings.offset;
        countLengths = dynamicTraits.lengths.count;
        countStrings = dynamicTraits.strings.count;
            {
                auto nestedArraysOffsets = reinterpret_cast<uint32_t*>(dynMem + dynamicTraits.strings.offset);
                for(uint32_t i = 0; i < dynamicTraits.strings.count; ++i){
                    nestedArraysOffsets[i] = dynamicTraits.strings.nested[i].offset;
                }
            }
            dynMemSize = dynamicTraits.totalDynamicSize;
        }
        
        uint32_t dynMemSize = 0;
        alignas(8) char dynMem[];
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_program returnValue(){
        return captures.ret;
    }

    ClCreateProgramWithSourceRpcM() = default;

    ClCreateProgramWithSourceRpcM(const Captures::DynamicTraits &dynamicTraits, cl_context context, cl_uint count, const char** strings, const size_t* lengths, cl_int* errcode_ret) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.context = context;
        args.count = count;
        args.strings = strings;
        args.lengths = lengths;
        args.errcode_ret = errcode_ret;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClCreateProgramWithSourceRpcM &message, cl_context context, cl_uint count, const char** strings, const size_t* lengths, cl_int* errcode_ret) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.context = context;
        message.args.count = count;
        message.args.strings = strings;
        message.args.lengths = lengths;
        message.args.errcode_ret = errcode_ret;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.strings){
            {
                 auto array = captures.getStrings();
                 for(uint32_t i = 0; i < dynMemTraits.strings.count; ++i) {
                     memcpy(asMemcpyDstT(array[i]), args.strings[i], dynMemTraits.strings.nested[i].size);
                 }
            }
        }
        if(args.lengths){
            memcpy(asMemcpyDstT(captures.getLengths()), args.lengths, dynMemTraits.lengths.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.errcode_ret){
            *args.errcode_ret = captures.errcode_ret;
        }
    }
};
static_assert(std::is_standard_layout_v<ClCreateProgramWithSourceRpcM>);
struct ClCreateProgramWithILRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 12;
    static constexpr float latency = 0.5;

    using ReturnValueT = cl_program;

    struct Args {
        cl_context context = {};
        const void* il = {};
        size_t length = {};
        cl_int* errcode_ret = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->context == rhs.context;
            equal &= this->il == rhs.il;
            equal &= this->length == rhs.length;
            equal &= this->errcode_ret == rhs.errcode_ret;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_context context, const void* il, size_t length, cl_int* errcode_ret);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits il = {};          
        };

        cl_program ret = {};
        cl_int errcode_ret;
        uint32_t countIl = 0;
        char il[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countIl = dynamicTraits.il.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_program returnValue(){
        return captures.ret;
    }

    ClCreateProgramWithILRpcM() = default;

    ClCreateProgramWithILRpcM(const Captures::DynamicTraits &dynamicTraits, cl_context context, const void* il, size_t length, cl_int* errcode_ret) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.context = context;
        args.il = il;
        args.length = length;
        args.errcode_ret = errcode_ret;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClCreateProgramWithILRpcM &message, cl_context context, const void* il, size_t length, cl_int* errcode_ret) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.context = context;
        message.args.il = il;
        message.args.length = length;
        message.args.errcode_ret = errcode_ret;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.il){
            memcpy(asMemcpyDstT(captures.il), args.il, dynMemTraits.il.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.errcode_ret){
            *args.errcode_ret = captures.errcode_ret;
        }
    }
};
static_assert(std::is_standard_layout_v<ClCreateProgramWithILRpcM>);
struct ClCreateProgramWithBinaryRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 13;
    static constexpr float latency = 1.0;

    using ReturnValueT = cl_program;

    struct Args {
        cl_context context = {};
        cl_uint num_devices = {};
        const cl_device_id* device_list = {};
        const size_t* lengths = {};
        const unsigned char** binaries = {};
        cl_int* binary_status = {};
        cl_int* errcode_ret = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->context == rhs.context;
            equal &= this->num_devices == rhs.num_devices;
            equal &= this->device_list == rhs.device_list;
            equal &= this->lengths == rhs.lengths;
            equal &= this->binaries == rhs.binaries;
            equal &= this->binary_status == rhs.binary_status;
            equal &= this->errcode_ret == rhs.errcode_ret;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_context context, cl_uint num_devices, const cl_device_id* device_list, const size_t* lengths, const unsigned char** binaries, cl_int* binary_status, cl_int* errcode_ret);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits device_list = {};          
            DynamicArgTraits lengths = {};          
            DynamicArgTraits binary_status = {};          
            DynamicArgTraits binaries = {};          
        };

        cl_program ret = {};
        cl_int errcode_ret;
        uint32_t offsetLengths = 0;
        uint32_t offsetBinary_status = 0;
        uint32_t offsetBinaries = 0;
        uint32_t countDevice_list = 0;
        uint32_t countLengths = 0;
        uint32_t countBinary_status = 0;
        uint32_t countBinaries = 0;
        const cl_device_id* getDevice_list() {
            auto offset = 0;
            return reinterpret_cast<const cl_device_id*>(dynMem + offset);
        }

        const size_t* getLengths() {
            auto offset = offsetLengths;
            return reinterpret_cast<const size_t*>(dynMem + offset);
        }

        cl_int* getBinary_status() {
            auto offset = offsetBinary_status;
            return reinterpret_cast<cl_int*>(dynMem + offset);
        }

        std::vector<const unsigned char*> getBinaries() {
            auto arrayOffset = offsetBinaries;
            auto nestedArraysOffsets = reinterpret_cast<uint32_t*>(dynMem + arrayOffset);
            
            using ElementT = const unsigned char*;
            auto elCount = countBinaries;
            std::vector<ElementT> ret;
            ret.reserve(elCount);
            for(uint32_t i = 0; i < elCount; ++i){
                ret.push_back(reinterpret_cast<ElementT>(dynMem + nestedArraysOffsets[i]));
            }
            return ret;
        }


        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        offsetLengths = dynamicTraits.lengths.offset;
        offsetBinary_status = dynamicTraits.binary_status.offset;
        offsetBinaries = dynamicTraits.binaries.offset;
        countDevice_list = dynamicTraits.device_list.count;
        countLengths = dynamicTraits.lengths.count;
        countBinary_status = dynamicTraits.binary_status.count;
        countBinaries = dynamicTraits.binaries.count;
            {
                auto nestedArraysOffsets = reinterpret_cast<uint32_t*>(dynMem + dynamicTraits.binaries.offset);
                for(uint32_t i = 0; i < dynamicTraits.binaries.count; ++i){
                    nestedArraysOffsets[i] = dynamicTraits.binaries.nested[i].offset;
                }
            }
            dynMemSize = dynamicTraits.totalDynamicSize;
        }
        
        uint32_t dynMemSize = 0;
        alignas(8) char dynMem[];
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_program returnValue(){
        return captures.ret;
    }

    ClCreateProgramWithBinaryRpcM() = default;

    ClCreateProgramWithBinaryRpcM(const Captures::DynamicTraits &dynamicTraits, cl_context context, cl_uint num_devices, const cl_device_id* device_list, const size_t* lengths, const unsigned char** binaries, cl_int* binary_status, cl_int* errcode_ret) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.context = context;
        args.num_devices = num_devices;
        args.device_list = device_list;
        args.lengths = lengths;
        args.binaries = binaries;
        args.binary_status = binary_status;
        args.errcode_ret = errcode_ret;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClCreateProgramWithBinaryRpcM &message, cl_context context, cl_uint num_devices, const cl_device_id* device_list, const size_t* lengths, const unsigned char** binaries, cl_int* binary_status, cl_int* errcode_ret) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.context = context;
        message.args.num_devices = num_devices;
        message.args.device_list = device_list;
        message.args.lengths = lengths;
        message.args.binaries = binaries;
        message.args.binary_status = binary_status;
        message.args.errcode_ret = errcode_ret;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.device_list){
            memcpy(asMemcpyDstT(captures.getDevice_list()), args.device_list, dynMemTraits.device_list.size);
        }
        if(args.lengths){
            memcpy(asMemcpyDstT(captures.getLengths()), args.lengths, dynMemTraits.lengths.size);
        }
        if(args.binaries){
            {
                 auto array = captures.getBinaries();
                 for(uint32_t i = 0; i < dynMemTraits.binaries.count; ++i) {
                     memcpy(asMemcpyDstT(array[i]), args.binaries[i], dynMemTraits.binaries.nested[i].size);
                 }
            }
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.binary_status){
            memcpy(args.binary_status, captures.getBinary_status(), dynMemTraits.binary_status.size);
        }
        if(args.errcode_ret){
            *args.errcode_ret = captures.errcode_ret;
        }
    }
};
static_assert(std::is_standard_layout_v<ClCreateProgramWithBinaryRpcM>);
struct ClCreateProgramWithBuiltInKernelsRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 14;
    static constexpr float latency = 1.0;

    using ReturnValueT = cl_program;

    struct Args {
        cl_context context = {};
        cl_uint num_devices = {};
        const cl_device_id* device_list = {};
        const char* kernel_names = {};
        cl_int* errcode_ret = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->context == rhs.context;
            equal &= this->num_devices == rhs.num_devices;
            equal &= this->device_list == rhs.device_list;
            equal &= this->kernel_names == rhs.kernel_names;
            equal &= this->errcode_ret == rhs.errcode_ret;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_context context, cl_uint num_devices, const cl_device_id* device_list, const char* kernel_names, cl_int* errcode_ret);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits device_list = {};          
            DynamicArgTraits kernel_names = {};          
        };

        cl_program ret = {};
        cl_int errcode_ret;
        uint32_t offsetKernel_names = 0;
        uint32_t countDevice_list = 0;
        uint32_t countKernel_names = 0;
        const cl_device_id* getDevice_list() {
            auto offset = 0;
            return reinterpret_cast<const cl_device_id*>(dynMem + offset);
        }

        const char* getKernel_names() {
            auto offset = offsetKernel_names;
            return reinterpret_cast<const char*>(dynMem + offset);
        }


        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        offsetKernel_names = dynamicTraits.kernel_names.offset;
        countDevice_list = dynamicTraits.device_list.count;
        countKernel_names = dynamicTraits.kernel_names.count;
        }
        
        alignas(8) char dynMem[];
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_program returnValue(){
        return captures.ret;
    }

    ClCreateProgramWithBuiltInKernelsRpcM() = default;

    ClCreateProgramWithBuiltInKernelsRpcM(const Captures::DynamicTraits &dynamicTraits, cl_context context, cl_uint num_devices, const cl_device_id* device_list, const char* kernel_names, cl_int* errcode_ret) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.context = context;
        args.num_devices = num_devices;
        args.device_list = device_list;
        args.kernel_names = kernel_names;
        args.errcode_ret = errcode_ret;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClCreateProgramWithBuiltInKernelsRpcM &message, cl_context context, cl_uint num_devices, const cl_device_id* device_list, const char* kernel_names, cl_int* errcode_ret) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.context = context;
        message.args.num_devices = num_devices;
        message.args.device_list = device_list;
        message.args.kernel_names = kernel_names;
        message.args.errcode_ret = errcode_ret;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.device_list){
            memcpy(asMemcpyDstT(captures.getDevice_list()), args.device_list, dynMemTraits.device_list.size);
        }
        if(args.kernel_names){
            memcpy(asMemcpyDstT(captures.getKernel_names()), args.kernel_names, dynMemTraits.kernel_names.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.errcode_ret){
            *args.errcode_ret = captures.errcode_ret;
        }
    }
};
static_assert(std::is_standard_layout_v<ClCreateProgramWithBuiltInKernelsRpcM>);
 // clUnloadCompiler ignored in generator - based on dont_generate_rpc_message flag
 // clUnloadPlatformCompiler ignored in generator - based on dont_generate_rpc_message flag
struct ClBuildProgramRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 15;
    static constexpr float latency = 2.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_program program = {};
        cl_uint num_devices = {};
        const cl_device_id* device_list = {};
        const char* options = {};
        void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data) = {};
        void* user_data = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->program == rhs.program;
            equal &= this->num_devices == rhs.num_devices;
            equal &= this->device_list == rhs.device_list;
            equal &= this->options == rhs.options;
            equal &= this->pfn_notify == rhs.pfn_notify;
            equal &= this->user_data == rhs.user_data;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_program program, cl_uint num_devices, const cl_device_id* device_list, const char* options, void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data), void* user_data);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits device_list = {};          
            DynamicArgTraits options = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        uint32_t offsetOptions = 0;
        uint32_t countDevice_list = 0;
        uint32_t countOptions = 0;
        const cl_device_id* getDevice_list() {
            auto offset = 0;
            return reinterpret_cast<const cl_device_id*>(dynMem + offset);
        }

        const char* getOptions() {
            auto offset = offsetOptions;
            return reinterpret_cast<const char*>(dynMem + offset);
        }


        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        offsetOptions = dynamicTraits.options.offset;
        countDevice_list = dynamicTraits.device_list.count;
        countOptions = dynamicTraits.options.count;
        }
        
        alignas(8) char dynMem[];
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClBuildProgramRpcM() = default;

    ClBuildProgramRpcM(const Captures::DynamicTraits &dynamicTraits, cl_program program, cl_uint num_devices, const cl_device_id* device_list, const char* options, void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data), void* user_data) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.program = program;
        args.num_devices = num_devices;
        args.device_list = device_list;
        args.options = options;
        args.pfn_notify = pfn_notify;
        args.user_data = user_data;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClBuildProgramRpcM &message, cl_program program, cl_uint num_devices, const cl_device_id* device_list, const char* options, void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data), void* user_data) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.program = program;
        message.args.num_devices = num_devices;
        message.args.device_list = device_list;
        message.args.options = options;
        message.args.pfn_notify = pfn_notify;
        message.args.user_data = user_data;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.device_list){
            memcpy(asMemcpyDstT(captures.getDevice_list()), args.device_list, dynMemTraits.device_list.size);
        }
        if(args.options){
            memcpy(asMemcpyDstT(captures.getOptions()), args.options, dynMemTraits.options.size);
        }
    }
};
static_assert(std::is_standard_layout_v<ClBuildProgramRpcM>);
struct ClCompileProgramRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 16;
    static constexpr float latency = 2.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_program program = {};
        cl_uint num_devices = {};
        const cl_device_id* device_list = {};
        const char* options = {};
        cl_uint num_input_headers = {};
        const cl_program* input_headers = {};
        const char** header_include_names = {};
        void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data) = {};
        void* user_data = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->program == rhs.program;
            equal &= this->num_devices == rhs.num_devices;
            equal &= this->device_list == rhs.device_list;
            equal &= this->options == rhs.options;
            equal &= this->num_input_headers == rhs.num_input_headers;
            equal &= this->input_headers == rhs.input_headers;
            equal &= this->header_include_names == rhs.header_include_names;
            equal &= this->pfn_notify == rhs.pfn_notify;
            equal &= this->user_data == rhs.user_data;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_program program, cl_uint num_devices, const cl_device_id* device_list, const char* options, cl_uint num_input_headers, const cl_program* input_headers, const char** header_include_names, void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data), void* user_data);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits device_list = {};          
            DynamicArgTraits input_headers = {};          
            DynamicArgTraits options = {};          
            DynamicArgTraits header_include_names = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        uint32_t offsetInput_headers = 0;
        uint32_t offsetOptions = 0;
        uint32_t offsetHeader_include_names = 0;
        uint32_t countDevice_list = 0;
        uint32_t countInput_headers = 0;
        uint32_t countOptions = 0;
        uint32_t countHeader_include_names = 0;
        const cl_device_id* getDevice_list() {
            auto offset = 0;
            return reinterpret_cast<const cl_device_id*>(dynMem + offset);
        }

        const cl_program* getInput_headers() {
            auto offset = offsetInput_headers;
            return reinterpret_cast<const cl_program*>(dynMem + offset);
        }

        const char* getOptions() {
            auto offset = offsetOptions;
            return reinterpret_cast<const char*>(dynMem + offset);
        }

        std::vector<const char*> getHeader_include_names() {
            auto arrayOffset = offsetHeader_include_names;
            auto nestedArraysOffsets = reinterpret_cast<uint32_t*>(dynMem + arrayOffset);
            
            using ElementT = const char*;
            auto elCount = countHeader_include_names;
            std::vector<ElementT> ret;
            ret.reserve(elCount);
            for(uint32_t i = 0; i < elCount; ++i){
                ret.push_back(reinterpret_cast<ElementT>(dynMem + nestedArraysOffsets[i]));
            }
            return ret;
        }


        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        offsetInput_headers = dynamicTraits.input_headers.offset;
        offsetOptions = dynamicTraits.options.offset;
        offsetHeader_include_names = dynamicTraits.header_include_names.offset;
        countDevice_list = dynamicTraits.device_list.count;
        countInput_headers = dynamicTraits.input_headers.count;
        countOptions = dynamicTraits.options.count;
        countHeader_include_names = dynamicTraits.header_include_names.count;
            {
                auto nestedArraysOffsets = reinterpret_cast<uint32_t*>(dynMem + dynamicTraits.header_include_names.offset);
                for(uint32_t i = 0; i < dynamicTraits.header_include_names.count; ++i){
                    nestedArraysOffsets[i] = dynamicTraits.header_include_names.nested[i].offset;
                }
            }
            dynMemSize = dynamicTraits.totalDynamicSize;
        }
        
        uint32_t dynMemSize = 0;
        alignas(8) char dynMem[];
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClCompileProgramRpcM() = default;

    ClCompileProgramRpcM(const Captures::DynamicTraits &dynamicTraits, cl_program program, cl_uint num_devices, const cl_device_id* device_list, const char* options, cl_uint num_input_headers, const cl_program* input_headers, const char** header_include_names, void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data), void* user_data) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.program = program;
        args.num_devices = num_devices;
        args.device_list = device_list;
        args.options = options;
        args.num_input_headers = num_input_headers;
        args.input_headers = input_headers;
        args.header_include_names = header_include_names;
        args.pfn_notify = pfn_notify;
        args.user_data = user_data;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClCompileProgramRpcM &message, cl_program program, cl_uint num_devices, const cl_device_id* device_list, const char* options, cl_uint num_input_headers, const cl_program* input_headers, const char** header_include_names, void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data), void* user_data) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.program = program;
        message.args.num_devices = num_devices;
        message.args.device_list = device_list;
        message.args.options = options;
        message.args.num_input_headers = num_input_headers;
        message.args.input_headers = input_headers;
        message.args.header_include_names = header_include_names;
        message.args.pfn_notify = pfn_notify;
        message.args.user_data = user_data;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.device_list){
            memcpy(asMemcpyDstT(captures.getDevice_list()), args.device_list, dynMemTraits.device_list.size);
        }
        if(args.options){
            memcpy(asMemcpyDstT(captures.getOptions()), args.options, dynMemTraits.options.size);
        }
        if(args.input_headers){
            memcpy(asMemcpyDstT(captures.getInput_headers()), args.input_headers, dynMemTraits.input_headers.size);
        }
        if(args.header_include_names){
            {
                 auto array = captures.getHeader_include_names();
                 for(uint32_t i = 0; i < dynMemTraits.header_include_names.count; ++i) {
                     memcpy(asMemcpyDstT(array[i]), args.header_include_names[i], dynMemTraits.header_include_names.nested[i].size);
                 }
            }
        }
    }
};
static_assert(std::is_standard_layout_v<ClCompileProgramRpcM>);
struct ClLinkProgramRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 17;
    static constexpr float latency = 2.0;

    using ReturnValueT = cl_program;

    struct Args {
        cl_context context = {};
        cl_uint num_devices = {};
        const cl_device_id* device_list = {};
        const char* options = {};
        cl_uint num_input_programs = {};
        const cl_program* input_programs = {};
        void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data) = {};
        void* user_data = {};
        cl_int* errcode_ret = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->context == rhs.context;
            equal &= this->num_devices == rhs.num_devices;
            equal &= this->device_list == rhs.device_list;
            equal &= this->options == rhs.options;
            equal &= this->num_input_programs == rhs.num_input_programs;
            equal &= this->input_programs == rhs.input_programs;
            equal &= this->pfn_notify == rhs.pfn_notify;
            equal &= this->user_data == rhs.user_data;
            equal &= this->errcode_ret == rhs.errcode_ret;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_context context, cl_uint num_devices, const cl_device_id* device_list, const char* options, cl_uint num_input_programs, const cl_program* input_programs, void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data), void* user_data, cl_int* errcode_ret);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits device_list = {};          
            DynamicArgTraits input_programs = {};          
            DynamicArgTraits options = {};          
        };

        cl_program ret = {};
        cl_int errcode_ret;
        uint32_t offsetInput_programs = 0;
        uint32_t offsetOptions = 0;
        uint32_t countDevice_list = 0;
        uint32_t countInput_programs = 0;
        uint32_t countOptions = 0;
        const cl_device_id* getDevice_list() {
            auto offset = 0;
            return reinterpret_cast<const cl_device_id*>(dynMem + offset);
        }

        const cl_program* getInput_programs() {
            auto offset = offsetInput_programs;
            return reinterpret_cast<const cl_program*>(dynMem + offset);
        }

        const char* getOptions() {
            auto offset = offsetOptions;
            return reinterpret_cast<const char*>(dynMem + offset);
        }


        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        offsetInput_programs = dynamicTraits.input_programs.offset;
        offsetOptions = dynamicTraits.options.offset;
        countDevice_list = dynamicTraits.device_list.count;
        countInput_programs = dynamicTraits.input_programs.count;
        countOptions = dynamicTraits.options.count;
        }
        
        alignas(8) char dynMem[];
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_program returnValue(){
        return captures.ret;
    }

    ClLinkProgramRpcM() = default;

    ClLinkProgramRpcM(const Captures::DynamicTraits &dynamicTraits, cl_context context, cl_uint num_devices, const cl_device_id* device_list, const char* options, cl_uint num_input_programs, const cl_program* input_programs, void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data), void* user_data, cl_int* errcode_ret) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.context = context;
        args.num_devices = num_devices;
        args.device_list = device_list;
        args.options = options;
        args.num_input_programs = num_input_programs;
        args.input_programs = input_programs;
        args.pfn_notify = pfn_notify;
        args.user_data = user_data;
        args.errcode_ret = errcode_ret;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClLinkProgramRpcM &message, cl_context context, cl_uint num_devices, const cl_device_id* device_list, const char* options, cl_uint num_input_programs, const cl_program* input_programs, void (CL_CALLBACK* pfn_notify)(cl_program program, void* user_data), void* user_data, cl_int* errcode_ret) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.context = context;
        message.args.num_devices = num_devices;
        message.args.device_list = device_list;
        message.args.options = options;
        message.args.num_input_programs = num_input_programs;
        message.args.input_programs = input_programs;
        message.args.pfn_notify = pfn_notify;
        message.args.user_data = user_data;
        message.args.errcode_ret = errcode_ret;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.device_list){
            memcpy(asMemcpyDstT(captures.getDevice_list()), args.device_list, dynMemTraits.device_list.size);
        }
        if(args.options){
            memcpy(asMemcpyDstT(captures.getOptions()), args.options, dynMemTraits.options.size);
        }
        if(args.input_programs){
            memcpy(asMemcpyDstT(captures.getInput_programs()), args.input_programs, dynMemTraits.input_programs.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.errcode_ret){
            *args.errcode_ret = captures.errcode_ret;
        }
    }
};
static_assert(std::is_standard_layout_v<ClLinkProgramRpcM>);
struct ClGetProgramBuildInfoRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 18;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_program program = {};
        cl_device_id device = {};
        cl_program_build_info param_name = {};
        size_t param_value_size = {};
        void* param_value = {};
        size_t* param_value_size_ret = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->program == rhs.program;
            equal &= this->device == rhs.device;
            equal &= this->param_name == rhs.param_name;
            equal &= this->param_value_size == rhs.param_value_size;
            equal &= this->param_value == rhs.param_value;
            equal &= this->param_value_size_ret == rhs.param_value_size_ret;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_program program, cl_device_id device, cl_program_build_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits param_value = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        size_t param_value_size_ret;
        uint32_t countParam_value = 0;
        char param_value[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countParam_value = dynamicTraits.param_value.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClGetProgramBuildInfoRpcM() = default;

    ClGetProgramBuildInfoRpcM(const Captures::DynamicTraits &dynamicTraits, cl_program program, cl_device_id device, cl_program_build_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.program = program;
        args.device = device;
        args.param_name = param_name;
        args.param_value_size = param_value_size;
        args.param_value = param_value;
        args.param_value_size_ret = param_value_size_ret;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClGetProgramBuildInfoRpcM &message, cl_program program, cl_device_id device, cl_program_build_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.program = program;
        message.args.device = device;
        message.args.param_name = param_name;
        message.args.param_value_size = param_value_size;
        message.args.param_value = param_value;
        message.args.param_value_size_ret = param_value_size_ret;
    }
    

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.param_value){
            memcpy(args.param_value, captures.param_value, dynMemTraits.param_value.size);
        }
        if(args.param_value_size_ret){
            *args.param_value_size_ret = captures.param_value_size_ret;
        }
    }
};
static_assert(std::is_standard_layout_v<ClGetProgramBuildInfoRpcM>);
struct ClCreateKernelRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 19;
    static constexpr float latency = 0.5;

    using ReturnValueT = cl_kernel;

    struct Args {
        cl_program program = {};
        const char* kernel_name = {};
        cl_int* errcode_ret = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->program == rhs.program;
            equal &= this->kernel_name == rhs.kernel_name;
            equal &= this->errcode_ret == rhs.errcode_ret;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_program program, const char* kernel_name, cl_int* errcode_ret);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits kernel_name = {};          
        };

        cl_kernel ret = {};
        cl_int errcode_ret;
        uint32_t countKernel_name = 0;
        char kernel_name[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countKernel_name = dynamicTraits.kernel_name.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_kernel returnValue(){
        return captures.ret;
    }

    ClCreateKernelRpcM() = default;

    ClCreateKernelRpcM(const Captures::DynamicTraits &dynamicTraits, cl_program program, const char* kernel_name, cl_int* errcode_ret) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.program = program;
        args.kernel_name = kernel_name;
        args.errcode_ret = errcode_ret;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClCreateKernelRpcM &message, cl_program program, const char* kernel_name, cl_int* errcode_ret) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.program = program;
        message.args.kernel_name = kernel_name;
        message.args.errcode_ret = errcode_ret;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.kernel_name){
            memcpy(asMemcpyDstT(captures.kernel_name), args.kernel_name, dynMemTraits.kernel_name.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.errcode_ret){
            *args.errcode_ret = captures.errcode_ret;
        }
    }
};
static_assert(std::is_standard_layout_v<ClCreateKernelRpcM>);
struct ClCloneKernelRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 20;
    static constexpr float latency = 0.5;

    using ReturnValueT = cl_kernel;

    struct Args {
        cl_kernel source_kernel = {};
        cl_int* errcode_ret = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->source_kernel == rhs.source_kernel;
            equal &= this->errcode_ret == rhs.errcode_ret;
            return equal;
        }
    }args;

    struct Captures {

        cl_kernel ret = {};
        cl_int errcode_ret;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_kernel returnValue(){
        return captures.ret;
    }

    ClCloneKernelRpcM() = default;

    ClCloneKernelRpcM(cl_kernel source_kernel, cl_int* errcode_ret) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.source_kernel = source_kernel;
        args.errcode_ret = errcode_ret;
    }
    
    static void fillWithoutCapture(ClCloneKernelRpcM &message, cl_kernel source_kernel, cl_int* errcode_ret) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.source_kernel = source_kernel;
        message.args.errcode_ret = errcode_ret;
    }
    

    void copyToCaller(){
        if(args.errcode_ret){
            *args.errcode_ret = captures.errcode_ret;
        }
    }
};
static_assert(std::is_standard_layout_v<ClCloneKernelRpcM>);
struct ClCreateKernelsInProgramRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 21;
    static constexpr float latency = 1.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_program program = {};
        cl_uint num_kernels = {};
        cl_kernel* kernels = {};
        cl_uint* num_kernels_ret = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->program == rhs.program;
            equal &= this->num_kernels == rhs.num_kernels;
            equal &= this->kernels == rhs.kernels;
            equal &= this->num_kernels_ret == rhs.num_kernels_ret;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_program program, cl_uint num_kernels, cl_kernel* kernels, cl_uint* num_kernels_ret);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits kernels = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        cl_uint num_kernels_ret;
        uint32_t countKernels = 0;
        cl_kernel kernels[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countKernels = dynamicTraits.kernels.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClCreateKernelsInProgramRpcM() = default;

    ClCreateKernelsInProgramRpcM(const Captures::DynamicTraits &dynamicTraits, cl_program program, cl_uint num_kernels, cl_kernel* kernels, cl_uint* num_kernels_ret) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.program = program;
        args.num_kernels = num_kernels;
        args.kernels = kernels;
        args.num_kernels_ret = num_kernels_ret;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClCreateKernelsInProgramRpcM &message, cl_program program, cl_uint num_kernels, cl_kernel* kernels, cl_uint* num_kernels_ret) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.program = program;
        message.args.num_kernels = num_kernels;
        message.args.kernels = kernels;
        message.args.num_kernels_ret = num_kernels_ret;
    }
    

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.kernels){
            memcpy(args.kernels, captures.kernels, dynMemTraits.kernels.size);
        }
        if(args.num_kernels_ret){
            *args.num_kernels_ret = captures.num_kernels_ret;
        }
    }
};
static_assert(std::is_standard_layout_v<ClCreateKernelsInProgramRpcM>);
struct ClGetCommandQueueInfoRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 22;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_command_queue command_queue = {};
        cl_command_queue_info param_name = {};
        size_t param_value_size = {};
        void* param_value = {};
        size_t* param_value_size_ret = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->command_queue == rhs.command_queue;
            equal &= this->param_name == rhs.param_name;
            equal &= this->param_value_size == rhs.param_value_size;
            equal &= this->param_value == rhs.param_value;
            equal &= this->param_value_size_ret == rhs.param_value_size_ret;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_command_queue command_queue, cl_command_queue_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits param_value = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        size_t param_value_size_ret;
        uint32_t countParam_value = 0;
        char param_value[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countParam_value = dynamicTraits.param_value.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClGetCommandQueueInfoRpcM() = default;

    ClGetCommandQueueInfoRpcM(const Captures::DynamicTraits &dynamicTraits, cl_command_queue command_queue, cl_command_queue_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.command_queue = command_queue;
        args.param_name = param_name;
        args.param_value_size = param_value_size;
        args.param_value = param_value;
        args.param_value_size_ret = param_value_size_ret;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClGetCommandQueueInfoRpcM &message, cl_command_queue command_queue, cl_command_queue_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.command_queue = command_queue;
        message.args.param_name = param_name;
        message.args.param_value_size = param_value_size;
        message.args.param_value = param_value;
        message.args.param_value_size_ret = param_value_size_ret;
    }
    

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.param_value){
            memcpy(args.param_value, captures.param_value, dynMemTraits.param_value.size);
        }
        if(args.param_value_size_ret){
            *args.param_value_size_ret = captures.param_value_size_ret;
        }
    }
};
static_assert(std::is_standard_layout_v<ClGetCommandQueueInfoRpcM>);
 // clGetProgramInfo ignored in generator - based on dont_generate_rpc_message flag
struct ClGetProgramInfoRpcHelperRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 23;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_program program = {};
        cl_program_info param_name = {};
        size_t param_value_size = {};
        void* param_value = {};
        size_t* param_value_size_ret = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->program == rhs.program;
            equal &= this->param_name == rhs.param_name;
            equal &= this->param_value_size == rhs.param_value_size;
            equal &= this->param_value == rhs.param_value;
            equal &= this->param_value_size_ret == rhs.param_value_size_ret;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_program program, cl_program_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits param_value = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        size_t param_value_size_ret;
        uint32_t countParam_value = 0;
        char param_value[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countParam_value = dynamicTraits.param_value.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClGetProgramInfoRpcHelperRpcM() = default;

    ClGetProgramInfoRpcHelperRpcM(const Captures::DynamicTraits &dynamicTraits, cl_program program, cl_program_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.program = program;
        args.param_name = param_name;
        args.param_value_size = param_value_size;
        args.param_value = param_value;
        args.param_value_size_ret = param_value_size_ret;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClGetProgramInfoRpcHelperRpcM &message, cl_program program, cl_program_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.program = program;
        message.args.param_name = param_name;
        message.args.param_value_size = param_value_size;
        message.args.param_value = param_value;
        message.args.param_value_size_ret = param_value_size_ret;
    }
    

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.param_value){
            memcpy(args.param_value, captures.param_value, dynMemTraits.param_value.size);
        }
        if(args.param_value_size_ret){
            *args.param_value_size_ret = captures.param_value_size_ret;
        }
    }
};
static_assert(std::is_standard_layout_v<ClGetProgramInfoRpcHelperRpcM>);
struct ClGetProgramInfoGetBinariesRpcHelperRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 24;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_program program = {};
        size_t total_binaries_size = {};
        unsigned char* concatenated_binaries = {};
        size_t binaries_count = {};
        const size_t* binaries_lengths = {};
        size_t* param_value_size_ret = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->program == rhs.program;
            equal &= this->total_binaries_size == rhs.total_binaries_size;
            equal &= this->concatenated_binaries == rhs.concatenated_binaries;
            equal &= this->binaries_count == rhs.binaries_count;
            equal &= this->binaries_lengths == rhs.binaries_lengths;
            equal &= this->param_value_size_ret == rhs.param_value_size_ret;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_program program, size_t total_binaries_size, unsigned char* concatenated_binaries, size_t binaries_count, const size_t* binaries_lengths, size_t* param_value_size_ret);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits concatenated_binaries = {};          
            DynamicArgTraits binaries_lengths = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        size_t param_value_size_ret;
        uint32_t offsetBinaries_lengths = 0;
        uint32_t countConcatenated_binaries = 0;
        uint32_t countBinaries_lengths = 0;
        unsigned char* getConcatenated_binaries() {
            auto offset = 0;
            return reinterpret_cast<unsigned char*>(dynMem + offset);
        }

        const size_t* getBinaries_lengths() {
            auto offset = offsetBinaries_lengths;
            return reinterpret_cast<const size_t*>(dynMem + offset);
        }


        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        offsetBinaries_lengths = dynamicTraits.binaries_lengths.offset;
        countConcatenated_binaries = dynamicTraits.concatenated_binaries.count;
        countBinaries_lengths = dynamicTraits.binaries_lengths.count;
        }
        
        alignas(8) char dynMem[];
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClGetProgramInfoGetBinariesRpcHelperRpcM() = default;

    ClGetProgramInfoGetBinariesRpcHelperRpcM(const Captures::DynamicTraits &dynamicTraits, cl_program program, size_t total_binaries_size, unsigned char* concatenated_binaries, size_t binaries_count, const size_t* binaries_lengths, size_t* param_value_size_ret) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.program = program;
        args.total_binaries_size = total_binaries_size;
        args.concatenated_binaries = concatenated_binaries;
        args.binaries_count = binaries_count;
        args.binaries_lengths = binaries_lengths;
        args.param_value_size_ret = param_value_size_ret;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClGetProgramInfoGetBinariesRpcHelperRpcM &message, cl_program program, size_t total_binaries_size, unsigned char* concatenated_binaries, size_t binaries_count, const size_t* binaries_lengths, size_t* param_value_size_ret) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.program = program;
        message.args.total_binaries_size = total_binaries_size;
        message.args.concatenated_binaries = concatenated_binaries;
        message.args.binaries_count = binaries_count;
        message.args.binaries_lengths = binaries_lengths;
        message.args.param_value_size_ret = param_value_size_ret;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.binaries_lengths){
            memcpy(asMemcpyDstT(captures.getBinaries_lengths()), args.binaries_lengths, dynMemTraits.binaries_lengths.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.concatenated_binaries){
            memcpy(args.concatenated_binaries, captures.getConcatenated_binaries(), dynMemTraits.concatenated_binaries.size);
        }
        if(args.param_value_size_ret){
            *args.param_value_size_ret = captures.param_value_size_ret;
        }
    }
};
static_assert(std::is_standard_layout_v<ClGetProgramInfoGetBinariesRpcHelperRpcM>);
struct ClGetMemObjectInfoRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 25;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_mem memobj = {};
        cl_mem_info param_name = {};
        size_t param_value_size = {};
        void* param_value = {};
        size_t* param_value_size_ret = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->memobj == rhs.memobj;
            equal &= this->param_name == rhs.param_name;
            equal &= this->param_value_size == rhs.param_value_size;
            equal &= this->param_value == rhs.param_value;
            equal &= this->param_value_size_ret == rhs.param_value_size_ret;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_mem memobj, cl_mem_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits param_value = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        size_t param_value_size_ret;
        uint32_t countParam_value = 0;
        char param_value[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countParam_value = dynamicTraits.param_value.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClGetMemObjectInfoRpcM() = default;

    ClGetMemObjectInfoRpcM(const Captures::DynamicTraits &dynamicTraits, cl_mem memobj, cl_mem_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.memobj = memobj;
        args.param_name = param_name;
        args.param_value_size = param_value_size;
        args.param_value = param_value;
        args.param_value_size_ret = param_value_size_ret;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClGetMemObjectInfoRpcM &message, cl_mem memobj, cl_mem_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.memobj = memobj;
        message.args.param_name = param_name;
        message.args.param_value_size = param_value_size;
        message.args.param_value = param_value;
        message.args.param_value_size_ret = param_value_size_ret;
    }
    

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.param_value){
            memcpy(args.param_value, captures.param_value, dynMemTraits.param_value.size);
        }
        if(args.param_value_size_ret){
            *args.param_value_size_ret = captures.param_value_size_ret;
        }
    }
};
static_assert(std::is_standard_layout_v<ClGetMemObjectInfoRpcM>);
struct ClGetImageInfoRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 26;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_mem image = {};
        cl_image_info param_name = {};
        size_t param_value_size = {};
        void* param_value = {};
        size_t* param_value_size_ret = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->image == rhs.image;
            equal &= this->param_name == rhs.param_name;
            equal &= this->param_value_size == rhs.param_value_size;
            equal &= this->param_value == rhs.param_value;
            equal &= this->param_value_size_ret == rhs.param_value_size_ret;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_mem image, cl_image_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits param_value = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        size_t param_value_size_ret;
        uint32_t countParam_value = 0;
        char param_value[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countParam_value = dynamicTraits.param_value.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClGetImageInfoRpcM() = default;

    ClGetImageInfoRpcM(const Captures::DynamicTraits &dynamicTraits, cl_mem image, cl_image_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.image = image;
        args.param_name = param_name;
        args.param_value_size = param_value_size;
        args.param_value = param_value;
        args.param_value_size_ret = param_value_size_ret;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClGetImageInfoRpcM &message, cl_mem image, cl_image_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.image = image;
        message.args.param_name = param_name;
        message.args.param_value_size = param_value_size;
        message.args.param_value = param_value;
        message.args.param_value_size_ret = param_value_size_ret;
    }
    

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.param_value){
            memcpy(args.param_value, captures.param_value, dynMemTraits.param_value.size);
        }
        if(args.param_value_size_ret){
            *args.param_value_size_ret = captures.param_value_size_ret;
        }
    }
};
static_assert(std::is_standard_layout_v<ClGetImageInfoRpcM>);
struct ClGetSamplerInfoRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 27;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_sampler sampler = {};
        cl_sampler_info param_name = {};
        size_t param_value_size = {};
        void* param_value = {};
        size_t* param_value_size_ret = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->sampler == rhs.sampler;
            equal &= this->param_name == rhs.param_name;
            equal &= this->param_value_size == rhs.param_value_size;
            equal &= this->param_value == rhs.param_value;
            equal &= this->param_value_size_ret == rhs.param_value_size_ret;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_sampler sampler, cl_sampler_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits param_value = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        size_t param_value_size_ret;
        uint32_t countParam_value = 0;
        char param_value[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countParam_value = dynamicTraits.param_value.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClGetSamplerInfoRpcM() = default;

    ClGetSamplerInfoRpcM(const Captures::DynamicTraits &dynamicTraits, cl_sampler sampler, cl_sampler_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.sampler = sampler;
        args.param_name = param_name;
        args.param_value_size = param_value_size;
        args.param_value = param_value;
        args.param_value_size_ret = param_value_size_ret;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClGetSamplerInfoRpcM &message, cl_sampler sampler, cl_sampler_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.sampler = sampler;
        message.args.param_name = param_name;
        message.args.param_value_size = param_value_size;
        message.args.param_value = param_value;
        message.args.param_value_size_ret = param_value_size_ret;
    }
    

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.param_value){
            memcpy(args.param_value, captures.param_value, dynMemTraits.param_value.size);
        }
        if(args.param_value_size_ret){
            *args.param_value_size_ret = captures.param_value_size_ret;
        }
    }
};
static_assert(std::is_standard_layout_v<ClGetSamplerInfoRpcM>);
struct ClGetKernelInfoRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 28;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_kernel kernel = {};
        cl_kernel_info param_name = {};
        size_t param_value_size = {};
        void* param_value = {};
        size_t* param_value_size_ret = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->kernel == rhs.kernel;
            equal &= this->param_name == rhs.param_name;
            equal &= this->param_value_size == rhs.param_value_size;
            equal &= this->param_value == rhs.param_value;
            equal &= this->param_value_size_ret == rhs.param_value_size_ret;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_kernel kernel, cl_kernel_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits param_value = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        size_t param_value_size_ret;
        uint32_t countParam_value = 0;
        char param_value[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countParam_value = dynamicTraits.param_value.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClGetKernelInfoRpcM() = default;

    ClGetKernelInfoRpcM(const Captures::DynamicTraits &dynamicTraits, cl_kernel kernel, cl_kernel_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.kernel = kernel;
        args.param_name = param_name;
        args.param_value_size = param_value_size;
        args.param_value = param_value;
        args.param_value_size_ret = param_value_size_ret;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClGetKernelInfoRpcM &message, cl_kernel kernel, cl_kernel_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.kernel = kernel;
        message.args.param_name = param_name;
        message.args.param_value_size = param_value_size;
        message.args.param_value = param_value;
        message.args.param_value_size_ret = param_value_size_ret;
    }
    

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.param_value){
            memcpy(args.param_value, captures.param_value, dynMemTraits.param_value.size);
        }
        if(args.param_value_size_ret){
            *args.param_value_size_ret = captures.param_value_size_ret;
        }
    }
};
static_assert(std::is_standard_layout_v<ClGetKernelInfoRpcM>);
struct ClGetKernelWorkGroupInfoRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 29;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_kernel kernel = {};
        cl_device_id device = {};
        cl_kernel_work_group_info param_name = {};
        size_t param_value_size = {};
        void* param_value = {};
        size_t* param_value_size_ret = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->kernel == rhs.kernel;
            equal &= this->device == rhs.device;
            equal &= this->param_name == rhs.param_name;
            equal &= this->param_value_size == rhs.param_value_size;
            equal &= this->param_value == rhs.param_value;
            equal &= this->param_value_size_ret == rhs.param_value_size_ret;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_kernel kernel, cl_device_id device, cl_kernel_work_group_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits param_value = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        size_t param_value_size_ret;
        uint32_t countParam_value = 0;
        char param_value[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countParam_value = dynamicTraits.param_value.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClGetKernelWorkGroupInfoRpcM() = default;

    ClGetKernelWorkGroupInfoRpcM(const Captures::DynamicTraits &dynamicTraits, cl_kernel kernel, cl_device_id device, cl_kernel_work_group_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.kernel = kernel;
        args.device = device;
        args.param_name = param_name;
        args.param_value_size = param_value_size;
        args.param_value = param_value;
        args.param_value_size_ret = param_value_size_ret;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClGetKernelWorkGroupInfoRpcM &message, cl_kernel kernel, cl_device_id device, cl_kernel_work_group_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.kernel = kernel;
        message.args.device = device;
        message.args.param_name = param_name;
        message.args.param_value_size = param_value_size;
        message.args.param_value = param_value;
        message.args.param_value_size_ret = param_value_size_ret;
    }
    

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.param_value){
            memcpy(args.param_value, captures.param_value, dynMemTraits.param_value.size);
        }
        if(args.param_value_size_ret){
            *args.param_value_size_ret = captures.param_value_size_ret;
        }
    }
};
static_assert(std::is_standard_layout_v<ClGetKernelWorkGroupInfoRpcM>);
struct ClGetKernelArgInfoRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 30;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_kernel kernel = {};
        cl_uint arg_indx = {};
        cl_kernel_arg_info param_name = {};
        size_t param_value_size = {};
        void* param_value = {};
        size_t* param_value_size_ret = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->kernel == rhs.kernel;
            equal &= this->arg_indx == rhs.arg_indx;
            equal &= this->param_name == rhs.param_name;
            equal &= this->param_value_size == rhs.param_value_size;
            equal &= this->param_value == rhs.param_value;
            equal &= this->param_value_size_ret == rhs.param_value_size_ret;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_kernel kernel, cl_uint arg_indx, cl_kernel_arg_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits param_value = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        size_t param_value_size_ret;
        uint32_t countParam_value = 0;
        char param_value[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countParam_value = dynamicTraits.param_value.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClGetKernelArgInfoRpcM() = default;

    ClGetKernelArgInfoRpcM(const Captures::DynamicTraits &dynamicTraits, cl_kernel kernel, cl_uint arg_indx, cl_kernel_arg_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.kernel = kernel;
        args.arg_indx = arg_indx;
        args.param_name = param_name;
        args.param_value_size = param_value_size;
        args.param_value = param_value;
        args.param_value_size_ret = param_value_size_ret;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClGetKernelArgInfoRpcM &message, cl_kernel kernel, cl_uint arg_indx, cl_kernel_arg_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.kernel = kernel;
        message.args.arg_indx = arg_indx;
        message.args.param_name = param_name;
        message.args.param_value_size = param_value_size;
        message.args.param_value = param_value;
        message.args.param_value_size_ret = param_value_size_ret;
    }
    

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.param_value){
            memcpy(args.param_value, captures.param_value, dynMemTraits.param_value.size);
        }
        if(args.param_value_size_ret){
            *args.param_value_size_ret = captures.param_value_size_ret;
        }
    }
};
static_assert(std::is_standard_layout_v<ClGetKernelArgInfoRpcM>);
struct ClGetKernelSubGroupInfoRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 31;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_kernel kernel = {};
        cl_device_id device = {};
        cl_kernel_sub_group_info param_name = {};
        size_t input_value_size = {};
        const void* input_value = {};
        size_t param_value_size = {};
        void* param_value = {};
        size_t* param_value_size_ret = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->kernel == rhs.kernel;
            equal &= this->device == rhs.device;
            equal &= this->param_name == rhs.param_name;
            equal &= this->input_value_size == rhs.input_value_size;
            equal &= this->input_value == rhs.input_value;
            equal &= this->param_value_size == rhs.param_value_size;
            equal &= this->param_value == rhs.param_value;
            equal &= this->param_value_size_ret == rhs.param_value_size_ret;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_kernel kernel, cl_device_id device, cl_kernel_sub_group_info param_name, size_t input_value_size, const void* input_value, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits input_value = {};          
            DynamicArgTraits param_value = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        size_t param_value_size_ret;
        uint32_t offsetParam_value = 0;
        uint32_t countInput_value = 0;
        uint32_t countParam_value = 0;
        const void* getInput_value() {
            auto offset = 0;
            return reinterpret_cast<const void*>(dynMem + offset);
        }

        void* getParam_value() {
            auto offset = offsetParam_value;
            return reinterpret_cast<void*>(dynMem + offset);
        }


        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        offsetParam_value = dynamicTraits.param_value.offset;
        countInput_value = dynamicTraits.input_value.count;
        countParam_value = dynamicTraits.param_value.count;
        }
        
        alignas(8) char dynMem[];
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClGetKernelSubGroupInfoRpcM() = default;

    ClGetKernelSubGroupInfoRpcM(const Captures::DynamicTraits &dynamicTraits, cl_kernel kernel, cl_device_id device, cl_kernel_sub_group_info param_name, size_t input_value_size, const void* input_value, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.kernel = kernel;
        args.device = device;
        args.param_name = param_name;
        args.input_value_size = input_value_size;
        args.input_value = input_value;
        args.param_value_size = param_value_size;
        args.param_value = param_value;
        args.param_value_size_ret = param_value_size_ret;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClGetKernelSubGroupInfoRpcM &message, cl_kernel kernel, cl_device_id device, cl_kernel_sub_group_info param_name, size_t input_value_size, const void* input_value, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.kernel = kernel;
        message.args.device = device;
        message.args.param_name = param_name;
        message.args.input_value_size = input_value_size;
        message.args.input_value = input_value;
        message.args.param_value_size = param_value_size;
        message.args.param_value = param_value;
        message.args.param_value_size_ret = param_value_size_ret;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.input_value){
            memcpy(asMemcpyDstT(captures.getInput_value()), args.input_value, dynMemTraits.input_value.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.param_value){
            memcpy(args.param_value, captures.getParam_value(), dynMemTraits.param_value.size);
        }
        if(args.param_value_size_ret){
            *args.param_value_size_ret = captures.param_value_size_ret;
        }
    }
};
static_assert(std::is_standard_layout_v<ClGetKernelSubGroupInfoRpcM>);
struct ClReleaseCommandQueueRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 32;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_command_queue command_queue = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->command_queue == rhs.command_queue;
            return equal;
        }
    }args;

    struct Captures {

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClReleaseCommandQueueRpcM() = default;

    ClReleaseCommandQueueRpcM(cl_command_queue command_queue) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.command_queue = command_queue;
    }
    
    static void fillWithoutCapture(ClReleaseCommandQueueRpcM &message, cl_command_queue command_queue) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.command_queue = command_queue;
    }
    
};
static_assert(std::is_standard_layout_v<ClReleaseCommandQueueRpcM>);
struct ClReleaseContextRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 33;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_context context = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->context == rhs.context;
            return equal;
        }
    }args;

    struct Captures {

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClReleaseContextRpcM() = default;

    ClReleaseContextRpcM(cl_context context) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.context = context;
    }
    
    static void fillWithoutCapture(ClReleaseContextRpcM &message, cl_context context) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.context = context;
    }
    
};
static_assert(std::is_standard_layout_v<ClReleaseContextRpcM>);
struct ClReleaseDeviceRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 34;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_device_id device = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->device == rhs.device;
            return equal;
        }
    }args;

    struct Captures {

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClReleaseDeviceRpcM() = default;

    ClReleaseDeviceRpcM(cl_device_id device) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.device = device;
    }
    
    static void fillWithoutCapture(ClReleaseDeviceRpcM &message, cl_device_id device) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.device = device;
    }
    
};
static_assert(std::is_standard_layout_v<ClReleaseDeviceRpcM>);
struct ClReleaseKernelRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 35;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_kernel kernel = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->kernel == rhs.kernel;
            return equal;
        }
    }args;

    struct Captures {

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClReleaseKernelRpcM() = default;

    ClReleaseKernelRpcM(cl_kernel kernel) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.kernel = kernel;
    }
    
    static void fillWithoutCapture(ClReleaseKernelRpcM &message, cl_kernel kernel) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.kernel = kernel;
    }
    
};
static_assert(std::is_standard_layout_v<ClReleaseKernelRpcM>);
struct ClReleaseSamplerRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 36;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_sampler sampler = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->sampler == rhs.sampler;
            return equal;
        }
    }args;

    struct Captures {

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClReleaseSamplerRpcM() = default;

    ClReleaseSamplerRpcM(cl_sampler sampler) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.sampler = sampler;
    }
    
    static void fillWithoutCapture(ClReleaseSamplerRpcM &message, cl_sampler sampler) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.sampler = sampler;
    }
    
};
static_assert(std::is_standard_layout_v<ClReleaseSamplerRpcM>);
struct ClReleaseProgramRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 37;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_program program = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->program == rhs.program;
            return equal;
        }
    }args;

    struct Captures {

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClReleaseProgramRpcM() = default;

    ClReleaseProgramRpcM(cl_program program) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.program = program;
    }
    
    static void fillWithoutCapture(ClReleaseProgramRpcM &message, cl_program program) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.program = program;
    }
    
};
static_assert(std::is_standard_layout_v<ClReleaseProgramRpcM>);
struct ClReleaseMemObjectRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 38;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_mem memobj = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->memobj == rhs.memobj;
            return equal;
        }
    }args;

    struct Captures {

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClReleaseMemObjectRpcM() = default;

    ClReleaseMemObjectRpcM(cl_mem memobj) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.memobj = memobj;
    }
    
    static void fillWithoutCapture(ClReleaseMemObjectRpcM &message, cl_mem memobj) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.memobj = memobj;
    }
    
};
static_assert(std::is_standard_layout_v<ClReleaseMemObjectRpcM>);
struct ClReleaseEventRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 39;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_event event = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->event == rhs.event;
            return equal;
        }
    }args;

    struct Captures {

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClReleaseEventRpcM() = default;

    ClReleaseEventRpcM(cl_event event) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.event = event;
    }
    
    static void fillWithoutCapture(ClReleaseEventRpcM &message, cl_event event) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.event = event;
    }
    
};
static_assert(std::is_standard_layout_v<ClReleaseEventRpcM>);
struct ClRetainCommandQueueRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 40;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_command_queue command_queue = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->command_queue == rhs.command_queue;
            return equal;
        }
    }args;

    struct Captures {

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClRetainCommandQueueRpcM() = default;

    ClRetainCommandQueueRpcM(cl_command_queue command_queue) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.command_queue = command_queue;
    }
    
    static void fillWithoutCapture(ClRetainCommandQueueRpcM &message, cl_command_queue command_queue) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.command_queue = command_queue;
    }
    
};
static_assert(std::is_standard_layout_v<ClRetainCommandQueueRpcM>);
struct ClRetainContextRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 41;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_context context = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->context == rhs.context;
            return equal;
        }
    }args;

    struct Captures {

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClRetainContextRpcM() = default;

    ClRetainContextRpcM(cl_context context) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.context = context;
    }
    
    static void fillWithoutCapture(ClRetainContextRpcM &message, cl_context context) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.context = context;
    }
    
};
static_assert(std::is_standard_layout_v<ClRetainContextRpcM>);
struct ClRetainDeviceRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 42;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_device_id device = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->device == rhs.device;
            return equal;
        }
    }args;

    struct Captures {

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClRetainDeviceRpcM() = default;

    ClRetainDeviceRpcM(cl_device_id device) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.device = device;
    }
    
    static void fillWithoutCapture(ClRetainDeviceRpcM &message, cl_device_id device) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.device = device;
    }
    
};
static_assert(std::is_standard_layout_v<ClRetainDeviceRpcM>);
struct ClRetainProgramRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 43;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_program program = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->program == rhs.program;
            return equal;
        }
    }args;

    struct Captures {

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClRetainProgramRpcM() = default;

    ClRetainProgramRpcM(cl_program program) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.program = program;
    }
    
    static void fillWithoutCapture(ClRetainProgramRpcM &message, cl_program program) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.program = program;
    }
    
};
static_assert(std::is_standard_layout_v<ClRetainProgramRpcM>);
struct ClRetainMemObjectRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 44;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_mem memobj = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->memobj == rhs.memobj;
            return equal;
        }
    }args;

    struct Captures {

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClRetainMemObjectRpcM() = default;

    ClRetainMemObjectRpcM(cl_mem memobj) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.memobj = memobj;
    }
    
    static void fillWithoutCapture(ClRetainMemObjectRpcM &message, cl_mem memobj) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.memobj = memobj;
    }
    
};
static_assert(std::is_standard_layout_v<ClRetainMemObjectRpcM>);
struct ClRetainSamplerRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 45;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_sampler sampler = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->sampler == rhs.sampler;
            return equal;
        }
    }args;

    struct Captures {

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClRetainSamplerRpcM() = default;

    ClRetainSamplerRpcM(cl_sampler sampler) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.sampler = sampler;
    }
    
    static void fillWithoutCapture(ClRetainSamplerRpcM &message, cl_sampler sampler) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.sampler = sampler;
    }
    
};
static_assert(std::is_standard_layout_v<ClRetainSamplerRpcM>);
struct ClRetainKernelRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 46;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_kernel kernel = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->kernel == rhs.kernel;
            return equal;
        }
    }args;

    struct Captures {

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClRetainKernelRpcM() = default;

    ClRetainKernelRpcM(cl_kernel kernel) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.kernel = kernel;
    }
    
    static void fillWithoutCapture(ClRetainKernelRpcM &message, cl_kernel kernel) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.kernel = kernel;
    }
    
};
static_assert(std::is_standard_layout_v<ClRetainKernelRpcM>);
struct ClRetainEventRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 47;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_event event = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->event == rhs.event;
            return equal;
        }
    }args;

    struct Captures {

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClRetainEventRpcM() = default;

    ClRetainEventRpcM(cl_event event) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.event = event;
    }
    
    static void fillWithoutCapture(ClRetainEventRpcM &message, cl_event event) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.event = event;
    }
    
};
static_assert(std::is_standard_layout_v<ClRetainEventRpcM>);
struct ClFlushRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 48;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_command_queue command_queue = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->command_queue == rhs.command_queue;
            return equal;
        }
    }args;

    struct Captures {

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClFlushRpcM() = default;

    ClFlushRpcM(cl_command_queue command_queue) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.command_queue = command_queue;
    }
    
    static void fillWithoutCapture(ClFlushRpcM &message, cl_command_queue command_queue) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.command_queue = command_queue;
    }
    
};
static_assert(std::is_standard_layout_v<ClFlushRpcM>);
struct ClFinishRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 49;
    static constexpr float latency = 2.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_command_queue command_queue = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->command_queue == rhs.command_queue;
            return equal;
        }
    }args;

    struct Captures {

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClFinishRpcM() = default;

    ClFinishRpcM(cl_command_queue command_queue) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.command_queue = command_queue;
    }
    
    static void fillWithoutCapture(ClFinishRpcM &message, cl_command_queue command_queue) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.command_queue = command_queue;
    }
    
};
static_assert(std::is_standard_layout_v<ClFinishRpcM>);
struct ClEnqueueNDRangeKernelRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 50;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_command_queue command_queue = {};
        cl_kernel kernel = {};
        cl_uint work_dim = {};
        const size_t* global_work_offset = {};
        const size_t* global_work_size = {};
        const size_t* local_work_size = {};
        cl_uint num_events_in_wait_list = {};
        const cl_event* event_wait_list = {};
        cl_event* event = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->command_queue == rhs.command_queue;
            equal &= this->kernel == rhs.kernel;
            equal &= this->work_dim == rhs.work_dim;
            equal &= this->global_work_offset == rhs.global_work_offset;
            equal &= this->global_work_size == rhs.global_work_size;
            equal &= this->local_work_size == rhs.local_work_size;
            equal &= this->num_events_in_wait_list == rhs.num_events_in_wait_list;
            equal &= this->event_wait_list == rhs.event_wait_list;
            equal &= this->event == rhs.event;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_command_queue command_queue, cl_kernel kernel, cl_uint work_dim, const size_t* global_work_offset, const size_t* global_work_size, const size_t* local_work_size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits global_work_offset = {};          
            DynamicArgTraits global_work_size = {};          
            DynamicArgTraits local_work_size = {};          
            DynamicArgTraits event_wait_list = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        cl_event event;
        uint32_t offsetGlobal_work_size = 0;
        uint32_t offsetLocal_work_size = 0;
        uint32_t offsetEvent_wait_list = 0;
        uint32_t countGlobal_work_offset = 0;
        uint32_t countGlobal_work_size = 0;
        uint32_t countLocal_work_size = 0;
        uint32_t countEvent_wait_list = 0;
        const size_t* getGlobal_work_offset() {
            auto offset = 0;
            return reinterpret_cast<const size_t*>(dynMem + offset);
        }

        const size_t* getGlobal_work_size() {
            auto offset = offsetGlobal_work_size;
            return reinterpret_cast<const size_t*>(dynMem + offset);
        }

        const size_t* getLocal_work_size() {
            auto offset = offsetLocal_work_size;
            return reinterpret_cast<const size_t*>(dynMem + offset);
        }

        const cl_event* getEvent_wait_list() {
            auto offset = offsetEvent_wait_list;
            return reinterpret_cast<const cl_event*>(dynMem + offset);
        }


        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        offsetGlobal_work_size = dynamicTraits.global_work_size.offset;
        offsetLocal_work_size = dynamicTraits.local_work_size.offset;
        offsetEvent_wait_list = dynamicTraits.event_wait_list.offset;
        countGlobal_work_offset = dynamicTraits.global_work_offset.count;
        countGlobal_work_size = dynamicTraits.global_work_size.count;
        countLocal_work_size = dynamicTraits.local_work_size.count;
        countEvent_wait_list = dynamicTraits.event_wait_list.count;
        }
        
        alignas(8) char dynMem[];
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClEnqueueNDRangeKernelRpcM() = default;

    ClEnqueueNDRangeKernelRpcM(const Captures::DynamicTraits &dynamicTraits, cl_command_queue command_queue, cl_kernel kernel, cl_uint work_dim, const size_t* global_work_offset, const size_t* global_work_size, const size_t* local_work_size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.command_queue = command_queue;
        args.kernel = kernel;
        args.work_dim = work_dim;
        args.global_work_offset = global_work_offset;
        args.global_work_size = global_work_size;
        args.local_work_size = local_work_size;
        args.num_events_in_wait_list = num_events_in_wait_list;
        args.event_wait_list = event_wait_list;
        args.event = event;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClEnqueueNDRangeKernelRpcM &message, cl_command_queue command_queue, cl_kernel kernel, cl_uint work_dim, const size_t* global_work_offset, const size_t* global_work_size, const size_t* local_work_size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.command_queue = command_queue;
        message.args.kernel = kernel;
        message.args.work_dim = work_dim;
        message.args.global_work_offset = global_work_offset;
        message.args.global_work_size = global_work_size;
        message.args.local_work_size = local_work_size;
        message.args.num_events_in_wait_list = num_events_in_wait_list;
        message.args.event_wait_list = event_wait_list;
        message.args.event = event;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.global_work_offset){
            memcpy(asMemcpyDstT(captures.getGlobal_work_offset()), args.global_work_offset, dynMemTraits.global_work_offset.size);
        }
        if(args.global_work_size){
            memcpy(asMemcpyDstT(captures.getGlobal_work_size()), args.global_work_size, dynMemTraits.global_work_size.size);
        }
        if(args.local_work_size){
            memcpy(asMemcpyDstT(captures.getLocal_work_size()), args.local_work_size, dynMemTraits.local_work_size.size);
        }
        if(args.event_wait_list){
            memcpy(asMemcpyDstT(captures.getEvent_wait_list()), args.event_wait_list, dynMemTraits.event_wait_list.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event){
            *args.event = captures.event;
        }
    }
};
static_assert(std::is_standard_layout_v<ClEnqueueNDRangeKernelRpcM>);
struct ClEnqueueTaskRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 51;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_command_queue command_queue = {};
        cl_kernel kernel = {};
        cl_uint num_events_in_wait_list = {};
        const cl_event* event_wait_list = {};
        cl_event* event = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->command_queue == rhs.command_queue;
            equal &= this->kernel == rhs.kernel;
            equal &= this->num_events_in_wait_list == rhs.num_events_in_wait_list;
            equal &= this->event_wait_list == rhs.event_wait_list;
            equal &= this->event == rhs.event;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_command_queue command_queue, cl_kernel kernel, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits event_wait_list = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        cl_event event;
        uint32_t countEvent_wait_list = 0;
        cl_event event_wait_list[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countEvent_wait_list = dynamicTraits.event_wait_list.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClEnqueueTaskRpcM() = default;

    ClEnqueueTaskRpcM(const Captures::DynamicTraits &dynamicTraits, cl_command_queue command_queue, cl_kernel kernel, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.command_queue = command_queue;
        args.kernel = kernel;
        args.num_events_in_wait_list = num_events_in_wait_list;
        args.event_wait_list = event_wait_list;
        args.event = event;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClEnqueueTaskRpcM &message, cl_command_queue command_queue, cl_kernel kernel, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.command_queue = command_queue;
        message.args.kernel = kernel;
        message.args.num_events_in_wait_list = num_events_in_wait_list;
        message.args.event_wait_list = event_wait_list;
        message.args.event = event;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event_wait_list){
            memcpy(asMemcpyDstT(captures.event_wait_list), args.event_wait_list, dynMemTraits.event_wait_list.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event){
            *args.event = captures.event;
        }
    }
};
static_assert(std::is_standard_layout_v<ClEnqueueTaskRpcM>);
struct ClEnqueueMarkerWithWaitListRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 52;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_command_queue command_queue = {};
        cl_uint num_events_in_wait_list = {};
        const cl_event* event_wait_list = {};
        cl_event* event = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->command_queue == rhs.command_queue;
            equal &= this->num_events_in_wait_list == rhs.num_events_in_wait_list;
            equal &= this->event_wait_list == rhs.event_wait_list;
            equal &= this->event == rhs.event;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_command_queue command_queue, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits event_wait_list = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        cl_event event;
        uint32_t countEvent_wait_list = 0;
        cl_event event_wait_list[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countEvent_wait_list = dynamicTraits.event_wait_list.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClEnqueueMarkerWithWaitListRpcM() = default;

    ClEnqueueMarkerWithWaitListRpcM(const Captures::DynamicTraits &dynamicTraits, cl_command_queue command_queue, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.command_queue = command_queue;
        args.num_events_in_wait_list = num_events_in_wait_list;
        args.event_wait_list = event_wait_list;
        args.event = event;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClEnqueueMarkerWithWaitListRpcM &message, cl_command_queue command_queue, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.command_queue = command_queue;
        message.args.num_events_in_wait_list = num_events_in_wait_list;
        message.args.event_wait_list = event_wait_list;
        message.args.event = event;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event_wait_list){
            memcpy(asMemcpyDstT(captures.event_wait_list), args.event_wait_list, dynMemTraits.event_wait_list.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event){
            *args.event = captures.event;
        }
    }
};
static_assert(std::is_standard_layout_v<ClEnqueueMarkerWithWaitListRpcM>);
struct ClEnqueueMarkerRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 53;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_command_queue command_queue = {};
        cl_event* event = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->command_queue == rhs.command_queue;
            equal &= this->event == rhs.event;
            return equal;
        }
    }args;

    struct Captures {

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        cl_event event;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClEnqueueMarkerRpcM() = default;

    ClEnqueueMarkerRpcM(cl_command_queue command_queue, cl_event* event) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.command_queue = command_queue;
        args.event = event;
    }
    
    static void fillWithoutCapture(ClEnqueueMarkerRpcM &message, cl_command_queue command_queue, cl_event* event) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.command_queue = command_queue;
        message.args.event = event;
    }
    

    void copyToCaller(){
        if(args.event){
            *args.event = captures.event;
        }
    }
};
static_assert(std::is_standard_layout_v<ClEnqueueMarkerRpcM>);
struct ClEnqueueBarrierWithWaitListRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 54;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_command_queue command_queue = {};
        cl_uint num_events_in_wait_list = {};
        const cl_event* event_wait_list = {};
        cl_event* event = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->command_queue == rhs.command_queue;
            equal &= this->num_events_in_wait_list == rhs.num_events_in_wait_list;
            equal &= this->event_wait_list == rhs.event_wait_list;
            equal &= this->event == rhs.event;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_command_queue command_queue, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits event_wait_list = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        cl_event event;
        uint32_t countEvent_wait_list = 0;
        cl_event event_wait_list[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countEvent_wait_list = dynamicTraits.event_wait_list.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClEnqueueBarrierWithWaitListRpcM() = default;

    ClEnqueueBarrierWithWaitListRpcM(const Captures::DynamicTraits &dynamicTraits, cl_command_queue command_queue, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.command_queue = command_queue;
        args.num_events_in_wait_list = num_events_in_wait_list;
        args.event_wait_list = event_wait_list;
        args.event = event;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClEnqueueBarrierWithWaitListRpcM &message, cl_command_queue command_queue, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.command_queue = command_queue;
        message.args.num_events_in_wait_list = num_events_in_wait_list;
        message.args.event_wait_list = event_wait_list;
        message.args.event = event;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event_wait_list){
            memcpy(asMemcpyDstT(captures.event_wait_list), args.event_wait_list, dynMemTraits.event_wait_list.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event){
            *args.event = captures.event;
        }
    }
};
static_assert(std::is_standard_layout_v<ClEnqueueBarrierWithWaitListRpcM>);
struct ClEnqueueBarrierRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 55;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_command_queue command_queue = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->command_queue == rhs.command_queue;
            return equal;
        }
    }args;

    struct Captures {

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClEnqueueBarrierRpcM() = default;

    ClEnqueueBarrierRpcM(cl_command_queue command_queue) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.command_queue = command_queue;
    }
    
    static void fillWithoutCapture(ClEnqueueBarrierRpcM &message, cl_command_queue command_queue) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.command_queue = command_queue;
    }
    
};
static_assert(std::is_standard_layout_v<ClEnqueueBarrierRpcM>);
struct ClEnqueueWaitForEventsRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 56;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_command_queue command_queue = {};
        cl_uint num_events = {};
        const cl_event* event_list = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->command_queue == rhs.command_queue;
            equal &= this->num_events == rhs.num_events;
            equal &= this->event_list == rhs.event_list;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_command_queue command_queue, cl_uint num_events, const cl_event* event_list);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits event_list = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        uint32_t countEvent_list = 0;
        cl_event event_list[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countEvent_list = dynamicTraits.event_list.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClEnqueueWaitForEventsRpcM() = default;

    ClEnqueueWaitForEventsRpcM(const Captures::DynamicTraits &dynamicTraits, cl_command_queue command_queue, cl_uint num_events, const cl_event* event_list) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.command_queue = command_queue;
        args.num_events = num_events;
        args.event_list = event_list;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClEnqueueWaitForEventsRpcM &message, cl_command_queue command_queue, cl_uint num_events, const cl_event* event_list) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.command_queue = command_queue;
        message.args.num_events = num_events;
        message.args.event_list = event_list;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event_list){
            memcpy(asMemcpyDstT(captures.event_list), args.event_list, dynMemTraits.event_list.size);
        }
    }
};
static_assert(std::is_standard_layout_v<ClEnqueueWaitForEventsRpcM>);
struct ClEnqueueMigrateMemObjectsRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 57;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_command_queue command_queue = {};
        cl_uint num_mem_objects = {};
        const cl_mem* mem_objects = {};
        cl_mem_migration_flags flags = {};
        cl_uint num_events_in_wait_list = {};
        const cl_event* event_wait_list = {};
        cl_event* event = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->command_queue == rhs.command_queue;
            equal &= this->num_mem_objects == rhs.num_mem_objects;
            equal &= this->mem_objects == rhs.mem_objects;
            equal &= this->flags == rhs.flags;
            equal &= this->num_events_in_wait_list == rhs.num_events_in_wait_list;
            equal &= this->event_wait_list == rhs.event_wait_list;
            equal &= this->event == rhs.event;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_command_queue command_queue, cl_uint num_mem_objects, const cl_mem* mem_objects, cl_mem_migration_flags flags, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits mem_objects = {};          
            DynamicArgTraits event_wait_list = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        cl_event event;
        uint32_t offsetEvent_wait_list = 0;
        uint32_t countMem_objects = 0;
        uint32_t countEvent_wait_list = 0;
        const cl_mem* getMem_objects() {
            auto offset = 0;
            return reinterpret_cast<const cl_mem*>(dynMem + offset);
        }

        const cl_event* getEvent_wait_list() {
            auto offset = offsetEvent_wait_list;
            return reinterpret_cast<const cl_event*>(dynMem + offset);
        }


        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        offsetEvent_wait_list = dynamicTraits.event_wait_list.offset;
        countMem_objects = dynamicTraits.mem_objects.count;
        countEvent_wait_list = dynamicTraits.event_wait_list.count;
        }
        
        alignas(8) char dynMem[];
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClEnqueueMigrateMemObjectsRpcM() = default;

    ClEnqueueMigrateMemObjectsRpcM(const Captures::DynamicTraits &dynamicTraits, cl_command_queue command_queue, cl_uint num_mem_objects, const cl_mem* mem_objects, cl_mem_migration_flags flags, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.command_queue = command_queue;
        args.num_mem_objects = num_mem_objects;
        args.mem_objects = mem_objects;
        args.flags = flags;
        args.num_events_in_wait_list = num_events_in_wait_list;
        args.event_wait_list = event_wait_list;
        args.event = event;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClEnqueueMigrateMemObjectsRpcM &message, cl_command_queue command_queue, cl_uint num_mem_objects, const cl_mem* mem_objects, cl_mem_migration_flags flags, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.command_queue = command_queue;
        message.args.num_mem_objects = num_mem_objects;
        message.args.mem_objects = mem_objects;
        message.args.flags = flags;
        message.args.num_events_in_wait_list = num_events_in_wait_list;
        message.args.event_wait_list = event_wait_list;
        message.args.event = event;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.mem_objects){
            memcpy(asMemcpyDstT(captures.getMem_objects()), args.mem_objects, dynMemTraits.mem_objects.size);
        }
        if(args.event_wait_list){
            memcpy(asMemcpyDstT(captures.getEvent_wait_list()), args.event_wait_list, dynMemTraits.event_wait_list.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event){
            *args.event = captures.event;
        }
    }
};
static_assert(std::is_standard_layout_v<ClEnqueueMigrateMemObjectsRpcM>);
 // clGetExtensionFunctionAddressForPlatform ignored in generator - based on dont_generate_rpc_message flag
struct ClCreateBufferRpcMImplicitArgs {
    void* hostptr = {};
    int hostptr_shmem_resource = {};
    size_t hostptr_offset_within_resource = {};
    size_t hostptr_aligned_size = {};
};

struct ClCreateBufferRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 58;
    static constexpr float latency = 1.0;

    using ReturnValueT = cl_mem;

    struct Args {
        cl_context context = {};
        cl_mem_flags flags = {};
        size_t size = {};
        void* host_ptr = {};
        cl_int* errcode_ret = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->context == rhs.context;
            equal &= this->flags == rhs.flags;
            equal &= this->size == rhs.size;
            equal &= this->host_ptr == rhs.host_ptr;
            equal &= this->errcode_ret == rhs.errcode_ret;
            return equal;
        }
    }args;

    ClCreateBufferRpcMImplicitArgs implicitArgs{};
    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_context context, cl_mem_flags flags, size_t size, void* host_ptr, cl_int* errcode_ret);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits host_ptr = {};          
        };

        cl_mem ret = {};
        cl_int errcode_ret;
        uint32_t countHost_ptr = 0;
        char host_ptr[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countHost_ptr = dynamicTraits.host_ptr.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_mem returnValue(){
        return captures.ret;
    }

    ClCreateBufferRpcM() = default;

    ClCreateBufferRpcM(const Captures::DynamicTraits &dynamicTraits, cl_context context, cl_mem_flags flags, size_t size, void* host_ptr, cl_int* errcode_ret) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.context = context;
        args.flags = flags;
        args.size = size;
        args.host_ptr = host_ptr;
        args.errcode_ret = errcode_ret;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClCreateBufferRpcM &message, cl_context context, cl_mem_flags flags, size_t size, void* host_ptr, cl_int* errcode_ret) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.context = context;
        message.args.flags = flags;
        message.args.size = size;
        message.args.host_ptr = host_ptr;
        message.args.errcode_ret = errcode_ret;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits, const Cal::Rpc::Ocl::ClCreateBufferRpcMImplicitArgs &implicitArgs){
        if(args.host_ptr){
            memcpy(asMemcpyDstT(captures.host_ptr), args.host_ptr, dynMemTraits.host_ptr.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits, Cal::Rpc::Ocl::ClCreateBufferRpcMImplicitArgs &implicitArgs){
        if(args.errcode_ret){
            *args.errcode_ret = captures.errcode_ret;
        }
         implicitArgs.hostptr = this->implicitArgs.hostptr;
         implicitArgs.hostptr_shmem_resource = this->implicitArgs.hostptr_shmem_resource;
         implicitArgs.hostptr_offset_within_resource = this->implicitArgs.hostptr_offset_within_resource;
         implicitArgs.hostptr_aligned_size = this->implicitArgs.hostptr_aligned_size;
    }
};
static_assert(std::is_standard_layout_v<ClCreateBufferRpcM>);
struct ClCreateBufferRpcHelperUseHostPtrZeroCopyMallocShmemRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 59;
    static constexpr float latency = 1.0;

    using ReturnValueT = cl_mem;

    struct Args {
        cl_context context = {};
        cl_mem_flags flags = {};
        size_t size = {};
        void* host_ptr = {};
        cl_int* errcode_ret = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->context == rhs.context;
            equal &= this->flags == rhs.flags;
            equal &= this->size == rhs.size;
            equal &= this->host_ptr == rhs.host_ptr;
            equal &= this->errcode_ret == rhs.errcode_ret;
            return equal;
        }
    }args;

    struct Captures {

        cl_mem ret = {};
        cl_int errcode_ret;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_mem returnValue(){
        return captures.ret;
    }

    ClCreateBufferRpcHelperUseHostPtrZeroCopyMallocShmemRpcM() = default;

    ClCreateBufferRpcHelperUseHostPtrZeroCopyMallocShmemRpcM(cl_context context, cl_mem_flags flags, size_t size, void* host_ptr, cl_int* errcode_ret) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.context = context;
        args.flags = flags;
        args.size = size;
        args.host_ptr = host_ptr;
        args.errcode_ret = errcode_ret;
    }
    
    static void fillWithoutCapture(ClCreateBufferRpcHelperUseHostPtrZeroCopyMallocShmemRpcM &message, cl_context context, cl_mem_flags flags, size_t size, void* host_ptr, cl_int* errcode_ret) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.context = context;
        message.args.flags = flags;
        message.args.size = size;
        message.args.host_ptr = host_ptr;
        message.args.errcode_ret = errcode_ret;
    }
    

    void copyToCaller(){
        if(args.errcode_ret){
            *args.errcode_ret = captures.errcode_ret;
        }
    }
};
static_assert(std::is_standard_layout_v<ClCreateBufferRpcHelperUseHostPtrZeroCopyMallocShmemRpcM>);
struct ClCreateSubBufferRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 60;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_mem;

    struct Args {
        cl_mem buffer = {};
        cl_mem_flags flags = {};
        cl_buffer_create_type buffer_create_type = {};
        const void* buffer_create_info = {};
        cl_int* errcode_ret = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->buffer == rhs.buffer;
            equal &= this->flags == rhs.flags;
            equal &= this->buffer_create_type == rhs.buffer_create_type;
            equal &= this->buffer_create_info == rhs.buffer_create_info;
            equal &= this->errcode_ret == rhs.errcode_ret;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_mem buffer, cl_mem_flags flags, cl_buffer_create_type buffer_create_type, const void* buffer_create_info, cl_int* errcode_ret);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits buffer_create_info = {};          
        };

        cl_mem ret = {};
        cl_int errcode_ret;
        uint32_t countBuffer_create_info = 0;
        char buffer_create_info[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countBuffer_create_info = dynamicTraits.buffer_create_info.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_mem returnValue(){
        return captures.ret;
    }

    ClCreateSubBufferRpcM() = default;

    ClCreateSubBufferRpcM(const Captures::DynamicTraits &dynamicTraits, cl_mem buffer, cl_mem_flags flags, cl_buffer_create_type buffer_create_type, const void* buffer_create_info, cl_int* errcode_ret) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.buffer = buffer;
        args.flags = flags;
        args.buffer_create_type = buffer_create_type;
        args.buffer_create_info = buffer_create_info;
        args.errcode_ret = errcode_ret;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClCreateSubBufferRpcM &message, cl_mem buffer, cl_mem_flags flags, cl_buffer_create_type buffer_create_type, const void* buffer_create_info, cl_int* errcode_ret) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.buffer = buffer;
        message.args.flags = flags;
        message.args.buffer_create_type = buffer_create_type;
        message.args.buffer_create_info = buffer_create_info;
        message.args.errcode_ret = errcode_ret;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.buffer_create_info){
            memcpy(asMemcpyDstT(captures.buffer_create_info), args.buffer_create_info, dynMemTraits.buffer_create_info.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.errcode_ret){
            *args.errcode_ret = captures.errcode_ret;
        }
    }
};
static_assert(std::is_standard_layout_v<ClCreateSubBufferRpcM>);
struct ClCreatePipeRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 61;
    static constexpr float latency = 1.0;

    using ReturnValueT = cl_mem;

    struct Args {
        cl_context context = {};
        cl_mem_flags flags = {};
        cl_uint pipe_packet_size = {};
        cl_uint pipe_max_packets = {};
        const cl_pipe_properties* properties = {};
        cl_int* errcode_ret = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->context == rhs.context;
            equal &= this->flags == rhs.flags;
            equal &= this->pipe_packet_size == rhs.pipe_packet_size;
            equal &= this->pipe_max_packets == rhs.pipe_max_packets;
            equal &= this->properties == rhs.properties;
            equal &= this->errcode_ret == rhs.errcode_ret;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_context context, cl_mem_flags flags, cl_uint pipe_packet_size, cl_uint pipe_max_packets, const cl_pipe_properties* properties, cl_int* errcode_ret);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits properties = {};          
        };

        cl_mem ret = {};
        cl_int errcode_ret;
        uint32_t countProperties = 0;
        cl_pipe_properties properties[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countProperties = dynamicTraits.properties.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_mem returnValue(){
        return captures.ret;
    }

    ClCreatePipeRpcM() = default;

    ClCreatePipeRpcM(const Captures::DynamicTraits &dynamicTraits, cl_context context, cl_mem_flags flags, cl_uint pipe_packet_size, cl_uint pipe_max_packets, const cl_pipe_properties* properties, cl_int* errcode_ret) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.context = context;
        args.flags = flags;
        args.pipe_packet_size = pipe_packet_size;
        args.pipe_max_packets = pipe_max_packets;
        args.properties = properties;
        args.errcode_ret = errcode_ret;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClCreatePipeRpcM &message, cl_context context, cl_mem_flags flags, cl_uint pipe_packet_size, cl_uint pipe_max_packets, const cl_pipe_properties* properties, cl_int* errcode_ret) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.context = context;
        message.args.flags = flags;
        message.args.pipe_packet_size = pipe_packet_size;
        message.args.pipe_max_packets = pipe_max_packets;
        message.args.properties = properties;
        message.args.errcode_ret = errcode_ret;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.properties){
            memcpy(asMemcpyDstT(captures.properties), args.properties, dynMemTraits.properties.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.errcode_ret){
            *args.errcode_ret = captures.errcode_ret;
        }
    }
};
static_assert(std::is_standard_layout_v<ClCreatePipeRpcM>);
struct ClGetPipeInfoRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 62;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_mem pipe = {};
        cl_pipe_info param_name = {};
        size_t param_value_size = {};
        void* param_value = {};
        size_t* param_value_size_ret = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->pipe == rhs.pipe;
            equal &= this->param_name == rhs.param_name;
            equal &= this->param_value_size == rhs.param_value_size;
            equal &= this->param_value == rhs.param_value;
            equal &= this->param_value_size_ret == rhs.param_value_size_ret;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_mem pipe, cl_pipe_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits param_value = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        size_t param_value_size_ret;
        uint32_t countParam_value = 0;
        char param_value[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countParam_value = dynamicTraits.param_value.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClGetPipeInfoRpcM() = default;

    ClGetPipeInfoRpcM(const Captures::DynamicTraits &dynamicTraits, cl_mem pipe, cl_pipe_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.pipe = pipe;
        args.param_name = param_name;
        args.param_value_size = param_value_size;
        args.param_value = param_value;
        args.param_value_size_ret = param_value_size_ret;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClGetPipeInfoRpcM &message, cl_mem pipe, cl_pipe_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.pipe = pipe;
        message.args.param_name = param_name;
        message.args.param_value_size = param_value_size;
        message.args.param_value = param_value;
        message.args.param_value_size_ret = param_value_size_ret;
    }
    

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.param_value){
            memcpy(args.param_value, captures.param_value, dynMemTraits.param_value.size);
        }
        if(args.param_value_size_ret){
            *args.param_value_size_ret = captures.param_value_size_ret;
        }
    }
};
static_assert(std::is_standard_layout_v<ClGetPipeInfoRpcM>);
struct ClCreateImageRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 63;
    static constexpr float latency = 1.0;

    using ReturnValueT = cl_mem;

    struct Args {
        cl_context context = {};
        cl_mem_flags flags = {};
        const cl_image_format* image_format = {};
        const cl_image_desc* image_desc = {};
        void* host_ptr = {};
        cl_int* errcode_ret = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->context == rhs.context;
            equal &= this->flags == rhs.flags;
            equal &= this->image_format == rhs.image_format;
            equal &= this->image_desc == rhs.image_desc;
            equal &= this->host_ptr == rhs.host_ptr;
            equal &= this->errcode_ret == rhs.errcode_ret;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_context context, cl_mem_flags flags, const cl_image_format* image_format, const cl_image_desc* image_desc, void* host_ptr, cl_int* errcode_ret);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits host_ptr = {};          
        };

        cl_mem ret = {};
        cl_image_format image_format;
        cl_image_desc image_desc;
        cl_int errcode_ret;
        uint32_t countHost_ptr = 0;
        char host_ptr[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countHost_ptr = dynamicTraits.host_ptr.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_mem returnValue(){
        return captures.ret;
    }

    ClCreateImageRpcM() = default;

    ClCreateImageRpcM(const Captures::DynamicTraits &dynamicTraits, cl_context context, cl_mem_flags flags, const cl_image_format* image_format, const cl_image_desc* image_desc, void* host_ptr, cl_int* errcode_ret) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.context = context;
        args.flags = flags;
        args.image_format = image_format;
        args.image_desc = image_desc;
        args.host_ptr = host_ptr;
        args.errcode_ret = errcode_ret;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClCreateImageRpcM &message, cl_context context, cl_mem_flags flags, const cl_image_format* image_format, const cl_image_desc* image_desc, void* host_ptr, cl_int* errcode_ret) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.context = context;
        message.args.flags = flags;
        message.args.image_format = image_format;
        message.args.image_desc = image_desc;
        message.args.host_ptr = host_ptr;
        message.args.errcode_ret = errcode_ret;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.image_format){
            captures.image_format = *args.image_format;
        }
        if(args.image_desc){
            captures.image_desc = *args.image_desc;
        }
        if(args.host_ptr){
            memcpy(asMemcpyDstT(captures.host_ptr), args.host_ptr, dynMemTraits.host_ptr.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.errcode_ret){
            *args.errcode_ret = captures.errcode_ret;
        }
    }
};
static_assert(std::is_standard_layout_v<ClCreateImageRpcM>);
struct ClCreateImage2DRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 64;
    static constexpr float latency = 1.0;

    using ReturnValueT = cl_mem;

    struct Args {
        cl_context context = {};
        cl_mem_flags flags = {};
        const cl_image_format* image_format = {};
        size_t image_width = {};
        size_t image_height = {};
        size_t image_row_pitch = {};
        void* host_ptr = {};
        cl_int* errcode_ret = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->context == rhs.context;
            equal &= this->flags == rhs.flags;
            equal &= this->image_format == rhs.image_format;
            equal &= this->image_width == rhs.image_width;
            equal &= this->image_height == rhs.image_height;
            equal &= this->image_row_pitch == rhs.image_row_pitch;
            equal &= this->host_ptr == rhs.host_ptr;
            equal &= this->errcode_ret == rhs.errcode_ret;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_context context, cl_mem_flags flags, const cl_image_format* image_format, size_t image_width, size_t image_height, size_t image_row_pitch, void* host_ptr, cl_int* errcode_ret);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits host_ptr = {};          
        };

        cl_mem ret = {};
        cl_image_format image_format;
        cl_int errcode_ret;
        uint32_t countHost_ptr = 0;
        char host_ptr[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countHost_ptr = dynamicTraits.host_ptr.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_mem returnValue(){
        return captures.ret;
    }

    ClCreateImage2DRpcM() = default;

    ClCreateImage2DRpcM(const Captures::DynamicTraits &dynamicTraits, cl_context context, cl_mem_flags flags, const cl_image_format* image_format, size_t image_width, size_t image_height, size_t image_row_pitch, void* host_ptr, cl_int* errcode_ret) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.context = context;
        args.flags = flags;
        args.image_format = image_format;
        args.image_width = image_width;
        args.image_height = image_height;
        args.image_row_pitch = image_row_pitch;
        args.host_ptr = host_ptr;
        args.errcode_ret = errcode_ret;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClCreateImage2DRpcM &message, cl_context context, cl_mem_flags flags, const cl_image_format* image_format, size_t image_width, size_t image_height, size_t image_row_pitch, void* host_ptr, cl_int* errcode_ret) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.context = context;
        message.args.flags = flags;
        message.args.image_format = image_format;
        message.args.image_width = image_width;
        message.args.image_height = image_height;
        message.args.image_row_pitch = image_row_pitch;
        message.args.host_ptr = host_ptr;
        message.args.errcode_ret = errcode_ret;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.image_format){
            captures.image_format = *args.image_format;
        }
        if(args.host_ptr){
            memcpy(asMemcpyDstT(captures.host_ptr), args.host_ptr, dynMemTraits.host_ptr.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.errcode_ret){
            *args.errcode_ret = captures.errcode_ret;
        }
    }
};
static_assert(std::is_standard_layout_v<ClCreateImage2DRpcM>);
struct ClCreateImage3DRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 65;
    static constexpr float latency = 1.0;

    using ReturnValueT = cl_mem;

    struct Args {
        cl_context context = {};
        cl_mem_flags flags = {};
        const cl_image_format* image_format = {};
        size_t image_width = {};
        size_t image_height = {};
        size_t image_depth = {};
        size_t image_row_pitch = {};
        size_t image_slice_pitch = {};
        void* host_ptr = {};
        cl_int* errcode_ret = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->context == rhs.context;
            equal &= this->flags == rhs.flags;
            equal &= this->image_format == rhs.image_format;
            equal &= this->image_width == rhs.image_width;
            equal &= this->image_height == rhs.image_height;
            equal &= this->image_depth == rhs.image_depth;
            equal &= this->image_row_pitch == rhs.image_row_pitch;
            equal &= this->image_slice_pitch == rhs.image_slice_pitch;
            equal &= this->host_ptr == rhs.host_ptr;
            equal &= this->errcode_ret == rhs.errcode_ret;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_context context, cl_mem_flags flags, const cl_image_format* image_format, size_t image_width, size_t image_height, size_t image_depth, size_t image_row_pitch, size_t image_slice_pitch, void* host_ptr, cl_int* errcode_ret);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits host_ptr = {};          
        };

        cl_mem ret = {};
        cl_image_format image_format;
        cl_int errcode_ret;
        uint32_t countHost_ptr = 0;
        char host_ptr[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countHost_ptr = dynamicTraits.host_ptr.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_mem returnValue(){
        return captures.ret;
    }

    ClCreateImage3DRpcM() = default;

    ClCreateImage3DRpcM(const Captures::DynamicTraits &dynamicTraits, cl_context context, cl_mem_flags flags, const cl_image_format* image_format, size_t image_width, size_t image_height, size_t image_depth, size_t image_row_pitch, size_t image_slice_pitch, void* host_ptr, cl_int* errcode_ret) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.context = context;
        args.flags = flags;
        args.image_format = image_format;
        args.image_width = image_width;
        args.image_height = image_height;
        args.image_depth = image_depth;
        args.image_row_pitch = image_row_pitch;
        args.image_slice_pitch = image_slice_pitch;
        args.host_ptr = host_ptr;
        args.errcode_ret = errcode_ret;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClCreateImage3DRpcM &message, cl_context context, cl_mem_flags flags, const cl_image_format* image_format, size_t image_width, size_t image_height, size_t image_depth, size_t image_row_pitch, size_t image_slice_pitch, void* host_ptr, cl_int* errcode_ret) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.context = context;
        message.args.flags = flags;
        message.args.image_format = image_format;
        message.args.image_width = image_width;
        message.args.image_height = image_height;
        message.args.image_depth = image_depth;
        message.args.image_row_pitch = image_row_pitch;
        message.args.image_slice_pitch = image_slice_pitch;
        message.args.host_ptr = host_ptr;
        message.args.errcode_ret = errcode_ret;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.image_format){
            captures.image_format = *args.image_format;
        }
        if(args.host_ptr){
            memcpy(asMemcpyDstT(captures.host_ptr), args.host_ptr, dynMemTraits.host_ptr.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.errcode_ret){
            *args.errcode_ret = captures.errcode_ret;
        }
    }
};
static_assert(std::is_standard_layout_v<ClCreateImage3DRpcM>);
struct ClCreateSamplerRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 66;
    static constexpr float latency = 1.0;

    using ReturnValueT = cl_sampler;

    struct Args {
        cl_context context = {};
        cl_bool normalized_coords = {};
        cl_addressing_mode addressing_mode = {};
        cl_filter_mode filter_mode = {};
        cl_int* errcode_ret = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->context == rhs.context;
            equal &= this->normalized_coords == rhs.normalized_coords;
            equal &= this->addressing_mode == rhs.addressing_mode;
            equal &= this->filter_mode == rhs.filter_mode;
            equal &= this->errcode_ret == rhs.errcode_ret;
            return equal;
        }
    }args;

    struct Captures {

        cl_sampler ret = {};
        cl_int errcode_ret;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_sampler returnValue(){
        return captures.ret;
    }

    ClCreateSamplerRpcM() = default;

    ClCreateSamplerRpcM(cl_context context, cl_bool normalized_coords, cl_addressing_mode addressing_mode, cl_filter_mode filter_mode, cl_int* errcode_ret) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.context = context;
        args.normalized_coords = normalized_coords;
        args.addressing_mode = addressing_mode;
        args.filter_mode = filter_mode;
        args.errcode_ret = errcode_ret;
    }
    
    static void fillWithoutCapture(ClCreateSamplerRpcM &message, cl_context context, cl_bool normalized_coords, cl_addressing_mode addressing_mode, cl_filter_mode filter_mode, cl_int* errcode_ret) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.context = context;
        message.args.normalized_coords = normalized_coords;
        message.args.addressing_mode = addressing_mode;
        message.args.filter_mode = filter_mode;
        message.args.errcode_ret = errcode_ret;
    }
    

    void copyToCaller(){
        if(args.errcode_ret){
            *args.errcode_ret = captures.errcode_ret;
        }
    }
};
static_assert(std::is_standard_layout_v<ClCreateSamplerRpcM>);
struct ClCreateSamplerWithPropertiesRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 67;
    static constexpr float latency = 1.0;

    using ReturnValueT = cl_sampler;

    struct Args {
        cl_context context = {};
        const cl_sampler_properties* properties = {};
        cl_int* errcode_ret = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->context == rhs.context;
            equal &= this->properties == rhs.properties;
            equal &= this->errcode_ret == rhs.errcode_ret;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_context context, const cl_sampler_properties* properties, cl_int* errcode_ret);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits properties = {};          
        };

        cl_sampler ret = {};
        cl_int errcode_ret;
        uint32_t countProperties = 0;
        cl_sampler_properties properties[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countProperties = dynamicTraits.properties.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_sampler returnValue(){
        return captures.ret;
    }

    ClCreateSamplerWithPropertiesRpcM() = default;

    ClCreateSamplerWithPropertiesRpcM(const Captures::DynamicTraits &dynamicTraits, cl_context context, const cl_sampler_properties* properties, cl_int* errcode_ret) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.context = context;
        args.properties = properties;
        args.errcode_ret = errcode_ret;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClCreateSamplerWithPropertiesRpcM &message, cl_context context, const cl_sampler_properties* properties, cl_int* errcode_ret) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.context = context;
        message.args.properties = properties;
        message.args.errcode_ret = errcode_ret;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.properties){
            memcpy(asMemcpyDstT(captures.properties), args.properties, dynMemTraits.properties.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.errcode_ret){
            *args.errcode_ret = captures.errcode_ret;
        }
    }
};
static_assert(std::is_standard_layout_v<ClCreateSamplerWithPropertiesRpcM>);
struct ClCreateImageWithPropertiesRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 68;
    static constexpr float latency = 1.0;

    using ReturnValueT = cl_mem;

    struct Args {
        cl_context context = {};
        const cl_mem_properties* properties = {};
        cl_mem_flags flags = {};
        const cl_image_format* image_format = {};
        const cl_image_desc* image_desc = {};
        void* host_ptr = {};
        cl_int* errcode_ret = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->context == rhs.context;
            equal &= this->properties == rhs.properties;
            equal &= this->flags == rhs.flags;
            equal &= this->image_format == rhs.image_format;
            equal &= this->image_desc == rhs.image_desc;
            equal &= this->host_ptr == rhs.host_ptr;
            equal &= this->errcode_ret == rhs.errcode_ret;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_context context, const cl_mem_properties* properties, cl_mem_flags flags, const cl_image_format* image_format, const cl_image_desc* image_desc, void* host_ptr, cl_int* errcode_ret);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits host_ptr = {};          
            DynamicArgTraits properties = {};          
        };

        cl_mem ret = {};
        cl_image_format image_format;
        cl_image_desc image_desc;
        cl_int errcode_ret;
        uint32_t offsetProperties = 0;
        uint32_t countHost_ptr = 0;
        uint32_t countProperties = 0;
        void* getHost_ptr() {
            auto offset = 0;
            return reinterpret_cast<void*>(dynMem + offset);
        }

        const cl_mem_properties* getProperties() {
            auto offset = offsetProperties;
            return reinterpret_cast<const cl_mem_properties*>(dynMem + offset);
        }


        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        offsetProperties = dynamicTraits.properties.offset;
        countHost_ptr = dynamicTraits.host_ptr.count;
        countProperties = dynamicTraits.properties.count;
        }
        
        alignas(8) char dynMem[];
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_mem returnValue(){
        return captures.ret;
    }

    ClCreateImageWithPropertiesRpcM() = default;

    ClCreateImageWithPropertiesRpcM(const Captures::DynamicTraits &dynamicTraits, cl_context context, const cl_mem_properties* properties, cl_mem_flags flags, const cl_image_format* image_format, const cl_image_desc* image_desc, void* host_ptr, cl_int* errcode_ret) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.context = context;
        args.properties = properties;
        args.flags = flags;
        args.image_format = image_format;
        args.image_desc = image_desc;
        args.host_ptr = host_ptr;
        args.errcode_ret = errcode_ret;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClCreateImageWithPropertiesRpcM &message, cl_context context, const cl_mem_properties* properties, cl_mem_flags flags, const cl_image_format* image_format, const cl_image_desc* image_desc, void* host_ptr, cl_int* errcode_ret) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.context = context;
        message.args.properties = properties;
        message.args.flags = flags;
        message.args.image_format = image_format;
        message.args.image_desc = image_desc;
        message.args.host_ptr = host_ptr;
        message.args.errcode_ret = errcode_ret;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.properties){
            memcpy(asMemcpyDstT(captures.getProperties()), args.properties, dynMemTraits.properties.size);
        }
        if(args.image_format){
            captures.image_format = *args.image_format;
        }
        if(args.image_desc){
            captures.image_desc = *args.image_desc;
        }
        if(args.host_ptr){
            memcpy(asMemcpyDstT(captures.getHost_ptr()), args.host_ptr, dynMemTraits.host_ptr.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.errcode_ret){
            *args.errcode_ret = captures.errcode_ret;
        }
    }
};
static_assert(std::is_standard_layout_v<ClCreateImageWithPropertiesRpcM>);
struct ClCreateBufferWithPropertiesRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 69;
    static constexpr float latency = 1.0;

    using ReturnValueT = cl_mem;

    struct Args {
        cl_context context = {};
        const cl_mem_properties* properties = {};
        cl_mem_flags flags = {};
        size_t size = {};
        void* host_ptr = {};
        cl_int* errcode_ret = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->context == rhs.context;
            equal &= this->properties == rhs.properties;
            equal &= this->flags == rhs.flags;
            equal &= this->size == rhs.size;
            equal &= this->host_ptr == rhs.host_ptr;
            equal &= this->errcode_ret == rhs.errcode_ret;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_context context, const cl_mem_properties* properties, cl_mem_flags flags, size_t size, void* host_ptr, cl_int* errcode_ret);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits host_ptr = {};          
            DynamicArgTraits properties = {};          
        };

        cl_mem ret = {};
        cl_int errcode_ret;
        uint32_t offsetProperties = 0;
        uint32_t countHost_ptr = 0;
        uint32_t countProperties = 0;
        void* getHost_ptr() {
            auto offset = 0;
            return reinterpret_cast<void*>(dynMem + offset);
        }

        const cl_mem_properties* getProperties() {
            auto offset = offsetProperties;
            return reinterpret_cast<const cl_mem_properties*>(dynMem + offset);
        }


        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        offsetProperties = dynamicTraits.properties.offset;
        countHost_ptr = dynamicTraits.host_ptr.count;
        countProperties = dynamicTraits.properties.count;
        }
        
        alignas(8) char dynMem[];
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_mem returnValue(){
        return captures.ret;
    }

    ClCreateBufferWithPropertiesRpcM() = default;

    ClCreateBufferWithPropertiesRpcM(const Captures::DynamicTraits &dynamicTraits, cl_context context, const cl_mem_properties* properties, cl_mem_flags flags, size_t size, void* host_ptr, cl_int* errcode_ret) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.context = context;
        args.properties = properties;
        args.flags = flags;
        args.size = size;
        args.host_ptr = host_ptr;
        args.errcode_ret = errcode_ret;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClCreateBufferWithPropertiesRpcM &message, cl_context context, const cl_mem_properties* properties, cl_mem_flags flags, size_t size, void* host_ptr, cl_int* errcode_ret) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.context = context;
        message.args.properties = properties;
        message.args.flags = flags;
        message.args.size = size;
        message.args.host_ptr = host_ptr;
        message.args.errcode_ret = errcode_ret;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.properties){
            memcpy(asMemcpyDstT(captures.getProperties()), args.properties, dynMemTraits.properties.size);
        }
        if(args.host_ptr){
            memcpy(asMemcpyDstT(captures.getHost_ptr()), args.host_ptr, dynMemTraits.host_ptr.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.errcode_ret){
            *args.errcode_ret = captures.errcode_ret;
        }
    }
};
static_assert(std::is_standard_layout_v<ClCreateBufferWithPropertiesRpcM>);
struct ClGetSupportedImageFormatsRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 70;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_context context = {};
        cl_mem_flags flags = {};
        cl_mem_object_type image_type = {};
        cl_uint num_entries = {};
        cl_image_format* image_formats = {};
        cl_uint* num_image_formats = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->context == rhs.context;
            equal &= this->flags == rhs.flags;
            equal &= this->image_type == rhs.image_type;
            equal &= this->num_entries == rhs.num_entries;
            equal &= this->image_formats == rhs.image_formats;
            equal &= this->num_image_formats == rhs.num_image_formats;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_context context, cl_mem_flags flags, cl_mem_object_type image_type, cl_uint num_entries, cl_image_format* image_formats, cl_uint* num_image_formats);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits image_formats = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        cl_uint num_image_formats;
        uint32_t countImage_formats = 0;
        cl_image_format image_formats[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countImage_formats = dynamicTraits.image_formats.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClGetSupportedImageFormatsRpcM() = default;

    ClGetSupportedImageFormatsRpcM(const Captures::DynamicTraits &dynamicTraits, cl_context context, cl_mem_flags flags, cl_mem_object_type image_type, cl_uint num_entries, cl_image_format* image_formats, cl_uint* num_image_formats) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.context = context;
        args.flags = flags;
        args.image_type = image_type;
        args.num_entries = num_entries;
        args.image_formats = image_formats;
        args.num_image_formats = num_image_formats;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClGetSupportedImageFormatsRpcM &message, cl_context context, cl_mem_flags flags, cl_mem_object_type image_type, cl_uint num_entries, cl_image_format* image_formats, cl_uint* num_image_formats) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.context = context;
        message.args.flags = flags;
        message.args.image_type = image_type;
        message.args.num_entries = num_entries;
        message.args.image_formats = image_formats;
        message.args.num_image_formats = num_image_formats;
    }
    

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.image_formats){
            memcpy(args.image_formats, captures.image_formats, dynMemTraits.image_formats.size);
        }
        if(args.num_image_formats){
            *args.num_image_formats = captures.num_image_formats;
        }
    }
};
static_assert(std::is_standard_layout_v<ClGetSupportedImageFormatsRpcM>);
struct ClSetKernelArgRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 71;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_kernel kernel = {};
        cl_uint arg_index = {};
        size_t arg_size = {};
        const void* arg_value = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->kernel == rhs.kernel;
            equal &= this->arg_index == rhs.arg_index;
            equal &= this->arg_size == rhs.arg_size;
            equal &= this->arg_value == rhs.arg_value;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_kernel kernel, cl_uint arg_index, size_t arg_size, const void* arg_value);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits arg_value = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        uint32_t countArg_value = 0;
        char arg_value[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countArg_value = dynamicTraits.arg_value.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClSetKernelArgRpcM() = default;

    ClSetKernelArgRpcM(const Captures::DynamicTraits &dynamicTraits, cl_kernel kernel, cl_uint arg_index, size_t arg_size, const void* arg_value) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.kernel = kernel;
        args.arg_index = arg_index;
        args.arg_size = arg_size;
        args.arg_value = arg_value;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClSetKernelArgRpcM &message, cl_kernel kernel, cl_uint arg_index, size_t arg_size, const void* arg_value) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.kernel = kernel;
        message.args.arg_index = arg_index;
        message.args.arg_size = arg_size;
        message.args.arg_value = arg_value;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.arg_value){
            memcpy(asMemcpyDstT(captures.arg_value), args.arg_value, dynMemTraits.arg_value.size);
        }
    }
};
static_assert(std::is_standard_layout_v<ClSetKernelArgRpcM>);
struct ClSetProgramSpecializationConstantRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 72;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_program program = {};
        cl_uint spec_id = {};
        size_t spec_size = {};
        const void* spec_value = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->program == rhs.program;
            equal &= this->spec_id == rhs.spec_id;
            equal &= this->spec_size == rhs.spec_size;
            equal &= this->spec_value == rhs.spec_value;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_program program, cl_uint spec_id, size_t spec_size, const void* spec_value);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits spec_value = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        uint32_t countSpec_value = 0;
        char spec_value[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countSpec_value = dynamicTraits.spec_value.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClSetProgramSpecializationConstantRpcM() = default;

    ClSetProgramSpecializationConstantRpcM(const Captures::DynamicTraits &dynamicTraits, cl_program program, cl_uint spec_id, size_t spec_size, const void* spec_value) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.program = program;
        args.spec_id = spec_id;
        args.spec_size = spec_size;
        args.spec_value = spec_value;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClSetProgramSpecializationConstantRpcM &message, cl_program program, cl_uint spec_id, size_t spec_size, const void* spec_value) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.program = program;
        message.args.spec_id = spec_id;
        message.args.spec_size = spec_size;
        message.args.spec_value = spec_value;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.spec_value){
            memcpy(asMemcpyDstT(captures.spec_value), args.spec_value, dynMemTraits.spec_value.size);
        }
    }
};
static_assert(std::is_standard_layout_v<ClSetProgramSpecializationConstantRpcM>);
struct ClEnqueueWriteBufferRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 73;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_command_queue command_queue = {};
        cl_mem buffer = {};
        cl_bool blocking_write = {};
        size_t offset = {};
        size_t size = {};
        const void* ptr = {};
        cl_uint num_events_in_wait_list = {};
        const cl_event* event_wait_list = {};
        cl_event* event = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->command_queue == rhs.command_queue;
            equal &= this->buffer == rhs.buffer;
            equal &= this->blocking_write == rhs.blocking_write;
            equal &= this->offset == rhs.offset;
            equal &= this->size == rhs.size;
            equal &= this->ptr == rhs.ptr;
            equal &= this->num_events_in_wait_list == rhs.num_events_in_wait_list;
            equal &= this->event_wait_list == rhs.event_wait_list;
            equal &= this->event == rhs.event;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, size_t offset, size_t size, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits event_wait_list = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        cl_event event;
        uint32_t countEvent_wait_list = 0;
        cl_event event_wait_list[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countEvent_wait_list = dynamicTraits.event_wait_list.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClEnqueueWriteBufferRpcM() = default;

    ClEnqueueWriteBufferRpcM(const Captures::DynamicTraits &dynamicTraits, cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, size_t offset, size_t size, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.command_queue = command_queue;
        args.buffer = buffer;
        args.blocking_write = blocking_write;
        args.offset = offset;
        args.size = size;
        args.ptr = ptr;
        args.num_events_in_wait_list = num_events_in_wait_list;
        args.event_wait_list = event_wait_list;
        args.event = event;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClEnqueueWriteBufferRpcM &message, cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, size_t offset, size_t size, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.command_queue = command_queue;
        message.args.buffer = buffer;
        message.args.blocking_write = blocking_write;
        message.args.offset = offset;
        message.args.size = size;
        message.args.ptr = ptr;
        message.args.num_events_in_wait_list = num_events_in_wait_list;
        message.args.event_wait_list = event_wait_list;
        message.args.event = event;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event_wait_list){
            memcpy(asMemcpyDstT(captures.event_wait_list), args.event_wait_list, dynMemTraits.event_wait_list.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event){
            *args.event = captures.event;
        }
    }
};
static_assert(std::is_standard_layout_v<ClEnqueueWriteBufferRpcM>);
struct ClEnqueueWriteBufferRpcHelperMallocHostRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 74;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_command_queue command_queue = {};
        cl_mem buffer = {};
        cl_bool blocking_write = {};
        size_t offset = {};
        size_t size = {};
        const void* ptr = {};
        cl_uint num_events_in_wait_list = {};
        const cl_event* event_wait_list = {};
        cl_event* event = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->command_queue == rhs.command_queue;
            equal &= this->buffer == rhs.buffer;
            equal &= this->blocking_write == rhs.blocking_write;
            equal &= this->offset == rhs.offset;
            equal &= this->size == rhs.size;
            equal &= this->ptr == rhs.ptr;
            equal &= this->num_events_in_wait_list == rhs.num_events_in_wait_list;
            equal &= this->event_wait_list == rhs.event_wait_list;
            equal &= this->event == rhs.event;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, size_t offset, size_t size, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits event_wait_list = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        cl_event event;
        uint32_t countEvent_wait_list = 0;
        cl_event event_wait_list[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countEvent_wait_list = dynamicTraits.event_wait_list.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClEnqueueWriteBufferRpcHelperMallocHostRpcM() = default;

    ClEnqueueWriteBufferRpcHelperMallocHostRpcM(const Captures::DynamicTraits &dynamicTraits, cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, size_t offset, size_t size, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.command_queue = command_queue;
        args.buffer = buffer;
        args.blocking_write = blocking_write;
        args.offset = offset;
        args.size = size;
        args.ptr = ptr;
        args.num_events_in_wait_list = num_events_in_wait_list;
        args.event_wait_list = event_wait_list;
        args.event = event;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClEnqueueWriteBufferRpcHelperMallocHostRpcM &message, cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, size_t offset, size_t size, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.command_queue = command_queue;
        message.args.buffer = buffer;
        message.args.blocking_write = blocking_write;
        message.args.offset = offset;
        message.args.size = size;
        message.args.ptr = ptr;
        message.args.num_events_in_wait_list = num_events_in_wait_list;
        message.args.event_wait_list = event_wait_list;
        message.args.event = event;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event_wait_list){
            memcpy(asMemcpyDstT(captures.event_wait_list), args.event_wait_list, dynMemTraits.event_wait_list.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event){
            *args.event = captures.event;
        }
    }
};
static_assert(std::is_standard_layout_v<ClEnqueueWriteBufferRpcHelperMallocHostRpcM>);
struct ClEnqueueWriteBufferRpcHelperZeroCopyMallocShmemRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 75;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_command_queue command_queue = {};
        cl_mem buffer = {};
        cl_bool blocking_write = {};
        size_t offset = {};
        size_t size = {};
        const void* ptr = {};
        cl_uint num_events_in_wait_list = {};
        const cl_event* event_wait_list = {};
        cl_event* event = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->command_queue == rhs.command_queue;
            equal &= this->buffer == rhs.buffer;
            equal &= this->blocking_write == rhs.blocking_write;
            equal &= this->offset == rhs.offset;
            equal &= this->size == rhs.size;
            equal &= this->ptr == rhs.ptr;
            equal &= this->num_events_in_wait_list == rhs.num_events_in_wait_list;
            equal &= this->event_wait_list == rhs.event_wait_list;
            equal &= this->event == rhs.event;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, size_t offset, size_t size, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits event_wait_list = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        cl_event event;
        uint32_t countEvent_wait_list = 0;
        cl_event event_wait_list[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countEvent_wait_list = dynamicTraits.event_wait_list.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClEnqueueWriteBufferRpcHelperZeroCopyMallocShmemRpcM() = default;

    ClEnqueueWriteBufferRpcHelperZeroCopyMallocShmemRpcM(const Captures::DynamicTraits &dynamicTraits, cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, size_t offset, size_t size, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.command_queue = command_queue;
        args.buffer = buffer;
        args.blocking_write = blocking_write;
        args.offset = offset;
        args.size = size;
        args.ptr = ptr;
        args.num_events_in_wait_list = num_events_in_wait_list;
        args.event_wait_list = event_wait_list;
        args.event = event;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClEnqueueWriteBufferRpcHelperZeroCopyMallocShmemRpcM &message, cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, size_t offset, size_t size, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.command_queue = command_queue;
        message.args.buffer = buffer;
        message.args.blocking_write = blocking_write;
        message.args.offset = offset;
        message.args.size = size;
        message.args.ptr = ptr;
        message.args.num_events_in_wait_list = num_events_in_wait_list;
        message.args.event_wait_list = event_wait_list;
        message.args.event = event;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event_wait_list){
            memcpy(asMemcpyDstT(captures.event_wait_list), args.event_wait_list, dynMemTraits.event_wait_list.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event){
            *args.event = captures.event;
        }
    }
};
static_assert(std::is_standard_layout_v<ClEnqueueWriteBufferRpcHelperZeroCopyMallocShmemRpcM>);
struct ClEnqueueWriteBufferRectRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 76;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_command_queue command_queue = {};
        cl_mem buffer = {};
        cl_bool blocking_write = {};
        const size_t* buffer_offset = {};
        const size_t* host_offset = {};
        const size_t* region = {};
        size_t buffer_row_pitch = {};
        size_t buffer_slice_pitch = {};
        size_t host_row_pitch = {};
        size_t host_slice_pitch = {};
        const void* ptr = {};
        cl_uint num_events_in_wait_list = {};
        const cl_event* event_wait_list = {};
        cl_event* event = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->command_queue == rhs.command_queue;
            equal &= this->buffer == rhs.buffer;
            equal &= this->blocking_write == rhs.blocking_write;
            equal &= this->buffer_offset == rhs.buffer_offset;
            equal &= this->host_offset == rhs.host_offset;
            equal &= this->region == rhs.region;
            equal &= this->buffer_row_pitch == rhs.buffer_row_pitch;
            equal &= this->buffer_slice_pitch == rhs.buffer_slice_pitch;
            equal &= this->host_row_pitch == rhs.host_row_pitch;
            equal &= this->host_slice_pitch == rhs.host_slice_pitch;
            equal &= this->ptr == rhs.ptr;
            equal &= this->num_events_in_wait_list == rhs.num_events_in_wait_list;
            equal &= this->event_wait_list == rhs.event_wait_list;
            equal &= this->event == rhs.event;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, const size_t* buffer_offset, const size_t* host_offset, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits event_wait_list = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        size_t buffer_offset[3];
        size_t host_offset[3];
        size_t region[3];
        cl_event event;
        uint32_t countEvent_wait_list = 0;
        cl_event event_wait_list[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countEvent_wait_list = dynamicTraits.event_wait_list.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClEnqueueWriteBufferRectRpcM() = default;

    ClEnqueueWriteBufferRectRpcM(const Captures::DynamicTraits &dynamicTraits, cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, const size_t* buffer_offset, const size_t* host_offset, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.command_queue = command_queue;
        args.buffer = buffer;
        args.blocking_write = blocking_write;
        args.buffer_offset = buffer_offset;
        args.host_offset = host_offset;
        args.region = region;
        args.buffer_row_pitch = buffer_row_pitch;
        args.buffer_slice_pitch = buffer_slice_pitch;
        args.host_row_pitch = host_row_pitch;
        args.host_slice_pitch = host_slice_pitch;
        args.ptr = ptr;
        args.num_events_in_wait_list = num_events_in_wait_list;
        args.event_wait_list = event_wait_list;
        args.event = event;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClEnqueueWriteBufferRectRpcM &message, cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, const size_t* buffer_offset, const size_t* host_offset, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.command_queue = command_queue;
        message.args.buffer = buffer;
        message.args.blocking_write = blocking_write;
        message.args.buffer_offset = buffer_offset;
        message.args.host_offset = host_offset;
        message.args.region = region;
        message.args.buffer_row_pitch = buffer_row_pitch;
        message.args.buffer_slice_pitch = buffer_slice_pitch;
        message.args.host_row_pitch = host_row_pitch;
        message.args.host_slice_pitch = host_slice_pitch;
        message.args.ptr = ptr;
        message.args.num_events_in_wait_list = num_events_in_wait_list;
        message.args.event_wait_list = event_wait_list;
        message.args.event = event;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.buffer_offset){
            memcpy(asMemcpyDstT(captures.buffer_offset), args.buffer_offset, 3 * sizeof(size_t));
        }
        if(args.host_offset){
            memcpy(asMemcpyDstT(captures.host_offset), args.host_offset, 3 * sizeof(size_t));
        }
        if(args.region){
            memcpy(asMemcpyDstT(captures.region), args.region, 3 * sizeof(size_t));
        }
        if(args.event_wait_list){
            memcpy(asMemcpyDstT(captures.event_wait_list), args.event_wait_list, dynMemTraits.event_wait_list.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event){
            *args.event = captures.event;
        }
    }
};
static_assert(std::is_standard_layout_v<ClEnqueueWriteBufferRectRpcM>);
struct ClEnqueueWriteBufferRectRpcHelperMallocHostRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 77;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_command_queue command_queue = {};
        cl_mem buffer = {};
        cl_bool blocking_write = {};
        const size_t* buffer_offset = {};
        const size_t* host_offset = {};
        const size_t* region = {};
        size_t buffer_row_pitch = {};
        size_t buffer_slice_pitch = {};
        size_t host_row_pitch = {};
        size_t host_slice_pitch = {};
        const void* ptr = {};
        cl_uint num_events_in_wait_list = {};
        const cl_event* event_wait_list = {};
        cl_event* event = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->command_queue == rhs.command_queue;
            equal &= this->buffer == rhs.buffer;
            equal &= this->blocking_write == rhs.blocking_write;
            equal &= this->buffer_offset == rhs.buffer_offset;
            equal &= this->host_offset == rhs.host_offset;
            equal &= this->region == rhs.region;
            equal &= this->buffer_row_pitch == rhs.buffer_row_pitch;
            equal &= this->buffer_slice_pitch == rhs.buffer_slice_pitch;
            equal &= this->host_row_pitch == rhs.host_row_pitch;
            equal &= this->host_slice_pitch == rhs.host_slice_pitch;
            equal &= this->ptr == rhs.ptr;
            equal &= this->num_events_in_wait_list == rhs.num_events_in_wait_list;
            equal &= this->event_wait_list == rhs.event_wait_list;
            equal &= this->event == rhs.event;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, const size_t* buffer_offset, const size_t* host_offset, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits event_wait_list = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        size_t buffer_offset[3];
        size_t host_offset[3];
        size_t region[3];
        cl_event event;
        uint32_t countEvent_wait_list = 0;
        cl_event event_wait_list[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countEvent_wait_list = dynamicTraits.event_wait_list.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClEnqueueWriteBufferRectRpcHelperMallocHostRpcM() = default;

    ClEnqueueWriteBufferRectRpcHelperMallocHostRpcM(const Captures::DynamicTraits &dynamicTraits, cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, const size_t* buffer_offset, const size_t* host_offset, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.command_queue = command_queue;
        args.buffer = buffer;
        args.blocking_write = blocking_write;
        args.buffer_offset = buffer_offset;
        args.host_offset = host_offset;
        args.region = region;
        args.buffer_row_pitch = buffer_row_pitch;
        args.buffer_slice_pitch = buffer_slice_pitch;
        args.host_row_pitch = host_row_pitch;
        args.host_slice_pitch = host_slice_pitch;
        args.ptr = ptr;
        args.num_events_in_wait_list = num_events_in_wait_list;
        args.event_wait_list = event_wait_list;
        args.event = event;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClEnqueueWriteBufferRectRpcHelperMallocHostRpcM &message, cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, const size_t* buffer_offset, const size_t* host_offset, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.command_queue = command_queue;
        message.args.buffer = buffer;
        message.args.blocking_write = blocking_write;
        message.args.buffer_offset = buffer_offset;
        message.args.host_offset = host_offset;
        message.args.region = region;
        message.args.buffer_row_pitch = buffer_row_pitch;
        message.args.buffer_slice_pitch = buffer_slice_pitch;
        message.args.host_row_pitch = host_row_pitch;
        message.args.host_slice_pitch = host_slice_pitch;
        message.args.ptr = ptr;
        message.args.num_events_in_wait_list = num_events_in_wait_list;
        message.args.event_wait_list = event_wait_list;
        message.args.event = event;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.buffer_offset){
            memcpy(asMemcpyDstT(captures.buffer_offset), args.buffer_offset, 3 * sizeof(size_t));
        }
        if(args.host_offset){
            memcpy(asMemcpyDstT(captures.host_offset), args.host_offset, 3 * sizeof(size_t));
        }
        if(args.region){
            memcpy(asMemcpyDstT(captures.region), args.region, 3 * sizeof(size_t));
        }
        if(args.event_wait_list){
            memcpy(asMemcpyDstT(captures.event_wait_list), args.event_wait_list, dynMemTraits.event_wait_list.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event){
            *args.event = captures.event;
        }
    }
};
static_assert(std::is_standard_layout_v<ClEnqueueWriteBufferRectRpcHelperMallocHostRpcM>);
struct ClEnqueueWriteBufferRectRpcHelperZeroCopyMallocShmemRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 78;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_command_queue command_queue = {};
        cl_mem buffer = {};
        cl_bool blocking_write = {};
        const size_t* buffer_offset = {};
        const size_t* host_offset = {};
        const size_t* region = {};
        size_t buffer_row_pitch = {};
        size_t buffer_slice_pitch = {};
        size_t host_row_pitch = {};
        size_t host_slice_pitch = {};
        const void* ptr = {};
        cl_uint num_events_in_wait_list = {};
        const cl_event* event_wait_list = {};
        cl_event* event = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->command_queue == rhs.command_queue;
            equal &= this->buffer == rhs.buffer;
            equal &= this->blocking_write == rhs.blocking_write;
            equal &= this->buffer_offset == rhs.buffer_offset;
            equal &= this->host_offset == rhs.host_offset;
            equal &= this->region == rhs.region;
            equal &= this->buffer_row_pitch == rhs.buffer_row_pitch;
            equal &= this->buffer_slice_pitch == rhs.buffer_slice_pitch;
            equal &= this->host_row_pitch == rhs.host_row_pitch;
            equal &= this->host_slice_pitch == rhs.host_slice_pitch;
            equal &= this->ptr == rhs.ptr;
            equal &= this->num_events_in_wait_list == rhs.num_events_in_wait_list;
            equal &= this->event_wait_list == rhs.event_wait_list;
            equal &= this->event == rhs.event;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, const size_t* buffer_offset, const size_t* host_offset, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits event_wait_list = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        size_t buffer_offset[3];
        size_t host_offset[3];
        size_t region[3];
        cl_event event;
        uint32_t countEvent_wait_list = 0;
        cl_event event_wait_list[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countEvent_wait_list = dynamicTraits.event_wait_list.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClEnqueueWriteBufferRectRpcHelperZeroCopyMallocShmemRpcM() = default;

    ClEnqueueWriteBufferRectRpcHelperZeroCopyMallocShmemRpcM(const Captures::DynamicTraits &dynamicTraits, cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, const size_t* buffer_offset, const size_t* host_offset, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.command_queue = command_queue;
        args.buffer = buffer;
        args.blocking_write = blocking_write;
        args.buffer_offset = buffer_offset;
        args.host_offset = host_offset;
        args.region = region;
        args.buffer_row_pitch = buffer_row_pitch;
        args.buffer_slice_pitch = buffer_slice_pitch;
        args.host_row_pitch = host_row_pitch;
        args.host_slice_pitch = host_slice_pitch;
        args.ptr = ptr;
        args.num_events_in_wait_list = num_events_in_wait_list;
        args.event_wait_list = event_wait_list;
        args.event = event;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClEnqueueWriteBufferRectRpcHelperZeroCopyMallocShmemRpcM &message, cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write, const size_t* buffer_offset, const size_t* host_offset, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.command_queue = command_queue;
        message.args.buffer = buffer;
        message.args.blocking_write = blocking_write;
        message.args.buffer_offset = buffer_offset;
        message.args.host_offset = host_offset;
        message.args.region = region;
        message.args.buffer_row_pitch = buffer_row_pitch;
        message.args.buffer_slice_pitch = buffer_slice_pitch;
        message.args.host_row_pitch = host_row_pitch;
        message.args.host_slice_pitch = host_slice_pitch;
        message.args.ptr = ptr;
        message.args.num_events_in_wait_list = num_events_in_wait_list;
        message.args.event_wait_list = event_wait_list;
        message.args.event = event;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.buffer_offset){
            memcpy(asMemcpyDstT(captures.buffer_offset), args.buffer_offset, 3 * sizeof(size_t));
        }
        if(args.host_offset){
            memcpy(asMemcpyDstT(captures.host_offset), args.host_offset, 3 * sizeof(size_t));
        }
        if(args.region){
            memcpy(asMemcpyDstT(captures.region), args.region, 3 * sizeof(size_t));
        }
        if(args.event_wait_list){
            memcpy(asMemcpyDstT(captures.event_wait_list), args.event_wait_list, dynMemTraits.event_wait_list.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event){
            *args.event = captures.event;
        }
    }
};
static_assert(std::is_standard_layout_v<ClEnqueueWriteBufferRectRpcHelperZeroCopyMallocShmemRpcM>);
struct ClEnqueueReadBufferRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 79;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_command_queue command_queue = {};
        cl_mem buffer = {};
        cl_bool blocking_read = {};
        size_t offset = {};
        size_t size = {};
        void* ptr = {};
        cl_uint num_events_in_wait_list = {};
        const cl_event* event_wait_list = {};
        cl_event* event = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->command_queue == rhs.command_queue;
            equal &= this->buffer == rhs.buffer;
            equal &= this->blocking_read == rhs.blocking_read;
            equal &= this->offset == rhs.offset;
            equal &= this->size == rhs.size;
            equal &= this->ptr == rhs.ptr;
            equal &= this->num_events_in_wait_list == rhs.num_events_in_wait_list;
            equal &= this->event_wait_list == rhs.event_wait_list;
            equal &= this->event == rhs.event;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, size_t offset, size_t size, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits event_wait_list = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        cl_event event;
        uint32_t countEvent_wait_list = 0;
        cl_event event_wait_list[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countEvent_wait_list = dynamicTraits.event_wait_list.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClEnqueueReadBufferRpcM() = default;

    ClEnqueueReadBufferRpcM(const Captures::DynamicTraits &dynamicTraits, cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, size_t offset, size_t size, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.command_queue = command_queue;
        args.buffer = buffer;
        args.blocking_read = blocking_read;
        args.offset = offset;
        args.size = size;
        args.ptr = ptr;
        args.num_events_in_wait_list = num_events_in_wait_list;
        args.event_wait_list = event_wait_list;
        args.event = event;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClEnqueueReadBufferRpcM &message, cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, size_t offset, size_t size, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.command_queue = command_queue;
        message.args.buffer = buffer;
        message.args.blocking_read = blocking_read;
        message.args.offset = offset;
        message.args.size = size;
        message.args.ptr = ptr;
        message.args.num_events_in_wait_list = num_events_in_wait_list;
        message.args.event_wait_list = event_wait_list;
        message.args.event = event;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event_wait_list){
            memcpy(asMemcpyDstT(captures.event_wait_list), args.event_wait_list, dynMemTraits.event_wait_list.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event){
            *args.event = captures.event;
        }
    }
};
static_assert(std::is_standard_layout_v<ClEnqueueReadBufferRpcM>);
struct ClEnqueueReadBufferRectRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 80;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_command_queue command_queue = {};
        cl_mem buffer = {};
        cl_bool blocking_read = {};
        const size_t* buffer_offset = {};
        const size_t* host_offset = {};
        const size_t* region = {};
        size_t buffer_row_pitch = {};
        size_t buffer_slice_pitch = {};
        size_t host_row_pitch = {};
        size_t host_slice_pitch = {};
        void* ptr = {};
        cl_uint num_events_in_wait_list = {};
        const cl_event* event_wait_list = {};
        cl_event* event = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->command_queue == rhs.command_queue;
            equal &= this->buffer == rhs.buffer;
            equal &= this->blocking_read == rhs.blocking_read;
            equal &= this->buffer_offset == rhs.buffer_offset;
            equal &= this->host_offset == rhs.host_offset;
            equal &= this->region == rhs.region;
            equal &= this->buffer_row_pitch == rhs.buffer_row_pitch;
            equal &= this->buffer_slice_pitch == rhs.buffer_slice_pitch;
            equal &= this->host_row_pitch == rhs.host_row_pitch;
            equal &= this->host_slice_pitch == rhs.host_slice_pitch;
            equal &= this->ptr == rhs.ptr;
            equal &= this->num_events_in_wait_list == rhs.num_events_in_wait_list;
            equal &= this->event_wait_list == rhs.event_wait_list;
            equal &= this->event == rhs.event;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, const size_t* buffer_offset, const size_t* host_offset, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits event_wait_list = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        size_t buffer_offset[3];
        size_t host_offset[3];
        size_t region[3];
        cl_event event;
        uint32_t countEvent_wait_list = 0;
        cl_event event_wait_list[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countEvent_wait_list = dynamicTraits.event_wait_list.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClEnqueueReadBufferRectRpcM() = default;

    ClEnqueueReadBufferRectRpcM(const Captures::DynamicTraits &dynamicTraits, cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, const size_t* buffer_offset, const size_t* host_offset, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.command_queue = command_queue;
        args.buffer = buffer;
        args.blocking_read = blocking_read;
        args.buffer_offset = buffer_offset;
        args.host_offset = host_offset;
        args.region = region;
        args.buffer_row_pitch = buffer_row_pitch;
        args.buffer_slice_pitch = buffer_slice_pitch;
        args.host_row_pitch = host_row_pitch;
        args.host_slice_pitch = host_slice_pitch;
        args.ptr = ptr;
        args.num_events_in_wait_list = num_events_in_wait_list;
        args.event_wait_list = event_wait_list;
        args.event = event;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClEnqueueReadBufferRectRpcM &message, cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, const size_t* buffer_offset, const size_t* host_offset, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.command_queue = command_queue;
        message.args.buffer = buffer;
        message.args.blocking_read = blocking_read;
        message.args.buffer_offset = buffer_offset;
        message.args.host_offset = host_offset;
        message.args.region = region;
        message.args.buffer_row_pitch = buffer_row_pitch;
        message.args.buffer_slice_pitch = buffer_slice_pitch;
        message.args.host_row_pitch = host_row_pitch;
        message.args.host_slice_pitch = host_slice_pitch;
        message.args.ptr = ptr;
        message.args.num_events_in_wait_list = num_events_in_wait_list;
        message.args.event_wait_list = event_wait_list;
        message.args.event = event;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.buffer_offset){
            memcpy(asMemcpyDstT(captures.buffer_offset), args.buffer_offset, 3 * sizeof(size_t));
        }
        if(args.host_offset){
            memcpy(asMemcpyDstT(captures.host_offset), args.host_offset, 3 * sizeof(size_t));
        }
        if(args.region){
            memcpy(asMemcpyDstT(captures.region), args.region, 3 * sizeof(size_t));
        }
        if(args.event_wait_list){
            memcpy(asMemcpyDstT(captures.event_wait_list), args.event_wait_list, dynMemTraits.event_wait_list.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event){
            *args.event = captures.event;
        }
    }
};
static_assert(std::is_standard_layout_v<ClEnqueueReadBufferRectRpcM>);
struct ClEnqueueReadBufferRectRpcHelperMallocHostRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 81;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_command_queue command_queue = {};
        cl_mem buffer = {};
        cl_bool blocking_read = {};
        const size_t* buffer_offset = {};
        const size_t* host_offset = {};
        const size_t* region = {};
        size_t buffer_row_pitch = {};
        size_t buffer_slice_pitch = {};
        size_t host_row_pitch = {};
        size_t host_slice_pitch = {};
        void* ptr = {};
        cl_uint num_events_in_wait_list = {};
        const cl_event* event_wait_list = {};
        cl_event* event = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->command_queue == rhs.command_queue;
            equal &= this->buffer == rhs.buffer;
            equal &= this->blocking_read == rhs.blocking_read;
            equal &= this->buffer_offset == rhs.buffer_offset;
            equal &= this->host_offset == rhs.host_offset;
            equal &= this->region == rhs.region;
            equal &= this->buffer_row_pitch == rhs.buffer_row_pitch;
            equal &= this->buffer_slice_pitch == rhs.buffer_slice_pitch;
            equal &= this->host_row_pitch == rhs.host_row_pitch;
            equal &= this->host_slice_pitch == rhs.host_slice_pitch;
            equal &= this->ptr == rhs.ptr;
            equal &= this->num_events_in_wait_list == rhs.num_events_in_wait_list;
            equal &= this->event_wait_list == rhs.event_wait_list;
            equal &= this->event == rhs.event;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, const size_t* buffer_offset, const size_t* host_offset, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits event_wait_list = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        size_t buffer_offset[3];
        size_t host_offset[3];
        size_t region[3];
        cl_event event;
        uint32_t countEvent_wait_list = 0;
        cl_event event_wait_list[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countEvent_wait_list = dynamicTraits.event_wait_list.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClEnqueueReadBufferRectRpcHelperMallocHostRpcM() = default;

    ClEnqueueReadBufferRectRpcHelperMallocHostRpcM(const Captures::DynamicTraits &dynamicTraits, cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, const size_t* buffer_offset, const size_t* host_offset, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.command_queue = command_queue;
        args.buffer = buffer;
        args.blocking_read = blocking_read;
        args.buffer_offset = buffer_offset;
        args.host_offset = host_offset;
        args.region = region;
        args.buffer_row_pitch = buffer_row_pitch;
        args.buffer_slice_pitch = buffer_slice_pitch;
        args.host_row_pitch = host_row_pitch;
        args.host_slice_pitch = host_slice_pitch;
        args.ptr = ptr;
        args.num_events_in_wait_list = num_events_in_wait_list;
        args.event_wait_list = event_wait_list;
        args.event = event;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClEnqueueReadBufferRectRpcHelperMallocHostRpcM &message, cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, const size_t* buffer_offset, const size_t* host_offset, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.command_queue = command_queue;
        message.args.buffer = buffer;
        message.args.blocking_read = blocking_read;
        message.args.buffer_offset = buffer_offset;
        message.args.host_offset = host_offset;
        message.args.region = region;
        message.args.buffer_row_pitch = buffer_row_pitch;
        message.args.buffer_slice_pitch = buffer_slice_pitch;
        message.args.host_row_pitch = host_row_pitch;
        message.args.host_slice_pitch = host_slice_pitch;
        message.args.ptr = ptr;
        message.args.num_events_in_wait_list = num_events_in_wait_list;
        message.args.event_wait_list = event_wait_list;
        message.args.event = event;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.buffer_offset){
            memcpy(asMemcpyDstT(captures.buffer_offset), args.buffer_offset, 3 * sizeof(size_t));
        }
        if(args.host_offset){
            memcpy(asMemcpyDstT(captures.host_offset), args.host_offset, 3 * sizeof(size_t));
        }
        if(args.region){
            memcpy(asMemcpyDstT(captures.region), args.region, 3 * sizeof(size_t));
        }
        if(args.event_wait_list){
            memcpy(asMemcpyDstT(captures.event_wait_list), args.event_wait_list, dynMemTraits.event_wait_list.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event){
            *args.event = captures.event;
        }
    }
};
static_assert(std::is_standard_layout_v<ClEnqueueReadBufferRectRpcHelperMallocHostRpcM>);
struct ClEnqueueReadBufferRectRpcHelperZeroCopyMallocShmemRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 82;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_command_queue command_queue = {};
        cl_mem buffer = {};
        cl_bool blocking_read = {};
        const size_t* buffer_offset = {};
        const size_t* host_offset = {};
        const size_t* region = {};
        size_t buffer_row_pitch = {};
        size_t buffer_slice_pitch = {};
        size_t host_row_pitch = {};
        size_t host_slice_pitch = {};
        void* ptr = {};
        cl_uint num_events_in_wait_list = {};
        const cl_event* event_wait_list = {};
        cl_event* event = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->command_queue == rhs.command_queue;
            equal &= this->buffer == rhs.buffer;
            equal &= this->blocking_read == rhs.blocking_read;
            equal &= this->buffer_offset == rhs.buffer_offset;
            equal &= this->host_offset == rhs.host_offset;
            equal &= this->region == rhs.region;
            equal &= this->buffer_row_pitch == rhs.buffer_row_pitch;
            equal &= this->buffer_slice_pitch == rhs.buffer_slice_pitch;
            equal &= this->host_row_pitch == rhs.host_row_pitch;
            equal &= this->host_slice_pitch == rhs.host_slice_pitch;
            equal &= this->ptr == rhs.ptr;
            equal &= this->num_events_in_wait_list == rhs.num_events_in_wait_list;
            equal &= this->event_wait_list == rhs.event_wait_list;
            equal &= this->event == rhs.event;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, const size_t* buffer_offset, const size_t* host_offset, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits event_wait_list = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        size_t buffer_offset[3];
        size_t host_offset[3];
        size_t region[3];
        cl_event event;
        uint32_t countEvent_wait_list = 0;
        cl_event event_wait_list[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countEvent_wait_list = dynamicTraits.event_wait_list.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClEnqueueReadBufferRectRpcHelperZeroCopyMallocShmemRpcM() = default;

    ClEnqueueReadBufferRectRpcHelperZeroCopyMallocShmemRpcM(const Captures::DynamicTraits &dynamicTraits, cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, const size_t* buffer_offset, const size_t* host_offset, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.command_queue = command_queue;
        args.buffer = buffer;
        args.blocking_read = blocking_read;
        args.buffer_offset = buffer_offset;
        args.host_offset = host_offset;
        args.region = region;
        args.buffer_row_pitch = buffer_row_pitch;
        args.buffer_slice_pitch = buffer_slice_pitch;
        args.host_row_pitch = host_row_pitch;
        args.host_slice_pitch = host_slice_pitch;
        args.ptr = ptr;
        args.num_events_in_wait_list = num_events_in_wait_list;
        args.event_wait_list = event_wait_list;
        args.event = event;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClEnqueueReadBufferRectRpcHelperZeroCopyMallocShmemRpcM &message, cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, const size_t* buffer_offset, const size_t* host_offset, const size_t* region, size_t buffer_row_pitch, size_t buffer_slice_pitch, size_t host_row_pitch, size_t host_slice_pitch, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.command_queue = command_queue;
        message.args.buffer = buffer;
        message.args.blocking_read = blocking_read;
        message.args.buffer_offset = buffer_offset;
        message.args.host_offset = host_offset;
        message.args.region = region;
        message.args.buffer_row_pitch = buffer_row_pitch;
        message.args.buffer_slice_pitch = buffer_slice_pitch;
        message.args.host_row_pitch = host_row_pitch;
        message.args.host_slice_pitch = host_slice_pitch;
        message.args.ptr = ptr;
        message.args.num_events_in_wait_list = num_events_in_wait_list;
        message.args.event_wait_list = event_wait_list;
        message.args.event = event;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.buffer_offset){
            memcpy(asMemcpyDstT(captures.buffer_offset), args.buffer_offset, 3 * sizeof(size_t));
        }
        if(args.host_offset){
            memcpy(asMemcpyDstT(captures.host_offset), args.host_offset, 3 * sizeof(size_t));
        }
        if(args.region){
            memcpy(asMemcpyDstT(captures.region), args.region, 3 * sizeof(size_t));
        }
        if(args.event_wait_list){
            memcpy(asMemcpyDstT(captures.event_wait_list), args.event_wait_list, dynMemTraits.event_wait_list.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event){
            *args.event = captures.event;
        }
    }
};
static_assert(std::is_standard_layout_v<ClEnqueueReadBufferRectRpcHelperZeroCopyMallocShmemRpcM>);
struct ClEnqueueReadBufferRpcHelperMallocHostRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 83;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_command_queue command_queue = {};
        cl_mem buffer = {};
        cl_bool blocking_read = {};
        size_t offset = {};
        size_t size = {};
        void* ptr = {};
        cl_uint num_events_in_wait_list = {};
        const cl_event* event_wait_list = {};
        cl_event* event = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->command_queue == rhs.command_queue;
            equal &= this->buffer == rhs.buffer;
            equal &= this->blocking_read == rhs.blocking_read;
            equal &= this->offset == rhs.offset;
            equal &= this->size == rhs.size;
            equal &= this->ptr == rhs.ptr;
            equal &= this->num_events_in_wait_list == rhs.num_events_in_wait_list;
            equal &= this->event_wait_list == rhs.event_wait_list;
            equal &= this->event == rhs.event;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, size_t offset, size_t size, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits event_wait_list = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        cl_event event;
        uint32_t countEvent_wait_list = 0;
        cl_event event_wait_list[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countEvent_wait_list = dynamicTraits.event_wait_list.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClEnqueueReadBufferRpcHelperMallocHostRpcM() = default;

    ClEnqueueReadBufferRpcHelperMallocHostRpcM(const Captures::DynamicTraits &dynamicTraits, cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, size_t offset, size_t size, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.command_queue = command_queue;
        args.buffer = buffer;
        args.blocking_read = blocking_read;
        args.offset = offset;
        args.size = size;
        args.ptr = ptr;
        args.num_events_in_wait_list = num_events_in_wait_list;
        args.event_wait_list = event_wait_list;
        args.event = event;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClEnqueueReadBufferRpcHelperMallocHostRpcM &message, cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, size_t offset, size_t size, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.command_queue = command_queue;
        message.args.buffer = buffer;
        message.args.blocking_read = blocking_read;
        message.args.offset = offset;
        message.args.size = size;
        message.args.ptr = ptr;
        message.args.num_events_in_wait_list = num_events_in_wait_list;
        message.args.event_wait_list = event_wait_list;
        message.args.event = event;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event_wait_list){
            memcpy(asMemcpyDstT(captures.event_wait_list), args.event_wait_list, dynMemTraits.event_wait_list.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event){
            *args.event = captures.event;
        }
    }
};
static_assert(std::is_standard_layout_v<ClEnqueueReadBufferRpcHelperMallocHostRpcM>);
struct ClEnqueueReadBufferRpcHelperZeroCopyMallocShmemRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 84;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_command_queue command_queue = {};
        cl_mem buffer = {};
        cl_bool blocking_read = {};
        size_t offset = {};
        size_t size = {};
        void* ptr = {};
        cl_uint num_events_in_wait_list = {};
        const cl_event* event_wait_list = {};
        cl_event* event = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->command_queue == rhs.command_queue;
            equal &= this->buffer == rhs.buffer;
            equal &= this->blocking_read == rhs.blocking_read;
            equal &= this->offset == rhs.offset;
            equal &= this->size == rhs.size;
            equal &= this->ptr == rhs.ptr;
            equal &= this->num_events_in_wait_list == rhs.num_events_in_wait_list;
            equal &= this->event_wait_list == rhs.event_wait_list;
            equal &= this->event == rhs.event;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, size_t offset, size_t size, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits event_wait_list = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        cl_event event;
        uint32_t countEvent_wait_list = 0;
        cl_event event_wait_list[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countEvent_wait_list = dynamicTraits.event_wait_list.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClEnqueueReadBufferRpcHelperZeroCopyMallocShmemRpcM() = default;

    ClEnqueueReadBufferRpcHelperZeroCopyMallocShmemRpcM(const Captures::DynamicTraits &dynamicTraits, cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, size_t offset, size_t size, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.command_queue = command_queue;
        args.buffer = buffer;
        args.blocking_read = blocking_read;
        args.offset = offset;
        args.size = size;
        args.ptr = ptr;
        args.num_events_in_wait_list = num_events_in_wait_list;
        args.event_wait_list = event_wait_list;
        args.event = event;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClEnqueueReadBufferRpcHelperZeroCopyMallocShmemRpcM &message, cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read, size_t offset, size_t size, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.command_queue = command_queue;
        message.args.buffer = buffer;
        message.args.blocking_read = blocking_read;
        message.args.offset = offset;
        message.args.size = size;
        message.args.ptr = ptr;
        message.args.num_events_in_wait_list = num_events_in_wait_list;
        message.args.event_wait_list = event_wait_list;
        message.args.event = event;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event_wait_list){
            memcpy(asMemcpyDstT(captures.event_wait_list), args.event_wait_list, dynMemTraits.event_wait_list.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event){
            *args.event = captures.event;
        }
    }
};
static_assert(std::is_standard_layout_v<ClEnqueueReadBufferRpcHelperZeroCopyMallocShmemRpcM>);
struct ClEnqueueCopyBufferRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 85;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_command_queue command_queue = {};
        cl_mem src_buffer = {};
        cl_mem dst_buffer = {};
        size_t src_offset = {};
        size_t dst_offset = {};
        size_t size = {};
        cl_uint num_events_in_wait_list = {};
        const cl_event* event_wait_list = {};
        cl_event* event = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->command_queue == rhs.command_queue;
            equal &= this->src_buffer == rhs.src_buffer;
            equal &= this->dst_buffer == rhs.dst_buffer;
            equal &= this->src_offset == rhs.src_offset;
            equal &= this->dst_offset == rhs.dst_offset;
            equal &= this->size == rhs.size;
            equal &= this->num_events_in_wait_list == rhs.num_events_in_wait_list;
            equal &= this->event_wait_list == rhs.event_wait_list;
            equal &= this->event == rhs.event;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_command_queue command_queue, cl_mem src_buffer, cl_mem dst_buffer, size_t src_offset, size_t dst_offset, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits event_wait_list = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        cl_event event;
        uint32_t countEvent_wait_list = 0;
        cl_event event_wait_list[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countEvent_wait_list = dynamicTraits.event_wait_list.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClEnqueueCopyBufferRpcM() = default;

    ClEnqueueCopyBufferRpcM(const Captures::DynamicTraits &dynamicTraits, cl_command_queue command_queue, cl_mem src_buffer, cl_mem dst_buffer, size_t src_offset, size_t dst_offset, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.command_queue = command_queue;
        args.src_buffer = src_buffer;
        args.dst_buffer = dst_buffer;
        args.src_offset = src_offset;
        args.dst_offset = dst_offset;
        args.size = size;
        args.num_events_in_wait_list = num_events_in_wait_list;
        args.event_wait_list = event_wait_list;
        args.event = event;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClEnqueueCopyBufferRpcM &message, cl_command_queue command_queue, cl_mem src_buffer, cl_mem dst_buffer, size_t src_offset, size_t dst_offset, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.command_queue = command_queue;
        message.args.src_buffer = src_buffer;
        message.args.dst_buffer = dst_buffer;
        message.args.src_offset = src_offset;
        message.args.dst_offset = dst_offset;
        message.args.size = size;
        message.args.num_events_in_wait_list = num_events_in_wait_list;
        message.args.event_wait_list = event_wait_list;
        message.args.event = event;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event_wait_list){
            memcpy(asMemcpyDstT(captures.event_wait_list), args.event_wait_list, dynMemTraits.event_wait_list.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event){
            *args.event = captures.event;
        }
    }
};
static_assert(std::is_standard_layout_v<ClEnqueueCopyBufferRpcM>);
struct ClEnqueueCopyBufferRectRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 86;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_command_queue command_queue = {};
        cl_mem src_buffer = {};
        cl_mem dst_buffer = {};
        const size_t* src_origin = {};
        const size_t* dst_origin = {};
        const size_t* region = {};
        size_t src_row_pitch = {};
        size_t src_slice_pitch = {};
        size_t dst_row_pitch = {};
        size_t dst_slice_pitch = {};
        cl_uint num_events_in_wait_list = {};
        const cl_event* event_wait_list = {};
        cl_event* event = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->command_queue == rhs.command_queue;
            equal &= this->src_buffer == rhs.src_buffer;
            equal &= this->dst_buffer == rhs.dst_buffer;
            equal &= this->src_origin == rhs.src_origin;
            equal &= this->dst_origin == rhs.dst_origin;
            equal &= this->region == rhs.region;
            equal &= this->src_row_pitch == rhs.src_row_pitch;
            equal &= this->src_slice_pitch == rhs.src_slice_pitch;
            equal &= this->dst_row_pitch == rhs.dst_row_pitch;
            equal &= this->dst_slice_pitch == rhs.dst_slice_pitch;
            equal &= this->num_events_in_wait_list == rhs.num_events_in_wait_list;
            equal &= this->event_wait_list == rhs.event_wait_list;
            equal &= this->event == rhs.event;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_command_queue command_queue, cl_mem src_buffer, cl_mem dst_buffer, const size_t* src_origin, const size_t* dst_origin, const size_t* region, size_t src_row_pitch, size_t src_slice_pitch, size_t dst_row_pitch, size_t dst_slice_pitch, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits event_wait_list = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        size_t src_origin[3];
        size_t dst_origin[3];
        size_t region[3];
        cl_event event;
        uint32_t countEvent_wait_list = 0;
        cl_event event_wait_list[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countEvent_wait_list = dynamicTraits.event_wait_list.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClEnqueueCopyBufferRectRpcM() = default;

    ClEnqueueCopyBufferRectRpcM(const Captures::DynamicTraits &dynamicTraits, cl_command_queue command_queue, cl_mem src_buffer, cl_mem dst_buffer, const size_t* src_origin, const size_t* dst_origin, const size_t* region, size_t src_row_pitch, size_t src_slice_pitch, size_t dst_row_pitch, size_t dst_slice_pitch, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.command_queue = command_queue;
        args.src_buffer = src_buffer;
        args.dst_buffer = dst_buffer;
        args.src_origin = src_origin;
        args.dst_origin = dst_origin;
        args.region = region;
        args.src_row_pitch = src_row_pitch;
        args.src_slice_pitch = src_slice_pitch;
        args.dst_row_pitch = dst_row_pitch;
        args.dst_slice_pitch = dst_slice_pitch;
        args.num_events_in_wait_list = num_events_in_wait_list;
        args.event_wait_list = event_wait_list;
        args.event = event;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClEnqueueCopyBufferRectRpcM &message, cl_command_queue command_queue, cl_mem src_buffer, cl_mem dst_buffer, const size_t* src_origin, const size_t* dst_origin, const size_t* region, size_t src_row_pitch, size_t src_slice_pitch, size_t dst_row_pitch, size_t dst_slice_pitch, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.command_queue = command_queue;
        message.args.src_buffer = src_buffer;
        message.args.dst_buffer = dst_buffer;
        message.args.src_origin = src_origin;
        message.args.dst_origin = dst_origin;
        message.args.region = region;
        message.args.src_row_pitch = src_row_pitch;
        message.args.src_slice_pitch = src_slice_pitch;
        message.args.dst_row_pitch = dst_row_pitch;
        message.args.dst_slice_pitch = dst_slice_pitch;
        message.args.num_events_in_wait_list = num_events_in_wait_list;
        message.args.event_wait_list = event_wait_list;
        message.args.event = event;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.src_origin){
            memcpy(asMemcpyDstT(captures.src_origin), args.src_origin, 3 * sizeof(size_t));
        }
        if(args.dst_origin){
            memcpy(asMemcpyDstT(captures.dst_origin), args.dst_origin, 3 * sizeof(size_t));
        }
        if(args.region){
            memcpy(asMemcpyDstT(captures.region), args.region, 3 * sizeof(size_t));
        }
        if(args.event_wait_list){
            memcpy(asMemcpyDstT(captures.event_wait_list), args.event_wait_list, dynMemTraits.event_wait_list.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event){
            *args.event = captures.event;
        }
    }
};
static_assert(std::is_standard_layout_v<ClEnqueueCopyBufferRectRpcM>);
struct ClEnqueueReadImageRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 87;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_command_queue command_queue = {};
        cl_mem image = {};
        cl_bool blocking_read = {};
        const size_t* src_origin = {};
        const size_t* region = {};
        size_t row_pitch = {};
        size_t slice_pitch = {};
        void* ptr = {};
        cl_uint num_events_in_wait_list = {};
        const cl_event* event_wait_list = {};
        cl_event* event = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->command_queue == rhs.command_queue;
            equal &= this->image == rhs.image;
            equal &= this->blocking_read == rhs.blocking_read;
            equal &= this->src_origin == rhs.src_origin;
            equal &= this->region == rhs.region;
            equal &= this->row_pitch == rhs.row_pitch;
            equal &= this->slice_pitch == rhs.slice_pitch;
            equal &= this->ptr == rhs.ptr;
            equal &= this->num_events_in_wait_list == rhs.num_events_in_wait_list;
            equal &= this->event_wait_list == rhs.event_wait_list;
            equal &= this->event == rhs.event;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_command_queue command_queue, cl_mem image, cl_bool blocking_read, const size_t* src_origin, const size_t* region, size_t row_pitch, size_t slice_pitch, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits event_wait_list = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        size_t src_origin[3];
        size_t region[3];
        cl_event event;
        uint32_t countEvent_wait_list = 0;
        cl_event event_wait_list[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countEvent_wait_list = dynamicTraits.event_wait_list.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClEnqueueReadImageRpcM() = default;

    ClEnqueueReadImageRpcM(const Captures::DynamicTraits &dynamicTraits, cl_command_queue command_queue, cl_mem image, cl_bool blocking_read, const size_t* src_origin, const size_t* region, size_t row_pitch, size_t slice_pitch, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.command_queue = command_queue;
        args.image = image;
        args.blocking_read = blocking_read;
        args.src_origin = src_origin;
        args.region = region;
        args.row_pitch = row_pitch;
        args.slice_pitch = slice_pitch;
        args.ptr = ptr;
        args.num_events_in_wait_list = num_events_in_wait_list;
        args.event_wait_list = event_wait_list;
        args.event = event;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClEnqueueReadImageRpcM &message, cl_command_queue command_queue, cl_mem image, cl_bool blocking_read, const size_t* src_origin, const size_t* region, size_t row_pitch, size_t slice_pitch, void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.command_queue = command_queue;
        message.args.image = image;
        message.args.blocking_read = blocking_read;
        message.args.src_origin = src_origin;
        message.args.region = region;
        message.args.row_pitch = row_pitch;
        message.args.slice_pitch = slice_pitch;
        message.args.ptr = ptr;
        message.args.num_events_in_wait_list = num_events_in_wait_list;
        message.args.event_wait_list = event_wait_list;
        message.args.event = event;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.src_origin){
            memcpy(asMemcpyDstT(captures.src_origin), args.src_origin, 3 * sizeof(size_t));
        }
        if(args.region){
            memcpy(asMemcpyDstT(captures.region), args.region, 3 * sizeof(size_t));
        }
        if(args.event_wait_list){
            memcpy(asMemcpyDstT(captures.event_wait_list), args.event_wait_list, dynMemTraits.event_wait_list.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event){
            *args.event = captures.event;
        }
    }
};
static_assert(std::is_standard_layout_v<ClEnqueueReadImageRpcM>);
struct ClEnqueueWriteImageRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 88;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_command_queue command_queue = {};
        cl_mem image = {};
        cl_bool blocking_write = {};
        const size_t* origin = {};
        const size_t* region = {};
        size_t input_row_pitch = {};
        size_t input_slice_pitch = {};
        const void* ptr = {};
        cl_uint num_events_in_wait_list = {};
        const cl_event* event_wait_list = {};
        cl_event* event = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->command_queue == rhs.command_queue;
            equal &= this->image == rhs.image;
            equal &= this->blocking_write == rhs.blocking_write;
            equal &= this->origin == rhs.origin;
            equal &= this->region == rhs.region;
            equal &= this->input_row_pitch == rhs.input_row_pitch;
            equal &= this->input_slice_pitch == rhs.input_slice_pitch;
            equal &= this->ptr == rhs.ptr;
            equal &= this->num_events_in_wait_list == rhs.num_events_in_wait_list;
            equal &= this->event_wait_list == rhs.event_wait_list;
            equal &= this->event == rhs.event;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_command_queue command_queue, cl_mem image, cl_bool blocking_write, const size_t* origin, const size_t* region, size_t input_row_pitch, size_t input_slice_pitch, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits event_wait_list = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        size_t origin[3];
        size_t region[3];
        cl_event event;
        uint32_t countEvent_wait_list = 0;
        cl_event event_wait_list[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countEvent_wait_list = dynamicTraits.event_wait_list.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClEnqueueWriteImageRpcM() = default;

    ClEnqueueWriteImageRpcM(const Captures::DynamicTraits &dynamicTraits, cl_command_queue command_queue, cl_mem image, cl_bool blocking_write, const size_t* origin, const size_t* region, size_t input_row_pitch, size_t input_slice_pitch, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.command_queue = command_queue;
        args.image = image;
        args.blocking_write = blocking_write;
        args.origin = origin;
        args.region = region;
        args.input_row_pitch = input_row_pitch;
        args.input_slice_pitch = input_slice_pitch;
        args.ptr = ptr;
        args.num_events_in_wait_list = num_events_in_wait_list;
        args.event_wait_list = event_wait_list;
        args.event = event;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClEnqueueWriteImageRpcM &message, cl_command_queue command_queue, cl_mem image, cl_bool blocking_write, const size_t* origin, const size_t* region, size_t input_row_pitch, size_t input_slice_pitch, const void* ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.command_queue = command_queue;
        message.args.image = image;
        message.args.blocking_write = blocking_write;
        message.args.origin = origin;
        message.args.region = region;
        message.args.input_row_pitch = input_row_pitch;
        message.args.input_slice_pitch = input_slice_pitch;
        message.args.ptr = ptr;
        message.args.num_events_in_wait_list = num_events_in_wait_list;
        message.args.event_wait_list = event_wait_list;
        message.args.event = event;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.origin){
            memcpy(asMemcpyDstT(captures.origin), args.origin, 3 * sizeof(size_t));
        }
        if(args.region){
            memcpy(asMemcpyDstT(captures.region), args.region, 3 * sizeof(size_t));
        }
        if(args.event_wait_list){
            memcpy(asMemcpyDstT(captures.event_wait_list), args.event_wait_list, dynMemTraits.event_wait_list.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event){
            *args.event = captures.event;
        }
    }
};
static_assert(std::is_standard_layout_v<ClEnqueueWriteImageRpcM>);
struct ClEnqueueCopyImageRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 89;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_command_queue command_queue = {};
        cl_mem src_image = {};
        cl_mem dst_image = {};
        const size_t* src_origin = {};
        const size_t* dst_origin = {};
        const size_t* region = {};
        cl_uint num_events_in_wait_list = {};
        const cl_event* event_wait_list = {};
        cl_event* event = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->command_queue == rhs.command_queue;
            equal &= this->src_image == rhs.src_image;
            equal &= this->dst_image == rhs.dst_image;
            equal &= this->src_origin == rhs.src_origin;
            equal &= this->dst_origin == rhs.dst_origin;
            equal &= this->region == rhs.region;
            equal &= this->num_events_in_wait_list == rhs.num_events_in_wait_list;
            equal &= this->event_wait_list == rhs.event_wait_list;
            equal &= this->event == rhs.event;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_command_queue command_queue, cl_mem src_image, cl_mem dst_image, const size_t* src_origin, const size_t* dst_origin, const size_t* region, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits event_wait_list = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        size_t src_origin[3];
        size_t dst_origin[3];
        size_t region[3];
        cl_event event;
        uint32_t countEvent_wait_list = 0;
        cl_event event_wait_list[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countEvent_wait_list = dynamicTraits.event_wait_list.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClEnqueueCopyImageRpcM() = default;

    ClEnqueueCopyImageRpcM(const Captures::DynamicTraits &dynamicTraits, cl_command_queue command_queue, cl_mem src_image, cl_mem dst_image, const size_t* src_origin, const size_t* dst_origin, const size_t* region, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.command_queue = command_queue;
        args.src_image = src_image;
        args.dst_image = dst_image;
        args.src_origin = src_origin;
        args.dst_origin = dst_origin;
        args.region = region;
        args.num_events_in_wait_list = num_events_in_wait_list;
        args.event_wait_list = event_wait_list;
        args.event = event;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClEnqueueCopyImageRpcM &message, cl_command_queue command_queue, cl_mem src_image, cl_mem dst_image, const size_t* src_origin, const size_t* dst_origin, const size_t* region, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.command_queue = command_queue;
        message.args.src_image = src_image;
        message.args.dst_image = dst_image;
        message.args.src_origin = src_origin;
        message.args.dst_origin = dst_origin;
        message.args.region = region;
        message.args.num_events_in_wait_list = num_events_in_wait_list;
        message.args.event_wait_list = event_wait_list;
        message.args.event = event;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.src_origin){
            memcpy(asMemcpyDstT(captures.src_origin), args.src_origin, 3 * sizeof(size_t));
        }
        if(args.dst_origin){
            memcpy(asMemcpyDstT(captures.dst_origin), args.dst_origin, 3 * sizeof(size_t));
        }
        if(args.region){
            memcpy(asMemcpyDstT(captures.region), args.region, 3 * sizeof(size_t));
        }
        if(args.event_wait_list){
            memcpy(asMemcpyDstT(captures.event_wait_list), args.event_wait_list, dynMemTraits.event_wait_list.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event){
            *args.event = captures.event;
        }
    }
};
static_assert(std::is_standard_layout_v<ClEnqueueCopyImageRpcM>);
struct ClEnqueueCopyImageToBufferRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 90;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_command_queue command_queue = {};
        cl_mem src_image = {};
        cl_mem dst_buffer = {};
        const size_t* src_origin = {};
        const size_t* region = {};
        size_t dst_offset = {};
        cl_uint num_events_in_wait_list = {};
        const cl_event* event_wait_list = {};
        cl_event* event = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->command_queue == rhs.command_queue;
            equal &= this->src_image == rhs.src_image;
            equal &= this->dst_buffer == rhs.dst_buffer;
            equal &= this->src_origin == rhs.src_origin;
            equal &= this->region == rhs.region;
            equal &= this->dst_offset == rhs.dst_offset;
            equal &= this->num_events_in_wait_list == rhs.num_events_in_wait_list;
            equal &= this->event_wait_list == rhs.event_wait_list;
            equal &= this->event == rhs.event;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_command_queue command_queue, cl_mem src_image, cl_mem dst_buffer, const size_t* src_origin, const size_t* region, size_t dst_offset, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits event_wait_list = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        size_t src_origin[3];
        size_t region[3];
        cl_event event;
        uint32_t countEvent_wait_list = 0;
        cl_event event_wait_list[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countEvent_wait_list = dynamicTraits.event_wait_list.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClEnqueueCopyImageToBufferRpcM() = default;

    ClEnqueueCopyImageToBufferRpcM(const Captures::DynamicTraits &dynamicTraits, cl_command_queue command_queue, cl_mem src_image, cl_mem dst_buffer, const size_t* src_origin, const size_t* region, size_t dst_offset, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.command_queue = command_queue;
        args.src_image = src_image;
        args.dst_buffer = dst_buffer;
        args.src_origin = src_origin;
        args.region = region;
        args.dst_offset = dst_offset;
        args.num_events_in_wait_list = num_events_in_wait_list;
        args.event_wait_list = event_wait_list;
        args.event = event;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClEnqueueCopyImageToBufferRpcM &message, cl_command_queue command_queue, cl_mem src_image, cl_mem dst_buffer, const size_t* src_origin, const size_t* region, size_t dst_offset, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.command_queue = command_queue;
        message.args.src_image = src_image;
        message.args.dst_buffer = dst_buffer;
        message.args.src_origin = src_origin;
        message.args.region = region;
        message.args.dst_offset = dst_offset;
        message.args.num_events_in_wait_list = num_events_in_wait_list;
        message.args.event_wait_list = event_wait_list;
        message.args.event = event;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.src_origin){
            memcpy(asMemcpyDstT(captures.src_origin), args.src_origin, 3 * sizeof(size_t));
        }
        if(args.region){
            memcpy(asMemcpyDstT(captures.region), args.region, 3 * sizeof(size_t));
        }
        if(args.event_wait_list){
            memcpy(asMemcpyDstT(captures.event_wait_list), args.event_wait_list, dynMemTraits.event_wait_list.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event){
            *args.event = captures.event;
        }
    }
};
static_assert(std::is_standard_layout_v<ClEnqueueCopyImageToBufferRpcM>);
struct ClEnqueueCopyBufferToImageRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 91;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_command_queue command_queue = {};
        cl_mem src_buffer = {};
        cl_mem dst_image = {};
        size_t src_offset = {};
        const size_t* dst_origin = {};
        const size_t* region = {};
        cl_uint num_events_in_wait_list = {};
        const cl_event* event_wait_list = {};
        cl_event* event = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->command_queue == rhs.command_queue;
            equal &= this->src_buffer == rhs.src_buffer;
            equal &= this->dst_image == rhs.dst_image;
            equal &= this->src_offset == rhs.src_offset;
            equal &= this->dst_origin == rhs.dst_origin;
            equal &= this->region == rhs.region;
            equal &= this->num_events_in_wait_list == rhs.num_events_in_wait_list;
            equal &= this->event_wait_list == rhs.event_wait_list;
            equal &= this->event == rhs.event;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_command_queue command_queue, cl_mem src_buffer, cl_mem dst_image, size_t src_offset, const size_t* dst_origin, const size_t* region, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits event_wait_list = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        size_t dst_origin[3];
        size_t region[3];
        cl_event event;
        uint32_t countEvent_wait_list = 0;
        cl_event event_wait_list[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countEvent_wait_list = dynamicTraits.event_wait_list.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClEnqueueCopyBufferToImageRpcM() = default;

    ClEnqueueCopyBufferToImageRpcM(const Captures::DynamicTraits &dynamicTraits, cl_command_queue command_queue, cl_mem src_buffer, cl_mem dst_image, size_t src_offset, const size_t* dst_origin, const size_t* region, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.command_queue = command_queue;
        args.src_buffer = src_buffer;
        args.dst_image = dst_image;
        args.src_offset = src_offset;
        args.dst_origin = dst_origin;
        args.region = region;
        args.num_events_in_wait_list = num_events_in_wait_list;
        args.event_wait_list = event_wait_list;
        args.event = event;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClEnqueueCopyBufferToImageRpcM &message, cl_command_queue command_queue, cl_mem src_buffer, cl_mem dst_image, size_t src_offset, const size_t* dst_origin, const size_t* region, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.command_queue = command_queue;
        message.args.src_buffer = src_buffer;
        message.args.dst_image = dst_image;
        message.args.src_offset = src_offset;
        message.args.dst_origin = dst_origin;
        message.args.region = region;
        message.args.num_events_in_wait_list = num_events_in_wait_list;
        message.args.event_wait_list = event_wait_list;
        message.args.event = event;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.dst_origin){
            memcpy(asMemcpyDstT(captures.dst_origin), args.dst_origin, 3 * sizeof(size_t));
        }
        if(args.region){
            memcpy(asMemcpyDstT(captures.region), args.region, 3 * sizeof(size_t));
        }
        if(args.event_wait_list){
            memcpy(asMemcpyDstT(captures.event_wait_list), args.event_wait_list, dynMemTraits.event_wait_list.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event){
            *args.event = captures.event;
        }
    }
};
static_assert(std::is_standard_layout_v<ClEnqueueCopyBufferToImageRpcM>);
struct ClEnqueueMapBufferRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 92;
    static constexpr float latency = 0.0;

    using ReturnValueT = void*;

    struct Args {
        cl_command_queue command_queue = {};
        cl_mem buffer = {};
        cl_bool blocking_map = {};
        cl_map_flags map_flags = {};
        size_t offset = {};
        size_t cb = {};
        cl_uint num_events_in_wait_list = {};
        const cl_event* event_wait_list = {};
        cl_event* event = {};
        cl_int* errcode_ret = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->command_queue == rhs.command_queue;
            equal &= this->buffer == rhs.buffer;
            equal &= this->blocking_map == rhs.blocking_map;
            equal &= this->map_flags == rhs.map_flags;
            equal &= this->offset == rhs.offset;
            equal &= this->cb == rhs.cb;
            equal &= this->num_events_in_wait_list == rhs.num_events_in_wait_list;
            equal &= this->event_wait_list == rhs.event_wait_list;
            equal &= this->event == rhs.event;
            equal &= this->errcode_ret == rhs.errcode_ret;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_map, cl_map_flags map_flags, size_t offset, size_t cb, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event, cl_int* errcode_ret);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits event_wait_list = {};          
        };

        void* ret = {};
        cl_event event;
        cl_int errcode_ret;
        uint32_t countEvent_wait_list = 0;
        cl_event event_wait_list[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countEvent_wait_list = dynamicTraits.event_wait_list.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    void* returnValue(){
        return captures.ret;
    }

    ClEnqueueMapBufferRpcM() = default;

    ClEnqueueMapBufferRpcM(const Captures::DynamicTraits &dynamicTraits, cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_map, cl_map_flags map_flags, size_t offset, size_t cb, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event, cl_int* errcode_ret) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.command_queue = command_queue;
        args.buffer = buffer;
        args.blocking_map = blocking_map;
        args.map_flags = map_flags;
        args.offset = offset;
        args.cb = cb;
        args.num_events_in_wait_list = num_events_in_wait_list;
        args.event_wait_list = event_wait_list;
        args.event = event;
        args.errcode_ret = errcode_ret;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClEnqueueMapBufferRpcM &message, cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_map, cl_map_flags map_flags, size_t offset, size_t cb, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event, cl_int* errcode_ret) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.command_queue = command_queue;
        message.args.buffer = buffer;
        message.args.blocking_map = blocking_map;
        message.args.map_flags = map_flags;
        message.args.offset = offset;
        message.args.cb = cb;
        message.args.num_events_in_wait_list = num_events_in_wait_list;
        message.args.event_wait_list = event_wait_list;
        message.args.event = event;
        message.args.errcode_ret = errcode_ret;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event_wait_list){
            memcpy(asMemcpyDstT(captures.event_wait_list), args.event_wait_list, dynMemTraits.event_wait_list.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event){
            *args.event = captures.event;
        }
        if(args.errcode_ret){
            *args.errcode_ret = captures.errcode_ret;
        }
    }
};
static_assert(std::is_standard_layout_v<ClEnqueueMapBufferRpcM>);
struct ClEnqueueUnmapMemObjectRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 93;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_command_queue command_queue = {};
        cl_mem memobj = {};
        void* mapped_ptr = {};
        cl_uint num_events_in_wait_list = {};
        const cl_event* event_wait_list = {};
        cl_event* event = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->command_queue == rhs.command_queue;
            equal &= this->memobj == rhs.memobj;
            equal &= this->mapped_ptr == rhs.mapped_ptr;
            equal &= this->num_events_in_wait_list == rhs.num_events_in_wait_list;
            equal &= this->event_wait_list == rhs.event_wait_list;
            equal &= this->event == rhs.event;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_command_queue command_queue, cl_mem memobj, void* mapped_ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits event_wait_list = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        cl_event event;
        uint32_t countEvent_wait_list = 0;
        cl_event event_wait_list[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countEvent_wait_list = dynamicTraits.event_wait_list.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClEnqueueUnmapMemObjectRpcM() = default;

    ClEnqueueUnmapMemObjectRpcM(const Captures::DynamicTraits &dynamicTraits, cl_command_queue command_queue, cl_mem memobj, void* mapped_ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.command_queue = command_queue;
        args.memobj = memobj;
        args.mapped_ptr = mapped_ptr;
        args.num_events_in_wait_list = num_events_in_wait_list;
        args.event_wait_list = event_wait_list;
        args.event = event;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClEnqueueUnmapMemObjectRpcM &message, cl_command_queue command_queue, cl_mem memobj, void* mapped_ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.command_queue = command_queue;
        message.args.memobj = memobj;
        message.args.mapped_ptr = mapped_ptr;
        message.args.num_events_in_wait_list = num_events_in_wait_list;
        message.args.event_wait_list = event_wait_list;
        message.args.event = event;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event_wait_list){
            memcpy(asMemcpyDstT(captures.event_wait_list), args.event_wait_list, dynMemTraits.event_wait_list.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event){
            *args.event = captures.event;
        }
    }
};
static_assert(std::is_standard_layout_v<ClEnqueueUnmapMemObjectRpcM>);
struct ClEnqueueFillBufferRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 94;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_command_queue command_queue = {};
        cl_mem memobj = {};
        const void* pattern = {};
        size_t patternSize = {};
        size_t offset = {};
        size_t size = {};
        cl_uint num_events_in_wait_list = {};
        const cl_event* event_wait_list = {};
        cl_event* event = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->command_queue == rhs.command_queue;
            equal &= this->memobj == rhs.memobj;
            equal &= this->pattern == rhs.pattern;
            equal &= this->patternSize == rhs.patternSize;
            equal &= this->offset == rhs.offset;
            equal &= this->size == rhs.size;
            equal &= this->num_events_in_wait_list == rhs.num_events_in_wait_list;
            equal &= this->event_wait_list == rhs.event_wait_list;
            equal &= this->event == rhs.event;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_command_queue command_queue, cl_mem memobj, const void* pattern, size_t patternSize, size_t offset, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits pattern = {};          
            DynamicArgTraits event_wait_list = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        cl_event event;
        uint32_t offsetEvent_wait_list = 0;
        uint32_t countPattern = 0;
        uint32_t countEvent_wait_list = 0;
        const void* getPattern() {
            auto offset = 0;
            return reinterpret_cast<const void*>(dynMem + offset);
        }

        const cl_event* getEvent_wait_list() {
            auto offset = offsetEvent_wait_list;
            return reinterpret_cast<const cl_event*>(dynMem + offset);
        }


        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        offsetEvent_wait_list = dynamicTraits.event_wait_list.offset;
        countPattern = dynamicTraits.pattern.count;
        countEvent_wait_list = dynamicTraits.event_wait_list.count;
        }
        
        alignas(8) char dynMem[];
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClEnqueueFillBufferRpcM() = default;

    ClEnqueueFillBufferRpcM(const Captures::DynamicTraits &dynamicTraits, cl_command_queue command_queue, cl_mem memobj, const void* pattern, size_t patternSize, size_t offset, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.command_queue = command_queue;
        args.memobj = memobj;
        args.pattern = pattern;
        args.patternSize = patternSize;
        args.offset = offset;
        args.size = size;
        args.num_events_in_wait_list = num_events_in_wait_list;
        args.event_wait_list = event_wait_list;
        args.event = event;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClEnqueueFillBufferRpcM &message, cl_command_queue command_queue, cl_mem memobj, const void* pattern, size_t patternSize, size_t offset, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.command_queue = command_queue;
        message.args.memobj = memobj;
        message.args.pattern = pattern;
        message.args.patternSize = patternSize;
        message.args.offset = offset;
        message.args.size = size;
        message.args.num_events_in_wait_list = num_events_in_wait_list;
        message.args.event_wait_list = event_wait_list;
        message.args.event = event;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.pattern){
            memcpy(asMemcpyDstT(captures.getPattern()), args.pattern, dynMemTraits.pattern.size);
        }
        if(args.event_wait_list){
            memcpy(asMemcpyDstT(captures.getEvent_wait_list()), args.event_wait_list, dynMemTraits.event_wait_list.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event){
            *args.event = captures.event;
        }
    }
};
static_assert(std::is_standard_layout_v<ClEnqueueFillBufferRpcM>);
struct ClEnqueueFillImageRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 95;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_command_queue command_queue = {};
        cl_mem image = {};
        const void* fill_color = {};
        const size_t* origin = {};
        const size_t* region = {};
        cl_uint num_events_in_wait_list = {};
        const cl_event* event_wait_list = {};
        cl_event* event = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->command_queue == rhs.command_queue;
            equal &= this->image == rhs.image;
            equal &= this->fill_color == rhs.fill_color;
            equal &= this->origin == rhs.origin;
            equal &= this->region == rhs.region;
            equal &= this->num_events_in_wait_list == rhs.num_events_in_wait_list;
            equal &= this->event_wait_list == rhs.event_wait_list;
            equal &= this->event == rhs.event;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_command_queue command_queue, cl_mem image, const void* fill_color, const size_t* origin, const size_t* region, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits event_wait_list = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        char fill_color[16];
        size_t origin[3];
        size_t region[3];
        cl_event event;
        uint32_t countEvent_wait_list = 0;
        cl_event event_wait_list[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countEvent_wait_list = dynamicTraits.event_wait_list.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClEnqueueFillImageRpcM() = default;

    ClEnqueueFillImageRpcM(const Captures::DynamicTraits &dynamicTraits, cl_command_queue command_queue, cl_mem image, const void* fill_color, const size_t* origin, const size_t* region, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.command_queue = command_queue;
        args.image = image;
        args.fill_color = fill_color;
        args.origin = origin;
        args.region = region;
        args.num_events_in_wait_list = num_events_in_wait_list;
        args.event_wait_list = event_wait_list;
        args.event = event;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClEnqueueFillImageRpcM &message, cl_command_queue command_queue, cl_mem image, const void* fill_color, const size_t* origin, const size_t* region, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.command_queue = command_queue;
        message.args.image = image;
        message.args.fill_color = fill_color;
        message.args.origin = origin;
        message.args.region = region;
        message.args.num_events_in_wait_list = num_events_in_wait_list;
        message.args.event_wait_list = event_wait_list;
        message.args.event = event;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.fill_color){
            memcpy(asMemcpyDstT(captures.fill_color), args.fill_color, 16);
        }
        if(args.origin){
            memcpy(asMemcpyDstT(captures.origin), args.origin, 3 * sizeof(size_t));
        }
        if(args.region){
            memcpy(asMemcpyDstT(captures.region), args.region, 3 * sizeof(size_t));
        }
        if(args.event_wait_list){
            memcpy(asMemcpyDstT(captures.event_wait_list), args.event_wait_list, dynMemTraits.event_wait_list.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event){
            *args.event = captures.event;
        }
    }
};
static_assert(std::is_standard_layout_v<ClEnqueueFillImageRpcM>);
struct ClWaitForEventsRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 96;
    static constexpr float latency = 2.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_uint num_events = {};
        const cl_event* event_list = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->num_events == rhs.num_events;
            equal &= this->event_list == rhs.event_list;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_uint num_events, const cl_event* event_list);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits event_list = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        uint32_t countEvent_list = 0;
        cl_event event_list[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countEvent_list = dynamicTraits.event_list.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClWaitForEventsRpcM() = default;

    ClWaitForEventsRpcM(const Captures::DynamicTraits &dynamicTraits, cl_uint num_events, const cl_event* event_list) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.num_events = num_events;
        args.event_list = event_list;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClWaitForEventsRpcM &message, cl_uint num_events, const cl_event* event_list) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.num_events = num_events;
        message.args.event_list = event_list;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event_list){
            memcpy(asMemcpyDstT(captures.event_list), args.event_list, dynMemTraits.event_list.size);
        }
    }
};
static_assert(std::is_standard_layout_v<ClWaitForEventsRpcM>);
struct ClGetEventInfoRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 97;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_event event = {};
        cl_event_info param_name = {};
        size_t param_value_size = {};
        void* param_value = {};
        size_t* param_value_size_ret = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->event == rhs.event;
            equal &= this->param_name == rhs.param_name;
            equal &= this->param_value_size == rhs.param_value_size;
            equal &= this->param_value == rhs.param_value;
            equal &= this->param_value_size_ret == rhs.param_value_size_ret;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_event event, cl_event_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits param_value = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        size_t param_value_size_ret;
        uint32_t countParam_value = 0;
        char param_value[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countParam_value = dynamicTraits.param_value.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClGetEventInfoRpcM() = default;

    ClGetEventInfoRpcM(const Captures::DynamicTraits &dynamicTraits, cl_event event, cl_event_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.event = event;
        args.param_name = param_name;
        args.param_value_size = param_value_size;
        args.param_value = param_value;
        args.param_value_size_ret = param_value_size_ret;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClGetEventInfoRpcM &message, cl_event event, cl_event_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.event = event;
        message.args.param_name = param_name;
        message.args.param_value_size = param_value_size;
        message.args.param_value = param_value;
        message.args.param_value_size_ret = param_value_size_ret;
    }
    

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.param_value){
            memcpy(args.param_value, captures.param_value, dynMemTraits.param_value.size);
        }
        if(args.param_value_size_ret){
            *args.param_value_size_ret = captures.param_value_size_ret;
        }
    }
};
static_assert(std::is_standard_layout_v<ClGetEventInfoRpcM>);
struct ClGetEventProfilingInfoRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 98;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_event event = {};
        cl_profiling_info param_name = {};
        size_t param_value_size = {};
        void* param_value = {};
        size_t* param_value_size_ret = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->event == rhs.event;
            equal &= this->param_name == rhs.param_name;
            equal &= this->param_value_size == rhs.param_value_size;
            equal &= this->param_value == rhs.param_value;
            equal &= this->param_value_size_ret == rhs.param_value_size_ret;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_event event, cl_profiling_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits param_value = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        size_t param_value_size_ret;
        uint32_t countParam_value = 0;
        char param_value[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countParam_value = dynamicTraits.param_value.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClGetEventProfilingInfoRpcM() = default;

    ClGetEventProfilingInfoRpcM(const Captures::DynamicTraits &dynamicTraits, cl_event event, cl_profiling_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.event = event;
        args.param_name = param_name;
        args.param_value_size = param_value_size;
        args.param_value = param_value;
        args.param_value_size_ret = param_value_size_ret;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClGetEventProfilingInfoRpcM &message, cl_event event, cl_profiling_info param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.event = event;
        message.args.param_name = param_name;
        message.args.param_value_size = param_value_size;
        message.args.param_value = param_value;
        message.args.param_value_size_ret = param_value_size_ret;
    }
    

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.param_value){
            memcpy(args.param_value, captures.param_value, dynMemTraits.param_value.size);
        }
        if(args.param_value_size_ret){
            *args.param_value_size_ret = captures.param_value_size_ret;
        }
    }
};
static_assert(std::is_standard_layout_v<ClGetEventProfilingInfoRpcM>);
struct ClCreateUserEventRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 99;
    static constexpr float latency = 1.0;

    using ReturnValueT = cl_event;

    struct Args {
        cl_context context = {};
        cl_int* errcode_ret = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->context == rhs.context;
            equal &= this->errcode_ret == rhs.errcode_ret;
            return equal;
        }
    }args;

    struct Captures {

        cl_event ret = {};
        cl_int errcode_ret;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_event returnValue(){
        return captures.ret;
    }

    ClCreateUserEventRpcM() = default;

    ClCreateUserEventRpcM(cl_context context, cl_int* errcode_ret) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.context = context;
        args.errcode_ret = errcode_ret;
    }
    
    static void fillWithoutCapture(ClCreateUserEventRpcM &message, cl_context context, cl_int* errcode_ret) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.context = context;
        message.args.errcode_ret = errcode_ret;
    }
    

    void copyToCaller(){
        if(args.errcode_ret){
            *args.errcode_ret = captures.errcode_ret;
        }
    }
};
static_assert(std::is_standard_layout_v<ClCreateUserEventRpcM>);
struct ClSetUserEventStatusRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 100;
    static constexpr float latency = 1.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_event event = {};
        cl_int execution_status = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->event == rhs.event;
            equal &= this->execution_status == rhs.execution_status;
            return equal;
        }
    }args;

    struct Captures {

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClSetUserEventStatusRpcM() = default;

    ClSetUserEventStatusRpcM(cl_event event, cl_int execution_status) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.event = event;
        args.execution_status = execution_status;
    }
    
    static void fillWithoutCapture(ClSetUserEventStatusRpcM &message, cl_event event, cl_int execution_status) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.event = event;
        message.args.execution_status = execution_status;
    }
    
};
static_assert(std::is_standard_layout_v<ClSetUserEventStatusRpcM>);
struct ClSetEventCallbackRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 101;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_event event = {};
        cl_int command_exec_callback_type = {};
        void (CL_CALLBACK* pfn_notify)(cl_event event, cl_int event_command_status, void *user_data) = {};
        void* user_data = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->event == rhs.event;
            equal &= this->command_exec_callback_type == rhs.command_exec_callback_type;
            equal &= this->pfn_notify == rhs.pfn_notify;
            equal &= this->user_data == rhs.user_data;
            return equal;
        }
    }args;

    struct Captures {

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClSetEventCallbackRpcM() = default;

    ClSetEventCallbackRpcM(cl_event event, cl_int command_exec_callback_type, void (CL_CALLBACK* pfn_notify)(cl_event event, cl_int event_command_status, void *user_data), void* user_data) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.event = event;
        args.command_exec_callback_type = command_exec_callback_type;
        args.pfn_notify = pfn_notify;
        args.user_data = user_data;
    }
    
    static void fillWithoutCapture(ClSetEventCallbackRpcM &message, cl_event event, cl_int command_exec_callback_type, void (CL_CALLBACK* pfn_notify)(cl_event event, cl_int event_command_status, void *user_data), void* user_data) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.event = event;
        message.args.command_exec_callback_type = command_exec_callback_type;
        message.args.pfn_notify = pfn_notify;
        message.args.user_data = user_data;
    }
    
};
static_assert(std::is_standard_layout_v<ClSetEventCallbackRpcM>);
struct ClGetDeviceAndHostTimerRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 102;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_device_id device = {};
        cl_ulong* device_timestamp = {};
        cl_ulong* host_timestamp = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->device == rhs.device;
            equal &= this->device_timestamp == rhs.device_timestamp;
            equal &= this->host_timestamp == rhs.host_timestamp;
            return equal;
        }
    }args;

    struct Captures {

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        cl_ulong device_timestamp;
        cl_ulong host_timestamp;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClGetDeviceAndHostTimerRpcM() = default;

    ClGetDeviceAndHostTimerRpcM(cl_device_id device, cl_ulong* device_timestamp, cl_ulong* host_timestamp) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.device = device;
        args.device_timestamp = device_timestamp;
        args.host_timestamp = host_timestamp;
    }
    
    static void fillWithoutCapture(ClGetDeviceAndHostTimerRpcM &message, cl_device_id device, cl_ulong* device_timestamp, cl_ulong* host_timestamp) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.device = device;
        message.args.device_timestamp = device_timestamp;
        message.args.host_timestamp = host_timestamp;
    }
    

    void copyToCaller(){
        if(args.device_timestamp){
            *args.device_timestamp = captures.device_timestamp;
        }
        if(args.host_timestamp){
            *args.host_timestamp = captures.host_timestamp;
        }
    }
};
static_assert(std::is_standard_layout_v<ClGetDeviceAndHostTimerRpcM>);
struct ClGetHostTimerRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 103;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_device_id device = {};
        cl_ulong* host_timestamp = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->device == rhs.device;
            equal &= this->host_timestamp == rhs.host_timestamp;
            return equal;
        }
    }args;

    struct Captures {

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        cl_ulong host_timestamp;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClGetHostTimerRpcM() = default;

    ClGetHostTimerRpcM(cl_device_id device, cl_ulong* host_timestamp) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.device = device;
        args.host_timestamp = host_timestamp;
    }
    
    static void fillWithoutCapture(ClGetHostTimerRpcM &message, cl_device_id device, cl_ulong* host_timestamp) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.device = device;
        message.args.host_timestamp = host_timestamp;
    }
    

    void copyToCaller(){
        if(args.host_timestamp){
            *args.host_timestamp = captures.host_timestamp;
        }
    }
};
static_assert(std::is_standard_layout_v<ClGetHostTimerRpcM>);
struct ClSVMAllocRpcMImplicitArgs {
    int shmem_resource = {};
    size_t offset_within_resource = {};
    size_t aligned_size = {};
};

struct ClSVMAllocRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 104;
    static constexpr float latency = 1.0;

    using ReturnValueT = void*;

    struct Args {
        cl_context context = {};
        cl_svm_mem_flags flags = {};
        size_t size = {};
        cl_uint alignment = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->context == rhs.context;
            equal &= this->flags == rhs.flags;
            equal &= this->size == rhs.size;
            equal &= this->alignment == rhs.alignment;
            return equal;
        }
    }args;

    ClSVMAllocRpcMImplicitArgs implicitArgs{};
    struct Captures {

        void* ret = {};

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    void* returnValue(){
        return captures.ret;
    }

    ClSVMAllocRpcM() = default;

    ClSVMAllocRpcM(cl_context context, cl_svm_mem_flags flags, size_t size, cl_uint alignment) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.context = context;
        args.flags = flags;
        args.size = size;
        args.alignment = alignment;
    }
    
    static void fillWithoutCapture(ClSVMAllocRpcM &message, cl_context context, cl_svm_mem_flags flags, size_t size, cl_uint alignment) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.context = context;
        message.args.flags = flags;
        message.args.size = size;
        message.args.alignment = alignment;
    }
    

    void copyToCaller(Cal::Rpc::Ocl::ClSVMAllocRpcMImplicitArgs &implicitArgs){
         implicitArgs.shmem_resource = this->implicitArgs.shmem_resource;
         implicitArgs.offset_within_resource = this->implicitArgs.offset_within_resource;
         implicitArgs.aligned_size = this->implicitArgs.aligned_size;
    }
};
static_assert(std::is_standard_layout_v<ClSVMAllocRpcM>);
struct ClSVMFreeRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 105;
    static constexpr float latency = 0.0;

    using ReturnValueT = void;

    struct Args {
        cl_context context = {};
        void* ptr = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->context == rhs.context;
            equal &= this->ptr == rhs.ptr;
            return equal;
        }
    }args;

    struct Captures {


        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    


    ClSVMFreeRpcM() = default;

    ClSVMFreeRpcM(cl_context context, void* ptr) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.context = context;
        args.ptr = ptr;
    }
    
    static void fillWithoutCapture(ClSVMFreeRpcM &message, cl_context context, void* ptr) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.context = context;
        message.args.ptr = ptr;
    }
    
};
static_assert(std::is_standard_layout_v<ClSVMFreeRpcM>);
struct ClEnqueueSVMMapRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 106;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_command_queue command_queue = {};
        cl_bool blocking_map = {};
        cl_map_flags map_flags = {};
        void* svm_ptr = {};
        size_t size = {};
        cl_uint num_events_in_wait_list = {};
        const cl_event* event_wait_list = {};
        cl_event* event = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->command_queue == rhs.command_queue;
            equal &= this->blocking_map == rhs.blocking_map;
            equal &= this->map_flags == rhs.map_flags;
            equal &= this->svm_ptr == rhs.svm_ptr;
            equal &= this->size == rhs.size;
            equal &= this->num_events_in_wait_list == rhs.num_events_in_wait_list;
            equal &= this->event_wait_list == rhs.event_wait_list;
            equal &= this->event == rhs.event;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_command_queue command_queue, cl_bool blocking_map, cl_map_flags map_flags, void* svm_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits event_wait_list = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        cl_event event;
        uint32_t countEvent_wait_list = 0;
        cl_event event_wait_list[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countEvent_wait_list = dynamicTraits.event_wait_list.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClEnqueueSVMMapRpcM() = default;

    ClEnqueueSVMMapRpcM(const Captures::DynamicTraits &dynamicTraits, cl_command_queue command_queue, cl_bool blocking_map, cl_map_flags map_flags, void* svm_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.command_queue = command_queue;
        args.blocking_map = blocking_map;
        args.map_flags = map_flags;
        args.svm_ptr = svm_ptr;
        args.size = size;
        args.num_events_in_wait_list = num_events_in_wait_list;
        args.event_wait_list = event_wait_list;
        args.event = event;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClEnqueueSVMMapRpcM &message, cl_command_queue command_queue, cl_bool blocking_map, cl_map_flags map_flags, void* svm_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.command_queue = command_queue;
        message.args.blocking_map = blocking_map;
        message.args.map_flags = map_flags;
        message.args.svm_ptr = svm_ptr;
        message.args.size = size;
        message.args.num_events_in_wait_list = num_events_in_wait_list;
        message.args.event_wait_list = event_wait_list;
        message.args.event = event;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event_wait_list){
            memcpy(asMemcpyDstT(captures.event_wait_list), args.event_wait_list, dynMemTraits.event_wait_list.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event){
            *args.event = captures.event;
        }
    }
};
static_assert(std::is_standard_layout_v<ClEnqueueSVMMapRpcM>);
struct ClEnqueueSVMUnmapRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 107;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_command_queue command_queue = {};
        void* svm_ptr = {};
        cl_uint num_events_in_wait_list = {};
        const cl_event* event_wait_list = {};
        cl_event* event = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->command_queue == rhs.command_queue;
            equal &= this->svm_ptr == rhs.svm_ptr;
            equal &= this->num_events_in_wait_list == rhs.num_events_in_wait_list;
            equal &= this->event_wait_list == rhs.event_wait_list;
            equal &= this->event == rhs.event;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_command_queue command_queue, void* svm_ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits event_wait_list = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        cl_event event;
        uint32_t countEvent_wait_list = 0;
        cl_event event_wait_list[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countEvent_wait_list = dynamicTraits.event_wait_list.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClEnqueueSVMUnmapRpcM() = default;

    ClEnqueueSVMUnmapRpcM(const Captures::DynamicTraits &dynamicTraits, cl_command_queue command_queue, void* svm_ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.command_queue = command_queue;
        args.svm_ptr = svm_ptr;
        args.num_events_in_wait_list = num_events_in_wait_list;
        args.event_wait_list = event_wait_list;
        args.event = event;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClEnqueueSVMUnmapRpcM &message, cl_command_queue command_queue, void* svm_ptr, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.command_queue = command_queue;
        message.args.svm_ptr = svm_ptr;
        message.args.num_events_in_wait_list = num_events_in_wait_list;
        message.args.event_wait_list = event_wait_list;
        message.args.event = event;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event_wait_list){
            memcpy(asMemcpyDstT(captures.event_wait_list), args.event_wait_list, dynMemTraits.event_wait_list.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event){
            *args.event = captures.event;
        }
    }
};
static_assert(std::is_standard_layout_v<ClEnqueueSVMUnmapRpcM>);
struct ClSetKernelArgSVMPointerRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 108;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_kernel kernel = {};
        cl_uint argIndex = {};
        const void* argValue = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->kernel == rhs.kernel;
            equal &= this->argIndex == rhs.argIndex;
            equal &= this->argValue == rhs.argValue;
            return equal;
        }
    }args;

    struct Captures {

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClSetKernelArgSVMPointerRpcM() = default;

    ClSetKernelArgSVMPointerRpcM(cl_kernel kernel, cl_uint argIndex, const void* argValue) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.kernel = kernel;
        args.argIndex = argIndex;
        args.argValue = argValue;
    }
    
    static void fillWithoutCapture(ClSetKernelArgSVMPointerRpcM &message, cl_kernel kernel, cl_uint argIndex, const void* argValue) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.kernel = kernel;
        message.args.argIndex = argIndex;
        message.args.argValue = argValue;
    }
    
};
static_assert(std::is_standard_layout_v<ClSetKernelArgSVMPointerRpcM>);
struct ClSetKernelExecInfoRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 109;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_kernel kernel = {};
        cl_kernel_exec_info param_name = {};
        size_t param_value_size = {};
        const void* param_value = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->kernel == rhs.kernel;
            equal &= this->param_name == rhs.param_name;
            equal &= this->param_value_size == rhs.param_value_size;
            equal &= this->param_value == rhs.param_value;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_kernel kernel, cl_kernel_exec_info param_name, size_t param_value_size, const void* param_value);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits param_value = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        uint32_t countParam_value = 0;
        char param_value[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countParam_value = dynamicTraits.param_value.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClSetKernelExecInfoRpcM() = default;

    ClSetKernelExecInfoRpcM(const Captures::DynamicTraits &dynamicTraits, cl_kernel kernel, cl_kernel_exec_info param_name, size_t param_value_size, const void* param_value) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.kernel = kernel;
        args.param_name = param_name;
        args.param_value_size = param_value_size;
        args.param_value = param_value;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClSetKernelExecInfoRpcM &message, cl_kernel kernel, cl_kernel_exec_info param_name, size_t param_value_size, const void* param_value) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.kernel = kernel;
        message.args.param_name = param_name;
        message.args.param_value_size = param_value_size;
        message.args.param_value = param_value;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.param_value){
            memcpy(asMemcpyDstT(captures.param_value), args.param_value, dynMemTraits.param_value.size);
        }
    }
};
static_assert(std::is_standard_layout_v<ClSetKernelExecInfoRpcM>);
struct ClEnqueueSVMMemFillRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 110;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_command_queue command_queue = {};
        void* svm_ptr = {};
        const void* pattern = {};
        size_t patternSize = {};
        size_t size = {};
        cl_uint num_events_in_wait_list = {};
        const cl_event* event_wait_list = {};
        cl_event* event = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->command_queue == rhs.command_queue;
            equal &= this->svm_ptr == rhs.svm_ptr;
            equal &= this->pattern == rhs.pattern;
            equal &= this->patternSize == rhs.patternSize;
            equal &= this->size == rhs.size;
            equal &= this->num_events_in_wait_list == rhs.num_events_in_wait_list;
            equal &= this->event_wait_list == rhs.event_wait_list;
            equal &= this->event == rhs.event;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_command_queue command_queue, void* svm_ptr, const void* pattern, size_t patternSize, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits pattern = {};          
            DynamicArgTraits event_wait_list = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        cl_event event;
        uint32_t offsetEvent_wait_list = 0;
        uint32_t countPattern = 0;
        uint32_t countEvent_wait_list = 0;
        const void* getPattern() {
            auto offset = 0;
            return reinterpret_cast<const void*>(dynMem + offset);
        }

        const cl_event* getEvent_wait_list() {
            auto offset = offsetEvent_wait_list;
            return reinterpret_cast<const cl_event*>(dynMem + offset);
        }


        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        offsetEvent_wait_list = dynamicTraits.event_wait_list.offset;
        countPattern = dynamicTraits.pattern.count;
        countEvent_wait_list = dynamicTraits.event_wait_list.count;
        }
        
        alignas(8) char dynMem[];
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClEnqueueSVMMemFillRpcM() = default;

    ClEnqueueSVMMemFillRpcM(const Captures::DynamicTraits &dynamicTraits, cl_command_queue command_queue, void* svm_ptr, const void* pattern, size_t patternSize, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.command_queue = command_queue;
        args.svm_ptr = svm_ptr;
        args.pattern = pattern;
        args.patternSize = patternSize;
        args.size = size;
        args.num_events_in_wait_list = num_events_in_wait_list;
        args.event_wait_list = event_wait_list;
        args.event = event;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClEnqueueSVMMemFillRpcM &message, cl_command_queue command_queue, void* svm_ptr, const void* pattern, size_t patternSize, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.command_queue = command_queue;
        message.args.svm_ptr = svm_ptr;
        message.args.pattern = pattern;
        message.args.patternSize = patternSize;
        message.args.size = size;
        message.args.num_events_in_wait_list = num_events_in_wait_list;
        message.args.event_wait_list = event_wait_list;
        message.args.event = event;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.pattern){
            memcpy(asMemcpyDstT(captures.getPattern()), args.pattern, dynMemTraits.pattern.size);
        }
        if(args.event_wait_list){
            memcpy(asMemcpyDstT(captures.getEvent_wait_list()), args.event_wait_list, dynMemTraits.event_wait_list.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event){
            *args.event = captures.event;
        }
    }
};
static_assert(std::is_standard_layout_v<ClEnqueueSVMMemFillRpcM>);
struct ClEnqueueSVMMigrateMemRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 111;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_command_queue command_queue = {};
        cl_uint num_svm_pointers = {};
        const void** svm_pointers = {};
        const size_t* sizes = {};
        cl_mem_migration_flags flags = {};
        cl_uint num_events_in_wait_list = {};
        const cl_event* event_wait_list = {};
        cl_event* event = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->command_queue == rhs.command_queue;
            equal &= this->num_svm_pointers == rhs.num_svm_pointers;
            equal &= this->svm_pointers == rhs.svm_pointers;
            equal &= this->sizes == rhs.sizes;
            equal &= this->flags == rhs.flags;
            equal &= this->num_events_in_wait_list == rhs.num_events_in_wait_list;
            equal &= this->event_wait_list == rhs.event_wait_list;
            equal &= this->event == rhs.event;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_command_queue command_queue, cl_uint num_svm_pointers, const void** svm_pointers, const size_t* sizes, cl_mem_migration_flags flags, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits svm_pointers = {};          
            DynamicArgTraits sizes = {};          
            DynamicArgTraits event_wait_list = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        cl_event event;
        uint32_t offsetSizes = 0;
        uint32_t offsetEvent_wait_list = 0;
        uint32_t countSvm_pointers = 0;
        uint32_t countSizes = 0;
        uint32_t countEvent_wait_list = 0;
        const void** getSvm_pointers() {
            auto offset = 0;
            return reinterpret_cast<const void**>(dynMem + offset);
        }

        const size_t* getSizes() {
            auto offset = offsetSizes;
            return reinterpret_cast<const size_t*>(dynMem + offset);
        }

        const cl_event* getEvent_wait_list() {
            auto offset = offsetEvent_wait_list;
            return reinterpret_cast<const cl_event*>(dynMem + offset);
        }


        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        offsetSizes = dynamicTraits.sizes.offset;
        offsetEvent_wait_list = dynamicTraits.event_wait_list.offset;
        countSvm_pointers = dynamicTraits.svm_pointers.count;
        countSizes = dynamicTraits.sizes.count;
        countEvent_wait_list = dynamicTraits.event_wait_list.count;
        }
        
        alignas(8) char dynMem[];
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClEnqueueSVMMigrateMemRpcM() = default;

    ClEnqueueSVMMigrateMemRpcM(const Captures::DynamicTraits &dynamicTraits, cl_command_queue command_queue, cl_uint num_svm_pointers, const void** svm_pointers, const size_t* sizes, cl_mem_migration_flags flags, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.command_queue = command_queue;
        args.num_svm_pointers = num_svm_pointers;
        args.svm_pointers = svm_pointers;
        args.sizes = sizes;
        args.flags = flags;
        args.num_events_in_wait_list = num_events_in_wait_list;
        args.event_wait_list = event_wait_list;
        args.event = event;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClEnqueueSVMMigrateMemRpcM &message, cl_command_queue command_queue, cl_uint num_svm_pointers, const void** svm_pointers, const size_t* sizes, cl_mem_migration_flags flags, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.command_queue = command_queue;
        message.args.num_svm_pointers = num_svm_pointers;
        message.args.svm_pointers = svm_pointers;
        message.args.sizes = sizes;
        message.args.flags = flags;
        message.args.num_events_in_wait_list = num_events_in_wait_list;
        message.args.event_wait_list = event_wait_list;
        message.args.event = event;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.svm_pointers){
            memcpy(asMemcpyDstT(captures.getSvm_pointers()), args.svm_pointers, dynMemTraits.svm_pointers.size);
        }
        if(args.sizes){
            memcpy(asMemcpyDstT(captures.getSizes()), args.sizes, dynMemTraits.sizes.size);
        }
        if(args.event_wait_list){
            memcpy(asMemcpyDstT(captures.getEvent_wait_list()), args.event_wait_list, dynMemTraits.event_wait_list.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event){
            *args.event = captures.event;
        }
    }
};
static_assert(std::is_standard_layout_v<ClEnqueueSVMMigrateMemRpcM>);
struct ClEnqueueSVMMemcpyRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 112;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_command_queue command_queue = {};
        cl_bool blocking = {};
        void* dst_ptr = {};
        const void* src_ptr = {};
        size_t size = {};
        cl_uint num_events_in_wait_list = {};
        const cl_event* event_wait_list = {};
        cl_event* event = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->command_queue == rhs.command_queue;
            equal &= this->blocking == rhs.blocking;
            equal &= this->dst_ptr == rhs.dst_ptr;
            equal &= this->src_ptr == rhs.src_ptr;
            equal &= this->size == rhs.size;
            equal &= this->num_events_in_wait_list == rhs.num_events_in_wait_list;
            equal &= this->event_wait_list == rhs.event_wait_list;
            equal &= this->event == rhs.event;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_command_queue command_queue, cl_bool blocking, void* dst_ptr, const void* src_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits event_wait_list = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        cl_event event;
        uint32_t countEvent_wait_list = 0;
        cl_event event_wait_list[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countEvent_wait_list = dynamicTraits.event_wait_list.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClEnqueueSVMMemcpyRpcM() = default;

    ClEnqueueSVMMemcpyRpcM(const Captures::DynamicTraits &dynamicTraits, cl_command_queue command_queue, cl_bool blocking, void* dst_ptr, const void* src_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.command_queue = command_queue;
        args.blocking = blocking;
        args.dst_ptr = dst_ptr;
        args.src_ptr = src_ptr;
        args.size = size;
        args.num_events_in_wait_list = num_events_in_wait_list;
        args.event_wait_list = event_wait_list;
        args.event = event;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClEnqueueSVMMemcpyRpcM &message, cl_command_queue command_queue, cl_bool blocking, void* dst_ptr, const void* src_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.command_queue = command_queue;
        message.args.blocking = blocking;
        message.args.dst_ptr = dst_ptr;
        message.args.src_ptr = src_ptr;
        message.args.size = size;
        message.args.num_events_in_wait_list = num_events_in_wait_list;
        message.args.event_wait_list = event_wait_list;
        message.args.event = event;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event_wait_list){
            memcpy(asMemcpyDstT(captures.event_wait_list), args.event_wait_list, dynMemTraits.event_wait_list.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event){
            *args.event = captures.event;
        }
    }
};
static_assert(std::is_standard_layout_v<ClEnqueueSVMMemcpyRpcM>);
struct ClEnqueueSVMMemcpyRpcHelperMalloc2UsmRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 113;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_command_queue command_queue = {};
        cl_bool blocking = {};
        void* dst_ptr = {};
        const void* src_ptr = {};
        size_t size = {};
        cl_uint num_events_in_wait_list = {};
        const cl_event* event_wait_list = {};
        cl_event* event = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->command_queue == rhs.command_queue;
            equal &= this->blocking == rhs.blocking;
            equal &= this->dst_ptr == rhs.dst_ptr;
            equal &= this->src_ptr == rhs.src_ptr;
            equal &= this->size == rhs.size;
            equal &= this->num_events_in_wait_list == rhs.num_events_in_wait_list;
            equal &= this->event_wait_list == rhs.event_wait_list;
            equal &= this->event == rhs.event;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_command_queue command_queue, cl_bool blocking, void* dst_ptr, const void* src_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits event_wait_list = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        cl_event event;
        uint32_t countEvent_wait_list = 0;
        cl_event event_wait_list[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countEvent_wait_list = dynamicTraits.event_wait_list.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClEnqueueSVMMemcpyRpcHelperMalloc2UsmRpcM() = default;

    ClEnqueueSVMMemcpyRpcHelperMalloc2UsmRpcM(const Captures::DynamicTraits &dynamicTraits, cl_command_queue command_queue, cl_bool blocking, void* dst_ptr, const void* src_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.command_queue = command_queue;
        args.blocking = blocking;
        args.dst_ptr = dst_ptr;
        args.src_ptr = src_ptr;
        args.size = size;
        args.num_events_in_wait_list = num_events_in_wait_list;
        args.event_wait_list = event_wait_list;
        args.event = event;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClEnqueueSVMMemcpyRpcHelperMalloc2UsmRpcM &message, cl_command_queue command_queue, cl_bool blocking, void* dst_ptr, const void* src_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.command_queue = command_queue;
        message.args.blocking = blocking;
        message.args.dst_ptr = dst_ptr;
        message.args.src_ptr = src_ptr;
        message.args.size = size;
        message.args.num_events_in_wait_list = num_events_in_wait_list;
        message.args.event_wait_list = event_wait_list;
        message.args.event = event;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event_wait_list){
            memcpy(asMemcpyDstT(captures.event_wait_list), args.event_wait_list, dynMemTraits.event_wait_list.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event){
            *args.event = captures.event;
        }
    }
};
static_assert(std::is_standard_layout_v<ClEnqueueSVMMemcpyRpcHelperMalloc2UsmRpcM>);
struct ClEnqueueSVMMemcpyRpcHelperUsm2MallocRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 114;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_command_queue command_queue = {};
        cl_bool blocking = {};
        void* dst_ptr = {};
        const void* src_ptr = {};
        size_t size = {};
        cl_uint num_events_in_wait_list = {};
        const cl_event* event_wait_list = {};
        cl_event* event = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->command_queue == rhs.command_queue;
            equal &= this->blocking == rhs.blocking;
            equal &= this->dst_ptr == rhs.dst_ptr;
            equal &= this->src_ptr == rhs.src_ptr;
            equal &= this->size == rhs.size;
            equal &= this->num_events_in_wait_list == rhs.num_events_in_wait_list;
            equal &= this->event_wait_list == rhs.event_wait_list;
            equal &= this->event == rhs.event;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_command_queue command_queue, cl_bool blocking, void* dst_ptr, const void* src_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits event_wait_list = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        cl_event event;
        uint32_t countEvent_wait_list = 0;
        cl_event event_wait_list[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countEvent_wait_list = dynamicTraits.event_wait_list.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClEnqueueSVMMemcpyRpcHelperUsm2MallocRpcM() = default;

    ClEnqueueSVMMemcpyRpcHelperUsm2MallocRpcM(const Captures::DynamicTraits &dynamicTraits, cl_command_queue command_queue, cl_bool blocking, void* dst_ptr, const void* src_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.command_queue = command_queue;
        args.blocking = blocking;
        args.dst_ptr = dst_ptr;
        args.src_ptr = src_ptr;
        args.size = size;
        args.num_events_in_wait_list = num_events_in_wait_list;
        args.event_wait_list = event_wait_list;
        args.event = event;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClEnqueueSVMMemcpyRpcHelperUsm2MallocRpcM &message, cl_command_queue command_queue, cl_bool blocking, void* dst_ptr, const void* src_ptr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.command_queue = command_queue;
        message.args.blocking = blocking;
        message.args.dst_ptr = dst_ptr;
        message.args.src_ptr = src_ptr;
        message.args.size = size;
        message.args.num_events_in_wait_list = num_events_in_wait_list;
        message.args.event_wait_list = event_wait_list;
        message.args.event = event;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event_wait_list){
            memcpy(asMemcpyDstT(captures.event_wait_list), args.event_wait_list, dynMemTraits.event_wait_list.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event){
            *args.event = captures.event;
        }
    }
};
static_assert(std::is_standard_layout_v<ClEnqueueSVMMemcpyRpcHelperUsm2MallocRpcM>);
struct ClCreateSubDevicesEXTRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 115;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_device_id in_device = {};
        const cl_device_partition_property_ext* properties = {};
        cl_uint num_entries = {};
        cl_device_id* out_devices = {};
        cl_uint* num_devices = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->in_device == rhs.in_device;
            equal &= this->properties == rhs.properties;
            equal &= this->num_entries == rhs.num_entries;
            equal &= this->out_devices == rhs.out_devices;
            equal &= this->num_devices == rhs.num_devices;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_device_id in_device, const cl_device_partition_property_ext* properties, cl_uint num_entries, cl_device_id* out_devices, cl_uint* num_devices);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits out_devices = {};          
            DynamicArgTraits properties = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        cl_uint num_devices;
        uint32_t offsetProperties = 0;
        uint32_t countOut_devices = 0;
        uint32_t countProperties = 0;
        cl_device_id* getOut_devices() {
            auto offset = 0;
            return reinterpret_cast<cl_device_id*>(dynMem + offset);
        }

        const cl_device_partition_property_ext* getProperties() {
            auto offset = offsetProperties;
            return reinterpret_cast<const cl_device_partition_property_ext*>(dynMem + offset);
        }


        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        offsetProperties = dynamicTraits.properties.offset;
        countOut_devices = dynamicTraits.out_devices.count;
        countProperties = dynamicTraits.properties.count;
        }
        
        alignas(8) char dynMem[];
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClCreateSubDevicesEXTRpcM() = default;

    ClCreateSubDevicesEXTRpcM(const Captures::DynamicTraits &dynamicTraits, cl_device_id in_device, const cl_device_partition_property_ext* properties, cl_uint num_entries, cl_device_id* out_devices, cl_uint* num_devices) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.in_device = in_device;
        args.properties = properties;
        args.num_entries = num_entries;
        args.out_devices = out_devices;
        args.num_devices = num_devices;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClCreateSubDevicesEXTRpcM &message, cl_device_id in_device, const cl_device_partition_property_ext* properties, cl_uint num_entries, cl_device_id* out_devices, cl_uint* num_devices) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.in_device = in_device;
        message.args.properties = properties;
        message.args.num_entries = num_entries;
        message.args.out_devices = out_devices;
        message.args.num_devices = num_devices;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.properties){
            memcpy(asMemcpyDstT(captures.getProperties()), args.properties, dynMemTraits.properties.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.out_devices){
            memcpy(args.out_devices, captures.getOut_devices(), dynMemTraits.out_devices.size);
        }
        if(args.num_devices){
            *args.num_devices = captures.num_devices;
        }
    }
};
static_assert(std::is_standard_layout_v<ClCreateSubDevicesEXTRpcM>);
struct ClReleaseDeviceEXTRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 116;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_device_id device = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->device == rhs.device;
            return equal;
        }
    }args;

    struct Captures {

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClReleaseDeviceEXTRpcM() = default;

    ClReleaseDeviceEXTRpcM(cl_device_id device) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.device = device;
    }
    
    static void fillWithoutCapture(ClReleaseDeviceEXTRpcM &message, cl_device_id device) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.device = device;
    }
    
};
static_assert(std::is_standard_layout_v<ClReleaseDeviceEXTRpcM>);
struct ClRetainDeviceEXTRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 117;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_device_id device = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->device == rhs.device;
            return equal;
        }
    }args;

    struct Captures {

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClRetainDeviceEXTRpcM() = default;

    ClRetainDeviceEXTRpcM(cl_device_id device) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.device = device;
    }
    
    static void fillWithoutCapture(ClRetainDeviceEXTRpcM &message, cl_device_id device) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.device = device;
    }
    
};
static_assert(std::is_standard_layout_v<ClRetainDeviceEXTRpcM>);
struct ClGetKernelSubGroupInfoKHRRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 118;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_kernel kernel = {};
        cl_device_id device = {};
        cl_kernel_sub_group_info param_name = {};
        size_t input_value_size = {};
        const void* input_value = {};
        size_t param_value_size = {};
        void* param_value = {};
        size_t* param_value_size_ret = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->kernel == rhs.kernel;
            equal &= this->device == rhs.device;
            equal &= this->param_name == rhs.param_name;
            equal &= this->input_value_size == rhs.input_value_size;
            equal &= this->input_value == rhs.input_value;
            equal &= this->param_value_size == rhs.param_value_size;
            equal &= this->param_value == rhs.param_value;
            equal &= this->param_value_size_ret == rhs.param_value_size_ret;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_kernel kernel, cl_device_id device, cl_kernel_sub_group_info param_name, size_t input_value_size, const void* input_value, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits input_value = {};          
            DynamicArgTraits param_value = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        size_t param_value_size_ret;
        uint32_t offsetParam_value = 0;
        uint32_t countInput_value = 0;
        uint32_t countParam_value = 0;
        const void* getInput_value() {
            auto offset = 0;
            return reinterpret_cast<const void*>(dynMem + offset);
        }

        void* getParam_value() {
            auto offset = offsetParam_value;
            return reinterpret_cast<void*>(dynMem + offset);
        }


        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        offsetParam_value = dynamicTraits.param_value.offset;
        countInput_value = dynamicTraits.input_value.count;
        countParam_value = dynamicTraits.param_value.count;
        }
        
        alignas(8) char dynMem[];
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClGetKernelSubGroupInfoKHRRpcM() = default;

    ClGetKernelSubGroupInfoKHRRpcM(const Captures::DynamicTraits &dynamicTraits, cl_kernel kernel, cl_device_id device, cl_kernel_sub_group_info param_name, size_t input_value_size, const void* input_value, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.kernel = kernel;
        args.device = device;
        args.param_name = param_name;
        args.input_value_size = input_value_size;
        args.input_value = input_value;
        args.param_value_size = param_value_size;
        args.param_value = param_value;
        args.param_value_size_ret = param_value_size_ret;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClGetKernelSubGroupInfoKHRRpcM &message, cl_kernel kernel, cl_device_id device, cl_kernel_sub_group_info param_name, size_t input_value_size, const void* input_value, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.kernel = kernel;
        message.args.device = device;
        message.args.param_name = param_name;
        message.args.input_value_size = input_value_size;
        message.args.input_value = input_value;
        message.args.param_value_size = param_value_size;
        message.args.param_value = param_value;
        message.args.param_value_size_ret = param_value_size_ret;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.input_value){
            memcpy(asMemcpyDstT(captures.getInput_value()), args.input_value, dynMemTraits.input_value.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.param_value){
            memcpy(args.param_value, captures.getParam_value(), dynMemTraits.param_value.size);
        }
        if(args.param_value_size_ret){
            *args.param_value_size_ret = captures.param_value_size_ret;
        }
    }
};
static_assert(std::is_standard_layout_v<ClGetKernelSubGroupInfoKHRRpcM>);
struct ClEnqueueMemFillINTELRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 119;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_command_queue command_queue = {};
        void* dstPtr = {};
        const void* pattern = {};
        size_t patternSize = {};
        size_t size = {};
        cl_uint num_events_in_wait_list = {};
        const cl_event* event_wait_list = {};
        cl_event* event = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->command_queue == rhs.command_queue;
            equal &= this->dstPtr == rhs.dstPtr;
            equal &= this->pattern == rhs.pattern;
            equal &= this->patternSize == rhs.patternSize;
            equal &= this->size == rhs.size;
            equal &= this->num_events_in_wait_list == rhs.num_events_in_wait_list;
            equal &= this->event_wait_list == rhs.event_wait_list;
            equal &= this->event == rhs.event;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_command_queue command_queue, void* dstPtr, const void* pattern, size_t patternSize, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits pattern = {};          
            DynamicArgTraits event_wait_list = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        cl_event event;
        uint32_t offsetEvent_wait_list = 0;
        uint32_t countPattern = 0;
        uint32_t countEvent_wait_list = 0;
        const void* getPattern() {
            auto offset = 0;
            return reinterpret_cast<const void*>(dynMem + offset);
        }

        const cl_event* getEvent_wait_list() {
            auto offset = offsetEvent_wait_list;
            return reinterpret_cast<const cl_event*>(dynMem + offset);
        }


        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        offsetEvent_wait_list = dynamicTraits.event_wait_list.offset;
        countPattern = dynamicTraits.pattern.count;
        countEvent_wait_list = dynamicTraits.event_wait_list.count;
        }
        
        alignas(8) char dynMem[];
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClEnqueueMemFillINTELRpcM() = default;

    ClEnqueueMemFillINTELRpcM(const Captures::DynamicTraits &dynamicTraits, cl_command_queue command_queue, void* dstPtr, const void* pattern, size_t patternSize, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.command_queue = command_queue;
        args.dstPtr = dstPtr;
        args.pattern = pattern;
        args.patternSize = patternSize;
        args.size = size;
        args.num_events_in_wait_list = num_events_in_wait_list;
        args.event_wait_list = event_wait_list;
        args.event = event;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClEnqueueMemFillINTELRpcM &message, cl_command_queue command_queue, void* dstPtr, const void* pattern, size_t patternSize, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.command_queue = command_queue;
        message.args.dstPtr = dstPtr;
        message.args.pattern = pattern;
        message.args.patternSize = patternSize;
        message.args.size = size;
        message.args.num_events_in_wait_list = num_events_in_wait_list;
        message.args.event_wait_list = event_wait_list;
        message.args.event = event;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.pattern){
            memcpy(asMemcpyDstT(captures.getPattern()), args.pattern, dynMemTraits.pattern.size);
        }
        if(args.event_wait_list){
            memcpy(asMemcpyDstT(captures.getEvent_wait_list()), args.event_wait_list, dynMemTraits.event_wait_list.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event){
            *args.event = captures.event;
        }
    }
};
static_assert(std::is_standard_layout_v<ClEnqueueMemFillINTELRpcM>);
struct ClEnqueueMemcpyINTELRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 120;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_command_queue command_queue = {};
        cl_bool blocking = {};
        void* dstPtr = {};
        const void* srcPtr = {};
        size_t size = {};
        cl_uint num_events_in_wait_list = {};
        const cl_event* event_wait_list = {};
        cl_event* event = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->command_queue == rhs.command_queue;
            equal &= this->blocking == rhs.blocking;
            equal &= this->dstPtr == rhs.dstPtr;
            equal &= this->srcPtr == rhs.srcPtr;
            equal &= this->size == rhs.size;
            equal &= this->num_events_in_wait_list == rhs.num_events_in_wait_list;
            equal &= this->event_wait_list == rhs.event_wait_list;
            equal &= this->event == rhs.event;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_command_queue command_queue, cl_bool blocking, void* dstPtr, const void* srcPtr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits event_wait_list = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        cl_event event;
        uint32_t countEvent_wait_list = 0;
        cl_event event_wait_list[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countEvent_wait_list = dynamicTraits.event_wait_list.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClEnqueueMemcpyINTELRpcM() = default;

    ClEnqueueMemcpyINTELRpcM(const Captures::DynamicTraits &dynamicTraits, cl_command_queue command_queue, cl_bool blocking, void* dstPtr, const void* srcPtr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.command_queue = command_queue;
        args.blocking = blocking;
        args.dstPtr = dstPtr;
        args.srcPtr = srcPtr;
        args.size = size;
        args.num_events_in_wait_list = num_events_in_wait_list;
        args.event_wait_list = event_wait_list;
        args.event = event;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClEnqueueMemcpyINTELRpcM &message, cl_command_queue command_queue, cl_bool blocking, void* dstPtr, const void* srcPtr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.command_queue = command_queue;
        message.args.blocking = blocking;
        message.args.dstPtr = dstPtr;
        message.args.srcPtr = srcPtr;
        message.args.size = size;
        message.args.num_events_in_wait_list = num_events_in_wait_list;
        message.args.event_wait_list = event_wait_list;
        message.args.event = event;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event_wait_list){
            memcpy(asMemcpyDstT(captures.event_wait_list), args.event_wait_list, dynMemTraits.event_wait_list.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event){
            *args.event = captures.event;
        }
    }
};
static_assert(std::is_standard_layout_v<ClEnqueueMemcpyINTELRpcM>);
struct ClEnqueueMemcpyINTELRpcHelperMalloc2UsmRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 121;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_command_queue command_queue = {};
        cl_bool blocking = {};
        void* dstPtr = {};
        const void* srcPtr = {};
        size_t size = {};
        cl_uint num_events_in_wait_list = {};
        const cl_event* event_wait_list = {};
        cl_event* event = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->command_queue == rhs.command_queue;
            equal &= this->blocking == rhs.blocking;
            equal &= this->dstPtr == rhs.dstPtr;
            equal &= this->srcPtr == rhs.srcPtr;
            equal &= this->size == rhs.size;
            equal &= this->num_events_in_wait_list == rhs.num_events_in_wait_list;
            equal &= this->event_wait_list == rhs.event_wait_list;
            equal &= this->event == rhs.event;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_command_queue command_queue, cl_bool blocking, void* dstPtr, const void* srcPtr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits event_wait_list = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        cl_event event;
        uint32_t countEvent_wait_list = 0;
        cl_event event_wait_list[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countEvent_wait_list = dynamicTraits.event_wait_list.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClEnqueueMemcpyINTELRpcHelperMalloc2UsmRpcM() = default;

    ClEnqueueMemcpyINTELRpcHelperMalloc2UsmRpcM(const Captures::DynamicTraits &dynamicTraits, cl_command_queue command_queue, cl_bool blocking, void* dstPtr, const void* srcPtr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.command_queue = command_queue;
        args.blocking = blocking;
        args.dstPtr = dstPtr;
        args.srcPtr = srcPtr;
        args.size = size;
        args.num_events_in_wait_list = num_events_in_wait_list;
        args.event_wait_list = event_wait_list;
        args.event = event;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClEnqueueMemcpyINTELRpcHelperMalloc2UsmRpcM &message, cl_command_queue command_queue, cl_bool blocking, void* dstPtr, const void* srcPtr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.command_queue = command_queue;
        message.args.blocking = blocking;
        message.args.dstPtr = dstPtr;
        message.args.srcPtr = srcPtr;
        message.args.size = size;
        message.args.num_events_in_wait_list = num_events_in_wait_list;
        message.args.event_wait_list = event_wait_list;
        message.args.event = event;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event_wait_list){
            memcpy(asMemcpyDstT(captures.event_wait_list), args.event_wait_list, dynMemTraits.event_wait_list.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event){
            *args.event = captures.event;
        }
    }
};
static_assert(std::is_standard_layout_v<ClEnqueueMemcpyINTELRpcHelperMalloc2UsmRpcM>);
struct ClEnqueueMemcpyINTELRpcHelperUsm2MallocRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 122;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_command_queue command_queue = {};
        cl_bool blocking = {};
        void* dstPtr = {};
        const void* srcPtr = {};
        size_t size = {};
        cl_uint num_events_in_wait_list = {};
        const cl_event* event_wait_list = {};
        cl_event* event = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->command_queue == rhs.command_queue;
            equal &= this->blocking == rhs.blocking;
            equal &= this->dstPtr == rhs.dstPtr;
            equal &= this->srcPtr == rhs.srcPtr;
            equal &= this->size == rhs.size;
            equal &= this->num_events_in_wait_list == rhs.num_events_in_wait_list;
            equal &= this->event_wait_list == rhs.event_wait_list;
            equal &= this->event == rhs.event;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_command_queue command_queue, cl_bool blocking, void* dstPtr, const void* srcPtr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits event_wait_list = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        cl_event event;
        uint32_t countEvent_wait_list = 0;
        cl_event event_wait_list[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countEvent_wait_list = dynamicTraits.event_wait_list.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClEnqueueMemcpyINTELRpcHelperUsm2MallocRpcM() = default;

    ClEnqueueMemcpyINTELRpcHelperUsm2MallocRpcM(const Captures::DynamicTraits &dynamicTraits, cl_command_queue command_queue, cl_bool blocking, void* dstPtr, const void* srcPtr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.command_queue = command_queue;
        args.blocking = blocking;
        args.dstPtr = dstPtr;
        args.srcPtr = srcPtr;
        args.size = size;
        args.num_events_in_wait_list = num_events_in_wait_list;
        args.event_wait_list = event_wait_list;
        args.event = event;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClEnqueueMemcpyINTELRpcHelperUsm2MallocRpcM &message, cl_command_queue command_queue, cl_bool blocking, void* dstPtr, const void* srcPtr, size_t size, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.command_queue = command_queue;
        message.args.blocking = blocking;
        message.args.dstPtr = dstPtr;
        message.args.srcPtr = srcPtr;
        message.args.size = size;
        message.args.num_events_in_wait_list = num_events_in_wait_list;
        message.args.event_wait_list = event_wait_list;
        message.args.event = event;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event_wait_list){
            memcpy(asMemcpyDstT(captures.event_wait_list), args.event_wait_list, dynMemTraits.event_wait_list.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event){
            *args.event = captures.event;
        }
    }
};
static_assert(std::is_standard_layout_v<ClEnqueueMemcpyINTELRpcHelperUsm2MallocRpcM>);
struct ClSetKernelArgMemPointerINTELRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 123;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_kernel kernel = {};
        cl_uint argIndex = {};
        const void* argValue = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->kernel == rhs.kernel;
            equal &= this->argIndex == rhs.argIndex;
            equal &= this->argValue == rhs.argValue;
            return equal;
        }
    }args;

    struct Captures {

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClSetKernelArgMemPointerINTELRpcM() = default;

    ClSetKernelArgMemPointerINTELRpcM(cl_kernel kernel, cl_uint argIndex, const void* argValue) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.kernel = kernel;
        args.argIndex = argIndex;
        args.argValue = argValue;
    }
    
    static void fillWithoutCapture(ClSetKernelArgMemPointerINTELRpcM &message, cl_kernel kernel, cl_uint argIndex, const void* argValue) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.kernel = kernel;
        message.args.argIndex = argIndex;
        message.args.argValue = argValue;
    }
    
};
static_assert(std::is_standard_layout_v<ClSetKernelArgMemPointerINTELRpcM>);
struct ClGetMemAllocInfoINTELRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 124;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_context context = {};
        const void* ptr = {};
        cl_mem_info_intel param_name = {};
        size_t param_value_size = {};
        void* param_value = {};
        size_t* param_value_size_ret = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->context == rhs.context;
            equal &= this->ptr == rhs.ptr;
            equal &= this->param_name == rhs.param_name;
            equal &= this->param_value_size == rhs.param_value_size;
            equal &= this->param_value == rhs.param_value;
            equal &= this->param_value_size_ret == rhs.param_value_size_ret;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_context context, const void* ptr, cl_mem_info_intel param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits param_value = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        size_t param_value_size_ret;
        uint32_t countParam_value = 0;
        char param_value[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countParam_value = dynamicTraits.param_value.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClGetMemAllocInfoINTELRpcM() = default;

    ClGetMemAllocInfoINTELRpcM(const Captures::DynamicTraits &dynamicTraits, cl_context context, const void* ptr, cl_mem_info_intel param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.context = context;
        args.ptr = ptr;
        args.param_name = param_name;
        args.param_value_size = param_value_size;
        args.param_value = param_value;
        args.param_value_size_ret = param_value_size_ret;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClGetMemAllocInfoINTELRpcM &message, cl_context context, const void* ptr, cl_mem_info_intel param_name, size_t param_value_size, void* param_value, size_t* param_value_size_ret) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.context = context;
        message.args.ptr = ptr;
        message.args.param_name = param_name;
        message.args.param_value_size = param_value_size;
        message.args.param_value = param_value;
        message.args.param_value_size_ret = param_value_size_ret;
    }
    

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.param_value){
            memcpy(args.param_value, captures.param_value, dynMemTraits.param_value.size);
        }
        if(args.param_value_size_ret){
            *args.param_value_size_ret = captures.param_value_size_ret;
        }
    }
};
static_assert(std::is_standard_layout_v<ClGetMemAllocInfoINTELRpcM>);
struct ClDeviceMemAllocINTELRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 125;
    static constexpr float latency = 1.0;

    using ReturnValueT = void*;

    struct Args {
        cl_context context = {};
        cl_device_id device = {};
        const cl_mem_properties_intel* properties = {};
        size_t size = {};
        cl_uint alignment = {};
        cl_int* errcode_ret = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->context == rhs.context;
            equal &= this->device == rhs.device;
            equal &= this->properties == rhs.properties;
            equal &= this->size == rhs.size;
            equal &= this->alignment == rhs.alignment;
            equal &= this->errcode_ret == rhs.errcode_ret;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_context context, cl_device_id device, const cl_mem_properties_intel* properties, size_t size, cl_uint alignment, cl_int* errcode_ret);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits properties = {};          
        };

        void* ret = {};
        cl_int errcode_ret;
        uint32_t countProperties = 0;
        cl_mem_properties_intel properties[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countProperties = dynamicTraits.properties.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    void* returnValue(){
        return captures.ret;
    }

    ClDeviceMemAllocINTELRpcM() = default;

    ClDeviceMemAllocINTELRpcM(const Captures::DynamicTraits &dynamicTraits, cl_context context, cl_device_id device, const cl_mem_properties_intel* properties, size_t size, cl_uint alignment, cl_int* errcode_ret) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.context = context;
        args.device = device;
        args.properties = properties;
        args.size = size;
        args.alignment = alignment;
        args.errcode_ret = errcode_ret;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClDeviceMemAllocINTELRpcM &message, cl_context context, cl_device_id device, const cl_mem_properties_intel* properties, size_t size, cl_uint alignment, cl_int* errcode_ret) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.context = context;
        message.args.device = device;
        message.args.properties = properties;
        message.args.size = size;
        message.args.alignment = alignment;
        message.args.errcode_ret = errcode_ret;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.properties){
            memcpy(asMemcpyDstT(captures.properties), args.properties, dynMemTraits.properties.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.errcode_ret){
            *args.errcode_ret = captures.errcode_ret;
        }
    }
};
static_assert(std::is_standard_layout_v<ClDeviceMemAllocINTELRpcM>);
struct ClHostMemAllocINTELRpcMImplicitArgs {
    int shmem_resource = {};
    size_t offset_within_resource = {};
    size_t aligned_size = {};
};

struct ClHostMemAllocINTELRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 126;
    static constexpr float latency = 1.0;

    using ReturnValueT = void*;

    struct Args {
        cl_context context = {};
        const cl_mem_properties_intel* properties = {};
        size_t size = {};
        cl_uint alignment = {};
        cl_int* errcode_ret = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->context == rhs.context;
            equal &= this->properties == rhs.properties;
            equal &= this->size == rhs.size;
            equal &= this->alignment == rhs.alignment;
            equal &= this->errcode_ret == rhs.errcode_ret;
            return equal;
        }
    }args;

    ClHostMemAllocINTELRpcMImplicitArgs implicitArgs{};
    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_context context, const cl_mem_properties_intel* properties, size_t size, cl_uint alignment, cl_int* errcode_ret);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits properties = {};          
        };

        void* ret = {};
        cl_int errcode_ret;
        uint32_t countProperties = 0;
        cl_mem_properties_intel properties[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countProperties = dynamicTraits.properties.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    void* returnValue(){
        return captures.ret;
    }

    ClHostMemAllocINTELRpcM() = default;

    ClHostMemAllocINTELRpcM(const Captures::DynamicTraits &dynamicTraits, cl_context context, const cl_mem_properties_intel* properties, size_t size, cl_uint alignment, cl_int* errcode_ret) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.context = context;
        args.properties = properties;
        args.size = size;
        args.alignment = alignment;
        args.errcode_ret = errcode_ret;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClHostMemAllocINTELRpcM &message, cl_context context, const cl_mem_properties_intel* properties, size_t size, cl_uint alignment, cl_int* errcode_ret) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.context = context;
        message.args.properties = properties;
        message.args.size = size;
        message.args.alignment = alignment;
        message.args.errcode_ret = errcode_ret;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits, const Cal::Rpc::Ocl::ClHostMemAllocINTELRpcMImplicitArgs &implicitArgs){
        if(args.properties){
            memcpy(asMemcpyDstT(captures.properties), args.properties, dynMemTraits.properties.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits, Cal::Rpc::Ocl::ClHostMemAllocINTELRpcMImplicitArgs &implicitArgs){
        if(args.errcode_ret){
            *args.errcode_ret = captures.errcode_ret;
        }
         implicitArgs.shmem_resource = this->implicitArgs.shmem_resource;
         implicitArgs.offset_within_resource = this->implicitArgs.offset_within_resource;
         implicitArgs.aligned_size = this->implicitArgs.aligned_size;
    }
};
static_assert(std::is_standard_layout_v<ClHostMemAllocINTELRpcM>);
struct ClSharedMemAllocINTELRpcMImplicitArgs {
    int shmem_resource = {};
    size_t offset_within_resource = {};
    size_t aligned_size = {};
};

struct ClSharedMemAllocINTELRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 127;
    static constexpr float latency = 1.0;

    using ReturnValueT = void*;

    struct Args {
        cl_context context = {};
        cl_device_id device = {};
        const cl_mem_properties_intel* properties = {};
        size_t size = {};
        cl_uint alignment = {};
        cl_int* errcode_ret = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->context == rhs.context;
            equal &= this->device == rhs.device;
            equal &= this->properties == rhs.properties;
            equal &= this->size == rhs.size;
            equal &= this->alignment == rhs.alignment;
            equal &= this->errcode_ret == rhs.errcode_ret;
            return equal;
        }
    }args;

    ClSharedMemAllocINTELRpcMImplicitArgs implicitArgs{};
    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_context context, cl_device_id device, const cl_mem_properties_intel* properties, size_t size, cl_uint alignment, cl_int* errcode_ret);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits properties = {};          
        };

        void* ret = {};
        cl_int errcode_ret;
        uint32_t countProperties = 0;
        cl_mem_properties_intel properties[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countProperties = dynamicTraits.properties.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    void* returnValue(){
        return captures.ret;
    }

    ClSharedMemAllocINTELRpcM() = default;

    ClSharedMemAllocINTELRpcM(const Captures::DynamicTraits &dynamicTraits, cl_context context, cl_device_id device, const cl_mem_properties_intel* properties, size_t size, cl_uint alignment, cl_int* errcode_ret) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.context = context;
        args.device = device;
        args.properties = properties;
        args.size = size;
        args.alignment = alignment;
        args.errcode_ret = errcode_ret;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClSharedMemAllocINTELRpcM &message, cl_context context, cl_device_id device, const cl_mem_properties_intel* properties, size_t size, cl_uint alignment, cl_int* errcode_ret) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.context = context;
        message.args.device = device;
        message.args.properties = properties;
        message.args.size = size;
        message.args.alignment = alignment;
        message.args.errcode_ret = errcode_ret;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits, const Cal::Rpc::Ocl::ClSharedMemAllocINTELRpcMImplicitArgs &implicitArgs){
        if(args.properties){
            memcpy(asMemcpyDstT(captures.properties), args.properties, dynMemTraits.properties.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits, Cal::Rpc::Ocl::ClSharedMemAllocINTELRpcMImplicitArgs &implicitArgs){
        if(args.errcode_ret){
            *args.errcode_ret = captures.errcode_ret;
        }
         implicitArgs.shmem_resource = this->implicitArgs.shmem_resource;
         implicitArgs.offset_within_resource = this->implicitArgs.offset_within_resource;
         implicitArgs.aligned_size = this->implicitArgs.aligned_size;
    }
};
static_assert(std::is_standard_layout_v<ClSharedMemAllocINTELRpcM>);
struct ClMemFreeINTELRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 128;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_context context = {};
        void* ptr = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->context == rhs.context;
            equal &= this->ptr == rhs.ptr;
            return equal;
        }
    }args;

    struct Captures {

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClMemFreeINTELRpcM() = default;

    ClMemFreeINTELRpcM(cl_context context, void* ptr) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.context = context;
        args.ptr = ptr;
    }
    
    static void fillWithoutCapture(ClMemFreeINTELRpcM &message, cl_context context, void* ptr) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.context = context;
        message.args.ptr = ptr;
    }
    
};
static_assert(std::is_standard_layout_v<ClMemFreeINTELRpcM>);
struct ClMemBlockingFreeINTELRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 129;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_context context = {};
        void* ptr = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->context == rhs.context;
            equal &= this->ptr == rhs.ptr;
            return equal;
        }
    }args;

    struct Captures {

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;

        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClMemBlockingFreeINTELRpcM() = default;

    ClMemBlockingFreeINTELRpcM(cl_context context, void* ptr) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.context = context;
        args.ptr = ptr;
    }
    
    static void fillWithoutCapture(ClMemBlockingFreeINTELRpcM &message, cl_context context, void* ptr) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.context = context;
        message.args.ptr = ptr;
    }
    
};
static_assert(std::is_standard_layout_v<ClMemBlockingFreeINTELRpcM>);
struct ClEnqueueMigrateMemINTELRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 130;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_command_queue command_queue = {};
        const void* ptr = {};
        size_t size = {};
        cl_mem_migration_flags flags = {};
        cl_uint num_events_in_wait_list = {};
        const cl_event* event_wait_list = {};
        cl_event* event = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->command_queue == rhs.command_queue;
            equal &= this->ptr == rhs.ptr;
            equal &= this->size == rhs.size;
            equal &= this->flags == rhs.flags;
            equal &= this->num_events_in_wait_list == rhs.num_events_in_wait_list;
            equal &= this->event_wait_list == rhs.event_wait_list;
            equal &= this->event == rhs.event;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_command_queue command_queue, const void* ptr, size_t size, cl_mem_migration_flags flags, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits event_wait_list = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        cl_event event;
        uint32_t countEvent_wait_list = 0;
        cl_event event_wait_list[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countEvent_wait_list = dynamicTraits.event_wait_list.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClEnqueueMigrateMemINTELRpcM() = default;

    ClEnqueueMigrateMemINTELRpcM(const Captures::DynamicTraits &dynamicTraits, cl_command_queue command_queue, const void* ptr, size_t size, cl_mem_migration_flags flags, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.command_queue = command_queue;
        args.ptr = ptr;
        args.size = size;
        args.flags = flags;
        args.num_events_in_wait_list = num_events_in_wait_list;
        args.event_wait_list = event_wait_list;
        args.event = event;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClEnqueueMigrateMemINTELRpcM &message, cl_command_queue command_queue, const void* ptr, size_t size, cl_mem_migration_flags flags, cl_uint num_events_in_wait_list, const cl_event* event_wait_list, cl_event* event) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.command_queue = command_queue;
        message.args.ptr = ptr;
        message.args.size = size;
        message.args.flags = flags;
        message.args.num_events_in_wait_list = num_events_in_wait_list;
        message.args.event_wait_list = event_wait_list;
        message.args.event = event;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event_wait_list){
            memcpy(asMemcpyDstT(captures.event_wait_list), args.event_wait_list, dynMemTraits.event_wait_list.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.event){
            *args.event = captures.event;
        }
    }
};
static_assert(std::is_standard_layout_v<ClEnqueueMigrateMemINTELRpcM>);
struct ClGetDeviceGlobalVariablePointerINTELRpcM {
    Cal::Rpc::RpcMessageHeader header;
    static constexpr uint16_t messageSubtype = 131;
    static constexpr float latency = 0.0;

    using ReturnValueT = cl_int;

    struct Args {
        cl_device_id device = {};
        cl_program program = {};
        const char* globalVariableName = {};
        size_t* globalVariableSizeRet = {};
        void** globalVariablePointerRet = {};

        bool shallowCompareEquals(const Args &rhs) const {
            bool equal = true;
            equal &= this->device == rhs.device;
            equal &= this->program == rhs.program;
            equal &= this->globalVariableName == rhs.globalVariableName;
            equal &= this->globalVariableSizeRet == rhs.globalVariableSizeRet;
            equal &= this->globalVariablePointerRet == rhs.globalVariablePointerRet;
            return equal;
        }
    }args;

    struct Captures {

        struct DynamicTraits {
            static DynamicTraits calculate(cl_device_id device, cl_program program, const char* globalVariableName, size_t* globalVariableSizeRet, void** globalVariablePointerRet);
            uint32_t totalDynamicSize = 0;
            DynamicArgTraits globalVariableName = {};          
        };

        cl_int ret = CL_DEVICE_NOT_AVAILABLE;
        size_t globalVariableSizeRet;
        void* globalVariablePointerRet;
        uint32_t countGlobalVariableName = 0;
        char globalVariableName[];

        void adjustCaptureLayout(const DynamicTraits &dynamicTraits){
        countGlobalVariableName = dynamicTraits.globalVariableName.count;
        }
        
        Captures() = default;
        Captures(const Captures &) = delete;
        Captures& operator=(const Captures& rhs) = delete;
        size_t getCaptureTotalSize() const;
        size_t getCaptureDynMemSize() const;

    }captures;
    

    cl_int returnValue(){
        return captures.ret;
    }

    ClGetDeviceGlobalVariablePointerINTELRpcM() = default;

    ClGetDeviceGlobalVariablePointerINTELRpcM(const Captures::DynamicTraits &dynamicTraits, cl_device_id device, cl_program program, const char* globalVariableName, size_t* globalVariableSizeRet, void** globalVariablePointerRet) {
        header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        header.subtype = messageSubtype;
        args.device = device;
        args.program = program;
        args.globalVariableName = globalVariableName;
        args.globalVariableSizeRet = globalVariableSizeRet;
        args.globalVariablePointerRet = globalVariablePointerRet;
        captures.adjustCaptureLayout(dynamicTraits);
    }
    
    static void fillWithoutCapture(ClGetDeviceGlobalVariablePointerINTELRpcM &message, cl_device_id device, cl_program program, const char* globalVariableName, size_t* globalVariableSizeRet, void** globalVariablePointerRet) {
        message.header.type = Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl;
        message.header.subtype = messageSubtype;
        message.args.device = device;
        message.args.program = program;
        message.args.globalVariableName = globalVariableName;
        message.args.globalVariableSizeRet = globalVariableSizeRet;
        message.args.globalVariablePointerRet = globalVariablePointerRet;
    }
    

    void copyFromCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.globalVariableName){
            memcpy(asMemcpyDstT(captures.globalVariableName), args.globalVariableName, dynMemTraits.globalVariableName.size);
        }
    }

    void copyToCaller(const Captures::DynamicTraits &dynMemTraits){
        if(args.globalVariableSizeRet){
            *args.globalVariableSizeRet = captures.globalVariableSizeRet;
        }
        if(args.globalVariablePointerRet){
            *args.globalVariablePointerRet = captures.globalVariablePointerRet;
        }
    }
};
static_assert(std::is_standard_layout_v<ClGetDeviceGlobalVariablePointerINTELRpcM>);

inline const char *getRpcCallFname(const RpcCallId callId) {
    static const std::unordered_map<RpcMessageHeader::MessageUniqueIdT, std::string> options = {
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetPlatformIDsRpcM::messageSubtype).id, "clGetPlatformIDs"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetPlatformInfoRpcM::messageSubtype).id, "clGetPlatformInfo"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetDeviceIDsRpcM::messageSubtype).id, "clGetDeviceIDs"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetDeviceInfoRpcM::messageSubtype).id, "clGetDeviceInfo"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateContextRpcM::messageSubtype).id, "clCreateContext"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateContextFromTypeRpcM::messageSubtype).id, "clCreateContextFromType"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetContextInfoRpcM::messageSubtype).id, "clGetContextInfo"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateSubDevicesRpcM::messageSubtype).id, "clCreateSubDevices"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateCommandQueueRpcM::messageSubtype).id, "clCreateCommandQueue"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClSetDefaultDeviceCommandQueueRpcM::messageSubtype).id, "clSetDefaultDeviceCommandQueue"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateCommandQueueWithPropertiesRpcM::messageSubtype).id, "clCreateCommandQueueWithProperties"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateProgramWithSourceRpcM::messageSubtype).id, "clCreateProgramWithSource"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateProgramWithILRpcM::messageSubtype).id, "clCreateProgramWithIL"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateProgramWithBinaryRpcM::messageSubtype).id, "clCreateProgramWithBinary"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateProgramWithBuiltInKernelsRpcM::messageSubtype).id, "clCreateProgramWithBuiltInKernels"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClBuildProgramRpcM::messageSubtype).id, "clBuildProgram"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCompileProgramRpcM::messageSubtype).id, "clCompileProgram"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClLinkProgramRpcM::messageSubtype).id, "clLinkProgram"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetProgramBuildInfoRpcM::messageSubtype).id, "clGetProgramBuildInfo"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateKernelRpcM::messageSubtype).id, "clCreateKernel"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCloneKernelRpcM::messageSubtype).id, "clCloneKernel"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateKernelsInProgramRpcM::messageSubtype).id, "clCreateKernelsInProgram"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetCommandQueueInfoRpcM::messageSubtype).id, "clGetCommandQueueInfo"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetProgramInfoRpcHelperRpcM::messageSubtype).id, "clGetProgramInfoRpcHelper"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetProgramInfoGetBinariesRpcHelperRpcM::messageSubtype).id, "clGetProgramInfoGetBinariesRpcHelper"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetMemObjectInfoRpcM::messageSubtype).id, "clGetMemObjectInfo"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetImageInfoRpcM::messageSubtype).id, "clGetImageInfo"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetSamplerInfoRpcM::messageSubtype).id, "clGetSamplerInfo"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetKernelInfoRpcM::messageSubtype).id, "clGetKernelInfo"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetKernelWorkGroupInfoRpcM::messageSubtype).id, "clGetKernelWorkGroupInfo"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetKernelArgInfoRpcM::messageSubtype).id, "clGetKernelArgInfo"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetKernelSubGroupInfoRpcM::messageSubtype).id, "clGetKernelSubGroupInfo"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClReleaseCommandQueueRpcM::messageSubtype).id, "clReleaseCommandQueue"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClReleaseContextRpcM::messageSubtype).id, "clReleaseContext"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClReleaseDeviceRpcM::messageSubtype).id, "clReleaseDevice"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClReleaseKernelRpcM::messageSubtype).id, "clReleaseKernel"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClReleaseSamplerRpcM::messageSubtype).id, "clReleaseSampler"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClReleaseProgramRpcM::messageSubtype).id, "clReleaseProgram"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClReleaseMemObjectRpcM::messageSubtype).id, "clReleaseMemObject"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClReleaseEventRpcM::messageSubtype).id, "clReleaseEvent"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClRetainCommandQueueRpcM::messageSubtype).id, "clRetainCommandQueue"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClRetainContextRpcM::messageSubtype).id, "clRetainContext"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClRetainDeviceRpcM::messageSubtype).id, "clRetainDevice"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClRetainProgramRpcM::messageSubtype).id, "clRetainProgram"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClRetainMemObjectRpcM::messageSubtype).id, "clRetainMemObject"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClRetainSamplerRpcM::messageSubtype).id, "clRetainSampler"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClRetainKernelRpcM::messageSubtype).id, "clRetainKernel"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClRetainEventRpcM::messageSubtype).id, "clRetainEvent"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClFlushRpcM::messageSubtype).id, "clFlush"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClFinishRpcM::messageSubtype).id, "clFinish"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueNDRangeKernelRpcM::messageSubtype).id, "clEnqueueNDRangeKernel"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueTaskRpcM::messageSubtype).id, "clEnqueueTask"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueMarkerWithWaitListRpcM::messageSubtype).id, "clEnqueueMarkerWithWaitList"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueMarkerRpcM::messageSubtype).id, "clEnqueueMarker"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueBarrierWithWaitListRpcM::messageSubtype).id, "clEnqueueBarrierWithWaitList"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueBarrierRpcM::messageSubtype).id, "clEnqueueBarrier"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueWaitForEventsRpcM::messageSubtype).id, "clEnqueueWaitForEvents"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueMigrateMemObjectsRpcM::messageSubtype).id, "clEnqueueMigrateMemObjects"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateBufferRpcM::messageSubtype).id, "clCreateBuffer"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateBufferRpcHelperUseHostPtrZeroCopyMallocShmemRpcM::messageSubtype).id, "clCreateBufferRpcHelperUseHostPtrZeroCopyMallocShmem"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateSubBufferRpcM::messageSubtype).id, "clCreateSubBuffer"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreatePipeRpcM::messageSubtype).id, "clCreatePipe"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetPipeInfoRpcM::messageSubtype).id, "clGetPipeInfo"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateImageRpcM::messageSubtype).id, "clCreateImage"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateImage2DRpcM::messageSubtype).id, "clCreateImage2D"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateImage3DRpcM::messageSubtype).id, "clCreateImage3D"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateSamplerRpcM::messageSubtype).id, "clCreateSampler"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateSamplerWithPropertiesRpcM::messageSubtype).id, "clCreateSamplerWithProperties"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateImageWithPropertiesRpcM::messageSubtype).id, "clCreateImageWithProperties"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateBufferWithPropertiesRpcM::messageSubtype).id, "clCreateBufferWithProperties"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetSupportedImageFormatsRpcM::messageSubtype).id, "clGetSupportedImageFormats"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClSetKernelArgRpcM::messageSubtype).id, "clSetKernelArg"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClSetProgramSpecializationConstantRpcM::messageSubtype).id, "clSetProgramSpecializationConstant"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueWriteBufferRpcM::messageSubtype).id, "clEnqueueWriteBuffer"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueWriteBufferRpcHelperMallocHostRpcM::messageSubtype).id, "clEnqueueWriteBufferRpcHelperMallocHost"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueWriteBufferRpcHelperZeroCopyMallocShmemRpcM::messageSubtype).id, "clEnqueueWriteBufferRpcHelperZeroCopyMallocShmem"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueWriteBufferRectRpcM::messageSubtype).id, "clEnqueueWriteBufferRect"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueWriteBufferRectRpcHelperMallocHostRpcM::messageSubtype).id, "clEnqueueWriteBufferRectRpcHelperMallocHost"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueWriteBufferRectRpcHelperZeroCopyMallocShmemRpcM::messageSubtype).id, "clEnqueueWriteBufferRectRpcHelperZeroCopyMallocShmem"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueReadBufferRpcM::messageSubtype).id, "clEnqueueReadBuffer"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueReadBufferRectRpcM::messageSubtype).id, "clEnqueueReadBufferRect"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueReadBufferRectRpcHelperMallocHostRpcM::messageSubtype).id, "clEnqueueReadBufferRectRpcHelperMallocHost"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueReadBufferRectRpcHelperZeroCopyMallocShmemRpcM::messageSubtype).id, "clEnqueueReadBufferRectRpcHelperZeroCopyMallocShmem"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueReadBufferRpcHelperMallocHostRpcM::messageSubtype).id, "clEnqueueReadBufferRpcHelperMallocHost"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueReadBufferRpcHelperZeroCopyMallocShmemRpcM::messageSubtype).id, "clEnqueueReadBufferRpcHelperZeroCopyMallocShmem"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueCopyBufferRpcM::messageSubtype).id, "clEnqueueCopyBuffer"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueCopyBufferRectRpcM::messageSubtype).id, "clEnqueueCopyBufferRect"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueReadImageRpcM::messageSubtype).id, "clEnqueueReadImage"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueWriteImageRpcM::messageSubtype).id, "clEnqueueWriteImage"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueCopyImageRpcM::messageSubtype).id, "clEnqueueCopyImage"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueCopyImageToBufferRpcM::messageSubtype).id, "clEnqueueCopyImageToBuffer"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueCopyBufferToImageRpcM::messageSubtype).id, "clEnqueueCopyBufferToImage"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueMapBufferRpcM::messageSubtype).id, "clEnqueueMapBuffer"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueUnmapMemObjectRpcM::messageSubtype).id, "clEnqueueUnmapMemObject"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueFillBufferRpcM::messageSubtype).id, "clEnqueueFillBuffer"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueFillImageRpcM::messageSubtype).id, "clEnqueueFillImage"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClWaitForEventsRpcM::messageSubtype).id, "clWaitForEvents"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetEventInfoRpcM::messageSubtype).id, "clGetEventInfo"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetEventProfilingInfoRpcM::messageSubtype).id, "clGetEventProfilingInfo"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateUserEventRpcM::messageSubtype).id, "clCreateUserEvent"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClSetUserEventStatusRpcM::messageSubtype).id, "clSetUserEventStatus"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClSetEventCallbackRpcM::messageSubtype).id, "clSetEventCallback"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetDeviceAndHostTimerRpcM::messageSubtype).id, "clGetDeviceAndHostTimer"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetHostTimerRpcM::messageSubtype).id, "clGetHostTimer"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClSVMAllocRpcM::messageSubtype).id, "clSVMAlloc"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClSVMFreeRpcM::messageSubtype).id, "clSVMFree"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueSVMMapRpcM::messageSubtype).id, "clEnqueueSVMMap"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueSVMUnmapRpcM::messageSubtype).id, "clEnqueueSVMUnmap"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClSetKernelArgSVMPointerRpcM::messageSubtype).id, "clSetKernelArgSVMPointer"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClSetKernelExecInfoRpcM::messageSubtype).id, "clSetKernelExecInfo"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueSVMMemFillRpcM::messageSubtype).id, "clEnqueueSVMMemFill"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueSVMMigrateMemRpcM::messageSubtype).id, "clEnqueueSVMMigrateMem"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueSVMMemcpyRpcM::messageSubtype).id, "clEnqueueSVMMemcpy"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueSVMMemcpyRpcHelperMalloc2UsmRpcM::messageSubtype).id, "clEnqueueSVMMemcpyRpcHelperMalloc2Usm"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueSVMMemcpyRpcHelperUsm2MallocRpcM::messageSubtype).id, "clEnqueueSVMMemcpyRpcHelperUsm2Malloc"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateSubDevicesEXTRpcM::messageSubtype).id, "clCreateSubDevicesEXT"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClReleaseDeviceEXTRpcM::messageSubtype).id, "clReleaseDeviceEXT"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClRetainDeviceEXTRpcM::messageSubtype).id, "clRetainDeviceEXT"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetKernelSubGroupInfoKHRRpcM::messageSubtype).id, "clGetKernelSubGroupInfoKHR"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueMemFillINTELRpcM::messageSubtype).id, "clEnqueueMemFillINTEL"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueMemcpyINTELRpcM::messageSubtype).id, "clEnqueueMemcpyINTEL"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueMemcpyINTELRpcHelperMalloc2UsmRpcM::messageSubtype).id, "clEnqueueMemcpyINTELRpcHelperMalloc2Usm"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueMemcpyINTELRpcHelperUsm2MallocRpcM::messageSubtype).id, "clEnqueueMemcpyINTELRpcHelperUsm2Malloc"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClSetKernelArgMemPointerINTELRpcM::messageSubtype).id, "clSetKernelArgMemPointerINTEL"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetMemAllocInfoINTELRpcM::messageSubtype).id, "clGetMemAllocInfoINTEL"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClDeviceMemAllocINTELRpcM::messageSubtype).id, "clDeviceMemAllocINTEL"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClHostMemAllocINTELRpcM::messageSubtype).id, "clHostMemAllocINTEL"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClSharedMemAllocINTELRpcM::messageSubtype).id, "clSharedMemAllocINTEL"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClMemFreeINTELRpcM::messageSubtype).id, "clMemFreeINTEL"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClMemBlockingFreeINTELRpcM::messageSubtype).id, "clMemBlockingFreeINTEL"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueMigrateMemINTELRpcM::messageSubtype).id, "clEnqueueMigrateMemINTEL"),
        std::pair<RpcMessageHeader::MessageUniqueIdT, std::string>(RpcCallId(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetDeviceGlobalVariablePointerINTELRpcM::messageSubtype).id, "clGetDeviceGlobalVariablePointerINTEL"),
    };

    auto it = options.find(callId.id);
    if(it == options.end()) {
        return "UNKNOWN";
    }
    return it->second.c_str();
}

inline auto getRpcCallId(const std::string &funcName) {
    using RetT = RpcCallId;
    static const std::unordered_map<std::string, RetT> options = {
        std::pair<std::string, RetT>("clGetPlatformIDs", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetPlatformIDsRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clGetPlatformInfo", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetPlatformInfoRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clGetDeviceIDs", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetDeviceIDsRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clGetDeviceInfo", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetDeviceInfoRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clCreateContext", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateContextRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clCreateContextFromType", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateContextFromTypeRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clGetContextInfo", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetContextInfoRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clCreateSubDevices", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateSubDevicesRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clCreateCommandQueue", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateCommandQueueRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clSetDefaultDeviceCommandQueue", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClSetDefaultDeviceCommandQueueRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clCreateCommandQueueWithProperties", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateCommandQueueWithPropertiesRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clCreateProgramWithSource", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateProgramWithSourceRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clCreateProgramWithIL", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateProgramWithILRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clCreateProgramWithBinary", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateProgramWithBinaryRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clCreateProgramWithBuiltInKernels", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateProgramWithBuiltInKernelsRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clBuildProgram", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClBuildProgramRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clCompileProgram", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCompileProgramRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clLinkProgram", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClLinkProgramRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clGetProgramBuildInfo", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetProgramBuildInfoRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clCreateKernel", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateKernelRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clCloneKernel", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCloneKernelRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clCreateKernelsInProgram", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateKernelsInProgramRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clGetCommandQueueInfo", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetCommandQueueInfoRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clGetProgramInfoRpcHelper", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetProgramInfoRpcHelperRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clGetProgramInfoGetBinariesRpcHelper", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetProgramInfoGetBinariesRpcHelperRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clGetMemObjectInfo", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetMemObjectInfoRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clGetImageInfo", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetImageInfoRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clGetSamplerInfo", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetSamplerInfoRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clGetKernelInfo", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetKernelInfoRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clGetKernelWorkGroupInfo", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetKernelWorkGroupInfoRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clGetKernelArgInfo", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetKernelArgInfoRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clGetKernelSubGroupInfo", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetKernelSubGroupInfoRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clReleaseCommandQueue", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClReleaseCommandQueueRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clReleaseContext", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClReleaseContextRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clReleaseDevice", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClReleaseDeviceRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clReleaseKernel", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClReleaseKernelRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clReleaseSampler", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClReleaseSamplerRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clReleaseProgram", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClReleaseProgramRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clReleaseMemObject", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClReleaseMemObjectRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clReleaseEvent", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClReleaseEventRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clRetainCommandQueue", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClRetainCommandQueueRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clRetainContext", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClRetainContextRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clRetainDevice", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClRetainDeviceRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clRetainProgram", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClRetainProgramRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clRetainMemObject", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClRetainMemObjectRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clRetainSampler", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClRetainSamplerRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clRetainKernel", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClRetainKernelRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clRetainEvent", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClRetainEventRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clFlush", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClFlushRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clFinish", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClFinishRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clEnqueueNDRangeKernel", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueNDRangeKernelRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clEnqueueTask", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueTaskRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clEnqueueMarkerWithWaitList", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueMarkerWithWaitListRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clEnqueueMarker", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueMarkerRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clEnqueueBarrierWithWaitList", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueBarrierWithWaitListRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clEnqueueBarrier", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueBarrierRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clEnqueueWaitForEvents", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueWaitForEventsRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clEnqueueMigrateMemObjects", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueMigrateMemObjectsRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clCreateBuffer", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateBufferRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clCreateBufferRpcHelperUseHostPtrZeroCopyMallocShmem", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateBufferRpcHelperUseHostPtrZeroCopyMallocShmemRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clCreateSubBuffer", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateSubBufferRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clCreatePipe", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreatePipeRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clGetPipeInfo", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetPipeInfoRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clCreateImage", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateImageRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clCreateImage2D", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateImage2DRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clCreateImage3D", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateImage3DRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clCreateSampler", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateSamplerRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clCreateSamplerWithProperties", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateSamplerWithPropertiesRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clCreateImageWithProperties", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateImageWithPropertiesRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clCreateBufferWithProperties", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateBufferWithPropertiesRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clGetSupportedImageFormats", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetSupportedImageFormatsRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clSetKernelArg", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClSetKernelArgRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clSetProgramSpecializationConstant", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClSetProgramSpecializationConstantRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clEnqueueWriteBuffer", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueWriteBufferRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clEnqueueWriteBufferRpcHelperMallocHost", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueWriteBufferRpcHelperMallocHostRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clEnqueueWriteBufferRpcHelperZeroCopyMallocShmem", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueWriteBufferRpcHelperZeroCopyMallocShmemRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clEnqueueWriteBufferRect", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueWriteBufferRectRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clEnqueueWriteBufferRectRpcHelperMallocHost", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueWriteBufferRectRpcHelperMallocHostRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clEnqueueWriteBufferRectRpcHelperZeroCopyMallocShmem", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueWriteBufferRectRpcHelperZeroCopyMallocShmemRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clEnqueueReadBuffer", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueReadBufferRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clEnqueueReadBufferRect", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueReadBufferRectRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clEnqueueReadBufferRectRpcHelperMallocHost", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueReadBufferRectRpcHelperMallocHostRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clEnqueueReadBufferRectRpcHelperZeroCopyMallocShmem", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueReadBufferRectRpcHelperZeroCopyMallocShmemRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clEnqueueReadBufferRpcHelperMallocHost", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueReadBufferRpcHelperMallocHostRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clEnqueueReadBufferRpcHelperZeroCopyMallocShmem", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueReadBufferRpcHelperZeroCopyMallocShmemRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clEnqueueCopyBuffer", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueCopyBufferRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clEnqueueCopyBufferRect", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueCopyBufferRectRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clEnqueueReadImage", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueReadImageRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clEnqueueWriteImage", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueWriteImageRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clEnqueueCopyImage", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueCopyImageRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clEnqueueCopyImageToBuffer", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueCopyImageToBufferRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clEnqueueCopyBufferToImage", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueCopyBufferToImageRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clEnqueueMapBuffer", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueMapBufferRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clEnqueueUnmapMemObject", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueUnmapMemObjectRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clEnqueueFillBuffer", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueFillBufferRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clEnqueueFillImage", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueFillImageRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clWaitForEvents", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClWaitForEventsRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clGetEventInfo", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetEventInfoRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clGetEventProfilingInfo", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetEventProfilingInfoRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clCreateUserEvent", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateUserEventRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clSetUserEventStatus", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClSetUserEventStatusRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clSetEventCallback", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClSetEventCallbackRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clGetDeviceAndHostTimer", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetDeviceAndHostTimerRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clGetHostTimer", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetHostTimerRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clSVMAlloc", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClSVMAllocRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clSVMFree", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClSVMFreeRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clEnqueueSVMMap", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueSVMMapRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clEnqueueSVMUnmap", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueSVMUnmapRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clSetKernelArgSVMPointer", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClSetKernelArgSVMPointerRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clSetKernelExecInfo", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClSetKernelExecInfoRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clEnqueueSVMMemFill", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueSVMMemFillRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clEnqueueSVMMigrateMem", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueSVMMigrateMemRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clEnqueueSVMMemcpy", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueSVMMemcpyRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clEnqueueSVMMemcpyRpcHelperMalloc2Usm", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueSVMMemcpyRpcHelperMalloc2UsmRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clEnqueueSVMMemcpyRpcHelperUsm2Malloc", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueSVMMemcpyRpcHelperUsm2MallocRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clCreateSubDevicesEXT", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateSubDevicesEXTRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clReleaseDeviceEXT", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClReleaseDeviceEXTRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clRetainDeviceEXT", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClRetainDeviceEXTRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clGetKernelSubGroupInfoKHR", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetKernelSubGroupInfoKHRRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clEnqueueMemFillINTEL", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueMemFillINTELRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clEnqueueMemcpyINTEL", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueMemcpyINTELRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clEnqueueMemcpyINTELRpcHelperMalloc2Usm", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueMemcpyINTELRpcHelperMalloc2UsmRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clEnqueueMemcpyINTELRpcHelperUsm2Malloc", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueMemcpyINTELRpcHelperUsm2MallocRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clSetKernelArgMemPointerINTEL", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClSetKernelArgMemPointerINTELRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clGetMemAllocInfoINTEL", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetMemAllocInfoINTELRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clDeviceMemAllocINTEL", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClDeviceMemAllocINTELRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clHostMemAllocINTEL", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClHostMemAllocINTELRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clSharedMemAllocINTEL", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClSharedMemAllocINTELRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clMemFreeINTEL", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClMemFreeINTELRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clMemBlockingFreeINTEL", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClMemBlockingFreeINTELRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clEnqueueMigrateMemINTEL", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueMigrateMemINTELRpcM::messageSubtype)),
        std::pair<std::string, RetT>("clGetDeviceGlobalVariablePointerINTEL", RetT(Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetDeviceGlobalVariablePointerINTELRpcM::messageSubtype)),
    };

    auto it = options.find(funcName);
    if(it == options.end()) {
        return std::optional<RetT>(std::nullopt);
    }
    return std::optional<RetT>(it->second);
}

namespace RpcCallIds {
static constexpr RpcCallId clGetPlatformIDs = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetPlatformIDsRpcM::messageSubtype};
static constexpr RpcCallId clGetPlatformInfo = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetPlatformInfoRpcM::messageSubtype};
static constexpr RpcCallId clGetDeviceIDs = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetDeviceIDsRpcM::messageSubtype};
static constexpr RpcCallId clGetDeviceInfo = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetDeviceInfoRpcM::messageSubtype};
static constexpr RpcCallId clCreateContext = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateContextRpcM::messageSubtype};
static constexpr RpcCallId clCreateContextFromType = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateContextFromTypeRpcM::messageSubtype};
static constexpr RpcCallId clGetContextInfo = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetContextInfoRpcM::messageSubtype};
static constexpr RpcCallId clCreateSubDevices = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateSubDevicesRpcM::messageSubtype};
static constexpr RpcCallId clCreateCommandQueue = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateCommandQueueRpcM::messageSubtype};
static constexpr RpcCallId clSetDefaultDeviceCommandQueue = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClSetDefaultDeviceCommandQueueRpcM::messageSubtype};
static constexpr RpcCallId clCreateCommandQueueWithProperties = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateCommandQueueWithPropertiesRpcM::messageSubtype};
static constexpr RpcCallId clCreateProgramWithSource = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateProgramWithSourceRpcM::messageSubtype};
static constexpr RpcCallId clCreateProgramWithIL = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateProgramWithILRpcM::messageSubtype};
static constexpr RpcCallId clCreateProgramWithBinary = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateProgramWithBinaryRpcM::messageSubtype};
static constexpr RpcCallId clCreateProgramWithBuiltInKernels = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateProgramWithBuiltInKernelsRpcM::messageSubtype};
static constexpr RpcCallId clBuildProgram = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClBuildProgramRpcM::messageSubtype};
static constexpr RpcCallId clCompileProgram = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCompileProgramRpcM::messageSubtype};
static constexpr RpcCallId clLinkProgram = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClLinkProgramRpcM::messageSubtype};
static constexpr RpcCallId clGetProgramBuildInfo = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetProgramBuildInfoRpcM::messageSubtype};
static constexpr RpcCallId clCreateKernel = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateKernelRpcM::messageSubtype};
static constexpr RpcCallId clCloneKernel = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCloneKernelRpcM::messageSubtype};
static constexpr RpcCallId clCreateKernelsInProgram = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateKernelsInProgramRpcM::messageSubtype};
static constexpr RpcCallId clGetCommandQueueInfo = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetCommandQueueInfoRpcM::messageSubtype};
static constexpr RpcCallId clGetProgramInfoRpcHelper = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetProgramInfoRpcHelperRpcM::messageSubtype};
static constexpr RpcCallId clGetProgramInfoGetBinariesRpcHelper = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetProgramInfoGetBinariesRpcHelperRpcM::messageSubtype};
static constexpr RpcCallId clGetMemObjectInfo = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetMemObjectInfoRpcM::messageSubtype};
static constexpr RpcCallId clGetImageInfo = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetImageInfoRpcM::messageSubtype};
static constexpr RpcCallId clGetSamplerInfo = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetSamplerInfoRpcM::messageSubtype};
static constexpr RpcCallId clGetKernelInfo = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetKernelInfoRpcM::messageSubtype};
static constexpr RpcCallId clGetKernelWorkGroupInfo = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetKernelWorkGroupInfoRpcM::messageSubtype};
static constexpr RpcCallId clGetKernelArgInfo = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetKernelArgInfoRpcM::messageSubtype};
static constexpr RpcCallId clGetKernelSubGroupInfo = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetKernelSubGroupInfoRpcM::messageSubtype};
static constexpr RpcCallId clReleaseCommandQueue = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClReleaseCommandQueueRpcM::messageSubtype};
static constexpr RpcCallId clReleaseContext = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClReleaseContextRpcM::messageSubtype};
static constexpr RpcCallId clReleaseDevice = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClReleaseDeviceRpcM::messageSubtype};
static constexpr RpcCallId clReleaseKernel = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClReleaseKernelRpcM::messageSubtype};
static constexpr RpcCallId clReleaseSampler = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClReleaseSamplerRpcM::messageSubtype};
static constexpr RpcCallId clReleaseProgram = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClReleaseProgramRpcM::messageSubtype};
static constexpr RpcCallId clReleaseMemObject = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClReleaseMemObjectRpcM::messageSubtype};
static constexpr RpcCallId clReleaseEvent = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClReleaseEventRpcM::messageSubtype};
static constexpr RpcCallId clRetainCommandQueue = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClRetainCommandQueueRpcM::messageSubtype};
static constexpr RpcCallId clRetainContext = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClRetainContextRpcM::messageSubtype};
static constexpr RpcCallId clRetainDevice = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClRetainDeviceRpcM::messageSubtype};
static constexpr RpcCallId clRetainProgram = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClRetainProgramRpcM::messageSubtype};
static constexpr RpcCallId clRetainMemObject = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClRetainMemObjectRpcM::messageSubtype};
static constexpr RpcCallId clRetainSampler = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClRetainSamplerRpcM::messageSubtype};
static constexpr RpcCallId clRetainKernel = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClRetainKernelRpcM::messageSubtype};
static constexpr RpcCallId clRetainEvent = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClRetainEventRpcM::messageSubtype};
static constexpr RpcCallId clFlush = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClFlushRpcM::messageSubtype};
static constexpr RpcCallId clFinish = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClFinishRpcM::messageSubtype};
static constexpr RpcCallId clEnqueueNDRangeKernel = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueNDRangeKernelRpcM::messageSubtype};
static constexpr RpcCallId clEnqueueTask = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueTaskRpcM::messageSubtype};
static constexpr RpcCallId clEnqueueMarkerWithWaitList = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueMarkerWithWaitListRpcM::messageSubtype};
static constexpr RpcCallId clEnqueueMarker = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueMarkerRpcM::messageSubtype};
static constexpr RpcCallId clEnqueueBarrierWithWaitList = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueBarrierWithWaitListRpcM::messageSubtype};
static constexpr RpcCallId clEnqueueBarrier = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueBarrierRpcM::messageSubtype};
static constexpr RpcCallId clEnqueueWaitForEvents = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueWaitForEventsRpcM::messageSubtype};
static constexpr RpcCallId clEnqueueMigrateMemObjects = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueMigrateMemObjectsRpcM::messageSubtype};
static constexpr RpcCallId clCreateBuffer = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateBufferRpcM::messageSubtype};
static constexpr RpcCallId clCreateBufferRpcHelperUseHostPtrZeroCopyMallocShmem = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateBufferRpcHelperUseHostPtrZeroCopyMallocShmemRpcM::messageSubtype};
static constexpr RpcCallId clCreateSubBuffer = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateSubBufferRpcM::messageSubtype};
static constexpr RpcCallId clCreatePipe = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreatePipeRpcM::messageSubtype};
static constexpr RpcCallId clGetPipeInfo = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetPipeInfoRpcM::messageSubtype};
static constexpr RpcCallId clCreateImage = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateImageRpcM::messageSubtype};
static constexpr RpcCallId clCreateImage2D = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateImage2DRpcM::messageSubtype};
static constexpr RpcCallId clCreateImage3D = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateImage3DRpcM::messageSubtype};
static constexpr RpcCallId clCreateSampler = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateSamplerRpcM::messageSubtype};
static constexpr RpcCallId clCreateSamplerWithProperties = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateSamplerWithPropertiesRpcM::messageSubtype};
static constexpr RpcCallId clCreateImageWithProperties = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateImageWithPropertiesRpcM::messageSubtype};
static constexpr RpcCallId clCreateBufferWithProperties = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateBufferWithPropertiesRpcM::messageSubtype};
static constexpr RpcCallId clGetSupportedImageFormats = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetSupportedImageFormatsRpcM::messageSubtype};
static constexpr RpcCallId clSetKernelArg = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClSetKernelArgRpcM::messageSubtype};
static constexpr RpcCallId clSetProgramSpecializationConstant = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClSetProgramSpecializationConstantRpcM::messageSubtype};
static constexpr RpcCallId clEnqueueWriteBuffer = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueWriteBufferRpcM::messageSubtype};
static constexpr RpcCallId clEnqueueWriteBufferRpcHelperMallocHost = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueWriteBufferRpcHelperMallocHostRpcM::messageSubtype};
static constexpr RpcCallId clEnqueueWriteBufferRpcHelperZeroCopyMallocShmem = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueWriteBufferRpcHelperZeroCopyMallocShmemRpcM::messageSubtype};
static constexpr RpcCallId clEnqueueWriteBufferRect = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueWriteBufferRectRpcM::messageSubtype};
static constexpr RpcCallId clEnqueueWriteBufferRectRpcHelperMallocHost = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueWriteBufferRectRpcHelperMallocHostRpcM::messageSubtype};
static constexpr RpcCallId clEnqueueWriteBufferRectRpcHelperZeroCopyMallocShmem = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueWriteBufferRectRpcHelperZeroCopyMallocShmemRpcM::messageSubtype};
static constexpr RpcCallId clEnqueueReadBuffer = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueReadBufferRpcM::messageSubtype};
static constexpr RpcCallId clEnqueueReadBufferRect = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueReadBufferRectRpcM::messageSubtype};
static constexpr RpcCallId clEnqueueReadBufferRectRpcHelperMallocHost = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueReadBufferRectRpcHelperMallocHostRpcM::messageSubtype};
static constexpr RpcCallId clEnqueueReadBufferRectRpcHelperZeroCopyMallocShmem = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueReadBufferRectRpcHelperZeroCopyMallocShmemRpcM::messageSubtype};
static constexpr RpcCallId clEnqueueReadBufferRpcHelperMallocHost = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueReadBufferRpcHelperMallocHostRpcM::messageSubtype};
static constexpr RpcCallId clEnqueueReadBufferRpcHelperZeroCopyMallocShmem = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueReadBufferRpcHelperZeroCopyMallocShmemRpcM::messageSubtype};
static constexpr RpcCallId clEnqueueCopyBuffer = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueCopyBufferRpcM::messageSubtype};
static constexpr RpcCallId clEnqueueCopyBufferRect = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueCopyBufferRectRpcM::messageSubtype};
static constexpr RpcCallId clEnqueueReadImage = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueReadImageRpcM::messageSubtype};
static constexpr RpcCallId clEnqueueWriteImage = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueWriteImageRpcM::messageSubtype};
static constexpr RpcCallId clEnqueueCopyImage = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueCopyImageRpcM::messageSubtype};
static constexpr RpcCallId clEnqueueCopyImageToBuffer = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueCopyImageToBufferRpcM::messageSubtype};
static constexpr RpcCallId clEnqueueCopyBufferToImage = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueCopyBufferToImageRpcM::messageSubtype};
static constexpr RpcCallId clEnqueueMapBuffer = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueMapBufferRpcM::messageSubtype};
static constexpr RpcCallId clEnqueueUnmapMemObject = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueUnmapMemObjectRpcM::messageSubtype};
static constexpr RpcCallId clEnqueueFillBuffer = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueFillBufferRpcM::messageSubtype};
static constexpr RpcCallId clEnqueueFillImage = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueFillImageRpcM::messageSubtype};
static constexpr RpcCallId clWaitForEvents = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClWaitForEventsRpcM::messageSubtype};
static constexpr RpcCallId clGetEventInfo = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetEventInfoRpcM::messageSubtype};
static constexpr RpcCallId clGetEventProfilingInfo = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetEventProfilingInfoRpcM::messageSubtype};
static constexpr RpcCallId clCreateUserEvent = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateUserEventRpcM::messageSubtype};
static constexpr RpcCallId clSetUserEventStatus = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClSetUserEventStatusRpcM::messageSubtype};
static constexpr RpcCallId clSetEventCallback = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClSetEventCallbackRpcM::messageSubtype};
static constexpr RpcCallId clGetDeviceAndHostTimer = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetDeviceAndHostTimerRpcM::messageSubtype};
static constexpr RpcCallId clGetHostTimer = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetHostTimerRpcM::messageSubtype};
static constexpr RpcCallId clSVMAlloc = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClSVMAllocRpcM::messageSubtype};
static constexpr RpcCallId clSVMFree = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClSVMFreeRpcM::messageSubtype};
static constexpr RpcCallId clEnqueueSVMMap = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueSVMMapRpcM::messageSubtype};
static constexpr RpcCallId clEnqueueSVMUnmap = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueSVMUnmapRpcM::messageSubtype};
static constexpr RpcCallId clSetKernelArgSVMPointer = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClSetKernelArgSVMPointerRpcM::messageSubtype};
static constexpr RpcCallId clSetKernelExecInfo = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClSetKernelExecInfoRpcM::messageSubtype};
static constexpr RpcCallId clEnqueueSVMMemFill = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueSVMMemFillRpcM::messageSubtype};
static constexpr RpcCallId clEnqueueSVMMigrateMem = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueSVMMigrateMemRpcM::messageSubtype};
static constexpr RpcCallId clEnqueueSVMMemcpy = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueSVMMemcpyRpcM::messageSubtype};
static constexpr RpcCallId clEnqueueSVMMemcpyRpcHelperMalloc2Usm = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueSVMMemcpyRpcHelperMalloc2UsmRpcM::messageSubtype};
static constexpr RpcCallId clEnqueueSVMMemcpyRpcHelperUsm2Malloc = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueSVMMemcpyRpcHelperUsm2MallocRpcM::messageSubtype};
static constexpr RpcCallId clCreateSubDevicesEXT = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClCreateSubDevicesEXTRpcM::messageSubtype};
static constexpr RpcCallId clReleaseDeviceEXT = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClReleaseDeviceEXTRpcM::messageSubtype};
static constexpr RpcCallId clRetainDeviceEXT = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClRetainDeviceEXTRpcM::messageSubtype};
static constexpr RpcCallId clGetKernelSubGroupInfoKHR = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetKernelSubGroupInfoKHRRpcM::messageSubtype};
static constexpr RpcCallId clEnqueueMemFillINTEL = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueMemFillINTELRpcM::messageSubtype};
static constexpr RpcCallId clEnqueueMemcpyINTEL = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueMemcpyINTELRpcM::messageSubtype};
static constexpr RpcCallId clEnqueueMemcpyINTELRpcHelperMalloc2Usm = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueMemcpyINTELRpcHelperMalloc2UsmRpcM::messageSubtype};
static constexpr RpcCallId clEnqueueMemcpyINTELRpcHelperUsm2Malloc = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueMemcpyINTELRpcHelperUsm2MallocRpcM::messageSubtype};
static constexpr RpcCallId clSetKernelArgMemPointerINTEL = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClSetKernelArgMemPointerINTELRpcM::messageSubtype};
static constexpr RpcCallId clGetMemAllocInfoINTEL = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetMemAllocInfoINTELRpcM::messageSubtype};
static constexpr RpcCallId clDeviceMemAllocINTEL = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClDeviceMemAllocINTELRpcM::messageSubtype};
static constexpr RpcCallId clHostMemAllocINTEL = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClHostMemAllocINTELRpcM::messageSubtype};
static constexpr RpcCallId clSharedMemAllocINTEL = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClSharedMemAllocINTELRpcM::messageSubtype};
static constexpr RpcCallId clMemFreeINTEL = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClMemFreeINTELRpcM::messageSubtype};
static constexpr RpcCallId clMemBlockingFreeINTEL = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClMemBlockingFreeINTELRpcM::messageSubtype};
static constexpr RpcCallId clEnqueueMigrateMemINTEL = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClEnqueueMigrateMemINTELRpcM::messageSubtype};
static constexpr RpcCallId clGetDeviceGlobalVariablePointerINTEL = {Cal::Rpc::RpcMessageHeader::messageTypeRpcOcl, ClGetDeviceGlobalVariablePointerINTELRpcM::messageSubtype};
} // namespace RpcCallIds

namespace RpcCallMessageTypes {
using clGetPlatformIDs = ClGetPlatformIDsRpcM;
using clGetPlatformInfo = ClGetPlatformInfoRpcM;
using clGetDeviceIDs = ClGetDeviceIDsRpcM;
using clGetDeviceInfo = ClGetDeviceInfoRpcM;
using clCreateContext = ClCreateContextRpcM;
using clCreateContextFromType = ClCreateContextFromTypeRpcM;
using clGetContextInfo = ClGetContextInfoRpcM;
using clCreateSubDevices = ClCreateSubDevicesRpcM;
using clCreateCommandQueue = ClCreateCommandQueueRpcM;
using clSetDefaultDeviceCommandQueue = ClSetDefaultDeviceCommandQueueRpcM;
using clCreateCommandQueueWithProperties = ClCreateCommandQueueWithPropertiesRpcM;
using clCreateProgramWithSource = ClCreateProgramWithSourceRpcM;
using clCreateProgramWithIL = ClCreateProgramWithILRpcM;
using clCreateProgramWithBinary = ClCreateProgramWithBinaryRpcM;
using clCreateProgramWithBuiltInKernels = ClCreateProgramWithBuiltInKernelsRpcM;
using clBuildProgram = ClBuildProgramRpcM;
using clCompileProgram = ClCompileProgramRpcM;
using clLinkProgram = ClLinkProgramRpcM;
using clGetProgramBuildInfo = ClGetProgramBuildInfoRpcM;
using clCreateKernel = ClCreateKernelRpcM;
using clCloneKernel = ClCloneKernelRpcM;
using clCreateKernelsInProgram = ClCreateKernelsInProgramRpcM;
using clGetCommandQueueInfo = ClGetCommandQueueInfoRpcM;
using clGetProgramInfoRpcHelper = ClGetProgramInfoRpcHelperRpcM;
using clGetProgramInfoGetBinariesRpcHelper = ClGetProgramInfoGetBinariesRpcHelperRpcM;
using clGetMemObjectInfo = ClGetMemObjectInfoRpcM;
using clGetImageInfo = ClGetImageInfoRpcM;
using clGetSamplerInfo = ClGetSamplerInfoRpcM;
using clGetKernelInfo = ClGetKernelInfoRpcM;
using clGetKernelWorkGroupInfo = ClGetKernelWorkGroupInfoRpcM;
using clGetKernelArgInfo = ClGetKernelArgInfoRpcM;
using clGetKernelSubGroupInfo = ClGetKernelSubGroupInfoRpcM;
using clReleaseCommandQueue = ClReleaseCommandQueueRpcM;
using clReleaseContext = ClReleaseContextRpcM;
using clReleaseDevice = ClReleaseDeviceRpcM;
using clReleaseKernel = ClReleaseKernelRpcM;
using clReleaseSampler = ClReleaseSamplerRpcM;
using clReleaseProgram = ClReleaseProgramRpcM;
using clReleaseMemObject = ClReleaseMemObjectRpcM;
using clReleaseEvent = ClReleaseEventRpcM;
using clRetainCommandQueue = ClRetainCommandQueueRpcM;
using clRetainContext = ClRetainContextRpcM;
using clRetainDevice = ClRetainDeviceRpcM;
using clRetainProgram = ClRetainProgramRpcM;
using clRetainMemObject = ClRetainMemObjectRpcM;
using clRetainSampler = ClRetainSamplerRpcM;
using clRetainKernel = ClRetainKernelRpcM;
using clRetainEvent = ClRetainEventRpcM;
using clFlush = ClFlushRpcM;
using clFinish = ClFinishRpcM;
using clEnqueueNDRangeKernel = ClEnqueueNDRangeKernelRpcM;
using clEnqueueTask = ClEnqueueTaskRpcM;
using clEnqueueMarkerWithWaitList = ClEnqueueMarkerWithWaitListRpcM;
using clEnqueueMarker = ClEnqueueMarkerRpcM;
using clEnqueueBarrierWithWaitList = ClEnqueueBarrierWithWaitListRpcM;
using clEnqueueBarrier = ClEnqueueBarrierRpcM;
using clEnqueueWaitForEvents = ClEnqueueWaitForEventsRpcM;
using clEnqueueMigrateMemObjects = ClEnqueueMigrateMemObjectsRpcM;
using clCreateBuffer = ClCreateBufferRpcM;
using clCreateBufferRpcHelperUseHostPtrZeroCopyMallocShmem = ClCreateBufferRpcHelperUseHostPtrZeroCopyMallocShmemRpcM;
using clCreateSubBuffer = ClCreateSubBufferRpcM;
using clCreatePipe = ClCreatePipeRpcM;
using clGetPipeInfo = ClGetPipeInfoRpcM;
using clCreateImage = ClCreateImageRpcM;
using clCreateImage2D = ClCreateImage2DRpcM;
using clCreateImage3D = ClCreateImage3DRpcM;
using clCreateSampler = ClCreateSamplerRpcM;
using clCreateSamplerWithProperties = ClCreateSamplerWithPropertiesRpcM;
using clCreateImageWithProperties = ClCreateImageWithPropertiesRpcM;
using clCreateBufferWithProperties = ClCreateBufferWithPropertiesRpcM;
using clGetSupportedImageFormats = ClGetSupportedImageFormatsRpcM;
using clSetKernelArg = ClSetKernelArgRpcM;
using clSetProgramSpecializationConstant = ClSetProgramSpecializationConstantRpcM;
using clEnqueueWriteBuffer = ClEnqueueWriteBufferRpcM;
using clEnqueueWriteBufferRpcHelperMallocHost = ClEnqueueWriteBufferRpcHelperMallocHostRpcM;
using clEnqueueWriteBufferRpcHelperZeroCopyMallocShmem = ClEnqueueWriteBufferRpcHelperZeroCopyMallocShmemRpcM;
using clEnqueueWriteBufferRect = ClEnqueueWriteBufferRectRpcM;
using clEnqueueWriteBufferRectRpcHelperMallocHost = ClEnqueueWriteBufferRectRpcHelperMallocHostRpcM;
using clEnqueueWriteBufferRectRpcHelperZeroCopyMallocShmem = ClEnqueueWriteBufferRectRpcHelperZeroCopyMallocShmemRpcM;
using clEnqueueReadBuffer = ClEnqueueReadBufferRpcM;
using clEnqueueReadBufferRect = ClEnqueueReadBufferRectRpcM;
using clEnqueueReadBufferRectRpcHelperMallocHost = ClEnqueueReadBufferRectRpcHelperMallocHostRpcM;
using clEnqueueReadBufferRectRpcHelperZeroCopyMallocShmem = ClEnqueueReadBufferRectRpcHelperZeroCopyMallocShmemRpcM;
using clEnqueueReadBufferRpcHelperMallocHost = ClEnqueueReadBufferRpcHelperMallocHostRpcM;
using clEnqueueReadBufferRpcHelperZeroCopyMallocShmem = ClEnqueueReadBufferRpcHelperZeroCopyMallocShmemRpcM;
using clEnqueueCopyBuffer = ClEnqueueCopyBufferRpcM;
using clEnqueueCopyBufferRect = ClEnqueueCopyBufferRectRpcM;
using clEnqueueReadImage = ClEnqueueReadImageRpcM;
using clEnqueueWriteImage = ClEnqueueWriteImageRpcM;
using clEnqueueCopyImage = ClEnqueueCopyImageRpcM;
using clEnqueueCopyImageToBuffer = ClEnqueueCopyImageToBufferRpcM;
using clEnqueueCopyBufferToImage = ClEnqueueCopyBufferToImageRpcM;
using clEnqueueMapBuffer = ClEnqueueMapBufferRpcM;
using clEnqueueUnmapMemObject = ClEnqueueUnmapMemObjectRpcM;
using clEnqueueFillBuffer = ClEnqueueFillBufferRpcM;
using clEnqueueFillImage = ClEnqueueFillImageRpcM;
using clWaitForEvents = ClWaitForEventsRpcM;
using clGetEventInfo = ClGetEventInfoRpcM;
using clGetEventProfilingInfo = ClGetEventProfilingInfoRpcM;
using clCreateUserEvent = ClCreateUserEventRpcM;
using clSetUserEventStatus = ClSetUserEventStatusRpcM;
using clSetEventCallback = ClSetEventCallbackRpcM;
using clGetDeviceAndHostTimer = ClGetDeviceAndHostTimerRpcM;
using clGetHostTimer = ClGetHostTimerRpcM;
using clSVMAlloc = ClSVMAllocRpcM;
using clSVMFree = ClSVMFreeRpcM;
using clEnqueueSVMMap = ClEnqueueSVMMapRpcM;
using clEnqueueSVMUnmap = ClEnqueueSVMUnmapRpcM;
using clSetKernelArgSVMPointer = ClSetKernelArgSVMPointerRpcM;
using clSetKernelExecInfo = ClSetKernelExecInfoRpcM;
using clEnqueueSVMMemFill = ClEnqueueSVMMemFillRpcM;
using clEnqueueSVMMigrateMem = ClEnqueueSVMMigrateMemRpcM;
using clEnqueueSVMMemcpy = ClEnqueueSVMMemcpyRpcM;
using clEnqueueSVMMemcpyRpcHelperMalloc2Usm = ClEnqueueSVMMemcpyRpcHelperMalloc2UsmRpcM;
using clEnqueueSVMMemcpyRpcHelperUsm2Malloc = ClEnqueueSVMMemcpyRpcHelperUsm2MallocRpcM;
using clCreateSubDevicesEXT = ClCreateSubDevicesEXTRpcM;
using clReleaseDeviceEXT = ClReleaseDeviceEXTRpcM;
using clRetainDeviceEXT = ClRetainDeviceEXTRpcM;
using clGetKernelSubGroupInfoKHR = ClGetKernelSubGroupInfoKHRRpcM;
using clEnqueueMemFillINTEL = ClEnqueueMemFillINTELRpcM;
using clEnqueueMemcpyINTEL = ClEnqueueMemcpyINTELRpcM;
using clEnqueueMemcpyINTELRpcHelperMalloc2Usm = ClEnqueueMemcpyINTELRpcHelperMalloc2UsmRpcM;
using clEnqueueMemcpyINTELRpcHelperUsm2Malloc = ClEnqueueMemcpyINTELRpcHelperUsm2MallocRpcM;
using clSetKernelArgMemPointerINTEL = ClSetKernelArgMemPointerINTELRpcM;
using clGetMemAllocInfoINTEL = ClGetMemAllocInfoINTELRpcM;
using clDeviceMemAllocINTEL = ClDeviceMemAllocINTELRpcM;
using clHostMemAllocINTEL = ClHostMemAllocINTELRpcM;
using clSharedMemAllocINTEL = ClSharedMemAllocINTELRpcM;
using clMemFreeINTEL = ClMemFreeINTELRpcM;
using clMemBlockingFreeINTEL = ClMemBlockingFreeINTELRpcM;
using clEnqueueMigrateMemINTEL = ClEnqueueMigrateMemINTELRpcM;
using clGetDeviceGlobalVariablePointerINTEL = ClGetDeviceGlobalVariablePointerINTELRpcM;
}

} // namespace Ocl
} // namespace Rpc
} // namespace Cal
// #### Generated code -- end ####
