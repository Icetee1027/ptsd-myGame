#include "Card/Greenhouse.hpp"
namespace card {
    Greenhouse::Greenhouse(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor)
        :Card(type, name, id, sfxs, image, iconcolor) {
    }
    bool Greenhouse::CanHaveCard(std::shared_ptr<Card> otherCard) {
        if (otherCard->GetCardType() != Type::Resource && otherCard->GetCardType() != Type::Villager)
        {
            return otherCard->GetCardType() == Type::Food;
        }
        return true;
    }
}