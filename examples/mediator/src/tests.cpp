#include "tests.h"

const char* SomeView::VIEW_ID = "SomeView_VIEW_ID";

Tests::Tests()
{
	viewFactory = new ViewFactory();
	mediatorFactory = new MediatorFactory();

	mediatorMap = new MediatorMap();

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