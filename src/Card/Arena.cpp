#include "Card/Arena.hpp"
#include "Card/CardMaker.hpp"
namespace card {
	Arena::Arena(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor)
		: Card(type, name, id, sfxs, image, iconcolor) {
		m_CanPush = 9;
		m_Moveable = 0;
		
	}
	bool Arena::CanHaveCard(std::shared_ptr<Card> otherCard) {
		return false;
	}
	void Arena::ArrangementUpdata() {
		for (int i = 0; i < 9; i++) {
			m_BaseVillagers.push_back(std::dynamic_pointer_cast<BaseVillager>(card::CardMaker::MakeCard("Dog")));
		}
		int size= std::max(m_BaseVillagers.size(), m_Mobs.size());
		m_Transform.scale = { size*0.7 ,1.3};
		auto VB = GetScaledSize().x / size;
		for (int i = 0; i < m_BaseVillagers.size(); i++) {
			glm::vec3 loc = { m_Transform.translation.x - GetScaledSize().x / 2 + VB * (i + float( size - m_BaseVillagers.size()) / 2) + 130,m_Transform.translation.y + 140, 5 };

			m_BaseVillagers[i]->SetTranslation(loc);
		}
		auto MB = GetScaledSize().x / size;
		for (int i = 0; i < m_Mobs.size(); i++) {
			m_Mobs[i]->SetMoveable(1);
			glm::vec3 loc = { m_Transform.translation.x - GetScaledSize().x / 2 + MB * (i + (float(size - m_Mobs.size()) / 2)) + 130,m_Transform.translation.y - 140, 0};
			m_Mobs[i]->SetTranslation(loc);
		}
	}
	void Arena::Update() {
		Card::Update();
		for (auto& a : m_BaseVillagers) {
			a->ChildUpdate();
		}
		for (auto& a : m_Mobs) {
			a->ChildUpdate();
		}
	}
}