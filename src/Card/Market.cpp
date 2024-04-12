#include "Card/Market.hpp"
namespace card {
    Market::Market(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor)
        :Card(type, name, id, sfxs, image, iconcolor) {
    }
    bool Market::CanHaveCard(std::shared_ptr<Card> otherCard) {

        // 如果 MyGameCard 不为空，则调用 WorldManager 的 CardCanBeSold 函数
        //return WorldManager::instance().CardCanBeSold(otherCard->MyGameCard);
        return false;
    }
}