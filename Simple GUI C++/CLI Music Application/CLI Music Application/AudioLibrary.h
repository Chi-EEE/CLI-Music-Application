#pragma once
#include "SelectableAudioList.h"
#include "Audio.h"
class AudioLibrary: public SelectableAudioList
{
public:
	AudioLibrary() {

	}
	void addAudio(Audio audio);
	bool removeAudio(std::shared_ptr<Audio> audio);
	std::string getAllAudio();
	int getAudioCount() { return this->audioList.getCount(); }
private:

};

