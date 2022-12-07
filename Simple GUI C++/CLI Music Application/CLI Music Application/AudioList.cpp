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
		} while (temp != nullptr && temp != audioList.getTail());
	}
	return nullptr;
}

void AudioList::addAudio(std::shared_ptr<Audio> audio)
{
	this->audioList.insert(audio);
}

bool AudioList::removeAudio(std::shared_ptr<Audio> audio)
{
	return audioList.removeData(audio);
}

void AudioList::playAllAudio()
{
	if (getAudioCount() > 0) {
		auto temp = this->audioList.getHead();
		do
		{
			temp->data->play();
			temp = temp->next;
		} while (temp != nullptr && temp != audioList.getTail());
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
		} while (temp != nullptr && temp != this->audioList.getTail());
		result += "||";
	}
	result += "\n\n";
	return result;
}