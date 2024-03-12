#include "Card/CardTitle.hpp"
namespace card {
	void CardTitle::Update() {
		m_Transform.translation +=  glm::vec3(0, 95, 0);
		m_ZIndex += 0.1;
	}
}