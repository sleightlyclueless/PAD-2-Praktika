#include <iostream>
#include <ctime>
#include "database.h"


// Function to get only digits on cin inputs
int get_number() {
	// Problem: Before cin int input like 10f3r5 resulted in 10 - break after the letter. Could lead to unwanted results.
	// Therefore check and only accept digit entries.

	// Initialize necessary vars
	std::string str;
	int a;
	int firsttime = 0;

	// Read whole input cin into string var first, because here it does not break after letters
	while (getline(std::cin, str))
	{
		// Exception if empty - request valid entry
		if (str.empty())
		{
			if (firsttime != 0)
			{
				std::cout << "Error, you have to enter something. Please do so!" << std::endl;
			}
			continue;
		}

		// Search if there is an unwanted char in string.
		// size_t can store up to max size of an object - if we do not find an unaccepted char it becomes -1 or npos (18446744073709551615 == -1)
		auto const flag = str.find_first_not_of("-0123456789");

		// npos is type size_t and cant be negative therefore it takes on the value of the highest possible number. If that is the case we have an accepted integer input
		if (flag == std::string::npos)
		{
			// Success - valid int - transform to int
			a = stoi(str);
			// If we found an fitting int - exit the whole while loop - we are done here
			break;
		}

		std::cout << "Error, enter only valid int numbers. Please try again!" << std::endl;
		firsttime++;
	}

	// When we exited the while loop we found an int var. Go ahead and return that to the function call.
	return a;
}

int main()
{
	setlocale(LC_ALL, "");
	srand(time(nullptr));

	Database::init();

	bool endthis = false;
	while (!endthis)
	{
		std::cout << "Welcome to your movie database. What do you want do do?"
			<< "Please choose one of the following options:" << std::endl
			<< "(1) Show all movies in vector" << std::endl
			<< "(2) Add a movie" << std::endl
			<< "(3) Remove movie from a specific position in vector" << std::endl
			<< "(4) Re-Sort movies" << std::endl
			<< "(5) Print average viewtime" << std::endl
			<< "(6) Print total viewtime" << std::endl
			<< "(7) Play specific movie from its position in vector" << std::endl
			<< "(8) Add random amount of random rewievs into vector" << std::endl
			<< "(9) Save current sorted state into file" << std::endl
			<< "(10) Quit programm" << std::endl;


		int input = get_number();
		while (input < 1 || input > 9)
		{
			std::cout << "Please choose between the given options 1-9!" << std::endl;
			input = get_number();
		}
		Movie m;
		int x;
		std::string filename;
		switch (input)
		{
		case 1:
			Database::printMovies();
			break;
		case 2:
			m = Movie("Paprika", 90, { 4, 4, 5, 3, 5 }, "Anime");
			Database::addMovie(m);
			break;
		case 3:
			if (Database::getMovieSize() > 0)
			{
				std::cout << "Enter the position of the movie in the Database to remove (counting starts at 0!): ";
				x = get_number();
				while (x < 0 || x > Database::getMovieSize() - 1)
				{
					std::cout << "Please enter a valid position from 0 - " << Database::getMovieSize() - 1 << "!" << std::endl;
					x = get_number();
				}
				Database::removeMovie(x);
			}
			else
			{
				std::cout << "No movies left!" << std::endl;
			}
			break;
		case 4:
			Database::sortMovies();
			Database::printMovies();
			break;
		case 5:
			std::cout << "Average viewtime is: " << Database::printAvgViewTime() << "min!" << std::endl;
			break;
		case 6:
			std::cout << "Total viewtime is: " << Database::printTotalViewTime() << "min!" << std::endl;
			break;
		case 7:
			if (Database::getMovieSize() > 0)
			{
				std::cout << "Enter the position of the movie in the Database to play (counting starts at 0!): ";
				x = get_number();
				while (x < 0 || x > Database::getMovieSize() - 1)
				{
					std::cout << "Please enter a valid position from 0 - " << Database::getMovieSize() - 1 << "!" << std::endl;
					x = get_number();
				}
				Database::playMovie(x);
			}
			else
			{
				std::cout << "No movies left!" << std::endl;
			}

			break;
		case 8:
			std::cout << "Enter the amount of random reviews you want to enter into the database: ";
			x = get_number();
			while (x < 1)
			{
				std::cout << "Please enter a valid number above 0!" << std::endl;
				x = get_number();
			}
			Database::simulateReviews(x);
			break;
		case 9:
			std::cout << "Please enter filename: ";
			std::cin >> filename;
			if (filename.find(".txt") == std::string::npos)
				filename += ".txt";
			Database::printMovies(filename);
			break;
		case 10:
			endthis = true;
			break;
		default:
			std::cout << "Error: Option not available!" << std::endl;
			break;
		}
	}
	
	return 0;
}

