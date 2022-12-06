#pragma once
#include "MenuOption.h"
#include "Console.h"
#include "AudioLibrary.h"
#include "Audio.h"
struct AddAudio : public MenuOption
{
	AddAudio(std::shared_ptr<AudioLibrary> audioLibrary) : audioLibrary(audioLibrary) {
		this->stageText.push_back("Would you like to add a Audio file? [0 = false or 1 = true]\n > ");
		this->stageText.push_back(std::make_pair("Please enter the Audio's Name:\n > ", this->audioName));
		this->stageText.push_back(std::make_pair("Please enter the Audio's Description: ", this->audioDescription));
		this->stageText.push_back(std::make_pair("Please enter the Audio's Duration:", this->audioDuration));
		this->stageText.push_back("Do you want to add an Artist to this Audio?: [0 = false or 1 = true]\n > ");
	}
	bool handle(int keyCode, bool isArrowKey) override {
		switch (this->stage)
		{
		case 0:
		{
			bool returned = YesOrNo(*this->confirm, keyCode, isArrowKey);
			if (returned) {
				this->stage++;
				return !this->confirm;
			}
			return false;
		}
		case 1:
		{
			if (inputText(*this->audioName, keyCode, isArrowKey)) {
				this->stage++;
			}
			return false;
		}
		case 2:
		{
			std::cout << "gfdssdf";
			if (inputText(*this->audioDescription, keyCode, isArrowKey)) {
				this->stage++;
			}
			return false;
		}
		case 3:
		{
			std::cout << "fjanadfsn";
			if (inputNumber(*this->audioDuration, keyCode, isArrowKey)) {
				this->stage++;
			}
			return false;
		}
		case 4:
		{
			if (YesOrNo(*this->confirm, keyCode, isArrowKey)) {
				this->stage++;
			}
			return false;
		}
		case 5:
		{
			std::shared_ptr<Artist> artist = nullptr;
			if (this->confirm)
			{
				if (inputText(*this->artistName, keyCode, isArrowKey)) {
					this->stage++;
				}
				artist = std::make_shared<Artist>(*this->artistName);
			}
			Audio newAudio = Audio(*this->audioName, *this->audioDescription, *this->audioDuration, artist);
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
	std::shared_ptr<std::string> audioName = std::make_shared<std::string>();
	std::shared_ptr<std::string> audioDescription = std::make_shared<std::string>();
	std::shared_ptr<int> audioDuration = std::make_shared<int>();
	std::shared_ptr<std::string> artistName = std::make_shared<std::string>();
	std::shared_ptr<bool> confirm = std::make_shared<bool>();
};