#include "Card/SlaughterHouse.hpp"
#include "Card/Animal.hpp"
namespace card {
    SlaughterHouse::SlaughterHouse(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor)
        :Card(type, name, id, sfxs, image, iconcolor) {
    }
    bool SlaughterHouse::CanHaveCard(std::shared_ptr<Card> otherCard) {
        // 计算当前卡片的子卡片数量和 otherCard 的子卡片数量之和
        int num = GetStackSize() -1+ otherCard->GetStackSize();

        // 如果 otherCard 是 Animal 类型，则返回子卡片数量之和是否小于等于 5
        if (std::dynamic_pointer_cast<Animal>(otherCard)) {
            return num <= 5;
        }

        // 如果 otherCard 不是 Animal 类型，则返回 false
        return false;
    }
}