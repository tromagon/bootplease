#ifndef _STAGE_H_
#define _STAGE_H_

#include "DisplayObjectContainer.h"
#include "utils\Vec2d.h"

class Stage: public DisplayObjectContainer
{
private:
    float m_Width;
    float m_Height;

public:
    float   GetStageWidth()     { return m_Width; }
    float   GetStageHeight()    { return m_Height; }

public:
    Stage(float width, float height) : m_Width(width), m_Height(height) {}
    virtual ~Stage() {};

    virtual DisplayObject*  HitTest(Vec2d localPoint) override;
};

#endif