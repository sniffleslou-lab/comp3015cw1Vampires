#include <SDL.h>
#include <iostream>
#include "Rounds.h"
#include "Guests.h"
#include "SDL_image.h"
#include "SDL_rect.h"
#include <fstream>


Rounds::Rounds() : CurrentRound(1),totalGuests(0),roundOver(false), roundStartTime(0), roundDuration(90000), currentGuestIndex(0){}

Rounds::~Rounds() {}


void Rounds::StartRound(SDL_Renderer* renderer) {

    totalGuests = 3 +(CurrentRound - 1) * 2;
    roundStartTime = SDL_GetTicks();

    std:: cout << "round " << CurrentRound << " started " << std::endl;

    int vampireCount = std::min(1 + CurrentRound / 2, totalGuests);
    //guests = loadGuests(std::string (ASSETS_PATH)+"/data/guestList.json",std::string(ASSETS_PATH)+"/data/vampire_traits.json",2);
    guests = loadGuests(
            std::string (ASSETS_PATH)+"/data/guestList.json",
                        std::string
                        (ASSETS_PATH)+"/data/vampire_traits.json",
                        totalGuests, vampireCount
                        );

    std::unordered_map<std::string, SDL_Texture*> textureCache;

    for(auto& g : guests){
        //testing if I am reusing because I am crying
        if(textureCache.find(g.portraitPath) != textureCache.end()){
            g.texture = textureCache[g.portraitPath];
            continue;
        }
        std::ifstream test(g.portraitPath);
        if(!test.good()){
            std::cerr << "portrait file not found: " << g.portraitPath<<std::endl;
            continue;
        }

        SDL_Surface* tempSurface = IMG_Load(g.portraitPath.c_str());
        if(!tempSurface){
            std::cerr<< "failed to load portrait: " << g.portraitPath << " | " <<IMG_GetError() << std::endl;
            continue;
        }
        g.texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
        SDL_FreeSurface(tempSurface);
        if(!g.texture){
            std::cerr << "texture creation has failed for: " << g.portraitPath << " | " << SDL_GetError()<<std::endl;
        }
        textureCache[g.portraitPath]= g.texture;

    }

  //  guests = loadGuest("../assets/data/guestList.json", "../assets/data/vampire_traits.json"),3;

}
void Rounds::Update() {
    Uint32 elapsedTime = SDL_GetTicks() - roundStartTime;
    if(elapsedTime >= roundDuration){
        roundOver = true;
        std::cout << "round over!" << std::endl;
    }
  // if (totalGuests <=0){
    //    roundOver = true;
    //    totalGuests +=2;
  //  }
}

void Rounds::render(SDL_Renderer *renderer) {
    Uint32 now = SDL_GetTicks();
    if(now - roundStartTime < 4000) return;
    if (guests.empty() || currentGuestIndex >= guests.size()) {
        std::cerr << "no guests to render or index out of range. \n";
        return;
    }
    Guest &g = guests[currentGuestIndex];
    if (!g.texture) {
        std::cerr << "no texture for guests " << g.name << " | path " << g.portraitPath << std::endl;
        return;
    }
    SDL_Rect dstRect = {325, 100, 150, 150};
    //std::cerr<< "drawing one guest: " << g.name << " | " << g.portraitPath << std::endl;
    if (SDL_RenderCopy(renderer, g.texture, nullptr, &dstRect) != 0) {
        std::cerr << "render copy failed: " << SDL_GetError() << std::endl;
    }
    /*
     int x = 50;
     int y = 100;
     int portraitWidth = 150;
     int portraitHeight = 150;

     //this sections draws guest portraits
     for(size_t i =0; i < guests.size();++i) {
         Guest &g = guests[i];

         if (!g.texture) { ;
             std::cerr << " no texture for guest " << g.name << " | path: " << g.portraitPath << std::endl;
             continue;
         }

             SDL_Rect dstRect = {
                     x + static_cast<int>(i*(portraitWidth +20)),y,portraitWidth,portraitHeight
             };
             std::cout << "drawing portrait: " << g.portraitPath << std::endl;

             if (SDL_RenderCopy(renderer,g.texture, nullptr,&dstRect) !=0) {
                 std::cerr << "Render copy  failed: " <<SDL_GetError() << std::endl;
             }
     }*/
}
void Rounds::nextGuest(bool letIn)
{
    if(guests.empty()||currentGuestIndex>=guests.size()) return;

    Guest& g = guests[currentGuestIndex];
    if(letIn){
        if(letIn && g.isVampire) vampiresLetIn++;
        else humansLetIn++;
    }else{
        if(!letIn && g.isVampire) vampiresKicked++;
        else humansKicked++;
    }

    if(currentGuestIndex + 1 < guests.size()){
        currentGuestIndex++;
    } else
    {
        roundOver= true;
        std::cout << "every guest has processed!" << std::endl;
    }
}
bool Rounds::allGuestsSeen() const {
    return currentGuestIndex >= guests.size();
}
void Rounds::startNextRound(SDL_Renderer *renderer) {
    if(CurrentRound >= 3) {
        roundOver = true;
        return;
    }
    CurrentRound++;
    currentGuestIndex =0;
    roundOver= false;
    StartRound(renderer);

}
std::string  Rounds::getCurrentGuestInfo() const {
    if(currentGuestIndex >= guests.size()) return "";

    const Guest& g =guests[currentGuestIndex];
    std::string info = "name: " + g.name;

    if (!g.traits.empty()){
        info += "\nTrait: ";
        for (size_t  i=0; i < g.traits.size(); ++i){
            info += g.traits[i];
            if(i<g.traits.size()-1){
                info += ", " ;
            }
        }
    }
    return info;
}

std::string Rounds::getEndingMessage() const {
    //this for the end scene
    if (vampiresLetIn >= 3 ){
        return "Iron.. The smell of blood reeks the halls, an blood bath."
               "\nYou let too many vampires in and no humans, "
               "\neven yourself, do not wake to see the daylight. ";
    }else if( humansKicked >= 6){
        return "You played too safe, shame those turned away will have fate undecided for better or worse";
    }else if( vampiresLetIn == 0 && humansKicked ==0){
        return "Hero. With every human saved and every vampire left outside, "
               "\nyou managed to let everyone see dawn with no bloodshed. "
               "\ncongrats";
    } else if(humansLetIn==0 && vampiresLetIn==0){
        return "at the end you hear a knock. Peeping through the hole of the door "
               "\nyou are overcome to let IT in \nbefore you know it grabs your hand, pulls you up,"
               "\nand suck every drop of blood.\ndead and failure.";
    }else{
        return "Some humans are saved... while some lie outside not moving.";
    }

;}
std::string Rounds::getScoreSummary() const {
    return "Humans Let In: " + std::to_string(humansLetIn)+
    "\nVampires Kicked: " +std::to_string(vampiresKicked)+
    "\nVampires Let In: " +std::to_string(vampiresLetIn)+
    "\nHumans Kicked: " +std::to_string(humansKicked);
}
bool Rounds::isRoundOver() const {
    return roundOver;
}

