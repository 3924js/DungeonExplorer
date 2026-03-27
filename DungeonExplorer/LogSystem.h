//LogSystem.h
#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "Character.h"
#include "Monster.h"
#include "Item.h"
#include "iomanip"


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
	TOTAL_SPOTS,
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
															"Rolled Dice",
															"Total Spots" };
//Text Hightlight Formats
namespace TextFormat {
	const std::string DEFAULT = "\033[0m";
	//bold, italic, underline, color
	const std::string RED = "\033[1;3;4;91m";
	const std::string GREEN = "\033[1;3;4;92m";
	const std::string YELLOW = "\033[1;3;4;93m";
	const std::string BLUE = "\033[1;3;4;94m";
	const std::string MAGENTA = "\033[1;3;4;95m";
	const std::string CYAN = "\033[1;3;4;96m";
	const std::string WHITE = "\033[1;3;4;97m";
}
static std::string GetHighlightColor(const Item& i) {
	switch (i.rarity) {
	case Rarity::Common:
		return TextFormat::BLUE;
	case Rarity::Rare:
		return TextFormat::MAGENTA;
	case Rarity::Legendary:
		return TextFormat::YELLOW;
	default:
		return TextFormat::DEFAULT;
	}
}

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
		std::cout << TextFormat::GREEN << "------------------------------" << TextFormat::DEFAULT << std::endl;
	}
public:
	/* Previous String Version
	static void EnterBattle(std::vector<std::string> monsters) {
		std::cout << ">>> The player encounters enemies!" << std::endl;
		GetInstance().Stats[IntStatTypes::TOTAL_BATTLES]++;
		for (std::string name : monsters) {
			std::cout << "-> " << name << " is preparing for a battle!" << std::endl;
			GetInstance().MonstersEncountered[name]++;
		}
		PrintLine();
	}*/

	static void EnterBattle(const std::vector<Monster*>& monsters) {
		std::cout << ">>> The player encounters enemies!" << std::endl;
		GetInstance().Stats[IntStatTypes::TOTAL_BATTLES]++;
		for (Monster* monster : monsters) {
			std::cout << "-> " << TextFormat::RED << monster->getName() << TextFormat::DEFAULT << " is preparing for a battle!" << std::endl;
			GetInstance().MonstersEncountered[monster->getName()]++;
		}
		PrintLine();
	}
	
	/* Previous String Version
	static void AttackMonster(std::string monsterName, int Damage) {
		std::cout << ">>> The player attacks the monster " << monsterName << "!" << std::endl;
		std::cout << "-> The Monster has taken "<< Damage << " damage!" << std::endl;
		GetInstance().Stats[IntStatTypes::ATTACKS]++;
		GetInstance().Stats[IntStatTypes::DEALT_DAMAGE] += Damage;
		PrintLine();
	}*/

	static void AttackMonster(Monster* monster, int Damage) {
		std::cout << ">>> The player attacks the monster " << TextFormat::RED << monster->getName() << TextFormat::DEFAULT << "!" << std::endl;
		std::cout << "-> The Monster has taken "<< Damage << " damage!" << std::endl;
		GetInstance().Stats[IntStatTypes::ATTACKS]++;
		GetInstance().Stats[IntStatTypes::DEALT_DAMAGE] += Damage;
		PrintLine();
	}

	/* Previous String Version
	static void AttackPlayer(std::string monsterName, int Damage) {
		std::cout << ">>> The monster " << monsterName << " attacks the player!" << std::endl;
		std::cout << "-> The player has taken " << Damage << " damage!" << std::endl;
		GetInstance().Stats[IntStatTypes::TAKEN_DAMAGE] += Damage;
		PrintLine();
	}*/

	static void AttackPlayer(Monster* monster, int Damage) {
		std::cout << ">>> The monster " << TextFormat::RED << monster->getName() << TextFormat::DEFAULT << " attacks the player!" << std::endl;
		std::cout << "-> The player has taken " << Damage << " damage!" << std::endl;
		GetInstance().Stats[IntStatTypes::TAKEN_DAMAGE] += Damage;
		PrintLine();
	}
	/* Previous String Version
	static void KillMonster(std::string monsterName) {
		std::cout << ">>> The player has defeated the monster " << monsterName << "!" << std::endl;
		GetInstance().MonstersKilled[monsterName]++;
		PrintLine();
	}*/

	static void KillMonster(Monster* monster) {
		std::cout << ">>> The player has defeated the monster " << TextFormat::RED << monster->getName() << TextFormat::DEFAULT << "!" << std::endl;
		GetInstance().MonstersKilled[monster->getName()]++;
		PrintLine();
	}

	/* Previous String Version
	static void BuyItem(std::string name) {	//Change needed if statistics counts each item separately.
		std::cout << ">>> The player Bought the item " << name << "!" << std::endl;
		GetInstance().Stats[IntStatTypes::BOUGHT_ITEM]++;
		PrintLine();
	}*/

	static void GetReward(int Exp, int Gold, const std::vector<Item>& Items) {
		std::cout << ">>> The player gets the rewards!" << std::endl;
		std::cout << "-> Earend experience point: " << Exp << std::endl;
		std::cout << "-> Earned gold: " << Exp << std::endl;
		for (Item i : Items) {
			std::cout << "-> Collected an item: " << GetHighlightColor(i) << i.name << TextFormat::DEFAULT << std::endl;
		}
		PrintLine();
	}

	static void BuyItem(Item item) {	//Change needed if statistics counts each item separately.

		std::cout << ">>> The player Bought the item " << GetHighlightColor(item) << item.name << TextFormat::DEFAULT << "!" << std::endl;
		GetInstance().Stats[IntStatTypes::BOUGHT_ITEM]++;
		PrintLine();
	}

	/* Previous String Version
	static void UseItem(std::string name) {	//Change needed if statistics counts each item separately.
		std::cout << ">>> The player used the item " << name << "!" << std::endl;
		GetInstance().Stats[IntStatTypes::USED_ITEM]++;
		PrintLine();
	}*/
	
	static void UseItem(Item item) {
		std::cout << ">>> The player used the item " << GetHighlightColor(item) << item.name << TextFormat::DEFAULT << "!" << std::endl;
		GetInstance().Stats[IntStatTypes::USED_ITEM]++;
		PrintLine();
	}

	static void ShowItems(std::vector<Item> Items) {
		std::cout << ">>> There are some items... " << std::endl;
		for (Item i : Items) {
			std::cout << "-> " << GetHighlightColor(i) << i.name << TextFormat::DEFAULT
				//<< std::setw(15 - i.name.size()) << i.rarity
				//<< std::setw(15 - i.name.size()) << i.type
				<< std::setw(15 - i.name.size()) << i.value << " Gold(s): "
				<< i.desc
				<< std::endl;
		}
		PrintLine();
	}

	static void PlayerDied() {	//Change needed if statistics counts each item separately.
		std::cout << ">>> The player has defeated!" << std::endl;
		PrintLine();
	}

	static void RollDice(int spots) {
		std::cout << ">>> Dice has rolled: " << spots << std::endl;
		GetInstance().Stats[IntStatTypes::ROLLED_DICE]++;
		GetInstance().Stats[IntStatTypes::TOTAL_SPOTS] += spots;
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