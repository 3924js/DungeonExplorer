#include <iostream>
#include "BattleManager.h"
#include "Goblin.h"
#include "Monster.h"

using namespace std;

int main() {
	//cout << "던전 탐험대" << endl;
	std::vector<Monster*> monster;
	monster.push_back(new Goblin("Goblin1" , 30, 10));
	monster.push_back(new Goblin("Goblin2" , 30, 10));
	monster.push_back(new Goblin("Goblin3" , 30, 10));
	
	BattleManager::GetInstance().StartBattle(monster);
	
	
}