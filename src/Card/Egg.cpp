#include "Card/Egg.hpp"
namespace card {
	Egg::Egg(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor)
		: Food(type, name, id, sfxs, image, iconcolor) {
	}
	bool Egg::CanHaveCard(std::shared_ptr<Card> otherCard) {
        if (!otherCard) {
            return false;
        }

      
        // 检查是否为 "chicken" 卡片，并且符合条件
        if (otherCard->GetCardName() == "Chicken" ) {
            return true;
        }

        // 检查是否为 "egg" 卡片，并且符合条件
        if (otherCard->GetCardName() == "Egg" && otherCard->GetParent()->GetCardName() == "Chicken") {
            return false;
        }

        // 调用基类的 CanHaveCard 函数
        return Food::CanHaveCard(otherCard);
	}
}