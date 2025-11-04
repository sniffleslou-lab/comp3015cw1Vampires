#define SDL_MAIN_HANDLED
#include <iostream>
#include <filesystem>
#include "SDL2/SDL.h"  
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"
#include "Game.h"
#include "Path.h"
#include "Rounds.h"
#include "Guests.h"





int main (int argc, char * argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "error", "Error initialising SDL", nullptr);
        return 1;

    }
    //ehhhh I hope this work
    // 
    if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & (IMG_INIT_PNG | IMG_INIT_JPG))) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_image Error", IMG_GetError(), nullptr);
        SDL_Quit();
        return 1;
    }

    // SDL_ttf
    if (TTF_Init() == -1) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_ttf Error", TTF_GetError(), nullptr);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    
    if (!(Mix_Init(MIX_INIT_OGG | MIX_INIT_MP3) & (MIX_INIT_OGG | MIX_INIT_MP3))) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_mixer Error", Mix_GetError(), nullptr);
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Audio Error", Mix_GetError(), nullptr);
        Mix_Quit();
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }
  
//calls game.h basically the same as setup. It shows a message when it fails
    Game game;
    if(!game.init("Vampires", 800, 600)) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", "FAILED TO INITIALISE GAME", nullptr);
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = game.getRenderer();
   /* Rounds rounds;
    game.setRounds(&rounds);
    rounds.StartRound(renderer);*/

    Rounds* r = new Rounds();
    game.setRounds(r);
    r->StartRound(renderer);

//for running
    while (game.isRunning())
    {
        game.handleEvents();
        game.update();

        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);

        game.render();

        SDL_RenderPresent(renderer);
/*
        if (rounds.isRoundOver()){
            std::cout<<"round is over! Next round...." << std::endl;
            rounds.startNextRound(renderer);
        }*/



    }
    delete r;
    game.clean();
    SDL_Quit();
    return 0;

    Mix_CloseAudio();
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}


