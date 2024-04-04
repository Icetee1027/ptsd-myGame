#include "App.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "Card/CardMaker.hpp"
#include "GiraffeText.hpp"
#include "ShapeHelper.hpp"
#include "Util/Time.hpp"

void App::Start() {
   // LOG_TRACE("Start");
    m_Giraffe->SetDrawable(
        std::make_shared<Util::Image>(RESOURCE_DIR"/sprites/giraffe.png"));
    m_Giraffe->SetZIndex(5);
    m_Giraffe->Start();

    m_GiraffeText->SetZIndex(0);
    m_GiraffeText->Start();
    AddCard(card::CardMaker::MakeCard("CoinChest"));

    m_Mouse->Start();
    m_Mouse->SetZIndex(4);

    m_Root.AddChild(m_Board);
    m_Root.AddChild(m_Giraffe);
    m_Root.AddChild(m_GiraffeText);
    m_Root.AddChild(m_Mouse);


    m_CurrentState = State::UPDATE;
}

bool customCompare(const std::multimap<int, std::shared_ptr<card::Card>>::iterator& a, const std::multimap<int, std::shared_ptr<card::Card>>::iterator& b) {
    return a->second->GetTransform().translation.y < b->second->GetTransform().translation.y;
}

void App::Update() {

    
    if (Util::Input::IsKeyUp(Util::Keycode::SPACE)) {
        m_IsPlayButton = m_IsPlayButton== App::PauseOrPlay::Pause? App::PauseOrPlay::Play: App::PauseOrPlay::Pause;
        m_GiraffeText->SetVisible(!m_GiraffeText->GetVisible());
    }
    switch (m_IsPlayButton)
    {
    case App::PauseOrPlay::Pause:
        Pause();
        break;
    case App::PauseOrPlay::Play:
        Play();
        break;
    }
    //------------------------------------------------------------



    if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB)) {
        m_Mouse->ClickDown();
        //LOG_DEBUG("worldsize:{}", m_WorldCards.size());
        auto target = m_Mouse->GetMousePosition(0);
        auto lowerBound = m_WorldCards.lower_bound(target.x - 100);
        auto upperBound = m_WorldCards.upper_bound(target.x + 100);
  
        std::vector<std::multimap<int, std::shared_ptr<card::Card>>::iterator> stacks;
        for (auto it = lowerBound; it != upperBound; ++it) {
            stacks.push_back(it);
        }
        std::sort(stacks.begin(), stacks.end(), customCompare);
        for (auto stack : stacks) {
            auto m_Card = ShapeHelper::IsPointInStack(stack->second, m_Mouse->GetMousePosition(stack->second));
            
            if (m_Card!=nullptr) {
                AddCard(m_Card->GetParent());
                
                m_Card->UnBindParent();
                m_Mouse->ObjectBind(m_Card);
                
                break;
            }
        }

        if (!m_Mouse->HasObjectBind()) {
            m_Mouse->ObjectBind(m_Camera);
        }
        LOG_DEBUG("Right button down");
    }

    if (Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB)) {
        auto object = std::dynamic_pointer_cast<card::Card>(m_Mouse->GetBindObject());
        if (object) {
            
            auto target = object->GetTransform().translation;
            auto lowerBound = m_WorldCards.lower_bound(target.x - 200);
            auto upperBound = m_WorldCards.upper_bound(target.x + 200);

            std::vector<std::multimap<int, std::shared_ptr<card::Card>>::iterator> stacks;
            for (auto it = lowerBound; it != upperBound; ++it) {
                stacks.push_back(it);
            }
            std::sort(stacks.begin(), stacks.end(), customCompare);
            
            for (auto stack : stacks) {
                if (ShapeHelper::IsCardInStack(stack->second, object) && stack->second != object->GetLast()&& stack->second->CanHaveCardOnTop(object)) {
                    object->BindParent(stack->second);
                    stack->second = object->GetLast();
                    App::RemoveCard(object->GetLast(), m_Mouse->GetCardOldX());
                    m_Mouse->ObjectUmBind();
                    break;
                }
            }
            if (m_Mouse->GetBindObject()) {
                App::MoveCardToNewX(object->GetLast(), int(object->GetLast()->GetTransform().translation.x));
                if (object->GetRoot()->GetPushCount() == 0) {
                        m_PushProcessingArea.push_back(object->GetRoot());
                    }
            }
        }
        m_Mouse->ClickUp();
        m_Mouse->ObjectUmBind();
        LOG_DEBUG("Right button up");
    }
    
    if (Util::Input::IsKeyUp(Util::Keycode::K)) {
        
        LOG_DEBUG(" m_WorldCards.size() {}", m_WorldCards.size());
       // LOG_DEBUG(" m_PushProcessingArea.size() {}", m_PushProcessingArea.size());
    }

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    if (Util::Input::IsKeyUp(Util::Keycode::F)) {
        //std::shared_ptr<card::Card> sem = card::CardMaker::MakeCard(files[m_WorldCards.size()]);
        std::shared_ptr<card::Card> sem = card::CardMaker::MakeCard("Coin");
        sem->SetTranslation(glm::vec3(200* m_WorldCards.size()+1, 0, 0));
        AddCard(sem);
        
    }
    if (Util::Input::IsKeyUp(Util::Keycode::G)) {
        //std::shared_ptr<card::Card> sem = card::CardMaker::MakeCard(files[m_WorldCards.size()]);
        std::shared_ptr<card::Card> sem = card::CardMaker::MakeCard("CoinChest");
        sem->SetTranslation(glm::vec3(200 * m_WorldCards.size() + 1, 0, 0));
        AddCard(sem);
    }
    if (Util::Input::IsKeyUp(Util::Keycode::C)) {
        if (!m_WorldCards.empty()) {
    
            auto lastElementIterator = std::prev(m_WorldCards.end());
            // 删除最后一个元素
            lastElementIterator->second->RemoveStack();
        }
    
    }

   //------------------------------------------------------------------
    CameraUpdate();
    
    m_Mouse->Update();

  
    StackUpdate();
    m_Root.Update();
 
}

void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
    m_WorldCards.clear();
}
void App::CameraUpdate() {
    if (Util::Input::IfScroll()) {
        auto delta = Util::Input::GetScrollDistance();
        m_Camera->MoveCamera(0, 0, 30 * delta.y);
    }

    if (Util::Input::IsKeyPressed(Util::Keycode::W)) {
        m_Camera->MoveCamera(0, 8, 0);
    }

    if (Util::Input::IsKeyPressed(Util::Keycode::S)) {
        m_Camera->MoveCamera(0, -8, 0);
    }


    if (Util::Input::IsKeyPressed(Util::Keycode::A)) {
        m_Camera->MoveCamera(-8, 0, 0);
    }


    if (Util::Input::IsKeyPressed(Util::Keycode::D)) {
        m_Camera->MoveCamera(8, 0, 0);
    }
    m_Camera->Update();
}
void App::StackUpdate() {
   

    std::vector<std::shared_ptr<card::Card>> cardsToUpdate;
    for (auto it = m_WorldCards.begin(); it != m_WorldCards.end(); ++it) {
        cardsToUpdate.push_back(it->second);
    }
    for (const auto& card : cardsToUpdate) {
        card->Update();
    }

    std::vector<std::list<std::weak_ptr<card::Card>>::iterator> expiredIterators;
    
    auto run = m_PushProcessingArea.begin();

    while(run!=m_PushProcessingArea.end()) {
        if (run->expired()||run->lock()==m_Mouse->GetBindObject()) {
            expiredIterators.push_back(run);
        }
        else {
            App::MoveCardToNewX(run->lock()->GetLast(), int(run->lock()->GetLast()->GetTransform().translation.x));
            auto object = run->lock()->GetRoot(); 
            auto target = glm::vec2(object->GetRoot()->GetTransform().translation.x, object->GetRoot()->GetTransform().translation.y);
            auto lowerBound = m_WorldCards.lower_bound(target.x - 220);
            auto upperBound = m_WorldCards.upper_bound(target.x + 220);
            float distance=0;

            for (auto st = lowerBound; st != upperBound; ++st) {
                if (ShapeHelper::IsStackInStack(st->second->GetRoot(), object) && st->second != object->GetLast()&& st->second->GetRoot()!= m_Mouse->GetBindObject()) {

                    if (st->second->GetPushCount()==0){
                        m_PushProcessingArea.push_back(st->second);
                    }

                    glm::vec2  itposition(st->second->GetRoot()->GetTransform().translation.x,st->second->GetRoot()->GetTransform().translation.y);
                    if (!distance || distance > glm::distance(itposition, target)) { distance = glm::distance(itposition, target); }
                    else continue;
                    glm::vec2 direction = target - itposition;
                    glm::vec2 unitVector = glm::normalize(direction);
                    object->SetPushing(unitVector*0.05f*float(st->second->GetStackSize())/float(object->GetStackSize()+ st->second->GetStackSize()), 40);
                }
            }
            if (object->GetPushCount() == 0) {
                expiredIterators.push_back(run);
            }
        }
        run++;
    }

    // 删除过期的元素
    for (auto it : expiredIterators) {
       m_PushProcessingArea.erase(it);
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


std::multimap<int, std::shared_ptr<card::Card>> App::m_WorldCards = {};
Util::Root App::m_Root;
std::list<std::weak_ptr<card::Card>> App::m_PushProcessingArea = {};
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

    // 如果未找到指定对象，则执行全部查找
    for (auto it = m_WorldCards.begin(); it != m_WorldCards.end(); ++it) {
        if (it->second == specifiedObj) {
            m_WorldCards.erase(it);
            return;
        }
    }
}
