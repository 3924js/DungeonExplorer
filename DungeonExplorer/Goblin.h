#pragma once
#include "Monster.h"
#include <string>
class Goblin :public Monster {
public:
	Goblin(std::string name, int health, int attack) :Monster(name, health, attack) {};

	virtual std::string getName() override;


	virtual int getHealth() override;


	virtual int getAttack() override;


	virtual void takeDamage(int damage) override;

	virtual int Attack() override;
};