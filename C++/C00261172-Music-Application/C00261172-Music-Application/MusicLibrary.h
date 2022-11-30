#pragma once
#include "CircularLinkedList.h"
#include "Song.h"
class MusicLibrary
{
public:
	int getSongCount() { return songs.getSize(); }
	CircularLinkedList<Song> getShuffledSongList();
private:
	CircularLinkedList<Song> songs;
};

