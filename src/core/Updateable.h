#ifndef  _UPDATEABLE_H_
#define  _UPDATEABLE_H_

class Updateable
{
public:
	Updateable() {}
	virtual ~Updateable() {}

	virtual void Update(float deltaTime = 0.0f) {}
};

#endif
