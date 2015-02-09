#include "events\Event.h"
#include "commands\Command.h"

class CommandA : public Command
{
public:
    CommandA(CommandMap& commandMap) : Command(commandMap) {};

    virtual void Execute() override;
};

class CommandB : public Command
{
public:
    CommandB(CommandMap& commandMap) : Command(commandMap) {};

    virtual void Execute() override;
};

class ExampleEvent : public Event
{
public:
    static const char* START_COMMAND_A;
    static const char* START_COMMAND_B;

    explicit ExampleEvent(const char* type) : Event(type) {}
};