#include "Card/Card.hpp"

namespace card {
    Card::Card(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image)
        :  m_Name(name), m_Id(id), m_Type(type) {
        m_Drawable = image;
        m_Moveable = true;
        for (const auto& ph : sfxs) {
            m_SFXs.push_back(ph);
        }
        m_Transform.scale = { 0.5, 0.5 };
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
    void Card::Update() {
        for (auto child : m_Children) {
            child->SetTranslation(m_Transform.translation);
            child->SetZIndex(m_ZIndex);
            child->Update();
        }
    }
}
