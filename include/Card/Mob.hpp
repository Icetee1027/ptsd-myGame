#ifndef MOB_HPP
#define MOB_HPP
#include "pch.hpp"
#include "Card/Combatable.hpp"
namespace card {
	class Mob : public Combatable {
	private:
	public:
		Mob(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image);
		virtual ~Mob() override = default;
	};
}
#endif // !MOB_HPP
