#include "Mouse.hpp"
#include "Util/Input.hpp"
#include "Util/Image.hpp"
#include "Util/Animation.hpp"
#include "ShapeHelper.hpp"
#include "Camera.hpp"
#include "Core/Drawable.hpp"
#include "Card/Card.hpp"
#include "App.hpp"
#include <typeinfo>
void Mouse::Start() {
    std::vector<std::string> images = { RESOURCE_DIR "/sprites/mouse2.png",
                                       RESOURCE_DIR "/sprites/mouse.png"};
    m_Drawable = std::make_shared<Util::Animation>(images,0,0,0,0);
    m_Drawable->SetWorld(Core::Drawable::World::UI);
}
void Mouse::Update() {
    m_Offset = Util::Input::GetCursorPosition() - m_LastPosition;
    m_LastPosition = Util::Input::GetCursorPosition();
    m_Transform.translation = glm::vec3(m_LastPosition, 0);
    if (m_BindObject != nullptr){ObjectDrag();}
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
    m_Distance = GetMousePosition(Object) //
        - glm::vec2(Object->GetTransform().translation.x, Object->GetTransform().translation.y);
    m_CardOldX = Object->GetTransform().translation.x;
}
void Mouse::ObjectUmBind() {
    
    m_BindObject = nullptr;
    
}
void Mouse::ObjectDrag() {
    if (std::dynamic_pointer_cast<Camera>(m_BindObject)) {
        m_BindObject->MoveObject(glm::vec3(m_Offset * ShapeHelper::CursorPositionWorldTr(0), 0));
    }
    else if(auto cardObject = std::dynamic_pointer_cast<card::Card>(m_BindObject)){
        m_BindObject->SetTranslation(glm::vec3(GetMousePosition(m_BindObject) - m_Distance, m_BindObject->GetTransform().translation.z));

        if (cardObject->GetTransform().translation.x < -1300) {
            cardObject->SetTranslation(glm::vec3(-1300, cardObject->GetTransform().translation.y, cardObject->GetTransform().translation.z));
        }
        else if (cardObject->GetTransform().translation.x > 1300) {
            cardObject->SetTranslation(glm::vec3(1300, cardObject->GetTransform().translation.y, cardObject->GetTransform().translation.z));
        }
        if (cardObject->GetTransform().translation.y > 625) {
            cardObject->SetTranslation(glm::vec3(cardObject->GetTransform().translation.x, 625, cardObject->GetTransform().translation.z));
        }
        else if (cardObject->GetTransform().translation.y - (cardObject->GetStackSize() - 1) * 47 < -625) {
            cardObject->SetTranslation(glm::vec3(cardObject->GetTransform().translation.x, -625 + (cardObject->GetStackSize() - 1) * 47, cardObject->GetTransform().translation.z));
        }
    }
}
glm::vec2 Mouse::GetMousePosition(const std::shared_ptr<Util::GameObject> &object) {
    glm::vec2 view = { Core::Drawable::GetView().x, Core::Drawable::GetView().y };
    glm::vec2 position = Util::Input::GetCursorPosition() * ShapeHelper::CursorPositionWorldTr(object->GetZIndex() / 50 + object->GetTransform().translation.z);
    return -view + position;
}
glm::vec2 Mouse::GetMousePosition(int a) {
    glm::vec2 view = { Core::Drawable::GetView().x, Core::Drawable::GetView().y };
    glm::vec2 position = Util::Input::GetCursorPosition() * ShapeHelper::CursorPositionWorldTr(a);
    return -view + position;
}
