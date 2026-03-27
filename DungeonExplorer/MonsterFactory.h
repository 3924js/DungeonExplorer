#pragma once
#include <vector>

class Monster;

class MonsterFactory {
private:
	std::vector<Monster*> monsters;
public:
	MonsterFactory();

	Monster* createRandomMonster();
};