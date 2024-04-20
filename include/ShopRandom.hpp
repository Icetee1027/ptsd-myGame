#ifndef SHOPRANDOM_HPP
#define SHOPRANDOM_HPP

#include "pch.hpp"
#include "Card/Card.hpp"
#include <map>

struct RandomElement {
    std::string name;
    std::vector<std::vector<std::string>> idea;
    std::vector<std::map<std::string, int>> prizes;

    // 構造函式
    RandomElement(const std::string& title, const std::vector<std::vector<std::string>>& ideas_vec, const std::vector<std::map<std::string, int>>& prizes_vec) : name(title) {
        idea=ideas_vec;
        prizes = prizes_vec;
    }
};

class ShopRandom {
public:
    static std::vector<std::string> DrawCardPack(const std::string& systemName);
private:
    static std::vector<RandomElement> database;
};

#endif // !SHOPRANDOM_HPP
