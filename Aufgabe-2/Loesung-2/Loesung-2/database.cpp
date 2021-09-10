#include "database.h"
#include "movie.h"
#include "series.h"
#include <fstream>
#include <iostream>


// Initialize static vector
std::vector<MediaFile*> Database::mediafiles_;

// Overloading print: Write to console
void Database::printMovies()
{
	std::stringstream str;
	
	str << "MediaFile-Database" << std::endl
		<< "Entries: " << mediafiles_.size() << std::endl
		<< "*****" << std::endl;
	
	for (MediaFile* &m : mediafiles_)
	{
		str << m->print(true).str();
	}
	str << "==================================" << std::endl;

	// Write to console
	std::cout << str.str();
}

// Overloading print: Write to file
void Database::printMovies(const std::string &path)
{
	std::stringstream str;
	std::ofstream source;

	str << "MediaFile-Database" << std::endl
		<< "Entries: " << mediafiles_.size() << std::endl
		<< "*****" << std::endl;

	for (MediaFile* &m : mediafiles_)
	{
		str << m->print(false).str();
		str << "*****" << std::endl;
	}

	// Write to file
	try
	{
		source.open(path);
		if (!source)
			throw std::runtime_error("Database::printMovies(...): File could not be opened!");
		source << str.str();
		source.close();
	}
	catch (std::runtime_error& e)
	{
		std::cout << e.what() << std::endl;
	}
	
}

// Add movie to static vector
void Database::addMediafile(MediaFile *m)
{
	mediafiles_.push_back(m);
	std::cout << "MediaFile " << m->getTitle() << " added!" << std::endl
		<< "=================================" << std::endl;
}

// Remove movie from static vector
void Database::removeMediafile(const int &id)
{
	bool found = false;
	int pos = 0;
	for (MediaFile* &m : mediafiles_)
	{
		if (m->getId() == id)
		{
			found = true;
			break;
		}
		pos++;
	}
	
	const std::string mname = mediafiles_.at(pos)->getTitle();
	mediafiles_.erase(mediafiles_.begin() + pos);
	std::cout << "=================================" << std::endl
		<< "Mediafile " << mname << " removed!" << std::endl
		<< "=================================" << std::endl;
}

// Selectionsort movies in vector
void Database::sortMovies()
{
	for (unsigned int i = 0; i < mediafiles_.size() - 1; i++) {
		int maxpos = i;

		// Search smallest element
		for (unsigned int j = i + 1; j < mediafiles_.size(); j++) {
			if (mediafiles_.at(j)->getRatingsAvg() > mediafiles_.at(maxpos)->getRatingsAvg()) {
				maxpos = j;
			}
		}
		
		// Switch places
		std::swap(mediafiles_.at(maxpos), mediafiles_.at(i));
	}

	std::cout << "=================================" << std::endl
		<< "Database sorted!" << std::endl
		<< "=================================" << std::endl;
}

// Return avg viewtime
void Database::returnAvgViewTime()
{
	double sum = 0;
	for (MediaFile* &m : mediafiles_)
	{
		sum += m->getLength();
	}

	// Return result rounded to 2 commas
	sum = sum / mediafiles_.size() * 100;	// 333,333
	sum = (int)sum;						// 333
	sum = (double)sum / 100;			// 3,33

	std::cout << "Average viewtime is: " << sum << "min!" << std::endl;
}

// Return total viewtime
void Database::returnTotalViewTime()
{
	int sum = 0;
	for (MediaFile* &m : mediafiles_)
	{
		sum += m->getTotalLength();
	}
	std::cout << "Total viewtime is: " << sum << "min!" << std::endl;
}

// "Play" movie / return name
void Database::playMedium(const int &id)
{
	bool found = false;
	int pos = 0;
	for (MediaFile*& m : mediafiles_)
	{
		if (m->getId() == id)
		{
			found = true;
			break;
		}
		pos++;
	}

	if (found)
	{
		std::cout << mediafiles_.at(pos)->getMediaType() << " running: " << mediafiles_.at(pos)->play() << std::endl;
	}
		
	if (!found)
		std::cout << "MediaFile did not exist in our database! Please try again!" << std::endl;
	
}

// Construct random reviews and add them to random movies in vector
void Database::simulateReviews(int& i)
{
	while (i > 0)
	{
		const int rating = rand() % 5 + 1;
		const int position = rand() % mediafiles_.size();
		mediafiles_.at(position)->addRating(rating);

		i--;
	}

	sortMovies();
}

// Init database / movie vector from default file or own file
bool Database::init(const std::string &filename)
{
	// Ini read-file sources
	std::ifstream source;
	std::string line;

	// Ini necessary vectors to read respective information into
	std::vector <Mediatype> mediaflags;
	std::vector<std::string> titles;
	std::vector<int> lens;
	std::vector<std::string> ratings;
	std::vector<std::string> genres;
	std::vector<int> releases;
	std::vector<int> episodes;

	// Clear heap upon init and reset ID nummeration
	for(MediaFile* &m: mediafiles_)
	{
		delete m;
	}
	MediaFile::global_id = 1;
	mediafiles_.clear();

	try
	{
		// Open file according to selected mode
		if (!filename.empty())
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

		// Check each line from file for relevant information for the vectors
		int linecount = 0;
		bool specialmedia = false;
		while (std::getline(source, line))
		{
			
			if (line.find("Title: ") != std::string::npos)
			{
				linecount = 0;
				specialmedia = false;
				titles.push_back(line.substr(line.find("Title: ") + 7));
			}

			if (line.find("Length: ") != std::string::npos)
				lens.push_back(std::stoi(line.substr(line.find("Length: ") + 8)));

			if (line.find("Ratings: ") != std::string::npos)
				ratings.push_back(line.substr(line.find("Ratings: ") + 9));
			
			if (line.find("Genre: ") != std::string::npos)
				genres.push_back(line.substr(line.find("Genre: ") + 7));

			if (line.find("Released: ") != std::string::npos)
			{
				specialmedia = true;
				releases.push_back(stoi(line.substr(line.find("Released: ") + 10)));
				episodes.push_back(0);
				mediaflags.push_back(Mediatype::movie);
			}
			else if (line.find("Episodes: ") != std::string::npos)
			{
				specialmedia = true;
				episodes.push_back(stoi(line.substr(line.find("Episodes: ") + 10)));
				releases.push_back(0);
				mediaflags.push_back(Mediatype::series);
			}
			linecount++;

			if (linecount > 4 && !specialmedia)
			{
				releases.push_back(0);
				episodes.push_back(0);
				mediaflags.push_back(Mediatype::mediafile);
				linecount = 0;
			}
			
		}

		// We are done with the file - close it again
		source.close();
		if (source.is_open())
			throw std::runtime_error("Database::init(...): File could not be closed!");
	}
	catch (std::ifstream::failure &e)
	{
		std::cout << e.what() << std::endl;
		return false;
	}
	catch (std::runtime_error &e)
	{
		std::cout << e.what() << std::endl;
		return false;
	}
	catch (...)
	{
		std::cout << "Default catch (throw string, int, whatever)" << std::endl;
	}

	// Check if all vectors are the same length - if not something is wrong with the file or data
	if (titles.size() == lens.size() && lens.size() == ratings.size() && ratings.size() == genres.size() && genres.size() == releases.size() && releases.size() == episodes.size())
	{
		// Read all the extracted information from filled file - vectors and process
		for (unsigned int i = 0; i < mediaflags.size(); i++)
		{
			std::string ratingstr = ratings.at(i);
			std::vector<int> ratingints;
			
			// Process rating string into vector for each line
			std::stringstream ss(ratingstr);
			std::string tmp;
			while (getline(ss, tmp, ' ')) {
				ratingints.push_back(stoi(tmp));
			}

			// TODO use main constructor
			if (mediaflags.at(i) == Mediatype::mediafile)
			{
				Mediatype type = Mediatype::mediafile;
				MediaFile* m = new MediaFile(titles.at(i), lens.at(i), ratingints, genres.at(i), type);
				addMediafile(m);
			}
			else if (mediaflags.at(i) == Mediatype::movie)
			{
				Mediatype type = Mediatype::movie;
				Movie* m = new Movie(titles.at(i), lens.at(i), ratingints, genres.at(i), type, releases.at(i));
				addMediafile(m);
			}
			else
			{
				Mediatype type = Mediatype::series;
				Series* s = new Series(titles.at(i), lens.at(i), ratingints, genres.at(i), type, episodes.at(i));
				addMediafile(s);
			}
		}
	} else
	{
		std::cout << "Something seems to be wrong with the file, please try again or check it!" << std::endl;
	}

	// When all movies entered sort them
	std::cout << "=================================" << std::endl
		<< "Database initialized!" << std::endl;
	sortMovies();
	return true;
}