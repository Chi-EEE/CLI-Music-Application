#pragma once
#include <iostream>
#include <string>

#include <map> // For Menu

// HANDLE
#include <windows.h>

// _getch
#include <stdio.h>
#include <conio.h>

// std::streamsize>::max()
#include <sstream>
#include <limits>

#include "Colour.h"

#include "CircularLinkedList.h"
#include "AudioLibrary.h"
class Application
{
public:
    Application();
    void run();
    void buildScreen();
    void buildMenu(int selectedOption);
    void displayAudioDetails(Audio* audio, int index);
    void addAudio();
    bool YesOrNo(std::string question);
    std::string EnterConsoleString(std::string statement);
    int EnterConsoleInt(std::string statement);
private:
    AudioLibrary audioLibrary;
    bool changed = true;
    const std::string LINE = "=======================================================================================================================\n";

    // https://stackoverflow.com/a/3114231
    typedef void (Application::* menu_method_t)(void);
    typedef std::map<std::string, menu_method_t> menu_func_map_t;
    menu_func_map_t menuOptions;
};