#include "Tween.h"

const char* TweenEvent::START = "TweenEvent_START";
const char* TweenEvent::UPDATE = "TweenEvent_UPDATE";
const char* TweenEvent::COMPLETE = "TweenEvent_COMPLETE";


void Tween::Play()
{
	if (m_State == PLAYING || m_State == DELAYED) return;

	m_IsPlaying = true;

	Init();

	TweenEvent evt(TweenEvent::START, *this);
	m_Dispatcher.Dispatch(evt);
}

void Tween::Stop()
{
	if (m_State == STOPPED) return;

	m_State = STOPPED;
}