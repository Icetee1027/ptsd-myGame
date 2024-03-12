#ifndef BRICKYARD_HPP
#define BRICKYARD_HPP
#include "pch.hpp"
#include "Card/Card.hpp"
namespace card {
	class Brickyard :public Card {
	private:
	public:
		Brickyard(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image);
		virtual ~Brickyard() override = default;
	};
}
#endif