#include <iostream>
#include <cstdlib>
#include "MonsterFactory.h"
#include "Goblin.h"

// Constructor
MonsterFactory::MonsterFactory() {
	// Add all Monster Class
	monsters.push_back(new Goblin("Goblin", 0, 0));
}

// create Random Monster
Monster* MonsterFactory::createRandomMonster() {
	int idx = rand()* monsters.size();
	return monsters[idx];
}