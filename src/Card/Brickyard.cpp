#include "Card/Brickyard.hpp"
namespace card {
    Brickyard::Brickyard(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor)
        : Card(type, name, id, sfxs, image, iconcolor) {
    }
    bool Brickyard::CanHaveCard(std::shared_ptr<Card> otherCard) {
        if (!(otherCard->GetCardName() == "Stone"))
        {
            return false;
        }
        return true;
    }
}