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
GameFlowManager::GameFlowManager() :
	gm(GameManager::GetInstance()), 
	bManager(nullptr), 
	sManager(StageManager::GetInstance())
	{}

// Overall game flow
void GameFlowManager::run() {
	setupPlayer();

	while(!gm.getIsGameClear()) {
		if (gm.getPlayer()->GetHP() > 0) {
			selectNextNode();
		}
		else break;
	}
	
	if (gm.getIsGameClear()) gameClear();
	else gameOver();
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
			break;
		}
	}

	// Select Player Jobs
	string jobName;
	int jNum = 0;
	cout << "\nSelect Player Job\n";
	cout << "1. Warrior\n2. Wizard\n3. Archer\n";
	cout << "Enter Job Number: ";
	while (!(cin >> jNum)) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "InVaild Input\nEnter Job Number: ";
	}
	
	Job* playerJob = nullptr;
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
		cout << "\nChoose the next Action\n";
		cout << "1. Fight Monster\n2. Enter Store\n3. Show Status\n";
		cout << "Select next path : ";

		// Guard Invalid Input
		if (!(cin >> nextNode)) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid Input\n";
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
		else if (nextNode == 3) {
			gm.getPlayer()->displayStatus();
			break;
		}

		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Invaild Input\n";
	}
}

// Generate Monster & Battle
void GameFlowManager::battleNode() {
	// Initialize Stage
	EStage currentStage = sManager.GetCurrentStage();
	if (currentStage == EStage::NONE) {
		sManager.SetStage(EStage::DARK_CAVE);
		currentStage = sManager.GetCurrentStage();
	}

	int level = gm.getPlayer()->GetLevel();

	// Select Stage
	if (level <= 3) {
		if (currentStage != EStage::DARK_CAVE) {
			cout << gm.getPlayer()->GetName() << " move to the Dark_Cave\n\n";
			sManager.SetStage(EStage::DARK_CAVE);
		}
	}
	else if (level <= 6) {
		if (currentStage != EStage::DIRTY_SWAMP) {
			cout << gm.getPlayer()->GetName() << " move to the Dirty_Swamp\n\n";
			sManager.SetStage(EStage::DIRTY_SWAMP);
		}
	}
	else if (level <= 9) {
		cout << "Stage 3\n";
		if (currentStage != EStage::MISTY_FOREST) {
			cout << gm.getPlayer()->GetName() << " move to the Misty  Fores\n\n";
			sManager.SetStage(EStage::MISTY_FOREST);
		}
	}
	else if (level == 10) {
		bossNode();
		return;
	}

	// Start Battle
	if (bManager == nullptr) {
		bManager = &BattleManager::GetInstance();
	}
	bManager->StartBattle();
	
	// Player Level Up
	if (gm.getPlayer()->GetEXP() >= 100) {
		string job = gm.getPlayer()->GetCurrentJob();
		Job* playerJob = gm.getPlayerJob();
		
		if (playerJob != nullptr) {
			gm.getPlayer()->LevelUP(*playerJob);
		}
	}
}

// Enter Store
void GameFlowManager::storeNode() {
	cout << "\nEnter Store\n";
	// Change to LogSystem Lobby

	// Restore HP to maxHP;
	int maxHp = gm.getPlayer()->GetMaxHP();
	gm.getPlayer()->SetHP(maxHp);

	// Initialize Store
	ItemManager::GetInstance().Initialize();
	Store store;
	store.InitializeStore();

	int selection;
	while (1) {
		cout << "\nSelect Action\n";
		cout << "1. buy Item\n2. Sell Item\n3. Leave Store\nEnter Choice: ";
		cin >> selection;
		int gold = gm.getPlayer()->GetGold();
		// Show Store Item & Buy Item
		if (selection == 1) {
			store.ShowShopMenu(gold);
			int ItemSelect;
			cout << "Enter the Item Number to Buy: ";
			cin >> ItemSelect;
			store.BuyItem(ItemSelect, gold, *gm.getInventory());
		}
		// Show Inventory & Sell Item
		else if (selection == 2) {
			gm.getInventory()->ShowInventory();
			int ItemSelect;
			cout << "Enter the Item Number to Sell: ";
			cin >> ItemSelect;
			store.SellItem(ItemSelect, gold, *gm.getInventory());
		}
		// Leave Store
		else if (selection == 3) {
			cout << "\nLeave the Store\n";
			break;

		}
	}
}

// Generate Boss & Battle
void GameFlowManager::bossNode() {
	cout << "\nEncounter Boss\n";
	Monster* boss = gm.generateBoss();
	if (bManager == nullptr) bManager = &BattleManager::GetInstance();
	bManager->StartBossBattle(boss);
}

void GameFlowManager::gameOver() {
	LogSystem::PlayerDied();
	LogSystem::ShowStatistics();
}

void GameFlowManager::gameClear() {
	LogSystem::ShowStatistics();
}