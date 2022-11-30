#pragma once

#include <iostream>
#include <unordered_map>// Map data type for storing Sets
#include <windows.h>	// WinApi header (Colours)
#include <ctime>		// Current time for random
#include <algorithm>	// For generating random string
#include "Colour.h"		// Colours for the console

class Menu
{
public:
	~Menu() {
		//sets.erase(sets.begin(), sets.end());
	}
	void run();

private:
	HANDLE hConsole; // Console window

	void SendSuccess(std::string successMessage);
	void SendError(std::string errorMessage);
	void SendError(std::string errorMessage, std::string extraMessage);
};

