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
GameManager::GameManager(): player(nullptr), playerJob(nullptr) {
	cMonster = new CreateMonster();
	inven = new Inventory;
}

// Destructor
GameManager::~GameManager() {
	if (player != nullptr) delete player;
	if (cMonster != nullptr) delete cMonster;
	if (playerJob != nullptr) delete playerJob;
}

// Create the player only if it does not exist
void GameManager::createPlayer(string name, Job* pJob) {
	playerJob = pJob;
	player = Character::GetInstance(name, *playerJob);
}

// SingleTon - Created only once
GameManager& GameManager::GetInstance() {
	static GameManager instance;
	return instance;
}

// Create Boss Level 10
Monster* GameManager::generateBoss() {
	return cMonster->createBoss("Boss", 10);
}

// Display all items in the inventory
void GameManager::displayInventory() {
	inven->ShowInventory();
}

// Show Inventory & Use Item
void GameManager::useItem() {
	inven->ShowInventory();
	inven->UseItem();
}