#include "Application.h"

Application::Application()
{
	initaliseMenus();
}

void Application::initaliseMenus()
{
	std::shared_ptr<Menu> audioMenu(new Menu);
	audioMenu->heading = "View Audio";

	std::shared_ptr<Menu> actionMenu(new Menu);
	actionMenu->heading = "Perform Actions";

	std::shared_ptr<AddAudio> addAudioOption = std::make_shared<AddAudio>(this->audioLibrary);
	addAudioOption->heading = "Add Audio";

	//std::shared_ptr<MenuOption> removeAudioOption(new MenuOption);
	//removeAudioOption->heading = "Remove Audio";
	//removeAudioOption->handle = std::bind(&Application::removeAudio, this, std::placeholders::_1, std::placeholders::_2);

	actionMenu->menuOptions.push_back(addAudioOption);
	//actionMenu->menuOptions.push_back(removeAudioOption);

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
			Console::getInstance()->clearConsole();
			// Display Main Menu Heading
			std::cout << std::get<std::shared_ptr<Menu>>(this->menuLayers[0])->heading << '\n';
			buildMenu(0);
		}
		int keyCode;
		bool isArrowKey = Console::getInstance()->getKey(keyCode);
		auto currentMenuOption = this->menuLayers[this->menuLayers.size() - 1];
		if (keyCode == VK_ESCAPE) {
			if (this->menuLayers.size() > 1) {
				if (std::holds_alternative<std::shared_ptr<Menu>>(currentMenuOption)) {
					std::shared_ptr<Menu> currentMenu = std::get<std::shared_ptr<Menu>>(currentMenuOption);
					currentMenu->selectedOption = 0;
				}
				else if (std::holds_alternative<std::shared_ptr<MenuOption>>(currentMenuOption)) {
					std::shared_ptr<MenuOption> currentMenu = std::get<std::shared_ptr<MenuOption>>(currentMenuOption);
				}
				this->menuLayers.pop_back();
				this->changed = true;
			}
		}
		else {
			if (std::holds_alternative<std::shared_ptr<MenuOption>>(currentMenuOption)) {
				bool result = std::get<std::shared_ptr<MenuOption>>(currentMenuOption)->handle(keyCode, isArrowKey);
				this->changed = true;
				if (result) {
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
		// Go through the menu options and print their text out
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
				Console::getInstance()->setConsoleColor(CYAN);
				std::cout << std::string(layerIndex * 2, ' ') << "V [" << currentMenu->selectedOption << "] " << menuOption->heading << '\n';
				Console::getInstance()->resetConsoleColor();
				buildMenu(layerIndex + 1);
			}
			else {
				Console::getInstance()->setConsoleColor(CYAN);
				std::cout << std::string(layerIndex * 2, ' ') << "> [" << currentMenu->selectedOption << "] " << menuOption->heading << '\n';
				Console::getInstance()->resetConsoleColor();
			}
		}
		else if (std::holds_alternative<std::shared_ptr<MenuOption>>(selectedMenu)) {
			std::shared_ptr<MenuOption> menuOption = std::get<std::shared_ptr<MenuOption>>(selectedMenu);
			if (layerIndex + 1 < this->menuLayers.size()) {
				Console::getInstance()->setConsoleColor(CYAN);
				std::cout << std::string(layerIndex * 2, ' ') << "V [" << currentMenu->selectedOption << "] " << menuOption->heading << '\n';
				Console::getInstance()->resetConsoleColor();
				menuOption->display();
			}
			else {
				Console::getInstance()->setConsoleColor(CYAN);
				std::cout << std::string(layerIndex * 2, ' ') << "  [" << currentMenu->selectedOption << "] " << menuOption->heading << '\n';
				Console::getInstance()->resetConsoleColor();
			}
			Console::getInstance()->resetConsoleColor();
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

//void Application::displayAudioDetails(Audio* audio, int index)
//{
//	setConsoleColor(BLUE);
//	bool selected = (audio == audioLibrary.getNextSelectedAudio().get());
//	if (selected)
//	{
//		Write("> ");
//	}
//	else
//	{
//		Write("> ");
//	}
//	std::cout << '[' << index << "] Audio Name: " << audio->getName() << '\n';
//	resetConsoleColor();
//	if (selected)
//	{
//		Artist* artist = audio->getArtist().get();
//		if (artist != nullptr)
//		{
//			Write("  Artist Name: " + artist->getName() + '\n');
//			std::cout << "  Artist Name: " << artist->getName() << '\n';
//		}
//		Write("  Duration: " + std::to_string(audio->getDuration()) + '\n');
//		Write("  Description: \n   -" + audio->getDescription() + '\n');
//	}
//}

//bool Application::addAudio(std::shared_ptr<MenuOption> menuOption, int keyCode, bool isArrowKey)
//{
//	switch (menuOption->stage)
//	{
//	case 0:
//		return true;
//		return false;
//	default:
//		break;
//	}
//	bool addAudio = YesOrNo("Would you like to add a Audio file?", keyCode, isArrowKey);
//	if (addAudio)
//	{
//		std::string name = inputText("Please enter the Audio's Name:");
//
//		std::string description = inputText("Please enter the Audio's Description:");
//
//		int duration = inputNumber("Please enter the Audio's Duration:");
//
//		bool addArtist = YesOrNo("Do you want to add an Artist to this Audio?:", keyCode, isArrowKey);
//
//		std::shared_ptr<Artist> artist = nullptr;
//		if (addArtist)
//		{
//			std::string artistName = inputText("Please enter the Artist's Name:");
//			artist = std::make_shared<Artist>(artistName);
//		}
//		Audio newAudio = Audio(name, description, duration, artist);
//		audioLibrary.addAudio(newAudio);
//		setConsoleColor(GREEN);
//		Write("- Audio Created: " + newAudio.getName() + '\n');
//		resetConsoleColor();
//		std::cin.ignore();
//	}
//}

//bool Application::removeAudio(int keyCode, bool isArrowKey)
//{
//	bool removeAudio = YesOrNo("Would you like to remove a Audio file?", keyCode, isArrowKey);
//	if (removeAudio)
//	{
//		std::string name = inputText("Please enter the Audio's Name:");
//
//		/*Audio newAudio = Audio(name, description, duration, artist);
//		audioLibrary.addAudio(newAudio);
//		buildMainMenu();*/
//		setConsoleColor(GREEN);
//		//std::cout << "- Audio Created: " << newAudio.getName() << '\n';
//		resetConsoleColor();
//		std::cin.ignore();
//	}
//}

//void Application::Write(std::string message)
//{
//	std::cout << message;
//}

int Application::mod(int left, int right) {
	return (left + right) % right;
}