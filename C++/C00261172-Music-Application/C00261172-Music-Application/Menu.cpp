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
			std::cout << "Text based Menu for Set class by Chi\n\t1) Create Set\n\t2) Add to Set\n\t3) Print Set\n\t4) Remove All from Set\n\t5) Contains in Set\n\t6) Remove From Set\n\t7) Search in Set\n\t8) Clear Set\n\t9) Equals Set\n\t10) Generate 3 - 5 Sets\n\nEnter an Option: ";
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
			break;
		case 2:
			break;
		default:
			SendError("Invalid Selection\n\n");
			break;
		}
	}
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