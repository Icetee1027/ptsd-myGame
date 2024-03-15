#ifndef ANIMAL_HPP
#define ANIMAL_HPP
#include "pch.hpp"
#include "Card/Mob.hpp"

namespace card {
	class Animal :public Mob {
	private:
	public:
		Animal(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image);
		virtual ~Animal() override = default;
	};
}
#endif // !ANIMAL_HPP
