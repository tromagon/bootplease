#ifndef _TWEEN_H_
#define _TWEEN_H_

#include "events\EventDispatcher.h"
#include "display\DisplayObject.h"
#include "TweenEvent.h"

class Tween : public EventDispatcher
{
public:
    Tween() {}
    virtual ~Tween() {}

    virtual void    Init() {}
    virtual void    Play();
    virtual void    Stop();
    virtual void    Update(float deltaTime) {}
    virtual bool    IsComplete() = 0;

protected:
    static const char STOPPED = 0;
    static const char DELAYED = 1;
    static const char PLAYING = 2;

    char                m_State;
};

typedef shared_ptr<Tween> TweenPtr;


template<class V, class C, V (C::*Get)(), void (C::*Set)(V)>
class TweenSpec : public Tween
{
public:
    explicit TweenSpec(C& target) 
        : m_Target(target), m_Duration(0), m_Delay(0), m_Elapsed(0), 
        m_ElapsedDelay(0), m_FromIsSet(false), m_EasingIsSet(false), m_IsComplete(false) {}
    ~TweenSpec() {}

    TweenSpec& From(V value)
    {
        m_FromIsSet = true;
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
        m_EasingIsSet = true;
        return *this;
    }

    template<class P>
    TweenSpec& OnComplete(void (P::*fct)(const Event&), P& proxy)
    {
        AddListener(TweenEvent::COMPLETE, fct, proxy);
        return *this;
    }

    void Init() override
    {
        if (!m_FromIsSet)
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

    bool IsComplete()
    {
        return m_IsComplete;
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

        float k = (m_EasingIsSet) ? m_EaseFct(p) : p;
        V v = Interpolate(m_From, m_To, k);
        (&m_Target->*Set)(v);

        if (p == 1.0f)
        {
            Stop();

            m_IsComplete = true;

            TweenEvent completeEvt(TweenEvent::COMPLETE, *this);
            Dispatch(completeEvt);
        }
    }

    V Interpolate(V a, V b, float v)
    {
        return V(a + (b - a) * v);
    }

    V       m_From;
    V       m_To;
    C&      m_Target;
    float   m_Duration;
    float   m_Delay;
    float   m_Elapsed;
    float   m_ElapsedDelay;
    bool    m_FromIsSet;
    float   (*m_EaseFct)(float);
    bool    m_EasingIsSet;
    bool    m_IsComplete;

};

typedef TweenSpec<float, DisplayObject, &DisplayObject::GetX, &DisplayObject::SetX> TweenX;
typedef TweenSpec<float, DisplayObject, &DisplayObject::GetY, &DisplayObject::SetY> TweenY;
typedef TweenSpec<float, DisplayObject, &DisplayObject::GetScaleX, &DisplayObject::SetScaleX> TweenScaleX;
typedef TweenSpec<float, DisplayObject, &DisplayObject::GetScaleY, &DisplayObject::SetScaleY> TweenScaleY;

#endif
