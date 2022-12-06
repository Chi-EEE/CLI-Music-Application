#pragma once
#include <iostream>
#include <unordered_map>// Map data type for storing Sets
#include <windows.h>	// WinApi header (Colours)
#include <ctime>		// Current time for random
#include <algorithm>	// For generating random string
#include "Colour.h"		// Colours for the console
#include "AudioLibrary.h"

class Menu
{
public:
	void run();
	//void generateSets();
	void addAudio();
	void removeAudio();
	void playAudio();
	void createPlaylist();
	void addAudioToPlaylist();
	void removeAudioFromPlaylist();
	void playAllAudioInPlaylist();
	void playAllAudioInProgram();
	//void equalsSet();

private:
	HANDLE hConsole; // Console window

	std::shared_ptr<AudioLibrary> audioLibrary;

	bool continueOperation();
	bool findSet(std::string setName);
	//std::string askForSet(std::string index);
	void displayAllAudio();
	void SendSuccess(std::string successMessage);
	void SendError(std::string errorMessage);
	void SendError(std::string errorMessage, std::string extraMessage);
};

