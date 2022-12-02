#pragma once
#include <iostream>
#include <string>
#include "CircularLinkedList.h"
#include "AudioLibrary.h"
class Application
{
public:
	void run();
    char keyPress();
private:
    AudioLibrary audioLibrary;
    bool changed = true;
    const std::string LINE = "=======================================================================================================================\n";
};