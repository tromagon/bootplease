#include "Tween.h"
#include "TweenEvent.h"

void Tween::Play()
{
    if (m_State == PLAYING || m_State == DELAYED) return;

    Init();

    const TweenEvent evt(TweenEvent::START, *this);
    Dispatch(evt);
}

void Tween::Stop()
{
    if (m_State == STOPPED) return;

    m_State = STOPPED;
}