#ifndef _COMMANDMAP_H_
#define _COMMANDMAP_H_

#include "Context.h"
#include <vector>

using namespace std;

class Command;

class CommandMap
{
private:
	Context&			m_Context;
	vector<Command*>	m_Detained;

protected:
	EventDispatcher&	GetDispatcher()			{ return m_Context.GetDispatcher(); }

public:
	explicit CommandMap(Context& context) : m_Context(context) {}
	~CommandMap() {}

	void				Detain(Command& command);
	void				Release(Command& command);

protected:
	int					GetDetainedIndex(Command& command);
};

#endif
