/*
 * Copyright (C) 2022-2023 Intel Corporation
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

enum class ImageSupported {
    Yes = 0,
    No = 1,
    Error = 2,
};

ImageSupported isImageSupportedOnTestedDevice(ze_device_handle_t device) {
    log<Verbosity::info>("Checking if images are supported on tested device!");

    ze_device_image_properties_t imageProperties = {ZE_STRUCTURE_TYPE_DEVICE_IMAGE_PROPERTIES};
    const auto zeDeviceGetImagePropertiesResult = zeDeviceGetImageProperties(device, &imageProperties);

    if (zeDeviceGetImagePropertiesResult != ZE_RESULT_SUCCESS) {
        log<Verbosity::error>("zeDeviceGetImageProperties() has failed! Error code: %d", static_cast<int>(zeDeviceGetImagePropertiesResult));
        return ImageSupported::Error;
    }

    const auto imagesSupported = imageProperties.maxImageDims1D != 0u ||
                                 imageProperties.maxImageDims2D != 0u ||
                                 imageProperties.maxImageDims3D != 0u ||
                                 imageProperties.maxImageBufferSize != 0u ||
                                 imageProperties.maxImageArraySlices != 0u ||
                                 imageProperties.maxSamplers != 0u ||
                                 imageProperties.maxReadImageArgs != 0u ||
                                 imageProperties.maxWriteImageArgs != 0u;

    return imagesSupported ? ImageSupported::Yes : ImageSupported::No;
}

ze_image_desc_t createImageDescription(void *pNext = nullptr) {
    return ze_image_desc_t{
        ZE_STRUCTURE_TYPE_IMAGE_DESC, // stype
        pNext,                        // pNext
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
}

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

    const auto imagesSupported = isImageSupportedOnTestedDevice(devices[0]);
    if (imagesSupported == ImageSupported::Error) {
        log<Verbosity::error>("Could not get information about support of images on given device! Aborting...");
        return -1;
    }

    if (imagesSupported == ImageSupported::No) {
        log<Verbosity::info>("Images are not supported on tested device! Skipping tests...");
        return 0;
    }

    ze_context_handle_t context{};
    RUN_REQUIRED_STEP(createContext(drivers[0], context));

    ze_image_view_planar_exp_desc_t imageViewPlanarExtension = {ZE_STRUCTURE_TYPE_IMAGE_VIEW_PLANAR_EXP_DESC};
    ze_image_desc_t imageDescription = createImageDescription(&imageViewPlanarExtension);

    ze_image_handle_t hImage{};
    RUN_REQUIRED_STEP(createImage(context, devices[0], hImage, imageDescription));

    ze_image_properties_t imageProperties{ZE_STRUCTURE_TYPE_IMAGE_PROPERTIES};
    RUN_REQUIRED_STEP(getImageProperties(devices[0], imageDescription, imageProperties));

    RUN_REQUIRED_STEP(destroyImage(hImage));
    RUN_REQUIRED_STEP(destroyContext(context));

    return 0;
}
