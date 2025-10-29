#pragma once
#include "SDL.h"
#include "Rounds.h"
#include "Guests.h"

class Game{
public:
    Game();
    ~Game();

    bool init(const char* title, int width, int height);
    void handleEvents();
    void update();
    void render();
    void clean();

    bool isRunning() const{ return running; }
    SDL_Renderer* getRenderer()const;

private:
    bool running;
    SDL_Window* window;
    SDL_Renderer* renderer;
    //buttons bellow
    SDL_Texture*KickButtonTexture;
    SDL_Texture*LetInButtonTexture;
    SDL_Rect kickButtonReact;
    SDL_Rect letInButtonReact;
    //text box
    SDL_Texture*TextBoxTexture;
    SDL_Rect  textBoxReact;
    Rounds rounds;
};