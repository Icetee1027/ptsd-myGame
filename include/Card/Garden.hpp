#ifndef GARDEN_HPP
#define GARDEN_HPP
#include "pch.hpp"
#include "Card/Card.hpp"
namespace card {
	class Garden :public Card {
	private:
	public:
		Garden(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image);
		virtual ~Garden() override = default;
	};
}
#endif