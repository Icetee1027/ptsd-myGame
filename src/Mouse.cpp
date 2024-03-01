#include "Mouse.hpp"
#include "Util/Input.hpp"
#include "Util/Image.hpp"
#include "Util/Animation.hpp"
#include "Util/ShapeHelper.hpp"
#include "Camera.hpp"
#include <typeinfo>
void Mouse::Update() {
    m_Distance = Util::Input::GetCursorPosition() - m_LastPosition;
    m_LastPosition = Util::Input::GetCursorPosition();
    m_Transform.translation.x = m_LastPosition.x;
    m_Transform.translation.y = m_LastPosition.y;
    if (m_BindObject != nullptr){ObjectDrag();}
}
void Mouse::Start() {
    std::vector<std::string> images = { RESOURCE_DIR "/sprites/mouse2.png",
                                       RESOURCE_DIR "/sprites/mouse.png"};
    m_Drawable = std::make_shared<Util::Animation>(images,0,0,0,0);
    m_Drawable->SetWorld(Core::Drawable::World::UI);
}
void Mouse::ClickDown() {
    auto animation = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
    animation->SetCurrentFrame(1);
}
void Mouse::ClickUp() {
    auto animation = std::dynamic_pointer_cast<Util::Animation>(m_Drawable);
    animation->SetCurrentFrame(0);
}
void Mouse::ObjectBind(std::shared_ptr<Util::GameObject> Object) {
    m_BindObject = Object;
}
void Mouse::ObjectUmBind() {
    m_BindObject = nullptr;
}
void Mouse::ObjectDrag() {
    if (typeid(*m_BindObject) == typeid(Camera)) {
        m_BindObject->MoveObject(glm::vec3(m_Distance * Util::ShapeHelper::CursorPositionWorldTr(0), 0));
      
    }
    else {

    }
}