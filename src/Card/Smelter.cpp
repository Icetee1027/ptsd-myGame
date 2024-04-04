#include "Card/Smelter.hpp"
namespace card {

    Smelter::Smelter(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor)
        :Card(type, name, id, sfxs, image,iconcolor) {
    }
    bool Smelter::CanHaveCard(std::shared_ptr<Card> otherCard) {
        if (otherCard->GetCardName() == "IronOre" ||
            otherCard->GetCardName() == "Wood" ||
            otherCard->GetCardName() == "Sand" ||
            otherCard->GetCardName() == "GoldOre" ||
            otherCard->GetCardName() == "Gold" ||
            otherCard->GetCardName() == "GoldBar" ||
            otherCard->GetCardName() == "Glass") {
            return true;
        }

        // 如果不是以上类型，则调用基类的 CanHaveCard 函数
        return Card::CanHaveCard(otherCard);
    }
}