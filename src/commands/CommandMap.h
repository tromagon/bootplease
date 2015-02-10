#ifndef _COMMANDMAP_H_
#define _COMMANDMAP_H_

#include "events\EventDispatcher.h"
#include "injection\Injector.h"
#include <vector>
#include <memory>

using namespace std;

class Command;
typedef unique_ptr<Command> CommandPtr;

class CommandMap
{
public:
    explicit CommandMap(EventDispatcherPtr& dispatcher, InjectorPtr& injector) 
        : m_Dispatcher(dispatcher), m_Injector(injector), m_NumMap(0), m_NumDetained(0) {}
    virtual ~CommandMap() {};

    void                    Detain(Command& command);
    void                    Release(Command& command);

    EventDispatcherPtr&     GetDispatcher()                     { return m_Dispatcher; }
    InjectorPtr&            GetInjector()                       { return m_Injector; }

protected:
    vector<CommandPtr>      m_Detained;
    int                     m_NumMap;
    int                     m_NumDetained;
    EventDispatcherPtr&     m_Dispatcher;
    InjectorPtr&            m_Injector;
};

typedef unique_ptr<CommandMap> CommandMapPtr;

#endif