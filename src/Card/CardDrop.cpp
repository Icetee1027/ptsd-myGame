#include "Card/CardDrop.hpp"
#include <cmath>
namespace card {
	void CardDrop::Update() {
		if (!Card.expired()) {
			if (Card.lock()->GetTransform().translation.z > 20 && m_Visible == false) {
				m_Visible = true;
			}
			else if (Card.lock()->GetTransform().translation.z < 20 && m_Visible == true) {
				m_Visible = false;
			}
			m_Transform.translation = Card.lock()->GetTransform().translation- glm::vec3(0,27,Card.lock()->GetTransform().translation.z-2);
			m_ZIndex -= 0.2- Card.lock()->GetTransform().translation.z;

		}
	}
}