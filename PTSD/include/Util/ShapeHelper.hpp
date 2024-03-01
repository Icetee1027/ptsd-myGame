#ifndef SHAPEHELPER_HPP
#define SHAPEHELPER_HPP
#include "Core/Drawable.hpp"
namespace Util {
class ShapeHelper {
public:
    static float CursorPositionWorldTr(const float z);
   /* static bool IsBoxOverlap(const std::shared_ptr<Util::GameObject> object1,
                             const std::shared_ptr<Util::GameObject> object2);
    static bool IsBoxOverlap_x(const std::shared_ptr<Util::GameObject> object1,
                               const std::shared_ptr<Util::GameObject> object2);
    static bool IsBoxOverlap_y(const std::shared_ptr<Util::GameObject> object1,
                               const std::shared_ptr<Util::GameObject> object2);

    static bool IsPointInSquare(const std::shared_ptr<Util::GameObject> object,
                                const glm::vec3 mouse);
    static bool
    IsPointInSquare_x(const std::shared_ptr<Util::GameObject> object,
                      const glm::vec3 mouse);
    static bool
    IsPointInSquare_y(const std::shared_ptr<Util::GameObject> object,
                      const glm::vec3 mouse);*/
};
} // namespace Util

#endif // !SHAPEHELPER_HPP
