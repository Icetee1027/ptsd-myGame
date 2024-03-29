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
        Rumors
    };

    class Card : public Util::GameObject, public std::enable_shared_from_this<Card> {
    protected:
        Type m_Type;
        std::string m_Name;
        unsigned int m_Id;
        std::vector<std::shared_ptr<Util::SFX>> m_SFXs;
        unsigned short m_Price = NULL;
        unsigned short m_Satiety = NULL;
        unsigned short m_HP = NULL;

    public:
        Card(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image);
        virtual ~Card() override = default;
        virtual void ClickDown();
        virtual void ClickUp();
        void Update() override;
        void ChildUpdate();
        void SetPrice(const unsigned short price) { m_Price = price; }
        unsigned short GetPrice() { return m_Price; }
        void SetSatiety(const unsigned short satiety){m_Satiety = m_Satiety;}
        unsigned short GetSatiety() { return m_Satiety; }
        void SetHP(const unsigned short hp) { m_HP = hp; }
        unsigned short GetHP() { return m_HP; }
        std::string GetCardName() { return m_Name; }
        unsigned int GetCardId() { return m_Id; }
        
    private:
        std::shared_ptr<Card> m_Child;
        std::shared_ptr<Card> m_Parent;
        std::weak_ptr<Card> m_Root;
        std::shared_ptr<Card> m_last;
        unsigned int m_PushCount = 0;
        glm::vec2 m_PushVector = { 0.0,0.0 };
        bool StatusStackRootUpDate = false;
    public:
        void PositionUpdate();
        void BindParent(std::shared_ptr<Card> parent);
        void BindChild(std::shared_ptr<Card> child);
        void UnBindParent();
        void UnBindChild();
        void SetRoot();
        void CheckRoot();
        void StackRootUpdate();

        bool CanHaveCardOnTop(std::shared_ptr<Card>  otherCard, bool isPrefab =false );
        bool CanHaveCard(std::shared_ptr<Card>  otherCard);
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
