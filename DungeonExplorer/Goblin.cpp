#include "Goblin.h"

std::string Goblin::getName() {
	return name;
}

int Goblin::getHealth() {
	return health;
}

int Goblin::getAttack() {
	return attack;
}

void Goblin::takeDamage(int damage) {
	health -= damage;
}