#include "Mediator.h"

Injector& Mediator::GetInjector()
{
	return m_MediatorMap->GetInjector();
}

void Mediator::DispatchContextEvent(Event& evt)
{
	m_MediatorMap->GetDispatcher()->Dispatch(evt);
}