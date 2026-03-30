//Warrior.cpp

#include "Character.h"
#include "Job.h"
#include "Warrior.h"
#include <iostream>
using namespace std;

FStat Warrior::GetBaseStat() const {
	//MaxHP, HP, Attack, Defense
	return { 150, 150, 30, 10 };
}

FStat Warrior::GetLevelUpBonus() const {
	//MaxHP, HP, Attack, Defense
	return { 50, 50, 10, 10 };
}

int Warrior::SkillDamage(const Character& character) const {
	
	int SkillAttack = 30 + character.GetLevel() * 10;
	
	return SkillAttack;
}

std::string Warrior::SkillName() const {
	return "Repeating Slash !";
}

std::string Warrior::JobName() const {
	return "Warrior";
}