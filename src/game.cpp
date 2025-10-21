#include <iostream>
#include "Game.h"

Game::Game() : window(nullptr),
running(false){}

Game::~Game(){}

bool Game::init(const char *title, int width, int height) {
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,0);
    if (!window) return false;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) return false;
    running =true;
    return true;

    //loading buttons
    
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){
            running = false;
        }
    }
}
void Game::update(){

}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0,0,0,255);//sets the colour as black, due to being aesthetic
    SDL_RenderClear(renderer);

    //buttons

    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}