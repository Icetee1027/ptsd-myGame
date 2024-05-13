#include "Card/Mob.hpp"
#include "Util/Time.hpp"
#include "App.hpp"
#include <random>
namespace card {
    Mob::Mob(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor)
        : Combatable(type, name, id, sfxs, image, iconcolor) {
        m_Moveable = false;
        m_CanPush = 5;
    }
    bool Mob::CanHaveCard(std::shared_ptr<Card> otherCard) {
        // 检查是否是 "bone" 和 "wolf" 的组合
        if (otherCard->GetCardName() == "bone" && m_Name == "wolf") {
            return true;
        }


        // 调用 AllCardsInStackMatchPred 函数，传入一个 lambda 表达式作为参数
        //return AllCardsInStackMatchPred(otherCard, [](const CardData& x) {
        //    // Lambda 表达式判断条件
        //    return std::dynamic_pointer_cast<Combatable>(x) && std::dynamic_pointer_cast<Animal>(x);
        //    });
        return false;
    }
    void Mob::UpdateCard() {
        if (m_CountTime >= m_Time && m_Parent==nullptr && m_Child==nullptr) {
            MobCardMoveing();
        }
        else {
            m_CountTime += Util::Time::GetDeltaTime();
        }


        // 设置随机数生成器
        Card::UpdateCard();
    }
    void Mob::MobCardMoveing() {
        if (!App::VillagerLocation.empty()) {

            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(1, 5);
            m_Time = dis(gen);
            m_CountTime = 0;
            glm::vec2 unitVector = getDirectionToClosestVillager();
            SetPushing(unitVector * (0.05f), 160);
            App::m_PushProcessingArea.push_back(shared_from_this());
        }
        else {
            BaseVillager::VillagerLocation = true;
        }

    }
    glm::vec2 Mob::getDirectionToClosestVillager() {
        // 找到距离自己最近的点的索引
        size_t closestIndex = 0;
        glm::vec2 dis = { m_Transform.translation.x,m_Transform.translation.y };
        float closestDistance = glm::distance(App::VillagerLocation[0], dis);
        for (size_t i = 1; i < App::VillagerLocation.size(); ++i) {
            float distance = glm::distance(App::VillagerLocation[i], dis);
            if (distance < closestDistance) {
                closestDistance = distance;
                closestIndex = i;
            }
        }

        // 计算朝向最近点的单位向量
        glm::vec2 direction = App::VillagerLocation[closestIndex] - dis;
        App::VillagerLocation.clear();
        return normalize(direction);
    }
}