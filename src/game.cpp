#include <iostream>
#include "Game.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

Game::Game() : window(nullptr),
renderer(nullptr),
running(false),
KickButtonTexture(nullptr),
LetInButtonTexture(nullptr),
TextBoxTexture(nullptr)

{}

Game::~Game(){}

bool Game::init(const char *title, int width, int height) {
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (!window) return false;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) return false;
    if(!(IMG_Init(IMG_INIT_PNG )&(IMG_INIT_PNG))){
        std::cerr << "IMG_InitFailed " << IMG_GetError() << std::endl;
    }
    char *basePath =SDL_GetBasePath();
    if (basePath){
        std::cout << "current working path is " << basePath << std::endl;
        SDL_free(basePath);
    }else{
        std::cerr << "SDL_GetBasePath Failed: " << SDL_GetError()<< std::endl;
    }
    if(TTF_Init()==-1){
        std::cerr << "ttf_init failed " << TTF_GetError() << std::endl;
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
    //textbox
    tempSurface = IMG_Load("../assets/textures/BorderOutline.png");
    if (!tempSurface){
        std::cerr <<"failed to load border: " << IMG_GetError() << std::endl;
    }else
    {
        TextBoxTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
        SDL_FreeSurface(tempSurface);
    }
    //font
    font = TTF_OpenFont("../assets/fonts/BLKCHCRY.TTF", 24);
    if(!font){
        std::cerr << "failed to load font: " << TTF_GetError() << std::endl;
    }
    //kickButtonReact = {100,400,128,64};
   // letInButtonReact = {100,400,128,64};
    kickButtonReact = {100,450,256,128};
    letInButtonReact = {450,450,256,128};
    textBoxReact = {20,260,760,180};


    running = true;
    return true;

}
SDL_Renderer* Game::getRenderer()const {
    return renderer;
}
void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){
            running = false;
        }
        if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT){
            int x = event.button.x;
            int y = event.button.y;

            if(x >= kickButtonReact.x && x <= kickButtonReact.x + kickButtonReact.w
                && y >= kickButtonReact.y && kickButtonReact.y + kickButtonReact.h)
            {
                std::cout<< "kick pressed\n";
                if(currentRound) currentRound->nextGuest();
            }
            if(x >= letInButtonReact.x && x <= letInButtonReact.x + letInButtonReact.w
               && y >= letInButtonReact.y && letInButtonReact.y + letInButtonReact.h)
            {
                std::cout<< "let in  pressed\n";
               if(currentRound) currentRound->nextGuest();
            }
        }
    }
}
void Game::setRounds(Rounds *rounds) {
    currentRound = rounds;
}
void Game::update(){
 if(rounds.isRoundOver()){
     SDL_Delay(6000);
     rounds.startNextRound(renderer);
 }
}

void Game::render() {
    if(currentRound){
        renderRoundText(currentRound->getCurrentRound());
    }

    //buttons
    kickButtonReact = {100,450,256,128};
    letInButtonReact = {450,450,256,128};
    textBoxReact = {20,290,760,150};
    SDL_RenderCopy(renderer, KickButtonTexture, nullptr, &kickButtonReact);
    SDL_RenderCopy(renderer, LetInButtonTexture, nullptr, &letInButtonReact);
    SDL_RenderCopy(renderer,TextBoxTexture, nullptr,&textBoxReact);


}
void Game::renderRoundText(int roundNumber) {
    SDL_Color white = {255, 255, 255};
    std::string roundText = "round " + std::to_string(roundNumber);
    SDL_Surface *textSurface = TTF_RenderText_Blended(font, roundText.c_str(), white);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_Rect textRect = {320, 270, textSurface->w, textSurface->h};
    SDL_RenderCopy(renderer,texture, nullptr, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(texture);
}

void Game::clean() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(KickButtonTexture);
    SDL_DestroyTexture(LetInButtonTexture);
    SDL_DestroyTexture(TextBoxTexture);
    IMG_Quit();

    SDL_Quit();
}