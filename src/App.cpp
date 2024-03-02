#include "App.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

#include "GiraffeText.hpp"

void App::Start() {
   // LOG_TRACE("Start");

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
        m_Mouse->ObjectBind(m_Camera);
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
    m_Camera->Update();
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
    //------------------------------------------------------------------
    m_Mouse->Update();
    m_Root.Update();
}

void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}
