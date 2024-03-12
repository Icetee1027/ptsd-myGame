#ifndef TRAVELINGCART_HPP
#define TRAVELINGCART_HPP
#include "pch.hpp"
#include "Card/Card.hpp"
namespace card {
	class TravellingCart :public Card {
	private:
	public:
		TravellingCart(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image);
		virtual ~TravellingCart() override = default;
	};
}
#endif