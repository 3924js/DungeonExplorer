#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <windows.h>

class LayoutManager {
private:
	static LayoutManager GetInstance() {
		static LayoutManager Instance;
		return Instance;
	}
	LayoutManager() {
		FrameBuffer = std::vector<std::string>(MainHeight + LogHeight," ");
		MainBuffer = std::vector<std::string>(MainHeight, " ");
		SideBuffer = std::vector<std::string>(MainHeight, " ");
		LogBuffer = std::vector<std::string>(MainHeight, " ");

	}

	std::vector<std::string> FrameBuffer;
	std::vector<std::string> MainBuffer;
	std::vector<std::string> SideBuffer;
	std::vector<std::string> LogBuffer;

	const int MainLeghth = 30;
	const int MainHeight = 15;

	const int SideLeghth = 10;
	const int SideHeight = 15;

	const int LogLeghth = 45;
	const int LogHeight = 10;

public:
	static void ClearWindow() {
		system("cls");
	}
	static void PrintFrame() {
		//Merge 3 bufferes into FrameBuffer


		//Clear console window and print FrameBuffer
		ClearWindow();
		for (int i = 0; i < GetInstance().MainBuffer.size(); i++) {
			std::cout << GetInstance().MainBuffer[i] << std::endl;
		}
	}
	static void UpdateMain(std::vector<std::string> Content) {
		GetInstance().MainBuffer = Content;
	}
	static void UpdateSide(std::vector<std::string> Content) {

	}
	static void UpdateLog(std::vector<std::string> Content) {

	}
};