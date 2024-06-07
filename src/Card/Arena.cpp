#include "Card/Arena.hpp"
#include "Card/CardMaker.hpp"
#include "ShapeHelper.hpp"
#include "Util/Time.hpp"
#include "App.hpp"
#include "SystemSettlementUI.hpp"
#include <random>
template <typename T>
T getRandomElement(const std::vector<T>& vec) {
	if (vec.empty()) {
		throw std::runtime_error("Cannot get an element from an empty vector.");
	}

	// 使用随机设备初始化随机数生成器
	std::random_device rd;
	std::mt19937 gen(rd());

	// 定义一个均匀分布 [0, vec.size() - 1]
	std::uniform_int_distribution<> dis(0, vec.size() - 1);

	// 返回随机选择的元素
	return vec[dis(gen)];
}
int randomOutcome(int probability) {
	// 检查概率值是否在有效范围内
	if (probability < 0 || probability > 100) {
		throw std::invalid_argument("Probability must be between 0 and 100.");
	}

	// 初始化随机数生成器
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 99);

	// 生成一个随机数
	int random_number = dis(gen);

	// 判断随机数是否在成功的概率范围内
	return (random_number < probability) ? 1 : 0;
}

namespace card {
	Arena::Arena(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor)
		: Card(type, name, id, sfxs, image, iconcolor) {
		m_CanPush = 9;
		m_Moveable = 0;
		m_circle->SetVisible(0);
		App::AddObjectToRoot(m_circle);
		//m_BaseVillagers.push_back(std::dynamic_pointer_cast<BaseVillager>(CardMaker::MakeCard("Dog")));
	}
	bool Arena::CanHaveCard(std::shared_ptr<Card> otherCard) {
		if (otherCard->GetCardType() == Type::Villager) {
			return true;
		}
		return false;
	}

	void Arena::ArrangementUpdata() {
		int size = std::max(m_BaseVillagers.size(), m_Mobs.size());
		m_Transform.scale = { size * 0.7 ,1.3 };
		auto VB = GetScaledSize().x / size;
		//LOG_ERROR("{},{}", m_BaseVillagers.size(), m_Mobs.size());
		for (int i = 0; i < m_BaseVillagers.size(); i++) {
			glm::vec3 loc = { m_Transform.translation.x - GetScaledSize().x / 2 + VB * (i + float(size - m_BaseVillagers.size()) / 2) + 130,m_Transform.translation.y + 140, 5 };
			m_BaseVillagers[i]->IsBattle = true;
			m_BaseVillagers[i]->SetTranslation(loc);
		}
		auto MB = GetScaledSize().x / size;
		for (int i = 0; i < m_Mobs.size(); i++) {
			m_Mobs[i]->SetMoveable(1);
			glm::vec3 loc = { m_Transform.translation.x - GetScaledSize().x / 2 + MB * (i + (float(size - m_Mobs.size()) / 2)) + 130,m_Transform.translation.y - 140, 0 };
			m_Mobs[i]->SetTranslation(loc);
		}
		auto end_it = std::remove_if(App::VillagerLocation.begin(), App::VillagerLocation.end(),
			[this](const std::weak_ptr<Card>& weakVillager) {
				auto villager = weakVillager.lock(); // 將 weak_ptr 轉換為 shared_ptr
				if (!villager) return false; // 如果轉換失敗（即指向的對象已經被刪除），返回 false
				return std::find_if(m_BaseVillagers.begin(), m_BaseVillagers.end(), [&villager](const std::shared_ptr<Card>& baseVillager) {
					return baseVillager == villager;
					}) != m_BaseVillagers.end();
			});

		App::VillagerLocation.erase(end_it, App::VillagerLocation.end());


	}

	bool Arena::CheckStatus() {
		bool updata = false;
		for (auto it = m_BaseVillagers.begin(); it != m_BaseVillagers.end(); ) {
			if ((*it)->GetHP() <= 0) {
				
				(*it)->VillagerDead();
				it = m_BaseVillagers.erase(it); 
				updata = true;
			}
			else {
				++it;
			}
		}
		for (auto it = m_Mobs.begin(); it != m_Mobs.end(); ) {
			if ((*it)->GetHP() <= 0) {
				(*it)->MobDead();
				it = m_Mobs.erase(it);
				updata = true;
			}
			else {
				++it;
			}
		}
		if (m_Mobs.size() <= 0 || m_BaseVillagers.size() <= 0) {
			for (auto& a : m_BaseVillagers) {
				a->IsBattle = false;
				App::AddCard(a);
			}
			for (auto& a : m_Mobs) {
				a->SetMoveable(0);
				App::AddCard(a);
			}
			RemoveCard();
			return 0;
		}
		
		if (updata) {
			ArrangementUpdata();
		}
		return 1;
	}
	void Arena::RoundAttack() {
		if (m_mode == Mode::Villager) {
			if (Villagers_index >= m_BaseVillagers.size())Villagers_index = 0;
			auto vi = m_BaseVillagers[Villagers_index];
			auto min_hp_mob = std::min_element(m_Mobs.begin(), m_Mobs.end(),
				[](const std::shared_ptr<Mob>& a, const std::shared_ptr<Mob>& b) {
					return a->GetHP() < b->GetHP();
				});
			auto mob_name = (*min_hp_mob)->GetCardName();
			if (randomOutcome(Villager_HitRate.find(vi->GetCardName())->second) && !randomOutcome(Mob_DodgeRate.find(mob_name)->second)) {

				m_attack = Villager_harm.find(vi->GetCardName())->second;
			}
			else {
				m_attack = 0;
			}
			Villagers_index++;
			if (Villagers_index >= m_BaseVillagers.size()) {
				Villagers_index = 0;
				m_mode = Mode::t_Mob;
			}
			m_circle->CircleMove(vi, (*min_hp_mob));
		}
		else {
			if (Villagers_index >= m_BaseVillagers.size())Villagers_index = 0;
			auto mob = m_Mobs[Mobs_index];
			auto vi = getRandomElement(m_BaseVillagers);
			auto vi_name = vi->GetCardName();
			float attack = 0;
			if (randomOutcome(Mob_HitRate.find(mob->GetCardName())->second) && !randomOutcome(Villager_DodgeRate.find(vi_name)->second)) {

				m_attack = Mob_harm.find(mob->GetCardName())->second;
			}
			else {
				m_attack = 0;
			}
			Mobs_index++;
			if (Mobs_index >= m_Mobs.size()) {
				Mobs_index = 0;
				m_mode = Mode::Villager;
			}
			m_circle->CircleMove(mob, vi);
		}
		m_circle->Attack = m_attack;
	}
	void Arena::Update() {
		if (SystemSettlementUI::IsSystemUpdta) {
			SystemSettlementUI::CurrentStorageCapacity--;
		}
		if (m_timeCount >= m_time) {
			m_timeCount = 0;
			if(!CheckStatus())return;
			RoundAttack();
		}
		else if (App::m_IsPlayButton == App::PauseOrPlay::Play) {
			m_timeCount += Util::Time::GetDeltaTime();
		}
		if (BaseVillager::VillagerLocation) {
			App::VillagerLocation.push_back(shared_from_this());
		}
		if (m_Child != nullptr) {
			if (auto v = std::dynamic_pointer_cast<BaseVillager>(m_Child)) {
				m_BaseVillagers.push_back(v);
				m_Child->RemoveCard();
				ArrangementUpdata();
			}
		}
		if (m_PushCount != 0) {
			for (auto& a : App::m_WorldCards) {
				if (a.second->GetCardName() == "Arena") {
					if (ShapeHelper::IsCardInCard(shared_from_this(), a.second) && m_Mobs.size() != 0) {
						auto x = std::dynamic_pointer_cast<Arena>(a.second);
						if (x == shared_from_this())continue;
						ArenaMerge(x);
						SetPushing(glm::vec2(), 0);
						break;
					}
				}
			}

		}
		Card::Update();
		m_circle->Update();
		for (auto& a : m_BaseVillagers) {
			a->ChildUpdate();
			a->ShakeUpdate();
		}
		for (auto& a : m_Mobs) {
			a->ChildUpdate();
			a->ShakeUpdate();
		}


	}
	void Arena::ArenaMerge(std::shared_ptr<Arena>& card) {

		auto t_Arena = std::dynamic_pointer_cast<Arena>(card::CardMaker::MakeCard("Arena"));
		t_Arena->SetMoveable(1);
		t_Arena->SetTranslation((m_Transform.translation + card->GetTransform().translation) / 2.0f);
		t_Arena->SetMoveable(0);

		t_Arena->m_Mobs.insert(t_Arena->m_Mobs.end(), m_Mobs.begin(), m_Mobs.end());
		t_Arena->m_Mobs.insert(t_Arena->m_Mobs.end(), card->m_Mobs.begin(), card->m_Mobs.end());

		t_Arena->m_BaseVillagers.insert(t_Arena->m_BaseVillagers.end(), m_BaseVillagers.begin(), m_BaseVillagers.end());
		t_Arena->m_BaseVillagers.insert(t_Arena->m_BaseVillagers.end(), card->m_BaseVillagers.begin(), card->m_BaseVillagers.end());

		m_BaseVillagers.clear();
		m_Mobs.clear();
		card->m_BaseVillagers.clear();
		card->m_Mobs.clear();
		t_Arena->ArrangementUpdata();
		App::AddCard(t_Arena);
		card->RemoveCard();
		RemoveCard();

	}
	void Arena::AddCard(std::shared_ptr<Card>& card) {
		if (auto v = std::dynamic_pointer_cast<BaseVillager>(card)) {
			m_BaseVillagers.push_back(v);
		}
		else if (auto m = std::dynamic_pointer_cast<Mob>(card))
		{
			m_Mobs.push_back(m);

		}
		else {
			LOG_ERROR("Arena::AddCard(std::shared_ptr<Card>& card) ERROR !!");
		}
		ArrangementUpdata();
	}
}
