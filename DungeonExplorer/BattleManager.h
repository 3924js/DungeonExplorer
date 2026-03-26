// BattleManager.h
#pragma once

class Character;
class Monster;

class BattleManager{
public:
	void StartBattle(Character& c, Monster& m);   
    
	bool AutoBattle(Character& c, Monster& m);
	void BattleReward(Character& c);

};