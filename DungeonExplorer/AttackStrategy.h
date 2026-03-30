#pragma once
#include "RollDice.h"
class AttackStrategy {
public:
	virtual ~AttackStrategy() = default;
	virtual int calculateDamage(int atk) = 0;
};

class NormalAttack :public AttackStrategy {
public:
	virtual int calculateDamage(int atk) override;
};

class SpecialAttack :public AttackStrategy {
public:
	virtual int calculateDamage(int atk) override;
};