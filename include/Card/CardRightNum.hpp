#ifndef CARDRIGHTNUM_HPP
#define CARDRIGHTNUM_HPP
#include "Card/Card.hpp"
#include "pch.hpp"

namespace card {
	class CardRightNum :public Util::GameObject {
	private:
		std::weak_ptr<Card> Card;
	public:
		CardRightNum() { m_Moveable = true; m_Transform.rotation = glm::radians(1.0); }
		~CardRightNum() override = default;
		void SetCard(std::weak_ptr<card::Card> card) { Card = card; }
		void Update() override;
	};
}
#endif // !CARDRIGHTNUM_HPP
