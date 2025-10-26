#include <SDL.h>
#include <iostream>
#include "Rounds.h"
#include "Guests.h"
#include "SDL_image.h"
#include "SDL_rect.h"


Rounds::Rounds() : CurrentRound(0),totalGuests(0),roundOver(0), roundStartTime(0), roundDuration(90000){}

Rounds::~Rounds() {}

void Rounds::StartRound() {
    roundOver = false;
    totalGuests = 3 +(CurrentRound - 1) * 2;
    roundStartTime = SDL_GetTicks();
    std:: cout << "round " << CurrentRound << " started " << std::endl;

    guests.clear();

  //  guests = loadGuest("../assets/data/guestList.json", "../assets/data/vampire_traits.json"),3;

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
    int y = 100;
    SDL_Rect dstRect;

    for (auto& g : guests)
    {
        SDL_Surface*tempSurface = IMG_Load(g.portraitPath.c_str());
        if(!tempSurface)
        {
            std::cerr << "failed to load painting: " << IMG_GetError()<< std::endl;
            continue;
        }
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,tempSurface);
        SDL_FreeSurface(tempSurface);
        SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
        SDL_DestroyTexture(texture);
        x+= 200;
    }
}
bool Rounds::isRoundOver() const {
    return roundOver;
}

