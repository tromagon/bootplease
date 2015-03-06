#include <iostream>
#include "display\Confiture.h"
#include "display\AssetManager.h"
#include "display\Image.h"

using namespace std;

int main(int argc, char* args[])
{
    printf("Display Tests");

    bootplease::Rectangle viewport = bootplease::Rectangle(0, 0, 800, 600);
    Confiture confiture(viewport);

    AssetManager assetManager;
    assetManager.loadAtlas("my-atlas", "atlas/my-atlas.png", "atlas/my-atlas.json");

    TextureAtlasPtr& atlas = assetManager.GetTextureAtlas("my-atlas");

    Image* image = new Image(*(atlas->GetTexture("yellow.png")));
    confiture.GetStage().AddChild(*image);

    //Main loop flag
    bool quit = false;

    //Event handler
    SDL_Event e;
        
    //Enable text input
    SDL_StartTextInput();

    //While application is running
    while( !quit )
    {
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
            //Handle keypress with current mouse position
            else if( e.type == SDL_TEXTINPUT )
            {
                int x = 0, y = 0;
                SDL_GetMouseState( &x, &y );
                //handleKeys( e.text.text[ 0 ], x, y );
            }
        }

        confiture.Render();   
    }

    SDL_StopTextInput();
    return 0;
}