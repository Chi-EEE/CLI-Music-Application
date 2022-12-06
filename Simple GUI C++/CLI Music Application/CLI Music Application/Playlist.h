#pragma 
#include "SelectableAudioList.h"
#include "Audio.h"
class Playlist: public SelectableAudioList
{
public:
	Playlist(std::string name);
	void addAudio(Audio audio);
private:
	std::string name;
};