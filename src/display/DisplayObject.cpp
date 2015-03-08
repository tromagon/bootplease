#include "DisplayObject.h"
#include "DisplayObjectContainer.h"
#include "Stage.h"
#include <math.h>

vector<DisplayObject*>  DisplayObject::ancestors;
bootplease::Rectangle   DisplayObject::helperRect;
Matrix                  DisplayObject::helperMatrix;
Vec2d                   DisplayObject::helperVec2d;

DisplayObject::~DisplayObject()
{
    if (GetParent())
    {
        GetParent()->RemoveChild(*this);
    }
}

void DisplayObject::SetX(float value)
{
    if (m_X != value)
    {
        m_X = value;
        m_OrientationChanged = true;
    }
}

void DisplayObject::SetY(float value)
{
    if (m_Y != value)
    {
        m_Y = value;
        m_OrientationChanged = true;
    }
}

void DisplayObject::SetPivotX(float value)
{
    if (m_PivotX != value)
    {
        m_PivotX = value;
        m_OrientationChanged = true;
    }
}

void DisplayObject::SetPivotY(float value)
{
    if (m_PivotY != value)
    {
        m_PivotY = value;
        m_OrientationChanged = true;
    }
}

void DisplayObject::SetScaleX(float value)
{
    if (m_ScaleX != value)
    {
        m_ScaleX = value;
        m_OrientationChanged = true;
    }
}

void DisplayObject::SetScaleY(float value)
{
    if (m_ScaleY != value)
    {
        m_ScaleY = value;
        m_OrientationChanged = true;
    }
}

void DisplayObject::SetRotation(float value)
{
    // todo : normalize rotation

    if (m_Rotation != value)
    {
        m_Rotation = value;
        m_OrientationChanged = true;
    }
}

void DisplayObject::SetAlpha(float value)
{
    m_Alpha = value < 0 ? 0 : (value > 1.0f) ? 1.0f : value;
}

float DisplayObject::GetWidth()
{
    return GetBounds(*m_Parent, helperRect).m_Width;
}

void DisplayObject::SetWidth(float value)
{
    SetScaleX(1.0f);
    float actualWidth = GetWidth();
    if (actualWidth != 0)
    {
        SetScaleX(value / actualWidth);
    }
}

float DisplayObject::GetHeight()
{
    return GetBounds(*m_Parent, helperRect).m_Height;
}

void DisplayObject::SetHeight(float value)
{
    SetScaleY(1.0f);
    float actualHeight = GetHeight();
    if (actualHeight != 0)
    {
        SetScaleY(value / actualHeight);
    }
}

void DisplayObject::SetParent(DisplayObjectContainer* value)
{
    // todo check if we re not adding it to itself
    m_Parent = value;
}

Stage* DisplayObject::GetStage()
{
    return dynamic_cast<Stage*>(&GetBase());
}

DisplayObject& DisplayObject::GetBase()
{
    DisplayObject* current = this;
    while(current->GetParent())
    {
        current = dynamic_cast<DisplayObject*>(current->GetParent());
    }

    return *current;
}

bool DisplayObject::hasVisibleArea()
{
    return m_Alpha != 0 && m_Visible && m_ScaleX != 0 && m_ScaleY != 0;
}

Matrix& DisplayObject::GetTransformationMatrix()
{
    if (m_OrientationChanged)
    {
        m_OrientationChanged = false;

        if (m_Rotation == 0)
        {
            m_TransformationMatrix.SetTo(m_ScaleX, 0, 0, m_ScaleY, 
                m_X - m_PivotX * m_ScaleX, m_Y - m_PivotY * m_ScaleY);
        }
        else
        {
            float cosa = cos(m_Rotation);
            float sina = sin(m_Rotation);
            float a = m_ScaleX * cosa;
            float b = m_ScaleX * sina;
            float c = m_ScaleY * -sina;
            float d = m_ScaleY * cosa;
            float tx = m_X - m_PivotX * a - m_PivotY * c;
            float ty = m_Y - m_PivotY * b - m_PivotY * d;

            m_TransformationMatrix.SetTo(a, b, c , d, tx, ty);
        }
    }

    return m_TransformationMatrix;
}

Matrix& DisplayObject::GetRelativeTransformationMatrix(DisplayObject* target, Matrix& resultMatrix)
{
    DisplayObject* commonParent;
    DisplayObject* currentObject;

    resultMatrix.Identity();

    if (target == this)
    {
        return resultMatrix;
    }
    
    if (target == dynamic_cast<DisplayObject*>(m_Parent) || (!target && !m_Parent))
    {
        resultMatrix.CopyFrom(GetTransformationMatrix());
        return resultMatrix;
    }
    
    if (!target || target == &GetBase())
    {
        // target at null represent the target space of the base object
        // -> move up from this to base

        currentObject = this;
        while (currentObject != target)
        {
            resultMatrix.Concat(currentObject->GetTransformationMatrix());
            currentObject = currentObject->m_Parent;
        }

        return resultMatrix;
    }
    
    if (target->GetParent() == this)
    {
        target->GetRelativeTransformationMatrix(this, resultMatrix);
        resultMatrix.Invert();
        
        return resultMatrix;
    }

    // 1. find commun parent of this and the target space

    commonParent = FindCommonParent(*this, *target);

    // 2. move up from this to common parent

    currentObject = this;
    while (currentObject != commonParent)
    {
        resultMatrix.Concat(currentObject->GetTransformationMatrix());
        currentObject = currentObject->GetParent();
    }

    if (commonParent == target)
    {
        return resultMatrix;
    }

    // 3. now move up from target until we reach the common parent

    helperMatrix.Identity();
    currentObject = target;
    while (currentObject != commonParent)
    {
        helperMatrix.Concat(currentObject->GetTransformationMatrix());
        currentObject = currentObject->GetParent();
    }

    // 4. now combine the two matrices

    helperMatrix.Invert();
    resultMatrix.Concat(helperMatrix);

    return resultMatrix;
}

DisplayObject* DisplayObject::HitTest(Vec2d localPoint)
{
    if (!m_Visible || !m_Touchable) return nullptr;

    if (GetBounds(*this, helperRect).ContainsPoint(localPoint))
    {
        return this;
    }

    return nullptr;
}

void DisplayObject::RemoveFromParent()
{
    if (m_Parent)
    {
        m_Parent->RemoveChild(*this);
    }
}

DisplayObject* DisplayObject::FindCommonParent(DisplayObject& objectA, DisplayObject& objectB)
{
    DisplayObject* currentObject = &objectA;

    while (currentObject)
    {
        ancestors.push_back(currentObject);
        currentObject = currentObject->GetParent();
    }

    currentObject = &objectB;

    while (currentObject && GetIndexOf(ancestors, *currentObject) != -1)
    {
        currentObject = currentObject->GetParent();
    }

    ancestors.clear();

    if (currentObject)
    {
        return currentObject;
    }
    
    return nullptr;
}

int DisplayObject::GetIndexOf(vector<DisplayObject*> list, DisplayObject& target)
{
    const unsigned int l = list.size();
    for (unsigned int i = 0 ; i < l ; i++)
    {
        if (list[i] == &target)
        {
            return i;
        }
    }

    return -1;
}