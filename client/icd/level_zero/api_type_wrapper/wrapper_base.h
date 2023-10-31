/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "level_zero/ze_api.h"
#include "level_zero/ze_ddi.h"
#include "shared/log.h"

#include <cstdlib>

extern ze_dditable_t l0Ddi;

namespace Cal::Client::Icd::LevelZero {

/*
 *  When custom handling is required for a specific L0 API type, then on ICD side
 *  a special type wrapper is introduced. Besides providing a specific functionality,
 *  it is aware of mapping between "local" and "remote objects".
 *
 *  From ICD point of view a remote object is just a handle received from UMD, which lives
 *  in service process. Therefore, such remote object cannot be accessed directly in client process.
 *
 *  A local object on contrary is an object created in client process to which ICD belongs.
 *  Such local object can be accessed and provides functionality, which is essential to
 *  customize specific function calls.
 *
 *  IcdWrapperBase contains functionality to ensure, that object hold in given variable
 *  can be used as local object.
 */
struct IcdWrapperBase {
    ze_dditable_t *ddiTable = &l0Ddi;

    bool isLocal() const { return ddiTable == &l0Ddi; }
    bool isRemote() const { return !isLocal(); }

    void ensureIsLocalObject() const {
        if (isRemote()) {
            log<Verbosity::critical>("Attempted to use remote object as local object!");
            std::abort();
        }
    }
};

/*
 * IcdMappedTypeWrapper is a base class of all ICD LevelZero type wrappers.
 * It provides functionality to safely get local object from API handle.
 */
template <typename LocalObjectT>
struct IcdMappedTypeWrapper : public IcdWrapperBase {
    LocalObjectT *asLocalObject() {
        ensureIsLocalObject();
        return static_cast<LocalObjectT *>(this);
    }

    const LocalObjectT *asLocalObject() const {
        ensureIsLocalObject();
        return static_cast<LocalObjectT *>(this);
    }
};

} // namespace Cal::Client::Icd::LevelZero
