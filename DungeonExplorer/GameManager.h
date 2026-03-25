#pragma once

class Monster;
class Character;

class GameManager {
public:
	Monster* generateMonster(int level);
	void battle(Character* character);
	void showInventory(Character* character);
};