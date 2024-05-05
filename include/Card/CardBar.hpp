#ifndef CARDBAR_HPP
#define CARDBAR_HPP
#include "Card/Card.hpp"
#include "pch.hpp"
#include "Util/GameObject.hpp"
namespace card {
	class CardBar :public Util::GameObject {
	private:

		std::weak_ptr<Card> Card;
	public:
		CardBar() { m_Moveable = true; m_Transform.rotation = glm::radians(1.0); m_Visible = false; }
		~CardBar() override = default;
		void SetCard(std::weak_ptr<card::Card> card) { Card = card; }
		void Update() override;
	};

	class CardBarBackground :public Util::GameObject {
	private:
		std::weak_ptr<Card> Card;
	public:
		CardBarBackground() { m_Moveable = true; m_Transform.rotation = glm::radians(1.0); m_Visible = false;
		}
		~CardBarBackground() override = default;
		void SetCard(std::weak_ptr<card::Card> card) { Card = card; }
		void Update() override;
	};
}
#endif // !CARDBAR_HPP
