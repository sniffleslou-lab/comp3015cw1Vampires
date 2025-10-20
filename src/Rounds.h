#include <iostream>
#include "SDL.h"

class Rounds{
    public:
        Rounds();
        ~Rounds();

        void StartRound();
        void Update();
        void render(SDL_Renderer *renderer);
        bool isRoundOver() const;



private:
    int CurrentRound;
    int totalGuests;
    bool roundOver;


    //timer stuff finish this later
    Uint32 roundStartTime;
    Uint32  roundDuration;
};