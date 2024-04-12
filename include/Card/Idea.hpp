#ifndef IDEA_HPP
#define IDEA_HPP
#include "pch.hpp"
#include "Card/Card.hpp"
namespace card {
	class Idea :public Card {
	private:
	public:
		Idea(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image,  const bool iconcolor);
		virtual ~Idea() override = default;
	};
}
#endif