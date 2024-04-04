#include "Card/Garden.hpp"
namespace card {
    Garden::Garden(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor)
        :Card(type, name, id, sfxs, image, iconcolor) {
    }
    bool Garden::CanHaveCard(std::shared_ptr<Card> otherCard) {
        if (otherCard->GetCardType() != Type::Resource && otherCard->GetCardType() != Type::Villager) {
            // 如果不是 Resources 和 Humans 类型，则判断是否是 Food 类型
            return otherCard->GetCardType() == Type::Food;
        }

        // 如果是 Resources 或 Humans 类型，则返回 true
        return true;
    }
}