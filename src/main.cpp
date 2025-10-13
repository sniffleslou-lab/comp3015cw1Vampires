#include <iostream>
#include "SDL.h"

using namespace std;

void cleanup(SDL_Window *win)
{
    SDL_DestoryWindow(win);
    SDL_Quit();
}

int main (int argc, char * argv[]) {
   if (SDL_Init(SDL_INIT_VIDEO) !=0{
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "error", "Error initializing sdl", nullptr);
        return 1;
    }
    int width = 800;
    int height = 600;
    SDL_Window *win = SDL_CreateWindow("sdl demo", SDL_WINDOWPOS_CENTERED, SDL_WIDNDOWPOS_CENTERED, width, height, 0);

    if (!win){
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", "FAILED TO CREATE WINDOW", nullptr);
        SDL_Quit();
        return 1;
    }
}

