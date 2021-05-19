#pragma once
#include <string>
#include <vector>

enum class Mediatype
{
	mediafile = 0,
	movie,
	series
};

class MediaFile
{
	public:
		// Static ID counter
		static int global_id;

		// Constructor
		MediaFile(std::string &title, int &length, std::vector<int> &ratings, std::string &genre, Mediatype &type);

		// Destructor
		virtual ~MediaFile() = default;

		// Getters / Setters
		int getId() const { return id_; }
		int getLength() const { return length_; }
		double getRatingsAvg() const { return ratings_avg_; }
		Mediatype getMediaType() const { return type_; }
	
		// Custom Methods
		double calcRatingAvg() const;	// Calculate the avg rating from ratings vector
		void addRating(int r);	// Add a rating to movie rating-vector
	
		virtual std::stringstream print(bool consolemode) const;	// Return a stringstream with all important information of a movie object (with or without id)
		virtual std::string play() { return title_; }	// Return title on play() call

	protected:
		// Attributes
		int id_ = -1;
		std::string title_ = "Title unspecified";
		int length_ = -1;
		std::vector<int> ratings_ = {};
		double ratings_avg_ = -1;
		std::string genre_ = "Genre unspecified";
		Mediatype type_ = Mediatype::mediafile;
		
};
