#include "Mediator.h"

void Mediator::DispatchContextEvent(Event& evt)
{
	GetDispatcher().Dispatch(evt);
}