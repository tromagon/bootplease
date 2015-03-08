#ifndef _GESTUREMANAGER_H_
#define _GESTUREMANAGER_H_

#include "Gesture.h"
#include "GestureEvent.h"
#include "core\Updateable.h"
#include "InputAdapter.h"
#include "Touch.h"
#include <vector>

using namespace std;

class TouchesManager;
class Stage;

class GestureManager : public Updateable
{
public:
	static const char* ID;

private:
    class GestureMapItem
    {
    public:
        DisplayObject&      m_Target;
        vector<Gesture*>    m_GestureList;

    public:
	    explicit GestureMapItem(DisplayObject& target) : m_Target(target) {}
	    ~GestureMapItem() {}
    };

    class TouchMapItem
    {
    public:
        Touch*              m_Touch;
        vector<Gesture*>    m_GestureList;
    };

private:
	InputAdapter&				m_InputAdapter;
	TouchesManager*				m_TouchesManager;
	vector<GestureMapItem*>		m_GestureMapItems;
    vector<TouchMapItem*>       m_TouchMapItems;
    Stage&						m_Stage;

public:
	InputAdapter&				GetInputAdapter() { return m_InputAdapter; }

public:
	explicit GestureManager(InputAdapter& inputAdapter, Stage& stage);
	~GestureManager();

	template<class G, class C>
	G& AddGesture(DisplayObject& target, void (C::*fct)(const Event&), C& proxy);

	template<class C>
	void RemoveGesture(Gesture& gesture, void (C::*fct)(const Event&), C& proxy);

	template<class C>
	void RemoveAllGesturesOf(C& proxy) {};

    bool Update(float deltaTime = 0.0f) override;

	void OnTouchBegin(Touch& touch);
	void OnTouchEnd(Touch& point);
	void OnTouchMove(Touch& point);

private:
	void			RemoveAllGestures();
	void			RemoveAllTouches();
	GestureMapItem* GetGestureMapItemByTarget(DisplayObject& target);
    TouchMapItem*   GetTouchMapItemByTouch(Touch& touch);
    int             GetTouchMapItemIndexByTouch(Touch& touch);
	int				GetGestureMapIndexByTarget(DisplayObject& target);
    void            GetHierarchy(DisplayObject& target, vector<DisplayObject*>& result);
};

template<class G, class C>
G& GestureManager::AddGesture(DisplayObject& target, void (C::*fct)(const Event&), C& proxy)
{
	G* gesture = new G(target);
	gesture->AddListener(GestureEvent::GESTURE_RECOGNIZED, fct, proxy);

    GestureMapItem* item = GetGestureMapItemByTarget(target);
    if (!item)
    {
        item = new GestureMapItem(target);
        m_GestureMapItems.push_back(item);
    }

    item->m_GestureList.push_back(gesture);
	return *gesture;
}

template<class C>
void GestureManager::RemoveGesture(Gesture& gesture, void (C::*fct)(const Event&), C& proxy)
{
	int index = GetGestureMapIndexByTarget(gesture.GetTarget());
    if (index == -1) return;

	GestureMapItem* item = m_GestureMapItems[index];
	vector<Gesture*>* gestureList = &item->m_GestureList;
	int i = gestureList->size();

    while (i-- > 0)
	{
		if ((*gestureList)[i] == &gesture)
		{
			gestureList->erase(gestureList->begin() + i);
			if (gestureList->size() == 0)
			{
				m_GestureMapItems.erase(m_GestureMapItems.begin() + index);
				delete item;
			}
		}
    }
}

#endif