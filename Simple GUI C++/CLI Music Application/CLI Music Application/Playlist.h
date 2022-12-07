#pragma 
#include "AudioList.h"
#include "Audio.h"
class Playlist: public AudioList
{
public:
	Playlist(std::string name);
	std::string getName();
private:
	std::string name;
};