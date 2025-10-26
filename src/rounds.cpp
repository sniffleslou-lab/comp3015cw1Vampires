#include <iostream>
#include "Rounds.h"
#include "Guests.h"

Rounds::Rounds() : CurrentRound(0),totalGuests(0),roundOver(0), roundStartTime(0), roundDuration(90000){}

Rounds::~Rounds() {}

void Rounds::StartRound() {
    roundOver = false;
    totalGuests = 3 +(CurrentRound - 1) * 2;
    roundStartTime = SDL_GetTicks();
    std:: cout << "round " << CurrentRound << " started " << std::endl;

    guests.clear();
    guestPortrait.clear()

    guests = loadGuest("../assets/data/guestList.json", "../assets/data/vampire_traits.json"),3;

}
void Rounds::Update() {
    Uint32 elapsedTime = SDL_GetTicks() - roundStartTime;
    if(elapsedTime >= roundDuration){
        roundOver = true;
        std::cout << "round over!" << std::endl;
    }
   if (totalGuests <=0);{
        roundOver = true;
        totalGuests +=2;
    }
}

void Rounds::render(SDL_Renderer *renderer) {
    int x = 50;
}
bool Rounds::isRoundOver() const {
    return roundOver;
}

