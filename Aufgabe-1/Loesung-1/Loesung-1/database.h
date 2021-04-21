#pragma once
#include "movie.h"

class Database
{
	private:
		// Attributes
		static std::vector<Movie> movies_;
		Database() = default;

	public:
		// Getters / Setters
		static int getMovieSize() { return movies_.size(); }
		
		// Custom Methods
		static void printMovies();
		static void printMovies(std::string path);
		static void addMovie(Movie m);
		static void removeMovie(int position);
		static void sortMovies();
		static double printAvgViewTime();
		static int printTotalViewTime();
		static void playMovie(int position);

		static void init();
		static void init(std::string filename);
		static void addMovieRating(int rating, int position);
		static void simulateReviews(int i);
};
