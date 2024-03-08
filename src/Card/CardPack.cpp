#include "Card/CardPack.hpp"
namespace card {
	CardPack::CardPack(std::string name, unsigned int id, const std::vector<std::string>& sfx_path, const std::string& cardback, std::vector<std::string> cards)
	: card::Card(name, id, sfx_path, cardback), m_Cards(cards) {
	}
}