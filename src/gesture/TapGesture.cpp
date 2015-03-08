#include "TapGesture.h"
#include "GestureEvent.h"

void TapGesture::OnTouchBegin(Touch& touch)
{
	SetState(BEGAN);
}

void TapGesture::OnTouchEnd(Touch& touch)
{
	if (m_State == BEGAN)
	{
		SetState(ENDED);

		GestureEvent evt(GestureEvent::GESTURE_RECOGNIZED, *this);
		Dispatch(evt);
	}
}

void TapGesture::OnTouchMove(Touch& touch)
{
    if (touch.GetLocationOffset().GetLength() > m_Slop)
    {
        m_State = ENDED;
    }
}