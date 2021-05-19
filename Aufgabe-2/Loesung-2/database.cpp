#include "database.h"

// Initialize static vector
std::vector<Movie*> Database::movies_;

// Overloading print: Write to console
std::stringstream Database::printMovies()
{
    std::stringstream str;

    str << "Movie-Database" << std::endl
        << "Entries: " << movies_.size() << std::endl
        << "*****" << std::endl;

    for (Movie* &m : movies_)
    {
        str << m->print(true).str();
    }
    str << "==================================" << std::endl;

    // Write to console
    return str;
}

// Overloading print: Write to file
void Database::printMovies(const std::string &path)
{
    std::stringstream str;
    std::ofstream source;

    str << "Movie-Database" << std::endl
        << "Entries: " << movies_.size() << std::endl
        << "*****" << std::endl;

    for (Movie* &m : movies_)
    {
        str << m->print(false).str();
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
std::stringstream Database::addMovie(Movie *m)
{
    std::stringstream str;

    movies_.push_back(m);
    str << "Movie " << m->play() << " added!" << std::endl
        << "=================================" << std::endl;

    return str;
}

// Remove movie from static vector
std::stringstream Database::removeMovie(const int &position)
{
    std::stringstream str;

    const std::string mname = movies_.at(position)->play();
    movies_.erase(movies_.begin() + position);
    str << "=================================" << std::endl
        << "Movie " << mname << " removed!" << std::endl
        << "=================================" << std::endl;

    return str;
}

// Selectionsort movies in vector
std::stringstream Database::sortMovies()
{
    std::stringstream str;

    for (int i = 0; i < movies_.size() - 1; i++) {
        int maxpos = i;

        // Search smallest element
        for (int j = i + 1; j < movies_.size(); j++) {
            if (movies_.at(j)->getRatingsAvg() > movies_.at(maxpos)->getRatingsAvg()) {
                maxpos = j;
            }
        }

        // Switch places
        std::swap(movies_.at(maxpos), movies_.at(i));
    }

    str << "=================================" << std::endl
        << "Database sorted!" << std::endl
        << "=================================" << std::endl;

    return str;
}

// Return avg viewtime
std::stringstream Database::returnAvgViewTime()
{
    std::stringstream str;

    double sum = 0;
    for (Movie* &m : movies_)
    {
        sum += m->getLength();
    }

    // Return result rounded to 2 commas
    sum = sum / movies_.size() * 100;	// 333,333
    sum = (int)sum;						// 333
    sum = (double)sum / 100;			// 3,33

    str << "Average viewtime is: " << sum << "min!" << std::endl;

    return str;
}

// Return total viewtime
std::stringstream Database::returnTotalViewTime()
{
    std::stringstream str;

    int sum = 0;
    for (Movie* &m : movies_)
    {
        sum += m->getLength();
    }
    str << "Total viewtime is: " << sum << "min!" << std::endl;

    return str;
}

// "Play" movie / return name
std::stringstream Database::playMovie(const int &position)
{
    std::stringstream str;
    str << "Movie running: " << movies_.at(position)->play() << std::endl;
    return str;
}

// Init database / movie vector from default file or own file
void Database::init(const bool &useownfile, const std::string &filename)
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
            source.open("F:/Dokumente/Programming/Uni/PAD-2-Praktika/Aufgabe-2/Loesung-2/database.txt", std::ios::in);
            if (!source)
                throw std::runtime_error("Database::init(...): File could not be opened!");
        }

        // Check each line from file for relevant information for the vectors
        while (std::getline(source, line))
        {
            if (line.find("Title: ") != std::string::npos)
                titles.push_back(line.substr(line.find("Title: ") + 7));

            if (line.find("Length: ") != std::string::npos)
                lens.push_back(std::stoi(line.substr(line.find("Length: ") + 8)));

            if (line.find("Ratings: ") != std::string::npos)
                ratings.push_back(line.substr(line.find("Ratings: ") + 9));

            if (line.find("Genre: ") != std::string::npos)
                genres.push_back(line.substr(line.find("Genre: ") + 7));
        }

        // We are done with the file - close it again
        source.close();
        if (source.is_open())
            throw std::runtime_error("Database::init(...): File could not be closed!");
    }
    catch (std::ifstream::failure &e)
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
            std::string ratingstr = ratings.at(i);
            std::vector<int> ratingints;

            // Process rating string into vector for each line
            std::stringstream ss(ratingstr);
            std::string tmp;
            while (getline(ss, tmp, ' ')) {
                ratingints.push_back(stoi(tmp));
            }

            // Add movie made to HEAP with its class constructor to vector string
            Movie *m = new Movie(titles.at(i), lens.at(i), ratingints, genres.at(i));
            addMovie(m);
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

// Construct random reviews and add them to random movies in vector
void Database::simulateReviews(int &i)
{
    while (i > 0)
    {
        const int rating = rand() % 5 + 1;
        const int position = rand() % movies_.size();
        movies_.at(position)->addRating(rating);

        i--;
    }

    sortMovies();
}
