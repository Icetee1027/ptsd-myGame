#include "Card/CardRightNum.hpp"
namespace card {
	void CardRightNum::Update() {
		m_Transform.translation += glm::vec3(72.5, -85, 0);
		m_ZIndex += 0.1;
	}
}