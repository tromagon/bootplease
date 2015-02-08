#include <memory>

class ModelA {};
class ModelB {};

typedef unique_ptr<ModelA> ModelAPtr;
typedef unique_ptr<ModelB> ModelBPtr;

class InjectionID
{
public:
    static const char* MODEL_A;
    static const char* MODEL_B;
    static const char* MODEL_A_2;
};

int main(array<System::String ^> ^args);