#ifndef CARDELEMENTPOOL_HPP
#define CARDELEMENTPOOL_HPP

#include <unordered_map>
#include<map>
#include <memory>
#include <utility>
#include "Util/Image.hpp"
#include "Util/Text.hpp"
#include "Card/Card.hpp"
#include "Util/color.hpp"
#include "Util/Animation.hpp"
namespace std {
    template <>
    struct hash<std::pair<int, int>> {
        size_t operator()(const std::pair<int, int>& p) const {
            size_t h1 = std::hash<int>{}(p.first);
            size_t h2 = std::hash<int>{}(p.second);
            return h1 ^ (h2 << 1);
        }
    };
}
namespace card {
    class CardElementPool {
    private:
        static std::unordered_map<std::string, std::pair<std::weak_ptr<Util::Image>, std::weak_ptr<Util::Text>>> elements;
        static std::unordered_map<std::pair<int, int>, std::weak_ptr<Util::Text>, std::hash<std::pair<int, int>>> numberTextElements;
        static const std::unordered_map<Type, glm::vec4> NumberColor;
        static const std::map<int, Util::Colors> m_Colors;

    public:
        static std::pair<std::shared_ptr<Util::Image>, std::shared_ptr<Util::Text>> getElement(const std::string& name,int color);
        static  std::shared_ptr<Core::Drawable> m_CardDorp; 
        static  std::shared_ptr<Util::Animation> m_CardLine;

        static std::shared_ptr<Util::Text> getNumberTextElement(int number, int color);
    };
}

#endif 
