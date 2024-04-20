#include "Card/Sell.hpp"
#include "Card/Card.hpp"
#include "Util/GameObject.hpp"
#include "Card/CardMaker.hpp"
#include "Card/CardElementPool.hpp"
#include "ShopRandom.hpp"
#include "App.hpp"
#include "Card/Chest.hpp"
namespace card {
    Sell::Sell(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor)
        :Card(type, name, id, sfxs, image, iconcolor) {
        m_Transform.scale = { 0.6,0.6 };
        m_Price = 0;
        m_CanPush = 0;
    }
    bool Sell::CanHaveCard(std::shared_ptr<Card> otherCard) {
        m_dic = otherCard->GetTransform().translation;
        return otherCard->HasPrice() && otherCard->GetCardName() != "TravellingCart" && otherCard->GetCardName() != "Coin"&& (otherCard->GetCardName() != "CoinChest"|| otherCard->GetPrice()==0);
    }

    void Sell::CreatCoinStack() {
        std::vector<std::shared_ptr<Card>> cards = {};
        for (int i = 0; i < m_Price; i++) {
            cards.push_back(card::CardMaker::MakeCard("Coin"));
        }
        for(int i=1;i<m_Price;i++){
            cards[i]->BindParent(cards[i-1]);
        }
        cards[0]->SetTranslation(m_Transform.translation - glm::vec3(0, 200, 0));
        App::AddCard(cards.back());
    }
    void Sell::UpdateCard() {

        auto childCards = GetAllCardsInStack();

        
        if (!childCards.empty()) {
            childCards.erase(childCards.begin());
        }

        for (auto& childCard : childCards) {
            if (childCard->HasPrice() && childCard->GetCardName() != "TravellingCart" && childCard->GetCardName() != "Coin" && (childCard->GetCardName() != "CoinChest" || childCard->GetPrice() == 0)) {
                LOG_ERROR("123");
                if (m_Price+childCard->GetPrice() >10) {
                    continue;
                }
                childCard->RemoveCard();
                m_Price+= childCard->GetPrice();
            }
            
        }
        if (m_Price > 0) {
            CreatCoinStack();
        }
        m_Price = 0;
        if (m_Child != nullptr) { m_Child->SetTranslation(m_dic); m_Child->RemoveFromParent(); LOG_ERROR("321"); }
        Card::UpdateCard();
    }
}