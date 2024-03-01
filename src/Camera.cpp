#include "Camera.hpp"
//#include "Core/Drawable.hpp"
void Camera::MoveCamera(float x, float y, float z) {
    m_Transform.translation -= glm::vec3(x, y, -z);
}
void Camera::Update() {
    Core::Drawable::SetView(m_Transform);
}
