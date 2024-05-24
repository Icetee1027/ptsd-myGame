#include "Card/Card.hpp"
#include "Card/Chest.hpp"
#include "Card/Combatable.hpp"
#include "Card/Equipable.hpp"
#include "Card/CardPack.hpp"
#include "Util/Time.hpp"
#include "App.hpp"
#include "Card/CardBar.hpp"
#include "Util/Input.hpp"
#include "SynthesisTable.hpp"
#include "SystemSettlementUI.hpp"
#include "ShopRandom.hpp"

#include <random>
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
        m_ClickTime = Util::Time::GetElapsedTimeMs();
        if (!m_SFXs.empty()) {
            m_SFXs[0]->Play();
        }
    }

    void Card::ClickUp() {
        if (Util::Time::GetElapsedTimeMs() - m_ClickTime < 120) {
            Clicking();
        }
        if (m_SFXs.size() > 1) {
            m_SFXs[1]->Play();
        }
    }

    void Card::Clicking() {

    }

    void Card::Update() {
        if (SystemSettlementUI::IsSystemUpdta) {
            SystemSettlementUI::CurrentStorageCapacity++;
        }
        UpdateCard();
        PositionUpdate();
        if (m_Parent != nullptr) {m_Parent->Update();}


        if (m_SynthesisTime != 0 && App::m_IsPlayButton==App::PauseOrPlay::Play && m_SyntheticStop == false) {
            SynthesisUpdate();
        }
        if (m_SyntheticStop == true && (Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB))) {
            m_CanSynthetic = true;
            m_SyntheticStop = false;
        }
        if (StatusStackRootUpDate) {
            StackRootUpdate();
        }
        if (m_CanSynthetic == true) {
            m_CanSynthetic = false;
            CanSynthetic();
            GetRoot();
            if(!weak_from_this().expired() &&GetRoot()->m_SyntheticTableid==-1){
                SpecialSynthesis();
            }
        }

        ChildUpdate();
    }

    void Card::SynthesisUpdate() {

        m_ProgressTime += Util::Time::GetDeltaTime()* (Util::Input::IsKeyPressed(Util::Keycode::X)?10:1);
        auto temp = std::dynamic_pointer_cast<CardBar>(m_Children[3]);
        temp->SetScaledSize(glm::vec2( m_ProgressTime / m_SynthesisTime, 1));
        if (m_SynthesisTime < m_ProgressTime) {
            if (m_Children[3] != nullptr || m_Children[4] != nullptr) {
                m_Children[3]->SetVisible(0);
                m_Children[4]->SetVisible(0);
            }
            SyntheticDone();
        }
    }

    void Card::ChildUpdate() {
        for (auto child : m_Children) {
            child->SetZIndex(m_ZIndex);
            child->Update();
        }
    }

    void Card::GenerateCard(std::vector<std::string>& cards) {
        for (auto& cardname: cards) {
            if (cardname == "")continue;
            std::random_device rd;
            std::mt19937 rng(rd());
            std::uniform_int_distribution<int> distribution(1, 360);
            float randomNumber = distribution(rng);
            float angleRadians = glm::radians(randomNumber);
            float sineValue = glm::sin(angleRadians);
            float cosineValue = glm::cos(angleRadians);
            auto card = card::CardMaker::MakeCard(cardname);
            bool moveable = card->CanMoveable();
            card->SetMoveable(1);
            card->SetTranslation(glm::vec3(sineValue * 150 + m_Transform.translation.x, cosineValue * 120 + m_Transform.translation.y, 0));
            card->SetMoveable(moveable);
            App::AddCardForG(card);
        }
        
    }
    void Card::GenerateCard(std::string& cardname) {
        if (cardname == "")return;
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<int> distribution(1, 360);
        float randomNumber = distribution(rng);
        float angleRadians = glm::radians(randomNumber);
        float sineValue = glm::sin(angleRadians);
        float cosineValue = glm::cos(angleRadians);
        auto card = card::CardMaker::MakeCard(cardname);
        bool moveable = card->CanMoveable();
        card->SetMoveable(1);
        card->SetTranslation(glm::vec3(sineValue * 150 + m_Transform.translation.x, cosineValue * 120 + m_Transform.translation.y, 0));
        card->SetMoveable(moveable);
        App::AddCard(card);
        

    }
    void Card::PositionUpdate() {
        if (m_Parent != nullptr) {
            m_Transform.translation = m_Parent->GetTransform().translation + glm::vec3(0, -47, 0);
        }
        else {
            if (m_PushCount != 0 && m_CanPush) {
                m_Transform.translation += glm::vec3(m_PushVector.x * m_PushCount, m_PushVector.y * m_PushCount, 0);
                m_PushCount--;
            }

            if (m_Transform.translation.x < -1800+110 && m_Type!= Type::Shop) {
                m_Transform.translation.x = -1800+110;
            }
            else if (m_Transform.translation.x > 1800-110&& m_Type != Type::Shop) {
                m_Transform.translation.x = 1800-110;
            }
            if (m_Transform.translation.y > 1100-135&& m_Type != Type::Shop) {
                m_Transform.translation.y = 1100-135;
            }else if(m_Transform.translation.y - (GetStackSize() - 1) * 47 < -1100+135 && m_Type != Type::Shop) {
                m_Transform.translation.y = -1100+135 + (GetStackSize() - 1) * 47;
            }
            
        }
        if (m_Child != nullptr) {
            GetChildren()[2]->SetVisible(m_Child->GetChildren()[2]->GetVisible());
        }
    }

    void Card::SetSynthesisTime(float time) {
        m_SynthesisTime = time;
        m_ProgressTime = 0;
        if (m_Children[3] != nullptr || m_Children[4] != nullptr) {
            m_Children[3]->SetVisible(1);
            m_Children[4]->SetVisible(1);
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
        else if (!weak_from_this().expired()&& App::m_Mouse->GetBindObject() == shared_from_this()) {
            App::m_Mouse->ObjectUmBind();
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
        m_Transform.translation.z = 0;
        StatusStackRootUpDate = false;
        if (m_Child != nullptr) {
            m_Child->StackRootUpdate();
        }
    }

    std::vector<std::string> Card::GetCardsName() {
        auto root = GetRoot();
        std::vector<std::string> cards = {};
        while (root != nullptr) {
            cards.push_back(root->GetCardName());
            root = root->GetChild();
        }
        return cards;
    }

    void Card::CanSynthetic() {
        auto name=GetCardsName();
        auto [a,b]=SynthesisTable::SyntheticCheck(name);
        if (a != -1) {

            if (GetRoot()->m_SyntheticTableid != a) {
                GetRoot()->SetSynthesisTime(SynthesisTable::m_SynthesisTable[a].time / b);
                GetRoot()->m_SyntheticTableid = a;
                LOG_DEBUG("index:{}:{}", SynthesisTable::m_SynthesisTable[a].time / b,a);
            }

           if (GetRoot() != shared_from_this() && GetRoot()->m_SyntheticTableid == m_SyntheticTableid && GetRoot()->m_SyntheticTableid != -1) {
                GetRoot()->m_ProgressTime = m_ProgressTime;
                CancelComposition();
            }
        }
        else if(m_SyntheticStop==false){
            if (!weak_from_this().expired())
                CancelComposition();
        }
        else if(m_SyntheticStop == true) {

        }

    }

    void Card::SyntheticDone() {
        auto thisCaard = shared_from_this();
        m_SynthesisTime = 0;
        auto t_id = m_SyntheticTableid;
        m_SyntheticTableid = -1;
        if (SynthesisTable::m_SynthesisTable[t_id].delet.size() == SynthesisTable::m_SynthesisTable[t_id].need.size() && SynthesisTable::m_SynthesisTable[t_id].name == "") {
            RemoveStack();
            return;
        }
        
        std::vector <std::string> element = SynthesisTable::m_SynthesisTable[t_id].delet;
        auto stack = GetAllCardsInStack();
        
        for (auto it = stack.begin(); it != stack.end();) {
            auto card = *it;
            auto cardName = card->GetCardName();
            auto findIt = std::find(element.begin(), element.end(), cardName);
            if (findIt != element.end() && card->m_UsageCount == 1) {
                // Found the card's name, remove it
                card->RemoveCard();
                it = stack.erase(it); // Advance iterator after erasing
                element.erase(findIt);
            }
            else if(findIt != element.end() && card->m_UsageCount > 1){
                card->m_UsageCount--;
                ++it; // Advance iterator if not erasing
            }
            else {
                ++it;
            }
        }
        if (!stack.empty()) {
            stack[0]->m_CanSynthetic = true;
        }
        if (SynthesisTable::m_SynthesisTable[t_id].random == false) {
            auto vt=std::vector<std::string>({SynthesisTable::m_SynthesisTable[t_id].name });
            GenerateCard(vt);
        }
        else if (SynthesisTable::m_SynthesisTable[t_id].name == "TreasureChest") {
            for (int i = 0; i < 4; i++) {
                auto vt=std::vector<std::string>({ ShopRandom::drawLottery(SynthesisTable::m_SynthesisTable[t_id].name) });
                GenerateCard(vt);
            }
        }
        else if (auto a= std::dynamic_pointer_cast<Portal>(thisCaard)) {
            for (int i = 0; i < (m_Name=="RarePortal"?2:3); i++) {
                auto a = ShopRandom::drawLottery(m_Name);
                GenerateCard(a);
            }
        }
        else {
            auto vt=std::vector<std::string>({ ShopRandom::drawLottery(SynthesisTable::m_SynthesisTable[t_id].name) });
            GenerateCard(vt);
        }
    }

    std::vector<std::shared_ptr<Card>> Card::GetAllCardsInStack() {

        auto root = GetRoot();
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
        if (std::dynamic_pointer_cast<Chest>(shared_from_this())|| std::dynamic_pointer_cast<Shop>(shared_from_this())|| std::dynamic_pointer_cast<Sell>(shared_from_this()))
        {
            num = 0;
        }
        int num2 = (isPrefab ? 1 : (otherCard->GetStackSize()));
        if (num + num2 > GetRoot()->m_MaxAnimalCount)
        {   
            //LOG_DEBUG("CanHaveCardOnTop out of size");
            return false;
        }
        if (std::dynamic_pointer_cast<CardPack>(rootcard) && rootcard->GetChild()!=nullptr )//rootCard.Child.CardData.DetermineCanHaveCardsWhenIsRoot
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
        if (std::dynamic_pointer_cast<Combatable>(shared_from_this()))
        {
            bool flag = false;
            if (otherCard->GetCardName() == "Bone" && m_Name == "Wolf")
            {
                flag = true;
            }
           
            if (!(std::dynamic_pointer_cast<Equipable>(otherCard) || dynamic_cast<Combatable*>(otherCard.get()) || flag))
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

    void Card::CancelComposition() {
        if (m_Children[3] != nullptr || m_Children[4] != nullptr) {
            m_Children[3]->SetVisible(0);
            m_Children[4]->SetVisible(0);
        }
        m_SynthesisTime = 0;
        m_SyntheticTableid = -1;
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
        //if (pushvector == glm::vec2(0, 0))return;
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
