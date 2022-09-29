/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "shared/utils.h"

#include "include/cal.h"
#include "shared/log.h"
#include "shared/sys.h"

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <optional>
#include <pwd.h>
#include <stdexcept>
#include <unistd.h>
#include <vector>

using namespace std::string_literals;

extern char *__progname;

namespace Cal {

namespace Utils {

std::optional<CpuInfo> CpuInfo::read() {
    auto cpuinfoFile = Cal::Sys::openFileForRead("/proc/cpuinfo", std::ios::in);
    if (!(*cpuinfoFile)) {
        log<Verbosity::error>("Could not read /proc/cpuinfo");
        return std::nullopt;
    }

    std::string line;
    while (std::getline(*cpuinfoFile, line)) {
        Regex regex("address sizes[\t ]+:[\t ]([0-9]+) bits physical, ([0-9]+) bits virtual");
        std::vector<Smatch> match(3);
        if (false == regex.matches(line.c_str(), match)) {
            continue;
        }

        CpuInfo ret = {};
        ret.physical = stoi(match[1].str());
        ret.virtual_ = stoi(match[2].str());
        return std::make_optional(ret);
    }

    log<Verbosity::error>("Could not parse cpuinfo");
    return std::nullopt;
}

std::string getProcessName() {
    return __progname;
}

std::filesystem::path getProcessPath() {
    auto execProcPath = std::filesystem::path("/proc") / std::to_string(getpid()) / "exe";
    return std::filesystem::read_symlink(execProcPath);
}

Regex::Regex(const char *regexStr) {
    const auto result = regcomp(&regex, regexStr, REG_EXTENDED);
    if (result != 0) {
        throw std::runtime_error{"Compilation of regex has failed! Error code = " + std::to_string(result)};
    }
}

Regex::~Regex() {
    regfree(&regex);
}

bool Regex::matches(const char *text, std::vector<Smatch> &matches) {
    std::vector<regmatch_t> regmatches{};
    regmatches.resize(matches.size());

    int result = regexec(&regex, text, regmatches.size(), regmatches.data(), 0);
    if (result != 0) {
        return false;
    }

    std::transform(regmatches.begin(), regmatches.end(), matches.begin(),
                   [text](const auto &regmatch) {
                       return Smatch{text, regmatch};
                   });
    return true;
}

bool Regex::matches(const char *text) {
    int result = regexec(&regex, text, 0, nullptr, 0);
    return result == 0;
}

char *getCalEnv(std::string_view name) {
    auto ret = Cal::Sys::getenv(name.data());
    return ret;
}

bool getCalEnvFlag(std::string_view name, bool defaultValue) {
    auto envStr = getCalEnv(name);
    if (nullptr == envStr) {
        return defaultValue;
    }

    bool value = defaultValue;
    bool valid = true;
    if (1 != strlen(envStr)) {
        valid = false;
    } else {
        switch (envStr[0]) {
        default:
            valid = false;
            break;
        case '1':
            [[fallthrough]];
        case 'T':
            [[fallthrough]];
        case 't':
            [[fallthrough]];
        case 'Y':
            [[fallthrough]];
        case 'y':
            value = true;
            break;
        case '0':
            [[fallthrough]];
        case 'F':
            [[fallthrough]];
        case 'f':
            [[fallthrough]];
        case 'N':
            [[fallthrough]];
        case 'n':
            value = false;
            break;
        }
    }

    if (false == valid) {
        log<Verbosity::error>("Invalid value for environment variable : %s, expected 1/0, got : %s", name.data(), envStr);
    }
    return value;
}

int64_t getCalEnvI64(std::string_view name, int64_t defaultValue) {
    auto envStr = getCalEnv(name);
    if (nullptr == envStr) {
        return defaultValue;
    }
    return atoll(envStr);
}

void *Heap::alloc(size_t sizeInBytes, size_t alignment) {
    if (this->getSizeLeft() < sizeInBytes) {
        return nullptr;
    }

    void *addr = nullptr;
    if (vma.getSubRanges().empty()) {
        addr = vma.getBoundingRange().base();
    } else {
        addr = vma.getSubRanges().rbegin()->getBoundingRange().rightBound();
    }

    addr = Cal::Utils::alignUp(addr, alignment);

    if (false == vma.getBoundingRange().contains({addr, sizeInBytes})) {
        if (Cal::Utils::alignUp(vma.getSubRanges().begin()->getBoundingRange().start, alignment) - vma.getBoundingRange().start >= sizeInBytes) {
            addr = Cal::Utils::alignUp(vma.getBoundingRange().base(), alignment);
        } else {
            addr = nullptr;
            auto prev = vma.getSubRanges().begin();
            auto it = prev + 1;
            while (it != vma.getSubRanges().end()) {
                if (Cal::Utils::alignUp(prev->getBoundingRange().end, alignment) - it->getBoundingRange().start >= sizeInBytes) {
                    addr = Cal::Utils::alignUp(prev->getBoundingRange().rightBound(), alignment);
                    break;
                }
                prev = it;
                ++it;
            }
            if (nullptr == addr) {
                log<Verbosity::debug>("Failed to allocate from heap");
            }
        }
    }

    commitRange({addr, sizeInBytes});
    return addr;
}

void Heap::free(void *addr) {
    auto range = vma.findSubRange({addr});
    if (nullptr == range) {
        log<Verbosity::error>("Attempted to free non-allocated range");
        return;
    }

    freeRange(range->getBoundingRange());
}

std::string getPathForTempFiles() {
    return calTempFilesDefaultPath.data() + std::to_string(geteuid()) + "/"s;
}

} // namespace Utils
} // namespace Cal
