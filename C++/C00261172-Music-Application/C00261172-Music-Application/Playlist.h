#pragma 
#include "LinkedList.h"
#include "Song.h"
class Playlist
{
public:
	void shuffle();
private:
	std::string playlistName;
	LinkedList<Song> songs;
};