// StageDarkCave.cpp
#include "StageDarkCave.h"
#include "Character.h"
#include "RandomManager.h"
#include <iostream>

StageDarkCave::StageDarkCave() : Stage(EStage::DARK_CAVE){
    // Roll dice event
    eventTable[1] = {"Dark Dark Dark", -10, 0};
    eventTable[2] = { "It's too dark to see the enemy.", 0, -3};
    eventTable[3] = {};
    eventTable[4] = {"Soon, my eyes got used to the dark.", 0, 1};
    eventTable[5] = {"I just swung my sword, and the monster got hit.", 0, 5};
    eventTable[6] = {"You loved the night time.", 10, 10};
}
void StageDarkCave::EnterStage(){
    std::cout << "========================================" << std::endl;
    std::cout << " [ Stage : Dark Cave ] " << std::endl;
    std::cout << " - Monster : Goblin , Orc" << std::endl;
    // Enter Log
    std::cout << " - \"Your footsteps break the heavy silence deep inside the cave. Something is moving.\"" << std::endl; 
    // Enter event
    // Roll dice 1 ~ 6
    int rollResult = RandomManager::GetInstance().GetRange(1,6);
    StageEvent& event = eventTable[rollResult];
    std::cout << "[RollDice] your Dice " << rollResult << std::endl;
    std::cout << "[Event] " << event.description << std::endl;
    // TODO:Update Character hp, atk
    if (event.hpDelta != 0)
        std::cout << "[Event] Player hp add " << event.hpDelta << std::endl;
    if (event.atkDelta != 0)
        std::cout << "[Event] Player atk add " << event.atkDelta << std::endl;
    std::cout << "========================================" << std::endl;
}

void StageDarkCave::RandomEvent(int chance){
    // chance % random event
    int eventChance = RandomManager::GetInstance().GetRange(1,100);
    if (eventChance <= chance)
    {
        StageEvent randomEvent[3] = {
            {"The sound of the bat's wings makes me scared.",0,-5},
            {"The goblin's laugh makes you scared.", -5,-3},
            {"You found the goblin's treasure.", 10, 10}
        };
        StageEvent event = randomEvent[ RandomManager::GetInstance().GetRange(1,3)];
        std::cout << "[Random Event] " << event.description << std::endl;
        // TODO:Update Character hp, atk
        if (event.hpDelta != 0)
            std::cout << "[Random Event] Player hp add " << event.hpDelta << std::endl;
        if (event.atkDelta != 0)
            std::cout << "[Random Event] Player atk add " << event.atkDelta << std::endl;
    }
}
