#include "Card/CardLeftNum.hpp"
namespace card {
	void CardLeftNum::Update() {
		if (!Card.expired()) {
			m_Transform.translation = Card.lock()->GetTransform().translation + glm::vec3(-57.5, -85, -85 *std::sin(glm::radians(1.0)));
			m_ZIndex += 0.1;
		
		}
	}

}