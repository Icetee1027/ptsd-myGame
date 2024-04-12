#include "Card/Card.hpp"
#include "Card/Chest.hpp"
#include "Card/Combatable.hpp"
#include "Card/Equipable.hpp"
#include "Card/CardPack.hpp"
#include "App.hpp"
namespace card {
    Card::Card(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor)
        :  m_Name(name), m_Id(id), m_Type(type) ,m_IconColor(iconcolor){
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
        UpdateCard();
        PositionUpdate();
        if (m_Parent != nullptr) {m_Parent->Update();}
        if (StatusStackRootUpDate) {
            StatusStackRootUpDate = false;
            StackRootUpdate();
        }
        ChildUpdate();


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
        }
        else {
            if (m_PushCount != 0) {
                m_Transform.translation += glm::vec3(m_PushVector.x * m_PushCount, m_PushVector.y * m_PushCount, 0);
                m_PushCount--;
            }

            if (m_Transform.translation.x < -1300&&0) {
                m_Transform.translation.x = -1300;
            }
            else if (m_Transform.translation.x > 1300&&0) {
                m_Transform.translation.x = 1300;
            }
            if (m_Transform.translation.y > 625) {
                m_Transform.translation.y = 625;
            }else if(m_Transform.translation.y - (GetStackSize() - 1) * 47 < -625) {
                m_Transform.translation.y = -625 + (GetStackSize() - 1) * 47;
            }
            
        }
        if (m_Child != nullptr) {
            GetChildren()[2]->SetVisible(m_Child->GetChildren()[2]->GetVisible());
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
        else if(!weak_from_this().expired()){
            m_Root = shared_from_this();
        }
    }
    void Card::RemoveStack() {
       
        if(m_Child!= nullptr) {
            auto Child = m_Child;
            UnBindChild();
            Child->RemoveStack();
        }
        else {
            
            App::RemoveCard(shared_from_this(), m_Transform.translation.x);
        }
        if (m_Parent!=nullptr) {
            auto parent = m_Parent;
            UnBindParent();
            parent->RemoveStack();
        }
      
    }
    void Card::RemoveCard() {
        if (m_Child != nullptr&&m_Parent!=nullptr) {
            auto parent = m_Parent;
            auto child = m_Child;
            this->UnBindParent();
            this->UnBindChild();
            child->BindParent(parent);
        }else if(m_Parent != nullptr&& m_Child == nullptr){
            auto parent = m_Parent;
            this->UnBindParent();
            App::AddCard(parent);
            App::RemoveCard(shared_from_this(), m_Transform.translation.x);
        }
        else if (m_Parent == nullptr && m_Child != nullptr) {
            auto child = m_Child;
            this->UnBindChild();
            child->StatusStackRootUpDate = true;
        }
        else {
            App::RemoveCard(shared_from_this(),m_Transform.translation.x);
        }
    }
    void Card::RemoveFromParent() {
        if (m_Parent != nullptr)
        {
            App::AddCard(m_Parent);
            
            UnBindParent();
        }
    }
    void Card::StackRootUpdate() {
        SetRoot();
        if (m_Child != nullptr) {
            m_Child->StackRootUpdate();
        }
    }
    std::vector<std::shared_ptr<Card>> Card::GetAllCardsInStack() {
        CheckRoot();
        auto root = m_Root.lock();
        std::vector<std::shared_ptr<Card>> stack = {root};
        while (root->GetChild() != nullptr) {
            root = root->GetChild();
            stack.push_back(root);
        }
        return stack;
    }
    bool Card::CanHaveCardOnTop(std::shared_ptr<Card>  otherCard, bool isPrefab ) {
        std::shared_ptr<Card> rootcard = otherCard->GetRoot();
        int num =GetStackSize();
        if (dynamic_cast<Chest*>(this))
        {
            num = 0;
        }
        int num2 = (isPrefab ? 1 : (otherCard->GetStackSize()));
        if (num + num2 > 10)
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
            if (otherCard->GetCardName() == "Bone" && m_Name == "Wolf")
            {
                flag = true;
            }
           
            if (!(dynamic_cast<Equipable*>(otherCard.get()) ||dynamic_cast<Combatable*>(otherCard.get()) || flag))
            {
                return false;
            }
        }
        //LOG_DEBUG("CanHaveCardOnTop in");
        return CanHaveCard(otherCard);
    }
    bool Card::CanHaveCard(std::shared_ptr<Card>  otherCard) {
        //LOG_DEBUG("CanHaveCard:{}", false);
        return false;
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
