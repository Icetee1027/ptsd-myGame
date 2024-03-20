#ifndef CARDTITLE_HPP
#define CARDTITLE_HPP
#include "Card/Card.hpp"
#include "pch.hpp"
#include "Util/GameObject.hpp"
namespace card {
	class CardTitle :public Util::GameObject {
	private:
		std::weak_ptr<Card> Card;
	public:
		CardTitle() { m_Moveable = true; m_Transform.rotation=glm::radians(1.0); }
		~CardTitle() override = default;
		void SetCard(std::weak_ptr<card::Card> card) { Card = card; }
		void Update() override;

	};
}
#endif // !CARDTITLE_HPP
