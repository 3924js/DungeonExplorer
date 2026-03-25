#include "Character.h"
#include "Item.h"
#include <iostream>

Character* Character::instance = nullptr;

Character::Character(std::string n) : name(n) {
	level = 1;
	maxHealth = 200;
	health = maxHealth;
	attack = 30;
}

Character* Character::getInstance(std::string name) {
	if (instance == nullptr) {
		instance = new Character(name);
	}
	return instance;
}

void Character::displayStatus() {
	return;
}

void Character::levelUp() {
	// if already at max level
	if (level >= 10) {
		std::cout << "Can not LevelUp anymore...\n\n";
		return;
	}
	++level;
	maxHealth += 20;
	attack += 5;
	health = maxHealth;
	std::cout << "level Up!!\nCurrent Level: " << level << "\n";
	std::cout << "restored your health to full health\n\n";
}

void Character::useItem(int index) {
	return;
}