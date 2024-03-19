#include "Card/CardTitle.hpp"
namespace card {
	void CardTitle::Update() {
		m_Transform.translation +=  glm::vec3(5, 92.5, 0);
		m_ZIndex += 0.1;
	}
}