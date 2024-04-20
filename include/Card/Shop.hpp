#ifndef SHOP_HPP
#define SHOP_HPP
#include "Card/Resource.hpp"
#include "pch.hpp"
#include "Card/Card.hpp"
#include <memory>
namespace card {
	class Shop :public Card {
	private:
		int m_BasicPrice;
		glm::vec3 m_dic;
		bool m_StatusUpdteCard = 1;
	public:
		bool m_StaticUpdate = false;
		Shop(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor);
		virtual ~Shop() override = default;
		void CreatCardPack();
		void Update() override;
		virtual bool CanHaveCard(std::shared_ptr<Card> otherCard) override;
		void UpdateCard() override;
	};
}
#endif