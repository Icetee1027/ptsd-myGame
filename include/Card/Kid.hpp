#ifndef KID_HPP
#define KID_HPP
#include "pch.hpp"
#include "Card/Card.hpp"
namespace card {
	class Kid :public Card {
	private:
	public:
		Kid(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor);
		virtual ~Kid() override = default;
	};
}
#endif