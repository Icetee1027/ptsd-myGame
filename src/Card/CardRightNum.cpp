#include "Card/CardRightNum.hpp"
namespace card {
	void CardRightNum::Update() {
		if (!Card.expired()) {
			m_Transform.translation = Card.lock()->GetTransform().translation + glm::vec3(72.5,-85, -85 *std::sin(glm::radians(1.0)));
			m_ZIndex += 0.1;
			
		}
	}
}