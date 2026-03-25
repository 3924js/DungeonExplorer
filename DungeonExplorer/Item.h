#pragma once
#include <string>

class Character;

class Item {
public:
	virtual std::string getName() = 0;
	virtual void use(Character* character) = 0;
};