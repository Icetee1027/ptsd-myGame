#include "Util/ShapeHelper.hpp"
#include "Util/Input.hpp"
#include "Core/Drawable.hpp"
namespace Util {
float ShapeHelper::CursorPositionWorldTr(const float z) {
    glm::vec2 winMPoint = Util::Input::GetCursorPosition();
    return  (z + Core::Drawable::GetView().z) / -360;
}
} // namespace Util
