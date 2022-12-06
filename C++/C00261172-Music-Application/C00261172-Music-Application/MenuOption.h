#pragma once
#include <iostream>
#include <string>
#include <functional>

#include "Console.h"

struct MenuOption {
	virtual bool handle(int keyCode, bool isArrowKey) = 0;
	void display() {
		std::cout << text;
	}
	/// <summary>
	/// Use Arrow Keys / A or D to decide which option to pick
	/// </summary>
	/// <param name="result"></param>
	/// <param name="keyCode"></param>
	/// <param name="isArrowKey"></param>
	/// <returns>true if complete</returns>
	bool YesOrNo(bool& result, int keyCode, bool isArrowKey)
	{
		this->text += "\n[";
		if (result)
		{
			this->text += "N |";
			//setConsoleColor(CYAN);
			this->text += " Y";
			//resetConsoleColor();
		}
		else
		{
			//setConsoleColor(CYAN);
			this->text += "N ";
			//resetConsoleColor();
			this->text += "| Y";
		}
		this->text += "]\n";
		switch (keyCode)
		{
		case 0x4B: // Left
			if (!isArrowKey)
				return false;
		case 0x4E: // N
			result = false;
			return false;
		case 0x4D: // Right
			if (!isArrowKey)
				return false;
		case 0x59: // Y
			result = false;
			return false;
		case VK_RETURN:
			return true;
		default:
			break;
		}
	}

	bool inputText(std::string& text, int keyCode, bool isArrowKey)
	{
		this->text += text;
		std::cout << keyCode;
		switch (keyCode) {
		case VK_BACK:
			if (VK_CONTROL) {
				text = "";
			}
			else if (text.length() > 0) {
				text.pop_back();
			}
			return false;
		case VK_SPACE:
			text += " ";
			return false;
		case VK_RETURN:
			return true;
		default:
			if (!isArrowKey) {
				if (keyCode >= 97 && keyCode <= 122) { // a - z
					text += 'a' + keyCode - 97;
				}
				else if (keyCode >= 65 && keyCode <= 90) { // A - Z
					text += 'A' + keyCode - 65;
				}
				else if (keyCode >= 48 && keyCode <= 57) { // 0 - 9
					text += '0' + keyCode - 48;
				}
			}
			return false;
		}
	}

	bool inputNumber(int& number, int keyCode, bool isArrowKey)
	{
		this->text += std::to_string(number);
		switch (keyCode) {
		case VK_BACK:
		{
			if (VK_CONTROL) {
				number = 0;
			}
			else if (number > 0) {
				number /= 10;
			}
			return false;
		}
		case VK_RETURN:
		{
			return number > 0;
		}
		}
		if (keyCode >= 48 && keyCode <= 57) { // 0 - 9
			number += keyCode - 48;
		}
		return false;
	}
	std::string text;
	std::string heading;
	short stage = 0;
};