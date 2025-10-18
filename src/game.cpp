#include <iostream>
#include "Game.h"

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){
            running = false;
        }
    }

}