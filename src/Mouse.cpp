#include "Mouse.hpp"
#include "Util/Input.hpp"
#include "Util/Image.hpp"
#include "Util/Animation.hpp"
void Mouse::Update() {
    glm::vec2 winMPoint = Util::Input::GetCursorPosition();
    m_Transform.translation.x = winMPoint.x;
    m_Transform.translation.y = winMPoint.y;
}
void Mouse::Start() {
    std::vector<std::string> images = {"../assets/sprites/mouse2.png",
                                       "../assets/sprites/mouse.png"};
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
void Mouse::ObjectBind(std::shared_ptr<Util::GameObject> &Object) {
    m_BindObject = Object;

}
void Mouse::ObjectUmBind() {

}
