#pragma once
#include "MenuOption.h"
#include "Console.h"
#include "AudioLibrary.h"
#include "Audio.h"
struct AddAudio : public MenuOption
{
	AddAudio() = default;
	AddAudio(std::shared_ptr<AudioLibrary> audioLibrary) : audioLibrary(audioLibrary) {
	}
	bool handle(int keyCode, bool isArrowKey) override {
		switch (this->stage)
		{
		case 0:
		{
			this->text = "Would you like to add a Audio file?";
			if (YesOrNo(this->confirm, keyCode, isArrowKey)) {
				this->stage++;
			}
			return !this->confirm;
		}
		case 1:
		{
			this->text = "Please enter the Audio's Name:\n > " + this->audioName;
			if (inputText(this->audioName, keyCode, isArrowKey)) {
				this->stage++;
			}
			return false;
		}
		case 2:
		{
			this->text = "Please enter the Audio's Description:";
			if (inputText(this->audioDescription, keyCode, isArrowKey)) {
				this->stage++;
			}
			return false;
		}
		case 3:
		{
			this->text = "Please enter the Audio's Duration:";
			if (inputNumber(this->audioDuration, keyCode, isArrowKey)) {
				this->stage++;
			}
			return false;
		}
		case 4:
		{
			this->text = "Do you want to add an Artist to this Audio?:";
			if (YesOrNo(this->confirm, keyCode, isArrowKey)) {
				this->stage++;
			}
			return false;
		}
		case 5:
		{
			std::shared_ptr<Artist> artist = nullptr;
			if (this->confirm)
			{
				if (inputText(this->artistName, keyCode, isArrowKey)) {
					this->stage++;
				}
				artist = std::make_shared<Artist>(artistName);
			}
			Audio newAudio = Audio(this->audioName, this->audioDescription, this->audioDuration, artist);
			audioLibrary->addAudio(newAudio);
			Console::getInstance()->setConsoleColor(GREEN);
			std::cout << "- Audio Created: " + newAudio.getName() + '\n';
			Console::getInstance()->resetConsoleColor();
			std::cin.ignore();
			return true;
		}
		default:
		{
			break;
		}
		}
	}
	std::shared_ptr<AudioLibrary> audioLibrary;
	std::string audioName = "";
	std::string audioDescription = "";
	int audioDuration = 0;
	std::string artistName = "";
	bool confirm = false;
};