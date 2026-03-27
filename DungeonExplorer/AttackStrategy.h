#pragma once
#include "RollDice.h"
class AttackStrategy {
public:
	virtual ~AttackStrategy() = default;
	virtual int calculateDamage(int level) = 0;
};

class DiceAttack :public AttackStrategy {
public:
	int calculateDamage(int atk) override {
		auto& gen = MakeRandom::getGenerator();

		int diceValue = RollDice::useDice(1,6);

		int minDmg = atk * diceValue * 1;
		int maxDmg = atk * diceValue * 3;

		std::uniform_int_distribution<int> dmgDist(minDmg, maxDmg);
		return dmgDist(gen);
	}
};