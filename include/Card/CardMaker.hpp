#ifndef CARDMAKER_HPP
#define CARDMAKER_HPP

#include "pch.hpp"
#include "card/AllCardPch.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <map> // Adding map library
#include "Util/Logger.hpp"
#include "Card/CardElementPool.hpp"
using json = nlohmann::json;

namespace card {
    class CardMaker {
    public:
        static Type GetJosnToType(int t);

        template<typename T>
        static std::function<std::shared_ptr<Card>(Type, const std::string&, int, const std::vector<std::shared_ptr<Util::SFX>>, const std::shared_ptr<Util::Image>,const bool)>
            createCardFunction();

        static std::shared_ptr<Card> MakeCard(std::string name);

        static std::vector<std::string> GetCardSFX(Type type);
    private:
        static const std::map<int, Type> typeMapping;
        static const std::unordered_map<Type, std::vector<std::string>> cardSFXMap;
    };

} // namespace card

#endif // !CARDMAKER_HPP
