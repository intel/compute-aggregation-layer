/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "gtest/gtest.h"
#include "test/mocks/artificial_events_manager_mock.h"
#include "test/mocks/log_mock.h"
#include "test/mocks/ongoing_hostptr_copies_manager_mock.h"

#include <cstdint>

using Cal::Mocks::MockArtificialEventsManager;
using Cal::Mocks::MockOngoingHostptrCopiesManager;

namespace Cal::Test::LevelZero::Service {

TEST(OngoingHostptrCopiesManagerTest, GivenEmptyManagerWhenRegisteringOngoingCopiesThenInternalContainerIsUpdatedWithValidRegistrationData) {
    const auto firstCommandList = reinterpret_cast<ze_command_list_handle_t>(0x7788);
    const auto firstAssociatedEvent = reinterpret_cast<ze_event_handle_t>(0x1234);
    const auto firstDestination = reinterpret_cast<void *>(0x5678);
    const size_t firstDestinationSize{256u};

    const auto secondCommandList = reinterpret_cast<ze_command_list_handle_t>(0x8800);
    const auto secondAssociatedEvent = reinterpret_cast<ze_event_handle_t>(0x2345);
    const auto secondDestination = reinterpret_cast<void *>(0x6789);
    const size_t secondDestinationSize{512u};

    // 0. Given.
    MockOngoingHostptrCopiesManager copiesManager{};
    ASSERT_TRUE(copiesManager.ongoingOperations.empty());

    // 1. When.
    copiesManager.registerCopyOperation(firstCommandList, firstAssociatedEvent, firstDestination, firstDestinationSize, true);
    copiesManager.registerCopyOperation(secondCommandList, secondAssociatedEvent, secondDestination, secondDestinationSize, false);

    // 2. Then.
    ASSERT_EQ(2u, copiesManager.ongoingOperations.size());

    EXPECT_EQ(firstCommandList, copiesManager.ongoingOperations[0].commandList);
    EXPECT_EQ(firstAssociatedEvent, copiesManager.ongoingOperations[0].associatedEvent);
    EXPECT_EQ(firstDestination, copiesManager.ongoingOperations[0].destination);
    EXPECT_EQ(firstDestinationSize, copiesManager.ongoingOperations[0].destinationSize);
    EXPECT_FALSE(copiesManager.ongoingOperations[0].isFinished);
    EXPECT_TRUE(copiesManager.ongoingOperations[0].canBeResubmitted);

    EXPECT_EQ(secondCommandList, copiesManager.ongoingOperations[1].commandList);
    EXPECT_EQ(secondAssociatedEvent, copiesManager.ongoingOperations[1].associatedEvent);
    EXPECT_EQ(secondDestination, copiesManager.ongoingOperations[1].destination);
    EXPECT_EQ(secondDestinationSize, copiesManager.ongoingOperations[1].destinationSize);
    EXPECT_FALSE(copiesManager.ongoingOperations[1].isFinished);
    EXPECT_FALSE(copiesManager.ongoingOperations[1].canBeResubmitted);
}

TEST(OngoingHostptrCopiesManagerTest, GivenManagerWithRegisteredCopiesThatCanBeResubmittedAndForOneOfThemEventIsFinishedWhenAcquiringFinishedCopiesThenTheyArePreservedAndReturned) {
    const auto firstCommandList = reinterpret_cast<ze_command_list_handle_t>(0x7788);
    const auto firstAssociatedEvent = reinterpret_cast<ze_event_handle_t>(0x1234);
    const auto firstDestination = reinterpret_cast<void *>(0x5678);
    const size_t firstDestinationSize{256u};

    const auto secondCommandList = reinterpret_cast<ze_command_list_handle_t>(0x8800);
    const auto secondAssociatedEvent = reinterpret_cast<ze_event_handle_t>(0x2345);
    const auto secondDestination = reinterpret_cast<void *>(0x6789);
    const size_t secondDestinationSize{512u};

    // 0. Given.
    MockOngoingHostptrCopiesManager copiesManager{};

    auto &firstRegisteredEntry = copiesManager.ongoingOperations.emplace_back();
    firstRegisteredEntry.commandList = firstCommandList;
    firstRegisteredEntry.associatedEvent = firstAssociatedEvent;
    firstRegisteredEntry.destination = firstDestination;
    firstRegisteredEntry.destinationSize = firstDestinationSize;
    firstRegisteredEntry.canBeResubmitted = true;
    firstRegisteredEntry.isFinished = true;

    auto &secondRegisteredEntry = copiesManager.ongoingOperations.emplace_back();
    secondRegisteredEntry.commandList = secondCommandList;
    secondRegisteredEntry.associatedEvent = secondAssociatedEvent;
    secondRegisteredEntry.destination = secondDestination;
    secondRegisteredEntry.destinationSize = secondDestinationSize;
    secondRegisteredEntry.canBeResubmitted = true;
    secondRegisteredEntry.isFinished = false;

    ASSERT_EQ(0u, copiesManager.operationsForResubmit.size());

    // 1. When.
    MockArtificialEventsManager eventsManagerMock{};
    eventsManagerMock.callBaseResetObtainedEvent = false;
    eventsManagerMock.callBaseReturnObtainedEvent = false;

    std::vector<Cal::Utils::AddressRange> finishedCopies;
    copiesManager.acquireFinishedCopies(eventsManagerMock, finishedCopies);

    // 2. Then.
    EXPECT_EQ(1u, eventsManagerMock.resetObtainedEventCallsCount);
    EXPECT_EQ(0u, eventsManagerMock.returnObtainedEventCallsCount);

    ASSERT_EQ(1u, finishedCopies.size());
    EXPECT_EQ(firstDestination, finishedCopies[0].base());
    EXPECT_EQ(firstDestinationSize, finishedCopies[0].size());

    ASSERT_EQ(1u, copiesManager.ongoingOperations.size());
    EXPECT_EQ(secondDestination, copiesManager.ongoingOperations[0].destination);
    EXPECT_EQ(secondDestinationSize, copiesManager.ongoingOperations[0].destinationSize);
    EXPECT_FALSE(copiesManager.ongoingOperations[0].isFinished);

    ASSERT_EQ(1u, copiesManager.operationsForResubmit.size());
    ASSERT_EQ(1u, copiesManager.operationsForResubmit.count(firstCommandList));

    auto &preservedOperations = copiesManager.operationsForResubmit[firstCommandList];
    ASSERT_EQ(1u, preservedOperations.size());

    EXPECT_EQ(firstAssociatedEvent, preservedOperations[0].associatedEvent);
    EXPECT_EQ(firstDestination, preservedOperations[0].destination);
    EXPECT_EQ(firstDestinationSize, preservedOperations[0].destinationSize);
}

TEST(OngoingHostptrCopiesManagerTest, GivenManagerWithRegisteredCopiesThatCannotBeResubmittedAndForOneOfThemEventIsFinishedWhenAcquiringFinishedCopiesThenTheyAreNotPreservedButAreReturned) {
    const auto firstCommandList = reinterpret_cast<ze_command_list_handle_t>(0x7788);
    const auto firstAssociatedEvent = reinterpret_cast<ze_event_handle_t>(0x1234);
    const auto firstDestination = reinterpret_cast<void *>(0x5678);
    const size_t firstDestinationSize{256u};

    const auto secondCommandList = reinterpret_cast<ze_command_list_handle_t>(0x8800);
    const auto secondAssociatedEvent = reinterpret_cast<ze_event_handle_t>(0x2345);
    const auto secondDestination = reinterpret_cast<void *>(0x6789);
    const size_t secondDestinationSize{512u};

    // 0. Given.
    MockOngoingHostptrCopiesManager copiesManager{};

    auto &firstRegisteredEntry = copiesManager.ongoingOperations.emplace_back();
    firstRegisteredEntry.commandList = firstCommandList;
    firstRegisteredEntry.associatedEvent = firstAssociatedEvent;
    firstRegisteredEntry.destination = firstDestination;
    firstRegisteredEntry.destinationSize = firstDestinationSize;
    firstRegisteredEntry.canBeResubmitted = false;
    firstRegisteredEntry.isFinished = true;

    auto &secondRegisteredEntry = copiesManager.ongoingOperations.emplace_back();
    secondRegisteredEntry.commandList = secondCommandList;
    secondRegisteredEntry.associatedEvent = secondAssociatedEvent;
    secondRegisteredEntry.destination = secondDestination;
    secondRegisteredEntry.destinationSize = secondDestinationSize;
    secondRegisteredEntry.canBeResubmitted = false;
    secondRegisteredEntry.isFinished = false;

    ASSERT_EQ(0u, copiesManager.operationsForResubmit.size());

    // 1. When.
    MockArtificialEventsManager eventsManagerMock{};
    eventsManagerMock.callBaseResetObtainedEvent = false;
    eventsManagerMock.callBaseReturnObtainedEvent = false;

    std::vector<Cal::Utils::AddressRange> finishedCopies;
    copiesManager.acquireFinishedCopies(eventsManagerMock, finishedCopies);

    // 2. Then.
    EXPECT_EQ(0u, eventsManagerMock.resetObtainedEventCallsCount);
    EXPECT_EQ(1u, eventsManagerMock.returnObtainedEventCallsCount);

    ASSERT_EQ(1u, finishedCopies.size());
    EXPECT_EQ(firstDestination, finishedCopies[0].base());
    EXPECT_EQ(firstDestinationSize, finishedCopies[0].size());

    ASSERT_EQ(1u, copiesManager.ongoingOperations.size());
    EXPECT_EQ(secondDestination, copiesManager.ongoingOperations[0].destination);
    EXPECT_EQ(secondDestinationSize, copiesManager.ongoingOperations[0].destinationSize);
    EXPECT_FALSE(copiesManager.ongoingOperations[0].isFinished);

    ASSERT_EQ(0u, copiesManager.operationsForResubmit.size());
}

TEST(OngoingHostptrCopiesManagerTest, GivenManagerAndNoPreservedOperationsForCommandListWhenTryingToResubmitCommandListThenNothingHappens) {
    // 0. Given.
    MockOngoingHostptrCopiesManager copiesManager{};

    ASSERT_TRUE(copiesManager.ongoingOperations.empty());
    ASSERT_TRUE(copiesManager.operationsForResubmit.empty());

    // 1. When.
    const auto commandList = reinterpret_cast<ze_command_list_handle_t>(0x7788);
    copiesManager.resubmitOperationsOfCommandList(commandList);

    // 2. Then.
    ASSERT_TRUE(copiesManager.ongoingOperations.empty());
    ASSERT_TRUE(copiesManager.operationsForResubmit.empty());
}

TEST(OngoingHostptrCopiesManagerTest, GivenManagerAndPreservedOperationsForCommandListWhenTryingToResubmitCommandListThenTheyAreSetToNotFinishedAndMovedToOngoingOperations) {
    const auto commandList = reinterpret_cast<ze_command_list_handle_t>(0x7788);
    const auto associatedEvent = reinterpret_cast<ze_event_handle_t>(0x1234);
    const auto destination = reinterpret_cast<void *>(0x5678);
    const size_t destinationSize{256u};

    // 0. Given.
    MockOngoingHostptrCopiesManager copiesManager{};
    ASSERT_TRUE(copiesManager.ongoingOperations.empty());

    auto &firstPreservedOperation = copiesManager.operationsForResubmit[commandList].emplace_back();
    firstPreservedOperation.commandList = commandList;
    firstPreservedOperation.associatedEvent = associatedEvent;
    firstPreservedOperation.destination = destination;
    firstPreservedOperation.destinationSize = destinationSize;
    firstPreservedOperation.canBeResubmitted = true;
    firstPreservedOperation.isFinished = true;

    // 1. When.
    copiesManager.resubmitOperationsOfCommandList(commandList);

    // 2. Then.
    ASSERT_FALSE(copiesManager.ongoingOperations.empty());
    EXPECT_EQ(1u, copiesManager.ongoingOperations.size());

    EXPECT_EQ(commandList, copiesManager.ongoingOperations[0].commandList);
    EXPECT_EQ(associatedEvent, copiesManager.ongoingOperations[0].associatedEvent);
    EXPECT_EQ(destination, copiesManager.ongoingOperations[0].destination);
    EXPECT_EQ(destinationSize, copiesManager.ongoingOperations[0].destinationSize);
    EXPECT_TRUE(copiesManager.ongoingOperations[0].canBeResubmitted);
    EXPECT_FALSE(copiesManager.ongoingOperations[0].isFinished);

    ASSERT_EQ(1u, copiesManager.operationsForResubmit.count(commandList));
    EXPECT_TRUE(copiesManager.operationsForResubmit[commandList].empty());
}

TEST(OngoingHostptrCopiesManagerTest, GivenManagerAndPreservedOperationsForCommandListWhenTryingToFreeAnotherCommandListThenNothingHappens) {
    const auto anotherCommandList = reinterpret_cast<ze_command_list_handle_t>(0x9988);
    const auto commandList = reinterpret_cast<ze_command_list_handle_t>(0x7788);
    const auto associatedEvent = reinterpret_cast<ze_event_handle_t>(0x1234);
    const auto anotherAssociatedEvent = reinterpret_cast<ze_event_handle_t>(0x7234);
    const auto destination = reinterpret_cast<void *>(0x5678);
    const size_t destinationSize{256u};

    // 0. Given.
    MockOngoingHostptrCopiesManager copiesManager{};

    auto &firstRegisteredEntry = copiesManager.ongoingOperations.emplace_back();
    firstRegisteredEntry.commandList = commandList;
    firstRegisteredEntry.associatedEvent = associatedEvent;
    firstRegisteredEntry.destination = destination;
    firstRegisteredEntry.destinationSize = destinationSize;
    firstRegisteredEntry.canBeResubmitted = true;
    firstRegisteredEntry.isFinished = true;

    auto &firstPreservedOperation = copiesManager.operationsForResubmit[commandList].emplace_back();
    firstPreservedOperation.commandList = commandList;
    firstPreservedOperation.associatedEvent = anotherAssociatedEvent;
    firstPreservedOperation.destination = destination;
    firstPreservedOperation.destinationSize = destinationSize;
    firstPreservedOperation.canBeResubmitted = true;
    firstPreservedOperation.isFinished = true;

    // 1. When.
    MockArtificialEventsManager eventsManagerMock{};
    eventsManagerMock.callBaseResetObtainedEvent = false;
    eventsManagerMock.callBaseReturnObtainedEvent = false;

    copiesManager.freeOperationsOfCommandList(anotherCommandList, eventsManagerMock);

    // 2. Then.
    EXPECT_EQ(0u, eventsManagerMock.resetObtainedEventCallsCount);
    EXPECT_EQ(0u, eventsManagerMock.returnObtainedEventCallsCount);

    ASSERT_EQ(1u, copiesManager.ongoingOperations.size());
    ASSERT_EQ(1u, copiesManager.operationsForResubmit.count(commandList));
    EXPECT_EQ(1u, copiesManager.operationsForResubmit[commandList].size());
}

TEST(OngoingHostptrCopiesManagerTest, GivenManagerAndPreservedOperationsForCommandListWhenTryingToFreeThisCommandListThenOperationsAreFreed) {
    const auto commandList = reinterpret_cast<ze_command_list_handle_t>(0x7788);
    const auto associatedEvent = reinterpret_cast<ze_event_handle_t>(0x1234);
    const auto anotherAssociatedEvent = reinterpret_cast<ze_event_handle_t>(0x7234);
    const auto destination = reinterpret_cast<void *>(0x5678);
    const size_t destinationSize{256u};

    // 0. Given.
    MockOngoingHostptrCopiesManager copiesManager{};

    auto &firstRegisteredEntry = copiesManager.ongoingOperations.emplace_back();
    firstRegisteredEntry.commandList = commandList;
    firstRegisteredEntry.associatedEvent = associatedEvent;
    firstRegisteredEntry.destination = destination;
    firstRegisteredEntry.destinationSize = destinationSize;
    firstRegisteredEntry.canBeResubmitted = true;
    firstRegisteredEntry.isFinished = true;

    auto &firstPreservedOperation = copiesManager.operationsForResubmit[commandList].emplace_back();
    firstPreservedOperation.commandList = commandList;
    firstPreservedOperation.associatedEvent = anotherAssociatedEvent;
    firstPreservedOperation.destination = destination;
    firstPreservedOperation.destinationSize = destinationSize;
    firstPreservedOperation.canBeResubmitted = true;
    firstPreservedOperation.isFinished = true;

    // 1. When.
    MockArtificialEventsManager eventsManagerMock{};
    eventsManagerMock.callBaseResetObtainedEvent = false;
    eventsManagerMock.callBaseReturnObtainedEvent = false;

    copiesManager.freeOperationsOfCommandList(commandList, eventsManagerMock);

    // 2. Then.
    EXPECT_EQ(0u, eventsManagerMock.resetObtainedEventCallsCount);
    EXPECT_EQ(2u, eventsManagerMock.returnObtainedEventCallsCount);

    ASSERT_EQ(0u, copiesManager.ongoingOperations.size());
    ASSERT_EQ(0u, copiesManager.operationsForResubmit.count(commandList));
}

} // namespace Cal::Test::LevelZero::Service
