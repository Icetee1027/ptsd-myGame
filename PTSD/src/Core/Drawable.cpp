// Drawable.cpp

#include "Core/Drawable.hpp"
#include "config.hpp"
namespace Core {
glm::vec3 Drawable::m_View = glm::vec3(0, 0, -int(WINDOW_HEIGHT) / 2);


glm::vec3 Drawable::GetView() {
    return m_View;
}
void Drawable::SetView(const Util::Transform &camera) {
    glm::vec3 CAMERA_POSITION = glm::vec3(0, 0, -(int(WINDOW_HEIGHT) / 2));
    m_View = CAMERA_POSITION + camera.translation;
}
}