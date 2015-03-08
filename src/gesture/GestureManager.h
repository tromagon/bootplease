#ifndef _GESTUREMANAGER_H_
#define _GESTUREMANAGER_H_

#include "Gesture.h"
#include "GestureEvent.h"
#include "core\Updateable.h"
#include "Touch.h"
#include <vector>
#include <unordered_map>

using namespace std;

class TouchesManager;
typedef unique_ptr<TouchesManager> TouchesManagerPtr;

class InputAdapter;
typedef unique_ptr<InputAdapter> InputAdapterPtr;

class Stage;

class GestureManager : public Updateable
{
public:
    explicit GestureManager(Stage& stage);

    static const char* ID;

    template<class G, class C>
    G& AddGesture(DisplayObject& target, void (C::*fct)(const Event&), C& proxy);

    template<class C>
    void RemoveGesture(DisplayObject& target, void (C::*fct)(const Event&), C& proxy);

    void RemoveGesture(Gesture& gesture);

    template<class C>
    void RemoveAllGesturesOf(C& proxy) {}

    template<class C>
    void registerAdapter();

    bool Update(float deltaTime = 0.0f) override;

    void OnTouchBegin(Touch& touch);
    void OnTouchEnd(Touch& point);
    void OnTouchMove(Touch& point);

private:
    void GetHierarchy(DisplayObject& target, vector<DisplayObject*>& result);

    typedef unordered_map<DisplayObject*, GesturePtr> GestureMap;
    typedef unordered_map<Touch*, GesturePtr> TouchGestureMap;

    InputAdapterPtr             m_InputAdapter;
    TouchesManagerPtr           m_TouchesManager;
    Stage&                      m_Stage;

    GestureMap                  m_gestureMap;
    TouchGestureMap             m_currentGestures;
};

template<class C>
void GestureManager::registerAdapter()
{
    m_InputAdapter = InputAdapterPtr(new C(m_TouchesManager));
}

template<class G, class C>
G& GestureManager::AddGesture(DisplayObject& target, void (C::*fct)(const Event&), C& proxy)
{
    G* gesture = new G(target);
    gesture->AddListener(GestureEvent::GESTURE_RECOGNIZED, fct, proxy);
    m_gestureMap.insert(make_pair(&target, GesturePtr(gesture)));
    return *gesture;
}

template<class C>
void GestureManager::RemoveGesture(DisplayObject& target, void (C::*fct)(const Event&), C& proxy)
{
    GestureMap::iterator it;
    for (it = m_gestureMap.begin() ; it != m_gestureMap.end() ; )
    {
        if (it->first == &target && it->second->HasListener(GestureEvent::GESTURE_RECOGNIZED, fct, proxy))
        {
            m_gestureMap.erase(it++);
        }
        else
        {
            ++it;
        }
    }
}

#endif