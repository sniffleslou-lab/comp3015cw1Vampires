#define SDL_MAIN_HANDLED
#include <iostream>
#include "SDL2/SDL.h"
#include "Game.h"
#include "Rounds.h"
#include "Guests.h"




int main (int argc, char * argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "error", "Error initialising SDL", nullptr);
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
}
