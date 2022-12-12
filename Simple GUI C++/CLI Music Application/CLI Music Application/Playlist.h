/// <summary>
/// Name: Chi Huu Huynh
/// Date: 06/12/2022
/// </summary>
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