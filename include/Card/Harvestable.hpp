#ifndef HARVESTABLE_HPP
#define HARVESTABLE_HPP
#include "pch.hpp"
#include "Card/Card.hpp"
namespace card {
	class Harvestable :public Card {
	private:
	public:
		Harvestable(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor);
		virtual ~Harvestable() override = default;
		virtual bool CanHaveCard(std::shared_ptr<Card> otherCard) override;
	};
}
#endif