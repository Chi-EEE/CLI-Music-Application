#pragma 
#include "AudioList.h"
#include "Audio.h"
class Playlist: public AudioList
{
public:
	Playlist(std::string name);
	void addAudio(Audio audio);
private:
	std::string name;
};