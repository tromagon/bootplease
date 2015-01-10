#include "tests.h"

#include <iostream>

using namespace std;

const char* ExampleEvent::INIT = "ExampleEvent_INIT";
const char* ExampleEvent::COMPLETE = "ExampleEvent_COMPLETE";
const char* ExampleEvent::SECOND_COMPLETE = "ExampleEvent_SECOND_COMPLETE";

EventDispatcherTest::EventDispatcherTest() : dispatcher(new EventDispatcher())
{
	cout << "----------- Start EventDispatcher Test" << endl;

	int i = dispatcher->AddListener(ExampleEvent::INIT, &EventDispatcherTest::hello, *this);
	dispatcher->AddListener(ExampleEvent::INIT, &EventDispatcherTest::hello2, *this);
	ExampleEvent evt(ExampleEvent::INIT);
	dispatcher->Dispatch(evt);
	dispatcher->RemoveListener(i);
	dispatcher->RemoveListener(ExampleEvent::INIT, &EventDispatcherTest::hello2, *this);
	dispatcher->Dispatch(evt);

	cout << "----------- End EventDispatcher Test" << endl;
}

EventDispatcherTest::~EventDispatcherTest()
{
	delete dispatcher;
}

void EventDispatcherTest::hello(Event& evt)
{
	std::cout << "Hello " << evt.GetType() << std::endl;
}

void EventDispatcherTest::hello2(Event& evt)
{
	std::cout << "Hello2 " << evt.GetType() << std::endl;
}