// BattleSupply.cpp
#include <iostream>
#include "BattleSupply.h"
#include "BattleTable.h"
#include "Character.h"
#include "StageManager.h"
#include "Monster.h"
#include "RandomManager.h"
#include "CreateMonster.h"
#include "ItemFactory.h"
#include "Inventory.h"

BattleSupply::BattleSupply(){
    monsterFactory["Goblin"] = CreateMonster::createGoblin;
    // TODO: add create Orc, Troll, Slime
    monsterFactory["Orc"] = CreateMonster::createGoblin;
    monsterFactory["Troll"] = CreateMonster::createGoblin;
    monsterFactory["Slime"] = CreateMonster::createGoblin; 
}
std::vector<Monster*> BattleSupply::BattleSpawnMonster(){
    spawnedList.clear();
    // spawn monster count < suffixes 
    std::vector<std::string> suffixes = {"Spearman", "Archer", "Guard", "Scout", "Shaman"};
    RandomManager::GetInstance().ShuffleVectorString(suffixes);
    
    // Check set stage
    EStage currentStage = StageManager::GetInstance().GetCurrentStage();
    if (currentStage == EStage::NONE) return spawnedList;
    
    // Check stage spawn monster 
    std::vector<std::string> monsterPool = BattleTable::GetMonsterToStage(currentStage);
    if (monsterPool.empty()) return spawnedList; 
    
    // Monster random count 1 ~ 4 
    int count = RandomManager::GetInstance().GetRange(1,4);
    for (int i = 0; i < count; ++i)
    {
        int randomIndex = RandomManager::GetInstance().GetRange(0, monsterPool.size() - 1);
        std::string findMonster = monsterPool[randomIndex];
        
        
        // Check monster in MonsterFactory 
        auto it = monsterFactory.find(findMonster);
        if (it == monsterFactory.end())
        {
            std::cout << "Error not found monster" << std::endl;
            continue; 
        }
        
        // Create Random Monster
        std::string monsterName = findMonster + " " + suffixes[i % suffixes.size()]; // defense if i > suffixes.size()
        Monster* newMonster = it->second(monsterName, player->GetLevel());
        spawnedList.push_back(newMonster);
        // for reward
        rewardList.push_back(findMonster);
    }
    return spawnedList; 
}

void BattleSupply::BattleReward(){
    int totalGold = 0;
    int totalEXP = rewardList.size();
    for (auto m : rewardList)
    {
        MonsterReward rewardMob = BattleTable::GetRewardToMonster(m);
        float randomChance = RandomManager::GetInstance().GetRange(0.0f, 1.0f);
        int randomGold = RandomManager::GetInstance().GetRange(rewardMob.minGold, rewardMob.maxGold);
        int playerGold = player->GetGold();
        Item getItem = ItemFactory::CreateItem(rewardMob.itemId);

        if (randomChance <= rewardMob.dropRate )
        {
            std::cout << "[Reward] " << m << " dropped an rewards!! (" << rewardMob.dropRate * 100 << "% drop) \n";
            std::cout << "[Reward] Player get gold : " << randomGold << " G\n";
            player->SetGold(playerGold + randomGold);
            
            std::cout << "[Reward] Player get Item : " << getItem.name << std::endl;
            // TODO: Player inventory
            // Character::GetInstance()->GetInventory().AddItem(getItem);
        }
        else
        {
            std::cout << "[Reward] " << m << " dropped nothing. (" << rewardMob.dropRate * 100 << "% drop) \n";
        }
    }
    std::cout << "[Reward] Player get Total EXP : " << totalEXP << " EXP\n";
    int getEXP = player->GetEXP();
    player->SetEXP(getEXP + totalEXP);
}
