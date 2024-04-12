#include "Card/Food.hpp"
#include "Card/BaseVillager.hpp"
namespace card {
    Food::Food(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor)
        :Card(type, name, id, sfxs, image, iconcolor) {
    }
    bool Food::CanHaveCard(std::shared_ptr<Card> otherCard) {
        if (!otherCard) {
            return false;
        }

        // 检查 otherCard 是否不是 Food 类型并且不是 Resources 类型
        if (!(std::dynamic_pointer_cast<Food>(otherCard)) && otherCard->GetCardType() != Type::Resource) {
            // 如果 otherCard 是 BaseVillager 类型，则根据 CanBePlacedOnVillager 返回结果
            if (std::dynamic_pointer_cast<BaseVillager>(otherCard)) {
                return true;
            }
            // 否则返回 false
            return false;
        }

        // 如果 otherCard 是 Food 类型或者是 Resources 类型，则返回 true
        return true;
    }
}