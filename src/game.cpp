#include <SDL2/SDL.h>
#include <iostream>
#include "Game.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <sstream>
#include "fstream"
#include <SDL2/SDL_mixer.h>

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
    std::cout << "SDL base path: " << basePath << std::endl;
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
    std::ifstream test("../assets/textures/KickButton.png");
    if (!test.is_open()) {
        std::cerr << "File not found or unreadable." << std::endl;
    }
    else {
        std::cerr << "File exists and is readable." << std::endl;
    }
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
    }
    //kick button
    std::string path = "../assets/textures/KickButton.png";
    std::cout << "Attempting to load: " << path << std::endl;
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
    //SMALL FONT& LARGE font
    fontSmall = TTF_OpenFont("../assets/fonts/BLKCHCRY.TTF", 20);
    fontLarge = TTF_OpenFont("../assets/fonts/BLKCHCRY.TTF", 50);

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2,2048)<0){
        std::cerr<< "SDL_mizer cannot initalize: " << Mix_GetError() << std::endl;
    }
    rainMusic = Mix_LoadMUS("../assets/sounds/calming-rain.wav");
    if (!rainMusic){
        std::cerr << "failed to load rain: " << Mix_GetError()<< std::endl;
    }else{
        Mix_PlayMusic(rainMusic, -1);
        Mix_VolumeMusic(3);
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
                if(currentRound) currentRound->nextGuest(false);
            }
            if(x >= letInButtonReact.x && x <= letInButtonReact.x + letInButtonReact.w
               && y >= letInButtonReact.y && letInButtonReact.y + letInButtonReact.h)
            {
                std::cout<< "let in  pressed\n";
               if(currentRound) currentRound->nextGuest(true);
            }
        }
    }
}
void Game::setRounds(Rounds *rounds) {
    currentRound = rounds;
}
void Game::update(){
/*
 if(rounds.isRoundOver()){
     SDL_Delay(6000);
     rounds.startNextRound(renderer);
 }*/
Uint32 now = SDL_GetTicks();

    switch (currentScene) {
        case Scene:: Start:
            if (now - sceneStartTime > 2000){
                currentScene = Scene::RoundIntro;
                sceneStartTime = SDL_GetTicks();
            }break;

        case Scene::RoundIntro:
            if(SDL_GetTicks()- sceneStartTime > 2000){
                currentScene=Scene::Gameplay;
                sceneStartTime = SDL_GetTicks();
            } break;
            case Scene::Gameplay:
                if (currentRound->isRoundOver()) {
                    if (currentRound->getCurrentRound() == 3)
                    {
                        currentScene = Scene::Score;
                        sceneStartTime = SDL_GetTicks();
                    } else {
                        currentRound->startNextRound(renderer);
                        currentScene = Scene::RoundIntro;
                        sceneStartTime = now;
                    }
                }break;
        case Scene::Score:
            renderText("Final Score", 300, 150);
            renderText(currentRound->getScoreSummary(),200,200);
            break;
            }

}

void Game::render() {


    switch (currentScene) {
        case Scene::Start:

            break;
        case Scene::RoundIntro:
            if (currentRound) {
                int roundNum = currentRound->getCurrentRound();

                if (roundNum == 1) {
                    renderText("Portraits of a Vampyre", 250, 150,fontLarge);
                    renderText("You're employed as a doorman at Rylatt's manor.", 200, 220);
                    renderText("You must only let humans in.. and not vampires.", 180, 260);
                }
                std::string roundMessage = "Round " + std::to_string(roundNum);
                renderText(roundMessage, 320, 300);
            }

            break;
        case Scene::Gameplay: {
            if (currentRound) {
                currentRound->render(renderer);
            }
            //buttons
            kickButtonReact = {100, 450, 256, 128};
            letInButtonReact = {450, 450, 256, 128};
            textBoxReact = {20, 290, 760, 150};
            SDL_RenderCopy(renderer, KickButtonTexture, nullptr, &kickButtonReact);
            SDL_RenderCopy(renderer, LetInButtonTexture, nullptr, &letInButtonReact);
            SDL_RenderCopy(renderer, TextBoxTexture, nullptr, &textBoxReact);

            std::string guestInfo = currentRound->getCurrentGuestInfo();
            int textY = textBoxReact.y + 20;

            std::istringstream guestStream(guestInfo);
            std::string guestLine;
            while (std::getline(guestStream,guestLine)){
                renderText(guestLine,textBoxReact.x + 20, textY,fontSmall);
                textY +=30;

            }
            break;
        }
        case Scene::Score: {
            renderText("final score", 300, 150,fontLarge);
            std::string summary = currentRound->getScoreSummary();
            int y = 200;
            std::istringstream stream(summary);
            std::string line;
            while (std::getline(stream, line)) {
                renderText(line, 200, y);
                y += 40;
            }
            std::string endingMessage = currentRound->getEndingMessage();

            std::istringstream endStream(endingMessage);
            std::string endLine;
            while (std::getline(endStream,endLine)){
                renderText(endLine,200,y,font);
                y+=40;
            }

            break;
        }

    }


}
void Game::renderText(const std::string& message, int x, int y, TTF_Font* customFont){

    SDL_Color white = { 255,255,255};
    TTF_Font* useFont = customFont ? customFont : font;
    SDL_Surface* textSurface= TTF_RenderText_Blended(useFont, message.c_str(), white);
    if(!textSurface){
        std::cerr << "failed to create text surface: " << TTF_GetError()<< std::endl;
        return;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,textSurface);
    if(!texture){
        std::cerr<<"failed to create texture: " << SDL_GetError()<< std::endl;
        SDL_FreeSurface(textSurface);
        return;
    }
    SDL_Rect textRect={x,y,textSurface->w,textSurface->h};
    SDL_RenderCopy(renderer,texture, nullptr,&textRect);
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
    Mix_FreeMusic(rainMusic);
    Mix_CloseAudio();

    SDL_Quit();
}

