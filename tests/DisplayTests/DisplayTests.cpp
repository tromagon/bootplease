#include <iostream>
#include "display\Confiture.h"
#include "display\AssetManager.h"
#include "display\Image.h"
#include "tween\TweenManager.h"
#include "tween\Easing.h"
#include "gesture\SDLInputAdapter.h"
#include "gesture\GestureManager.h"
#include "gesture\TapGesture.h"

#define FRAME_TIME  (30.0f / 1000.0f)

using namespace std;

class GestureHandler
{
public:
    void OnUpTap(const Event& evt);
};

void GestureHandler::OnUpTap(const Event& evt)
{
    cout << "tap tap" << endl;
}

TweenManager tweenManager;
DisplayObjectContainer root;
DisplayObjectContainer container;
DisplayObjectPtr image;
GestureHandler gestureHandler;

int main(int argc, char* args[])
{
    printf("Display Tests");

    bootplease::Rectangle viewport = bootplease::Rectangle(0, 0, 800, 600);
    Confiture confiture(viewport);

    //SDLInputAdapter inputAdapter;
    GestureManager gestureManager = GestureManager(confiture.GetStage()); 
    gestureManager.registerAdapter<SDLInputAdapter>();

    AssetManager assetManager;
    assetManager.loadAtlas("my-atlas", "atlas/my-atlas.png", "atlas/my-atlas.json");

    TextureAtlasPtr& atlas = assetManager.GetTextureAtlas("my-atlas");

    TapGesture* m_UpTap = &(gestureManager.AddGesture<TapGesture>(root, &GestureHandler::OnUpTap, gestureHandler));

    TweenX& tweenX = tweenManager.CreateTween<TweenX>(root);
    tweenX
        .From(0).To(500).Duration(2.0f)
        .Delay(1.0f)
        .Easing(Linear::EaseNone)
        .Play();

    image = DisplayObjectPtr(new Image(atlas->GetTexture("grid_bgnd.png")));
    confiture.GetStage().AddChild(root);
    root.AddChild(container);

    root.SetScaleX(.5f);
    root.SetScaleY(.5f);

    container.AddChild(image);

    image->SetX(-100 / 2);
    image->SetY(-100 / 2);

    container.SetX(100);
    container.SetY(100);

    float angle = 0.f;

    //Main loop flag
    bool quit = false;
        
    //Enable text input
    SDL_StartTextInput();

    //While application is running
    while( !quit )
    {
        quit = gestureManager.Update(FRAME_TIME);

        tweenManager.Update(FRAME_TIME);

        angle += 0.01f;
        container.SetRotation(angle);
        confiture.Render();   
    }

    SDL_StopTextInput();
    return 0;
}