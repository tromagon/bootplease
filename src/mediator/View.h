#ifndef _VIEW_H_
#define _VIEW_H_

#include "events\EventDispatcher.h"
#include <memory>

class View : public EventDispatcher
{
public:
	View() {}
	virtual ~View() {}
};

typedef unique_ptr<View> ViewPtr;


#endif