#ifndef CARDACK_HPP
#define CARDACK_HPP
#include "pch.hpp"
#include "Card/Card.hpp"
#include "Camera.hpp"
namespace card {
	class CardPack :public Card {
	private:
		std::vector<std::string> m_Cards;
		
	public:
		CardPack(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image,  const bool iconcolor);
		virtual ~CardPack() override = default;
		void GenerateCard();
		void SetCards(std::vector<std::string> cards) { m_Cards = cards; }
		void Update() override;
		void Clicking() override;
	};
}
#endif