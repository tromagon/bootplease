#include "ScreenManager.h"

const char* ScreenManagerEvent::TRANSITION_COMPLETE = "ScreenManagerEvent_TRANSITION_COMPLETE";

void ScreenManager::OnNextScreen(Event& evt)
{
	m_Busy = false;

	ScreenManagerEvent managerEvt(ScreenManagerEvent::TRANSITION_COMPLETE);
	Dispatch(managerEvt);
}