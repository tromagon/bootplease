#include "Command.h"
#include "EventDispatcher.h"

void Command::DispatchContextEvent(Event& evt)
{
	GetDispatcher().Dispatch(evt);
}