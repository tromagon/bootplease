// CommandMapTests.cpp : main project file.

#include "stdafx.h"

#include "CommandMapTests.h"
#include "events\EventDispatcher.h"
#include "commands\EventCommandMap.h"
#include "injection\Injector.h"

using namespace System;

const char* ExampleEvent::START_COMMAND_A = "ExampleEvent_INIT";
const char* ExampleEvent::START_COMMAND_B = "ExampleEvent_START_COMMAND_B";

void CommandA::Execute()
{
     Console::WriteLine(L"Command A executed");
}

void CommandB::Execute()
{
     Console::WriteLine(L"Command B executed");
}

int main(array<System::String ^> ^args)
{
    Console::WriteLine(L"Starting CommandMapTests");

    EventDispatcherPtr dispatcher = EventDispatcherPtr(new EventDispatcher());
    InjectorPtr injector = InjectorPtr(new Injector());

    EventCommandMap eventCommandMap(dispatcher, injector);

    eventCommandMap.Map<CommandA>(ExampleEvent::START_COMMAND_A);
    eventCommandMap.Map<CommandB>(ExampleEvent::START_COMMAND_B);

    ExampleEvent evt(ExampleEvent::START_COMMAND_A);
	dispatcher->Dispatch(evt);

    eventCommandMap.UnMap<CommandA>(ExampleEvent::START_COMMAND_A);

    //eventCommandMap.UnMap(ExampleEvent::INIT, &CommandFactory::GetExampleCommandA, commandFactory);


    //eventCommandMap.Map2(ExampleEvent::INIT);
    system("pause");

    return 0;
}
