#pragma once
#include <string>
#include "AttackStrategy.h"
class Monster {
protected:
	std::string name;
	int health;
	int attack;
	AttackStrategy* attackStrategy;

public:
	Monster(std::string name, int health, int attack, AttackStrategy* attackStrategy) :name(name), health(health), attack(attack),attackStrategy(attackStrategy) {};
	virtual std::string getName() = 0;
	virtual int getHealth() = 0;
	virtual int getAttack() = 0;
	virtual void takeDamage(int damage) = 0;
	virtual int Attack() = 0;
	virtual ~Monster() = default;
};