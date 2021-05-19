#pragma once
#include "mediafile.h"

// ReSharper disable once CppClassCanBeFinal
class Movie : public MediaFile
{
	public:
		Movie(std::string &title, int &length, std::vector<int> &ratings, std::string &genre, Mediatype &type, int &released);

		std::stringstream print(bool consolemode) const override;

		static std::stringstream checkOlder(Movie &m1, Movie &m2);
	

	private:
		int released_ = -1;
};
