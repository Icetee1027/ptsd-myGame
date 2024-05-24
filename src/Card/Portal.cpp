#include "Card/Portal.hpp"
#include "ShopRandom.hpp"
namespace card{
    Portal::Portal(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor)
        : Card(type, name, id, sfxs, image,iconcolor) {
        m_Moveable = 0;
    }
    bool Portal::CanHaveCard(std::shared_ptr<Card> otherCard) {
        /*if (WorldManager::instance().CurrentRunOptions.IsPeacefulMode) {
            return false;
        }*/

        // 检查卡片是否允许在传送门中
        //if (CardIsAllowedInPortal(otherCard)) {
        //    // 如果允许，在传送门中的卡片是否都满足条件
        //    return otherCard->AllChildrenMatchPredicate([](const std::shared_ptr<CardData>& x) {
        //        return CardIsAllowedInPortal(x);
        //        });
        //}

        // 如果卡片不允许在传送门中，则返回 false
        return false;
    }
    void Portal::SpecialSynthesis() {

     
    }
}