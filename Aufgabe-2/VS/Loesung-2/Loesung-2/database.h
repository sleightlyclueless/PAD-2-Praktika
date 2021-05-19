#pragma once
#include "mediafile.h"
#include <sstream>

class Database
{
	public:
		// Getters / Setters
		static std::vector<MediaFile*> getMovies() { return mediafiles_; }
		static int getMovieSize() { return mediafiles_.size(); }

		// Custom Methods
		static void printMovies();							// Overloading print: Write to console
		static void printMovies(const std::string &path);	// Overloading print: Write to file
		static void addMediafile(MediaFile *m);						// Add movie to static vector
		static void removeMediafile(const int &id);		// Remove movie from static vector
		static void sortMovies();							// Selectionsort movies in vector
		static void returnAvgViewTime();					// Return avg viewtime
		static void returnTotalViewTime();					// Return total viewtime
		static void playMedium(const int &id);				// "Play" movie / return name
		static void simulateReviews(int& i); // Construct random reviews and add them to random movies in vector
	
		static bool init(const std::string &filename); // Init database / movie vector from default file or own file
		

	private:
		// Attributes
		static std::vector<MediaFile*> mediafiles_;

		// Private constructor
		Database() = default;
};
