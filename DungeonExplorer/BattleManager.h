// BattleManager.h
#pragma once
#include "BattleDice.h"
#include "Character.h"


class Character;
class Monster;


class BattleManager{
    BattleManager() = default; 
    BattleDice rollDice;
    DiceResult diceResult;
    Character& c = *Character::GetInstance();
public:
    static BattleManager& GetInstance(){
        static BattleManager instance;
        return instance;
    }
    
    BattleManager(const BattleManager&) = delete;
    BattleManager operator=(const BattleManager&) = delete;
    
    void StartBattle(std::vector<Monster*> m);   
    bool AutoBattle(std::vector<Monster*> m);
    void DiceResultMessage(DiceResult result);
};