#pragma once
#include <iostream>
#include <string>

#include <map> // For Menu

#include "Console.h"
#include <windows.h> // Virtual Key

#include "Menu.h"

#include "Colour.h"

#include "CircularLinkedList.h"
#include "AudioLibrary.h"

#include <functional>

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