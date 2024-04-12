#ifndef CARDACK_HPP
#define CARDACK_HPP
#include "pch.hpp"
#include "Card/Card.hpp"
namespace card {
	class CardPack :public Card {
	private:
	public:
		CardPack(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor);
		virtual ~CardPack() override = default;
	};
}
#endif