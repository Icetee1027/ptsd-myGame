#ifndef POOP_HPP
#define POOP_HPP
#include "pch.hpp"
#include "Card/Card.hpp"
namespace card {
	class Poop :public Card {
	private:
	public:
		Poop(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor);
		virtual ~Poop() override = default;
		virtual bool CanHaveCard(std::shared_ptr<Card> otherCard) override;
	};
}
#endif