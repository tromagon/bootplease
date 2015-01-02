#ifndef _TESTS_H_
#define _TESTS_H_

#include "MediatorMap.h"
#include <iostream>

class ModelA {};

class InjectionID
{
public:
	static const char* MODEL_A;
};

class SomeView : public View
{
public:
	static const char* VIEW_ID;

public:
	int someInt;

public:
	SomeView() : someInt(64) {};
	~SomeView() {};	
};


class SomeMediator : public Mediator
{
public:
	SomeMediator() {};
	~SomeMediator() {};	

	void OnInitialized() override;

	SomeView& GetSomeView() { return static_cast<SomeView&>(GetView()); }
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


