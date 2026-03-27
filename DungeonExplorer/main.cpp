#include <iostream>
#include "LogSystem.h"
#include "Goblin.h"
#include <memory>

using namespace std;

int main() {
	Monster* A = new Goblin("Gob",1,2);
	Monster* B = new Goblin("Slime", 10, 20);
	vector<Monster*> Group = { A, B };

	Item Potion(1, "Potion", ItemType::Potion, Rarity::Common, 30, "Consumable that heals the player for 50 points", 1);
	Item Jewel(1, "Jewel", ItemType::Etc, Rarity::Legendary, 100, "Cursed Jewel for the magic", 1);
	Item Sword(1, "Sword", ItemType::Weapon, Rarity::Rare, 50, "Dangerous sword of the old kingdom", 1);

	LogSystem::EnterBattle(Group);
	LogSystem::AttackMonster(A, 30);
	LogSystem::AttackPlayer(A, 30);
	LogSystem::KillMonster(A);
	LogSystem::GetReward(30, 50, { Jewel,Sword });


	LogSystem::BuyItem(Potion);
	LogSystem::UseItem(Potion);
	LogSystem::RollDice(16);

	LogSystem::ShowStatistics();
}