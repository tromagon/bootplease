#ifndef _HITTESTER_H_
#define _HITTESTER_H_

#include "Stage.h"

class HitTester
{
private:
    Stage& m_Stage;

public:
    HitTester(Stage& stage) : m_Stage(stage) {}
    virtual ~HitTester() {}

    DisplayObject& HitTest(Vec2d point);
};


#endif