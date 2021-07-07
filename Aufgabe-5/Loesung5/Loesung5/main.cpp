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
			<< "(4) getNode() - search node with specific key" << std::endl
			<< "(5) moveToRoot() - move current up to root" << std::endl
			<< "(6) moveToParent() - move current up a level" << std::endl
			<< "(7) moveToChildLeft() - move current to left child" << std::endl
			<< "(8) moveToChildRight() - move current to right child" << std::endl
			<< "(9) checkEmpty() - check if tree is empty" << std::endl
			<< "(10) ins() - add node to tree" << std::endl
			<< "(11) del() - delete current element" << std::endl
			<< "(12) clear() - clear tree" << std::endl
			<< "(13) ini() - ini basic tree" << std::endl
			<< "(14) print() - print tree" << std::endl
			<< "(15) balance() - sussy bakka" << std::endl
			<< "(16) Quit programm" << std::endl << std::endl
			<< "Please choose the operation you wish to execute: ";
		
		// User input
		int input = get_number();
		while (input < 1 || 16 < input)
		{
			std::cout << "Please choose between the given options 1-15!" << std::endl;
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
					std::cout << "Search node by following key (pay in mind keys consist of '0' and '1' marking level in keylength and path in left and right for '0' and '1': ";
					long x = get_number();
					while (x < 1)
					{
						std::cout << "Keys start at 1" << std::endl;
						x = get_number();
					}
						
					a.getNode(x);
					std::cout << "Found node: " << std::endl
						<< "Key: " << a.getCurrent()->key << std::endl
						<< "Value: " << std::to_string(a.getCurrent()->print()) << std::endl;
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
					a.moveToRoot();
					std::cout << "Moved to root successfully!" << std::endl;
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
					a.moveToParent();
					std::cout << "Moved to parent successfully!" << std::endl;
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
					a.moveToChildLeft();
					std::cout << "Moved to left child successfully!" << std::endl;
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
					a.moveToChildRight();
					std::cout << "Moved to left child successfully!" << std::endl;
				}
				catch (std::out_of_range& e)
				{
					std::cout << e.what() << std::endl;
					system("pause");
				}
				break;
			
			case 9:
				std::cout << std::boolalpha;
				std::cout << a.checkEmpty() << std::endl;
				std::cout << std::noboolalpha;
				break;

			
			case 10: {
				std::cout << "Enter number to insert: ";
				int x = get_number();

				try
				{
					a.ins(x);
				}
				catch (std::out_of_range& e)
				{
					std::cout << e.what() << std::endl;
					system("pause");
				}

			} break;

			case 11: {
				std::cout << "Enter key to delete: ";
				const int x = get_number();
				try
				{
					a.del(x);
				}
				catch (std::out_of_range& e)
				{
					std::cout << e.what() << std::endl;
					system("pause");
				}
				catch (std::invalid_argument& e)
				{
					std::cout << e.what() << std::endl;
					system("pause");
				}
			} break;

			case 12:
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

			case 13:
				a.ini();
				break;

			case 14:
				try
				{
					std::stringstream str;
					std::cout << "Choose print mode" << std::endl
						<< "(1) - print tree" << std::endl
						<< "(2) - print tree preorder" << std::endl
						<< "(3) - print tree inorder" << std::endl
						<< "(4) - print tree postorder" << std::endl;

					int x = get_number();
					while (x < 1 || 4 < x)
					{
						std::cout << "Please choose between the given options 1-4!" << std::endl;
						x = get_number();
					}

					switch(x)
					{
						case 1:
							a.print(a.getRoot(), str);
							std::cout << str.str() << std::endl;
							break;
						case 2:
							a.printPreOrder(a.getRoot(), str);
							std::cout << str.str() << std::endl;
							break;
						case 3:
							a.printInOrder(a.getRoot(), str);
							std::cout << str.str() << std::endl;
							break;
						case 4:
							a.printPostOrder(a.getRoot(), str);
							std::cout << str.str() << std::endl;
							break;
						default:
							std::cout << "Invalid print - mode! Please try again!" << std::endl;
					}

				}
				catch (std::out_of_range& e)
				{
					std::cout << e.what() << std::endl;
					system("pause");
				}
				break;

			case 15: {
				try
				{
					a.balance(a.getRoot());
				}
				catch (std::out_of_range& e)
				{
					std::cout << e.what() << std::endl;
					system("pause");
				}
			} break;
			
			case 16:
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