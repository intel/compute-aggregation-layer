/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#define FULL_VERBOSITY_IN_RELEASE_BUILD 1
#define ENABLE_BLOATED_VERBOSITY 1

#include "cal.h"
#include "level_zero/ze_api.h"
#include "shared/log.h"
#include "test/utils/assertions.h"
#include "test/utils/l0_common_steps.h"

using namespace Cal::Testing::Utils::LevelZero;

bool createImage(ze_context_handle_t context, ze_device_handle_t device, ze_image_handle_t &hImage, ze_image_desc_t &imageDescription) {
    auto zeImageCreateResult = zeImageCreate(context, device, &imageDescription, &hImage);
    if (zeImageCreateResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeImageCreate() has failed! Error code: %d", static_cast<int>(zeImageCreateResult));
        return false;
    }

    log<Verbosity::info>("Image has been created! Image = %p", static_cast<void *>(hImage));
    return true;
}

bool destroyImage(ze_image_handle_t hImage) {
    auto zeImageDestroyResult = zeImageDestroy(hImage);
    if (zeImageDestroyResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeImageDestroy() has failed! Error code: %d", static_cast<int>(zeImageDestroyResult));
        return false;
    }

    log<Verbosity::info>("Image has been destroyed!");
    return true;
}

bool getImageProperties(ze_device_handle_t device, ze_image_desc_t &imageDescription, ze_image_properties_t &imageProperties) {
    log<Verbosity::info>("Getting image properties!");

    const auto zeImageGetPropertiesResult = zeImageGetProperties(device, &imageDescription, &imageProperties);
    if (zeImageGetPropertiesResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeImageGetProperties() has failed! Error code: %d", static_cast<int>(zeImageGetPropertiesResult));
        return false;
    }

    log<Verbosity::info>("Success! Properties samplerFilterFlags is %d", static_cast<int>(imageProperties.samplerFilterFlags));
    return true;
}

int main(int argc, const char *argv[]) {
    Cal::Utils::initMaxDynamicVerbosity(Verbosity::debug);

    std::vector<ze_driver_handle_t> drivers{};
    std::vector<ze_device_handle_t> devices{};

    RUN_REQUIRED_STEP(initL0());
    RUN_REQUIRED_STEP(getDrivers(drivers));
    RUN_REQUIRED_STEP(getDevices(drivers[0], devices));

    ze_context_handle_t context{};
    RUN_REQUIRED_STEP(createContext(drivers[0], context));

    ze_image_desc_t imageDescription{
        ZE_STRUCTURE_TYPE_IMAGE_DESC, // stype
        nullptr,                      // pNext
        0,                            // flags
        ZE_IMAGE_TYPE_1D,             // type
        {
            // format
            ZE_IMAGE_FORMAT_LAYOUT_8,  // layout
            ZE_IMAGE_FORMAT_TYPE_UINT, // type
            ZE_IMAGE_FORMAT_SWIZZLE_R, // x
            ZE_IMAGE_FORMAT_SWIZZLE_G, // y
            ZE_IMAGE_FORMAT_SWIZZLE_B, // z
            ZE_IMAGE_FORMAT_SWIZZLE_A  // w
        },
        16, // width
        0,  // height
        0,  // depth
        0,  // arraylevels
        0   // miplevels
    };

    ze_image_handle_t hImage{};
    RUN_REQUIRED_STEP(createImage(context, devices[0], hImage, imageDescription));

    ze_image_properties_t imageProperties{ZE_STRUCTURE_TYPE_IMAGE_PROPERTIES};
    RUN_REQUIRED_STEP(getImageProperties(devices[0], imageDescription, imageProperties));

    RUN_REQUIRED_STEP(destroyImage(hImage));
    RUN_REQUIRED_STEP(destroyContext(context));

    return 0;
}
