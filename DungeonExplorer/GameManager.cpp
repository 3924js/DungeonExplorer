#include <iostream>
#include <string>
#include "GameManager.h"
#include "Goblin.h"
#include "Character.h"

using namespace std;

// Constructor
GameManager::GameManager(): enemy(nullptr), player(nullptr) {
	bManager = new BattleManager();
	// Move this to another place such as main
	/*
	string name;
	cout << "Input Player Name: ";
	// Enter name allowing spces
	while(true) {
		getline(cin, name);

		//Remove leading whitespaces from the string
		size_t startBlank = name.find_first_not_of(" \t\n\r\f\v");

		// if the input contains only whitespace
		if (startBlank == string::npos) {
			cout  << "is InValid value\n Input Player Name: ";
		}
		else {
			// Store the input after removing leading whitespace
			name = name.substr(startBlank);
			cout << "Your Name is " << name << "\n";
			break;
		}
	}
	*/
}

// Destructor
GameManager::~GameManager() {
	if (enemy != nullptr) delete enemy;
	if (player != nullptr) delete player;
}

// Create the player only if it does not exist
void GameManager::createPlayer(string name) {
	if (player != nullptr) {
		cout << "The player already exists.\n ";
		return;
	}
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
	// To-Do -> The monster type will be determined based on the player's current level
	if (enemy == nullptr && player != nullptr) enemy = new Goblin("Goblin", 0, 0);
}

void GameManager::battle() {
	if (enemy == nullptr) {
		// 1. print a message and end the function
		cout << "There is no Monster to Fight.\n";
		return;

		// 2. create monster and start the battle
		//generateMonster();
	}
	bManager->StartBattle(*player, *enemy);
}

// Display all items in the inventory
void GameManager::displayInventory() {
	// use this after the inventory has benn added to the Character class
	//player->getInven().ShowInventory();
}