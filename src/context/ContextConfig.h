#ifndef _CONTEXTCONFIG_H_
#define _CONTEXTCONFIG_H_

//#include "context\Context.h"
#include <memory>

using namespace std;

class Injector;
typedef unique_ptr<Injector> InjectorPtr;

class EventCommandMap;
typedef unique_ptr<EventCommandMap> EventCommandMapPtr;

class DirectCommandMap;
typedef unique_ptr<DirectCommandMap> DirectCommandMapPtr;

class MediatorMap;
typedef unique_ptr<MediatorMap> MediatorMapPtr;

class Context;

class ContextConfig
{
    friend class Context;
    
public:
    ContextConfig() {}
    ~ContextConfig() {}

    Injector&            GetInjector()           { return *m_Injector; }
    EventCommandMap&     GetEventCommandMap()    { return *m_EventCommandMap; }
    DirectCommandMap&    GetDirectCommandMap()   { return *m_DirectCommandMap; }
    MediatorMap&         GetMediatorMap()        { return *m_MediatorMap; }

protected:
    virtual void Configure() = 0;
    void Dispose() {}

    void                    SetInjector(Injector& value)                    { m_Injector = &value; }
    void                    SetEventCommandMap(EventCommandMap& value)      { m_EventCommandMap = &value; }
    void                    SetDirectCommandMap(DirectCommandMap& value)    { m_DirectCommandMap = &value; }
    void                    SetMediatorMap(MediatorMap& value)              { m_MediatorMap = &value; }

    Injector*               m_Injector;
    EventCommandMap*        m_EventCommandMap;
    DirectCommandMap*       m_DirectCommandMap;
    MediatorMap*            m_MediatorMap;
};

typedef unique_ptr<ContextConfig> ContextConfigPtr;

#endif