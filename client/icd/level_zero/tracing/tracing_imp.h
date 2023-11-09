/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "client/icd/level_zero/tracing/tracing.h"

#include <atomic>
#include <chrono>
#include <level_zero/ze_api.h>
#include <level_zero/ze_ddi.h>
#include <list>
#include <mutex>
#include <vector>

extern ze_dditable_t l0Ddi;

namespace Cal::Client::Icd {

extern thread_local ze_bool_t tracingInProgress;
extern struct APITracerContextImp *pGlobalAPITracerContextImp;

typedef struct TracerArrayEntry {
    zet_core_callbacks_t corePrologues;
    zet_core_callbacks_t coreEpilogues;
    zet_device_handle_t hDevice;
    void *pUserData;
} tracer_array_entry_t;

typedef struct TracerArray {
    size_t tracerArrayCount;
    tracer_array_entry_t *tracerArrayEntries;
} tracer_array_t;

typedef enum tracingState {
    disabledState,        // tracing has never been enabled
    enabledState,         // tracing is enabled.
    disabledWaitingState, // tracing has been disabled, but not waited for
} tracingState_t;

struct APITracerImp : APITracer {
    ze_result_t destroyTracer(zet_tracer_exp_handle_t phTracer) override;
    ze_result_t setPrologues(zet_core_callbacks_t *pCoreCbs) override;
    ze_result_t setEpilogues(zet_core_callbacks_t *pCoreCbs) override;
    ze_result_t enableTracer(ze_bool_t enable) override;

    tracer_array_entry_t tracerFunctions{};
    tracingState_t tracingState = disabledState;

  private:
};

class ThreadPrivateTracerData {
  public:
    void clearThreadTracerDataOnList(void) { onList = false; }
    void removeThreadTracerDataFromList(void);
    bool testAndSetThreadTracerDataInitializedAndOnList(void);
    bool onList;
    bool isInitialized;
    ThreadPrivateTracerData();
    ~ThreadPrivateTracerData();

    std::atomic<tracer_array_t *> tracerArrayPointer;

  private:
    ThreadPrivateTracerData(const ThreadPrivateTracerData &);
    ThreadPrivateTracerData &operator=(const ThreadPrivateTracerData &);
};

struct APITracerContextImp : APITracerContext {
  public:
    APITracerContextImp() {
        activeTracerArray.store(&emptyTracerArray, std::memory_order_relaxed);
    };

    ~APITracerContextImp() override;

    static void apiTracingEnable(ze_init_flag_t flag);

    void *getActiveTracersList() override;
    void releaseActivetracersList() override;

    ze_result_t enableTracingImp(struct APITracerImp *newTracer, ze_bool_t enable);
    ze_result_t finalizeDisableImpTracingWait(struct APITracerImp *oldTracer);

    bool isTracingEnabled();

    void addThreadTracerDataToList(ThreadPrivateTracerData *threadDataP);
    void removeThreadTracerDataFromList(ThreadPrivateTracerData *threadDataP);

  private:
    std::mutex traceTableMutex;
    tracer_array_t emptyTracerArray = {0, NULL};
    std::atomic<tracer_array_t *> activeTracerArray;

    //
    // a list of tracer arrays that were once active, but
    // have been replaced by a new active array.  These
    // once-active tracer arrays may continue for some time
    // to have references to them among the per-thread
    // tracer array pointers.
    //
    std::list<tracer_array_t *> retiringTracerArrayList;

    std::list<struct APITracerImp *> enabledTracerImpList;

    ze_bool_t testForTracerArrayReferences(tracer_array_t *tracerArray);
    size_t testAndFreeRetiredTracers();
    size_t updateTracerArrays();

    std::list<ThreadPrivateTracerData *> threadTracerDataList;
    std::mutex threadTracerDataListMutex;
};

extern thread_local ThreadPrivateTracerData myThreadPrivateTracerData;

template <class T>
class APITracerCallbackStateImp {
  public:
    T currentApiCallback;
    void *pUserData;
};

template <class T>
class APITracerCallbackDataImp {
  public:
    T apiOrdinal = {};
    std::vector<Cal::Client::Icd::APITracerCallbackStateImp<T>> prologCallbacks;
    std::vector<Cal::Client::Icd::APITracerCallbackStateImp<T>> epilogCallbacks;
};

#define ZE_HANDLE_TRACER_RECURSION(ze_api_ptr, ...) \
    do {                                            \
        if (Cal::Client::Icd::tracingInProgress) {  \
            return ze_api_ptr(__VA_ARGS__);         \
        }                                           \
        Cal::Client::Icd::tracingInProgress = 1;    \
    } while (0)

#define ZE_GEN_TRACER_ARRAY_ENTRY(callbackPtr, tracerArray, tracerArrayIndex, callbackType, callbackCategory, callbackFunction) \
    do {                                                                                                                        \
        callbackPtr = tracerArray->tracerArrayEntries[tracerArrayIndex].callbackType.callbackCategory.callbackFunction;         \
    } while (0)

#define ZE_GEN_PER_API_CALLBACK_STATE(perApiCallbackData, tracerType, callbackCategory, callbackFunctionType)                               \
    Cal::Client::Icd::tracer_array_t *currentTracerArray;                                                                                   \
    currentTracerArray = (Cal::Client::Icd::tracer_array_t *)Cal::Client::Icd::pGlobalAPITracerContextImp->getActiveTracersList();          \
    if (currentTracerArray) {                                                                                                               \
        for (size_t i = 0; i < currentTracerArray->tracerArrayCount; i++) {                                                                 \
            tracerType prologueCallbackPtr;                                                                                                 \
            tracerType epilogue_callback_ptr;                                                                                               \
            ZE_GEN_TRACER_ARRAY_ENTRY(prologueCallbackPtr, currentTracerArray, i, corePrologues, callbackCategory, callbackFunctionType);   \
            ZE_GEN_TRACER_ARRAY_ENTRY(epilogue_callback_ptr, currentTracerArray, i, coreEpilogues, callbackCategory, callbackFunctionType); \
                                                                                                                                            \
            Cal::Client::Icd::APITracerCallbackStateImp<tracerType> prologCallback;                                                         \
            prologCallback.currentApiCallback = prologueCallbackPtr;                                                                        \
            prologCallback.pUserData = currentTracerArray->tracerArrayEntries[i].pUserData;                                                 \
            perApiCallbackData.prologCallbacks.push_back(prologCallback);                                                                   \
                                                                                                                                            \
            Cal::Client::Icd::APITracerCallbackStateImp<tracerType> epilogCallback;                                                         \
            epilogCallback.currentApiCallback = epilogue_callback_ptr;                                                                      \
            epilogCallback.pUserData = currentTracerArray->tracerArrayEntries[i].pUserData;                                                 \
            perApiCallbackData.epilogCallbacks.push_back(epilogCallback);                                                                   \
        }                                                                                                                                   \
    }

template <typename TFunction_pointer, typename TParams, typename TTracer, typename TTracerPrologCallbacks, typename TTracerEpilogCallbacks, typename... Args>
ze_result_t apiTracerWrapperImp(TFunction_pointer zeApiPtr,
                                TParams paramsStruct,
                                TTracer apiOrdinal,
                                TTracerPrologCallbacks prologCallbacks,
                                TTracerEpilogCallbacks epilogCallbacks,
                                Args &&...args) {
    ze_result_t ret = ZE_RESULT_SUCCESS;
    std::vector<APITracerCallbackStateImp<TTracer>> *callbacksPrologs = &prologCallbacks;

    std::vector<void *> ppTracerInstanceUserData;
    ppTracerInstanceUserData.resize(callbacksPrologs->size());

    for (size_t i = 0; i < callbacksPrologs->size(); i++) {
        if (callbacksPrologs->at(i).currentApiCallback != nullptr)
            callbacksPrologs->at(i).currentApiCallback(paramsStruct, ret, callbacksPrologs->at(i).pUserData, &ppTracerInstanceUserData[i]);
    }
    ret = zeApiPtr(args...);
    std::vector<APITracerCallbackStateImp<TTracer>> *callbacksEpilogs = &epilogCallbacks;
    for (size_t i = 0; i < callbacksEpilogs->size(); i++) {
        if (callbacksEpilogs->at(i).currentApiCallback != nullptr)
            callbacksEpilogs->at(i).currentApiCallback(paramsStruct, ret, callbacksEpilogs->at(i).pUserData, &ppTracerInstanceUserData[i]);
    }
    Cal::Client::Icd::tracingInProgress = 0;
    Cal::Client::Icd::pGlobalAPITracerContextImp->releaseActivetracersList();
    return ret;
}

} // namespace Cal::Client::Icd
