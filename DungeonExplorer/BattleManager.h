// BattleManager.h
#pragma once
#include "BattleDice.h"

class Character;
class Monster;

struct DiceResult;

class BattleManager{
    BattleManager();
public:
    static BattleManager& GetInstance(){
        static BattleManager instance;
        return instance;
    }
    
    BattleManager(const BattleManager&) = delete;
    BattleManager operator=(const BattleManager&) = delete;
    
    void StartBattle(Character& c, Monster& m);   
    bool AutoBattle(Character& c, Monster& m);
    void CalculateDiceResult(DiceResult result);
};