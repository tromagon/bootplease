// InjectorTests.cpp : main project file.

#include "stdafx.h"
#include "injection\Injector.h"
#include "InjectorTests.h"

using namespace System;

const char* InjectionID::MODEL_A = "InjectionID_MODEL_A";
const char* InjectionID::MODEL_B = "InjectionID_MODEL_B";

int main(array<System::String ^> ^args)
{
    Console::WriteLine(L"Starting InjectorTests");

    ModelA* modelA = new ModelA();
    ModelB* modelB = new ModelB();

    Injector injector;

    injector.Map(modelA, InjectionID::MODEL_A);
    //injector.Map(modelB, InjectionID::MODEL_B);

    if (injector.GetInstanceById<ModelA>(InjectionID::MODEL_A))
    {
        Console::WriteLine(L"Model A found in injector");
    }

    injector.UnMap(modelA);
    
    if (!injector.GetInstanceById<ModelA>(InjectionID::MODEL_A))
    {
        Console::WriteLine(L"Model A removed from injector");
    }

    injector.UnMap(InjectionID::MODEL_B);

    if (!injector.GetInstanceById<ModelB>(InjectionID::MODEL_B))
    {
        Console::WriteLine(L"Model B removed from injector");
    }

    system("pause");
    return 0;
}