#ifndef CHEST_HPP
#define CHEST_HPP
#include "pch.hpp"
#include "Card/Card.hpp"
namespace card {
	class Chest :public Card {
	private:
	public:
		Chest(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image);
		virtual ~Chest() override = default;
	};
}
#endif