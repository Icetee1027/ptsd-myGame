#ifndef SLAUGHTERHOUSE_HPP
#define SLAUGHTERHOUSE_HPP
#include "pch.hpp"
#include "Card/Card.hpp"
namespace card {
	class SlaughterHouse :public Card {
	private:
	public:
		SlaughterHouse(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image);
		virtual ~SlaughterHouse() override = default;
	};
}
#endif