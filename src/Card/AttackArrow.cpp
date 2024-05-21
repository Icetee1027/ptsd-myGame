#include "Card/Arena.hpp"
#include "Card/CardMaker.hpp"
#include "ShapeHelper.hpp"
#include "Util/Time.hpp"
#include "App.hpp"
#include <random>
namespace card {
	AttackArrow::AttackArrow() {
		m_Drawable = std::make_shared<Util::Image>(RESOURCE_DIR"/sprites/circle.png");
		m_Children.push_back(std::make_shared< AttackText>());
	}
	AttackText::AttackText() {
		m_Drawable = std::make_shared<Util::Text>(RESOURCE_DIR"/fonts/Attack.ttf", 55, " ", Util::Color::FromRGB(255, 157, 0));
		m_Visible = 0;
	}
	void AttackText::display(int value, glm::vec3 lo) {
		if (auto a = std::dynamic_pointer_cast<Util::Text>(m_Drawable)) {
			if (value == 0) {
				a->SetText("miss");
			}
			else {
				a->SetText(std::to_string(-value));
			}
		}
		m_Transform.translation = lo + glm::vec3(130, -30, 0);
		m_Visible = 1;
		m_timeCount = 0;
	}
	void AttackText::Update() {
		if (m_timeCount >= 0.5) {
			m_Visible = 0;
		}
		else {
			m_timeCount += Util::Time::GetDeltaTime();
		}
	}
	// 函数：根据时间百分比插值位置
	glm::vec2 lerp(const glm::vec2& start, const glm::vec2& end, float t) {
		return (1.0f - t) * start + t * end;
	}

	// 函数：根据时间百分比移动圆球
	glm::vec2 moveCircle(const glm::vec2& startPoint, const glm::vec2& endPoint, float timePercentage) {
		if (timePercentage < 0.0f || timePercentage > 1.0f) {
			return endPoint;
		}
		return lerp(startPoint, endPoint, timePercentage);
	}
	void AttackArrow::Update() {
		if (m_CircleTime <= m_timeCount) {
			if (m_Visible != 0) {
				if (auto& a = std::dynamic_pointer_cast<Mob>(m_c2)) {
					if (Attack != 0)a->Shake();
					a->SetAndUpdateHp(a->GetHP() - Attack);
				}
				else if (auto& a = std::dynamic_pointer_cast<BaseVillager>(m_c2)) {
					if (Attack != 0)a->Shake();
					a->SetAndUpdateHp(a->GetHP() - Attack);
				}
				if (auto& t = std::dynamic_pointer_cast<AttackText>(m_Children[0])) {
					t->display(Attack, m_Transform.translation);
				}
			}
			m_Visible = 0;
		}
		else if (App::m_IsPlayButton == App::PauseOrPlay::Play) {
			m_timeCount += Util::Time::GetDeltaTime();
			glm::vec2 startPoint = { m_c1->GetTransform().translation.x,m_c1->GetTransform().translation.y };
			glm::vec2 endPoint = { m_c2->GetTransform().translation.x,m_c2->GetTransform().translation.y };
			m_Transform.translation = { moveCircle(startPoint,endPoint,m_timeCount / m_CircleTime) ,7 };
		}
	}
	void AttackArrow::CircleMove(const std::shared_ptr<Card>& c1, const std::shared_ptr<Card>& c2) {
		m_c1 = c1;
		m_c2 = c2;
		m_timeCount = 0;
		m_Visible = 1;
	}

}