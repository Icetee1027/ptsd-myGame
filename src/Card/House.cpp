#include "Card/House.hpp"
#include "Card/BaseVillager.hpp"
#include "Card/Kid.hpp"
namespace card {
    House::House(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor)
        :Card(type, name, id, sfxs, image, iconcolor) {
    }
    bool House::CanHaveCard(std::shared_ptr<Card> otherCard) {
        if (std::dynamic_pointer_cast<BaseVillager>(otherCard) || std::dynamic_pointer_cast<Kid>(otherCard)) {
            return true;
        }

        // 检查 otherCard 的 Id 是否与当前卡片的 Id 相同
        if (otherCard->GetCardName() == m_Name) {
            return true;
        }

        // 调用基类的 CanHaveCard 函数
        return Card::CanHaveCard(otherCard);
    }
    
}