#include "List.h"
#include "main.h"

#include <chrono>

int main()
{
    srand(time(nullptr));
	
	List<int> a;             // sorted linked List aus ints
    // List<double> a;       // sorted linked List aus ints
    // List<char> a;         // sorted linked List aus ints
    // List<std::string> a;  // sorted linked List aus ints
	
    bool endthis = false;    // checkEnd flag

    while (!endthis)
    {
        // Print user interface
        std::cout
            << "Welcome to your linked list (type int). You can execute the following operations:" << std::endl
            << "(1) get - get current Node" << std::endl
            << "(2) checkEmpty - check if list is empty" << std::endl
            << "(3) checkBeginning - check if we reached lists start" << std::endl
            << "(4) checkEnd - check if we reached lists end" << std::endl
            << "(5) adv - advance pointer forward once" << std::endl
            << "(6) rec - recede pointer backwards once" << std::endl
            << "(7) reset - pointer to first" << std::endl
            << "(8) insNode - insert element at current position" << std::endl
			<< "(9) insNodeSorted - insert element at sorted position (requires sorted list)" << std::endl
            << "(10) del - delete element at current position" << std::endl
            << "(11) fill - fill list with n random elements" << std::endl
            << "(12) clear - clear list" << std::endl
            << "(13) selectionsort - run selectionsort on list" << std::endl
            << "(14) insertionsort - run insertionsort on list" << std::endl
            << "(15) bubblesort - run bubblesort on list" << std::endl
            << "(16) mergesort - run mergesort on list" << std::endl
            << "(17) heapsort - run heapsort on list" << std::endl
            << "(18) quickort - run quicksort on list" << std::endl
            << "(19) quickort stable - run quicksort stable on list" << std::endl
            << "(20) print - print full list" << std::endl
            << "(21) print tree - print full list with tree view" << std::endl
            << "(22) Quit programm" << std::endl << std::endl
            << "Please choose the operation you wish to execute: ";

        // User input
        int input = get_number();
        while (input < 1 || 22 < input)
        {
            std::cout << "Please choose between the given options 1-21!" << std::endl;
            input = get_number();
        }

        std::chrono::time_point<std::chrono::system_clock> t0;
        std::chrono::time_point<std::chrono::system_clock> t1;
        std::chrono::duration<double> T{};

        switch (input)
        {
	        case 1:
	            try
	            {
	                std::cout << "Current element: " << a.get().print() << std::endl;
	            }
	            catch (std::out_of_range& e)
	            {
	                std::cout << e.what() << std::endl;
	                system("pause");
	            }
	            break;

	        case 2:
	            std::cout << std::boolalpha;  // return bool as strings
	            std::cout << a.checkEmpty() << std::endl;
	            std::cout << std::noboolalpha;
	            break;

	        case 3:
	            std::cout << std::boolalpha;  // return bool as strings
	            std::cout << a.checkBeginning() << std::endl;
	            std::cout << std::noboolalpha;
	            break;

	        case 4:
	            std::cout << std::boolalpha;  // return bool as strings
	            std::cout << a.checkEnd() << std::endl;
	            std::cout << std::noboolalpha;
	            break;

	        case 5: {
	            if (a.adv())
	                std::cout << "Pointer advanced successfully" << std::endl;
	            else
	            {
	                std::cout << "Error in List<T>::adv(): Pointer can not advance - You reached the lists end." << std::endl;
	                system("pause");
	            }
	        }   break;

	        case 6: {
	            if (a.rec())
	                std::cout << "Pointer receded successfully" << std::endl;
	            else
	            {
	                std::cout << "Error in List<T>::rec(): Pointer can not recede - You reached the lists beginning." << std::endl;
	                system("pause");
	            }
	        }   break;

	        case 7:
	            try
	            {
	                a.reset();
	                std::cout << "Pointer reset successfully" << std::endl;
	            }
	            catch (std::out_of_range& e)
	            {
	                std::cout << e.what() << std::endl;
	                system("pause");
	            }
        		
	            break;

	        case 8: {
	            std::cout << "Enter number to insert: ";
	            const int x = get_number();

	            /*double x;
	            std::cin >> x;*/

	            /*char x;
	            std::cin >> x;*/

	            /*std::string x;
	            std::getline(std::cin, x);*/

	            try
	            {
	                //a.insNodeSorted(x);
	                a.insNode(x);
	                std::cout << "Node with value ";

	                if (typeid(x) != typeid(std::string))
	                    std::cout << std::to_string(x);
	                else
	                    std::cout << x;

	                if (typeid(x) == typeid(char))
	                    std::cout << "(" << x << ")";

	                std::cout << " inserted successfully." << std::endl;
	            }
	            catch (...)
	            {
	                std::cout << "Node could not be inserted." << std::endl;
	                system("pause");
	            }
	        } break;

			case 9: {
				std::cout << "Enter number to insert: ";
				const int x = get_number();

				/*double x;
				std::cin >> x;*/

				/*char x;
				std::cin >> x;*/

				/*std::string x;
				std::getline(std::cin, x);*/

				try
				{
					//a.insNodeSorted(x);
					a.insNodeSorted(x);
					std::cout << "Node with value ";

					if (typeid(x) != typeid(std::string))
						std::cout << std::to_string(x);
					else
						std::cout << x;

					if (typeid(x) == typeid(char))
						std::cout << "(" << x << ")";

					std::cout << " inserted successfully." << std::endl;
				}
				catch (...)
				{
					std::cout << "Node could not be inserted." << std::endl;
					system("pause");
				}
			} break;

	        case 10:
	            if (!a.checkEmpty()) {
	                a.del();
	                std::cout << "Current node deleted successfully." << std::endl;
	            }
	            else
	            {
	                std::cout << "Nothing to delete." << std::endl;
	                system("pause");
	            }
	            break;

	        case 11: {
	            std::cout << "How many elements would you like to enter into your list?" << std::endl;
	            const int x = get_number();
	            std::cout << "Elements in my list should be values between 0 and ";
	            const int y = get_number();
	            a.fill(x, y);
	        } break;

	        case 12:
	            try
	            {
	                a.clear();
	                std::cout << "List cleared successfully" << std::endl;
	            }
	            catch (std::out_of_range& e)
	            {
	                std::cout << e.what() << std::endl;
	                system("pause");
	            }
	            break;

	        case 13:
	            try
	            {
	                t0 = std::chrono::system_clock::now();
	                std::cout << List<int>::selectionSort(a).str() << std::endl;
	                t1 = std::chrono::system_clock::now();
	                T = t1 - t0;
	                std::cout << "Selectionsort took " << T.count() << "s to complete." << std::endl;
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
	                t0 = std::chrono::system_clock::now();
	                std::cout << List<int>::insertionSort(a).str() << std::endl;
	                t1 = std::chrono::system_clock::now();
	                T = t1 - t0;
	                std::cout << "Insertionsort took " << T.count() << "s to complete." << std::endl;
	            }
	            catch (std::out_of_range& e)
	            {
	                std::cout << e.what() << std::endl;
	                system("pause");
	            }
	            break;

	        case 15:
	            try
	            {
	                t0 = std::chrono::system_clock::now();
	                std::cout << List<int>::bubbleSort(a).str() << std::endl;
	                t1 = std::chrono::system_clock::now();
	                T = t1 - t0;
	                std::cout << "Bubblesort took " << T.count() << "s to complete." << std::endl;
	            }
	            catch (std::out_of_range& e)
	            {
	                std::cout << e.what() << std::endl;
	                system("pause");
	            }
	            break;
        	
	        case 16:
	            try
	            {
	                t0 = std::chrono::system_clock::now();
	                std::cout << List<int>::mergeSort(a).str() << std::endl;
	                t1 = std::chrono::system_clock::now();
	                T = t1 - t0;
	                std::cout << "Mergesort took " << T.count() << "s to complete." << std::endl;
	            }
	            catch (std::out_of_range& e)
	            {
	                std::cout << e.what() << std::endl;
	                system("pause");
	            }
	            break;

	        case 17:
	            try
	            {
	                t0 = std::chrono::system_clock::now();
	                std::cout << List<int>::heapSort(a).str() << std::endl;
	                t1 = std::chrono::system_clock::now();
	                T = t1 - t0;
	                std::cout << "Heapsort took " << T.count() << "s to complete." << std::endl;
	            }
	            catch (std::out_of_range& e)
	            {
	                std::cout << e.what() << std::endl;
	                system("pause");
	            }
				break;

	        case 18:
	            try
	            {
	                t0 = std::chrono::system_clock::now();
	                std::cout << List<int>::quickSort(a).str() << std::endl;
	                t1 = std::chrono::system_clock::now();
	                T = t1 - t0;
	                std::cout << "Quicksort took " << T.count() << "s to complete." << std::endl;
	            }
	            catch (std::out_of_range& e)
	            {
	                std::cout << e.what() << std::endl;
	                system("pause");
	            }
	            break;

	        case 19:
	            try
	            {
	                t0 = std::chrono::system_clock::now();
	                std::cout << List<int>::quickSortStable(a).str() << std::endl;
	                t1 = std::chrono::system_clock::now();
	                T = t1 - t0;
	                std::cout << "Quicksort stable took " << T.count() << "s to complete." << std::endl;
	            }
	            catch (std::out_of_range& e)
	            {
	                std::cout << e.what() << std::endl;
	                system("pause");
	            }
	            break;
        		
	        case 20:
	            try
	            {
	                std::cout << "========== Your linked list =============" << std::endl;
	                std::cout << a.print().str();
	                std::cout << "=========================================" << std::endl;
	            }
	            catch (std::out_of_range& e)
	            {
	                std::cout << e.what() << std::endl;
	                system("pause");
	            }
	            break;

	        case 21:
	            try
	            {
	                std::cout << "========== Your linked list =============" << std::endl;
	                std::cout << a.print_tree().str();
	                std::cout << "=========================================" << std::endl;
	            }
	            catch (std::out_of_range& e)
	            {
	                std::cout << e.what() << std::endl;
	                system("pause");
	            }
	            break;

	        case 22:
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
