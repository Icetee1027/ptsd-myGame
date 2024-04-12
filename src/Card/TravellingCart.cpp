#include "Card/TravellingCart.hpp"
namespace card {
    TravellingCart::TravellingCart(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor)
        :Card(type, name, id, sfxs, image, iconcolor) {
    }
    bool TravellingCart::CanHaveCard(std::shared_ptr<Card> otherCard) {
        //// 如果 otherCard 的 MyGameCard 为空，则检查其 Id 是否等于 "gold"
        //if (otherCard == nullptr) {
        //    return otherCard->Id == "Gold";
        //}

        //// 检查 otherCard 是否通过金币购买，或者是否通过金币宝箱购买
        //if (WorldManager::instance().BoughtWithGold(otherCard->MyGameCard, GoldToUse, true) ||
        //    WorldManager::instance().BoughtWithGoldChest(otherCard->MyGameCard, GoldToUse)) {
        //    return true;
        //}

        //// 如果以上条件都不满足，则返回 false
        return false;
    }
}