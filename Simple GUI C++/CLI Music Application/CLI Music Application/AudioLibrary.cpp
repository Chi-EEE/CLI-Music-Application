#include "AudioLibrary.h"

void AudioLibrary::addAudio(Audio audio)
{
	this->audioList.insert(std::make_shared<Audio>(audio));
}

std::string AudioLibrary::getAllAudio()
{
	std::string result = "";
	if (getAudioCount() > 0)
	{
		auto temp = this->audioList.getHead();
		do {
			result += "||" + temp->data->getName();
			temp = temp->next;
		} while (temp != nullptr && temp != this->audioList.getTail());
		result += "||";
	}
	result += "\n\n";
	return result;
}
