#pragma once
#include "MenuOption.h"
struct AddAudio : public MenuOption
{
	bool handle(int keyCode, bool isArrowKey) override {
		switch (this->stage)
		{
		case 0:
			bool addAudio = YesOrNo("Would you like to add a Audio file?", keyCode, isArrowKey);
			return addAudio;
		case 1:
			std::string name = EnterConsoleString("Please enter the Audio's Name:");
			this->stage++;
			return true;
		case 2:
			std::string description = EnterConsoleString("Please enter the Audio's Description:");
			return true;
		case 3:
			int duration = EnterConsoleInt("Please enter the Audio's Duration:");
			return true;
		case 4:
			bool addArtist = YesOrNo("Do you want to add an Artist to this Audio?:", keyCode, isArrowKey);
			return true;
		case 5:
			std::shared_ptr<Artist> artist = nullptr;
			if (addArtist)
			{
				std::string artistName = EnterConsoleString("Please enter the Artist's Name:");
				artist = std::make_shared<Artist>(artistName);
			}
			Audio newAudio = Audio(name, description, duration, artist);
			audioLibrary.addAudio(newAudio);
			setConsoleColor(GREEN);
			Write("- Audio Created: " + newAudio.getName() + '\n');
			resetConsoleColor();
			std::cin.ignore();
			return true;
		default:
			break;
		}
	}
};