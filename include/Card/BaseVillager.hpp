#ifndef BASEVILLAGER_HPP
#define  BASEVILLAGER_HPP
#include "pch.hpp"
#include "Card/Combatable.hpp"

namespace card {
	class BaseVillager : public Combatable {
	private:
		std::string m_Weaponry = "";
		long m_doubleclicktime = 0;
		float m_time = 1;
		glm::vec3 OroriginalLocation;
	public:
		void VillagerDead();
		void ShakeUpdate();
		void SetAndUpdateHp(float hp);
		bool IsBattle = false;
		bool m_StaticUpdate = false;
		void SetWeaponry(std::string str) { m_Weaponry = str; };
		static bool VillagerLocation;
		BaseVillager(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const  bool iconcolor);
		virtual ~BaseVillager() override = default;
		virtual bool CanHaveCard(std::shared_ptr<Card> otherCard) override;
		void UpdateCard() override; 
		void SpecialSynthesis() override;
		void Clicking() override;
		void DoubleClick();
		void Shake() {
			m_time = 0;
			OroriginalLocation = m_Transform.translation;
		};
	};
}

#endif // !BASEVILLAGER_HPP
