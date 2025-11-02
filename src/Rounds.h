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
        void nextGuest(bool letIn);
        //for rounds
        bool allGuestsSeen() const;
        int getCurrentRound()const{return CurrentRound;}
        void startNextRound(SDL_Renderer* renderer);
        std::string getScoreSummary()const;
        //starting by displaying info
        std::string  getCurrentGuestInfo() const;
        std::string getEndingMessage() const;

    int getVampiresLetIn() const{return vampiresLetIn;}
    int getHumansLetIn() const{return humansLetIn;}
    int getVampiresKicked() const{return vampiresKicked;}
    int getHumansKicked() const{return humansKicked;}










private:
    size_t currentGuestIndex = 0;
    int CurrentRound = 1;
    int totalGuests = 3;
    bool roundOver = false;

    //working on scores
    int humansLetIn = 0;
    int vampiresLetIn = 0;
    int vampiresKicked = 0;
    int humansKicked = 0;



    //timer stuff finish this later
    Uint32 roundStartTime = 0;
    Uint32  roundDuration = 90000;



    std::vector<Guest> guests;
};