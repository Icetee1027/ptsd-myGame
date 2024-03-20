#ifndef CARDLEFTNUM_HPP
#define CARDLEFTNUM_HPP
#include "pch.hpp"
#include "Util/GameObject.hpp"
#include "Card/Card.hpp"
namespace card {
	class CardLeftNum : public Util::GameObject {
	private:
		std::weak_ptr<Card> Card;
	public:
		CardLeftNum() { m_Moveable = true; m_Transform.rotation = glm::radians(1.0); }
		~CardLeftNum() override = default;
		void SetCard(std::weak_ptr<card::Card> card) { Card = card; }
		void Update() override;

	};
}

#endif