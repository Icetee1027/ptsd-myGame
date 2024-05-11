#include "App.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "Card/CardMaker.hpp"
#include "GiraffeText.hpp"
#include "ShapeHelper.hpp"
#include "Util/Time.hpp"
bool customCompare(const std::multimap<int, std::shared_ptr<card::Card>>::iterator& a,
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

    if (Util::Input::IsKeyUp(Util::Keycode::SPACE)) {
        m_IsPlayButton = m_IsPlayButton == App::PauseOrPlay::Pause ? App::PauseOrPlay::Play : App::PauseOrPlay::Pause;
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
    if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB)) {
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
                        m_SideTitle->SetVisible(0);
                    }
                    else if (it == 2) {
                        m_SideElement[2]->SetVisible(0);
                        m_SideElement[1]->SetVisible(1);
                        m_SideElement[0]->SetVisible(1);
                        m_SideText->SetVisible(1);
                        m_SideTitle->SetVisible(1);

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

    if (Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB)) {
        mouseUp();
        //LOG_DEBUG("Right button up");
    }

    if (Util::Input::IsKeyUp(Util::Keycode::K)) {
        auto a = std::dynamic_pointer_cast<card::Card>(m_Mouse->GetBindObject());
        if (a) {
            a->SetSynthesisTime(3);
        }
       
    }

    if (Util::Input::IsKeyUp(Util::Keycode::F)) {
        //std::shared_ptr<card::Card> sem = card::CardMaker::MakeCard(files[m_WorldCards.size()]);
        std::shared_ptr<card::Card> sem = card::CardMaker::MakeCard("IronBar");
        sem->SetTranslation(glm::vec3(200 * (m_WorldCards.size()-7) + 1, 0, 0));
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
    auto Cardobject = std::dynamic_pointer_cast<card::Card>(m_Mouse->GetBindObject());
    for (const auto& card : cardsToUpdate) {
        if (Cardobject && card->CanHaveCardOnTop(Cardobject)&& m_Mouse->GetBindObject()!=card->GetRoot()) { card->GetChildren()[2]->SetVisible(1);}
        else { card->GetChildren()[2]->SetVisible(0); }
        card->Update();
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
            auto lowerBound = m_WorldCards.lower_bound(target.x - 220);
            auto upperBound = m_WorldCards.upper_bound(target.x + 220);
            float distance = 0;

            for (auto st = lowerBound; st != upperBound; ++st) {
                if (ShapeHelper::IsStackInStack(st->second->GetRoot(), object) && st->second != object->GetLast() && st->second->GetRoot() != m_Mouse->GetBindObject()) {
                    if (st->second->GetPushCount() == 0) {
                        m_PushProcessingArea.push_back(st->second);
                    }
                    glm::vec2  itposition(st->second->GetRoot()->GetTransform().translation.x, st->second->GetRoot()->GetTransform().translation.y);
                    if ((!distance || distance > glm::distance(itposition, target)) && st->second->IsCanPush() >= object->IsCanPush()) { distance = glm::distance(itposition, target); }
                    else continue;
                    glm::vec2 direction = target - itposition;
                    glm::vec2 unitVector = glm::normalize(direction);
                    float proportion = st->second->IsCanPush() == object->IsCanPush()?float(st->second->GetStackSize())/ float(object->GetStackSize() + st->second->GetStackSize()):1;
                    object->SetPushing(unitVector * (0.08f *  proportion), 33);
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
        auto lowerBound = m_WorldCards.lower_bound(target.x - 200);
        auto upperBound = m_WorldCards.upper_bound(target.x + 200);

        std::vector<std::multimap<int, std::shared_ptr<card::Card>>::iterator> stacks;
        for (auto it = lowerBound; it != upperBound; ++it) {
            stacks.push_back(it);
        }
        std::sort(stacks.begin(), stacks.end(), [&target](const auto& a, const auto& b) {
            return customCompare(a, b, target);
            });

        for (auto stack : stacks) {
            if (ShapeHelper::IsCardInStack(stack->second, object) && stack->second != object->GetLast() && stack->second->CanHaveCardOnTop(object)) {
                object->BindParent(stack->second);
                object->m_CanSynthetic = true;//
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
            }
        }
    }
    m_Mouse->ObjectUmBind();
}