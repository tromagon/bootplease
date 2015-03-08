#ifndef _DISPLAYOBJECTCONTAINER_H_
#define _DISPLAYOBJECTCONTAINER_H_

#include "DisplayObject.h"
#include <vector>

using namespace std;

class DisplayObjectContainer : public DisplayObject
{
public:
    DisplayObjectContainer() : m_NumChildren(0) {}
    virtual ~DisplayObjectContainer();

    DisplayObjectPtr&       AddChild(DisplayObjectPtr& child);
    DisplayObjectPtr&       AddChildAt(DisplayObjectPtr& child, int index);
    DisplayObject&          AddChild(DisplayObject& child);
    DisplayObject&          AddChildAt(DisplayObject& child, int index);
    DisplayObjectPtr&       RemoveChild(DisplayObjectPtr& child);
    DisplayObject&          RemoveChild(DisplayObject& child);
    DisplayObject&          RemoveChildAt(int index);
    DisplayObject&          GetChildAt(int index);
    int                     GetChildIndex(DisplayObject& child);
    virtual bootplease::Rectangle&      GetBounds(DisplayObject& target, bootplease::Rectangle& resultRect) override;
    int                     GetNumChildren()    { return m_NumChildren; }
    virtual DisplayObject*  HitTest(Vec2d localPoint) override;
    virtual void            Render(RenderSupport& renderSupport, float parentAlpha) override;

protected:
    void                    RemoveAllChildren();

private:
    DisplayObject&          CleanChild(DisplayObject& child, int index);

    vector<DisplayObject*>  m_Children;
    int                     m_NumChildren;
};

#endif