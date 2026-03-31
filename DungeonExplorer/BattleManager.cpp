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
        std::cout << TextFormat::YELLOW << "[System]" << TextFormat::DEFAULT << " Kill all monster! win character!!!\n";
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
        
        std::cout << TextFormat::YELLOW << "[System]" << TextFormat::DEFAULT  << " Turn count : " << turnCount << std::endl;
        
        // Check alive monster
        int aliveCount = 0;
        for (auto monsters : m) { if (monsters != nullptr && monsters->getHealth() > 0) { aliveCount++; } }
        
        std::cout << TextFormat::YELLOW << "[System]" << TextFormat::DEFAULT << " Alive Monsters count : " << aliveCount << std::endl;
        
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
        std::cout << TextFormat::YELLOW << "[System]" << TextFormat::DEFAULT << " Miss!!  \"" << diceRoll.missMessage() << "\"\n";
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
        int skillDamage = playerJob->SkillDamage(c);
        
        // Skill All monster attack
        LogSystem::UseSkill(target, playerJob->SkillName(), skillDamage);
        for (auto& monsters : m)
        {
            if (monsters->getHealth() > 0)
            {
                // Job Damage
                monsters->takeDamage(skillDamage);
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
            int monsterDamage = monsters->Attack();
            if (c.GetDefense() > monsterDamage)
            {
                LogSystem::AttackPlayer(monsters, 0);
                
                // Miss message
                std::cout << TextFormat::YELLOW << "[System]" << TextFormat::DEFAULT 
                << " Your high defense blocked the attack!! " << std::endl;
                
            }   
            else
            {
                int resultDamage = monsterDamage - c.GetDefense();
                c.SetHP(c.GetHP() - resultDamage);
                LogSystem::AttackPlayer(monsters, resultDamage);
            }
        }
    }
}

void BattleManager::ApplyDiceResult(DiceResult result){
    LogSystem::RollDice(result.diceNum);
    
    // Dice description 
    std::cout << TextFormat::YELLOW << "[System]" << TextFormat::DEFAULT << " \"" << result.description << "\"" << std::endl;
    if (result.hpDelta != 0)
    {
        c.SetMaxHP(c.GetMaxHP() + result.hpDelta);
        
        // + Max hp message
        std::cout << TextFormat::YELLOW << "[System]" << TextFormat::DEFAULT 
        << " Player hp add : " << result.hpDelta << ", Player Max hp : " << c.GetMaxHP() << std::endl;
        
    }
    if (result.atkDelta != 0)
    {

        c.SetAttack(c.GetAttack() + result.atkDelta);
        
        // + Character Attack Message
        std::cout << TextFormat::YELLOW << "[System]" << TextFormat::DEFAULT 
        << " Player attack add : " << result.atkDelta << ", Player Atk : " << c.GetAttack() << std::endl;
    }
    if (result.missChance != 0) 
    { 
        
        // + Miss Chance message
        std::cout << TextFormat::YELLOW << "[System]" << TextFormat::DEFAULT 
        << " Player miss Chance -" << result.missChance << std::endl; 
        
    }
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
                // HP 40% message
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
        
        // Check alive boss
        if (boss->getHealth() <= 0)
        {
            isWin = 1;
            break;
        }
        
        // boss turn
        if (bossTurn % 3 != 0)
        {
            boss->SetStrategy(std::make_unique<NormalAttack>());
            int bossDamage = boss->getAttack();
            if (c.GetDefense() > bossDamage)
            {
                LogSystem::AttackPlayer(boss, 0);
                
                std::cout << TextFormat::YELLOW << "[System]" << TextFormat::DEFAULT 
                << " Your high defense blocked the attack!! " << std::endl;
            }   
            else
            {
                int resultDamage = bossDamage - c.GetDefense();
                c.SetHP(c.GetHP() - resultDamage);
                LogSystem::AttackPlayer(boss, resultDamage);
            }
        }
        // boss skill
        else if (bossTurn % 3 == 0)
        {
            boss->SetStrategy(std::make_unique<SpecialAttack>());
            int bossSkillDamage = boss->getAttack();
            if (c.GetDefense() > bossSkillDamage)
            {
                LogSystem::AttackPlayer(boss, 0);
                
                
                std::cout << TextFormat::YELLOW << "[System]" << TextFormat::DEFAULT 
                << " Your high defense blocked the attack!! " << std::endl;
            }   
            else
            {
                int resultDamage = bossSkillDamage - c.GetDefense();
                
                // useSKill Log
                std::cout << ">>> The BOSS casts a skill!" << std::endl;
                std::cout << "-> " << TextFormat::MAGENTA << "Feel my power!" << TextFormat::DEFAULT << "!" << std::endl;
                std::cout << "-> The Player has taken " << resultDamage << " damage!" << std::endl;
                
                c.SetHP(c.GetHP() - resultDamage);
            }
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


