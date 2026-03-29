#pragma once

class GameManager;
class BattleManager;
class StageManager;

class GameFlowManager {
private:
	GameManager& gm;
	StageManager& sManager;
	BattleManager* bManager;

	bool isGameClear;
public:
	GameFlowManager();

	void run();

	void setupPlayer();

	void selectNextNode();

	void battleNode();

	void storeNode();

	void bossNode();

	void gameOver();

	void gameClear();
};