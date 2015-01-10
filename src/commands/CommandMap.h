#ifndef _COMMANDMAP_H_
#define _COMMANDMAP_H_

#include "Context.h"
#include <vector>

using namespace std;

class Command;

class CommandMap
{
protected:
	Context&			m_Context;
	vector<Command*>	m_Detained;
	int					m_NumMap;
	int					m_NumDetained;

protected:
	EventDispatcher&	GetDispatcher()			{ return m_Context.GetDispatcher(); }

public:
	explicit CommandMap(Context& context) : m_Context(context), m_NumMap(0), m_NumDetained(0) {}
	virtual ~CommandMap();

	void				Detain(Command& command);
	void				Release(Command& command);

protected:
	int					GetDetainedIndex(Command& command);

private:
	void				ClearDetained();
};

#endif
