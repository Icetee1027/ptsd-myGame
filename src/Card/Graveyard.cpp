#include "Card/Graveyard.hpp"
namespace card {
    Graveyard::Graveyard(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image)
        :Harvestable(type, name, id, sfxs, image) {
    }
}