#include <iostream>
#include "Rounds.h"

Rounds::Rounds() : CurrentRound(0),totalGuests(0),roundOver(0){}

Rounds::~Rounds() {}

void Rounds::StartRound() {
    roundOver = false;
    totalGuests = 3;
    std:: cout << "round " << CurrentRound << " started " << std::endl;
}
void Rounds::Update() {
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

