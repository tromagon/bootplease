#include "TweenManager.h"

void TweenManager::Update(float deltaTime)
{
	ClearCompleteTweens();

	const unsigned short l = m_Tweens.size();
	for (unsigned int i = 0 ; i < l ; i++)
	{
		m_Tweens[i]->Update(deltaTime);
	}
}

void TweenManager::AddTween(Tween& tween)
{
	tween.AddListener(TweenEvent::COMPLETE, &TweenManager::onTweenComplete, *this);
	m_Tweens.push_back(&tween);
}

int TweenManager::GetTweenIndex(Tween& tween)
{
	const unsigned short l = m_Tweens.size();
	for (unsigned int i = 0 ; i < l ; i++)
	{
		if (m_Tweens[i] == &tween)
		{
			return i;
		}
	}

	return -1;
}

void TweenManager::ClearCompleteTweens()
{
	const unsigned short l = m_CompleteTweens.size();
	for (int i = l - 1 ; i >= 0 ; i--)
	{
		Tween& tween = *(m_CompleteTweens[i]);
		m_Tweens.erase(m_Tweens.begin() + GetTweenIndex(tween));
		m_CompleteTweens.erase(m_CompleteTweens.begin() + i);
		delete &tween;
	}
}

void TweenManager::onTweenComplete(Event& evt)
{
	TweenEvent& tweenEvent = static_cast<TweenEvent&>(evt);
	Tween& tween = tweenEvent.GetTween();
	tween.RemoveListener(TweenEvent::COMPLETE, &TweenManager::onTweenComplete, *this);
	m_CompleteTweens.push_back(&tween);

	
}