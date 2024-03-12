#ifndef COMBATABLE_HPP
#define COMBATABLE_HPP
#include "pch.hpp"
#include "Card/Card.hpp"
namespace card {
	class Combatable :public Card {
	private:
	public:
		Combatable(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image);
		virtual ~Combatable() override = default;
	};
}
#endif