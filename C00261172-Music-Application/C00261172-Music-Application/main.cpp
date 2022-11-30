#include <iostream>
#include <string>
#include "CircularLinkedList.h"
#include "Song.h"
int main() {
	CircularLinkedList<Song> songs;
	songs.insert(Song{ std::string("Name"), Artist{}, 1.9f });
	songs.insert(Song{ std::string("Name"), Artist{}, 1.9f });
	return 0;
}