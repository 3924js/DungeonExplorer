// BattleManager.cpp
#include "BattleManager.h"
#include "Character.h"
#include "Monster.h"
#include "StageManager.h"
#include <iostream>

BattleManager::BattleManager(){
    // Roll dice event
}

void BattleManager::StartBattle(Character& c, Monster& m){
    bool isWin = AutoBattle(c, m);
    if (isWin)
    {
        std::cout << "Kill " << m.getName() << "win character\n";
        // Reward 
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
        // Roll Dice
        DiceResult diceResult = BattleDice::GetInstance().Roll();
        // Player attack monster
        CalculateDiceResult(diceResult);
        
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

void BattleManager::CalculateDiceResult(DiceResult result){
    // TODO: Slow output 
    std::cout << "Roll Dice.." << std::endl;
    std::cout << "Complete Roll Dice. \nYour dice : " << result.diceNum << std::endl;
    std::cout << "[Event] \"" << result.description << "\"" << std::endl;
    // result ! = 0 output message
    if (result.hpDelta != 0)
    {
        std::cout << "[Event] Player hp add : " << result.hpDelta << std::endl;
    }

    if (result.atkDelta != 0)
    {
        std::cout << "[Event] Player attack add : " << result.atkDelta << std::endl;
    }
    if (result.missChance != 0){
        std::cout << "[Event] Player miss Chance -" << result.missChance << std::endl;
    }
}