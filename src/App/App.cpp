#include "App.hpp"
#include "SystemSettlementUI.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "GiraffeText.hpp"
#include "ShapeHelper.hpp"
#include "Util/Time.hpp"
#include "Card/CardElementPool.hpp"
#include "Card/Poop.hpp"
#include "Card/CardPack.hpp"
void App::Start() {
   // LOG_TRACE("Start");
    //auto cardpack1 = std::dynamic_pointer_cast<card::CardPack>(m_cardpack2);
    ////cardpack->SetCards(std::vector<std::string>({"Villager","BerryBush","Rock","Wood","Coin"}));
    //cardpack1->SetCards(std::vector<std::string>({ "Villager","BerryBush","Rock","Wood","Coin" }));
    //cardpack->SetCards(std::vector<std::string>({"Villager","BerryBush","Rock","Wood","Coin"}));
    //m_CardPacks.push_back(cardpack1);

    std::shared_ptr<card::Card> m_cardpack2= card::CardMaker::MakeCard("Pack");
    auto cardpack = std::dynamic_pointer_cast<card::CardPack>(m_cardpack2);
    auto vstr = std::vector<std::string>({ "Villager","BerryBush","Rock","Wood","Coin" });
    cardpack->SetCards(vstr);
    AddCard(cardpack);

    for (int i = 0; i < m_Shops.size(); i++) {
        
        if (auto a = std::dynamic_pointer_cast<card::Shop>(m_Shops[i])) {
            a->ShopInit();
            //LOG_ERROR("{}", m_Shops[i]->GetCardName());
        }
        m_Shops[i]->SetTranslation(glm::vec3(-950 + i * 280, 1050, 0));
        m_Shops[i]->SetMoveable(0);
        AddCard(m_Shops[i]);
    }
    m_GiraffeText->SetZIndex(-1);
    m_GiraffeText->InitText(RESOURCE_DIR"/fonts/Inter.ttf", 75, "Pause",
       glm::vec3(255,255,255));
    m_GiraffeText->SetVisible(0);

    m_Background->SetImage(RESOURCE_DIR"/sprites/Background.png");

    m_SideElement[0]->SetImage(RESOURCE_DIR"/sprites/SideBlock.png");
    m_SideElement[0]->SetMoveable(1);
    m_SideElement[0]->SetTranslation(glm::vec3(-520, 0, 0));
    m_SideElement[0]->SetScaledSize(glm::vec2({ 1, 1.1 }));
    m_SideElement[0]->SetMoveable(0);
    m_SideElement[0]->SetZIndex(1);
    m_SideElement[0]->SetVisible(0);
    
    m_SideElement[1]->SetImage(RESOURCE_DIR"/sprites/Button0.png");
    m_SideElement[1]->SetMoveable(1);
    m_SideElement[1]->SetTranslation(glm::vec3(-408, 0, 0));
    m_SideElement[1]->SetMoveable(0);
    m_SideElement[1]->SetZIndex(2);
    m_SideElement[1]->SetVisible(0);
    

    m_SideElement[2]->SetImage(RESOURCE_DIR"/sprites/Button1.png");
    m_SideElement[2]->SetMoveable(1);
    m_SideElement[2]->SetTranslation(glm::vec3(-625, 0, 0));
    m_SideElement[2]->SetMoveable(0);
    m_SideElement[2]->SetZIndex(2);
    m_SideElement[2]->SetVisible(1);
   

    m_SideText->InitText(RESOURCE_DIR"/fonts/Inter.ttf", 16, "Blue Print", glm::vec3(0, 0, 0));
    m_SideText->BluePrintINIT();
    m_SideText->SetTranslation(glm::vec3(-610, 18, 0));
    m_SideText->SetZIndex(2);
    m_SideText->SetVisible(0);
    
    m_Menu->SetImage(RESOURCE_DIR"/sprites/Menu.png");
    m_Menu->SetZIndex(1);
    m_Menu->SetVisible(1);
    
    m_MenuElement[0]->InitText(RESOURCE_DIR"/fonts/Welatte Brush.ttf", 90, "stackland!",
        glm::vec3(0, 0, 0));
    m_MenuElement[0]->SetTranslation(glm::vec3(0, 185, 0));
    m_MenuElement[0]->SetZIndex(1.5);

    m_MenuElement[1]->InitText(RESOURCE_DIR"/fonts/Welatte Brush.ttf", 75, "start",
        glm::vec3(0, 0, 0));
    m_MenuElement[1]->SetTranslation(glm::vec3(0, 30, 0));
    m_MenuElement[1]->SetZIndex(1.5);

    m_MenuElement[2]->InitText(RESOURCE_DIR"/fonts/Welatte Brush.ttf", 75, "quit",
        glm::vec3(0, 0, 0));
    m_MenuElement[2]->SetTranslation(glm::vec3(0, -100, 0));
    m_MenuElement[2]->SetZIndex(1.5);
    //AddCard(card::CardMaker::MakeCard("CoinChest"));
    m_Mouse->Start();
    m_Mouse->SetZIndex(5);

    for (auto m : m_MenuElement) {
        m_Root.AddChild(m);
    }
    m_InteractiveBox->SetVisible(0);
    m_Root.AddChild(m_InteractiveBox);
    m_Root.AddChild(m_Menu);
    m_Root.AddChild(m_Background);
    m_Root.AddChild(m_Board);
    m_Root.AddChild(m_GiraffeText); 
    m_Root.AddChild(m_Mouse);
    m_Root.AddChild(m_System);
    m_Root.AddChild(m_SideText);
    for (auto m : m_SideElement) {
        m_Root.AddChild(m);
    }

    m_CurrentState = State::UPDATE;
}


void App::Update() {
    /*if (Util::Input::IsKeyUp(Util::Keycode::X)) {
        Camera::CameraShake();
        
    }*/

    if (Util::Input::IfExit()) {
        m_CurrentState = State::END;
        return;
    }
    
    if (Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB)) {
        m_Mouse->ClickUp();
    }
    switch (m_Modle)
    {
    case App::Modle::Origin:
        Origin();
        break;
    case App::Modle::Menu:
        Menu();
        break;
    case App::Modle::Playing:
        Playing();
        break;
    default:
        break;
    }
    if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB)) {
        m_Mouse->ClickDown();
    }
    
    if (card::CardElementPool::m_CardLine != nullptr) {
        card::CardElementPool::m_CardLine->Update();
    }
    m_Root.Update();
}

void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
    m_WorldCards.clear();
    VillagerLocation.clear();
    m_SideText.reset();
}


void App::AddCardForG(std::shared_ptr<card::Card> NewCard) {
    
    if (NewCard != nullptr) {
        auto target = NewCard->GetTransform().translation;
        auto lowerBound = m_WorldCards.lower_bound(target.x - 600);
        auto upperBound = m_WorldCards.upper_bound(target.x + 600);

        std::vector<std::multimap<int, std::shared_ptr<card::Card>>::iterator> stacks;
        for (auto it = lowerBound; it != upperBound; ++it) {
            stacks.push_back(it);
        }
      

        for (auto stack : stacks) {
            if (stack->second->GetCardName()==NewCard->GetCardName()  && ShapeHelper::IsCardNearStack(stack->second, NewCard) && stack->second != NewCard->GetLast() && stack->second->CanHaveCardOnTop(NewCard)) {

                NewCard->BindParent(stack->second);
                stack->second->m_CanSynthetic = true;
                stack->second = NewCard->GetLast();
                stack->second->StackRootUpdate();
                if (stack->second->GetRoot()->GetPushCount() == 0) {
                    m_PushProcessingArea.push_back(stack->second->GetRoot());
                }
                return ;
            }
        }
        
        m_WorldCards.emplace(NewCard->GetTransform().translation.x, NewCard);
        if (NewCard->GetRoot()->GetPushCount() == 0) {
            m_PushProcessingArea.push_back(NewCard->GetRoot());
        }
    }
}
void App::AddCard(std::shared_ptr<card::Card> NewCard) {
    if (NewCard != nullptr) {
        m_WorldCards.emplace(NewCard->GetTransform().translation.x, NewCard);
        if (NewCard->GetRoot()->GetPushCount() == 0) {
            m_PushProcessingArea.push_back(NewCard->GetRoot());
        }
    }
}

void App::AddObjectToRoot(std::shared_ptr<Util::GameObject> object) {
    m_Root.AddChild(object);
}

void App::MoveCardToNewX(const std::shared_ptr<card::Card>& specifiedObj, int oldX) {
    
    int newX = specifiedObj->GetRoot()->GetTransform().translation.x;
    auto range = m_WorldCards.equal_range(oldX);
    for (auto it = range.first; it != range.second; ++it) {
        if (it->second == specifiedObj) { // 检查指针是否指向相同的对象
            m_WorldCards.erase(it);
            m_WorldCards.emplace(newX, specifiedObj);

            return;
        }
    }

    // 如果未找到指定对象，则执行全部查找
    for (auto it = m_WorldCards.begin(); it != m_WorldCards.end(); ++it) {
        if (it->second == specifiedObj) { // 检查指针是否指向相同的对象
            m_WorldCards.erase(it);
            m_WorldCards.emplace(newX, specifiedObj);
            return;
        }
    }
    
}

void App::RemoveCard(const std::shared_ptr<card::Card>& specifiedObj, int X) {
    auto range = m_WorldCards.equal_range(X);
    for (auto it = range.first; it != range.second; ++it) {
        if (it->second == specifiedObj) {
            m_WorldCards.erase(it);
            return;
        }
    }
    for (auto it = m_WorldCards.begin(); it != m_WorldCards.end(); ++it) {
        if (it->second == specifiedObj) {
            m_WorldCards.erase(it);
            return;
        }
    }
}
App::PauseOrPlay App::m_IsPlayButton = PauseOrPlay::Play;
std::multimap<int, std::shared_ptr<card::Card>> App::m_WorldCards = {};
Util::Root App::m_Root;
std::list<std::weak_ptr<card::Card>> App::m_PushProcessingArea = {};
std::vector<std::weak_ptr<card::Card>> App::VillagerLocation = {};
std::shared_ptr<GiraffeText > App::m_SideText = std::make_shared<GiraffeText>();
std::shared_ptr<Mouse> App::m_Mouse = std::make_shared<Mouse>();
App::SystemStatus App::m_SystemMode = App::SystemStatus::Settlement5;

