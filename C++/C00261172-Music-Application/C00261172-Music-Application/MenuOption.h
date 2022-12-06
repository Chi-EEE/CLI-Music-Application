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
	std::string text;
	std::string heading;
	short stage = 0;
};