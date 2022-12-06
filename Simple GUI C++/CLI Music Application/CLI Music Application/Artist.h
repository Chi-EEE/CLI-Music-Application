#pragma once
#include <string>
class Artist
{
public:
	Artist();
	Artist(std::string name);
	void setName(std::string name) { this->name = name; }
	std::string getName() { return this->name; }
	bool operator==(Artist& rhs);
	std::string name;
private:
};

