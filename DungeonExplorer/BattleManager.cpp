// BattleManager.cpp
#include "BattleManager.h"
#include "Character.h"
#include "Monster.h"
#include "StageManager.h"
#include "RandomManager.h"
#include "BattleSupply.h"
#include <iostream>


void BattleManager::StartBattle(){
    // Random monster spawn required
    // 1. Current stage spawn monster
    // 2. Random count monster
    // 3. Different monster name
    std::vector<Monster*> m = BattleSupply::GetInstance().BattleSpawnMonster(); 
    std::cout << "[Spawn] Spawn monsters!" << std::endl;
    for (auto& monsters : m)
    {
        std::cout << "[Spawn] " << monsters->getName() << ", Health : " << monsters->getHealth() << ", Attack : " <<
            monsters->getAttack() << std::endl;
    }

    // first Turn Roll Dice
    diceResult = rollDice.Roll();
    ApplyDiceResult(diceResult);

    // Enter Battle
    std::cout << "[Spawn] Spawn Monster count : " << m.size() << std::endl;
    bool isWin = AutoBattle(m);

    // End battle, stage random event.
    StageManager::GetInstance().RunRandomEvent(20);
    if (isWin && c.GetHP() > 0)
    {
        std::cout << "[System] Kill all monster! win character!!!\n";
        // Reward 
        BattleSupply::GetInstance().BattleReward(); 
    }
    else
    {
        std::cout << c.GetName() << "[System] die. Game Over.\n";
        // Game End 
    }
    // Delete new monsters
    for (Monster* monsters : m)
    {
        if (monsters != nullptr)
        {
            delete monsters;
            monsters = nullptr;
        }
    }
}

bool BattleManager::AutoBattle(std::vector<Monster*>& m){
    turnCount = 1;
    while (c.GetHP() > 0)
    {
        // Set attack target && Check die monster
        Monster* target = nullptr;
        for (auto monster : m)
        {
            if (monster->getHealth() > 0)
            {
                target = monster;
                break;
            }   
        }
        // Check die all monsters -> Win 
        if (target == nullptr)
            break;
        std::cout << "[Turn] Turn count : " << turnCount << std::endl;
        PlayerTurn(m, target);
        MonstersTurn(m);
        ++turnCount;
    }
    return c.GetHP() > 0;
}

bool BattleManager::PlayerTurn(std::vector<Monster*>& m, Monster*& target){
    std::vector<Monster*> killedMonster;
    // Check miss 
    int randomResult = RandomManager::GetInstance().GetRange(1, 100);
    if (randomResult <= diceResult.missChance) { std::cout << "[Miss] \"" << rollDice.missMessage() << "\"\n"; }
    // Player attack monster(target)
    else if (turnCount % 3 != 0)
    {
        target->takeDamage(c.GetAttack());
        std::cout << "[Attack] " << c.GetName() << " attack " << target->getName() << ". "
            << target->getName() << " Health  : " << target->getHealth() << ". " << std::endl;
        if (target != nullptr && target->getHealth() <= 0)
        {
            killedMonster.push_back(target);
            target = nullptr;
        }
    }
    // 3 Turn use skill
    else if (turnCount % 3 == 0)
    {
        std::cout << "[Attack] " << c.GetName() << " use skill !!" << std::endl; // TODO: c.skillName() 
        // Skill All monster attack
        for (auto& monsters : m)
        {
            if (monsters->getHealth() > 0)
            {
                // TODO: monsters->takeDamage(c.skillAttack); and monsterHP dead HP == 0
                monsters->takeDamage(300);
                std::cout << "[Attack] " << c.GetName() << " attack " << monsters->getName() << ". "
                    << monsters->getName() << " Health  : " << monsters->getHealth() << ". " << std::endl;
                // if Kill monster
                if (monsters->getHealth() <= 0){ killedMonster.push_back(monsters); }
            }
        }
    }
    // if kill monsters message
    if (!killedMonster.empty())
    {
        for (auto& killMonster : killedMonster)
        {
            std::cout << "[Kill] monster " << killMonster->getName() << std::endl;
        }
    }
    return true;
}

void BattleManager::MonstersTurn(std::vector<Monster*>& m){
    // Check alive monster count
    int aliveCount = 0;
    for (auto monsters : m) { if (monsters != nullptr && monsters->getHealth() > 0) { aliveCount++; } }
    std::cout << "[Monster] " << "Alive Monsters count : " << aliveCount << std::endl;

    // Monsters attack Player
    for (auto monsters : m)
    {
        if (monsters->getHealth() > 0)
        {
            c.SetHP(c.GetHP() - monsters->getAttack());
            std::cout << "[Damage] " << monsters->getName() << " attack " << c.GetName() << ", "
                << c.GetName() << " Health : " << c.GetHP() << std::endl;
        }
    }
}

void BattleManager::ApplyDiceResult(DiceResult result){
    // TODO: Slow output 
    std::cout << "[Dice] " << "Roll Dice..." << std::endl;
    std::cout << "[Dice] " << "Complete Roll Dice. \n[Dice] Your dice : " << result.diceNum << std::endl;
    std::cout << "[Event] \"" << result.description << "\"" << std::endl;
    if (result.hpDelta != 0)
    {
        // Set Character hp
        if (result.hpDelta > 0)
        {
            c.SetHP(c.GetMaxHP() + result.hpDelta);
            c.SetHP(c.GetMaxHP());
        }
        else { c.SetHP(c.GetMaxHP() + result.hpDelta); }
        std::cout << "[Event] Player hp add : " << result.hpDelta << ", Player hp : " << c.GetHP() << std::endl;
    }
    if (result.atkDelta != 0)
    {
        // Set Character Attack
        // TODO: c.SetAttack(c.GetAttack() + result.atkDelta);
        std::cout << "[Event] Player attack add : " << result.atkDelta << ", Player Atk : " << c.GetAttack() <<
            std::endl;
    }
    if (result.missChance != 0) { std::cout << "[Event] Player miss Chance -" << result.missChance << std::endl; }
}
