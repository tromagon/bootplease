#include "injection\Injector.h"

bool Injector::HasInjection(const char* id)
{
    auto it = m_Map.find(id);
    return (it != m_Map.end());
}

void Injector::UnMap(const char* id)
{
    m_Map.erase(m_Map.find(id));
    m_NumInjections--;
}

void Injector::UnMapAll()
{
    m_Map.clear();
    m_NumInjections = 0;
}