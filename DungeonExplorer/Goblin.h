#pragma once
#include "Monster.h"
#include <string>
class Goblin :public Monster {
public:
	Goblin(std::string name, int health, int attack) :Monster(name, health, attack) {
		health = 10;
		attack = 20;
	};

	virtual std::string getName() override;


	virtual int getHealth() override;


	virtual int getAttack() override;


	virtual void takeDamage(int damage) override;

};