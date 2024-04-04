#include "Card/Blueprint.hpp"
namespace card {
    Blueprint::Blueprint(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor)
        : Card(type, name, id, sfxs, image, iconcolor) {
    }
    bool Blueprint::CanHaveCard(std::shared_ptr<Card> otherCard) {
        if (!(dynamic_cast<Blueprint*>(otherCard.get())))
        {
            return otherCard->GetCardType() == Type::Rumors;
        }
        return true;
    }

}