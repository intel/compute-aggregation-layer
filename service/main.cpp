/*
 * Copyright (C) 2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "generated_shared_level_zero.h"
#include "generated_shared_ocl.h"
#include "include/cal.h"
#include "service/cochoreographer.h"
#include "service/service.h"
#include "shared/log.h"
#include "shared/utils.h"

#include <cstdio>
#include <cstring>
#include <getopt.h>
#include <string>

void printCalServiceHelp();
void printCalServiceVersion();
int printCalUnimplementedApiCalls(const char *arg);
std::string getFullExePathIfExists(const char *fileName);

constexpr option options[] = {
    {"persistent", no_argument, nullptr, 'p'},
    {"help", no_argument, nullptr, 'h'},
    {"version", no_argument, nullptr, 'v'},
    {"unimplemented", required_argument, nullptr, 'u'},
    {nullptr, 0, nullptr, 0}};

int main(int argc, const char *argv[]) {
    std::string choreographiesPath = ".";

    Cal::Service::ServiceConfig serviceConfig;
    bool isPersistentMode = false;

    int option;
    while ((option = getopt_long(argc, const_cast<char *const *>(argv), "+phvu:", options, nullptr)) != -1) {
        switch (option) {
        case 'p':
            isPersistentMode = true;
            break;
        case 'h':
            printCalServiceHelp();
            return 0;
        case 'v':
            printCalServiceVersion();
            return 0;
        case 'u':
            return printCalUnimplementedApiCalls(optarg);
        default:
            fprintf(stderr, "Use -h or --help to get help\n");
            return 1;
        }
    }

    if (argc == 1) {
        isPersistentMode = true;
    }

    if (isPersistentMode == false) {
        Cal::Service::ServiceConfig::RunnerConfig runner;

        runner.command = getFullExePathIfExists(argv[optind]);
        if (runner.command.empty()) {
            fprintf(stderr, "File %s does not exist\n", argv[optind]);
            return -1;
        }

        runner.args.assign(argv + optind, argv + argc);
        runner.args.push_back(nullptr);

        serviceConfig.runner = runner;
        serviceConfig.listener.socketPath += "runner/" + std::to_string(getpid()) + "/";
        Cal::Sys::setenv(calUseLoggerNameEnvName.data(), "1", 1);
    }

    std::filesystem::create_directories(serviceConfig.listener.socketPath.c_str());
    serviceConfig.listener.socketPath.append("socket");

    if (isPersistentMode == false) {
        Cal::Sys::setenv(calListenerSocketPathEnvName.data(), serviceConfig.listener.socketPath.c_str(), 1);
    }

    Cal::Utils::initDynamicVerbosity();
    auto chrLib = Cal::Service::ChoreographyLibrary::create();
    if (Cal::Utils::getCalEnvFlag(calEnableAilEnvName)) {
        chrLib->load(".");
    }
    Cal::Service::Provider service(std::move(chrLib), std::move(serviceConfig));
    return service.run(isPersistentMode);
}

void printCalServiceHelp() {
    const char *buildMode;
#ifdef NDEBUG
    buildMode = "RELEASE";
#else
    buildMode = "DEBUG";
#endif
    printf("Compute Aggregation Layer for oneAPI Level Zero and OpenCL(TM) Applications service built in %s mode.\n\n", buildMode);
    printf("Synopsis:\n");
    printf("    calrun [options] [command] [command_options]\n\n");
    printf("Available command line options:\n");
    printf("   -h  --help                 Show this help\n");
    printf("   -v  --version              Show version\n");
    printf("   -p  --persistent           Start cal in server mode, that applications can connect to. Running CAL without parameters is identical to running in persistent mode.\n");
    printf("   -u  --unimplemented ocl    List all OCL Api calls that are currently missing in the implementations\n");
    printf("                       l0     List all Level Zero Api calls that are currently missing in the implementations\n");

    printf("\n");

    printf("Available environment variables:\n");
    bool bechmarkingAvailable = Cal::Utils::minStaticVebosity <= Verbosity::performance;
    printf("%s: 1/0 to enable/disable benchmarking logs%s\n", calBenchmarkEnvName.data(), bechmarkingAvailable ? "" : " (NOT AVAILABLE - try different build mode if needed)");

    auto allVerb = Cal::Utils::getListOfAllExistingVerbosityLevels();
    printf("%s: %s (all case sensitive) to set max verbosity level", calVerbosityEnvName.data(), allVerb.c_str());
    auto availableVerb = Cal::Utils::getListOfAllAvailableVerbosityLevels();
    if (availableVerb != allVerb) {
        printf(" (AVAILABILITY WARNING: build was configured to support only: %s)", availableVerb.c_str());
    }
    printf("\n");
    printf("%s: to set default RPC channel size (in MB), builtin default is: %dMB\n", calDefaultRpcChannelSizeEnvName.data(), Cal::Service::Provider::staticDefaultRpcMessageChannelSizeMB);
    printf("\n");
    printf("Default builtin max verbosity level in this build: %s\n", Cal::Utils::Log::to_cstring(Cal::Utils::maxDynamicVerbosity));
    printf("Default builtin benchmarking mode: %d\n", Cal::Utils::minDynamicVerbosity <= Verbosity::performance);
    printf("\n");
    printf("In case of errors with message that service/client failed to open/create shmem (shared memory), please try to increase limit of open files per process, e.g. with following linux command:\n");
    printf("    user soft nofile 16384\n");
}

int printCalUnimplementedApiCalls(const char *arg) {
    auto apiName = Cal::Utils::toLower(arg);
    if ("ocl" == apiName) {
        auto unimplementedApis = Cal::Service::Apis::Ocl::getListOfUnimplementedFunctionNames();
        printf("Unsupported API calls for OCL : \n");
        for (const auto &f : unimplementedApis) {
            printf("  %s\n", f.c_str());
        }
        return 0;
    } else if ("l0" == apiName) {
        auto unimplementedApisL0 = Cal::Service::Apis::LevelZero::getListOfUnimplementedFunctionNames();
        printf("Unsupported API calls for L0: \n");
        for (const auto &f : unimplementedApisL0) {
            printf("  %s\n", f.c_str());
        }
        return 0;
    } else {
        printf("Unknown API name %s, expected (case insensitive): ocl, l0\n", arg);
        return 1;
    }
}

std::string getFullExePathIfExists(const char *fileName) {
    if (std::filesystem::exists(fileName)) {
        return std::string(fileName);
    }

    std::string tmp;
    std::istringstream ss(getenv("PATH"));
    while (std::getline(ss, tmp, ':')) {
        if (std::filesystem::exists(tmp + "/" + fileName)) {
            return std::string(tmp + "/" + fileName);
        }
    }

    return std::string();
}

void printCalServiceVersion() {
    printf("%s", NAME_TO_STR(CAL_REVISION));
#ifndef NDEBUG
    printf("[DEBUG]");
#endif
    printf("\n");
    printf("Built on : %s\n", NAME_TO_STR(CAL_BUILD_SYSTEM));
}
