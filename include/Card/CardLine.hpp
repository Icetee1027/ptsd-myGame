#ifndef CARDLINE_HPP
#define CARDLINE_HPP
#include "pch.hpp"
#include "Util/GameObject.hpp"
#include "Card/Card.hpp"
namespace card {
	class CardLine : public Util::GameObject {
	private:
		std::weak_ptr<Card> Card;
	public:
		CardLine() { m_Moveable = true; m_Transform.rotation = glm::radians(1.0); m_Transform.scale = { 0.6, 0.6 }; }
		~CardLine() override = default;
		void SetCard(std::weak_ptr<card::Card> card) { Card = card; }
		void Update() override;

	};
}

#endif