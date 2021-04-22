#pragma once
#include "movie.h"
#include <fstream>
#include <sstream>
#include <iostream>

class Database
{
	private:
		// Attributes
		static std::vector<Movie> movies_;

		// Private constructor
		Database() = default;

	public:
		// Getters / Setters
		static int getMovieSize() { return movies_.size(); }

		// Custom Methods
		static void printMovies();					// Overloading print: Write to console
		static void printMovies(const std::string &path);
		static void addMovie(const Movie &m);				// Add movie to static vector
		static void removeMovie(const int &position);		// Remove movie from static vector
		static void sortMovies();					// Selectionsort movies in vector
		static void returnAvgViewTime();			// Return avg viewtime
		static void returnTotalViewTime();			// Return total viewtime
		static void playMovie(const int &position);		// "Play" movie / return name

		static void init(const bool &useownfile, const std::string &filename); // Init database / movie vector from default file or own file
		static void addMovieRating(const int &rating, const int &position); // Add rating to specific movie in vector with its position
		static void simulateReviews(int &i); // Construct random reviews and add them to random movies in vector
};
