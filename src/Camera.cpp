#include "Util/Time.hpp"
#include "Camera.hpp"
#include "Core/Drawable.hpp"

Camera::Camera() {
    m_Moveable = true;
    m_Transform.translation = { 0,0,-150 };
}
void Camera::MoveCamera(float x, float y, float z) {
    m_Transform.translation -= glm::vec3(x, y, -z)* float(Util::Time::GetDeltaTime()*240);
}
void Camera::Update() {
    Core::Drawable::SetView(m_Transform);
}
void Camera::ClickDown() {

}
void Camera::ClickUp() {

}
