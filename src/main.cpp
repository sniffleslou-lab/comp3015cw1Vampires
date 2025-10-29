#include <iostream>
#include "SDL.h"
#include "Game.h"



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

    SDL_Renderer* renderer = Game.Renderer()
    Rounds rounds
    rounds.StartRound(renderer);

//for running
    while (game.isRunning())
    {
        game.handleEvents();
        game.update();
        rounds.update();
        game.render();
        rounds.render(renderer);


    }
    game.clean();
    SDL_Quit();
    return 0;
}
