#include "Menu.h"

Menu::Menu(std::string heading, std::vector<std::variant<std::pair<std::string, std::function<void()>>, std::shared_ptr<Menu>>> options)
{
	this->heading = heading;
	this->options = options;
};

MenuExitResult Menu::listen()
{
	int selectedOption = 0;
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
				auto option = options[i];
				if (std::holds_alternative<std::pair<std::string, std::function<void()>>>(option))
				{
					std::pair<std::string, std::function<void()>> heading = std::get<std::pair<std::string, std::function<void()>>>(option);
					std::cout << '[' << i << "] " << heading.first << '\n';
				}
				else if (std::holds_alternative<std::shared_ptr<Menu>>(option))
				{
					Menu* subMenu = std::get<std::shared_ptr<Menu>>(option).get();
					std::cout << "> " << '[' << i << "] " << subMenu->heading << '\n';
				}
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
			if (isArrowKey && selectedOption < this->options.size() - 1)
			{
				changed = true;
				selectedOption++;
			}
			break;
		}
		case VK_ESCAPE:
		{
			auto option = options[selectedOption];
			if (std::holds_alternative<std::shared_ptr<Menu>>(option))
			{
				Menu* subMenu = std::get<std::shared_ptr<Menu>>(option).get();
				subMenu->listen();
			}
			else {
				return MenuExitResult::ESCAPE;
			}
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