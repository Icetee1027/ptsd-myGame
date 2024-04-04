#include "Card/Gold.hpp"
namespace card {
    Gold::Gold(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor)
        :Card(type, name, id, sfxs, image, iconcolor) {
    }
    bool Gold::CanHaveCard(std::shared_ptr<Card> otherCard) {
        // 检查 otherCard 的卡片类型是否不是 Resources
        if (otherCard->GetCardType() != Type::Resource) {
            // 如果不是 Resources 类型，则判断是否是 Humans 类型
            return otherCard->GetCardType() == Type::Villager;
        }

        // 如果是 Resources 类型，则返回 true
        return true;
    }

}