#include "Card/Sawmill.hpp"
namespace card {
    Sawmill::Sawmill(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor)
        :Card(type, name, id, sfxs, image, iconcolor) {
    }
    bool Sawmill::CanHaveCard(std::shared_ptr<Card> otherCard) {
        return otherCard->GetCardName() == "Wood";
    }
}