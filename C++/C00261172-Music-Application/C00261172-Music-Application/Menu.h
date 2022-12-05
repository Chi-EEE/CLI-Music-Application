#pragma once
#include <string>
#include <variant>
#include <functional>

#include "MenuOption.h"
#include "MenuExitResult.h"

struct Menu
{
	std::string heading;
	std::vector<std::variant<std::shared_ptr<Menu>, MenuOption>> menuOptions;
	int selectedOption = 0;
};
