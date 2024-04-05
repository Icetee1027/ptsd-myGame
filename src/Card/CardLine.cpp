#include "Card/CardLine.hpp"
namespace card {
	void CardLine::Update() {
		if (!Card.expired()) {
			m_Transform.translation = Card.lock()->GetTransform().translation - glm::vec3(0, 0,2);
			m_ZIndex += 2;

		}
	}

}