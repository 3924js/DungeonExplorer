#include "CreateMonster.h"

Monster* CreateMonster::createGoblin(std::string name, int level) {
	auto& gen = MakeRandom::getGenerator();

	std::uniform_int_distribution<int> hpDist(level * 20, level * 30);
	std::uniform_int_distribution<int> atkDist(level * 5, level * 10);
	int hp = hpDist(gen);
	int atk = atkDist(gen);

	return new Goblin(name, hp, atk);
}

Monster* CreateMonster::create(MonsterType type, std::string name, int level) {
	switch (type) {
	case MonsterType::Goblin: return createGoblin(name, level);
	}
}