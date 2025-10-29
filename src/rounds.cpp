#include <SDL.h>
#include <iostream>
#include "Rounds.h"
#include "Guests.h"
#include "SDL_image.h"
#include "SDL_rect.h"


Rounds::Rounds() : CurrentRound(1),totalGuests(0),roundOver(false), roundStartTime(0), roundDuration(90000){}

Rounds::~Rounds() {}

void Rounds::StartRound(SDL_Renderer* renderer) {
    roundOver = false;
    totalGuests = 3 +(CurrentRound - 1) * 2;
    roundStartTime = SDL_GetTicks();
    std:: cout << "round " << CurrentRound << " started " << std::endl;
    guests.clear();
    loadData();

    for(auto& g : guests){
        SDL_Surface* tempSurface = IMG_Load(g.portraitPath.c_str());
        if(!tempSurface){
            std::cerr<< "failed to load portrait: " << g.portraitPath << " | " <<IMG_GetError() << "\n";
            continue;
        }
        g.texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
        SDL_FreeSurface(tempSurface);

    }

  //  guests = loadGuest("../assets/data/guestList.json", "../assets/data/vampire_traits.json"),3;

}
void Rounds::Update() {
    Uint32 elapsedTime = SDL_GetTicks() - roundStartTime;
    if(elapsedTime >= roundDuration){
        roundOver = true;
        std::cout << "round over!" << std::endl;
    }
   if (totalGuests <=0){
        roundOver = true;
        totalGuests +=2;
    }
}

void Rounds::render(SDL_Renderer *renderer) {
    int x = 50;
    int y = 100;
    int portraitWidth = 150;
    int portraitHeight = 150;

    //this sections draws guest portraits
    for(size_t i =0; i < guests.size();++i){
        Guest& g =guests[i];

        if(!g.texture) continue;

            SDL_Rect dstRect = {
                    x + static_cast<int>(i*(portraitWidth +20)),y,portraitWidth,portraitHeight
            };

            SDL_RenderCopy(renderer,g.texture, nullptr,&dstRect);
    }
}
bool Rounds::isRoundOver() const {
    return roundOver;
}

