// BattleManager.h
#pragma once

class Character;
class Monster;

class BattleManager{
    BattleManager() = default;
public:
    static BattleManager& GetInstance(){
        static BattleManager instance;
        return instance;
    }
    
    BattleManager(const BattleManager&) = delete;
    BattleManager operator=(const BattleManager&) = delete;
    
    void StartBattle(Character& c, Monster& m);   
    
    bool AutoBattle(Character& c, Monster& m);
    // void BattleReward(Character& c); -> Move GameManager 
};