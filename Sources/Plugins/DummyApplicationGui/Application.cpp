#include "Application.h"
#include <SDL3/SDL.h>

using namespace Plugins::DummyApplicationGui;

int Application::run(int argc, char **argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) == false)
    {
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("PluginDummyApplicationGui", 640, 480, 0);

    if (window == nullptr)
    {
        return 1;
    }

    SDL_Surface* surface = SDL_GetWindowSurface(window);

    while (true)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event) == true)
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                SDL_DestroyWindow(window);

                SDL_Quit();

                return 0;
            }
        }
        
        SDL_FillSurfaceRect(surface, nullptr, SDL_MapSurfaceRGB(surface, 0xFF, 0xFF, 0xFF));

        SDL_UpdateWindowSurface(window);
    }
}