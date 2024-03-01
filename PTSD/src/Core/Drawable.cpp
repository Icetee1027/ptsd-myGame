// Drawable.cpp

#include "Core/Drawable.hpp"

namespace Core {
glm::vec3 Drawable::m_View = CAMERA_POSITION;


glm::vec3 Drawable::GetView() {
    return m_View;
}
void Drawable::SetView(const Util::Transform &camera) {
    m_View = CAMERA_POSITION + camera.translation;
}
}