#include "Card/Animal.hpp"
namespace card {
    Animal::Animal(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const  bool iconcolor)
        : Mob(type, name, id, sfxs, image, iconcolor) {
        m_Moveable = true;
    }
    bool Animal::CanHaveCard(std::shared_ptr<Card> otherCard){
        if (!std::dynamic_pointer_cast<Animal>(otherCard))
        {
            return false;
        }
        return Mob::CanHaveCard(otherCard);
    }
}