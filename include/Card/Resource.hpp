#ifndef RESOURCE_HPP
#define RESOURCE_HPP
#include "pch.hpp"
#include "Card/Card.hpp"
namespace card {
	class Resource :public Card {
	private:
	public:
		Resource(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor);
		virtual ~Resource() override = default;
	};
}
#endif