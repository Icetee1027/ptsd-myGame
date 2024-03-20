#include "App.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "Card/CardMaker.hpp"
#include "GiraffeText.hpp"
#include "Util/ShapeHelper.hpp"


void App::Start() {
   // LOG_TRACE("Start");
   
   
  
    //LOG_ERROR("{},{}",  m_test[0]->GetScaledSize().x, m_test[0]->GetScaledSize().y);
    m_Giraffe->SetDrawable(
        std::make_shared<Util::Image>(RESOURCE_DIR"/sprites/giraffe.png"));
    m_Giraffe->SetZIndex(5);
    m_Giraffe->Start();

    m_GiraffeText->SetZIndex(0);
    m_GiraffeText->Start();

    m_Mouse->Start();
    m_Mouse->SetZIndex(4);

    m_Root.AddChild(m_Giraffe);
    m_Root.AddChild(m_GiraffeText);
    m_Root.AddChild(m_Mouse);
    m_test.push_back(card::CardMaker::MakeCard("LumberCamp"));

    m_CurrentState = State::UPDATE;
}

void App::Update() {
    if (Util::Input::IsKeyUp(Util::Keycode::SPACE)) {
        m_IsPlayButton = m_IsPlayButton== App::PauseOrPlay::Pause? App::PauseOrPlay::Play: App::PauseOrPlay::Pause;
        m_GiraffeText->SetVisible(!m_GiraffeText->GetVisible());
        m_Mouse->ObjectUmBind();
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
        std::vector<std::shared_ptr<card::Card>> cardsInRange;

  
        auto target = m_Mouse->GetMousePosition(0);
        auto lowerBound = m_WorldCards.lower_bound(target.x - 100);

        // 找到 x 坐标大于 targetX + range 的第一个元素的迭代器
        auto upperBound = m_WorldCards.upper_bound(target.x + 100);

        for (auto it = lowerBound; it != upperBound; ++it) {
            
            m_Mouse->ObjectBind(it->second);
            break;
        }
        if (!m_Mouse->HasObjectBind()) {
            m_Mouse->ObjectBind(m_Camera);
        }
        LOG_DEBUG("Right button down");
    }
    if (Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB)) {
        m_Mouse->ClickUp();
        m_Mouse->ObjectUmBind();
        LOG_DEBUG("Right button up");
    }

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

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    if (Util::Input::IsKeyUp(Util::Keycode::F)) {
        std::shared_ptr<card::Card> sem = card::CardMaker::MakeCard(files[m_WorldCards.size()]);
        sem->SetTranslation(glm::vec3(200* m_WorldCards.size()+1, 0, 0));
        AddCard(sem);
    }

    if (Util::Input::IsKeyUp(Util::Keycode::C)) {
        if (!m_WorldCards.empty()) {
    
            auto lastElementIterator = std::prev(m_WorldCards.end());
            // 删除最后一个元素
            m_WorldCards.erase(lastElementIterator);
        }
    }
    //------------------------------------------------------------------

    m_Camera->Update();
    m_Mouse->Update();
    if (!m_test.empty()) {
        m_test.back()->Update();
    }
    for (auto it = m_WorldCards.begin(); it != m_WorldCards.end(); ++it) {
        it->second->Update();
    }
    m_Root.Update();
}

void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
    m_WorldCards.clear();
}

void App::AddCard(std::shared_ptr<card::Card> NewCard) {
    m_WorldCards.emplace(NewCard->GetTransform().translation.x, NewCard);
}


std::multimap<int, std::shared_ptr<card::Card>> App::m_WorldCards = {};
Util::Root App::m_Root;
void App::AddObjectToRoot(std::shared_ptr<Util::GameObject> object) {
    m_Root.AddChild(object);
}
void App::MoveCardToNewX(const std::shared_ptr<card::Card>& specifiedObj, int oldX) {
    int newX = specifiedObj->GetTransform().translation.x;
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
