#include "Application.h"

Application::Application()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	menuOptions["Add Audio"] = &Application::addAudio;
}

void Application::run()
{
	int selectedOption = 0;
	while (true)
	{
		if (this->changed)
		{
			this->changed = false;
			buildScreen();
			buildMenu(selectedOption);
		}
		wchar_t cki = keyPress();
		switch (cki)
		{
		case 0x48:
		{
			if (selectedOption > 0)
			{
				this->changed = true;
				selectedOption--;
			}
			break;
		}
		case 0x50:
		{
			if (selectedOption < menuOptions.size() - 1)
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
			(this->*(it->second))();
			break;
		}
		case VK_TAB:
		{
			std::cout << "\b \b";
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

void Application::buildScreen()
{
	clear();
	std::cout << "My Audio Files: \n" << LINE << "\n";
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
		//DisplayAudioDetails(selectedAudio, index);
		selectedAudio = this->audioLibrary.getNextSelectedAudio();
	} while (firstSelectedAudio != selectedAudio);
	std::cout << LINE << "\n";
}

void Application::buildMenu(int selectedOption)
{
	std::cout << "Actions:\n";
	int i = 0;
	for (const auto& option : menuOptions) {
		if (i == selectedOption)
		{
			setConsoleColor(CYAN);
			std::cout << "-> ";
			resetConsoleColor();
		}
		std::cout << '[' << i << "] " << option.first << '\n';
		i++;
	}
}

void Application::addAudio()
{
	bool addAudio = YesOrNo("Would you like to add a Audio file?");
	if (addAudio)
	{
		/*string name = EnterConsoleString("Please enter the Audio's Name:");

		string description = EnterConsoleString("Please enter the Audio's Description:");

		int duration = EnterConsoleInt("Please enter the Audio's Duration:");

		bool addArtist = YesOrNo("Do you want to add an Artist to this Audio?:");

		Artist ? artist = null;
		if (addArtist)
		{
			string artistName = EnterConsoleString("Please enter the Artist's Name:");
			artist = new(artistName);
		}
		Audio newAudio = new(name, description, duration, artist);
		AudioLibrary.AddMusic(newAudio);
		BuildScreen();
		Console.ForegroundColor = ConsoleColor.Green;
		Console.WriteLine("- Audio Created: " + newAudio.Name);
		ResetConsoleColor();
		Console.ReadKey(true);
		Changed = true;*/
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
				std::cout << "N|";
				setConsoleColor(CYAN);
				std::cout << "Y";
				resetConsoleColor();
			}
			else
			{
				setConsoleColor(CYAN);
				std::cout << "N";
				resetConsoleColor();
				std::cout << "|Y";
			}
			std::cout << "]\n";
		}
		wchar_t cki = keyPress();
		switch (cki)
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
		case VK_RETURN:
			return yes;
		default:
			std::cout << "\b \b";
			break;
		}
	}
}

// https://stackoverflow.com/a/55918450
int Application::keyPress()
{
	int ch = _getch();  //Will return '0'
	if (ch != 0x00 && ch != 0xE0) {
		return ch;
	}
	ch = _getch();
	return ch;
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