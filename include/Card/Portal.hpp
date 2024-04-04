#ifndef PORTAL_HPP
#define PORTAL_HPP
#include "pch.hpp"
#include "Card/Card.hpp"
namespace card {
	class Portal :public Card {
	private:
	public:
		Portal(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor);
		virtual ~Portal() override = default;
		virtual bool CanHaveCard(std::shared_ptr<Card> otherCard) override;
	};
}
#endif // !PORTAL_HPP
