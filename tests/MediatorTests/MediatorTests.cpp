// MediatorTests.cpp : main project file.

#include "stdafx.h"
#include <iostream>

#include "MediatorTests.h"
#include "mediator\MediatorMap.h"

using namespace System;
using namespace std;

const char* ViewA::ID = "ViewA";

void MediatorA::OnInitialized()
{
    cout << "Mediator A initialized" << endl;
}

int main(array<System::String ^> ^args)
{
    Console::WriteLine(L"Starting MediatorTests");

    Config config;
    InjectorPtr injector;
    EventDispatcherPtr eventDispatcher;

    MediatorMap mediatorMap(eventDispatcher, injector);
    mediatorMap.Map(ViewA::ID, &Config::GetView, config).To(&Config::GetMediator, config);

    ViewA* view = mediatorMap.GetView<ViewA>(ViewA::ID);

    system("pause");
    return 0;
}