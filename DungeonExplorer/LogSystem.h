//LogSystem.h
#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>

//Statistics enum
enum IntStatTypes {
	TOTAL_BATTLES,
	ATTACKS,
	DEALT_DAMAGE,
	TAKEN_DAMAGE,
	KILLED_MONSTERS,
	EARNED_MONEY,
	BOUGHT_ITEM,
	USED_ITEM,
	ROLLED_DICE,
	COUNT
};
static const std::string IntStatNames[IntStatTypes::COUNT] = { "Total Battles",
															"Attacks",
															"Dealt Damage",
															"Taken Damage",
															"Killed Monsters",
															"Earned Money",
															"Bought Items",
															"Used Items",
															"Rolled Dice" };

//Log Management Class
class LogSystem {
private:
	//Singleton 
	static LogSystem& GetInstance() {
		static LogSystem Instance;
		return Instance;
	}
	//Constructor
	LogSystem(){
		//Initialize all integer statistics values
		for (int i = 0; i < IntStatTypes::COUNT; i++) Stats[i] = 0;
	}
	//Destructor
	~LogSystem() = default;

	//Statistics variables
	int Stats[IntStatTypes::COUNT];
	std::map<std::string, int> MonstersEncountered;
	std::map<std::string, int> MonstersKilled;

	//print message separation line in the console
	static void PrintLine() {
		std::cout << "= = = = = = = = = = = = = = = = = = = = " << std::endl;
	}
public:
	static void EnterBattle(std::vector<std::string> monsters) {
		std::cout << ">>> The player encounters enemies!" << std::endl;
		GetInstance().Stats[IntStatTypes::TOTAL_BATTLES]++;
		for (std::string name : monsters) {
			std::cout << "-> " << name << " is preparing for a battle!" << std::endl;
			GetInstance().MonstersEncountered[name]++;
		}
		PrintLine();
	}

	/*Replace after Monster class added
	static void EnterBattle(const std::vector<Monster>& monsters) {
		std::cout << ">>> The player encounters enemies!" << std::endl;
		GetInstance().Stats[IntStatTypes::TOTAL_BATTLES]++;
		for (Monster monster : monsters) {
			std::cout << "-> " << monster.GetName() << " is preparing for a battle!" << std::endl;
			GetInstance().MonsterEncountered[name]++;
		}
		PrintLine();
	}
	}*/

	static void AttackMonster(std::string monsterName, int Damage) {
		std::cout << ">>> The player attacks the monster " << monsterName << "!" << std::endl;
		std::cout << "-> The Monster has taken "<< Damage << " damage!" << std::endl;
		GetInstance().Stats[IntStatTypes::ATTACKS]++;
		GetInstance().Stats[IntStatTypes::DEALT_DAMAGE] += Damage;
		PrintLine();
	}
	/*Replace after Monster class added
	static void AttackMonster(const Monster& monster, int Damage) {
		std::cout << ">>> The player attacks the monster " << monster.GetName() << "!" << std::endl;
		std::cout << "-> The Monster has taken "<< Damage << " damage!" << std::endl;
		GetInstance().Stats[IntStatTypes::ATTACKS]++;
		GetInstance().Stats[IntStatTypes::DEALT_DAMAGE]++;
		PrintLine();
	}
	}*/

	static void AttackPlayer(std::string monsterName, int Damage) {
		std::cout << ">>> The monster " << monsterName << " attacks the player!" << std::endl;
		std::cout << "-> The player has taken " << Damage << " damage!" << std::endl;
		GetInstance().Stats[IntStatTypes::TAKEN_DAMAGE] += Damage;
		PrintLine();
	}
	/*Replace after Monster class added
	static void AttackPlayer(const Monster& monster, int Damage) {
		std::cout << ">>> The monster " << monster.GetName() << " attacks the player!" << std::endl;
		std::cout << "-> The player has taken " << Damage << " damage!" << std::endl;
		GetInstance().Stats[IntStatTypes::TAKEN_DAMAGE]++;
		PrintLine();
	}
	}*/

	static void KillMonster(std::string monsterName) {
		std::cout << ">>> The player has defeated the monster " << monsterName << "!" << std::endl;
		GetInstance().MonstersKilled[monsterName]++;
		PrintLine();
	}
	/*Replace after Monster class added
	static void KillMonster(const Monster& monster) {
		std::cout << ">>> The player has defeated the monster " << monster.GetName() << "!" << std::endl;
		GetInstance().MonsterKilled[monsterName]++;
		PrintLine();
	}*/

	static void BuyItem(std::string name) {	//Change needed if statistics counts each item separately.
		std::cout << ">>> The player Bought the item " << name << "!" << std::endl;
		GetInstance().Stats[IntStatTypes::BOUGHT_ITEM]++;
		PrintLine();
	}

	/*Replace after item class added
	static void BuyItem(Item item) {	//Change needed if statistics counts each item separately.
		std::cout << ">>> The player Bought the item " << item.GetName() << "!" << std::endl;
		GetInstance().Stats[IntStatTypes::BOUGHT_ITEM]++;
		PrintLine();
	}
	}*/

	static void UseItem(std::string name) {	//Change needed if statistics counts each item separately.
		std::cout << ">>> The player used the item " << name << "!" << std::endl;
		GetInstance().Stats[IntStatTypes::USED_ITEM]++;
		PrintLine();
	}
	
	/*Replace after item class added
	static void UseItem(Item item) {
		std::cout << ">>> The player used the item " << item.GetName() << "!" << std::endl;
		GetInstance().Stats[IntStatTypes::USED_ITEM]++;
		PrintLine();
	}
	}*/

	static void PlayerDied() {	//Change needed if statistics counts each item separately.
		std::cout << ">>> The player has defeated!" << std::endl;
		PrintLine();
	}

	static void ShowStatistics() {
		LogSystem& Instance = LogSystem::GetInstance();
		std::cout << ">>> Gameplay Statistics" << std::endl;

		//show int stats
		for (int i = 0; i < IntStatTypes::COUNT; i++) {
			std::cout << "-> " << IntStatNames[i] << ": " << Instance.Stats[i]<< std::endl;
		}
		std::cout << std::endl;

		//show monster encountered
		std::cout << "--> Monsters Encountered" << std::endl;
		for (auto i = Instance.MonstersEncountered.begin(); i != Instance.MonstersEncountered.end() ; i++) {
			std::cout << "-> " << i->first << ": " << i->second <<  " times" << std::endl;
		}
		std::cout << std::endl;

		//show monster killed
		std::cout << "--> Monsters Killed" << std::endl;
		for (auto i = Instance.MonstersKilled.begin(); i != Instance.MonstersKilled.end(); i++) {
			std::cout << "-> " << i->first << ": " << i->second << " times" << std::endl;
		}
		std::cout << std::endl;
		
		PrintLine();
	}
};