#include "Card/CardLeftNum.hpp"
namespace card {
	void CardLeftNum::Update() {
		m_Transform.translation += glm::vec3(-57.5, -85, 0);
	m_ZIndex += 0.1;
	}

}