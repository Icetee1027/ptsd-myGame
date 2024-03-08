#ifndef CARD_HPP
#define CARD_HPP

#include "Util/GameObject.hpp"
#include "Util/SFX.hpp"
#include "Util/Image.hpp"
#include <vector>
#include <string>
#include <memory>

namespace card {
    class Card : public Util::GameObject {
    protected:
        std::string m_Name;
        unsigned int m_Id;
        std::shared_ptr<Util::Image> m_Drawable;
        std::vector<std::shared_ptr<Util::SFX>> m_SFXs;
        unsigned short m_Price;
        unsigned short m_Satiety;
        unsigned short  m_HP;
    public:
        Card(std::string name, unsigned int id, const std::vector<std::string>& sfx_path, const std::string& cardback);
        virtual ~Card() override = default;
        virtual void ClickDown();
        virtual void ClickUp();
        std::string GetCardName() { return m_Name; }
        unsigned int GetCardId() { return m_Id; }
    };
}

#endif // !CARD_HPP
