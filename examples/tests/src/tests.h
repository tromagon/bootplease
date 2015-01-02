#ifndef _TESTS_H_
#define _TESTS_H_

#include "EventDispatcher.h"
#include "Sequence.h"
#include "Injector.h"

#include <iostream>


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
	EventDispatcher* dispatcher;

public:
	EventDispatcherTest();
	~EventDispatcherTest();

	void hello(Event& evt);
	void hello2(Event& evt);
};

class Params;

class SequenceTest
{
private:
	EventDispatcher* dispatcher;
	Sequence* sequence;

public:
	SequenceTest();
	~SequenceTest();

	void methodA();
	void methodB(Params& params);

	void onInit(Event& evt);
	void onComplete(Event& evt);
	void onSequenceStarted(Event& evt);
	void onSequenceStepComplete(Event& evt);
	void onSequenceComplete(Event& evt);
};

class Params
{
public:
	int m_X;
	int m_Y;

public:
	Params(int x, int y) : m_X(x), m_Y(y) {}
	~Params(){};
};

#endif


class InjectionTest
{
private:
	Injector injector;

public:
	InjectionTest();
	~InjectionTest() {};
};

class InjectionID
{
public:
	static const char* MODEL_A;
	static const char* MODEL_B;
	static const char* MODEL_A_2;
};

class ModelA {};
class ModelB {};

class CommandMapTest
{
public:
	CommandMapTest();
	~CommandMapTest() {};
};

class ExampleCommandA : public Command
{
public:
	ExampleCommandA() {}
	~ExampleCommandA() {}

	virtual void execute() override;
};

class ExampleCommandB : public Command
{
public:
	ExampleCommandB() {}
	~ExampleCommandB() {}

	virtual void execute() override;

private:
	void onEvent(Event& evt);
};

class CommandFactory
{
public:
	CommandFactory() {}
	~CommandFactory() {}

	Command& GetExampleCommandA() { return *(new ExampleCommandA()); };
	Command& GetExampleCommandB() { return *(new ExampleCommandB()); };
};


class Tests
{

public:
	Tests();
	~Tests();

	void Update(float deltaTime);
};


