#ifndef _ISEQUENCE_H_
#define _ISEQUENCE_H_

#include "EventDispatcher.h"

class ISequence : public EventDispatcher
{
public:
    ISequence() {}
    virtual ~ISequence() {}

    virtual int     IncrementIndex()    { return 0; };
    virtual void    CompleteStep()      {};
    virtual bool    IsNextStepAsync()   { return false; }
};

#endif