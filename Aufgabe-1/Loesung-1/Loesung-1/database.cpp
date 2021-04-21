#include "database.h"

// Initialize static vector
std::vector<Movie> Database::movies_;

// Overloading print: Write to console
void Database::printMovies()
{
	std::stringstream str;
	
	str << "Movie-Database" << std::endl
		<< "Entries: " << movies_.size() << std::endl
		<< "*****" << std::endl;
	
	for (Movie &m : movies_)
	{
		str << m.print(true).str();
	}
	str << "==================================" << std::endl;

	// Write to console
	std::cout << str.str();
}

// Overloading print: Write to file
void Database::printMovies(const std::string path)
{
	std::stringstream str;
	std::ofstream source;

	str << "Movie-Database" << std::endl
		<< "Entries: " << movies_.size() << std::endl
		<< "*****" << std::endl;

	for (Movie& m : movies_)
	{
		str << m.print(false).str();
	}

	// Write to file
	source.open(path);
	if (!source.is_open()) { throw std::runtime_error("Database::printMovies(...): File could not be created!"); }
	source << str.str();
	source.close();
}

// Add movie to static vector
void Database::addMovie(const Movie m)
{
	movies_.push_back(m);
}

// Remove movie from static vector
void Database::removeMovie(const int position)
{
	movies_.erase(movies_.begin() + position);
}

// Bubblesort movies in vector
void Database::sortMovies()
{
	// Selectionsort
	for (int i = 0; i < movies_.size() - 1; i++) {
		int minpos = i;

		// Search smallest element
		for (int j = i + 1; j < movies_.size(); j++) {
			if (movies_.at(j).getRatingsAvg() < movies_.at(minpos).getRatingsAvg()) {
				minpos = j;
			}
		}
		// Switch places
		const Movie temp = movies_.at(i);
		movies_.at(i) = movies_.at(minpos);
		movies_.at(minpos) = temp;
	}

	std::cout << "=================================" << std::endl
		<< "Sorted!" << std::endl
		<< "=================================" << std::endl;
}

// Return avg viewtime
double Database::returnAvgViewTime()
{
	double sum = 0;
	for (const Movie &m : movies_)
	{
		sum += m.getLength();
	}

	// Return result rounded to 2 commas
	sum = sum / movies_.size() * 100;	// 333,333
	sum = (int)sum;						// 333
	return (double)sum / 100;			// 3,33
}

// Return total viewtime
int Database::returnTotalViewTime()
{
	int sum = 0;
	for (const Movie &m : movies_)
	{
		sum += m.getLength();
	}
	return sum;
}

// "Play" movie / return name
void Database::playMovie(const int position)
{
	std::cout << "Movie running: " << movies_.at(position).play() << std::endl;
}

// Init database / movie vector from default file or own file
void Database::init(const bool useownfile, const std::string filename)
{
	// Ini read-file sources
	std::ifstream source;
	std::string line;

	// Ini necessary vectors to read respective information into
	std::vector<std::string> titles;
	std::vector<int> lens;
	std::vector<std::string> ratings;
	std::vector<std::string> genres;

	try
	{
		// Open file according to selected mode
		if (useownfile)
		{
			source.open(filename, std::ios::in);
			if (!source)
				throw std::runtime_error("Database::init(...): File could not be opened!");
		} else
		{
			source.open("database.txt", std::ios::in);
			if (!source)
				throw std::runtime_error("Database::init(...): File could not be opened!");
		}

		// Check if file access successful
		if (!source.is_open())
			throw std::runtime_error("Database::init(...): File could not be opened!");

		// Check each line from file for relevant information for the vectors
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

		// We are done with the file - close it again
		source.close();
		if (source.is_open())
			throw std::runtime_error("Database::init(...): File could not be closed!");
	}
	catch (std::ifstream::failure& e)
	{
		std::cout << e.what() << std::endl;
		return;
	}
	catch (std::runtime_error &e)
	{
		std::cout << e.what() << std::endl;
		return;
	}

	// Check if all vectors are the same length - if not something is wrong with the file or data
	if (titles.size() == lens.size() && lens.size() == ratings.size() && ratings.size() == genres.size())
	{
		// Read all the extracted information from filled file - vectors and process
		for (int i = 0; i < titles.size(); i++)
		{
			std::string title = titles.at(i);
			int length = lens.at(i);
			std::string ratingstr = ratings.at(i);
			std::string genre = genres.at(i);

			// Process rating string into vector for each line
			std::stringstream ss(ratingstr);
			std::string tmp;
			std::vector<int> ratingints;
			while (getline(ss, tmp, ' ')) {
				ratingints.push_back(stoi(tmp));
			}

			// Add movie made with its class constructor to vector string
			addMovie(Movie(title, length, ratingints, genre));
		}
	} else
	{
		std::cout << "Something seems to be wrong with the file, please try again or check it!" << std::endl;
	}
	

	// When all movies entered sort them
	std::cout << "=================================" << std::endl
		<< "Database initialized!" << std::endl;
	sortMovies();
}

// Add rating to specific movie in vector with its position
void Database::addMovieRating(const int rating, const int position)
{
	movies_.at(position).addRating(rating);
}

// Construct random reviews and add them to random movies in vector
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