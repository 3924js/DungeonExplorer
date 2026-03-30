//Warrior.h
#pragma once

#include "Stat.h"

class Character;

class Job;

class Warrior : public Job
{
public:
	virtual FStat GetBaseStat() const;
	virtual FStat GetLevelUpBonus() const;
	virtual int Skill(const Character& character) const;
};