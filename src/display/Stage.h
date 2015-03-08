#ifndef _STAGE_H_
#define _STAGE_H_

#include "DisplayObjectContainer.h"
#include "utils\Vec2d.h"

class Stage: public DisplayObjectContainer
{
public:
    Stage(float width, float height) : m_Width(width), m_Height(height) {}
    virtual ~Stage() {};

    float   GetStageWidth()     { return m_Width; }
    float   GetStageHeight()    { return m_Height; }

    virtual DisplayObject*  HitTest(Vec2d localPoint) override;

private:
    float m_Width;
    float m_Height;
};

#endif