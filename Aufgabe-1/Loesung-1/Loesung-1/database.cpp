#include "database.h"
std::vector<Movie> Database::movies_;

void Database::printMovies()
{
}

void Database::addMovie(const Movie m)
{
	movies_.push_back(m);
}

void Database::removeMovie(const int position)
{
}

void Database::sortMovies()
{
}

int Database::printAvgViewStats()
{
	return 0;
}

int Database::printTotalViewStats()
{
	return 0;
}

void Database::playMovie(const int position)
{
	int i = 0;
	for (const Movie& m : movies_)
	{
		std::cout << "Porno läuft: " << m.play() << std::endl;
		i++;
	}
}
