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

void Menu::run() {
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	audioLibrary = std::make_shared<AudioLibrary>();

	int selection = 0;
	while (true) // MAIN LOOP
	{
		while (true) // Loop to check if user has inputted correct data type
		{
			// Starting text
			std::cout << "CLI Music Application by Chi\n\t1) Add Audio\n\t2) Remove Audio\n\t3) Play Audio\n\t4) Create Artist\n\t5) Create Playlist\n\t6) Add Audio to Playlist\n\t7) Remove Audio from Playlist\n\t8) Play all Audio from Playlist\n\n> ";
			std::cin >> selection;
			if (!std::cin.fail()) {
				break;
			}
			SendError("Error: Numbers only.\n\n");
			std::cin.clear();
			std::cin.ignore(256, '\n');
		}
		std::cout << "\n";
		switch (selection) // Menu system
		{
		case 1:
			addAudio();
			break;
		case 2:
			removeAudio();
			break;
		case 3:
			playAudio();
			break;
		case 4:
			createArtist();
			break;
		case 5:
			createPlaylist();
			break;
		case 6:
			addAudioToPlaylist();
			break;
		case 7:
			removeAudioFromPlaylist();
			break;
		case 8:
			playAllAudioInPlaylist();
			break;
		case 9:
			//generateSets();
			break;
		default:
			SendError("Invalid Selection\n\n");
			break;
		}
	}
}

///// <summary>
///// Make 3 to 5 sets with a size of 1 to 5 with a random amount of keys
///// </summary>
//void Menu::generateSets()
//{
//	std::srand(static_cast<unsigned>(time(nullptr)));		//Initalise random seed
//	int amountOfSets = 3 + rand() % 3;
//	for (int i = 0; i < amountOfSets; i++) { // Generate 3 - 5 sets
//		std::string randomString = random_string(5);	// Random 5 characters
//		int randomSize = 1 + rand() % 5;						// Make set with random 1 to 5 size
//		sets[randomString] = std::make_unique<Set>(randomSize);	// Create a unique pointer for the set with size of random
//		for (int i = 0; i < randomSize - rand() % randomSize; i++) {
//			sets[randomString]->add(random_string(5));
//		}
//	}
//	SendSuccess(std::to_string(amountOfSets) + " Sets have been generated.\n\n");
//}


void Menu::addAudio() {
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
		std::cout << "\nWould you like to add an Artist to this Audio:\n\t0 = No\n\t1 = Yes\n> ";
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
		if (this->artists.size() == 0) {
			SendError("There are no artists available.");
			if (YesOrNo("\nWould you like to create an artist?:\n\t0 = No\n\t1 = Yes\n> ")) {
				auto artist = createArtist();
				this->audioLibrary->addAudio(std::make_shared<Audio>(audioName, audioDescription, audioDuration, artist));
				SendSuccess("Created Audio: " + audioName + " | Description: " + audioDescription + " | Duration: " + std::to_string(audioDuration) + " | Artist: " + artist->getName() + ".\n\n");
			}
			else {
				this->audioLibrary->addAudio(std::make_shared<Audio>(audioName, audioDescription, audioDuration));
				SendSuccess("Created Audio: " + audioName + " | Description: " + audioDescription + " | Duration: " + std::to_string(audioDuration) + ".\n\n");
			}
		}
		else {
			if (YesOrNo("\nWould you like to create an artist?:\n\t0 = No\n\t1 = Yes\n> ")) {
				auto artist = createArtist();
				this->audioLibrary->addAudio(std::make_shared<Audio>(audioName, audioDescription, audioDuration, artist));
				SendSuccess("Created Audio: " + audioName + " | Description: " + audioDescription + " | Duration: " + std::to_string(audioDuration) + " | Artist: " + artist->getName() + ".\n\n");
			}
			else {
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
					SendError("\nError: Please enter a number between 1 and " + std::to_string(artists.size()) + "\n\n");
					std::cin.clear();
					std::cin.ignore(256, '\n');
				} while (true);
				this->audioLibrary->addAudio(std::make_shared<Audio>(audioName, audioDescription, audioDuration, artists[artistIndex - 1]));
				SendSuccess("Created Audio: " + audioName + " | Description: " + audioDescription + " | Duration: " + std::to_string(audioDuration) + " | Artist: " + artists[artistIndex]->getName() + ".\n\n");
			}
		}
	}
	else {
		this->audioLibrary->addAudio(std::make_shared<Audio>(audioName, audioDescription, audioDuration));
		SendSuccess("Created Audio: " + audioName + " | Description: " + audioDescription + " | Duration: " + std::to_string(audioDuration) + ".\n\n");
	}
}

void Menu::removeAudio() {
	displayAllAudio();

	std::string audioName;
	std::shared_ptr<Audio> audio = askForAudio(audioName, audioLibrary);
	if (audio == nullptr) {
		return; // EXIT FUNCTION
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
		SendSuccess("Removed '" + audio->getName() + "' from the entire Application.\n\n");
	}
	else {
		SendError("Unable to find Audio with the name '" + audioName + "'.\n\n");
	}
}

void Menu::playAudio() {
	displayAllAudio();
	std::string audioName;
	std::shared_ptr<Audio> audio = askForAudio(audioName, audioLibrary);
	if (audio != nullptr) {
		audio->play();
	}
}

std::shared_ptr<Artist> Menu::createArtist() {
	std::string artistName;

	std::cout << "Please enter the Artist's Name: ";
	std::cin >> artistName;
	auto artist = std::make_shared<Artist>(artistName);
	this->artists.push_back(artist);
	SendSuccess("Created Artist: " + artistName + ".\n\n");
	return artist;
}

void Menu::createPlaylist() {
	std::string playlistName;
	std::cout << "Please enter the Playlist's Name: ";
	std::cin >> playlistName;
	playlists.insert(std::make_shared<Playlist>(playlistName));
	SendSuccess("Created playlist '" + playlistName + "'.\n\n");
}

void Menu::addAudioToPlaylist() {
	if (playlists.getCount() == 0) {
		SendError("There are no playlists in this Application. Please add a playlist.\n");
		return;
	}
	if (audioLibrary->getAudioCount() == 0) {
		SendError("There are no audio files in this Application. Please add an Audio file.\n");
		return;
	}
	displayAllPlaylists();

	std::string playlistName;
	std::shared_ptr<Playlist> playlist = askForPlaylist(playlistName);
	if (playlist != nullptr) {
		displayAllAudio();
		std::string audioName;
		std::shared_ptr<Audio> audio = askForAudio(audioName, audioLibrary);
		if (audio != nullptr) {
			playlist->addAudio(audio);
			SendSuccess("'" + audioName + "' was added to the playlist '" + playlistName + "'.\n\n");
		}
	}
}

void Menu::removeAudioFromPlaylist() 
{
	if (playlists.getCount() == 0) {
		SendError("There are no playlists in this Application. Please add a playlist.\n");
		return;
	}
	if (audioLibrary->getAudioCount() == 0) {
		SendError("There are no audio files in this Application. Please add an Audio file.\n");
		return;
	}
	displayAllPlaylists();

	std::string playlistName;
	std::shared_ptr<Playlist> playlist = askForPlaylist(playlistName);
	if (playlist != nullptr) {
		std::cout << "All Audio files in the Playlist: " << playlist->getAllAudio();
		std::string audioName;
		std::shared_ptr<Audio> audio = askForAudio(audioName, playlist);
		if (audio != nullptr) {
			playlist->removeAudio(audio);
			SendSuccess("'" + audioName + "' was removed from the playlist '" + playlistName + "'.\n\n");
		}
	}
}

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

void Menu::playAllAudioInProgram()
{
	std::cout << "Now playing all the audio files in this application.\n\n";
	audioLibrary->playAllAudio();
}

/// <summary>
/// Ask user if they would like to continue operation
/// </summary>
/// <returns>True = continue / False = stop</returns>
bool Menu::continueOperation() {
	return YesOrNo("\nWould you like to continue:\n\t0 = No\n\t1 = Yes\n> ");
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
	result += "\n\n";
	std::cout << result;
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