/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include <dlfcn.h>
#include <string>
#include <type_traits>
#include <utility>

namespace Cal::Testing::Utils {

class DynamicLibrary final {
  public:
    DynamicLibrary(const DynamicLibrary &lib) = delete;
    DynamicLibrary &operator=(const DynamicLibrary &lib) = delete;

    DynamicLibrary(std::string name)
        : name{std::move(name)} {
        libHandle = dlopen(this->name.c_str(), RTLD_LAZY);
    }

    ~DynamicLibrary() {
        close();
    }

    DynamicLibrary(DynamicLibrary &&other) noexcept
        : libHandle{std::exchange(other.libHandle, nullptr)},
          name{std::move(other.name)} {}

    DynamicLibrary &operator=(DynamicLibrary &&other) noexcept {
        if (this == &other) {
            return *this;
        }

        close();

        libHandle = std::exchange(other.libHandle, nullptr);
        name = std::move(other.name);

        return *this;
    }

    void close() {
        if (libHandle) {
            dlclose(libHandle);
            libHandle = nullptr;
        }
    }

    bool isLoaded() const {
        return libHandle != nullptr;
    }

    template <typename FunctionT>
    auto getFunction(const std::string &symbol) {
        static_assert(std::is_function_v<FunctionT>, "Passed type is not a function!");

        if (!libHandle) {
            return static_cast<std::add_pointer_t<FunctionT>>(nullptr);
        }

        return reinterpret_cast<std::add_pointer_t<FunctionT>>(dlsym(libHandle, symbol.c_str()));
    }

  private:
    void *libHandle{nullptr};
    std::string name{};
};

} // namespace Cal::Testing::Utils
