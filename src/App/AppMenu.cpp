#include "App.hpp"
#include "Util/Input.hpp"
#include "ShapeHelper.hpp"
void App::Menu() {
    for (int it = 1; it != 3; it++) {
        if (ShapeHelper::IsPonstInMenu(m_MenuElement[it], Util::Input::GetCursorPosition())) {
            if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || it == 1 && Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB)) {
                m_Modle = Modle::Playing;
                m_Background = nullptr;
                for (auto t : m_MenuElement) {
                    t->SetVisible(0);
                }
                m_Menu->SetVisible(0);
                //LOG_ERROR("menu element is error111111111111111");
                return;
            }
            else if (it == 2&& Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB)) {
                m_CurrentState = State::END;
                //LOG_ERROR("menu element is error222222222222222");
                return;
            }
            m_MenuElement[it]->SetScale(glm::vec2(1.4, 1.4));
        }
        else {
            m_MenuElement[it]->SetScale(glm::vec2(1, 1));
        }
    
    }
}