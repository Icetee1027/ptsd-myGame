#include "Card/Mob.hpp"
#include "Util/Time.hpp"
#include "Card/CardMaker.hpp"
#include "App.hpp"
#include <random>
#include "SystemSettlementUI.hpp"
#include "ShapeHelper.hpp"
#include "ShopRandom.hpp"
namespace card {
    Mob::Mob(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor)
        : Combatable(type, name, id, sfxs, image, iconcolor) {
        m_Moveable = false;
        m_CanPush = 5;
    }
    bool Mob::CanHaveCard(std::shared_ptr<Card> otherCard) {
        // 检查是否是 "bone" 和 "wolf" 的组合
        if (otherCard->GetCardName() == "bone" && m_Name == "wolf" || otherCard->GetCardType()==Type::Villager) {
            return true;
        }


        // 调用 AllCardsInStackMatchPred 函数，传入一个 lambda 表达式作为参数
        //return AllCardsInStackMatchPred(otherCard, [](const CardData& x) {
        //    // Lambda 表达式判断条件
        //    return std::dynamic_pointer_cast<Combatable>(x) && std::dynamic_pointer_cast<Animal>(x);
        //    });
        return false;
    }
    void Mob::ArenaStrat(std::shared_ptr<BaseVillager>  villager) {
        
        if (villager == nullptr) {
            if (WhoToChase.lock() == App::m_Mouse->GetBindObject()) {
                App::m_Mouse->ObjectUmBind();
                WhoToChase.lock()->GetChildren()[2]->SetVisible(0);
                
            }
           
            if (auto ca = std::dynamic_pointer_cast<BaseVillager>(WhoToChase.lock())) {

                auto t_Arena = std::dynamic_pointer_cast<Arena>(card::CardMaker::MakeCard("Arena"));
                t_Arena->SetMoveable(1);
                t_Arena->SetTranslation(m_Transform.translation);
                t_Arena->SetMoveable(0);
                t_Arena->m_Mobs.push_back(std::dynamic_pointer_cast<Mob>(shared_from_this()));
                t_Arena->m_BaseVillagers.push_back(ca);
                t_Arena->ArrangementUpdata();
                App::AddCard(t_Arena);
                WhoToChase.lock()->RemoveCard();
            }
            else if(auto ca = std::dynamic_pointer_cast<Arena>(WhoToChase.lock()))
            {
                ca->AddCard(shared_from_this());
            }
            else {
                LOG_ERROR("Mob::ArenaStrat ERROR!!");
            }
        }
        else {
            auto t_Arena = std::dynamic_pointer_cast<Arena>(card::CardMaker::MakeCard("Arena"));
            t_Arena->SetMoveable(1);
            t_Arena->SetTranslation(m_Transform.translation);
            t_Arena->SetMoveable(0);
            t_Arena->m_Mobs.push_back(std::dynamic_pointer_cast<Mob>(shared_from_this()));
            t_Arena->m_BaseVillagers.push_back(villager);
            villager->RemoveCard();
            t_Arena->ArrangementUpdata();
            App::AddCard(t_Arena);
        }
        App::VillagerLocation.clear();
        RemoveCard();
    }

    void Mob::UpdateCard() {
        if (SystemSettlementUI::IsSystemUpdta) {
            SystemSettlementUI::CurrentStorageCapacity--;
        }
        if (m_StaticUpdate == true) {
            m_StaticUpdate = false;
            m_Children.back()->SetDrawable(CardElementPool::getNumberTextElement(m_HP, m_IconColor));
        }
        if (m_Child != nullptr && m_Child->GetCardType() == Type::Villager) {
            ArenaStrat(std::dynamic_pointer_cast<BaseVillager>(m_Child));
        }
        if (m_PushCount != 0 ) {
            if (!WhoToChase.expired()) {
                if (auto sharedPtrLocked = WhoToChase.lock()) {
                    if (auto ca = std::dynamic_pointer_cast<BaseVillager>(WhoToChase.lock())) {
                        if (ca->IsBattle == true) {
                            MobCardMoveing();
                        }
                    }
                    if (ShapeHelper::IsCardInCard(shared_from_this(), sharedPtrLocked)) {
                        ArenaStrat();
                    }
                }
            }
        }
        if (m_CountTime >= m_Time && m_Parent==nullptr && m_Child==nullptr) {
            MobCardMoveing();
        }
        else if(App::m_IsPlayButton == App::PauseOrPlay::Play){
            m_CountTime += Util::Time::GetDeltaTime();
        }
        
        // 设置随机数生成器
        Card::UpdateCard();
    }
    void Mob::MobCardMoveing() {
        
        if (m_Movestop == true)return;
        if (!App::VillagerLocation.empty() && App::VillagerLocation.size()<30000) {
            //for (auto& a : App::VillagerLocation) {
            //    LOG_DEBUG("{}", a.lock()->GetCardName());
            //}
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(1, 5);
            m_Time = dis(gen);
            m_CountTime = 0;
            glm::vec2 unitVector = getDirectionToClosestVillager();
            SetPushing(unitVector * (0.05f), 160);
            App::m_PushProcessingArea.push_back(shared_from_this());

            BaseVillager::VillagerLocation = false;
            
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
            LOG_ERROR("Mob::getDirectionToClosestVillager() App::VillagerLocation.empty()) error");
            return glm::vec2();
        }
        std::vector<glm::vec2> vdis = {};
        for (auto a : App::VillagerLocation) {
            auto sharedPtr = a.lock(); // 取得 std::shared_ptr
            if (sharedPtr&& !a.expired()) {
                vdis.push_back(glm::vec2(sharedPtr->GetTransform().translation.x, sharedPtr->GetTransform().translation.y));
            }
            else {
                LOG_ERROR("Mob::getDirectionToClosestVillager() error!!");
            }
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
        return normalize(direction);
    }
    double rand_norma(double mean, double stddev) {
        static std::default_random_engine generator(Util::Time::GetElapsedTimeMs());
        std::normal_distribution<double> distribution(mean, stddev);
        return distribution(generator);
    }
   void Mob::ShakeUpdate() {
        if (shake_time >= 0.1) {
            return;
        }

        shake_time += Util::Time::GetDeltaTime();

        double shake_offset_x = rand_norma(0.0, 6);
        double shake_offset_y = rand_norma(0.0, 7);
        //LOG_DEBUG("{}:{}:{}", shake_offset_x, shake_offset_y, shake_offset_z);

        m_Transform.translation+= glm::vec3(shake_offset_x, shake_offset_y, 0);
        if (shake_time >= 0.1) {
            m_Transform.translation = OroriginalLocation;
        }
    }
   void Mob::SetAndUpdateHp(float hp) {
       m_HP = hp;
       m_Children.back()->SetDrawable(CardElementPool::getNumberTextElement(m_HP, m_IconColor));
   }
   void Mob::MobDead() {
       if (m_Name == "Chicken" || m_Name == "Rabbit") {
           auto a = ShopRandom::drawLottery(m_Name);
           GenerateCard(a);
       }
       else if (m_Name == "Cow") {
           GenerateCard(std::string("Milk"));
           GenerateCard(std::string("RawMeat"));
       }
       else if (m_Name != "Slime") {
           for (int i = 0; i < 2; i++) {
               auto a = ShopRandom::drawLottery(m_Name);
               GenerateCard(a);
           }
       }
       else {
           for (int i = 0; i < 4; i++) {
               GenerateCard(std::string("SmallSlime"));
           }
       }
   }
}