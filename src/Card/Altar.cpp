#include "Card/Altar.hpp"
namespace card {
    Altar::Altar(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image,const  bool iconcolor)
        : Card(type, name, id, sfxs, image, iconcolor) {
    }
    bool Altar::CanHaveCard(std::shared_ptr<Card>  otherCard){
        if (!(otherCard->GetCardName() == "Charcoal") && !(otherCard->GetCardName() == "RawMeat"))
        {
            return otherCard->GetCardName() == "Gold";
        }
        return true;
    }

}