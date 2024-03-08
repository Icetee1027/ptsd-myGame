#ifndef CARDMAKER_HPP
#define CARDMAKER_HPP
#include "pch.hpp"
#include "Card/Card.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include "Util/Logger.hpp"
#include "Card/Cardsfx.hpp"
using json = nlohmann::json;
namespace card {
	enum class Type{ 
		Villager,
		Equiqment,
		Food,
		Mob,
		CardPack,
		Resource,
		Structure,
		Idea,
		Location
	};
	card::Type GetJosnToType(int t) {
		switch (t)
		{
		case(0):
			return card::Type::Villager;
		case(1):
			return card::Type::Equiqment;
		case(2):
			return card::Type::Food;
		case(3):
			return card::Type::Mob;
		case(4):
			return card::Type::CardPack;
		case(5):
			return card::Type::Resource;
		case(6):
			return card::Type::Structure;
		case(7):
			return card::Type::Idea;
		case(8):
			return card::Type::Location;
		default:
			LOG_ERROR("fill type out of range");
			break;
		}
	}
	std::shared_ptr<Card> MakeCard(std::string name) {
		std::ifstream file(RESOURCE_DIR"josn/cardpack.json");
		json attribute;
		attribute  << file;
		std::vector<std::string> sfxs;
		std::string image = RESOURCE_DIR"audio/sprites/card" + attribute["image"];
		for (auto sfx : card::GetCardSFX(attribute["type"])) {
			sfxs.push_back(RESOURCE_DIR"audio/sfx" + sfx);
		}
		std::shared_ptr<Card> temp = nullptr;
		if (attribute["class"] == "Food") {
			temp = std::make_shared<Food>(attribute["name"], attribute["id"], sfxs, image);
		}
		else if (attribute["class"] == "Altar") {
			temp = std::make_shared<Altar>(attribute["name"], attribute["id"], sfxs, image);
		}
		else if (attribute["class"] == "AnimalPen") {
			temp = std::make_shared<AnimalPen>(attribute["name"], attribute["id"], sfxs, image);
		}
		else if (attribute["class"] == "Blueprint") {
			temp = std::make_shared<Blueprint>(attribute["name"], attribute["id"], sfxs, image);
		}
		else if (attribute["class"] == "Brickyard") {
			temp = std::make_shared<Brickyard>(attribute["name"], attribute["id"], sfxs, image);
		}
		else if (attribute["class"] == "Chest") {
			temp = std::make_shared<Chest>(attribute["name"], attribute["id"], sfxs, image);
		}
		else if (attribute["class"] == "Combatable") {
			temp = std::make_shared<Combatable>(attribute["name"], attribute["id"], sfxs, image);
		}
		else if (attribute["class"] == "Corpse") {
			temp = std::make_shared<Corpse>(attribute["name"], attribute["id"], sfxs, image);
		}
		else if (attribute["class"] == "Garden") {
			temp = std::make_shared<Garden>(attribute["name"], attribute["id"], sfxs, image);
		}
		else if (attribute["class"] == "Gold") {
			temp = std::make_shared<Gold>(attribute["name"], attribute["id"], sfxs, image);
		}
		else if (attribute["class"] == "Greenhouse") {
			temp = std::make_shared<Greenhouse>(attribute["name"], attribute["id"], sfxs, image);
		}
		else if (attribute["class"] == "Harvestable") {
			temp = std::make_shared<Harvestable>(attribute["name"], attribute["id"], sfxs, image);
		}
		else if (attribute["class"] == "House") {
			temp = std::make_shared<House>(attribute["name"], attribute["id"], sfxs, image);
		}
		else if (attribute["class"] == "Kid") {
			temp = std::make_shared<Kid>(attribute["name"], attribute["id"], sfxs, image);
		}
		else if (attribute["class"] == "Market") {
			temp = std::make_shared<Market>(attribute["name"], attribute["id"], sfxs, image);
		}
		else if (attribute["class"] == "Poop") {
			temp = std::make_shared<Poop>(attribute["name"], attribute["id"], sfxs, image);
		}
		else if (attribute["class"] == "Resource") {
			temp = std::make_shared<Resource>(attribute["name"], attribute["id"], sfxs, image);
		}
		else if (attribute["class"] == "Sawmill") {
			temp = std::make_shared<Sawmill>(attribute["name"], attribute["id"], sfxs, image);
		}
		else if (attribute["class"] == "SlaughterHouse") {
			temp = std::make_shared<SlaughterHouse>(attribute["name"], attribute["id"], sfxs, image);
		}
		else if (attribute["class"] == "Smelter") {
			temp = std::make_shared<Smelter>(attribute["name"], attribute["id"], sfxs, image);
		}
		else if (attribute["class"] == "Smelter") {
			temp = std::make_shared<Smelter>(attribute["name"], attribute["id"], sfxs, image);
		}
		else if (attribute["class"] == "TravellingCart") {
			temp = std::make_shared<TravellingCart>(attribute["name"], attribute["id"], sfxs, image);
		}
		else if (attribute["class"] == "Equipable") {
			temp = std::make_shared<Equipable>(attribute["name"], attribute["id"], sfxs, image);
		}
		else if (attribute["class"] == "CardPack") {
			temp = std::make_shared<CardPack>(attribute["name"], attribute["id"], sfxs, image);
		}
		else {
			LOG_ERROR("card class is not found");
		}

		return temp;
	}

}
#endif // !CARDMAKER_HPP
