#ifndef BASEVILLAGER_HPP
#define  BASEVILLAGER_HPP
#include "pch.hpp"
#include "Card/Combatable.hpp"

namespace card {
	class BaseVillager : public Combatable {
	private:
		std::string m_Weaponry = "";
		long m_doubleclicktime = 0;
	public:
		void SetWeaponry(std::string str) { m_Weaponry = str; };
		static bool VillagerLocation;
		BaseVillager(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const  bool iconcolor);
		virtual ~BaseVillager() override = default;
		virtual bool CanHaveCard(std::shared_ptr<Card> otherCard) override;
		void UpdateCard() override; 
		void SpecialSynthesis() override;
		void Clicking() override;
		void DoubleClick();
	};
}

#endif // !BASEVILLAGER_HPP
