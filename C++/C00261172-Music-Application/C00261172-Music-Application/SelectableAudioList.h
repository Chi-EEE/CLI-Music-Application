#pragma once
#include "CircularLinkedList.h"
#include "DoubleLinkedNode.h"
#include "Audio.h"

class SelectableAudioList
{
public:
	std::shared_ptr<Audio> getSelectedAudio();
	std::shared_ptr<Audio> getNextSelectedAudio();
	std::shared_ptr<Audio> removeSelectedAudio();

protected:
	//CircularLinkedList<Audio> audioList = CircularLinkedList<Audio>();

private:
	std::shared_ptr<DoubleLinkedNode<Audio>> selectedAudio;
};

