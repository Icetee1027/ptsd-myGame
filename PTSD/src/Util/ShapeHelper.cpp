#include "Util/ShapeHelper.hpp"
#include "Util/Input.hpp"
#include "Core/Drawable.hpp"
#include "config.hpp"
namespace Util {
float ShapeHelper::CursorPositionWorldTr(const float z) {
    glm::vec2 winMPoint = Util::Input::GetCursorPosition();
    return (z + Core::Drawable::GetView().z) / ( -WINDOW_HEIGHT / 2);
}
} // namespace Util
