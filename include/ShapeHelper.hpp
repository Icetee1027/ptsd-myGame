#ifndef SHAPEHELPER_HPP
#define SHAPEHELPER_HPP
#include "Core/Drawable.hpp"
#include "Card/Card.hpp"

class ShapeHelper {
public:
    static float CursorPositionWorldTr(const float z);
   /* static bool IsBoxOverlap(const std::shared_ptr<Util::GameObject> object1,
                             const std::shared_ptr<Util::GameObject> object2);
    static bool IsBoxOverlap_x(const std::shared_ptr<Util::GameObject> object1,
                               const std::shared_ptr<Util::GameObject> object2);
    static bool IsBoxOverlap_y(const std::shared_ptr<Util::GameObject> object1,
                               const std::shared_ptr<Util::GameObject> object2);

   
    static bool
    IsPointInSquare_x(const std::shared_ptr<Util::GameObject> object,
                      const glm::vec3 mouse);
    static bool
    IsPointInSquare_y(const std::shared_ptr<Util::GameObject> object,
                      const glm::vec3 mouse);*/
    static std::shared_ptr<card::Card> IsPointInStack(const std::shared_ptr<card::Card> card,
                                const glm::vec2 mouse);

    static bool IsCardInStack(const std::shared_ptr<card::Card> stack,
        const std::shared_ptr<card::Card> card);
    static bool IsStackInStack(const std::shared_ptr<card::Card> stack,
        const std::shared_ptr<card::Card> card);
};


#endif // !SHAPEHELPER_HPP
