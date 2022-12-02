#pragma once
#include <string>
#include "Artist.h"
class Audio
{
public:
	Audio(std::string name, std::string description, float duration, Artist artist) {
		this->name = name;
		this->description = description;
		this->duration = duration;
		this->artist = artist;
	}
	void setName(std::string name) { this->name = name; }
	std::string getName() { return this->name; }
	std::string getDescription() { return this->description; }
	Artist getArtist() { return this->artist; }
	float getDuration() { return this->duration; }

	inline bool operator==(Audio& rhs) {
		return this->artist == rhs.artist && this->description == rhs.getDescription() && this->name == rhs.getName() && this->duration == rhs.getDuration();
	}
	inline bool operator!=(Audio& rhs) { return !(*this == rhs); }
private:
	std::string name;
	std::string description;
	Artist artist;
	float duration;
};