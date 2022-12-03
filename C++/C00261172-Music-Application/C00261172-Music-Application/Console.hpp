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
	/// <summary>
	/// Waits and outputs the key code pressed
	/// Source: https://stackoverflow.com/a/55918450
	/// </summary>
	/// <param name="keyCode">The code of the Key pressed</param>
	/// <returns>Whether it is a function key or an arrow key</returns>
	bool getKey(int& keyCode)
	{
		keyCode = _getch();  //Will return '0'
		if (keyCode != 0x00 && keyCode != 0xE0) {
			return false;
		}
		keyCode = _getch();
		return true;
	}
	static Console* getInstance() {
		return Console::instance;
	}
private:
	static Console* instance;
	Console() {
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	}
	HANDLE hConsole; // Console window
};
Console* Console::instance = new Console();