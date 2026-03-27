//Character.cpp

#include "Character.h"
#include <iostream>

//constructor
Character::Character(const std::string& name) : Name(name), Level(1), MaxHP(200), MaxMP(100), Attack(30), EXP(0), Gold(0) {
	HP = GetMaxHP();
	MP = GetMaxMP();
}

//Singleton Pattern, YH add
Character* Character::Instance = nullptr;

Character* Character::GetInstance(std::string name) {
	if (Instance == nullptr) {
		Instance = new Character(name);
	}
	return Instance;
}

//singleton instance delete, YH add
void Character::DestroyInstance() {
	delete Instance;
	Instance = nullptr;
}


//Status View
void Character::displayStatus() const {
	std::cout << std::endl;
	std::cout << "[Status]" << std::endl;
	std::cout << "Name: " << Name << std::endl;
	std::cout << std::endl;
	std::cout << "Level:" << Level << std::endl;
	std::cout << "EXP: " << EXP << std::endl;
	std::cout << std::endl;
	std::cout << "HP: " << HP << "/" << MaxHP << std::endl;
	std::cout << "MP: " << MP << "/" << MaxMP << std::endl;
	std::cout << "Attack: " << Attack << std::endl;
	std::cout << std::endl;	//YH add
	std::cout << "Gold: " << Gold << std::endl;	//YH add
}

//Level UP
void Character::LevelUP() {
	if (EXP >= 100) {
		++Level;
		EXP = EXP - 100;
	}
}


//Getter
std::string Character::GetName() const { return Name; }
int Character::GetLevel() const { return Level; }
int Character::GetMaxHP() const { return MaxHP; }
int Character::GetMaxMP() const { return MaxMP; }
int Character::GetHP() const { return HP; }
int Character::GetMP() const { return MP; }
int Character::GetAttack() const { return Attack; }
int Character::GetEXP() const { return EXP; }
int Character::GetGold() const { return Gold; }	//YH add


//Setter
void Character::SetName(std::string name) {
	Name = name;
}
void Character::SetLevel(int level) {
	//level underflow prevention
	if (level < 1) {
		level = 1;
	}
	if (Level < level) {
		Level = level;
	}
}
void Character::SetMaxHP(int maxhp) {
	if (maxhp < 0) {
		maxhp = 0;
	}
}
void Character::SetMaxMP(int maxmp) {

}
void Character::SetHP(int hp) {
	//HP underflow/overflow prevention
	if (hp < 0) {
		hp = 0;
	}
	else if (MaxHP < hp) {
		hp = MaxHP;
	}
	HP = hp;
}
void Character::SetMP(int mp) {
	//MP underflow/overflow prevention
	if (mp < 0) {
		mp = 0;
	}
	else if (MaxMP < mp) {
		mp = MaxMP;
	}
	HP = mp;
}
void Character::SetAttack(int attack) {
	Attack = attack;
}
void Character::SetEXP(int exp) {
	EXP = exp;
}
//YH add
void Character::SetGold(int gold) {
	
	if (gold < 0) {
		gold = 0;
	}
	Gold = gold;
}