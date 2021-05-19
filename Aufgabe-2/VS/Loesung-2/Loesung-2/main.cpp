#include "database.h"
#include <iostream>
#include <ctime>
#include <thread>
#include <chrono>

#include "movie.h"
#include "series.h"
using namespace std::chrono_literals;

// Function to get only digits on cin inputs
int get_number() {
	// Problem: Before cin int input like 10f3r5 resulted in 10 - break after the letter. Could lead to unwanted results.
	// Therefore check and only accept digit entries.

	// Initialize necessary vars
	std::string str;
	int a = -1;

	// Read whole input cin into string var first, because here it does not break after letters
	while (getline(std::cin, str))
	{
		// Exception if empty - request valid entry
		if (str.empty())
		{
			std::cout << "Error, you have to enter something. Please do so!" << std::endl;
			continue;
		}

		// Search if there is an unwanted char in string.
		// size_t can store up to max size of an object - if we do not find an unaccepted char it becomes -1 or npos (18446744073709551615 == -1)
		size_t const flag = str.find_first_not_of("-0123456789");

		// npos is type size_t and cant be negative therefore it takes on the value of the highest possible number. If that is the case we have an accepted integer input
		if (flag == std::string::npos)
		{
			// Success - valid int - transform to int
			a = stoi(str);
			// If we found an fitting int - exit the whole while loop - we are done here
			break;
		}

		std::cout << "Error, enter only valid int numbers. Please try again!" << std::endl;
	}

	// When we exited the while loop we found an int var. Go ahead and return that to the function call.
	return a;
}

int main()
{
	// Enable utf-8 and srandom seed
	setlocale(LC_ALL, "");
	srand(time(nullptr));

	// Initialize Database beforehand
	Database::init("");

	// Initialize end flag
	bool endthis = false;
	
	while (!endthis && Database::getMovieSize() > 0)
	{
		// Print user interface
		std::cout << std::endl
			<< "Welcome to your movie database. What do you want do do?" << std::endl
			<< "Please choose one of the following options:" << std::endl
			<< "(1) Show all movies in vector - sorted by avg rating" << std::endl
			<< "(2) Play specific movie from its id" << std::endl
			<< "(3) Add review(s) to mediafile" << std::endl
			<< "(4) Load Database from file" << std::endl
			<< "(5) Save Database to file" << std::endl
			<< "(6) Add mediafile" << std::endl
			<< "(7) Remove mediafile" << std::endl
			<< "(8) Compare movies for older" << std::endl
			<< "(9) Show average viewtime" << std::endl
			<< "(10) Show total viewtime" << std::endl
			<< "(11) Simulate n amount of ratings" << std::endl
			<< "(12) Quit programm" << std::endl;

		// Get input
		int input = get_number();
		while (input < 1 || input > 12)
		{
			std::cout << "Please choose between the given options 1-12!" << std::endl;
			input = get_number();
		}

		bool run = true;
		std::string filename;

		// Process selection with given functions
		switch (input)
		{
			case 1:
				Database::sortMovies();
				Database::printMovies();
				break;
			
			case 2:
				if (Database::getMovieSize() > 0)
				{
					std::cout << "Enter the id of the medium in the Database to play: ";
					int x = get_number();
					Database::playMedium(x);
				}
				else
				{
					std::cout << "No movies left!" << std::endl;
				}
				break;
			
			case 3: {
					if (Database::getMovieSize() > 0)
					{
						std::cout << "Enter the id of the movie in the Database to add ratings to." << std::endl;
						const int id = get_number();
						bool found = false;
						int pos = 0;
						for (MediaFile*& m : Database::getMovies())
						{
							if (m->getId() == id)
							{
								found = true;
								break;
							}
							pos++;
						}

						if (found)
						{
							while (run)
							{
								std::cout << "Enter rating for the movie (1 - 5): ";
								int mrating = get_number();
								while (mrating < 1 || mrating > 5) {
									std::cout << "Please enter a valid number (1 - 5)!" << std::endl;
									mrating = get_number();
								}
								Database::getMovies().at(pos)->addRating(mrating);

								std::cout << "Do you want to add another rating? Please choose one of the following options:" << std::endl
									<< "(1) Yes" << std::endl
									<< "(2) No" << std::endl;
								int x = get_number();
								while (x < 1 || x > 2)
								{
									std::cout << "Please enter a valid number: 1 or 2!" << std::endl;
									x = get_number();
								}
								if (x == 1)
									continue;

								run = false;
							}
							std::cout << std::endl;
						}
						else
						{
							std::cout << "MediaFile did not exist in our database! Please try again!" << std::endl;
						}
					}
					else
					{
						std::cout << "No movies left!" << std::endl;
					}

				} break;
			
			case 4:
				{
					int counter = 0;
					bool flag = false;

					while (counter < 3 && flag == false)
					{
						std::cout << "Please enter text-filename for the load: (" << 3 - counter << " tries left!) ";
						getline(std::cin, filename);
						if (filename.find(".txt") == std::string::npos)
							filename += ".txt";

						flag = Database::init(filename);

						if (!flag)
							counter++;
					}

					if (!flag)
					{
						std::this_thread::sleep_for(2s);
						std::cout << "Manual init failed. Using standard database!" << std::endl;
						Database::init("");
					}
				
				} break;
			
			case 5:
				{
					std::cout << "Please enter text-filename for the save: ";
					getline(std::cin, filename);
					if (filename.find(".txt") == std::string::npos)
						filename += ".txt";

					Database::printMovies(filename);
				} break;
			
			case 6:	{
					// Initialize nessecary case vars
					std::string mname;
					std::string mgenre;

					std::cout << "Enter the name of the media: ";
					getline(std::cin, mname);
					std::cout << std::endl;

					std::cout << "Enter the total length of the media in minutes: ";
					int mlength = get_number();
					std::cout << std::endl;

					std::cout << "Enter ratings of the media 1 - 5: ";
					std::vector<int> mratings;
					int mrating = get_number();
					while (mrating < 1 || mrating > 5) {
						std::cout << "Please enter a valid number: 1 - 5!" << std::endl;
						mrating = get_number();
					}
					mratings.push_back(mrating);
					int x = 1;
					while (x == 1)
					{
						std::cout << "Do you want to add another rating? Please choose one of the following options:" << std::endl
							<< "(1) Yes" << std::endl
							<< "(2) No" << std::endl;
						x = get_number();
						while (x < 1 || x > 2)
						{
							std::cout << "Please enter a valid number: 1 or 2!" << std::endl;
							x = get_number();
						}
						if (x == 1) {
							std::cout << "Enter ratings of the movie 1 - 5: ";
							mrating = get_number();
							while (mrating < 1 || mrating > 5) {
								std::cout << "Please enter a valid number: 1 - 5!" << std::endl;
								mrating = get_number();
							}
							mratings.push_back(mrating);
						}
					}
					std::cout << std::endl;

					std::cout << "Enter the genre of the media: ";
					getline(std::cin, mgenre);
					std::cout << std::endl;

					Mediatype type;
					MediaFile* m;
					int n;
					std::cout << "Enter the type of the media: " << std::endl
						<< "(0) - Other media" << std::endl
						<< "(1) - Movie" << std::endl
						<< "(2) - Series" << std::endl;
					x = get_number();
					while (x < 0 || x > 2)
					{
						std::cout << "Please enter a valid number: 1 or 2!" << std::endl;
						x = get_number();
					}
					
					switch(x)
					{
						case 0:
							type = Mediatype::mediafile;
							m = new MediaFile(mname, mlength, mratings, mgenre, type);
							Database::addMediafile(m);
							break;
						case 1:
							type = Mediatype::movie;
						
							std::cout << "Enter the release year of the movie: ";
							n = get_number();
							std::cout << std::endl;

							m = new Movie(mname, mlength, mratings, mgenre, type, n);
							Database::addMediafile(m);
							break;
						case 2:
							type = Mediatype::series;

							std::cout << "Enter the amount of episodes for the series: ";
							n = get_number();
							std::cout << std::endl;

							m = new Series(mname, mlength, mratings, mgenre, type, n);
							Database::addMediafile(m);
							
							break;
						default:
							std::cout << "Something went wrong." << std::endl;
							break;
					}
				} break;

			case 7: {
					
				if (Database::getMovieSize() > 0)
				{
					std::cout << "Enter the id of the mediafile you wish to remove from the database." << std::endl;
					int x = get_number();
					while (x < 0 || x > Database::getMovieSize() - 1)
					{
						std::cout << "Please enter a valid position from 0 - " << Database::getMovieSize() - 1 << "!" << std::endl;
						x = get_number();
					}

					Database::removeMediafile(x);
				}
				else
				{
					std::cout << "No movies left!" << std::endl;
				}
			} break;

			case 8: {

				if (Database::getMovieSize() > 0)
				{
					MediaFile* m1 = nullptr;
					MediaFile* m2 = nullptr;
					bool found1 = false;
					bool found2 = false;

					std::cout << "Enter the id of the first movie to compare: ";
					const int id1 = get_number();

					for (MediaFile*& m : Database::getMovies())
					{
						if (m->getId() == id1 && m->getMediaType() == Mediatype::movie)
						{
							found1 = true;
							m1 = m;
							break;
						}
					}

					std::cout << "Enter the id of the second movie to compare: ";
					const int id2 = get_number();
					for (MediaFile*& m : Database::getMovies())
					{
						if (m->getId() == id2 && m->getMediaType() == Mediatype::movie)
						{
							found2 = true;
							m2 = m;
							break;
						}
					}

					if (found1 && found2)
					{
						Movie mov1 = dynamic_cast<const Movie&>(*m1);
						Movie mov2 = dynamic_cast<const Movie&>(*m2);
						std::cout << Movie::checkOlder(mov1, mov2).str();
					}
					else
					{
						std::cout << "Something went wrong with this comparison! Please try again!" << std::endl;
					}

				}
				else
				{
					std::cout << "No movies left!" << std::endl;
				}
			} break;

			case 9:
				Database::returnAvgViewTime();
				break;

			case 10:
				Database::returnTotalViewTime();
				break;

			case 11:
				{
					std::cout << "Enter the amount of random reviews you want to enter into the database: ";
					int x = get_number();
					while (x < 1)
					{
						std::cout << "Please enter a valid number above 0!" << std::endl;
						x = get_number();
					}
					Database::simulateReviews(x);
				} break;
			
			case 12:
				endthis = true;
				break;
			
			default:
				std::cout << "Error: Option not available!" << std::endl;
				break;
		}
		std::cout << std::endl << std::endl;
	}
	
	return 0;
}

