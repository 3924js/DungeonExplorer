#pragma once 
//Character.h

#include <string>

class Character
{
public:
	static Character* GetInstance(std::string name); //YH add
	static void DestroyInstance(); //singleton instance delete

	void displayStatus() const;
	void LevelUP();

	std::string GetName() const;
	int GetLevel() const;
	int GetMaxHP() const;
	int GetMaxMP() const;
	int GetHP() const;
	int GetMP() const;
	int GetAttack() const;
	int GetEXP() const;
	int GetGold() const;	//YH add

	void SetName(std::string name);
	void SetLevel(int level);
	void SetMaxHP(int maxhp);
	void SetMaxMP(int maxmp);
	void SetHP(int hp);
	void SetMP(int mp);
	void SetAttack(int attack);
	void SetEXP(int exp);
	void SetGold(int gold);	//YH add

private:
	//Singleton Pattern
	Character(const std::string& name);  //YH move
	Character(const Character&) = delete; //YH add
	Character& operator = (const Character&) = delete; //YH add
	
	static Character* Instance; //YH add

	std::string Name;
	int Level;
	int MaxHP;
	int MaxMP;
	int HP;
	int MP;
	int Attack;
	int EXP;
	int Gold;	//YH add
};

