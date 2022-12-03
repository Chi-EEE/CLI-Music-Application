#include "Menu.h"

Menu::Menu(std::vector<std::string> options)
{
	this->options = options;
};

MenuExitResult Menu::listen(int& selectedOption)
{
	bool changed = true;
	while (true)
	{
		if (changed)
		{
			changed = false;
			for (int i = 0; i < options.size(); i++) 
			{
				if (i == selectedOption)
				{
					Console::getInstance()->setConsoleColor(CYAN);
					std::cout << "-> ";
					Console::getInstance()->resetConsoleColor();
				}
				std::cout << '[' << i << "] " << options[i] << '\n';
			}
			//buildScreen();
		}
		int keyCode;
		bool isArrowKey = Console::getInstance()->getKey(keyCode);
		switch (keyCode)
		{
		case 0x48: // Up
		{
			if (isArrowKey && selectedOption > 0)
			{
				changed = true;
				selectedOption--;
			}
			break;
		}
		case 0x50: // Down
		{
			if (isArrowKey && selectedOption < this->options.size())
			{
				changed = true;
				selectedOption++;
			}
			break;
		}
		case VK_ESCAPE:
		{
			return MenuExitResult::ESCAPE;
		}
		case VK_TAB:
		{
			return MenuExitResult::TAB;
		}
		case VK_RETURN:
		{
			return MenuExitResult::ENTER;
		}
		default:
		{
			std::cout << "\b \b";
			break;
		}
		}
	}
}