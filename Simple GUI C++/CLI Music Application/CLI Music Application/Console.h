#pragma once

// HANDLE
#include <windows.h>

// _getch
#include <stdio.h>
#include <conio.h>

// std::streamsize>::max()
#include <sstream>
#include <limits>

#include "Colour.h"

class Console {
public:
	/// <summary>
	/// Sets the console text color to the color int
	/// </summary>
	/// <param name="color"></param>
	void setConsoleColor(int color)
	{
		SetConsoleTextAttribute(hConsole, color);
	}
	/// <summary>
	/// Resets the console color to the default color
	/// </summary>
	void resetConsoleColor()
	{
		SetConsoleTextAttribute(hConsole, WHITE);
	}
	/// <summary>
	/// Clears the console.
	/// Source: https://stackoverflow.com/a/52895729
	/// </summary>
	void clearConsole() {
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
private:
	static Console* instance;
	Console() {
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	}
	HANDLE hConsole; // Console window
};