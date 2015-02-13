// ContextTests.cpp : main project file.

#include "stdafx.h"
#include "context\Context.h"
#include "ContextTests.h"
#include <iostream>

using namespace System;
using namespace std;

const char* SomeModel::ID = "someModelId";

void CustomConfig::Configure()
{
    cout << "Custom Config configuration" << endl;
    SomeModelPtr someModel = SomeModelPtr(new SomeModel());
    GetInjector().Map(someModel, SomeModel::ID);
}

SomeModel::SomeModel() 
{
    cout << "SomeModel construction" << endl;
}

SomeModel::~SomeModel() 
{
    cout << "SomeModel destruction" << endl;
}

int main(array<System::String ^> ^args)
{
    Context context;
    context.AddConfig<CustomConfig>();
    context.Execute();

    system("pause");

    return 0;
}
