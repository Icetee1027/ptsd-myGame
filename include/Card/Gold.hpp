#ifndef GOLD_HPP
#define GOLD_HPP
#include "pch.hpp"
#include "Card/Card.hpp"
namespace card {
	class Gold :public Card {
	private:
	public:
		Gold(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image);
		virtual ~Gold() override = default;
	};
}
#endif