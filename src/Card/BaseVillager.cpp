#include "Card/BaseVillager.hpp"
#include "Card/Food.hpp"
#include "Util/Time.hpp"
#include <random>
#include "SystemSettlementUI.hpp"
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
        if (SystemSettlementUI::IsSystemUpdta) {
            if (m_Name =="Dog") {
                SystemSettlementUI::AmountFoodRequired ++;
            }
            else {
                SystemSettlementUI::AmountFoodRequired+=2;
            }
            SystemSettlementUI::CurrentStorageCapacity--;
        }
        if (m_StaticUpdate == true) {
            m_StaticUpdate = false;
            m_Children.back()->SetDrawable(CardElementPool::getNumberTextElement(m_HP, m_IconColor));
        }
        if(VillagerLocation)
            App::VillagerLocation.push_back(shared_from_this());
    }
    void BaseVillager::DoubleClick(){
        if (m_Parent == nullptr) {
            if (m_Name != "Villager" && m_Name != "Dog") {
                auto card1 = std::dynamic_pointer_cast<BaseVillager>(card::CardMaker::MakeCard("Villager"));

                if (card1) {
                    m_Transform.translation.z = 0;
                    card1->SetTranslation(m_Transform.translation);
                    card1->SetHP(m_HP);
                    card1->m_StaticUpdate = true;
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
        if (m_Parent == nullptr && m_Child!=nullptr && m_Child->GetChild()==nullptr && m_Name == "Villager" && m_Name != "Dog") {
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
    double rand_normal(double mean, double stddev) {
        static std::default_random_engine generator(Util::Time::GetElapsedTimeMs());
        std::normal_distribution<double> distribution(mean, stddev);
        return distribution(generator);
    }
    void BaseVillager::SetAndUpdateHp(float hp) {
        m_HP = hp;
        m_Children.back()->SetDrawable(CardElementPool::getNumberTextElement(m_HP, m_IconColor));
    }
    void BaseVillager::VillagerDead() {
        GenerateCard(std::string("Corpse"));
    }
    void BaseVillager::ShakeUpdate() {
        if (m_time >= 0.1) {
            return;
        }

        m_time += Util::Time::GetDeltaTime();


        double shake_offset_x = rand_normal(0.0, 6);
        double shake_offset_y = rand_normal(0.0, 7);
        //LOG_DEBUG("{}:{}:{}", shake_offset_x, shake_offset_y, shake_offset_z);

        m_Transform.translation+= glm::vec3(shake_offset_x, shake_offset_y,0);
        if (m_time >= 0.1) {
            m_Transform.translation = OroriginalLocation;
        }

    }
    bool BaseVillager::VillagerLocation = 0;
}