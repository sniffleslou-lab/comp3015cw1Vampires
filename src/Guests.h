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
};
std::vector<Guest> loadGuests(const std::string& guestFilePath, const std::string & vampireFilePath,int vampireCount);

