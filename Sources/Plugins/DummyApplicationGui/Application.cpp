#include "Application.h"
#include <iostream>
#include <SDL3/SDL.h>

using namespace Plugins::DummyApplicationGui;

int Application::run(int argc, char **argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) == false)
    {
        std::cerr << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("PluginDummyApplicationGui", 640, 480, 0);

    if (window == nullptr)
    {
        std::cerr << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);

    if (renderer == nullptr)
    {
        std::cerr << SDL_GetError() << std::endl;
        return 1;
    }

    while (true)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event) == true)
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                
                SDL_Quit();

                return 0;
            }
        }
        
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderLine(renderer, 0, 0, 100, 100);

        SDL_FRect rectangle;
        rectangle.x = 100;
        rectangle.y = 100;
        rectangle.w = 100;
        rectangle.h = 100;

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &rectangle);

        SDL_RenderPresent(renderer);
    }
}