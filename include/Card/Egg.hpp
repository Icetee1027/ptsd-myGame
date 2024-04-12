#ifndef EGG_HPP
#define EGG_HPP
#include "pch.hpp"
#include "Card/Food.hpp"
namespace card {
	class Egg : public Food {
	private:
	public:
		Egg(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor);
		virtual ~Egg() override = default;
		virtual bool CanHaveCard(std::shared_ptr<Card> otherCard) override;
	};
}

#endif // !EGG_HPP
