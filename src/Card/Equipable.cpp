#include "Card/Equipable.hpp"
namespace card {
    Equipable::Equipable(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor)
        :Card(type, name, id, sfxs, image, iconcolor) {
    }
    bool Equipable::CanHaveCard(std::shared_ptr<Card> otherCard) {
        if (!otherCard) {
            return false;
        }

        // 检查 otherCard 的卡片类型是否是 Equipable 或 Humans
        if (otherCard->GetCardType() !=Type::Equipment && otherCard->GetCardType() != Type::Villager) {
            // 如果不是 Equipable 或 Humans 类型，则判断是否是 Resources 类型
            return otherCard->GetCardType() == Type::Resource;
        }

        // 如果是 Equipable 或 Humans 类型，则返回 true
        return true;
    }

}