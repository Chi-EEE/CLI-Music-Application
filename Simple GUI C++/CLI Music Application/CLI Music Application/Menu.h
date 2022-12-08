#pragma once
#include <iostream>
#include <unordered_map>// Map data type for storing Sets
#include <windows.h>	// WinApi header (Colours)
#include <ctime>		// Current time for random
#include <algorithm>	// For generating random string
#include "Colour.h"		// Colours for the console
#include "AudioLibrary.h"
#include "Playlist.h"

class Menu
{
public:
	void run();
	void viewAudioMenu(); 
	void generateAudioFiles();
	void addAudio();
	void viewAudioDetails(std::string audioName, std::shared_ptr<Audio> audio);
	void updateAudio(std::string audioName, std::shared_ptr<Audio> audio); 
	void removeAudio(std::string audioName, std::shared_ptr<Audio> audio);
	void playAudio(std::string audioName, std::shared_ptr<Audio> audio);
	void viewPlaylistMenu(); 
	std::shared_ptr<Artist> createArtist();
	void createPlaylist();
	void addAudioToPlaylist();
	void removeAudioFromPlaylist();
	void playAllAudioInPlaylist();
	void playAllAudioInProgram();

private:
	HANDLE hConsole; // Console window

	std::shared_ptr<AudioLibrary> audioLibrary;
	CircularLinkedList<Playlist> playlists;
	std::vector<std::shared_ptr<Artist>> artists;

	bool continueOperation();
	bool YesOrNo(std::string question);
	std::shared_ptr<Audio> askForAudio(std::string& audioName, std::shared_ptr<AudioList> audioList);
	std::shared_ptr<Playlist> askForPlaylist(std::string& playlistName);
	void displayAllAudio();
	void displayAllPlaylists();
	void SendSuccess(std::string successMessage);
	void SendError(std::string errorMessage);
	void SendError(std::string errorMessage, std::string extraMessage);
};

