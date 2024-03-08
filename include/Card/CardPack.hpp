#ifndef CARDPACK_HPP
#define CARDPACK_HPP

#include "pch.hpp"
#include "Card/Card.hpp"

namespace card {
    class CardPack : public card::Card {
    private:
        std::vector<std::string> m_Cards;
    public:
        CardPack(std::string name, unsigned int id, const std::vector<std::string>& sfx_path, const std::string& cardback, std::vector<std::string> cards);
        ~CardPack() override = default;


    };
}
#endif // !CARDPACK_HPP
