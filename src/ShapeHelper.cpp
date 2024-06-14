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
    int a = 0;
    while (m_Card!=nullptr) {
        auto posistion = m_Card->GetTransform().translation;
        bool IsInX = mouse.x > posistion.x - m_Card->GetScaledSize().x / 2 && mouse.x < posistion.x + m_Card->GetScaledSize().x / 2;
        bool IsInY = (mouse.y > posistion.y - m_Card->GetScaledSize().y /2 )&& (mouse.y < posistion.y + m_Card->GetScaledSize().y / 2);
        if (IsInX && IsInY) return m_Card;
        m_Card = m_Card->GetParent();
        a++;
    }
    return  nullptr;
}
bool ShapeHelper::IsPonstInMenu(const std::shared_ptr< Util::GameObject>& text, const glm::vec2 mouse) {
    bool fx = mouse.x > text->GetTransform().translation.x - text->GetScaledSize().x / 2 && mouse.x < text->GetTransform().translation.x + text->GetScaledSize().x / 2;
    bool fy = mouse.y > text->GetTransform().translation.y - text->GetScaledSize().y / 2 && mouse.y < text->GetTransform().translation.y + text->GetScaledSize().y / 2;
    return fx && fy;
}
bool ShapeHelper::IsCardNearStack(const std::shared_ptr<card::Card>& stack,
    const std::shared_ptr<card::Card>& card) {
    auto pos1 = stack->GetTransform().translation;
    auto size1 = stack->GetScaledSize();
    auto pos2 = card->GetTransform().translation;
    auto size2 = card->GetScaledSize();
    int height1 = stack->GetStackSize();

    // Calculate the bounds of stack1

    float bottom1 = pos1.y - size1.y / 2-600;
    float top1 = pos1.y + size1.y / 2 + (height1 - 1) * 47+600;

    // Calculate the bounds of stack2

    float bottom2 = pos2.y - size2.y / 2;
    float top2 = pos2.y + size2.y / 2;

    // Check if the stacks' positions overlap

    bool isInY = top1 > bottom2 && bottom1 < top2;

    return isInY;
}
bool ShapeHelper::IsCardInStack(const std::shared_ptr<card::Card>& stack,
    const std::shared_ptr<card::Card>& card) {
    auto pos1 = stack->GetTransform().translation;
    auto size1 = stack->GetScaledSize();
    auto pos2 = card->GetTransform().translation;
    auto size2 = card->GetScaledSize();
    int height1 = stack->GetStackSize();

    // Calculate the bounds of stack1
    float left1 = pos1.x - size1.x / 2;
    float right1 = pos1.x + size1.x / 2;
    float bottom1 = pos1.y - size1.y / 2;
    float top1 = pos1.y + size1.y / 2 + (height1 - 1) * 47;

    // Calculate the bounds of stack2
    float left2 = pos2.x - size2.x / 2;
    float right2 = pos2.x + size2.x / 2;
    float bottom2 = pos2.y - size2.y / 2;
    float top2 = pos2.y + size2.y / 2;

    // Check if the stacks' positions overlap
    bool isInX = right1 > left2 && left1 < right2;
    bool isInY = top1 > bottom2 && bottom1 < top2;

    return isInX && isInY;
}
bool ShapeHelper::IsStackInStack(const std::shared_ptr<card::Card>& stack1,
    const std::shared_ptr<card::Card>& stack2) {
    auto pos1 = stack1->GetTransform().translation;
    auto size1 = stack1->GetScaledSize();
    auto pos2 = stack2->GetTransform().translation;
    auto size2 = stack2->GetScaledSize();
    int height1 = stack1->GetStackSize();
    int height2 = stack2->GetStackSize();

    // Calculate the extended bounds
    float extendedMargin = 10.0f;

    // Calculate the bounds of stack1
    float left1 = pos1.x - size1.x / 2 - extendedMargin;
    float right1 = pos1.x + size1.x / 2 + extendedMargin;
    float bottom1 = pos1.y - size1.y / 2 - extendedMargin - (height1 - 1) * 47 + extendedMargin;
    float top1 = pos1.y + size1.y / 2;

    // Calculate the bounds of stack2
    float left2 = pos2.x - size2.x / 2 - extendedMargin;
    float right2 = pos2.x + size2.x / 2 + extendedMargin;
    float bottom2 = pos2.y - size2.y / 2 - extendedMargin - (height2 - 1) * 47 + extendedMargin;
    float top2 = pos2.y + size2.y / 2 ;

    // Check if the stacks' positions overlap
    bool isInX = right1 > left2 && left1 < right2;
    bool isInY = top1 > bottom2 && bottom1 < top2;
 
    return isInX && isInY;
}
bool ShapeHelper::IsCardInCard(const std::shared_ptr<card::Card>& card1, const std::shared_ptr<card::Card>& card2) {
    auto pos1 = card1->GetTransform().translation;
    auto size1 = card1->GetScaledSize();
    auto pos2 = card2->GetTransform().translation;
    auto size2 = card2->GetScaledSize();

    // Calculate the extended bounds
    float extendedMargin = 40.0f;

    // Calculate the bounds of stack1
    float left1 = pos1.x - size1.x / 2 - extendedMargin;
    float right1 = pos1.x + size1.x / 2 + extendedMargin;
    float bottom1 = pos1.y - size1.y / 2 - extendedMargin;
    float top1 = pos1.y + size1.y / 2 + extendedMargin;

    // Calculate the bounds of stack2
    float left2 = pos2.x - size2.x / 2 - extendedMargin;
    float right2 = pos2.x + size2.x / 2 + extendedMargin;
    float bottom2 = pos2.y - size2.y / 2 - extendedMargin;
    float top2 = pos2.y + size2.y / 2  + extendedMargin;

    // Check if the stacks' positions overlap
    bool isInX = right1 > left2 && left1 < right2;
    bool isInY = top1 > bottom2 && bottom1 < top2;

    return isInX && isInY;
}

