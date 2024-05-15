#ifndef ARENA_HPP
#define ARENA_HPP
#include "pch.hpp"
#include "Card/Card.hpp"
#include "Card/BaseVillager.hpp"
#include "Card/Mob.hpp"
namespace card {
	class Arena :public Card {
	private:
	public:
		Arena(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor);
		std::vector<std::shared_ptr<BaseVillager>> m_BaseVillagers = {};
		std::vector<std::shared_ptr<Mob>> m_Mobs = {};
		virtual ~Arena() override = default;
		virtual bool CanHaveCard(std::shared_ptr<Card> otherCard) override;
		void ArrangementUpdata();
		void Update() override;
	};
}
#endif