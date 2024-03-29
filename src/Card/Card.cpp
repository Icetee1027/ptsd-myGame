#include "Card/Card.hpp"
#include "Card/Chest.hpp"
#include "Card/Combatable.hpp"
#include "Card/Equipable.hpp"
#include "Card/CardPack.hpp"
#include "App.hpp"
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
            m_Transform.translation = m_Parent->GetTransform().translation + glm::vec3(0, -47, 0);
            m_Parent->Update();
        }
        else {
            if (m_PushCount != 0) {
                m_Transform.translation += glm::vec3(m_PushVector.x * m_PushCount, m_PushVector.y * m_PushCount, 0);
                m_PushCount--;  
            }
        }
    }

    void Card::BindParent(std::shared_ptr<Card> parent) {
        if (m_Parent == nullptr) {
            m_Parent = parent;
            parent->BindChild(shared_from_this());
            StatusStackRootUpDate = true;
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
            StatusStackRootUpDate = true;
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
            m_Child->StackRootUpdate();
        }
    }
    bool Card::CanHaveCardOnTop(std::shared_ptr<Card>  otherCard, bool isPrefab ) {
        std::shared_ptr<Card> rootcard = otherCard->GetRoot();
        int num =GetStackSize();
        if (dynamic_cast<Chest*>(this))
        {
            num = 0;
        }
        int num2 = (isPrefab ? 1 : (otherCard->GetStackSize()));
        if (num + num2 > 5)
        {
            LOG_DEBUG("CanHaveCardOnTop out of size");
            return false;
        }
        if (dynamic_cast<CardPack*>(rootcard.get()) && rootcard->GetChild()!=nullptr )//rootCard.Child.CardData.DetermineCanHaveCardsWhenIsRoot
        {
            return rootcard->GetChild()->CanHaveCard(otherCard);
        }
        /*if (rootCard.CardData.DetermineCanHaveCardsWhenIsRoot)
        {
            return rootCard.CardData.CanHaveCard(otherCard);
        }*/
       /* if (MyGameCard.IsEquipped)
        {
            return false;
        }*/
        if (dynamic_cast<Combatable*>(this))
        {
            bool flag = false;
            if (otherCard->GetCardName() == "bone" && m_Name == "wolf")
            {
                flag = true;
            }
           
            if (!(dynamic_cast<Equipable*>(otherCard.get()) ||dynamic_cast<Combatable*>(otherCard.get()) || flag))
            {
                return false;
            }
        }
        LOG_DEBUG("CanHaveCardOnTop in");
        return CanHaveCard(otherCard);
    }
    bool Card::CanHaveCard(std::shared_ptr<Card>  otherCard) {
        LOG_DEBUG("CanHaveCard:{}", true);
        return true;
    }
    int Card::GetStackSize() {
        auto card = m_Root.lock();
        int count = 0;
        while (card != nullptr) {
            card = card->m_Child;
            count++;
        }
        return count;
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
    
    void Card::SetPushing(glm::vec2 pushvector,unsigned int count) {
        if (m_Parent == nullptr) {
            m_PushVector = pushvector;
            m_PushCount = count;
        }
        else {
            CheckRoot();
            m_Root.lock()->SetPushing(pushvector);
        }
    }
    int Card::GetPushCount() {
        return GetRoot()->m_PushCount;
    }
}
