#include "Card/Card.hpp"

namespace card {
    Card::Card(std::string name, unsigned int id, const std::vector<std::string>& sfx_path, const std::string& cardback)
        : m_Name(name), m_Id(id), m_Drawable(std::make_shared<Util::Image>(cardback)) {

        m_Moveable = true;
        for (const auto& ph : sfx_path) {
            m_SFXs.push_back(std::make_shared<Util::SFX>(ph));
        }
    }

    void Card::ClickDown() {
        if (!m_SFXs.empty()) {
            m_SFXs[0]->Play();
        }
    }

    void Card::ClickUp() {
        if (m_SFXs.size() > 1) {
            m_SFXs[1]->Play();
        }
    }
}
