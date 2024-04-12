#include "Card/CardElementPool.hpp"
#include "Card/Card.hpp"
#include <cstddef>
#include <string.h>

namespace card {
    std::pair<std::shared_ptr<Util::Image>, std::shared_ptr<Util::Text>> CardElementPool::getElement(const std::string& name,const int color) {
        auto it = elements.find(name);
        if (it != elements.end()) {

            auto& pair = it->second;
            auto image = pair.first.lock();
            auto text = pair.second.lock();

            if (!image) {

                image = std::make_shared<Util::Image>(RESOURCE_DIR "/sprites/cards/" + name + ".png");

                pair.first = image;
                //LOG_DEBUG("圖片更新");
            }

            if (!text) {

                text = std::make_shared<Util::Text>(RESOURCE_DIR"/fonts/BABY-CRIBS.ttf", 35, name, Util::Color::FromName(m_Colors.at(1)));
                //LOG_DEBUG("文本更新");
                pair.second = text;
            }

                //LOG_DEBUG("{}", name);
            //LOG_DEBUG("圖片指針輸出");
            return std::make_pair(image, text);
        }

        auto newImage = std::make_shared<Util::Image>(RESOURCE_DIR "/sprites/cards/" + name + ".png");
        
        unsigned short textColor;
        if(name == "HumbleBegining") textColor = 0;
        else textColor = 1;
        /*
        if(strchr(name," ")!= NULL){
            name.replace()
        }
        */

        auto newText = std::make_shared<Util::Text>(RESOURCE_DIR"/fonts/BABY-CRIBS.ttf", 32.5, name, Util::Color::FromName(m_Colors.at(textColor)));
        elements[name] = std::make_pair(std::weak_ptr<Util::Image>(newImage), std::weak_ptr<Util::Text>(newText));

        //LOG_DEBUG("圖片創新後指針輸出");
        return std::make_pair(newImage, newText);
    }
    std::shared_ptr<Util::Text> CardElementPool::getNumberTextElement(int number, int color) {
        auto it = numberTextElements.find(std::make_pair(number, color));
        if (it != numberTextElements.end()) {
            auto text = it->second.lock();
            if (!text) {
                text = std::make_shared<Util::Text>(RESOURCE_DIR"/fonts/Bangers.ttf", 32.5, std::to_string(number), Util::Color::FromName(m_Colors.at(color)));
                numberTextElements[std::make_pair(number, color)] = text;
            }
            return text;
        }

        auto newText = std::make_shared<Util::Text>(RESOURCE_DIR"/fonts/Bangers.ttf", 32.5, std::to_string(number), Util::Color::FromName(m_Colors.at(color)));
        numberTextElements[std::make_pair(number, color)] = newText;
        return newText;
    }
    const std::unordered_map<Type, glm::vec4> CardElementPool::NumberColor = {
        {Type::Villager, {}},
        {Type::Equipment, {}},
        {Type::Food, {}},
        {Type::Mob, {}},
        {Type::CardPack, {}},
        {Type::Resource, {}},
        {Type::Structure, {}},
        {Type::Idea, {}},
        {Type::Location, {}}
    };
    const std::map<int, Util::Colors> CardElementPool::m_Colors = {
        {0, Util::Colors::WHITE},
        {1, Util::Colors::BLACK}
    };
    std::unordered_map<std::string, std::pair<std::weak_ptr<Util::Image>, std::weak_ptr<Util::Text>>> CardElementPool::elements = {};

    std::unordered_map<std::pair<int, int>, std::weak_ptr<Util::Text>, std::hash<std::pair<int, int>>> CardElementPool::numberTextElements = {};
    std::shared_ptr<Core::Drawable> CardElementPool::m_CardDorp =nullptr;
    std::shared_ptr<Util::Animation> CardElementPool::m_CardLine = nullptr;
}
