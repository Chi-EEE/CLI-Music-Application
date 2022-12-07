#pragma once
#include "CircularLinkedList.h"
#include "Audio.h"

class AudioList
{
public:
	std::shared_ptr<Audio> getAudioByName(std::string audioName);
	void addAudio(std::shared_ptr<Audio> audio);
	bool removeAudio(std::shared_ptr<Audio> audio);
	void playAllAudio();
	bool removeAudioByName(std::string audioName);
	std::string getAllAudio();
	int getAudioCount() { return this->audioList.getCount(); }

protected:
	CircularLinkedList<Audio> audioList = CircularLinkedList<Audio>();

private:
	std::shared_ptr<DoubleLinkedNode<Audio>> selectedAudio;
};

