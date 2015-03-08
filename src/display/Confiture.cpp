#include "Confiture.h"

const char* Confiture::ID = "Confiture_CONFITURE_ID";

void Confiture::Update(float deltaTime)
{
    // is there anything to update ?
}

void Confiture::Render()
{
    m_RenderSupport.NextFrame();

    m_Stage.Render(m_RenderSupport, 1.0f);

    m_RenderSupport.EndFrame();

    // consider displaying stats here by getting draw count
}