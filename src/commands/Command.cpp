#include "Command.h"
#include "EventDispatcher.h"
#include "CommandMap.h"
#include "MediatorMap.h"

void Command::SetContext(Context& value)
{
	m_Context = &value;
}

void Command::SetEvent(const Event& evt)
{
	m_Event = &evt;
}

void Command::SetCommandMap(CommandMap& value)
{
	m_CommandMap = & value;
}

EventDispatcher& Command::GetDispatcher()
{
	return m_Context->GetDispatcher();
}

const Event& Command::GetEvent()
{
	return *m_Event;
}

Injector& Command::GetInjector()
{
	return m_Context->GetInjector();
}

MediatorMap& Command::GetMediatorMap()
{
	return m_Context->GetMediatorMap();
}

void Command::DispatchContextEvent(const Event& evt)
{
	GetDispatcher().Dispatch(evt);
}

void Command::Detain()
{
	m_CommandMap->Detain(*this);
}

void Command::Release()
{
	m_CommandMap->Release(*this);
}