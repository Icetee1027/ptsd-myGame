#include "SynthesisTable.hpp"
#include "Card/AllCardPch.hpp"

std::vector<SynthesisTable::Table> SynthesisTable::m_SynthesisTable = {
    {"AnimalPen", {"Plank", "Plank","Wood","Wood","IronBar"}, {"Plank", "Plank","Wood","Wood","IronBar"}, 30.0, false,"Villager"},//1
    {"AppleTree", {"Apple"}, {"Apple"}, 120.0, false,"Soil"},//2
    {"BerryBush", {"Berry"}, {"Berry"}, 120.0, false,"Soil"},//3
    {"Brick",{"Stone","Stone","Stone","Brickyard"},{"Stone","Stone","Stone"},10.0,false},//5
    {"Brick",{"Stone","Stone","Stone"},{"Stone","Stone","Stone"},30.0,false,"Villager"},//5
    {"Campfire",{"Stick","Flint"},{"Stick","Flint"},30.0,false},//6
    {"CoinChest",{"Coin","Wood","Wood"},{"Coin","Wood","Wood"},10.0,false},//7
    {"Farm",{"Soil","Brick","Brick","Plank","Plank"},{"Soil","Brick","Brick","Plank","Plank"},40.0,false,"Villager"},//8
    {"Garden",{"Soil","Wood","Wood","Stone","Stone"},{"Soil","Wood","Wood","Stone","Stone"},40.0,false,"Villager"},//9
    {"House",{"Stone","Wood","Wood"},{"Stone","Wood","Wood"},30.0,false,"Villager"},//10
    {"IronMine",{"Flint","Flint","Wood","Stone"},{"Flint","Flint","Wood","Stone"},30.0,false,"Villager"},//11
    {"LumberCamp",{"Wood","Wood","Wood","Stone"},{"Wood","Wood","Wood","Stone"},30.0,false,"Villager"},//12
    {"Market",{"Coin","Coin","Coin","Plank","Brick"},{"Coin","Coin","Coin","Plank","Brick"},30.0,false,"Villager"},//13
    {"Quarry",{"Stone","Stone","Stone","Wood"},{"Stone","Stone","Stone","Wood"},30.0,false,"Villager"},//14
    {"Sawmill",{"Plank","Stone","IronBar"},{"Plank","Stone","IronBar"},30.0,false,"Villager"},//15
    {"Shed",{"Wood","Stone","Stick"},{"Wood","Stone","Stick"},30.0,false,"Villager"},//16
    {"Smelter",{"Flint","Flint","Brick","Brick","Plank"},{"Flint","Flint","Brick","Brick","Plank"},30.0,false,"Villager"},//17
    {"Smithy",{"IronBar","IronBar","Brick","Brick"},{"IronBar","IronBar","Brick","Brick"},30.0,false,"Villager"},//18
    {"Stove",{"Flint","Brick","IronBar"},{"Flint","Brick","IronBar"},30.0,false,"Villager"},//19
    {"Temple",{"Plank","Plank","Plank","Plank","Plank","Brick","Brick","Brick","Brick","Brick","IronBar","IronBar","IronBar"},{"Plank","Plank","Plank","Plank","Plank","Brick","Brick","Brick","Brick","Brick","IronBar","IronBar","IronBar"},180.0,false,"Villager",3},//20
    {"Warehouse",{"IronBar","Stone"},{"IronBar","Stone"},30.0,false,"Villager"},//21
    {"Demon",{"Temple","GoldenGoblet"},{"GoldenGoblet"},30.0,false},//22
    {"IronBar",{"IronOre","Wood","Smelter"},{"IronOre","Wood"},10.0,false,"Villager"},//23
    {"Plank",{"Wood","Wood","Wood","Sawmill"},{"Wood","Wood","Wood"},10.0,false},//24
    {"Plank",{"Wood","Wood","Wood"},{"Wood","Wood","Wood"},30.0,false,"Villager"},//24
    {"Stick",{"Wood"},{"Wood"},10.0,false,"Villager"},//24
    {"Carrot",{"Carrot"},{},180.0,false,"Soil"},//25
    {"CookedMeat",{"RawMeat","Campfire"},{"RawMeat"},60.0,false},//26
    {"CookedMeat",{"RawMeat","Stove"},{"RawMeat"},18.0,false},//26
    {"Frittata",{"Egg","Potato","Campfire"},{"Egg","Potato"},60.0,false},//27
    {"Frittata",{"Egg","Potato","Stove"},{"Egg","Potato"},18.0,false},//27
    {"FruitSalad",{"Apple","Berry"},{"Apple","Berry"},10.0,false},//28
    {"Milkshake",{"Milk","Berry"},{"Milk","Berry"},10.0,false},//28
    {"Mushroom",{"Mushroom"},{},120.0,false,"Soil"},//29
    {"Omelette",{"Egg","Egg","Campfire"},{"Egg","Egg"},90.0,false},//30
    {"Omelette",{"Egg","Egg","Stove"},{"Egg","Egg"},27.0,false},//30
    {"Onion",{"Onion"},{},120.0,false,"Soil"},//31
    {"Potato",{"Potato"},{},120.0,false,"Soil"},//32
    {"Stew",{"Potato","Onion","Carrot","RawMeat","Campfire"},{"Potato","Onion","Carrot","RawMeat"},120.0,false},//33
    {"Stew",{"Potato","Onion","Carrot","RawMeat","Stove"},{"Potato","Onion","Carrot","RawMeat"},36.0,false},//33
    {"Graveyard",{"Corpse","Corpse"},{"Corpse","Corpse"},15.0,false},//34
    {"Spear",{"Wood","Stick","Stick"},{"Wood","Stick","Stick"},15.0,false},//35
    {"Sword",{"IronBar","Stick","Stick"},{"IronBar","Stick","Stick"},15.0,false},//36
    {"BerryBush", {"BerryBush"}, {"BerryBush"}, 10.0, true,"Villager" },//1--
    {"AppleTree", {"AppleTree"}, {"AppleTree"}, 10.0, true,"Villager" },//2--
    {"IronDeposit", {"IronDeposit"}, {"IronDeposit"}, 10.0, true,"Villager" },//2--
    {"Rock", {"Rock"}, {"Rock"}, 10.0, true,"Villager" },//3--
    {"Tree", {"Tree"}, {"Tree"}, 10.0, true,"Villager" },//4--
    {"Catacombs", {"Catacombs"}, {}, 60.0, true,"Villager" },//5--
    {"Forest", {"Forest"}, {}, 60.0, true,"Villager" },//6--
    {"Graveyard", {"Graveyard"}, {}, 60.0, true,"Villager" },//7--
    {"Mountain", {"Mountain"}, {}, 60.0, true,"Villager" },//8--
    {"OldVillage", {"OldVillage"}, {}, 60.0, true,"Villager" },//9--
    {"Plains", {"Plains"}, {}, 60.0, true,"Villager" },//10--
  
};
bool isSubset(const std::vector<std::string>& a, const std::vector<std::string>& b) {
    std::unordered_map<std::string, int> counts_a;

    // Count the occurrences of each element in a
    for (const auto& elem : a) {
        counts_a[elem]++;
    }

    // Check if all elements in b are present in a with equal or greater counts
    for (const auto& elem : b) {
        if (counts_a[elem] == 0) {
            return false; // Element in b is not present in a
        }
        counts_a[elem]--; // Decrease the count of element in a
    }

    return true;
}
int isVillager(const std::vector<std::string>& a, const int count=1) {
    std::vector<std::string> Villager = { "Villager","Explorer","Militia","Swordsman" };
    int m_count = 0;
    float time = 0;
    for (const auto& elem : Villager) {
        if (std::find(a.begin(), a.end(), elem) != a.end()) {
            m_count +=1;
            time++;
        }
    }
    if (std::find(a.begin(), a.end(), "Dog") != a.end()) {
        m_count += 1;
        time+= 0.7;
    }
    if (count <= m_count) {
        return time / m_count;
    }
    else {
        return -1;
    }
}
bool isSoil(const std::string& a) {
    std::vector<std::string> Soil = { "Poop","Soil","Garden","Farm" };
    for (const auto& elem : Soil) {
        if (a==elem) {
            return 1;
        }
    }
    return 0;
}
std::pair<int,int> SynthesisTable::SyntheticCheck(std::vector<std::string> &cards) {
    int conSynthetic = -1;
    int size = 0;
    int efficiency = 1;
    for (int it = 0; it < m_SynthesisTable.size(); ++it) {
        if (isSubset(cards, m_SynthesisTable[it].need)) {
            if (m_SynthesisTable[it].medium == "Villager") {
                if (isVillager(cards) != -1) {
                    efficiency = isVillager(cards);
                    if (size <= m_SynthesisTable[it].need.size()) {
                        conSynthetic = it;
                        size = m_SynthesisTable[it].need.size();
                    }
                }
                else {
                    continue;
                }
            }
            
            if (m_SynthesisTable[it].medium == "Soil") {
                if (isSoil(cards[0])) {
                    if (size <= m_SynthesisTable[it].need.size()) {
                        conSynthetic = it;
                        size = m_SynthesisTable[it].need.size();
                    }
                }
                else {
                    continue;
                }
            }
            
            if (size <= m_SynthesisTable[it].need.size()) {
                conSynthetic = it;
                size = m_SynthesisTable[it].need.size();
            }
        }
    }

    return std::pair(conSynthetic, efficiency);
}
