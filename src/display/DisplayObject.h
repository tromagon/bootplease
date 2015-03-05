#ifndef _DISPLAYOBJECT_H_
#define _DISPLAYOBJECT_H_

#include "utils\Matrix.h"
#include "utils\Rectangle.h"
#include "utils\Vec2d.h"
#include "events\EventDispatcher.h"

#include <vector>

using namespace std;

class RenderSupport;
class DisplayObjectContainer;
class Stage;

class DisplayObject : public EventDispatcher
{
private:
    float                       m_X;
    float                       m_Y;
    float                       m_PivotX;
    float                       m_PivotY;
    float                       m_ScaleX;
    float                       m_ScaleY;
    float                       m_Rotation;
    float                       m_Alpha;
    bool                        m_Visible;
    DisplayObjectContainer*     m_Parent;
    Matrix                      m_TransformationMatrix;
    bool                        m_OrientationChanged;
    bool                        m_Touchable;

public:
    float       GetX()                          { return m_X; }
    void        SetX(float value);

    float       GetY()                          { return m_Y; }
    void        SetY(float value);

    float       GetPivotX()                     { return m_Y; }
    void        SetPivotX(float value);

    float       GetPivotY()                     { return m_Y; }
    void        SetPivotY(float value);

    float       GetScaleX()                     { return m_ScaleX; }
    void        SetScaleX(float value);

    float       GetScaleY()                     { return m_ScaleY; }
    void        SetScaleY(float value);

    float       GetRotation()                   { return m_Rotation; }
    void        SetRotation(float value);

    float       GetAlpha()                      { return m_Alpha; }
    void        SetAlpha(float value);

    bool        GetVisible()                    { return m_Visible; }
    void        SetVisible(bool value)          { m_Visible = value; }

    float       GetWidth();
    void        SetWidth(float value);

    float       GetHeight();
    void        SetHeight(float value);

    bool        GetTouchable()                  { return m_Touchable; }
    void        SetTouchable(bool value)        { m_Touchable = value; }

    DisplayObjectContainer*     GetParent()                                 { return m_Parent; }
    void                        SetParent(DisplayObjectContainer* value);

    Stage*                      GetStage();
    DisplayObject&              GetBase();

protected:
    static vector<DisplayObject*>   ancestors;
    static bootplease::Rectangle    helperRect;
    static Matrix                   helperMatrix;
    static Vec2d                    helperVec2d;

public:
    DisplayObject() 
        : m_X(0.0f), m_Y(0.0f), m_PivotX(0.0f), m_PivotY(0.0f), m_ScaleX(1.0f), m_ScaleY(1.0f), m_Rotation(0.0f), 
        m_Alpha(1.0f), m_Visible(true), m_Parent(nullptr), m_OrientationChanged(false), m_Touchable(true) {}

    virtual ~DisplayObject() {}

    bool                    hasVisibleArea();
    virtual bootplease::Rectangle&      GetBounds(DisplayObject& target, bootplease::Rectangle& resultRect) { return resultRect; }
    Matrix&                 GetTransformationMatrix();
    Matrix&                 GetRelativeTransformationMatrix(DisplayObject* target, Matrix& resultMatrix);
    virtual DisplayObject*  HitTest(Vec2d localPoint);
    virtual void            Render(RenderSupport& renderSupport, float parentAlpha) {}
    void                    RemoveFromParent();

private:
    DisplayObject*          FindCommonParent(DisplayObject& objectA, DisplayObject& objectB);
    int                     GetIndexOf(vector<DisplayObject*> list, DisplayObject& target);
};

#endif