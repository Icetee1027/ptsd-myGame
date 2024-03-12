#ifndef CORPSE_HPP
#define CORPSE_HPP
#include "pch.hpp"
#include "Card/Card.hpp"
namespace card {
	class Corpse :public Card {
	private:
	public:
		Corpse(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image);
		virtual ~Corpse() override = default;
	};
}
#endif