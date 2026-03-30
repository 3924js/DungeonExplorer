#include "AttackStrategy.h"

int NormalAttack::calculateDamage(int atk) {
	auto& gen = MakeRandom::getGenerator();

	int diceValue = RollDice::useDice(1, 6);

	int minDmg = atk * diceValue * 0.05;
	int maxDmg = atk * diceValue * 0.1;
	std::uniform_int_distribution<int> dmgDist(minDmg, maxDmg);
	return dmgDist(gen);
}

int SpecialAttack::calculateDamage(int atk) {
	auto& gen = MakeRandom::getGenerator();

	int diceValue = RollDice::useDice(1, 6);

	int minDmg = atk * diceValue * 0.2;
	int maxDmg = atk * diceValue * 0.5;
	std::uniform_int_distribution<int> dmgDist(minDmg, maxDmg);
	return dmgDist(gen);
}