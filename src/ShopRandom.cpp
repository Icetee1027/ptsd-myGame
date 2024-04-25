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
