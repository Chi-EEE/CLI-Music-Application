#pragma once
#include "Set.h"

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
		sets.erase(sets.begin(), sets.end());
	}
	void run();
	void generateSets();
	void createSet();
	void addToSet();
	void printSet();
	void removeAllFromSet();
	void containsInSet();
	void removeFromSet();
	void searchInSet();
	void clearSet();
	void equalsSet();

private:
	HANDLE hConsole; // Console window

	std::unordered_map<std::string, std::unique_ptr<Set>> sets; // Set storage

	bool continueOperation();
	bool findSet(std::string setName);
	std::string askForSet(std::string index);
	void listSets();
	void SendSuccess(std::string successMessage);
	void SendError(std::string errorMessage);
	void SendError(std::string errorMessage, std::string extraMessage);
};

