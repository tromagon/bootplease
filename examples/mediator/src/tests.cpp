#include "tests.h"

const char* SomeView::VIEW_ID = "SomeView_VIEW_ID";

Tests::Tests()
{
	viewFactory = new ViewFactory();
	mediatorFactory = new MediatorFactory();

	mediatorMap = new MediatorMap();
	mediatorMap->Map(SomeView::VIEW_ID, &ViewFactory::GetSomeView, *viewFactory).To(&MediatorFactory::GetSomeMediator, *mediatorFactory);

	View* someView = mediatorMap->GetView(SomeView::VIEW_ID);
}

Tests::~Tests()
{
	delete mediatorMap;
}