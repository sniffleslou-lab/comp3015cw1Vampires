#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Guests.h"
#include <filesystem>
#include <SDL2/SDL_image.h>
#include <algorithm>
#include <random>
#include "Path.h"
#include <chrono>
#include <SDL2/SDL.h>

namespace fs =std::filesystem;
using json = nlohmann::json;

//this is for randomly assigning a portrait
std::string getRandomPortrait(const std::string& genderFolder)
{
    std::vector<std::string> portraits;
    for(const auto& entry :fs::directory_iterator(genderFolder))
    {
        if(entry.is_regular_file())
        {
            //portraits.push_back(entry.path().string());
            std::string path = entry.path().string();

            //i think ds_store is breaking the game
            if (path.find(".DS_Store") != std::string::npos) continue;
            if(entry.path().extension()==".png"){
                portraits.push_back(path);
            }
        }
    }
    if (portraits.empty()){
        std::cerr << "no portraits found in folder: " << genderFolder <<std::endl;
        return "";
    }
    int index=rand() %portraits.size();
    return portraits[index];

}

std::vector<Guest> loadGuests(const std::string& guestFilePath, const std::string & vampireFilePath,int totalGuests, int vampireCount)

{

    std::vector<Guest> allGuests;
    std::vector<Guest> selectedGuests;
    std::vector<std::string> vampireTraits;
    //attempt3 loading guests
    std::ifstream guestList(guestFilePath);
    if(!guestList.is_open()){
        std::cerr << "could not open guest list json from path: " << std::endl;
        return selectedGuests;
    }else {
        std::cerr << "opened gustlist json!" <<std::endl;
    }
    //json guestJson;
    //guestList >> guestJson;
    json guestJson;
    try {
        guestList >> guestJson;
    }
    catch (const std::exception& e) {
        std::cerr << "json parssing error: " << e.what() << std::endl;
        return selectedGuests;
    }


    for (auto &item: guestJson["guests"]) {
        Guest g;
        g.id = item["id"];
        g.name = item["name"];
        g.gender = item["gender"];
        g.traits = item["traits"].get<std::vector<std::string>>();
        g.isVampire = false;

        if (g.gender == "m")
            g.portraitPath = getRandomPortrait(std::string(ASSETS_PATH) + "textures/M");
            //g.portraitPath = getRandomPortrait("assets/textures/M");

        else if (g.gender == "f")
            g.portraitPath = getRandomPortrait(std::string(ASSETS_PATH) + "textures/F");

        allGuests.push_back(g);
    }
    //stuffling and selecting totalguests
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::shuffle(allGuests.begin(), allGuests.end(), std::default_random_engine(seed));
            for(int i = 0; i < totalGuests && i < allGuests.size(); ++i){
                selectedGuests.push_back(allGuests[i]);
            }
        //vampiretraits.j
        // son
        std::ifstream vampireFile(vampireFilePath);
        json vampJson;
        vampireFile >> vampJson;
        vampireTraits = vampJson["vampireTraits"].get<std::vector<std::string>>();

        srand(static_cast<unsigned int>(time(nullptr)));
        for (int i = 0; i < vampireCount && !selectedGuests.empty(); i++) {
            int index = rand() % selectedGuests.size();
            selectedGuests[index].isVampire = true;

            for (int j = 0; j < 2; j++) {
                int tIndex = rand() % vampireTraits.size();
                selectedGuests[index].traits.push_back(vampireTraits[tIndex]);
            }
        }
        return selectedGuests;

    }


