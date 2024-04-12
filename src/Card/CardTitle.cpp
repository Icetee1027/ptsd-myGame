#include "Card/CardTitle.hpp"
#include <cmath>
namespace card {
	void CardTitle::Update() {
		if (!Card.expired()) {
			m_Transform.translation = Card.lock()->GetTransform().translation + glm::vec3(5, 92.5, 92.5*std::sin(glm::radians(1.0)));
			m_ZIndex += 0.2;
			
		}
	}
}