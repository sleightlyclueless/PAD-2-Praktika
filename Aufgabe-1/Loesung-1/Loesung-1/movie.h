#pragma once
#include <iostream>
#include <string>
#include <vector>

class Movie
{
	private:
		// Attributes
		int id_ = -1;
		std::string title_ = "Title unspecified";
		int length_ = 90;
		std::vector<int> ratings_ = {};
		double ratings_avg_ = -1;
		std::string genre_ = "Genre unspecified";
	
	public:
		static int global_id;
		// Constructor
		Movie() = default;
		Movie(const std::string title, const int length, const std::vector<int> ratings, const std::string genre);

		// Destructor
		~Movie() = default;

		// Getters / Setters
		int getLength() const { return length_; }
		double getRatingsAvg() const { return ratings_avg_; }

		void setTitle(const std::string t) { title_ = t; }
		void setLength(const int l) { length_ = l; }
		void setRatingsTotal(const int r) { ratings_avg_ = r; }
		void setGenre(const std::string g) { genre_ = g; }
	
		// Custom Methods
		std::stringstream print(const bool showid) const;
		double calcRatingAvg() const;
		void addRating(int r);
		std::string play() const { return title_; }
};
