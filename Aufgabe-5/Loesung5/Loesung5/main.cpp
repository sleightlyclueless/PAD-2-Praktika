#include <iostream>
#include "main.h"
#include "BinarySearchTree.h"

int main()
{
	srand(time(nullptr));

	BinarySearchTree<int> a;             // sorted linked List aus ints
	
	bool endthis = false;    // checkEnd flag

	while (!endthis)
	{
		// Print user interface
		std::cout
			<< "Welcome to your linked list (type int). You can execute the following operations:" << std::endl
			<< "(1) checkEmpty - check if list is empty" << std::endl
			<< "(2) getCurrent - print current element" << std::endl
			<< "(3) insroot - insert element at current position" << std::endl
			<< "(4) insleft - insert element at current position" << std::endl
			<< "(5) insright - insert element at current position" << std::endl
			<< "(6) del - delete element at current position" << std::endl
			<< "(7) clear - clear tree" << std::endl
			<< "(8) Print tree" << std::endl
			<< "(9) Quit programm" << std::endl << std::endl
			<< "Please choose the operation you wish to execute: ";

		// User input
		int input = get_number();
		while (input < 1 || 9 < input)
		{
			std::cout << "Please choose between the given options 1-7!" << std::endl;
			input = get_number();
		}

		switch (input)
		{
			case 1:
				std::cout << std::boolalpha;  // return bool as strings
				std::cout << a.checkEmpty() << std::endl;
				std::cout << std::noboolalpha;
				break;

			case 2:
				try
				{
					std::cout << "Current value: " << std::to_string(a.get()->print()) << std::endl;
				}
				catch (std::out_of_range& e)
				{
					std::cout << e.what() << std::endl;
					system("pause");
				}
			
				break;
			
			case 3: {
				std::cout << "Enter number to insert: ";
				int x = get_number();

				if(a.insRoot(x))
					std::cout << "Node with value " << x << " inserted successfully." << std::endl;
				else
					std::cout << "Node could not be inserted." << std::endl;

			} break;

			case 4: {
				std::cout << "Enter number to insert: ";
				int x = get_number();

				if (a.insLeft(a.getCurrent(), x))
					std::cout << "Node with value " << x << " inserted successfully." << std::endl;
				else
					std::cout << "Node could not be inserted." << std::endl;

			} break;

			case 5: {
				std::cout << "Enter number to insert: ";
				int x = get_number();

				if (a.insRight(a.getCurrent(), x))
					std::cout << "Node with value " << x << " inserted successfully." << std::endl;
				else
					std::cout << "Node could not be inserted." << std::endl;

			} break;

			case 6: {
				if (a.del())
					std::cout << "Current node deleted successfully." << std::endl;
				else
					std::cout << "Nothing to delete." << std::endl;

			} break;

			case 7:
				try
				{
					a.clear(a.getRoot());
					std::cout << "List cleared successfully" << std::endl;
				}
				catch (std::out_of_range& e)
				{
					std::cout << e.what() << std::endl;
					system("pause");
				}
				break;

			case 8:
				try
				{
					std::stringstream str;
					a.print_tree(a.getRoot(), str);
					std::cout << str.str() << std::endl;
				}
				catch (std::out_of_range& e)
				{
					std::cout << e.what() << std::endl;
					system("pause");
				}
				break;

			case 9:
				endthis = true;
				break;

			default:
				std::cout << "Invalid command." << std::endl;
				system("pause");
				break;
		}

		std::cout << std::endl << "==============================================" << std::endl;

	}

	return 0;
}