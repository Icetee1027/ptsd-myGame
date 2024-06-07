#ifndef CHEST_HPP
#define CHEST_HPP
#include "pch.hpp"
#include "Card/Card.hpp"
namespace card {
	class Chest :public Card {
	private:
		std::string m_HeldCardName = "Coin";
		int m_MaxCoinCount = 50;
		bool m_StatusUpdteCard = 0;
	public:
		int m_StaticUpdate = false;
		Chest(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor);
		virtual ~Chest() override = default;
		virtual bool CanHaveCard(std::shared_ptr<Card> otherCard) override;
		std::shared_ptr<Chest> GetChestWithSpace();
		int GetMaxCoinCount() { return m_MaxCoinCount; }
		void SetChestPrice(int price);
		void Update() override;
		void UpdateCard() override;
	};
}
#endif