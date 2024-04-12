#include "Card/Harvestable.hpp"
#include "Card/BaseVillager.hpp"
namespace card {
    Harvestable::Harvestable(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor)
        :Card(type, name, id, sfxs, image, iconcolor) {
    }
    bool Harvestable::CanHaveCard(std::shared_ptr<Card> otherCard) {
       
        if (!std::dynamic_pointer_cast<BaseVillager>(otherCard)) {
         
            return otherCard->GetCardName() == m_Name;
        }

    
        return true;
    }
}