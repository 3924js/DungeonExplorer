#pragma once
#include <string>

class Monster;
class Character;
class CreateMonster;
class Inventory;

class GameManager {
private:
	GameManager();

	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;

	Monster* enemy;
	Character* player;
	CreateMonster* cMonster;
	Inventory* inven;

public:
	static GameManager& GetInstance();

	~GameManager();

	void createPlayer(std::string name = "player");

	void generateMonster(int level = 0);

	void displayInventory();

	void useItem();

	Monster* getEnemy() { return enemy; }
	Character* getPlayer() { return player; }
};
