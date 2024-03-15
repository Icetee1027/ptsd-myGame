#include "Card/Mob.hpp"
namespace card {
    Mob::Mob(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image)
        : Combatable(type, name, id, sfxs, image) {
    }
}