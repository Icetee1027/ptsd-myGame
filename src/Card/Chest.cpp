#include "Card/Chest.hpp"
#include "Card/CardElementPool.hpp"
namespace card {
    Chest::Chest(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor)
        : Card(type, name, id, sfxs, image, iconcolor) {
    }
    bool Chest::CanHaveCard(std::shared_ptr<Card> otherCard) {

		if (otherCard->GetCardName() == m_Name)
		{
			return true;
		}
		if (otherCard->GetCardName() == m_HeldCardName)
		{
			return GetChestWithSpace() != nullptr;
		}
		return false;
    }
    std::shared_ptr<Chest> Chest::GetChestWithSpace() {
        auto allCards = GetAllCardsInStack();

        for (auto& gameCard : allCards) {
            // 檢查是否為 Chest 並且金幣數量還沒達到最大金幣數量
            if (std::shared_ptr<Chest> chest = std::dynamic_pointer_cast<Chest>(gameCard); chest != nullptr && chest->GetPrice() < chest->GetMaxCoinCount()) {
                return chest;  // 返回第一個符合條件的 Chest
            }
        }
        return nullptr;  // 如果沒有符合條件的 Chest，返回 nullptr
    }
    // 覆寫基類的虛函式 UpdateCard
    void Chest::Update() {
        if (m_StaticUpdate == true) {
            m_StaticUpdate = false;
            m_Children.back()->SetDrawable(CardElementPool::getNumberTextElement(m_Price, m_IconColor));
       }
        Card::Update();
    }
    void Chest::UpdateCard(){
        // 將 Value 設置為 CoinCount
        int Value = m_Price;

        // 檢查是否沒有父節點
        if (m_Parent==nullptr) {
            // 取得所有子卡片
            auto childCards = GetAllCardsInStack();

            // 遍歷子卡片
            for (auto& childCard : childCards) {
                // 檢查子卡片的 ID 是否等於 HeldCardId
                if (childCard->GetCardName() == m_HeldCardName) {
                    // 取得一個有空間的箱子
                    auto  chestWithSpace = GetChestWithSpace();

                    // 如果找不到有空間的箱子
                    if (!chestWithSpace) {
                        // 將子卡片從父節點中移除並跳出迴圈
                        childCard->RemoveFromParent();
                        break;
                    }

                    // 如果有空間的箱子的金幣數量小於最大金幣數量
                    if (chestWithSpace->GetPrice() < chestWithSpace->m_MaxCoinCount) {
                        // 摧毀子卡片並將箱子的金幣數量增加一
                        childCard->RemoveCard(); // spawnSmoke = true
                        chestWithSpace->m_Price++;
                        chestWithSpace->m_StaticUpdate = true;
                    }
                }
            }
        }

        Card::UpdateCard();
    }


}