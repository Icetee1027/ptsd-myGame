#ifndef BUILDING_HPP
#define BUILDING_HPP
#include "pch.hpp"
#include "Card/Card.hpp"
namespace card {
	class Building : public Card {
	private:
	public:
		Building(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image);
		virtual ~Building() override = default;
	};
}
#endif // !BUILDING_HPP
