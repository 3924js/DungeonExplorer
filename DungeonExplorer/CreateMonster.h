#pragma once
#include <random>
#include <string>
#include "Goblin.h"
#include "MakeRandom.h"
enum class MonsterType{Goblin,Orc,Slime};

class CreateMonster {
public:
	static Monster* create(MonsterType type, std::string name, int level);
	static Monster* createGoblin(std::string name, int level);
	
};