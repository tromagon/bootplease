#include "TweenManager.h"
#include "display\DisplayObject.h"

const char* TweenManager::ID = "TweenManager_ID";

bool TweenManager::Update(float deltaTime)
{
    vector<TweenPtr>::const_iterator it;
    for (it = m_Tweens.begin() ; it != m_Tweens.end() ; )
    {
        (*it)->Update(deltaTime);

        if ((*it)->IsComplete())
        {
            m_Tweens.erase(it);
        }
        else
        {
            it++;
        }
    }

    return true;
}