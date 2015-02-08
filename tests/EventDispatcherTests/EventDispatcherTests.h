#include "events\Event.h"

class CustomEvent : public Event
{
public:
    static const char* INIT;

    explicit CustomEvent(const char* type) : Event(type) {}
};

class EventReceiver
{
public:
    void onEventReceived(const Event& evt);
};

int main(array<System::String ^> ^args);