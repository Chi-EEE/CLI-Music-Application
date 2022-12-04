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

#include "CircularLinkedList.h"
#include "AudioLibrary.h"

#include "MenuExitResult.h"
class Application
{
public:
	Application();
	void run();
	void buildMainMenu();
	void buildAudioMenu(int& selectedOption);
	void displayAudioDetails(Audio* audio, int index);
	MenuExitResult handleAudioMenu(int& mainMenuOptionIndex);
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
private:
	HANDLE hConsole; // Console window

	AudioLibrary audioLibrary;
	bool changed = true;
	const std::string LINE = "=======================================================================================================================\n";
	
	int selectedMainOption = 0;
	bool selectedMainOptionOpened = false;

	int levels = 0;
	std::vector<int> numbers;

	// https://stackoverflow.com/a/3114231
	typedef MenuExitResult(Application::* mainMenu_method_t)(int&);
	typedef std::map<std::string, mainMenu_method_t> mainMenu_func_map_t;
	mainMenu_func_map_t mainMenuOptions;

	typedef void (Application::* menu_method_t)(void);
	typedef std::map<std::string, menu_method_t> menu_func_map_t;
	menu_func_map_t menuOptions;
};

struct Menu
{
	int selectedOption = 0;
	MenuExitResult handleAudioMenu(int& mainMenuOptionIndex);
	int selectedOption = 0;
};