#include "Camera.hpp"
#include "Util/Time.hpp"
//#include "Core/Drawable.hpp"
void Camera::MoveCamera(float x, float y, float z) {
    m_Transform.translation -= glm::vec3(x, y, -z)* float(Util::Time::GetDeltaTime()*240);
    m_Moveable = true;
    LOG_DEBUG("{}", float(Util::Time::GetDeltaTime() * 240));
}
void Camera::Update() {
    Core::Drawable::SetView(m_Transform);
}
