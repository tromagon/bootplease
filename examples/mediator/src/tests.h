#ifndef _TESTS_H_
#define _TESTS_H_

#include "MediatorMap.h"
#include <iostream>


class SomeView : public View
{
public:
	static const char* VIEW_ID;

public:
	SomeView() {};
	~SomeView() {};	
};


class SomeMediator : public Mediator
{
public:
	SomeMediator() {};
	~SomeMediator() {};	
};


class ViewFactory
{
public:
	ViewFactory() {};
	~ViewFactory() {};

	View& GetSomeView()
	{
		return *(new SomeView());
	}
};


class MediatorFactory
{
public:
	MediatorFactory() {};
	~MediatorFactory() {};

	Mediator& GetSomeMediator()
	{
		return *(new SomeMediator());
	}
};


class Tests
{
private:
	ViewFactory*		viewFactory;
	MediatorFactory*	mediatorFactory;
	MediatorMap*		mediatorMap;

public:
	Tests();
	~Tests();

	void Update(float deltaTime) {};
};




#endif

