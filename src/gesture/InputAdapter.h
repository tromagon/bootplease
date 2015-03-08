#ifndef _INPUTADAPTER_H_
#define _INPUTADAPTER_H_

#include "core\Updateable.h"
#include "gesture\TouchesManager.h"
#include <memory>

using namespace std;

//class TouchesManager;
//typedef unique_ptr<TouchesManager> TouchesManagerPtr;

class InputAdapter
{
protected:
    TouchesManagerPtr&  m_TouchesManager;

public:
    TouchesManagerPtr&  GetTouchesManager() { return m_TouchesManager; }

public:
    InputAdapter(TouchesManagerPtr& touchesManager) : m_TouchesManager(touchesManager) {}
    virtual ~InputAdapter() {}

    virtual bool Update(float deltaTime = 0.0f) = 0;
};

typedef unique_ptr<InputAdapter> InputAdapterPtr;

#endif