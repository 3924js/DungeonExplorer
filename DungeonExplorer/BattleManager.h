// BattleManager.h
#pragma once
#include "BattleDice.h"
#include "Character.h"
#include "GameManager.h"


class Character;
class Monster;


class BattleManager{
private:
    int turnCount;
    BattleDice diceRoll;
    DiceResult diceResult;
    Character& c = *GameManager::GetInstance().getPlayer();
    BattleManager() = default; 
public:
    static BattleManager& GetInstance(){
        static BattleManager instance;
        return instance;
    }
    
    BattleManager(const BattleManager&) = delete;
    BattleManager operator=(const BattleManager&) = delete;
    
    void StartBattle();   
    bool AutoBattle(std::vector<Monster*>& m);
    bool PlayerTurn(std::vector<Monster*>& m, Monster*& target);
    void MonstersTurn(std::vector<Monster*>& m);
    void ApplyDiceResult(DiceResult result);
};