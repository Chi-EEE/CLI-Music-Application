#include "Artist.h"

bool Artist::operator==(Artist& rhs)
{
	return this->name == rhs.getName();
}
