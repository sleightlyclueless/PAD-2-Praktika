#ifndef MOVIE_H
#define MOVIE_H

#include <string>
#include <vector>

class Movie
{
    private:
        // Attributes
        int id_ = -1;
        std::string title_ = "Title unspecified";
        int length_ = -1;
        std::vector<int> ratings_ = {};
        double ratings_avg_ = -1;
        std::string genre_ = "Genre unspecified";

    public:
        // Static ID counter
        static int global_id;

        // Constructor
        Movie(std::string &title, int &length, std::vector<int> &ratings, std::string &genre);

        // Destructor
        ~Movie() = default;

        // Getters / Setters
        int getLength() const { return length_; }
        double getRatingsAvg() const { return ratings_avg_; }

        // Custom Methods
        double calcRatingAvg() const;	// Calculate the avg rating from ratings vector
        std::stringstream print(bool consolemode) const;	// Return a stringstream with all important information of a movie object (with or without id)
        void addRating(int r);	// Add a rating to movie rating-vector
        std::string play() const { return title_; }	// Return title on play() call
};


#endif // MOVIE_H
