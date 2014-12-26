#include "Transitions.h"

const char* TransitionEvent::COMPLETE = "TransitionEvent_COMPLETE";
const float Transition::DEFAULT_ANIMATION_TIME = 0.5f;

void Transition::OnTransitionComplete(Event& evt)
{
	TransitionEvent completeEvt(TransitionEvent::COMPLETE);
	Dispatch(completeEvt);
}

void MoveLeft::Play()
{
	m_NextScreen->SetAlpha(1);

	TweenX& tween = m_TweenManager->CreateTween<TweenX>(*m_NextScreen);
	tween
		.From(m_NextScreen->GetScreenWidth())
		.To(0)
		.Duration(DEFAULT_ANIMATION_TIME)
		.OnComplete(&MoveLeft::OnTransitionComplete, *this)
		.Play();

	if (m_PreviousScreen)
	{
		TweenX& prevScrTween = m_TweenManager->CreateTween<TweenX>(*m_PreviousScreen);
		prevScrTween
			.To(m_PreviousScreen->GetScreenWidth())
			.Duration(DEFAULT_ANIMATION_TIME)
			.Play();
	}
}

void MoveLeft::Stop()
{
	// should kill tween for current target, go through tweenManager for that
}

void MoveLeft::Reverse()
{
	TweenX& tween = m_TweenManager->CreateTween<TweenX>(*m_NextScreen);
	tween
		.To(m_NextScreen->GetScreenWidth())
		.Duration(DEFAULT_ANIMATION_TIME)
		.OnComplete(&MoveLeft::OnTransitionComplete, *this)
		.Play();

	if (m_PreviousScreen)
	{
		TweenX& prevScrTween = m_TweenManager->CreateTween<TweenX>(*m_PreviousScreen);
		prevScrTween
			.To(0)
			.Duration(DEFAULT_ANIMATION_TIME)
			.Play();
	}
}