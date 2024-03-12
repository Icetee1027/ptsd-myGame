#ifndef POOP_HPP
#define POOP_HPP
#include "pch.hpp"
#include "Card/Card.hpp"
namespace card {
	class Poop :public Card {
	private:
	public:
		Poop(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image);
		virtual ~Poop() override = default;
	};
}
#endif