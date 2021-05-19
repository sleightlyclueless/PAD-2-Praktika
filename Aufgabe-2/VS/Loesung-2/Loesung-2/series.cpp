// Constructor
#include "series.h"
#include <ostream>
#include <sstream>

Series::Series(std::string &title, int &length, std::vector<int> &ratings, std::string &genre, Mediatype &type, int &episodes) : MediaFile(title, length, ratings, genre, type)
{
	episodes_ = episodes;
	nextepisode_ = 1;
	lengthavg_ = length / episodes;
}

std::stringstream Series::print(const bool consolemode) const
{
	std::stringstream str;
	str << MediaFile::print(consolemode).str();
	str << "Episodes: " << episodes_ << std::endl;
	if (consolemode)
		str << "Esitmated length per Episode: " << lengthavg_  << "min" << std::endl;
	
	return str;
}

std::string Series::play()
{
	std::stringstream str;
	if (nextepisode_+1 > episodes_)
		nextepisode_ = 0;
	
	str << "Now playing " << title_ << std::endl
		<< "Episode " << nextepisode_++ << " of " << episodes_ << std::endl;
	
	return str.str();
}
