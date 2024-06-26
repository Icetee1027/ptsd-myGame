#include "Card/AnimalPen.hpp"
#include "Card/Animal.hpp"
namespace card {
    AnimalPen::AnimalPen(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor)
        : Card(type, name, id, sfxs, image, iconcolor) {
		m_MaxAnimalCount = 4;
    }
    bool AnimalPen::CanHaveCard(std::shared_ptr<Card> otherCard){

		if (otherCard->GetCardName() == "Egg")
		{
			return true;
		}
		if (otherCard->GetCardName() == "MagicDust" || otherCard->GetCardName() == "Soil")
		{
			return true;
		}
		int num = GetStackSize()-1 + otherCard->GetStackSize();
		
		if (std::dynamic_pointer_cast<Animal>(otherCard))
		{    

			return num <= m_MaxAnimalCount;
		}
		return false;
    }

}