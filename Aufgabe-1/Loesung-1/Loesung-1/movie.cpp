#include "movie.h"
#include <sstream>

// Static ID counter
int Movie::global_id = 1;

// Constructor
Movie::Movie(std::string &title, int &length, std::vector<int> &ratings, std::string &genre): title_(title),length_(length), ratings_(ratings), genre_(genre)
{
	id_ = global_id++;
	ratings_avg_ = calcRatingAvg();
}

// Calculate the avg rating from ratings vector
double Movie::calcRatingAvg() const
{
	double sum = 0;

	for (int r : ratings_)
	{
		sum += r;
	}

	// Return result rounded to 2 commas
	sum = sum / ratings_.size() * 100;	// 333,3333
	sum = (int)sum;						// 333
	return (double)sum / 100;			// 3,33
}

// Return a stringstream with all important information of a movie object (with or without id)
std::stringstream Movie::print(const bool consolemode) const
{
	std::stringstream str;

	if (consolemode)
		str << "ID: " << id_ << std::endl;
	
	str << "Title: " << title_ << std::endl
		<< "Length: " << length_ << "min" << std::endl;

	if (consolemode)
	{
		str << "Ratings: " << ratings_avg_ << std::endl;
	}
	else
	{
		str << "Ratings: ";
		for (const int x: ratings_)
		{
			str << x << " ";
		}
		str << std::endl;
	}

	str << "Genre: " << genre_ << std::endl
		<< "*****" << std::endl;

	return str;
}

// Add a rating to movie rating-vector
void Movie::addRating(const int r)
{
	if (r < 1 || r > 5)
		return;
		
	ratings_.push_back(r);
	ratings_avg_ = calcRatingAvg();
}
