#ifndef CARDDROP_HPP
#define CARDDROP_HPP
#include "Card/Card.hpp"
#include "pch.hpp"
#include "Util/GameObject.hpp"
namespace card {
	class CardDrop :public Util::GameObject {
	private:
		std::weak_ptr<Card> Card;
	public:
		CardDrop() { m_Moveable = true; m_Transform.rotation = glm::radians(1.0); m_Transform.scale = { 0.48, 0.48 };
		}
		~CardDrop() override = default;
		void SetCard(std::weak_ptr<card::Card> card) { Card = card; }
		void Update() override;

	};
}
#endif // !CARDTITLE_HPP
