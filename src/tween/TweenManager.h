#ifndef _TWEENMANAGER_H_
#define _TWEENMANAGER_H_

#include "core\Updateable.h"
#include "Tween.h"
#include <vector>

using namespace std;

class DisplayObject;

class TweenManager : public Updateable
{
public:
    TweenManager() {}
    ~TweenManager() {}

    static const char* ID;
    
    void    Update(float deltaTime = 0.0f) override;

    template<class C>
    C&      CreateTween(DisplayObject& target);

private:
    vector<TweenPtr>  m_Tweens;
};

template<class C>
C& TweenManager::CreateTween(DisplayObject& target)
{
    C* tween = new C(target);
    m_Tweens.push_back(TweenPtr(tween));
    return *tween;
}

#endif