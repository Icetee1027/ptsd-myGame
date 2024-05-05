#include "Card/CardBar.hpp"
namespace card {
	void CardBar::Update() {
		if (!Card.expired()) {
			m_Transform.translation = Card.lock()->GetTransform().translation + glm::vec3(0, 132, 150* std::sin(glm::radians(1.0)));
			m_ZIndex += 0.2;

		}
	}
	void CardBarBackground::Update() {
		if (!Card.expired()) {
			m_Transform.translation = Card.lock()->GetTransform().translation + glm::vec3(0, 132, 140 * std::sin(glm::radians(1.0)));
			m_ZIndex += 0.2;

		}
	}
}