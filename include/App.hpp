#ifndef APP_HPP
#define APP_HPP
#include "SystemSettlementUI.hpp"
#include "Card/CardMaker.hpp"
#include "Card/Card.hpp"
#include "pch.hpp" // IWYU pragma: export
#include "Util/Root.hpp"
#include "Card/Shop.hpp"
#include "Background.hpp"
#include "InteractiveBox.hpp"
#include "Giraffe.hpp"
#include "GiraffeText.hpp"
#include "Camera.hpp"
#include "Mouse.hpp"
#include "card/Card.hpp"
#include <list>
#include <map>
#include <cmath>
#include "Board.hpp"
class App {
public:
    enum class PauseOrPlay {
        Pause,
        Play
    };
    enum class Modle {
        Origin,
        Menu,
        Playing
    };
    enum class State {
        START,
        UPDATE,
        END,
    };
    enum class SystemStatus {
        play,
        Settlement1,
        Settlement2,
        Settlement3,
        Settlement4,
    };
    State GetCurrentState() const { return m_CurrentState; }
    ~App()= default;

    void Start();

    void Update();

    void End(); // NOLINT(readability-convert-member-functions-to-static)
    static void AddCard(std::shared_ptr<card::Card> NewCard); 
    static void AddObjectToRoot(std::shared_ptr<Util::GameObject> object);
    static void MoveCardToNewX(const std::shared_ptr<card::Card>& specifiedObj, int oldX = 0); 
    static void RemoveCard(const std::shared_ptr<card::Card>& specifiedObj, int X = 0);
    static void ChangeCard(const std::shared_ptr<card::Card>& specifiedObj,  const std::shared_ptr<card::Card> toChange, int X = 0);
    static PauseOrPlay m_IsPlayButton; 
    static std::list<std::weak_ptr<card::Card>> m_PushProcessingArea;
    static std::vector<std::weak_ptr<card::Card>> VillagerLocation;
    static std::shared_ptr<GiraffeText > m_SideText;
    static std::shared_ptr<Mouse> m_Mouse;
    static std::multimap<int, std::shared_ptr<card::Card>> m_WorldCards;
private:
    void Play();
    void Settlement1Updata();
    void Pause();
    void CameraUpdate();
    void StackUpdate();
    void Origin();
    void Menu();
    void Playing();
    void mouseUp();
    void SystemUpdta();
    
private:
    std::vector<std::shared_ptr<card::Card>> m_SettlementVillage = {};
    std::vector<std::shared_ptr<card::Card>> m_SettlementFood = {};
    std::shared_ptr<InteractiveBox> m_InteractiveBox = std::make_shared< InteractiveBox>();
    State m_CurrentState = State::START;
    Modle m_Modle = Modle::Origin;
    SystemStatus m_SystemMode = SystemStatus::play;
    std::vector<std::shared_ptr<Background>> m_SideElement = { std::make_shared<Background>(),std::make_shared<Background>(),std::make_shared<Background>() };
    std::vector<std::shared_ptr<GiraffeText>> m_MenuElement = { std::make_shared<GiraffeText>() ,std::make_shared<GiraffeText>() ,std::make_shared<GiraffeText>() };
    std::shared_ptr< SystemSettlementUI> m_System = std::make_shared< SystemSettlementUI>();
    int m_Food = 0;
    int m_NeedFood = 0;
    float m_TimeCount=0;
    glm::vec2 m_StartPoint;
    glm::vec2  m_EndPoint;
    std::shared_ptr<Background> m_Background = std::make_shared<Background>();
    std::shared_ptr<Background> m_Menu = std::make_shared<Background>();

    std::shared_ptr<GiraffeText> m_GiraffeText = std::make_shared<GiraffeText>();
    std::shared_ptr<Camera> m_Camera = std::make_shared<Camera>();
    
   
    static Util::Root m_Root;
    std::vector<std::shared_ptr<card::Card>> m_Shops = { card::CardMaker::MakeCard("Sell") ,
                                                         card::CardMaker::MakeCard("HumbleBegining") ,//
                                                         card::CardMaker::MakeCard("SeekingWisdom"), //
                                                         card::CardMaker::MakeCard("ReapAndSow"),//
                                                         card::CardMaker::MakeCard("CuriousCuisine") ,//
                                                         card::CardMaker::MakeCard("LogicandReason") ,//
                                                         card::CardMaker::MakeCard("TheArmory") ,//
                                                         card::CardMaker::MakeCard("Explorers") ,//
                                                         //card::CardMaker::MakeCard("OrderandStructure") ,
                                                        };
    std::shared_ptr<Board> m_Board = std::make_shared<Board>();
    std::vector<std::string> files = { "AnimalPen", "Apple", "AppleTree", "Baby", "Bear", "Berry", "BerryBush",//
        "Bone", "Brick", "Brickyard", "Campfire", "Carrot", "Catacombs", "Chicken", "Coin", "CoinChest", "CookedMeat",//
        "Corpse", "Cow", "Demon", "Dog", "Egg", "Explorer", "Farm", "Flint", "Forest", "Frittata", "FruitSalad", "Garden", //
        "GiantRat", "Goblin", "GoldenGoblet", "Graveyard", "House", "IronBar", "IronDeposit", "IronMine", "IronOre",//
        "Key", "LumberCamp", "MagicDust", "Map", "Market", "Militia", "Milk", "Milkshake", "Mountain", "Mushroom", "OldTome", //
        "OldVillage", "Omelette", "Onion", "Plains", "Plank", "Poop", "Potato", "Quarry", "Rabbit", "RarePortal", "Rat", //
        "RawMeat", "Rock", "Sawmill", "Shed", "Skeleton", "Slime", "SmallSlime",//
        "Smelter", "Smithy", "Soil", "Spear", "Stew", "Stick", "Stone",  "StrangePortal", "Sword", "Swordsman", "Temple", //
        "TravellingCart", "TreasureChest", "Tree", "Villager", "Warehouse", "WickedWitch", "Wolf", "Wood" };


};
#endif
