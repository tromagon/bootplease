#ifndef _INJECTOR_H_
#define _INJECTOR_H_

#include <unordered_map>
#include <memory>

using namespace std;

class Injector
{
public:
    Injector() : m_NumInjections(0) {}

    int     GetNumInjections() { return m_NumInjections; }
    bool    HasInjection(const char* id);
    void    UnMap(const char* id);

    template<class C>
    bool    HasInjection(C& obj);

    template<class C>
    void    Map(C& obj, const char* id);

    template<class C>
    void    UnMap(C& obj);

    template<class C>
    C&      GetInstanceById(const char* id);

private:
    class IInjectorMappingSpec
    {
    public:
        IInjectorMappingSpec() {};
        virtual ~IInjectorMappingSpec() {};
    };

    typedef unique_ptr<IInjectorMappingSpec> IInjectorMappingSpecPtr;

    template<class C>
    class InjectorMappingSpec : public IInjectorMappingSpec
    {
    public:
        explicit InjectorMappingSpec(C& instance) : m_Instance(instance) {};
        virtual ~InjectorMappingSpec() {};

        C&  GetInstance()   { return m_Instance; }

    private:
        C&  m_Instance;
    };

    class InjectorMapping
    {
    public:
        template<class C>
        InjectorMapping(C& instance) : m_Spec(IInjectorMappingSpecPtr(new InjectorMappingSpec<C>(instance))) {}

        template<class C>
        C&  GetInstance() { return static_cast<InjectorMappingSpec<C>*>(m_Spec.get())->GetInstance(); }

    private:
        IInjectorMappingSpecPtr     m_Spec;
    };

    typedef unique_ptr<InjectorMapping> InjectorMappingPtr;

    void    UnMapAll();

    unordered_map<const char*, InjectorMappingPtr>  m_Map;
    int                                             m_NumInjections;
};

template<class C>
bool Injector::HasInjection(C& obj)
{
    for(auto it = begin(m_Map); it != end(m_Map); it++)
    {
        if (it->second->GetInstance<C>() == obj)
        {
            return true;
        }
    }

    return false;
}

template<class C>
void Injector::Map(C& instance, const char* id)
{
    m_Map[id] = InjectorMappingPtr(new InjectorMapping(instance));
    m_NumInjections++;
}

template<class C>
void Injector::UnMap(C& obj)
{
    for(auto it = begin(m_Map); it != end(m_Map); it++)
    {
        if (it->second->GetInstance<C>() == obj)
        {
            m_NumInjections--;
            m_Map.erase(it->first);
            return;
        }
    }
}

template<class C>
C& Injector::GetInstanceById(const char* id)
{
    return m_Map[id]->GetInstance<C>();
}

#endif