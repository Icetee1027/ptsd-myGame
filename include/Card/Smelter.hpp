#ifndef SMELTER_HPP
#define SMELTER_HPP

#include "pch.hpp"
#include "Card/Card.hpp"

namespace card {
    class Smelter : public Card {
    private:
    public:
        Smelter(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image);
        virtual ~Smelter() override = default;
    };
}

#endif // SMELTER_HPP
