#ifndef BUILDING_HPP
#define BUILDING_HPP
#include "pch.hpp"
#include "Card/Card.hpp"
#include "SystemSettlementUI.hpp"
namespace card {
	class Building : public Card {
	private:
	public:
		Building(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor);
		virtual ~Building() override = default;
		virtual bool CanHaveCard(std::shared_ptr<Card> otherCard) override;
		void UpdateCard() override {
			if (SystemSettlementUI::IsSystemUpdta) {
				if (m_Name == "shed") {
					SystemSettlementUI::MaxStorageCapacity += 4;

				}
				else if(m_Name=="Warehouse"){
					SystemSettlementUI::MaxStorageCapacity += 14;
				}
				
			}
		}
	}; 
}
#endif // !BUILDING_HPP
