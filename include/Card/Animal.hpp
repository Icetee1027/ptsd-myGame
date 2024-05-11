#ifndef ANIMAL_HPP
#define ANIMAL_HPP
#include "pch.hpp"
#include "Card/Mob.hpp"

namespace card {
	class Animal :public Mob {
	private:
		float m_RawCardsTime= 0;
	public:
		Animal(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor);
		virtual ~Animal() override = default;
        virtual bool CanHaveCard(std::shared_ptr<Card> otherCard) override;
		void Clicking() override;
		void MobCardMoveing() override;
		void UpdateCard() override;
	};
}
#endif // !ANIMAL_HPP
