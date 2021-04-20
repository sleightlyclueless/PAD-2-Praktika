#include "movie.h"
int Movie::global_id = 1;

Movie::Movie(const std::string title, const int length, const std::vector<int> ratings, const std::string genre): title_(title),length_(length), ratings_(ratings), genre_(genre)
{
	id_ = global_id++;
	ratings_total_ = calcRatingAvg();
}

void Movie::print() const
{
	std::cout << "Movie ID: " << id_ << std::endl
		<< "Movie title: " << title_ << std::endl
		<< "Movie length: " << length_ << "min" << std::endl;
		
	for (int r : ratings_)
	{
		std::cout << r << " ";
	}

	std::cout << "Rating average: " << ratings_total_ << std::endl
		<< "Movie genre: " << genre_ << std::endl;
}

double Movie::calcRatingAvg() const
{
	int c = 0;
	int sum = 0;
	
	for (int r : ratings_)
	{
		sum += r;
		c++;
	}
	
	// sum = sum / c * 100;
	return (double)sum / c;
}

void Movie::addRating(const int r)
{
	if (r < 1 || r > 5)
	{
		std::cout << "Only ratings from 1-5 please!" << std::endl;
		return;
	}
		
	ratings_.push_back(r);
	ratings_total_ = calcRatingAvg();
}
