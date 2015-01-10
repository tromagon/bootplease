#ifndef _INJECTED_H_
#define _INJECTED_H_

class Injector;

class Injected
{
private:
	Injector*	m_Injector;

public:
	Injector&	GetInjector()					{ return *m_Injector; }
	void		SetInjector(Injector& value)	{ m_Injector = &value; }

public:
	Injected() {}
	virtual ~Injected() {}
};


#endif