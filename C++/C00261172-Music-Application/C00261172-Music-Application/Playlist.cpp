#include "Playlist.h"

Playlist::Playlist(std::string name): SelectableAudioList()
{
	this->name = name;
}

void Playlist::addAudio(Audio audio)
{
	//this->audioList.insert(audio);
}
