//Wizard.cpp

#include "Character.h"
#include "Job.h"
#include "Wizard.h"
#include <iostream>
using namespace std;

FStat Wizard::GetBaseStat() const {
	//MaxHP, HP, Attack
	return { 40, 30, 50, 10 };
}

FStat Wizard::GetLevelUpBonus() const {
	//MaxHP, HP, Attack
	return { 10, 10, 20, 10 };
}

int Wizard::SkillDamage(const Character& character) const {

	int SkillAttack = 50 + character.GetLevel() * 20;

	return SkillAttack;
}

std::string Wizard::SkillName() const {
	return "Fireball !";
}