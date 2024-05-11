#ifndef MOB_HPP
#define MOB_HPP
#include "pch.hpp"
#include "Card/Combatable.hpp"
namespace card {
	class Mob : public Combatable {
	protected:
		float m_Time = 3;
		float m_CountTime=0;
	public:
		Mob(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor);
		virtual ~Mob() override = default;
		virtual bool CanHaveCard(std::shared_ptr<Card> otherCard) override;
		virtual void MobCardMoveing();
		virtual void UpdateCard() override;
		glm::vec2 getDirectionToClosestVillager();
	};
}
#endif // !MOB_HPP
