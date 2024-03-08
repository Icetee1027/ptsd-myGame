#ifndef CARDSFX_HPP
#define CARDSFX_HPP
#include "pch.hpp"
#include "Card/CardMaker.hpp"
namespace card {
	std::vector<std::string> GetCardSFX(card::Type type) {
		switch (type)
		{
		case card::Type::Villager:
			return std::vector<std::string>();
		case card::Type::Equiqment:
			return std::vector<std::string>();
		case card::Type::Food:
			return std::vector<std::string>();
		case card::Type::Mob:
			return std::vector<std::string>();
		case card::Type::CardPack:
			return std::vector<std::string>();
		case card::Type::Resource:
			return std::vector<std::string>();
		case card::Type::Structure:
			return std::vector<std::string>();
		case card::Type::Idea:
			return std::vector<std::string>();
		case card::Type::Location:
			return std::vector<std::string>();
		default:
			LOG_ERROR("cardsfx's type is not found");
			return std::vector<std::string>();
		}
	}
}
#endif // !CARDSFX_HPP
