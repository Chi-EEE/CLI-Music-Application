#pragma once
#include <string>
#include <functional>
class MenuOption {
public:
	std::string heading;
	std::function<bool(int, bool)> handle;
	short stage = 0;
};