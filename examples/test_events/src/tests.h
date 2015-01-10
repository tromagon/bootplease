#ifndef _TESTS_H_
#define _TESTS_H_

#include "EventDispatcher.h"

class ExampleEvent : public Event
{
public:
	static const char* INIT;
	static const char* COMPLETE;
	static const char* SECOND_COMPLETE;

public:
	explicit ExampleEvent(const char* type) : Event(type) {}
	virtual ~ExampleEvent() {}

};

class EventDispatcherTest
{
private:
	 EventDispatcher* const dispatcher;

public:
	EventDispatcherTest();
	~EventDispatcherTest();

	void hello(Event& evt);
	void hello2(Event& evt);
};

#endif


