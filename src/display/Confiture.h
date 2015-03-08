#ifndef _CONFITURE_H_
#define _CONFITURE_H_

#include "RenderSupport.h"
#include "Stage.h"
#include "utils\Rectangle.h"
#include "core\Updateable.h"
#include "core\Renderable.h"

class Confiture : public Updateable, public Renderable
{
public:
    explicit Confiture(bootplease::Rectangle viewport)
        : m_Viewport(viewport), m_Stage(viewport.m_Width, viewport.m_Height) {}

    static const char* ID;

    Stage&  GetStage() { return m_Stage; }

    void Update(float deltaTime) override;
    void Render() override;

private:
    Stage                   m_Stage;
    RenderSupport           m_RenderSupport;
    bootplease::Rectangle   m_Viewport;
};

#endif