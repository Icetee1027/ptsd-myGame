#ifndef BASEVILLAGER_HPP
#define  BASEVILLAGER_HPP
#include "pch.hpp"
#include "Card/Combatable.hpp"

namespace card {
	class BaseVillager : public Combatable {
	private:
	public:
		static bool VillagerLocation;
		BaseVillager(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const  bool iconcolor);
		virtual ~BaseVillager() override = default;
		virtual bool CanHaveCard(std::shared_ptr<Card> otherCard) override;
		void UpdateCard() override;
	};
}

#endif // !BASEVILLAGER_HPP
