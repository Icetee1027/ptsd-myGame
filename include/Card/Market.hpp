#ifndef MARKET_HPP
#define MARKET_HPP
#include "pch.hpp"
#include "Card/Card.hpp"
namespace card {
	class Market :public Card {
	private:
	public:
		Market(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor);
		virtual ~Market() override = default;
		virtual bool CanHaveCard(std::shared_ptr<Card> otherCard) override;
	};
}
#endif