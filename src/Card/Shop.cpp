#include "Card/Shop.hpp"
#include "Card/Card.hpp"
#include "Util/GameObject.hpp"

namespace card {
    Shop::Shop(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor)
        :Card(type, name, id, sfxs, image, iconcolor) {
        cost = this->GetPrice();
    }
    
    void Shop::SetCost(std::shared_ptr<card::Card> InputCard){
        if(InputCard->GetCardName() == "Coin"){
            auto price = this->GetPrice();
            this->SetPrice(--price);
        }
    }
}