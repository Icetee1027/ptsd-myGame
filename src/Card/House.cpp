#include "Card/House.hpp"
namespace card {
    House::House(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image)
        :Card(type, name, id, sfxs, image) {
    }

}