#include "AudioLibrary.h"

void AudioLibrary::addAudio(Audio audio)
{
	this->audioList.insert(std::make_shared<Audio>(audio));
}

bool AudioLibrary::removeAudio(std::shared_ptr<Audio> audio)
{
	if (getAudioCount() > 0)
	{
		auto temp = this->audioList.getHead();
		do {
			if (audio == temp->data) {

			}
			temp = temp->next;
		} while (temp != this->audioList.getTail());
	}
	return false;
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
		} while (temp != this->audioList.getTail());
		result += "||";
	}
	result += "\n\n";
	return result;
}
