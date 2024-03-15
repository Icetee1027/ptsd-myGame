#ifndef GRAVEYARD_HPP
#define GRAVEYARD_HPP
#include "pch.hpp"
#include "Card/Harvestable.hpp"
namespace card {
	class Graveyard :public Harvestable {
	private:
	public:
		Graveyard(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image);
		virtual ~Graveyard() override = default;
	};
}
#endif // !GRAVEYARD_HPP
