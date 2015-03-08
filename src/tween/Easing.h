#ifndef _EASING_H_
#define _EASING_H_

class Linear
{
public:
    static float EaseNone(float p)
    {
        return p;
    }
};

#endif