// BattleManager.cpp
#include "BattleManager.h"
#include "Character.h"
#include "Monster.h"
#include "StageManager.h"
#include "RandomManager.h"
#include <iostream>




void BattleManager::StartBattle(std::vector<Monster*> m){
    std::cout << "Spawn monsters!" << std::endl;
    for (auto& monsters : m)
    {
        std::cout << "[Spawn] " << monsters->getName() << ", Health : " << monsters->getHealth() << ", Attack : " <<
            monsters->getAttack() << std::endl;
    }
    
    // first Turn Roll Dice
    diceResult = rollDice.Roll();
    DiceResultMessage(diceResult);
    
    // Enter Battle
    std::cout << "Spawn Monster count : " << m.size() << std::endl;
    bool isWin = AutoBattle(m);
    
    // End battle, stage random event.
    StageManager::GetInstance().RunRandomEvent(20);
    if (isWin && c.GetHP() > 0)
    {
        std::cout << "Kill all monster! win character!!!\n";
        // Reward 
    }
    else
    {
        std::cout << c.GetName() << " die. Game Over.\n";
        // Game End 
    }
}

bool BattleManager::AutoBattle(std::vector<Monster*> m){
    int turnCount = 0;
    while (c.GetHP() > 0)
    {
        int aliveCount = 0;
        std::cout << "[Turn] Turn count : " << turnCount << std::endl;
        // Set attack target 
        Monster* target = nullptr;
        for (auto monster : m)
        {
            if (monster->getHealth() > 0)
            {
                target = monster;
                break;
            }
        }
        // Check die monsters
        if (target == nullptr)
            break;


        // Check miss 
        int randomResult = RandomManager::GetInstance().GetRange(1, 100);
        if (randomResult <= diceResult.missChance) { std::cout << "[Miss] \"" << rollDice.missMessage() << "\"\n"; }
        // Player attack monster(target)
        else if (turnCount == 0 || turnCount % 3 != 0)
        {
            target->takeDamage(c.GetAttack());
            std::cout << "[Attack] "<< c.GetName() << " attack " << target->getName() << ". "
                << target->getName() << " Health  : " << target->getHealth() << ". " << std::endl;
        }
        // 3 Turn use skill
        else if (turnCount != 0 && turnCount % 3 == 0)
        {
            // TODO: target->takeDamage(c.skillAttack); , c.skillName() W
            std::cout << "[Attack] " << c.GetName() << " use skill " << target->getName() << ". " <<
               target->getName() << " Health  : " << target->getHealth() << ". " << std::endl;
        }
        
        // if Kill monster = nullptr
        if (target->getHealth() <= 0)
        {
            std::cout << "[Kill] monster " << target->getName() << std::endl;
            target = nullptr;
        }
        // Check alive monster count
        for (auto monsters : m)
        {
            if (monsters != nullptr && monsters->getHealth() > 0)
            {
                aliveCount++;
            }
        }
        std::cout << "[Monster] " << "Alive Monsters count : " << aliveCount << std::endl;
        
        // Monsters attack Player
        for (auto monsters : m)
        {
            if (monsters->getHealth() > 0){
            c.SetHP(c.GetHP() - monsters->getAttack());
            std::cout << "[Damage] "<<monsters->getName() << " attack " << c.GetName() << ", "
                << c.GetName() << " Health : " << c.GetHP() << std::endl;
            }
        }
        ++turnCount;
    }
    return c.GetHP() > 0;
}

void BattleManager::DiceResultMessage(DiceResult result){
    // TODO: Slow output 
    std::cout << "[Dice] " << "Roll Dice..." << std::endl;
    std::cout << "[Dice] " << "Complete Roll Dice. \nYour dice : " << result.diceNum << std::endl;
    std::cout << "[Dice] " << "[Event] \"" << result.description << "\"" << std::endl;
    if (result.hpDelta != 0)
    {
        // Set Character hp
        if (result.hpDelta > 0)
        {
            c.SetMaxHP(c.GetMaxHP() + result.hpDelta);
            c.SetHP(c.GetMaxHP());
        }
        else { c.SetHP(c.GetMaxHP() + result.hpDelta); }
        std::cout << "[Event] Player hp add : " << result.hpDelta << ", Player hp : " << c.GetHP() << std::endl;
    }
    if (result.atkDelta != 0)
    {
        // Set Character Attack
        c.SetAttack(c.GetAttack() + result.atkDelta);
        std::cout << "[Event] Player attack add : " << result.atkDelta << ", Player Atk : " << c.GetAttack() << std::endl;
    }
    if (result.missChance != 0) { std::cout << "[Event] Player miss Chance -" << result.missChance << std::endl; }
}
