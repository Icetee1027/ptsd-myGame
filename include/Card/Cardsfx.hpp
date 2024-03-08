#ifndef CARDSFX_HPP
#define CARDSFX_HPP
#include "pch.hpp"
#include "Card/CardMaker.hpp"
namespace card {
	std::vector<std::string> GetCardSFX(card::Ttpe type) {
		switch (type)
		{
		case card::Ttpe::Villager:
			return std::vector<std::string>();
		case card::Ttpe::Equiqment:
			return std::vector<std::string>();
		case card::Ttpe::Food:
			return std::vector<std::string>();
		case card::Ttpe::Mob:
			return std::vector<std::string>();
		case card::Ttpe::CardPack:
			return std::vector<std::string>();
		case card::Ttpe::Resource:
			return std::vector<std::string>();
		case card::Ttpe::Structure:
			return std::vector<std::string>();
		case card::Ttpe::Idea:
			return std::vector<std::string>();
		case card::Ttpe::Location:
			return std::vector<std::string>();
		default:
			LOG_ERROR("cardsfx's type is not found";
			return std::vector<std::string>();
		}
	}
}
#endif // !CARDSFX_HPP
