#include "CreateMonster.h"

Monster* CreateMonster::createGoblin(std::string name, int level) {
	auto& gen = MakeRandom::getGenerator();

	std::uniform_int_distribution<int> hpDist(level * 20, level * 30);
	std::uniform_int_distribution<int> atkDist(level * 5, level * 10);
	int hp = hpDist(gen);
	int atk = atkDist(gen);

	auto normalAttack = std::make_unique<NormalAttack>();

	return new Goblin(name, hp, atk, std::move(normalAttack));
}

Monster* CreateMonster::createOrc(std::string name, int level) {
	auto& gen = MakeRandom::getGenerator();

	std::uniform_int_distribution<int> hpDist(level * 20, level * 30);
	std::uniform_int_distribution<int> atkDist(level * 5, level * 10);
	int hp = hpDist(gen);
	int atk = atkDist(gen);

	auto normalAttack = std::make_unique<NormalAttack>();

	return new Orc(name, hp, atk, std::move(normalAttack));
}

Monster* CreateMonster::createSlime(std::string name, int level) {
	auto& gen = MakeRandom::getGenerator();

	std::uniform_int_distribution<int> hpDist(level * 20, level * 30);
	std::uniform_int_distribution<int> atkDist(level * 5, level * 10);
	int hp = hpDist(gen);
	int atk = atkDist(gen);

	auto normalAttack = std::make_unique<NormalAttack>();

	return new Slime(name, hp, atk, std::move(normalAttack));
}

Monster* CreateMonster::createTroll(std::string name, int level) {
	auto& gen = MakeRandom::getGenerator();

	std::uniform_int_distribution<int> hpDist(level * 20, level * 30);
	std::uniform_int_distribution<int> atkDist(level * 5, level * 10);
	int hp = hpDist(gen);
	int atk = atkDist(gen);

	auto normalAttack = std::make_unique<NormalAttack>();

	return new Troll(name, hp, atk, std::move(normalAttack));
}

Monster* CreateMonster::createBoss(std::string name, int level) {
	auto& gen = MakeRandom::getGenerator();

	std::uniform_int_distribution<int> hpDist(level * 30, level * 40);
	std::uniform_int_distribution<int> atkDist(level * 7, level * 12);
	int hp = hpDist(gen);
	int atk = atkDist(gen);

	auto normalAttack = std::make_unique<NormalAttack>();

	return new Boss(name, hp, atk, std::move(normalAttack));
}

Monster* CreateMonster::create(MonsterType type, std::string name, int level) {
	switch (type) {
	case MonsterType::Goblin: return createGoblin(name, level);
	case MonsterType::Orc: return createOrc(name, level);
	case MonsterType::Slime: return createSlime(name, level);
	case MonsterType::Troll: return createTroll(name, level);
	}
}