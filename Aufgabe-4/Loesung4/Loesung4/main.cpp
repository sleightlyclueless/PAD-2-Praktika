#include "List.h"
#include "main.h"

int main()
{
    srand(time(NULL));
	
    // List<int> a;          // sorted linked List aus ints
    // List<double> a;       // sorted linked List aus ints
    // List<char> a;         // sorted linked List aus ints
    // List<std::string> a;  // sorted linked List aus ints


    List<int> a;
    a.ini(15);
    std::cout << a.print().str() << std::endl;
    List<int>::mergeSort(a);
    std::cout << a.print().str() << std::endl;
    std::cout << a.print_tree().str();
	
    bool endthis = false;       // end flag

    while (!endthis)
    {
        // Print user interface
        std::cout
            << "Welcome to your linked list (type int). You can execute the following operations:" << std::endl
            << "(1) get - get current Node" << std::endl
            << "(2) empty - check if list is empty" << std::endl
            << "(3) beginning - check if we reached lists start" << std::endl
            << "(4) end - check if we reached lists end" << std::endl
            << "(5) adv - advance pointer forward once" << std::endl
            << "(6) rec - recede pointer backwards once" << std::endl
            << "(7) reset - pointer to first" << std::endl
            << "(8) ins - insert element at current position" << std::endl
            << "(9) del - delete element at current position" << std::endl
            << "(10) print - print full list" << std::endl
            << "(11) Quit programm" << std::endl << std::endl
            << "Please choose the operation you wish to execute: ";

        // User input
        int input = get_number();
        while (input < 1 || 11 < input)
        {
            std::cout << "Please choose between the given options 1-9!" << std::endl;
            input = get_number();
        }

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
            std::cout << a.empty() << std::endl;
            std::cout << std::noboolalpha;
            break;

        case 3:
            std::cout << std::boolalpha;  // return bool as strings
            std::cout << a.beginning() << std::endl;
            std::cout << std::noboolalpha;
            break;

        case 4:
            std::cout << std::boolalpha;  // return bool as strings
            std::cout << a.end() << std::endl;
            std::cout << std::noboolalpha;
            break;

        case 5: {
            const bool flag = a.adv();
            if (flag)
                std::cout << "Pointer advanced successfully" << std::endl;
            else
            {
                std::cout << "Error in List<T>::adv(): Pointer can not advance - You reached the lists end." << std::endl;
                system("pause");
            }
        }   break;

        case 6: {
            const bool flag = a.rec();
            if (flag)
                std::cout << "Pointer receded successfully" << std::endl;
            else
            {
                std::cout << "Error in List<T>::rec(): Pointer can not recede - You reached the lists start." << std::endl;
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
                a.insSorted(x);
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

        case 9:
            if (!a.empty()) {
                a.del();
                std::cout << "Current node deleted successfully." << std::endl;
            }
            else
            {
                std::cout << "Nothing to delete." << std::endl;
                system("pause");
            }
            break;

        case 10:
            std::cout << "========== Your linked list =============" << std::endl;
            std::cout << a.print().str();
            std::cout << "=========================================" << std::endl;
            break;

        case 11:
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
