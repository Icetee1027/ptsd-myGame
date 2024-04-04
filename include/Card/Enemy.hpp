#ifndef ENEMY_HPP
#define ENEMY_HPP
#include  "pch.hpp"
#include "Card/Mob.hpp"
namespace card {
	class Enemy :public Mob {
	private:
	public:
		Enemy(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor);
		virtual ~Enemy() override = default;
		
	};
}
#endif // !ENEMY_HP
