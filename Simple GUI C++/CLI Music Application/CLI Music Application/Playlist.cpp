#include "Playlist.h"

Playlist::Playlist(std::string name): AudioList()
{
	this->name = name;
}

std::string Playlist::getName()
{
	return this->name;
}
