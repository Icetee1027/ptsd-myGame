#include "Card/Building.hpp"
namespace card {
    Building::Building(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor)
        : Card(type, name, id, sfxs, image, iconcolor) {
    }
    bool Building::CanHaveCard(std::shared_ptr<Card> otherCard) {
        if (otherCard->GetCardName() == m_Name)
        {
            return true;
        }
        return Card::CanHaveCard(otherCard);
    }
}