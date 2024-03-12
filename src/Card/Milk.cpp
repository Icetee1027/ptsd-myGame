#include "Card/Milk.hpp"
namespace card {
	Milk::Milk(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image)
		: Food(type, name, id, sfxs, image) {

	}
}