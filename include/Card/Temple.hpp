#ifndef TEMPLE_HPP
#define TEMPLE_HPP
#include "pch.hpp"
#include "Card/Card.hpp"
namespace card {
	class Temple :public Card {
	private:
	public:
		Temple(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor);
		virtual bool CanHaveCard(std::shared_ptr<Card> otherCard) override;
		virtual ~Temple() override = default;
	};
}
#endif // !TEMPLE_HPP
