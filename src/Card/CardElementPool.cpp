#include "Card/CardElementPool.hpp"
namespace card {
    std::pair<std::shared_ptr<Util::Image>, std::shared_ptr<Util::Text>> CardElementPool::getElement(const std::string& name) {
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

                text = std::make_shared<Util::Text>(RESOURCE_DIR"/fonts/BABY-CRIBS.ttf", 35, name, Util::Color::FromRGB(10, 5, 0));
                //LOG_DEBUG("文本更新");
                pair.second = text;
            }

                LOG_DEBUG("{}", name);
            //LOG_DEBUG("圖片指針輸出");
            return std::make_pair(image, text);
        }

        auto newImage = std::make_shared<Util::Image>(RESOURCE_DIR "/sprites/cards/" + name + ".png");
        auto newText = std::make_shared<Util::Text>(RESOURCE_DIR"/fonts/BABY-CRIBS.ttf", 35, name, Util::Color::FromRGB(10, 5, 0));
        elements[name] = std::make_pair(std::weak_ptr<Util::Image>(newImage), std::weak_ptr<Util::Text>(newText));

        //LOG_DEBUG("圖片創新後指針輸出");
        return std::make_pair(newImage, newText);
    }
    std::shared_ptr<Util::Text> CardElementPool::getNumberTextElement(int number) {
        auto it = numberTextElements.find(number);
        if (it != numberTextElements.end()) {
            auto text = it->second.lock();
            if (!text) {
                text = std::make_shared<Util::Text>(RESOURCE_DIR"/fonts/Bangers.ttf", 35, std::to_string(number), Util::Color::FromRGB(255, 255, 255));
                numberTextElements[number] = text;
            }
            return text;
        }

        auto newText = std::make_shared<Util::Text>(RESOURCE_DIR"/fonts/Bangers.ttf", 35, std::to_string(number), Util::Color::FromRGB(255, 255, 255));
        numberTextElements[number] = newText;
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
}
