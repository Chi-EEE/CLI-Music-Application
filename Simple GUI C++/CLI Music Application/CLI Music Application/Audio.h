#pragma once
#include <memory>
#include <string>
#include <iostream>
#include "Artist.h"

class Audio
{
public:
	Audio(std::string name, std::string description, float duration) {
		this->name = name;
		this->description = description;
		this->duration = duration;
		this->artist = nullptr;
	}
	Audio(std::string name, std::string description, float duration, std::shared_ptr<Artist> artist) {
		this->name = name;
		this->description = description;
		this->duration = duration;
		this->artist = artist;
	}

	void play();

	void setName(std::string name) { this->name = name; }
	std::string getName() { return this->name; }
	std::string getDescription() { return this->description; }
	std::shared_ptr<Artist> getArtist() { return this->artist; }
	float getDuration() { return this->duration; }

	inline bool operator==(Audio& rhs) {
		return this->artist == rhs.artist && this->description == rhs.getDescription() && this->name == rhs.getName() && this->duration == rhs.getDuration();
	}
	inline bool operator!=(Audio& rhs) { return !(*this == rhs); }
private:
	std::string name;
	std::string description;
	std::shared_ptr<Artist> artist;
	float duration;
};