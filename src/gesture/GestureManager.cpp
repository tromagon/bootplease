#include "GestureManager.h"
#include "display\Stage.h"
#include "TouchesManager.h"
#include "InputAdapter.h"

const char* GestureManager::ID = "GestureManager_ID";

GestureManager::GestureManager(Stage& stage) 
        : m_Stage(stage), m_TouchesManager(TouchesManagerPtr(new TouchesManager(*this, stage))) {}

void GestureManager::RemoveGesture(Gesture& gesture)
{
    GestureMap::iterator it;
    for (it = m_gestureMap.begin() ; it != m_gestureMap.end() ; )
    {
        if (it->second.get() == &gesture)
        {
            m_gestureMap.erase(it++);
        }
        else
        {
            ++it;
        }
    }
}

void GestureManager::OnTouchBegin(Touch& touch)
{
    //clear previous gestures for this touch
    TouchGestureMap::iterator it;
    for (it = m_currentGestures.begin() ; it != m_currentGestures.end() ; )
    {
        if (it->first == &touch)
        {
            m_currentGestures.erase(it++);
        }
        else
        {
            ++it;
        }
    }

    vector<DisplayObject*> hierarchy;
    DisplayObject* target = touch.GetTarget();

    GetHierarchy(*target, hierarchy);

    const unsigned int l = hierarchy.size();
    for (unsigned int i = 0 ; i < l ; ++i)
    {
        target = hierarchy[i];

        GestureMap::iterator it;
        for (it = m_gestureMap.begin() ; it != m_gestureMap.end() ; ++it)
        {
            if (it->first == target)
            {
                GesturePtr& gesture = it->second;
                if (gesture->GetEnabled())
                {
                    m_currentGestures.insert(make_pair(&touch, gesture));
                    gesture->BeginTouch(touch);
                }
            }
        }
    }
}

void GestureManager::OnTouchEnd(Touch& touch)
{
    TouchGestureMap::iterator it;
    for (it = m_currentGestures.begin() ; it != m_currentGestures.end() ; )
    {
        if (it->first == &touch)
        {
            it->second->EndTouch(touch);
            m_currentGestures.erase(it++);
        }
        else
        {
            ++it;
        }
    }
}

void GestureManager::OnTouchMove(Touch& touch)
{
    TouchGestureMap::iterator it;
    for (it = m_currentGestures.begin() ; it != m_currentGestures.end() ; )
    {
        GesturePtr& gesture = it->second;
        if (gesture->isTrackingTouch(touch.GetId()))
        {
            it->second->MoveTouch(touch);
            ++it;
        }
        else
        {
            m_currentGestures.erase(it++);
        }
    }
}

bool GestureManager::Update(float deltaTime)
{
    bool quit = m_InputAdapter->Update(deltaTime);
    if (!quit)
    {
        m_TouchesManager->Update(deltaTime);
    }

    return quit;
}

void GestureManager::GetHierarchy(DisplayObject& target, vector<DisplayObject*>& result)
{
    DisplayObject* current = &target;
    while (current)
    {
        result.push_back(current);
        current = current->GetParent();
    }
}