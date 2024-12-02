/*
 * Copyright (C) 2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once
#include "cal.h"

#include <string>

namespace Cal::Service {

namespace MallocOverride {

class ClientData {
  public:
    explicit ClientData(void *handle) : handle{handle} {}
    ~ClientData();

    void *getHandle() const { return handle; }

    ClientData(ClientData &) = delete;
    ClientData &operator=(ClientData &) = delete;

  private:
    void *handle = nullptr;
};

bool isOverridenInCAL();

ClientData *initializeClientData();

void *importPtr(void *ptr, ClientData *data);

} // namespace MallocOverride

void checkForRequiredFilesMallocOverride(std::string &fullCalLibPath);

} // namespace Cal::Service
