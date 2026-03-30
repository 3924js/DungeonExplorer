#include "AttackStrategy.h"

int NormalAttack::calculateDamage(int atk) {
	auto& gen = MakeRandom::getGenerator();

	int diceValue = RollDice::useDice(1, 6);

	int minDmg = atk * diceValue * 0.1;
	int maxDmg = atk * diceValue * 0.2;
	if (minDmg <= 0) minDmg = 1;
	if (maxDmg <= 0) maxDmg = 1;
	std::uniform_int_distribution<int> dmgDist(minDmg, maxDmg);
	return dmgDist(gen);
}

int SpecialAttack::calculateDamage(int atk) {
	auto& gen = MakeRandom::getGenerator();

	int diceValue = RollDice::useDice(1, 6);

	int minDmg = atk * diceValue * 0.2;
	int maxDmg = atk * diceValue * 0.3;
	if (minDmg <= 0) minDmg = 1;
	if (maxDmg <= 0) maxDmg = 1;
	std::uniform_int_distribution<int> dmgDist(minDmg, maxDmg);
	return dmgDist(gen);
}