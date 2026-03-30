#include <iostream>
#include <string>
#include "GameManager.h"
#include "Character.h"
#include "CreateMonster.h"
#include "Inventory.h"
#include "Job.h"
#include "Warrior.h"

using namespace std;

// Constructor
GameManager::GameManager(): enemy(nullptr), player(nullptr) {
	cMonster = new CreateMonster();
	inven = new Inventory;
}

// Destructor
GameManager::~GameManager() {
	if (enemy != nullptr) delete enemy;
	if (player != nullptr) delete player;
	if (cMonster != nullptr) delete cMonster;
}

// Create the player only if it does not exist
void GameManager::createPlayer(string name, Job* pJob) {
	Job* job = pJob;
	player = Character::GetInstance(name, *job);
	delete job;
}

// SingleTon - Created only once
GameManager& GameManager::GetInstance() {
	static GameManager instance;
	return instance;
}

void GameManager::generateMonster(int level) {
	// if no level is given, use the player's level
	if (level == 0) level = player->GetLevel();

	// Create a monster only if there is no current monster
	if (enemy == nullptr && player != nullptr) {
		MonsterType newMonster;
		string MonsterName;
		if (level <= 3) {
			newMonster = MonsterType::Slime;
			MonsterName = "Slime";
		}
		else if (level <= 6) {
			newMonster = MonsterType::Goblin;
			MonsterName = "Goblin";
		}
		else if (level <= 9){
			newMonster = MonsterType::Orc;
			MonsterName = "Orc";
		}
		else {
			cMonster->createBoss("Boss", level);
			return;
		}
		cMonster->create(newMonster, MonsterName, level);
	}

}

// Display all items in the inventory
void GameManager::displayInventory() {
	// use this after the inventory has benn added to the Character class
	inven->ShowInventory();
}

void GameManager::useItem() {
	inven->ShowInventory();
	inven->UseItem();
}