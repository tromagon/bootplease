#ifndef _TWEEN_H_
#define _TWEEN_H_

#include "EventDispatcher.h"
#include "Display.h"

class Tween;

class TweenEvent : public Event
{
public:
	static const char* START;
	static const char* UPDATE;
	static const char* COMPLETE;

private:
	Tween& m_Tween;

public:
	Tween&	GetTween() { return m_Tween; }

public:
	explicit TweenEvent(const char* type, Tween& tween) 
		: Event(type), m_Tween(tween) {}

	virtual ~TweenEvent() {}
};


class Tween
{
protected:
	static const char STOPPED = 0;
	static const char DELAYED = 1;
	static const char PLAYING = 2;

protected:
	bool				m_IsPlaying;
	EventDispatcher		m_Dispatcher;
	char				m_State;

public:
	Tween() {}
	virtual ~Tween() {}

	virtual void	Init() {}
	virtual void	Play();
	virtual void	Stop();
	virtual void	Update(float deltaTime) {}

	template<class C>
	int		AddListener(const char* eventType, void (C::*fct)(Event&), C& o);

	template<class C>
	void	RemoveListener(const char* eventType, void (C::*fct)(Event&), C& o);
};

template<class C>
int Tween::AddListener(const char* eventType, void (C::*fct)(Event&), C& proxy)
{
	return m_Dispatcher.AddListener(eventType, fct, proxy);
}

template<class C>
void Tween::RemoveListener(const char* eventType, void (C::*fct)(Event&), C& proxy)
{
	return m_Dispatcher.RemoveListener(eventType, fct, proxy);
}

template<class V, class C, V (C::*Get)(), void (C::*Set)(V)>
class TweenSpec : public Tween
{
private:
	V		m_From;
	V		m_To;
	C&		m_Target;
	float	m_Duration;
	float	m_Delay;
	float	m_Elapsed;
	bool	m_IsFromSet;
	float	m_ElapsedDelay;
	float	(*m_EaseFct)(float);

public:
	explicit TweenSpec(C& target) 
		: m_Target(target), m_Duration(0), m_Delay(0), m_Elapsed(0), m_ElapsedDelay(0) {}
	~TweenSpec() {}

	TweenSpec& From(V value)
	{
		m_IsFromSet = true;
		m_From = value;
		return *this;
	}

	TweenSpec& To(V value)
	{
		m_To = value;
		return *this;
	}

	TweenSpec& Duration(float value)
	{
		m_Duration = value;
		return *this;
	}

	TweenSpec& Delay(float value)
	{
		m_Delay = value;
		return *this;
	}

	TweenSpec& Easing(float (*value)(float))
	{
		m_EaseFct = value;
		return *this;
	}

	template<class P>
	TweenSpec& OnUpdate(void (P::*fct)(Event&), P& proxy)
	{
		m_Dispatcher.AddListener(TweenEvent::UPDATE, fct, proxy);
		return *this;
	}

	template<class P>
	TweenSpec& OnComplete(void (P::*fct)(Event&), P& proxy)
	{
		m_Dispatcher.AddListener(TweenEvent::COMPLETE, fct, proxy);
		return *this;
	}

	void Init() override
	{
		if (!m_IsFromSet)
		{
			m_From = (&m_Target->*Get)();
		}
	}

	void Update(float deltaTime) override
	{
		if (m_State == STOPPED) return;

		if (m_State == PLAYING)
		{
			UpdateTween(deltaTime);
			return;
		}

		m_ElapsedDelay += deltaTime;

		if (m_ElapsedDelay < m_Delay)
		{
			m_State = DELAYED;
		}
		else
		{
			m_State = PLAYING;
		}
	}

private:
	void UpdateTween(float deltaTime)
	{
		m_Elapsed += deltaTime;
		float p = m_Elapsed / m_Duration;
		if (p >= 1.0f)
		{
			p = 1.0f;
		}

		float k = m_EaseFct(p);
		V v = Interpolate(m_From, m_To, k);
		(&m_Target->*Set)(v);

		TweenEvent updateEvt(TweenEvent::UPDATE, *this);
		m_Dispatcher.Dispatch(updateEvt);

		if (p == 1.0f)
		{
			Stop();

			TweenEvent completeEvt(TweenEvent::COMPLETE, *this);
			m_Dispatcher.Dispatch(completeEvt);
		}
	}

	V Interpolate(V a, V b, float v)
	{
		return V(a + (b - a) * v);
	}

};

typedef TweenSpec<int, IDisplay, &IDisplay::GetX, &IDisplay::SetX> TweenX;


#endif
