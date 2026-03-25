#include "GameManager.h"
#include <iostream>

#include "Character.h" // test

using namespace std;

int main() {
	//cout << "던전 탐험대" << endl;

	Character* p1 = new Character("player");
	
	int input;
	while (1) {
		cout << "Input 1 to LevelUp(end: -1): ";
		cin >> input;
		if (input == -1) break;
		else if (input == 1) p1->levelUp();
		else cout << input << " is Invalid input\n\n";
	}

	delete p1;
}