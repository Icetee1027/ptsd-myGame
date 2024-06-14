#include "App.hpp"
#include <random>
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "Card/CardMaker.hpp"
#include "GiraffeText.hpp"
#include "ShapeHelper.hpp"
#include "Util/Time.hpp"
bool customCompare1(const std::multimap<int, std::shared_ptr<card::Card>>::iterator& a,
    const std::multimap<int, std::shared_ptr<card::Card>>::iterator& b,
    const glm::vec3& targetPosition) {
    glm::vec3 distanceA = a->second->GetTransform().translation - targetPosition;
    glm::vec3 distanceB = b->second->GetTransform().translation - targetPosition;
    // 使用glm::length計算向量長度作為距離
    return glm::length(distanceA) < glm::length(distanceB);
}
bool customCompareDown(const std::multimap<int, std::shared_ptr<card::Card>>::iterator& a, const std::multimap<int, std::shared_ptr<card::Card>>::iterator& b) {
    return a->second->GetTransform().translation.y < b->second->GetTransform().translation.y;
}
void App::Playing() {

    if (Util::Input::IsKeyUp(Util::Keycode::SPACE) && m_SystemMode == SystemStatus::play) {
        m_IsPlayButton = m_IsPlayButton == App::PauseOrPlay::Pause ? App::PauseOrPlay::Play : App::PauseOrPlay::Pause;
        if (m_IsPlayButton == App::PauseOrPlay::Pause) m_GiraffeText->SetVisible(1);
        else  m_GiraffeText->SetVisible(0);
    }

    switch (m_IsPlayButton)
    {
    case App::PauseOrPlay::Pause:
        break;
    case App::PauseOrPlay::Play:
        break;
    }
    if (Util::Input::IsKeyUp(Util::Keycode::F1) && (m_SystemMode == SystemStatus::Settlement1 || m_SystemMode == SystemStatus::play)) {
        std::shared_ptr<card::Card> m_cardpack2 = card::CardMaker::MakeCard("Pack");
        auto cardpack = std::dynamic_pointer_cast<card::CardPack>(m_cardpack2);
        auto vstr = std::vector<std::string>({ "Villager","BerryBush","BerryBush","AppleTree","AppleTree","IronDeposit"});
        cardpack->SetCards(vstr);
        cardpack->SetTranslation(glm::vec3(100,0,0));
        AddCard(cardpack);
    }
    if (Util::Input::IsKeyUp(Util::Keycode::F2) && (m_SystemMode == SystemStatus::Settlement1 || m_SystemMode == SystemStatus::play)) {
        std::shared_ptr<card::Card> m_cardpack2 = card::CardMaker::MakeCard("Pack");
        auto cardpack = std::dynamic_pointer_cast<card::CardPack>(m_cardpack2);
        auto vstr = std::vector<std::string>({ "Villager","House" });
        cardpack->SetTranslation(glm::vec3(201, 0, 0));
        cardpack->SetCards(vstr);
        AddCard(cardpack);
    }
    if (Util::Input::IsKeyUp(Util::Keycode::F3) && (m_SystemMode == SystemStatus::Settlement1 || m_SystemMode == SystemStatus::play)) {
        std::shared_ptr<card::Card> m_cardpack2 = card::CardMaker::MakeCard("Pack");
        auto cardpack = std::dynamic_pointer_cast<card::CardPack>(m_cardpack2);
        auto vstr = std::vector<std::string>({ "IronBar","Stone","Coin","Coin","Coin","Plank","Brick","Coin","Wood","Wood"});
        cardpack->SetCards(vstr);
        cardpack->SetTranslation(glm::vec3(220, 0, 0));
        AddCard(cardpack); 
    }
    if (Util::Input::IsKeyUp(Util::Keycode::F4) && (m_SystemMode == SystemStatus::Settlement1 || m_SystemMode == SystemStatus::play)) {
        std::shared_ptr<card::Card> m_cardpack2 = card::CardMaker::MakeCard("Pack");
        auto cardpack = std::dynamic_pointer_cast<card::CardPack>(m_cardpack2);
        auto vstr = std::vector<std::string>({ "Stove","RawMeat","Stove","Egg","Egg","Berry","Soil","Farm","Apple"});
        cardpack->SetCards(vstr);
        cardpack->SetTranslation(glm::vec3(300, 0, 0));
        AddCard(cardpack);
    }

    if (Util::Input::IsKeyUp(Util::Keycode::F5) && (m_SystemMode == SystemStatus::Settlement1 || m_SystemMode == SystemStatus::play)) {
        std::shared_ptr<card::Card> m_cardpack2 = card::CardMaker::MakeCard("Pack");
        auto cardpack = std::dynamic_pointer_cast<card::CardPack>(m_cardpack2);
        auto vstr = std::vector<std::string>({ "Militia","Swordsman","Dog","Swordsman","Swordsman","Bear","Wolf","Slime","Slime"});
        cardpack->SetCards(vstr);
        cardpack->SetTranslation(glm::vec3(400, 0, 0));
        AddCard(cardpack);
    }
    if (Util::Input::IsKeyUp(Util::Keycode::F7) && (m_SystemMode == SystemStatus::Settlement1 || m_SystemMode == SystemStatus::play)) {
        std::shared_ptr<card::Card> m_cardpack2 = card::CardMaker::MakeCard("Pack");
        auto cardpack = std::dynamic_pointer_cast<card::CardPack>(m_cardpack2);
        auto vstr = std::vector<std::string>({ "Stew","Stew","Stew","Stew","Stew","Stew","Stew","Stew","Stew","Stew","Stew","Stew","Stew","Stew","Stew","Stew","Stew","Stew","Stew" });
        cardpack->SetCards(vstr);
        cardpack->SetTranslation(glm::vec3(600, 0, 0));
        AddCard(cardpack);
    }
    if (Util::Input::IsKeyUp(Util::Keycode::F6) && (m_SystemMode == SystemStatus::Settlement1 || m_SystemMode == SystemStatus::play)) {
        std::shared_ptr<card::Card> m_cardpack2 = card::CardMaker::MakeCard("Pack");
        auto cardpack = std::dynamic_pointer_cast<card::CardPack>(m_cardpack2);
        auto vstr = std::vector<std::string>({ "Villager","Villager","Villager","Villager","Sword","Sword","Sword","Sword","Villager","Villager","Villager","Villager","Sword","Sword","Sword","Sword","Temple","GoldenGoblet"});
        cardpack->SetCards(vstr);
        cardpack->SetTranslation(glm::vec3(650, 0, 0));
        AddCard(cardpack);
    }

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE)) {
        mouseUp();
        m_Modle = Modle::Menu;
        m_IsPlayButton = PauseOrPlay::Pause;
        m_GiraffeText->SetVisible(1);
        m_Menu->SetVisible(1);
        for (auto t : m_MenuElement) {
            t->SetVisible(1);
        }
        return;
    }

    //--------------------------------------------------------------------
    if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB) && (m_SystemMode == SystemStatus::Settlement1 || m_SystemMode == SystemStatus::play)) {
        //LOG_DEBUG("worldsize:{}", m_WorldCards.size());
        if (!m_Mouse->HasObjectBind()) {
            for (int it = 0; it < 3; it++) {
                if (ShapeHelper::IsPonstInMenu(m_SideElement[it], Util::Input::GetCursorPosition())&& m_SideElement[it]->GetVisible()) {
                    m_Mouse->ObjectBind(m_SideElement[it]);
                    if (it == 0)continue;
                    else if (it == 1) {
                        m_SideElement[2]->SetVisible(1);
                        m_SideElement[1]->SetVisible(0);
                        m_SideElement[0]->SetVisible(0);
                        m_SideText->SetVisible(0);

                    }
                    else if (it == 2) {
                        m_SideElement[2]->SetVisible(0);
                        m_SideElement[1]->SetVisible(1);
                        m_SideElement[0]->SetVisible(1);
                        m_SideText->SetVisible(1);


                    }
                }
            }
            
        }

        if (!m_Mouse->HasObjectBind()) {
            auto target = glm::vec3(m_Mouse->GetMousePosition(0), 0);
            auto lowerBound = m_WorldCards.lower_bound(target.x - 100);
            auto upperBound = m_WorldCards.upper_bound(target.x + 100);

            std::vector<std::multimap<int, std::shared_ptr<card::Card>>::iterator> stacks;
            for (auto it = lowerBound; it != upperBound; ++it) {
                stacks.push_back(it);
            }
            std::sort(stacks.begin(), stacks.end(), customCompareDown);
            for (auto stack : stacks) {
                auto m_Card = ShapeHelper::IsPointInStack(stack->second, m_Mouse->GetMousePosition(stack->second));

                if (m_Card != nullptr) {
                    
                    AddCard(m_Card->GetParent());
                    m_Card->UnBindParent();
                    m_Card->SetTranslation(glm::vec3(m_Card->GetTransform().translation.x, m_Card->GetTransform().translation.y, 25));
                    stack->second->GetRoot()->m_SyntheticStop = true;
                    stack->second->GetRoot()->m_CanSynthetic = true;
                    m_Mouse->ObjectBind(m_Card);

                    break;
                }
            }
        }
        if (!m_Mouse->HasObjectBind()) {
            m_Mouse->ObjectBind(m_Camera);
        }
       // LOG_DEBUG("Right button down");
    }

    if (Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB) && (m_SystemMode == SystemStatus::Settlement1 || m_SystemMode == SystemStatus::play)) {
        mouseUp();
        //LOG_DEBUG("Right button up");
    }

    if (Util::Input::IsKeyUp(Util::Keycode::E) && (m_SystemMode == SystemStatus::Settlement1 || m_SystemMode == SystemStatus::play)) {
        if (m_SideElement[1]->GetVisible() == 1) {
            m_SideElement[2]->SetVisible(1);
            m_SideElement[1]->SetVisible(0);
            m_SideElement[0]->SetVisible(0);
            m_SideText->SetVisible(0);

        }
        else{
            m_SideElement[2]->SetVisible(0);
            m_SideElement[1]->SetVisible(1);
            m_SideElement[0]->SetVisible(1);
            m_SideText->SetVisible(1);
        }
    }

    //------------------------------------------------------------------
    CameraUpdate();
    m_Mouse->Update();
    SystemUpdta();
    StackUpdate();
    

}
void App::CameraUpdate() {
    if (Util::Input::IfScroll() && (m_SystemMode == SystemStatus::Settlement1 || m_SystemMode == SystemStatus::play) ) {
        auto delta = Util::Input::GetScrollDistance();
        m_Camera->MoveCamera(0, 0, 30 * delta.y);
    }

    if (Util::Input::IsKeyPressed(Util::Keycode::W) && (m_SystemMode == SystemStatus::Settlement1 || m_SystemMode == SystemStatus::play) ) {
        m_Camera->MoveCamera(0, 8, 0);
    }

    if (Util::Input::IsKeyPressed(Util::Keycode::S) && (m_SystemMode == SystemStatus::Settlement1 || m_SystemMode == SystemStatus::play)) {
        m_Camera->MoveCamera(0, -8, 0);
    }

    if (Util::Input::IsKeyPressed(Util::Keycode::A) && (m_SystemMode == SystemStatus::Settlement1 || m_SystemMode == SystemStatus::play)) {
        m_Camera->MoveCamera(-8, 0, 0);
    }

    if (Util::Input::IsKeyPressed(Util::Keycode::D) && (m_SystemMode == SystemStatus::Settlement1 || m_SystemMode == SystemStatus::play)) {
        m_Camera->MoveCamera(8, 0, 0);
    }

    m_Camera->Update();
}

void App::StackUpdate() {
    std::vector<std::shared_ptr<card::Card>> cardsToUpdate;
    for (auto it = m_WorldCards.begin(); it != m_WorldCards.end(); ++it) {
        cardsToUpdate.push_back(it->second);
    }
    auto Cardobject = std::dynamic_pointer_cast<card::Card>(m_Mouse->GetBindObject());
    for (const auto& card : cardsToUpdate) {
        if (Cardobject && card->CanHaveCardOnTop(Cardobject) && m_Mouse->GetBindObject() != card->GetRoot() && card->GetCardType() != card::Type::Mob && card->GetCardName() != "Arena")card->GetChildren()[2]->SetVisible(1);
        else { card->GetChildren()[2]->SetVisible(0); }
        card->Update();
    }
    if (card::Shop::statusUPdata) {
        card::Shop::statusUPdata == false;
        for (int i = 0; i < m_Shops.size(); i++) {
            if (auto a = std::dynamic_pointer_cast<card::Shop>(m_Shops[i])) {
                a->ShopInit();
            }
         
        }
    }
    std::vector<std::list<std::weak_ptr<card::Card>>::iterator> expiredIterators;
   
    auto run = m_PushProcessingArea.begin();
    while (run != m_PushProcessingArea.end()) {
        if (run->expired() || run->lock() == m_Mouse->GetBindObject()) {
            expiredIterators.push_back(run);
        }
        else {
            App::MoveCardToNewX(run->lock()->GetLast(), int(run->lock()->GetLast()->GetTransform().translation.x));
            auto object = run->lock()->GetRoot();
            auto target = glm::vec2(object->GetRoot()->GetTransform().translation.x, object->GetRoot()->GetTransform().translation.y);
            auto lowerBound = m_WorldCards.lower_bound(target.x -1400);
            auto upperBound = m_WorldCards.upper_bound(target.x + 1400);
            float distance = 0;

            for (auto st = lowerBound; st != upperBound; ++st) {
                    //LOG_DEBUG("123  {}    {}     {}", ShapeHelper::IsStackInStack(st->second->GetRoot(), object), st->second != object->GetLast(), st->second->GetRoot() != m_Mouse->GetBindObject());
                if (ShapeHelper::IsStackInStack(st->second->GetRoot(), object) && st->second != object->GetLast() && st->second->GetRoot() != m_Mouse->GetBindObject()) {
                    //LOG_ERROR("name {}", st->second->GetRoot()->GetCardName());

                    if (st->second->GetPushCount() == 0 && st->second->IsCanPush() <= object->IsCanPush()) {
                        m_PushProcessingArea.insert(std::next(run), st->second);
                    }
                    glm::vec2  itposition(st->second->GetRoot()->GetTransform().translation.x, st->second->GetRoot()->GetTransform().translation.y);
                    if ((!distance || distance > glm::distance(itposition, target)) && st->second->IsCanPush() >= object->IsCanPush()) { distance = glm::distance(itposition, target); 
                    }
                    else continue;
                    glm::vec2 direction = target - itposition;
                    glm::vec2 unitVector = glm::normalize(direction);
                    float proportion = st->second->IsCanPush() == object->IsCanPush()?float(st->second->GetStackSize())/ float(object->GetStackSize() + st->second->GetStackSize()):1;
                    object->SetPushing(unitVector * (0.52f *  proportion), 15);
                }
            }
            if (object->GetPushCount() == 0) {
                expiredIterators.push_back(run);
            }
        }
        run++;
    }
    for (auto it : expiredIterators) {
        m_PushProcessingArea.erase(it);
    }

}

void App::mouseUp() {
    auto object = std::dynamic_pointer_cast<card::Card>(m_Mouse->GetBindObject());
    if (object&&object->CanMoveable()==1) {
        m_Mouse->GetBindObject()->SetTranslation(glm::vec3(m_Mouse->GetBindObject()->GetTransform().translation.x, m_Mouse->GetBindObject()->GetTransform().translation.y, 0));
        auto target = object->GetTransform().translation;
        auto lowerBound = m_WorldCards.lower_bound(target.x - 5200);
        auto upperBound = m_WorldCards.upper_bound(target.x + 5200);

        std::vector<std::multimap<int, std::shared_ptr<card::Card>>::iterator> stacks;
        for (auto it = lowerBound; it != upperBound; ++it) {
            stacks.push_back(it);
        }
        std::sort(stacks.begin(), stacks.end(), [&target](const auto& a, const auto& b) {
            return customCompare1(a, b, target);
            });

        for (auto stack : stacks) {
            if (ShapeHelper::IsCardInStack(stack->second, object) && stack->second != object->GetLast() && stack->second->CanHaveCardOnTop(object)) {
                object->BindParent(stack->second);
                stack->second->m_CanSynthetic = true;//
                if(stack->second->GetRoot()->GetPushCount() == 0) {
                    stack->second->SetPushing(glm::vec2(), 2);
                }
                stack->second = object->GetLast();
                if (stack->second->GetRoot()->GetPushCount() == 0) {
                    m_PushProcessingArea.push_back(stack->second->GetRoot());
                }
                App::RemoveCard(object->GetLast(), m_Mouse->GetCardOldX());
                m_Mouse->ObjectUmBind();
                break;
            }
        }
        if (m_Mouse->GetBindObject()) {
            App::MoveCardToNewX(object->GetLast(), int(object->GetLast()->GetTransform().translation.x));
            object->m_CanSynthetic = true;
            if (object->GetRoot()->GetPushCount() == 0) {
                m_PushProcessingArea.push_back(object->GetRoot());
                object->SetPushing(glm::vec2(), 2);

            }
        }
    }
    m_Mouse->ObjectUmBind();
}
void GeneratePortal(std::string& cardname) {
    if (cardname == "")return;
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> distribution(1, 360);
    float randomNumber = distribution(rng);
    float angleRadians = glm::radians(randomNumber);
    float sineValue = glm::sin(angleRadians);
    float cosineValue = glm::cos(angleRadians);
    auto card = card::CardMaker::MakeCard(cardname);
    bool moveable = card->CanMoveable();
    card->SetMoveable(1);
    card->SetTranslation(glm::vec3(sineValue * 3000 , cosineValue * 2500 , 0));
    card->SetMoveable(moveable);
    card->m_CanSynthetic = true;
    App::AddCard(card);


}
void App::SystemUpdta() {
    m_System->Update();
   
    switch (m_SystemMode)
    {
    case App::SystemStatus::play:
        if (m_System->IsSettlement()) {
            m_SystemMode = SystemStatus::Settlement1;
            m_IsPlayButton = PauseOrPlay::Pause;
            m_GiraffeText->SetVisible(1);
            m_InteractiveBox->SetVisible(1);
            m_InteractiveBox->SetMoveable(1);
            m_InteractiveBox->SetTranslation(glm::vec3(-380, -200, 0));
            m_InteractiveBox->SetMoveable(0);

        }
        break;
    case App::SystemStatus::Settlement1:
        if (m_System->maxhas >= m_System->nowhas || (Util::Input::IsKeyUp(Util::Keycode::Q))) {
            m_InteractiveBox->SetText(0, "The end of this month. \nYou can start feeding the villagers.");
            m_InteractiveBox->SetText(1, "ok");
            if (ShapeHelper::IsPonstInMenu(m_InteractiveBox->GetChildren()[1], Util::Input::GetCursorPosition())|| (Util::Input::IsKeyUp(Util::Keycode::Q))) {
                m_InteractiveBox->GetChildren()[1]->SetScaledSize(glm::vec2(1.5, 1.5));
                if (Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB) || (Util::Input::IsKeyUp(Util::Keycode::Q))) {
                    m_SystemMode = SystemStatus::Settlement2;
                    m_InteractiveBox->SetVisible(0);
                    m_SettlementVillage.clear();
                    m_SettlementFood.clear();
                    for (auto& c : m_WorldCards) {
                        for (auto& a : c.second->GetAllCardsInStack()) {
                            if (auto x = std::dynamic_pointer_cast<card::BaseVillager>(a)) {
                                m_SettlementVillage.push_back(x);
                                c.second->m_CanSynthetic = true;
                            }
                            else if (auto x = std::dynamic_pointer_cast<card::Food>(a)) {
                                m_SettlementFood.push_back(x);
                                c.second->GetRoot()->StatusStackRootUpDate = true;
                                c.second->m_CanSynthetic = true;


                            }
                            else if (auto x = std::dynamic_pointer_cast<card::Kid>(a)) {
                                m_SettlementVillage.push_back(x);
                                c.second->m_CanSynthetic = true;

                            }

                        }
                    }
                    for (auto& c : m_WorldCards) {
                        if (c.second->GetCardName() == "TravellingCart") {
                            c.second->RemoveCard();
                            break;
                        }
                    }
                    if (!m_SettlementVillage.empty()) {
                        m_EndPoint = { m_SettlementVillage.back()->GetTransform().translation.x,m_SettlementVillage.back()->GetTransform().translation.y };
                        m_NeedFood = (m_SettlementVillage.back()->GetCardName() == "Dog" || m_SettlementVillage.back()->GetCardName() == "Baby")? 1:2;
                    }
                    if (!m_SettlementFood.empty()) {
                        m_StartPoint = { m_SettlementFood.back()->GetTransform().translation.x ,m_SettlementFood.back()->GetTransform().translation.y };
                        m_Food = m_SettlementFood.back()->GetSatiety();
                    }
                }

            }
            else {
                m_InteractiveBox->GetChildren()[1]->SetScaledSize(glm::vec2(1, 1));
            }
        }
        else {
            m_InteractiveBox->SetText(0, "There are too many cards on the field! \nPlease reduce the number of cards.");
            m_InteractiveBox->SetText(1, " ");
        }
        m_InteractiveBox->Update();
        break;
    case App::SystemStatus::Settlement2:
        Settlement1Updata();
        break;
    case App::SystemStatus::Settlement3:
        if (ShapeHelper::IsPonstInMenu(m_InteractiveBox->GetChildren()[1], Util::Input::GetCursorPosition())) {
            m_InteractiveBox->GetChildren()[1]->SetScaledSize(glm::vec2(1.5, 1.5));
            
            if (Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB)) {
                std::string text = "";
                if (m_System->MoonCount > 5&& (m_System->MoonCount+2) % 4 == 0) {
                    if ((m_System->MoonCount+2)%12 ==0 ){
                        text = "A wild rare portal appeared!!\n";
                        GeneratePortal(std::string("RarePortal"));
                    }
                    else {
                        text = "A wild strange portal appeared!!\n";
                        GeneratePortal(std::string("StrangePortal"));
                    }
                }
                if (m_System->MoonCount > 2 && (m_System->MoonCount) % 3 == 0) {
                    text += "A Travelling Car appeared!!\n";
                    GeneratePortal(std::string("TravellingCart"));

                }
                m_InteractiveBox->SetText(0, text+"Start of a new month.");
                
                for (auto& a : m_SettlementVillage) {
                    if (auto x = std::dynamic_pointer_cast<card::BaseVillager>(a)) {
                        x->GetRoot()->m_CanSynthetic = true;
                        x->VillagerDead();
                        x->RemoveCard();
                    }
                    else if (auto x = std::dynamic_pointer_cast<card::Kid>(a)) {
                        x->GetRoot()->m_CanSynthetic = true;
                        x->VillagerDead();
                        x->RemoveCard();

                    }
                }
                m_SystemMode = SystemStatus::Settlement4;
                m_SettlementVillage.clear();
                m_SettlementFood.clear();
               
            }

        }
        else {
            m_InteractiveBox->GetChildren()[1]->SetScaledSize(glm::vec2(1, 1));
        }
       
        break;
    case App::SystemStatus::Settlement4:
        if (ShapeHelper::IsPonstInMenu(m_InteractiveBox->GetChildren()[1], Util::Input::GetCursorPosition())) {
            m_InteractiveBox->GetChildren()[1]->SetScaledSize(glm::vec2(1.5, 1.5));
            if (Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB)) {
                m_System->m_MoonTimeCount = 0;
                m_System->MoonCount++;
                m_SystemMode = SystemStatus::play;
                m_InteractiveBox->SetVisible(0);
                m_IsPlayButton =App::PauseOrPlay::Play ;
                m_System->Settlement = 0;
                if (m_IsPlayButton == App::PauseOrPlay::Pause) m_GiraffeText->SetVisible(1);
                else  m_GiraffeText->SetVisible(0);
            }

        }
        else {
            m_InteractiveBox->GetChildren()[1]->SetScaledSize(glm::vec2(1, 1));
        }
        break;
    case App::SystemStatus::Settlement5:
        m_GiraffeText->SetVisible(1);
        m_InteractiveBox->SetVisible(1);
        m_InteractiveBox->SetMoveable(1);
        m_InteractiveBox->SetTranslation(glm::vec3(-380, -200, 0));
        m_InteractiveBox->SetMoveable(0);
        m_InteractiveBox->Update();
        m_InteractiveBox->SetText(0, "Click on the card pack to start the game.");
        if (ShapeHelper::IsPonstInMenu(m_InteractiveBox->GetChildren()[1], Util::Input::GetCursorPosition())) {
            m_InteractiveBox->GetChildren()[1]->SetScaledSize(glm::vec2(1.5, 1.5));
            if (Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB)) {
                m_System->start = true;
                m_SystemMode = SystemStatus::play;
                m_InteractiveBox->SetVisible(0);
                m_IsPlayButton = App::PauseOrPlay::Play;
                m_System->Settlement = 0;
                if (m_IsPlayButton == App::PauseOrPlay::Pause) m_GiraffeText->SetVisible(1);
                else  m_GiraffeText->SetVisible(0);
            }

        }
        else {
            m_InteractiveBox->GetChildren()[1]->SetScaledSize(glm::vec2(1, 1));
        }
        break;
    case App::SystemStatus::Settlement6:
        m_GiraffeText->SetVisible(1);
        m_InteractiveBox->SetVisible(1);
        m_InteractiveBox->SetMoveable(1);
        m_InteractiveBox->SetTranslation(glm::vec3(-380, -200, 0));
        m_InteractiveBox->SetMoveable(0);
        m_InteractiveBox->Update();
        m_InteractiveBox->SetText(0, "You Lose!\nAll the villagers died.\nGame is over!");
        if (ShapeHelper::IsPonstInMenu(m_InteractiveBox->GetChildren()[1], Util::Input::GetCursorPosition())) {
            m_InteractiveBox->GetChildren()[1]->SetScaledSize(glm::vec2(1.5, 1.5));
            if (Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB)) {
                m_CurrentState = State::END;
                if (m_IsPlayButton == App::PauseOrPlay::Pause) m_GiraffeText->SetVisible(1);
                else  m_GiraffeText->SetVisible(0);
            }

        }
        else {
            m_InteractiveBox->GetChildren()[1]->SetScaledSize(glm::vec2(1, 1));
        }
        break;
    default:
        break;
    }

}
glm::vec2 lerp(const glm::vec2& start, const glm::vec2& end, float t) {
    return (1.0f - t) * start + t * end;
}

// 函数：根据时间百分比移动圆球
glm::vec2 moveCircle(const glm::vec2& startPoint, const glm::vec2& endPoint, float timePercentage) {
    if (timePercentage < 0.0f || timePercentage > 1.0f) {
        return endPoint;
    }
    return lerp(startPoint, endPoint, timePercentage);
}
void App::Settlement1Updata() {
    if (m_TimeCount>0.5) {
        m_TimeCount = 0;
        int looe = m_NeedFood;
        m_NeedFood -= m_Food;
        m_Food -= looe;
        if(m_NeedFood<=0){
            if (!m_SettlementVillage.empty())m_SettlementVillage.pop_back();
            if (!m_SettlementVillage.empty()) {
                m_EndPoint = { m_SettlementVillage.back()->GetTransform().translation.x,m_SettlementVillage.back()->GetTransform().translation.y };
                m_NeedFood = (m_SettlementVillage.back()->GetCardName() == "Dog" || m_SettlementVillage.back()->GetCardName() == "Baby") ? 1 : 2;

            }
            else {
                m_SettlementFood.clear();
                m_Camera->SetTranslation(glm::vec3(0, 0, -520));
                m_InteractiveBox->SetVisible(1);
                m_InteractiveBox->SetText(0, " This month, none of your villagers starved to death.");
                m_SystemMode = SystemStatus::Settlement3;
                return;
            }
        }
        if(m_Food<=0){
            if (!m_SettlementFood.empty())m_SettlementFood.pop_back();
            if (!m_SettlementFood.empty()) {
                m_StartPoint = { m_SettlementFood.back()->GetTransform().translation.x ,m_SettlementFood.back()->GetTransform().translation.y };
                m_Food = m_SettlementFood.back()->GetSatiety();
            }
            else {
                m_SettlementFood.clear();
                m_InteractiveBox->SetText(0," The village suffered from starvation deaths of " + std::to_string(m_SettlementVillage.size()) + " Village this month." );
                m_InteractiveBox->SetVisible(1);
                m_Camera->SetTranslation(glm::vec3(0, 0, -320));
                m_SystemMode = SystemStatus::Settlement3;
                return;
            }
        }
        else {
            m_StartPoint = { m_SettlementFood.back()->GetTransform().translation.x ,m_SettlementFood.back()->GetTransform().translation.y };
        }
        
    }
    else {
        if (m_SettlementVillage.empty() || m_SettlementFood.empty()) {
            m_TimeCount += 1;
        }
        else {
            m_SettlementFood.back()->RemoveCard();
            m_Camera->SetTranslation(glm::vec3(-m_SettlementFood.back()->GetTransform().translation.x, -m_SettlementFood.back()->GetTransform().translation.y, -120));
            m_SettlementFood.back()->SetTranslation(glm::vec3(moveCircle(m_StartPoint, m_EndPoint, m_TimeCount / 0.5), 7));
            m_TimeCount += Util::Time::GetDeltaTime();
            m_SettlementFood.back()->Update();
        }
     


    }

}