#include "ShopRandom.hpp"
#include <random>
std::vector<std::string> ShopRandom::DrawCardPack(const std::string& systemName) {
    // 查找指定名称的抽奖系统
    auto it = std::find_if(database.begin(), database.end(), [&systemName](const RandomElement& element) {
        return element.name == systemName;
        });

    // 如果找到了对应的抽奖系统
    if (it != database.end()) {
        const auto& prizePools = it->prizes;

        // 初始化随机数种子
        std::random_device rd;
        std::mt19937 rng(rd());

        // 抽奖结果向量
        std::vector<std::string> winners;
        for (const auto& prizePool : prizePools) {
            // 每次抽奖都独立计算总概率
            int totalProbability = 0;
            for (const auto& item : prizePool) {
                totalProbability += item.second;
            }

            // 生成随机数
            std::uniform_int_distribution<int> distribution(1, totalProbability);
            int randomNumber = distribution(rng);

            // 计算落在哪个奖品区间
            int sum = 0;
            for (const auto& item : prizePool) {
                sum += item.second;
                if (randomNumber <= sum) {
                    winners.push_back(item.first);
                    break;
                }
            }
        }

        // 检查是否有idea
        const auto& ideas = it->idea;
        if (!ideas.empty()) {
            // 找到还有idea的獎池
            std::vector<int> indicesWithIdeas;
            for (size_t i = 0; i < ideas.size(); ++i) {
                if (!ideas[i].empty()) {
                    indicesWithIdeas.push_back(i);
                }
            }

            // 如果有还有idea的獎池
            if (!indicesWithIdeas.empty()) {
                // 随机选择一个有idea的獎池
                std::uniform_int_distribution<int> distributionPool(0, indicesWithIdeas.size() - 1);
                int selectedPoolIndex = distributionPool(rng);
                int selectedPool = indicesWithIdeas[selectedPoolIndex];

                // 随机选择该獎池中的一个idea
                std::uniform_int_distribution<int> distributionIdea(0, ideas[selectedPool].size() - 1);
                int selectedIdeaIndex = distributionIdea(rng);
                std::string selectedIdea = ideas[selectedPool][selectedIdeaIndex];

                // 修改抽奖结果，同时删除被选中的idea
                winners[selectedPool] = selectedIdea;
                auto& ideaPool = database[it - database.begin()].idea[selectedPool];
                ideaPool.erase(ideaPool.begin() + selectedIdeaIndex);
            }
        }

        return winners;
    }
    else {
        // 如果未找到对应的抽奖系统，返回空结果
        LOG_ERROR("Error: Cannot find the specified draw system: ");
        return {};
    }
}
std::string ShopRandom::drawLottery(const std::string& lotterySystemName) {
    // 儲存找到的抽獎系統
    const RandomElementsy* foundSystem = nullptr;

    // 在數據庫中查找抽獎系統
    for (auto it = databasesy.begin(); it != databasesy.end(); ++it) {
        const RandomElementsy& sys = *it;
        if (sys.name == lotterySystemName) {
            foundSystem = &sys; // 找到了抽獎系統，保存指針
            break; // 找到後即退出循環
        }
    }

    // 如果找到了抽獎系統
    if (foundSystem != nullptr) {
        // 計算總的中獎概率
        int totalProbability = 0;
        for (const auto& pair : foundSystem->prizes) {
            totalProbability += pair.second;
        }

        // 使用均勻分佈來隨機選擇一個數字
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, totalProbability);
        int randomNumber = dis(gen);

        // 根據隨機數選擇獎項
        int currentProbability = 0;
        for (const auto& pair : foundSystem->prizes) {
            currentProbability += pair.second;
            if (randomNumber <= currentProbability) {
                return pair.first;
            }
        }
    }
    LOG_ERROR("SynthesisTable random error");
    return ""; // 如果未找到對應的抽獎系統，返回空字符串
}


std::vector<RandomElementsy> ShopRandom::databasesy{
    {
        "BerryBush",
        {
            {"Rabbit",1},
            {"Berry",99}
        }
    },
    {
        "AppleTree",
        {
            {"Apple",80},
            {"Stick",20}
        }
    },
    {
        "IronDeposit",
        {
            {"Stone",30},
            {"IronOre",60},
            {"Coin",10}
        }
    },
    {
        "Rock",
        {
            {"Flint",30},
            {"Stone",60},
            {"Coin",10}
        }
    },
    {
        "Tree",
        {   {"Wood",60},
            {"Stick",30},
            {"Apple",10}
        }
    },
    {
        "Catacombs",
        {
            {"Skeleton",13},
            {"Goblin", 13},
            {"GiantRat", 13},
            {"Slime", 13},
            {"Wolf", 13},
            {"TreasureChest", 10}
        }
    },
    {
        "Forest",
        {
            {"Rabbit", 10},
            {"Goblin", 4},
            {"Rat", 4},
            {"Slime", 4},
            {"Mushroom", 10},
            {"Apple", 5},
            {"Tree", 10},
            {"BerryBush", 10},
            {"AppleTree", 5},
            {"Stick", 14},
            {"Catacombs", 7},
            {"TreasureChest", 5}
        }
    },
    {
        "Graveyard",
        {
            {"Skeleton", 12},
            {"Soil", 25},
            {"Bone", 12},
            {"TreasureChest", 25},
            {"Catacombs", 12},
            {"Corpse", 12}
        }
    },
    {
        "Mountain",
        {
            {"Goblin", 3},
            {"Rat", 3},
            {"Slime", 3},
            {"IronDeposit", 21},
            {"Rock", 10},
            {"TreasureChest", 3},
            {"Catacombs", 3}
        }
    },
    {
        "Old Village",
        {
            {"Slime", 10},
            {"Goblin", 1},
            {"Rat", 1},
            {"Milk", 9},
            {"Wood", 17},
            {"IronBar", 9},
            {"Coin", 17},
            {"Villager", 9},
            {"Corpse", 9},
            {"TreasureChest", 9},
            {"Catacombs", 4},
            {"OldTome", 4}
        }
    },
    {
        "Plains",
        {
            {"Chicken", 14},
            {"Cow", 14},
            {"Rat", 14},
            {"Wolf", 7},
            {"Onion", 14},
            {"Mushroom", 7},
            {"Carrot", 7},
            {"Milk", 7},
            {"Soil", 14}
        }
    }

};




std::vector<RandomElement> ShopRandom::database = {
    {
        "HumbleBegining",
        {
            {},
            {},
            {"IdeaGrowth", "IdeaHouse", "IdeaOffspring", "IdeaStick"}//4
        },
        {
            { {"Stone", 19},{"Wood", 19},{"BerryBush", 13},{"Rock", 13},{"Soil", 13},{"Tree", 13},{"Key", 3},{"Rabbit", 3},{"Rat", 3} },
            {{"Stone", 19},{"Wood", 19},{"BerryBush", 13},{"Rock", 13},{"Soil", 13},{"Tree", 13},{"Key", 3},{"Rabbit", 3},{"Rat", 3}},
            {{"Stone", 19},{"Wood", 19},{"BerryBush", 13},{"Rock", 13},{"Soil", 13},{"Tree", 13},{"Key", 3},{"Rabbit", 3},{"Rat", 3}}
        }
    },
    {
        "SeekingWisdom",
        {
            {"IdeaBrick", "IdeaCampfire", "IdeaPlank", "IdeaSpear", "IdeaShed"},
            {},
            { "IdeaCoinChest", "IdeaGarden"},//7
            {}
        },
        {
            {{"BerryBush", 33}, {"Rock", 33}, {"Tree", 33}},
            {{"Stone", 27}, {"Wood", 27}, {"Flint", 13}, {"Poop", 13}, {"Stick", 13}, {"Coin", 7}},
            {{"BerryBush", 33}, {"Rock", 33}, {"Tree", 33}},
            {{"BerryBush", 33}, {"Rock", 33}, {"Tree", 33}}
        }
    },
    {
        "ReapAndSow",
        {
            {}, {}, {"IdeaChicken",  "IdeaLumberCamp", "IdeaQuarry"}, {}//3
        },
        {
            {{"Apple", 25}, {"Berry", 25}, {"Carrot", 25}, {"Raw Meat", 25}},
            {{"Chicken", 25}, {"Cow", 25}, {"Rabbit", 25}, {"Soil", 25}},
            {{"BerryBush", 33}, {"Rock", 33}, {"Tree", 33}},
            {{"BerryBush", 33}, {"Rock", 33}, {"Tree", 33}}
        }
    },
    {
        "CuriousCuisine",
        {
            {}, {"IdeaCookedMeat", "IdeaFrittata", "IdeaFruitSalad", "IdeaMilkshake", "IdeaOmelette", "IdeaStew", "IdeaStove"}, {}//7
        },
        {
            {{"Egg", 20}, {"Milk", 20}, {"Mushroom", 20}, {"Onion", 20}, {"Potato", 20}},
            {{"BerryBush", 33}, {"Rock", 33}, {"Tree", 33}},
            {{"Apple", 25}, {"Berry", 25}, {"Carrot", 25}, {"RawMeat", 25}}
        }
    },
    {
        "LogicandReason",
        {
            {},
            {},
            {"IdeaAnimalPen", "IdeaBrickyard", "IdeaFarm", "IdeaIronBar", "IdeaIronMine", "IdeaMarket", "IdeaSawmill", "IdeaSmelter", "IdeaSmithy", "IdeaWarehouse"},//10
            {}
        },
        {
            {{"BerryBush", 33}, {"Rock", 33}, {"Tree", 33}},
            {{"Brick", 33}, {"IronOre", 33}, {"Plank", 33}},
            {{"Tree", 33}, {"Rock", 33}, {"BerryBush", 33}},
            {{"BerryBush", 33}, {"Rock", 33}, {"Tree", 33}}
        }
    },
{
        "TheArmory",
        {
            {  "IdeaSword"},//"RumorDarkForest"//1
            {},
            {}
        },
        {
            {{"BerryBush", 33}, {"Rock", 33}, {"Tree", 33}},
            {{"Bear", 12.5}, {"Rat", 12.5}, {"GiantRat", 12.5}, {"Goblin", 12.5}, {"Mimic", 12.5}, {"Skeleton", 12.5}, {"Skeleton", 12.5}, {"Wolf", 12.5}},
            {{"Brick", 33}, {"IronOre", 33}, {"Plank", 33}}
        }
    },
    {
        "Explorers",
        {
            {}, {}, {"IdeaTemple"}//1
        },
        {
            {{"BerryBush", 33}, {"Rock", 33}, {"Tree", 33}},
            {{"Bear", 12.5}, {"Rat", 12.5}, {"GiantRat", 12.5}, {"Goblin", 12.5}, {"Mimic", 12.5}, {"Skeleton", 12.5}, {"Skeleton", 12.5}, {"Wolf", 12.5}},
            {{"Forest", 25}, {"Mountain", 25}, {"OldVillage", 25}, {"Plains", 25}}
        }
    },
    {
        "OrderandStructure",
        {
            {},{},{},
            {}
        },
        {
            {{"Iron Deposit", 100}},
            {{"Berry Bush", 33}, {"Rock", 33}, {"Tree", 33}},
            {{"Berry Bush", 33}, {"Rock", 33}, {"Tree", 33}},
            {{"Brick", 33}, {"Iron Ore", 33}, {"Plank", 33}}
        }
    }
   
};
