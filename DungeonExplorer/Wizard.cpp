//Wizard.cpp

#include "Character.h"
#include "Job.h"
#include "Wizard.h"
#include <iostream>
using namespace std;

FStat Wizard::GetBaseStat() const {
	//MaxHP, HP, Attack
	return { 50, 50, 50, 5 };
}

FStat Wizard::GetLevelUpBonus() const {
	//MaxHP, HP, Attack
	return { 10, 10, 20, 5 };
}

int Wizard::SkillDamage(const Character& character) const {

	int SkillAttack = 60 + character.GetLevel() * 30;

	return SkillAttack;
}

std::string Wizard::SkillName() const {
	return "Fireball !";
}

std::string Wizard::JobName() const {
	return "Wizard";
}
