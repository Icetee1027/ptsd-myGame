#ifndef BASEVILLAGER_HPP
#define  BASEVILLAGER_HPP
#include "pch.hpp"
#include "Card/Combatable.hpp"

namespace card {
	class BaseVillager : public Combatable {
	private:
	public:
		BaseVillager(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image);
		virtual ~BaseVillager() override = default;
	};
}

#endif // !BASEVILLAGER_HPP
