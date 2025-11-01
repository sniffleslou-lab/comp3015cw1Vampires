#pragma once
#include <iostream>
#include "SDL.h"
#include <vector>

struct Guest {
    int id;
    std::string name;
    std::string gender;
    std::vector<std::string> traits;
    std::string portraitPath;
    bool isVampire;
    SDL_Texture* texture = nullptr;
};
std::vector<Guest> loadGuests(const std::string& guestFilePath, const std::string & vampireFilePath,int totalGuests, int vampireCount);

