#include <iostream>
#include "database.h"

int main()
{
	setlocale(LC_ALL, "");
	
	const std::vector<int> ratings = { 0,1,4,6 };
	const Movie m = Movie("Filmtitel", 200, ratings, 11, "Hardcore");

	Database::addMovie(m);
	Database::playMovie(0);

	
	return 0;
}
