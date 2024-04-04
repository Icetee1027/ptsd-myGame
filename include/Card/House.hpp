#ifndef HOUSE_HPP
#define HOUSE_HPP
#include "pch.hpp"
#include "Card/Card.hpp"
namespace card {
	class House :public Card {
	private:
	public:
		House(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor);
		virtual ~House() override = default;
		virtual bool CanHaveCard(std::shared_ptr<Card> otherCard) override;
	};
}
#endif