// BattleManager.cpp
#include "BattleManager.h"
#include "Character.h"
#include "Monster.h"
#include "StageManager.h"
#include "RandomManager.h"
#include "BattleSupply.h"
#include "LogSystem.h"
#include "GameFlowManager.h"
#include "inventory.h"
#include "Job.h"
#include <iostream>


void BattleManager::StartBattle(){
    // Random monster spawn 
    std::vector<Monster*> m = BattleSupply::GetInstance().BattleSpawnMonster(); 
    // first Turn Roll Dice
    diceResult = diceRoll.Roll();
    ApplyDiceResult(diceResult);
    // std::cout << "[Spawn] Spawn monsters!" << std::endl;
    LogSystem::EnterBattle(m);
    bool isWin = AutoBattle(m);
    // End battle, stage random event.
    StageManager::GetInstance().RunRandomEvent(20);
    
    
    if (isWin && c.GetHP() > 0)
    {
        std::cout << "[System] Kill all monster! win character!!!\n";
        // Reward 
        BattleSupply::GetInstance().BattleReward(); 
        // buff effect end
        Inventory* inv = GameManager::GetInstance().getInventory();
        inv->SetTempAtkBuff(0);
    }
    else
    {
        // Game End 
        GameFlowManager GFM;
        GFM.gameOver();
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
        std::cout << "[System] Turn count : " << turnCount << std::endl;
        // Check alive monster
        int aliveCount = 0;
        for (auto monsters : m) { if (monsters != nullptr && monsters->getHealth() > 0) { aliveCount++; } }
        std::cout << "[System] " << "Alive Monsters count : " << aliveCount << std::endl;
        std::cout << ">>> Player HP " << c.GetHP() << std::endl;
        
        UsePotionToPer(0.4f);
        
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
    if (randomResult <= diceResult.missChance)
    {
        std::cout << "[System] Miss!!  \"" << diceRoll.missMessage() << "\"\n";
    }
    // Player attack monster(target)
    else if (turnCount % 3 != 0)
    {
        target->takeDamage(c.GetAttack());
        LogSystem::AttackMonster(target, c.GetAttack());
        if (target != nullptr && target->getHealth() <= 0)
        {
            LogSystem::KillMonster(target);
            killedMonster.push_back(target);
            target = nullptr;
        }
    }
    // 3 Turn use skill
    else if (turnCount % 3 == 0)
    {
        Job* playerJob = GameManager::GetInstance().getPlayerJob();
        
        std::cout << "[System] " << c.GetName() << " use skill !! "  
         << playerJob->SkillName() << std::endl;
        // Skill All monster attack
        for (auto& monsters : m)
        {
            if (monsters->getHealth() > 0)
            {
                // Job Damage
                int skillDamage = playerJob->SkillDamage(c);
                monsters->takeDamage(skillDamage);
                
                LogSystem::AttackMonster(monsters, skillDamage);
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
            LogSystem::KillMonster(killMonster);
        }
    }
    return true;
}

void BattleManager::MonstersTurn(std::vector<Monster*>& m){
    for (auto monsters : m)
    {
        if (monsters->getHealth() > 0)
        {
            c.SetHP(c.GetHP() + c.GetDefense() - monsters->Attack());
            LogSystem::AttackPlayer(monsters, monsters->getAttack());
        }
    }
}

void BattleManager::ApplyDiceResult(DiceResult result){
    LogSystem::RollDice(result.diceNum);
    // std::cout << "[Dice] Your dice : " << result.diceNum << std::endl;
    std::cout << "[System] \"" << result.description << "\"" << std::endl;
    if (result.hpDelta != 0)
    {
        // Set Character hp
        if (result.hpDelta > 0)
        {
            c.SetHP(c.GetMaxHP() + result.hpDelta);
        }
        else { c.SetHP(c.GetMaxHP() + result.hpDelta); }
        std::cout << "[System] Player hp add : " << result.hpDelta << ", Player hp : " << c.GetHP() << std::endl;
    }
    if (result.atkDelta != 0)
    {
        // Set Character Attack
        c.SetAttack(c.GetAttack() + result.atkDelta);
        std::cout << "[System] Player attack add : " << result.atkDelta << ", Player Atk : " << c.GetAttack() << std::endl;
    }
    if (result.missChance != 0) { std::cout << "[System] Player miss Chance -" << result.missChance << std::endl; }
}

void BattleManager::UsePotionToPer(float perHP){
    // Check Player MAX HP 30 %
    int playerHP = c.GetHP();
    int playerMaxHP = c.GetMaxHP();
    Inventory* inv = GameManager::GetInstance().getInventory();
    std::vector<Item>& findItem = GameManager::GetInstance().getInventory()->GetOwnedItems();
    
    if (playerHP <= playerMaxHP * perHP)
    {
        for (auto it = findItem.begin(); it < findItem.end(); ++it)
        {
            if (it->id == 301 || it->id == 302)
            {
                std::cout << TextFormat::RED 
                << "[System] " << c.GetName() << " HP is Only " << perHP * 100 << "% !!!!" 
                << TextFormat::DEFAULT << std::endl;
                std::cout << "[System] " << c.GetName() << " HP : " << playerHP << std::endl;
                inv->UseItem();
                std::cout << "[System] " << c.GetName() << " HP : " << c.GetHP() << std::endl;
                return; 
            }
        }
    }
}

void BattleManager::StartBossBattle(Monster* boss){
    GameFlowManager GFM;
    bool isWin = 0;
    int bossTurn = 1;

    int normalDamage = normalAtk.calculateDamage(boss->getAttack());
    int specialDamage = specialAtk.calculateDamage(boss->getAttack());
    
    while(c.GetHP() >  0){
        std::cout << "[System] Turn Count : " << bossTurn << std::endl;
        
        UsePotionToPer(0.4f);
        
        // player turn
        if (bossTurn % 3 != 0)
        {
            boss->takeDamage(c.GetAttack());
            LogSystem::AttackMonster(boss, c.GetAttack());
        }
        // Player use skill
        else if (bossTurn % 3 == 0)
        {
            Job* playerJob = GameManager::GetInstance().getPlayerJob();
            int skillDamage = playerJob->SkillDamage(c);
            boss->takeDamage(skillDamage);
            LogSystem::AttackMonster(boss, skillDamage);
        }
        
        // boss turn
        if (bossTurn % 2 != 0)
        {
            c.SetHP(c.GetHP() + c.GetDefense() - normalDamage);
            LogSystem::AttackPlayer(boss, normalDamage);
        }
        // boss skill
        else if (bossTurn % 2 == 0)
        {
            c.SetHP(c.GetHP() + c.GetDefense() - specialDamage);
            LogSystem::AttackPlayer(boss, specialDamage);
        }
        
        if (boss->getHealth() <= 0)
        {
            isWin = 1;
            break;
        }
        ++bossTurn;
    }
    
    // Check isWin
    if (isWin)
    {
        GFM.gameClear();
    }
    else
    {
        GFM.gameOver();
    }
}


