#ifndef _S3EINPUTADAPTER_H_
#define _S3EINPUTADAPTER_H_

#include <SDL.h>
#include "InputAdapter.h"

class SDLInputAdapter : public InputAdapter
{
public:
    SDLInputAdapter() {}
    ~SDLInputAdapter() {}

    virtual bool Update(float deltaTime = 0.0f) override;

private:
    static const int DEFAULT_TOUCH_ID;

    SDL_Event m_event;
    int x, y;
};

#endif