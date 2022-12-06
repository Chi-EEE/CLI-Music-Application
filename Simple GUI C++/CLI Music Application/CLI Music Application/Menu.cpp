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
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		const size_t max_index = (sizeof(charset) - 1);
		return charset[rand() % max_index];
	};
	std::string str(length, 0);
	std::generate_n(str.begin(), length, randchar);
	return str;
}

void Menu::run() {
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	int selection = 0;
	while (true) // MAIN LOOP
	{
		while (true) // Loop to check if user has inputted correct data type
		{
			// Starting text
			std::cout << "CLI Music Application by Chi\n\t1) Add Audio\n\t2) Remove Audio\n\t3) Play Audio\n\t4) Create Playlist\n\t5) Add Audio to Playlist\n\t6) Remove Audio from Playlist\n\t7) Play all Audio from Playlist\n\t8) Play All Audio in Program\n\n> ";
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
			createPlaylist();
			break;
		case 5:
			addAudioToPlaylist();
			break;
		case 6:
			removeAudioFromPlaylist();
			break;
		case 7:
			playAllAudioInPlaylist();
			break;
		case 8:
			playAllAudioInProgram();
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

/// <summary>
/// Ask user to input a name for the set,
/// if another set is found with the name then
/// repeat the question.
/// If not then continue to the next question
/// Ask the user for the set size.
/// If the inputted value is not a number then
/// repeat the question.
/// If not then create the set with the given values with
/// Set name being the index for the unordered_map to reference by and
/// Set Size being the size of the set
/// </summary>
void Menu::addAudio() {
	//std::string setName;
	//int setSize = 1;

	//while (true) {
	//	std::cout << "Enter the name of the new set: ";
	//	std::cin >> setName;
	//	if (!findSet(setName)) { // Check if set isn't inside of the unordered_map
	//		break;
	//	}
	//	SendError("\nAnother Set with the same name was already made.\n\n");
	//	if (!continueOperation()) {
	//		return; // EXIT FUNCTION
	//	}
	//}
	//while (true) {
	//	std::cout << "\nEnter the size of the new set: \n";
	//	std::cin >> setSize;
	//	if (!std::cin.fail()) {
	//		break;
	//	}
	//	SendError("Error: Numbers only.\n");
	//	std::cin.clear();
	//	std::cin.ignore(256, '\n');
	//}
	//sets[setName] = std::make_unique<Set>(setSize); // Create a unique pointer for the set
	//SendSuccess("Set: " + setName + " | Size: " + std::to_string(setSize) + " was created.\n\n");
}

/// <summary>
/// Ask user for set and ask them for a value to add into the Set,
/// if the Set is full, then display that it's full
/// if the Set already has the value, then display that it already has the value
/// if the Set doesn't have the value and it isn't full then display that it was successful
/// </summary>
void Menu::removeAudio() {
	//listSets();
	//std::string setName;
	//bool continueAdd = false;

	//setName = askForSet("");
	//if (setName == "") { return; }

	//while (true)
	//{
	//	std::string value;
	//	std::cout << "Please enter the value that you are going to put into the Set '" << setName << "':\n";
	//	std::cin >> value;
	//	std::cout << "\n";
	//	switch (sets[setName]->add(value)) {
	//	case SetResult::Success:
	//		SendSuccess("Successfully added '" + value + "' to Set: " + setName + "\n");
	//		break;
	//	case SetResult::AlreadyIn:
	//		SendError("Unable to add '" + value + "' to Set: " + setName + "\n", "Key is already inside of the Set.\n");
	//		break;
	//	case SetResult::Full:
	//		SendError("Unable to add '" + value + "' to Set: " + setName + "\n", "Set is full.\n");
	//		break;
	//	}
	//	if (!continueOperation()) {
	//		return; // EXIT FUNCTION
	//	}
	//}
}

/// <summary>
/// Ask the user for a Set and
/// Call the print function in the Set class
/// </summary>
void Menu::playAudio() {
	//listSets();
	//std::string setName;

	//setName = askForSet("");
	//if (setName == "") { return; }

	//sets[setName]->print();
	//std::cout << "\n";
}

/// <summary>
/// Ask for 2 Sets and remove all the keys inside of set1 that are also in set2
/// </summary>
void Menu::createPlaylist() {
	/*listSets();
	std::string setName1;
	std::string setName2;

	setName1 = askForSet("[1] ");
	if (setName1 == "") { return; }
	setName2 = askForSet("[2] ");
	if (setName2 == "") { return; }

	SendSuccess("Removed " + std::to_string(sets[setName1]->removeAll(sets[setName2])) + " keys inside of the Set: " + setName1 + "\n\n");*/
}

/// <summary>
/// Ask the user for Set and find the value they inputted inside of the Set
/// </summary>
void Menu::addAudioToPlaylist() {
	/*listSets();
	std::string setName;
	std::string input;

	setName = askForSet("");
	if (setName == "") { return; }

	std::cout << "Enter a value that will want to find in the Set: " << setName << "\n";
	std::cin >> input;

	std::cout << "\n";
	if (sets[setName]->contains(input)) {
		SendSuccess("Found '" + input + "' inside of the Set: " + setName + "\n");
	}
	else {
		SendError("'" + input + "' wasn't found inside of the Set: " + setName + "\n");
	}
	std::cout << "\n";*/
}

/// <summary>
/// Ask user for set.
/// If they have entered a valid Set then
/// Ask user to delete a key from the Set,
/// If the key isn't found then warn them
/// If the key is found then remove the key from the Set and send them a success message
/// </summary>
void Menu::removeAudioFromPlaylist() {
	//listSets();
	//std::string setName;
	//std::string input;

	//setName = askForSet("");
	//if (setName == "") { return; }
	//sets[setName]->print();
	//std::cout << "\n";

	//while (true) {
	//	while (true) {
	//		std::cout << "Enter a value you want to remove from the Set: " << setName << "\n";
	//		std::cin >> input;
	//		if (sets[setName]->remove(input)) {
	//			break;
	//		}
	//		SendError("'" + input + "' wasn't found inside of the Set: " + setName + "\n\n");
	//		if (!continueOperation()) {
	//			return;
	//		}
	//	}
	//	SendSuccess("'" + input + "' was removed from the Set: " + setName + "\n\n");
	//	if (!continueOperation()) {
	//		return;
	//	}
	//}
}

/// <summary>
/// Ask user for set,
/// Ask user for key to find in set.
/// If key is found in Set then print out it's index position
/// Else send error
/// </summary>
void Menu::playAllAudioInPlaylist() {
	/*listSets();
	std::string setName;
	std::string input;

	setName = askForSet("");
	if (setName == "") { return; }
	sets[setName]->print();
	std::cout << "\n";

	int keyIndex = 0;

	while (true) {
		std::cout << "Enter a value that will want to find it's index in the Set: " << setName << "\n";
		std::cin >> input;
		keyIndex = sets[setName]->search(input);
		if (keyIndex) {
			break;
		}
		SendError("'" + input + "' wasn't found inside of the Set: " + setName + "\n\n");
		if (!continueOperation()) {
			return;
		}
	}
	SendSuccess("'" + input + "' was found inside of the Set: " + setName + " at index position: " + std::to_string(keyIndex - 1) + "\n\n");*/
}

/// <summary>
/// Ask user for set and clear the set
/// </summary>
void Menu::playAllAudioInProgram() {
	/*listSets();
	std::string setName;

	setName = askForSet("");
	if (setName == "") { return; }
	sets[setName]->clear();

	SendSuccess("Set: '" + setName + "' was cleared!\n\n");*/
}

/// <summary>
/// Ask user for two set names and call the Set equals method with the second Set as the parameter
///	If the first set equals second set then
/// Send success else Send error
/// </summary>
//void Menu::equalsSet() {
//	listSets();
//	std::string setName1;
//	std::string setName2;
//
//	setName1 = askForSet("[1] ");
//	if (setName1 == "") { return; }
//	setName2 = askForSet("[2] ");
//	if (setName2 == "") { return; }
//
//	if (sets[setName1]->equals(sets[setName2])) {
//		SendSuccess("Set: '" + setName1 + "' equals to Set: " + setName2 + "!\n\n");
//	}
//	else {
//		SendError("Set: '" + setName1 + "' does not equals to Set: " + setName2 + "!\n\n");
//	}
//}

/// <summary>
/// Ask user if they would like to continue operation
/// </summary>
/// <returns>True = continue/ False = stop</returns>
bool Menu::continueOperation() {
	bool continueOp = false;
	while (true) {
		std::cout << "Would you like to continue:\n\t0 = No\n\t1 = Yes\n\nEnter an Option: ";
		std::cin >> continueOp;
		if (!std::cin.fail()) {
			break;
		}
		SendError("\nError: 0 or 1\n\n");
		std::cin.clear();
		std::cin.ignore(256, '\n');
	}
	std::cout << "\n";
	return continueOp;
}

/// <summary>
/// Checks if the set is available in the unordered_map
/// </summary>
/// <param name="setName">Set Name</param>
/// <returns>True = Found | False = not Found</returns>
bool Menu::findSet(std::string setName) {
	return false;
	//return sets.find(setName) != sets.end();
}

/// <summary>
/// Ask the user for a set name,
/// If a set is found then break out of the loop,
/// If there is no set then the user can exit out of the loop
/// </summary>
/// <param name="index"></param>
/// <returns></returns>
std::string Menu::askForSet(std::string index) {
	std::string setName;
	while (true)
	{
		std::cout << index << "Enter the name of your set: ";
		std::cin >> setName;
		// This if statement checks if the name of the set is in the unordered_map
		if (findSet(setName)) {
			break;
		}
		SendError("\nSet not found.\n\n");
		if (!continueOperation()) {
			return ""; // EXIT FUNCTION
		}
	}
	std::cout << "\n";
	return setName;
}

/// <summary>
/// Loop through all of the keys inside of the sets unordered_map
/// </summary>
void Menu::listSets() {
	/*std::string setsString;
	for (std::unordered_map<std::string, std::unique_ptr<Set>>::iterator iter = sets.begin(); iter != sets.end(); ++iter)
	{
		setsString = setsString + "||" + iter->first;
	}
	setsString = setsString + "||\n\n";
	std::cout << "Set Names: " << setsString;*/
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