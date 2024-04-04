#include "Card/Poop.hpp"
namespace card {
    Poop::Poop(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor)
        :Card(type, name, id, sfxs, image, iconcolor) {
    }
    bool Poop::CanHaveCard(std::shared_ptr<Card> otherCard) {
        // 检查 otherCard 的卡片类型是否不是 Resources、Humans、Food，并且不是当前卡片
        if (otherCard->GetCardType() != Type::Resource &&
            otherCard->GetCardType() != Type::Villager &&
            otherCard->GetCardType() != Type::Food &&
            !(otherCard->GetCardName() == m_Name)) {
            // 如果是 Structures 类型，则检查其是否不是建筑
            if (otherCard->GetCardType() == Type::Structure) {
                return true;
            }
            // 其他情况返回 false
            return false;
        }

        // 如果是 Resources、Humans、Food 类型之一，或者是当前卡片，则返回 true
        return true;
    }
}