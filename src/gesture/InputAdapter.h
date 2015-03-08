#ifndef _INPUTADAPTER_H_
#define _INPUTADAPTER_H_

#include "core\Updateable.h"

class TouchesManager;

class InputAdapter
{
protected:
    TouchesManager*     m_TouchesManager;

public:
    TouchesManager&     GetTouchesManager()                         { return *m_TouchesManager; }
    void                SetTouchesManager(TouchesManager& value)    { m_TouchesManager = &value; }

public:
    InputAdapter() {}
    virtual ~InputAdapter() {}

    virtual bool Update(float deltaTime = 0.0f) = 0;
};

#endif