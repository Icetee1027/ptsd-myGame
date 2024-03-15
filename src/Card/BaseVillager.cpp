#include "Card/BaseVillager.hpp"
namespace card{
    BaseVillager::BaseVillager(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image)
        :Combatable(type, name, id, sfxs, image) {
    }
}