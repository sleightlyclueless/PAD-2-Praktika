#pragma once
#include <iostream>
#include <string>
#include <vector>

class Movie
{
	private:
		// Attributes
		int id_;
		std::string title_ = "Title unspecified";
		int length_ = 90;
		std::vector<int> ratings_ = {};
		double ratings_total_ = -1;
		std::string genre_ = "Genre unspecified";
	
	public:
		static int global_id;
		// Constructor
		Movie() = default;
		Movie(const std::string title, const int length, const std::vector<int> ratings, const std::string genre);

		// Destructor
		~Movie() = default;

		// Getters / Setters
		int getId() const { return id_; }
		std::string getTitle() const { return title_; }
		int getLength() const { return length_; }
		// std::vector<int>* getRatings() { return &ratings_; }
		std::vector<int> getRatings() const { return ratings_; }
		double getRatingsTotal() const { return ratings_total_; }
		std::string getGenre() const { return genre_; }

		void setTitle(const std::string t) { title_ = t; }
		void setLength(const int l) { length_ = l; }
		void setRatingsTotal(const int r) { ratings_total_ = r; }
		void setGenre(const std::string g) { genre_ = g; }
	
		// Custom Methods
		void print() const;
		double calcRatingAvg() const;
		void addRating(int r);
		std::string play() const { return title_; }
};
