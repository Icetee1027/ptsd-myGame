#include "Card/Mob.hpp"
#include "Util/Time.hpp"
#include "Card/CardMaker.hpp"
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
    void Mob::ArenaStrat() {
        auto t_Arena = std::dynamic_pointer_cast<Arena>(card::CardMaker::MakeCard("Arena"));
        t_Arena->SetTranslation(m_Transform.translation);
        t_Arena->m_Mobs.push_back(std::dynamic_pointer_cast<Mob>(shared_from_this()));
        t_Arena->m_BaseVillagers.push_back(WhoToChase.lock());
        t_Arena->ArrangementUpdata();
        App::AddCard(t_Arena);
        RemoveCard();


        WhoToChase.lock()->RemoveCard();
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
        
        if (m_Movestop == true)return;
        if (!App::VillagerLocation.empty() ) {

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
        if (App::VillagerLocation.empty()) {
            LOG_ERROR("Mob::getDirectionToClosestVillager() error");
            return glm::vec2();
        }
        std::vector<glm::vec2> vdis = {};
        for(auto& a : App::VillagerLocation) {
            vdis.push_back(glm::vec2(a->GetTransform().translation.x,a->GetTransform().translation.y));
        }
        float closestDistance = glm::distance(vdis[0], dis);
        for (size_t i = 1; i < vdis.size(); ++i) {
            float distance = glm::distance(vdis[i], dis);
            if (distance < closestDistance) {
                closestDistance = distance;
                closestIndex = i;
            }
        }
        WhoToChase = App::VillagerLocation[closestIndex];
        // 计算朝向最近点的单位向量
        glm::vec2 direction = vdis[closestIndex] - dis;
        App::VillagerLocation.clear();
        ArenaStrat();
        return normalize(direction);
    }
}