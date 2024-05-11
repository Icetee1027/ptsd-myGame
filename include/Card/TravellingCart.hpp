#ifndef TRAVELINGCART_HPP
#define TRAVELINGCART_HPP
#include "pch.hpp"
#include "Card/Card.hpp"
namespace card {
	class TravellingCart :public Card {
	private:
		int m_BasicPrice;
		glm::vec3 m_dic;
		bool m_StatusUpdteCard = 1;
		int count = 0;
	public:
		bool m_StaticUpdate = false;
		TravellingCart(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor);
		virtual ~TravellingCart() override = default;
		void CreatCardPack();
		void Update() override;
		virtual bool CanHaveCard(std::shared_ptr<Card> otherCard) override;
		void UpdateCard() override;
	};
}
#endif