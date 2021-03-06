#include <iostream>
#include "main.h"
#include "BinarySearchTree.h"

int main()
{

	BinarySearchTree<int> a;		// sorted linked List aus ints
	bool endthis = false;			// checkEnd flag

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
			<< "(14) balance() - balance tree (same deepest level)" << std::endl
			<< "(15) print() - print tree" << std::endl
			<< "(16) Quit programm" << std::endl << std::endl
			<< "Please choose the operation you wish to execute: ";
		
		// User input
		int input = get_number();
		while (input < 1 || 16 < input)
		{
			std::cout << "Please choose between the given options 1-15!" << std::endl;
			input = get_number();
		}

		// Try and catch al cases
		try
		{
			switch (input)
			{			
				case 1:
					std::cout << "Amount of elements within tree: " << a.getLength() << std::endl;
					break;

				case 2:
					std::cout << "Root element: " << std::endl
						<< "Key: " << a.getRoot()->key << std::endl
						<< "Value: " << std::to_string(a.getRoot()->print()) << std::endl;
					break;

				case 3:
					std::cout << "Current element: " << std::endl
						<< "Key: " << a.getCurrent()->key << std::endl
						<< "Value: " << std::to_string(a.getCurrent()->print()) << std::endl;
					break;

				case 4: {
					std::cout
						<< "Search node by following key (pay in mind keys consist of '0' and '1' marking level in keylength and path in left and right for '0' and '1': ";
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
				} break;

				case 5:
					a.moveToRoot();
					std::cout << "Moved to root successfully!" << std::endl;
					break;

				case 6:
					a.moveToParent();
					std::cout << "Moved to parent successfully!" << std::endl;
					break;

				case 7:
					a.moveToChildLeft();
					std::cout << "Moved to left child successfully!" << std::endl;
					break;

				case 8:
					a.moveToChildRight();
					std::cout << "Moved to right child successfully!" << std::endl;
					break;

				case 9:
					std::cout << std::boolalpha;
					std::cout << a.checkEmpty() << std::endl;
					std::cout << std::noboolalpha;
					break;

				case 10: {
					std::cout << "Enter number to insert: ";
					const int x = get_number();
					a.ins(x);
				} break;

				case 11: {
					std::cout << "Enter key to delete: ";
					const int x = get_number();
					a.del(x);
				} break;

				case 12:
					a.clear(a.getRoot());
					std::cout << "List cleared successfully" << std::endl;
					break;

				case 13:
					a.ini();
					break;

				case 14: {
					a.balance(a.getRoot());
				} break;

				case 15: {
					std::stringstream str;
					std::cout << "Choose print mode" << std::endl
						<< "(1) - print tree preorder" << std::endl
						<< "(2) - print tree inorder" << std::endl
						<< "(3) - print tree postorder" << std::endl;

					int x = get_number();
					while (x < 1 || 3 < x)
					{
						std::cout << "Please choose between the given options 1-4!" << std::endl;
						x = get_number();
					}

					switch (x)
					{
						case 1:
							a.printPreOrder(a.getRoot(), str);
							std::cout << "Your tree consists of -" << a.getLength() << "- nodes:" << std::endl
								<< str.str() << std::endl;
							break;
						case 2:
							a.printInOrder(a.getRoot(), str);
							std::cout << "Your tree consists of -" << a.getLength() << "- nodes:" << std::endl
								<< str.str() << std::endl;
							break;
						case 3:
							a.printPostOrder(a.getRoot(), str);
							std::cout << "Your tree consists of -" << a.getLength() << "- nodes:" << std::endl
								<< str.str() << std::endl;
							break;
						default:
							std::cout << "Invalid print - mode! Please try again!" << std::endl;
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

		std::cout << std::endl << "==============================================" << std::endl;

	}

	return 0;
}