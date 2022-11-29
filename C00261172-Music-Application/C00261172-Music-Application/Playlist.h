#pragma 
#include "LinkedList.h"
#include "Song.h"
class Playlist
{
	std::string playlistName;
	LinkedList<Song> songs;
};