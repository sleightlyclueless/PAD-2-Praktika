#include "database.h"
#include <fstream>
#include <sstream>

std::vector<Movie> Database::movies_;

void Database::printMovies()
{
	std::stringstream str;
	
	str << "Film-Datenbank" << std::endl
		<< "Eintraege: " << movies_.size() << std::endl
		<< "*****" << std::endl;
	
	for (Movie &m : movies_)
	{
		str << m.print(true).str();
	}

	// Write to console
	std::cout << str.str();
}

void Database::printMovies(const std::string path)
{
	std::ofstream source;
	std::stringstream str;

	str << "Movie-Database" << std::endl
		<< "Entries: " << movies_.size() << std::endl
		<< "*****" << std::endl;

	for (Movie& m : movies_)
	{
		str << m.print(true).str();
	}

	// Write to file
	source.open(path);
	if (!source.is_open()) { throw std::runtime_error("Database::printMovies(...): File could not be created!"); }

	source << str.str();
	source.close();

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
	// Bubblesort
	for (int i = 0; i < movies_.size() - 1; i++) {
		int minpos = i;

		for (int j = i + 1; j < movies_.size(); j++) {
			if (movies_.at(j).getRatingsAvg() < movies_.at(minpos).getRatingsAvg()) {
				minpos = j;
			}
		}
		const Movie temp = movies_.at(i);
		movies_.at(i) = movies_.at(minpos);
		movies_.at(minpos) = temp;
	}
}

double Database::printAvgViewTime()
{
	double sum = 0;
	for (const Movie &m : movies_)
	{
		sum += m.getLength();
	}

	sum = sum / movies_.size() * 100;
	sum = (int)sum;
	return (double)sum / 100;
}

int Database::printTotalViewTime()
{
	int sum = 0;
	for (const Movie &m : movies_)
	{
		sum += m.getLength();
	}
	return sum;
}

void Database::playMovie(const int position)
{
	std::cout << "Movie running: " << movies_.at(position).play() << std::endl;
}

void Database::init()
{
	std::ifstream source;
	std::string line;

	std::vector<std::string> titles;
	std::vector<int> lens;
	std::vector<std::string> ratings;
	std::vector<std::string> genres;

	try
	{
		
		source.open("database.txt", std::ios::in);

		if (!source.is_open())
			throw std::runtime_error("Database::init(...): File could not be opened!");

		while (std::getline(source, line))
		{
			if (line.find("Title") != std::string::npos)
				titles.push_back(line.substr(line.find("Title: ") + 7));

			if (line.find("Length") != std::string::npos)
				lens.push_back(std::stoi(line.substr(line.find("Length: ") + 8)));

			if (line.find("Ratings") != std::string::npos)
				ratings.push_back(line.substr(line.find("Ratings: ") + 9));

			if (line.find("Genre") != std::string::npos)
				genres.push_back(line.substr(line.find("Genre: ") + 7));
		}

		source.close();
	}
	catch (std::ifstream::failure& e)
	{
		std::cout << e.what() << std::endl;
	}


	for (int i = 0; i < titles.size(); i++)
	{
		std::string t = titles.at(i);
		int l = lens.at(i);
		std::string r = ratings.at(i);
		std::string tmp;
		std::vector<int> rint;
		std::string g = genres.at(i);

		std::stringstream ss(r);

		while (getline(ss, tmp, ' ')) {
			rint.push_back(stoi(tmp));
		}

		addMovie(Movie(t, l, rint, g));
	}

	sortMovies();

}

void Database::init(std::string filename)
{
	std::ifstream source;
	std::string line;

	std::vector<std::string> titles;
	std::vector<int> lens;
	std::vector<std::string> ratings;
	std::vector<std::string> genres;

	try
	{
		
		source.open(filename, std::ios::in);

		if (!source.is_open())
			throw std::runtime_error("Database::init(...): File could not be opened!");

		while (std::getline(source, line))
		{
			if (line.find("Title") != std::string::npos)
				titles.push_back(line.substr(line.find("Title: ") + 7));

			if (line.find("Length") != std::string::npos)
				lens.push_back(std::stoi(line.substr(line.find("Length: ") + 8)));

			if (line.find("Ratings") != std::string::npos)
				ratings.push_back(line.substr(line.find("Ratings: ") + 9));

			if (line.find("Genre") != std::string::npos)
				genres.push_back(line.substr(line.find("Genre: ") + 7));
		}

		source.close();
	}
	catch (std::ifstream::failure& e)
	{
		std::cout << e.what() << std::endl;
	}


	for (int i = 0; i < titles.size(); i++)
	{
		std::string t = titles.at(i);
		int l = lens.at(i);
		std::string r = ratings.at(i);
		std::string tmp;
		std::vector<int> rint;
		std::string g = genres.at(i);

		std::stringstream ss(r);

		while (getline(ss, tmp, ' ')) {
			rint.push_back(stoi(tmp));
		}

		addMovie(Movie(t, l, rint, g));
	}

	sortMovies();

}


void Database::addMovieRating(const int rating, const int position)
{
	movies_.at(position).addRating(rating);
}

void Database::simulateReviews(int i)
{
	while (i > 0)
	{
		const int rating = rand() % 5 + 1;
		const int position = rand() % movies_.size();

		addMovieRating(rating, position);
		i--;
	}

	sortMovies();
}