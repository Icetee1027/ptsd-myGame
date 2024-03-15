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

    class Card : public Util::GameObject {
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
        void SetPrice(const unsigned short price) { m_Price = price; }
        unsigned short GetPrice() { return m_Price; }
        void SetSatiety(const unsigned short satiety){m_Satiety = m_Satiety;}
        unsigned short GetSatiety() { return m_Satiety; }
        void SetHP(const unsigned short hp) { m_HP = hp; }
        unsigned short GetHP() { return m_HP; }
        std::string GetCardName() { return m_Name; }
        unsigned int GetCardId() { return m_Id; }
    };
}

#endif // CARD_HPP
