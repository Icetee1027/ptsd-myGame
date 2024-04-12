#ifndef CARD_HPP
#define CARD_HPP

#include "Util/GameObject.hpp"
#include "Util/SFX.hpp"
#include "Util/Image.hpp"
#include <vector>
#include <string>
#include <memory>


namespace card {

    enum class Type {
        Villager,
        Equipment,
        Food,
        Mob,
        CardPack,
        Resource,
        Structure,
        Idea,
        Location,
        Rumors,
        Shop
    };

    class Card : public Util::GameObject, public std::enable_shared_from_this<Card> {
    protected:
        bool m_IconColor;
        Type m_Type;
        std::string m_Name;
        unsigned int m_Id;
        std::vector<std::shared_ptr<Util::SFX>> m_SFXs;
        unsigned short m_Price = NULL;
        unsigned short m_Satiety = NULL;
        unsigned short m_HP = NULL;
        unsigned short m_CardPackNum = NULL;
        std::vector<std::string> m_FirstIdeaPool;
        std::vector<std::string> m_SecondIdeaPool;
        std::vector<std::string> m_ThirdIdeaPool;
        std::vector<std::string> m_ForthIdeaPool;
        std::vector<std::string> m_FirstCardsPool;
        std::vector<std::string> m_SecondCardsPool;
        std::vector<std::string> m_ThirdCardsPool;
        std::vector<std::string> m_ForthCardsPool;
        std::vector<unsigned short> m_FirstCardsRate;
        std::vector<unsigned short> m_SecondCardsRate;
        std::vector<unsigned short> m_ThirdCardsRate;
        std::vector<unsigned short> m_ForthCardsRate;

    public:
        Card(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image,const bool iconcolor);
        virtual ~Card() override = default;
        virtual void ClickDown();
        virtual void ClickUp();
        void SetPrice(const unsigned short price) { m_Price = price; }
        unsigned short GetPrice() { return m_Price; }
        void SetSatiety(const unsigned short satiety){m_Satiety = m_Satiety;}
        unsigned short GetSatiety() { return m_Satiety; }
        void SetHP(const unsigned short hp) { m_HP = hp; }
        void SetCardPackNum(const unsigned short CardPackNum) { m_CardPackNum = CardPackNum; }
        void SetFirstIdeaPool(const std::vector<std::string>FirstIdeaPool) {m_FirstIdeaPool = FirstIdeaPool;}
        void SetSecondIdeaPool(const std::vector<std::string>SecondIdeaPool) {m_SecondIdeaPool = SecondIdeaPool;}
        void SetThirdIdeaPool(const std::vector<std::string>ThirdIdeaPool) {m_ThirdIdeaPool = ThirdIdeaPool;}
        void SetForthIdeaPool(const std::vector<std::string>ForthIdeaPool) {m_ForthIdeaPool = ForthIdeaPool;}
        void SetFirstCardsPool(const std::vector<std::string>FirstCardsPool) {m_FirstCardsPool = FirstCardsPool;}
        void SetSecondCardsPool(const std::vector<std::string>SecondCardsPool) {m_SecondCardsPool = SecondCardsPool;}
        void SetThirdCardsPool(const std::vector<std::string>ThirdCardsPool) {m_ThirdCardsPool = ThirdCardsPool;}
        void SetForthCardsPool(const std::vector<std::string>ForthCardsPool) {m_ForthCardsPool = ForthCardsPool;}
        void SetFirstCardsRate(const std::vector<unsigned short>FirstCardsRate) {m_FirstCardsRate = FirstCardsRate;}
        void SetSecondCardsRate(const std::vector<unsigned short>SecondCardsRate) {m_SecondCardsRate = SecondCardsRate;}
        void SetThirdCardsRate(const std::vector<unsigned short>ThirdCardsRate) {m_ThirdCardsRate = ThirdCardsRate;}
        void SetForthCardsRate(const std::vector<unsigned short>ForthCardsRate) {m_ForthCardsRate = ForthCardsRate;}
        unsigned short GetHP() { return m_HP; }
        std::string GetCardName() { return m_Name; }
        Type GetCardType() { return m_Type; }
        unsigned int GetCardId() { return m_Id; }
        unsigned short GetCardPackNum() { return m_CardPackNum;}
        std::vector<std::string> GetFirstIdeaPool() {return m_FirstIdeaPool;}
        std::vector<std::string> GetSecondIdeaPool() {return m_SecondIdeaPool;}
        std::vector<std::string> GetThirdIdeaPool() {return m_ThirdIdeaPool;}
        std::vector<std::string> GetForthIdeaPool() {return m_ForthIdeaPool;}
        std::vector<std::string> GetFirstCardsPool() {return m_FirstCardsPool;}
        std::vector<std::string> GetSecondCardsPool() {return m_SecondCardsPool;}
        std::vector<std::string> GetThirdCardsPool() {return m_ThirdCardsPool;}
        std::vector<std::string> GetForthCardsPool() {return m_ForthCardsPool;}
        std::vector<unsigned short> GetFirstCardsRate() {return m_FirstCardsRate;}
        std::vector<unsigned short> GetSecondCardsRate() {return m_SecondCardsRate;}
        std::vector<unsigned short> GetThirdCardsRate() {return m_ThirdCardsRate;}
        std::vector<unsigned short> GetForthCardsRate() {return m_ForthCardsRate;}
        
        virtual void Update() override;
        void ChildUpdate();
    protected:
        std::shared_ptr<Card> m_Child;
        std::shared_ptr<Card> m_Parent;
        std::weak_ptr<Card> m_Root;
        std::shared_ptr<Card> m_last;
        unsigned int m_PushCount = 0;
        glm::vec2 m_PushVector = { 0.0,0.0 };
    public:
        bool StatusStackRootUpDate = false;
        virtual void UpdateCard(){}
        void PositionUpdate();
        void StackRootUpdate();
        void BindParent(std::shared_ptr<Card> parent);
        void BindChild(std::shared_ptr<Card> child);
        void UnBindParent();
        void UnBindChild();
        void SetRoot();
        void CheckRoot();
    public:
        virtual bool CanHaveCard(std::shared_ptr<Card>  otherCard);
        bool CanHaveCardOnTop(std::shared_ptr<Card>  otherCard, bool isPrefab =false );

        std::vector<std::shared_ptr<Card>> GetAllCardsInStack();
        void RemoveStack();
        void RemoveCard();
        void RemoveFromParent();
        int GetStackSize();
        int GetPushCount();
        void SetPushing(glm::vec2 pushvector, unsigned int count=50);

        std::shared_ptr<Card> GetParent() { return m_Parent; }
        std::shared_ptr<Card> GetChild(){ return m_Child; }

        std::shared_ptr<Card> GetLast();
        std::shared_ptr<Card> GetRoot() { CheckRoot(); return m_Root.lock(); }

    };
}
//-----------

#endif // CARD_HPP
