#ifndef TREASURECHEST_HPP
#define TREASURECHEST_HPP
#include "pch.hpp"
#include "Card/Card.hpp"
namespace card {
	class TreasureChest :public Card {
	private:
	public:
		TreasureChest(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor);
		virtual ~TreasureChest() override = default;
		virtual bool CanHaveCard(std::shared_ptr<Card> otherCard) override;
	};
}
#endif // !TREASURECHEST_HPP
