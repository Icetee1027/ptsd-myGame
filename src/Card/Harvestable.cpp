#include "Card/Harvestable.hpp"
#include "Card/BaseVillager.hpp"
namespace card {
    Harvestable::Harvestable(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor)
        :Card(type, name, id, sfxs, image, iconcolor) {
    }
    bool Harvestable::CanHaveCard(std::shared_ptr<Card> otherCard) {
        // 检查 otherCard 是否不是 BaseVillager 类型
        if (!std::dynamic_pointer_cast<BaseVillager>(otherCard)) {
            // 如果不是 BaseVillager 类型，则检查其 Id 是否与当前卡片的 Id 相同
            return otherCard->GetCardName() == m_Name;
        }

        // 如果是 BaseVillager 类型，则返回 true
        return true;
    }
}