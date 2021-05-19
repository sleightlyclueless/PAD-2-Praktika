#pragma once
#include <string>
#include <vector>
#include <ostream>

enum class Mediatype
{
	mediafile = 0,
	movie,
	series
};
inline std::ostream& operator << (std::ostream& os, const Mediatype& m)
{
	const int x = (int)m;
	switch (x)
	{
		case 0:
			os << "Other media";
			break;
		case 1:
			os << "Movie";
			break;
		case 2:
			os << "Series";
			break;
		default:
			os << "Enum value does not exist";
			break;
	}
	return os;
}

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
		std::string getTitle() const { return title_; }
		virtual int getLength() const { return length_; }
		virtual int getTotalLength() const { return length_; }
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
