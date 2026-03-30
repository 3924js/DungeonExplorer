#pragma once
#include <random>
#include <string>
#include "Goblin.h"
class CreateMonster {
private:
	static inline std::mt19937& getGenerator() {
		static std::random_device rd;
		static std::mt19937 gen(rd());
		return gen;
	}
public:
	static Monster* createGoblin(std::string name, int level);

};