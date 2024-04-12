#ifndef GRAVEYARD_HPP
#define GRAVEYARD_HPP
#include "pch.hpp"
#include "Card/Harvestable.hpp"
namespace card {
	class Graveyard :public Harvestable {
	private:
	public:
		Graveyard(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor);
		virtual ~Graveyard() override = default;
		virtual bool CanHaveCard(std::shared_ptr<Card> otherCard) override;
	};
}
#endif // !GRAVEYARD_HPP
