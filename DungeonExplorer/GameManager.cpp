#include <iostream>
#include <string>
#include "GameManager.h"
#include "Character.h"
#include "MonsterFactory.h"

using namespace std;

// Constructor
GameManager::GameManager(): enemy(nullptr), player(nullptr) {
	mFactory = new MonsterFactory();
}

// Destructor
GameManager::~GameManager() {
	if (enemy != nullptr) delete enemy;
	if (player != nullptr) delete player;
	if (mFactory != nullptr) delete mFactory;
}

// Create the player only if it does not exist
void GameManager::createPlayer(string name) {
	player = new Character(name);
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
	if (enemy == nullptr && player != nullptr) enemy = mFactory->createRandomMonster();
}

// Display all items in the inventory
void GameManager::displayInventory() {
	// use this after the inventory has benn added to the Character class
	//player->getInven().ShowInventory();
}