// Constructor
#include "movie.h"
#include <sstream>

Movie::Movie(std::string &title, int &length, std::vector<int> &ratings, std::string &genre, Mediatype &type, int &released) : MediaFile(title, length, ratings, genre, type)
{
	released_ = released;
}

std::stringstream Movie::print(const bool consolemode) const
{
    std::stringstream str;
	str << "=================================" << std::endl
		<< "Printing movie: " << std::endl;
    str << MediaFile::print(consolemode).str();
    str << "Year: " << released_ << std::endl;
    return str;
}

std::stringstream Movie::checkOlder(Movie &m1, Movie &m2)
{
	std::stringstream str;
	
	if (m1.released_ > m2.released_)
	{
		str << "=================================" << std::endl
			<< "Older movie: " << std::endl;
		str << m2.print(true).str();
		str << "Year: " << m2.released_ << std::endl;
	}

	if (m2.released_ > m1.released_)
	{
		str << "=================================" << std::endl
			<< "Older movie: " << std::endl;
		str << m1.print(true).str() << std::endl;
	}

	if (m2.released_ == m1.released_)
	{
		str << "Both movies from the same year: " << m1.released_ << std::endl;
	}
	
	return str;
}

