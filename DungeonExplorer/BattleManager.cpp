// BattleManager.cpp
#include "BattleManager.h"
#include "Character.h"
#include "Monster.h"
#include "StageManager.h"
#include <iostream>

void BattleManager::StartBattle(Character& c, Monster& m){
    bool isWin = AutoBattle(c, m);
    if (isWin)
    {
        std::cout << "Kill " << m.getName() << "win character\n";
    }
    else
    {
        std::cout << c.GetName() << " die. Game Over.\n"; 
    }
}

bool BattleManager::AutoBattle(Character& c, Monster& m){
    // TODO: Random monster spawn. to Stage
    std::cout << "Spawn " << m.getName()
    << " Health : " << m.getHealth() << ", Attack : " << m.getAttack() << std::endl;
	
    while (m.getHealth() > 0 && c.GetHP() > 0)
    {
        // Player attack monster
        m.takeDamage(c.GetAttack());
        std::cout << c.GetName() << " attack " << m.getName() 
        << m.getName() << " Health  : " << m.getHealth() << std::endl;
        // Monster attack player
        c.SetHP(c.GetHP() - m.getAttack());
        std::cout << m.getName() << " attack " << c.GetName()
        << c.GetName() << " Health : " << c.GetHP() << std::endl;
        // 20% Random Event
        StageManager::GetInstance().RunRandomEvent(20);
    }
    return c.GetHP() > 0;
}