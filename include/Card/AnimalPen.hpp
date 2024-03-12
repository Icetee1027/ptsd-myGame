#ifndef ANIMALPEN_HPP
#define ANIMALPEN_HPP
#include "pch.hpp"
#include "Card/Card.hpp"
namespace card {
	class AnimalPen :public Card {
	private:
	public:
		AnimalPen(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image);
		virtual ~AnimalPen() override = default;
	};
}
#endif