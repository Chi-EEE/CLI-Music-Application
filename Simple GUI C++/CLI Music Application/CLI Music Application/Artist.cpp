#include "Artist.h"

Artist::Artist()
{
}

Artist::Artist(std::string name)
{
	this->name = name;
}

bool Artist::operator==(Artist& rhs)
{
	return this->name == rhs.getName();
}
