#ifndef DATABASE_H
#define DATABASE_H

#include "movie.h"
#include <iostream>
#include <fstream>
#include <sstream>

class Database
{
    private:
        // Attributes
        static std::vector<Movie*> movies_;

        // Private constructor
        Database() = default;

    public:
        // Getters / Setters
        static int getMovieSize() { return movies_.size(); }

        // Custom Methods
        static std::stringstream printMovies();							// Overloading print: Write to console
        static void printMovies(const std::string &path);	// Overloading print: Write to file
        static std::stringstream addMovie(Movie *m);						// Add movie to static vector
        static std::stringstream removeMovie(const int &position);		// Remove movie from static vector
        static std::stringstream sortMovies();							// Selectionsort movies in vector
        static std::stringstream returnAvgViewTime();					// Return avg viewtime
        static std::stringstream returnTotalViewTime();					// Return total viewtime
        static std::stringstream playMovie(const int &position);			// "Play" movie / return name

        static void init(const bool &useownfile, const std::string &filename); // Init database / movie vector from default file or own file
        static void simulateReviews(int &i); // Construct random reviews and add them to random movies in vector
};

#endif // DATABASE_H
