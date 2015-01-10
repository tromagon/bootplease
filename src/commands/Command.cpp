#include "Command.h"
#include "EventDispatcher.h"

void Command::DispatchContextEvent(Event& evt)
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