#include "Card/Resource.hpp"
#include "Card/Building.hpp"
namespace card {
    Resource::Resource(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor)
        :Card(type, name, id, sfxs, image, iconcolor) {
    }
    bool Resource::CanHaveCard(std::shared_ptr<Card> otherCard) {
		if (otherCard->GetCardType() != Type::Equipment && otherCard->GetCardType() != Type::Resource && otherCard->GetCardType() != Type::Villager && otherCard->GetCardType() != Type::Food && !(otherCard->GetCardName() == m_Name))
		{

			if (otherCard->GetCardType() != Type::Structure&& otherCard->GetCardType() != Type::CardPack && otherCard->GetCardType()!= Type::Mob)
			{
				return !std::dynamic_pointer_cast<Building>(otherCard);
			}
			return false;
		}
		return true;
    }
}