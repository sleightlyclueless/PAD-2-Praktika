#pragma once
#include <fstream>
#include <sstream>

inline void init()
{
	// ifstream
	// ofstream
	std::ifstream source;
	std::string line;

	std::vector<std::string> titles;
	std::vector<int> lens;
	std::vector<std::string> ratings;
	std::vector<std::string> genres;
	
	try
	{
		source.open("database.txt", std::ios::in);

		if (!source)
			return;

		
		while (std::getline(source, line))
		{
			int pos;
			
			if (line.find("Title"))
			{
				pos = line.find("Title: ");
				titles.push_back(line.substr(pos + 1));
			}
			if (line.find("Laenge"))
			{
				pos = line.find("Laenge: ");
				lens.push_back(std::stoi(line.substr(pos + 1)));
			}
			if (line.find("Bewertungen"))
			{
				pos = line.find("Bewertungen: ");
				ratings.push_back(line.substr(pos + 1));
			}
			if (line.find("Genre"))
			{
				pos = line.find("Genre: ");
				genres.push_back(line.substr(pos + 1));
			}
		}

		source.close();
	}
	catch (std::ifstream::failure &e)
	{
		std::cout << e.what() << std::endl;
	}


	for (int i = 0; i < titles.size(); i++)
	{
		std::string t = titles.at(i);
		int l = lens.at(i);
		std::string r = ratings.at(i);
		std::string g = genres.at(i);


		// TODO PROCESS RATINGS AND SO ON
		std::stringstream ss(r);
		std::istream_iterator<std::string> begin(ss);
		std::istream_iterator<std::string> end;
		std::vector<std::string> vstrings(begin, end);
		std::copy(vstrings.begin(), vstrings.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
	}
	
}
