// BattleDice.h 
#pragma once
#include <string>
#include <map>
#include <vector>

struct DiceResult{
    std::string description;
    int hpDelta;
    int atkDelta;
    int missChance;
    int diceNum = 0;
};

class BattleDice{
private:
    BattleDice();
    std::map<int, std::vector<DiceResult>> eventTable;
public:
    // Singleton 
    static BattleDice& GetInstance(){
        static BattleDice instance;
        return instance; 
    }
    
    BattleDice(const BattleDice&) = delete;
    BattleDice operator=(const BattleDice&) = delete;
    
    DiceResult Roll();
};