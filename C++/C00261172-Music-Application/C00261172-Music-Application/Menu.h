#pragma once
#include <iostream> // cout
#include <vector> // vector
#include <string> // string

#include "Console.hpp"
#include <windows.h> // Virtual Key

class Menu
{
public:
    Menu(std::vector<std::string> options);
    enum MenuExitResult listen(int& selectedOption);
private:
    std::string heading;
    std::vector<std::string> options;
};

enum MenuExitResult {
    ENTER,
    ESCAPE,
    TAB
};