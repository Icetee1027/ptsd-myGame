#include "Card/Animal.hpp"
#include <random>
#include "App.hpp"
#include "card/BaseVillager.hpp"
#include "Util/Time.hpp"
namespace card {
    Animal::Animal(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const  bool iconcolor)
        : Mob(type, name, id, sfxs, image, iconcolor) {
        m_Moveable = true;
        m_CanPush = 1;
    }
    bool Animal::CanHaveCard(std::shared_ptr<Card> otherCard){
        if (otherCard->GetCardType() == Type::Villager) {
            return true;
        }
        if (!std::dynamic_pointer_cast<Animal>(otherCard))
        {
            return false;
        }
        if (m_Parent != nullptr) {
            return true;
        }
        return false;
    }
    void Animal::Clicking() {
        MobCardMoveing();
    }
    void Animal::UpdateCard() {
        if (m_RawCardsTime >= 120) {
            if (m_Name == "Chicken") {
                std::vector<std::string> cardList = { "Egg" };
                GenerateCard(cardList);

            }
            else if (m_Name == "Cow") {
                std::vector<std::string> cardList = { "Milk" };
                GenerateCard(cardList);
            }
            m_RawCardsTime = 0;
        }
        else {
            m_RawCardsTime += Util::Time::GetDeltaTime();
        }
        Mob::UpdateCard();
    }
    void Animal::MobCardMoveing() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(10, 15);
        m_Time = dis(gen);
        std::uniform_real_distribution<> diss(0.0, glm::two_pi<double>());
        m_CountTime = 0;

        // 生成随机角度
        double randomAngle = diss(gen);

        // 使用角度生成二维向量
        glm::vec2 randomVector = glm::vec2(std::cos(randomAngle), std::sin(randomAngle));

        // 将向量归一化为单位向量
        glm::vec2 unitVector = normalize(randomVector);
        SetPushing(unitVector * (0.05f), 160);
        App::m_PushProcessingArea.push_back(shared_from_this());
    }
    
}