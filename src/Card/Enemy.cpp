#include "Card/Enemy.hpp"
namespace card {
    Enemy::Enemy(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image)
        : Mob(type, name, id, sfxs, image) {
    }
}