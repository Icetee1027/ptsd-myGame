#include "Card/Card.hpp"

namespace card {
    Card::Card(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image)
        :  m_Name(name), m_Id(id), m_Type(type) {
        m_Drawable = image;
        m_Moveable = true;
        for (const auto& ph : sfxs) {
            m_SFXs.push_back(ph);
        }
        m_Transform.rotation= glm::radians(1.0);
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
       
        PositionUpdate();
        ChildUpdate();
        
        if (StatusStackRootUpDate) {
            StatusStackRootUpDate = false;
            StackRootUpdate();
        }
    }
    void Card::ChildUpdate() {
        for (auto child : m_Children) {
            child->SetZIndex(m_ZIndex);
            child->Update();
        }
    }
    void Card::PositionUpdate() {
        if (m_Parent != nullptr) {
            m_Transform.translation = m_Parent->GetTransform().translation + glm::vec3(0, 47, 0);
        }
    }

    void Card::BindParent(std::shared_ptr<Card> parent) {
        if (m_Parent == nullptr) {
            m_Parent = parent;
            parent->BindChild(shared_from_this());
            m_Root = parent->GetRoot();
        }
    }

    void Card::BindChild(std::shared_ptr<Card> child) {
        if (m_Child == nullptr) {
            m_Child = child;
            child->BindParent(shared_from_this());
        }
    }
    void Card::UnBindParent() {
        std::shared_ptr<Card> parent=m_Parent;
        if (m_Parent != nullptr) {
            m_Parent = nullptr;
            parent->UnBindChild();
            m_Root = shared_from_this();
        }
    }
    void Card::UnBindChild() {
        std::shared_ptr<Card> child=m_Child;
        if (m_Child != nullptr) {
            m_Child = nullptr;
            child->UnBindParent();
        }
    }
    void Card::SetRoot() {
        if (m_Parent != nullptr) {
            m_Root = m_Parent->GetRoot();
        }
        else {
            m_Root = shared_from_this();
        }
    }

    void Card::StackRootUpdate() {
        SetRoot();
        if (m_Child != nullptr) {
            StackRootUpdate();
        }
    }

    int Card::GetStackSize() {
        if (m_Parent == nullptr || m_Root.expired()) {
            if (m_Child != nullptr) {
                return 1 + m_Child->GetStackSize();
            }
            else {
                return 1;
            }
        }else{
            m_Root.lock()->GetStackSize();
        }
    }
    std::shared_ptr<Card> Card::GetLast() {
        if (m_Child == nullptr) {
            return shared_from_this();
        }
        else {
            return m_Child->GetLast();
        }
    }
    void Card::CheckRoot() {
        if (m_Root.expired()) {
            SetRoot();
        }
    }
}
