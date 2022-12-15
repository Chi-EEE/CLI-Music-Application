#include "AudioList.h"

std::shared_ptr<Audio> AudioList::getAudioByName(std::string audioName)
{
	if (getAudioCount() > 0) {
		auto temp = audioList.getHead();
		do
		{
			if (audioName == temp->data->getName()) {
				return temp->data;
			}
			temp = temp->next;
		} while (temp != nullptr && temp != audioList.getHead());
	}
	return nullptr;
}

bool AudioList::insertAudio(std::shared_ptr<Audio> audio)
{
	if (getAudioByName(audio->getName()) == nullptr) {
		this->audioList.insert(audio);
		return true;
	}
	return false;
}

bool AudioList::removeAudio(std::shared_ptr<Audio> audio)
{
	return audioList.removeData(audio);
}

void AudioList::playAllAudio()
{
	if (getAudioCount() > 0) {
		bool continuePlaying = false;
		auto temp = this->audioList.getHead();
		do
		{
			temp->data->play();
			temp = temp->next;
			while (true) {
				std::cout << "Do you want to continue playing audio from this list?";
				std::cin >> continuePlaying;
				if (!std::cin.fail()) {
					break;
				}
				std::cout << "\nError: 0 or 1";
				std::cin.clear();
				std::cin.ignore(256, '\n');
			}
		} while (continuePlaying);
	}
}

bool AudioList::removeAudioByName(std::string audioName)
{
	auto audio = getAudioByName(audioName);
	if (audio) {
		return audioList.removeData(audio);
	}
	return false;
}

std::string AudioList::getAllAudio()
{
	std::string result = "";
	if (getAudioCount() > 0)
	{
		auto temp = this->audioList.getHead();
		do {
			result += "||" + temp->data->getName();
			temp = temp->next;
		} while (temp != nullptr && temp != this->audioList.getHead());
		result += "||";
	}
	result += "\n\n";
	return result;
}