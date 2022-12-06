#pragma once
#include "CircularLinkedList.h"
#include "Audio.h"

class AudioList
{
public:
	std::shared_ptr<Audio> getAudioByName(std::string audioName);
	bool removeAudio(std::shared_ptr<Audio> audio);
	int getAudioCount() { return this->audioList.getCount(); }

protected:
	CircularLinkedList<Audio> audioList = CircularLinkedList<Audio>();

private:
	std::shared_ptr<DoubleLinkedNode<Audio>> selectedAudio;
};

