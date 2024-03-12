#ifndef HARVESTABLE_HPP
#define HARVESTABLE_HPP
#include "pch.hpp"
#include "Card/Card.hpp"
namespace card {
	class Harvestable :public Card {
	private:
	public:
		Harvestable(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image);
		virtual ~Harvestable() override = default;
	};
}
#endif