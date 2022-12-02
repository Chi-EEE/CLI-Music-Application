#pragma once
#include "SelectableAudioList.h"
#include "CircularLinkedList.h"
#include "Audio.h"
class AudioLibrary: public SelectableAudioList
{
public:
	void addAudio(Audio audio);
private:

};

