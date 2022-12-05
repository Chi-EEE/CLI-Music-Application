#include "Application.h"

Application::Application()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	initaliseMenus();
}

void Application::initaliseMenus()
{
	std::shared_ptr<Menu> audioMenu(new Menu);
	audioMenu->heading = "View Audio";

	std::shared_ptr<Menu> actionMenu(new Menu);
	actionMenu->heading = "Perform Actions";

	std::shared_ptr<MenuOption> addAudioOption = std::make_shared<MenuOption>();
	addAudioOption->heading = "Add Audio";
	addAudioOption->handle = std::bind(&Application::addAudio, this, std::placeholders::_1, std::placeholders::_2);

	std::shared_ptr<MenuOption> removeAudioOption(new MenuOption);
	removeAudioOption->heading = "Remove Audio";
	removeAudioOption->handle = std::bind(&Application::removeAudio, this, std::placeholders::_1, std::placeholders::_2);

	actionMenu->menuOptions.push_back(addAudioOption);
	actionMenu->menuOptions.push_back(removeAudioOption);

	std::shared_ptr<Menu> mainMenu(new Menu);
	mainMenu->heading = "My CLI Music Application";
	mainMenu->menuOptions.push_back(audioMenu);
	mainMenu->menuOptions.push_back(actionMenu);
	menuLayers.push_back(mainMenu);
}

void Application::run()
{
	while (true)
	{
		if (this->changed)
		{
			this->changed = false;
			clear();
			// Display Main Menu Heading
			std::cout << std::get<std::shared_ptr<Menu>>(this->menuLayers[0])->heading << '\n';
			buildMenu(0);
		}
		int keyCode;
		bool isArrowKey = GetKey(keyCode);
		auto currentMenuOption = this->menuLayers[this->menuLayers.size() - 1];
		if (keyCode == VK_ESCAPE) {
			if (this->menuLayers.size() > 1) {
				if (std::holds_alternative<std::shared_ptr<Menu>>(currentMenuOption)) {
					std::shared_ptr<Menu> currentMenu = std::get<std::shared_ptr<Menu>>(currentMenuOption);
					currentMenu->selectedOption = 0;
				}
				this->menuLayers.pop_back();
				this->changed = true;
			}
		}
		else {
			if (std::holds_alternative<std::shared_ptr<MenuOption>>(currentMenuOption)) {
				bool result = std::get<std::shared_ptr<MenuOption>>(currentMenuOption)->handle(keyCode, isArrowKey);
				if (!result) {
					if (this->menuLayers.size() > 1) {
						if (std::holds_alternative<std::shared_ptr<Menu>>(currentMenuOption)) {
							std::shared_ptr<Menu> currentMenu = std::get<std::shared_ptr<Menu>>(currentMenuOption);
							currentMenu->selectedOption = 0;
						}
						this->menuLayers.pop_back();
						this->changed = true;
					}
				}
			}
			else if (std::holds_alternative<std::shared_ptr<Menu>>(currentMenuOption)) {
				handleMenu(std::get<std::shared_ptr<Menu>>(currentMenuOption), keyCode, isArrowKey);
			}
		}
	}
}

void Application::handleMenu(std::shared_ptr<Menu> currentMenu, int keyCode, bool isArrowKey) {
	switch (keyCode)
	{
	case 0x48: // Up
		if (!isArrowKey)
			break;
	case 0x77: // W
	{
		if (currentMenu->menuOptions.size() > 0 && currentMenu->selectedOption > 0)
		{
			this->changed = true;
			currentMenu->selectedOption--;
		}
		break;
	}
	case 0x50: // Down
		if (!isArrowKey)
			break;
	case 0x73: // S
	{
		if (currentMenu->menuOptions.size() > 0 && currentMenu->selectedOption < currentMenu->menuOptions.size() - 1)
		{
			this->changed = true;
			currentMenu->selectedOption++;
		}
		break;
	}
	case VK_RETURN:
	{
		if (currentMenu->menuOptions.size() > 0) {
			auto selectedMenuOption = currentMenu->menuOptions[currentMenu->selectedOption];
			this->menuLayers.push_back(selectedMenuOption);
			this->changed = true;
		}
		break;
	}
	case VK_TAB:
	{
		if (this->menuLayers.size() > 1) {
			currentMenu->selectedOption = 0;
			this->menuLayers.pop_back();
			std::shared_ptr<Menu> parentMenu = std::get<std::shared_ptr<Menu>>(this->menuLayers[this->menuLayers.size() - 1]);
			if (GetKeyState(VK_SHIFT)) {
				parentMenu->selectedOption = mod(parentMenu->selectedOption - 1, this->menuLayers.size());
			}
			else {
				parentMenu->selectedOption = mod(parentMenu->selectedOption + 1, this->menuLayers.size());
			}
			this->changed = true;
		}
		break;
	}
	}
}

void Application::buildMenu(int layerIndex)
{
	std::shared_ptr<Menu> currentMenu = std::get<std::shared_ptr<Menu>>(this->menuLayers[layerIndex]);
	if (currentMenu->menuOptions.size() > 0) {
		for (int i = 0; i < currentMenu->selectedOption; i++) {
			if (std::holds_alternative<std::shared_ptr<Menu>>(currentMenu->menuOptions[i])) {
				std::shared_ptr<Menu> menuOption = std::get<std::shared_ptr<Menu>>(currentMenu->menuOptions[i]);
				std::cout << std::string(layerIndex * 2, ' ') << "> [" << i << "] " << menuOption->heading << '\n';
			}
			else if (std::holds_alternative<std::shared_ptr<MenuOption>>(currentMenu->menuOptions[i])) {
				std::shared_ptr<MenuOption> menuOption = std::get<std::shared_ptr<MenuOption>>(currentMenu->menuOptions[i]);
				std::cout << std::string(layerIndex * 2, ' ') << "  [" << i << "] " << menuOption->heading << '\n';
			}
		}
		auto selectedMenu = currentMenu->menuOptions[currentMenu->selectedOption];
		if (std::holds_alternative<std::shared_ptr<Menu>>(selectedMenu)) {
			std::shared_ptr<Menu> menuOption = std::get<std::shared_ptr<Menu>>(selectedMenu);
			if (layerIndex + 1 < this->menuLayers.size()) {
				setConsoleColor(CYAN);
				std::cout << std::string(layerIndex * 2, ' ') << "V [" << currentMenu->selectedOption << "] " << menuOption->heading << '\n';
				resetConsoleColor();
				buildMenu(layerIndex + 1);
			}
			else {
				setConsoleColor(CYAN);
				std::cout << std::string(layerIndex * 2, ' ') << "> [" << currentMenu->selectedOption << "] " << menuOption->heading << '\n';
				resetConsoleColor();
			}
		}
		else if (std::holds_alternative<std::shared_ptr<MenuOption>>(selectedMenu)) {
			std::shared_ptr<MenuOption> menuOption = std::get<std::shared_ptr<MenuOption>>(selectedMenu);
			setConsoleColor(CYAN);
			std::cout << std::string(layerIndex * 2, ' ') << "  [" << currentMenu->selectedOption << "] " << menuOption->heading << '\n';
			resetConsoleColor();
		}
		for (int i = currentMenu->selectedOption + 1; i < currentMenu->menuOptions.size(); i++) {
			if (std::holds_alternative<std::shared_ptr<Menu>>(currentMenu->menuOptions[i])) {
				std::shared_ptr<Menu> menuOption = std::get<std::shared_ptr<Menu>>(currentMenu->menuOptions[i]);
				std::cout << std::string(layerIndex * 2, ' ') << "> [" << i << "] " << menuOption->heading << '\n';
			}
			else if (std::holds_alternative<std::shared_ptr<MenuOption>>(currentMenu->menuOptions[i])) {
				std::shared_ptr<MenuOption> menuOption = std::get<std::shared_ptr<MenuOption>>(currentMenu->menuOptions[i]);
				std::cout << std::string(layerIndex * 2, ' ') << "  [" << i << "] " << menuOption->heading << '\n';
			}
		}
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

bool Application::addAudio(std::shared_ptr<MenuOption> menuOption, int keyCode, bool isArrowKey)
{
	switch (menuOption->stage)
	{
	case 0:
		return true;
		return false;
	default:
		break;
	}
	bool addAudio = YesOrNo("Would you like to add a Audio file?", keyCode, isArrowKey);
	if (addAudio)
	{
		std::string name = EnterConsoleString("Please enter the Audio's Name:");

		std::string description = EnterConsoleString("Please enter the Audio's Description:");

		int duration = EnterConsoleInt("Please enter the Audio's Duration:");

		bool addArtist = YesOrNo("Do you want to add an Artist to this Audio?:", keyCode, isArrowKey);

		std::shared_ptr<Artist> artist = nullptr;
		if (addArtist)
		{
			std::string artistName = EnterConsoleString("Please enter the Artist's Name:");
			artist = std::make_shared<Artist>(artistName);
		}
		Audio newAudio = Audio(name, description, duration, artist);
		audioLibrary.addAudio(newAudio);
		setConsoleColor(GREEN);
		Write("- Audio Created: " + newAudio.getName() + '\n');
		resetConsoleColor();
		std::cin.ignore();
	}
}

bool Application::removeAudio(int keyCode, bool isArrowKey)
{
	bool removeAudio = YesOrNo("Would you like to remove a Audio file?", keyCode, isArrowKey);
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

bool Application::YesOrNo(std::string question, int keyCode, bool isArrowKey)
{
	this->changed = true;
	bool yes = false;
	if (this->changed)
	{
		this->changed = false;
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

std::string Application::EnterConsoleString(std::string statement)
{
	this->changed = true;
	while (true)
	{
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
	std::cout << message;
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

int Application::mod(int left, int right) {
	return (left + right) % right;
}