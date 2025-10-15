#pragma once
#include "SDL.h"

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
private:
    bool running;
    SDL_Window* window;
    SDL_Renderer* renderer;
};