#pragma once
#include "SDL2/SDL.h"
#include "Rounds.h"
#include "Guests.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"

class Game{
public:
    Game();
    ~Game();

    bool init(const char* title, int width, int height);
    void handleEvents();
    void update();
    void render();
    void clean();
    void setRounds(Rounds* rounds);
    bool isRunning() const{ return running; }
    SDL_Renderer* getRenderer()const;
    void renderText(const std::string& message, int x, int y,TTF_Font* customFont= nullptr);
    enum class Scene{
        Start,
        RoundIntro,
        Gameplay,
        Score
    };
    Scene currentScene = Scene::Start;
    Uint32 sceneStartTime =0;


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
    Rounds* currentRound;
    TTF_Font* font = nullptr;
    TTF_Font* fontLarge = nullptr;
    TTF_Font* fontSmall = nullptr;

    //for background track
    Mix_Music* rainMusic = nullptr;



};
