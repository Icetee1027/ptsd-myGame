#include "Card/CardPack.hpp"
#include "Card/CardMaker.hpp"
#include "App.hpp"
#include "Util/Time.hpp"
#include "SystemSettlementUI.hpp"
#include <random>
/*
* #include "Card/Card.hpp"
#include <cstddef>
#include <glm/fwd.hpp>
#include <memory>
#include "Mouse.hpp"
#include "Util/Logger.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

*/

namespace card {
    CardPack::CardPack(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image,  const bool iconcolor)
        : Card(type, name, id, sfxs, image, iconcolor){
        m_CanPush = 4;
    }

    void CardPack::GenerateCard(){
        Camera::CameraShake();
        if (m_Cards.empty()) {
            App::RemoveCard(shared_from_this(), m_Transform.translation.x);
            return;
        }
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<int> distribution(1, 360);
        float randomNumber = distribution(rng);
        float angleRadians = glm::radians(randomNumber);
        float sineValue = glm::sin(angleRadians);
        float cosineValue = glm::cos(angleRadians);
        auto cardname = m_Cards[0];
        m_Cards.erase(m_Cards.begin());
        try
        {
            auto card=card::CardMaker::MakeCard(cardname);
            bool moveable = card->CanMoveable();
            card->SetMoveable(1);
            card->SetTranslation(glm::vec3(sineValue * 150 + m_Transform.translation.x, cosineValue * 150 + m_Transform.translation.y, 0));
            card->SetMoveable(moveable);

            if (card->GetCardName().find("Idea") != std::string::npos) {
                App::m_SideText->AddBluePrint(card->GetCardName());
            }

            App::AddCardForG(card);

        }
        catch (const std::exception&)
        {
            LOG_ERROR("Card Pack ERROR name:{}", cardname);
        }
        if (m_Cards.empty()) {
            App::RemoveCard(shared_from_this(), m_Transform.translation.x);
            return;
        }
    }
    void CardPack::Clicking() {
        GenerateCard();
    }
    void CardPack::Update() {
        if (SystemSettlementUI::IsSystemUpdta) {
            SystemSettlementUI::CurrentStorageCapacity--;
        }
        if (m_Children[0]!=nullptr&& m_Children[0]->GetVisible()==1) {
            m_Children[0]->SetVisible(0);
        }
        Card::Update();
    }

}