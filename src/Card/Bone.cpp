#include "Card/Bone.hpp"
namespace card {
    Bone::Bone(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image)
        : Resource(type, name, id, sfxs, image) {
    }
}