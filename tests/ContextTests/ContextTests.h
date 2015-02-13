#include "context\ContextConfig.h"
#include <memory>

using namespace std;

class CustomConfig : public ContextConfig
{
public:
    CustomConfig() {};

    void Configure();
};

class SomeModel
{
public:
    static const char* ID;

public:
    SomeModel();
    ~SomeModel();
};

typedef unique_ptr<SomeModel> SomeModelPtr;