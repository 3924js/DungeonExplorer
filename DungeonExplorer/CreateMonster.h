#pragma once
#include <random>
#include <string>
#include "Goblin.h"
#include "MakeRandom.h"
enum class MonsterType { Goblin, Orc, Slime, Troll, Boss };

class CreateMonster {
public:
	static Monster* create(MonsterType type, std::string name, int level);
	static Monster* createGoblin(std::string name, int level);
	static Monster* createOrc(std::string name, int level);
	static Monster* createSlime(std::string name, int level);
	static Monster* createTroll(std::string name, int level);
	static Monster* createBoss(std::string name, int level);

};