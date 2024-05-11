#include "Card/Market.hpp"
#include "Card/CardMaker.hpp"
#include "App.hpp"
namespace card {
    Market::Market(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor)
        :Card(type, name, id, sfxs, image, iconcolor) {
    }
    bool Market::CanHaveCard(std::shared_ptr<Card> otherCard) {
        if (otherCard->HasPrice()) {
            return true;
        }
        // 如果 MyGameCard 不为空，则调用 WorldManager 的 CardCanBeSold 函数
        //return WorldManager::instance().CardCanBeSold(otherCard->MyGameCard);
        return false;
    }
    void Market::CreatCoinStack() {
        std::vector<std::shared_ptr<Card>> cards = {};
        for (int i = 0; i < m_Coin; i++) {
            cards.push_back(card::CardMaker::MakeCard("Coin"));
        }
        for (int i = 1; i < m_Coin; i++) {
            cards[i]->BindParent(cards[i - 1]);
        }
        cards[0]->SetTranslation(m_Transform.translation - glm::vec3(0, 200, 0));
        App::AddCard(cards.back());
    }
    void Market::SyntheticDone() {
        m_SynthesisTime = 0;
        m_SyntheticTableid = -1;
        if (m_Child != nullptr && m_Child->HasPrice()) {
            m_Coin = m_Child->GetPrice() * 2;
            m_Child->RemoveCard();
            CreatCoinStack();
        }
        if (m_Child!=nullptr && m_Child->HasPrice()) {
            SetSynthesisTime(60.0);
        }
    }
}