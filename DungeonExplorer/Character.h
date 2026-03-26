//Character.h

#include <string>

class Character
{
public:
	Character(const std::string& name);
	void displayStatus() const;
	void LevelUP();

	std::string GetName() const;
	int GetLevel() const;
	int GetMaxHP() const;
	int GetMaxMP() const;
	int GetHP() const;
	int GetMP() const;
	int GetAttack() const;
	int GetEXP() const;

	void SetName(std::string name);
	void SetLevel(int level);
	void SetMaxHP(int maxhp);
	void SetMaxMP(int maxmp);
	void SetHP(int hp);
	void SetMP(int mp);
	void SetAttack(int attack);
	void SetEXP(int exp);

private:
	std::string Name;
	int Level;
	int MaxHP;
	int MaxMP;
	int HP;
	int MP;
	int Attack;
	int EXP;
};
