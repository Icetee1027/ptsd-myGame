#ifndef EQUIPABLE_HPP
#define EQUIPABLE_HPP
#include "pch.hpp"
#include "Card/Card.hpp"
namespace card {
	class Equipable :public Card {
	private:
	public:
		Equipable(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image);
		virtual ~Equipable() override = default;
	};
}
#endif