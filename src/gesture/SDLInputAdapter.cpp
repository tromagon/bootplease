#include "SDLInputAdapter.h"
#include "utils\Vec2d.h"
#include "TouchesManager.h"
#include <iostream>

using namespace std;

const int SDLInputAdapter::DEFAULT_TOUCH_ID = 0;

bool SDLInputAdapter::Update(float deltaTime)
{
    SDL_PollEvent(&m_event);

    bool quit = false;

    switch(m_event.type)
    {
    case SDL_QUIT:
        quit = true;
        break;

    case SDL_MOUSEMOTION:
        SDL_GetMouseState(&x, &y);
        GetTouchesManager().OnTouchMove(DEFAULT_TOUCH_ID, Vec2d(x, y));
        break;

    case SDL_MOUSEBUTTONDOWN:
        SDL_GetMouseState(&x, &y);
        GetTouchesManager().OnTouchBegin(DEFAULT_TOUCH_ID, Vec2d(x, y));
        break;

    case SDL_MOUSEBUTTONUP:
        SDL_GetMouseState(&x, &y);
        GetTouchesManager().OnTouchEnd(DEFAULT_TOUCH_ID, Vec2d(x, y));
        break;
    }

    return quit;
}