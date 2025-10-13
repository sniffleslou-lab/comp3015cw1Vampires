#include <iostream>
#include "SDL.h"

using namespace std;

void cleanup(SDL_Window *win)
{
    SDL_DestroyWindow(win);
    SDL_Quit();
}

int main (int argc, char * argv[])
{
   if (SDL_Init(SDL_INIT_VIDEO) !=0)
   {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "error", "Error initializing sdl", nullptr);
        return 1;
    }
    int width = 800;
    int height = 600;
    SDL_Window *win = SDL_CreateWindow("SDL Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);

    if (!win){
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", "FAILED TO CREATE WINDOW", nullptr);
        SDL_Quit();
        return 1;
    }
    //for testing, event loop
    bool running = true;
    SDL_Event event;
    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT){
                running = false;
            }
        }

    }
    cleanup(win);
    return 0;
}

