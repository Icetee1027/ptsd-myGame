#include "Card/Graveyard.hpp"
namespace card {
    Graveyard::Graveyard(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor)
        :Harvestable(type, name, id, sfxs, image, iconcolor) {
    }
    bool Graveyard::CanHaveCard(std::shared_ptr<Card> otherCard) {
        if (otherCard->GetCardName() == "Corpse")
        {
            return true;
        }
        return Harvestable::CanHaveCard(otherCard);
    }
}