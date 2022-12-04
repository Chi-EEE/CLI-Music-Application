#pragma once
#include <iostream> // cout
#include <vector> // vector
#include <string> // string

#include "Console.h"
#include <windows.h> // Virtual Key

#include <memory>
#include <variant>
#include <functional>

class Menu
{
public:
	Menu(std::string heading, std::vector<std::variant<std::pair<std::string, std::function<void()>>, std::shared_ptr<Menu>>> options);
	enum MenuExitResult listen();
private:
	std::string heading;
	std::vector<std::variant<std::pair<std::string, std::function<void()>>, std::shared_ptr<Menu>>> options;
};

enum MenuExitResult {
	ENTER,
	ESCAPE,
	TAB
};