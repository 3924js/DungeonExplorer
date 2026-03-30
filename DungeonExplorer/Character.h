//Character.h
#pragma once 

#include "Stat.h"
#include <string>


class Job;

class Character
{
public:
	static Character* GetInstance(const std::string& name, const Job& job);
	static void DestroyInstance(); //singleton instance delete

	void displayStatus() const;
	void LevelUP(const Job& job);

	std::string GetName() const;
	int GetLevel() const;
	int GetMaxHP() const;
	//int GetMaxMP() const;
	int GetHP() const;
	//int GetMP() const;
	int GetAttack() const;
	int GetEXP() const;
	int GetGold() const;

	//void SetName(std::string name);
	//void SetLevel(int level);
	//void SetMaxHP(int maxhp);
	//void SetMaxMP(int maxmp);
	void SetHP(int hp);
	//void SetMP(int mp);
	//void SetAttack(int attack);
	void SetEXP(int exp);
	void SetGold(int gold);

private:
	//Singleton Pattern
	Character(const std::string& name, const Job& job); 
	Character(const Character&) = delete;
	Character& operator = (const Character&) = delete;
	
	static Character* Instance;

	std::string Name;
	int Level;
	FStat stat; //MaxHP, HP, Attack
	int EXP;
	int Gold;
};