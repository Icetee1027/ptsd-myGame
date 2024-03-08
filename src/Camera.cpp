#include "Util/Time.hpp"
#include "Camera.hpp"
#include "Core/Drawable.hpp"

Camera::Camera() : m_CameraPosition(0.0f, 0.0f, 0.0f) {
    m_Moveable = true;
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
