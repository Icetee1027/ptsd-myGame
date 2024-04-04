#ifndef ALTAR_HPP
#define ALTAR_HPP
#include "pch.hpp"
#include "Card/Card.hpp"

namespace card {
	class Altar :public Card {
	private:
	public:
		Altar(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const  bool iconcolor);
		virtual ~Altar() override = default;
		bool CanHaveCard(std::shared_ptr<Card>  otherCard) override;
	};
}

#endif