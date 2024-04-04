#ifndef GREENHOUSE_HPP
#define GREENHOUSE_HPP
#include "pch.hpp"
#include "Card/Card.hpp"
namespace card {
	class Greenhouse :public Card {
	private:
	public:
		Greenhouse(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor);
		virtual ~Greenhouse() override = default;
		virtual bool CanHaveCard(std::shared_ptr<Card> otherCard) override;
	};
}
#endif