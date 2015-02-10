// CommandMapTests.cpp : main project file.

#include "stdafx.h"

#include "CommandMapTests.h"
#include "events\EventDispatcher.h"
#include "commands\EventCommandMap.h"
#include "commands\DirectCommandMap.h"
#include "injection\Injector.h"

using namespace System;

const char* ExampleEvent::START_COMMAND_A = "ExampleEvent_START_COMMAND_A";
const char* ExampleEvent::START_COMMAND_B = "ExampleEvent_START_COMMAND_B";
const char* ExampleEvent::RELEASE_COMMAND_A = "ExampleEvent_RELEASE_COMMAND_A";

void CommandA::Execute()
{
     Console::WriteLine(L"Command A executed");
     GetDispatcher()->AddListener(ExampleEvent::RELEASE_COMMAND_A, &CommandA::OnRelease, *this);

     Detain();

     Console::WriteLine(L"Command A detained");
}

void CommandA::OnRelease(const Event& event)
{
    Console::WriteLine(L"Command A released");

    GetDispatcher()->RemoveListener(ExampleEvent::RELEASE_COMMAND_A, &CommandA::OnRelease, *this);

    Release();
}

CommandA::~CommandA()
{
    Console::WriteLine(L"Command A Destroyed");
}

void CommandB::Execute()
{
     Console::WriteLine(L"Command B executed");
}

CommandB::~CommandB()
{
    Console::WriteLine(L"Command B Destroyed");
}

int main(array<System::String ^> ^args)
{
    Console::WriteLine(L"Starting EventCommandMap Tests");

    EventDispatcherPtr dispatcher = EventDispatcherPtr(new EventDispatcher());
    InjectorPtr injector = InjectorPtr(new Injector());

    EventCommandMap eventCommandMap(dispatcher, injector);
    eventCommandMap.Map<CommandA>(ExampleEvent::START_COMMAND_A);
    eventCommandMap.Map<CommandB>(ExampleEvent::START_COMMAND_B);

    ExampleEvent evt(ExampleEvent::START_COMMAND_A);
    dispatcher->Dispatch(evt);

    ExampleEvent evt2(ExampleEvent::RELEASE_COMMAND_A);
    dispatcher->Dispatch(evt2);

    ExampleEvent evt3(ExampleEvent::START_COMMAND_B);
    dispatcher->Dispatch(evt3);

    eventCommandMap.UnMap<CommandA>(ExampleEvent::START_COMMAND_A);

    Console::WriteLine(L"Starting DirectCommandMap Tests");

    DirectCommandMap directCommandMap(dispatcher, injector);
    directCommandMap.Map<CommandA>();
    directCommandMap.Map<CommandB>();
    directCommandMap.Execute();

    dispatcher->Dispatch(evt2);

    system("pause");

    return 0;
}
