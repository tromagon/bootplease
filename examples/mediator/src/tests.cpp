#include "tests.h"
#include "Injector.h"

const char* SomeView::VIEW_ID = "SomeView_VIEW_ID";
const char* InjectionID::MODEL_A = "InjectionID_MODEL_A";

Tests::Tests()
{
	Injector injector;
	ModelA* modelA = new ModelA();
	injector.Map(modelA, InjectionID::MODEL_A);

	viewFactory = new ViewFactory();
	mediatorFactory = new MediatorFactory();

	mediatorMap = new MediatorMap();
	injector.SetMediatorMap(*mediatorMap);

	View* someView = mediatorMap->GetView(SomeView::VIEW_ID);
	if (!someView)
	{
		cout << "SomeView could not be found" << endl;
	}

	mediatorMap->Map(SomeView::VIEW_ID, &ViewFactory::GetSomeView, *viewFactory).To(&MediatorFactory::GetSomeMediator, *mediatorFactory);
	someView = mediatorMap->GetView(SomeView::VIEW_ID);
}

Tests::~Tests()
{
	delete mediatorMap;
	delete mediatorFactory;
	delete viewFactory;
}

void SomeMediator::OnInitialized()
{
	cout << "SomeMediator is initialized" << endl;

	if (GetInjector().GetInstanceById<ModelA>(InjectionID::MODEL_A))
	{
		cout << "Model A found in injector" << endl; 
	}
}