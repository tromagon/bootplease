#ifndef _TAPGESTURE_H_
#define _TAPGESTURE_H_

#include "Gesture.h"

class TapGesture : public Gesture
{
public:
    explicit TapGesture(DisplayObject& target) : Gesture(target), m_Slop(20) {}
    ~TapGesture() {}

    const float m_Slop;

protected:
    virtual void OnTouchBegin(Touch& touch) override;
    virtual void OnTouchEnd(Touch& touch) override;
    virtual void OnTouchMove(Touch& touch) override;
};

#endif