#ifndef MOB_HPP
#define MOB_HPP
#include "pch.hpp"
#include "Card/Combatable.hpp"
#include "Card/BaseVillager.hpp"
namespace card {
	class Mob : public Combatable {
	protected:
		float m_Time = 3;
		float m_CountTime=0;
		std::weak_ptr<Card> WhoToChase;
		float shake_time = 1;
		glm::vec3 OroriginalLocation;
	public:
		void MobDead();
		void SetAndUpdateHp(float hp);
		void ShakeUpdate();
		bool m_StaticUpdate = false;
		bool m_Movestop = false;
		Mob(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor);
		virtual ~Mob() override = default;
		virtual bool CanHaveCard(std::shared_ptr<Card> otherCard) override;
		virtual void MobCardMoveing();
		virtual void UpdateCard() override;
		void ArenaStrat(std::shared_ptr<BaseVillager> villager = nullptr);
		glm::vec2 getDirectionToClosestVillager();
		void Shake() {
			shake_time = 0; 
			OroriginalLocation= m_Transform.translation;
		};
	};
}
#endif // !MOB_HPP
