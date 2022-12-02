#include "Application.h"
#include <conio.h>

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
	char character;
	std::cin >> character;
	#ifdef DEBUG
	std::cout << character << '\n';
	#endif
	return 0;
}
