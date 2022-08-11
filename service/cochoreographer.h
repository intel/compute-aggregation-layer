/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "shared/rpc.h"

#include <memory>
#include <string>
#include <vector>

namespace Cal {

namespace Service {

class IMember {
  public:
    enum StepFeedback { execute,
                        skip };
    virtual StepFeedback makeStepBefore(Cal::Rpc::RpcMessageHeader &command) = 0;
    virtual StepFeedback makeStepAfter(Cal::Rpc::RpcMessageHeader &command) = 0;
};

class ISpectacle;

class IChoreography {
  public:
    virtual bool recruitByPpid() const = 0;
    virtual bool recruitByName() const = 0;
    virtual const std::string &getName() const = 0;
    virtual std::unique_ptr<ISpectacle> createSpectacle(const std::vector<Cal::Rpc::DirectCallCallbackT> &directCallCallbacks) const = 0;
};

class ISpectacle {
  public:
    virtual bool isStillRecruting() const = 0;
    virtual IMember *addNewMember() = 0;
    virtual const IChoreography &getChoreography() const = 0;
};

class ChoreographyLibrary {
  public:
    static std::unique_ptr<ChoreographyLibrary> create();

    ChoreographyLibrary() = default;
    virtual ~ChoreographyLibrary() = default;

    virtual void load(const std::string &srcPath) {
        return;
    }
    virtual const IChoreography *get(const std::string &name) {
        return nullptr;
    }
};

} // namespace Service

} // namespace Cal
