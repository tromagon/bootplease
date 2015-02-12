// MediatorTests.cpp : main project file.

#include "stdafx.h"
#include <iostream>

#include "MediatorTests.h"
#include "mediator\MediatorMap.h"

using namespace System;
using namespace std;

const char* ViewA::ID = "ViewA";

ViewA::ViewA()
{
    cout << "ViewA constructor" << endl;
}

ViewA::~ViewA()
{
    cout << "ViewA destructor" << endl;
}

MediatorA::MediatorA() 
{
    cout << "MediatorA constructor" << endl;
}

MediatorA::~MediatorA() 
{
    cout << "MediatorA destructor" << endl;
}

void MediatorA::OnInitialized()
{
    cout << "Mediator A initialized" << endl;
}

int main(array<System::String ^> ^args)
{
    Console::WriteLine(L"Starting MediatorTests");

    InjectorPtr injector;
    EventDispatcherPtr eventDispatcher;

    MediatorMap mediatorMap(eventDispatcher, injector);
    mediatorMap.Map<ViewA, MediatorA>(ViewA::ID);

    ViewA& view = mediatorMap.GetView<ViewA>(ViewA::ID);
    mediatorMap.DisposeView(view);

    mediatorMap.UnMap(ViewA::ID);

    system("pause");
    return 0;
}