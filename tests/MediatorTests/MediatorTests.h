#include "mediator\Mediator.h"
#include "mediator\View.h"

class MediatorA : public Mediator
{
public:
    MediatorA();
    ~MediatorA();

    virtual void OnInitialized() override;
};

class ViewA : public View
{
public:
    static const char* ID;

public:
    ViewA();
    ~ViewA();
};

class Config
{
public:
    Mediator& GetMediator() { return *(new MediatorA()); }
    View& GetView()         { return *(new ViewA()); }
};