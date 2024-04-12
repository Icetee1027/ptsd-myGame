#include "Card/TreasureChest.hpp"
namespace card {
    TreasureChest::TreasureChest(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor)
        : Card(type, name, id, sfxs, image, iconcolor) {
    }
    bool TreasureChest::CanHaveCard(std::shared_ptr<Card> otherCard) {
        if (otherCard->GetCardName()!= "Key") {
            return otherCard->GetCardName() == "TreasureChest";
        }

        // 如果 otherCard 的 Id 等于 "key"，则返回 true
        return true;
    }
}