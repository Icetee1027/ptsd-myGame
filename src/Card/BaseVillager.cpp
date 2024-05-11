#include "Card/BaseVillager.hpp"
#include "Card/Food.hpp"
#include "App.hpp"
namespace card{
    BaseVillager::BaseVillager(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor)
        :Combatable(type, name, id, sfxs, image, iconcolor) {
    }
    bool BaseVillager::CanHaveCard(std::shared_ptr<Card> otherCard){
        if (!std::dynamic_pointer_cast<BaseVillager>(otherCard) && otherCard->GetCardType() != Type::Resource && otherCard->GetCardType() != Type::Equipment && !(dynamic_cast<Food*>(otherCard.get())))
        {
            return false;
        }
        return true;
    }
    void BaseVillager::UpdateCard() {
        if(VillagerLocation)
            App::VillagerLocation.push_back(glm::vec2(m_Transform.translation.x, m_Transform.translation.y));
    }
    bool BaseVillager::VillagerLocation = 0;
}