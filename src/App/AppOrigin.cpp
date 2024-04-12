#include "App.hpp"
#include "Util/Input.hpp"
#include "ShapeHelper.hpp"
void App::Origin() {
    for (int it = 1; it != 3; it++) {
        if (ShapeHelper::IsPonstInMenu(m_MenuElement[it], Util::Input::GetCursorPosition())) {
            if ( it == 1 && Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB)) {
                m_Modle = Modle::Playing;
                m_Background = nullptr;
                
                m_MenuElement[0]->SetText(RESOURCE_DIR"/fonts/Welatte Brush.ttf", 90, "menU!",
                    glm::vec3(0, 0, 0));
                m_MenuElement[0]->SetTranslation(glm::vec3(0, 185, 0));
                m_MenuElement[0]->SetZIndex(1.5);

                m_MenuElement[1]->SetText(RESOURCE_DIR"/fonts/Welatte Brush.ttf", 75, "continue",
                    glm::vec3(0, 0, 0));
                m_MenuElement[1]->SetTranslation(glm::vec3(0, 30, 0));
                m_MenuElement[1]->SetZIndex(1.5);

                for (auto t : m_MenuElement) {
                    t->SetVisible(0);
                }

                m_Menu->SetVisible(0);
                //LOG_ERROR("menu element is error111111111111111");
                return;
            }
            else if (it == 2 && Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB)) {
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
    m_Mouse->Update();
}