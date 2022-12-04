#include "Application.h"

Application::Application()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	mainMenuOptions["My Audio Files"] = &Application::handleAudioMenu;
	mainMenuOptions["Perform Actions"] = &Application::handleAudioMenu;
	menuOptions["Add Audio"] = &Application::addAudio;
	menuOptions["Remove Audio"] = &Application::addAudio;
}

void Application::run()
{
	while (true)
	{
		if (this->changed)
		{
			this->changed = false;
			buildMainMenu();
		}
		int keyCode;
		bool isArrowKey = GetKey(keyCode);
		switch (keyCode)
		{
		case 0x48: // Up
		{
			if (isArrowKey && this->selectedMainOption > 0)
			{
				this->changed = true;
				this->selectedMainOption--;
			}
			break;
		}
		case 0x50: // Down
		{
			if (isArrowKey && this->selectedMainOption < mainMenuOptions.size() - 1)
			{
				this->changed = true;
				this->selectedMainOption++;
			}
			break;
		}
		case VK_RETURN:
		{
			this->selectedMainOptionOpened = true;
			break;
		}
		default:
		{
			std::cout << "\b \b";
			break;
		}
		break;
		}
	}
}

void Application::buildMainMenu()
{
	clear();
	std::cout << "CLI Music Application\n";
	int i = 0;
	for (const auto& option : mainMenuOptions) {
		if (i == this->selectedMainOption)
		{
			setConsoleColor(CYAN);
			if (this->selectedMainOptionOpened) {
				std::cout << LINE << "V [" << i << "] " << option.first << '\n' << LINE;
				auto it = mainMenuOptions.begin();
				std::advance(it, this->selectedMainOption);
				this->changed = true;
				this->levels++;
				(this->*(it->second))(this->selectedMainOption);
				this->levels--;
				this->changed = true;
			}
			else {
				std::cout << "> [" << i << "] " << option.first << '\n';
			}
			resetConsoleColor();
		} else {
			std::cout << "> [" << i << "] " << option.first << '\n';
		}
		i++;
	}
}

void Application::buildAudioMenu(int& selectedOption)
{
	std::cout << "Actions:\n";
	int i = 0;
	for (const auto& option : menuOptions) {
		if (i == selectedOption)
		{
			setConsoleColor(CYAN);
			Write("-> ");
			resetConsoleColor();
			std::cout << '[' << i << "] " << option.first << '\n';
		}
		else {
			Write('[' + std::to_string(i) + "] " + option.first + '\n');
		}
		i++;
	}
}

void Application::displayAudioDetails(Audio* audio, int index)
{
	setConsoleColor(BLUE);
	bool selected = (audio == audioLibrary.getNextSelectedAudio().get());
	if (selected)
	{
		Write("> ");
	}
	else
	{
		Write("> ");
	}
	std::cout << '[' << index << "] Audio Name: " << audio->getName() << '\n';
	resetConsoleColor();
	if (selected)
	{
		Artist* artist = audio->getArtist().get();
		if (artist != nullptr)
		{
			Write("  Artist Name: " + artist->getName() + '\n');
			std::cout << "  Artist Name: " << artist->getName() << '\n';
		}
		Write("  Duration: " + std::to_string(audio->getDuration()) + '\n');
		Write("  Description: \n   -" + audio->getDescription() + '\n');
	}
}

MenuExitResult Application::handleAudioMenu(int& mainMenuOptionIndex) {
	int selectedOption = 0;
	while (true)
	{
		if (this->changed)
		{
			this->changed = false;
			buildMainMenu();
			buildAudioMenu(selectedOption);
		}
		int keyCode;
		bool isArrowKey = GetKey(keyCode);
		switch (keyCode)
		{
		case 0x48: // Up
		{
			if (isArrowKey && selectedOption > 0)
			{
				this->changed = true;
				selectedOption--;
			}
			break;
		}
		case 0x50: // Down
		{
			if (isArrowKey && selectedOption < menuOptions.size() - 1)
			{
				this->changed = true;
				selectedOption++;
			}
			break;
		}
		case VK_RETURN:
		{
			auto it = menuOptions.begin();
			std::advance(it, selectedOption);
			this->changed = true;
			(this->*(it->second))();
			this->changed = true;
			break;
		}
		case VK_TAB:
		{
			if (GetKeyState(VK_SHIFT)) {
				return MenuExitResult::SHIFT_TAB;
			}
			return MenuExitResult::TAB;
		}
		case VK_ESCAPE:
		{
			return MenuExitResult::ESCAPE;
		}
		default:
		{
			std::cout << "\b \b";
			break;
		}
		break;
		}
	}
}

void Application::addAudio()
{
	bool addAudio = YesOrNo("Would you like to add a Audio file?");
	if (addAudio)
	{
		std::string name = EnterConsoleString("Please enter the Audio's Name:");

		std::string description = EnterConsoleString("Please enter the Audio's Description:");

		int duration = EnterConsoleInt("Please enter the Audio's Duration:");

		bool addArtist = YesOrNo("Do you want to add an Artist to this Audio?:");

		std::shared_ptr<Artist> artist = nullptr;
		if (addArtist)
		{
			std::string artistName = EnterConsoleString("Please enter the Artist's Name:");
			artist = std::make_shared<Artist>(artistName);
		}
		Audio newAudio = Audio(name, description, duration, artist);
		audioLibrary.addAudio(newAudio);
		buildMainMenu();
		setConsoleColor(GREEN);
		Write("- Audio Created: " + newAudio.getName() + '\n');
		resetConsoleColor();
		std::cin.ignore();
	}
}

void Application::removeAudio()
{
	bool removeAudio = YesOrNo("Would you like to remove a Audio file?");
	if (removeAudio)
	{
		std::string name = EnterConsoleString("Please enter the Audio's Name:");

		/*Audio newAudio = Audio(name, description, duration, artist);
		audioLibrary.addAudio(newAudio);
		buildMainMenu();*/
		setConsoleColor(GREEN);
		//std::cout << "- Audio Created: " << newAudio.getName() << '\n';
		resetConsoleColor();
		std::cin.ignore();
	}
}

bool Application::YesOrNo(std::string question)
{
	this->changed = true;
	bool yes = false;
	while (true)
	{
		if (changed)
		{
			changed = false;
			buildMainMenu();
			Write(question + "\n[");
			if (yes)
			{
				std::cout << "N |";
				setConsoleColor(CYAN);
				std::cout << " Y";
				resetConsoleColor();
			}
			else
			{
				setConsoleColor(CYAN);
				std::cout << "N ";
				resetConsoleColor();
				std::cout << "| Y";
			}
			std::cout << "]\n";
		}
		int keyCode;
		bool isArrowKey = GetKey(keyCode);
		if (isArrowKey) {
			switch (keyCode)
			{
			case 0x4E: // N
			case 0x4B: // Left
				if (yes)
				{
					changed = true;
					yes = false;
				}
				break;
			case 0x59: // Y
			case 0x4D: // Right
				if (!yes)
				{
					changed = true;
					yes = true;
				}
				break;
			default:
				break;
			}
		}
		else if (keyCode == VK_RETURN) {
			return yes;
		}
		else if (keyCode == VK_ESCAPE) {
			return false;
		}
	}
}

std::string Application::EnterConsoleString(std::string statement)
{
	this->changed = true;
	while (true)
	{
		buildMainMenu();
		Write(statement + "\n> ");
		std::string input;
		std::cin >> input;
		// https://stackoverflow.com/a/59690824
		if (std::cin.fail()) {
			std::cin.clear();
#pragma push_macro("max")
#undef max
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  //skip bad input
#pragma pop_macro("max")
			Write("Please enter a valid string.\n");
			_getch();
		}
		else {
			return input;
		}
	}
}

int Application::EnterConsoleInt(std::string statement)
{
	this->changed = true;
	while (true)
	{
		buildMainMenu();
		Write(statement + "\n> ");
		int input;
		std::cin >> input;
		if (std::cin.fail()) {
			std::cin.clear();
#pragma push_macro("max")
#undef max
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  //skip bad input
#pragma pop_macro("max")
			Write("Please enter a valid number.\n");
			_getch();
		}
		else {
			return input;
		}
	}
}

void Application::Write(std::string message)
{
	std::cout << std::string(this->levels * 2, ' ') << message;
}

/// <summary>
/// Source: https://stackoverflow.com/a/55918450
/// </summary>
/// <param name="keyCode">The code of the Key pressed</param>
/// <returns>Whether it is a function key or an arrow key</returns>
bool Application::GetKey(int& keyCode)
{
	keyCode = _getch();  //Will return '0'
	if (keyCode != 0x00 && keyCode != 0xE0) {
		return false;
	}
	keyCode = _getch();
	return true;
}

void Application::setConsoleColor(int color) {
	SetConsoleTextAttribute(hConsole, color);
}

void Application::resetConsoleColor() {
	SetConsoleTextAttribute(hConsole, WHITE);
}

// https://stackoverflow.com/a/52895729
void Application::clear() {
#if defined _WIN32
	system("cls");
	//clrscr(); // including header file : conio.h
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
	system("clear");
	//std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences 
#elif defined (__APPLE__)
	system("clear");
#endif
}