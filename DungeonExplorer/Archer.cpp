//Archer.cpp

#include "Character.h"
#include "Job.h"
#include "Archer.h"
#include <iostream>
using namespace std;

FStat Archer::GetBaseStat() const {
	//MaxHP, HP, Attack
	return { 60, 60, 40 };
}

FStat Archer::GetLevelUpBonus() const {
	//MaxHP, HP, Attack
	return { 20, 20, 20 };
}

int Archer::Skill(const Character& character) const {
	cout << "Barrage !" << endl;

	int SkillAttack = 40 + character.GetLevel() * 20;

	return SkillAttack;
}