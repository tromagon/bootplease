#ifndef _DISPLAYOBJECTCONTAINER_H_
#define _DISPLAYOBJECTCONTAINER_H_

#include "DisplayObject.h"
#include <vector>

using namespace std;

class DisplayObjectContainer : public DisplayObject
{
private:
    vector<DisplayObject*>  m_Children;
    int                     m_NumChildren;

public:
    int                     GetNumChildren()    { return m_NumChildren; }

public:
    DisplayObjectContainer() : m_NumChildren(0) {}
    virtual ~DisplayObjectContainer();

    virtual DisplayObject&  AddChild(DisplayObject& child);
    virtual DisplayObject&  AddChildAt(DisplayObject& child, int index);
    virtual DisplayObject&  RemoveChild(DisplayObject& child);
    virtual DisplayObject&  RemoveChildAt(int index);
    DisplayObject&          GetChildAt(int index);
    int                     GetChildIndex(DisplayObject& child);
    virtual bootplease::Rectangle&      GetBounds(DisplayObject& target, bootplease::Rectangle& resultRect) override;
    virtual DisplayObject*  HitTest(Vec2d localPoint) override;
    virtual void            Render(RenderSupport& renderSupport, float parentAlpha) override;

protected:
    void                    RemoveAllChildren();

private:
    DisplayObject&          CleanChild(DisplayObject& child, int index);
};

#endif