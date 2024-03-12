#ifndef EGG_HPP
#define EGG_HPP
#include "pch.hpp"
#include "Card/Food.hpp"
namespace card {
	class Egg : public Food {
	private:
	public:
		Egg(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image);

		virtual ~Egg() override = default;
	};
}

#endif // !EGG_HPP
