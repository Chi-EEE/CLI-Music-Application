#pragma once
#include <string>
#include <functional>
struct MenuOption {
	std::string heading;
	std::function<void()> handle;
};