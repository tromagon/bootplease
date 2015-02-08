// SequencerTests.cpp : main project file.

#include "stdafx.h"
#include "SequencerTests.h"
#include <iostream>
#include "Sequence.h"
#include "EventDispatcher.h"
#include "SequenceEvent.h"

using namespace System;

const char* ExampleEvent::INIT = "ExampleEvent_INIT";
const char* ExampleEvent::COMPLETE = "ExampleEvent_COMPLETE";
const char* ExampleEvent::SECOND_COMPLETE = "ExampleEvent_SECOND_COMPLETE";

EventDispatcherPtr dispatcher;

void A::methodA()
{
	Console::WriteLine(L"Method A called");
}

void A::methodB(const Event& evt)
{
	Console::WriteLine(L"Method B called");

	ExampleEvent completeEvent(ExampleEvent::COMPLETE);
	dispatcher->Dispatch(completeEvent);

	ExampleEvent secondCompleteEvent(ExampleEvent::SECOND_COMPLETE);
	dispatcher->Dispatch(secondCompleteEvent);
}

void A::methodC(const Event& evt)
{
	Console::WriteLine(L"Method C called");
}

void A::onSequenceStarted(const Event& evt)
{
	Console::WriteLine(L"Sequence Started");
}

void A::onSequenceStepComplete(const Event& evt)
{
	Console::WriteLine(L"SequenceStep Complete");
}

void A::onSequenceComplete(const Event& evt)
{
	Console::WriteLine(L"Sequence Complete");
}

int main(array<System::String ^> ^args)
{
	A a;

    dispatcher = EventDispatcherPtr(new EventDispatcher());
	dispatcher->AddListener(ExampleEvent::INIT, &A::methodB, a);

	Sequence sequence(dispatcher);
	sequence.AddListener(SequenceEvent::STARTED, &A::onSequenceStarted, a);
	sequence.AddListener(SequenceEvent::STEP_COMPLETE, &A::onSequenceStepComplete, a);
	sequence.AddListener(SequenceEvent::COMPLETE, &A::onSequenceComplete, a);

	sequence.Call(&A::methodA, a);
	const ExampleEvent evt(ExampleEvent::INIT);
	sequence.Dispatch(evt);

	sequence.WaitFor(ExampleEvent::COMPLETE, &A::methodC, a);
	sequence.WaitFor(ExampleEvent::SECOND_COMPLETE);
	sequence.Dispatch(evt);
	sequence.WaitFor(ExampleEvent::COMPLETE);
	sequence.WaitFor(ExampleEvent::SECOND_COMPLETE);

	sequence.Start();

	system("pause");
    return 0;
}
