#include <iostream>
#include "BattleManager.h"
#include "StageManager.h"
#include "Character.h"
#include "ItemManager.h"

using namespace std;

int main() {
	//cout << "던전 탐험대" << endl;
	ItemManager::GetInstance().Initialize();
	StageManager::GetInstance().SetStage(DARK_CAVE);
	
	BattleManager::GetInstance().StartBattle();
	
	Character::GetInstance()->GetInventory().ShowInventory();
}