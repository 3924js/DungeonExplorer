#pragma once
#include <string>

class Monster {
protected:
	std::string name;
	int health;
	int attack;

public:
	Monster(std::string name, int health, int attack) :name(name), health(health), attack(attack) {};
	virtual std::string getName() = 0;
	virtual int getHealth() = 0;
	virtual int getAttack() = 0;
	virtual void takeDamage(int damage) = 0;
	virtual ~Monster() = default;
};