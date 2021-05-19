#pragma once
#include "mediafile.h"

// ReSharper disable once CppClassCanBeFinal
class Series : public MediaFile
{
	public:
		Series(std::string &title, int &length, std::vector<int> &ratings, std::string &genre, Mediatype &type, int &episodes);

		std::stringstream print(bool consolemode) const override;
		std::string play() override;

	private:
		int episodes_ = -1;
		int nextepisode_ = -1;
		int lengthavg_ = -1;
};
