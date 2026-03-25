#pragma once
#include "Item.h"
#include <string>

class HealthPotion : public Item {
private:
	std::string name;
	int healthRestore;
public:
	HealthPotion();

	std::string getName() override;

	void use(Character* character) override;
};