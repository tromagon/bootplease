#ifndef _CONTEXT_H_
#define _CONTEXT_H_

class Renderable;
class Updateable;
class Renderer;
class UpdateManager;
class EventDispatcher;
class Injector;
class EventCommandMap;
class DirectCommandMap;
class MediatorMap;
class ContextConfig;

class Context
{
private:
	EventDispatcher*	m_Dispatcher;
	Injector*			m_Injector;
	EventCommandMap*	m_EventCommandMap;
	DirectCommandMap*	m_DirectCommandMap;
	MediatorMap*		m_MediatorMap;
	ContextConfig*		m_Config;
	UpdateManager*		m_UpdateManager;
	Renderer*			m_Renderer;
		
public:
	EventDispatcher&	GetDispatcher()			{ return *m_Dispatcher; }
	Injector&			GetInjector()			{ return *m_Injector; }
	EventCommandMap&	GetEventCommandMap()	{ return *m_EventCommandMap; }
	DirectCommandMap&	GetDirectCommandMap()	{ return *m_DirectCommandMap; }
	MediatorMap&		GetMediatorMap()		{ return *m_MediatorMap; }
	
public:
	Context();
	~Context();

	void Update(float deltaTime = 0.0f);
	void Render();

	void Configure(ContextConfig& config);
	void Execute();

	void AddToUpdate(Updateable& updateable);
	void AddToRenderer(Renderable& renderable);
	void RemoveFromUpdate(Updateable& updateable);
	void RemoveFromRenderer(Renderable& renderable);

	void Dispose();
};

#endif