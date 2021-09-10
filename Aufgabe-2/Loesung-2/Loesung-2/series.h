#pragma once
#include "mediafile.h"

// ReSharper disable once CppClassCanBeFinal
class Series : public MediaFile
{
	public:
		Series(std::string &title, int &length, std::vector<int> &ratings, std::string &genre, Mediatype &type, int &episodes);

		std::stringstream print(bool consolemode) const override;
	// TODO OVERRIDE IST NUR EINE PRÜFUNG OB OBERKLASSE FUNKTION HAT
		std::string play() override;

		int getLength() const override { return lengthavg_; }
		int getTotalLength() const override { return length_; }

	private:
		int episodes_ = -1;
		int nextepisode_ = 1;
		int lengthavg_ = -1;
};
