#include "Card/Corpse.hpp"
namespace card {
    Corpse::Corpse(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor)
        : Card(type, name, id, sfxs, image, iconcolor) {
    }
	bool Corpse::CanHaveCard(std::shared_ptr<Card>  otherCard) {
		std::shared_ptr<Corpse> corpsePtr = std::dynamic_pointer_cast<Corpse>(otherCard);
		return (corpsePtr != nullptr);
	}

}