#pragma once
#include <string>
#include <functional>
struct MenuOption {
	std::string heading;
	std::function<bool(int, bool)> handle;
	short stage = 0;
};