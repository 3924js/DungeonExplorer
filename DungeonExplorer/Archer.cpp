//Archer.cpp

#include "Character.h"
#include "Job.h"
#include "Archer.h"
#include <iostream>
using namespace std;

FStat Archer::GetBaseStat() const {
	//MaxHP, HP, Attack
	return { 100, 100, 40, 10 };
}

FStat Archer::GetLevelUpBonus() const {
	//MaxHP, HP, Attack
	return { 20, 20, 20, 5 };
}

int Archer::SkillDamage(const Character& character) const {

	int SkillAttack = 40 + character.GetLevel() * 20;

	return SkillAttack;
}

std::string Archer::SkillName() const {
	return "Barrage !";
}


std::string Archer::JobName() const {
	return "Archer";
}