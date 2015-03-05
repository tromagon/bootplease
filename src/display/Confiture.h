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
    static const char* ID;

private:
    Stage*          m_Stage;
    RenderSupport   m_RenderSupport;
    bootplease::Rectangle       m_Viewport;

public:
    Stage&  GetStage() { return *m_Stage; }

public:
    explicit Confiture(bootplease::Rectangle viewport);
    ~Confiture();

    void Update(float deltaTime) override;

    void Render() override;
};

#endif