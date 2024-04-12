#ifndef SAWMILL_HPP
#define SAWMILL_HPP
#include "pch.hpp"
#include "Card/Card.hpp"
namespace card {
	class Sawmill :public Card {
	private:
	public:
		Sawmill(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor);
		virtual ~Sawmill() override = default;
		virtual bool CanHaveCard(std::shared_ptr<Card> otherCard) override;
	};
}
#endif