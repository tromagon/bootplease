#ifndef _VIEW_H_
#define _VIEW_H_

#include "EventDispatcher.h"

class View : public EventDispatcher
{
public:
	View() {}
	virtual ~View() {}
};


#endif