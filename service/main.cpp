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
#include <functional>
#include <getopt.h>
#include <string>
#include <sys/file.h>

void printCalServiceHelp();
void printCalServiceVersion();
int printCalUnimplementedApiCalls(const char *arg);
std::string getFullExePathIfExists(const char *fileName);

constexpr option options[] = {
    {"persistent", no_argument, nullptr, 'p'},
    {"shared", no_argument, nullptr, 's'},
    {"help", no_argument, nullptr, 'h'},
    {"version", no_argument, nullptr, 'v'},
    {"unimplemented", required_argument, nullptr, 'u'},
    {nullptr, 0, nullptr, 0}};

int main(int argc, const char *argv[]) {
    std::string choreographiesPath = ".";

    Cal::Service::ServiceConfig serviceConfig;
    bool isExplicitPersistentMode = false;
    bool isExplicitSharedRunnerMode = false;

    int option;
    while ((option = getopt_long(argc, const_cast<char *const *>(argv), "+pshvu:", options, nullptr)) != -1) {
        switch (option) {
        case 'p':
            isExplicitPersistentMode = true;
            break;
        case 's':
            isExplicitSharedRunnerMode = true;
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

    if (isExplicitPersistentMode && isExplicitSharedRunnerMode) {
        fprintf(stderr, "Calrun cannot be in both persistent (-p) and shared_runner (-s) mode\n");
        return 1;
    }

    if ((argc == 1) || isExplicitPersistentMode) {
        serviceConfig.mode = Cal::Service::ServiceConfig::Mode::persistent;
    } else {
        serviceConfig.mode = Cal::Service::ServiceConfig::Mode::runner;
    }

    if (isExplicitSharedRunnerMode) {
        serviceConfig.mode = Cal::Service::ServiceConfig::Mode::sharedRunner;
    }

    if (serviceConfig.isAnyRunnerMode()) {
        Cal::Service::ServiceConfig::RunnerConfig runner;

        runner.command = getFullExePathIfExists(argv[optind]);
        if (runner.command.empty()) {
            fprintf(stderr, "File %s does not exist\n", argv[optind]);
            return -1;
        }

        runner.args.assign(argv + optind, argv + argc);
        runner.args.push_back(nullptr);

        serviceConfig.runner = runner;
        Cal::Sys::setenv(calUseLoggerNameEnvName.data(), "1", 1);
        if (Cal::Service::ServiceConfig::Mode::sharedRunner == serviceConfig.mode) {
            std::string commandLine = Cal::Utils::concatenate(&argv[optind], &argv[argc], "");
            size_t commandLineHash = std::hash<std::string>()(commandLine);
            serviceConfig.listener.socketPath += "shared_runner/" + std::to_string(commandLineHash) + "/";
        } else {
            serviceConfig.listener.socketPath += "runner/" + std::to_string(getpid()) + "/";
        }
    }

    std::filesystem::create_directories(serviceConfig.listener.socketPath.c_str());
    serviceConfig.listener.socketPath.append("socket");

    if (serviceConfig.isAnyRunnerMode()) {
        Cal::Sys::setenv(calListenerSocketPathEnvName.data(), serviceConfig.listener.socketPath.c_str(), 1);
    }

    Cal::Utils::initDynamicVerbosity();

    std::unique_ptr<Cal::Ipc::Connection> existingSharedCalConnection = nullptr;
    if (Cal::Service::ServiceConfig::Mode::sharedRunner == serviceConfig.mode) {
        auto connectionFactory = std::make_unique<Cal::Ipc::NamedSocketClientConnectionFactory>();
        existingSharedCalConnection = connectionFactory->connect(serviceConfig.listener.socketPath.c_str());
        if (existingSharedCalConnection && (false == existingSharedCalConnection->isAlive())) {
            log<Verbosity::debug>("Existing service is not responsive\n");
            existingSharedCalConnection.reset();
        }
        if (nullptr == existingSharedCalConnection) {
            auto lockPath = serviceConfig.listener.socketPath;
            lockPath = serviceConfig.listener.socketPath + "_lock";
            serviceConfig.sharedRunnerLockFd = open(lockPath.c_str(), O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
            if (-1 == serviceConfig.sharedRunnerLockFd) {
                log<Verbosity::critical>("Could not open %s\n", lockPath.c_str());
                return -1;
            }
            if (0 != flock(serviceConfig.sharedRunnerLockFd, LOCK_EX)) {
                log<Verbosity::critical>("Could not lock %s\n", lockPath.c_str());
                return -1;
            }
            existingSharedCalConnection = connectionFactory->connect(serviceConfig.listener.socketPath.c_str());
            if (existingSharedCalConnection && (false == existingSharedCalConnection->isAlive())) {
                log<Verbosity::debug>("Existing service is not responsive\n");
                existingSharedCalConnection.reset();
            }
            if (nullptr != existingSharedCalConnection) {
                if ((0 != flock(serviceConfig.sharedRunnerLockFd, LOCK_UN)) || (0 != close(serviceConfig.sharedRunnerLockFd))) {
                    log<Verbosity::critical>("Could not unlock %s\n", lockPath.c_str());
                }
            }
        }
    }

    if (existingSharedCalConnection) {
        log<Verbosity::debug>("Establishing pass-through connection");
        Cal::Service::checkForRequiredFiles();
        Cal::Service::spawnProcessAndWait(serviceConfig.runner.value());
        return 0;
    } else { // new service
        log<Verbosity::debug>("Establishing new service instance");
        auto chrLib = Cal::Service::ChoreographyLibrary::create();
        if (Cal::Utils::getCalEnvFlag(calEnableAilEnvName)) {
            chrLib->load(".");
        }
        Cal::Service::Provider service(std::move(chrLib), std::move(serviceConfig));
        return service.run();
    }
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
    printf("   -s  --shared               Start cal in shared runner mode. In this mode, identical parallel workload invocations will share a single CAL service which will be started on demand and kept alive no longer than needed.\n");
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
