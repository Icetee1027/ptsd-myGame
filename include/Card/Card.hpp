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
        short m_Price = NULL;
        short m_Satiety = NULL;
        short m_HP = NULL;
        bool m_HasPrice = 0;
        bool m_HasSatiety = 0;
        bool m_HasHP = 0;
        int  m_CanPush = 1;
        float m_ClickTime;
        float m_SynthesisTime = 0;
        float m_ProgressTime=0;
    public:
        Card(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image,const bool iconcolor);
        virtual ~Card() override = default;
        virtual void ClickDown();
        virtual void ClickUp();
        virtual void Clicking();

        bool HasPrice() {return m_HasPrice;}
        bool HasSatiety() { return m_HasSatiety; }
        bool HasHP() { return m_HasHP; }
        int IsCanPush() { return m_CanPush; }

        void SetCanPush(bool in) { m_CanPush = in; }
        void SetSatiety(short satiety){m_Satiety = satiety;}
        void SetHP(const unsigned short hp) { m_HP = hp; }
        void SetPrice(const unsigned short price) { m_Price = price; }
        void SetHasPreice(bool in) { m_HasPrice = in; }
        void SetHasSatiety(bool in) { m_HasSatiety = in; }
        void SetHasHP(bool in) { m_HasHP = in; }

        unsigned short GetPrice() { return m_Price; }
        unsigned short GetSatiety() { return m_Satiety; }
        short GetHP() { return m_HP; }
        std::string GetCardName() { return m_Name; }
        Type GetCardType() { return m_Type; }
        unsigned int GetCardId() { return m_Id; }
        void SetSynthesisTime(float time);
        
        
        virtual void Update() override;
        virtual void SynthesisUpdate();
        virtual void SpecialSynthesis(){}
        void ChildUpdate();
    protected:
        std::shared_ptr<Card> m_Child;
        std::shared_ptr<Card> m_Parent;
        std::weak_ptr<Card> m_Root;
        std::shared_ptr<Card> m_last;
        unsigned int m_PushCount = 0;
        glm::vec2 m_PushVector = { 0.0,0.0 };
    public:
        void GenerateCard(std::vector<std::string>& cards);
        void Card::GenerateCard(std::string& cards);
        int m_MaxAnimalCount = 20;
        int m_UsageCount = 1;
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
        bool m_CanSynthetic=false;
        bool m_SyntheticStop = false;
        int m_SyntheticTableid = -1;
        bool m_IsCanPush = true;
        virtual bool CanHaveCard(std::shared_ptr<Card>  otherCard);
        void CancelComposition();
        bool CanHaveCardOnTop(std::shared_ptr<Card>  otherCard, bool isPrefab =false );
        std::vector<std::string> GetCardsName();
        void CanSynthetic();
        virtual void SyntheticDone();
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
