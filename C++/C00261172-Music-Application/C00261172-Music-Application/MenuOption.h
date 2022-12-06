#pragma once
#include <iostream>
#include <string>
#include <functional>

#include "Console.h"

#include <memory>
#include <variant>

struct MenuOption {
	virtual bool handle(int keyCode, bool isArrowKey) = 0;
	void display() {
		auto currentStageText = stageText[this->stage];
		if (std::holds_alternative<std::string>(currentStageText)) {
			std::cout << std::get<std::string>(currentStageText);
		}
		else if (std::holds_alternative<std::pair<std::string, std::variant<std::shared_ptr<int>, std::shared_ptr<std::string>>>>(currentStageText)) {
			auto currentStageTextWithVariable = std::get<std::pair<std::string, std::variant<std::shared_ptr<int>, std::shared_ptr<std::string>>>>(currentStageText);
			if (std::holds_alternative<std::shared_ptr<std::string>>(currentStageTextWithVariable.second)) {
				std::cout << currentStageTextWithVariable.first << *std::get<std::shared_ptr<std::string>>(currentStageTextWithVariable.second);
			}
			else if (std::holds_alternative<std::shared_ptr<int>>(currentStageTextWithVariable.second)) {
				std::cout << currentStageTextWithVariable.first << *std::get<std::shared_ptr<int>>(currentStageTextWithVariable.second);
			}
		}
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
			result = true;
			return false;
		case VK_RETURN:
			return true;
		default:
			return false;
		}
	}

	bool inputText(std::string& text, int keyCode, bool isArrowKey)
	{
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
	std::string heading;
	short stage = 0;
	std::vector<std::variant<std::string, std::pair<std::string, std::variant<std::shared_ptr<int>, std::shared_ptr<std::string>>>>>
		stageText{};
};