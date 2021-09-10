#pragma once
#include <fstream>
#include <iostream>
#include <string>

struct dimensions
{
	int h;
	int w;
} h, d;

inline void bonus()
{/*
	double d;
	const std::string file = "cover1.ppm";

	std::ofstream output;
	std::ifstream input;
	std::string line;

	int w = 1000;
	int h = 600;

	try
	{
		std::ofstream fout("cover2.ppm");
		if (!fout)
			throw std::runtime_error("Database::bonus(...): File could not be opened!");

		fout << "P3\n";
		fout << w << " " << h << "\n";
		fout << "255\n";

		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				fout << rand() % 256 << " "
					<< rand() % 256 << " "
					<< rand() % 256 << " ";
			}
		}

		fout.close();
	}
	catch (std::runtime_error& e)
	{
		std::cout << e.what() << std::endl;
		return;
	}
*/}
