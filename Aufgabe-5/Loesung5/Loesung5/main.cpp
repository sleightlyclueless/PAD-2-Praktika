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
			<< "(1) getLength() - check length of tree" << std::endl
			<< "(2) getRoot() - check root element" << std::endl
			<< "(3) getCurrent() - check current element" << std::endl
			<< "(4) moveToRoot() - move current up to root" << std::endl
			<< "(5) moveToParent() - move current up a level" << std::endl
			<< "(6) moveToChildLeft() - move current to left child" << std::endl
			<< "(7) moveToChildRight() - move current to right child" << std::endl
			<< "(8) checkEmpty() - check if tree is empty" << std::endl
			<< "(9) insRoot() - add root element" << std::endl
			<< "(10) insLeft() - add left child element" << std::endl
			<< "(11) insRight() - add right child element" << std::endl
			<< "(12) del() - delete current element" << std::endl
			<< "(13) clear() - clear tree" << std::endl
			<< "(14) print() - print tree" << std::endl
			<< "(15) Quit programm" << std::endl << std::endl
			<< "Please choose the operation you wish to execute: ";
		
		// User input
		int input = get_number();
		while (input < 1 || 15 < input)
		{
			std::cout << "Please choose between the given options 1-7!" << std::endl;
			input = get_number();
		}

		switch (input)
		{
			case 1:
				std::cout << "Elements within tree: " << a.getLength() << std::endl;
				break;

			case 2:
				try
				{
					std::cout << "Root element: " << std::endl
						<< "Key: " << a.getRoot()->key << std::endl
						<< "Value: " << std::to_string(a.getRoot()->print()) << std::endl;
				}
				catch (std::out_of_range& e)
				{
					std::cout << e.what() << std::endl;
					system("pause");
				}
				break;

			case 3:
				try
				{
					std::cout << "Current element: " << std::endl
						<< "Key: " << a.getCurrent()->key << std::endl
						<< "Value: " << std::to_string(a.getCurrent()->print()) << std::endl;
				}
				catch (std::out_of_range& e)
				{
					std::cout << e.what() << std::endl;
					system("pause");
				}
				break;

			case 4:
				try
				{
					a.moveToRoot();
					std::cout << "Moved to root successfully!" << std::endl;
				}
				catch (std::out_of_range& e)
				{
					std::cout << e.what() << std::endl;
					system("pause");
				}
				break;
			
			case 5:
				try
				{
					a.moveToParent();
					std::cout << "Moved to parent successfully!" << std::endl;
				}
				catch (std::out_of_range& e)
				{
					std::cout << e.what() << std::endl;
					system("pause");
				}
				break;

			case 6:
				try
				{
					a.moveToChildLeft();
					std::cout << "Moved to left child successfully!" << std::endl;
				}
				catch (std::out_of_range& e)
				{
					std::cout << e.what() << std::endl;
					system("pause");
				}
				break;

			case 7:
				try
				{
					a.moveToChildRight();
					std::cout << "Moved to left child successfully!" << std::endl;
				}
				catch (std::out_of_range& e)
				{
					std::cout << e.what() << std::endl;
					system("pause");
				}
				break;
			
			case 8:
				std::cout << std::boolalpha;
				std::cout << a.checkEmpty() << std::endl;
				std::cout << std::noboolalpha;
				break;

			
			case 9: {
				std::cout << "Enter number to insert: ";
				int x = get_number();

				try
				{
					a.insRoot(x);
				}
				catch (std::out_of_range& e)
				{
					std::cout << e.what() << std::endl;
					system("pause");
				}

			} break;

			case 10: {
				std::cout << "Enter number to insert: ";
				int x = get_number();

				try
				{
					a.insLeft(a.getCurrent(), x);
				}
				catch (std::out_of_range& e)
				{
					std::cout << e.what() << std::endl;
					system("pause");
				}
					
			} break;

			case 11: {
				std::cout << "Enter number to insert: ";
				int x = get_number();

				try
				{
					a.insRight(a.getCurrent(), x);
				}
				catch (std::out_of_range& e)
				{
					std::cout << e.what() << std::endl;
					system("pause");
				}

			} break;

			case 12: {
					
				try
				{
					a.del();
				}
				catch (std::out_of_range& e)
				{
					std::cout << e.what() << std::endl;
					system("pause");
				}

			} break;

			case 13:
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

			case 14:
				try
				{
					std::stringstream str;
					a.print(a.getRoot(), str);
					std::cout << str.str() << std::endl;
				}
				catch (std::out_of_range& e)
				{
					std::cout << e.what() << std::endl;
					system("pause");
				}
				break;

			case 15:
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