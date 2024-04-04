#include "Card/CardMaker.hpp"
#include "App.hpp"
namespace card {

    Type CardMaker::GetJosnToType(int t) {
        auto it = typeMapping.find(t);
        if (it != typeMapping.end()) {
            return it->second;
        }
        else {
            LOG_ERROR("fill type out of range");
            return Type::Villager; // Using Villager as the default value here
        }
    }

    template<typename T>
    static std::function<std::shared_ptr<Card>(Type, const std::string&, int, const std::vector<std::shared_ptr<Util::SFX>>, const std::shared_ptr<Util::Image>, const bool)>
        CardMaker::createCardFunction() {
        return [](Type type, const std::string& name, int id, const std::vector<std::shared_ptr<Util::SFX>>& sfxs, const std::shared_ptr<Util::Image>& image, const bool iconcolor) {
            return std::make_shared<T>(type, name, id, sfxs, image, iconcolor);
            };
    }

    std::shared_ptr<Card> CardMaker::MakeCard(std::string name) {
        std::ifstream file(RESOURCE_DIR "/json/" + name + ".json");
        json attribute;
        attribute << file;

        Type m_Type = GetJosnToType(attribute["type"]);
   
        std::shared_ptr<Card> temp = nullptr;
        auto [image, title] = CardElementPool::getElement(attribute["name"], attribute["textcolor"]);
        std::shared_ptr<CardTitle> m_Title = std::make_shared<CardTitle>();
        m_Title->SetDrawable(title);
        
        std::vector<std::string> sfxs;
        for (const auto& sfx : GetCardSFX(m_Type)) {
            sfxs.push_back(RESOURCE_DIR "/audio/sfx" + sfx);
        }

        static const std::map<std::string, std::function<std::shared_ptr<Card>(Type, const std::string&, int, const std::vector<std::shared_ptr<Util::SFX>>&, const std::shared_ptr<Util::Image>&, const bool)>> cardCreators = {
            {"Food", createCardFunction<Food>()},
            {"Altar", createCardFunction<Altar>()},
            {"AnimalPen", createCardFunction<AnimalPen>()},
            {"Blueprint", createCardFunction<Blueprint>()},
            {"Brickyard", createCardFunction<Brickyard>()},
            {"Chest", createCardFunction<Chest>()},
            {"Combatable", createCardFunction<Combatable>()},
            {"Corpse", createCardFunction<Corpse>()},
            {"Garden", createCardFunction<Garden>()},
            {"Gold", createCardFunction<Gold>()},
            {"Greenhouse", createCardFunction<Greenhouse>()},
            {"Harvestable", createCardFunction<Harvestable>()},
            {"House", createCardFunction<House>()},
            {"Kid", createCardFunction<Kid>()},
            {"Market", createCardFunction<Market>()},
            {"Poop", createCardFunction<Poop>()},
            {"Resource", createCardFunction<Resource>()},
            {"Sawmill", createCardFunction<Sawmill>()},
            {"SlaughterHouse", createCardFunction<SlaughterHouse>()},
            {"Smelter", createCardFunction<Smelter>()},
            {"TravellingCart", createCardFunction<TravellingCart>()},
            {"Equipable", createCardFunction<Equipable>()},
            {"CardPack", createCardFunction<CardPack>()},
            {"Milk",createCardFunction<Milk>() },
            { "Egg",createCardFunction<Egg>() },
            { "Bone",createCardFunction<Bone>() },
            { "BaseVillager",createCardFunction<BaseVillager>() },
            { "Animal",createCardFunction<Animal>() },
            { "Enemy",createCardFunction<Enemy>() },
            { "Graveyard",createCardFunction<Graveyard>() },
            { "Portal",createCardFunction<Portal>() },
            { "Temple",createCardFunction<Temple>() },
            { "Building",createCardFunction<Building>() },
            { "TreasureChest",createCardFunction<TreasureChest>() },
            { "Shop",createCardFunction<Shop>() },
        };

        auto it = cardCreators.find(attribute["class"]);
        if (it != cardCreators.end()) {
            bool coloer = true;
            if (attribute.contains("textcolor")) {
                if (attribute["textcolor"] == 0)coloer = false;
            }
            else { LOG_ERROR("{} not found textcolor", name); }
            temp = it->second(m_Type, attribute["name"], attribute["id"], std::vector<std::shared_ptr<Util::SFX>>(), image, coloer);
        }
        else {
            LOG_ERROR("card class is not found");
        }
        m_Title->SetCard(temp);
        temp->AddChild(m_Title);

        if (attribute.contains("hp")) {
            int hp = attribute["hp"];
            std::shared_ptr<CardRightNum> number=std::make_shared<CardRightNum>();
            number->SetDrawable(CardElementPool::getNumberTextElement(hp,attribute["textcolor"]));
            temp->SetHP(hp);
            number->SetCard(temp);
            temp->AddChild(number); 
    
        }else if (attribute.contains("satiety")) {
            int satiety = attribute["satiety"];
            std::shared_ptr<CardRightNum> number = std::make_shared<CardRightNum>();
            number->SetDrawable(CardElementPool::getNumberTextElement(satiety, attribute["textcolor"]));
            temp->SetSatiety(satiety);
            number->SetCard(temp);
            temp->AddChild(number);
     
        }
        if (attribute.contains("price")) {
            int price = attribute["price"];
            std::shared_ptr<CardLeftNum> number = std::make_shared<CardLeftNum>();
            if (name != "Coin") {
                number->SetDrawable(CardElementPool::getNumberTextElement(price, attribute["textcolor"]));
                temp->AddChild(number); 
                number->SetCard(temp);
            }
            temp->SetPrice(price);
        }

        App::AddObjectToRoot(temp);
        return temp;
    }

    std::vector<std::string> CardMaker::GetCardSFX(Type type) {
        auto it = cardSFXMap.find(type);
        if (it != cardSFXMap.end()) {
            return it->second;
        }
        else {
            LOG_ERROR("cardsfx's type is not found");
            return std::vector<std::string>();
        }
    }

    const std::map<int, Type> CardMaker::typeMapping = {
        {0, Type::Villager},
        {1, Type::Equipment},
        {2, Type::Food},
        {3, Type::Mob},
        {4, Type::CardPack},
        {5, Type::Resource},
        {6, Type::Structure},
        {7, Type::Idea},
        {8, Type::Location},
        {9, Type::Rumors},
        {10, Type::Shop}
    };

    const std::unordered_map<Type, std::vector<std::string>> CardMaker::cardSFXMap = {
        {Type::Villager, {}},
        {Type::Equipment, {}},
        {Type::Food, {}},
        {Type::Mob, {}},
        {Type::CardPack, {}},
        {Type::Resource, {}},
        {Type::Structure, {}},
        {Type::Idea, {}},
        {Type::Location, {}},
        {Type::Rumors, {}},
        {Type::Shop, {}}
    };
}
