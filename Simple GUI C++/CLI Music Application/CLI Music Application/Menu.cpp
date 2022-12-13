/// <summary>
/// Name: Chi Huu Huynh
/// Date: 06/12/2022
/// </summary>
#include "Menu.h"

/// <summary>
/// Generate random strings | Credits: https://stackoverflow.com/a/440240
/// </summary>
/// <param name="length">length of string</param>
/// <returns></returns>
std::string random_string(size_t length)
{
	auto randchar = []() -> char
	{
		const char charset[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";
		const size_t max_index = (sizeof(charset) - 1);
		return charset[rand() % max_index];
	};
	std::string str(length, 0);
	std::generate_n(str.begin(), length, randchar);
	return str;
}

/// <summary>
/// The main loop of the application
/// </summary>
void Menu::run() {
	std::srand(static_cast<unsigned>(time(nullptr)));		//Initalise random seed
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	audioLibrary = std::make_shared<AudioLibrary>();

	int selection = 0;
	while (true) // MAIN LOOP
	{
		while (true) // Loop to check if user has inputted correct data type
		{
			// Starting text
			std::cout << "CLI Music Application by Chi\n 1) Audio Menu\n 2) Playlist Menu\n 3) Artist Menu\n> ";
			std::cin >> selection;
			if (!std::cin.fail()) {
				break;
			}
			SendError("Error: Numbers only.\n");
			std::cin.clear();
			std::cin.ignore(256, '\n');
		}
		std::cout << "\n";
		switch (selection) // Menu system
		{
		case 1:
			viewAudioMenu();
			break;
		case 2:
			viewPlaylistMenu();
			break;
		case 3:
			viewArtistMenu();
			break;
		default:
			SendError("Invalid Selection\n");
			break;
		}
	}
}

/// <summary>
/// The submenu for handling audio files
/// </summary>
void Menu::viewAudioMenu()
{
	while (true) // Loop to check if user has inputted correct data type
	{
		int menuSelection;
		while (true) {
			std::cout << "=Audio Menu=\n1) Create Audio\n2) Search and preview Audio\n3) Generate 3-5 Audio Files\n4) Exit\n> ";
			std::cin >> menuSelection;
			switch (menuSelection) {
			case 1:
			{
				createAudio();
				break;
			}
			case 2:
			{
				while (true) {
					displayAllAudio();
					std::string audioName;
					std::shared_ptr<Audio> audio = askForAudio(audioName, audioLibrary);
					if (audio != nullptr) {
						while (true) {
							int selection;
							std::cout << audioName << ":\n1) View Audio Details\n2) Update Audio\n3) Remove Audio\n4) Play Audio\n> ";
							std::cin >> selection;
							switch (selection) // Menu system
							{
							case 1:
								viewAudioDetails(audio);
								break;
							case 2:
								updateAudio(audioName, audio);
								break;
							case 3:
								removeAudio(audioName, audio);
								break;
							case 4:
								playAudio(audioName, audio);
								break;
							default:
								SendError("Invalid Selection\n");
								break;
							}
							if (YesOrNo("Do you want to finish editing '" + audioName + "'?\n 0 = No\n 1 = Yes\n> ")) {
								return;
							}
						}
					}
					if (YesOrNo("Do you want finish editing audio files?\n 0 = No\n 1 = Yes\n> ")) {
						break;
					}
				}
				break;
			}
			case 3:
			{
				generateAudioFiles();
				break;
			}
			case 4:
			{
				return;
			}
			}
		}
	}
}

/// <summary>
/// Asks the user to create an Audio instance with its name, description, duration and artist.
/// </summary>
void Menu::createAudio() {
	std::string audioName;
	std::string audioDescription;
	int audioDuration = 1;

	while (true) {
		std::cout << "Please enter the Audio's Name: ";
		std::cin >> audioName;
		if (audioLibrary->getAudioByName(audioName) == nullptr)
		{
			break;
		}
		SendError("There is already an Audio file with the name '" + audioName + "'!\nIf you wish to update the Audio, please remove and re-add it.");
		if (!continueOperation()) {
			return; // EXIT FUNCTION
		}
	}
	if (!continueOperation()) {
		return; // EXIT FUNCTION
	}
	std::cout << "Please enter the Audio's Description: ";
	std::cin >> audioDescription;
	if (!continueOperation()) {
		return; // EXIT FUNCTION
	}
	while (true) {
		std::cout << "Please enter the Audio's Duration: ";
		std::cin >> audioDuration;
		if (!std::cin.fail()) {
			break;
		}
		SendError("Error: Numbers only.\n");
		std::cin.clear();
		std::cin.ignore(256, '\n');
	}

	bool confirmAddArtist = false;
	while (true) {
		std::cout << "\nWould you like to add an Artist to this Audio:\n 0 = No\n 1 = Yes\n> ";
		std::cin >> confirmAddArtist;
		if (!std::cin.fail()) {
			break;
		}
		SendError("\nError: 0 or 1");
		std::cin.clear();
		std::cin.ignore(256, '\n');
	}
	std::cout << "\n";
	if (confirmAddArtist) {
		if (YesOrNo("\nWould you like to create an artist?:\n 0 = No\n 1 = Yes\n> ")) {
			auto artist = createArtist();
			this->audioLibrary->createAudio(std::make_shared<Audio>(audioName, audioDescription, audioDuration, artist));
			SendSuccess("Created Audio: " + audioName + " | Description: " + audioDescription + " | Duration: " + std::to_string(audioDuration) + " | Artist: " + artist->getName() + ".\n");
		}
		else if (this->artists.size() > 0) {
			std::cout << "Artists:\n";
			for (int i = 0; i < artists.size(); i++) {
				std::cout << '[' << i << "] '" << artists[i]->getName() << "'\n";
			}
			int artistIndex;
			do {
				std::cout << "Please enter the index of the artist you want to add to this audio\n > ";
				std::cin >> artistIndex;
				if (!std::cin.fail() && artistIndex >= 1 && artistIndex <= artists.size()) {
					break;
				}
				SendError("\nError: Please enter a number between 1 and " + std::to_string(artists.size()) + "\n");
				std::cin.clear();
				std::cin.ignore(256, '\n');
			} while (true);
			this->audioLibrary->createAudio(std::make_shared<Audio>(audioName, audioDescription, audioDuration, artists[artistIndex - 1]));
			SendSuccess("Created Audio: " + audioName + " | Description: " + audioDescription + " | Duration: " + std::to_string(audioDuration) + " | Artist: " + artists[artistIndex]->getName() + ".\n");
		}
		else {
			SendError("There are no artists available.\n");
			this->audioLibrary->createAudio(std::make_shared<Audio>(audioName, audioDescription, audioDuration));
			SendSuccess("Created Audio: " + audioName + " | Description: " + audioDescription + " | Duration: " + std::to_string(audioDuration) + ".\n");
		}
	}
	else {
		this->audioLibrary->createAudio(std::make_shared<Audio>(audioName, audioDescription, audioDuration));
		SendSuccess("Created Audio: " + audioName + " | Description: " + audioDescription + " | Duration: " + std::to_string(audioDuration) + ".\n");
	}
}

/// <summary>
/// Displays the inputted audio’s details
/// </summary>
/// <param name="audio">Audio to be printed</param>
void Menu::viewAudioDetails(std::shared_ptr<Audio> audio) {
	auto artist = audio->getArtist();
	if (artist != nullptr) {
		std::cout << "Audio: " << audio->getName() << "\n Audio Description: " << audio->getDescription() << "\n Artist: " << audio->getArtist() << "\n Duration: " << audio->getDuration() << "\n";
	}
	else {
		std::cout << "Audio: " << audio->getName() << "\n Audio Description: " << audio->getDescription() << "\n Duration: " << audio->getDuration() << "\n";
	}
}

/// <summary>
/// Asks the user to decide which property to update in the inputted audio
/// </summary>
/// <param name="audioName">Audio name</param>
/// <param name="audio">Audio to be changed</param>
void Menu::updateAudio(std::string audioName, std::shared_ptr<Audio> audio)
{
	while (true) {
		int selection;
		std::cout << "Which property of the Audio do you want to edit?\n 1) Name\n 2) Description\n 3) Artist\n 4) Duration\n 5) Exit\n> ";
		std::cin >> selection;
		switch (selection) {
		case 1:
		{
			std::string newAudioName;
			while (true) {
				std::cout << "Please enter the Audio's new Name:\n> ";
				std::cin >> newAudioName;
				if (audioLibrary->getAudioByName(newAudioName) == nullptr)
				{
					if (!continueOperation()) {
						break;
					}
					audio->setName(newAudioName);
					SendSuccess(audioName + "'s new Name is: " + newAudioName + ".\n");
					break;
				}
				SendError("There is already an Audio file with the name '" + newAudioName + "'!\nIf you wish to update the Audio, please remove and re-add it.");
				if (!continueOperation()) {
					break;
				}
			}
			break;
		}
		case 2:
		{
			std::string newAudioDescription;
			std::cout << "Please enter the Audio's Description: ";
			std::cin >> newAudioDescription;
			if (continueOperation()) {
				audio->setDescription(newAudioDescription);
				SendSuccess(audioName + "'s new Description is: " + newAudioDescription + ".\n");
			}
			break;
		}
		case 3:
		{
			if (YesOrNo("\nWould you like to create an artist?:\n 0 = No\n 1 = Yes\n> ")) {
				auto artist = createArtist();
				if (continueOperation()) {
					audio->setArtist(artist);
					SendSuccess(audioName + "'s new Artist is: " + artist->getName() + ".\n");
				}
			}
			else if (this->artists.size() > 0) {
				std::cout << "Artists:\n";
				for (int i = 0; i < artists.size(); i++) {
					std::cout << '[' << i << "] '" << artists[i]->getName() << "'\n";
				}
				int artistIndex;
				do {
					std::cout << "Please enter the index of the artist you want to add to this audio\n > ";
					std::cin >> artistIndex;
					if (!std::cin.fail() && artistIndex >= 1 && artistIndex <= artists.size()) {
						break;
					}
					SendError("\nError: Please enter a number between 1 and " + std::to_string(artists.size()) + "\n");
					std::cin.clear();
					std::cin.ignore(256, '\n');
				} while (true);
				if (!continueOperation()) {
					break;
				}
				audio->setArtist(artists[artistIndex]);
				SendSuccess(audioName + "'s new Artist is: " + artists[artistIndex]->getName() + ".\n");
			}
			else {
				SendError("There are no artists available. Unable to edit the audio's artist.\n");
			}
			break;
		}
		case 4:
		{
			float newAudioDuration;
			while (true) {
				std::cout << "Please enter the Audio's new Duration: ";
				std::cin >> newAudioDuration;
				if (!std::cin.fail()) {
					break;
				}
				SendError("Error: Numbers only.\n");
				std::cin.clear();
				std::cin.ignore(256, '\n');
			}
			if (!continueOperation()) {
				break;
			}
			audio->setDuration(newAudioDuration);
			break;
		}
		case 5:
		{
			return;
		}
		}
	}
}

/// <summary>
/// Removes the inputted audio from the program
/// </summary>
/// <param name="audioName">Audio name</param>
/// <param name="audio">Audio to be deleted</param>
void Menu::removeAudio(std::string audioName, std::shared_ptr<Audio> audio) {
	if (!continueOperation()) {
		return;
	}
	if (audioLibrary->removeAudio(audio)) {
		if (playlists.getCount() > 0) {
			auto temp = playlists.getHead();
			do
			{
				temp->data->removeAudio(audio);
				temp = temp->next;
			} while (temp != nullptr && temp != playlists.getHead());
		}
		SendSuccess("Removed '" + audio->getName() + "' from the entire Application.\n");
	}
	else {
		SendError("Unable to find Audio with the name '" + audioName + "'.\n");
	}
}

/// <summary>
/// Prints out that the inputted audio is playing
/// </summary>
/// <param name="audioName">Audio Name</param>
/// <param name="audio">Audio to be played</param>
void Menu::playAudio(std::string audioName, std::shared_ptr<Audio> audio) {
	audio->play();
}

/// <summary>
/// Sub menu for handling playlists
/// </summary>
void Menu::viewPlaylistMenu()
{
	while (true) // Loop to check if user has inputted correct data type
	{
		int menuSelection;
		while (true) {
			std::cout << "=Playlist Menu=\n1) Create Playlist\n2) Search and preview Playlist\n3) Generate 3-5 Playlists\n4) Exit\n> ";
			std::cin >> menuSelection;
			switch (menuSelection) {
			case 1:
			{
				createPlaylist();
				break;
			}
			case 2:
			{
				while (true) {
					displayAllPlaylists();
					std::string playlistName;
					std::shared_ptr<Playlist> playlist = askForPlaylist(playlistName);
					if (playlist != nullptr) {
						while (true) {
							int selection;
							std::cout << playlistName << ":\n1) View Playlist Audios\n2) Add Audio to Playlist\n3) Remove Audio from Playlist\n4) Remove Playlist\n5) Play all Audios in Playlist\n> ";
							std::cin >> selection;
							switch (selection) // Menu system
							{
							case 1:
								viewPlaylist(playlist);
								break;
							case 2:
								addAudioToPlaylist(playlist);
								break;
							case 3:
								removeAudioFromPlaylist(playlist);
								break;
							case 4:
								removePlaylist(playlist);
								break;
							case 5:
								playlist->playAllAudio();
								break;
							default:
								SendError("Invalid Selection\n");
								break;
							}
							if (YesOrNo("Do you want to finish editing '" + playlistName + "'?\n 0 = No\n 1 = Yes\n> ")) {
								return;
							}
						}
					}
					if (YesOrNo("Do you want finish editing the playlists?\n 0 = No\n 1 = Yes\n> ")) {
						break;
					}
				}
				break;
			}
			case 3:
			{
				generatePlaylist();
				break;
			}
			case 4:
			{
				return;
			}
			}
		}
	}
}

/// <summary>
/// Sub menu for handling Artist
/// </summary>
void Menu::viewArtistMenu()
{
	while (true) // Loop to check if user has inputted correct data type
	{
		int menuSelection;
		while (true) {
			std::cout << "=Artist Menu=\n1) Create Artist\n2) Delete Artist\n3) Generate 3-5 Artist\n4) Exit\n> ";
			std::cin >> menuSelection;
			switch (menuSelection) {
			case 1:
			{
				createArtist();
				break;
			}
			case 2:
			{
				removeArtist();
				break;
			}
			case 3:
			{
				generateArtists();
				break;
			}
			case 4:
			{
				return;
			}
			}
		}
	}
}

/// <summary>
/// Lists all the Audio inside of the Playlist
/// </summary>
/// <param name="playlist"></param>
void Menu::viewPlaylist(std::shared_ptr<Playlist> playlist) {
	std::cout << "All Audio files in the Playlist: " << playlist->getAllAudio();
}

/// <summary>
/// Asks the user which Audio to add to the Audio parameter
/// </summary>
/// <param name="playlist">Playlist to add the Audio into</param>
void Menu::addAudioToPlaylist(std::shared_ptr<Playlist> playlist) {
	if (audioLibrary->getAudioCount() == 0) {
		SendError("There are no audio files in this Application. Please add an Audio file.\n");
		return;
	}
	if (playlist != nullptr) {
		displayAllAudio();
		std::string audioName;
		std::shared_ptr<Audio> audio = askForAudio(audioName, audioLibrary);
		if (audio != nullptr) {
			if (playlist->createAudio(audio)) {
				SendSuccess("'" + audioName + "' was added to the playlist '" + playlist->getName() + "'.\n");
			}
			else {
				SendError("Unable to add '" + audioName + "' to the playlist. '" + audioName + "' is already in the playlist.");
			}
		}
	}
}

/// <summary>
/// Asks the user which audio to remove from the inputted playlist
/// </summary>
/// <param name="playlist"></param>
void Menu::removeAudioFromPlaylist(std::shared_ptr<Playlist> playlist) {
	viewPlaylist(playlist);
	std::string audioName;
	std::shared_ptr<Audio> audio = askForAudio(audioName, playlist);
	if (audio != nullptr) {
		playlist->removeAudio(audio);
		SendSuccess("'" + audioName + "' was removed from the playlist '" + playlist->getName() + "'.\n");
	}
}

/// <summary>
/// Removes the inputted playlist from the program
/// </summary>
/// <param name="playlist"></param>
void Menu::removePlaylist(std::shared_ptr<Playlist> playlist) {
	if (playlists.removeData(playlist)) {
		SendSuccess("Removed Playlist '" + playlist->getName() + "' from the Application.\n");
	}
	else {
		SendError("Unable to Remove Playlist '" + playlist->getName() + "' from the Application.\n");
	}
}

/// <summary>
/// Asks the user to input a name to create an artist
/// </summary>
/// <returns></returns>
std::shared_ptr<Artist> Menu::createArtist() {
	std::string artistName;
	std::cout << "Please enter the Artist's Name: ";
	std::cin >> artistName;
	auto artist = std::make_shared<Artist>(artistName);
	this->artists.push_back(artist);
	SendSuccess("Created Artist: " + artistName + ".\n\n");
	return artist;
}

/// <summary>
/// Removes the artist from the program
/// </summary>
void Menu::removeArtist() {
	displayAllArtists();
	while (true) {
		std::string artistName;
		std::cout << "Please enter the Artist's Name you want to remove: ";
		std::cin >> artistName;
		for (int i = 0; i < artists.size(); i++) {
			if (artists[i]->getName() == artistName) {
				SendSuccess("Removed Artist: " + artistName + ".\n\n");
				artists.erase(artists.begin() + i);
				return;
			}
		}
		SendError("Unable to find Artist: " + artistName + ".\n\n");
		if (!continueOperation()) {
			return;
		}
	}
}

/// <summary>
///  Asks the user to input a name to create a new playlist 
/// </summary>
void Menu::createPlaylist() {
	std::string playlistName;
	std::cout << "Please enter the Playlist's Name: ";
	std::cin >> playlistName;
	playlists.insert(std::make_shared<Playlist>(playlistName));
	SendSuccess("Created playlist '" + playlistName + "'.\n\n");
}

/// <summary>
/// Goes through all the audio in the playlist and plays them one at a time, asking if the user wants to continue
/// </summary>
void Menu::playAllAudioInPlaylist()
{
	if (playlists.getCount() == 0) {
		SendError("There are no playlists in this Application. Please add a playlist.\n");
		return;
	}
	displayAllPlaylists();
	std::string playlistName;
	std::shared_ptr<Playlist> playlist = askForPlaylist(playlistName);
	if (playlist != nullptr)
	{
		std::cout << "Now playing " << playlist->getName() << "\n";
		playlist->playAllAudio();
	}
}

/// <summary>
/// Goes through all the audio in the program and plays them one at a time, asking if the user wants to continue
/// </summary>
void Menu::playAllAudioInProgram()
{
	std::cout << "Now playing all the audio files in this application.\n";
	audioLibrary->playAllAudio();
}

/// <summary>
/// Ask user if they would like to continue operation
/// </summary>
/// <returns>True = continue / False = stop</returns>
bool Menu::continueOperation() {
	return YesOrNo("\nWould you like to continue:\n 0 = No\n 1 = Yes\n> ");
}

bool Menu::YesOrNo(std::string question) {
	bool confirmation = false;
	while (true) {
		std::cout << question;
		std::cin >> confirmation;
		if (!std::cin.fail()) {
			break;
		}
		SendError("\nError: 0 or 1");
		std::cin.clear();
		std::cin.ignore(256, '\n');
	}
	std::cout << "\n";
	return confirmation;
}

std::shared_ptr<Audio> Menu::askForAudio(std::string& audioName, std::shared_ptr<AudioList> audioList)
{
	if (audioList->getAudioCount() == 0) {
		SendError("There are no audio files in this Application. Please add an Audio file.\n");
		return nullptr;
	}
	std::shared_ptr<Audio> audio = nullptr;
	while (true) {
		std::cout << "Please enter the Audio's Name: ";
		std::cin >> audioName;
		audio = audioList->getAudioByName(audioName);
		if (audio != nullptr) {
			break;
		}
		SendError("Unable to find Audio with the name '" + audioName + "'.\n");
		if (!continueOperation()) {
			return nullptr; // EXIT FUNCTION
		}
		std::cin.clear();
		std::cin.ignore(256, '\n');
	}
	return audio;
}

std::shared_ptr<Playlist> Menu::askForPlaylist(std::string& playlistName)
{
	if (playlists.getCount() == 0) {
		SendError("There are no playlists in this Application. Please add a playlist.\n");
		return nullptr;
	}
	while (true) {
		std::cout << "Please enter the Playlist's Name: ";
		std::cin >> playlistName;
		auto temp = playlists.getHead();
		do
		{
			if (playlistName == temp->data->getName()) {
				return temp->data;
			}
			temp = temp->next;
		} while (temp != nullptr && temp != playlists.getTail());
		SendError("Unable to find Playlist with the name '" + playlistName + "'.\n");
		if (!continueOperation()) {
			return nullptr; // EXIT FUNCTION
		}
		std::cin.clear();
		std::cin.ignore(256, '\n');
	}
	return nullptr;
}

void Menu::displayAllAudio()
{
	std::cout << "All Audio files in the Program: " << audioLibrary->getAllAudio();
}

void Menu::displayAllPlaylists() {
	std::cout << "All Playlists in the Program: ";
	std::string result = "";
	if (this->playlists.getCount() > 0)
	{
		auto temp = this->playlists.getHead();
		do {
			result += "||" + temp->data->getName();
			temp = temp->next;
		} while (temp != nullptr && temp != this->playlists.getTail());
		result += "||";
	}
	result += "\n";
	std::cout << result;
}

void Menu::displayAllArtists() {
	std::cout << "All Artists in the Program: ";
	std::string result = "";
	for (int i = 0; i < artists.size(); i++) {
		result += "||" + artists[i]->getName();
	}
	result += "||\n";
	std::cout << result;
}

void Menu::generateAudioFiles()
{
	int amountOfAudio = 3 + rand() % 3;
	for (int i = 0; i < amountOfAudio; i++) {
		std::string randomName = random_string(5);	// Random 5 characters
		std::string randomDescription = random_string(5);
		int randomDuration = 1 + rand() % 30;
		audioLibrary->createAudio(std::make_shared<Audio>(randomName, randomDescription, randomDuration));
	}
	SendSuccess(std::to_string(amountOfAudio) + " Audio Files have been generated.\n");
}

void Menu::generatePlaylist()
{
	int amountOfPlaylist = 3 + rand() % 3;
	for (int i = 0; i < amountOfPlaylist; i++) {
		std::string randomName = random_string(5);	// Random 5 characters
		playlists.insert(std::make_shared<Playlist>(randomName));
	}
	SendSuccess(std::to_string(amountOfPlaylist) + " Playlists have been generated.\n");
}

void Menu::generateArtists()
{
	int amountOfArtist = 3 + rand() % 3;
	for (int i = 0; i < amountOfArtist; i++) {
		std::string randomName = random_string(5);	// Random 5 characters
		artists.push_back(std::make_shared<Artist>(randomName));
	}
	SendSuccess(std::to_string(amountOfArtist) + " Artists have been generated.\n");
}

/// <summary>
/// Send success message with green colour
/// </summary>
/// <param name="successMessage">Raw string</param>
void Menu::SendSuccess(std::string successMessage) {
	SetConsoleTextAttribute(hConsole, GREEN);
	std::cout << successMessage;
	SetConsoleTextAttribute(hConsole, WHITE);
}

/// <summary>
/// Send error message with red colour
/// </summary>
/// <param name="errorMessage">Raw string</param>
void Menu::SendError(std::string errorMessage) {
	SetConsoleTextAttribute(hConsole, RED);
	std::cout << errorMessage;
	SetConsoleTextAttribute(hConsole, WHITE);
}

/// <summary>
/// Send Error message with red and grey colour
/// </summary>
/// <param name="errorMessage">Raw string</param>
/// <param name="extraMessage">Raw string</param>
void Menu::SendError(std::string errorMessage, std::string extraMessage) {
	SetConsoleTextAttribute(hConsole, RED);
	std::cout << errorMessage;
	SetConsoleTextAttribute(hConsole, GREY);
	std::cout << extraMessage;
	SetConsoleTextAttribute(hConsole, WHITE);
}