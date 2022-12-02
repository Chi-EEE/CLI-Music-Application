#include "Application.h"
#include <windows.h>
#include <iostream>
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */

void Application::run()
{
	int selectedOption = 0;
	while (true)
	{
		keyPress();
		/*if (Changed)
		{
			Changed = false;
			BuildScreen();
			BuildMenu(selectedOption);
		}
		ConsoleKeyInfo cki = getch();
		switch (cki.Key)
		{
		case ConsoleKey.UpArrow:
			if (selectedOption > 0)
			{
				Changed = true;
				selectedOption--;
			}
			break;
		case ConsoleKey.DownArrow:
			if (selectedOption < MenuOptions.Count - 1)
			{
				Changed = true;
				selectedOption++;
			}
			break;
		case ConsoleKey.Enter:
			MenuOptions.ElementAt(selectedOption).Value.DynamicInvoke();
			break;
		case ConsoleKey.Tab:
			Console.Write("\b \b");
			break;
		default:
			Console.Write("\b \b");
			break;
		}
	}*/
	}
}

char Application::keyPress()
{
	clock_t clock = std::clock();
	while (true) {
		std::cout << std::clock() - clock << "\n";
	}
	if (GetKeyState(VK_RETURN) < 0) {
		std::cout << "1";
	}
	////#ifdef _DEBUG
	//std::cout << "HI";
	//std::cout << character << '\n';
	////#endif
	return 0;
}
