#include "commands\Command.h"
#include "events\EventDispatcher.h"
#include "commands\CommandMap.h"
#include "mediator\MediatorMap.h"
#include "injection\Injector.h"

void Command::SetEvent(const Event& evt)
{
    m_Event = &evt;
}

EventDispatcherPtr& Command::GetDispatcher()
{
    return m_CommandMap->GetDispatcher();
}

const Event& Command::GetEvent()
{
    return *m_Event;
}

InjectorPtr& Command::GetInjector()
{
    return m_CommandMap->GetInjector();
}

bool Command::GetIsDetained()
{
    return m_IsDetained;
}

void Command::DispatchContextEvent(const Event& evt)
{
    GetDispatcher()->Dispatch(evt);
}

void Command::Detain()
{
    m_IsDetained = true;
}

void Command::Release()
{
    m_IsDetained = false;

    m_CommandMap->Release(*this);
}