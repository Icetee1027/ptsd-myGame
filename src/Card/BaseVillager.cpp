#include "Card/BaseVillager.hpp"
#include "Card/Food.hpp"
#include "Util/Time.hpp"
#include "App.hpp"
namespace card{
    BaseVillager::BaseVillager(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor)
        :Combatable(type, name, id, sfxs, image, iconcolor) {
    }
    bool BaseVillager::CanHaveCard(std::shared_ptr<Card> otherCard){
        if (!std::dynamic_pointer_cast<BaseVillager>(otherCard) && otherCard->GetCardType() != Type::Resource && otherCard->GetCardType() != Type::Equipment && !(dynamic_cast<Food*>(otherCard.get())))
        {
            return false;
        }
        return true;
    }
    void BaseVillager::UpdateCard() {
        if(VillagerLocation)
            App::VillagerLocation.push_back(std::dynamic_pointer_cast<BaseVillager>(shared_from_this()));
    }
    void BaseVillager::DoubleClick(){
        if (m_Parent == nullptr) {
            if (m_Name != "Villager") {
                auto card1 = card::CardMaker::MakeCard("Villager");

                if (card1) {
                    m_Transform.translation.z = 0;
                    card1->SetTranslation(m_Transform.translation);
                    card1->SetHP(m_HP);
                    App::AddCard(card1);
                    std::vector<std::string> t = { m_Weaponry };
                    GenerateCard(t);

                }

                RemoveStack();
            }
        }
    }
    void BaseVillager::Clicking() {
        if (Util::Time::GetElapsedTimeMs() - m_doubleclicktime < 200) {
            DoubleClick();
       }
        m_doubleclicktime = Util::Time::GetElapsedTimeMs();
    }
    void BaseVillager::SpecialSynthesis() {
        if (m_Parent == nullptr && m_Child!=nullptr && m_Child->GetChild()==nullptr && m_Name == "Villager") {
            if (m_Child->GetCardName() == "Map") {
                auto card = std::dynamic_pointer_cast<BaseVillager>(card::CardMaker::MakeCard("Explorer"));

                if (card) {
                    card->SetTranslation(m_Transform.translation);
                    card->SetWeaponry("Map");
                    App::AddCard(card);

                }
                RemoveStack();

            }
            else if (m_Child->GetCardName() == "Spear") {
                auto card = std::dynamic_pointer_cast<BaseVillager>(card::CardMaker::MakeCard("Militia"));
                if (card) {
                    card->SetTranslation(m_Transform.translation);
                    card->SetWeaponry("Spear");
                    App::AddCard(card);

                }
                RemoveStack();

            }
            else if (m_Child->GetCardName() == "Sword") {
                auto card = std::dynamic_pointer_cast<BaseVillager>(card::CardMaker::MakeCard("Swordsman"));
                if (card) {
                    card->SetTranslation(m_Transform.translation);
                    card->SetWeaponry("Sword");
                    App::AddCard(card);

                }
                RemoveStack();

            }
        }
       
    }
    bool BaseVillager::VillagerLocation = 0;
}