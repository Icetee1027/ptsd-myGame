#ifndef MILK_HPP
#define MILK_HPP
#include "pch.hpp"
#include "Card/Food.hpp"
namespace card {
	class Milk : public Food {
	private:
	public:
		Milk(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor);
		virtual ~Milk() override = default;
	};
}
#endif // !MILK_HPP
