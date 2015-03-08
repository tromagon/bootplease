#ifndef  _UPDATEABLE_H_
#define  _UPDATEABLE_H_

class Updateable
{
public:
    Updateable() {}
    virtual ~Updateable() {}

    virtual bool Update(float deltaTime = 0.0f) = 0;
};

#endif
