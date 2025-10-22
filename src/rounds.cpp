#include <iostream>
#include "Rounds.h"

Rounds::Rounds() : CurrentRound(0),totalGuests(0),roundOver(0), roundStartTime(0), roundDuration(90000){}

Rounds::~Rounds() {}

void Rounds::StartRound() {
    roundOver = false;
    totalGuests = 3;
    roundStartTime = SDL_GetTicks();
    std:: cout << "round " << CurrentRound << " started " << std::endl;
}
void Rounds::Update() {
    Uint32 elapsedTime = SDL_GetTicks() - roundStartTime;
    if(elapsedTime >= roundDuration){
        roundOver = true;
        std::cout << "round over!" << std::endl;
    }
    totalGuests <=0;{
        roundOver = true;
        totalGuests +=2;
    }
}

void Rounds::render(SDL_Renderer *renderer) {
    //just a shell atm need to do
}
bool Rounds::isRoundOver() const {
    return roundOver;
}

