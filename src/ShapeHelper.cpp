#include "ShapeHelper.hpp"
#include "Util/Input.hpp"
#include "Core/Drawable.hpp"
#include "config.hpp"

float ShapeHelper::CursorPositionWorldTr(const float z) {
    glm::vec2 winMPoint = Util::Input::GetCursorPosition();
    return (z + Core::Drawable::GetView().z) / -(int(WINDOW_HEIGHT) / 2);
}
std::shared_ptr<card::Card> ShapeHelper::IsPointInStack(std::shared_ptr<card::Card> card,
    const glm::vec2 mouse) {
    std::shared_ptr<card::Card> m_Card=card;
    while (m_Card!=nullptr) {
        auto posistion = m_Card->GetTransform().translation;
        bool IsInX = mouse.x > posistion.x - m_Card->GetScaledSize().x / 2 && mouse.x < posistion.x + m_Card->GetScaledSize().x / 2;
        bool IsInY = (mouse.y > posistion.y - m_Card->GetScaledSize().y /2 )&& (mouse.y < posistion.y + m_Card->GetScaledSize().y / 2);
        if (IsInX && IsInY) return m_Card;
        m_Card = m_Card->GetParent();
    }
    return  nullptr;
}
std::shared_ptr<card::Card> ShapeHelper::IsCardInStack(const std::shared_ptr<card::Card> stack,
    const std::shared_ptr<card::Card> card) {
    auto CardPosistion = card->GetTransform().translation;
    auto StackPosistion = stack->GetTransform().translation;
    bool IsInX = StackPosistion.x > CardPosistion.x - card->GetScaledSize().x && StackPosistion.x > CardPosistion.x + card->GetScaledSize().x ;


    return nullptr;
}

