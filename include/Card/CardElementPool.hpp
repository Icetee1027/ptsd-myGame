#ifndef CARDELEMENTPOOL_HPP
#define CARDELEMENTPOOL_HPP

#include <unordered_map>
#include <memory>
#include "Util/Image.hpp"
#include "Util/Text.hpp"
#include "Card/Card.hpp"
#include "Util/color.hpp"

namespace card {
    class CardElementPool {
    private:
        std::unordered_map<std::string, std::pair<std::weak_ptr<Util::Image>, std::weak_ptr<Util::Text>>> elements;
        std::unordered_map<int, std::weak_ptr<Util::Text>> numberTextElements;
        static const std::unordered_map<Type, glm::vec4> NumberColor;

    public:
        std::pair<std::shared_ptr<Util::Image>, std::shared_ptr<Util::Text>> getElement(const std::string& name);


        std::shared_ptr<Util::Text> getNumberTextElement(int number);
    };
}

#endif 
