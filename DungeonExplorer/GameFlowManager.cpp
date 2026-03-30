#include "GameFlowManager.h"
#include "GameManager.h"
#include "Character.h"
#include "LogSystem.h"
#include "BattleManager.h"
#include "StageManager.h"
#include "Job.h"
#include "Warrior.h"
#include "Wizard.h"
#include "Archer.h"
#include "Store.h"
#include <string>
#include <iostream>

using namespace std;

// Constructor
GameFlowManager::GameFlowManager() :gm(GameManager::GetInstance()), bManager(nullptr), sManager(StageManager::GetInstance()), isGameClear(false) {}

// Overall game flow
void GameFlowManager::run() {
	setupPlayer();

	while(!isGameClear) {
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

	// Select Player Jobs
	Job* playerJob = nullptr;
	string jobName;
	int jNum = 0;
	cout << "Select Player Job\n";
	cout << "1. Warrior\n2. Wizard\n3. Archer\n";
	cout << "Enter Job Number: ";
	while (!cin >> jNum) {
		cout << "InVaild Input\nEnter Job Number: ";
	}
	
	switch (jNum)
	{
	case 1:
		playerJob = new Warrior();
		jobName = "Warrior";
		break;
	case 2:
		playerJob = new Wizard();
		jobName = "Wizard";
		break;
	case 3:
		playerJob = new Archer();
		jobName = "Archer";
		break;
	default:
		break;
	}

	LogSystem::CreateCharacter(name, jobName);
	gm.createPlayer(name, playerJob);
}

// Select next path
void GameFlowManager::selectNextNode() {
	Character* player = gm.getPlayer();

	int nextNode = 0;

	while (true) {
		cout << "Choose the next path\n";
		cout << "1. Monster\n2. Store\n";
		cout << "Select next path : ";

		if (!(cin >> nextNode)) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invaild Input\n";
			continue;
		}

		if (nextNode == 1){
			battleNode();
			break;
		}
		else if (nextNode == 2) {
			storeNode();
			break;
		}

		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Invaild Input\n";
	}
}

// Generate Monster & Battle
void GameFlowManager::battleNode() {
	EStage currentStage = sManager.GetCurrentStage();
	if (currentStage == EStage::NONE) {
		sManager.SetStage(EStage::DARK_CAVE);
		currentStage = sManager.GetCurrentStage();
	}

	int level = gm.getPlayer()->GetLevel();

	if (level <= 3) {
		if (currentStage != EStage::DARK_CAVE) {
			cout << gm.getPlayer()->GetName() << " move to the DARK_CAVE\n\n";
			sManager.SetStage(EStage::DARK_CAVE);
			currentStage = sManager.GetCurrentStage();
		}
	}
	else if (level <= 6) {
		if (currentStage != EStage::DIRTY_SWAMP) {
			cout << gm.getPlayer()->GetName() << " move to the DIRTY_SWAMP\n\n";
			sManager.SetStage(EStage::DIRTY_SWAMP);
			currentStage = sManager.GetCurrentStage();
		}
	}
	else if (level <= 9) {
		cout << "Stage 3\n";
	}
	else if (level == 10) {
		bossNode();
		return;
	}

	cout << "Encounter Monster\n";
	gm.generateMonster();
	if (bManager == nullptr) {
		bManager = &BattleManager::GetInstance();
	}
	bManager->StartBattle();
}

// Enter Store
void GameFlowManager::storeNode() {
	cout << "Enter Store\n";
	Store store;
	store.InitializeStore();
	int selection;
	while (1) {
		cout << "Select Action\n";
		cout << "1. buy Item\n2. Sell Item\n3. Leave Store\n Enter Choice: ";
		cin >> selection;
		int gold = gm.getPlayer()->GetGold();
		if (selection == 1) {
			store.ShowShopMenu(gold);
			int ItemSelect;
			cout << "Enter the Item Number to Buy: ";
			cin >> ItemSelect;
			store.BuyItem(ItemSelect, gold, *gm.getInventory());
		}
		else if (selection == 2) {
			gm.getInventory()->ShowInventory();
			int ItemSelect;
			cout << "Enter the Item Number to Sell: ";
			cin >> ItemSelect;
			store.SellItem(ItemSelect, gold, *gm.getInventory());
		}
		else if (selection == 3) {
			cout << "Leave the Store\n";
			break;

		}
	}
}

// Generate Boss & Battle
void GameFlowManager::bossNode() {
	cout << "Encounter Boss\n";
	gm.generateMonster();
	if (bManager == nullptr) bManager = &BattleManager::GetInstance();
	bManager->StartBattle();
}

void GameFlowManager::gameOver() {
	cout << "Game Over\n";
	LogSystem::PlayerDied();
}

void GameFlowManager::gameClear() {
	isGameClear = true;
	LogSystem::ShowStatistics();
}