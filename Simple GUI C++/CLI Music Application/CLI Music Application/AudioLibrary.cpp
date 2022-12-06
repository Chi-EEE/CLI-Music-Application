#include "AudioLibrary.h"

void AudioLibrary::addAudio(Audio audio)
{
	this->audioList.insert(std::make_shared<Audio>(audio));
}