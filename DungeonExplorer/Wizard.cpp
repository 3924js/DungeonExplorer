//Wizard.cpp

#include "Character.h"
#include "Job.h"
#include "Wizard.h"
#include <iostream>
using namespace std;

FStat Wizard::GetBaseStat() const {
	//MaxHP, HP, Attack
	return { 30, 30, 50 };
}

FStat Wizard::GetLevelUpBonus() const {
	//MaxHP, HP, Attack
	return { 10, 10, 20 };
}

int Wizard::Skill(const Character& character) const {
	cout << "Fireball !" << endl;

	int SkillAttack = 50 + character.GetLevel() * 20;

	return SkillAttack;
}