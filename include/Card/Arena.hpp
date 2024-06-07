#ifndef ARENA_HPP
#define ARENA_HPP
#include "pch.hpp"
#include "Card/Card.hpp"
#include "Card/BaseVillager.hpp"
#include "Card/Mob.hpp"
#include <map>
namespace card {
	class AttackText:public Util::GameObject {
	private:
		float m_timeCount = 1;

	public:
		AttackText();
		~AttackText() = default;
		void Update() override;
		void display(int value, glm::vec3 lo);

	};
	class AttackArrow :public Util::GameObject, public std::enable_shared_from_this<AttackArrow> {
	private:
		std::shared_ptr<Card> m_c1;
		std::shared_ptr<Card> m_c2;
		const float m_CircleTime = 0.3;
		float m_timeCount = 1;
	public:
		float Attack;
		AttackArrow();
		~AttackArrow() = default;
		void Update() override;
		void CircleMove(const std::shared_ptr<Card>& c1, const std::shared_ptr<Card>& c2);
		
	};
	class Arena :public Card {
	private:
		const float m_time = 0.75;
		float m_timeCount = 0;
		int Villagers_index = 0;
		int Mobs_index = 0;
		float m_attack = 0;
		std::shared_ptr<AttackArrow> m_circle = std::make_shared< AttackArrow>();
		enum Mode
		{
			t_Mob,
			Villager
		};
		Mode m_mode = Mode::Villager;
		const std::map<std::string, float> Villager_harm = {{"Dog",1.0f},{"Militia",2.0f},{"Villager",2.0f},{"Explorer",3.0f},{"Swordsman",4.0f}};
		const std::map<std::string, float> Mob_harm = { {"Chicken",1.0f} ,{"Cow",1.0f} ,{"Rabbit",1.0f} ,//
														{"Rat",1.0f},{"SmallSlime",2.0f},//
														{"Skeleton",2.0f},{"Goblin",2.0f},{"Slime",2.0f},//
														{"GiantRat",3.0f},{"Wolf",3.0f},{"Bear",3.0f},//
														{ "Demon", 3.0f } };	

		const std::map<std::string, int> Villager_HitRate = { {"Dog",70},{"Militia",80},{"Villager",80},{"Explorer",85},{"Swordsman",85} };
		const std::map<std::string, int> Mob_HitRate = { {"Chicken",60} ,{"Cow",60} ,{"Rabbit",60} ,//
														{"Rat",65},{"SmallSlime",65},//
														{"Skeleton",70},{"Goblin",70},{"Slime",70},//
														{"GiantRat",70},{"Wolf",70},{"Bear",70},//
														{ "Demon", 80 } };

		const std::map<std::string, int> Villager_DodgeRate = { {"Dog",20},{"Militia",20},{"Villager",20},{"Explorer",25},{"Swordsman",25} };
		const std::map<std::string, int> Mob_DodgeRate = { {"Chicken",10} ,{"Cow",0} ,{"Rabbit",10} ,
														{"Rat",10},{"SmallSlime",10},//
														{"Skeleton",10},{"Goblin",10},{"Slime",10},//
														{"GiantRat",10},{"Wolf",10},{"Bear",10},//
														{ "Demon", 10 } };

		
	public:
		Arena(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor);
		std::vector<std::shared_ptr<BaseVillager>> m_BaseVillagers = {};
		std::vector<std::shared_ptr<Mob>> m_Mobs = {};
		virtual ~Arena() override = default;
		virtual bool CanHaveCard(std::shared_ptr<Card> otherCard) override;
		void ArrangementUpdata();
		void AddCard(std::shared_ptr<Card>& card);
		void ArenaMerge(std::shared_ptr<Arena>& card);
		void Update() override;
		void RoundAttack();
		bool CheckStatus();
	};
	
}
#endif