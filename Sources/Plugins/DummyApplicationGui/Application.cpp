#include "Application.h"
#include <SDL3/SDL.h>
#include <string>

using namespace Plugins::DummyApplicationGui;

constexpr int kScreenWidth{ 640 };
constexpr int kScreenHeight{ 480 };

/* Global Variables */
//The window we'll be rendering to
SDL_Window* gWindow{ nullptr };

//The surface contained by the window
SDL_Surface* gScreenSurface{ nullptr };

//The image we will load and show on the screen
SDL_Surface* gHelloWorld{ nullptr };

bool init()
{
    //Initialization flag
    bool success{ true };

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) == false)
    {
        SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        //Create window
        if (gWindow = SDL_CreateWindow("SDL3 Tutorial: Hello SDL3", kScreenWidth, kScreenHeight, 0); gWindow == nullptr)
        {
            SDL_Log("Window could not be created! SDL error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            //Get window surface
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }

    return success;
}

bool loadMedia()
{
    //File loading flag
    bool success{ true };

    //Load splash image
    std::string imagePath{ "01-hello-sdl3/hello-sdl3.bmp" };
    if (gHelloWorld = SDL_LoadBMP(imagePath.c_str()); gHelloWorld == nullptr)
    {
        SDL_Log("Unable to load image %s! SDL Error: %s\n", imagePath.c_str(), SDL_GetError());
        success = true;
    }

    return success;
}

void close()
{
    //Clean up surface
    SDL_DestroySurface(gHelloWorld);
    gHelloWorld = nullptr;

    //Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;
    gScreenSurface = nullptr;

    //Quit SDL subsystems
    SDL_Quit();
}

int Application::run(int argc, char **argv)
{
    //Final exit code
    int exitCode{ 0 };

    //Initialize
    if (init() == false)
    {
        SDL_Log("Unable to initialize program!\n");
        exitCode = 1;
    }
    else
    {
        //Load media
        if (loadMedia() == false)
        {
            SDL_Log("Unable to load media!\n");
            exitCode = 2;
        }
        else
        {
            //The quit flag
            bool quit{ false };

            //The event data
            SDL_Event e;
            SDL_zero(e);

            //Fill the surface white
            SDL_FillSurfaceRect(gScreenSurface, nullptr, SDL_MapSurfaceRGB(gScreenSurface, 0xFF, 0xFF, 0xFF));

            //Render image on screen
            SDL_BlitSurface(gHelloWorld, nullptr, gScreenSurface, nullptr);

            //Update the surface
            SDL_UpdateWindowSurface(gWindow);
        }
    }

    //Clean up
    close();

    return exitCode;
}