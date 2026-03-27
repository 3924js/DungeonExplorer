#include "GameFlowManager.h"
#include "GameManager.h"
#include "Character.h"
#include "LogSystem.h"
#include "BattleManager.h"
#include <string>
#include <iostream>

using namespace std;

// Constructor
GameFlowManager::GameFlowManager() :gm(GameManager::GetInstance()), bManager(nullptr), isGameClear(false) {}

// Overall game flow
void GameFlowManager::run() {
	setupPlayer();

	while(isGameClear) {
		if (gm.getPlayer()->GetHP() > 0) {
			selectNextNode();
		}
		else {
			gameOver();
		}
	}
	
	gameClear();
}

// Input Player Name & create Player
void GameFlowManager::setupPlayer() {
	string name;
	cout << "Input Player Name: ";

	// Enter name allowing spces
	while (true) {
		getline(cin, name);

		//Remove leading whitespaces from the string
		size_t startBlank = name.find_first_not_of(" \t\n\r\f\v");

		// if the input contains only whitespace
		if (startBlank == string::npos) {
			cout << "is InValid value\n Input Player Name: ";
		}
		else {
			// Store the input after removing leading whitespace
			name = name.substr(startBlank);
			cout << "Your Name is " << name << "\n";
			break;
		}
	}

	gm.createPlayer(name);
}

// Select next path
void GameFlowManager::selectNextNode() {
	Character* player = gm.getPlayer();

	int nextNode = 0;
	int currentLevel = player->GetLevel();
	bool canBossSelect = currentLevel > 5;

	while (true) {
		cout << "Select Next path\n";
		cout << "1. Monster\n2. Store\n";
		if (canBossSelect) cout << "3. Boss\n";
		cout << "Select next path : ";

		if (!(cin >> nextNode)) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invaild Input\n";
			continue;
		}

		if (nextNode == 1 || nextNode == 2 || (nextNode == 3 && canBossSelect)){
			break;
		}

		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Invaild Input\n";
	}

	switch (nextNode)
	{
	case 1:
		battleNode();
		break;
	case 2:
		storeNode();
		break;
	case 3:
		bossNode();
		break;
	default:
		break;
	}
}

// Generate Monster & Battle
void GameFlowManager::battleNode() {
	cout << "Encounter Monster\n";
	gm.generateMonster();
	if (bManager == nullptr) bManager = new BattleManager();
	bManager->StartBattle(*gm.getPlayer(), *gm.getEnemy());
}

// Enter Store
void GameFlowManager::storeNode() {
	cout << "Enter Store\n";
	// after Store Mergy
}

// Generate Boss & Battle
void GameFlowManager::bossNode() {
	cout << "Encounter Boss\n";
	gm.generateMonster();
	if (bManager == nullptr) bManager = new BattleManager();
	bManager->StartBattle(*gm.getPlayer(), *gm.getEnemy());
}

void GameFlowManager::gameOver() {
	cout << "Game Over\n";
	LogSystem::PlayerDied();
}

void GameFlowManager::gameClear() {
	isGameClear = true;
	LogSystem::ShowStatistics();
}