#ifndef _SWIPEGESTURE_H_
#define _SWIPEGESTURE_H_

#include "Gesture.h"

class SwipeGesture : public Gesture
{
public:
    explicit SwipeGesture(DisplayObject& target) : Gesture(target), m_Slop(20) {}
    ~SwipeGesture() {}

    const Vec2d& GetOffset() const   { return m_Offset; }

protected:
    virtual void OnTouchBegin(Touch& touch) override;
    virtual void OnTouchEnd(Touch& touch) override;
    virtual void OnTouchMove(Touch& touch) override;

private:
    // provide a way to get a more accurate slop depending on dpi
    
    static const int   MAX_DURATION;
    static const float MIN_OFFSET;
    static const float MIN_VELOCIY;
    static const float ANGLE;

    const float     m_Slop;
    Vec2d           m_Location;
    long            m_StartTime;
    Vec2d           m_AvrgVel;
    Vec2d           m_Offset;
    
    static Vec2d    absVel;
};

#endif