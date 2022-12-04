﻿#include "Application.h"

Application::Application()
{
	menuOptions["Add Audio"] = &Application::addAudio;
}

void Application::run()
{
	std::pair<std::string, void()>a(std::string("HELLO"), this->addAudio); // TO FIX
	Menu menu = Menu("My Audio Files",
		{
			
		}
	);
	while (true)
	{
		int selectedOption = 0;
		MenuExitResult result = menu.listen();
		//if (this->changed)
		//{
		//	this->changed = false;
		//	buildScreen();
		//	buildMenu(selectedOption);
		//}
		//int keyCode;
		//bool isArrowKey = KeyPress(keyCode);
		//switch (keyCode)
		//{
		//case 0x48: // Up
		//{
		//	if (isArrowKey && selectedOption > 0)
		//	{
		//		this->changed = true;
		//		selectedOption--;
		//	}
		//	break;
		//}
		//case 0x50: // Down
		//{
		//	if (isArrowKey && selectedOption < menuOptions.size() - 1)
		//	{
		//		this->changed = true;
		//		selectedOption++;
		//	}
		//	break;
		//}
		//case VK_RETURN:
		//{
		//	auto it = menuOptions.begin();
		//	std::advance(it, selectedOption);
		//	(this->*(it->second))();
		//	break;
		//}
		//case VK_TAB:
		//{
		//	std::cout << "\b \b";
		//	break;
		//}
		//default:
		//{
		//	std::cout << "\b \b";
		//	break;
		//}
		//break;
		//}
	}
}

void Application::buildScreen()
{
	Console::getInstance()->clearConsole();
	std::cout << "My Audio Files: \n" << LINE;
	std::shared_ptr<Audio> firstSelectedAudio = this->audioLibrary.getSelectedAudio();
	std::shared_ptr<Audio> selectedAudio = firstSelectedAudio;
	int index = 1;
	do
	{
		if (selectedAudio == nullptr)
		{
			std::cout << "  [No Audio found]\n";
			break;
		}
		displayAudioDetails(selectedAudio.get(), index);
		selectedAudio = this->audioLibrary.getNextSelectedAudio();
	} while (firstSelectedAudio != selectedAudio);
	std::cout << LINE;
}

void Application::buildMenu(int selectedOption)
{
	std::cout << "Actions:\n";
	int i = 0;
	for (const auto& option : menuOptions) {
		if (i == selectedOption)
		{
			Console::getInstance()->setConsoleColor(CYAN);
			std::cout << "-> ";
			Console::getInstance()->resetConsoleColor();
		}
		std::cout << '[' << i << "] " << option.first << '\n';
		i++;
	}
}

void Application::displayAudioDetails(Audio* audio, int index)
{
	Console::getInstance()->setConsoleColor(BLUE);
	bool selected = (audio == audioLibrary.getNextSelectedAudio().get());
	if (selected)
	{
		std::cout << "V ";
	}
	else
	{
		std::cout << "> ";
	}
	std::cout << '[' << index << "] Audio Name: " << audio->getName() << '\n';
	Console::getInstance()->resetConsoleColor();
	if (selected)
	{
		Artist* artist = audio->getArtist().get();
		if (artist != nullptr)
		{
			std::cout << "  Artist Name: " << artist->getName() << '\n';
		}
		std::cout << "  Duration: " << audio->getDuration() << '\n';
		std::cout << "  Description: \n   -" << audio->getDescription() << '\n';
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
		buildScreen();
		Console::getInstance()->setConsoleColor(GREEN);
		std::cout << "- Audio Created: " << newAudio.getName() << '\n';
		Console::getInstance()->resetConsoleColor();
		std::cin.ignore();
	}
}

bool Application::YesOrNo(std::string question)
{
	changed = true;
	bool yes = false;
	while (true)
	{
		if (changed)
		{
			changed = false;
			buildScreen();
			std::cout << question << "\n[";
			if (yes)
			{
				std::cout << "N |";
				Console::getInstance()->setConsoleColor(CYAN);
				std::cout << " Y";
				Console::getInstance()->resetConsoleColor();
			}
			else
			{
				Console::getInstance()->setConsoleColor(CYAN);
				std::cout << "N ";
				Console::getInstance()->resetConsoleColor();
				std::cout << "| Y";
			}
			std::cout << "]\n";
		}
		int keyCode;
		bool isArrowKey = Console::getInstance()->getKey(keyCode);
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
	}
}

std::string Application::EnterConsoleString(std::string statement)
{
	changed = true;
	while (true)
	{
		buildScreen();
		std::cout << statement << "\n> ";
		std::string input;
		std::cin >> input;
		// https://stackoverflow.com/a/59690824
		if (std::cin.fail()) {
			std::cin.clear();
#pragma push_macro("max")
#undef max
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  //skip bad input
#pragma pop_macro("max")
			std::cout << "Please enter a valid string.\n";
			_getch();
		}
		else {
			return input;
		}
	}
}

int Application::EnterConsoleInt(std::string statement)
{
	changed = true;
	while (true)
	{
		buildScreen();
		std::cout << statement << "\n> ";
		int input;
		std::cin >> input;
		if (std::cin.fail()) {
			std::cin.clear();
#pragma push_macro("max")
#undef max
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  //skip bad input
#pragma pop_macro("max")
			std::cout << "Please enter a valid number.\n";
			_getch();
		}
		else {
			return input;
		}
	}
}