#include <iostream>
#include "display\Confiture.h"
#include "display\AssetManager.h"
#include "display\Image.h"

#define PI 3.14159265

using namespace std;

int main(int argc, char* args[])
{
    printf("Display Tests");

    bootplease::Rectangle viewport = bootplease::Rectangle(0, 0, 800, 600);
    Confiture confiture(viewport);

    AssetManager assetManager;
    assetManager.loadAtlas("my-atlas", "atlas/my-atlas.png", "atlas/my-atlas.json");

    TextureAtlasPtr& atlas = assetManager.GetTextureAtlas("my-atlas");

    DisplayObjectContainer* container = new DisplayObjectContainer();
    DisplayObjectContainer* root = new DisplayObjectContainer();

    Image* image = new Image(atlas->GetTexture("grid_bgnd.png"));
    confiture.GetStage().AddChild(*root);
    root->AddChild(*container);

    root->SetScaleX(.5f);
    root->SetScaleY(.5f);

    //confiture.GetStage().AddChild(*image);

    //image->SetScaleX(2.f);
    container->AddChild(*image);
    //image->SetX(200);
    //image->SetY(100);
    //image->SetScaleX(2.f);
    //image->SetScaleX(-1.f);
    //image->SetRotation(3.f * M_PI / 4.f);

    //image->SetScaleX(-0.5f);
    //image->SetScaleY(0.5f);
    image->SetX(-100 / 2);
    image->SetY(-100 / 2);

    //image->SetScaleX(.5f);
    container->SetX(100);
    container->SetY(100);

    float angle = 0.f;

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

        angle += 0.01f;
        container->SetRotation(angle);
        confiture.Render();   
    }

    SDL_StopTextInput();
    return 0;
}