#ifndef SHOP_HPP
#define SHOP_HPP
#include "Card/Resource.hpp"
#include "pch.hpp"
#include "Card/Card.hpp"
#include <memory>
namespace card {
	class Shop :public Card {
	private:
		unsigned short cost;
	public:
		Shop(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor);
		virtual ~Shop() override = default;
		void SetCost(std::shared_ptr<card::Card> InputCard);
	};
}
#endif