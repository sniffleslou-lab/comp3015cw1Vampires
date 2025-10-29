#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Guests.h"
#include <filesystem>

namespace fs =std::filesystem;
using json = nlohmann::json;

//this is for randomly assigning portrait
std::string getRandomPortrait(const std::string& genderFolder)
{
    std::vector<std::string> portraits;
    for(const auto& entry :fs::directory_iterator(genderFolder))
    {
        if(entry.is_regular_file())
        {
            portraits.push_back(entry.path().string());
        }
    }
    int index=rand() %portraits.size();
    return portraits[index];

}

std::vector<Guest> loadGuests(const std::string& guestFilePath, const std::string & vampireFilePath,int vampireCount)
{
    std::vector<Guest> guests;
    std::vector<std::string> vampireTraits;
    //attempt3 loading guests
    std::ifstream guestList("../assets/data/guestList.json");
    json guestJson;
    guestList >> guestJson;

    for (auto &item: guestJson["guests"]) {
        Guest g;
        g.id = item["id"];
        g.name = item["name"];
        g.gender = item["gender"];
        g.traits = item["traits"].get<std::vector<std::string>>();
        g.isVampire = false;

        if (g.gender == "m")
            g.portraitPath = getRandomPortrait("../assets/textures/M");
        else if (g.gender == "f")
            g.portraitPath = getRandomPortrait("../assets/textures/F");

        guests.push_back(g);
    }

        //vampiretraits.json
        std::ifstream vampireFile("../assets/data/vampire_traits.json");
        json vampJson;
        vampireFile >> vampJson;
        vampireTraits = vampJson["vampireTraits"].get<std::vector<std::string>>();

        srand(static_cast<unsigned int>(time(nullptr)));
        for (int i = 0; i < vampireCount && !guests.empty(); i++) {
            int index = rand() % guests.size();
            guests[index].isVampire = true;

            for (int j = 0; j < 2; j++) {
                int tIndex = rand() % vampireTraits.size();
                guests[index].traits.push_back(vampireTraits[tIndex]);
            }
        }
        return guests;

    }


