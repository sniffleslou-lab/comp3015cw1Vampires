#pragma once
#include <iostream>
#include "SDL.h"
#include "Guests.h"
#include <vector>

class Rounds{
    public:
        Rounds();
        ~Rounds();

        void StartRound(SDL_Renderer* renderer);
        void Update();
        void render(SDL_Renderer *renderer);
        bool isRoundOver() const;
        void nextGuest();



private:
    size_t currentGuestIndex;
    int CurrentRound;
    int totalGuests;
    bool roundOver;


    //timer stuff finish this later
    Uint32 roundStartTime;
    Uint32  roundDuration;

    std::vector<Guest> guests;
};