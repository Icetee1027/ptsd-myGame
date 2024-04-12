#include "Card/Mob.hpp"
namespace card {
    Mob::Mob(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor)
        : Combatable(type, name, id, sfxs, image, iconcolor) {
        m_Moveable = false;
    }
    bool Mob::CanHaveCard(std::shared_ptr<Card> otherCard) {
        // 检查是否是 "bone" 和 "wolf" 的组合
        if (otherCard->GetCardName() == "bone" && m_Name == "wolf") {
            return true;
        }

        // 检查是否是 "milk" 和 "feral_cat" 的组合
        if (otherCard->GetCardName() == "milk" && m_Name == "feral_cat") {
            return true;
        }

        // 调用 AllCardsInStackMatchPred 函数，传入一个 lambda 表达式作为参数
        //return AllCardsInStackMatchPred(otherCard, [](const CardData& x) {
        //    // Lambda 表达式判断条件
        //    return std::dynamic_pointer_cast<Combatable>(x) && std::dynamic_pointer_cast<Animal>(x);
        //    });
        return false;
    }
}