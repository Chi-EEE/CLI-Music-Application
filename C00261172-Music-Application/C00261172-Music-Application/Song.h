#pragma once
#include <string>
#include "Artist.h"
class Song
{
public:
	Song(std::string name, Artist artist, float duration) {
		this->name = name;
		this->artist = artist;
		this->duration = duration;
	}
	void setName(std::string name) { this->name = name; }
	std::string getName() { return this->name; }
	Artist getArtist() { return this->artist; }
	float getDuration() { return this->duration; }
private:
	std::string name;
	Artist artist;
	float duration;
};