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
        //for rounds
        bool allGuestsSeen() const;
        int getCurrentRound()const{return CurrentRound;}
        void startNextRound(SDL_Renderer* renderer);





private:
    size_t currentGuestIndex = 0;
    int CurrentRound = 1;
    int totalGuests = 3;
    bool roundOver = false;


    //timer stuff finish this later
    Uint32 roundStartTime = 0;
    Uint32  roundDuration = 90000;

    std::vector<Guest> guests;
};