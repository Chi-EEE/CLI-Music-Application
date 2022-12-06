#pragma once
#include "AudioList.h"
#include "Audio.h"
class AudioLibrary: public AudioList
{
public:
	AudioLibrary() {

	}
	void addAudio(Audio audio);
	std::string getAllAudio();
private:

};

