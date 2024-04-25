#include "Card/Shop.hpp"
#include "Card/Card.hpp"
#include "Util/GameObject.hpp"
#include "Card/CardMaker.hpp"
#include "Card/CardElementPool.hpp"
#include "ShopRandom.hpp"
#include "App.hpp"
#include "Card/Chest.hpp"
namespace card {
    Shop::Shop(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor)
        :Card(type, name, id, sfxs, image, iconcolor) {
        if (name == "HumbleBegining")
            m_BasicPrice = 3;
        else if (name == "SeekingWisdom")
            m_BasicPrice = 4;
        else if (name == "ReapAndSow")
            m_BasicPrice = 10;
        else if (name == "CuriousCuisine")
            m_BasicPrice = 10;
        else if (name == "LogicandReason")
            m_BasicPrice = 15;
        else if (name == "TheArmory")
            m_BasicPrice = 15;
        else if (name == "Explorers")
            m_BasicPrice = 20;
        else if (name == "OrderandStructure") {
            m_BasicPrice = 25;
        }
        m_Transform.scale = { 0.6,0.6 };
        m_CanPush = 10;
    }
    bool Shop::CanHaveCard(std::shared_ptr<Card> otherCard) {
        m_dic = otherCard->GetTransform().translation;
        m_StatusUpdteCard = otherCard->GetCardName() == "Coin" || otherCard->GetCardName() == "CoinChest"?1:0;
        return otherCard->GetCardName() == "Coin" || otherCard->GetCardName() == "CoinChest";
    }
    void Shop::Update() {
        if (m_StaticUpdate == true) {
            m_StaticUpdate = false;
            m_Children.back()->SetDrawable(CardElementPool::getNumberTextElement(m_Price, m_IconColor));
        }
        Card::Update();
    }
    void Shop::CreatCardPack() {
        std::shared_ptr<Card> card = CardMaker::MakeCard("Pack");
        auto pack = std::dynamic_pointer_cast<CardPack>(card);
        pack->SetCards(ShopRandom::DrawCardPack(m_Name));
        card->SetTranslation(m_Transform.translation - glm::vec3(0, 200,0));
        App::AddCard(card);

    }
    void Shop::UpdateCard() {
        if (!m_StatusUpdteCard) {
            Card::UpdateCard();
            return;
        }

        m_StatusUpdteCard = 0;

        // 取得所有子卡片
        auto childCards = GetAllCardsInStack();
        if (!childCards.empty()) {
            childCards.erase(childCards.begin());
        }

        // 遍歷子卡片
        for (auto& childCard : childCards) {
            
            if (m_Price != 0 && childCard->GetCardName() == "Coin") {
                // 摧毀子卡片並將箱子的金幣數量增加一
                childCard->RemoveCard();
                m_Price--;
                m_StaticUpdate = true;

            }
            if (m_Price == 0 && childCard->GetCardName() == "Coin") {
                m_Price = m_BasicPrice;
                m_StaticUpdate = true;
                //LOG_DEBUG("{}:{}", m_Price, m_BasicPrice);
                if (childCard->GetChild() == nullptr) {
                    childCard->RemoveCard();
                }
                else {
                    m_Child->RemoveFromParent();
                }
                CreatCardPack();
                break;
            }
            
            if (childCard->GetCardName() == "CoinChest") {
                //LOG_DEBUG("{}:{}", m_Price, m_BasicPrice);
                bool status = 1;
                auto chest = std::dynamic_pointer_cast<Chest>(childCard);
                while (chest->GetPrice() != 0) {
                    if (m_Price != 0) {
                        // 摧毀子卡片並將箱子的金幣數量增加一
                        chest->SetChestPrice(chest->GetPrice() - 1);
                        m_Price--;
                        m_StaticUpdate = true;
                    }
                    if (m_Price == 0) {
                        m_Price = m_BasicPrice;
                        m_StaticUpdate = true;
                        status = 0;
                        CreatCardPack();
                        break;
                    }
                }
                if (status == 0)
                    break;
                
            }
        }
        
        if (m_Child != nullptr) { m_Child->SetTranslation(m_dic); m_Child->RemoveFromParent(); }
        Card::UpdateCard();
    }
}