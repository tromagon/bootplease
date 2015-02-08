// EventDispatcherTests.cpp : main project file.

#include "stdafx.h"
#include <iostream>
#include "events\EventDispatcher.h"
#include "EventDispatcherTests.h"

using namespace System;

const char* CustomEvent::INIT = "CustomEvent_INIT";

void EventReceiver::onEventReceived(const Event& evt)
{
    Console::WriteLine(L"Custom Event Received");
}

int main(array<System::String ^> ^args)
{
    Console::WriteLine(L"Starting EventDispatcherTests");

    EventReceiver receiver;
    EventDispatcher eventDispatcher;
    eventDispatcher.AddListener(CustomEvent::INIT, &EventReceiver::onEventReceived, receiver);
    eventDispatcher.Dispatch(CustomEvent(CustomEvent::INIT));
    eventDispatcher.RemoveListener(CustomEvent::INIT, &EventReceiver::onEventReceived, receiver);
    eventDispatcher.Dispatch(CustomEvent(CustomEvent::INIT));

    system("pause");
    return 0;
}
