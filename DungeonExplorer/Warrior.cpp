//Warrior.cpp

#include "Character.h"
#include "Job.h"
#include "Warrior.h"
#include <iostream>
using namespace std;

FStat Warrior::GetBaseStat() const {
	//MaxHP, HP, Attack
	return { 100, 100, 20, 60 };
}

FStat Warrior::GetLevelUpBonus() const {
	//MaxHP, HP, Attack
	return { 30, 30, 10, 20 };
}

int Warrior::SkillDamage(const Character& character) const {
	
	int SkillAttack = 20 + character.GetLevel() * 10;
	
	return SkillAttack;
}

std::string Warrior::SkillName() const {
	return "Repeating Slash !";
}