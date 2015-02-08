#ifndef _VIEW_H_
#define _VIEW_H_

#include "events\EventDispatcher.h"

class View : public EventDispatcher
{
public:
	View() {}
	virtual ~View() {}
};


#endif