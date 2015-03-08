#include "GestureManager.h"
#include "display\Stage.h"
#include "TouchesManager.h"

const char* GestureManager::ID = "GestureManager_ID";

GestureManager::GestureManager(InputAdapter& inputAdapter, Stage& stage) : m_InputAdapter(inputAdapter), m_Stage(stage)
{
	m_TouchesManager = new TouchesManager(*this, m_Stage);
	inputAdapter.SetTouchesManager(*m_TouchesManager);
}

GestureManager::~GestureManager()
{
	RemoveAllGestures();
	RemoveAllTouches();
	
	delete m_TouchesManager;
}

void GestureManager::OnTouchBegin(Touch& touch)
{
    TouchMapItem* touchMapItem = GetTouchMapItemByTouch(touch);
    vector<Gesture*>* gesturesForTouch;
    if (!touchMapItem)
    {
        touchMapItem = new TouchMapItem();
        touchMapItem->m_Touch = &touch;
        m_TouchMapItems.push_back(touchMapItem);
        gesturesForTouch = &(touchMapItem->m_GestureList);
    }
    else
    {
        gesturesForTouch = &(touchMapItem->m_GestureList);
        gesturesForTouch->clear();
    }

    vector<DisplayObject*> hierarchy;
    DisplayObject* target = touch.GetTarget();

    GetHierarchy(*target, hierarchy);

    vector<Gesture*>* gesturesForTarget;
    GestureMapItem* gestureMapItem;

	const unsigned int l = hierarchy.size();
	for (unsigned int i = 0 ; i < l ; ++i)
    {
		target = hierarchy[i];

        gestureMapItem = GetGestureMapItemByTarget(*target);
        if (gestureMapItem)
        {
            gesturesForTarget = &(gestureMapItem->m_GestureList);
            int i = gesturesForTarget->size();
            while (i-- > 0)
            {
                Gesture& gesture = *(*gesturesForTarget)[i];
                if (gesture.GetEnabled())
                {
                    gesturesForTouch->insert(gesturesForTouch->begin(), &gesture);
                }
            }
        }
    }

    int i = gesturesForTouch->size();
    while (i-- > 0)
    {
        Gesture& gesture = *(*gesturesForTouch)[i];
        gesture.BeginTouch(touch);
    }
}

void GestureManager::OnTouchEnd(Touch& touch)
{
    int index = GetTouchMapItemIndexByTouch(touch);
    TouchMapItem& touchMapItem = *m_TouchMapItems[index];

    vector<Gesture*> gestureForTouch = touchMapItem.m_GestureList;
    int i = gestureForTouch.size();

    while (i-- > 0)
    {
        Gesture& gesture = *touchMapItem.m_GestureList[i];
        if (gesture.isTrackingTouch(touch.GetId()))
        {
            gesture.EndTouch(touch);
        }
    }

    m_TouchMapItems.erase(m_TouchMapItems.begin() + index);
    delete &touchMapItem;
}

void GestureManager::OnTouchMove(Touch& touch)
{
	int index = GetTouchMapItemIndexByTouch(touch);
    TouchMapItem& touchMapItem = *m_TouchMapItems[index];

    vector<Gesture*> gestureForTouch = touchMapItem.m_GestureList;
    int i = gestureForTouch.size();

    while (i-- > 0)
    {
        Gesture& gesture = *touchMapItem.m_GestureList[i];
        if (gesture.isTrackingTouch(touch.GetId()))
        {
            gesture.MoveTouch(touch);
        }
        else
        {
            gestureForTouch.erase(gestureForTouch.begin() + index);
        }
    }
}

void GestureManager::RemoveAllGestures()
{
	int i = m_GestureMapItems.size();
	while (--i >= 0)
	{
		delete m_GestureMapItems[i];
	}

	m_GestureMapItems.clear();
}

void GestureManager::RemoveAllTouches()
{
	int i = m_TouchMapItems.size();
	while (--i >= 0)
	{
		delete m_TouchMapItems[i];
	}

	m_TouchMapItems.clear();
}

bool GestureManager::Update(float deltaTime)
{
	bool quit = m_InputAdapter.Update(deltaTime);
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

GestureManager::GestureMapItem* GestureManager::GetGestureMapItemByTarget(DisplayObject& target)
{
    const unsigned short l = m_GestureMapItems.size();
    for (unsigned int i = 0 ; i < l ; i++)
	{
        GestureMapItem* item = m_GestureMapItems[i];

        if (&item->m_Target == &target)
        {
            return item;
        }
    }

    return nullptr;
}

GestureManager::TouchMapItem* GestureManager::GetTouchMapItemByTouch(Touch& touch)
{
    const unsigned short l = m_TouchMapItems.size();
    for (unsigned int i = 0 ; i < l ; i++)
	{
        TouchMapItem* item = m_TouchMapItems[i];

        if (item->m_Touch == &touch)
        {
            return item;
        }
    }

    return nullptr;
}

int GestureManager::GetTouchMapItemIndexByTouch(Touch& touch)
{
    const unsigned short l = m_TouchMapItems.size();
    for (unsigned int i = 0 ; i < l ; i++)
	{
        TouchMapItem* item = m_TouchMapItems[i];

        if (item->m_Touch == &touch)
        {
            return i;
        }
    }

    return -1;
}

int GestureManager::GetGestureMapIndexByTarget(DisplayObject& target)
{
	const unsigned short l = m_GestureMapItems.size();
    for (unsigned int i = 0 ; i < l ; i++)
	{
        GestureMapItem* item = m_GestureMapItems[i];

        if (&item->m_Target == &target)
        {
            return i;
        }
    }

    return -1;
}