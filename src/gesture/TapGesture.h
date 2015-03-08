#ifndef _TAPGESTURE_H_
#define _TAPGESTURE_H_

#include "Gesture.h"

class TapGesture : public Gesture
{
public:
    // provide a way to get a more accurate slop depending on dpi
    const float m_Slop;

public:
	explicit TapGesture(DisplayObject& target) : Gesture(target), m_Slop(20) {}
	~TapGesture() {}

protected:
	virtual void OnTouchBegin(Touch& touch) override;
	virtual void OnTouchEnd(Touch& touch) override;
	virtual void OnTouchMove(Touch& touch) override;
};

#endif