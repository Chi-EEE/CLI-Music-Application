#pragma once
#include "CircularLinkedList.h"
#include "Audio.h"

class SelectableAudioList
{
public:
	bool removeAudio(std::shared_ptr<Audio> audio);
	std::shared_ptr<Audio> getSelectedAudio();
	std::shared_ptr<Audio> getNextSelectedAudio();
	bool removeSelectedAudio();

protected:
	CircularLinkedList<Audio> audioList = CircularLinkedList<Audio>();

private:
	std::shared_ptr<DoubleLinkedNode<Audio>> selectedAudio;
};

