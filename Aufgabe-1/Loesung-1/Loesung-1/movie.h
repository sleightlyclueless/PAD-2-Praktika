#pragma once
#include <iostream>
#include <string>
#include <vector>

class Movie
{
	private:
		// Attributes
		std::string title_ = "";
		int length_ = 0;
		std::vector<int> ratings_ = {};
		int ratings_total_ = 0;
		std::string genre_ = "";
	
	public:
		// Constructor
		Movie() = default;
		Movie(const std::string title, const int length, const std::vector<int> ratings, const int ratings_total, const std::string genre);

		// Destructor
		~Movie() = default;

		// Getters / Setters
		std::string getTitle() const { return title_; }
		int getLength() const { return length_; }
		// std::vector<int>* getRatings() { return &ratings_; }
		std::vector<int> getRatings() const { return ratings_; }
		int getRatingsTotal() const { return ratings_total_; }
		std::string getGenre() const { return genre_; }

		void setTitle(const std::string t) { title_ = t; }
		void setLength(const int l) { length_ = l; }
		void setRatingsTotal(const int r) { ratings_total_ = r; }
		void setGenre(const std::string g) { genre_ = g; }
	
		// Custom Methods
		void print() const;
		void addRating();
		std::string play() const;
};
