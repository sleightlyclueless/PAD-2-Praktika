#pragma once
#include "movie.h"

class Database
{
	private:
		// Attributes
		static std::vector<Movie> movies_;

	public:
		// Getters / Setters
		
		// Custom Methods
		static void printMovies();
		static void addMovie(const Movie m);
		static void removeMovie(const int position);
		static void sortMovies();
		static double printAvgViewTime();
		static int printTotalViewTime();
		static void playMovie(const int position);
};
