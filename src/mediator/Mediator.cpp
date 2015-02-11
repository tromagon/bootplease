#include "Mediator.h"

void Mediator::DispatchContextEvent(const Event& evt)
{
    GetDispatcher()->Dispatch(evt);
}