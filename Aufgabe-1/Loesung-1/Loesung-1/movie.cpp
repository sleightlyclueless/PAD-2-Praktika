#include "movie.h"
#include <sstream>

int Movie::global_id = 1;

Movie::Movie(const std::string title, const int length, const std::vector<int> ratings, const std::string genre): title_(title),length_(length), ratings_(ratings), genre_(genre)
{
	id_ = global_id++;
	ratings_avg_ = calcRatingAvg();
}

std::stringstream Movie::print(const bool showid) const
{
	std::stringstream str;
	std::string rating;

	if (showid)
		str << "ID: " << id_ << std::endl;
	
	str
		<< "Title: " << title_ << std::endl
		<< "Length: " << length_ << "min" << std::endl
		<< "Ratings: " << ratings_avg_ << std::endl
		<< "Genre: " << genre_ << std::endl
		<< "*****" << std::endl;

	return str;
}

double Movie::calcRatingAvg() const
{
	int c = 0;
	double sum = 0;
	
	for (int r : ratings_)
	{
		sum += r;
		c++;
	}

	sum = sum / c * 100;		// 333,3333
	sum = (int)sum;				// 333
	return (double)sum / 100;	// 3,33
}

void Movie::addRating(const int r)
{
	if (r < 1 || r > 5)
	{
		std::cout << "Only ratings from 1-5 please!" << std::endl;
		return;
	}
		
	ratings_.push_back(r);
	ratings_avg_ = calcRatingAvg();
}
