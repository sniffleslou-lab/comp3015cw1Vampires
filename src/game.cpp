#include <iostream>
#include "Game.h"
#include "SDL_image.h"

Game::Game() : window(nullptr),
renderer(nullptr),
running(false),
KickButtonTexture(nullptr),
LetInButtonTexture(nullptr)
{}

Game::~Game(){}

bool Game::init(const char *title, int width, int height) {
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (!window) return false;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) return false;
    if(!(IMG_Init(IMG_INIT_PNG)&IMG_INIT_PNG)){
        std::cerr << "IMG_InitFailed " << IMG_GetError() << std::endl;
    }
    char *basePath =SDL_GetBasePath();
    if (basePath){
        std::cout << "current working path is " << basePath << std::endl;
        SDL_free(basePath);
    }else{
        std::cerr << "SDL_GetBasePath Failed: " << SDL_GetError()<< std::endl;
    }

    //loading buttons
    //kick button
    SDL_Surface *tempSurface = IMG_Load("../assets/textures/KickButton.png");
    if (!tempSurface) {
        std::cerr << "failed to load kick button: " << IMG_GetError() << std::endl;
    } else {
        KickButtonTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
        SDL_FreeSurface(tempSurface);
    }
    //let in button
    tempSurface = IMG_Load("../assets/textures/LetInButton.png");
    if (!tempSurface) {
        std::cerr << "failed to load let in button: " << IMG_GetError() << std::endl;
    } else {
        LetInButtonTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
        SDL_FreeSurface(tempSurface);
    }
    kickButtonReact = {100,400,128,64};
    letInButtonReact = {100,400,128,64};
    running = true;
    return true;
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
    kickButtonReact = {100,400,256,128};
    letInButtonReact = {450,400,256,128};
    SDL_RenderCopy(renderer, KickButtonTexture, nullptr, &kickButtonReact);
    SDL_RenderCopy(renderer, LetInButtonTexture, nullptr, &letInButtonReact);

    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(KickButtonTexture);
    SDL_DestroyTexture(LetInButtonTexture);
    IMG_Quit();
    SDL_Quit();
}