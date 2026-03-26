// BattleManager.cpp
#include "BattleManager.h"
#include "Character.h"
#include "Monster.h"
#include <iostream>
#include <cstdlib>

void BattleManager::StartBattle(Character& c, Monster& m){
	/* Start condition
	 * + Check Character live
	 * + Skip store 
	 * + Check invite store
	*/
	bool isWin = AutoBattle(c, m);
	if (isWin)
	{
		std::cout << "Kill " << m.name << "win character\n"
		BattleReward(c);
	}
	else if (!isWin)
	{
		std::cout << c.name << " die. Game Over.\n"; 
	}
}

bool BattleManager::AutoBattle(Character& c, Monster& m){
	std::cout << "Spawn " << m.name 
	<< " Health : " << m.health << ", Attack : " << m.attack << std::endl;
	
	while (m.health > 0 && c.health > 0)
	{
		m.setHealth(m.health - c.attack);
		std::cout << c.name << " attack " << m.name 
		<< m.name << " Health  : " << m.health << std::endl;

		c.setHealth(c.health - m.attack);
		std::cout << m.name << " attack " << c.name 
		<< c.name << " Health : " << c.health << std::endl;
	}
	return c.health > 0;
}

void BattleManager::BattleReward(Character& c){
	int expReward = 50;
	int goldReward = (rand() % 11) + 10; // 10 ~ 20 
	int maxRand = 30;

	c.experience += expReward;
	c.gold += goldReward;
	if (rand() % 100 < maxRand) // 30% get item
	{
		if (rand() % 2 == 0) // 50% get item 
		{
			c.inventory.push_back(new HealthPotion());
		}
		else
		{
			c.inventory.push_back(new AttackBoost());
		}
	}

	if (c.experience > 99) // EXP > 99  -> Level up
	{
		while (c.experience > 99)
		{
			c.levelUP();
			c.experience -= 100; // turn over EXP 
		}
	}
	std::cout << c.name << expReward << goldReward << 
	"Character EXP, Gold" << c.experience << c.gold << "\n";
}