#ifndef BLUEPRINT_HPP
#define BLUEPRINT_HPP
#include "pch.hpp"
#include "Card/Card.hpp"
namespace card {
	class Blueprint :public Card {
	private:
	public:
		Blueprint(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image);
		virtual ~Blueprint() override = default;
	};
}
#endif