#ifndef _TWEENMANAGER_H_
#define _TWEENMANAGER_H_

#include "Updateable.h"
#include "Tween.h"
#include "Display.h"
#include <vector>

using namespace std;

class TweenManager : public IUpdateable
{
private:
	vector<Tween*>	m_Tweens;
	vector<Tween*>	m_CompleteTweens;

public:
	TweenManager() {}
	~TweenManager() {}
	
	void		Update(float deltaTime = 0.0f) override;

	template<class C>
	C&			CreateTween(IDisplay& target);

private:
	void		AddTween(Tween& tween);
	int			GetTweenIndex(Tween& tween);
	void		ClearCompleteTweens();
	void		onTweenComplete(Event& evt);

};

template<class C>
C& TweenManager::CreateTween(IDisplay& target)
{
	C* c = new C(target);
	AddTween(*c);
	return *c;
}

#endif
