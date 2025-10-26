#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>


using json = nlohmann::json;

struct Guest{
    int id;
    std::string name;
    std::string gender;
    std::vector<std::string> traits;
    std::string portraitPath;
    bool isVampire;


};
std::vector<Guest> guests;
std::vector<std::string> vampireTraits;

void loadData()
{
    //attempt3 loading guests
    std::ifstream guestList("../assets/data/guestList.json");
    json guestJson;
    guestList >> guestJson;

    for (auto& item : guestJson["guests"])
    {
        Guest g;
        g.name = item["name"];
        g.gender = item["gender"];
        g.traits = item["traits"].get<std::vector<std::string>>();
        g.isVampire = false;
        guests.push_back(g);
    }
    //vampiretraits.json
    std::ifstream vampireFile("../assets/data/vampire_traits.json");
    json vampJson;
    vampireFile >> vampJson;
    vampireTraits = vampJson["vampireTraits"].get<std::vector<std::string>>();
}
//now we randomly assign vampire
void assignVampires(int count)
{
    srand(time(nullptr));
    for(int i = 0; i < count; i++)
    {
        int index = rand() % vampireTraits.size();
        guests[index].isVampire = true;

        for(int j=0; j<2; j++){
            int tIndex =rand()%vampireTraits.size();
            guests[index].traits.push_back(vampireTraits[tIndex]);
        }
    }

}