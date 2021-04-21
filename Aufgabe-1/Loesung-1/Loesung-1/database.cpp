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
	movies_.erase(movies_.begin() + position);
}

void Database::sortMovies()
{
	for (Movie m1: movies_)
	{
		for (Movie m2 : movies_)
		{
			if (m1.getRatingsAvg() < m2.getRatingsAvg())
			{
				const Movie temp = m1;
				m1 = m2;
				m2 = temp;
			}
		}
	}
}

double Database::printAvgViewTime()
{
	double sum = 0;
	int counter = 0;
	for (const Movie& m : movies_)
	{
		sum += m.getLength();
		counter++;
	}
	return sum / counter;
}

int Database::printTotalViewTime()
{
	int sum = 0;
	for (const Movie& m : movies_)
	{
		sum += m.getLength();
	}
	return sum;
}

void Database::playMovie(const int position)
{
	std::cout << "Film läuft: " << movies_.at(position).play() << std::endl;
}
