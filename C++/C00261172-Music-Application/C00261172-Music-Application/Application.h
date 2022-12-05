#pragma once
#include <iostream>
#include <string>

#include <map> // For Menu

// HANDLE
#include <windows.h>

// _getch
#include <stdio.h>
#include <conio.h>

// std::streamsize>::max()
#include <sstream>
#include <limits>

#include "Colour.h"

#include <vector>

#include <variant>
#include <functional>

#include "CircularLinkedList.h"
#include "AudioLibrary.h"

#include "Menu.h"
#include "MenuOption.h"
#include "MenuExitResult.h"
class Application
{
public:
	Application();
	void run();
private:
	void initaliseMenus();
	void buildMenu(int layerIndex);
	void displayAudioDetails(Audio* audio, int index);
	void addAudio();
	void removeAudio();
	bool YesOrNo(std::string question);
	std::string EnterConsoleString(std::string statement);
	int EnterConsoleInt(std::string statement);
	void Write(std::string message);
	bool GetKey(int& keyCode);
	void setConsoleColor(int color);
	void resetConsoleColor();
	void clear();
	int mod(int left, int right); 
	HANDLE hConsole; // Console window

	AudioLibrary audioLibrary;
	bool changed = true;
	const std::string LINE = "=======================================================================================================================\n";

	std::vector<std::shared_ptr<Menu>> menuLayers{};
};