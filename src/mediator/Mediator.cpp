#include "Mediator.h"
#include "mediator\MediatorMap.h"

void Mediator::DispatchContextEvent(const Event& evt)
{
    GetDispatcher()->Dispatch(evt);
}

InjectorPtr& Mediator::GetInjector()       
{ 
    return m_MediatorMap->GetInjector(); 
} 

EventDispatcherPtr& Mediator::GetDispatcher()     
{ 
    return m_MediatorMap->GetDispatcher(); 
}