#include "Stage.h"

DisplayObject* Stage::HitTest(Vec2d localPoint)
{
    if (!GetVisible() || !GetTouchable()) return nullptr;

    if (localPoint.x < 0 || localPoint.x > m_Width || localPoint.y < 0 || localPoint.y > m_Height)
    {
        return nullptr;
    }

    DisplayObject* target = DisplayObjectContainer::HitTest(localPoint);
    if (!target) target = this;

    return target;
}