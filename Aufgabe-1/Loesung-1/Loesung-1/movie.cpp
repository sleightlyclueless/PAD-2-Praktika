#include "movie.h"

Movie::Movie(const std::string title, const int length, const std::vector<int> ratings, const int ratings_total, const std::string genre): title_(title),length_(length), ratings_(ratings), ratings_total_(ratings_total), genre_(genre)
{
}

void Movie::print() const
{
}

void Movie::addRating()
{
}

std::string Movie::play() const
{
	return title_;
}
