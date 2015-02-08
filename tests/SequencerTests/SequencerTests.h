#include "Event.h"

class ExampleEvent : public Event
{
public:
	static const char* INIT;
	static const char* COMPLETE;
	static const char* SECOND_COMPLETE;

	explicit ExampleEvent(const char* type) : Event(type) {}
};

class A
{
public:
	void methodA();
	void methodB(const Event& evt);
	void methodC(const Event& evt);

	void onSequenceStarted(const Event& evt);
	void onSequenceStepComplete(const Event& evt);
	void onSequenceComplete(const Event& evt);
};

int main(array<System::String ^> ^args);